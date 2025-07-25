from sqlalchemy import create_engine
from sqlalchemy.exc import SQLAlchemyError
import pandas as pd

def load_data_to_postgres(players_df, matches_df, db_url: str):
    """
    Charge les DataFrames players et matches dans une base PostgreSQL.

    Args:
        players_df (pd.DataFrame): DataFrame contenant les joueurs (player_id, name)
        matches_df (pd.DataFrame): DataFrame contenant les matchs enrichis (avec winner_id, loser_id, etc.)
        db_url (str): URL de connexion PostgreSQL, exemple: postgresql://user:password@host:port/dbname

    Raises:
        SQLAlchemyError en cas de problème de connexion ou d'insertion
    """
    try:
        engine = create_engine(db_url)

        players_df.to_sql('players', engine, if_exists='replace', index=False)
        print(f"{len(players_df)} joueurs insérés.")

        matches_df.to_sql('matches', engine, if_exists='replace', index=False)
        print(f"{len(matches_df)} matchs insérés.")

        print("Chargement des données terminé avec succès.")

        players_df = pd.read_sql("SELECT * FROM players", engine)
        print(players_df)

    except SQLAlchemyError as e:
        print("Erreur lors du chargement dans PostgreSQL :", e)
        raise