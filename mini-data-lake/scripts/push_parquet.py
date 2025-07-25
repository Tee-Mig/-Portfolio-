from git import Repo
from pathlib import Path

repo_dir = Path(r"C:\Users\migue\OneDrive\Bureau\info\python\data_engineering\mini-data-lake\my_git")
file_path = repo_dir / 'air_pollution.parquet'

repo = Repo(repo_dir)

repo.index.add([str(file_path)])

repo.index.commit('Mise à jour du fichier air_pollution.parquet')

origin = repo.remote(name='origin')
origin.push()

print("✅ Fichier poussé sur GitHub.")