00685020 push ebp
00685021 mov ebp, esp
00685023 push ecx
00685024 cmp dword ptr [ecx + 0x28], 1
00685028 push esi
00685029 je 0x685074
0068502b mov eax, dword ptr [ebp + 0xc]
0068502e mov esi, dword ptr [eax + 0x24]
00685031 test esi, esi
00685033 je 0x685074
00685035 mov eax, dword ptr [esi + 0x320]
0068503b test eax, eax
0068503d je 0x68504c
0068503f nop 
00685040 mov esi, eax
00685042 mov eax, dword ptr [esi + 0x320]
00685048 test eax, eax
0068504a jne 0x685040
0068504c cmp dword ptr [esi + 0x28], 1
00685050 jne 0x685074
00685052 push 0x4e
00685054 mov ecx, esi
00685056 call 0x78d4c0
0068505b test eax, eax
0068505d jle 0x685074
0068505f push 0x4e
00685061 mov ecx, esi
00685063 call 0x78d4c0
00685068 imul eax, dword ptr [ebp + 8]
0068506c add eax, eax
0068506e pop esi
0068506f pop ecx
00685070 pop ebp
00685071 ret 8
00685074 mov eax, dword ptr [ebp + 8]
00685077 pop esi
00685078 pop ecx
00685079 pop ebp
0068507a ret 8
