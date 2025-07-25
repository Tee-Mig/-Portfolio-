import luigi
import pandas as pd
from sqlalchemy import create_engine  # Pour se connecter à SQLite
from pipeline.tasks.convert_parquet import ConvertToParquet  # Tâche précédente de conversion
from pipeline.utils.logger import get_logger  # Logger personnalisé

# Création d'un logger spécifique à ce module
logger = get_logger(__name__)

class LoadData(luigi.Task):
    def requires(self):
        # Cette tâche dépend de ConvertToParquet
        return ConvertToParquet()

    def output(self):
        # Fichier témoin qui indique que la tâche s'est terminée avec succès
        return luigi.LocalTarget("data/load_complete.txt")

    def run(self):
        # Lecture du fichier Parquet produit par la tâche précédente
        logger.info("Chargement du fichier Parquet en cours...")
        df = pd.read_parquet(self.input().path)

        # Connexion à la base de données SQLite (créée si elle n'existe pas)
        logger.info("Connexion à la base SQLite et insertion des données...")
        engine = create_engine("sqlite:///data/foods_nutrition.db")

        # Chargement des données dans la table 'foods_nutrition'
        df.to_sql("foods_nutrition", con=engine, if_exists="replace", index=False)

        # Création du fichier de sortie (indicateur que la tâche est finie)
        with self.output().open("w") as f:
            f.write("Chargement terminé")
        logger.info("Données chargées avec succès dans SQLite.")