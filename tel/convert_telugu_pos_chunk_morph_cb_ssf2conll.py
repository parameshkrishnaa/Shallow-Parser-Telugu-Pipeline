import re
import sys


def parse_af(fs):

    m = re.search(r"af='([^']*)'", fs)

    if not m:
        return "_", "_", "_"

    parts = m.group(1).split(",")
    parts += ["_"] * (8 - len(parts))

    lemma, lcat, gender, number, person, case, vib, suff = parts[:8]

    lemma = lemma if lemma else "_"
    lcat = lcat if lcat else "_"

    feats = (
        f"Gender={gender or '_'}|"
        f"Number={number or '_'}|"
        f"Person={person or '_'}|"
        f"Case={case or '_'}|"
        f"Vib={vib or '_'}|"
        f"Suff={suff or '_'}"
    )

    return lemma, lcat, feats


def load_clause_sentences(cb_file):

    sentences = []

    with open(cb_file, encoding="utf-8") as f:

        for line in f:

            line = line.strip()

            # normalize clause brackets
            line = re.sub(r'(\w+)\[', r' {\1} ', line)
            line = re.sub(r'\](\w+)', r' {/\1} ', line)

            tokens = line.split()

            sentences.append(tokens)

    return sentences


def convert_ssf(ssf_file, cb_file):

    cb_sentences = load_clause_sentences(cb_file)

    with open(ssf_file, encoding="utf-8") as f:
        lines = f.readlines()

    sent_index = -1
    cb_index = 0

    token_id = 0
    chunk_tag = None
    inside_chunk = False

    for line in lines:

        line = line.strip()

        if not line:
            continue

        if line.startswith("#Text"):
            print(line)
            continue

        if line.startswith("<Sentence"):

            sent_index += 1
            cb_index = 0
            token_id = 0

            sid = re.search(r'id="(\d+)"', line)

            if sid:
                print(f"# sent_id = {sid.group(1)}")

            continue

        if line.startswith("</Sentence>"):
            print()
            continue

        if re.match(r"\d+\s+\(\(", line):

            parts = line.split()
            chunk_tag = parts[-1]
            inside_chunk = False
            continue

        if line == "))":
            chunk_tag = None
            inside_chunk = False
            continue

        if re.match(r"\d+\.\d+", line):

            token_id += 1

            parts = line.split("\t")

            if len(parts) < 4:
                parts = re.split(r"\s+", line, maxsplit=3)

            _, word, pos, fs = parts

            lemma, lcat, feats = parse_af(fs)

            if not inside_chunk:
                chunk = f"B-{chunk_tag}"
                inside_chunk = True
            else:
                chunk = f"I-{chunk_tag}"

            clause_tags = []

            if sent_index < len(cb_sentences):

                cb_tokens = cb_sentences[sent_index]

                # opening tags before token
                while cb_index < len(cb_tokens) and cb_tokens[cb_index].startswith("{") and not cb_tokens[cb_index].startswith("{/"):
                    clause_tags.append(cb_tokens[cb_index])
                    cb_index += 1

                # consume word
                if cb_index < len(cb_tokens):
                    cb_index += 1

                # closing tags after token
                while cb_index < len(cb_tokens) and cb_tokens[cb_index].startswith("{/"):
                    clause_tags.append(cb_tokens[cb_index])
                    cb_index += 1

            clause = "|".join(clause_tags) if clause_tags else "_"

            row = [
                str(token_id),
                word,
                lemma,
                lcat,
                pos,
                feats,
                "_",
                chunk,
                clause
            ]

            print("\t".join(row))


if __name__ == "__main__":

    convert_ssf(sys.argv[1], sys.argv[2])