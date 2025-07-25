from src.click import click_img, drag_and_drop_with_random_area, click_coords
from src.constants import (
    DEFAULT_FAST_RECLICK_TIME,
    DEFAULT_CONFIDENCE,
)
from src.screen import find_img
from src.packs import remove_packs
from src.packs import NOT_SHOW_TODAY_DUNGEON
import pytesseract
from src.arena import go_to_arena

import cv2
import numpy as np
import pyautogui
import os
import re

from PIL import ImageGrab, Image

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# Constants
# SUBS_REGION1 = (415, 600, 675, 174)
SUBS_REGION1 = (415, 600, 1090, 774)

# Match threshold
MATCH_THRESHOLD = 0.8
MIN_DISTANCE = 20  # pixels


def normalize_line(line):
    return (
        line.lower()
        .replace(" ", "")
        .replace("é", "e")
        .replace("è", "e")
        .replace("ê", "e")
        .replace("à", "a")
        .replace("î", "i")
    )


def should_keep_rune(lines):
    normalized = [normalize_line(line) for line in lines]

    def is_percentage_stat(line, keywords):
        return any(line.startswith(k + "+") and line.endswith("%") for k in keywords)

    group1_keywords = ["pv", "def", "atq", "vit"]
    group2_keywords = ["txcritiq", "dgtscritiq", "atq", "vit"]

    group1_matches = sum(
        1 for line in normalized if is_percentage_stat(line, group1_keywords)
    )
    group2_matches = sum(
        1
        for line in normalized
        if any(k in line for k in group2_keywords if k != "atq")
        or is_percentage_stat(line, ["atq"])
    )
    has_vit = any("vit" in line for line in normalized)

    return group1_matches >= 2 or group2_matches >= 2 or has_vit


def extract_text_from_screenshot_runes_dj():
    screenshot = ImageGrab.grab(bbox=SUBS_REGION1)
    open_cv_image = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)

    gray = cv2.cvtColor(open_cv_image, cv2.COLOR_BGR2GRAY)

    # Contrast enhancement (amplify difference between text & background)
    contrasted = cv2.equalizeHist(gray)

    blurred = cv2.GaussianBlur(contrasted, (3, 3), 0)

    # Slightly lower threshold (retain tail of 'q')
    _, thresh = cv2.threshold(blurred, 128, 255, cv2.THRESH_BINARY)

    # Softer sharpening (less aggressive than before to preserve text shape)
    kernel = np.array([[0, -0.6, 0], [-0.6, 4.2, -0.6], [0, -0.6, 0]])
    sharpened = cv2.filter2D(thresh, -1, kernel)

    # Small dilation helps define tail curves in q/p/y
    dilated = cv2.dilate(sharpened, np.ones((1, 1), np.uint8), iterations=1)

    processed_image = Image.fromarray(dilated)

    text = pytesseract.image_to_string(processed_image, lang="eng+fra")
    raw_lines = [line.strip() for line in text.split("\n") if line.strip()]

    # Post-OCR typo correction
    typo_corrections = {
        "tigq.": "tiq.",
        "dats": "Dgts",
        "dots": "Dgts",
        "rls": "RES",
        "dlf": "DEF",
        "dlf.": "DEF",
        "rlf": "RES",
        "vlf": "VIT",
    }

    corrected_lines = []
    for line in raw_lines:
        corrected = line
        for typo, correct in typo_corrections.items():
            corrected = re.sub(typo, correct, corrected, flags=re.IGNORECASE)
        corrected_lines.append(corrected)

    return corrected_lines, screenshot


# Saves screenshot to appropriate folder
def process_rune_image_from_screenshot():
    lines, cropped = extract_text_from_screenshot_runes_dj()
    keep = should_keep_rune(lines)

    # Format filename
    name = "_".join(line.replace(" ", "") for line in lines)
    name = name.replace("/", "").replace(":", "") + ".png"  # Clean illegal chars

    folder = "runes/kept" if keep else "runes/sold"
    os.makedirs(folder, exist_ok=True)
    save_path = os.path.join(folder, name)

    ImageGrab.grab(bbox=(394, 387, 1148, 877)).save(save_path)
    # cropped.save(save_path)

    return keep


def locate_template(haystack, needle, threshold=MATCH_THRESHOLD, use_gray=False):
    if use_gray:
        haystack = cv2.cvtColor(haystack, cv2.COLOR_BGR2GRAY)
        needle = cv2.cvtColor(needle, cv2.COLOR_BGR2GRAY)

    result = cv2.matchTemplate(haystack, needle, cv2.TM_CCOEFF_NORMED)
    locations = np.where(result >= threshold)
    w, h = needle.shape[1], needle.shape[0]
    return [(int(pt[0] + w / 2), int(pt[1] + h / 2)) for pt in zip(*locations[::-1])]


def filter_close_points(points, min_distance=MIN_DISTANCE):
    filtered = []
    for pt in points:
        if all(
            np.linalg.norm(np.array(pt) - np.array(other)) >= min_distance
            for other in filtered
        ):
            filtered.append(pt)
    return filtered


def region_has_overlap(center, template_size, other_locations):
    x, y = center
    w, h = template_size
    for ox, oy in other_locations:
        if abs(x - ox) < w and abs(y - oy) < h:
            return True
    return False


