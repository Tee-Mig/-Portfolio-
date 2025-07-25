from collections import namedtuple

# * path: string, confidence: float, region: tuple[int, int, int, int], index: int, x_offset: int, y_offset: int, click_area_reduction: int, precise: bool
ClickImage = namedtuple(
    "ClickImage",
    [
        "path",
        "confidence",
        "region",
        "index",
        "x_offset",
        "y_offset",
        "click_area_reduction",
        "precise",
    ],
)


# * path: string, confidence: float, region: tuple[int, int, int, int], precise: bool
WaitingImage = namedtuple("WaitingImage", ["path", "confidence", "region", "precise"])
