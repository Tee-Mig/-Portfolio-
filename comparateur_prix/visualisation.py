import matplotlib.pyplot as plt
import pandas as pd
from pandas import DataFrame

def show_price_distribution(df: DataFrame, product_name: str):
    df["price"] = df["price"].astype(str).str.replace("$", "", regex=False).str.strip()
    df["price"] = pd.to_numeric(df["price"], errors="coerce")
    df = df.dropna(subset=["price"])

    df_grouped = df.groupby("title", as_index=False)["price"].mean()

    df_sorted = df_grouped.sort_values(by="price", ascending=True)

    plt.figure(figsize=(11, 7))
    df_sorted = df.sort_values(by="price", ascending=True)
    plt.barh(df_sorted["title"], df_sorted["price"], color="skyblue")
    plt.xlabel("Prix ($)")
    plt.title(f"Comparaison des prix : {product_name}")
    plt.tight_layout()
    plt.show()