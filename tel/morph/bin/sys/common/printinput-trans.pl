
# Printing the file

while($line=<>)
{
	$line=~s/\^//;
	print $line;
}
