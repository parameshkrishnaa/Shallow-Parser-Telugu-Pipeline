while ($line=<>) {
$line=~s/\n/ /g;
$line=~s/O /O \n/g;
print $line;
}
