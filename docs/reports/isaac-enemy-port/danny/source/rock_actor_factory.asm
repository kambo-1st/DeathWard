004e70a0 push ebp
004e70a1 mov ebp, esp
004e70a3 and esp, 0xfffffff8
004e70a6 sub esp, 0x34
004e70a9 mov eax, dword ptr [ebp + 0xc]
004e70ac movss dword ptr [esp + 4], xmm3
004e70b2 mov dword ptr [esp + 8], edx
004e70b6 mov dword ptr [esp], ecx
004e70b9 push ebx
004e70ba push esi
004e70bb push edi
004e70bc sub eax, 1
004e70bf je 0x4e70e0
004e70c1 sub eax, 1
004e70c4 je 0x4e70d9
004e70c6 sub eax, 1
004e70c9 je 0x4e70cf
004e70cb xor edi, edi
004e70cd jmp 0x4e70e5
004e70cf mov esi, 0x21
004e70d4 lea edi, [esi - 0x16]
004e70d7 jmp 0x4e70ea
004e70d9 mov edi, 2
004e70de jmp 0x4e70e5
004e70e0 mov edi, 1
004e70e5 mov esi, 0x332
004e70ea call 0x6c3d90
004e70ef mov ebx, dword ptr [ebp + 8]
004e70f2 mov ecx, dword ptr [0xbfd65c]
004e70f8 push 0
004e70fa push eax
004e70fb push 0
004e70fd push ebx
004e70fe push 0xc02fec
004e7103 push dword ptr [esp + 0x20]
004e7107 push edi
004e7108 push esi
004e7109 call 0x6d0ca0
004e710e mov esi, eax
004e7110 and dword ptr [esi + 0x160], 0xfffffffb
004e7117 mov ecx, dword ptr [esi + 0x164]
004e711d mov dword ptr [esi + 0x164], ecx
004e7123 test ebx, ebx
004e7125 je 0x4e719e
004e7127 mov ecx, dword ptr [ebx + 0x160]
004e712d and ecx, 0x100
004e7133 or ecx, 0
004e7136 je 0x4e719e
004e7138 movss xmm1, dword ptr [0xc02fec]
004e7140 lea eax, [esp + 0x18]
004e7144 movss xmm0, dword ptr [0xc02ff0]
004e714c mov ecx, esi
004e714e push -1
004e7150 push eax
004e7151 mov dword ptr [esp + 0x20], 0
004e7159 mov dword ptr [esp + 0x24], 0
004e7161 mov dword ptr [esp + 0x28], 0
004e7169 mov dword ptr [esp + 0x2c], 0
004e7171 movss dword ptr [esp + 0x30], xmm1
004e7177 movss dword ptr [esp + 0x34], xmm0
004e717d movss dword ptr [esp + 0x38], xmm1
004e7183 movss dword ptr [esp + 0x3c], xmm0
004e7189 mov dword ptr [esp + 0x40], 0
004e7191 mov dword ptr [esp + 0x44], 0
004e7199 call 0x685510
004e719e mov eax, dword ptr [esi]
004e71a0 mov ecx, esi
004e71a2 call dword ptr [eax + 0xc]
004e71a5 movss xmm0, dword ptr [esp + 0x10]
004e71ab mov dword ptr [esi + 0x2a4], 0
004e71b5 movss dword ptr [esi + 0x2a8], xmm0
004e71bd call 0x6c3d90
004e71c2 mov ecx, dword ptr [esp + 0x14]
004e71c6 movd xmm0, eax
004e71ca cvtdq2pd xmm0, xmm0
004e71ce shr eax, 0x1f
004e71d1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e71da cvtpd2ps xmm0, xmm0
004e71de mulss xmm0, dword ptr [0xb6a19c]
004e71e6 subss xmm0, dword ptr [0xb6a480]
004e71ee addss xmm0, xmm0
004e71f2 subss xmm0, dword ptr [0xb6a8cc]
004e71fa movss dword ptr [esi + 0xb00], xmm0
004e7202 mov eax, dword ptr [ecx]
004e7204 movss xmm0, dword ptr [0xb6af28]
004e720c comiss xmm0, dword ptr [esi + 0x2a8]
004e7213 mov dword ptr [esi + 0x2b8], eax
004e7219 mov eax, dword ptr [ecx + 4]
004e721c mov dword ptr [esi + 0x2bc], eax
004e7222 mov eax, esi
004e7224 mov dword ptr [esi + 0xab4], 0x10
004e722e jbe 0x4e7244
004e7230 mov dword ptr [esi + 0x17c], 3
004e723a mov dword ptr [esi + 0x180], 0
004e7244 pop edi
004e7245 pop esi
004e7246 pop ebx
004e7247 mov esp, ebp
004e7249 pop ebp
004e724a ret 
