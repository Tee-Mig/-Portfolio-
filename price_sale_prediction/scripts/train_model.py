import argparse
import pandas as pd
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
import joblib
import os
from tensorflow.keras.callbacks import EarlyStopping

def main(args):
    print("Chargement des données...")
    df = pd.read_csv(args.data)

    X = df.drop(columns=["title", "target"])
    y = df["target"]

    categorical_features = ["platform", "genre"]
    numerical_features = ["release_year", "metacritic_score", "player_count"]

    preprocessor = ColumnTransformer([
        ("num", StandardScaler(), numerical_features),
        ("cat", OneHotEncoder(sparse_output=False, handle_unknown="ignore"), categorical_features)
    ])

    print("Prétraitement des données...")
    X_processed = preprocessor.fit_transform(X)

    os.makedirs(os.path.dirname(args.model_output), exist_ok=True)
    joblib.dump(preprocessor, args.model_output + "_preprocessor.pkl")

    X_train, X_val, y_train, y_val = train_test_split(X_processed, y, test_size=0.2, random_state=42)

    model = tf.keras.Sequential([
        tf.keras.layers.Dense(64, activation='relu', input_shape=(X_train.shape[1],)),
        tf.keras.layers.Dense(32, activation='relu'),
        tf.keras.layers.Dense(1)
    ])

    model.compile(optimizer='adam', loss='mse', metrics=['mae'])

    early_stop = EarlyStopping(
        monitor='val_loss',
        patience=5,
        restore_best_weights=True
    )

    print("Entraînement du modèle...")
    model.fit(X_train, y_train, validation_data=(X_val, y_val), epochs=150, batch_size=8, callbacks=[early_stop], verbose=1)

    print("Évaluation du modèle sur le jeu de validation...")
    loss, mae = model.evaluate(X_val, y_val, verbose=1)
    print(f"MAE sur validation : {mae:.2f} €")

    print(f"Sauvegarde du modèle dans {args.model_output} ...")
    model.save(args.model_output)
    print("Modèle et préprocesseur sauvegardés.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Entraînement d'un modèle TensorFlow")
    parser.add_argument('--data', type=str, required=True, help="Chemin vers le CSV de données préparées")
    parser.add_argument('--model_output', type=str, required=True, help="Chemin pour sauvegarder le modèle")
    args = parser.parse_args()
    main(args)
