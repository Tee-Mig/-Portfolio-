#! C:\Users\migue\AppData\Local\Programs\Python\Python312\python.exe

import sqlite3
import pandas as pd
from dotenv import load_dotenv
import os
from api_clients.supplier1 import get_product_supplier1
from api_clients.supplier2 import get_product_supplier2
from api_clients.supplier3 import get_product_supplier3
from utils.file_utils import load_file
import xml.etree.ElementTree as ET
from tabulate import tabulate
from typing import Union, List, Dict, Optional
from db import save_to_csv, save_to_sqlite
from visualisation import show_price_distribution

def print_all_products(data: Dict[int, Union[Dict[str, Union[str, float, int, None]], ET.Element]]) -> None:
    print("source 1:")
    for elem in data[1]["products"]:
        print(elem["title"])

    print("\nsource 2:")
    for elem in data[2].findall("item"):
        title = elem.find("title")
        if title is not None and title.text:
            print(title.text.strip())

    print("\nsource 3:")
    for elem in data[3]["shopping_results"]:
        print(elem["title"])

def get_data(data: Union[List[Dict[str, Union[str, float, int, None]]], ET.Element], product_to_compare: str) -> List[Dict[str, Optional[str]]]:
    processed_data = []
    if isinstance(data, list):
        for item in data:
            if product_to_compare.lower() in item.get("title", "").lower():
                processed_data.append({
                "title": item.get("title", None),
                "price": f"{str(item.get("price", None))}$",
                "brand": item.get("brand", None),
                "category": item.get("category", None),
                "rate": item.get("rating", None)
            })
    elif isinstance(data, ET.Element):
        for item in data.findall("item"):
            title = item.find("title")
            if (title is not None and product_to_compare.lower() in title.text.lower()):
                processed_data.append({
                    "title": item.find("title").text if item.find("title") is not None else None,
                    "price": f"{str(item.find("price").text)}$" if item.find("price") is not None else None,
                    "brand": item.find("brand").text if item.find("brand") is not None else None,
                    "category": item.find("category").text if item.find("category") is not None else None,
                    "rate": item.find("rating").find("rate").text if item.find("rating").find("rate") is not None else None,
                })
    return processed_data

def compare_prices():
    load_dotenv()
    api_key: Optional[str] = os.getenv("API_KEY_SERPAPI")
    data: Dict[int, Union[Dict[str, Union[str, float, int, None]], ET.Element]] = {}

    filenames: Dict[int, str] = {
        1: "data/dummyjson.json",
        2: "data/fakestoreapi.xml",
        3: "data/serpapi.json"
    }
    supplier_functions: Dict[int, Optional[Union[str, bytes]]] = {
        1: lambda: get_product_supplier1(), # json format
        2: lambda: get_product_supplier2(convert_to_xml=True), # xml formal
        3: lambda: get_product_supplier3(api_key) # json format with api key
    }

    for i in range (1, 4):
        if os.path.exists(filenames[i]):
            data[i] = load_file(filenames[i])
        else:
            data[i] = supplier_functions[i]()

    product: str = None
    while (product is None or product == "see"):
        product = str(input("What product do you want to compare the price ? Put 'see' to see all the products available:\n"))
        if (product == "see"):
            print_all_products(data)

    processed_data1 = get_data(data[1]["products"], product)
    processed_data2 = get_data(data[2], product)
    processed_data3 = get_data(data[3]["shopping_results"], product)

    # add source and fix printing
    for item in processed_data1:
        item['source'] = 'dummyjson'
    for item in processed_data2:
        item['source'] = 'fakestorejson'
    for item in processed_data3:
        item['source'] = 'serpapi'
        item['price'] = item['price'].replace(' â‚¬', '')

    if processed_data1 == [] and processed_data2 == [] and processed_data3 == []:
        print("There no product to compare")
    else:
        df = pd.DataFrame(processed_data1 + processed_data2 + processed_data3)
        pd.set_option("display.colheader_justify", "center")

        print(tabulate(df, headers='keys', tablefmt='fancy_grid', showindex=False))

        # save
        save_to_csv(df, "data/result.csv")
        save_to_sqlite(df, "data/products.db", table_name="products")

        # Visualisation
        show_price_distribution(df, product)

def read_db(filename):
    conn = sqlite3.connect(filename)

    tables = pd.read_sql_query("SELECT name FROM sqlite_master WHERE type='table';", conn)
    print(f"All tables:\n{tables}\n")

    df = pd.read_sql_query(f"SELECT * FROM products;", conn)
    print(f"Table:\n{df.head()}")

    conn.close()

def main() -> int:
    compare_prices()
    read_db("data/products.db")

    print("Fin")
    return 0

if __name__ == "__main__":
    main()