import subprocess
import os
import sys
import shutil
from pathlib import Path
import time

# Set environment for UTF-8
env = os.environ.copy()
env["LC_ALL"] = "en_US.UTF-8"
env["LANG"] = "en_US.UTF-8"

#from config import tel_modules_path

#tel_modules_path = '/home/nagaraju/git/shallow-parser-pipeline/tel/'
tel_modules_path = env["setu"]

# tel_modules_path = str(Path(__file__).resolve().parent) + "/"
# print(f"TEL Modules Path: {tel_modules_path}/")

# === Shell script paths ===
PIPELINE = [
	("tokenizer", tel_modules_path + "/tokenizer/tokenizer_run.sh"),
	("morph", tel_modules_path + "/morph/bin/sl/morph/tel/morph.sh"),
	("postagger", tel_modules_path + "/postagger/bin/sl/postagger/postagger.sh"),
	("chunker", tel_modules_path + "/chunker/bin/sl/chunker/tel/chunker.sh"),
	("pruning", tel_modules_path + "/pruning/bin/sl/pruning/pruning.sh"),
	("guessmorph", tel_modules_path + "/guessmorph/bin/sl/guess_morph/guess-morph.sh"),
	("pickonemorph", tel_modules_path + "/pickonemorph/bin/sl/pickonemorph/tel/pickonemorph.sh"),
	("convertor", tel_modules_path + "/convertor/wx2utf_run_ssf.sh")
]

def ensure_utf8_lines(filepath, remove_fs_pipe=True):
	with open(filepath, 'r', encoding='utf-8') as f:
		lines = [line.rstrip() for line in f if line.strip()]
		if remove_fs_pipe:
			lines = [line.replace("<fs>|", "") for line in lines]
	with open(filepath, 'w', encoding='utf-8') as f:
		f.write('\n'.join(lines) + '\n')

def run_script(step_name, script_path, input_file, output_file, working_dir,  timeout=3, retries=1):
	print(f"Running {step_name}...")
	os.chdir(working_dir)
	attempt = 0
	while attempt <= retries:
		try:
			with open(output_file, 'w', encoding='utf-8') as out_f:
				if step_name == "convertor":
					#print(f"Executing convertor script: {script_path} ssf tel {input_file}")
					result = subprocess.run(['sh', script_path, "ssf", "tel", input_file, ],
										stdout=out_f, stderr=subprocess.PIPE,
										text=True, env=env, timeout=timeout)
				else:
					#print(f"Executing script: {script_path} {input_file} ")
					result = subprocess.run(['sh', script_path, input_file],
										stdout=out_f, stderr=subprocess.PIPE,
										text=True, env=env, timeout=timeout)
			if result.returncode != 0:
				print(f"[ERROR] {step_name} failed:\n{result.stderr}")
				return False
			ensure_utf8_lines(output_file)
			return True

		except subprocess.TimeoutExpired:
			print(f"[TIMEOUT] {step_name} timed out after {timeout}s (attempt {attempt + 1})")
			attempt += 1
		except Exception as e:
			print(f"[EXCEPTION] {step_name} on attempt {attempt + 1}: {e}")
			attempt += 1

def process_line(line_num, line_text, output_base, final_output_path):
	sent_dir = output_base / f"Sent_{line_num}"
	sent_dir.mkdir(parents=True, exist_ok=True)

	files = {
		"input": sent_dir / "line.txt",
		"tokenizer": sent_dir / "tokenizer.txt",
		"morph": sent_dir / "morph.txt",
		"postagger": sent_dir / "postag.txt",
		"chunker": sent_dir / "chunk.txt",
		"pruning": sent_dir / "prune.txt",
		"guessmorph": sent_dir / "gm.txt",
		"pickonemorph": sent_dir / "pm.txt",
		"convertor": sent_dir / "convertor.txt",
	}

	files["input"].write_text(line_text + '\n', encoding='utf-8')

	prev_output = files["input"]
	for step_name, script_path in PIPELINE:
		output_file = files[step_name]
		if step_name == "morph":
			time.sleep(1)  # Wait for 1 second before running morph
		if not run_script(step_name, script_path, str(prev_output), str(output_file),  working_dir=str(sent_dir)):
			with open(final_output_path, 'a', encoding='utf-8') as out_f:
				line = f'#Text={line_text}\n<Sentence id="{line_num}">\n'
				line += f'[ERROR] {step_name} failed for line {line_num}\n'
				out_f.write(line)
			return
		prev_output = output_file

	# Append final output
	if files["convertor"].exists():
		lines = files["convertor"].read_text(encoding='utf-8').splitlines()
		if lines:
			lines[0] = f'#Text={line_text}\n<Sentence id="{line_num}">'
		with open(final_output_path, 'a', encoding='utf-8') as out_f:
			out_f.write('\n'.join(lines) + '\n')
	else:
		print(f"#Text={line_text}\n[WARNING] No pickonemorph output for line {line_num}")

def main():
	if len(sys.argv) < 2:
		print("Usage: python script.py <input_file>")
		sys.exit(1)

	input_path = Path(sys.argv[1]).resolve()
	output_path = input_path.with_name(input_path.name + "_pickone_out.txt")
	output_base = Path(tel_modules_path + "/OUTPUT.tmp/")

	# Clean and prepare output directory
	if output_base.exists():
		shutil.rmtree(output_base)
	output_base.mkdir(parents=True)

	# Clear final output file
	output_path.write_text('', encoding='utf-8')

	with open(input_path, 'r', encoding='utf-8') as f:
		for line_num, line in enumerate(f, 1):
			line = line.strip()
			if not line:
				continue
			print(f"[{line_num}] Processing...")
			process_line(line_num, line, output_base, output_path)

if __name__ == "__main__":
	main()
