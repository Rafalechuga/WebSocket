#!/bin/bash

 rm ./out/Compiler.out
 rm ./out/Servidor.out

 echo Compiling program...

 find  ./src -type "d" >./fonts/H_Files.txt

 find ./src -name "*.c" >./fonts/C_Files.txt

 gcc  -o ./out/Compiler.out ./compiler/Compiler.c

 ./out/Compiler.out

 gcc ./sqlite3/sqlite3.c -I ./sqlite3/ -c

 gcc @./fonts/H_Files.txt -I ./sqlite3/  @./fonts/C_Files.txt sqlite3.o -o ./out/Servidor.out -lpthread -ldl

 echo Compile has been finished!
 echo





 



