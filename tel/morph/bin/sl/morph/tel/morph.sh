#!/bin/bash
#export LANG=en_US.UTF-8
#export LC_ALL=en_US.UTF-8
#setu/morph=$2
perl $setu/morph/bin/sl/morph/tel/printinput.pl $1 > morphinput
perl $setu/morph/bin/sl/morph/tel/deletesentencetag.pl < morphinput > morph-temp
perl $setu/morph/bin/sl/morph/tel/remove_zwj.pl < morph-temp > morph-temp1

## NEW CONVERTORI 1.4.5 030311
# 1.4.7  150311
# 1.4.8  020111
perl $setu/morph/../convertor/convertor_indic.pl -f=ssf -l=tel -s=utf -t=wx -i=morph-temp1 -o=morph-splitin

perl $setu/morph/bin/sl/morph/tel/word-split.pl < morph-splitin > morph-splitout
cut -f1-3 morph-splitout > morph-actualinput
$setu/morph/bin/sl/morph/tel/morph.out --pdgmfilepath $setu/morph/data_bin/sl/morph/tel/ --uwordpath $setu/morph/data_bin/sl/morph/tel/dict_tel --dictfilepath $setu/morph/data_bin/sl/morph/tel -ULDWH --in=morph-actualinput --out=morphoutput
perl $setu/morph/bin/sl/morph/tel/cat-change.pl < morphoutput > morphoutput2
python3 $setu/morph/bin/sl/morph/tel/map_input_output.py morph-splitin morphoutput2 > morphoutput3
python3 $setu/morph/bin/sl/morph/tel/post_processor.py morphoutput3 $setu/morph/bin/sl/morph/tel/telugu_genders_wx.txt > morphoutput4
perl $setu/morph/bin/sl/morph/tel/printinput.pl morphoutput4
