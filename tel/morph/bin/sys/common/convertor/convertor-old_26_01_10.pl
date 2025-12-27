#!/usr/bin/perl
#Reading command line arguments
use Getopt::Long "GetOptions";
$ENV{"LC_ALL"} = "C";
&GetOptions("help!"=>\$help,'mode=s' => \$mode,
		'path=s'=> \$path,
		'stype=s'=>\$stype,
		'slang=s'=>\$slang,
		'tlang=s'=>\$tlang,
		's=s' => \$src,
		't=s' => \$tgt,
	   );
print "Unprocessed by Getopt::Long\n" if $ARGV[0];

foreach (@ARGV) {
        print "$_\n";
        exit(0);
}


if($help eq 1)
{
        print "SSF/TEXT-UTF-WX Convertor  - SSF?TEXT 3.3.3\n(27th Jan 2009 last modified on 17th Nov 2008)\n\n";
        print "usage : ./run-convertor.pl --path=/home/convertor-3.3.3 --stype=text --tlang=hin -s wx -t utf \n";
        print "or ./run-convertor.pl --path=/home/convertor-3.3.3 --stype=ssf --tlang=hin -s wx -t utf \n";
        print "or  ./run-convertor.pl --path=/home/convertor-3.3.3 --stype=text -s utf -t wx --slang=hin \n";
        print "or  ./run-convertor.pl --path=/home/convertor-3.3.3 --stype=ssf -s utf -t wx --slang=hin \n";
        exit(0);
}
#Checking for each command line arguments
if($path eq "")
{
        print "Please Specify the Path as defined in --help\n";
        exit(0);

}
if($stype eq "")
{
        print "Please Specify the Source Language type in ssf/text as defined in --help\n";
        exit(0);

}
if(($slang eq "") and ($src eq "utf"))
{
        print "Please Specify the Source Language as defined in --help\n";
        exit(0);

}
else{
	if($slang eq "")
	{
		$slang = "hin"; #Default Source language is hindi
	}
}
if(($tlang eq "") and ($src eq "wx"))
{
        print "Please Specify the Target Language as defined in --help\n";
        exit(0);

}
else
{
        if($tlang eq "")
        {
                $tlang = "hin";	#Default Target language is hindi
        }
}
if($src eq "")
{
        print "Please Specify the Src Font as defined in --help [utf/wx]\n";
        exit(0);

}
if($tgt eq "")
{
        print "Please Specify the Target Font as defined in --help [utf/wx]\n";
        exit(0);

}

my $bin=$path."/bin";

#Requiring Mapping modules
require "$bin/$tlang/wx2utf.pl";
require "$bin/$slang/utf2wx.pl";

#Requiring API
require "$path/API/feature_filter.pl";

#Symbols not to be converted
my $symbols="\@\'\"\`\(\)";

