__asm__(
".text \n"
".global " START " \n"
START ": \n"
"	xor %rbp,%rbp \n"
".weak _DYNAMIC \n"
".hidden _DYNAMIC \n"
"	andq $-16,%rsp \n"
"	call " START "_c \n"
);
