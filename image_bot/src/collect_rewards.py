from src.click import click_img, drag_and_drop_with_random_area, click_until_red_pixel
from src.screen import find_img_with_red_top_right, find_img
from src.constants import DEFAULT_FAST_RECLICK_TIME, DEFAULT_CONFIDENCE
from src.packs import remove_packs


def collect_missions_rewards():
    remove_packs([("img/missions.png",)])

    if find_img_with_red_top_right(("img/missions.png",), number_of_red_pixel=700):
        click_img([("img/missions.png",)], [("img/croix4.png",)])
        click_img(
            [("img/recevoir_missions.png",)],
            wait_until_images_to_click_gone=True,
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )

    click_img(
        [
            ("img/croix1.png",),
            ("img/croix_rune.png",),
            ("img/recolter.png",),
        ],  # todo upgrade rune ?
        wait_until_images_to_click_gone=True,
        click_random=False,
    )


def collect_shop_reward():
    remove_packs([("img/shop.png",)])

    if find_img_with_red_top_right(("img/shop.png",), number_of_red_pixel=2950):
        click_img([("img/shop.png",)], [("img/croix4.png",)])
        click_img(
            [("img/croix1.png",)],
            [{"path": "img/limite.png", "precise": True}],
        )
        click_img(
            [{"path": "img/limite.png", "precise": True}],
            [{"path": "img/limite_selected.png", "precise": True}],
        )
        # collect 25 crystals
        if find_img([("img/free_crystals.png",)]):
            click_img([("img/free_crystals.png",)], [("img/ok.png",)])
            click_img([("img/ok.png",)], wait_until_images_to_click_gone=True)

        # collect monthly rewards
        if find_img([("img/monsthly_rewards.png",)]):
            click_img([("img/monsthly_rewards.png",)], [("img/recevoir_monthly.png",)])
            click_img([("img/recevoir_monthly.png",)], [("img/ok.png",)])
            click_img([("img/ok.png",)], wait_until_images_to_click_gone=True)

        # collect 1 mystical scroll
        click_img(
            [{"path": "img/exclusif.png", "precise": True}],
            [{"path": "img/exclusif_selected.png", "precise": True}],
        )
        if find_img([("img/free_ms.png",)]):
            click_img([("img/free_ms.png",)], [("img/ok.png",)])
            click_img([("img/ok.png",)], wait_until_images_to_click_gone=True)


def collect_current_inbox():
    click_img([("img/inbox_refresh.png",)])
    if find_img([{"path": "img/recevoir_en_une_fois.png", "precise": True}]):
        click_img(
            [("img/recevoir_en_une_fois.png",)],
            [("img/recevoir.png",), ("img/ok.png",)],
        )
        click_img(
            [("img/recevoir.png",), ("img/ok.png",)], [("img/inbox_refresh.png",)]
        )


