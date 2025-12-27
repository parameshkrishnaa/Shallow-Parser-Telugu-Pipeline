#C_FLAGS = cc -g -w -DGNU
#C_FLAGS = cc -g -Wall -DGNU
#C_FLAGS = cc -g -fno-common -DGNU
C_FLAGS = cc -g -DGNU
CC_FLAGS = ${C_FLAGS} -c
INCLUDE_PROG = ../../../../data_bin/sl/morph/tel/
INCLUDE_COM = ./common/analyser/
INCLUDE_C_DATA = ../../../../data_src/sl/morph/tel/c_data/
OBJECTF = adaM_suff.o adj_nEna.o adj_ni.o adj_pAti.o adj_xi.o adv.o adv_xi.o ani_suff.o aux_info.o Avy_srch_tel.o avy.o new_build_struct.o chk_cons_ending_for_wrds.o chk_uword_dict.o comp_verbs.o comp_verbs_heuristics.o const.o cp_suff_add_struct.o cp_to_struct.o cp_to_struct_chk_pdgm.o derived_const.o derived_adj_noun_heuristics.o derived_adv_noun_heuristics.o derived_noun_heuristics.o derived_noun1_heuristics.o derived_verb_heuristics.o dict_lookup.o e_suff.o feature_value.o gala.o get_derived_rt.o get_paradigm.o get_pdgm_info.o get_suff.o ina_suff.o isvowel.o lex_port.o sandhi_splitter.o clitic_stripper.o name_comp_offset.o num_gaMta_suff.o num_suff.o noun_Ena.o noun_lAMti.o noun_nom.o noun_pron.o main_telugu.o match_dict.o match_in_hypothetical_dict.o morph_telugu.o my_fatal.o order.o print_default_ans.o adj_split.o aux_clt_split.o tam_split.o verb_lcat_verify.o lcat_verify.o print_telugu.o print_hori.o read_file_tel.o snt_mark.o suff_build_struct.o suff_tab_lookup.o verify_root_telugu.o vwl_harmony.o wanaM_suff.o wunna_suff.o yoVkka.o fgetword.o my_blk_bsrch.o my_bsrch.o morph_logger.o suff_info_port.o
morph.out : ${OBJECTF}
	#gcc  `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0`  -o morph.out ${OBJECTF} -lgdbm 
	gcc  ${OBJECTF} `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0`  -o morph.out -lgdbm 
adaM_suff.o : ${INCLUDE_PROG}adaM_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}adaM_suff.c
adj_nEna.o : ${INCLUDE_PROG}adj_nEna.c
	${CC_FLAGS} ${INCLUDE_PROG}adj_nEna.c
adj_ni.o : ${INCLUDE_PROG}adj_ni.c
	${CC_FLAGS} ${INCLUDE_PROG}adj_ni.c
adj_pAti.o : ${INCLUDE_PROG}adj_pAti.c
	${CC_FLAGS} ${INCLUDE_PROG}adj_pAti.c
adj_xi.o : ${INCLUDE_PROG}adj_xi.c
	${CC_FLAGS} ${INCLUDE_PROG}adj_xi.c
adv_xi.o : ${INCLUDE_PROG}adv_xi.c
	${CC_FLAGS} ${INCLUDE_PROG}adv_xi.c
adv.o : ${INCLUDE_PROG}adv.c
	${CC_FLAGS} ${INCLUDE_PROG}adv.c
ani_suff.o : ${INCLUDE_PROG}ani_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}ani_suff.c
aux_info.o : ${INCLUDE_PROG}aux_info.c
	${CC_FLAGS} ${INCLUDE_PROG}aux_info.c
Avy_srch_tel.o : Avy_srch_tel.c
	${CC_FLAGS} Avy_srch_tel.c
avy.o : ${INCLUDE_PROG}avy.c
	${CC_FLAGS} ${INCLUDE_PROG}avy.c
new_build_struct.o : new_build_struct.c
	${CC_FLAGS} new_build_struct.c
chk_uword_dict.o : chk_uword_dict.c
	${CC_FLAGS} chk_uword_dict.c
chk_cons_ending_for_wrds.o : chk_cons_ending_for_wrds.c
	${CC_FLAGS} chk_cons_ending_for_wrds.c
