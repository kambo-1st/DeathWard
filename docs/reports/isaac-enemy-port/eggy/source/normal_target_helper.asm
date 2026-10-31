00695a30 push ebp
00695a31 mov ebp, esp
00695a33 and esp, 0xfffffff8
00695a36 sub esp, 0x1c
00695a39 push ebx
00695a3a push esi
00695a3b mov esi, ecx
00695a3d push edi
00695a3e mov eax, dword ptr [esi + 0x164]
00695a44 mov ecx, dword ptr [esi + 0x160]
00695a4a mov dword ptr [esp + 0x24], eax
00695a4e mov eax, ecx
00695a50 and eax, 0x200
00695a55 or eax, 0
00695a58 je 0x695bf3
00695a5e movss xmm0, dword ptr [esi + 0xb7c]
00695a66 ucomiss xmm0, dword ptr [0xc02fec]
00695a6d mov edi, dword ptr [0xbfd65c]
00695a73 lahf 
00695a74 test ah, 0x44
00695a77 jp 0x695a8e
00695a79 movss xmm0, dword ptr [esi + 0xb80]
00695a81 ucomiss xmm0, dword ptr [0xc02ff0]
00695a88 lahf 
00695a89 test ah, 0x44
00695a8c jnp 0x695ac2
00695a8e and ecx, 0x4000
00695a94 or ecx, 0
00695a97 jne 0x695bd6
00695a9d mov ecx, edi
00695a9f call 0x6d0380
00695aa4 test al, al
00695aa6 jne 0x695bd6
00695aac mov eax, dword ptr [edi + 0x1a30dc]
00695ab2 mov ecx, 0xf
00695ab7 cdq 
00695ab8 idiv ecx
00695aba test edx, edx
00695abc jne 0x695bd6
00695ac2 call 0x6c3d90
00695ac7 movss xmm2, dword ptr [0xb6a19c]
00695acf movd xmm0, eax
00695ad3 cvtdq2pd xmm0, xmm0
00695ad7 shr eax, 0x1f
00695ada addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695ae3 cvtpd2ps xmm1, xmm0
00695ae7 mulss xmm1, xmm2
00695aeb call 0x6c3d90
00695af0 movd xmm0, eax
00695af4 cvtdq2pd xmm0, xmm0
00695af8 shr eax, 0x1f
00695afb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695b04 cvtpd2ps xmm0, xmm0
00695b08 mulss xmm0, xmm2
00695b0c mulss xmm0, xmm1
00695b10 mulss xmm0, dword ptr [0xb6abe4]
00695b18 movss dword ptr [esp + 0xc], xmm0
00695b1e call 0x6c3d90
00695b23 movd xmm0, eax
00695b27 cvtdq2pd xmm0, xmm0
00695b2b shr eax, 0x1f
00695b2e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695b37 cvtpd2ps xmm0, xmm0
00695b3b mulss xmm0, xmm2
00695b3f mulss xmm0, dword ptr [0xb6a874]
00695b47 addss xmm0, xmm0
00695b4b movss dword ptr [esp + 0x20], xmm0
00695b51 call 0x411fe0
00695b56 mulss xmm0, dword ptr [esp + 0xc]
00695b5c addss xmm0, dword ptr [esi + 0x294]
00695b64 movss dword ptr [esp + 0x18], xmm0
00695b6a movss xmm0, dword ptr [esp + 0x20]
00695b70 call 0x412010
00695b75 mulss xmm0, dword ptr [esp + 0xc]
00695b7b lea eax, [esp + 0x18]
00695b7f sub esp, 0xc
00695b82 mov ecx, dword ptr [edi + 0x18190]
00695b88 movss xmm3, dword ptr [esi + 0x2c8]
00695b90 addss xmm0, dword ptr [esi + 0x298]
00695b98 movss dword ptr [esp + 8], xmm3
00695b9e movss dword ptr [esp + 4], xmm3
00695ba4 movss dword ptr [esp], xmm3
00695ba9 push eax
00695baa lea eax, [esp + 0x30]
00695bae movss dword ptr [esp + 0x2c], xmm0
00695bb4 push eax
00695bb5 call 0x7cec10
00695bba movss xmm0, dword ptr [esp + 0x20]
00695bc0 movss dword ptr [esi + 0xb7c], xmm0
00695bc8 movss xmm0, dword ptr [esp + 0x24]
00695bce movss dword ptr [esi + 0xb80], xmm0
00695bd6 mov eax, dword ptr [ebp + 8]
00695bd9 mov ecx, dword ptr [esi + 0xb7c]
00695bdf mov edx, dword ptr [esi + 0xb80]
00695be5 mov dword ptr [eax + 4], edx
00695be8 mov dword ptr [eax], ecx
00695bea pop edi
00695beb pop esi
00695bec pop ebx
00695bed mov esp, ebp
00695bef pop ebp
00695bf0 ret 8
00695bf3 and ecx, 0x1000800
00695bf9 or ecx, 0
00695bfc je 0x695c0c
00695bfe mov eax, dword ptr [esi + 0x28]
00695c01 cmp eax, 0x10
00695c04 jne 0x695c30
00695c06 cmp dword ptr [esi + 0x2c], 2
00695c0a je 0x695c3c
00695c0c mov ecx, esi
00695c0e call 0x695680
00695c13 mov ecx, dword ptr [eax + 0x294]
00695c19 mov edx, dword ptr [eax + 0x298]
00695c1f mov eax, dword ptr [ebp + 8]
00695c22 mov dword ptr [eax + 4], edx
00695c25 mov dword ptr [eax], ecx
00695c27 pop edi
00695c28 pop esi
00695c29 pop ebx
00695c2a mov esp, ebp
00695c2c pop ebp
