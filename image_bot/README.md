# Image Automation Bot

Ce projet permet d'automatiser des interactions graphiques sur écran (clics, détections, drag-and-drop) à l’aide de modèles d’images et de reconnaissance visuelle avec OpenCV, PIL et PyAutoGUI.

## Fonctionnalités principales

- 🔍 **Détection d’image à l’écran** avec précision configurable
- 🎯 **Clics automatisés** sur des images avec position aléatoire dans une zone définie
- 🔁 **Clics conditionnels** jusqu’à détection d’un pixel rouge ou de changements d’écran
- 🧠 **Filtrage intelligent** des correspondances proches pour éviter les doublons
- 🧱 **Drag and drop** entre deux zones avec vérification de stabilité de l’écran
- 🔐 **Sécurité des clics** avec vérification de la similarité couleur et des dimensions

## Technologies

- Python 3
- OpenCV
- NumPy
- PIL (Pillow)
- PyAutoGUI

## Structure

- `find_img()`, `find_img_with_red_top_right()` : détection d’image avec ou sans vérification de pixels rouges.
- `click_img()` : clics automatisés sur image avec logiques avancées.
- `drag_and_drop_with_random_area()` : glisser-déposer contrôlé entre deux zones.
- Fonctions annexes : `has_screen_changed()`, `click_until_pixel_color_detected()`, etc.

## Lancement

pip install -r requirements.txt
python main.py
