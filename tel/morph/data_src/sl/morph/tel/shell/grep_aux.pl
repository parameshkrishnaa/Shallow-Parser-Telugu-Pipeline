open(FEATURES,"$ARGV[0]");
$i=1;
while($feature=<FEATURES>)
{
chomp($feature);
if($features{$feature} != NULL)
{
$features{$feature}=$features{$feature}."#". $i;
$i++;
}
else
{
$features{$feature}=$i;
$i=$i+1;
}
}
close(FEATURES);


$b[1]=$features{"v tam aka_wappu person any "}; 
$b[2]=$features{"v tam aka_mAnu person any "}; 
$b[3]=$features{"v tam akuMdA_uMdu person any "}; 
$b[4]=$features{"v tam akuMdA_cUdu person any "}; 
$b[5]=$features{"v tam i_po person any "}; 
$b[6]=$features{"v tam i_vaccu person any "}; 
$b[7]=$features{"v tam i_uMdu person any "}; 
$b[8]=$features{"v tam i_cUdu person any "}; 
$b[9]=$features{"v tam i_wIru person any "}; 
$b[10]=$features{"v tam i_peVttu person any "}; 
$b[11]=$features{"v tam i_pAreVyyi person any "}; 
$b[12]=$features{"v tam i_veVyyi person any "}; 
$b[13]=$features{"v tam a_le person any "}; 
$b[14]=$features{"v tam a_badu person any "}; 
$b[15]=$features{"v tam a_gala person any "}; 
$b[16]=$features{"v tam a_bo person any "}; 
$b[17]=$features{"v tam a_nAraMBiMcu person any "}; 
$b[18]=$features{"v tam a_neru person any "}; 
$b[19]=$features{"v tam a_bUnu person any "}; 
$b[20]=$features{"v tam a_goru person any "}; 
$b[21]=$features{"v tam a_ivvu person any "}; 
$b[22]=$features{"v tam a_uMdu person any "}; 
$b[23]=$features{"v tam a_manu person any "}; 
$b[24]=$features{"v tam a_walacu person any "}; 
$b[25]=$features{"v tam a_goVttu person any "}; 
$b[26]=$features{"v tam a_beVttu person any "}; 
$b[27]=$features{"v tam a_wagu person any "}; 
$b[28]=$features{"v tam a_gUdu person any "}; 
$b[29]=$features{"v tam a_galugu person any "}; 
$b[30]=$features{"v tam a_wiyyi person any "}; 
$b[31]=$features{"v tam a_joVccu person any "};
$b[32]=$features{"v tam a_vaccu person any "}; 
$b[33]=$features{"v tam a_jAlu person any "};
$b[34]=$features{"v tam a_paracu person any "};
$b[35]=$features{"v tam a_komanu person any "};
$b[36]=$features{"v tam a_sAgu person any "};
$b[37]=$features{"v tam a_valayu person any "};
$b[38]=$features{"v tam a_buxXiputtu person any "};
$b[39]=$features{"v tam a_buxXavvu person any "};
$b[40]=$features{"v tam a_buxXeVyyi person any "};
$b[41]=$features{"v tam wU_uMdu person any "};
$b[42]=$features{"v tam wU_po person any "};
$b[43]=$features{"v tam wU_vaccu person any "};
$b[44]=$features{"v tam koVn person any "};
$b[45]=$features{"v tam aka_po person any "};
$b[46]=$features{"v tam aka_uMdu person any "};

for ($k = 1;$k<47;$k++)
{
#@tmp=$b[$k];
@tmp = split(/#/,$b[$k]);
foreach $tmp (@tmp){
$PRESENT{$tmp} = 1;
#print $tmp,"\n";
}
}
while($in=<STDIN>)
{
$in =~s/,/","/g;
$in =~s/^/"/;
$in=~ s/","$//;
$in =~  s/"([0-9]*)$/\1,/;
$num = $1;
if($PRESENT{$num}) { print $in; }
}
