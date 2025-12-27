#Entering corresponding to
#n parsarg adj_nEnaxi_na
#n parsarg adj_nEna_swrI
#n parsarg adj_nEnavAdu
#n parsarg adj_nEnavaru
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
$b[1]=$features{"n parsarg adj_nEnaxi_na "};
$b[2]=$features{"n parsarg adj_nEnaxi_swrI "};
$b[3]=$features{"n parsarg adj_nEnavAdu "};
$b[4]=$features{"n parsarg adj_nEnavAru "};

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
