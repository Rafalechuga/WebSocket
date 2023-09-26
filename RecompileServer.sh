#!/bin/bash

 rm ./out/Compiler.out
 rm ./out/Excecutable.out

 echo Compiling program...

 find  ./src -type "*.h" >./fonts/H_Files.txt

 find ./src -name "*.c" >./fonts/C_Files.txt

 gcc   -o ./out/Compiler.out ./compiler/Compiler.c

 ./out/Compiler.out

 gcc @./fonts/H_Files.txt -I ./sqlite3/  @./fonts/C_Files.txt sqlite3.o -o ./out/Excecutable.out -lpthread -ldl

 echo Compile has been finished!
 echo
