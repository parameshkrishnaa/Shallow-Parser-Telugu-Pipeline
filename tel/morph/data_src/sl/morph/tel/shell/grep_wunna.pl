#Entering corresponding to
#n v tam person wunnaperson any
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
$b[1]=$features{"v tam wunna person any "};


while($in = <STDIN>)
{
if ($in =~ /,,$b[1]\b/)
{
$in =~ s/,/","/g;
$in =~ s/^/"/;
$in =~ s/","$//;
$in =~ s/"([0-9]*)$/\1,/;
$in =~ s/^"/"ix/;
print $in;
$in =~ s/^"ix/"udAv/;
print $in;
$in =~ s/^"udAv/"urAv/;
print $in;
}
}
