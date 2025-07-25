from random import random
from src.click import click_img
from src.constants import DEFAULT_FAST_RECLICK_TIME, DEFAULT_CONFIDENCE
from src.screen import find_img, find_img_with_red_top_right
from src.enums import Rta
from src.arena import go_to_arena

REGION_TEAM = (169, 691, 453, 314)
REGION_LEAD = (207, 177, 612, 385)
REGION_BAN = (1078, 185, 592, 383)

CONDITION_TO_QUIT = [
    {
        "path": "img/silver3.png",
        "confidence": DEFAULT_CONFIDENCE - 0.05,
        "precise": True,
    }
]
CONDITION_TO_QUIT_SL = [
    {
        "path": "img/silver1.png",
        "confidence": DEFAULT_CONFIDENCE - 0.05,
        "precise": True,
    },
    {
        "path": "img/silver2.png",
        "confidence": DEFAULT_CONFIDENCE - 0.05,
        "precise": True,
    },
    {
        "path": "img/silver3.png",
        "confidence": DEFAULT_CONFIDENCE - 0.05,
        "precise": True,
    },
]

RTA_TEAM = [
    {"path": "img/maxi_icon.png", "region": REGION_TEAM},
    {"path": "img/wind_robo_icon.png", "region": REGION_TEAM},
    {"path": "img/dark_robo_icon.png", "region": REGION_TEAM},
    {"path": "img/bellenus_icon.png", "region": REGION_TEAM},
    {"path": "img/dorothy_icon.png", "region": REGION_TEAM},
]

RTA_TEAM_FOUR_STARS_ONLY = [
    {"path": "img/shimitae_icon.png", "region": REGION_TEAM},
    {"path": "img/draco_icon.png", "region": REGION_TEAM},
    {"path": "img/pralin_icon.png", "region": REGION_TEAM},
    {"path": "img/leah_icon.png", "region": REGION_TEAM},
    {"path": "img/julie_icon.png", "region": REGION_TEAM},
]

BAN = [
    {"path": "img/iunu.png", "region": REGION_BAN},
    {
        "path": "img/arena_speed_lead.png",
        "region": REGION_BAN,
        "confidence": DEFAULT_CONFIDENCE + 0.05,
    },
    {
        "path": "img/speed_lead.png",
        "region": REGION_BAN,
        "confidence": DEFAULT_CONFIDENCE + 0.05,
    },
]

LEAD = [
    {
        "path": "img/arena_speed_lead.png",
        "region": REGION_LEAD,
        "confidence": DEFAULT_CONFIDENCE + 0.05,
    },
    {
        "path": "img/speed_lead.png",
        "region": REGION_LEAD,
        "confidence": DEFAULT_CONFIDENCE + 0.05,
    },
]


def handle_quit_sequence(button_to_begin):
    click_img([("img/croix4.png",)], [("img/oui.png",), ("img/ok.png",)])
    click_img([("img/oui.png",), ("img/ok.png",)], button_to_begin)


def click_on_target():
    click_img(
        [
            {"path": "img/top_green_arrow.png", "precise": True, "y_offset": 150},
            {"path": "img/top_yellow_arrow.png", "precise": True, "y_offset": 150},
            {"path": "img/top_red_arrow.png", "precise": True, "y_offset": 150},
        ],
        click_random=False,
    )


def fight():
    while (find_img([("img/victory.png",), ("img/defeated.png",)])) is False:
        if find_img([("img/dark_robo_s1.png",)]):
            click_img(
                [("img/dark_robo_s2.png",), ("img/dark_robo_s3.png",)],
                click_random=False,
            )
            click_on_target()
        if find_img([("img/wind_robo_s1.png",)]):
            click_img(
                [("img/wind_robo_s2.png",), ("img/wind_robo_s3.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/maxi_s1.png",)]):
            click_img(
                [("img/maxi_s3.png",), ("img/maxi_s2.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/bellenus_form1_s1.png",), ("img/bellenus_form2_s1.png",)]):
            click_img(
                [("img/bellenus_form1_s3.png",), ("img/bellenus_form2_s2.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/dorothy_s1.png",)]):
            click_img(
                [("img/dorothy_s3.png",), ("img/dorothy_s2.png",)],
                click_random=False,
            )
            click_on_target()


def fight_four_stars_SL():
    while (find_img([("img/victory.png",), ("img/defeated.png",)])) is False:
        if find_img([("img/draco_s1.png",)]):
            click_img(
                [("img/draco_s3.png",), ("img/draco_s2.png",)],
                click_random=False,
            )
            click_on_target()
        if find_img([("img/pralin_s1.png",)]):
            click_img(
                [("img/pralin_s3.png",), ("img/pralin_s2.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/shimitae_s1.png",)]):
            click_img(
                [("img/shimitae_s2.png",), ("img/shimitae_s3.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/julie_s1.png",)]):
            click_img(
                [("img/julie_s3.png", DEFAULT_CONFIDENCE - 0.2), ("img/julie_s2.png",)],
                click_random=False,
            )
            click_on_target()

        if find_img([("img/leah_s1.png",)]):
            click_img(
                [("img/leah_s2.png",)],
                click_random=False,
            )
            click_on_target()


