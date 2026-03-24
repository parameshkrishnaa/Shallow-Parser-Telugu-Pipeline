#!/usr/bin/perl

use Getopt::Long;
GetOptions("help!"=>\$help,"path=s"=>\$vibh_home,"input=s"=>\$input,"output=s",\$output);
print "Unprocessed by Getopt::Long\n" if $ARGV[0];
foreach (@ARGV) {
	print "$_\n";
	exit(0);
}

if($help eq 1)
{
	print "Telugu Generator  - Generator Version 0.91\n(9th Sep 2008 )\n\n";
	print "usage : perl ./tel_gen.pl --path=/home/tel_gen [-i inputfile|--input=\"input_file\"] [-o outputfile|--output=\"output_file\"] \n";
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

open(SONDICT,"$vibh_home/data_src/song");
@SONS = <SONDICT>;
chomp(@SONS);

%song_hash = ();
foreach $song_1 (@SONS) {
	($root,$song) = split(/\,/,$song_1);
	$key = $root;
	$song_hash{$key} = $song;
}

open(AUXDICT,"$vibh_home/data_src/aux");
@AUXS = <AUXDICT>;
chomp(@AUXS);

%aux_hash = ();
foreach $aux_1 (@AUXS) {
	($root,$aux) = split(/\,/,$aux_1);
	$key = $root;
	$aux_hash{$key} = $aux;
}
open(PLDICT,"$vibh_home/data_src/placetribenouns.txt");
@PLS = <PLDICT>;
chomp(@PLS);

%pls_hash = ();
foreach $pls_1 (@PLS) {
	($root,$pls) = split(/\,/,$pls_1);
	$key = $root;
	$pls_hash{$key} = $pls;
}

open(TPL,"$vibh_home/data_src/temporalnouns.txt");
@TPLS = <TPL>;
chomp(@TPLS);

%tpls_hash = ();
foreach $tpls_1 (@TPLS) {
	($root,$tpls) = split(/\,/,$tpls_1);
	$key = $root;
	$tpls_hash{$key} = $tpls;
}

sub tel_gen
{
	&read($input);
	@nodes=&get_leaves();
	for($i=0;$i<=@nodes;$i++)
	{
		$cword = &get_field($nodes[$i],4);
		$cpos = &get_field($nodes[$i],3);
		$fs_array = &read_FS($cword);
		@lex = &get_values("lex", $fs_array);
		@cat = &get_values("cat", $fs_array);
		my @vib = &get_values("vib", $fs_array);
		my @case = &get_values("cas", $fs_array);
		my @num = &get_values("num", $fs_array);
		foreach $lex(@lex) {
			$cwordl = $lex;
		}
		foreach $cat(@cat) {
			$ccat = $cat;
		}
		$pls=$pls_hash{$cwordl};
		if(($pls eq "yes")&&($cpos eq "NN")&&($cword=~/vAru,vAru_obl'/)){
			$cword=~s/,,vAru,vAru_obl/o,vAru,vAru/g;
			&modify_field($nodes[$i],4,$cword);
		}
		if(($cpos!~/SYM/)&&($ccat eq "punc")){
			&modify_field($nodes[$i],3,"SYM");
		}
		if(($cpos eq "NN")&&($cword=~/'mahA,/)){
			&modify_field($nodes[$i],3,"JJ");
		}
		if($i!=0) {
			$pword1 = &get_field($nodes[$i-1],4);
			$ppos = &get_field($nodes[$i-1],3);
			$ptok = &get_field($nodes[$i-1],2);
			$fs_array1 = &read_FS($pword1);
			@lex1 = &get_values("lex", $fs_array1);
			@cat1 = &get_values("cat", $fs_array1);
			foreach $lex1(@lex1) {
				$pword1 = $lex1;
			}
			foreach $cat1(@cat1) {
				$pcat = $cat1;
			}
			my $aux,$song;
			$aux=$aux_hash{$cwordl};
			$song=$song_hash{$ptok};
			$tpls=$tpls_hash{$ptok};

			if(($aux ne "yes")&&($ppos eq "VM")&&($cpos eq "VAUX")&&($ccat eq "v")){
				&modify_field($nodes[$i],3,"VM");
			}
			if(($song eq "yes")&&($ppos eq "NN")&&($cpos eq "NN")&&($cword=~/pAdu,v,/)){
				&modify_field($nodes[$i],3,"VM");
			}
			if(($tpls eq "yes")&&($ppos eq "NN")&&($cpos eq "VM")&&($cword=~/'nAtu,v,/)){
				&modify_field($nodes[$i],3,"NN");
			}
		}
	}
}

&tel_gen();
if($output eq "")
{
	&print_tree();
}
else
{
	&print_tree_file($output);
}
