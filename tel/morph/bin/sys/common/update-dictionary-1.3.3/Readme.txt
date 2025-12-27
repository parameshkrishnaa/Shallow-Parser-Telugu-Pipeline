
Dictionary Database Updater
===========================

sapan@cse.iitb.ac.in
IIT Bombay
July 7, 2008

IMPORTANT NOTE:------------
DSFRecord is enhanced to support Cross-linking of words. Depending on the size of the input 5-line DSF files, this version may take 10min-20min for execution.
If the execution is aborted prematurely, the tool will generate temporary files in input directory. User must delete these files manually before running the tool again.
The name of the temporary files will be <language-Namecode>-CLTemp.txt (e.g. hin-CLTemp.txt, mar-CLTemp.txt)
---------------------------

To run the dictionary database updater, execute the shell script update-dictionary. Usage of that script is as follows:

Usage:
 update-dictionary OPTIONS ...
 where OPTIONS are 
 -h --help		 for help on sample usage
 -i 		 input directory (mandatory) 
 -o 		 output directory (mandatory) 
 -s 		 source language (3-letter language code, optional)  
 -t 		 target language (3-letter language code, optional) 

Paths can be absolute or relative.

If source and target languages are not specified, all files present in input directory are processed.

The files in input directory can be updated to add more synsets and this utility can be used to update dictionary database at outputdirectory which can then be processed by MultiDictAPI.

The specified language files in input directory must be named strictly as follows:
<3-letter lang code in lower case>.txt
E.g. Hindi File should be named "hin.txt" exactly and no other file (e.g "HIN.txt" or "hindi.txt") will be processed.

If the source and target languages are not specified, all the files with "txt" extension in input directory will be processed.
So make sure there are no other files or directory in the input directory other than DSF data if you want to process the whole directory.

Example: Adding synsets to user_dictionary for the language pair Hindi and Telugu.

1. Go to user_dictionary (default is setu/data_bin/sl_tl/lexicaltransfer/user_dict).
2. Go to the languauge-pair directory i.e. hin-tel.

3. Open the file hin.txt. Add a new synset as a five line entry as shown below.
ID		:: 48 
CAT		::  ADJECTIVE 
CONCEPT		::  बिना नाम का या जिसका कोई नाम न हो 
EXAMPLE		::  "रामू ने अनाथ आश्रम से एक अनाम बालक को गोद लिया" 
SYNSET-HINDI	:: अनाम 

4. Open the file tel.txt. Add the corresponding Telugu synset as a five line entry as shown below.
ID		:: 48 
CAT		::  ADJECTIVE 
CONCEPT		::  పేరులేని లేదా ఏ పేరూ లేని వ్యక్తి 
EXAMPLE		::  "రాము ఒక అనాథ ఆశ్రమం నుండి ఒక అనామక బాలుడిని దత్తత తీసుకున్నాడు" 
SYNSET-TELUGU	:: అనామక 
Please make sure that the new synset-id is unique and does not clash with existing synset ids. Also the hindi and telugu synset-id should be the same.

5. Run the script with the options shown below:
update-dictionary -i $user_dictionary/hin-tel  -o $user_dictionary/hin-tel -sHIN -tTEL

6. You can now give $user_dictionary as an input to the lexicalTransferEngine (using the -r command line option) so that the added synsets are included by the API.
