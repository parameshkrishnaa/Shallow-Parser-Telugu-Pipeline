#!/usr/bin/perl
#vesrion 4 
%var_hash=();

sub rule_match 
{
	my $sent=@_[0];
	my $ref_RULE_TREE_=@_[1];
	
	@_RULE_TREE_=@$ref_RULE_TREE_;

	my $count=0;
		
	## Handling SSF 
	my @tree=&get_children(0,$sent);		
	my $ssf_string=&get_field($tree[0],3,$sent);
	if($ssf_string eq "SSF")
	{
		@nodes=&get_children(1,$sent);
	}
	else
	{
		@nodes=@tree
	}


	my $flag=0;
	for(my $i=0;$i<=$#nodes;)
	{
		for(my $j=0;$j<=$#_RULE_TREE_;$j++)
		{
			my ($f0,$f1,$f2,$f3,$f4)=&get_fields($nodes[$i],$sent);
			my $temp_i=$i;
			my $old_i=$i;
 			my $old_k=0; 
			my $val=0;
			my $skip=0;
			my @array_lhs1=$_RULE_TREE_[$j]->[0];
			for(my $k=0;$_RULE_TREE_[$j]->[0]->[$k]->{"chunk"} ne "";)
			{
				$log->info("RULE AT-$f3\n");
				$log->info("Rule No--$_RULE_TREE_[$j]->[2]->[0]\n");
				$log->info("Pos in Rule--,",$k+1,"\n");
				$log->info("Rule Chunk Tag:,",$_RULE_TREE_[$j]->[0]->[$k]->{"chunk"},"\n");
#				$log->info("Rule Start:,",$_RULE_TREE_[$j]->[0]->[$k]->{"start"},"\n");
#				$log->info("Rule End:,",$_RULE_TREE_[$j]->[0]->[$k]->{"end"}, $i ,"\n");
				if(($f3 eq $_RULE_TREE_[$j]->[0]->[$k]->{"chunk"}))
				{
					if($_RULE_TREE_[$j]->[0]->[$k]->{"drop"}==1)
					{
						$log->info("DROP ",$_RULE_TREE_[$j]->[0]->[$k]->{"chunk"},"\n");
					}	
					if($_RULE_TREE_[$j]->[0]->[$k]->{"head_val"} eq 0)
					{
						$ref_check=$_RULE_TREE_[$j]->[0]->[$k]->{"fs"};
						$flag=&children_fs_match($nodes[$temp_i],$sent,\$_RULE_TREE_[$j]->[0]->[$k]->{"fs"});
					}
					if($_RULE_TREE_[$j]->[0]->[$k]->{"head_val"} eq 1)
					{
						$flag=&head_fs_match($nodes[$temp_i],$sent,\$_RULE_TREE_[$j]->[0]->[$k]->{"head_fs"});
						if($flag eq 1)
						{
							$ref_check=$_RULE_TREE_[$j]->[0]->[$k]->{"fs"};
							$flag=&children_fs_match($nodes[$temp_i],$sent,\$_RULE_TREE_[$j]->[0]->[$k]->{"fs"});
						}
					}
					if($flag ne "1")
					{
						$i=$old_i;
						last;
					}
					else
					{
						$temp_i++;
						$k++;
#						$log->info("piyush $k and $temp_i \n");
						if($temp_i>$#nodes and $_RULE_TREE_[$j]->[0]->[$k]->{"chunk"} eq "")
						{
							$i=$old_i;
							$val=0;
							last;	
						}
						if($temp_i>$#nodes)
						{
							$flag=0;
							$val=0;
							$i=$old_i;
							last;	
						}

						($f0,$f1,$f2,$f3,$f4)=&get_fields($nodes[$temp_i],$sent);
						
						next;
					}
				}
				else
				{
					$flag=0;
					$i=$old_i;
					last;
				}
			}
			if($flag eq 1)
			{
				my %temp_array_rhs=$_RULE_TREE_[$j]->[1]->[0];
				($f0,$f1,$f2,$f3,$f4)=&get_fields($nodes[$i],$sent);
				$log->info("Applying Rule number:$_RULE_TREE_[$j]->[2]->[0],\@ $f0\n");
				&modify_tree_rhs(\@nodes,$i,$sent,\$_RULE_TREE_[$j],$skip);
				@nodes=&get_children(0,$sent);
				$flag=0;
				next;
			}
		}
		$i++;
		
	}
}


sub match_fs
{
	my $word1=@_[0];
	my $pos1=@_[1];
	my $fs1=@_[2];
	my $ref_hash=@_[3];
	my $sent=@_[4];
	my %temp_hash=%$ref_hash;
	
	my $fs_array = &read_FS($fs1,$sent);

	my $flag=1;
	my $att;
	my @array_fs;
	foreach $uu(%temp_hash)
	{
		if($temp_hash{$uu} ne "") 
		{
			if($uu eq "word_var")
			{
				$flag=1;
				next;
			}
			my @check=&get_values($uu,$fs_array);
			@check[0]=~s/"//g;	
			if($uu eq "pos")
			{
				@check[0]=$pos1;
			}
			if($uu eq "word")
			{
				@check[0]=$word1;
			}
			if($uu eq "cm" or $uu eq "tam")
			{
				@check=&get_values("vib",$fs_array);
			}
			if($uu eq "suff")
			{
				@check=&get_values("tam",$fs_array);
			}
			if($uu eq "root")
			{
				@check=&get_values("lex",$fs_array);
			}
			if($uu eq "pers")
			{
				@check=&get_values("per",$fs_array);
			}
			if($uu eq "lcat")
			{
				@check=&get_values("cat",$fs_array);
			}
			if($uu eq "gend")
			{
				@check=&get_values("gen",$fs_array);
			}
			if($uu eq "case")
			{
				@check=&get_values("cas",$fs_array);
			}
#			$log->info("check ",$uu," ",$temp_hash{$uu}," ",@check[0],"\n");
			if(@check[0] eq $temp_hash{$uu})
			{
				$flag=1;
				next;
			}
			if(@check[0] eq "" and $temp_hash{$uu} eq "NULL"){
				next;
			}


################################ MATCHING VARIABLES##################################

			#for variable of the form $x,$y;
#			$log->info("ppp $temp_hash{$uu} \n");	
			if($temp_hash{$uu}=~/(^\$[a-zA-Z0-9]+)$/){
				$var_hash{$1}=@check[0];
				$log->info("Variable:$1 Value:@check[0]\n");
				next;
			}
			
			#for variable of the form $x=>list and filename type
			if($temp_hash{$uu}=~/(\$[a-zA-Z0-9]+)?=>(.*)?$/){
				$variable=$1;
				$var=$2;
#				$log->info("guess $variable, $var,\n");
				if($var=~/(.*)\.txt/){
					@check[0]=~s/"//g;	
					my $var_file=$file.$1.".txt";
					open(Fp,$var_file);
					while(<Fp>)
					{
						if($_=~/(.*)\n/){
							$log->info("file Variable:$1 Value:@check[0]\n");
							if($1 eq @check[0])
							{
								$flag=1;
								$var_list{$variable}=$1;
								last;
							}
							else{
								$flag=0;}
							}
					}
					if($flag eq 0){
						return;}
					}
				else{
					if($flag ne 0)
					{
					@check[0]=~s/"//g;	
					@val=split(',',$var);
					foreach my $viv(@val){
						$log->info("list Variable:$viv Value:@check[0]\n");
						if($viv eq @check[0]){
							@check[0]=$viv;
							$flag=1;
#							$log->info("pol $1 $viv\n");
							$var_list{$1}=$viv;
							last;}
						else{
							$flag=0;}
						 }
					if($flag eq 0){
						return;}
					}	
				    }	
			
				$var_hash{$1}=@check[0];
				$log->info("Flag:$flag Variable:$1 Value:@check[0]\n");
				next;
			}

			#for variable of the form $x.ani
#			$log->info("yupps $temp_hash{$uu},$uu \n");
			if($temp_hash{$uu}=~/(.*)?\.(\$[a-zA-Z0-9]+)?/){
				my $temp1=$1;
				my $temp2=$2;
				if(@check[0]=~/$temp1(.*)/)
				{
					@tem=split('"',$1);
					$log->info("Variable:$temp2 Value:@tem[0]\n");
					$var_hash{$temp2}=@tem[0];
					$flag=1;
					next;
				}
				else{
					$flag=0;
				}
			}

			#for variable of the form wunn.$x 
			if($temp_hash{$uu}=~/(\$[a-zA-Z0-9]+)?\.(.*)?/){
				my $temp1=$1;
				my $temp2=$2;
				if(@check[0]=~/(.*)$temp2/)
				{
					@tem=split('"',$1);
					$log->info("Variable:$temp1 Value:@tem[0]\n");
					$var_hash{$temp1}=@tem[0];
					$flag=1;
					next;
				}
				else{
					$flag=0;
				}
			}
			if($temp_hash{$uu} ne @check[0]){
				$flag=0;
				$log->info("Input Value and Rule Value :$temp_hash{$uu} and @check[0] Don't Match\n");
				return $flag;
			}
			
		}
	}
	return $flag;
}

sub head_fs_match
{
	my $node=@_[0];
	my $sent=@_[1];
	my $ref_temp_fs_hash=@_[2];
	my $ref_temp_hash=$$ref_temp_fs_hash;
	my %temp_hash=%$ref_temp_hash;
	my $flag=1;
	my ($f0,$f1,$f2,$f3,$f4)=&get_fields($node,$sent);
	$flag=&match_fs($f2,$f3,$f4,\%temp_hash,$sent);
	$log->info("Head Flag Val=$flag\n");
	return $flag;
}

sub children_fs_match
{
	my $node=@_[0];
	my $sent=@_[1];
	my $ref_temp_fs_array=@_[2];
	my $ref_temp_array=$$ref_temp_fs_array;
	my @temp_array=@$ref_temp_array;
	my @children=&get_children($node,$sent);
	my $num=@children;

	for($l=0;$l<$num;$l++)
	{
		my ($f0,$f1,$f2,$f3,$f4)=&get_fields($children[$l],$sent);
		my $ref_temp_hash=$temp_array[$l];
		my %temp_hash=%$ref_temp_hash;
		$log->info("Word::$f2 ::Pos::$f3 ::Fs::$f4::\n");
		$flag=&match_fs($f2,$f3,$f4,\%temp_hash,$sent);
		$log->info("Part Flag Val=$flag\n");
		if($flag==0)
		{
			return $flag;
		}
	}
	$ref_temp_hash=$temp_array[3];
	$num=@temp_array;
	%temp_hash=%$ref_temp_hash;
	if($#children<$#temp_array)
	{
		return 0;
	}
	$log->info("Flag Val=$flag\n");
	return $flag;
}
1;
