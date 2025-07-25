from flask import Flask, jsonify
import luigi
import pandas as pd
import os
from pipeline.core.analysis import see_all_datas_on_db
from pipeline.jobs.etl_pipeline import ETLPipeline
import requests
from typing import Union, Dict, Any, Tuple
from flask import Response
import subprocess
from flask import jsonify

app = Flask(__name__)

@app.route("/")
def home() -> str:
    return """
    <html>
    <head>
        <title>Bienvenue sur l'API Produits</title>
        <style>
            body {
                background-color: #f9f9f9;
                font-family: Arial, sans-serif;
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
            }
            .container {
                text-align: center;
                background-color: #ffffff;
                padding: 40px;
                border-radius: 12px;
                box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            }
            h1 {
                color: #333;
                margin-bottom: 20px;
            }
            a {
                display: block;
                margin: 10px 0;
                color: #007bff;
                text-decoration: none;
                font-size: 18px;
            }
            a:hover {
                text-decoration: underline;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1>Bienvenue sur l'API Produits</h1>
            <a href="/products">Afficher l'API des produits</a>
            <a href="/plot">Afficher le graphique</a>
        </div>
    </body>
    </html>
    """

@app.route('/run-task', methods=['GET'])
def run_task():
    try:
        result = subprocess.run(
            ["python", "-m", "luigi",
             "--module", "pipeline.jobs.etl_pipeline",
             "ETLPipeline", "--local-scheduler"],
            check=True,
            capture_output=True,
            text=True
        )
        return jsonify({
            "status": "success",
            "output": result.stdout
        })
    except subprocess.CalledProcessError as e:
        return jsonify({
            "status": "error",
            "error": e.stderr
        }), 500

@app.route("/products")
def get_products() -> Union[str, Tuple[Response, int]]:
    parquet_path = os.path.join("data", "parquet", "data.parquet")
    if not os.path.exists(parquet_path):
        return jsonify({"error": "Fichier non trouvé"}), 404

    df = pd.read_parquet(parquet_path)
    return df.head(10).to_json(orient="records")

@app.route("/plot")
def get_plot() -> str:
    img_base64 = see_all_datas_on_db()
    html = f"""
        <html>
        <head>
            <style>
                body {{
                    background-color: #f5f5f5;
                    font-family: Arial, sans-serif;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    height: 100vh;
                    margin: 0;
                }}
                .container {{
                    text-align: center;
                    background-color: #fff;
                    padding: 30px;
                    border-radius: 10px;
                    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
                }}
                h2 {{
                    color: #2c3e50;
                    margin-bottom: 20px;
                }}
                img {{
                    max-width: 100%;
                    height: auto;
                    border-radius: 6px;
                    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
                }}
            </style>
        </head>
        <body>
            <div class="container">
                <h2>Nutrition Score</h2>
                <img src="data:image/png;base64,{img_base64}" alt="Nutrition Plot"/>
            </div>
        </body>
        </html>
        """
    return html

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)