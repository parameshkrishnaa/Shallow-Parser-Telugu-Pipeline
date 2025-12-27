sed '1,$s/^#define/int/
     1,$s/SIZEOF/sizeof/
     1,$s/\([0-9]\)/= \1/
     1,$s/$/;/
     1,$s/ADAM_SUFF/adaM_suff/
     1,$s/INA_SUFF/ina_suff/
     1,$s/E_SUFF/e_suff/
     1,$s/ANI_SUFF/ani_suff/
     1,$s/WUNNA_SUFF/wunna_suff/
     1,$s/AUX/aux/
     1,$s/IND/ind/
     1,$s/LEX/lex/
     1,$s/ADV_SUFF/adv_suff/
     1,$s/NUM_SUFF/num_suff/
     1,$s/NUM_GAMTA_SUFF/num_gaMta_suff/
     1,$s/GARU_SUFF/gAru_suff/
     1,$s/YOVKKA_SUFF/yoVkka_suff/
     1,$s/WANAM_SUFF/wanaM_suff/
     1,$s/noun_ENA/noun_Ena/' < ../c_data/derived_const.h > ../c_data/derived_const.c
