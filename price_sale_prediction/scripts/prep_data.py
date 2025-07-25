import argparse
import pandas as pd

def preprocess(input_path, output_path):
    print(f"Chargement des données brutes depuis {input_path} ...")
    df = pd.read_csv(input_path)
    
    if 'date' in df.columns:
        df['date'] = pd.to_datetime(df['date'], errors='coerce')
        df = df.dropna(subset=['date'])
        
        df['day_of_week'] = df['date'].dt.dayofweek
        
        df['month'] = df['date'].dt.month
    
    df = df.dropna()
    
    df = df[pd.to_numeric(df['target'], errors='coerce').notnull()]
    
    print(f"Données nettoyées : {df.shape[0]} lignes restantes.")
    
    print(f"Sauvegarde des données traitées dans {output_path} ...")
    df.to_csv(output_path, index=False)
    print("Préparation terminée.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Préparation et nettoyage des données")
    parser.add_argument('--input', type=str, required=True, help="data/raw/raw_data.csv")
    parser.add_argument('--output', type=str, required=True, help="data/processed/processed_data.csv")
    args = parser.parse_args()
    
    preprocess(args.input, args.output)