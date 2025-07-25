import duckdb
import matplotlib.pyplot as plt

REMOTE_PARQUET = "https://raw.githubusercontent.com/Tee-Mig/mini-data-lake/main/air_pollution.parquet"

query = f"""
    SELECT country, city, COUNT(*) AS days_measured, ROUND(AVG(pm25), 2) AS avg_pm25
    FROM read_parquet('{REMOTE_PARQUET}')
    GROUP BY country, city
    ORDER BY avg_pm25 DESC
    LIMIT 10
"""

con = duckdb.connect()
df = con.execute(query).fetchdf()

print("[🌍] Résultats depuis un fichier distant hébergé sur GitHub :")
print(df)

# Visualisation matplotlib
plt.figure(figsize=(12, 6))
plt.bar(df['city'] + " (" + df['country'] + ")", df['avg_pm25'], color='skyblue')
plt.xticks(rotation=45, ha='right')
plt.xlabel('Ville (Pays)')
plt.ylabel('Moyenne PM2.5')
plt.title('Top 10 des villes avec la moyenne de pollution PM2.5')
plt.tight_layout()
plt.show()