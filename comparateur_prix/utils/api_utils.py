import requests
from utils.file_utils import write_content_on_file
from urllib.parse import urlparse
import dicttoxml
import xml.dom.minidom
from typing import Optional, Union, Dict, Any

def get_product_supplier(
    url: str,
    params: Optional[Dict[str, Any]] = None,
    filename: Optional[str] = None,
    convert_to_xml: bool = False
) -> Optional[Union[str, bytes]]:
    response = requests.get(url, params)
    if response.status_code == 200:
        if filename is None:
            parsed = urlparse(url)
            netloc = parsed.netloc

            current_filename = netloc.split('.')[0]
        else:
            current_filename = filename
        data = response.json()
        if convert_to_xml:
            data = dicttoxml.dicttoxml(data, custom_root='products', attr_type=False)
            dom = xml.dom.minidom.parseString(data)
            data = dom.toprettyxml(indent="  ").encode("utf-8")
            current_filename += '.xml'
        else:
            current_filename += '.json'

        write_content_on_file(data, f'data/{current_filename}')
        return data
    else:
        print(f"Erreur {response.status_code} : {response.text}")