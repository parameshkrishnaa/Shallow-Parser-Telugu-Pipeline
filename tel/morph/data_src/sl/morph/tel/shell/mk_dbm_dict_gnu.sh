export LC_ALL=C
#rm -f ../../../../../data_bin/sl/morph/tel/dict_tel
###cat ../dict/dict.1 ../dict/dict.2 ../dict/dict.3 ../dict/dict.4 ../dict/dict.5 ../dict/dict.6 ../dict/dict.7 ../dict/dict.8 ../dict/dict.9 > j                   
cat ../dict/dict.1 ../dict/dict.2 ../dict/dict.3 ../dict/dict.4 ../dict/dict.5 ../dict/dict.6 ../dict/dict.7 ../dict/dict.8 ../dict/dict.9 ../dict/dict.10 ../dict/dict.fw > j                   
#cat ../dict/dict.1 > j                   
sort j>jj
perl join_dict_old.pl < jj > dict.dbm.c
#rm  j jj
perl create_dbm_dict.pl GDBM dict_tel < dict.dbm.c
#rm -f dict.dbm.c
chmod 644 dict_tel
mv dict_tel ../../../../../data_bin/sl/morph/tel/
