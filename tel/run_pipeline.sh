#$1 is input file in .txt format
python3 run_pipeline.py $1
python3 convert_telugu_pos_chunk_morph_ssf2conll.py $1_pickone_out.txt
cat out.conllu
