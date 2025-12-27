#path=$2
perl $setu/pickonemorph/bin/sl/pickonemorph/tel/printinput.pl $1 > pickonemorphinput 
perl $setu/pickonemorph/bin/sl/pickonemorph/tel/pickonemorph.pl --path=$setu/pickonemorph/bin/sl/pickonemorph/tel --input=pickonemorphinput
