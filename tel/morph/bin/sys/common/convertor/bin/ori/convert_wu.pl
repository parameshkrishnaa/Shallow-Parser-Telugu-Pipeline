#!/usr/bin/perl

&wx_utf($ARGV[0]);
sub wx_utf
{

$infile =$_[0];


%vowel = qw(
a	2821
A	2822
i	2823
I	2824
u	2825
U	2826
q	2827
Q	2828
e	2831
E	2832
o	2835
O	2836
);

%cons = qw(
k	2837
K	2838
g	2839
G	2840
f	2841
c	2842
C	2843
j	2844
J	2845
F	2846
t	2847
T	2848
d	2849
D	2850
N	2851
w	2852
W	2853
x	2854
X	2855
n	2856
p	2858
P	2859
b	2860
B	2861
m	2862
y	2863
r	2864
l	2866
lY	2867
v	2869
S	2870
R	2871
s	2872
h	2873
);
%join_vowel =qw(
A	2878
i	2879
I	2880
u	2881
U	2882
q	2883
Qୄ	2884
e	2887
E	2888
o	2891
O	2892
);

$cons="[kKgGfcCjJFtTdDNwWxXnpPbBmyrlvRSsh]Y?Y?";
$vowel = "[HaAiIuUeEoO]V?";

open(F, "<:utf8", "$infile");
binmode ( STDOUT, ":utf8" );

while($line=<F>) {
	@chars=();
	$flag = 0;
	while(1)
	{
		if($line=~/^($vowel)/ and $flag==0)
		{
			print chr($vowel{$1});
			$line = $';
		}
		elsif($line=~/^($vowel)/ and $flag==1)
		{
			print chr($join_vowel{$1}) if($1 ne "a");
			$line = $';
			$flag=0;
		}
		elsif($line =~/^(M)/)
		{
			$line = $';
			$flag=0;
			print chr(2990);
			print chr(3021);
		}
		elsif($line=~/^($cons)/)
		{
			$flag = 1;
			print chr($cons{$1});
			$line = $';
			if($line!~/^$vowel/)
			{
				if($line=~/^(Z)/)
				{
					$line =$';
				}
				print chr(3021);
			}
		}
		elsif($line=~/^(.)/)
		{
			$flag=0;
			print $1;
			$line = $';
		}
		elsif(length($line)>0)
		{
			$flag=0;
			@chars = split(//,$line);
			print $chars[0];
			shift @chars;
			$line = join("",@chars);
		}
		else
		{
			last;
		}
	}
}

close(F);
}
1;
