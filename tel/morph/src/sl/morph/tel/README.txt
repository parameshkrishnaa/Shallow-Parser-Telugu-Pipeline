				MORPH 3.0 (MORPH ANALYZER WITH SANDHI SPLITTER)
						-------------------
Morph : 


Requirements:
------------
Operating System		:    LINUX/UNIX system

Compiler/Interpreter/Librarie(s):    gcc, glib-2.0 and SSF API's

For installation on Linux, please refer to the file INSTALL.


Directory Structure:
--------------------

morph
     |
     |---src (functional source code of the morph)
     |    
     |---data_bin (data bin files)
     |	  |--sl
     |	  
     |	  
     |---data_src
     |
     |---API (SSF API's)
     |
     |---tests (contains the referenece input and output)
     |     |
     |     |--tel (contains the referenece input and output of telugu as source langauge)
     |
     |---doc (documentaion files of the morph)
     |
     |---README (How to run/use the module)
     |
     |---INSTALL (How to install in sampark directory structure)
     |
     |---ChangeLog (version inforamation)
     |
     |---Makefile (first level make file for copying the module source in sampark system)
     |
     |---Makefile.stage2 (2nd level make file for actual installation/copying in the bin and data_bin directory)
     |
     |---morph_run.sh (to run the morph module)
     |
     |---morph.sh (for the use of dashboard spec file)
     |
     |---morph.spec (individual morph module run with dashboard)


How to Use??
------------

1. $setu/bin/sl/morph/tel/morph.out --logfilepath morph.log --pdgmfilepath $setu/data_bin/sl/morph/tel/ --uwordpath $setu/data_bin/sl/morph/tel/dict_final --dictfilepath $setu/data_bin/sl/morph/tel  -ULDWH --inputfile morph.rin --outputfile morph.rout

   
   *resource is the data_src/sl/morph/tel/* file 

   *sample input and output files are provided in the tests dir namely morph.rin morph.rout.

2. update the db file in case of any change in the data file.

  cd $setu/src/sl/morph
  make


#################################
Author: Christopher M
	CALTS
	HCU, Hyderabad	

Any Quries or suggestions mail to
christopher@research.iiit.ac.in
(or)
efthachris@gmail.com 
Ph.No: 09395325120
#################################

