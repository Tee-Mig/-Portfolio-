from src.click import click_img
from src.screen import find_img
from src.dungeons import launch_dj
from src.arena import arena
from src.enums import Dungeon, Rta
from src.constants import DEFAULT_FAST_RECLICK_TIME, DEFAULT_CONFIDENCE
from src.collect_rewards import collect_all_rewards
from src.rta import rta
from src.packs import CLOSE_PACKS
from src.store import store_all
from src.shop import reset_view_and_buy_shops


def display_ldplayer_full_window():
    click_img(
        [("img/ldplayer_icon.png", DEFAULT_CONFIDENCE - 0.1)],
        [("img/maximise_ldplayer.png",), ("img/minimise_ldplayer.png",)],
    )
    click_img([("img/maximise_ldplayer.png",)], [("img/minimise_ldplayer.png",)])


def update_info_on_screen():
    click_img(
        [
            ("img/croix_pub_ldplayer.png",),
            {"path": "img/accueil.png", "y_offset": 45},
        ],
        [
            ("img/sw_task.png",),
            ("img/sw_task2.png",),
            ("img/aucun_element_recent.png",),
        ],
        click_random=False,
    )

    if find_img([("img/aucun_element_recent.png",)]):
        click_img([("img/aucun_element_recent.png",)], [("img/sw_icon.png",)])
        click_img([("img/sw_icon.png",)], wait_until_images_to_click_gone=True)
    else:
        click_img(
            [
                ("img/sw_task.png",),
                ("img/sw_task2.png",),
            ],
            wait_until_images_to_click_gone=True,
        )


def update_game():
    click_img([("img/ok.png",)], [("img/maj.png",)])
    click_img(
        [("img/maj.png",), ("img/non_merci.png",)],
        [{"path": "img/jouer.png", "precise": True}],
    )
    click_img([{"path": "img/close_tab.png", "index": -1}], [("img/sw_icon.png",)])
    click_img([("img/sw_icon.png",)], wait_until_images_to_click_gone=True)


def launch_and_update_screen():
    update_info_on_screen()

    while True:
        click_img(
            [
                ("img/oui.png",),
                ("img/ne_plus_montrer_ajd.png",),
                {
                    "path": "img/touch_to_start.png",
                    "y_offset": 90,
                    "confidence": DEFAULT_CONFIDENCE - 0.05,
                },
            ],
            CLOSE_PACKS
            + [
                ("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35),
                ("img/back_arrow.png",),
                ("img/retour.png",),
                ("img/combat_de_classement.png",),
                ("img/ok.png",),
            ],
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )

        if find_img([("img/ok.png",)]):
            update_game()
        else:
            break

def sw_routine(data):
    display_ldplayer_full_window()  # * perfect

    launch_and_update_screen()  # * perfect
    reset_view_and_buy_shops(data["items_to_buy_in_shops"])  # * perfect

    if data["dungeon_data"]["dungeon"] is not Dungeon.NONE:
        launch_dj(data["dungeon_data"])  # * need launch all dj + errors(if no energy)
    if data["store_monster"]:
        store_all()  # * perfect
    if data["collect_rewards"]:
        collect_all_rewards()  # * good -> need code collect event rewards + upgrade rune ?

    if data["arena"]:
        arena(data["buy_arena_shop"])  # * good -> works perfectly but need update logic

    if data["rta"] is not Rta.NONE:
        rta(data["rta"])



def main():
    data = {
        "dungeon_data": {
            "dungeon": Dungeon.NONE,
            "30x10_run": True,
        },
        # * items to buy in magic and guild shop
        "items_to_buy_in_shops": {
            "ld_pieces": True,  # light and dark pieces
            "ms": True,  # mystical scroll
            "leg_scroll_pieces": True,  # legendary scroll pieces
            "grave_scroll_pieces": True,  # grave scroll pieces
            "unknown_scrolls": True,  # unknown scrolls
            "monster_pieces": True,  # monster pieces
        },
        "buy_arena_shop": {
            "diablemon": True,  # diablemon
            "ld_pieces": True,  # ld pieces
            "ms": True,  # mystical scroll
            "transmog_pieces": True,  # transmog pieces in rta shop
            "arcemon": True,  # arcemon in guilde shop
        },
        "collect_rewards": False,
        "store_monster": False,
        "rta": Rta.REGULAR,
        "arena": True,
    }
    sw_routine(data)

    return 0


if __name__ == "__main__":
    main()
