import luigi
import json
from pipeline.tasks.extract import ExtractData
from pipeline.utils.logger import get_logger
from lxml import etree
from typing import Dict, List, Optional

logger = get_logger(__name__)

def build_tag_tree(paths: List[str]) -> Dict[str, dict]:
    tree: Dict[str, dict] = {}
    for path in paths:
        parts = path.split('/')
        node = tree
        for part in parts:
            node = node.setdefault(part, {})
    return tree

def remove_empty_tags(root: etree.Element) -> None:
    stack: List[etree.Element] = [root]
    to_remove: List[tuple[etree.Element, etree.Element]] = []

    while stack:
        current = stack.pop()
        for child in list(current):
            stack.append(child)
            is_empty_text = child.text is None or not child.text.strip()
            is_empty_children = len(child) == 0
            if is_empty_text and is_empty_children:
                to_remove.append((current, child))

    for parent, child in to_remove:
        parent.remove(child)

def clean_xml(xml_str: str) -> str:
    parser = etree.XMLParser(remove_blank_text=True)
    root: etree.Element = etree.fromstring(xml_str.encode('utf-8'), parser)
    tags_to_keep: List[str] = [
        "_id",
        "product_name",
        "ingredients_text",
        "ingredients_tags",
        "nutriments/energy_100g",
        "nutriments/fat_100g",
        "nutriments/saturated-fat_100g",
        "nutriments/carbohydrates_100g",
        "nutriments/sugars_100g",
        "nutriments/fiber_100g",
        "nutriments/proteins_100g",
        "nutriments/salt_100g",
        "nutriments/sodium_100g",
        "nutrition_grades",
    ]

    tag_tree: Dict[str, dict] = build_tag_tree(tags_to_keep)

    products: Optional[etree.Element] = root.find("products")
    if products is None:
        return etree.tostring(root, pretty_print=True, encoding="utf-8").decode("utf-8")
    else:
        root = products

    for item in root.findall("item"):
        for child in list(item):
            if child.tag in tag_tree:
                allowed_subtags = tag_tree[child.tag]
                if allowed_subtags:
                    for sub in list(child):
                        if sub.tag not in allowed_subtags:
                            child.remove(sub)
                    if len(child) == 0:
                        item.remove(child)
            else:
                item.remove(child)

    remove_empty_tags(root)

    for elem in root.iter():
        if elem.text:
            elem.text = elem.text.strip().lower()

    return etree.tostring(root, pretty_print=True, encoding="utf-8").decode("utf-8")

class TransformData(luigi.Task):
    def requires(self) -> luigi.Task:
        return ExtractData()

    def output(self) -> luigi.LocalTarget:
        return luigi.LocalTarget("data/processed/data_transformed.xml", format=luigi.format.UTF8)

    def run(self) -> None:
        with self.input().open("r") as infile:
            data: str = infile.read()
        logger.info("Transformation des données...")
        data = clean_xml(data)
        with self.output().open("w") as f:
            f.write(data)