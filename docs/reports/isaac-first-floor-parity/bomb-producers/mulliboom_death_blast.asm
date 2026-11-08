004f9f31 cmp byte ptr [edi + 0x16b], 0
004f9f38 je 0x4fa1bd
004f9f3e mov eax, dword ptr [edi + 0x2c]
004f9f41 cmp eax, 2
004f9f44 jne 0x4f9fd6
004f9f4a movups xmm0, xmmword ptr [0xbfec58]
004f9f51 mov ecx, dword ptr [0xbfd65c]
004f9f57 lea esi, [edi + 0x294]
004f9f5d push 0
004f9f5f push 0
004f9f61 push 4
004f9f63 sub esp, 0x10
004f9f66 mov eax, esp
004f9f68 push edi
004f9f69 push 1
004f9f6b sub esp, 8
004f9f6e movups xmmword ptr [eax], xmm0
004f9f71 mov dword ptr [esp + 4], 0x42700000
004f9f79 mov dword ptr [esp], 0x42200000
004f9f80 push esi
004f9f81 call 0x6d1750
