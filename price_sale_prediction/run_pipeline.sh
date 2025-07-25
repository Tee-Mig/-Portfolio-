echo "Préparation des données..."
python scripts/prep_data.py --input data/raw/raw_data.csv --output data/processed/processed_data.csv

echo "Entraînement du modèle..."
python scripts/train_model.py --data data/processed/processed_data.csv --model_output models/model.keras

echo "Prédictions sur nouvelles données..."
python scripts/predict.py --model models/model.keras --input data/processed/processed_data.csv --output outputs/predictions.csv

echo "Évaluation du modèle..."
python scripts/evaluate.py --input outputs/predictions.csv

echo "Pipeline terminée !"