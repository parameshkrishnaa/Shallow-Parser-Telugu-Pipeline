#!/usr/bin/perl
##tel-avy.wx 
#[teltamilmt@localhost MyPerl]$ mv Avy avy.txt
$file1 = 'vcon';
$file2 = 'CCV';
open (R, $file1) || die ("Could not open $file!");
open (P, $file2) || die ("Could not open $file!");
# $counter = 0;
while ($Rline = <R>)
{ 
        chomp $_;
       # my @R = split(//,$Rline);
        seek P,0,0; # return to beginning of the P file
        while ($Pline = <P>)
        { 
                chomp $_;
        #        my @P = split(//,$Pline);
                        #if($P[2] ne $R[2]) {
                        chomp($Rline);
                             print "$Rline$Pline";
                        #}
        }
     #   print "$counter\n";
#        $counter++;
 
 
}
close (P);
close (R);
