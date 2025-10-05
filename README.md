# Algo Homework #2

## To Do:

[x] make a mergeSort function (mayhaps make a headerfile)
[x] make array class
[ ] create a makefile - should compile any c++ files into unique executables
[x] add a bash command to compare test input and output
[x] implement in class algorithm with my modifications

## Counting inversions

* Replicate the in class code
* When finding midCount, have an additional variable that holds the sum of all previous left numbers
  * midCount += leftSums + i*rightSort[i]

## How to use bash command
> ./runTest.bat \<exe file> \<txt file>

* The txt file defaults to *test.txt*
* The command will automatically use the text_in and text_out folders
* DO NOT specify the input file is in the text_in folder (it already knows)
