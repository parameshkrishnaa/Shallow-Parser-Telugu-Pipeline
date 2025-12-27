%SPEC_FILE%
#
# Generated Dashboard Specification file 
#
# This file gives the specifications to run the system. It contains:
#DO NOT change the naming convention of any of the sections.


%GLOBAL%
#
# Global variables 
#

# Root directory of the system
<ENV>$mt_iiit=/usr/share/Dashboard
<ENV>$setu=/home/nagaraju/sampark
<ENV>$src=$setu/src
<ENV>$bin=$setu/bin
<ENV>$data_bin=$setu/data_bin
<ENV>$data_src=$setu/data_src
<ENV>$val_data=$setu/val_data

# Other variables used in the generation of executable
# type=int, char, char*
<VAR>$slang=tel
<VAR>$tlang=tam
<VAR>$stlang=tel_tam

# API for PERL,C language
<API lang=perl>$mt_iiit/lib/shakti_tree_api.pl
<API lang=perl>$mt_iiit/lib/feature_filter.pl
<API lang=C>$mt_iiit/c_api_v1/c_api_v1.h
# READER,PRINTER function for language PERL
<READER lang=perl>read
<PRINTER lang=perl>print_tree_file

# READER,PRINTER function for language C
<INCLUDE lang=C>stdio.h
<INCLUDE lang=C>stdlib.h
<READER lang=C>read_ssf_from_file
<PRINTER lang=C>print_tree_to_file

# Output directory for storing temporaries (relative path to current dir)
#<OUTPUT_DIR>OUTPUT.tmp
#<OUTPUT_DIR>$val_data/system/$stlang
<OUTPUT_DIR>/home/nagaraju/temp/

# Run in SPEED or DEBUG or USER mode
<MODE>DEBUG
#<MODE>SPEED


%SYSTEM%

# Each module should have a unique identifying name (i.e. unique value for the second column)

# -----------------------------------------------
# Source Language Analyzer Modules (SL)
# -----------------------------------------------

# Morph Analyzer
#1morph-2.5.1$bin/sl/morph/tel/morph.shdep=<START>intype=1lang=sh
1	morph-2.6		$bin/sl/morph/tel/morph.sh	dep=<START>	intype=1	lang=sh

#### Pos Tagger
2	postagger-1.4	$bin/sl/postagger/postagger.sh	dep=<PREV>	lang=sh

##### Chunker
3	chunker-1.3		$bin/sl/chunker/tel/chunker.sh	dep=<PREV>	lang=sh

##### Prunning 
4	pruning-1.7		$bin/sl/pruning/pruning.sh	dep=<PREV>	intype=1	lang=sh

##Guess morph
5	guess-morph-1.0		$bin/sl/guess_morph/guess-morph.sh	dep=<PREV>	intype=1	lang=sh

##Pickone morph
6	pickonemorph-1.1	$bin/sl/pickonemorph/tel/pickonemorph.sh	dep=<PREV>	intype=1	lang=sh
