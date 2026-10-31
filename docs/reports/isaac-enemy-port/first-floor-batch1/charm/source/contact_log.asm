0068f440 push ebp
0068f441 mov ebp, esp
0068f443 and esp, 0xfffffff8
0068f446 cvtss2sd xmm0, xmm0
0068f44a call 0x9ec394
0068f44f cvtsd2ss xmm0, xmm0
0068f453 mov esp, ebp
0068f455 pop ebp
0068f456 ret 
