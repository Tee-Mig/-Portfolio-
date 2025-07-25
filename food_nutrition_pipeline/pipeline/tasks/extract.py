import luigi
from pipeline.utils.logger import get_logger  # Import de ton logger personnalisé
import requests
from dicttoxml import dicttoxml  # Pour convertir un dictionnaire en XML

# On initialise le logger avec le nom du module courant
logger = get_logger(__name__)

def get_data():
    first_page_number = 1
    page_size = 10

    url = f"https://world.openfoodfacts.org/api/v2/search?page={first_page_number}&page_size={page_size}"
    
    # Envoi d'une requête HTTP GET
    response = requests.get(url)
    
    if response.status_code == 200:
        # Conversion de la réponse JSON en XML avec un root <products>
        xml_bytes = dicttoxml(response.json(), custom_root='products', attr_type=False)
        xml_str = xml_bytes.decode("utf-8")
        return xml_str
    else:
        raise Exception(f"Erreur {response.status_code} : {response.text}")


class ExtractData(luigi.Task):
    # Paramètre de sortie configurable, par défaut dans data/raw/data.xml
    output_path = luigi.Parameter(default="data/raw/data.xml")

    def output(self):
        # Déclaration de la cible de sortie au format UTF-8
        return luigi.LocalTarget(self.output_path, format=luigi.format.UTF8)

    def run(self):
        logger.info("Extraction des données en cours...")  # Journalisation informative
        data = get_data()
        
        # Écriture des données dans le fichier de sortie
        with self.output().open("w") as f:
            f.write(data)