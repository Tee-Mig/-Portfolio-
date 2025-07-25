from typing import List, Tuple, Union
import cv2
import numpy as np
from PIL import ImageGrab
import pyautogui

from src.fill_defaults import to_waiting_image_list_fill_default
from src.image_utils import (
    load_template,
    take_screenshot,
    is_color_similar,
    find_image_position,
    filter_close_matches,
)


# * perfect
def find_img(images: List[Union[Tuple, dict]]) -> bool:
    images = to_waiting_image_list_fill_default(images or [])

    for img in images:
        template = load_template(img.path)
        region = img.region
        bbox = (
            (region[0], region[1], region[0] + region[2], region[1] + region[3])
            if region
            else None
        )

        screen = take_screenshot(region=bbox)
        matches = find_image_position(screen, template, img.confidence)

        if not matches:
            continue

        if not img.precise:
            return True

        matches = filter_close_matches(matches)
        h, w = template.shape[:2]

        for x, y in matches:
            matched_area = screen[y : y + h, x : x + w]
            if matched_area.shape[:2] != (h, w):
                continue
            if is_color_similar(template, matched_area):
                return True

    return False


# * perfect
def find_img_with_red_top_right(
    image: Union[Tuple, dict],
    number_of_red_pixel: int = 1200,
    show_area: bool = False,
) -> bool:
    img = to_waiting_image_list_fill_default([image])[0]

    template = load_template(img.path)
    h, w = template.shape[:2]

    # Capture region
    region = img.region
    bbox = (
        (region[0], region[1], region[0] + region[2], region[1] + region[3])
        if region
        else None
    )
    screenshot = take_screenshot(region=bbox)

    result = cv2.matchTemplate(screenshot, template, cv2.TM_CCOEFF_NORMED)
    loc = np.where(result >= img.confidence)
    coords = filter_close_matches(list(zip(*loc[::-1])), threshold=30)

    for x, y in coords:
        matched_area = screenshot[y : y + h, x : x + w]
        if matched_area.shape[:2] != (h, w):
            continue

        if img.precise and not is_color_similar(template, matched_area):
            continue

        # Check red pixels in top-right area
        top_right_x = x + w
        top_right_y = y

        red_region_left = top_right_x - 100
        red_region_top = top_right_y - 100
        red_region_right = red_region_left + 200
        red_region_bottom = red_region_top + 200

        red_bbox = (
            red_region_left,
            red_region_top,
            red_region_right,
            red_region_bottom,
        )

        if show_area:
            pyautogui.moveTo(red_region_left, red_region_top, duration=0.2)
            pyautogui.moveTo(red_region_right, red_region_bottom, duration=0.2)

        red_img = ImageGrab.grab(bbox=red_bbox)
        red_np = np.array(red_img)
        red_hsv = cv2.cvtColor(
            cv2.cvtColor(red_np, cv2.COLOR_RGB2BGR), cv2.COLOR_BGR2HSV
        )

        lower_red1 = np.array([0, 100, 100])
        upper_red1 = np.array([10, 255, 255])
        lower_red2 = np.array([160, 100, 100])
        upper_red2 = np.array([180, 255, 255])

        mask1 = cv2.inRange(red_hsv, lower_red1, upper_red1)
        mask2 = cv2.inRange(red_hsv, lower_red2, upper_red2)
        red_mask = cv2.bitwise_or(mask1, mask2)

        red_pixels = cv2.countNonZero(red_mask)

        if red_pixels >= number_of_red_pixel:
            return True

    return False