def collect_inbox_rewards():
    remove_packs([("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)])

    while drag_and_drop_with_random_area(
        start_point=(166, 454),
        start_area_radius=50,
        end_point=(166, 775),
        end_area_radius=50,
        image_conditions=[("img/inbox.png",)],
    ):
        pass

    if find_img([("img/inbox.png",)]):
        click_img([("img/inbox.png",)], [("img/inbox_refresh.png",)])
        if find_img([("img/box_unchecked2.png",)]):
            click_img([("img/box_unchecked2.png",)], [("img/ok.png",)])
            click_img([("img/ok.png",)], [("img/box_checked2.png",)])

        collect_current_inbox()

        if find_img_with_red_top_right(
            ("img/guild_inbox.png",), number_of_red_pixel=700
        ):
            click_img(
                [{"path": "img/guild_inbox.png", "precise": True}],
                wait_until_images_to_click_gone=True,
                reclick_time=DEFAULT_FAST_RECLICK_TIME,
            )
            collect_current_inbox()

        if find_img_with_red_top_right(
            ("img/points_sociaux_inbox.png",), number_of_red_pixel=700
        ):
            click_img(
                [{"path": "img/points_sociaux_inbox.png", "precise": True}],
                wait_until_images_to_click_gone=True,
                reclick_time=DEFAULT_FAST_RECLICK_TIME,
            )

            click_img(
                [{"path": "img/tout_recevoir.png", "precise": True}],
                [
                    {"path": "img/tout_recevoir_greyish.png", "precise": True},
                    ("img/ok.png",),
                ],
            )
            click_img([("img/ok.png",)], wait_until_images_to_click_gone=True)

        # * put back for anniversary
        # if find_img_with_red_top_right(("img/X_years_inbox.png",)):
        #     click_img(
        #         [{"path": "img/X_years_inbox.png", "precise": True}],
        #         wait_until_images_to_click_gone=True,
        #         reclick_time=DEFAULT_FAST_RECLICK_TIME,
        #     )
        #     collect_current_inbox()


def collect_social_points_and_guild_energy():
    remove_packs([("img/communaute.png",)])

    click_img([("img/communaute.png",)], [("img/ami.png",)])

    if find_img([("img/pointage.png",)]) and find_img_with_red_top_right(
        ("img/pointage.png",), 800
    ):
        click_img(
            [("img/pointage.png",)],
            [("img/recuperer.png",)],
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
        click_img(
            [("img/recuperer.png",)],
            [("img/ok2.png",)],
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
        click_img(
            [("img/ok2.png",)],
            wait_until_images_to_click_gone=True,
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
        click_img(
            [
                {
                    "path": "img/croix1.png",
                    "region": (0, 0, 1600, 1080),
                    "click_area_reduction": 0.5,
                }
            ],
            wait_until_images_to_click_gone=True,
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )

    click_img(
        [("img/ami.png",)],
        [("img/tout_envoyer.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )
    click_img(
        [("img/tout_envoyer.png",)],
        [("img/ok.png",), ("img/oui.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )
    click_img(
        [("img/ok.png",), ("img/oui.png",)],
        [("img/tout_envoyer.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )


def collect_energy_and_crystals_buildings():
    remove_packs([("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)])

    click_img(
        [
            {
                "path": "img/energy_icon.png",
                "region": (0, 0, 1500, 1080),
                "y_offset": 90,
            }
        ],
        wait_until_images_to_click_gone=True,
    )
    click_img(
        [
            {
                "path": "img/crystal_icon.png",
                "y_offset": 90,
            }
        ],
        wait_until_images_to_click_gone=True,
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )


def collect_energy_and_crystals_dimension():
    remove_packs([("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)])

    click_img([("img/energy_icon2.png",)], [("img/plus.png",)])
    click_img(
        [{"path": "img/plus.png", "index": 0}], [("img/energy_social_point.png",)]
    )
    click_img([("img/energy_social_point.png",)], [("img/plus2.png",)])

    bar_status = click_until_red_pixel(
        images_to_click=[("img/plus2.png",)],
        red_pixel_region=(651, 589, 86, 64),
        waiting_images=[("img/end_cursor_energy.png",)],
    )

    if bar_status:
        click_img([("img/moins3.png",)])

    if bar_status is None:
        click_img(
            [{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}],
            wait_until_images_to_click_gone=True,
        )
    else:
        click_img([("img/acheter2.png",)], [("img/ok.png",)])
        click_img([("img/ok.png",)], [("img/energy_social_point.png",)])

    # get crystal dimension
    while drag_and_drop_with_random_area(
        start_point=(1233, 569),
        start_area_radius=50,
        end_point=(416, 556),
        end_area_radius=50,
        image_conditions=[
            ("img/crystal_dimension.png",),
            ("img/no_crystal_dimension.png",),
        ],
    ):
        pass
    if find_img([("img/crystal_dimension.png",)]):
        click_img([("img/crystal_dimension.png",)], [("img/acheter_shop.png",)])
        click_img([("img/acheter_shop.png",)], [("img/ok.png",)])
        click_img([("img/ok.png",)], wait_until_images_to_click_gone=True)


def buy_max(reaps=True):
    if find_img([("img/creer.png",)]):
        bar_status = click_until_red_pixel(
            images_to_click=[("img/plus3.png",)],
            red_pixel_region=(877, 772, 594, 32),
            waiting_images=[("img/end_cursor_shop.png",)],
        )
        if bar_status:
            click_img([("img/moins2.png",)])

        if bar_status is not None:
            if reaps:
                while True:
                    click_img(
                        [("img/creer.png",)],
                        [("img/fermer.png",), ("img/oui.png",), ("img/ok.png",)],
                    )
                    if find_img([("img/ok.png",)]):
                        click_img([("img/ok.png",)], [("img/moins2.png",)])
                        click_img([("img/moins2.png",)])
                    else:
                        break
                click_img([("img/oui.png",)], [("img/fermer.png",)])
                click_img([("img/fermer.png",)], wait_until_images_to_click_gone=True)
            else:
                click_img([("img/creer.png",)], [("img/oui.png",)])
                click_img([("img/oui.png",)], [("img/vente_selective.png",)])
                click_img(
                    [("img/vente_selective.png",)], [("img/vente_selective3.png",)]
                )
                click_img([("img/vente_selective3.png",)], [("img/oui.png",)])
                click_img(
                    [("img/oui.png",)],
                    [
                        {
                            "path": "img/croix1.png",
                            "region": (0, 0, 1500, 1080),
                            "precise": True,
                        }
                    ],
                )
                click_img(
                    [{"path": "img/croix1.png", "region": (0, 0, 1500, 1080)}],
                    wait_until_images_to_click_gone=True,
                )


def get_reap_and_buy_magic_boxes():
    remove_packs([("img/crafting_building.png",)])

    click_img([("img/crafting_building.png",)], [("img/crafting.png",)])
    click_img([("img/crafting.png",)], [("img/special.png",)])
    click_img(
        [("img/special.png",)],
        [("img/reap_antic.png",)],
        reclick_time=DEFAULT_FAST_RECLICK_TIME,
    )

    buy_max()

    click_img(
        [{"path": "img/reap_antic.png", "precise": True}],
        wait_until_images_to_click_gone=True,
    )

    buy_max()

    click_img([("img/autres.png",)], [("img/magic_box.png",)])
    click_img(
        [("img/magic_box.png",)],
        [("img/magic_box_page.png",)],
    )

    buy_max(False)


def make_wish():
    remove_packs([("img/wish_building.png",)])

    click_img([("img/wish_building.png",)], [("img/voeux.png",)])
    click_img([("img/voeux.png",)], [("img/make_a_wish.png",)])
    click_img([("img/make_a_wish.png",)], [("img/oui.png",)])
    if find_img([("img/faire_un_voeu.png",)]):
        click_img(
            [("img/oui.png",)],
            [{"path": "img/make_a_wish_greyish.png", "precise": True}],
        )
        while (
            find_img([{"path": "img/make_a_wish_greyish.png", "precise": True}])
            or find_img([{"path": "img/croix1.png", "precise": True}]) is False
        ):
            pass
        click_img(
            [("img/croix_rune.png",), ("img/croix1.png",)],
            wait_until_images_to_click_gone=True,
            click_random=False,
        )
    else:
        click_img([("img/non.png",)], wait_until_images_to_click_gone=True)

    # * reset view
    remove_packs([("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)])

    click_img(
        [("img/magic_shop_building.png", DEFAULT_CONFIDENCE - 0.35)],
        [("img/acheter.png",)],
    )
    click_img(
        [
            ("img/ok.png",),
            ("img/acheter.png",),
        ],
        [{"path": "img/echoppe_de_magie.png", "precise": True}],
        click_random=False,
    )


def collect_rewards_on_event_page(recevoir_buttons, termine_buttons, errors):
    while find_img([("img/reward_on_event.png",)]):
        click_img([("img/reward_on_event.png",)], [("img/back_event.png",)])
        while drag_and_drop_with_random_area((977, 943), 50, (973, 112), 50):
            click_counter = 0
            while find_img(recevoir_buttons) and click_counter < 8:
                click_img(recevoir_buttons)
                if find_img(errors):
                    while find_img(recevoir_buttons) is False:
                        pass
                    break
                while find_img(termine_buttons) is False:
                    pass
                click_counter += 1
        click_img([("img/back_event.png",)], [("img/nouvelles.png",)])


def get_events_rewards():
    remove_packs([("img/event_icon.png",)])

    recevoir_buttons = [
        {"path": "img/recevoir_event1.png", "precise": True},
        {"path": "img/recevoir_event2.png", "precise": True},
        {"path": "img/recevoir_event3.png", "precise": True},
        {"path": "img/recevoir_event4.png", "precise": True},
    ]

    termine_buttons = [
        {"path": "img/recevoir_event_grey1.png", "precise": True},
        {"path": "img/recevoir_event_grey2.png", "precise": True},
        {"path": "img/termine_event1.png", "precise": True},
        {"path": "img/termine_event2.png", "precise": True},
        {"path": "img/termine_event3.png", "precise": True},
        {"path": "img/termine_event4.png", "precise": True},
    ]

    errors = [("img/veuillez_verifier.png",)]

    click_img([("img/event_icon.png",)], [("img/nouvelles.png",)])
    click_img([("img/evenement.png",)], [("img/evenement_selected.png",)])

    collect_rewards_on_event_page(recevoir_buttons, termine_buttons, errors)
    while drag_and_drop_with_random_area((1128, 827), 50, (1141, 326), 50):
        collect_rewards_on_event_page(recevoir_buttons, termine_buttons, errors)

    click_img([("img/croix_page_events.png",)], wait_until_images_to_click_gone=True)


def collect_all_rewards():
    collect_energy_and_crystals_buildings()  # * perfect
    collect_shop_reward()  # * perfect
    collect_social_points_and_guild_energy()  # * perfect
    collect_missions_rewards()  # * good todo: upgrade rune after ?
    collect_energy_and_crystals_dimension()  # * perfect
    make_wish()  # * good todo: upgrade rune after ?
    get_events_rewards()  # * perfect
    collect_inbox_rewards()  # * perfect
    get_reap_and_buy_magic_boxes()  # * perfect
