00608b14 mov ecx, eax
00608b16 cmp eax, 0x21
00608b19 je 0x6092f0
00608b1f cmp eax, 0x75
00608b22 je 0x6092f0
00608b28 cmp eax, 0x2b
00608b2b je 0x608b32
00608b2d cmp eax, 0x49
00608b30 jne 0x608b64
00608b32 push dword ptr [edi + 0x2bc]
00608b38 push dword ptr [edi + 0x2b8]
00608b3e push 0
00608b40 push 0xbeab70
00608b45 push 0xbeab18
00608b4a push 0
00608b4c push esi
00608b4d call 0x9ec34c
00608b52 add esp, 0x14
00608b55 mov ecx, eax
00608b57 call 0x6aa830
00608b5c test al, al
00608b5e je 0x609289
00608b64 push edi
00608b65 lea ecx, [esp + 0x58]
00608b69 call 0x4229a0
00608b6e movss xmm0, dword ptr [esp + 0x14]
00608b74 lea ecx, [esp + 0x54]
00608b78 mulss xmm0, dword ptr [edi + 0x2e0]
00608b80 mov eax, dword ptr [esi]
00608b82 push 0x1e
00608b84 push ecx
00608b85 push 0
00608b87 push 0
00608b89 push ecx
00608b8a mov ecx, esi
00608b8c movss dword ptr [esp], xmm0
00608b91 call dword ptr [eax + 0x20]
