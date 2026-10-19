import logging
import os
class MusicXMLParser:
    def __init__(self):
        pass

    def process(self, input_path, output_midi_path):
        """
        Parses a MusicXML file (.xml or .mxl), extracts metadata, and converts it to a standard MIDI file.
        """
        from music21 import converter, tempo, note
        if not os.path.exists(input_path):
            raise FileNotFoundError(f"Input file not found: {input_path}")

        logger.info(f"Parsing MusicXML file: {input_path}")

        try:
            # Parse the score
            score = converter.parse(input_path)

            metadata = {
                "title": None,
                "composer": None,
                "lyrics": []
            }

            # Extract metadata
            if score.metadata is not None:
                if score.metadata.title:
                    metadata["title"] = score.metadata.title
                if score.metadata.composer:
                    metadata["composer"] = score.metadata.composer

            # Extract precise lyrics with timestamps
            # We iterate through all notes in the flattened score.
            # `music21` elements have an `offset` (in quarter notes) from the start of the piece.
            # To get seconds, we need to know the current tempo.

            # 1. Map tempo changes
            tempo_map = score.metronomeMarkBoundaries()

            # music21 provides a built-in offset-to-seconds converter if tempo marks exist.
            # However, if the MusicXML file doesn't explicitly declare a tempo, we default to 120 BPM.
            default_bpm = 120.0

            # Extract first tempo mark if exists
            tm = score.flat.getElementsByClass('MetronomeMark')
            if tm:
                default_bpm = tm[0].number

            def offset_to_seconds(off):
                # Simple and robust conversion assuming constant tempo for now
                # 1 quarter note offset = (60 / BPM) seconds
                return float(off) * (60.0 / default_bpm)

            # 2. Extract notes with lyrics
            structured_lyrics = []
            current_line = []

            for n in score.flat.notes:
                if n.lyric is not None:
                    # Calculate timestamps
                    start_sec = offset_to_seconds(n.offset)
                    end_sec = offset_to_seconds(n.offset + n.quarterLength)

                    syllable = n.lyric

                    # music21 stores syllabic information in n.lyrics[0].syllabic
                    # typical values: 'begin', 'middle', 'end', 'single'
                    is_end_of_word = True
                    if hasattr(n, 'lyrics') and n.lyrics and n.lyrics[0].syllabic in ['begin', 'middle']:
                        is_end_of_word = False

                    current_line.append({
                        'text': syllable,
                        'start': start_sec,
                        'end': end_sec,
                        'is_end_of_word': is_end_of_word
                    })

                    # If the note is followed by a long rest or it's the end of a phrase,
                    # we should break the line. For now, we will group by measures or sensible pauses.
                    # As a simple heuristic, if the gap to the next note is > 1 second, start a new line.
                    # Or, we can just return the raw structured syllables and let the TTS engine or orchestrator decide.

            if current_line:
                # Group syllables into logical lines for subtitles
                final_lines = []
                temp_line_str = ""
                line_start = None
                line_end = None

                for syl in current_line:
                    if line_start is None:
                        line_start = syl['start']

                    line_end = syl['end']

                    if syl['is_end_of_word']:
                        temp_line_str += syl['text'] + " "
                    else:
                        temp_line_str += syl['text'] # No space if it's the middle of a word

                    # Let's break lines every 5-6 words or if there is a massive gap.
                    # A robust method is to just pass the array of words back to main.py

                # We'll just pass the structured exact timings back.
                # The video uploader expects a list of dicts: [{'text': "phrase", 'start': 0.0, 'end': 2.0}]
                # Let's group them nicely into phrases.

                phrases = []
                phrase_words = []
                phrase_start = current_line[0]['start'] if current_line else 0

                for idx, syl in enumerate(current_line):
                    phrase_words.append(syl['text'] if not syl['is_end_of_word'] else syl['text'] + " ")

                    # Break phrase if: end of list, OR gap to next is > 1.5s, OR phrase is long (> 6 words)
                    gap_to_next = 0
                    if idx + 1 < len(current_line):
                        gap_to_next = current_line[idx+1]['start'] - syl['end']

                    if idx == len(current_line) - 1 or gap_to_next > 1.5 or len(phrase_words) > 8:
                        phrases.append({
                            'text': "".join(phrase_words).strip(),
                            'start': phrase_start,
                            'end': syl['end']
                        })
                        phrase_words = []
                        if idx + 1 < len(current_line):
                            phrase_start = current_line[idx+1]['start']

                metadata["lyrics"] = phrases
                metadata["raw_lyrics_text"] = " ".join([p['text'] for p in phrases])

            # Convert to MIDI and save
            logger.info(f"Converting {input_path} to MIDI: {output_midi_path}")
            score.write('midi', fp=output_midi_path)

            return metadata

        except Exception as e:
            logger.error(f"Failed to parse MusicXML: {e}")
            raise e
