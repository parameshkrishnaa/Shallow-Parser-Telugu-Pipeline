import re
import sys


def parse_af_raw(fs):
    """
    Return AF string directly (like Tamil format)
    """
    m = re.search(r"af='([^']*)'", fs)
    if not m:
        return "_"
    return m.group(1)


def load_clause_sentences(cb_file):

    sentences = []

    with open(cb_file, encoding="utf-8") as f:
        for line in f:

            line = line.strip()

            # Normalize brackets → tokens
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

        # Sentence start
        if line.startswith("<Sentence"):

            sent_index += 1
            cb_index = 0
            token_id = 0

            continue

        if line.startswith("</Sentence>"):
            print()
            continue

        # Chunk start
        if re.match(r"\d+\s+\(\(", line):
            parts = line.split()
            chunk_tag = parts[-1]
            inside_chunk = False
            continue

        # Chunk end
        if line == "))":
            chunk_tag = None
            inside_chunk = False
            continue

        # Token line
        if re.match(r"\d+\.\d+", line):

            token_id += 1

            parts = line.split("\t")
            if len(parts) < 4:
                parts = re.split(r"\s+", line, maxsplit=3)

            _, word, pos, fs = parts

            af_raw = parse_af_raw(fs)

            # Chunk tagging
            if not inside_chunk:
                chunk = f"B-{chunk_tag}"
                inside_chunk = True
            else:
                chunk = f"I-{chunk_tag}"

            clause_tags = []

            if sent_index < len(cb_sentences):

                cb_tokens = cb_sentences[sent_index]

                # OPEN tags
                while cb_index < len(cb_tokens) and cb_tokens[cb_index].startswith("{") and not cb_tokens[cb_index].startswith("{/"):
                    clause_tags.append(cb_tokens[cb_index])
                    cb_index += 1

                # WORD match
                if cb_index < len(cb_tokens):
                    cb_index += 1

                # CLOSE tags
                while cb_index < len(cb_tokens) and cb_tokens[cb_index].startswith("{/"):
                    clause_tags.append(cb_tokens[cb_index])
                    cb_index += 1

            clause = "|".join(clause_tags) if clause_tags else "o"

            # FINAL FORMAT
            row = [
                str(sent_index + 1),   # Sentence ID
                "1",                  # Paragraph ID (fixed)
                str(token_id),
                word,
                pos,
                chunk,
                af_raw,
                "o",                 # GOV column
                clause
            ]

            print("\t".join(row))


if __name__ == "__main__":
    convert_ssf(sys.argv[1], sys.argv[2])