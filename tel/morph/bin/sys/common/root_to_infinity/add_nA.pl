#!/usr/local/bin/perl

use Getopt::Long;
GetOptions("help!"=>\$help,"path=s"=>\$vibh_home,"input=s"=>\$input,"output=s",\$output);
print "Unprocessed by Getopt::Long\n" if $ARGV[0];
foreach (@ARGV) {
	print "$_\n";
	exit(0);
}

if($help eq 1)
{
	print "Hindi Generator  - Generator Version 0.9\n(11th July 2008 )\n\n";
	print "usage : perl ./hindi_gen.pl --path=/home/hin_gen [-i inputfile|--input=\"input_file\"] [-o outputfile|--output=\"output_file\"] \n";
	print "\tIf the output file is not mentioned then the output will be printed to STDOUT\n";
	exit(0);
}

if($vibh_home eq "")
{
	print "Please Specify the Path as defined in --help\n";
	exit(0);

}

require "$vibh_home/API/shakti_tree_api.pl";
require "$vibh_home/API/feature_filter.pl";

sub hindi_gen
{
	&read($input);
	my @children = &get_children(0);

	foreach my $child (@children)
	{
		&change_fs($child);

		my @lc = &get_leaves_child($child);

		foreach my $c (@lc)
		{
			&change_fs($c);
		}
	}

	if($output eq "")
	{
		&print_tree();
	}
	else
	{
		&print_tree_file($output);
	}
}

sub change_fs()
{
	my $node = $_[0];

	        my $fs = &get_field($node, 4);
        	my $arr_fs = &read_FS($fs);
	        my @cat = &get_values("cat", $arr_fs);

        	if($cat[0] eq "v")
	        {
        	        my @root = &get_values("lex", $arr_fs);
			
			if($root[0] eq "hE" or $root[0] eq "WA")
			{
				return;
			}

                	$root[0] = $root[0]."nA";

	                &update_attr_val("lex", \@root, $arr_fs);
        	}

	        my $new_fs = &make_string($arr_fs);
        	&modify_field($node, 4, $new_fs);
}

&hindi_gen();


