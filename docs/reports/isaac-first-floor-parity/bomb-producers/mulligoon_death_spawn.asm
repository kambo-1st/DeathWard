004f9fd6 cmp eax, 1
004f9fd9 jne 0x4fa044
004f9fdb call 0x6af030
004f9fe0 test eax, eax
004f9fe2 jg 0x4f9fec
004f9fe4 movss xmm0, dword ptr [0xb6a928]
004f9fec lea ecx, [ebp - 0xf0]
004f9ff2 movss dword ptr [ebp - 0xf8], xmm0
004f9ffa mov dword ptr [ebp - 0xf4], 0
004fa004 lea esi, [edi + 0x294]
004fa00a call 0x430d70
004fa00f push eax
004fa010 push 7
004fa012 lea eax, [ebp - 0xf8]
004fa018 mov ecx, edi
004fa01a push eax
004fa01b push esi
004fa01c call 0x6a1a20
004fa021 call 0x6c3d90
004fa026 mov ecx, dword ptr [0xbfd65c]
004fa02c push eax
004fa02d push 0
004fa02f push edi
004fa030 push 0xc02fec
004fa035 push esi
004fa036 push 3
004fa038 push 4
004fa03a call 0x422e20
004fa03f jmp 0x4fa1bd
