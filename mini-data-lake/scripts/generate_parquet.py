import pandas as pd
from pathlib import Path

input_csv = Path("data/clean/air_pollution_clean.csv")
output_parquet = Path("lake/air_pollution.parquet")

output_parquet.parent.mkdir(parents=True, exist_ok=True)

df = pd.read_csv(input_csv)

df.to_parquet(output_parquet, index=False)

print(f"[✔] Données converties en Parquet dans {output_parquet}")