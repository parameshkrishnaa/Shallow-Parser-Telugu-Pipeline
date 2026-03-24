use Getopt::Long;
GetOptions("help!"=>\$help,"path=s"=>\$vibh_home,"input=s"=>\$input,"output=s",\$output);
print "Unprocessed by Getopt::Long\n" if $ARGV[0];
foreach (@ARGV) {
	print "$_\n";
	exit(0);
}
if($help eq 1) {
	print "Telugu Generator  - Generator Version 0.91\n(9th Sep 2008 )\n\n";
	print "usage : perl ./pos_rep.pl --path=/home/pos_rep [-i inputfile|--input=\"input_file\"] [-o outputfile|--output=\"output_file\"] \n";
	print "\tIf the output file is not mentioned then the output will be printed to STDOUT\n";
	exit(0);
}
if($vibh_home eq "") {
	print "Please Specify the Path as defined in --help\n";
	exit(0);
}
require "$vibh_home/API/shakti_tree_api.pl";
require "$vibh_home/API/feature_filter.pl";
sub pos_rep {
	&read($input);
	@nodes=&get_leaves();
	for($i=0;$i<=@nodes;$i++) {
		my $cpos,$cword1,$fs_array,$ccat;
		$cword = &get_field($nodes[$i],4);
		$ctok = &get_field($nodes[$i],2);
		$cpos = &get_field($nodes[$i],3);
		$fs_array = &read_FS($cword);
		@lex = &get_values("lex", $fs_array);
		@cat = &get_values("cat", $fs_array);

		if(($cword=~/,I,I'.*\|.*,0,0_V'/)&&($cpos=~/NN/)){
			$cword=~s/<(.*),I'>\|//g;
			$cword=$cword."|<$1,I'>";
			&modify_field($nodes[$i],4,$cword);
		}

		if(($i ne $#nodes)&&($cword=~/,nu,nu'.*\|.*,ni,ni'/)&&($cpos=~/NN|PRP/)){
			$cword=~s/<(.*)>\|//g;
			$cword=$cword."|<$1>";
			&modify_field($nodes[$i],4,$cword);
		}

if(($cpos=~/V/)&&($cword=~/'.*,n,.*,d,0.*\|.*,n,.*,o,ti,/)&&($cword!~/,v,|,avy,/)){
			&modify_field($nodes[$i],3,"NN");
		}

		if(($cpos eq "RB")&&($cat[0] eq "avy")){
			my @newcat;
			$newcat[0]="avy";
			#&update_attr_val("cat",\@newcat,$fs_array,$nodes[$i]);
			#my $ret_string = &make_string($fs_array,$nodes[$i]);
			$cword=~s/,avy,/,adv,/g;
			&modify_field($nodes[$i],4,$cword);
		}
		if($cword!~/\|/){
			$cpos = &get_field($nodes[$i],3);
			foreach $cat(@cat) {
				$ccat = $cat;
			}
		}
		if($i!=0) {
			my $ppos,$pword1,$fs_array1,$pcat;
			$pword1 = &get_field($nodes[$i-1],4);
			$tok1 = &get_field($nodes[$i-1],2);
			$pos = &get_field($nodes[$i-1],3);
			$fs_array1 = &read_FS($pword1);
#To Convert NN to JJ when followed with NN and having case obl  - chris,krrd-210714

			if(($cpos=~/VM/)&&($cword!~/,v,/)&&($cword=~/,n,.*,n,/)){
				&modify_field($nodes[$i],3,"NN");
			}
			if(($pos=~/NN/)&&($cpos=~/NN/)&&(($pword1=~/.*,adj,.*,n,.*,o,ti,.*/)||($pword1=~/.*,n,.*,o,ti,/))&&($tok1=~/a$|pu$/)){
				if($pword1=~/.*,n,.*,0,0.*,n,.*,o,/){
					$pword1=~s/<(.*),0,0'>\|//g;
					$pword1=$pword1."|<$1,0,0'>";
					&modify_field($nodes[$i-1],4,$pword1);

				}
				&modify_field($nodes[$i-1],3,"JJ");
			}
	if(($pos eq "JJ")&&($cpos=~/NN|JJ/)&&($tok1=~/Ena$/)&&($pword1=~/,ina,ina'.*,Ena,/)){
				$pword1=~s/<(.*)>\|//g;
				$pword1=$pword1."|<$1>";
				&modify_field($nodes[$i-1],4,$pword1);
			}

			if(($pos=~/Q/)&&($cpos=~/NN/)&&($pword1=~/,n,.*,0_o'.*,num,.*/)){
				$pword1=~s/<(.*)>\|//g;
				$pword1=$pword1."|<$1>";
				&modify_field($nodes[$i-1],4,$pword1);
				$npos2="";
			}
			if(($pos=~/VM/)&&($pword1=~/,v,.*,A,A'.*,v,.*,inA,inA'/)){
				$pword1=~s/<(.*)>\|//g;
				$pword1=$pword1."|<$1>";
				&modify_field($nodes[$i-1],4,$pword1);
				$npos2="";
			}
			if(($pos=~/VM/)&&($pword1=~/,v,.*,koVn_wunna_.*,v,.*,koVn_ina_/)){
				$pword1=~s/<(.*)>\|//g;
				$pword1=$pword1."|<$1>";
				&modify_field($nodes[$i-1],4,$pword1);
				$npos2="";
			}
			# WQ blocked since : emonani is counter to this rule. - rajini, chris-190115
			#if(($pos=~/WQ|QF|QC/)&&($cpos=~/UT/)&&($ctok eq "ani")){
			if(($pos=~/QF|QC/)&&($cpos=~/UT/)&&($ctok eq "ani")){
				&delete_node($nodes[$i],$sent);
			}

			if($pword1!~/\|/){
				$ppos = &get_field($nodes[$i-1],3);
				@lex1 = &get_values("lex", $fs_array1);
				@cat1 = &get_values("cat", $fs_array1);
				foreach $lex1(@lex1) {
					$lex1=~s/_.*$//g;
					$pword = $lex1;
				}
				foreach $cat1(@cat1) {
					$pcat = $cat1;
				}

				if(($ppos!~/J/)&&($pcat eq "adj")){
					&modify_field($nodes[$i-1],3,"JJ");
				}
				elsif(($ppos!~/PRP|NN/)&&($pcat eq "pn")){
					&modify_field($nodes[$i-1],3,"PRP");
				}
				elsif(($ppos!~/NST/)&&($pcat eq "nst")){
					&modify_field($nodes[$i-1],3,"NST");
				}
				elsif(($ppos!~/N|P|J/)&&($pcat eq "n")){
					&modify_field($nodes[$i-1],3,"NN");
				}
				elsif(($ppos!~/PS/)&&($pcat eq "avy")&&($lex1[0] eq "na")){
					&modify_field($nodes[$i-1],3,"PSP");
				}
				elsif(($ppos!~/V/)&&($pcat eq "v")){
					&modify_field($nodes[$i-1],3,"VM");
#print "ima here with $cword\n";
					if(($cword=~/,v,|,avy,/)&&($ctok!~/^vAdu$|^nAku$/)){
					&modify_field($nodes[$i],3,"VAUX");
					}
				}
				elsif(($ppos!~/SYM/)&&($pcat eq "punc")){
					&modify_field($nodes[$i],3,"SYM");
				}
				if(($ppos=~/NN|PRP/)&&($cpos eq "PRP")&&($pword1=~/,ti,/)&&($cword=~/,nst,/)){
					&modify_field($nodes[$i],3,"NST");
				}
				if(($ppos=~/VM/)&&($cpos eq "PRP")&&($pword1=~/,v,(.*),ina,/)&&($cword=~/\'aMxuna,/)){
					&modify_field($nodes[$i],3,"VAUX");
				}
				if(($ppos=~/VM/)&&($cpos eq "VM")&&($pword1=~/,v,(.*),Ali_ani,/)&&($cword=~/\'uMdu,/)){
					&modify_field($nodes[$i],3,"VAUX");
				}
				#if(($ppos=~/VM/)&&($cpos eq "VM")&&($pword1=~/,v,(.*),ani,/)&&($cword=~/\'po,/)){
				#	&modify_field($nodes[$i],3,"VAUX");
				#}


			}

		}
	}
}
&pos_rep();
if($output eq "") {
	&print_tree();
}
else {
	&print_tree_file($output);
}
