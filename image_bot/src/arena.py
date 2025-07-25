from src.click import click_img, drag_and_drop_with_random_area, click_until_red_pixel
from src.screen import find_img, find_img_with_red_top_right
from src.constants import DEFAULT_FAST_RECLICK_TIME
from src.packs import CLOSE_PACKS, NOT_SHOW_TODAY_PACKS, GRASS
from src.constants import DEFAULT_REGION, DEFAULT_CONFIDENCE


def go_to_arena(regular_arena=True):
    click_img(
        [("img/bataille_button.png",)] + NOT_SHOW_TODAY_PACKS + CLOSE_PACKS + GRASS,
        [
            {"path": "img/retour.png", "precise": True},
            {"path": "img/combat_de_classement.png", "precise": True},
            {"path": "img/back_arrow.png", "precise": True},
        ],
        click_random=False,
    )

    if find_img([("img/back_arrow.png",)]):
        drag_and_drop_with_random_area(
            start_point=(644, 548),
            start_area_radius=50,
            end_point=(1356, 554),
            end_area_radius=50,
            image_conditions=[("img/arena_island.png",)],
        )
        click_img(
            NOT_SHOW_TODAY_PACKS + CLOSE_PACKS + [("img/arena_island.png",)],
            [("img/arene.png",)],
            click_random=False,
        )
        click_img(
            [("img/arene.png",)],
            [("img/rival.png",), ("img/remove_arena_ranking.png",)],
        )
        click_img([("img/remove_arena_ranking.png",)], [("img/rival.png",)])

    if regular_arena and find_img([("img/combat_de_classement.png",)]):
        click_img(
            [("img/arena_tab.png",)],
            [("img/rival.png",), ("img/remove_arena_ranking.png",)],
        )
        click_img([("img/remove_arena_ranking.png",)], [("img/rival.png",)])


def check_rival_team():
    if not find_img([("img/rival_team.png",)]):
        click_img([("img/arena_shorcut.png",)], [("img/rival_shorcut.png",)])
        click_img([("img/rival_shorcut.png",)], [("img/rival_team.png",)])


def fight_rival():
    while not (find_img([("img/victory.png",), ("img/defeated.png",)])):
        click_img(
            [{"path": "img/auto_button.png", "confidence": DEFAULT_CONFIDENCE - 0.2}]
        )


