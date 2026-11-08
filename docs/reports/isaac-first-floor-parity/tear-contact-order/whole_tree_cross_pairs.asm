00416f10 push ebp
00416f11 mov ebp, esp
00416f13 and esp, 0xfffffff8
00416f16 sub esp, 0x34
00416f19 mov eax, dword ptr [ebp + 8]
00416f1c push ebx
00416f1d mov ebx, ecx
00416f1f push esi
00416f20 mov ecx, dword ptr [eax + 0x1c]
00416f23 sub ecx, dword ptr [eax + 0x18]
00416f26 mov eax, 0x63e7063f
00416f2b imul ecx
00416f2d push edi
00416f2e mov edi, dword ptr [ebx + 0x1c]
00416f31 mov eax, 0x63e7063f
00416f36 sar edx, 6
00416f39 mov ecx, edi
00416f3b sub ecx, dword ptr [ebx + 0x18]
00416f3e mov esi, edx
00416f40 shr esi, 0x1f
00416f43 add esi, edx
00416f45 mov dword ptr [esp + 0x3c], ebx
00416f49 imul ecx
00416f4b sar edx, 6
00416f4e mov eax, edx
00416f50 shr eax, 0x1f
00416f53 add eax, edx
00416f55 cmp eax, esi
00416f57 je 0x416f6b
00416f59 push 0xb3f644
00416f5e push 3
00416f60 call 0x95e330
00416f65 mov edi, dword ptr [ebx + 0x1c]
00416f68 add esp, 8
00416f6b mov eax, dword ptr [ebx]
00416f6d mov esi, dword ptr [ebx + 0x18]
00416f70 sub edi, esi
00416f72 mov dword ptr [esp + 0x24], eax
00416f76 mov dword ptr [esp + 0x18], 0
00416f7e mov eax, dword ptr [eax + 0xd4]
00416f84 mov dword ptr [esp + 0x20], eax
00416f88 mov eax, 0x63e7063f
00416f8d imul edi
00416f8f sar edx, 6
00416f92 mov eax, edx
00416f94 shr eax, 0x1f
00416f97 add eax, edx
00416f99 je 0x417131
00416f9f xor ebx, ebx
00416fa1 xor edi, edi
00416fa3 mov dword ptr [esp + 0x1c], ebx
00416fa7 mov eax, dword ptr [ebp + 8]
00416faa lea ecx, [ebx + esi]
00416fad xor edx, edx
00416faf mov dword ptr [esp + 0x10], ecx
00416fb3 mov dword ptr [esp + 0x14], edx
00416fb7 mov eax, dword ptr [eax + 0x18]
00416fba add eax, ebx
00416fbc lea ebx, [ecx + 0xa0]
00416fc2 mov dword ptr [esp + 0x34], eax
00416fc6 mov dword ptr [esp + 0x38], ebx
00416fca cmp dword ptr [ebx], edx
00416fcc jbe 0x4170f9
00416fd2 xor ebx, ebx
00416fd4 cmp dword ptr [eax + 0xa0], ebx
00416fda jbe 0x4170dd
00416fe0 mov edi, dword ptr [ecx]
00416fe2 mov esi, dword ptr [eax + ebx*4]
00416fe5 mov ecx, dword ptr [edi + 0x24]
00416fe8 mov edx, ecx
00416fea mov eax, dword ptr [esi + 0x24]
00416fed cmp ecx, eax
00416fef cmovl edx, eax
00416ff2 imul edx, dword ptr [esp + 0x20]
00416ff7 cmp eax, ecx
00416ff9 cmovl ecx, eax
00416ffc add edx, ecx
00416ffe cmp edi, esi
00417000 je 0x4170c4
00417006 mov ecx, dword ptr [esp + 0x24]
0041700a cmp edx, dword ptr [ecx + 0xd0]
00417010 jge 0x4170c4
00417016 mov ecx, dword ptr [ecx + 0xc4]
0041701c mov eax, edx
0041701e shr eax, 5
00417021 and edx, 0x1f
00417024 mov dword ptr [esp + 0x2c], eax
00417028 mov dword ptr [esp + 0x30], ecx
0041702c mov eax, dword ptr [ecx + eax*4]
0041702f mov ecx, edx
00417031 mov dword ptr [esp + 0x28], eax
00417035 mov eax, 1
0041703a shl eax, cl
0041703c mov ecx, dword ptr [esp + 0x28]
00417040 test ecx, eax
00417042 jne 0x4170c4
00417048 mov eax, dword ptr [esp + 0x2c]
0041704c bts ecx, edx
0041704f mov edx, dword ptr [esp + 0x30]
00417053 mov dword ptr [edx + eax*4], ecx
00417056 movss xmm0, dword ptr [edi + 0x2cc]
0041705e movss xmm2, dword ptr [0xbc7a28]
00417066 ucomiss xmm0, xmm2
00417069 lahf 
0041706a test ah, 0x44
0041706d jp 0x4170b5
0041706f movss xmm0, dword ptr [edi + 0x2d0]
00417077 movss xmm1, dword ptr [0xbc7a2c]
0041707f ucomiss xmm0, xmm1
00417082 lahf 
00417083 test ah, 0x44
00417086 jp 0x4170b5
00417088 movss xmm0, dword ptr [esi + 0x2cc]
00417090 ucomiss xmm0, xmm2
00417093 lahf 
00417094 test ah, 0x44
00417097 jp 0x4170b5
00417099 movss xmm0, dword ptr [esi + 0x2d0]
004170a1 ucomiss xmm0, xmm1
004170a4 lahf 
004170a5 test ah, 0x44
004170a8 jp 0x4170b5
004170aa mov edx, esi
004170ac mov ecx, edi
004170ae call 0x689cf0
004170b3 jmp 0x4170be
004170b5 mov edx, esi
004170b7 mov ecx, edi
004170b9 call 0x689980
004170be inc dword ptr [0xbfd640]
004170c4 mov eax, dword ptr [esp + 0x34]
004170c8 inc ebx
004170c9 mov ecx, dword ptr [esp + 0x10]
004170cd cmp ebx, dword ptr [eax + 0xa0]
004170d3 jb 0x416fe0
004170d9 mov edx, dword ptr [esp + 0x14]
004170dd mov ebx, dword ptr [esp + 0x38]
004170e1 inc edx
004170e2 add ecx, 4
004170e5 mov dword ptr [esp + 0x14], edx
004170e9 mov dword ptr [esp + 0x10], ecx
004170ed cmp edx, dword ptr [ebx]
004170ef jb 0x416fd2
004170f5 mov edi, dword ptr [esp + 0x18]
004170f9 mov eax, dword ptr [esp + 0x3c]
004170fd inc edi
004170fe mov ebx, dword ptr [esp + 0x1c]
00417102 add ebx, 0xa4
00417108 mov dword ptr [esp + 0x18], edi
0041710c mov dword ptr [esp + 0x1c], ebx
00417110 mov ecx, dword ptr [eax + 0x1c]
00417113 mov esi, dword ptr [eax + 0x18]
00417116 sub ecx, esi
00417118 mov eax, 0x63e7063f
0041711d imul ecx
0041711f sar edx, 6
00417122 mov eax, edx
00417124 shr eax, 0x1f
00417127 add eax, edx
00417129 cmp edi, eax
0041712b jb 0x416fa7
00417131 pop edi
00417132 pop esi
00417133 pop ebx
00417134 mov esp, ebp
00417136 pop ebp
00417137 ret 4
0041713a int3 
0041713b int3 
0041713c int3 
0041713d int3 