# WX -> UTF Conversion
if($src eq "wx" and $tgt eq "utf")
{
	open(STDIN,"<:utf8");
	while($line=<STDIN>)
        {
                chomp ($line);
		#SSF Conversion
		if(($stype eq "SSF") or ($stype eq "ssf"))
                {
                	($num,$lex,$pos,$fs) = split(/\t/,$line);
			#TKN Field Conversion
	                if($lex ne "((" and $lex ne "))")
        	        {	
				#Symbol extracted and stored
				$first=substr($lex,0,1);
				$presymbol="";
				$postsymbol="";
				if($symbols=~/^(.*)($first)(.*)$/)
			        {
					$lex=substr($lex,1);
					$presymbol=$first;
				}
				$last=substr($lex,length($lex)-1,1);
				if($symbols=~/^(.*)($last)(.*)$/)
			        {
					$lex=substr($lex,0,length($lex)-1);
					$postsymbol= $last;
				}
				if(($first=~/\./) and ($tlang eq "hin"))
				{
					$presymbol="";
					$lex="\.".$lex;
				}
				if(($last=~/\./) and ($tlang eq "hin"))
				{
					$postsymbol="";
					$lex=$lex."\.";
				}
				#Bengla v->b mapping
				if($tlang eq "ben")
				{
					$lex=~s/v/b/g;
				}
				#Identifying source language
	                        $srlang = &findlang($lex);
				#Conversion happens when source language is english(wx)
				if($srlang eq "eng")
				{
					if($lex=~m/^[0-9]+$/)
					{
						$lex_out=$lex;
					}
					else{
                        			system("echo $lex > word");
						#Conversion function call
	                        		&wx2utf($path,"word","out_word");
			                        open(FILE1,"out_word");
        			                $lex_out = <FILE1>;
                			        chomp($lex_out);
                        			system("rm -f word out_word");
					}
				}
				else{
					$lex_out=$lex;
				}
				#Reattaching symbols
				$lex_out=$presymbol.$lex_out.$postsymbol;
	                }
        	        if($fs ne "")
                	{	
				#Feature Structure conversion
	                        @fss = split(/\|/,$fs);
        	                my $len = @fss;
                	        @string  = "";
                        	$newfs = "";
	                        my $i=0;
        	                foreach $af (@fss)
                	        {
					#Extraction of each fields using API 
	                                my $FSreference = &read_FS($af,$line);
        	                        my @lex_root = &get_values("lex",$FSreference);
        	                        my @cat_root = &get_values("cat",$FSreference);
                	                my @fs_vib = &get_values("vib",$FSreference);
                        	        my @fs_head = &get_values("head",$FSreference);
                                	my @fs_name = &get_values("name",$FSreference);
	                                
					#Lexical field conversion
					foreach $field (@lex_root)
        	                        {
						#Symbol extracted and stored
						$first=substr($field,0,1);
						$presymbol="";
						$postsymbol="";
						if($symbols=~/^(.*)($first)(.*)$/)
					        {
							$field=substr($field,1);
							$presymbol=$first;
						}
						$last=substr($field,length($field)-1,1);
						if($symbols=~/^(.*)($last)(.*)$/)
					        {
							$field=substr($field,0,length($field)-1);
							$postsymbol= $last;
						}
						if(($first=~/\./) and ($tlang eq "hin"))
						{
							$presymbol="";
							$field="\.".$field;
						}
						if(($last=~/\./) and ($tlang eq "hin"))
						{
							$postsymbol="";
							$field=$field."\.";
						}
						#Bengla v->b mapping
						if($tlang eq "ben")
						{
							$field=~s/v/b/g;
						}
						#Identifying source language
        	                		$srlang = &findlang($field);
						#Conversion happens when language is english and not puncuation or number
						if(($srlang eq "eng") and ($cat_root[0] ne "punc") and ($cat_root[0] ne "num"))
						{
	                        	                system("echo $field > word ");
							#Conversion function call
        	                        	        &wx2utf($path,"word","out_word");
                	                        	open(FILE1,"out_word");
	                        	                $val_out = <FILE1>;
							chomp($val_out);
                                	        	system("rm -f word out_word");
						}
						else{
							$val_out=$field;
						}
						#Reattaching symbols
						$val_out=$presymbol.$val_out.$postsymbol;

						#updating the Lex field with new value using API
                                        	my @lex_arr=();
	                                        push @lex_arr,$val_out;
        	                                &update_attr_val("lex", \@lex_arr,$FSreference,$af);
                	                        $string[$i]=&make_string($FSreference,$af);
                        	        }
					#Vibhakthi field conversion
                                	foreach $field1 (@fs_vib)
	                                {
						#Symbol extracted and stored
						$first=substr($field1,0,1);
						$presymbol="";
						$postsymbol="";
						if($symbols=~/^(.*)($first)(.*)$/)
					        {
							$field1=substr($field1,1);
							$presymbol=$first;
						}
						$last=substr($field1,length($field1)-1,1);
						if($symbols=~/^(.*)($last)(.*)$/)
					        {
							$field1=substr($field1,0,length($field1)-1);
							$postsymbol= $last;
						}
						if(($first=~/\./) and ($tlang eq "hin"))
						{
							$presymbol="";
							$field1="\.".$field1;
						}
						if(($last=~/\./) and ($tlang eq "hin"))
						{
							$postsymbol="";
							$field1=$field1."\.";
						}
						#Bengla v->b mapping
						if($tlang eq "ben")
						{
							$field1=~s/v/b/g;
						}
						#Identifying source language
        	                		$srlang = &findlang($field1);
						#Conversion happens when source language is english(wx)
						if($srlang eq "eng")
						{
	                        	                system("echo $field1 > word ");
							#Conversion function call
        	                        	        &wx2utf($path,"word","out_word");
                	                        	open(FILE1,"out_word");
	                        	                $vib_out = <FILE1>;
        	                        	        chomp($vib_out);
                                	        	system("rm -f word out_word");
						}
						else{
							$vib_out=$field1;
						}
						#Reattaching symbols
						$vib_out=$presymbol.$vib_out.$postsymbol;

						#Updating vibhakthi field with new value using API
                                        	my @fs_vib_arr=();
	                                        push @fs_vib_arr,$vib_out;
        	                                &update_attr_val("vib", \@fs_vib_arr,$FSreference,$af);
                	                        $string[$i]=&make_string($FSreference,$af);
                        	        }
					#HEAD conversion
                                	foreach $field (@fs_head)
	                                {
						#Symbol extracted and stored
        	                                $flag = 0;
                	                        if($field=~/^\".*\"/)
                        	                {
                                	                $field=~s/\"//g;
                                        	        $flag = 1;
	                                        }	
						$flag1=0;
						if($field=~/^\@.*/)
					        {
                					($sym,$field)=split(/\@/,$field);
							$flag1=1;
						}
						#Bengla v->b mapping
						if($tlang eq "ben")
						{
							$field=~s/v/b/g;
						}
						#Identifying source language
        	                		$srlang = &findlang($field);
						#Conversion happens when source language is english(wx)
						if($srlang eq "eng")
						{
	                        	                system("echo $field > word ");
							#Conversion function call
        	                        	        &wx2utf($path,"word","out_word");
                	                        	open(FILE1,"out_word");
	                        	                $val_out = <FILE1>;
        	                        	        chomp($val_out);
	                                        	system("rm -f word out_word");
						}
						else{
							$val_out=$field;
						}
						#Reattaching symbols
						if($flag1)
        	                                {
                	                                $val_out="@".$val_out;
                        	                }
                                	        if($flag)
						{
                                                	$val_out = "\"".$val_out."\"";
                                        	}
						#HEAD updation using API
        	                                my @head_arr=();
                	                        push @head_arr,$val_out;
                        	                &update_attr_val("head", \@head_arr,$FSreference,$af);
                                	        $string[$i]=&make_string($FSreference,$af);
	                                }	
					#NAME conversion
        	                        foreach $field (@fs_name)
                	                {
						#Symbol extracted and stored
                        	                $flag = 0;
                                	        if($field=~/^\".*\"/)
                                        	{
                                                	$field=~s/\"//g;
	                                                $flag = 1;
        	                                }
						$flag1=0;
						if($field=~/^\@.*/)
					        {
                					($sym,$field)=split(/\@/,$field);
							$flag1=1;
						}
						#Bengla v->b mapping
						if($tlang eq "ben")
						{
							$field=~s/v/b/g;
						}
						#Identifying source language
        	                		$srlang = &findlang($field);
						#Conversion happens when source language is english(wx)
						if($srlang eq "eng")
						{
	                        	                system("echo $field > word ");
							#Conversion function call
        	                        	        &wx2utf($path,"word","out_word");
                	                        	open(FILE1,"out_word");
	                        	                $val_out = <FILE1>;
        	                        	        chomp($val_out);
        	                                	system("rm -f word out_word");
						}
						else{
							$val_out=$field;
						}
						#Reattaching symbols
						if($flag1)
        	                                {
                	                                $val_out="@".$val_out;
                        	                }
                                	        if($flag)
                                        	{
                                                	$val_out = "\"".$val_out."\"";
	                                        }
						#Updation of NAME using API
                	                        my @name_arr=();
                        	                push @name_arr,$val_out;
                                	        &update_attr_val("name", \@name_arr,$FSreference,$af);
                                        	$string[$i]=&make_string($FSreference,$af);
                                	}
	                                $i++;
        	                }
				#Making New FS
				foreach $string (@string)
				{	
					if(--$len)
					{	
        	                       		$newfs=$newfs.$string."|";
					}
					else
					{
						$newfs=$newfs.$string;
					}
				}
				#Clean up of Arrays
				delete @string[0..$#string];
				delete @lex_root[0..$#lex_root];
				delete @fss[0..$#fss];

				#Printing converted line
				if($line =~ /\(\(/ or $line =~ /\)\)/)
				{
					($num,$lex,$pos,$fs) = split(/\t/,$line);
					print $num,"\t",$lex,"\t",$pos,"\t",$newfs,"\n";
				}
				else
				{
					print $num,"\t",$lex_out,"\t",$pos,"\t",$newfs,"\n";
				}
			}	
			else{
				if($lex ne "((" and $lex ne "))")
				{
					print $num,"\t",$lex_out,"\t",$pos,"\t",$fs,"\n";
				}
				else{
					print $line."\n";
				}
			}
		}
		#TEXT File conversion
		elsif(($stype eq "TEXT") or ($stype eq "text"))
                {
                        @words = split(/\s/,$line);
                        $symbol=0;
                        $symbol1=0;
                        foreach $lex (@words)
                        {
				#Symbol extracted and stored
				$first=substr($lex,0,1);
				$presymbol="";
				$postsymbol="";
				if($symbols=~/^(.*)($first)(.*)$/)
			        {
					$lex=substr($lex,1);
					$presymbol=$first;
				}
				$last=substr($lex,length($lex)-1,1);
				if($symbols=~/^(.*)($last)(.*)$/)
			        {
					$lex=substr($lex,0,length($lex)-1);
					$postsymbol= $last;
				}
				if(($first=~/\./) and ($tlang eq "hin"))
				{
					$presymbol="";
					$lex="\.".$lex;
				}
				if(($last=~/\./) and ($tlang eq "hin"))
				{
					$postsymbol="";
					$lex=$lex."\.";
				}
				#Bengla v->b mapping
				if($tlang eq "ben")
				{
					$lex=~s/v/b/g;
				}
				#Identifying source language
	                        $srlang = &findlang($lex);
				#Conversion happens when source language is english(wx)
				if($srlang eq "eng")
				{
					if($lex=~m/^[0-9]+$/)
					{
						$lex_out=$lex;
					}
					else{
                                		system("echo $lex > word");
						#Conversion function call
		                                &wx2utf($path,"word","out_word");
        		                        open(FILE1,"out_word");
                		                $lex_out = <FILE1>;
                        		        chomp($lex_out);
                                		system("rm -f word out_word");
					}
				}
                                else
                                {
                                        $lex_out = $lex;
                                }
				#Reattaching symbols
				$lex_out=$presymbol.$lex_out.$postsymbol;
                                print $lex_out." ";
                        }
                        print "\n";
                }
        }
}
# UTF -> WX Conversion
elsif($src eq "utf" and $tgt eq "wx")
{
	open(STDIN,"<:utf8");
	while($line = <STDIN>)
	{
		chomp ($line);
		#SSF Conversion
		if(($stype eq "SSF") or ($stype eq "ssf"))
                {
			($num,$lex,$pos,$fs) = split(/\t/,$line);
			
			#TKN Field Conversion
			if($lex ne "((" and $lex ne "))")
			{	
				#Symbol extracted and stored
				$first=substr($lex,0,1);
				$presymbol="";
				$postsymbol="";
				if($symbols=~/^(.*)($first)(.*)$/)
			        {
					$lex=substr($lex,1);
					$presymbol=$first;
				}
				$last=substr($lex,length($lex)-1,1);
				if($symbols=~/^(.*)($last)(.*)$/)
			        {
					$lex=substr($lex,0,length($lex)-1);
					$postsymbol= $last;
				}
				#Identifying source language
	        	        $srlang = &findlang($lex);
				#if intended source language is marathi set $srlang to marathi
				if(($slang eq "mar") and ($srlang eq "hin"))
				{
					$srlang="mar";
				}
				#Conversion happens only when the input is in source language specified by user
				if($srlang=~/$slang/)
				{
					system("echo $lex > word");
					#Conversion function call
					&utf2wx($path,"word","out_word");
					open(FILE1,"out_word");
					$lex_out = <FILE1>;
					chomp($lex_out);
					system("rm -f word out_word");
				}
				else
				{
					$lex_out = $lex;
				}
				#Reattaching symbols
				$lex_out=$presymbol.$lex_out.$postsymbol;
			}
			if($fs ne "")
			{
				#Feature Structure conversion
				@fss = split(/\|/,$fs);
				my $len = @fss;
				@string  = "";
				$newfs = "";
				my $i=0;
				foreach $af (@fss)
				{
					#Extraction of each fields using API 
					my $FSreference = &read_FS($af,$line);
					my @lex_root = &get_values("lex",$FSreference);
					my @fs_vib = &get_values("vib",$FSreference);
					my @fs_head = &get_values("head",$FSreference);
		                        my @fs_name = &get_values("name",$FSreference);
					#Lexical field conversion
					foreach $field (@lex_root)
					{
						#Symbol extracted and stored
						$first=substr($field,0,1);
						$presymbol="";
						$postsymbol="";
						if($symbols=~/^(.*)($first)(.*)$/)
					        {
							$field=substr($field,1);
							$presymbol=$first;
						}
						$last=substr($field,length($field)-1,1);
						if($symbols=~/^(.*)($last)(.*)$/)
					        {
							$field=substr($field,0,length($field)-1);
							$postsymbol= $last;
						}
						#Identifying source language
			                        $srlang = &findlang($field);
						if(($slang eq "mar") and ($srlang eq "hin"))
						{
							$srlang="mar";
						}
						#Conversion happens only when the input is in source language specified by user
						if($srlang=~/$slang/)
						{
							system("echo $field > word ");
							#Conversion function call
							&utf2wx($path,"word","out_word");
							open(FILE1,"out_word");
							$val_out = <FILE1>;
							chomp($val_out);
							system("rm -f word out_word");
						}
						else{
							$val_out=$field;
						}
						#Reattaching symbols
						$val_out=$presymbol.$val_out.$postsymbol;
						#updating the Lex field with new value using API
						my @lex_arr=();
						push @lex_arr,$val_out;
						&update_attr_val("lex", \@lex_arr,$FSreference,$af);
						$string[$i]=&make_string($FSreference,$af);
					}
					#Vibhakthi field conversion
					foreach $field1 (@fs_vib)
                       	        	{
						#Symbol extracted and stored
						$first=substr($field1,0,1);
						$presymbol="";
						$postsymbol="";
						if($symbols=~/^(.*)($first)(.*)$/)
					        {
							$field1=substr($field1,1);
							$presymbol=$first;
						}
						$last=substr($field1,length($field1)-1,1);
						if($symbols=~/^(.*)($last)(.*)$/)
					        {
							$field1=substr($field1,0,length($field1)-1);
							$postsymbol= $last;
						}
						#Identifying source language
		                        	$srlang = &findlang($field1);
						if(($slang eq "mar") and ($srlang eq "hin"))
						{
							$srlang="mar";
						}
						#Conversion happens only when the input is in source language specified by user
						if($srlang=~/$slang/)
						{
							system("echo $field1 > word ");
							#Conversion function call
							&utf2wx($path,"word","out_word");
			                               	open(FILE1,"out_word");
	        			               	$vib_out = <FILE1>;
	        		        	        chomp($vib_out);
                                        		system("rm -f word out_word");
						}
						else{
							$vib_out=$field1;
						}
						#Reattaching symbols
						$vib_out=$presymbol.$vib_out.$postsymbol;
						#Updating vibhakthi field with new value using API
	                               	        my @vib_arr=();
        	                               	push @vib_arr,$vib_out;
	        	                        &update_attr_val("vib", \@vib_arr,$FSreference,$af);
        	        	                $string[$i]=&make_string($FSreference,$af);
                	        	}
					#HEAD conversion
					foreach $field (@fs_head)
		                        {
						#Symbol extracted and stored
        		        	        $flag=0;
                		                if($field=~/^\".*\"/)
                        		        {
	                                                $field=~s/\"//g;
        	                               	        $flag = 1;
	        	                        }
						$flag1=0;
					        if($field=~/^\@.*/)
				        	{
                					($sym,$field)=split(/\@/,$field);
					                $flag1=1;
						}
						#Identifying source language
			                        $srlang = &findlang($field);
						if(($slang eq "mar") and ($srlang eq "hin"))
						{
							$srlang="mar";
						}
						#Conversion happens only when the input is in source language specified by user
						if($srlang=~/$slang/)
						{
							system("echo $field > word ");
							#Conversion function call
							&utf2wx($path,"word","out_word");
        	                		        open(FILE1,"out_word");
                	                		$head_out = <FILE1>;
			                               	chomp($head_out);
        	                	       		system("rm -f word out_word");
						}
						else{
							$head_out=$field;
						}
						#Reattaching symbols
						if($flag1)
						{
        	                                        $head_out="@".$head_out;
                	                        }
	                	                if($flag)
	        	        	        {
        	        	        		$head_out = "\"".$head_out."\"";
	                	        	}
						#HEAD updation using API
                	                        my @head_arr=();
	                	                push @head_arr,$head_out;
        	                	        &update_attr_val("head", \@head_arr,$FSreference,$af);
                	                	$string[$i]=&make_string($FSreference,$af);
	                        	}
					#NAME conversion
        	                        foreach $field (@fs_name)
	        	                {
						#Symbol extracted and stored
        	        	        	$flag=0;
                	        	        if($field=~/^\".*\"/)
                        	        	{
                                			$field=~s/\"//g;
	                                        	$flag = 1;
		                                }
						$flag1=0;
					        if($field=~/^\@.*/)
					        {
                					($sym,$field)=split(/\@/,$field);
				                	$flag1=1;
						}
						#Identifying source language
			                        $srlang = &findlang($field);
						if(($slang eq "mar") and ($srlang eq "hin"))
						{
							$srlang="mar";
						}
						#Conversion happens only when the input is in source language specified by user
						if($srlang=~/$slang/)
						{
							system("echo $field > word ");
							#Conversion function call
							&utf2wx($path,"word","out_word");
        	                		        open(FILE1,"out_word");
                	                		$name_out = <FILE1>;
	                        	       		chomp($name_out);
	                                		system("rm -f word out_word");
						}
						else{
							$name_out=$field;
						}
						#Reattaching symbols
						if($flag1)
						{
							$name_out="@".$name_out;
						}
		                                if($flag)
        		                        {
						         $name_out = "\"".$name_out."\"";
        	                	        }
						#Updation of NAME using API
	                	                my @name_arr=();
        	                	        push @name_arr,$name_out;
                	                	&update_attr_val("name", \@name_arr,$FSreference,$af);
                        	               	$string[$i]=&make_string($FSreference,$af);
	                        	}
					$i++;
				}
				#Making New FS
				foreach $string (@string)
				{
					if(--$len)
					{
						$newfs=$newfs.$string."|";
					}
					else
					{
						$newfs=$newfs.$string;
					}
				}
				#Clean up of Arrays
				delete @string[0..$#string];
				delete @lex_root[0..$#lex_root];
				delete @fss[0..$#fss];
				#Printing converted line
				if($line =~ /\(\(/ or $line =~ /\)\)/)
				{
					($num,$lex,$pos,$fs) = split(/\t/,$line);
					print $num,"\t",$lex,"\t",$pos,"\t",$newfs,"\n";                       
			        }
				else
				{
					print $num,"\t",$lex_out,"\t",$pos,"\t",$newfs,"\n";
				}
			}
			else{
	                       	if($lex ne "((" and $lex ne "))")
		                {
        		               	print $num,"\t",$lex_out,"\t",$pos,"\t",$fs,"\n";
                        	}
	                       	else{
		                        print $line."\n";
        		        }
                	}
		}
		#TEXT File conversion
		elsif(($stype eq "TEXT") or ($stype eq "text"))
                {
                        @words = split(/\s/,$line);
                        foreach $lex (@words)
                        {
				if(($lex=~/^\|.*/) and (($slang eq "hin") or ($slang eq "mar")))
				{
					$lex=~s/\|/\./g;
				}
				#Symbol extracted and stored
				$first=substr($lex,0,1);
				$presymbol="";
				$postsymbol="";
				if($symbols=~/^(.*)($first)(.*)$/)
			        {
					$lex=substr($lex,1);
					$presymbol=$first;
				}
				$last=substr($lex,length($lex)-1,1);
				if($symbols=~/^(.*)($last)(.*)$/)
			        {
					$lex=substr($lex,0,length($lex)-1);
					$postsymbol= $last;
				}
				#Identifying source language
				$srlang = &findlang($lex);
	                        if(($slang eq "mar") and ($srlang eq "hin"))
        	                {
                	                $srlang="mar";
                        	}
				#Conversion happens only when the input is in source language specified by user
	                        if($srlang=~/$slang/)
	                        {
                                	system("echo $lex > word ");
					#Conversion function call
					&utf2wx($path,"word","out_word");
        	                        open(FILE1,"out_word");
                	                $lex_out = <FILE1>;
                        	        chomp($lex_out);
                                	system("rm -f word out_word");
				}
                                else
                                {
                                        $lex_out = $lex;
                                }
				#Reattaching symbols
				$lex_out=$presymbol.$lex_out.$postsymbol;
                                print $lex_out." ";
                        }
                        print "\n";
                }
	}
}

#Module to find the source language
#Language is determined by the unicode value of first letter(ignoring numbers and _) of the word 
sub findlang
{
        $infile =$_[0];
        system("echo $_[0] > lanword");
        open(FILE, "<:utf8", "lanword");
        $word = <FILE>;
	if($word=~/([0-9]+\_)(.*)/)
	{
		$word=$2;
	}
        @letter = split(//,$word);
        $val = ord($letter[0]);
	system("rm -f lanword");

        if($val >= 2304 and $val <= 2431)
        {
                $result = "hin";
        }
        elsif($val >= 2432 and $val <= 2559)
        {
                $result = "ben";
        }
        elsif($val >= 2560 and $val <= 2659)
        {
                $result = "pan";
        }
        elsif($val >= 2944 and $val <= 3071)
        {
                $result = "tam";
        }
        elsif($val >= 3072 and $val <= 3199)
        {
                $result = "tel";
        }
        elsif($val >= 3200 and $val <= 3327)
	{
                $result = "kan";
        }
        elsif($val >= 3328 and $val <= 3455)
        {
                $result = "mal";
        }
        elsif($val >= 1536 and $val <= 1791)
        {
                $result = "urd";
        }
        else
        {
                $result = "eng";
        }
        return $result;
}

