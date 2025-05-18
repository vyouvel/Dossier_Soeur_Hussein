.DATA
x DW 10
y DB 20, 30, 40
z DW 100

.CODE
start: MOV AX, x
       ADD AX, [DS:1]
       MOV BX, AX
       CMP BX, z
       JZ fin
       PUSH BX
       MOV CX, 5
       ADD CX, AX
       POP DX
       CMP DX, CX
       ALLOC
       MOV [ES:AX], CX
       FREE
fin: HALT