def go_to_rta(rta_type):
    if find_img([("img/combat_de_classement.png",)]) is False:
        go_to_arena(False)
        click_img(
            [("img/rta_tab.png",)], [("img/combat_de_classement.png",), ("img/ok.png",)]
        )
        click_img([("img/ok.png",)], [("img/combat_de_classement.png",)])

    if rta_type is Rta.REGULAR:
        if (
            find_img([{"path": "img/combat_de_classement.png", "precise": True}])
            is False
        ):
            return False
    else:
        if find_img([("img/special_league.png",)]):
            click_img([("img/special_league.png",)], [("img/commencer_SL.png",)])
            if (find_img([{"path": "img/commencer_SL.png", "precise": True}])) is False:
                return False
        else:
            return False

    return True


def collect_rta_rewards():
    if find_img_with_red_top_right(("img/info.png",), 1000):
        click_img([("img/info.png",)], [("img/defis_de_saison.png",)])
        click_img(
            [("img/defis_de_saison.png",)],
            [{"path": "img/defis_de_saison_selected.png", "precise": True}],
        )
        click_img(
            [("img/recolter_rta.png",)],
            wait_until_images_to_click_gone=True,
            reclick_time=DEFAULT_FAST_RECLICK_TIME,
        )
        click_img([("img/croix1.png",)], [("img/combat_de_classement.png",)])


def rta(rta_type):
    can_go_rta = go_to_rta(rta_type)

    if can_go_rta:
        if rta_type is Rta.REGULAR:
            button_to_begin = [
                {"path": "img/combat_de_classement.png", "precise": True}
            ]
        else:
            button_to_begin = [{"path": "img/commencer_SL.png", "precise": True}]

        if rta_type is Rta.REGULAR:
            rta_team = RTA_TEAM
        elif rta_type is Rta.SL_FOUR_STARS_ONLY:
            rta_team = RTA_TEAM_FOUR_STARS_ONLY

        while True:
            rank_to_quit = (
                CONDITION_TO_QUIT if rta_type is Rta.REGULAR else CONDITION_TO_QUIT_SL
            )
            quit = (
                1
                if find_img(rank_to_quit)
                or (find_img([("img/placement_en_cours.png",)]) and random() > 0.3)
                else 0
            )
            click_img(button_to_begin, [("img/croix4.png",), ("img/ok.png",)])
            if find_img([("img/no_rta_wing_SL.png",), ("img/no_rta_wing.png",)]):
                click_img([("img/ok.png",)], button_to_begin)
                break

            if quit:
                handle_quit_sequence(button_to_begin)
                continue

            for i in range(5):
                check_monster_picked = []
                protection_no_click = []
                if i <= 2:
                    CLICK = rta_team
                    check_monster_picked = [
                        (
                            "img/monster_picked.png",
                            DEFAULT_CONFIDENCE - 0.35,
                            REGION_TEAM,
                        )
                    ]
                elif i == 3:
                    CLICK = BAN
                    protection_no_click = [("img/select_lead.png",)]
                else:
                    CLICK = LEAD

                while (
                    find_img(
                        [
                            {"path": "img/ok_rta_greyish.png", "precise": True},
                            ("img/ok.png",),
                        ]
                        + check_monster_picked
                    )
                ) is False:
                    pass

                click_img(
                    CLICK,
                    [{"path": "img/ok_rta.png", "precise": True}, ("img/ok.png",)]
                    + protection_no_click  # * if there is no ban
                    + check_monster_picked,
                    reclick_time=DEFAULT_FAST_RECLICK_TIME,
                    click_random=False,
                )
                click_img(
                    [{"path": "img/ok_rta.png", "precise": True}],
                    wait_until_images_to_click_gone=True,
                    reclick_time=DEFAULT_FAST_RECLICK_TIME,
                )

                if find_img([("img/ok.png",)] + check_monster_picked):
                    break

            if find_img([("img/ok.png",)]):
                click_img([("img/ok.png",)], button_to_begin)
                continue

            if find_img(check_monster_picked):
                handle_quit_sequence(button_to_begin)
                continue

            if rta_type is Rta.REGULAR:
                fight()
            elif rta_type is Rta.SL_FOUR_STARS_ONLY:
                fight_four_stars_SL()
            click_img(
                [
                    ("img/victory.png", DEFAULT_CONFIDENCE - 0.05),
                    ("img/defeated.png", DEFAULT_CONFIDENCE - 0.05),
                ],
                button_to_begin,
                reclick_time=DEFAULT_FAST_RECLICK_TIME,
            )

    click_img([("img/croix1.png",)], wait_until_images_to_click_gone=True)

    collect_rta_rewards()
