
# Printing the file

use Encode;
#use strict;

binmode(STDIN, ":utf8");
binmode(STDOUT, ":utf8");

while($line=<>)
{
	
	utf8::decode($line);
	$line=~s/\x{2018}/'/g; # <2018> ‘ is Replaced by single quote "'"
	$line=~s/\x{2019}/'/g; # <2019> ’ is Replaced by single quote "'"
	$line=~s/\x{200D}//g; # <200D> is Removed
	$line=~s/\x{200C}//g; # <200C> is Removed
	$line=~s/\x{200c}//g; # <200C> is Removed
	$line=~s/\x{202c}//g; # <200C> is Removed
	$line=~s/\x{200B}//g; # <200B> is Removed
	$line=~s/\x{feff}//g; # <feff> is Removed
	$line=~s/\x{0D}//g; #  is Removed
	$line=~s/\x{00A0}/ /g; 
	$line=~s/\x{008B}//g;
	$line=~s/\x{0965}/||/g;
#U+008B
#U+00A0
	print $line;
}
