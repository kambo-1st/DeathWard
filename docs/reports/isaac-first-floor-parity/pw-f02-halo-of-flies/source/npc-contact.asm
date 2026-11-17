006089cf mov ecx, dword ptr [esi + 0x28]
006089d2 cmp ecx, 0xd
006089d5 je 0x6089ea
006089d7 cmp ecx, 0xe
006089da jne 0x608ab2
006089e0 cmp dword ptr [esi + 0x2c], 2
006089e4 je 0x608b00
006089ea mov eax, dword ptr [esi]
006089ec mov ecx, esi
006089ee call dword ptr [eax + 0x24]
006089f1 mov eax, dword ptr [edi + 0x2c]
006089f4 cmp eax, 0x2b
006089f7 jne 0x6094a0
006089fd call 0x6c3d90
00608a02 push eax
00608a03 push 0
00608a05 push 0
00608a07 push 0xc02fec
00608a0c lea ecx, [edi + 0x294]
00608a12 push ecx
00608a13 mov ecx, dword ptr [0xbfd65c]
00608a19 push 3
00608a1b push 0x3e8
00608a20 call 0x422e20
00608a25 mov eax, dword ptr [edi]
00608a27 mov ecx, edi
00608a29 call dword ptr [eax + 0x28]
00608a2c mov eax, dword ptr [edi + 0x30]
00608a2f mov edx, 1
00608a34 mov dword ptr [esp + 0x7c], edx
00608a38 cmp eax, edx
00608a3a jne 0x6093da
00608a40 mov ecx, dword ptr [edi + 0x360]
00608a46 lea eax, [esp + 0x18]
00608a4a push 0
00608a4c push eax
00608a4d call 0x749480
00608a52 push 0
00608a54 push 0
00608a56 push 4
00608a58 push 1
00608a5a push ecx
00608a5b mov dword ptr [esp], 0x3f19999a
00608a62 lea ecx, [edi + 0xe4]
00608a68 push edi
00608a69 push ecx
00608a6a mov edx, eax
00608a6c sub esp, 0x10
00608a6f mov eax, esp
00608a71 movups xmm0, xmmword ptr [edx]
00608a74 push ecx
00608a75 mov ecx, dword ptr [0xbfd65c]
00608a7b movups xmmword ptr [eax], xmm0
00608a7e lea eax, [edi + 0x294]
00608a84 movss xmm0, dword ptr [esp + 0x44]
00608a8a subss xmm0, dword ptr [0xb6a614]
00608a92 mulss xmm0, dword ptr [0xb6a9ec]
00608a9a addss xmm0, dword ptr [0xb6aa8c]
00608aa2 movss dword ptr [esp], xmm0
00608aa7 push eax
00608aa8 call 0x6d26e0
00608aad jmp 0x6094a0
00608ab2 cmp ecx, 0x12
00608ab5 je 0x6089ea
00608abb cmp ecx, 0x50
00608abe je 0x6089ea
00608ac4 cmp ecx, 0xde
00608aca je 0x6089ea
00608ad0 cmp ecx, 0x100
00608ad6 je 0x6089ea
00608adc cmp ecx, 0x128
00608ae2 je 0x6089ea
00608ae8 cmp ecx, 0x119
00608aee je 0x6089ea
00608af4 cmp ecx, 0x364
00608afa je 0x6089ea
00608b00 cmp eax, 0x82
00608b05 jne 0x608b14
00608b07 cmp dword ptr [edi + 0xc9c], -1
00608b0e jne 0x6094a0
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
