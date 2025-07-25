#! C:\Users\migue\AppData\Local\Programs\Python\Python312\python.exe

from etl.extract import extract_matches
from etl.transform import clean_match_data, split_players
import pandas as pd
from etl.load import load_data_to_postgres
from dotenv import load_dotenv
import os
from sqlalchemy import create_engine

def main():
    load_dotenv()

    user = os.getenv("POSTGRES_USER")
    password = os.getenv("POSTGRES_PASSWORD")
    host = os.getenv("POSTGRES_HOST")
    port = os.getenv("POSTGRES_PORT")
    db = os.getenv("POSTGRES_DB")

    file_path = "data/atp_matches_2024.csv"
    raw_df  = extract_matches(file_path)
    cleaned_df = clean_match_data(raw_df)
    all_players, matches_data = split_players(cleaned_df)

    # print(all_players.head(3))
    print(matches_data.head(3))

    db_url = f"postgresql+psycopg2://{user}:{password}@{host}:{port}/{db}"

    print(matches_data.head(5))

    load_data_to_postgres(all_players, matches_data, db_url)

if __name__ == "__main__":
    main()