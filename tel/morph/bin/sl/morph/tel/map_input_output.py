import sys
import re

if len(sys.argv) < 3:
	print("Usage: python map_input_output.py <input_file1> <input_file2>")
	sys.exit(1)

input_file1 = sys.argv[1]
input_file2 = sys.argv[2]

# Read first file line by line, save in a dictionary with index as key
orig_input_dict = {}
with open(input_file1, 'r', encoding='utf-8') as f1:
	for idx, line in enumerate(f1):
		parts = line.split('\t')
		orig_input_dict[idx] = parts[1].rstrip('\n')

# # Example: print the dictionary
# for idx, line in lines_dict.items():
# 	print(f"{idx}: {line}")

out_array = []
word_split_flag = 0
with open(input_file2, 'r', encoding='utf-8') as f2:
	lines = f2.readlines()
	actual_index = 0
	for i in range(len(lines)):
		line = lines[i]
		# Split the line by tab
		parts = line.rstrip('\n').split('\t')
		if len(parts) < 3:
			continue

		index = int(parts[0])  # Convert the first part to an integer index

		#ignore sandhi output lines
		try:
			next_index = int(lines[i+1].rstrip('\n').split('\t')[0])  # Convert the second part to an integer index
		except:
			next_index = -1
		try:
			prev_index = int(lines[i-1].rstrip('\n').split('\t')[0])   # Convert the second part to an integer index
		except:
			prev_index = -1

		# if first column is same for both next and current line then its sandhi split
		if (index == next_index) :
			out_array.append(line.rstrip('\n'))
			actual_index = actual_index + 1
			
			continue
		
		# if first column is same for both next and previous line then its sandhi split
		if (index == prev_index) :
			out_array.append(line.rstrip('\n'))
			continue

		#if the unk column has number appeneded in the end its word split for clue
		if (re.search(r'unk\d', parts[2])) :
			line = re.sub(r'unk\d', 'unk', line)  # Replace 'unk\d' with 'unk'
			out_array.append(line.rstrip('\n'))
			if word_split_flag == 0:
				word_split_flag = 1
				actual_index = actual_index + 1
			else:
				word_split_flag = 0
			continue

		out_str = ''
		try:
			actual_word = orig_input_dict[actual_index]
		except:
			actual_word = parts[1]

		actual_index = actual_index + 1

		out_str = f"{index}\t{actual_word}\t{parts[2]}\t{parts[3]}"
		out_array.append(out_str)

print("\n".join(out_array))  # Print the output string without adding an extra newline

