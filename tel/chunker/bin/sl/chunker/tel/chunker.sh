#path=$2
perl $setu/chunker/bin/sl/chunker/tel/common/ssf2tnt_pos.pl $1 > chunkinput_pos.tnt
crf_test -m $setu/chunker/bin/sl/chunker/tel/200k_telugu_chunker_model chunkinput_pos.tnt > chunker_out.tnt

perl $setu/chunker/bin/sl/chunker/tel/common/convert_biotossf.pl < chunker_out.tnt 
# Comment the previous line and uncomment the following lines if the system is tel-hin-ilmt
#perl $setu/bin/sl/chunker/tel/common/convert_biotossf.pl < chunker_out.tnt > chunker_out1.tnt
#perl $setu/bin/sl/chunker/tel/chunk_repair/chunk_repair.pl --path=$setu/bin/sl/chunker/tel/chunk_repair --resource=$setu/bin/sl/chunker/tel/chunk_repair/Rules --input=chunker_out1.tnt
