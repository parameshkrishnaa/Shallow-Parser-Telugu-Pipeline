## Deals with  spelling variation & simple SANDHI for TELUGU --TEL-TAM MT##
#Oct, 2008, PARAMESHKRISHNA
#Then adopted for Telugu-Hindi by  gurao 1May2012
use Encode;
#use strict;

binmode(STDIN, ":utf8");
binmode(STDOUT, ":utf8");

	$count = 0;
while($line=<>)
{
chomp($line);
	my $word1,$word2, $word;
	##my $word1, $word;
	utf8::decode($line);
	$line=~s/\x{2018}/'/g; # <2018> ‘ is Replaced by single quote "'"
        $line=~s/\x{2019}/'/g; # <2019> ’ is Replaced by single quote "'"
        $line=~s/\x{200D}//g; # <200D> is Removed
        $line=~s/\x{200C}//g; # <200C> is Removed
        $line=~s/\x{200c}//g; # <200C> is Removed
        $line=~s/\x{202c}//g; # <200C> is Removed
        $line=~s/\x{200B}//g; # <200B> is Removed
        $line=~s/\x{2022}/\./g; # • is converted to .
        $line=~s/\x{feff}//g; # <feff> is Removed
        $line=~s/\x{0D}//g; # ^M is Removed
		$line=~s/\x{00A0}/ /g; 
		$line=~s/\x{008B}//g;
        $line=~s/á//g; # 

	$line=~/([0-9]*)\t(.*)\t(.*)/;
	$num=$1;
	$word=$2;

#	if($word=~/([A-z]+)(a[dmnvrx])emo([A-z]*)/) {
#	$word=~/([A-z]+)(a[dmnvrx])emo([A-z]*)/;
#	$word=$1$2."u\tunk";
#	$word1="emo".$3;
#	}
# 060211 
	
##SPELL ERROR 
### 231111
	$word=~s/^vadduna/oVdduna/;
	$word=~s/^caxivAsw/caxivesw/;
	$word=~s/paxArX/paxArW/;
	$word=~s/prAXa/prAWa/;
	$word=~s/paXa/paWa/;
	$word=~s/ArXik/ArWik/;
	$word=~s/arXaM/arWaM/;
	$word=~s/arXam/arWam/;
	$word=~s/^eVmEnA/emEnA/;
	$word=~s/^bAvuNNani/bAvuMdunani/;
	$word=~s/^paMdakkani/paMdagakani/;
	$word=~s/^koVMceM/koVMceVM/;
	$word=~s/koVvad/kovad/;
	$word=~s/^meM/memu/;
	$word=~s/^nixxar/nixra/;
	$word=~s/lloV$/llo/;
	$word=~s/^maxya/maXya/;
	$word=~s/^sAyiMwr/sAyaMwr/;
	$word=~s/svawahAga$/svawahAgA/;
	$word=~s/rAwrillu/rAwrilYlu/;
	$word=~s/AwiXya/AwiWya/;
	$word=~s/^Bavisyaw/BaviRyaw/;
	$word=~s/cUdaccu/cUdavaccu/;
	$word=~s/paddayi/paddAyi/;
	$word=~s/^goVMdA/guMdA/;
	$word=~s/gurYrYaM/gurraM/;
	$word=~s/^kApowe/kAkapowe/;
	$word=~s/^koVluvEvu\t/koVluvavvu\t/;
	$word=~s/^mAneVyy$/mAneVyyi/;
	$word=~s/^mAnuvulu/mAnavulu/;
	$word=~s/^mAtlAdako/mAtlAduko/;
	$word=~s/^mavuwu/avuwu/;
	$word=~s/^poVru\t/poru\t/;
	$word=~s/^purAwawwva/purAwawva/;
	$word=~s/^svecca/svecCa/;
	$word=~s/^veVlYlaDAnni/veVlYladAnni/;
	$word=~s/^veVxava/veVXava/;
	$word=~s/^vyavariMc/vyavahariMc/;
	$word=~s/^weVvAcI/wivAcI/;
	$word=~s/^xiyetar/Wiyetar/;
	$word=~s/^xurGaM/xurgaM/;
	$word=~s/^yuxxaM/yuxXaM/;
	$word=~s/^kaMtlo/kaMtilo/;
	$word=~s/^hOtal/hotal/;
	$word=~s/^cirAggA/cirAkugA/;
	$word=~s/iunna/ivunna/; ##	kaligiunna
	$word=~s/^kAgAdAlawo/kAgadAlawo/;
	$word=~s/^bAlex/bAgAlex/;
	$word=~s/^moVxatnuMc/moVxatinuMc/;
	$word=~s/veVlYlAM/veVlYlAmu/;	##veVlYlAM
	$word=~s/veVlYlYAM/veVlYlAmu/;	##veVlYlAM
	$word=~s/ccAM\t/ccAmu\t/;	##kAniccAM
	$word=~s/McAM\t/McAmu\t/;	##AsvAxiMcAM
	$word=~s/peVttale\t/peVttalexu\t/;	##veVlYlAM
	$word=~s/marcipo/maricipo/;	##veVlYlAM
	$word=~s/marcibo/maricibo/;	##veVlYlAM
	$word=~s/^cotiki/cotuki/;	##
	$word=~s/xaMta\t/xata\t/;	##vaswuMxaMta
	$word=~s/^manipiMc/anipiMc/;	##vaswuMxaMta
	$word=~s/^parcina/paricina/;	##vaswuMxaMta
	$word=~s/^goVNakkaMdi/goVNagakaMdi/;	##vaswuMxaMta
	$word=~s/^sarukku/saruku/;	##vaswuMxaMta
	$word=~s/^ceskuMt/cesukoVMt/;	##vaswuMxaMta
	$word=~s/^mugguruni/muggurini/;	##vaswuMxaMta
	$word=~s/klni\t/kulani\t/;	##paryAtaklni 
	$word=~s/pAxaPaMkw/pAxapaMkw/;	##pAxaPaMkwulalo
	$word=~s/valsina/valasina/;	##UhiMcukovalsina, valsina
	$word=~s/ggurni\t/ggurini\t/;	##muggurni
	$word=~s/amuxvArA/aMxvArA/; #samAcAramuxvArA
	$word=~s/sAranaX/sAranAW/;
	$word=~s/^sarle/sarele/;
	$word=~s/^sAyiMwr/sAyaMwir/;  #sAyiMwrAlu
	$word=~s/^axbuwa/axBuwa/; #axbuwa
	$word=~s/gurrapaSAla/gurrapuSAla/;#gurrapaSAlalu
	$word=~s/vyavariMc/vyavahariMc/;#vyavariMc
	$word=~s/vyayasAya/vyavasAya/;#vyayasAya
	$word=~s/xiyeatar/Wiyetar/;#xiyeatar
	$word=~s/icadaM/iMcadaM/;#sevicadaM
	$word=~s/teVrrakoVtta/teVrrakota/;#teVrrakoVtta
	$word=~s/varuNaasi/varuNAsi/;#varuNaasi
	$word=~s/veVlaSAr/veVliSAr/;#veVlaSArani
	$word=~s/xaggaxi\t/xaginaxi\t/;#xaggaxi
	$word=~s/wadisAyi\t/wadicAyi\t/;#wadisAyi
	$word=~s/^mamUlu\t/mAmUlu\t/;#mamUlu
	$word=~s/^BAxapad/bAXapad/;#bAXapadinattu
	$word=~s/wuMparl/wuMparal/;#nItiwuMparlu
	$word=~s/maruvale/maravale/;#maruvaleni
	$word=~s/kuneru\t/kuMtAru\t/;#anukuneru => anukuMtAru [ceVppevu, ceVpperu = ceVpwAvu, ceVpwAru]
	$word=~s/^Avalaku\t/Avaliki\t/;#Avaliki = anwappakkam
	$word=~s/bAvutuMxi\t/bAvuMtuMxi\t/;#bAvutuMxi
	#$word=~s/vIrla([kn])i/vIrula$1i/;#yuxXavIrlani
	$word=~s/galasi/galisi/;#kalagalisi
	##$word=~s/piluvabad/pilavabad/;#badu forms are chopped; in that case piluva to be pilava to analyse correctly # blocked on 14112013, since it is carried by MA correctly-chris,rajini
	$word=~s/^velYlYe/veVlYlYe/; #velYlYexI
	$word=~s/^aXbuw/axBuw/; #aXbuwaMgA
	$word=~s/xAgiMxi/xAgivuMxi/; #aXbuwaMgA
	$word=~s/sevicaMdaM/seviMcadaM/; #sevicaMdaM
	$word=~s/EkyawE/Ekyawa/; #sevicaMdaM
	$word=~s/^([A-z]*)([aeoiu])kAvadaM/$1avvadaM/; #vIlukAvadaM
	$word=~s/^([A-z]*)MkAvadaM/$1mavvadaM/; #priyaMkAvadaM
	$word=~s/^ayipobo/ayipo/; #ayipobowunnAM
	$word=~s/^svawahAga/svawahAgA/; #svawahAga
	$word=~s/anukuMdagA\t/anukuMtuMdagA\t/;
	$word=~s/^vrASevAru/vrAsevAru/;#vrASevAru
	$word=~s/^mAneVyy$/mAneVyyi/;#mAneVyy
	$word=~s/Alloki$/Alaloki/;#poVlAlloki
	$word=~s/^kalasipo/kalisipo/;#kalasipoye
	$word=~s/^aMnnAru/annAru/;#	aMnnAru
	$word=~s/^munuRyul/manuRyul/;#munuRyulu
	$word=~s/^xemudu\t/xevudu\t/;#xemudu
	$word=~s/ceseMxuru\t/ceseMxuku\t/;#ceseMxuru
	$word=~s/^matlAd/mAtlAd/;#ceseMxuru
	$word=~s/^nilucunna/nilicivunna/;#ceseMxuru
	$word=~s/^roddula/rodla/;#ceseMxuru
	$word=~s/^graxXa/graxxa/;#ceseMxuru
	$word=~s/poyinanU\t/poyinA\t/;#pUdipoyinanU
	$word=~s/^BaXraM/BaxraM/;#BaXraMgA
	$word=~s/lonu\t/lonU\t/;#sAmrAjyaMlonu
	$word=~s/unnE\t/unnAyi\t/;#unnE = > unnAyi gurao-290812
	$word=~s/([AIaiooeuUV])swE\t/$1swAyi\t/;#vaswE = > vaswAyi gurao-290812
	$word=~s/uMtE\t/uMtAyi\t/;#uMtE = > uMtAyi gurao-290812
	$word=~s/inE\t/inAyi\t/;# kalisinE = > kalisinAyi chris-270812

#spell variation

#020712#	$word=~s/vacceMxuk/vaccexAnik/;#vacceMxuku as vaccexAniki; 
#


#if($word=~/\.([A-z])\./) { #AAA.... n2 diff lines..
#	$word=~/(.*)([A-z])\.(.*)/;
#	$word=$1."\tunk";
#	$word1=$2."\tunk";
#	$word="\.".$3;
#	}## 231111
	
	#if($word=~/^([^A-z])([A-z]*)([^A-z])\t/) 
	if($word=~/^([^A-z])([A-z]+)([^A-z])\t/) {
	$word="$1\tunk";
	$word1="$2\tunk";
	$word2="$3\tunk";
	}
		
#	if($word=~/lokeVllA/) {
#	$word=~s/lokeVllA/lokallA/;
#	}
	if($word=~/kovAlasi/) {  #ceVppukovAlasiMxi
	$word=~s/vAlasi/valasi/;
	}
	if($word=~/^xIMwo\t/) {
	$word=~s/xIMwo/xIniwo/;
	}
	if($word=~/logala/) {
	$word=~s/logala/lo/;
	$word1="unna\tunk";
	}
	if($word=~/amaMd([Ii])\t/) { #gurao27092012 anyAyamaMdi
	$word=~s/([A-z]+)amaMd([Ii])/$1aM/;
	$word1="aMd$2\tunk";
	}
	if($word=~/xXaMd([Ii])\t/) { #gurao27092012 anyAyamaMdi
	$word=~s/([A-z]+)xXaMd([Ii])/$1xXi/;
	$word1="aMd$2\tunk";
	}
	if($word=~/lonunna/) {	##SarIraMlonunna
	$word=~s/lonunna/lo/;
	$word1="unna\tunk";
	}
	if($word=~/loMci\t/) {
	$word=~s/loMci/lonuMci/;	##AhAraMloMci
	}
	if($word=~/moVxalukuni\t/) {
	$word=~s/moVxalukuni/moVxalukoVni/;	##AhAraMloMci
	}
	if($word=~/anetivi\t/) {
	$word=~s/anetivi/anevi/;	##anetivi
	}
	if($word=~/ayina[^p]/) { #ayinapudu
	$word=~s/ayina/Ena/;
	}
	if($word=~/assalu/) {
	$word=~s/assalu/asalu/;
	}
	#if($word=~/ayinA\t/) { ayinA is a verb EnA is a particle
	#$word=~s/ayinA/EnA/;
	#}
	if($word=~/kovavala/) { ## ceVppukovavalasiMxi
	$word=~s/kovavala/kovala/;
	}
	if($word=~/nAXud/) {
	$word=~s/nAXud/nAWud/;
	}
	if($word=~/lYlY/) {  
	$word=~s/lYlY/lYl/;
	}
	if($word=~/^SawABxA/) {  ##SawABxAniki=>SawAbxAniki
	$word=~s/SawABxA/SawAbxA/;
	}
	if($word=~/iu/) {
	$word=~s/iu/ivu/;
	}
	if($word=~/aa/) { ##maawraM
	$word=~s/aa/A/;
	}
	if($word=~/^XeSa/) { ##XeSapu
	$word=~s/^XeSa/xeSa/;
	}
	if($word=~/^kArANA/){ ##	kArANAla => kAraNAla
	$word=~s/^kArAN/kAraN/;
	}
	if($word=~/([A-z]+)(\")/) {  #word" => word " gurao24102012
        $word=~/([A-z]+)(\")(.*)/;
	$word=$1."\tunk";
	$word1=$2.$3;
}
	if($word=~/tixAkA/) {
	$word=~s/tixAkA/tixAka/;
	}
	if($word=~/ullo/) {
	$word=~s/ullo/ulalo/;
	}
	

	if($word=~/^vu/) {
	$word=~s/^vu/u/;
	}
	if($word=~/^vU/) {
	$word=~s/^vU/U/;
	}
	if($word=~/^vo/) {
	$word=~s/^vo/o/;
	}
	if($word=~/^yi/) {
	$word=~s/^yi/i/;
	}
	if($word=~/^yeV/) {
	$word=~s/^yeV/eV/;
	}
	if($word=~/^ye/) {
	$word=~s/^ye/e/;
	}
	if($word=~/^yI/) {
	$word=~s/^yI/I/;
	}
	if($word=~/pUduku\t/) {  	##  goVMwupUduku
	$word=~s/pUduku\t/pUdukoVni\t/;
	}
	if($word=~/^sAnAmaMxi/) {  	##  goVMwupUduku
	$word=~s/sAnAmaMxi/cAlAmaMxi/;
	}

	#if($word=~/[^rN]apu\t/) {  	## prAMwapu, BArawaxeSapu needs to be in genitive. Repair and TG has sum prblm. Temporarily written here, *caxarapu, xakRiNapu
	if($word=~/[^rN]apu\t/ && $word!~/vArAMwapu/) {  	## prAMwapu, BArawaxeSapu needs to be in genitive. Repair and TG has sum prblm. Temporarily written here, *caxarapu, xakRiNapu
	$word=~s/apu/aMyoVkka/g;
	}
	if($word=~/^ammayi/) {  	## ammayi
	$word=~s/^ammayi/ammAyi/g;
	}
	if($word=~/oV\t/) {  	## kutuMbAlloV
	$word=~s/oV\t/o\t/g;
	}
	if($word=~/coVkapowe\t/) {  	## kUrcoVkapowe
	$word=~s/oVkapowe/okapowe/g;
	}
	
	if($word=~/[^m]mulo/) { ## roVmmuloni *roVMmMloni 240312
	$word=~s/mulo/Mlo/;
	}
	if($word=~/vanni\t/) {	##ivanni
	$word=~s/vanni/vannI/;
	}
	if($word=~/SAKAhA/) { ##SAKAhArame
	$word=~s/SAKAhA/SAkAhA/;
	}
	#if($word=~/annaxi\t/) { ##annaxi
	#$word=~s/annaxi/anexi/;
	#}
	if(($word=~/muwo\t/)||($word=~/mugA\t/)) {
	$word=~s/mugA/MgA/;
	$word=~s/muwo/Mwo/;
	}
	if($word=~/[^l][^Amue]mu\t/) { #soVmmu 260210_Paramesh, Aduxumu 300310_Paramesh, AdawAmu 010410_Paramesh #ceVppalemu
	$word=~s/mu\t/M\t/;
	}
	if($word=~/[nr]AM\t/) { #mAtlAdukunnAM => mAtlAdukunnAmu
	$word=~s/AM\t/Amu\t/;
	}
#	if($word=~/unnAM\t/) { #bayaluxerAM
#	$word=~s/AM\t/Amu\t/;
#	}
	if($word=~/wAM\t/) {
	$word=~s/wAM/wAmu/;
	}
	if($word=~/uMtAM\t/) {
	$word=~s/uMtAM/uMtAmu/;
	}
	if($word=~/maxya/) {
	$word=~s/maxya/maXya/;
	}
	if($word=~/^eVmEnA\t/) {
	$word=~s/eVmEnA/emEnA/;
	}
	if($word=~/abaduwA/) {
	$word=~s/abaduwA/abadawA/;
	}
#	if($word=~/xAriwIyunu/) { #240510;guraoblocked since it is wrong27092012
#	$word=~s/wIyu/wiyyu/;
#	}
	if($word=~/‘/) {
	$word=~s/‘/'/;
	}
	if($word=~/’/) {
	$word=~s/’/'/;
	}
	if($word=~/–/) {
	$word=~s/–/-/;
	}
	if($word=~/“/) {
	$word=~s/“/"/;
	}
	if($word=~/”/) { # ”
	$word=~s/”/"/;
	}
	if($word=~/…/) {
	$word=~s/…/\.\.\./;
	}
	
	
	if ($word=~/^"([A-z]+)"/) { ##rU.10kotla modifiedon 24102012
	$word=~/(.*)"([A-z]+)"(.*)/;
	$word=$1."\"\tunk";
	$word1=$2."\tunk";
	$word2="\"".$3;
	}
	if ($word=~/^rU\.([0-9]+).*([A-z])/) { ##rU.10kotla modifiedon 24102012
	$word=~/(.*)rU\.([0-9]+)([A-z])(.*)/;
	$word=$1."rU\.\tunk";
	$word1=$2."\tunk";
	$word2=$3.$6;
	}
	if ($word=~/[A-z]\..*\.[A-z]/) {### AAA...BB as a three entry
	$word=~/(.*)([A-z]+)\.(.*)\.([A-z]+)(.*)/;
	$word=$1.$2."\tunk";
	$word1="\.".$3."\.\tunk";
	$word2=$4.$5;
	}
	if ($word=~/([A-z]+)\..*\.([0-9]+)/) { #avalokiswe...30
	$word=~/(.*)([A-z]+)\.(.*)\.([0-9]+)(.*)/;
	$word=$1.$2."\tunk";
	$word1="\.".$3."\.\tunk";
	$word2=$4.$5;
	}
	
	if($word=~/([A-z])\.\./) { #AAA.... n2 diff lines..
	$word=~/(.*)([A-z])\.\.(.*)/;
	$word=$1.$2."\tunk";
	$word1="\.\.".$3;
	}
#	if($word=~/([A-z])\./) { #AAA. ... n2 diff lines..
#	$word=~/(.*)([A-z])\.(.*)/;
#	$word=$1.$2."\tunk";
#	$word1="\.".$3;
#	}
	
	if($word=~/\.([A-z])/) { #.....AAA n2 diff lines..
	$word=~/(.*)\.([A-z])(.*)/;
	$word=$1."\.\tunk";
	$word1=$2.$3;
	}
	if($word=~/\.([0-9]+)/) { # ...30
	$word=~/(.*)\.([0-9]+)(.*)/;
	$word=$1."\.\tunk";
	$word1=$2.$3;
	}
	if($word=~/^([0-9]+)([A-z]+)/) { # 600maMxi, 10kotla
	$word=~/(.*)([0-9]+)([A-z]+)(.*)/;
	$word=$1."$2\tunk";
	$word1=$3.$4;
	}
	### 'saMpraxAyamu
	if($word=~/^["'][A-z]/) { #'harinA n2 diff lines..
	$word=~/(.*)(['"])([A-z])(.*)/;
	$word=$1.$2."\tunk";
	$word1=$3.$4;
	}
	### saMpraxAyamu'
	if($word=~/[A-z]["']\t/) { #harinA' n2 diff lines..
	$word=~/(.*)([A-z])(["'])\t(.*)/;
	$word=$1."$2\tunk";
	$word1=$3."\t".$4;
	}
	if($word=~/^caxavAlsiMxenani/) {  	##caxavAlsiMxe
	$word=~/(.*)caxavAlsiMxenani(.*)/;
	$word=$1."caxava\tunk";
	$word1="valasiMxe\tunk";
	$word2="ani".$2;
	}
	if($word=~/leVnnounnAyi/) {  	##viMwaleVnnounnAyi
	$word=~/(.*)leVnnounnAyi(.*)/;
	$word=$1."lu\tunk";
	$word1="eVnno\tunk";
	$word2="unnAyi".$2;
	}
	if($word=~/kulexemo/) {  	## sarukulexemo
	$word=~/(.*)kulexemo(.*)/;
	$word=$1."ku\tunk";
	$word1="lexu\tunk";
	$word2="emo".$2;
	}
=head
	if($word=~/[A-z]lexani\t/) {  	## iccexilexani
	$word=~/(.*)lexani(.*)/;
	$word=$1."\tunk";
	$word1="lexu\tunk";
	$word2="ani".$2;
	}
=cut
	if($word=~/^lexani\t/) {  	## iccexilexani
	$word=~/(.*)lexani(.*)/;
	$word=$1."lexu\tunk";
	$word1="ani".$2;
	}
	if($word=~/^mIrosAri/) {  	## mIrosAri
	$word=~/(.*)mIrosAri(.*)/;
	$word=$1."mIru\tunk";
	$word1="oVka\tunk";
	$word2="sAri".$2;
	}
#rU.10kotla
	if($word=~/([A-z])kUdA\t/) {	##jAgrawwalanukUdA
	$word=~/(.*)kUdA(.*)/;
	$word=$1."\tunk";
	$word1="kUdA".$2;
	}
	if($word=~/([A-z])atle[nmrvx]u\t/) {	##kanipiMcatlexu
	$word=~/(.*)atle(.*)/;
	$word=$1."adaM\tunk";
	$word1="le".$2;
	}
	if($word=~/([A-z])wunnatle\t/) {	##vihariswunnatle
	$word=~/(.*)wunnatle(.*)/;
	$word=$1."wunna\tunk";
	$word1="atle".$2;
	}
	if($word=~/cAlaMtunnAru\t/) {	##cAlaMtunnAru
	$word=~/(.*)cAlaM(.*)/;
	$word=$1."cAlu\tunk";
	$word1="aM".$2;
	}
	if($word=~/vAlaMtunnAru\t/) {	##wIsukovAlaMtunnAru
	$word=~/(.*)vAlaMtu(.*)/;
	$word=$1."vAli\tunk";
	$word1="aMtu".$2;
	}
	if($word=~/ixaMtunnAru\t/) {	##maMcixaMtunnAru
	$word=~/(.*)ixaMtu(.*)/;
	$word=$1."ixi\tunk";
	$word1="aMtu".$2;
	}
	if($word=~/aMtuMt/) {	##aMtuMtAru
	$word=~/(.*)aMtu(.*)/;
	$word=$1."aMtU\tunk";
	$word1="u".$2;
	}
#	if($word=~/([A-z])ale[nmrvx]u\t/) {	##
#	$word=~/(.*)ale(.*)/;
#	$word=$1."a\tunk";
#	$word1="le".$2;
#	}
	if($word=~/([A-z])ttuMde\t/) {	##kattinattuMde
	$word=~/(.*)ttuMde(.*)/;
	$word=$1."ttu\tunk";
	$word1="uMde".$2;
	}
	if($word=~/([A-z])manaMxar([A-z]*)/) {
	$word=~/(.*)manaMxar(.*)/;
	$word=$1."mana\tunk";
	$word1="aMxar".$2;
	}
	if($word=~/([A-z]+)kaMxar([A-z]*)/) {
	$word=~/(.*)kaMxar(.*)/;
	$word=$1."ku\tunk";
	$word1="aMxar".$2;
	}
	if($word=~/([A-z]+)naMxar([A-z]*)/) {
	$word=~/(.*)naMxar(.*)/;
	$word=$1."ni\tunk";
	$word1="aMxar".$2;
	}
	if($word=~/([A-z]+)vEpul([A-z]*)/) {
	$word=~/(.*)vEpul(.*)/;
	$word=$1."\tunk";
	$word1="vEpul".$2;
	}
	if($word=~/([A-z]+)Ayemo\t/) {
	$word=~/(.*)Ayemo(.*)/;
	$word=$1."Ayi\tunk";
	$word1="emo".$2;
	}
	if($word=~/([A-z]+)remo\t/) {	##marcipoyAremo
	$word=~/(.*)remo(.*)/;
	$word=$1."ru\tunk";
	$word1="emo".$2;
	}
	if($word=~/([A-z]+)Axemo\t/) {
	$word=~/(.*)Axemo(.*)/;
	$word=$1."Axu\tunk";
	$word1="emo".$2;
	}
	if($word=~/([A-z]+)Mxemo\t/) { ##uMtuMxemo
	$word=~/(.*)Mxemo(.*)/;
	$word=$1."Mxi\tunk";
	$word1="emo".$2;
	}
	if($word=~/([A-z]+)emonanipisw([A-z]+)/) {
	$word=~/(.*)emonanipisw(.*)/;
	$word=$1."emo\tunk";
	$word1="anipisw".$2;
	}
	if($word=~/([A-z]+)axanipisw([A-z]+)/) {  #BAravaMwamEnaxanipiswunnA
	$word=~/(.*)([^k])axanipisw(.*)/;
	$word=$1.$2."axi\tunk";
	$word1="anipisw".$3;
	}
	if($word=~/([A-z]+)[^k]anipisw([A-z]+)/) {  #but not for kanipisw
	$word=~/(.*)[^k]anipisw(.*)/;
	$word=$1."\tunk";
	$word1="anipisw".$2;
	}
	if($word=~/nirASrayulE/) {
	$word=~s/nirASrayulE/nirASrayulu/;
	$word1="E"."\tunk";
	}
	if($word=~/([A-z])mAwraM\t/) {		###anexi+mAwraM
	$word=~s/mAwraM//;
	$word1="mAwraM"."\tunk";
	}
	#blocked paramesh 05072012
	#if($word=~/([A-z])gAnU\t/) {		###ArogyaMgAnU
	#$word=~s/gAnU/gA/;
##	$word1="mAwraM"."\tunk";
	#}
	if($word=~/nirASrayula([yv])/) {
	$word=~/(.*)nirASrayula(.*)/;
	$word=$1."nirASrayulu\tunk";
	$word1="a".$2;
	}
	
	if($word=~/liMtiki\t/) { ##vAlYliMtiki
	$word=~/(.*)liMti(.*)/;
	$word=$1."lu\tunk";
	$word1="iMti".$2;
	}
	if($word=~/lakoVswe\t/) { ##viRayAlakoVswe
	$word=~/(.*)lakoVswe(.*)/;
	$word=$1."laku\tunk";
	$word1="vaswe".$2;
	}
	if($word=~/mar([iaeV]+)ppud/) {
	$word=~/(.*)mar(.*)/;
	$word=$1."mari\tunk";
	$word1=$2;
	}
	if($word=~/ppudavi\t/) { ##ippudavi
	$word=~/(.*)davi(.*)/;
	$word=$1."du\tunk";
	$word1="avi".$2;
	}
	if($word=~/demuMxi\t/) { ##ikkademuMxi
	$word=~/(.*)demuM(.*)/;
	$word=$1."da\tunk";
	$word1="emuM".$2;
	}
	if($word=~/[rd]ikkada\t/) { ##ArAXiswArikkada
	$word=~/(.*)ikkada(.*)/;
	$word=$1."u\tunk";
	$word1="ikkada".$2;
	}
	if($word=~/AvalivEp/) { ##AvalivEpuna
	$word=~/(.*)AvalivEp(.*)/;
	$word=$1."avawali\tunk";
	$word1="vEp".$2;
	}
	if($word=~/mareVkkad/) {
	$word=~/(.*)mareVkkad(.*)/;
	$word=$1."mari\tunk";
	$word1="eVkkad".$2;
	}
	if($word=~/deVkkad/) {	#vAdeVkkada
	$word=~/(.*)deVkkad(.*)/;
	$word=$1."du\tunk";
	$word1="eVkkad".$2;
	}
	if($word=~/keVppud/) {
	$word=~/(.*)keVppud(.*)/;
	$word=$1."ku\tunk";
	$word1="eVppud".$2;
	}
	if($word=~/mavatamegAk/) {
	$word=~/(.*)mavatamegAk(.*)/;
	$word=$1."M\tunk";
	$word1="avatamegAk".$2;
	}
	if($word=~/muwo\t/) {
	$word=~s/muwo\t/Mwo\t/;
	}
	if($word=~/mugA\t/) {
	$word=~s/mugA\t/MgA\t/;
	}
	if($word=~/mulone/) {
	$word=~s/mulone/Mlone/;
	}
	#if($word=~/[^u]gAne\t/) {	##BAgaMgAne, *nenannattugAne
	#$word=~/(.*)gAne(.*)/;
	#$word=$1."\tunk";
	#$word1="gAne".$2;
	#}

#91213
#	if($word=~/Mwudiccina/) {	##BagavaMwudiccina
#	$word=~/(.*)Mwud(.*)/;
#	$word=$1."Mwudu\tunk";
#	$word1=$2;
#	}
	if($word=~/wunnappudu\t/) {	##bawukuwunnappudu
	$word=~/(.*)unnappudu(.*)/;
	$word=$1."u\tunk";
	$word1="unnappudu".$2;
	}
	#if($word=~/inappud/) {	#vaccinappudallA
	#$word=~/(.*)inappud(.*)/;
	#$word=$1."ina\tunk";
	#$word1="appud".$2;
	#}
	if($word=~/[A-z]unnapudu\t/) {	##unnapudu
	$word=~/(.*)unnapudu(.*)/;
	$word=$1."\tunk";
	$word1="unnappudu".$2;
	}

	if($word=~/([drvnmc])aMtunn/) { ##gadapavaccaMtunnAru
	$word=~/(.*)([drvnmc])aMtunn(.*)/;
	$word=$1.$2."u\tunk";
	$word1="aMtunn".$3;
	}
	if($word=~/AyaMte/) {
	$word=~/(.*)AyaMte(.*)/;
	$word=$1."Ayi\tunk";
	$word1="aMte".$2;
	}
	if($word=~/lemaMte/) { ##viRayAlemaMte
	$word=~/(.*)lemaMte(.*)/;
	$word=$1."lu\tunk";
	$word1="emaMte".$2;
	}
	if($word=~/xxAmaMte\t/) { ## palakarixxAmaMte
	$word=~/(.*)xxAmaMte(.*)/;
	$word=$1."xxAmu\tunk";
	$word1="aMte".$2;
	}
	if($word=~/[^v]AlsiM/) {
	$word=~s/AlsiM/avalasiM/;
	}
	if($word=~/iMcucunnA/) {
	$word=~s/iMcucunnA/iMcuwunnA/;
	}
	if($word=~/([A-z]+)veVlYlA/) {  ##poVrugUruveVlYlA gurao27092012
	$word=~/(.*)veVlYlA(.*)/;
	$word=$1."\tunk";
	$word1="veVlYlA".$2;
	}
	if($word=~/lokoVcciM/) {
	$word=~/(.*)lokoVcciM(.*)/;
	$word=$1."loki"."\tunk";
	$word1="vacciM".$2;
	}
	if($word=~/moVcciMxi/) {
	$word=~/(.*)moVcciMxi(.*)/;
	$word=$1."M"."\tunk";
	$word1="vacciMxi".$2;
	}
	if($word=~/([A-z]+)koVsw([A-z]+)/) {
	$word=~/([A-z]+)koVsw(.*)/;
	$word=$1."ku"."\tunk";
	$word1="vasw".$2;
	}
	if($word=~/([A-z]+)koVccesw([A-z]+)/) {
	$word=~/([A-z]+)koVccesw(.*)/;
	$word=$1."ku"."\tunk";
	$word1="vaccesw".$2;
	}
	if($word=~/nuMdoVcc/) {
	$word=~/(.*)nuMdoVcc(.*)/;
	$word=$1."nuMdi"."\tunk";
	$word1="oVcc".$2;
	}
	if($word=~/anadigiwe/) {
	$word=~/(.*)anadigiwe(.*)/;
	$word=$1."ani"."\tunk";
	$word1="adigiwe".$2;
	}
	if($word=~/atlayiwe/) {
	$word=~s/atlayiwe/atlEwe/;
	}
	if($word=~/vonanna/) {
	$word=~/(.*)vonanna(.*)/;
	$word=$1."vo"."\tunk";
	$word1="anina".$2;
	}
	if($word=~/levonanna/) {
	$word=~/(.*)levonanna(.*)/;
	$word=$1."levo"."\tunk";
	$word1="anina".$2;
	}
	#caxavAlsiMxenani
	
	if($word=~/^maniRIyana/) {  	## maniRIyana
	$word=~/(.*)maniRIyana(.*)/;
	$word=$1."maniRi\tunk";
	$word1="IyanA".$2;
	}
	if(($word=~/enani\t/)&&($word!~/^n/)) {	#nijamenani
	$word=~/(.*)enani(.*)/;
	$word=$1."e"."\tunk";
	$word1="ani".$2;
	}
	if($word=~/iMxani/) {
	$word=~/(.*)iMxani(.*)/;
	$word=$1."iMxi\tunk";
	$word1="ani".$2;
	}
#if($word=~/[A-z][^M]xAni\t/) {	##kaxAni, *aMxAni, *oVkaxAni
#	$word=~/(.*)xAni(.*)/;
#	$word=$1."xA\tunk";
#	$word1="ani".$2;
#	}
	if($word=~/annAdawanu/) {
	$word=~/(.*)annAdawanu(.*)/;
	$word=$1."annAdu"."\tunk";
	$word1="awanu".$2;
	}
	if($word=~/annAdAyana/) {
	$word=~/(.*)annAdAyana(.*)/;
	$word=$1."annAdu"."\tunk";
	$word1="Ayana".$2;
	}
	if($word=~/annaxAmeV/) {
	$word=~/(.*)annaxAmeV(.*)/;
	$word=$1."aMxi" ."\tunk";
	$word1="AmeV".$2;
	}
	if($word=~/annatluMxi/) {
	$word=~/(.*)annatluMxi(.*)/;
	$word=$1."annatlu\tunk";
	$word1="uMxi".$2;
	}
#110110 PARAMESH
	#if($word=~/rAMwAnni/) {  #prAMwAnni
	#$word=~/(.*)rAMwAnni(.*)/;
	#$word=$1."rAMwaM\tunk";
	#$word1="anni".$2;
	#}
	if($word=~/amEnAyi/) { #BAgamEnAyi
	$word=~/(.*)amEnAyi(.*)/;
	$word=$1."aM\tunk";
	$word1="EnAyi".$2;
	}
	if($word=~/maniccAvu/) { #janmaniccAvu
	$word=~/(.*)maniccAvu(.*)/;
	$word=$1."ma\tunk";
	$word1="iccAvu".$2;
	}
	if($word=~/agalamanna\t/) { ##sAXiMcagalamanna
	$word=~/(.*)agalamanna(.*)/;
	$word=$1."a\tunk";
	$word1="galamu\tunk";
	$word2="anna".$2;
	}
	if($word=~/[dm]anna\t/) { ## unnAmanna, wayAravuwunnAdanna
	$word=~/(.*)anna(.*)/;
	$word=$1."u\tunk";
	$word1="anna".$2;
	}
	#if($word=~/yanunna/) { #maXyanunna
	#$word=~/(.*)yanunna(.*)/;
	#$word=$1."yana\tunk";
	#$word1="nunna".$2;
	#}
	if($word=~/alunna/) { #godalunna
	$word=~/(.*)alunna(.*)/;
	$word=$1."alu\tunk";
	$word1="unna".$2;
	}
	if($word=~/lEpoyAyi/) { #BAgAlEpoyAyi
	$word=~/(.*)EpoyAyi(.*)/;
	$word=$1."u\tunk";
	$word1="EpoyAyi".$2;
	}
	if($word=~/ioV/) { #prawioVkadinI
	$word=~/(.*)ioV(.*)/;
	$word=$1."i\tunk";
	$word1="oV".$2;
	}
	if($word=~/[lg]unnAyi/) { #rARtrAlunnAyi, nAlugunnAyi
	$word=~/(.*)unnAyi(.*)/;
	$word=$1."u\tunk";
	$word1="unnAyi".$2;
	}
	if($word=~/lunnAru\t/) { #rARtrAlunnAyi
	$word=~/(.*)unnA(.*)/;
	$word=$1."u\tunk";
	$word1="unnA".$2;
	}
	if($word=~/lanni/) { #swAnAlannitinI
	$word=~/(.*)lanni(.*)/;
	$word=$1."lu\tunk";
	$word1="anni".$2;
	}
	if($word=~/lannI\t/) { #	godalannI 240510
	$word=~/(.*)lannI(.*)/;
	$word=$1."lu\tunk";
	$word1="annI".$2;
	}
	if($word=~/raman([iI]+)\t/) { #rARtramanI, raMXramani
	$word=~/(.*)raman(.*)/;
	$word=$1."raM\tunk";
	$word1="an".$2;
	}
	if($word=~/vannI\t/) { #avannI
	$word=~/(.*)vann(.*)/;
	$word=$1."vi\tunk";
	$word1="ann".$2;
	}
	if($word=~/[AEIOUVeioua][lr]aMwA\t/) { #vIraMwA, loyalaMwA
	$word=~/(.*)aMwA(.*)/;
	$word=$1."u\tunk";
	$word1="aMwA".$2;
	}
	if($word=~/rAwraMwA\t/) { #rAwraMwA
	$word=~/(.*)rAwraMwA(.*)/;
	$word=$1."rAwri\tunk";
	$word1="aMwA".$2;
	}
	if($word=~/[^n][t]aMwA\t/) { #xqRtaMwA
	$word=~/(.*)aMwA(.*)/;
	$word=$1."i\tunk";
	$word1="aMwA".$2;
	}
	if($word=~/maMwA\t/) { #aMxamaMwA
	$word=~/(.*)maMwA(.*)/;
	$word=$1."M\tunk";
	$word1="aMwA".$2;
	}
	if($word=~/AnnaMwA\t/) { #aMxAnnaMwA, *winnaMwa
	$word=~/(.*)nnaMwA(.*)/;
	$word=$1."nni\tunk";
	$word1="aMwA".$2;
	}
#220110 PARAMESH
	if($word=~/lapEbadi\t/) { #grAmAlapEbadi
	$word=~/(.*)lapEbadi(.*)/;
	$word=$1."la\tunk";
	$word1="pEbadi".$2;
	}
	if($word=~/amoVka/) { #nagaramoVkati
	$word=~/(.*)amoVka(.*)/;
	$word=$1."aM\tunk";
	$word1="oVka".$2;
	}
	if($word=~/laMxukoV/) { # #nIrAjanAlaMxukoVMxi
	$word=~/(.*)laMxukoV(.*)/;
	$word=$1."laMxu\tunk";
	$word1="koV".$2;
	}
	if($word=~/ixeperu/) { # ixeperuwo
	$word=~/(.*)xeperu(.*)/;
	$word=$1."xe\tunk";
	$word1="peru".$2;
	}
	#if($word=~/cinapudu/) { # AkramiMcinapudu
	#$word=~/(.*)cinapudu(.*)/;
	#$word=$1."cina\tunk";
	#$word1="appudu".$2;
	#}
	if($word=~/^yunnaxi/) { #yunnaxi
	$word=~s/^yu/u/;
	}
#170210 PARAMESH
#
	if($word=~/arXaMkAni/) { # arXaMkAni
	$word=~/(.*)arXaMkAni(.*)/;
	$word=$1."arXaM\tunk";
	$word1="kAni".$2;
	}
	if($word=~/iwara[A-z]/) { #iwaravAhanAla
	$word=~/(.*)iwara(.*)/;
	$word=$1."iwara\tunk";
	$word1=$2;
	}
	if($word=~/\tI[A-z]/) { # IxAri
	$word=~/(.*)I(.*)/;
	$word=$1."I\tunk";
	$word1=$2;
	}
	if($word=~/[A-z]unappatik/) { # kriwaMnAtivani
	$word=~/(.*)unappatik(.*)/;
	$word=$1."una\tunk";
	$word1="unnappatik".$2;
	}
	if($word=~/nAtivani/) { # kriwaMnAtivani  nirNayiMcabaduwuMxani
	$word=~/(.*)nAtivani(.*)/;
	$word=$1."nAtivi\tunk";
	$word1="ani".$2;
	}
	if($word=~/gaxani\t/) { # jaragaxani
	$word=~/(.*)gaxani(.*)/;
	$word=$1."gaxu\tunk";
	$word1="ani".$2;
	}
	if($word=~/nikani\t/) { # snAnAnikani
	$word=~/(.*)nikani(.*)/;
	$word=$1."niki\tunk";
	$word1="ani".$2;
	}
	#020712#if($word=~/[kld][Aea]xani\t/) { #  ^lexani,kAxani,kUdaxani
	#$word=~/(.*)xani(.*)/;
	#$word=$1."xu\tunk";
	#$word1="ani".$2;
	#}

	if($word=~/wunnaxani\t|[^l]exani\t|inaxani\t/) { # waleVwwuwunnaxani  [nirNayiMcabaduwuMxani] ^lexani, *jarugaxani
	$word=~/(.*)xani(.*)/;
	$word=$1."xi\tunk";
	$word1="ani".$2;
	}
	if($word=~/koVnevani/) { # DIkoVnevani
	$word=~/(.*)nevani(.*)/;
	$word=$1."ne\tunk";
	$word1="ani".$2;
	}
#020712#	if($word=~/[^p]accani\t/) { # ceyavaccani, NOT paccani
	#$word=~/(.*)ccani(.*)/;
	#$word=$1."ccu\tunk";
	#$word1="ani".$2;
	#}
	if($word=~/[kx]allA\t/) { # ceyavalasiMxallA,prapaMcaMlokallA
	$word=~/(.*)allA(.*)/;
	$word=$1."i\tunk";
	$word1="allA".$2;
	}
	#020712if($word=~/xanuko/) { # cUdalexanukoMdi
#	$word=~/(.*)xanuko(.*)/;
#	$word=$1."xu\tunk";
#	$word1="anuko".$2;
#	}
	if($word=~/[mnvxy]anuk/) { # 
	$word=~/(.*)anuk(.*)/;
	$word=$1."u\tunk";
	$word1="anuk".$2;
	}
#020712#	if($word=~/[l]anuk/) { # uMdAlanukune
	#$word=~/(.*)anuk(.*)/;
	#$word=$1."i\tunk";
	#$word1="anuk".$2;
	#}
	if($word=~/lixxarU\t/) { # xaMpawulixxarU
	$word=~/(.*)lixxarU(.*)/;
	$word=$1."lu\tunk";
	$word1="ixxarU".$2;
	}
	if($word=~/awE\t/) { # EkyawE
	$word=~/(.*)awE(.*)/;
	$word=$1."awa\tunk";
	$word1="E".$2;
	}
	if($word=~/([A-z])varakU\t/) { # ippativarakEwe
	$word=~/(.*)varakU(.*)/;
	$word=$1."\tunk";
	$word1="varakU".$2;
	}
	if($word=~/[ua]sArE[nw][Ae]\t/) { # oVkkasArayinA
	$word=~/(.*)sArE(.*)/;
	$word=$1."sAri\tunk";
	$word1="E".$2;
	}
	#if($word=~/[dr]EnA|[dr]Ewe/) { # eVvarEnA, eVvarEwe, puMdEwe
	#$word=~/(.*)E(.*)/;
	#$word=$1."u\tunk";
	#$word1="E".$2;
	#}
	if($word=~/u[v]emi\t/) { # wakkuvemi, wakkuvEwe
	$word=~/(.*)vemi(.*)/;
	$word=$1."va\tunk";
	$word1="emi".$2;
	}
	if($word=~/Alanexi\t/) { # peVMcukovAlanexi, jIviMcAlanexi
	$word=~/(.*)Alanexi(.*)/;
	$word=$1."Ali\tunk";
	$word1="anexi".$2;
	}
	if($word=~/akEnA\t|akEwe\t/) { # ippativarakEwe
	$word=~/(.*)akE(.*)/;
	$word=$1."aku\tunk";
	$word1="E".$2;
	}
	if($word=~/ikEnA\t|ikEwe\t/) { # ippativarakEwe
		$word=~/(.*)ikE(.*)/;
		$word=$1."iki\tunk";
		$word1="E".$2;
	}
#if($word=~/mEnA|mEwe/) { # kosamEnA, *emEnA
#$word=~/(.*)mE(.*)/;
#$word=$1."M\tunk";
#$word1="E".$2;
#}
	if($word=~/avEnA\t/) { # goVppavEnA
		$word=~/(.*)vE(.*)/;
		$word=$1."vi\tunk";
		$word1="E".$2;
	}
	if($word=~/lYlE\t/) { #peVxxavAlYlE
		$word=~/(.*)lYlE(.*)/;
		$word=$1."lYlu\tunk";
		$word1="E".$2;
	}
	if($word=~/ccaMtu\t/) { # gadapavaccaMtu
	$word=~/(.*)ccaMtu(.*)/;
	$word=$1."ccu\tunk";
	$word1="aMtU".$2;
	}
	if($word=~/ccaMtA/) { # nammavaccaMtArA
	$word=~/(.*)ccaMtA(.*)/;
	$word=$1."ccu\tunk";
	$word1="aMtA".$2;
	}
# blocked for testing today
#	if($word=~/inaMxu/) { # gadipinaMxulake
#	$word=~/(.*)ina(.*)/;
#	$word=$1."ina\tunk";
#	$word1="a".$2;
#	}
	if($word=~/leMto\t/) { # guNAleMto
	$word=~/(.*)leMt(.*)/;
	$word=$1."lu\tunk";
	$word1="eMt".$2;
	}

	if($word=~/luMtA/) { # halvAluMtAyi
	$word=~/(.*)luMt(.*)/;
	$word=$1."lu\tunk";
	$word1="uMt".$2;
	}
	if($word=~/kuMtuMtA/) { # anukuMtuMtAM
	$word=~/(.*)tuMt(.*)/;
	$word=$1."tU\tunk";
	$word1="uMt".$2;
	}
	if($word=~/[drml]unna\t/) { # vArunna
	$word=~/(.*)unna(.*)/;
	$word=$1."u\tunk";
	$word1="unna".$2;
	}
	if($word=~/lanna[vx]i\t/) { # peVMcukovAlannaxi
	$word=~/(.*)lanna(.*)/;
	$word=$1."li\tunk";
	$word1="anna".$2;
	}
	if($word=~/lanna\t/) { # kalavAlanna
	$word=~/(.*)lanna(.*)/;
	$word=$1."li\tunk";
	$word1="anna".$2;
	}
#050610
	if($word=~/([A-z])vuMxi/) { # kriwaMnAtivani
	$word=~/(.*)vuMxi(.*)/;
	$word=$1."\tunk";
	$word1="uMxi".$2;
	}
	if($word=~/[aA][xrl]aMtU\t/) {	##cAlaMtU, weVliyanivAraMtU, caliMcakUdaxaMtU, kaluguwuMxaMtunnAru
	$word=~/(.*)aMtU(.*)/;
	$word=$1."u\tunk";
	$word1="aMtU".$2;
	}
	if($word=~/[A-z]xeMtaMte\t/) {	##axeMtaMte
	$word=~/(.*)axeMtaM(.*)/;
	$word=$1."axi\tunk";
	$word1="eMtaM".$2;
	}
	if($word=~/([A-z])llAge\t/) { ##xaMpawullAge
	$word=~/(.*)llAge(.*)/;
	$word=$1."la\tunk";
	$word1="lAge".$2;
	}
	if($word=~/([A-z])maMwati/) { ##xeSamaMwatilo,n         M+aMw
	$word=~/(.*)maMwati(.*)/;
	$word=$1."M\tunk";
	$word1="aMwati".$2;
	}
	if($word=~/([A-z])naMwati/) {##adavinaMwatinI
	$word=~/(.*)naMwati(.*)/;
	$word=$1."ni\tunk";
	$word1="aMwati".$2;
	}
	if($word=~/[xk]emI\t/) {##alAMtixemI, wamakemI
	$word=~/(.*)emI\t(.*)/;
	$word=$1."i\tunk";
	$word1="emI\t".$2;
	}
	if($word=~/([A-z])llAMtivi\t/) {##portullAMtivi
	$word=~/(.*)llAMtivi\t(.*)/;
	$word=$1."lu\tunk";
	$word1="lAMtivi\t".$2;
	}
	if($word=~/([A-z])ulOu\t/) {##vimukwulOu
	$word=~/(.*)lOu(.*)/;
	$word=$1."lu\tunk";
	$word1="avvu".$2;
	}
#xaMpawullAge,adv        la+lAge
#xeSamaMwatilo,n         M+aMwati
	if($word=~/([A-z])EunnA([dnmvry])u\t/) { # kriwaMnAtivani
	$word=~/(.*)EunnA(.*)/;
	$word=$1."E\tunk";
	$word1="unnA".$2;
	}
	if($word=~/[A-z]vunnA([dnmvry])u\t/) { # kriwaMnAtivani
	$word=~/(.*)vunnA(.*)/;
	$word=$1."\tunk";
	$word1="unnA".$2;
	}
#060610

#	if($word=~/\tcAlaMtunnA[dnmr]u\t/) { # cAlaMtunnAru
#	$word=~/(.*)cAla(.*)/;
#	$word=$1."u\tunk";
#	$word1="a".$2;
#	}

	#if($word=~/[A-z]gAceVpp.*aMtun/) { # ixamixXaMgAceVppalemaMtunnAru
	#$word=~/(.*)gAceVpp(.*)aMtun(.*)/;
	#$word=$1."gA\tunk";
	#$word1="ceVpp"."$2\tunk";
	#$word2="aMtun".$3;
	#}
	if($word=~/^pUjalaMxukuMtunnA[dnmr]u\t/) { # pUjalaMxukuMtunnAdu
	$word=~/(.*)pUjalaM(.*)/;
	$word=$1."pUjalu\tunk";
	$word1="aM".$2;
	}
### becoz aMtunnAdu => *aMtu+unnAdu
	#if($word=~/[A-z][u]MtunnA[dnmr]u\t/) { # jarupukuMtunnAru
	#$word=~/(.*)unnA(.*)/;
	#$word=$1."U\tunk";
	#$word1="unnA".$2;
	#}
	if($word=~/([A-z])uMxaMtunnA[dnmr]u\t/) { # kaluguwuMxaMtunnAru
	$word=~/(.*)aMtunn(.*)/;
	$word=$1."i\tunk";
	$word1="aMtunn".$2;
	}
	if($word=~/[aeouAEIOUM][x][a]MtunnA[dnmr]u\t/) { # caliMcakUdaxaMtunnAru, cAlaMtunnAru, *maMcixaMtunnAru
	$word=~/(.*)aMtunn(.*)/;
	$word=$1."u\tunk";
	$word1="aMtunn".$2;
	}

#	if($word=~/[A-z]wunnA[dnmr]u\t/) { # ceswunnAru 
#	$word=~/(.*)unnA(.*)/;
#	$word=$1."U\tunk";
#	$word1="unnA".$2;
#	}
	if($word=~/[^vlktwn]unnA([dnmvry])u\t/) { # wamilYulunnAru, *cesukunnAru, *aMtunnAru
	$word=~/(.*)unnA(.*)/;
	$word=$1."u\tunk";
	$word1="unnA".$2;
	}
	#020712#if($word=~/anunnA([dnmvry])u\t/) { # nirmiMcanunnAru
	#$word=~/(.*)anunnA(.*)/;
	#$word=$1."an\tunk";
	#$word1="unnA".$2;
	#}
	#020712#if($word=~/anunna\t/) { # jaruganunna
	#$word=~/(.*)anunna(.*)/;
	#$word=$1."a\tunk";
	#$word1="unna".$2;
	#}
	#020712#if($word=~/agala[mdxrn]/) {  	## sAXiMcagalaru, prAraMBiMcagalamani
	#$word=~/(.*)agala(.*)/;
	#$word=$1."a\tunk";
	#$word1="gala".$2;
	#}
	#if($word=~/([dnvrm])ani\t/)  # wArani, puttalexani,viXAnamani
	##if($word=~/([dnvr])ani\t/)  # wArani, puttalexani,viXAnamani, *bahumani, 
#020712	if($word=~/[^ev]([v])ani\t/) { # wArani,*poVrani=poVra+ni puttalexani,viXAnamani, *bahumani, *wanani => wanYnYE, *cUdani, *uMdevani, *ivvani
#	$word=~/(.*)ani(.*)/;
#	$word=$1."u\tunk";
#	$word1="ani".$2;
#	}
	if($word=~/([A-z])kkumani\t/) { # curukkumani
	$word=~/(.*)umani(.*)/;
	$word=$1."u\tunk";
	$word1="ani".$2;
	}
#020712	if($word=~/alemu\t/) {  	## ceVppalemu
#	$word=~/(.*)alemu(.*)/;
#	$word=$1."a\tunk";
#	$word1="lemu".$2;
#	}
#020712	if($word=~/alemani\t/) { # sAXiMcalemani	
#	$word=~/(.*)alemani(.*)/;
#	$word=$1."a\tunk";
#	$word1="lemu\tunk";
#	$word2="ani".$2;
#	}
	if($word=~/([l])unnatlu\t/) { #jalavanarulunnatlu
	$word=~/(.*)unnatlu(.*)/;
	$word=$1."u\tunk";
	$word1="unnatlu".$2;
	}
#020712	if($word=~/([dnr])anI\t/) { # unnAranI, 
#	$word=~/(.*)anI(.*)/;
#	$word=$1."u\tunk";
#	$word1="anI".$2;
#	}
	if($word=~/([v])anI\t/) { #  kanipiMcevanI, **bahumanI
	$word=~/(.*)anI(.*)/;
	$word=$1."i\tunk";
	$word1="anI".$2;
	}
#020712#	if($word=~/Ayani\t/) { #wagguwAyani
	#$word=~/(.*)yani(.*)/;
	#$word=$1."yi\tunk";
	#$word1="ani".$2;
	#}
	if($word=~/[A-z]munnaxi\t/) { # unnaxi
	$word=~/(.*)munn(.*)/;
	$word=$1."M\tunk";
	$word1="unn".$2;
	}
#xaMpawullAge,adv        la+lAge
#xeSamaMwatilo,n         M+aMwati
	if($word=~/[A-z]awyaMwa\t/) { # nagarAlaloawyaMwa
	$word=~/(.*)awyaMwa(.*)/;
	$word=$1."\tunk";
	$word1="awyaMwa".$2;
	}
	if($word=~/[A-z]lenaMwa\t/) { # UhiMcalenaMwa, *wanaMwa	unk* winnaMwa modified by gurao24092012
	$word=~/(.*)lenaMwa(.*)/;
	$word=$1."ni\tunk";
	$word1="aMwa".$2;
	}
	if($word=~/[A-z]inaMwa\t/) { # UhiMcalenaMwa, *wanaMwa	unk* winnaMwa included by gurao24092012
	$word=~/(.*)inaMwa(.*)/;
	$word=$1."ina\tunk";
	$word1="aMwa".$2;
	}
	if($word=~/[A-z]amiswAyi\t/) { # svAgawamiswAyi
	$word=~/(.*)amiswAyi(.*)/;
	$word=$1."aM\tunk";
	$word1="iswAyi".$2;
	}
#070610
#
	if($word=~/([A-z])amicc/) { # aMkiwamiccAdu, samAXAnamiccinatlu
	$word=~/(.*)amicc(.*)/;
	$word=$1."aM\tunk";
	$word1="icc".$2;
	}
	if($word=~/([A-z])MxaMte\t/) { #"axemitaMte, vacciMxaMte
	$word=~/(.*)MxaMte(.*)/;
	$word=$1."Mxi\tunk";
	$word1="aMte".$2;
	}
	if($word=~/([A-z])kkuvane\t/) { #wakkuvane
	$word=~/(.*)ane(.*)/;
	$word=$1."a\tunk";
	$word1="ane".$2;
	}
#	if($word=~/[mvr]ane\t/) { #vacciMxane, vyakwiwvamanexi, *uMdane, *
	#$word=~/(.*)ane(.*)/;
	#$word=$1."u\tunk";
	#$word1="ane".$2;
	#}
	if($word=~/[A-z][A-z][A-z][yx]ane\t/) { #vaccAyane, *Ayane
	$word=~/(.*)ane(.*)/;
	$word=$1."i\tunk";
	$word1="ane".$2;
	}
	if($word=~/[A-z][A-z][A-z][dnmvr]ane[xv]i\t/) { #vyakwiwvamanexi
	$word=~/(.*)ane(.*)/;
	$word=$1."u\tunk";
	$word1="ane".$2;
	}
	if($word=~/\tI[pn]a/) { #IpattaNAniki, InagaraMlo
	$word=~/(.*)I(.*)/;
	$word=$1."\tunk";
	$word1=$2;
	}
	if($word=~/[A-z]amEnAgAni\t/) { #nagaramEnAgAni
	$word=~/(.*)amEnAgAni(.*)/;
	$word=$1."aM\tunk";
	$word1=$2;
	}
	if($word=~/[A-z]paraMgA\t/) { #nagaramEnAgAni
	$word=~/(.*)paraMgA(.*)/;
	$word=$1."\tunk";
	$word1="paraMgA".$2;
	}
	if($word=~/[A-z]lanodiMcA[dnmvry]u\t/) { #rAjulanodiMcAdu
	$word=~/(.*)lanodiM(.*)/;
	$word=$1."lanu\tunk";
	$word1="odiM".$2;
	}
	if($word=~/[^m]aMwatA\t/) { #rAjulanodiMcAdu
	$word=~/(.*)aMwatA(.*)/;
	$word=$1."\tunk";
	$word1="aMwatA".$2;
	}
	if($word=~/([A-z])amaMwatA\t/) { #rAjulanodiMcAdu
	$word=~/(.*)amaMwatA(.*)/;
	$word=$1."aM\tunk";
	$word1="aMwatA".$2;
	}

	if($word=~/[A-z]xoVkkate\t/) { #rAjulanodiMcAdu
	$word=~/(.*)xoVkka(.*)/;
	$word=$1."xi\tunk";
	$word1="oVkka".$2;
	}
	if($word=~/([A-z])aMnuMdI\t/) { #rAjulanodiMcAdu
	$word=~/(.*)aMnuMdI(.*)/;
	$word=$1."aM\tunk";
	$word1="nuMdI".$2;
	}
	if($word=~/uMdaraMte\t/) { #uMdaraMte #20/12/2010
	$word=~/(.*)raMte(.*)/;
	$word=$1."ru\tunk";
	$word1="aMte".$2;
	}

#ixoVkkate
#080610
	if($word=~/ArXaM\t/) { #rakRaNArXaM
	$word=~s/ArXaM/ArWaM/; 
	}
	if($word=~/xaggaralone\t/) { #rakRaNArXaM
	$word=~s/xaggara/xaggiri/; 
	}
	if($word=~/lexuta\t/) { #convert lexuta > lexata
	$word=~s/lexuta/lexata/; 
	}
#91213
#	if($word=~/ayinapudu/) { #ayinapudu
#	$word=~s/inapudu/inappudu/; 
#	}
#blocked to check prAraMBamE - krrd, chris,nag-240714
#	if($word=~/amE\t/) { #rAjulanodiMcAdu
#	$word=~/(.*)amE\t(.*)/;
#	$word=$1."aM\tunk";
#	$word1="ayyi\t".$2;
#	}
	if($word=~/lexuta\t/) { #lexuta > lexu, aMta
        $word=~/(.*)lexuta\t(.*)/;
        $word=$1."lexu\tunk";
        $word1="aMta\t".$2;
        }
	if($word=~/lexata\t/) { #lexata > lexu, aMta
        $word=~/(.*)lexata\t(.*)/;
        $word=$1."lexu\tunk";
        $word1="aMta\t".$2;
        }

	#if($word=~/[^ ]\.\.\t/) { #harinA.... n2 diff lines..
	#$word=~/(.*)([A-z])\.\.(.*)/;
	#$word=$1.$2."\tunk";
	#$word1="\.\.".$3;
	#}

	
	#if($word=~/\.\.\t/ { #XXXX....XXXX n2 diff lines..
	#$word=~/(.*)([A-z])\.\.(.*)/;
	#$word=$1.$2."\tunk";
	#$word1="\.\.".$3;
	#}
	if($word=~/^kanpis/) {  ## kanpiswAyi
	$word=~s/kanpi/kanipi/;
	}
	if($word=~/peVduwAyi\t/) {  ## kanpiswAyi
	$word=~s/peVduwAyi/peVdawAyi/;
	}
	if($word=~/[^I]rulni\t/) {  ##  vanarulni => vanarlanu, *yuxXavIrulni
	$word=~s/ulni/lani/;
	}
	if($word=~/([^l])evani\t/) { #vaccevani 210111
	$word=~/(.*)vani\t(.*)/;
	$word=$1."vi\tunk";
	$word1="ani\t".$2;
	}
	if($word=~/^levani\t/) { #levani 210111
	$word=~/(.*)vani\t(.*)/;
	$word=$1."vu\tunk";
	$word1="ani\t".$2;
	}
	if($word=~/[rd]eVvarU\t/) { #vAreVvarU
	$word=~/(.*)eVvarU\t(.*)/;
	$word=$1."u\tunk";
	$word1="eVvarU\t".$2;
	}
	if($word=~/[A-z]gannamAta\t/) { #alAgannamAta
	$word=~/(.*)gannamAta(.*)/;
	$word=$1."ga\tunk";
	$word1="annamAta".$2;
	}
	if($word=~/([A-z])amaMxi\t/) {	##anekamaMxi
	$word=~/(.*)amaMxi(.*)/;
	$word=$1."a\tunk";
	$word1="maMxi".$2;
	}
	if($word=~/([A-z])AlanipiM/) {	##cUdAlanipiMce
	$word=~/(.*)AlanipiM(.*)/;
	$word=$1."Ali\tunk";
	$word1="anipiM".$2;
	}
	if($word=~/([A-z])AlannA\t/) {	##cUdAlannnA
	$word=~/(.*)AlannA(.*)/;
	$word=$1."Ali\tunk";
	$word1="annA".$2;
	}	
	if($word=~/^emaMtA/) {	##emaMtAru
	$word=~/(.*)emaMtA(.*)/;
	$word=$1."emi\tunk";
	$word1="aMtA".$2;
	}	
	if($word=~/eVlAgaMte\t/) {	##eVlAgaMte
	$word=~/(.*)gaMte(.*)/;
	$word=$1."ga\tunk";
	$word1="aMte".$2;
	}	
	#if($word=~/deVppudu/) {  	## eVppudeVppudu
#	$word=~/(.*)deVppudu(.*)/;
#	$word=$1."du\tunk";
#	$word1="eVppudu".$2;
#	}
	if($word=~/[dmr]ayiwe\t/) {  	## koVMxarayiwe
	$word=~/(.*)ayiwe(.*)/;
	$word=$1."u\tunk";
	$word1="ayiwe".$2;
	}
	if($word=~/([A-z]+)gAn[iI]\t/) {  	## lAMtivigAnI
	$word=~/(.*)gAn(.*)/;
	$word=$1."\tunk";
	$word1="gAn".$2;
	}
	if($word=~/lexugAn[iI]/) {  	## lexugAnI
	$word=~/(.*)lexugA(.*)/;
	$word=$1."lexu\tunk";
	$word1="gA".$2;
	}
#	if($word=~/[oa]leni\t/) {  	## maruvaleni, werukoleni, 210211-BLOCKED becoz double splitting is needed here UhiMcalenaMwa 
#	$word=~/(.*)leni\t(.*)/;
#	$word=$1."\tunk";
#	$word1="leni\t".$2;
#	}
	if($word=~/[i]lenivA([rdlY]+)u/) {  	## AsakwilenivAru
	$word=~/(.*)lenivA(.*)/;
	$word=$1."\tunk";
	$word1="lenivA".$2;
	}
	if($word=~/vArikunna\t/) {  	## vArikunna, but not imudcukunna
	$word=~/(.*)kunna\t(.*)/;
	$word=$1."ki\tunk";
	$word1="unna\t".$2;
	}
	if($word=~/([A-z])atemiti\t/) {  	## oVkkatemiti
	$word=~/(.*)atemiti\t(.*)/;
	$word=$1."ati\tunk";
	$word1="emiti\t".$2;
	}
	if($word=~/mAtemiti\t/) {  	## mAtemiti
	$word=~/(.*)Atemiti\t(.*)/;
	$word=$1."Ata\tunk";
	$word1="emiti\t".$2;
	}
	if($word=~/iMkeVMxuk/) {  	## iMkeVMxuku
	$word=~/(.*)iMkeVMxuk(.*)/;
	$word=$1."iMkA\tunk";
	$word1="eVMxuk".$2;
	}
	if($word=~/xaggaruM/) {  	## xaggaruMde
	$word=~/(.*)xaggaruM(.*)/;
	$word=$1."xaggara\tunk";
	$word1="uM".$2;
	}

	if($word=~/([A-z]+)patla\t/) {  	## viRayAlapatla
	$word=~/(.*)patla(.*)/;
	$word=$1."\tunk";
	$word1="patla".$2;
	}
	if($word=~/nilucuMte\t/) {  	## nilucuMte ==> nilicuMte
	$word=~s/nilucu/nilicu/;
	}
	if($word=~/waxiwawara/) {  	## waxiwawara
	$word=~s/waxiwawara/waxiwara/;
	}
	if($word=~/([A-z])lalonu\t/) {  	## 3       aMculalonu      unk     <fs af='aMculalonu,unk,,,,,,'>
	$word=~s/lalonu/laloni/;
	}
	if($word=~/^muKaputaM([A-z]+)/) {  	## muKaputaM
	$word=~s/muKaputaM/muKaputa/;
	}
	if($word=~/లకు\t/) {  	## 500లకు
	$word=~s/లకు/laku/;
	}
	if($word=~/([A-z])isArilAne\t/) {  	## prawisArilAne
	$word=~/(.*)isArilAne(.*)/;
	$word=$1."i\tunk";
	$word1="sArilAne".$2;
	}
	if($word=~/([A-z])udoVkaru\t/) {  	## nAvikudoVkaru
	$word=~/(.*)udoVkaru(.*)/;
	$word=$1."udu\tunk";
	$word1="oVkaru".$2;
	}
=head because gurrayyAru should not be split
	if($word=~/([A-z]+)ayyA[rmvdn]u\t/) {  	## gallaMwayyAru
	$word=~/(.*)ayyA(.*)/;
	$word=$1."u\tunk";
	$word1="ayyA".$2;
	}
=cut
	if($word=~/([A-z]+)muMxi\t/) {  	## pramAxamuMxi
	$word=~/(.*)muMxi(.*)/;
	$word=$1."M\tunk";
	$word1="uMxi".$2;
	}

	if($word=~/([A-z]+)amEMxi\t/) {  	## apramawwamEMxi
	$word=~/(.*)amEMxi(.*)/;
	$word=$1."aM\tunk";
	$word1="EMxi".$2;
	}
#020712	if($word=~/([A-z]+)abaddAyi\t/) {  	## prAraMBiMcabaddAyi
#	$word=~/(.*)abaddAyi(.*)/;
#	$word=$1."a\tunk";
#	$word1="baddAyi".$2;
#	}
#020712	if($word=~/([A-z]+)abaddA([rmnvd])u\t/) {  	## prAraMBiMcabaddAyi
#	$word=~/(.*)abaddA(.*)/;
#	$word=$1."a\tunk";
#	$word1="baddA".$2;
#	}
	if($word=~/([A-z])kovavalasi/) {  	## cerukovavalasiMxe
	$word=~s/kovava/kova/g;
	}
	if($word=~/vItanniMtinI\t/) {  	## vItanniMtinI
	$word=~/(.*)vItanni(.*)/;
	$word=$1."vIti\tunk";
	$word1="anni".$2;
	}
	if($word=~/^vAlYloVs/) {  	## vAlYloVswe
	$word=~/(.*)vAlYloVs(.*)/;
	$word=$1."vAlYlu\tunk";
	$word1="voVs".$2;
	}
	#if($word=~/pilavabade\t/) {  	## pilavabade
	#$word=~/(.*)pilavabade(.*)/;
	#$word=$1."pilava\tunk";
	#$word1="bade".$2;
	#}
#	if($word=~/([A-z]+)ukuneru\t/) {  	## anukuneru
#	$word=~s/kuneru/koneru/g;
#	}
	if($word=~/tn[ui]Mc[iI]\t/) {  	## xaggarnuMci 
	$word=~s/tn[ui]Mc/tinuMc/g;
	}
	if($word=~/rn[ui]Mc[iI]\t/) {  	## xaggarnuMci 
	$word=~s/rn[ui]Mc/ranuMc/g;
	}

	##if($word=~/([A-z]+)n([ui])M([cd])([IUAeo])\t/)   	## elYlanuMci 17112012gurao
	if($word=~/([adeiouAEIOUV]+])n([ui])M([cd])([IUAeo])\t/) {  	## elYlanuMci 17112012gurao #Paramesh_020313 changed [A-z] to vowels becoz it affects words like ikkadnuMcI
	$inn=$word;
	$inn=~/(.*)n[ui]M[cd]([IUeAo])(.*)/g;
	$word=$1."\tunk";
	$word1="nuMd".$2.$3;
	}
	if($word=~/([iaV])kkadn([ui])M([cd])([IUAeo])\t/) {  	## elYlanuMci 17112012gurao #Paramesh_020313 changed [A-z] to vowels becoz it affects words like ikkadnuMcI
	#if($word=~/ikkadnuMdI\t/) {  	## elYlanuMci 17112012gurao #Paramesh_020313 changed [A-z] to vowels becoz it affects words like ikkadnuMcI
	$inn=$word;
	$inn=~/(.*)n[ui]M[cd]([IUeAo])(.*)/g;
	$word=$1."i\tunk";
	$word1="nuMd".$2.$3;
	}
#	if($word=~/n[ui]Mc[AIeoiIE]\t/) {  	## elYlanuMci 
#	$word=~/(.*)n[ui]Mc(.*)/g;
#	$word=$1."\tunk";
#	$word1="niMc".$2;
#	}

	if($word=~/([A-z])wonna\t/) {  	## AkarRiswonna
	$word=~/(.*)wonna(.*)/;
	$word=$1."wU\tunk";
	$word1="unna".$2;
	}
	if($word=~/([A-z])nnenu\t/) {  	## annAnnenu
	$word=~/(.*)nnenu(.*)/;
	$word=$1."nu\tunk";
	$word1="nenu".$2;
	}
	if($word=~/([A-z])Asare\t/) {  	## unnAsare
	$word=~/(.*)Asare(.*)/;
	$word=$1."A\tunk";
	$word1="sare".$2;
	}
	if($word=~/([A-z])xavadAni/) {  	## woVmmixavadAniki
	$word=~/(.*)xavadAni(.*)/;
	$word=$1."xi\tunk";
	$word1="avadAni".$2;
	}
#	if($word=~/([A-z]*)AnaMwaraM\t/) {  	## add in pc_data:: yAwrAnaMwaraM
#	$word=~/(.*)AnaMwaraM(.*)/;
#	$word=$1."a\tunk";
#	$word1="waruvAwa".$2;
#	}
#	if($word=~/([A-z]*)AnaMwara\t/) {  	## add in pc_data:: yAwrAnaMwaraM
#	$word=~/(.*)AnaMwara(.*)/;
#	$word=$1."a\tunk";
#	$word1="waruvAwa".$2;
#	}
	if($word=~/([A-z]+)tlayyiMxi\t/) {  	## padinatlayyiMxi
	$word=~/(.*)tlayyiMxi(.*)/;
	$word=$1."tlu\tunk";
	$word1="ayyiMxi".$2;
	}
	if($word=~/([A-z]+) mayy[AeioUI]\t/) {  	## prAraMBa mayyiMxi
	$word=~/(.*) mayy[AeioUI](.*)/;
	$word=$1."M\tunk";
	$word1="ayy".$2;
	}
	if($word=~/([A-z])aMkaMte\t/) {  	## saMpraxAyaMkaMte
	$word=~/(.*)aMkaMte(.*)/;
	$word=$1."aM\tunk";
	$word1="kaMte".$2;
	}
	if($word=~/([A-z])AraMte\t/) {  	## waralivaswuMtAraMte
	$word=~/(.*)AraMte(.*)/;
	$word=$1."Aru\tunk";
	$word1="aMte".$2;
	}
	if($word=~/^bAlevu\t/) {  	## bAlevu
	$word=~/(.*)bAlevu(.*)/;
	$word=$1."bAgA\tunk";
	$word1="levu".$2;
	}
	if($word=~/^anukuMdagA\t/) {  	## anukuMdagA
	$word=~/(.*)anukuMdagA(.*)/;
	$word=$1."anukoVni\tunk";
	$word1="uMdagA".$2;
	}
#	if($word=~/n[ui]Mc[AIeoiIE]\t/) {  	## elYlanuMci 
#	$word=~/(.*)n[ui]Mc(.*)/g;
#	$word=$1."\tunk";
#	$word1="niMc".$2;
#	}

	if($word=~/([A-z])wonna\t/) {  	## AkarRiswonna
	$word=~/(.*)wonna(.*)/;
	$word=$1."wU\tunk";
	$word1="unna".$2;
	}
	if($word=~/([A-z])nnenu\t/) {  	## annAnnenu
	$word=~/(.*)nnenu(.*)/;
	$word=$1."nu\tunk";
	$word1="nenu".$2;
	}
	if($word=~/([A-z])Asare\t/) {  	## unnAsare
	$word=~/(.*)Asare(.*)/;
	$word=$1."A\tunk";
	$word1="sare".$2;
	}
	if($word=~/([A-z])xavadAni/) {  	## woVmmixavadAniki
	$word=~/(.*)xavadAni(.*)/;
	$word=$1."xi\tunk";
	$word1="avadAni".$2;
	}
#	if($word=~/([A-z])AnaMwaraM\t/) {  	## add in pc_data:: yAwrAnaMwaraM
#	$word=~/(.*)AnaMwaraM(.*)/;
#	$word=$1."a\tunk";
#	$word1="waruvAwa".$2;
#	}
	if($word=~/([A-z]+)tlayyiMxi\t/) {  	## padinatlayyiMxi
	$word=~/(.*)tlayyiMxi(.*)/;
	$word=$1."tlu\tunk";
	$word1="ayyiMxi".$2;
	}
	if($word=~/([A-z]+) mayy[AeioUI]\t/) {  	## prAraMBa mayyiMxi
	$word=~/(.*) mayy[AeioUI](.*)/;
	$word=$1."M\tunk";
	$word1="ayy".$2;
	}
	if($word=~/([A-z])aMkaMte\t/) {  	## saMpraxAyaMkaMte
	$word=~/(.*)aMkaMte(.*)/;
	$word=$1."aM\tunk";
	$word1="kaMte".$2;
	}
	if($word=~/([A-z])AraMte\t/) {  	## waralivaswuMtAraMte
	$word=~/(.*)AraMte(.*)/;
	$word=$1."Aru\tunk";
	$word1="aMte".$2;
	}
	if($word=~/^bAlevu\t/) {  	## bAlevu
	$word=~/(.*)bAlevu(.*)/;
	$word=$1."bAgA\tunk";
	$word1="levu".$2;
	}
	if($word=~/^anukuMdagA\t/) {  	## anukuMdagA
	$word=~/(.*)anukuMdagA(.*)/;
	$word=$1."anukoVni\tunk";
	$word1="uMdagA".$2;
	}
	if($word=~/^nAkemo\t/) {  	##nAkemo
	$word=~/(.*)nAkemo(.*)/;
	$word=$1."nAku\tunk";
	$word1="emo".$2;
	}
	if($word=~/[Ar][kr]eVMxuk/) {  	##nAkeVMxuko, mIreVMxuku
	$word=~/(.*)[Ar][kr]eVMxuk(.*)/;
	$word=$1."u\tunk";
	$word1="eVMxuk".$2;
	}
	if($word=~/^nIko\t/) {  	##nIko viRayam ceVppanA? nIku+oVka
	$word=~/(.*)nIko(.*)/;
	$word=$1."nIku\tunk";
	$word1="oVka".$2;
	}
	if($word=~/^anukuMdagA\t/) {  	##anukuMdagA
	$word=~/(.*)anukuMdagA(.*)/;
	$word=$1."anukoVni\tunk";
	$word1="uMdagA".$2;
	}
	if($word=~/([A-z]+)arAni\t/) {  	## BariMcarAni gurao29092012 
	$word=~/(.*)arAni(.*)/;
	$word=$1."a\tunk";
	$word1="rAni".$2;
	}
# vItanniMtinI, cerukovavalasiMxe
#if($word=~/moVxatisArigA/) {  	## moVttamoVxatisArigA
#$word=~/(.*)moVxatisArigA(.*)/;
#$word=$1."moVxati\tunk";
#$word1="sArigA".$2;
#}
	if($word=~/^v([AI])rixxar/) {  	##  vArixxari gurao06032013
	$word=~/(.*)v([AI])rixxar(.*)/;
	$word=$1."v$2ru\tunk";
	$word1="ixxar".$3;
	}
	if($word=~/^manixxar/) {  	##  manixxarikI
	$word=~/(.*)manixxar(.*)/;
	$word=$1."mana\tunk";
	$word1="ixxar".$2;
	}
	if($word=~/^nuvveMti/) {  	##  nuvveMti
	$word=~/(.*)nuvveMti(.*)/;
	$word=$1."nuvvu\tunk";
	$word1="eMti".$2;
	}
	if($word=~/^rAsuMt/) {  	##  rAsuMtAdu
	$word=~/(.*)rAsuMt(.*)/;
	$word=$1."rAsi\tunk";
	$word1="uMt".$2;
	}
	if($word=~/^anukuMdagA/) {  	##  anukuMdagA
	$word=~/(.*)anukuMdagA(.*)/;
	$word=$1."anukoVni\tunk";
	$word1="uMdagA".$2;
	}
	if($word=~/^vAlYlalAge/) {  	##  vAlYlalAge
	$word=~/(.*)vAlYlalAge(.*)/;
	$word=$1."vAlYla\tunk";
	$word1="lAge".$2;
	}
	if($word=~/^vallanemo/) {  	##  vallanemo
	$word=~/(.*)vallanemo(.*)/;
	$word=$1."valla\tunk";
	$word1="emo".$2;
	}
	if($word=~/([A-z])AlsirAva/) {  	##  caxavAlsirAvataMwo
	$word=~/(.*)AlsirAva(.*)/;
	$word=$1."Alsi\tunk";
	$word1="rAva".$2;
	}
	if($word=~/ayyAvaMta/) {  	##  ayyAvaMta
	$word=~/(.*)ayyAvaMta(.*)/;
	$word=$1."ayyAvu\tunk";
	$word1="aMta".$2;
	}
	if($word=~/^eVvaranuk/) {  	##  eVvaranukunnaxi
	$word=~/(.*)eVvaranuk(.*)/;
	$word=$1."eVvaru\tunk";
	$word1="anuk".$2;
	}
	if($word=~/([A-z])kolenann/) {  	## waleVwwukolenannAdu
	$word=~/(.*)lenann(.*)/;
	$word=$1."lenu\tunk";
	$word1="ann".$2;
	}
	#if($word=~/([A-z])annA(.*)/) {  	## awadannAdu
	#$word=~/(.*)annA(.*)/;
	#$word=$1."u\tunk";
	#$word1="annA".$2;
	#}
	if($word=~/([A-z])vukaxA\t/) {  	## annAvukaxA
	$word=~/(.*)vukaxA(.*)/;
	$word=$1."vu\tunk";
	$word1="kaxA".$2;
	}
	if($word=~/^parlexan/) {  	## parlexannAdu
	$word=~/(.*)parlexan(.*)/;
	$word=$1."parlexu\tunk";
	$word1="an".$2;
	}
	if($word=~/([A-z])laMxaraM\t/) {  	## snehiwulaMxaraM
	$word=~/(.*)laMxaraM(.*)/;
	$word=$1."la\tunk";
	$word1="aMxaraM".$2;
	}
	if($word=~/([A-z])attanipiM/) {  	## 'rAsinattanipiMcixirA
	$word=~/(.*)attanipiM(.*)/;
	$word=$1."attu\tunk";
	$word1="anipiM".$2;
	}
	if($word=~/^neneVpp/) {  	## neneVppudU
	$word=~/(.*)neneVpp(.*)/;
	$word=$1."nenu\tunk";
	$word1="eVpp".$2;
	}
	if($word=~/^nenanna/) {  	## nenannattugAne
	$word=~/(.*)nenanna(.*)/;
	$word=$1."nenu\tunk";
	$word1="anna".$2;
	}
	if($word=~/([A-z]+)naMwe\t/) {  	## caxivAnaMwe
	$word=~/(.*)naMwe(.*)/;
	$word=$1."nu\tunk";
	$word1="aMwe".$2;
	}
	#if($word=~/([A-z]+)BARa/) {  	##vAlYlaBARaku etc gurao29092012 
	#$word=~/(.*)BARa(.*)/;
	#$word=$1."\tunk";
	#$word1="BARa".$2;
	#}
	if($word=~/([aeiouAEIOUV]+)uMx([A-z]+)/) {  	##cariwrauMxi etc gurao29092012 
	$word=~/(.*)uMx(.*)/;
	$word=$1."\tunk";
	$word1="uMx".$2;
	}
	if($word=~/([A-z]+)vuMx([A-z]+)/) {  	##cariwrauMxi etc gurao29092012 
	$word=~/(.*)vuMx(.*)/;
	$word=$1."\tunk";
	$word1="uMx".$2;
	}
	#if($word=~/([A-z]+)uMde([A-z]+)/) {  	##cariwrauMdexi etc gurao29092012 
	#$word=~/(.*)([^aAiIuUeEoO])uMde(.*)/;
	#$word=$1.$2"\tunk";
	#$word1="uMde".$2;
	#}
	if($word=~/([A-z]+)kolpo/) {  	##spqhakolpoyAdu etc gurao29092012 
	$word=~/(.*)kolpo(.*)/;
	$word=$1."\tunk";
	$word1="kolpo".$2;
	}
	if($word=~/([A-z])xayyiM/) {  	## eVnimixayyiMxi
	$word=~/(.*)xayyiM(.*)/;
	$word=$1."xi\tunk";
	$word1="ayyiM".$2;
	}
	if($word=~/weVlInattu/) {  	## weVlInattu
	$word=~/(.*)weVlInattu(.*)/;
	$word=$1."weVliyani\tunk";
	$word1="atlu".$2;
	}
	if($word=~/([A-z])raMtAr[Aeou]\t/) {  	## rAsAraMtAru , eVvaraMtArA
	$word=~/(.*)raMtAr(.*)/;
	$word=$1."ru\tunk";
	$word1="aMtAr".$2;
	}
	if($word=~/([A-z])sepayyAka\t/) {  	## kAsepayyAka
	$word=~/(.*)sepayyA(.*)/;
	$word=$1."sepu\tunk";
	$word1="ayyA".$2;
	}
	if($word=~/ceswAdanuko/) {  	## ceswAdanukolexu
	$word=~/(.*)ceswAdanuko(.*)/;
	$word=$1."ceswAdu\tunk";
	$word1="anuko".$2;
	}
	if($word=~/BujAlakeVw/) {  	## BujAlakeVwwukuni
	$word=~/(.*)lakeVw(.*)/;
	$word=$1."laku\tunk";
	$word1="eVw".$2;
	}
##	if($word=~/abowe\t/) {  	## xiMcabowe; This is written 4 timebeing becoz it is not wrking in new morph.
##	$word=~/(.*)abowe(.*)/;
##	$word=$1."a\tunk";
##	$word1="powe".$2;
##	}
###	if($word=~/uMtArani\t/)   	## To change the pos tagger=>jIviswuMtArani	NN
	#if($word=~/uMtArani\t/) {  	## wIsukokapovadaMwo
	#$word=~/(.*)uMtArani(.*)/;
	#$word=$1."uMtAru\tunk";
	#$word1="ani".$2;
	#}
#	if($word=~/kokapovadaM/) {  	## wIsukokapovadaMwo
#	$word=~/(.*)kokapovadaM(.*)/;
#	$word=$1."koka\tunk";
#	$word1="povadaM".$2;
#	}
	if($word=~/([A-z])nattunnA/) {  	## ceswunnattunnAru
	$word=~/(.*)nattunnA(.*)/;
	$word=$1."nattu\tunk";
	$word1="unnA".$2;
	}
#	if($word=~/kogalugu/) {  	## pariRkariMcukogaluguwAro
#	$word=~/(.*)kogalugu(.*)/;
#	$word=$1."ko\tunk";
#	$word1="galugu".$2;
#	}
	if($word=~/([A-z])vAlsivuM/) {  	## wIsukurAvAlsivuMtuMxi
	$word=~/(.*)vAlsivuM(.*)/;
	$word=$1."valasi\tunk";
	$word1="uM".$2;
	}
	if($word=~/^adugidu/) {  	## adugiduwoMxi
	$word=~/(.*)adugidu(.*)/;
	$word=$1."adugu\tunk";
	$word1="peVdu".$2;
	}
	if($word=~/([A-z])rAlaMxiMc/) {  	## sahakArAlaMxiMcina
	$word=~/(.*)rAlaMxiMc(.*)/;
	$word=$1."rAlu\tunk";
	$word1="aMxiMc".$2;
	}
#	if($word=~/([A-z])alekapo/) {  	## rAyalekapoyAnu, nammalekapoyAnu
#	$word=~/(.*)alekapo(.*)/;
#	$word=$1."a\tunk";
#	$word1="lekapo".$2;
#	}
	if($word=~/koVxavemi/) {  	## koVxavemi
	$word=~/(.*)koVxavemi(.*)/;
	$word=$1."koVxava\tunk";
	$word1="emi".$2;
	}
	if($word=~/([A-z])aMlexu\t/) {  	## lABaMlexu
	$word=~/(.*)aMlexu(.*)/;
	$word=$1."aM\tunk";
	$word1="lexu".$2;
	}
	if($word=~/lYlixxaru\t/) {  	## vIlYlixxaru
	$word=~/(.*)lYlixx(.*)/;
	$word=$1."lYlu\tunk";
	$word1="ixx".$2;
	}
	if($word=~/^ArneVllu/) {  	## ArneVllugA
	$word=~/(.*)ArneVllu(.*)/;
	$word=$1."Aru\tunk";
	$word1="neVlalu".$2;
	}
	if($word=~/([A-z])exilexu\t/) {  	## iccexilexu
	$word=~/(.*)exilexu(.*)/;
	$word=$1."exi\tunk";
	$word1="lexu".$2;
	}
	if($word=~/([A-z])ivalle\t/) {  	## nItivalle
	$word=~/(.*)ivalle(.*)/;
	$word=$1."i\tunk";
	$word1="valle".$2;
	}
#020712	if($word=~/AdamannA/) {  	## mAtlAdamannAru
#	$word=~/(.*)AdamannA(.*)/;
#	$word=$1."Ada\tunk";
#	$word1="annA".$2;
#	}
	if($word=~/([A-z])wenunnatlu/) {  	## wenunnatlu
	$word=~/(.*)wenunnatlu(.*)/;
	$word=$1."wen\tunk";
	$word1="unnatlu".$2;
	}
## abadu verbs are splitted here since morph has this prblm
#
#020712	if($word=~/abaduwu[Mn]/) {  	##	aMxiMcabaduwunna
#	$word=~/(.*)abaduwu(.*)/;
#	$word=$1."a\tunk";
#	$word1="baduwu".$2;
#	}
#	if($word=~/abadina/) {  	##pAliMpabadinaxi
#	$word=~/(.*)abadina(.*)/;
#	$word=$1."a\tunk";
#	$word1="badina".$2;
#	}
#	if($word=~/([^l])[^glr]abad([ie])\t/) {  	##vyavahariMcabade, * nilabadi, *warabadi
#	$word=~/(.*)abad([ie])(.*)/;
#	$word=$1."a\tunk";
#	$word1="bad".$2.$3;
#	}
#	
	if($word=~/[A-z]ganna\t/) {  	##	ammalaganna
	$word=~/(.*)ganna(.*)/;
	$word=$1."\tunk";
	$word1="kanna".$2;
	}
	if($word=~/([A-z])EnaveVMtane/) {  	##	pUrwEnaveVMtane
	$word=~/(.*)EnaveVMtane(.*)/;
	$word=$1."Ena\tunk";
	$word1="veVMtane".$2;
	}
#	if($word=~/agaligiMxi/) {  	##	ApagaligiMxi
#	$word=~/(.*)agaligi(.*)/;
#	$word=$1."a\tunk";
#	$word1="galigi".$2;
#	}
#	if($word=~/akapo/) {  	##	cUdakapovataMwo
#	$word=~/(.*)akapo(.*)/;
#	$word=$1."aka\tunk";
#	$word1="po".$2;
#	}
	if($word=~/([A-z])ukeVlYiwe/) {  	##	muMxukeVlYiwe
	$word=~/(.*)ukeVlYiwe(.*)/;
	$word=$1."uku\tunk";
	$word1="veVlYwe".$2;
	}
	if($word=~/([A-z])nattayi\t/) {  	##	kamminattayi
	$word=~/(.*)nattayi(.*)/;
	$word=$1."nattu\tunk";
	$word1="ayyi".$2;
	}
	if($word=~/vItananni/) {  	##vItananniMtinI
	$word=~/(.*)vItananni(.*)/;
	$word=$1."vItini\tunk";
	$word1="anni".$2;
	}
#Temperarily splitting it, becoz the first analysis has reduplication
	if($word=~/([A-z])ipowunnatl/) {  	##vItananniMtinI
	$word=~/(.*)ipowunnatl(.*)/;
	$word=$1."i\tunk";
	$word1="powunnatl".$2;
	}

	if($word=~/([A-z])nnappudl/) {  	##walacukunnappudallA
#print "iam here with $word\n";
	$word=~/(.*)nnappud(.*)/;
	$word=$1."nna\tunk";
	$word1="appud".$2;
	}
#	if($word=~/axaginaxi/) {  	##cUdaxaginaxi
#	$word=~/(.*)axagina(.*)/;
#	$word=$1."a\tunk";
#	$word1="xagina".$2;
#	}
	if($word=~/([A-z])atamegAka\t/) {  	##uMdatamegAka
	$word=~/(.*)atamegAka(.*)/;
	$word=$1."atame\tunk";
	$word1="gAka".$2;
	}
	if($word=~/([A-z])koVxx([iI])\t/) {  	##weVlivikoVxxI
	$word=~/(.*)koVxx(.*)/;
	$word=$1."\tunk";
	$word1="koVxx".$2;
	}
	if($word=~/([A-z])vArani\t/) {  	##weVlivigalavArani
	$word=~/(.*)vArani(.*)/;
	$word=$1."vAru\tunk";
	$word1="ani".$2;
	}
	if($word=~/([A-z])wuMxI\t/) {  	##aMxiswuMxI
	$word=~/(.*)wuMxI(.*)/;
	$word=$1."wuMxi\tunk";
	$word1="I".$2;
	}
#	if($word=~/aleka\t/) {  	##veVlYlaleka
#	$word=~/(.*)aleka(.*)/;
#	$word=$1."a\tunk";
#	$word1="leka".$2;
#	}
	if($word=~/([A-z])layiwe\t/) {  	##3	prajalayiwe	unk
	$word=~/(.*)layiwe(.*)/;
	$word=$1."lu\tunk";
	$word1="ayiwe".$2;
	}
	if($word=~/^maroti\t/) {  	##3	prajalayiwe	unk
	$word=~/(.*)maroti(.*)/;
	$word=$1."maro\tunk";
	$word1="oVkati".$2;
	}
	if($word=~/^axeMtirA\t/) {  	#axeMtirA
	$word=~/(.*)axeMtirA(.*)/;
	$word=$1."axi\tunk";
	$word1="eMtirA".$2;
	}
	if($word=~/^ogoVppa\t/) {  	#ogoVppa
	$word=~/(.*)ogoVppa(.*)/;
	$word=$1."o\tunk";
	$word1="goVppa".$2;
	}
	if($word=~/([A-z])AligAnI\t/) {  	#ivvAligAnI
	$word=~/(.*)AligAnI(.*)/;
	$word=$1."Ali\tunk";
	$word1="gAnI".$2;
	}
	if($word=~/([A-z])eMtanexi\t/) {  	#eMtanexi
	$word=~/(.*)eMtanexi(.*)/;
	$word=$1."eMti\tunk";
	$word1="anexi".$2;
	}
	if($word=~/xIninuMde\t/) {  	#xIninuMde
	$word=~/(.*)ninuMde(.*)/;
	$word=$1."ni\tunk";
	$word1="nuMde".$2;
	}
	if($word=~/([A-z]+)A([rdmvn])anI\t/) {  	#nirmiMcAranI
	$word=~/(.*)anI(.*)/;
#	$word=~/([A-z]+)A([rdmvn])anI/
	$word=$1."u\tunk";
	$word1="anI".$2;
	}
	if($word=~/([A-z])ananusari/) {  	#godananusariswU
	$word=~/(.*)ananusari(.*)/;
	$word=$1."anu\tunk";
	$word1="anusari".$2;
	}
	if($word=~/([A-z])rnEnA\t/) { ##eVvarnEnA gurao30052012
	$word=~/(.*)rnEnA(.*)/;
	$word=$1."rni\tunk";
	$word1="EnA".$2;
	}
	if($word=~/([aAeEiIoOuU])nenA\t/) { ##awanenA, panenA gurao27082012
	$word=~/(.*)nenA(.*)/;
	$word=$1."nu\tunk";
	$word=$1."ni\tunk";
	$word1="enA".$2;
	}
	if($word=~/([A-z])lnEnA\t/) { ##mimmalnEnA gurao30052012
	$word=~/(.*)lnEnA(.*)/;
	$word=$1."lni\tunk";
	$word1="EnA".$2;
	}
	if($word=~/([A-z])inEnA\t/) { ##vAdinEnA gurao30052012
	$word=~/(.*)inEnA(.*)/;
	$word=$1."ini\tunk";
	$word1="EnA".$2;
	}
	if($word=~/([A-z])unEnA\t/) { ##kaleVktarunEnAgurao30052012
	$word=~/(.*)unEnA(.*)/;
	$word=$1."unu\tunk";
	$word1="EnA".$2;
	}
	if($word=~/([A-z])([dmnvr])emole\t/) { #gurao30052012
	$word=~/(.*)wA([dmnvr])emole(.*)/;
	$word=$1."wA$2u\tunk";
	$word1="emole"."$3";
	}
	if($word=~/([A-z])tA([dmnvr])emo\t/) {	##kUrcuMtAremo modified to include vaswA([dmnvr])emo gurao30052012
	$word=~/(.*)tA([dmnvr])emo(.*)/;
	$word=$1."tA$2u\tunk";
	$word1="emo".$3;
	}
	if($word=~/([A-z])wA([dmnvr]+)emo\t/) {	##marcipowAremo modified to include vaswA([dmnvr])emo gurao30052012
		$word=~/(.*)wA([dmnvr]+)emo(.*)/;
		$word=$1."wA$2u\tunk";
		$word1="emo".$3;
	}
	if($word=~/emonani\t/) {
		$word=~/(.*)emonani(.*)/;
		$word=$1."emo"."\tunk";
		$word1="ani".$2;
	}
	if($word=~/iMxrAxi\t/) {	##marcipowAremo modified to include vaswA([dmnvr])emo gurao30052012
	$word=~/(.*)iMxrAxi(.*)/;
	$word=$1."iMxrudu\tunk";
	$word1="Axi".$2;
	}
##	if($word=~/kani\t/) {	##iMtikani
##	$word=~/(.*)kani(.*)/;
##	$word=$1."ki\tunk";
##	$word1="ani".$3;
##	}
##	if($word=~/pani\t/) {	##repani
##	$word=~/(.*)pani(.*)/;
##	$word=$1."pu\tunk";
##	$word1="ani".$3;
##	}

####################################################

	if($word1 ne "") {
	print "1\t$word$count\n";
	print "1\t$word1$count\n";
	} else {
	print "1\t$word\t$count\n";
	}
	if(($word1 ne "")&&($word2 ne "")) {
	print "1\t$word2\t$count\n"; 
	$word2=~s/.*//g; }
	$count = $count + 1;
}
