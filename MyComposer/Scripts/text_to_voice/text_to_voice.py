from gtts import gTTS
import pyttsx3
import librosa
from notes import BINS_BUCKET1, BINS_BUCKET2, BINS_BUCKET3


def text_to_mp3(text: str, filename: str):
    # Initialize gTTS with the selected language
    tts = gTTS(text=text, lang='en', slow=False)

    # Save the speech to an audio file
    tts.save("./music/" + filename)


def text_to_wav(text: str, filename: str):
    # Initialize the TTS engine
    engine = pyttsx3.init()

    engine.setProperty('rate', 200)  # Speed of speech
    engine.setProperty('volume', 1.0)  # Volume level (0.0 to 1.0)

    # Save to WAV
    engine.save_to_file(text, "./music/" + filename)
    engine.runAndWait()

def _get_note_with_length_per_note_mili_sec(notes, key, length_per_note_mili_sec):
    try:
        if notes[len(notes) - 1][0] == key:
            # print(f" Appending {(key, notes[len(notes)-1][1]+1)}")
            notes[len(notes) - 1] = (key, notes[len(notes) - 1][1] + length_per_note_mili_sec)
        else:
            # print(f" Appending {(key, 1)}")
            notes.append((key, length_per_note_mili_sec))
    except IndexError:
        # print(f" Appending {(key, 1)}")
        notes.append((key, length_per_note_mili_sec))

def mp3_to_notes(filename: str):
    sample_rate = 40000
    y, sr = librosa.load("./music/" + filename, sr=sample_rate)
    pitches, magnitudes = librosa.core.piptrack(y=y, sr=sr, fmin=31, fmax=4978)

    length_per_note_mili_sec = round((y.shape[0] / sample_rate) / pitches.shape[1] * 1000)

    notes = []

    for t in range(pitches.shape[1]):
        index = magnitudes[:, t].argmax()
        pitch = int(pitches[index, t])

        if pitch < 175:
            for key, value in BINS_BUCKET1.items():
                if value[0] <= pitch <= value[1]:
                    _get_note_with_length_per_note_mili_sec(notes, key, length_per_note_mili_sec)

        elif 174 < pitch < 988:
            for key, value in BINS_BUCKET2.items():
                if value[0] <= pitch <= value[1]:
                    _get_note_with_length_per_note_mili_sec(notes, key, length_per_note_mili_sec)

        else:
            for key, value in BINS_BUCKET3.items():
                if value[0] <= pitch <= value[1]:
                    _get_note_with_length_per_note_mili_sec(notes, key, length_per_note_mili_sec)

