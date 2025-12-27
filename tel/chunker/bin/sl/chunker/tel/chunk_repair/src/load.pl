#!/usr/bin/persl
#version 2
#3 functions fill_fs, parse and load
%var_list=();
$file;
sub fill_fs
{
        my $word_var=@_[0];
        my $word=@_[1];
        my $pos=@_[2];
        my $fs=@_[3];
	my $variable=@_[4];
	$flag_var=1;
	if($variable eq '')
	{
		$flag_var=0;
	}	
	$variable=~s/"//g;
	@tem=split(';',$variable);
	foreach my $item(@tem)
	{
		if($item=~/(.*)=(.*)/)
		{
			$var_list{$1}=$2;
		}
	}
        my %fs_hash=();
        my $root,$lcat,$num,$gend,$pers,$tam,$case,$cm;
	my $spec,$emph,$dubi,$interj,$conj,$hon,$agr_gen,$agr_num,$agr_per,$suff;
	if($word_var ne "")
        {
		$fs_hash{"word_var"}=$word_var;
        }
        if($word ne "")
        {
		$temp=$word;
		if ($var_list{$word}){
			$temp=$word."=>".$var_list{$word};}
                $word=$temp;
                $fs_hash{"word"}=$word;
        }
        if($pos ne "")
        {
		$temp=$pos;
		if (exists $var_list{$pos}){
			$temp=$pos."=>".$var_list{$pos};}
                $pos=$temp;
                $fs_hash{"pos"}=$pos;
        }
	if($fs eq "")
	{
        	return(\%fs_hash);
	}
	$fs=~s/<//g;
	$fs=~s/>//g;
	my @values=split(',',$fs);
	foreach my $val(@values)
	{
		$flag=0;
	        if($val=~/root=\s*"\s*([^\s\"]+)/)
	        {
	                $root=$1;
			if($1 eq "")
			{$root="NULL";}	
	                $fs_hash{"root"}=$root;
			$flag=1;
		}
	        if($val=~/lcat=\s*"\s*([^\s\"]+)/)
	        {
	                $lcat=$1;
			if($1 eq "")
			{$lcat="NULL";}	
	                $fs_hash{"lcat"}=$lcat;
			$flag=1;
		}
	        if($val=~/gend=\s*"\s*([^\s\"]*)/)
	        {
	                $gend=$1;
	                if($1 eq "")
			{$gend="NULL";}
			$fs_hash{"gend"}=$gend;
			$flag=1;
	        }
	        if($val=~/num=\s*"\s*([^\s\"]*)/)
	        {
	                $num=$1;
	                if($1 eq "")
			{$num="NULL";}
			$fs_hash{"num"}=$num;
			$flag=1;
	        }
	        if($val=~/pers=\s*"\s*([^\s\"]*)/)
	        {
		        $pers=$1;
	                if($1 eq "")
			{$pers="NULL";}
			$fs_hash{"pers"}=$pers;
			$flag=1;
	        }
	        if($val=~/tam=\s*"\s*([^\s\"]*)/)
	        {
	                $tam=$1;
	                if($1 eq "")
			{$tam="NULL";}
			$fs_hash{"tam"}=$tam;
			$flag=1;
		}
		if($val=~/suff=\s*"\s*([^\s\"]*)/)
		{
			$tam=$1;
			if($1 eq "")
			{$tam="NULL";}
			$fs_hash{"suff"}=$tam;
			$flag=1;
		}
		if($val=~/cm=\s*"\s*([^\s\"]*)/)
	        {
	                $cm=$1;
	                if($1 eq "")
			{$cm="NULL";}
			$fs_hash{"cm"}=$cm;
			$flag=1;
	        }
		if($val=~/case=\s*"\s*([^\s\"]*)/)
	        {
	                $case=$1;
	                if($1 eq "")
			{$case="NULL";}
			$fs_hash{"case"}=$case;
			$flag=1;
	        }
		elsif($flag==0)
		{
#			print "batao ",$val,"\n";
			$val=~s/"//g;
			@va=split('=',$val);
			$rt=$va[0];	
			$temp=$va[1];
			if (exists $var_list{$va[1]}){
				$temp=$va[1]."=>".$var_list{$va[1]};}
               		$va[1]=$temp;
#			print "tete ",$va[0],$va[1],"\n";
			$fs_hash{$va[0]}=$va[1];
			$flag=1;
		}
	}
        
        return(\%fs_hash);

}
sub check_rule
{
	my $ref_array=@_[0];
	my $rule_no=@_[1];
	my @array=@$ref_array;
	my $i,$j;
	my $num=@array;
	
	while ($i<$num)
	{
		if($array[$i] =~/([A-Z]+)\~?([0-9]+)?(\<[^\>]*\>)?(\(\()?(.*)?(\)\))?/)
		{
			my $chunk1=$1;
			my $token_id1=$2;
			my $chunk_id1=$chunk1."~".$token_id1;
			$j=$i+1;
			while ($j<$num)
			{
				if($array[$j]=~/([A-Z]+)\~?([0-9]+)?(\<[^\>]*\>)?(\(\()?(.*)?(\)\))?/)
				{
					my $chunk2=$1;
					my $token_id2=$2;
					my $chunk_id2=$chunk2."~".$token_id2;

					if($chunk_id1 eq $chunk_id2)
					{
						print "ERROR: Check the LOG FILE\n";
						$log->info("Check the Rule @ $rule_no\n");	
						exit(0);
					}
				}
				$j++;
			}
		}
		$i++;
	}
}

sub parse
{
        my $rule_no=@_[0];
        my $lhs=@_[1];
        my $rhs=@_[2];
        my $ref_Tree=@_[3];
	my $variable=@_[4];

        @_RULE_TREE_=@$ref_Tree;

	my @_LHS_=();
	my @_RHS_=();

#	$log->info("Parsing and Loading the Rule----$rule_no\n");
#	$log->info("Lhs Parsing and Loading\n");
	$log->info("LHS::@_[1]::\n");
	my @array=split(/\s+/,$lhs);
	$log->info("Number of Chunks:@array\n");
	my $i=0;
	my $x1,$y1;

	#Checking LHS
	&check_rule(\@array,$rule_no);
	
	while ($i<=$#array)
	{
		my $x=@array[$i];
		if($x=~/([\%]*)([A-Z]+)\~?([0-9]+)?(\<[^\>]*\>)?(\(\()?(.*)?(\)\))?/)
		{
			my @fs_array=();
			my $order=$1;
			my $chunk=$2;
			my $token_id=$3;
			my $words_fs=$6;
			my $head_fs=$4;
			my %head_hash=();
			my $head_val=0;
		        my $start_of_sent=0;	
		        my $end_of_sent=0;	
		        my $multi_subs=0;	
			$log->info("LHS:Chunk_tag--$chunk~$token_id\n");
			$log->info("Value--$words_fs and ~$head_fs\n");
#			$log->info("Value--1 $1 2 $2 3 $3 4 $4 5 $5 6 $6\n");
			if($order eq "%%"){
				$start_of_sent=1;}
			if($words_fs =~/\%\%/){
				$end_of_sent=1;}
			if($words_fs =~/\*/){
		        	$multi_subs=1;}
			if($words_fs=~/^\{/)
			{
				my @array_words=split(/\}/,$words_fs);
				foreach my $y (@array_words)
				{
					$log->info("word-$y\n");
#					if($y=~/\{([^:]*::)?([\$\.\_a-zA-Z0-9]+)?\%?([a-zA-Z]+)?(\<[^\>]*\>)?/)
					if($y=~/\{([^:]*::)?([\$\.\_a-zA-Z0-9]+)?\%?([\$\.\_a-zA-Z0-9]+)?(\<[^\>]*\>)?/)
					{
						
						my $word_var=$1;
#						$log->info("Word Var-$word_var,Word-$word,Pos-$pos,Fs-$fs\n");
						@test=split(':',$word_var);
						$word_var=@test[0];
#						chop($word_var);
						my $word=$2;
						my $pos=$3;
						my $fs=$4;
						$log->info("Word Var-$word_var,Word-$word,Pos-$pos,Fs-$fs\n");
#						$log->info("word-$word,pos-$pos,fs-$fs\n");
						if($fs ne "" or $word ne "" or $pos ne "" or $word_var ne "")
						{
							my $ref_fs_hash=&fill_fs($word_var,$word,$pos,$fs,$variable);
							my %fs_hash=%$ref_fs_hash;
							push(@fs_array,$ref_fs_hash);
						}
					}
				}
			}
			if($head_fs ne "")
			{
				$head_val=1;
				my $ref_head_hash=&fill_fs("","","",$head_fs);
				%head_hash=%$ref_head_hash;
			}
			$log->info("Headvalue:$head_val start $start_of_sent end $end_of_sent\n");
#			my $_LHS_1={"chunk"=>"$chunk","token_id"=>"$token_id","fs"=>\@fs_array,"head_val"=>$head_val,"head_fs"=>\%head_hash};
			my $_LHS_1={"chunk"=>"$chunk","token_id"=>"$token_id","fs"=>\@fs_array,"head_val"=>$head_val,"head_fs"=>\%head_hash,"start"=>$start_of_sent,"end"=>$end_of_sent,"operator"=>$multi_subs};
			push(@_LHS_,$_LHS_1);
		}
		$i++;
	}

	#RHS PARSING AND LOADING

	$log->info("Parsing RHS\n");
#	$log->info("RHS::@_[2]\n");
        my @array_rhs=split(/\s+/,$rhs);

	&check_rule(\@array_rhs,$rule_no);

#	$log->info("Number of Chunks:",$#array_rhs+1,"\n");
	my $i=0;
	while ($i<=$#array_rhs)
	{
		my $x=@array_rhs[$i];
		if($x=~/(\+)?([A-Z]+)\~?([0-9]+)?(\<[^\<]*\>)?(\(\()?(.*)?(\)\))?/)
		{
			my $add_id=0;
			if($1 eq "+")
			{
				$add_id=1;
			}
			my $chunk=$2;
			my $token_id=$3;
			$log->info("RHS:Chunk_tag-$chunk~$token_id\n");
			my $words_fs=$6;
			my $head_fs=$4;
			my @rhs_fs_array=();
			$log->info("Value--1 $1 2 $2 3 $3 4 $4 5 $5 6 $6\n");

			my %head_hash=();
			my $head_val=0;
			my @drop_childs;      ##List of children to be deleted
			my @add_childs;       ##List of children to be deleted
			my $count_child=1;
			my $multi_subs=0;
			if($words_fs =~/\*/){
		        	$multi_subs=1;}
			if($words_fs=~/^\{/ or $word_fs=~/^+/)
			{
				my @array_rhs_words=split(/\}/,$words_fs);

				foreach my $y (@array_rhs_words)
				{

					if($y eq "{")
					{	
						$log->info("drop yes\n");
						push(@drop_childs,$count_child);
					}
#					if($y=~/(\+)?\{([^:]*::)?([\$\.\_a-zA-Z0-9\^]+)?\%?([a-zA-Z]+)?(\<[^\>]*\>)?/)
					if($y=~/(\+)?\{([^:]*::)?([\$\.\_a-zA-Z0-9\^]+)?\%?([\$\.\_a-zA-Z0-9]+)?(\<[^\>]*\>)?/)
					{
						my $add_child=$1;
						if($add_child eq "+")
						{
							$log->info("Add child\n");
							push(@add_childs,$count_child);
						}
						my $word_var=$2;
						@test=split(':',$word_var);
						$word_var=@test[0];
#						chop($word_var);
						my $word=$3;
						my $pos=$4;
						my $fs=$5;
						$log->info("Word Var-$word_var,Word-$word,Pos-$pos,Fs-$fs\n");
						if($fs ne "" or $word ne "" or $pos ne "" or $word_var ne "")
						{
							my $ref_rhs_fs_hash=&fill_fs($word_var,$word,$pos,$fs);
							my %rhs_fs_hash=%$ref_rhs_fs_hash;
							push(@rhs_fs_array,$ref_rhs_fs_hash);
						}
					}
					$count_child++;
				}
			}

			if($head_fs ne "")
			{
				$head_val=1;
				my $ref_head_hash=&fill_fs("","","",$head_fs);
				%head_hash=%$ref_head_hash;
			}

			my $_RHS_1={"chunk"=>"$chunk",
				"token_id"=>"$token_id",
				"fs"=>\@rhs_fs_array,
				"add"=>"$add_id",
				"add_val"=>$#array_rhs_words+2,
				"drop_childs"=>\@drop_childs,
				"add_childs"=>\@add_childs,
				"head_val"=>"$head_val",
				"operator"=>$multi_subs,
				"head_fs"=>\%head_hash};
			push(@_RHS_,$_RHS_1);
		}
		$i++;

	}
	my @_RULE_NO_;
       	push(@_RULE_NO_,$rule_no);
        my @RULE=();
        push(@RULE,\@_LHS_);
        push(@RULE,\@_RHS_);
        push(@RULE,\@_RULE_NO_);
        push(@_RULE_TREE_,\@RULE);

	$total_rules=@_RULE_TREE_;
#	$log->info("yesy ",\@add_childs,"\n");
	$log->info("###Number of Rules: $total_rules,\n");
	$total_rules--;
	for($lind=0;$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"chunk"} ne "";$lind++)
	{
		my $match=0;
		for($rind=0;$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"chunk"} ne "";$rind++)
		{
			$left_chunk=$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"chunk"}."~".$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"token_id"};
			$right_chunk=$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"chunk"}."~".$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"token_id"};
			my @drop_childs;
			if($left_chunk eq $right_chunk)
			{
				$match=1;
				my $left_c_ind=0,$right_c_ind=0,$flag_check=0;
				my $check_lhs=$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"fs"};
				my @check_lhs_arr=@$check_lhs;
				for($left_c_ind=0;$left_c_ind<=$#check_lhs_arr;$left_c_ind++)
				{
					
					my $lword_index=$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"fs"}->[$left_c_ind]->{"word_var"};
					if($lword_index ne "")
					{

						my $child_match=0;
						my $check_rhs=$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"fs"};
						my @check_rhs_arr=@$check_rhs;
						for($right_c_ind=0;$right_c_ind<=$#check_rhs_arr;$right_c_ind++)
						{
							my $rword_index=$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"fs"}->[$right_c_ind]->{"word_var"};
							if($lword_index eq $rword_index)
							{
								$child_match=1;
								last;
							}
						}
						if($child_match==0)
						{
							$flag_check=1;
							push(@drop_childs,$left_c_ind+1);
						}
						next;
					}
					else
					{last;}
				}
				if($flag_check==1)
				{
					foreach (@drop_childs)
					{
						$log->info("DROP--",$_,"\n");
					}	
					$_RULE_TREE_[$total_rules]->[1]->[$rind]->{"drop_childs"}=\@drop_childs;
				}
				next;
			}
		}
		if($match==0)
		{
			$log->info("Dropping:$left_chunk\n");	
			$_RULE_TREE_[$total_rules]->[0]->[$lind]->{"drop"}=1;			
		}
	}
        return (\@_RULE_TREE_);
}
sub load
{
        my $rule_file=@_[0];
	$tem=@_[0];
	@temp=split('/',$tem);
	$file='';
	$loop=1;
	while($loop<$#temp){
		$file=$file.'/'.@temp[$loop];
		$loop=$loop+1;	}
	$file=$file.'/';
        my $ref_RULE_TREE_=@_[1];
        open(Fp,$rule_file);
	my %var=();

        while(<Fp>)
        {
                if($_=~/^\#/ or $_=~/^\s*\n/)
                {
                        next;
                }
                if($_=~/([a-zA-Z0-9\~\(\)\{\}\"\$\_\<\>\s]+)/)
                {

                }
		if($_=~/^\s*V\s*([0-9][0-9]*)\s*:(.*)::\s*(.*)/)
		{
			my $rules=$2;
			my $variables=$3; 
			@no_of_rules=split(';',$rules);
			foreach my $val(@no_of_rules)
			{
				if($val=~/R([0-9][0-9]*)/)
				{
					$var{$1}=$variables;
				}
			}

		}
		if($_=~/^\s*R\s*([0-9][0-9]*)\s*:\s*(.*)=>\s*(.*)\s*\n/)
                {
                        my $rule_no=$1;
                        my $LHS=$2;
                        my $RHS=$3;
			$log->info("RULE:,$_,\n");
                        my $ref_RULE_TREE_=&parse($rule_no,$LHS,$RHS,$ref_RULE_TREE_,$var{$rule_no});
                }
        }
        return($ref_RULE_TREE_);
}
1;
