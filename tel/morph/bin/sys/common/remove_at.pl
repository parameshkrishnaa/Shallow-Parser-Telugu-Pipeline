#!/usr/bin/perl
sub remove_at {
	my $line;
	while ($line = <>)
	{
		$line=~s/@//g;
		print $line;
	}
}
&remove_at;
