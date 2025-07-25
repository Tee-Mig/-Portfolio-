from src.click import click_img, click_until_pixel_color_detected, click_coords
import cv2
import numpy as np
import pyautogui
from typing import Tuple
from random import randint, uniform
from src.dungeons import locate_template, filter_close_points
from PIL import ImageGrab, Image
import pytesseract
import re

from src.constants import DEFAULT_CONFIDENCE, DEFAULT_REGION, DEFAULT_SCROLL_AMOUNT

# Load your template image
template_path = "img/more.png"
template = cv2.imread(template_path, cv2.IMREAD_COLOR)
template_w, template_h = template.shape[1], template.shape[0]
OFFSET = 230  # y-offset above the match point
OCR_REGION_SIZE = (293, 151)


def find_all_template_locations(template_img, confidence=0.9):
    screenshot = pyautogui.screenshot()
    screen_np = np.array(screenshot)
    screen_bgr = cv2.cvtColor(screen_np, cv2.COLOR_RGB2BGR)

    result = cv2.matchTemplate(screen_bgr, template_img, cv2.TM_CCOEFF_NORMED)
    loc = np.where(result >= confidence)
    points = list(zip(*loc[::-1]))  # (x, y) points
    return points


def extract_text_from_screenshot(region):
    # Screenshot
    screenshot = ImageGrab.grab(bbox=region)
    bgr = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2BGR)
    hsv = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV)

    # HSV masks
    lower_orange = np.array([10, 80, 100])
    upper_orange = np.array([40, 255, 255])
    mask_orange = cv2.inRange(hsv, lower_orange, upper_orange)

    lower_gray = np.array([0, 0, 90])
    upper_gray = np.array([180, 60, 210])
    mask_gray = cv2.inRange(hsv, lower_gray, upper_gray)

    combined_mask = cv2.bitwise_or(mask_orange, mask_gray)
    result = cv2.bitwise_and(bgr, bgr, mask=combined_mask)

    # Preprocessing
    gray = cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)
    _, binary = cv2.threshold(gray, 25, 255, cv2.THRESH_BINARY)
    kernel = np.ones((1, 1), np.uint8)
    dilated = cv2.dilate(binary, kernel, iterations=1)

    # OCR
    config = r"--oem 3 --psm 6 -c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+0123456789.%[]"
    text = pytesseract.image_to_string(dilated, config=config, lang="eng+fra")
    print(f"text = {text}")

    # Cleanup
    lines = [re.sub(r"[»›>→\-]+", "", l).strip() for l in text.split("\n") if l.strip()]
    print(f"lines = {lines}")

    # Corrections for common OCR errors
    ocr_corrections = {
        "Lt]": "SPD",
        "SPO": "SPD",  # other potential misreads
        "SpD": "SPD",
        "SPDd": "SPD",
    }

    stats = []
    values = []
    final_output = []

    for line in lines:
        # Apply manual corrections
        for wrong, correct in ocr_corrections.items():
            line = line.replace(wrong, correct)

        # Cleanups
        line = line.replace("ﬂat", "flat")
        line = re.sub(r"\s+", " ", line)

        # Remove any bracketed values like [+5], [3], etc.
        line = re.sub(r"\[[^\]]*\]", "", line).strip()

        if re.match(r"^\+[\d]+", line):
            values.append(line)
        elif re.match(r"^[A-Za-z ]+$", line):
            stats.append(line)
        elif "-" in line:
            final_output.append("-")
        else:
            # Handle merged stat+value
            match = re.match(r"^(.*?)(\+[\d]+)$", line)
            if match:
                stat, val = match.groups()
                final_output.append(f"{stat.strip()} {val.strip()}")
            else:
                stats.append(line)

    while len(values) < len(stats):
        values.append("")

    for stat, val in zip(stats, values):
        final_output.append(f"{stat} {val}".strip())

    print(f"final_output = {final_output}")
    return final_output, Image.fromarray(dilated)


def screenshot_cv(region=None):
    shot = pyautogui.screenshot(region=region)
    return cv2.cvtColor(np.array(shot), cv2.COLOR_RGB2BGR)


def find_all_images(image_path: str, confidence: float = 0.9, region=None) -> int:
    screen = screenshot_cv(region)
    template = cv2.imread(image_path)
    h, w = template.shape[:2]
    result = cv2.matchTemplate(screen, template, cv2.TM_CCOEFF_NORMED)

    loc = np.where(result >= confidence)
    points = list(zip(*loc[::-1]))  # (x, y) format

    # Filter overlapping boxes
    boxes = []
    for pt in points:
        if not any(abs(pt[0] - b[0]) < w and abs(pt[1] - b[1]) < h for b in boxes):
            boxes.append(pt)

    return len(boxes)


