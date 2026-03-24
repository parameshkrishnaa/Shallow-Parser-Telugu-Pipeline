SHELL = /bin/sh


all: data_compile data_dict

data_compile:
	./new_data_compile.sh 
data_dict:
	./mk_dbm_dict_gnu.sh 	
	cp -rf ../pc_data/derivation ../../../../../data_bin/sl/morph/tel/
clean:
	rm -rf ../../../../../data_bin/sl/morph/tel/*
