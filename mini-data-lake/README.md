# Mini Data Lake - Analyse de la pollution de l'air

Ce projet illustre la création d’un mini Data Lake pour analyser des données de pollution atmosphérique, en utilisant Python, DuckDB, et GitHub pour le stockage.

---

## Objectifs

- Nettoyer des données brutes CSV
- Convertir les données nettoyées en format Parquet optimisé
- Héberger le fichier Parquet sur GitHub (dépôt public)
- Interroger les données Parquet localement ou à distance avec DuckDB via SQL
- Visualiser les résultats avec matplotlib

---

## Utilisation

### 1. Nettoyage des données

python scripts/clean_data.py

### 2. Conversion en Parquet

python scripts/upload_to_duckdb_lake.py

### 3. Pousser le fichier Parquet sur GitHub

python scripts/push_parquet.py

### 4. Requête sur fichier local

python scripts/query_duckdb.py

### 5. Requête sur fichier distant (GitHub)

python scripts/query_duckdb_cloud.py

### 6. Visualisation

python scripts/visualize_pollution.py

### Prérequis

- Python 3.7+
- Librairies Python : pandas, duckdb, matplotlib, gitpython (pour push_parquet.py)
- Git installé et configuré
