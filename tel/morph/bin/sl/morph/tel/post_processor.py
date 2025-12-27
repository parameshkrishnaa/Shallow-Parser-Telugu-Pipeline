import sys
import re
gender_map = {}
def process_analysis(analysis):
	fields = analysis.split(',')
	if len(fields) < 8:
		return analysis  # Not enough fields, return as is
	root = fields[0]
	root = re.sub(r'<fs af=\'','', root)
	# print(f"Processing root: {root}")
	gender = fields[2]
	if root in gender_map:
		gender = gender_map[root]
		fields[2] = gender
		# print(f"Root '{root}' gender {gender}")
	analysis = ','.join(fields)
	fields = analysis.split(',')

	#map 8th field ending with below values
	clitic_map = {
		'_A': 'Intr',	#Interrogative
		'_o': 'Dub',
		'_e': 'Emph',
		'_V': 'Incl',
		'_le': 'Conf'	#Confirmative
	}
	#map 7th field starting with below values
	case_marker_map = {
		'niMci': 'Abl',
		'ni': 'Acc',
		'ki': 'Dat',
		'wo': 'Ins',
		'lo': 'Loc',
		'yoVkka': 'Gen',
		'0': 'Nom',
		'kosaM': 'Ben',
	}
	#map 7th field starting with below values
	tense_map = {
		'wA': 'Fut',
		'A': 'Pst',
		'wunna': 'Prog',
		'a_lexu': 'Pst_Neg',
		'a': 'Fut_Neg',
	}

	clitic_value = None
	for suffix, label in clitic_map.items():
		eighth_field = fields[7]
		eighth_field = eighth_field.replace('\'>', '')  # Remove spaces for accurate matching
		# print(eighth_field)
		if re.search(r'' + suffix + '$', eighth_field):	#suffix in fields[7]:
			clitic_value = label
			break

	case_marker_value = None
	if( fields[1] == 'n'):
		for marker, label in case_marker_map.items():
			if re.search(r'^' + marker + r'_', fields[6]) or re.search(r'^' + marker + r'$', fields[6]):	#marker in fields[7]:
				case_marker_value = label
				break

	tense_value = None
	if( fields[1] == 'v'):
		for marker, label in tense_map.items():
			if re.search(r'^' + marker + r'_', fields[6]) or re.search(r'^' + marker + r'$', fields[6]):	#marker in fields[7]:
				tense_value = label
				break

	if clitic_value:
		# Add clitic as a key-value pair at the end
		# analysis = analysis + f",clitic='{clitic_value}'"
		analysis = re.sub(r'\'>', '\', clitic=\''+ clitic_value + '\'>', analysis)

	if case_marker_value:
		# Add case marker as a key-value pair at the end
		# analysis = analysis + f",clitic='{clitic_value}'"
		analysis = re.sub(r'\'>', '\', case_name=\''+ case_marker_value + '\'>', analysis)

	if tense_value:
		# Add tense as a key-value pair at the end
		# analysis = analysis + f",clitic='{clitic_value}'"
		if('Neg' in tense_value):
			tense_value = tense_value.replace('_Neg', '')
			analysis = re.sub(r'\'>', '\', Tense=\''+ tense_value + '\', Neg=\'Yes\'>', analysis)
		else:
			analysis = re.sub(r'\'>', '\', Tense=\''+ tense_value + '\'>', analysis)
	return analysis

#make unique ordered list from the input array
def make_unique_ordered(arr):
    seen = set()
    unique = []
    for item in arr:
        if item not in seen:
            seen.add(item)
            unique.append(item)
    return unique

def main():
	input_file = sys.argv[1] if len(sys.argv) > 1 else None
	gender_file = sys.argv[2]#"telugu_genders_wx.txt"
	if not input_file:
		print("Usage: python post_processor.py <input_file>")
		sys.exit(1)
	with open(gender_file, 'r', encoding='utf-8') as f:
		for  line in f:
			line = line.rstrip('\n')
			if not line.strip():
				continue
			cols = line.split('\t')
			if len(cols) < 2:
				continue
			gender_map[cols[0]] = cols[1]
			# print(cols[0], cols
	with open(input_file, 'r', encoding='utf-8') as f:
		for line in f:
			line = line.rstrip('\n')
			if not line.strip():
				print(line)
				continue
			cols = line.split('\t')
			if len(cols) < 4:
				print(line)
				continue
			analyses = cols[3].split('|')
			analyses = make_unique_ordered(analyses)	#return unique ordered analysis
			processed_analyses = [process_analysis(a) for a in analyses]
			cols[3] = '|'.join(processed_analyses)
			print('\t'.join(cols))

if __name__ == "__main__":
	main()
