import duckdb
from pathlib import Path

parquet_file = Path("lake/air_pollution.parquet")

con = duckdb.connect()

query = f"""
SELECT
    country,
    city,
    COUNT(*) AS days_measured,
    ROUND(AVG(pm25), 2) AS avg_pm25
FROM read_parquet('{parquet_file}')
GROUP BY country, city
ORDER BY avg_pm25 DESC
"""

df = con.execute(query).fetchdf()

print("[📊] Résultats depuis fichier parquet local :")
print(df)