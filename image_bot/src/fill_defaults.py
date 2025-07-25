from src.data_types import ClickImage, WaitingImage
from typing import List, Union
from src.constants import (
    DEFAULT_CONFIDENCE,
    DEFAULT_REGION,
    DEFAULT_CLICK_AREA_REDUCTION,
    DEFAULT_INDEX,
    DEFAULT_X_OFFSET,
    DEFAULT_Y_OFFSET,
    DEFAULT_PRECISE,
)


def to_click_image_list_fill_default(
    images_raw: List[Union[tuple, dict]],
) -> List[ClickImage]:
    images = []

    for img in images_raw:
        if isinstance(img, dict):
            path = img.get("path")
            confidence = img.get("confidence", DEFAULT_CONFIDENCE)
            region = img.get("region", DEFAULT_REGION)
            index = img.get("index", DEFAULT_INDEX)
            x_offset = img.get("x_offset", DEFAULT_X_OFFSET)
            y_offset = img.get("y_offset", DEFAULT_Y_OFFSET)
            click_area_reduction = img.get(
                "click_area_reduction", DEFAULT_CLICK_AREA_REDUCTION
            )
            precise = img.get("precise", DEFAULT_PRECISE)

        elif isinstance(img, tuple):
            # Unpack based on length with defaults
            path = img[0]
            confidence = img[1] if len(img) > 1 else DEFAULT_CONFIDENCE
            region = img[2] if len(img) > 2 else DEFAULT_REGION
            index = img[3] if len(img) > 3 else DEFAULT_INDEX
            x_offset = img[4] if len(img) > 4 else DEFAULT_X_OFFSET
            y_offset = img[5] if len(img) > 5 else DEFAULT_Y_OFFSET
            click_area_reduction = (
                img[6] if len(img) > 6 else DEFAULT_CLICK_AREA_REDUCTION
            )
            precise = img[7] if len(img) > 7 else DEFAULT_PRECISE

        else:
            raise ValueError("Image input must be a tuple or dictionary")

        images.append(
            ClickImage(
                path=path,
                confidence=confidence,
                region=region,
                index=index,
                x_offset=x_offset,
                y_offset=y_offset,
                click_area_reduction=click_area_reduction,
                precise=precise,
            )
        )

    return images


def to_waiting_image_list_fill_default(
    images_raw: List[Union[tuple, dict]],
) -> List[WaitingImage]:
    images = []

    for img in images_raw:
        if isinstance(img, dict):
            path = img.get("path")
            confidence = img.get("confidence", DEFAULT_CONFIDENCE)
            region = img.get("region", DEFAULT_REGION)
            precise = img.get("precise", DEFAULT_PRECISE)

        elif isinstance(img, tuple):
            path = img[0]
            confidence = img[1] if len(img) > 1 else DEFAULT_CONFIDENCE
            region = img[2] if len(img) > 2 else DEFAULT_REGION
            precise = img[3] if len(img) > 3 else DEFAULT_PRECISE

        else:
            raise ValueError("Image input must be a tuple or dictionary")

        images.append(
            WaitingImage(
                path=path, confidence=confidence, region=region, precise=precise
            )
        )

    return images
