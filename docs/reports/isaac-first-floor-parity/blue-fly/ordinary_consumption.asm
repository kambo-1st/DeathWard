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