comp_verbs.o : comp_verbs.c
	${CC_FLAGS} comp_verbs.c
comp_verbs_heuristics.o : comp_verbs_heuristics.c
	${CC_FLAGS} comp_verbs_heuristics.c
#delete_yv.o : delete_yv.c 	#not used in morph
#	${CC_FLAGS} delete_yv.c
const.o : ${INCLUDE_C_DATA}const.c
	${CC_FLAGS} ${INCLUDE_C_DATA}const.c
cp_suff_add_struct.o : cp_suff_add_struct.c
	${CC_FLAGS} cp_suff_add_struct.c
cp_to_struct.o : ${INCLUDE_COM}cp_to_struct.c
	${CC_FLAGS} ${INCLUDE_COM}cp_to_struct.c
cp_to_struct_chk_pdgm.o :${INCLUDE_COM}cp_to_struct_chk_pdgm.c
	${CC_FLAGS} ${INCLUDE_COM}cp_to_struct_chk_pdgm.c
derived_const.o : ${INCLUDE_C_DATA}derived_const.c
	${CC_FLAGS} ${INCLUDE_C_DATA}derived_const.c
suff_info_port.o : ${INCLUDE_C_DATA}suff_info_port.c
	${CC_FLAGS} ${INCLUDE_C_DATA}suff_info_port.c
derived_adj_noun_heuristics.o : derived_adj_noun_heuristics.c
	${CC_FLAGS} derived_adj_noun_heuristics.c
derived_adv_noun_heuristics.o : derived_adv_noun_heuristics.c
	${CC_FLAGS} derived_adv_noun_heuristics.c
derived_noun_heuristics.o : derived_noun_heuristics.c
	${CC_FLAGS} derived_noun_heuristics.c
derived_noun1_heuristics.o : derived_noun1_heuristics.c
	${CC_FLAGS} derived_noun1_heuristics.c
derived_verb_heuristics.o : derived_verb_heuristics.c
	${CC_FLAGS} derived_verb_heuristics.c
#clt.o : clt.c
#	${CC_FLAGS} clt.c
clitic_stripper.o : clitic_stripper.c
	${CC_FLAGS} clitic_stripper.c
#new_ss.o : new_ss.c  #renamed to sandhi_splitter
#	${CC_FLAGS} new_ss.c
sandhi_splitter.o : sandhi_splitter.c
	#gcc  `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -g -DGNU -c  sandhi_splitter.c
	${CC_FLAGS} sandhi_splitter.c
dict_lookup.o :${INCLUDE_COM}dict_lookup.c
	${CC_FLAGS} ${INCLUDE_COM}dict_lookup.c
e_suff.o : ${INCLUDE_PROG}e_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}e_suff.c
feature_value.o : ${INCLUDE_PROG}feature_value.c
	${CC_FLAGS} ${INCLUDE_PROG}feature_value.c
gala.o : ${INCLUDE_PROG}gala.c
	${CC_FLAGS} ${INCLUDE_PROG}gala.c
get_derived_rt.o : get_derived_rt.c
	${CC_FLAGS} get_derived_rt.c
get_paradigm.o : ${INCLUDE_COM}get_paradigm.c
	${CC_FLAGS} ${INCLUDE_COM}get_paradigm.c
get_pdgm_info.o :${INCLUDE_COM}get_pdgm_info.c
	${CC_FLAGS} ${INCLUDE_COM}get_pdgm_info.c
get_suff.o : ${INCLUDE_COM}get_suff.c
	${CC_FLAGS} ${INCLUDE_COM}get_suff.c
ina_suff.o : ${INCLUDE_PROG}ina_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}ina_suff.c
isvowel.o : isvowel.c
	${CC_FLAGS} isvowel.c
lex_port.o :${INCLUDE_COM}lex_port.c
	${CC_FLAGS} ${INCLUDE_COM}lex_port.c
name_comp_offset.o : name_comp_offset.c 
	${CC_FLAGS} name_comp_offset.c
num_suff.o : ${INCLUDE_PROG}num_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}num_suff.c
num_gaMta_suff.o : ${INCLUDE_PROG}num_gaMta_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}num_gaMta_suff.c
noun_Ena.o : ${INCLUDE_PROG}noun_Ena.c
	${CC_FLAGS} ${INCLUDE_PROG}noun_Ena.c
