import luigi
import pandas as pd
import pyarrow as pa
import pyarrow.parquet as pq
from pipeline.tasks.transform import TransformData
from pipeline.utils.logger import get_logger
from lxml import etree
import os
from typing import List, Dict, Any

logger = get_logger(__name__)

def convert_into_arr_of_lst(xml_str: str) -> List[Dict[str, Any]]:
    """
    Convert an XML string to a list of dictionaries.
    Handles nested elements by flattening the structure.

    Args:
        xml_str (str): Raw XML data as a string.

    Returns:
        List[Dict[str, Any]]: A list of records parsed from the XML.
    """
    root = etree.fromstring(xml_str.encode("utf-8"))

    rows = []
    for item in root.findall("item"):
        record = {}
        for child in item:
            if len(child) == 0:
                record[child.tag] = child.text
            else:
                for sub in child:
                    key = f"{child.tag}_{sub.tag}"
                    record[key] = sub.text
        rows.append(record)
    return rows

class ConvertToParquet(luigi.Task):
    """
    Luigi task to convert transformed XML data into Parquet format.
    Depends on: TransformData
    Outputs: data/parquet/data.parquet
    """

    def requires(self) -> luigi.Task:
        """
        Specifies that this task depends on the output of TransformData.
        """
        return TransformData()

    def output(self) -> luigi.LocalTarget:
        """
        Defines the output location of the Parquet file.
        """
        return luigi.LocalTarget("data/parquet/data.parquet")

    def run(self) -> None:
        """
        Converts the transformed XML string to a pandas DataFrame,
        then saves it as a Parquet file using PyArrow.
        """
        with self.input().open("r") as f:
            data = f.read()
            logger.debug("Read transformed XML data.")

        records = convert_into_arr_of_lst(data)
        logger.info(f"Parsed {len(records)} records from XML.")

        df = pd.DataFrame(records)
        table = pa.Table.from_pandas(df)

        os.makedirs(os.path.dirname(self.output().path), exist_ok=True)
        pq.write_table(table, self.output().path)
        logger.info(f"Parquet file written to {self.output().path}")