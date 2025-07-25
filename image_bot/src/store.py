from src.packs import remove_packs
from src.click import click_img
from src.screen import find_img


def put_in_storage():
    if find_img([{"path": "img/arrow_storage.png", "precise": True}]):
        click_img(
            [{"path": "img/arrow_storage.png", "precise": True}],
            wait_until_images_to_click_gone=True,
        )


def check_if_all_selected():
    if find_img([("img/unchecked_box.png",)]):
        click_img([("img/unchecked_box.png",)], [("img/checked_box.png",)])


def store_arcemon():
    remove_packs([("img/arcemon_building.png",)])

    click_img([("img/arcemon_building.png",)], [("img/entreposer.png",)])
    click_img([("img/entreposer.png",)], [("img/croix1.png",)])
    check_if_all_selected()
    put_in_storage()


def store_monster():
    remove_packs([("img/monster_building.png",)])

    click_img([("img/monster_building.png",)], [("img/invoque.png",)])
    click_img([("img/invoque.png",)], [("img/croix1.png",)])
    check_if_all_selected()
    put_in_storage()


def store_all():
    store_arcemon()
    store_monster()
