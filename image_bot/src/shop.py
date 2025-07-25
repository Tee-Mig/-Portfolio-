from src.click import click_img
from src.screen import find_img
from src.packs import remove_packs, NOT_SHOW_TODAY_SHOP, CLOSE_PACKS
from src.constants import DEFAULT_CONFIDENCE, DEFAULT_FAST_RECLICK_TIME


def buy_items(items_to_buy):
    while find_img(items_to_buy):
        click_img(items_to_buy, [("img/acheter_shop.png",)])
        click_img([("img/acheter_shop.png",)], wait_until_images_to_click_gone=True)
        if find_img(NOT_SHOW_TODAY_SHOP):
            click_img(
                NOT_SHOW_TODAY_SHOP,
                reclick_time=DEFAULT_FAST_RECLICK_TIME,
                wait_until_images_to_click_gone=True,
                click_random=False,
            )


def get_all_items_to_buy(buy_items_shop):
    items_to_buy = []
    items_to_buy += [("img/ld_pieces.png",)] if buy_items_shop["ld_pieces"] else []
    items_to_buy += [("img/ms.png",)] if buy_items_shop["ms"] else []
    items_to_buy += (
        [("img/leg_scroll_pieces.png",)] if buy_items_shop["leg_scroll_pieces"] else []
    )
    items_to_buy += (
        [("img/grave_scroll_pieces.png",)]
        if buy_items_shop["grave_scroll_pieces"]
        else []
    )
    items_to_buy += (
        [("img/unknown_scrolls.png",)] if buy_items_shop["unknown_scrolls"] else []
    )
    items_to_buy += (
        [("img/monster_pieces.png", DEFAULT_CONFIDENCE - 0.23)]
        if buy_items_shop["monster_pieces"]
        else []
    )
    return items_to_buy


def buy_shop(building, items_to_buy, confidence=DEFAULT_CONFIDENCE):
    remove_packs([(building, confidence)])

    click_img(
        [(building, confidence)],
        [("img/acheter.png",)],
    )
    click_img([("img/acheter.png",)], NOT_SHOW_TODAY_SHOP + [("img/stars_shop.png",)])
    click_img(
        NOT_SHOW_TODAY_SHOP,
        [("img/stars_shop.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )
    buy_items(items_to_buy)


def go_to_homescreen():
    click_img(
        [("img/retour.png",)] + CLOSE_PACKS,
        [
            ("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35),
            {"path": "img/back_arrow.png", "precise": True},
        ],
    )
    click_img(
        [{"path": "img/back_arrow.png", "precise": True}] + CLOSE_PACKS,
        [("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)],
    )


def reset_view_and_buy_shops(items_to_buy_in_shops):
    collect_rewards = any(items_to_buy_in_shops.values())
    go_to_homescreen()

    if collect_rewards:
        items_to_buy = get_all_items_to_buy(items_to_buy_in_shops)
        # * check guild shop
        buy_shop("img/guild_shop_building.png", items_to_buy, DEFAULT_CONFIDENCE - 0.35)

        # * check magic shop
        buy_shop("img/magic_shop_building.png", items_to_buy, DEFAULT_CONFIDENCE - 0.15)
    else:
        click_img(
            [("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)],
            [("img/acheter.png",)],
        )
        click_img(
            [("img/acheter.png",)],
            NOT_SHOW_TODAY_SHOP + [("img/echoppe_de_magie.png",)],
        )
