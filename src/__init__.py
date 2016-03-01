# inner = sys.stdin.read()
import json

from gitworks import commit_patch
from handsome import full_project_info
from list_utils import filter_input
from translation import yandex_translate

# 3 из репозитория.
# Дополнительно нужно выводить русифицированные строки
# TZ 4.1.3
# Про архитектуру: модули и инструкции по расширению каждого модуля.


project_group = "import"
inner = "terminology-0.9.0-1-rosa2014.1.x86_64.rpm"
yandex_api_key = "trnsl.1.1.20160131T164826Z.1cd5efb8cc6af7a6.0d34545e70be2a8bdd261d6cf743ae3df1429d13"

assert yandex_translate(yandex_api_key, "en-ru",
                        "Lazy cat jumps over talking dog") == "Ленивый кот перепрыгивает через говорящая собака"

project_info = [full_project_info(project_group, f) for f in filter_input(inner)]
print(json.dumps(project_info))
translated_files = ""

for f in project_info[0]["desktop_files"]:
    print(str(f["path"]))
    translated_files = translated_files + f["path"] + "\n"
    for i in f["strings"]:
        pair = i.split('=')
        translated = str(pair[0] + "[ru]=" + yandex_translate(yandex_api_key, "en-ru", pair[1]))
        translated_files = translated_files + translated + "\n"
        print(i)
        print(translated)

commit_patch(project_info[0]["git"], project_info[0]["package_name"], translated_files)
