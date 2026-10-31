0068d7b0 push ebp
0068d7b1 mov ebp, esp
0068d7b3 and esp, 0xfffffff8
0068d7b6 push ecx
0068d7b7 push esi
0068d7b8 mov esi, ecx
0068d7ba call 0x6c3d90
0068d7bf mov ecx, dword ptr [0xbfd65c]
0068d7c5 push 0
0068d7c7 push eax
0068d7c8 push 0
0068d7ca push esi
0068d7cb push 0xc02fec
0068d7d0 lea eax, [esi + 0x294]
0068d7d6 push eax
0068d7d7 push 7
0068d7d9 push 0x3e8
0068d7de call 0x6d0ca0
0068d7e3 push 0
0068d7e5 push 0xbeaaec
0068d7ea push 0xbeab18
0068d7ef push 0
0068d7f1 push eax
0068d7f2 call 0x9ec34c
0068d7f7 movss xmm0, dword ptr [ebp + 8]
0068d7fc mov esi, eax
0068d7fe add esp, 0x14
0068d801 mov ecx, esi
0068d803 mov edx, dword ptr [esi]
0068d805 movss dword ptr [esi + 0xd8], xmm0
0068d80d movss dword ptr [esi + 0xdc], xmm0
0068d815 call dword ptr [edx + 0xc]
0068d818 mov eax, esi
0068d81a pop esi
0068d81b mov esp, ebp
0068d81d pop ebp
0068d81e ret 4