noun_lAMti.o : ${INCLUDE_PROG}noun_lAMti.c
	${CC_FLAGS} ${INCLUDE_PROG}noun_lAMti.c
noun_nom.o : ${INCLUDE_PROG}noun_nom.c
	${CC_FLAGS} ${INCLUDE_PROG}noun_nom.c
noun_pron.o : ${INCLUDE_PROG}noun_pron.c
	${CC_FLAGS} ${INCLUDE_PROG}noun_pron.c
main_telugu.o : main_telugu.c
	gcc  `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -g -DGNU -c  main_telugu.c 
my_fatal.o : ${INCLUDE_COM}my_fatal.c
	${CC_FLAGS} ${INCLUDE_COM}my_fatal.c
morph_telugu.o : morph_telugu.c
	${CC_FLAGS} morph_telugu.c
match_dict.o : ${INCLUDE_COM}match_dict.c
	${CC_FLAGS} ${INCLUDE_COM}match_dict.c
fgetword.o : ${INCLUDE_COM}fgetword.c
	${CC_FLAGS} ${INCLUDE_COM}fgetword.c
my_blk_bsrch.o : ${INCLUDE_COM}my_blk_bsrch.c
	${CC_FLAGS} ${INCLUDE_COM}my_blk_bsrch.c
morph_logger.o:${INCLUDE_COM}morph_logger.c
	${CC_FLAGS} ${INCLUDE_COM}morph_logger.c
my_bsrch.o:${INCLUDE_COM}my_bsrch.c
	${CC_FLAGS} ${INCLUDE_COM}my_bsrch.c
match_in_hypothetical_dict.o : match_in_hypothetical_dict.c
	${CC_FLAGS} match_in_hypothetical_dict.c
order.o : order.c
	${CC_FLAGS} order.c
print_hori.o : print_hori.c
	${CC_FLAGS} print_hori.c
aux_clt_split.o : aux_clt_split.c
	${CC_FLAGS} aux_clt_split.c
tam_split.o : tam_split.c
	${CC_FLAGS} tam_split.c
lcat_verify.o : lcat_verify.c
	${CC_FLAGS} lcat_verify.c
verb_lcat_verify.o : verb_lcat_verify.c
	${CC_FLAGS} verb_lcat_verify.c
adj_split.o : adj_split.c
	${CC_FLAGS} adj_split.c
print_telugu.o : print_telugu.c
	${CC_FLAGS} print_telugu.c
print_default_ans.o : ${INCLUDE_COM}print_default_ans.c
	${CC_FLAGS} ${INCLUDE_COM}print_default_ans.c
read_file_tel.o : read_file_tel.c
	${CC_FLAGS} read_file_tel.c
snt_mark.o : ${INCLUDE_COM}snt_mark.c
	${CC_FLAGS} ${INCLUDE_COM}snt_mark.c
suff_build_struct.o : ${INCLUDE_COM}suff_build_struct.c
	${CC_FLAGS} ${INCLUDE_COM}suff_build_struct.c
suff_tab_lookup.o : ${INCLUDE_COM}suff_tab_lookup.c
	${CC_FLAGS} ${INCLUDE_COM}suff_tab_lookup.c
vwl_harmony.o : vwl_harmony.c
	${CC_FLAGS} vwl_harmony.c
verify_root_telugu.o : verify_root_telugu.c
	${CC_FLAGS} verify_root_telugu.c
wunna_suff.o : ${INCLUDE_PROG}wunna_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}wunna_suff.c
wanaM_suff.o : ${INCLUDE_PROG}wanaM_suff.c
	${CC_FLAGS} ${INCLUDE_PROG}wanaM_suff.c
yoVkka.o : ${INCLUDE_PROG}yoVkka.c
	${CC_FLAGS} ${INCLUDE_PROG}yoVkka.c
clean:
	rm -f *.o
#	rm -f ../common/analyser/obj/*.*
#	rm -f ../../../../bin/sl/morph/tel/*

install:
	mv ./morph.out  ../../../../bin/sl/morph/tel/
