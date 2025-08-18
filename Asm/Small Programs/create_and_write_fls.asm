section .data
    pathname dd "/home/miguel/Code/Homo_Deus/Assembly/x86/test.txt"
    toWrite dd "Hello",0ah,0dh"$" ;hello + new line character
section .text
global main

main: 
  mov eax, 5
  mov ebx, pathname
  mov ecx, 101o ;octal value
  mov edx, 700o
  int 80h   ;create file

  mov ebx, eax
  mov eax, 4 ;write syscall
  mov ecx, toWrite
  mov edx, 15 ;size of string
  int 80h

  mov eax,1
  mov ebx, 0
  int 80h
