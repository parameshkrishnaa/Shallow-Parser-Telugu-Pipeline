while($line=<>)
{
	chomp($line);
	($id,$token,$pos,$fs)=split(/\t+/,$line);
	chomp($fs);
	if($pos eq "FRAGP"){
		$pos=~s/FRAGP/BLK/g;
	}
	if($fs=~/\|/)
	{
		$fs=~s/<fs af=\'|\'>//g;
		if(($fs) && ($fs=~/\|/))
		{
			($fs1,$fs2,$fs3,$fs4)=split(/\|/,$fs);
			($root1,$lcat1,$g1,$n1,$p1,$c1,$tam1,$suff1)=split(/,/,$fs1);
			($root2,$lcat2,$g2,$n2,$p2,$c2,$tam2,$suff2)=split(/,/,$fs2);
			if(($suff1 eq "0_o")&&($suff2 eq "lo"))
			{
				$fs1 ="" ;
			}	
			#if(($suff1 eq "nu")&&($suff2 eq "ni")) {
			#	$tmp =$fs1 ;
			#	$fs1=$fs2;
			#	$fs2=$tmp;
			#}
		}
		$fst1= "$id\t$token\t$pos\t<fs af='$fs2'>";
		$fst2= "$id\t$token\t$pos\t<fs af='$fs1'>|<fs af='$fs2'>";
		if($fs1 eq "") {
			print "$fst1\n";
		}
		else {
			print "$fst2\n";
		}
	}
	else {
		print "$id\t$token\t$pos\t$fs\n";
	}
}
