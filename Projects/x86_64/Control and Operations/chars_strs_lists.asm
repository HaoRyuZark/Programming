section .data
        list DB 1,2,4,5     ; list of items
        string1 DB "ABA",0  ; string with null terminator
        char DB 'A'         ;
        string2 DB "CDB",0  ;

section .text
global _start

_start:
      MOV bl, [string1]
      MOV eax, 1,
      XOR ebi, ebi
      SYSCALL
