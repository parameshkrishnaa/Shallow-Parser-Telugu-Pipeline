perl grep_adj_xi.pl feature_value < suff_info | sort -u > jnk
wc -l jnk > jnk1
sed -e 's/^[ ]*//
        s/[A-Za-z].*$//' jnk1 > jnk2
sed '1s/^/#define SIZEOF_adj_xi /' jnk2 > const1.h
cat const1.h >> ../c_data/derived_const.h
cat ../c_data/head_adj_xi jnk ../c_data/tail > ../../../../../data_bin/sl/morph/tel/adj_xi.c
