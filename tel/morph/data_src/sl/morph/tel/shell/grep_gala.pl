# entries corresponding to
#v tama_gala person an
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
$b[1]=$features{"v tam a_gala person any "};

while($in = <STDIN>){

if ($in =~ /,,$b[1]\b/)
{
$in =~ s/,/","/g;
$in =~ s/^/"/;
$in =~ s/","$//;
$in =~ s/"([0-9]*)$/\1,/;
$in =~ s/^"alag/"/;
print $in;
}
}
