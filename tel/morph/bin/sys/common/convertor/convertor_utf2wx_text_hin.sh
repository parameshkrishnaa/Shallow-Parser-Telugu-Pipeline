perl $setu/bin/sys/common/printinput.pl $1 > convertorinput
perl $setu/bin/sys/common/convertor/convertor.pl --path=$setu/bin/sys/common/convertor --stype=text --slang=hin -s utf -t wx < convertorinput

