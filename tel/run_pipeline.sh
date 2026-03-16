#$1 is input file in .txt format
python3 run_pipeline.py $1
cd clauseboundary
python3 inference.py model ../in.txt out.txt
cd ..
python3 convert_telugu_pos_chunk_morph_cb_ssf2conll.py $1_pickone_out.txt clauseboundary/out.txt > out.conllu
cat out.conllu
