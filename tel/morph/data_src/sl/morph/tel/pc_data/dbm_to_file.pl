#!/usr/bin/perl 


#use strict;
use autodie;
use warnings;
use GDBM_File;

my (%hash, $key, $val);
my $filename = $ARGV[0];
tie %hash, 'GDBM_File', $filename, &GDBM_READER, 0640; 

while (($key, $val) = each %hash) {
	print "|$key|$val|\n";
}

untie %hash;
