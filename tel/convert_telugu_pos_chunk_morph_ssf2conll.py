import re

def parse_fs(fs_str):
	m = re.search(r"af='([^']*)'", fs_str)
	if not m:
		return ["NULL"] * 8

	parts = m.group(1).split(",")

	# ఖాళీగా ఉన్న ఫీల్డ్స్‌ని NULL గా మార్చడం
	parts = [p if p.strip() != "" else "NULL" for p in parts]

	# 8 ఫీల్డ్స్‌కి pad/trim చెయ్యడం
	parts = parts + ["NULL"] * (8 - len(parts))
	return parts[:8]

def convert_to_conllu(input_file, output_file):
	with open(input_file, "r", encoding="utf-8") as f:
		lines = f.readlines()

	out_lines = []
	sent_id = None
	chunk_tag = None
	inside_chunk = False
	token_id = 0

	for line in lines:
		line = line.strip()
		if not line:
			continue
		if line.startswith("#Text"):
			out_lines.append(line)
			continue
		# Sentence start
		if line.startswith("<Sentence"):
			sent_id = re.search(r"id=[\"'](\d+)[\"']", line).group(1)
			out_lines.append(f"# sent_id = {sent_id}")
			token_id = 0
			continue

		# Sentence end
		if line.startswith("</Sentence>"):
			out_lines.append("")  # blank line between sentences
			continue


		if re.search(r"\t\(\(\t", line):
			parts = line.split("\t")
			if len(parts) >= 3:
				chunk_tag = parts[2]  # NP, VGF, BLK, etc.
				inside_chunk = False
			continue

		# Token line like: "1.1 అడల్ట్ JJ  <fs af='అడల్ట్,adj,,,,,,'>"
		if re.match(r"\d+\.\d+", line):
			# print(line)

			token_id += 1
			parts = line.split("\t")
			if len(parts) < 4:
				continue
			_, token, pos, fs = parts[0], parts[1], parts[2], parts[3]

			af_fields = parse_fs(fs)

			# BIS tagging
			if not inside_chunk:
				chunk_bis = f"B-{chunk_tag}"
				inside_chunk = True
			else:
				chunk_bis = f"I-{chunk_tag}"

			#row = [str(token_id), token, pos, chunk_bis] + af_fields
			row = [str(token_id), token, pos, chunk_bis, fs] #+ fs
			out_lines.append("\t".join(row))
			continue

		# Chunk end "))"
		if line.strip() == "))":
			chunk_tag = None
			inside_chunk = False
			continue

	with open(output_file, "w", encoding="utf-8") as f:
		f.write("\n".join(out_lines))

# Example usage
import sys
convert_to_conllu(sys.argv[1], "out.conllu")
