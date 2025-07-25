import io
import base64
import numpy as np
import sqlite3
import pandas as pd
import matplotlib.pyplot as plt
from pandas import DataFrame, Series
from typing import List, Dict, Any

def print_specific_columns(df: DataFrame, cols_to_print: List[str] = ["nutriments_sugars_100g", "nutriments_fat_100g"]) -> None:
    available_cols: List[str] = [col for col in cols_to_print if col in df.columns]
    print(df[available_cols])


def print_all_data_in_chunk(df: DataFrame, chunk_size: int = 3) -> None:
    num_cols: int = len(df.columns)
    for i in range(0, num_cols, chunk_size):
        chunk: DataFrame = df.iloc[:, i:i+chunk_size]
        print(f"Columns {i + 1} to {min(i + chunk_size, num_cols)}:")
        print(chunk.head())  # Or .to_string(index=False) for cleaner output
        print("-" * 40)


def get_custom_nutrition_score(row: Series) -> float:
    recommended: Dict[str, float] = {
        "nutriments_energy_100g": 500,
        "nutriments_fat_100g": 15,
        "nutriments_saturated-fat_100g": 5,
        "nutriments_carbohydrates_100g": 30,
        "nutriments_sugars_100g": 5,
        "nutriments_fiber_100g": 2.5,
        "nutriments_proteins_100g": 5,
        "nutriments_salt_100g": 0.3,
        "nutriments_sodium_100g": 0.12
    }
    score: float = 0
    count: int = 0
    for nutrient, rec_val in recommended.items():
        val: Any = row.get(nutrient)
        if val is not None and not pd.isna(val):
            try:
                val = float(val)
            except (ValueError, TypeError):
                continue
            diff: float = abs(val - rec_val) / rec_val
            score += diff
            count += 1
    if count == 0:
        return np.nan
    return score / count


def see_all_datas_on_db() -> None:
    with sqlite3.connect("data/foods_nutrition.db") as conn:
        df: DataFrame = pd.read_sql_query("SELECT * FROM foods_nutrition LIMIT 20", conn)

    df["nutrition_score"] = df.apply(lambda row: get_custom_nutrition_score(row), axis=1)
    df = df.dropna(subset=["nutrition_score"])

    plt.figure(figsize=(12, 6))
    plt.bar(df["product_name"], df["nutrition_score"], color="skyblue")
    plt.xticks(rotation=45, ha="right")
    plt.xlabel("Product")
    plt.ylabel("Nutrition Score (Lower is Better)")
    plt.title("Score According Nutrition of Food Products")
    plt.tight_layout()
    plt.show()

    # Sauvegarde du graphique en mémoire (buffer)
    buf = io.BytesIO()
    plt.savefig(buf, format="png")
    plt.close()
    buf.seek(0)

    # Encodage en base64 pour affichage HTML
    img_base64 = base64.b64encode(buf.read()).decode('utf-8')
    return img_base64
