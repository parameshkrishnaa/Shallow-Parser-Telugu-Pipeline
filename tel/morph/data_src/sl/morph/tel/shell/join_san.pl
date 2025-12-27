# This program produces a file with uniq key that is required for dbm 
$_ = <STDIN>;
$_ =~ /([\d]+)\t(.*)$/;
#$_ =~ /"([^"]+)","(.*)"/;

$prev1 = $1;
$prev2 = $2;
while(<STDIN>)
{
$cur = $prev1..$prev2;
#$_ =~ /"([^"]+)","(.*)"/;
$_ =~ /([\d]+)\t(.*)$/;
$next1 = $1;
$next2 = $2;
while($prev1 eq $next1) 
{
$cur = $cur."#".$next2;
$_ = <STDIN>;
#$_ =~ /"([^"]+)","(.*)"/;
$_ =~ /([\d]+)\t(.*)$/;
$next1 = $1;
$next2 = $2;
}
print  $cur,"\n";
$cur="";
$prev1 = $next1;
$prev2 = $next2;
}
#print "\"",$next1,"\",\"",$next2,"\"\n";
print "$next1\t$next2\n";
