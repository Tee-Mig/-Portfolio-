from typing import List, Tuple
from typing import Union
from src.click import click_img
from src.constants import DEFAULT_FAST_RECLICK_TIME

CROIX_RUNE = [("img/croix_rune.png",)]

CLOSE_PACKS = [
    ("img/croix1.png",),
    ("img/croix2.png",),
    ("img/croix3.png",),
    ("img/croix4.png",),
    ("img/croix_collab1.png",),
    ("img/croix_collab2.png",),
]

NOT_SHOW_TODAY_PACKS = [
    ("img/ne_plus_montrer_ajd.png",),
    ("img/oui.png",),
]

NOT_SHOW_TODAY_SHOP = [
    ("img/ne_plus_montrer_ajd2.png",),
    ("img/oui2.png",),
    ("img/ok.png",),
]

NOT_SHOW_TODAY_DUNGEON = [
    ("img/ne_plus_montrer_ajd2.png",),
    ("img/oui.png",),
]

GRASS = [
    ("img/grass.png", DEFAULT_FAST_RECLICK_TIME - 0.05),
    ("img/grass2.png", DEFAULT_FAST_RECLICK_TIME - 0.05),
]


def remove_packs(
    images: List[Union[Tuple, dict]],
    not_show_today: List[Union[Tuple, dict]] = NOT_SHOW_TODAY_PACKS,
    close_packs: List[Union[Tuple, dict]] = CLOSE_PACKS,
    grass: List[Union[Tuple, dict]] = GRASS,
):
    click_img(
        not_show_today + close_packs + grass,
        images,
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
        click_random=False,
    )
