perl grep_adv.pl feature_value < suff_info | sort -u > jnk
wc -l jnk > jnk1
sed -e 's/^[ ]*//
        s/[A-Za-z].*$//' jnk1 > jnk2
sed '1s/^/#define SIZEOF_ADV_SUFF /' jnk2 > const1.h
cat const1.h >> ../c_data/derived_const.h
cat ../c_data/head_adv jnk ../c_data/tail > ../../../../../data_bin/sl/morph/tel/adv.c
