import duckdb

REMOTE_PARQUET = "https://raw.githubusercontent.com/Tee-Mig/mini-data-lake/main/air_pollution.parquet"

query = f"""
    SELECT country, city, COUNT(*) AS days_measured, ROUND(AVG(pm25), 2) AS avg_pm25
    FROM read_parquet('{REMOTE_PARQUET}')
    GROUP BY country, city
    ORDER BY avg_pm25 DESC
"""

con = duckdb.connect()
df = con.execute(query).fetchdf()

print("[🌍] Résultats depuis un fichier distant hébergé sur GitHub :")
print(df)