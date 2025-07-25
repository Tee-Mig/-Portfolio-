from random import uniform

# * screen
CURRENT_WIDTH = 1920  # * default screen width resolution
CURRENT_HEIGHT = 1080  # * default screen height resolution

# * click
DEFAULT_CLICK_TIME = uniform(0.01, 0.05)  # * : float(in second)
DEFAULT_RECLICK_TIME = uniform(4, 5)  # * : float(in second)
DEFAULT_FAST_RECLICK_TIME = uniform(0.3, 0.4)  # * : float(in second)
DEFAULT_INDEX = None
DEFAULT_X_OFFSET = 0
DEFAULT_Y_OFFSET = 0
DEFAULT_DRAG_AND_DROP_TIME = uniform(0.2, 0.3)

# * image
DEFAULT_CLICK_AREA_REDUCTION = (
    0.7  # * : float(from 0 to 1): how much we reduce clicking area on image
)
DEFAULT_CONFIDENCE = 0.9  # * float(from 0 to 1) -> precision for finding image
DEFAULT_REGION = (0, 0, CURRENT_WIDTH, CURRENT_HEIGHT)  # * default search image region
DEFAULT_COLOR_TOLERANCE = 10  # * default tolerance for pixel matching
DEFAULT_PRECISE = False

# * other
CHECK_INTERVAL = uniform(0.003, 0.004)  # todo remove after
DEFAULT_SCROLL_AMOUNT = 50
