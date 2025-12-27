#entries corresponding to
#n number eka parsarg0
#n number bahu parsarg 0
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
$b[1]=$features{"n number eka parsarg 0 "};
$b[2]=$features{"n number bahu parsarg 0 "};

for ($k = 1;$k<3;$k++){                               
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
