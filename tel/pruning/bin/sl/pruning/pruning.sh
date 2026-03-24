#path=$2
perl $setu/pruning/bin/sl/pruning/printinput.pl $1 > pruneinput
perl $setu/pruning/bin/sl/pruning/pruning.pl --path=$setu/pruning/bin/sl/pruning --resource=$setu/pruning/bin/sl/pruning/mapping.dat --input=pruneinput
