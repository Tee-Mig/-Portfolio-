# Tennis Stats Tracker 🎾

Application Streamlit pour visualiser des statistiques de matchs de tennis à partir de données ATP.  
Le projet inclut un pipeline ETL pour extraire, nettoyer, transformer et charger les données dans une base PostgreSQL,  
puis une interface web interactive pour explorer joueurs et matchs.

---

## Table des matières

- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Configuration](#configuration)
- [Utilisation](#utilisation)
- [Structure du projet](#structure-du-projet)
- [Dépendances](#dépendances)
- [Licence](#licence)

---

## Fonctionnalités

- Chargement des données ATP depuis CSV
- Nettoyage et transformation des données (extraction des joueurs, liens entre joueurs et matchs)
- Stockage dans une base PostgreSQL via SQLAlchemy
- Interface web Streamlit avec :
  - Liste interactive des joueurs
  - Affichage des matchs liés à un joueur sélectionné
  - Liste des matchs récents
- Support Docker avec conteneurs pour PostgreSQL et Streamlit

---

### Configuration du .env

POSTGRES_USER=ton_utilisateur
POSTGRES_PASSWORD=ton_mot_de_passe
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
POSTGRES_DB=db

### Prérequis

- Python 3.8+
- Docker & Docker Compose (optionnel mais recommandé)
- PostgreSQL (si non utilisé via Docker)

### Dependences principales

- pandas
- sqlalchemy
- psycopg2-binary
- streamlit
- python-dotenv
- st-aggrid

### Installation manuelle

cd tennis-stats-tracker
pip install -r requirements.txt
docker-compose up --build
