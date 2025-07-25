import streamlit as st
import pandas as pd
from sqlalchemy import create_engine, text
from sqlalchemy.exc import OperationalError
import os
import time
from dotenv import load_dotenv
from st_aggrid import AgGrid, GridOptionsBuilder

def wait_for_db(db_url: str, timeout: int = 30):
    """
    Attend que la base de données PostgreSQL soit prête à accepter les connexions.
    
    Args:
        db_url (str): URL de connexion SQLAlchemy.
        timeout (int): Temps maximal d'attente en secondes.
    """
    start_time = time.time()
    while True:
        try:
            engine = create_engine(db_url)
            with engine.connect() as connection:
                connection.execute(text("SELECT 1"))
            print("✅ Connexion à la base réussie.")
            break
        except OperationalError:
            if time.time() - start_time > timeout:
                raise Exception("⛔ La base de données n'est pas accessible après 30 secondes.")
            print("⏳ Attente de la base de données...")
            time.sleep(2)

def display_stats():
    load_dotenv()

    user = os.getenv("POSTGRES_USER")
    password = os.getenv("POSTGRES_PASSWORD")
    host = os.getenv("POSTGRES_HOST")
    port = os.getenv("POSTGRES_PORT")
    db = os.getenv("POSTGRES_DB")

    db_url = f"postgresql+psycopg2://{user}:{password}@{host}:{port}/{db}"
    
    # Attend que la DB soit prête
    wait_for_db(db_url)

    engine = create_engine(db_url)

    st.title("🎾 Tennis Stats Tracker")

    tab1, tab2 = st.tabs(["Joueurs", "Matchs"])

    with tab1:
        st.header("Liste des joueurs")
        try:
            st.header("Clique sur un joueur pour voir ses matchs")
            players_df = pd.read_sql("SELECT * FROM players", engine)
            matches_df = pd.read_sql("SELECT * FROM matches", engine)

            gb = GridOptionsBuilder.from_dataframe(players_df)
            gb.configure_selection(selection_mode="single", use_checkbox=True)
            grid_options = gb.build()

            grid_response = AgGrid(
                players_df,
                gridOptions=grid_options,
                update_mode="SELECTION_CHANGED",
                fit_columns_on_grid_load=True,
                height=300
            )

            selected = grid_response.get("selected_rows", [])
            if isinstance(selected, pd.DataFrame) and not selected.empty:
                selected_row = selected.iloc[0]
                player_name = selected_row["name"]
                st.info(f"Joueur sélectionné : {player_name}")

                player_name_lower = player_name.lower()

                player_matches = matches_df[
                    (matches_df["winner_name"].str.lower() == player_name_lower) |
                    (matches_df["loser_name"].str.lower() == player_name_lower)
                ]

                st.subheader(f"Matchs joués par {player_name}")
                st.dataframe(player_matches)
            else:
                st.info("Sélectionne un joueur pour afficher ses matchs.")

        except Exception as e:
            st.error(f"Erreur lors du chargement des joueurs : {e}")

    with tab2:
        st.header("Liste des matchs")
        try:
            matches_df = pd.read_sql("SELECT * FROM matches LIMIT 100", engine)
            st.dataframe(matches_df)
        except Exception as e:
            st.error(f"Erreur lors du chargement des matchs : {e}")

if __name__ == "__main__":
    display_stats()
