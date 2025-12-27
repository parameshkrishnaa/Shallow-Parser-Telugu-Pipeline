#Entering corresponding to
#n number eka parsarg gAdu
#n number eka parsarg gawweV 
#n number eka parsarg vAdu 
#n number eka parsarg Ayana 
#n number eka parsarg vArbahuu
#n number eka parsarg xi
#n number eka parsarg vi
#n number eka parsarg gAru
#from feature_value
open(FEATURES,"$ARGV[0]");
$i=1;
while($feature=<FEATURES>)
{
chomp($feature);
if($features{$feature} != NULL)
{
$features{$feature}=$features{$feature} ."#". $i;
$i++;
}
else
{
$features{$feature}=$i;
$i=$i+1;
}
}
close(FEATURES);
$b[1]=$features{"n number eka parsarg gAdu "};
$b[2]=$features{"n number eka parsarg gawweV "};
$b[3]=$features{"n number eka parsarg vAdu "};
$b[4]=$features{"n number eka parsarg Ayana "};
$b[5]=$features{"n number eka parsarg vAru "};
$b[6]=$features{"n number eka parsarg xi "};
$b[7]=$features{"n number eka parsarg vi "};
$b[8]=$features{"n number eka parsarg gAru "};
$b[9]=$features{"n number bahu parsarg gAdu "};
$b[10]=$features{"n number bahu parsarg gawweV "};
$b[11]=$features{"n number bahu parsarg vAdu "};
$b[12]=$features{"n number bahu parsarg Ayana "};
$b[13]=$features{"n number bahu parsarg vAru "};
$b[14]=$features{"n number bahu parsarg xi "};
$b[15]=$features{"n number bahu parsarg vi "};
$b[16]=$features{"n number bahu parsarg gAru "};
$b[17]=$features{"P number eka parsarg gAdu "};
$b[18]=$features{"P number eka parsarg gawweV "};
$b[19]=$features{"P number eka parsarg vAdu "};
$b[20]=$features{"P number eka parsarg Ayana "};
$b[21]=$features{"P number eka parsarg vAru "};
$b[22]=$features{"P number eka parsarg xi "};
$b[23]=$features{"P number eka parsarg vi "};
$b[24]=$features{"P number eka parsarg gAru "};
$b[25]=$features{"P number bahu parsarg gAdu "};
$b[26]=$features{"P number bahu parsarg gawweV "};
$b[27]=$features{"P number bahu parsarg vAdu "};
$b[28]=$features{"P number bahu parsarg Ayana "};
$b[29]=$features{"P number bahu parsarg vAru "};
$b[30]=$features{"P number bahu parsarg xi "};
$b[31]=$features{"P number bahu parsarg vi "};
$b[32]=$features{"P number bahu parsarg gAru "};

for ($k = 1;$k<33;$k++)
{
@tmp = split(/#/,$b[$k]);
foreach $tmp (@tmp){
$PRESENT{$tmp} = 1;
#print $tmp,"\n";
}
}

while($in = <STDIN>){
$in =~s/,/","/g;
$in =~s/^/"/;
$in=~s/","$//;
$in =~  s/"([0-9]*)$/\1,/;
$num = $1;
if($PRESENT{$num}) { print $in;}
}
