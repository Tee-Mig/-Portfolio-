from utils.api_utils import get_product_supplier
from typing import Optional, Union

def get_product_supplier3(api_key: str, filename: str = None) -> Optional[Union[str, bytes]]:
    params = {
        "engine": "google_shopping",
        "q": "coca cola 1.5L",
        "hl": "fr",
        "gl": "fr",
        "api_key": api_key
    }
    
    return get_product_supplier("https://serpapi.com/search", params, filename)