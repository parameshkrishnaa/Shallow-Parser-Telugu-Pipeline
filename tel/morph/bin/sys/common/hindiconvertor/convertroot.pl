#!/usr/bin/perl

use Getopt::Long "GetOptions";
$ENV{"LC_ALL"} = "C";
&GetOptions('mode=s' => \$mode,
		's=s' => \$src,
		't=s' => \$tgt,
		'p=s' => \$path,
	   );

if($src eq "wx" and $tgt eq "utf")
{
	while($line = <STDIN>)
	{
		if($line =~ /\)\)/ or $line =~ /entence/ or $line =~ /tory/ or $line =~ /^\s*$/)
		{
			print $line;
		}
		else
		{
			chomp($line);

			($num,$lex,$pos,$fs) = split(/\t/,$line);

			if($lex ne "\(\(")
			{
				if($lex !~ /^@/)
				{
					system("echo $lex > word");
					system("sh $path/bin/sys/common/hindiconvertor/convert-wx2ssf.sh word > out_word");
					open(FILE1,"out_word");
					$lex_out = <FILE1>;
					chomp($lex_out);
				}
				else
				{
					$lex_out = $lex;
				}
			}
			else
			{
				$lex_out = $lex;
			}
			
			if($lex_out eq "")
			{
				$lex_out = $lex;
			}
			if($fs ne "")
			{
				@fss = split(/\|/,$fs);
				$new_fs  = "";
				foreach $af (@fss)
				{
					@fields = split(/\'/,$af);
					$fields[1] = $fields[1].",a";
					($root,@temp) = split(/\,/,$fields[1]);
					$tam = $temp[5];
					$new_field = $fields[0]."'";
					if($root !~ /^@/)
					{	

#-----------------------------convertor-----------------------------------------------------------------------
						system("echo $root > word ");
						system("sh $path/bin/sys/common/hindiconvertor/convert-wx2ssf.sh word > out_word");
						open(FILE1,"out_word");
						$val_out = <FILE1>;
						chomp($val_out);
					}
					else
					{
						$val_out = $root;
					}
					$tam_out = "";
					if($tam_out =~ /^\s*$/)
					{
						$tam_out = $tam;
					}
					chomp($tam_out);
					$new_field = $new_field.$val_out.",";
					$num_temp = @temp;
					$num_temp--;
					for ($ka = 0; $ka < $num_temp; $ka++)
					{
						if($ka == 5)
						{
							$new_field = $new_field.$tam_out.",";		
						}
						else
						{
							$new_field = $new_field.$temp[$ka].",";		
						}
					}
					chop($new_field);
					$num_fields = @fields;
					for ($ka = 2; $ka < $num_fields; $ka++)
					{
						$new_field = $new_field."'".$fields[$ka];
					}
					$new_fs = $new_fs.$new_field."|";
				}
				chop($new_fs);
				print $num,"\t",$lex_out,"\t",$pos,"\t",$new_fs,"\n";
			}
			else
			{
				print $num,"\t",$lex_out,"\t",$pos,"\t",$fs,"\n";
			}
		}
	}
}
elsif($src eq "utf" and $tgt eq "wx")
{
	while($line = <STDIN>)
	{
		if( $line =~ /\)\)/ or $line =~ /entence/ or $line =~ /tory/ or $line =~ /^\s*$/)
		{
			print $line;
		}
		else
		{
			chomp($line);

			($num,$lex,$pos,$fs) = split(/\t/,$line);

			if($lex ne "\(\(")
			{
				if($lex !~ /^@/)
				{
					system("echo $lex > word");
					system("sh $path/bin/sys/common/hindiconvertor/convert-utf2wx.sh word > out_word");
					open(FILE1,"out_word");
					$lex_out = <FILE1>;
					chomp($lex_out);
				}
				else
				{
					$lex_out = $lex;
				}
			}
			else
			{
				$lex_out = $lex;
			}
			
			if($lex_out eq "")
			{
				$lex_out = $lex;
			}
			if($fs ne "")
			{
				@fss = split(/\|/,$fs);
				$new_fs  = "";
				foreach $af (@fss)
				{
					@fields = split(/\'/,$af);
					$fields[1] = $fields[1].",a";
					($root,@temp) = split(/\,/,$fields[1]);
					$tam = $temp[6];
					$new_field = $fields[0]."'";

					if($root !~ /^@/)
					{
#-----------------------------convertor-----------------------------------------------------------------------
							system("echo $root > word ");
							system("sh $path/bin/sys/common/hindiconvertor/convert-utf2wx.sh word > out_word");
							open(FILE1,"out_word");
							$val_out = <FILE1>;
							chomp($val_out);
#-------------------------------------------------------------------------------------------------------------			

					}
					else
					{
						$val_out = $root;
					}
					$tam_out = "";
					if($tam_out =~ /^\s*$/)
					{
						$tam_out = $tam;
					}
					$new_field = $new_field.$val_out.",";		
					$num_temp = @temp;
					$num_temp--;
#	print " -->  $num_temp--> ";
					for ($ka = 0; $ka < $num_temp; $ka++)
					{
						if($ka == 6)
						{
							$new_field = $new_field.$tam_out.",";		
						}
						else
						{
							$new_field = $new_field.$temp[$ka].",";		
						}
					}
						chop($new_field);
					$num_fields = @fields;
					for ($ka = 2; $ka < $num_fields; $ka++)
					{
						$new_field = $new_field."'".$fields[$ka];
					}
					$new_fs = $new_fs.$new_field."|";
				}
				chop($new_fs);
				print $num,"\t",$lex_out,"\t",$pos,"\t",$new_fs,"\n";
			}
			else
			{
				print $num,"\t",$lex_out,"\t",$pos,"\t",$fs,"\n";
			}
		}
	}
}
#system("rm word");
