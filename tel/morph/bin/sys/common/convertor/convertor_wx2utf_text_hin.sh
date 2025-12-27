perl $setu/bin/sys/common/printinput.pl $1 > convertorinput
perl $setu/bin/sys/common/convertor/convertor.pl --path=$setu/bin/sys/common/convertor --stype=text --tlang=hin -s wx -t utf < convertorinput

