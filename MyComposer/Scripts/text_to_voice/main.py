import sys
from text_to_voice import text_to_mp3, mp3_to_notes
import time


def run_my_composer(text: str, gender: str):
    if gender == "male":
        raise NotImplementedError("Gender 'male' is not supported")

    elif gender == "female":
        filename: str = str(int(time.time())) + "_female_output.mp3"
        text_to_mp3(text, filename)
        mp3_to_notes(filename)

    else:
        raise ValueError("Gender should be 'male' or 'female'")


if __name__ == '__main__':
    text: str = sys.argv[1]
    gender: str = sys.argv[2]

    run_my_composer(text, gender)
