
# Printing the file

while($line=<>)
{
	$line=~s/@//;
	$line=~s/\^//;
	print $line;
}
