1. To compile :
gcc hw2.c -o hw

to run without arguments to print the current directory
./hw

to print the files by passing argument (current directory)
./hw ./

to print the files in the privous directory
./hw ../

to print files and its details 
./hw -S

to print the file with size equals to or below
./hw -s filesize

to print the files in the files with the text name
./hw -f "txt 0"

to print the files with multiple arguments 
example:
./hw -s 1024, -f "jpg 1"

to print the files when -s and -f is passed
./hw -s -f

Graduate Students Only] The program should support a fourth command-line option:
./hw -t f
./hw -t d