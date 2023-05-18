import os

import bs4
import requests

FILE_PATH = os.path.split(os.path.dirname(__file__))[-1]


def get(word: str):
    try:
        page = requests.get(
            f"https://searchsentences.com/words/{word}-in-a-sentence",
        )
        page.raise_for_status()
    except requests.RequestException as e:
        return [], f"{FILE_PATH} couldn't get a web page: {e}"

    soup = bs4.BeautifulSoup(page.content, "html.parser")
    src = soup.find_all("li", {"class": "sentence-row"})
    sentences = []
    for sentence_block in src:
        if (sentence := sentence_block.find("span")) is None:
            continue
        text = sentence.get_text()
        if text:
            sentences.append(text)

    sentences.sort(key=len)
    i = 0
    size = yield
    while i < len(sentences):
        size = yield sentences[i : i + size], ""
        i += size

    return [], ""


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