def scroll_until_image_found(
    image_path: str,
    scroll_amount: int = DEFAULT_SCROLL_AMOUNT,
    target_occurrences: int = 1,
    confidence: float = DEFAULT_CONFIDENCE,
    region: Tuple[int, int, int, int] = DEFAULT_REGION,
    scrolling_area: Tuple[int, int, int, int] = (100, 100, 1700, 900),
    delay: float = (0.5, 0.6),
):
    left, top, width, height = scrolling_area
    x = randint(left, left + width - 1)
    y = randint(top, top + height - 1)
    pyautogui.moveTo(x, y)

    while True:
        count = find_all_images(image_path, confidence, region)

        if count >= target_occurrences:
            return True

        pyautogui.scroll(scroll_amount)
        # sleep(uniform(*delay))


def display_optimizer_window():
    click_img([("img/swop_icon.png",)], [("img/swop_window.png",)])
    click_img([("img/swop_maximise.png",)], [("img/swop_minimize.png",)])


def go_to_optimizer_tab():
    click_until_pixel_color_detected(
        image_path="img/optimizer_tab.png",
        pixel_offset=(10, 10),
        target_color=(11, 15, 20),
        tolerance=5,
    )


def locate_template_multiscale(
    image, template, threshold=0.8, scales=[1.0, 0.95, 1.05]
):
    found_points = []

    for scale in scales:
        resized_template = cv2.resize(template, (0, 0), fx=scale, fy=scale)
        result = cv2.matchTemplate(image, resized_template, cv2.TM_CCOEFF_NORMED)
        loc = np.where(result >= threshold)
        points = list(zip(*loc[::-1]))  # x, y format
        found_points.extend(points)

    return found_points


def apply_runes():
    RUNE_GRID_REGION = (250, 0, 1670, 1080)
    confidence = DEFAULT_CONFIDENCE - 0.1

    # Load templates
    croix_template = cv2.imread("img/croix_monster_optimizer.png")

    # Screenshot for rune detection
    croix_img = pyautogui.screenshot(region=RUNE_GRID_REGION)
    croix_np = np.array(croix_img)
    croix_bgr = cv2.cvtColor(croix_np, cv2.COLOR_RGB2BGR)

    # Detect runes
    croix_loc = locate_template_multiscale(
        croix_bgr, croix_template, threshold=confidence
    )
    croix_locations = filter_close_points(croix_loc, min_distance=28)

    TEMPLATE_WIDTH, TEMPLATE_HEIGHT = croix_template.shape[1], croix_template.shape[0]
    X_OFFSET = -50  # If needed for UI alignment

    for loc in croix_locations:
        # Get center of the match
        center_x = loc[0] + TEMPLATE_WIDTH // 2
        center_y = loc[1] + TEMPLATE_HEIGHT // 2

        # Adjust to screen coordinates
        screen_x = RUNE_GRID_REGION[0] + center_x + X_OFFSET
        screen_y = RUNE_GRID_REGION[1] + center_y

        click_coords((screen_x, screen_y), [("img/more.png",)])
        scroll_until_image_found(
            image_path="img/more.png",
            scroll_amount=-20,
            target_occurrences=6,
            confidence=DEFAULT_CONFIDENCE - 0.2,
        )

        scroll_until_image_found(image_path="img/builds.png")
        click_img([("img/builds.png",)], [("img/pick_a_monster.png",)])


def test():
    # x, y, w, h = pyautogui.locateOnScreen("img/more.png")
    # offset = 230

    # # (293, 151) width and height
    # print(f"x = {x} | y = {y - offset}")
    # pyautogui.moveTo(x, y - offset)
    # pyautogui.moveTo(x + 293, (y - offset) + 151)

    matches = find_all_template_locations(
        template, confidence=DEFAULT_CONFIDENCE - 0.15
    )

    print(f"len = {len(matches)}")
    for x_loc, y_loc in matches:
        region = (
            x_loc,
            y_loc - OFFSET,
            x_loc + OCR_REGION_SIZE[0],
            y_loc - OFFSET + OCR_REGION_SIZE[1],
        )
        lines, snap = extract_text_from_screenshot(region)  # todo need fixing here
        snap.save(f"{str(x_loc)}.png")
        print(f"Text at ({x_loc}, {y_loc}):")
        for line in lines:
            print(f"  - {line}")
        print("-" * 30)
    exit()


def apply_runes_from_optimizer():  # rune_tab.png
    display_optimizer_window()

    test()  # todo ongoing fix read runes subs in rune optimizer here

    go_to_optimizer_tab()

    scroll_until_image_found(image_path="img/builds.png")

    click_img([("img/builds.png",)], [("img/pick_a_monster.png",)])

    apply_runes()

    click_img([("img/swop_icon.png",)])
