#Lines corresponding to the feature
#n parsarg num_1 (gaMta)
#n parsarg num_2 (gaMta)
#n parsarg num_10-num_12 (vAdu,axi,vAru)
#n parsarg num_18-num_20 (nnara,MbAvu,muppAvu)
# to be extracted from feature_value
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
$b[1]=$features{"n parsarg num_1 "};
$b[2]=$features{"n parsarg num_2 "};
$b[3]=$features{"n parsarg num_10 "};
$b[4]=$features{"n parsarg num_11 "};
$b[5]=$features{"n parsarg num_12 "};
$b[6]=$features{"n parsarg num_18 "};
$b[7]=$features{"n parsarg num_19 "};
$b[8]=$features{"n parsarg num_20 "};

for ($k = 1;$k<9;$k++)
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
