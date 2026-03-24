use GDBM_File;	#added instead of require "use.pl";

if($ARGV[0] eq "GDBM"){
#require "use.pl";
	#tie(%LEX,GDBM_File,$ARGV[1],0666,0);
tie(%LEX,GDBM_File,$ARGV[1], &GDBM_WRCREAT, 0640) or die "Cannot open:$!\n";
}
else{ dbmopen(%LEX,$ARGV[1],0666); }

while(<STDIN>)
{
chomp($_);
$_=~s/^##.*##$//g;
#print "$_\n";
#$_ =~ /"([^"]+)","(.*)"$/;
$_ =~ /([\d]+)\t(.*)$/;
#print "|$1|$2|\n";
#print "|$1|$_|\n";
$LEX{$1} = $_;
}

if($ARGV[0] eq "GDBM"){ untie(%LEX); }
else{ dbmclose(%LEX); }
