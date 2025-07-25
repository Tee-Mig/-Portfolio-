from typing import List, Tuple, Union
import pyautogui
import cv2
import numpy as np
from time import time
from random import shuffle, choice
from random import randint, uniform
from time import sleep

# * external functions
from src.data_types import ClickImage, WaitingImage
from src.fill_defaults import (
    to_click_image_list_fill_default,
    to_waiting_image_list_fill_default,
)
from src.constants import (
    DEFAULT_CLICK_TIME,
    DEFAULT_RECLICK_TIME,
    DEFAULT_CONFIDENCE,
    DEFAULT_DRAG_AND_DROP_TIME,
    DEFAULT_REGION,
)
from src.image_utils import (
    load_template,
    take_screenshot,
    find_image_position,
    filter_close_matches,
    is_color_similar,
    has_red_pixel,
    is_any_image_visible,
    find_clickable_image,
    find_image_opencv,
    is_pixel_present,
)


def random_click_position(
    x: int,
    y: int,
    w: int,
    h: int,
    x_offset: int,
    y_offset: int,
    reduction: float,
) -> Tuple[int, int]:
    rw, rh = int(w * reduction), int(h * reduction)
    cx, cy = x + w // 2, y + h // 2
    return min(max(randint(cx - rw // 2, cx + rw // 2), x), x + w) + x_offset, min(
        max(randint(cy - rh // 2, cy + rh // 2), y), y + h
    ) + y_offset


def click_on_images(
    images: List[ClickImage], click_time: float, click_random: bool
) -> bool:
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
            matches = [
                (x, y)
                for (x, y) in matches
                if is_color_similar(
                    template,
                    screen[y : y + template.shape[0], x : x + template.shape[1]],
                )
            ]
            if not matches:
                continue

        if img.index is not None:
            if img.index < len(matches):
                match = matches[img.index]
            else:
                raise IndexError(
                    f"Index {img.index} is out of bounds for {len(matches)} match(es) found."
                )
        else:
            match = choice(matches)

        x, y = match
        h, w = template.shape[:2]

        # ✅ Ensure match is inside screen bounds
        if y + h > screen.shape[0] or x + w > screen.shape[1] or x < 0 or y < 0:
            continue  # Skip invalid matches

        # ✅ Adjust for region offset
        if img.region:
            x += img.region[0]
            y += img.region[1]

        # ✅ Calculate random click position
        cx, cy = random_click_position(
            x, y, w, h, img.x_offset, img.y_offset, img.click_area_reduction
        )

        if click_time is None:
            current_click_time = DEFAULT_CLICK_TIME
        else:
            current_click_time = click_time
        pyautogui.click(cx, cy, duration=current_click_time)
        return True

    return False


def is_any_waiting_image_present(images: List[WaitingImage]) -> bool:
    for img in images:
        template = load_template(img.path)
        left, top, width, height = img.region
        bbox = (left, top, left + width, top + height) if img.region else None
        screen = take_screenshot(region=bbox)
        matches = find_image_position(screen, template, img.confidence)
        if not matches:
            continue

        matches = filter_close_matches(matches) if img.precise else matches
        if not matches:
            continue

        if img.precise:
            matches = [
                (x, y)
                for (x, y) in matches
                if is_color_similar(
                    template,
                    screen[y : y + template.shape[0], x : x + template.shape[1]],
                )
            ]
            if not matches:
                continue

        return True
    return False


def wait_until_any_image_visible(images: List[WaitingImage]) -> bool:
    while True:
        if is_any_waiting_image_present(images):
            return True
        pass


def are_all_images_gone(images: List[WaitingImage]) -> bool:
    for img in images:
        template = load_template(img.path)
        left, top, width, height = img.region
        bbox = (left, top, left + width, top + height) if img.region else None
        screen = take_screenshot(region=bbox)
        matches = find_image_position(screen, template, img.confidence)
        if not matches:
            continue

        matches = (
            filter_close_matches(matches)
            if img.precise or img.index is not None
            else matches
        )
        if not matches:
            continue

        if img.precise:
            matches = [
                (x, y)
                for (x, y) in matches
                if is_color_similar(
                    template,
                    screen[y : y + template.shape[0], x : x + template.shape[1]],
                )
            ]
            if not matches:
                continue
            return False
        else:
            return False

    return True


# * perfect
def click_img(
    images_to_click: List[Union[Tuple, dict]],
    waiting_images: List[Union[Tuple, dict]] = None,
    see_images_to_click_first: bool = False,
    wait_until_images_to_click_gone: bool = False,
    click_random: bool = True,
    click_time: float = None,
    reclick_time: float = None,
) -> bool:
    images_to_click = to_click_image_list_fill_default(images_to_click or [])
    waiting_images = to_waiting_image_list_fill_default(waiting_images or [])
    clicked = False

    if see_images_to_click_first:
        wait_until_any_image_visible(images_to_click)

    if wait_until_images_to_click_gone:
        while not are_all_images_gone(images_to_click):
            if click_on_images(images_to_click, click_time, click_random):
                clicked = True
                if reclick_time is None:
                    current_reclick_time = DEFAULT_RECLICK_TIME
                else:
                    current_reclick_time = reclick_time
                start = time()
                while time() - start < current_reclick_time:
                    if are_all_images_gone(images_to_click):
                        break

        if waiting_images:
            while not is_any_waiting_image_present(waiting_images):
                pass
        return clicked

    if not waiting_images:
        return click_on_images(images_to_click, click_time, click_random)

    while True:
        if is_any_waiting_image_present(waiting_images):
            return clicked

        if not is_any_waiting_image_present(waiting_images):
            if click_on_images(images_to_click, click_time, click_random):
                clicked = True
                if reclick_time is None:
                    current_reclick_time = DEFAULT_RECLICK_TIME
                else:
                    current_reclick_time = reclick_time
                start = time()
                while time() - start < current_reclick_time:
                    if is_any_waiting_image_present(waiting_images):
                        return True


def calculate_point(base: Tuple[int, int], radius: int, mode: str) -> Tuple[int, int]:
    if mode == "min":
        return (base[0] - radius, base[1] - radius)
    elif mode == "max":
        return (base[0] + radius, base[1] + radius)
    else:
        return (
            base[0] + randint(-radius, radius),
            base[1] + randint(-radius, radius),
        )


def has_screen_changed(
    before: np.ndarray, after: np.ndarray, confidence: float
) -> bool:
    if before.shape != after.shape:
        return True
    diff = cv2.absdiff(before, after)
    non_zero = np.count_nonzero(diff)
    total = diff.size
    similarity = 1 - (non_zero / total)
    return similarity < confidence


def wait_until_screen_stable(
    region: Tuple[int, int, int, int],
    confidence: float,
    check_interval: float = 0.2,
    stable_count_required: int = 3,
    max_wait_time: float = 5.0,
) -> np.ndarray:
    """
    Wait until the screen has shown stable images for a number of consecutive checks.
    """
    prev = take_screenshot(region)
    stable_count = 0
    start_time = time()

    while True:
        sleep(check_interval)
        curr = take_screenshot(region)
        if not has_screen_changed(prev, curr, confidence):
            stable_count += 1
            if stable_count >= stable_count_required:
                return curr
        else:
            stable_count = 0
        prev = curr

        if time() - start_time > max_wait_time:
            return curr  # give up after max_wait_time


def images_found(images: List[WaitingImage]) -> bool:
    for img in images:
        template = load_template(img.path)
        screenshot = take_screenshot(region=img.region)
        matches = find_image_position(screenshot, template, img.confidence)
        if matches:
            return True
    return False


# * perfect
def drag_and_drop_with_random_area(
    start_point: Tuple[int, int],
    start_area_radius: int,
    end_point: Tuple[int, int],
    end_area_radius: int,
    image_conditions: List[Union[Tuple, dict]] = None,
    show_areas: bool = False,
    drag_mode: str = "random",  # "random", "min", "max"
    region: Tuple[int, int, int, int] = None,  # Area to check for screen stability
    confidence: float = DEFAULT_CONFIDENCE,  # Threshold for screen change detection
    drag_and_drop_time: float = None,
) -> bool:
    waiting_images = []
    if image_conditions:
        waiting_images = to_waiting_image_list_fill_default(image_conditions)
        if images_found(waiting_images):
            return False  # already found, no need to drag
    if show_areas:
        for point, radius in [
            (start_point, start_area_radius),
            (end_point, end_area_radius),
        ]:
            if drag_and_drop_time is None:
                current_drag_and_drop_time = DEFAULT_DRAG_AND_DROP_TIME
            else:
                current_drag_and_drop_time = drag_and_drop_time
            pyautogui.moveTo(
                point[0] - radius,
                point[1] - radius,
                duration=current_drag_and_drop_time,
            )
            if drag_and_drop_time is None:
                current_drag_and_drop_time = DEFAULT_DRAG_AND_DROP_TIME
            else:
                current_drag_and_drop_time = drag_and_drop_time
            pyautogui.moveTo(
                point[0] + radius,
                point[1] + radius,
                duration=current_drag_and_drop_time,
            )

    # Repeat drag until screen stabilizes and condition image is found
    while True:
        before_drag = take_screenshot(region)

        # Perform drag
        from_point = calculate_point(start_point, start_area_radius, drag_mode)
        to_point = calculate_point(end_point, end_area_radius, drag_mode)

        pyautogui.moveTo(from_point)
        pyautogui.mouseDown()
        if drag_and_drop_time is None:
            current_drag_and_drop_time = DEFAULT_DRAG_AND_DROP_TIME
        else:
            current_drag_and_drop_time = drag_and_drop_time
        pyautogui.moveTo(to_point, duration=current_drag_and_drop_time)
        pyautogui.mouseUp()

        # Wait for screen to settle
        sleep(uniform(0.25, 0.3))
        after_drag = wait_until_screen_stable(region, confidence)

        # If screen did not change at all — stop, no point continuing
        if not has_screen_changed(before_drag, after_drag, confidence):
            return False

        # Check if desired images are now present
        if not waiting_images:
            return True  # No condition to wait for

        if images_found(waiting_images):
            return True


def click_until_red_pixel(
    images_to_click: List[Union[tuple, dict]],
    red_pixel_region: Tuple[int, int, int, int],
    waiting_images: List[Union[tuple, dict]] = None,
    click_random=True,
    click_time=None,
) -> bool:
    images = to_click_image_list_fill_default(images_to_click)
    waiting_images = to_click_image_list_fill_default(waiting_images or [])
    clicked = None

    while True:
        if has_red_pixel(red_pixel_region):
            return clicked

        if is_any_image_visible(waiting_images):
            return False

        match, template, img = find_clickable_image(images, click_random)
        if match is None:
            return None

        x, y = match
        if img.region:
            x += img.region[0]
            y += img.region[1]

        w, h = template.shape[1], template.shape[0]
        cx, cy = random_click_position(
            x, y, w, h, img.x_offset, img.y_offset, img.click_area_reduction
        )

        if click_time is None:
            current_click_time = DEFAULT_CLICK_TIME
        else:
            current_click_time = click_time
        pyautogui.click(cx, cy, duration=current_click_time)
        clicked = True


def click_coords(
    coord: Tuple[int, int],
    waiting_images: List[Union[Tuple, dict]] = None,
    click_time: float = None,
    reclick_time: float = None,
):
    waiting_images = to_waiting_image_list_fill_default(waiting_images or [])

    while True:
        if click_time is None:
            current_click_time = DEFAULT_CLICK_TIME
        else:
            current_click_time = click_time
        pyautogui.click(coord[0], coord[1], duration=current_click_time)

        if reclick_time is None:
            current_reclick_time = DEFAULT_RECLICK_TIME
        else:
            current_reclick_time = reclick_time
        start = time()
        while time() - start < current_reclick_time:
            if is_any_waiting_image_present(waiting_images):
                return True


def click_until_pixel_color_detected(
    image_path: str,
    pixel_offset: Tuple[int, int],
    target_color: Tuple[int, int, int],
    tolerance: int = 5,
    confidence: float = DEFAULT_CONFIDENCE,
    region: Tuple[int, int, int, int] = DEFAULT_REGION,
    reclick_time: Tuple[float, float] = None,
):
    while True:
        try:
            match_location = find_image_opencv(image_path, confidence, region)
            if match_location:
                click_x = match_location[0] + pixel_offset[0]
                click_y = match_location[1] + pixel_offset[1]
                if is_pixel_present(click_x, click_y, tolerance, target_color):
                    return

                pyautogui.click(click_x, click_y)

                if reclick_time is None:
                    current_reclick_time = DEFAULT_RECLICK_TIME
                else:
                    current_reclick_time = reclick_time
                start = time()
                while time() - start < current_reclick_time:
                    if is_pixel_present(click_x, click_y, tolerance, target_color):
                        return

        except Exception as _:
            pass
