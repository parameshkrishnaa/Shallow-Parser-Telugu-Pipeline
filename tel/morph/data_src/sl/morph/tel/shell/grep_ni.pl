#Entering corresponding to
#n parsarg adj_nixi_na
#n parsarg adj_nixi_swrI
#n parsarg adj_nivAdu
#n parsarg adj_nivAru 
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
$n=$features{"n parsarg adj_nixi_na "};
$m=$features{"n parsarg adj_nixi_swrI "};
$l=$features{"n parsarg adj_nivAdu "};
$p=$features{"n parsarg adj_nivAru "};
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
if($in=~/,,$m\b/)
{
$in=~s/,/","/g;
$in=~ s/^/"/;
$in=~  s/","$//;
$in=~ s/"([0-9]*)$/\1,/;
print $in;
}
if($in=~/,,$l\b/)
{
$in =~ s/,/","/g;
$in=~ s/^/"/;
$in =~  s/","$//;
$in =~ s/"([0-9]*)$/\1,/;
print $in;
}
if($in=~/,,$p\b/)
{
$in=~ s/,/","/g;
$in=~ s/^/"/;
$in =~ s/","$//;
$in =~  s/"([0-9]*)$/\1,/;
print $in;
}
}
