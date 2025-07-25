import pandas as pd
from typing import Tuple

def clean_match_data(df: pd.DataFrame) -> pd.DataFrame:
    """
    Nettoie et prépare les données de matchs pour insertion en base de données.
    
    - Garde les colonnes essentielles
    - Convertit les types
    - Supprime les lignes avec données critiques manquantes

    Args:
        df: DataFrame brut extrait du CSV

    Returns:
        DataFrame nettoyé prêt pour insertion
    """
    # Sélection des colonnes utiles
    columns = [
        "tourney_id", "tourney_name", "surface", "tourney_level", "tourney_date",
        "match_num", "round", "score", "minutes",
        "winner_name", "loser_name",
        "w_ace", "w_df", "w_1stIn", "w_1stWon", "w_bpSaved", "w_bpFaced",
        "l_ace", "l_df", "l_1stIn", "l_1stWon", "l_bpSaved", "l_bpFaced",
        "winner_rank", "loser_rank"
    ]
    df = df[columns].copy()

    # Conversion de la date au format standard
    df["tourney_date"] = pd.to_datetime(df["tourney_date"], format="%Y%m%d", errors="coerce")

    # Suppression des lignes critiques nulles
    df = df.dropna(subset=["winner_name", "loser_name", "tourney_date", "score"])

    # Nettoyage des noms de joueurs
    df["winner_name"] = df["winner_name"].str.strip()
    df["loser_name"] = df["loser_name"].str.strip()

    # Durée en entier (certains fichiers ont des valeurs nulles ou float)
    df["minutes"] = pd.to_numeric(df["minutes"], errors="coerce").fillna(0).astype(int)

    return df


def split_players(df: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
    winners = df["winner_name"].dropna().unique()
    losers = df["loser_name"].dropna().unique()
    all_players = pd.Series(list(set(winners).union(set(losers))), name="name")
    all_players = all_players.to_frame()

    # Normalize player names in all_players
    all_players["name"] = all_players["name"].str.lower().str.strip()

    # Remove duplicates just in case
    all_players = all_players.drop_duplicates(subset=["name"]).sort_values("name").reset_index(drop=True)

    # Create player_id
    all_players["player_id"] = all_players.index + 1

    # Normalize names in df for merging
    df["winner_name"] = df["winner_name"].str.lower().str.strip()
    df["loser_name"] = df["loser_name"].str.lower().str.strip()

    # Merge to add winner_id and loser_id
    df = df.merge(
        all_players.rename(columns={"name": "winner_name", "player_id": "winner_id"}),
        on="winner_name",
        how="left"
    )
    df = df.merge(
        all_players.rename(columns={"name": "loser_name", "player_id": "loser_id"}),
        on="loser_name",
        how="left"
    )

    return all_players, df
