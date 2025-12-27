#Entering corresponding to
#n paarsarg adj_wanaM 
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
$n=$features{"n parsarg adj_wanaM "};
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
