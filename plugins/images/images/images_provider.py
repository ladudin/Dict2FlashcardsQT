import json
import os
import re

import bs4
import requests

PLUGIN_NAME = os.path.split(os.path.dirname(__file__))[-1]


def get(word: str):
    link = f"https://www.google.com/search?tbm=isch&q={word}"
    user_agent = (
        "Mozilla/5.0 (Windows NT 6.1; Win64; x64) ApplewebKit/537.36 (KHTML, like Gecko) "
        "Chrome/70.0.3538.67 Safari/537.36"
    )
    headers = {"User-Agent": user_agent}
    try:
        r = requests.get(link, headers=headers)
        r.raise_for_status()
    except requests.RequestException:
        return [], f"[{PLUGIN_NAME}]: Couldn't get a web page!"

    html = r.text
    soup = bs4.BeautifulSoup(r.text, "html.parser")
    rg_meta = soup.find_all("div", {"class": "rg_meta"})
    metadata = [json.loads(e.text) for e in rg_meta]
    results = [d["ou"] for d in metadata]

    batch_size = yield
    if not results:
        regex = re.escape("AF_initDataCallback({")
        regex += r"[^<]*?data:[^<]*?" + r"(\[[^<]+\])"

        for txt in re.findall(regex, html):
            data = json.loads(txt)

            try:
                for d in data[31][0][12][2]:
                    try:
                        results.append(d[1][3][0])
                        if not len(results) % batch_size:
                            batch_size = yield results, ""
                            results = []
                    except Exception as exception:
                        pass
            except Exception as exception:
                try:
                    for d in data[56][1][0][0][1][0]:
                        try:
                            results.append(d[0][0]["444383007"][1][3][0])
                            if not len(results) % batch_size:
                                batch_size = yield results, ""
                                results = []
                        except Exception as exception:
                            pass
                except Exception as exception:
                    pass
    return results, ""


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
