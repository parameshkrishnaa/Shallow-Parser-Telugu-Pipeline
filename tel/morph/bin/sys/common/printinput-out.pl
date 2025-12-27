
# Printing the file

while($line=<>)
{
	$line=~s/\@//g;
	print $line;
}
