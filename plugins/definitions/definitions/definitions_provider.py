import os

from .utils import RESULT_FORMAT
from .utils import define as _define


def translate(definitons_data: RESULT_FORMAT):
    audio_region_field = "UK_audio_links"
    word_list = []

    for word, pos_lists in definitons_data.items():
        for pos_data in pos_lists:
            pos = pos_data["POS"]
            pos_fields = pos_data["data"]

            for (
                definition,
                definition_translation,
                examples,
                domain,
                level,
                region,
                usage,
                image,
                alt_terms,
                irreg_forms,
                region_audio_links,
            ) in zip(
                pos_fields["definitions"],
                pos_fields["definitions_translations"],
                pos_fields["examples"],
                pos_fields["domains"],
                pos_fields["levels"],
                pos_fields["regions"],
                pos_fields["usages"],
                pos_fields["image_links"],
                pos_fields["alt_terms"],
                pos_fields["irregular_forms"],
                pos_fields[audio_region_field],
            ):  # type: ignore
                current_word_dict = {
                    "word": word.strip(),
                    "special": irreg_forms + alt_terms,
                    "definition": f"{definition_translation}\n{definition}"
                    if definition_translation
                    else definition,
                    "examples": examples,
                    "audios": {
                        "web": region_audio_links,
                        "local": [],
                    },
                    "images": {
                        "web": [image] if image else [],
                        "local": [],
                    },
                    "other": [],
                    "tags": {
                        "domain": domain,
                        "region": region,
                        "usage": usage,
                        "pos": pos,
                    },
                }
                if level:
                    current_word_dict["tags"]["level"] = level

                word_list.append(current_word_dict)
    return word_list


def load():
    return


def unload():
    return


def get_config_description():
    return {}


def get_default_config():
    return {}


def set_config(new_config: dict) -> dict:
    return {}


def get(word: str):
    batch_size = yield
    definitions, error = _define(
        word,
    )
    cards = translate(definitions)
    i = 0
    while i < len(cards):
        res_batch = cards[i : i + batch_size]
        i += batch_size
        batch_size = yield res_batch, error
    return


if __name__ == "__main__":
    a = get("test")
    next(a)
    qwerwq = a.send(5)
