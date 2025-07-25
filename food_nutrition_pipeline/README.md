# Food Nutrition Pipeline

Un pipeline de données automatisé pour extraire, transformer et analyser les informations nutritionnelles des produits alimentaires à partir de l'API Open Food Facts.

# Description

Ce projet est un exemple d’orchestration de pipeline ETL (Extract, Transform, Load) utilisant **Luigi** en local pour automatiser l'extraction, la transformation et le chargement de données alimentaires, et **Flask** pour exposer les résultats via une API web.

## Fonctionnalités principales

- Extraction des données depuis l'API Open Food Facts
- Nettoyage et transformation des données XML
- Conversion en format Parquet pour un stockage efficace
- Chargement dans une base SQLite locale
- API Flask pour consulter les données et afficher un graphique nutritionnel
- Orchestration des étapes ETL avec Luigi en local

## Libraries/Technologies

- luigi
- pandas
- lxml
- pyarrow
- matplotlib
- sqlalchemy
- flask
- docker
- gitlab-ci

## Installation

pip install -r requirements.txt

## Utilisations

- docker-compose up --build
- python main.py directement dans le terminal

## Utiliser l’API Flask

Accéder à l’API produit :

- http://localhost:5000/products

Afficher le graphique nutritionnel :

- http://localhost:5000/plot

Déclencher la pipeline via l’API :

- http://localhost:5000/run-task

Page d’accueil :

- http://localhost:5000/
