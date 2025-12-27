export LC_ALL=C
cp ../c_data/const1.h  ../c_data/derived_const.h
./grep_Ena.sh
./grep_adaM.sh
./grep_wanaM.sh
./grep_adv.sh
./grep_ani.sh
./grep_aux.sh
./grep_e.sh
./grep_gala.sh
./grep_ina.sh
./grep_lAMti.sh
./grep_nEna.sh
./grep_ni.sh
./grep_nom.sh
./grep_num.sh
./grep_num_gaMta.sh
./grep_pAti.sh
./grep_pron.sh
./grep_yoVkka.sh
./grep_wunna.sh
./grep_adj_xi.sh
./grep_adv_xi.sh
#./grep_xi.sh
./prp_derived_const.sh
cp ../c_data/derived_const.h ../../../../../data_bin/sl/morph/tel/
rm jnk*
