from utils.api_utils import get_product_supplier
from typing import Optional, Union

def get_product_supplier1(filename: str = None) -> Optional[Union[str, bytes]]:
    return get_product_supplier("https://dummyjson.com/products/category/smartphones", filename=filename)