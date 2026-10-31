006909f0 push ebp
006909f1 mov ebp, esp
006909f3 and esp, 0xfffffff8
006909f6 push ecx
006909f7 push ebx
006909f8 mov ebx, ecx
006909fa push esi
006909fb push edi
006909fc cmp dword ptr [ebx + 0xe8c], 0
00690a03 jl 0x690a7d
00690a05 mov ecx, dword ptr [ebx + 0xe88]
00690a0b lea edi, [ebx + 0xe88]
00690a11 mov esi, dword ptr [ebp + 8]
00690a14 test ecx, ecx
00690a16 je 0x690a88
00690a18 cmp ecx, esi
00690a1a je 0x690ab2
00690a20 movss xmm1, dword ptr [ebx + 0x294]
00690a28 movss xmm0, dword ptr [ebx + 0x298]
00690a30 movss xmm4, dword ptr [ecx + 0x294]
00690a38 movss xmm5, dword ptr [ecx + 0x298]
00690a40 subss xmm4, xmm1
00690a44 movss xmm3, dword ptr [esi + 0x294]
00690a4c subss xmm5, xmm0
00690a50 movss xmm2, dword ptr [esi + 0x298]
00690a58 subss xmm3, xmm1
00690a5c subss xmm2, xmm0
00690a60 mulss xmm4, xmm4
00690a64 mulss xmm5, xmm5
00690a68 mulss xmm2, xmm2
00690a6c mulss xmm3, xmm3
00690a70 addss xmm5, xmm4
00690a74 addss xmm2, xmm3
00690a78 comiss xmm5, xmm2
00690a7b ja 0x690a8c
00690a7d xor al, al
00690a7f pop edi
00690a80 pop esi
00690a81 pop ebx
00690a82 mov esp, ebp
00690a84 pop ebp
00690a85 ret 8
00690a88 cmp ecx, esi
00690a8a je 0x690ab2
00690a8c test ecx, ecx
00690a8e je 0x690aa4
00690a90 lea eax, [esp + 0xc]
00690a94 mov dword ptr [esp + 0xc], edi
00690a98 push eax
00690a99 add ecx, 0x324
00690a9f call 0x4bc3c0
00690aa4 mov dword ptr [edi], esi
00690aa6 test esi, esi
00690aa8 je 0x690ab2
00690aaa push edi
00690aab mov ecx, esi
00690aad call 0x4bae70
00690ab2 mov eax, dword ptr [ebp + 0xc]
00690ab5 pop edi
00690ab6 mov dword ptr [ebx + 0xe8c], eax
00690abc mov al, 1
00690abe pop esi
00690abf pop ebx
00690ac0 mov esp, ebp
00690ac2 pop ebp
00690ac3 ret 8
