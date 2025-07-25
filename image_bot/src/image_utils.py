import numpy as np
import cv2
from PIL import ImageGrab, Image
from math import hypot
from typing import List, Tuple, Optional
from random import randint, shuffle, choice
import pyautogui

from src.data_types import ClickImage
from src.constants import DEFAULT_CONFIDENCE

template_cache = {}


def load_template(path: str) -> np.ndarray:
    if path not in template_cache:
        template_cache[path] = cv2.cvtColor(
            np.array(Image.open(path)), cv2.COLOR_RGB2BGR
        )
    return template_cache[path]


def take_screenshot(region: Optional[Tuple[int, int, int, int]] = None) -> np.ndarray:
    return cv2.cvtColor(np.array(ImageGrab.grab(bbox=region)), cv2.COLOR_RGB2BGR)


def find_image_position(
    screen: np.ndarray,
    template: np.ndarray,
    confidence: float = DEFAULT_CONFIDENCE,
) -> List[Tuple[int, int]]:
    result = cv2.matchTemplate(screen, template, cv2.TM_CCOEFF_NORMED)
    return list(zip(*np.where(result >= confidence)[::-1]))


def filter_close_matches(
    matches: List[Tuple[int, int]],
    threshold: float = 10.0,
) -> List[Tuple[int, int]]:
    out = []
    for x1, y1 in matches:
        if all(hypot(x1 - x2, y1 - y2) > threshold for (x2, y2) in out):
            out.append((x1, y1))
    return out


def is_color_similar(
    template: np.ndarray,
    matched: np.ndarray,
    sat_thresh: float = 30.0,
    val_thresh: float = 40.0,
) -> bool:
    thsv = cv2.cvtColor(template, cv2.COLOR_BGR2HSV)
    mhsv = cv2.cvtColor(matched, cv2.COLOR_BGR2HSV)
    if thsv.shape != mhsv.shape:
        mhsv = cv2.resize(mhsv, (thsv.shape[1], thsv.shape[0]))
    _, s1, v1 = cv2.mean(thsv)[:3]
    _, s2, v2 = cv2.mean(mhsv)[:3]
    return abs(s1 - s2) < sat_thresh and abs(v1 - v2) < val_thresh


# ------------------------------------------------------------------------


def has_red_pixel(
    region: Tuple[int, int, int, int], red_threshold=180, diff_threshold=80
) -> bool:
    x, y, w, h = region
    left, top, right, bottom = x, y, x + w, y + h

    if right <= left or bottom <= top:
        raise ValueError(f"Invalid region dimensions: {region}")

    screenshot = ImageGrab.grab(bbox=(left, top, right, bottom))
    pixels = np.array(screenshot)

    red, green, blue = pixels[:, :, 0], pixels[:, :, 1], pixels[:, :, 2]
    red_enough = red > red_threshold
    red_dominant = (red - green > diff_threshold) & (red - blue > diff_threshold)

    return np.any(red_enough & red_dominant)


def random_click_position(x, y, w, h, x_offset, y_offset, reduction) -> Tuple[int, int]:
    rw, rh = int(w * reduction), int(h * reduction)
    cx, cy = x + w // 2, y + h // 2
    return (
        min(max(randint(cx - rw // 2, cx + rw // 2), x), x + w) + x_offset,
        min(max(randint(cy - rh // 2, cy + rh // 2), y), y + h) + y_offset,
    )


def find_clickable_image(
    images: List[ClickImage], click_random=True
) -> Tuple[Tuple[int, int], np.ndarray, ClickImage]:
    if click_random:
        shuffle(images)

    for img in images:
        template = load_template(img.path)
        left, top, width, height = img.region
        bbox = (left, top, left + width, top + height) if img.region else None
        screen = take_screenshot(region=bbox)

        matches = find_image_position(screen, template, confidence=img.confidence)
        if not matches:
            continue

        if img.precise or img.index is not None:
            matches = filter_close_matches(matches)
            if not matches:
                continue

        if img.precise:
            valid_matches = []
            for x, y in matches:
                matched_area = screen[
                    y : y + template.shape[0], x : x + template.shape[1]
                ]
                if is_color_similar(template, matched_area):
                    valid_matches.append((x, y))
            matches = valid_matches
            if not matches:
                continue

        if img.index is not None:
            if img.index < len(matches):
                return matches[img.index], template, img
            else:
                continue
        else:
            return choice(matches), template, img

    return None, None, None


def is_any_image_visible(images: List[ClickImage]) -> bool:
    for img in images:
        template = load_template(img.path)
        bbox = (
            (
                img.region[0],
                img.region[1],
                img.region[0] + img.region[2],
                img.region[1] + img.region[3],
            )
            if img.region
            else None
        )
        screen = take_screenshot(region=bbox)
        matches = find_image_position(screen, template, confidence=img.confidence)
        if matches:
            return True
    return False


def color_matches(
    actual: Tuple[int, int, int], expected: Tuple[int, int, int], tolerance: int
) -> bool:
    return all(abs(a - e) <= tolerance for a, e in zip(actual, expected))


def screenshot_cv(region=None):
    shot = pyautogui.screenshot(region=region)
    return cv2.cvtColor(np.array(shot), cv2.COLOR_RGB2BGR)


def find_image_opencv(
    template_path: str,
    confidence: float,
    region: Tuple[int, int, int, int],
):
    screen = screenshot_cv()

    if region:
        left, top, width, height = region
        screen = screen[top : top + height, left : left + width]

    template = cv2.imread(template_path)
    result = cv2.matchTemplate(screen, template, cv2.TM_CCOEFF_NORMED)

    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(result)
    if max_val >= confidence:
        match_top_left = max_loc
        if region:
            match_top_left = (
                match_top_left[0] + region[0],
                match_top_left[1] + region[1],
            )
        return match_top_left  # top-left coordinates of matched area

    return None


def is_pixel_present(
    click_x: int, click_y: int, tolerance: int, target_color: Tuple[int, int, int]
):
    pixel_color = pyautogui.screenshot().getpixel((click_x, click_y))
    if color_matches(pixel_color, target_color, tolerance):
        return True
    return False
