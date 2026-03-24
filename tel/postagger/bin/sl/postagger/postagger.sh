#ath=$2
perl $setu/postagger/bin/sl/postagger/printinput.pl $1 > postaggerinput
perl $setu/postagger/bin/sl/postagger/deletesentencetag.pl < postaggerinput > postaggerinput1
perl $setu/postagger/bin/sl/postagger/common/ssf2tnt.pl < postaggerinput1 > input.tnt
perl $setu/postagger/bin/sl/postagger/common/extra_features.pl < input.tnt > extra_input.tmp
crf_test -m $setu/postagger/bin/sl/postagger/200k_telugu_pos_model extra_input.tmp > crfout.tmp
perl $setu/postagger/bin/sl/postagger/common/split.pl < crfout.tmp > postagger_out.tnt
perl $setu/postagger/bin/sl/postagger/common/tnt2ssf.pl < postagger_out.tnt > postaggerout

## wrapper to correct the wrong POS; parameshkrishna_CALTS UoH 060612
perl $setu/postagger/bin/sl/postagger/pos-repair.pl < postaggerout
# Comment the previous line and uncomment the following three lines if the system is tel-hin-ilmt
#perl $setu/postagger/bin/sl/postagger/pos_repair/pos_repair.pl --path=$setu/postagger/bin/sl/postagger/pos_repair --i postaggerout > postaggerout1
#perl $setu/postagger/bin/sl/postagger/pos-repair.pl postaggerout1 > postaggerout2
#perl $setu/postagger/bin/sl/postagger/pos_repair/pos-repair_2.pl --path=$setu/postagger/bin/sl/postagger/pos_repair --i=postaggerout2

