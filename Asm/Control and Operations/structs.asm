section .data

Point struct
  dd x ?
  dd y ?
Point ends

myPoint Point{0 , 0}

MyUnion union
  small db ?
  medium dw ?
  large dd ?
  huge dq ?
MyUnion ends

pp MyUnion{0fffffffh}

section .code

SomeFunc proc
    mov [rcx].Point.x, 100
    mov pp.medium, 100
    ret
SomeFunc endp
end

  
