import pandas as pd
from pathlib import Path

# === Chemins ===
input_path = Path("data/raw/air_pollution_raw.csv")
output_path = Path("data/clean/air_pollution_clean.csv")
output_path.parent.mkdir(parents=True, exist_ok=True)

# === Lecture des données ===
df = pd.read_csv(input_path)

# === Nettoyage ===
df["date"] = pd.to_datetime(df["date"], errors="coerce")
df = df.dropna(subset=["city", "country", "date", "pm25"])  # lignes incomplètes
df = df[df["pm25"] >= 0]  # supprimer les valeurs négatives

# === Ajout d'une colonne : catégorie de pollution ===
def classify_pm25(value):
    if value <= 12:
        return "Good"
    elif value <= 35.4:
        return "Moderate"
    elif value <= 55.4:
        return "Unhealthy for Sensitive Groups"
    else:
        return "Unhealthy"

df["pm25_category"] = df["pm25"].apply(classify_pm25)

# === Sauvegarde des données nettoyées ===
df.to_csv(output_path, index=False)
print(f"[✔] Données nettoyées sauvegardées dans {output_path}")