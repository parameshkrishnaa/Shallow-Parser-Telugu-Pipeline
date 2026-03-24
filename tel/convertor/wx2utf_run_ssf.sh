#path=$4
if [ $# -le 1 ]
then
        echo "Error - Arguments missing!!"
        echo -e "Syntax :\nsh $0 <format-type[text|SSF]> <language[hin|tel|..]> <input-file-name>";
        echo -e "e.g.:\nsh $0 ssf hin input-file-name";
exit
fi

perl -C $setu/convertor/convertor_indic.pl -f=$1 -l=$2 -s=wx -t=utf -i=$3
#perl convertor_indic.pl -f=text -l=tam -s=utf -t=wx -i=$1 -o=$1.wx
