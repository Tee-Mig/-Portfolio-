import json
import os
import xml.etree.ElementTree as ET
from typing import Any, Union

def write_content_on_file(content: Union[dict, list, bytes], filename: str) -> None:
    os.makedirs(os.path.dirname(filename), exist_ok=True)

    if filename.endswith(".xml"):
        with open(filename, "wb") as file:
            file.write(content)
    else:
        with open(filename, "w", encoding="utf-8") as file:
            json.dump(content, file, indent=2, ensure_ascii=False)

def load_file(filename: str) -> Union[ET.Element, Any]:
    if filename.endswith(".xml"):
        return ET.parse(filename).getroot()
    elif filename.endswith(".json"):
        with open(filename, "r") as file:
            return json.load(file)