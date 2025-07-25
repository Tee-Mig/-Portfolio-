import argparse
import pandas as pd
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
import numpy as np

def main(args):
    print("Chargement des prédictions...")
    df = pd.read_csv(args.input)

    if "target" not in df.columns:
        raise ValueError("La colonne 'target' (valeurs réelles) est manquante dans le fichier.")

    if "predicted_price" not in df.columns:
        raise ValueError("La colonne 'predicted_price' (prédictions) est manquante dans le fichier.")

    y_true = df["target"]
    y_pred = df["predicted_price"]

    print("Calcul des métriques...")
    mae = mean_absolute_error(y_true, y_pred)
    rmse = np.sqrt(mean_squared_error(y_true, y_pred))
    r2 = r2_score(y_true, y_pred)

    print("\n🎯 Évaluation du modèle :")
    print(f"📉 MAE  (Mean Absolute Error)       : {mae:.2f} €")
    print(f"📏 RMSE (Root Mean Squared Error)   : {rmse:.2f} €")
    print(f"📈 R²   (Coefficient de détermination): {r2:.4f}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Évaluation des performances du modèle")
    parser.add_argument('--input', type=str, required=True, help="CSV contenant target et predicted_price")
    args = parser.parse_args()
    main(args)