00686d98 and ecx, 0x4000
00686d9e or ecx, 0
00686da1 jne 0x687038
00686da7 cmp byte ptr [edi + 0x308], cl
00686dad jne 0x68701d
00686db3 mov esi, dword ptr [edi + 8]
00686db6 mov byte ptr [esp + 0x1b], cl
00686dba cmp esi, dword ptr [edi + 0xc]
00686dbd je 0x68701d
00686dc3 xorps xmm0, xmm0
00686dc6 nop word ptr [eax + eax]
00686dd0 movss xmm1, dword ptr [esi]
00686dd4 comiss xmm1, xmm0
00686dd7 jbe 0x686ffc
00686ddd mov ecx, dword ptr [0xbfd65c]
00686de3 mov eax, dword ptr [ecx + 0x1c3164]
00686de9 shr eax, 6
00686dec test al, 1
00686dee je 0x686e1b
00686df0 movaps xmm0, xmmword ptr [0xb6c360]
00686df7 lea eax, [esp + 0x50]
00686dfb movups xmmword ptr [esp + 0x50], xmm0
00686e00 sub esp, 8
00686e03 cvtps2pd xmm0, xmm1
00686e06 movsd qword ptr [esp], xmm0
00686e0b push 0xb48eac
00686e10 push eax
00686e11 push edx
00686e12 push ecx
00686e13 call 0x6d59e0
00686e18 add esp, 0x18
00686e1b mov eax, dword ptr [esi + 0xc]
00686e1e mov ecx, dword ptr [esi + 8]
00686e21 mov dword ptr [esp + 0x54], eax
00686e25 mov eax, ecx
00686e27 and eax, 0x202
00686e2c or eax, 0
00686e2f je 0x686e81
00686e31 and ecx, 4
00686e34 or ecx, 0
00686e37 jne 0x686e81
00686e39 mov edi, dword ptr [0xbfd680]
00686e3f lea ecx, [esp + 0x30]
00686e43 mov dword ptr [esp + 0x30], 0x2b
00686e4b call 0x8b1340
00686e50 sub esp, 8
00686e53 mov dword ptr [esp + 4], 0
00686e5b mov dword ptr [esp], 0x3f800000
00686e62 push 0
00686e64 push 2
00686e66 push ecx
00686e67 mov dword ptr [esp], 0x3f800000
00686e6e lea ecx, [edi + 0x29de0]
00686e74 push dword ptr [esp + 0x44]
00686e78 call 0x888de0
00686e7d mov edi, dword ptr [esp + 0x3c]
00686e81 movss xmm0, dword ptr [edi + 0x2d8]
00686e89 xorps xmm1, xmm1
00686e8c subss xmm0, dword ptr [esi]
00686e90 comiss xmm1, xmm0
00686e93 movss dword ptr [edi + 0x2d8], xmm0
00686e9b jb 0x686eb6
00686e9d mov eax, dword ptr [esi + 8]
00686ea0 and eax, 1
00686ea3 or eax, 0
00686ea6 jne 0x686eb6
00686ea8 mov al, 1
00686eaa xorps xmm0, xmm0
00686ead mov byte ptr [esp + 0x1b], al
00686eb1 jmp 0x687000
