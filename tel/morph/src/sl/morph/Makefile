SHELL = /bin/sh

SUBDIRS = ../../../data_src/sl/morph/tel/shell tel 


.PHONY: $(SUBDIRS) 

all: 
compile: $(SUBDIRS)
	 
$(SUBDIRS): 
	export LANG=C
	$(MAKE) -C $@

install:
	mv tel/*.o tel/common/analyser/obj/
	cp tel/morph.out ../../../bin/sl/morph/tel/
	cp ../../../data_src/sl/morph/tel/dict/prop_noun_lex.dic ../../../data_bin/sl/morph/tel
	cp ../../../data_src/sl/morph/tel/dict/uword.dic ../../../data_bin/sl/morph/tel
	cp -rf ../../../data_src/sl/morph/tel/pc_data/derivation ../../../data_bin/sl/morph/tel/
	#mv tel/rls ../../../data_bin/sl/morph/tel
## Paramesh
#	cp ../../../bin/sl/morph/tel/rls ../../../data_bin/sl/morph/tel
##
clean:
	$(MAKE) -C tel clean
	$(MAKE) -C ../../../data_src/sl/morph/tel/shell/ clean
