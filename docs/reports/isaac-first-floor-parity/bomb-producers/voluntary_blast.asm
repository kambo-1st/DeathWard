004f9e1a cmp eax, 5
004f9e1d jne 0x4f9f31
004f9e23 movss xmm0, dword ptr [edi + 0x2c4]
004f9e2b mulss xmm0, dword ptr [0xb6a560]
004f9e33 movss dword ptr [edi + 0x2c4], xmm0
004f9e3b cmp dword ptr [edi + 0x90], 0
004f9e42 je 0x4f9e51
004f9e44 cmp byte ptr [edi + 0xa0], 0
004f9e4b jne 0x4f9f29
004f9e51 movups xmm0, xmmword ptr [0xbfec58]
004f9e58 mov ecx, dword ptr [0xbfd65c]
004f9e5e lea esi, [edi + 0x294]
004f9e64 push 0
004f9e66 push 0
004f9e68 push 4
004f9e6a sub esp, 0x10
004f9e6d mov eax, esp
004f9e6f push edi
004f9e70 push 1
004f9e72 sub esp, 8
004f9e75 movups xmmword ptr [eax], xmm0
004f9e78 mov dword ptr [esp + 4], 0x42700000
004f9e80 mov dword ptr [esp], 0x42200000
004f9e87 push esi
004f9e88 call 0x6d1750