def arena_fight_cycle(
    region: tuple[int, int, int, int] = DEFAULT_REGION,
    bottom_rivals=False,
):
    while find_img(
        [
            {"path": "img/arena_wing.png", "region": region},
            {"path": "img/arena_wing2.png", "region": region},
        ]
    ):
        click_img(
            [
                {"path": "img/arena_wing.png", "region": region},
                {"path": "img/arena_wing2.png", "region": region},
            ],
            [
                ("img/go_arena.png",),
                {"path": "img/croix1.png", "region": (0, 0, 1500, 1080)},
            ],
        )
        if find_img([{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}]):
            return
        check_rival_team()
        click_img([("img/go_arena.png",)], wait_until_images_to_click_gone=True)
        fight_rival()
        click_img(
            [("img/victory.png",), ("img/defeated.png",)],
            [("img/arene_list.png",)],
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
        if bottom_rivals:
            drag_and_drop_with_random_area(
                start_point=(933, 713),
                start_area_radius=50,
                end_point=(901, 420),
                end_area_radius=50,
                image_conditions=[("img/bottom_rivals.png",)],
            )


def buy_item():
    click_img([("img/acheter_shop.png",)], [("img/oui3.png",)])
    click_img([("img/oui3.png",)], [("img/ok3.png",)])
    click_img([("img/ok3.png",)], wait_until_images_to_click_gone=True)


def buy_items_in_arena_shop(buy_arena_shop):
    click_img([("img/croix1.png",)], [("img/shop_arena_button.png",)])

    click_img([("img/shop_arena_button.png",)], [("img/rta_shop_tab.png",)])

    if buy_arena_shop["diablemon"] and find_img([("img/devilmon.png",)]):
        click_img([("img/devilmon.png",)], [("img/acheter_shop.png",)])
        buy_item()

    if (
        find_img([("img/devilmon.png",)]) is False
        or buy_arena_shop["diablemon"] is False
    ):
        if buy_arena_shop["ld_pieces"] and find_img(
            [("img/ld_pieces_arena_shop.png",)]
        ):
            click_img([("img/ld_pieces_arena_shop.png",)], [("img/acheter_shop.png",)])
            is_red_pixel = click_until_red_pixel(
                images_to_click=[("img/plus3.png",)],
                red_pixel_region=(1026, 609, 88, 59),
                waiting_images=[
                    ("img/end_cursor_shop.png",),
                    ("img/full_item_to_buy.png", DEFAULT_CONFIDENCE + 0.05),
                ],
            )
            if is_red_pixel:
                click_img([("img/moins.png",)])
            if is_red_pixel is None:
                click_img(
                    [("img/croix_rune.png",)], wait_until_images_to_click_gone=True
                )
            else:
                buy_item()

        if (
            buy_arena_shop["ld_pieces"] is False
            or find_img([("img/ld_pieces_arena_shop.png",)]) is False
            and buy_arena_shop["ms"]
            and find_img([("img/ms_arena_shop.png",)])
        ):
            click_img([("img/ms_arena_shop.png",)], [("img/acheter_shop.png",)])
            is_red_pixel = click_until_red_pixel(
                images_to_click=[("img/plus3.png",)],
                red_pixel_region=(1026, 609, 88, 59),
                waiting_images=[("img/end_cursor_shop.png",)],
            )
            if is_red_pixel:
                click_img([("img/moins.png",)])
            if is_red_pixel is None:
                click_img(
                    [("img/croix_rune.png",)], wait_until_images_to_click_gone=True
                )
            else:
                buy_item()

    if buy_arena_shop["transmog_pieces"]:
        click_img([("img/rta_shop_tab.png",)], [("img/rta_shop_tab_selected.png",)])
        drag_and_drop_with_random_area(
            start_point=(1233, 569),
            start_area_radius=50,
            end_point=(416, 556),
            end_area_radius=50,
            image_conditions=[
                ("img/shift_stones.png",),
                ("img/no_shift_stones.png",),
            ],
        )
        if find_img([("img/shift_stones.png",)]):
            click_img([("img/shift_stones.png",)], [("img/acheter_shop.png",)])
            buy_item()

    if buy_arena_shop["arcemon"]:
        click_img(
            [("img/guild_arena_tab.png",)], [("img/guild_arena_tab_selected.png",)]
        )
        if find_img([("img/arcemon_shop.png",)]):
            click_img([("img/arcemon_shop.png",)], [("img/acheter_shop.png",)])
            buy_item()


def arena(buy_arena_shop):
    go_to_arena()

    click_img([("img/rival.png",)], [("img/arena_wing.png",)])

    arena_fight_cycle((0, 380, 1920, 700))

    if find_img([{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}]) is False:
        if find_img_with_red_top_right(("img/rival_tab.png",)):
            drag_and_drop_with_random_area(
                start_point=(933, 713),
                start_area_radius=50,
                end_point=(901, 420),
                end_area_radius=50,
                image_conditions=[("img/bottom_rivals.png",)],
            )

            arena_fight_cycle(bottom_rivals=True)

            if (
                find_img([{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}])
                is False
            ):
                drag_and_drop_with_random_area(
                    start_point=(901, 420),
                    start_area_radius=50,
                    end_point=(933, 713),
                    end_area_radius=50,
                    image_conditions=[("img/top_rivals.png",)],
                )
                arena_fight_cycle()
        else:
            arena_fight_cycle()
    click_img(
        [{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}],
        wait_until_images_to_click_gone=True,
    )

    buy_arena_shop_status = any(buy_arena_shop.values())
    if buy_arena_shop_status:
        buy_items_in_arena_shop(buy_arena_shop)
