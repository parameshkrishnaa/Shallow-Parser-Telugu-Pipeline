# Shallow Parser Pipeline
Telugu Pipeline

## Settings
cd to the shallow-parser-pipeline/tel
````
export setu=/home/user/shallow-parser-pipeline/tel
````
## Dependencies
## CRF++ 0.51+
Download: https://drive.google.com/file/d/1ytMgBCdU0E3JihL8K24XbogEmne_OLte/view?usp=drive_link

### Follow below steps to install CRF++

````
cd CRF++-0.51
./configure
make
$make install
````

### Check if the installtion was successful using below command

````
crf_test --version
````

**Note if you get an error as below**
if **libcrfpp.so.0** not found after CRF installation than execute the below command

````
ln -s /usr/local/lib/libcrfpp.so.0 /usr/lib/libcrfpp.so.0
````

## Morph Analyszer dependencies

````
sudo yum install gcc gdbm libgdbm-dev glib-2.0 libglib2.0-dev pkg-config
````

## for ubuntu 20+ to install glib2.0
````
sudo apt-get install libgtk2.0-dev
````

*For ubuntu use following command*

````
sudo apt-get install gcc libgdbm-dev libglib2.0-dev g++ pkg-config
````

## Install
cd to shallow-parser-pipeline/tel/morph/src/sl/morph
````
make compile
make install

````
## to run pipeline upto pickonemorph
````
python3 run_pipeline.py <in.txt>
````

## View in.txt_pickone.txt for the pickone output


# To setup clause boundary
Follow the README.md in clauseboundary

## To run pipeline upto clauseboundary
````
sh run_pipeline.sh in.txt

