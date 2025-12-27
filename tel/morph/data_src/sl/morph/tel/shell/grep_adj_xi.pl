#entries corresponding to
#n parsarg adj_xi_na
#n oarsarg adj_xi_swrI
#n parsarg adj_vAdu
# n parsarg adj_vAru
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
$b[1]=$features{"n parsarg adj_xi_na "};
$b[2]=$features{"n parsarg adj_xi_swrI "};
$b[3]=$features{"n parsarg adj_vAdu "};
$b[4]=$features{"n parsarg adj_vAru "};

for ($k = 1;$k<5;$k++)
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
