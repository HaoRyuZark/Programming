.data
  my_ints1 dd 0, 1, 2, 3, 4
  my_ints2 dd 5, 5, 5, 5, 5

.code

Test proc
  movdqu xmm0, xmmword ptr[my_ints1] 
  movdqu xmm1, xmmword ptr[my_ints2]

  padd xmm0, xmm1 ;add vectors 
  ret             ;to know the exact number of ops for different data types look at AVX512
Test endp
end
