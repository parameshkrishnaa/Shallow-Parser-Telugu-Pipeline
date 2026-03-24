perl $setu/bin/sys/common/printinput.pl $1 > $1.aa
perl $setu/bin/sys/common/deletesentencetag.pl < $1.aa > $1.ab
perl $setu/bin/sl/postagger/common/ssf2tnt.pl <$1.ab > $1.ac
perl $setu/bin/sl/postagger/common/extra_features.pl < $1.ac > $1.ad
crf_test -m $setu/data_bin/sl/postagger/tel/200k_telugu_pos_model $1.ad > $1.ae
perl $setu/bin/sl/postagger/common/split.pl < $1.ae > $1.af
perl $setu/bin/sl/postagger/common/tnt2ssf.pl < $1.af > $1.ag

## wrapper to correct the wrong POS; parameshkrishna_CALTS UoH 060612
perl $setu/bin/sl/postagger/pos-repair.pl < $1.ag
# Comment the previous line and uncomment the following three lines if the system is tel-hin-ilmt
#perl $setu/bin/sl/postagger/pos_repair/pos_repair.pl --path=$setu/bin/sl/postagger/pos_repair --i postaggerout > postaggerout1
#perl $setu/bin/sl/postagger/pos-repair.pl postaggerout1 > postaggerout2
#perl $setu/bin/sl/postagger/pos_repair/pos-repair_2.pl --path=$setu/bin/sl/postagger/pos_repair --i=postaggerout2
rm $1.a*
