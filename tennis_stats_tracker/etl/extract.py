import pandas as pd
import wget
import os

def extract_matches(file_path: str) -> pd.DataFrame:
    """
    Lit un fichier CSV de matches ATP et retourne un DataFrame Pandas.

    Args:
        filepath (str or Path): Chemin vers le fichier CSV (ex: "data/atp_matches_2023.csv")

    Returns:
        DataFrame contenant les données brutes du fichier CSV
    """
    try:
        url = "https://raw.githubusercontent.com/JeffSackmann/tennis_atp/master/atp_matches_2024.csv"

        if os.path.exists(file_path) is False:
            wget.download(url, out=file_path)

        df = pd.read_csv(file_path, encoding="ISO-8859-1")
        return df
    except FileNotFoundError:
        print(f"Fichier non trouvé : {file_path}")
        raise
    except Exception as e:
        print(f"Erreur lors du chargement : {e}")
        raise