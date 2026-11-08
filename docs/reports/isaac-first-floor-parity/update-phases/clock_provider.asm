00970040 push ebp
00970041 mov ebp, esp
00970043 sub esp, 8
00970046 cmp byte ptr [0xbfd66b], 0
0097004d jne 0x970065
0097004f push 0
00970051 push 0x10001
00970056 call 0x99b7a0
0097005b add esp, 8
0097005e xorps xmm0, xmm0
00970061 mov esp, ebp
00970063 pop ebp
00970064 ret 
00970065 cmp byte ptr [0xbfe370], 0
0097006c je 0x970080
0097006e lea eax, [ebp - 8]
00970071 push eax
00970072 call dword ptr [0xa060c4]
00970078 mov eax, dword ptr [ebp - 8]
0097007b mov edx, dword ptr [ebp - 4]
0097007e jmp 0x970088
00970080 call dword ptr [0xbfe398]
00970086 xor edx, edx
00970088 sub eax, dword ptr [0xbfe380]
0097008e mov ecx, eax
00970090 sbb edx, dword ptr [0xbfe384]
00970096 call 0x9eb970
0097009b mulsd xmm0, qword ptr [0xbfe378]
009700a3 mov esp, ebp
009700a5 pop ebp
009700a6 ret 
