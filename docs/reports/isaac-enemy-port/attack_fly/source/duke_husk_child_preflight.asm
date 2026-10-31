0045e9a1 mov eax, dword ptr [edi + 0x2c]
0045e9a4 test eax, eax
0045e9a6 jne 0x45eadd
0045e9ac mov ecx, dword ptr [edi + 0x30]
0045e9af mov eax, 0x12
0045e9b4 cmp ecx, 1
0045e9b7 jne 0x45e9c5
0045e9b9 mov dword ptr [ebp - 0x23c], 0x50
0045e9c3 jmp 0x45e9d6
0045e9c5 cmp ecx, 2
0045e9c8 mov edx, 0x3d
0045e9cd cmove eax, edx
0045e9d0 mov dword ptr [ebp - 0x23c], eax
0045e9d6 call 0x6c3d90
0045e9db movss xmm0, dword ptr [esi]
0045e9df mov ecx, dword ptr [0xbfd65c]
0045e9e5 push 0
0045e9e7 push 0xbeab70
0045e9ec push 0xbeab18
0045e9f1 push 0
0045e9f3 push eax
0045e9f4 push 0
0045e9f6 push edi
0045e9f7 movss dword ptr [ebp - 0x2fc], xmm0
0045e9ff lea eax, [ebp - 0x2fc]
0045ea05 movss xmm0, dword ptr [edi + 0x298]
0045ea0d addss xmm0, dword ptr [0xb6a9c8]
0045ea15 push 0xc02fec
0045ea1a push eax
0045ea1b push 0
0045ea1d push dword ptr [ebp - 0x23c]
0045ea23 movss dword ptr [ebp - 0x2f8], xmm0
0045ea2b call 0x422e20
0045ea30 push eax
0045ea31 call 0x9ec34c
0045ea36 movss xmm2, dword ptr [0xb6a874]
0045ea3e add esp, 0x14
0045ea41 mov ecx, dword ptr [eax + 0x164]
0045ea47 and dword ptr [eax + 0x160], 0xfffffffb
0045ea4e mov byte ptr [eax + 0x16c], 1
0045ea55 mov dword ptr [eax + 0x164], ecx
0045ea5b cmp dword ptr [edi + 0x30], 0
0045ea5f jne 0x45eeee
0045ea65 movss xmm1, dword ptr [eax + 0xb88]
0045ea6d mulss xmm1, dword ptr [0xb6a680]
0045ea75 movss dword ptr [eax + 0xb88], xmm1
0045ea7d mulss xmm1, dword ptr [eax + 0x30c]
0045ea85 movaps xmm0, xmm1
0045ea88 mulss xmm1, dword ptr [0xbc7a2c]
0045ea90 mulss xmm0, dword ptr [0xbc7a28]
0045ea98 movss dword ptr [eax + 0xdc], xmm1
0045eaa0 movss dword ptr [eax + 0xd8], xmm0
0045eaa8 movss xmm0, dword ptr [eax + 0x2dc]
0045eab0 mulss xmm0, dword ptr [0xb6a754]
0045eab8 movss dword ptr [eax + 0x2dc], xmm0
0045eac0 movss xmm0, dword ptr [eax + 0x2d8]
0045eac8 mulss xmm0, dword ptr [0xb6a754]
0045ead0 movss dword ptr [eax + 0x2d8], xmm0
