#Entering corresponding to
# v tam adaM person any
#from feature_value
open(FEATURES,"$ARGV[0]");
$i=1;
while($feature=<FEATURES>)
{
chomp($feature);
$features{$feature}=$i;
$i=$i+1;
}
close(FEATURES);
$n=$features{"v tam adaM person any "};
while($in=<STDIN>)
{
if($in =~ /,,$n\b/  )
{
$in=~ s/,/","/g;
$in=~s/^/"/;
$in=~  s/","$//;
$in=~ s/"([0-9]*)$/\1,/;
print $in;
}
}
