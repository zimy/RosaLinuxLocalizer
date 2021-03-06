import yaml
from os import listdir
from os.path import isfile, join


def filter_input(file_names):
    """
    splits input stream onto strings
    :param file_names: slash-n-separated list of file names
    :return: list of file names [string]
    """
    return [x for x in file_names.split("\n") if ".rpm" in x]


def in_dir(path):
    return [f for f in listdir(path) if isfile(join(path, f))]


def from_file_with_list(path):
    with open(path, 'r') as stream:
        try:
            print(yaml.load(stream))
        except yaml.YAMLError as exc:
            print(exc)
