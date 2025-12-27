if($ARGV[0] eq "GDBM"){
require "./use.pl";
#tie(%LEX,GDBM_File,$ARGV[1],0666,0);
tie(%LEX,GDBM_File,$ARGV[1], &GDBM_WRCREAT, 0640) or die "Cannot open:$!\n";
}
else{ dbmopen(%LEX,$ARGV[1],0666); }
while(<STDIN>)
{
$_ =~ /"([^"]+)","([^"]+)",$/;
$LEX{$1} = $2;
}
if($ARGV[0] eq "GDBM"){ untie(%LEX); }
else{ dbmclose(%LEX); }
