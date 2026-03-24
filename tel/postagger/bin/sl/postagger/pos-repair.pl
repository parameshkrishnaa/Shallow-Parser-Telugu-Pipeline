#!usr/bin/perl
#PARAMESHKRISHNA, CALTS, 060612
# (1) This program corrects POS information by looking at the ends.

while($line=<>)
{
chomp($line);
($id,$token,$pos,$fs)=split(/\t+/,$line);
chomp($fs);
if (($token=~/a[dt]aM$/)&&($pos eq "NN"))
{
$pos=~s/NN/VM/;
}
#39	muMxuMcatAniki	NN	<fs af='muMxuMcu,v,,sg,,,adaM_ki,adaM_ki'>
if (($token=~/a[dt]Aniki/)&&($pos eq "NN"))
{
$pos=~s/NN/VM/;
}
#5.1	cUxxAmA	NN	<fs af='cUdu,v,,pl,2,,xA,xA_A'>
if (($token=~/xxAmA$/)&&($pos eq "NN")) {
$pos=~s/NN/VM/;
}
#29	poKarAlo	VM	<fs af='poKarA,n,,pl,,,0,0_o'>|<fs af='poKarA,n,,sg,,,lo,lo'

if (($token=~/^poKarA/)&&($pos eq "VM")) {
$pos=~s/VM/NN/;
}
if (($token=~/ipo$/)&&($pos eq "NN")) {
$pos=~s/NN/VM/;
}
if (($token=~/^patla$/)&&($pos eq "NN")) {
$pos=~s/NN/PSP/;
}
if (($token=~/^kAnixi$/)&&($pos eq "NN")) {
$pos=~s/NN/VM/;
}
if (($token=~/^kAgA$/)&&($pos eq "NN")) {
$pos=~s/NN/CC/;
}
if (($token=~/^badina/)&&($pos eq "NN")) {
$pos=~s/NN/VM/;
}
if (($token=~/^loniki/)&&($pos eq "VM")) {
$pos=~s/VM/PSP/;
}
if (($token=~/^loki/)&&($pos eq "NN")) {
$pos=~s/NN/PSP/;
}
if (($token=~/[aeiou]gAru$/)&&($pos eq "VM")) {
$pos=~s/VM/NN/;
}
#if (($token=~/ani$/)&&($pos eq "VM")&&($fs=~/_ani,.*_ani'/)) {
#my $id2;
#$id2=$id+1;
#$fs=~s/(.*)_ani,(.*)_ani'>/$1,$2'>\n$id2\tani\tUT\t<fs af='ani,avy,,,,,,'>/;
#}

$line ="$id\t$token\t$pos\t$fs";
print "$line\n";
}

