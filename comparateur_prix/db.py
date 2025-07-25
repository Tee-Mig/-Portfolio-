import pandas as pd
import sqlite3
from pandas import DataFrame

def save_to_csv(df: DataFrame, filename: str) -> None:
    df.to_csv(filename, index=False)
    print(f"[✔] Données enregistrées dans {filename}")

def save_to_sqlite(df: DataFrame, db_name: str, table_name: str = "products") -> None:
    conn = sqlite3.connect(db_name)
    df.to_sql(table_name, conn, if_exists="replace", index=False)
    conn.close()
    print(f"[✔] Données enregistrées dans la base {db_name} ({table_name})")