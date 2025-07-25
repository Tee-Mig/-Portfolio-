from utils.api_utils import get_product_supplier
from typing import Optional, Union

def get_product_supplier2(filename: str = None, convert_to_xml: bool = False) -> Optional[Union[str, bytes]]:
    get_product_supplier("https://fakestoreapi.com/products/category/electronics", filename=filename, convert_to_xml=convert_to_xml)