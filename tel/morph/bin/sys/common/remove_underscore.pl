#!/usr/bin/perl
sub remove_at {
	my $line;
	while ($line = <>)
	{
		$line=~s/_/ /g;
		print $line;
	}
}
&remove_at;
