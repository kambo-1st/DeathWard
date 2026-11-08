0064e939 push edi
0064e93a lea ecx, [ebp - 0x38]
0064e93d call 0x4229a0
0064e942 mov eax, dword ptr [esi]
0064e944 lea ecx, [ebp - 0x38]
0064e947 movss xmm0, dword ptr [ebp - 0xb0]
0064e94f push 0x1e
0064e951 push ecx
0064e952 push dword ptr [ebp - 0xd0]
0064e958 push dword ptr [ebp - 0xd4]
0064e95e push ecx
0064e95f mov ecx, esi
0064e961 movss dword ptr [esp], xmm0
0064e966 call dword ptr [eax + 0x20]
