#!usr/bin/perl
#This program is to modify
#(i) "pn" to "v" when tam is "ina","e", 
#(ii) "pn" to "n" when tam is "vAru", "Ena"
#(iii) "n" to "v" when tam is "adaM"
#PARAMESH 20/01/2011
##7.2	purAwanamEnaxi	NN	<fs af='purAwana,adj,,,,,xEnaxi_na,xEnaxi_na_adj' poslcat="NM">

use Encode;
binmode(STDIN, ":utf8");
binmode(STDOUT, ":utf8");

while($line=<>)
{
	
	utf8::decode($line);
	$line=~s/\x{2018}/'/g; # <2018> ‘ is Replaced by single quote "'"
	$line=~s/\x{2019}/'/g; # <2019> ’ is Replaced by single quote "'"
	$line=~s/\x{200D}//g; # <200D> is Removed
	$line=~s/\x{200C}//g; # <200C> is Removed
	$line=~s/\x{200c}//g; # <200C> is Removed
	$line=~s/\x{202c}//g; # <200C> is Removed
	$line=~s/\x{200B}//g; # <200B> is Removed
	$line=~s/\x{feff}//g; # <feff> is Removed
	$line=~s/\x{0D}//g; #  is Removed
	$line=~s///g; #  is Removed
##	print $line;

chomp($line);
($id,$token,$pos,$fs)=split(/\t+/,$line);
chomp($fs);

##if ($fs=~/\|/){
##print $line;
##}
if (($fs!~/\|/)){
##if (($fs!~/\|/)||($fs=~/adaM.*\|/)){
##2       veVlYladAnni    unk     <fs af='veVlYlu,n,,sg,,,adaM_nu,adaM_nu'>|<fs af='veVlYlu,n,,sg,,,adaM_ni,adaM_ni'>
#
###print "Im fs--$fs\n";
	($root1,$lcat1,$g1,$n1,$p1,$c1,$tam1,$suff1)=split(/,/,$fs);
#print " Imhere with $root1\n";
	##print " I am suff--- $suff1\n";
	if(($tam1=~/adaM/)&&($lcat1 eq "n")) {
		$lcat1=~s/n/v/;
	         }
		if (($root1=~/[^A-z]XO/)&&($lcat1 eq "unk"))
#7	"	unk	<fs af='"XO,unk,,,,,,'>
			{
			$root1=~s/XO/$1/;
			$lcat1= "punc";
			}
	#4.2	eVkkuvagA	RB	<fs af='eVkkuva,adj,,,,,gA,gA_adj' poslcat="NM">
	#eVkkuva as noun;
#	print " I am root1--- $root1\n";
	if(($root1=~/eVkkuva$/)&&($lcat1 eq "adj")&&($tam1 ne "0")) { $lcat1=~s/^adj/n/; $n1="sg";  }
#7       waruvAwive      unk     <fs af='waruvAyi,pn,,pl,,,xi_0,xi_0_e'>
	if (($lcat1 eq "pn") and ($tam1 eq "ni_xi") and ($suff1=~/ni_xi_gA/)) #7	uMxigA	unk	<fs af='uMdu,pn,,sg,,,ni_xi,ni_xi_gA'>
		{
			$lcat1 =~s/pn/v/g;
			$g1="n";
			$n1="sg";
			$p1="3";
			$tam1="A";
		}
## Blocked due to generation problem becoz, muKyamEnavi is generated as mukkiyawu in Tamil
	if (($lcat1 eq "pn") and ($tam1 eq "xi")and ($n1 eq "sg") and ($suff1=~/xi_gA/))  ## cinnaxigA	unk	<fs af='cinna,pn,,sg,,,xi,xi_gA'>,
				{
			$lcat1 =~s/pn/adj/g;
			$g1="n";
			$n1="sg";
			$p1="3";
			$tam1="gA"; 
				}
	if (($lcat1 eq "pn") and ($tam1=~/^vAru/)and ($n1 eq "pl")) {
	#1	britiRuvAri	unk	<fs af='britiRu,pn,,pl,,,vAru,vAru_obl'>			{
			$lcat1 =~s/pn/n/g;
			$g1="n";
			$n1="sg";
			$p1="3";
			$tam1=~s/vAru/0/; 
			$tam1=~s/^0_//; 
		###	if($root1=~/vAri$/) { $tam1="ti"; }
			$root1=$root1."vAru"; 
				}
	if (($lcat1 eq "pn") and ($tam1 eq "xi")and ($n1 eq "pl"))  ## ## but  muKyamEnavi     <fs af='muKya,pn,,pl,,,xi,xi_0'>
				{ #2       goVppavi        unk     <fs af='goVppa,pn,,pl,,,xi,xi_0'>
			$lcat1 =~s/pn/adj/g;
			$g1="n";
			$n1="pl";
			$p1="3";
			$tam1="0"; ## Here nEnA is n+EnA n=Noun mukya]ADJ=>mukyaM]N=>mukyamEnA]ADJ=>mukyamEnavi]N
				}
	if (($lcat1 eq "adj") and ($tam1 eq "xEnaxi_na"))  ## 7.2	purAwanamEnaxi	NN	<fs af='purAwana,adj,,,,,xEnaxi_na,xEnaxi_na_adj' poslcat="NM">
				{
			$lcat1 =~s/adj/n/g;
			$root1 =~s/a$/aM/g;
			$g1="n";
			$n1="sg";
			$p1="3";
			$tam1="Ena_axi"; ## Here nEnA is n+EnA n=Noun mukya]ADJ=>mukyaM]N=>mukyamEnA]ADJ=>mukyamEnavi]N
				}


	if($tam1=~/_/) {
		($ta1,$ta2)=split(/\_/,$tam1);
	if (($lcat1 eq "pn") and ($ta1=~/^ina|^e$|^ani|^wunna$/) and ($ta2=~/axi/) and ($n1 eq "pl"))# and ($suff !~/\|/))
 #1       uMdevi  unk     <fs af='uMdu,pn,,pl,,,e_axi,e_axi_0'>

				{
			$lcat1 =~s/pn/v/g;
			$g1="any";
			$n1="any";
			$p1="any";
			$tam1=~s/_axi/_avi/;
				}
		if (($lcat1 eq "pn") and ($ta1=~/^ina|^e$|^ani|^wunna$/) and ($ta2=~/axi/) and ($n1 eq "sg"))# and ($suff !~/\|/))
 #1       uMdevi  unk     <fs af='uMdu,pn,,pl,,,e_axi,e_axi_0'>

				{
			$lcat1 =~s/pn/v/g;
			$g1="any";
			$n1="any";
			$p1="any";
				}
			
	##		print "Im herew with $lcat1 and $ta1 \n";
	if (($lcat1 eq "pn") and ($ta1=~/ina|^e|wunna|^ani|^i$|^e$|^wU|^a$|^aka|^koVn|^akuMdA/))# and ($suff !~/\|/))
				{
			$lcat1 =~s/pn/v/g;
			$lcat1 =~s/n/v/g;
#			$g1="any";
#			$n1="any";
#			$p1="any";

				}
		if (($lcat1 eq "pn") and ($ta1=~/vAru|vAlYlu/))
				{
			$lcat1 =~s/pn/n/g;
			$g1="n";
			$n1="any";
			$p1="any";
				}
		if (($lcat1 eq "pn") and ($ta1=~/Ena/) and ($suff1=~/_gA'/))
			{
			$lcat1 =~s/pn/n/g;
			$g1="n";
			#$n1="any";
			$p1="any";
			$tam1=$suff1;
			$tam1=~s/'>//g;
				}
		if (($lcat1 eq "pn") and ($ta1=~/Ena/))
				{
			$lcat1 =~s/pn/n/g;
			$g1="n";
			#$n1="any";
			$p1="any";
				}

			}

##10	muKyamEnavi	unk	<fs af='muKya,pn,,pl,,,xi,xi_0'>
	
		$fs = "$root1,$lcat1,$g1,$n1,$p1,$c1,$tam1,$suff1";

		}

$line ="$id\t$token\t$pos\t$fs";
print "$line\n";
}

