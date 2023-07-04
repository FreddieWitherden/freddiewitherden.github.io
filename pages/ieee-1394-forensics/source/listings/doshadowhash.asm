movl  %r13d,%r15d
jmp   0x1000807d5
movl  $0xffffc8f6,%r15d            ; r15d = eDSAuthFailed
movq  $0x00000000,0xfffff588(%rbp)
cmpb  $0x00,0xfffff587(%rbp)
jneq  0x1000809a6
testl %r15d,%r15d
jneq  0x1000808ee