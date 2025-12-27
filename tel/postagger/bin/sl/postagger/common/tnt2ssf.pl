#! /usr/bin/perl
sub tnt2ssf
{
	my $line = "";
	my $startFlag = 1;
	my $wno = 1;
	my $prevCTag = "";
	my $error = "";
	my $lno = 0;
	my $sno = 1;


	#scan each line from standard input
	print "<Sentence id=\"$sno\">\n";
	while($line = <>)
	{
		if($line =~ /^\s*$/)
		{	
			
			print "</Sentence>\n";
			$sno++;
			print "<Sentence id=\"$sno\">\n";

			$wno=1;
			next;
		}
		if($line eq "")
		{
			print "</Sentence>\n";
			$sno++;
			print "<Sentence id=\"$sno\">\n";
			$wno=1;
			next;
		}

		chomp($line);

		my @cols = split(/[ ]+/,$line);
		$cols[2]=~s/___/ /g;
		print $wno,"\t",$cols[0],"\t",$cols[1],"\t",$cols[2],"\n";
		$wno ++;
	}
	print "</Sentence>\n";
}
&tnt2ssf;
