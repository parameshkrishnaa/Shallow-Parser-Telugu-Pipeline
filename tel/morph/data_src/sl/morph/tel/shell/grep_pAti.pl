#entries corresponding to 
#n parsarg adj_pAti.pl from feature_value
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
$b1=$features{"n parsarg adj_pAti "};

while($in = <STDIN>){
if ($in=~ /,,$b1\b/)
{
$in =~s/,/","/g;
$in =~s/^/"/;
$in=~s/","$//;
$in =~  s/"([0-9]*)$/\1,/;
 print $in;
}
}
