push 10h              ; Hash length (16 chars)
add  ebx, 34h
push ebx              ; Source1
push esi              ; Source2
call RtlCompareMemory ; Compare
cmp  eax, 10h         ; Were all 16 chars equal
jnz  short $_1        ; No, jump to $_1
mov  al, 1            ; Yes, set al = 1
$_2:                  ; Remainder of function

$_1:
xor  al, al           ; Zero al
jmp  $_2              ; Jump to $_2