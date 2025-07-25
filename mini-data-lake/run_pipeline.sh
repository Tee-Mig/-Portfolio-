echo "[1] Nettoyage des données"
python scripts/clean_data.py

echo "[2] Upload vers le Cloud"
python scripts/generate_parquet.py 

echo "[3] Fichier poussé sur GitHub."
python scripts/push_parquet.py

echo "[4] Reqiete local"
python scripts/query_duckdb.py

echo "[5] Requete distance"
python scripts/query_duckdb_cloud.py

echo "[5] Visualisation des donnees"
python scripts/visualize_pollution.py

echo "[✔] Pipeline terminée"