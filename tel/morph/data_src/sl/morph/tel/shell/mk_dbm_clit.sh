export LC_ALL=C
#rm -f ../../../../../data_bin/sl/morph/tel/dict_tel
###cat ../dict/dict.1 ../dict/dict.2 ../dict/dict.3 ../dict/dict.4 ../dict/dict.5 ../dict/dict.6 ../dict/dict.7 ../dict/dict.8 ../dict/dict.9 > j                   

#sort the suff_info
#sort clitics-rls >clr
#rm ../../../../../src/sl/morph/tel/clitic_tel
FILE=../../../../../data_bin/sl/morph/tel/clitic_tel
#if [-f $FILE]
#then
#rm ../../../../../data_bin/sl/morph/tel/clitic_tel
#echo "$FILE removed".
#fi
cat ../pc_data/clitics-rls > clr
#create unique keys for suff_info
#perl join_suff.pl < as1 > js
#rm  as1
#create suff_gdbm file for above created file
perl create_dbm_clitic.pl GDBM clitic_tel< clr
rm clr
chmod 644 clitic_tel
#mv clitic_tel ../../../../../src/sl/morph/tel/
mv clitic_tel ../../../../../data_bin/sl/morph/tel/