def remove_rune_with_bad_subs():
    RUNE_GRID_REGION = (1180, 372, 546, 405)
    MARKS_GRID_REGION2 = (1180, 372, 546, 500)

    # Load templates
    rune_template_1 = cv2.imread("img/rune.png")
    rune_template_2 = cv2.imread("img/rune2.png")
    check_template = cv2.imread("img/check.png")
    sold_template = cv2.imread("img/sold.png")

    # Screenshot for rune detection
    rune_img = pyautogui.screenshot(region=RUNE_GRID_REGION)
    rune_np = np.array(rune_img)
    rune_bgr = cv2.cvtColor(rune_np, cv2.COLOR_RGB2BGR)

    # Screenshot for marks detection (larger region)
    marks_img = pyautogui.screenshot(region=MARKS_GRID_REGION2)
    marks_np = np.array(marks_img)
    marks_bgr = cv2.cvtColor(marks_np, cv2.COLOR_RGB2BGR)

    # Detect runes
    rune_locs_1 = locate_template(rune_bgr, rune_template_1)
    rune_locs_2 = locate_template(rune_bgr, rune_template_2)
    all_runes = rune_locs_1 + rune_locs_2
    rune_locations = filter_close_points(all_runes)

    # Detect marks
    check_locations = locate_template(marks_bgr, check_template, use_gray=True)
    sold_locations = locate_template(marks_bgr, sold_template)

    for loc in rune_locations:
        screen_x = RUNE_GRID_REGION[0] + loc[0]
        screen_y = RUNE_GRID_REGION[1] + loc[1]
        if not region_has_overlap(
            loc, check_template.shape[1::-1], check_locations
        ) and not region_has_overlap(loc, sold_template.shape[1::-1], sold_locations):
            click_coords(
                (screen_x, screen_y), [("img/legendaire.png",), ("img/heroique.png",)]
            )
            keep = process_rune_image_from_screenshot()
            if keep:
                click_coords(
                    (screen_x, screen_y),
                    [("img/rejouer.png",)],
                )
            else:
                click_img([("img/croix_rune.png",)], [("img/rejouer.png",)])


def sell_bad_runes():
    remove_rune_with_bad_subs()
    while drag_and_drop_with_random_area(
        (1458, 438), 20, (1460, 792), 20, confidence=(DEFAULT_CONFIDENCE + 0.05)
    ):
        remove_rune_with_bad_subs()


def farm_dj(upgrade_runes: bool = True):
    go_to_arena()

    while True:
        click_img(
            [("img/open_combat_repet.png",)], wait_until_images_to_click_gone=True
        )
        if find_img([("img/rejouer.png",)]):
            sort_and_upgrade_runes(upgrade_runes)

            click_img(
                [("img/rejouer.png",)], [("img/combats_a_repetition_button_raid.png",)]
            )  # mig
            click_img(
                [("img/box_unchecked.png",)], [("img/box_checked.png",)]
            )  # put to x30 runs
            click_img(
                [("img/combats_a_repetition_button_raid.png",)],
                [("img/reduce_combat_repet.png",)],
            )


def sort_and_upgrade_runes(upgrade_runes: bool = True):
    click_img([("img/vente_selective.png",)], [("img/vente_selective2.png",)])
    if upgrade_runes:
        sell_bad_runes()
    click_img(
        [("img/vente_selective2.png",)],
        NOT_SHOW_TODAY_DUNGEON + [("img/ok.png",)],
    )
    if find_img([("img/no_selection_dj.png",)]):
        click_img(
            [("img/ok.png",)], [{"path": "img/vente_selective2.png", "precise": True}]
        )
        click_img([("img/annuler.png",)], [("img/vente_selective.png",)])
    else:
        click_img(
            NOT_SHOW_TODAY_DUNGEON + [("img/ok.png",)],
            [("img/vente_selective.png",)],
            click_random=False,
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
    # upgrade_runes()


def stop_dj():
    click_img(
        [("img/oui.png",), ("img/fin_des_combats.png",)],
        [{"path": "img/selection_du_donjon.png", "precise": True}],
        click_random=False,
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )

    sort_and_upgrade_runes()
    click_img(
        [("img/selection_du_donjon.png",)],
        [("img/donjon_de_cairos.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )


def launch_dj(dungeon_data):
    remove_packs([("img/repet_building.png", DEFAULT_CONFIDENCE - 0.3)])

    click_img(
        [("img/repet_building.png", DEFAULT_CONFIDENCE - 0.3)],
        [("img/combats_a_repetition_icon.png",)],
    )
    click_img(
        [("img/combats_a_repetition_icon.png",)], [("img/combats_a_repetition.png",)]
    )
    if find_img([("img/vente_selective.png",)]):
        stop_dj()
    click_img(
        [("img/donjon_de_cairos.png",)],
        [{"path": "img/go_launch_dj.png", "region": (0, 800, 1920, 280)}],
    )
    click_img(
        [{"path": "img/go_launch_dj.png", "region": (0, 800, 1920, 280)}],
        [("img/combats_a_repetition_button.png",)],
    )
    if dungeon_data["30x10_run"]:
        click_img(
            [("img/box_unchecked.png",)], [("img/box_checked.png",)]
        )  # put to x30 runs
    else:
        click_img(
            [("img/box_checked.png",)], [("img/box_unchecked.png",)]
        )  # put to x10 runs
    click_img(
        [("img/combats_a_repetition_button.png",)], [("img/reduce_combat_repet.png",)]
    )
    click_img([("img/reduce_combat_repet.png",)], wait_until_images_to_click_gone=True)
