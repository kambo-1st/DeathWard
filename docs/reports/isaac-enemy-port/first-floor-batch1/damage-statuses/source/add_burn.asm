00685ca0 push ebp
00685ca1 mov ebp, esp
00685ca3 and esp, 0xfffffff8
00685ca6 push ecx
00685ca7 push ebx
00685ca8 push esi
00685ca9 push edi
00685caa mov edi, dword ptr [ebp + 8]
00685cad mov esi, ecx
00685caf push edi
00685cb0 call 0x684b00
00685cb5 test al, al
00685cb7 jne 0x685e11
00685cbd cmp dword ptr [esi + 0x28], 1
00685cc1 jne 0x685cd9
00685cc3 push 0
00685cc5 push 0x278
00685cca mov ecx, esi
00685ccc call 0x73af30
00685cd1 test al, al
00685cd3 jne 0x685e11
00685cd9 push edi
00685cda push dword ptr [ebp + 0xc]
00685cdd mov ecx, esi
00685cdf call 0x685020
00685ce4 movss xmm1, dword ptr [ebp + 0x10]
00685ce9 xorps xmm0, xmm0
00685cec comiss xmm0, xmm1
00685cef mov edx, eax
00685cf1 jb 0x685d34
00685cf3 cmp dword ptr [esi + 0x28], 1
00685cf7 je 0x685d2c
00685cf9 mov ecx, dword ptr [edi + 0x24]
00685cfc test ecx, ecx
00685cfe je 0x685d2c
00685d00 mov eax, dword ptr [ecx + 0x320]
00685d06 test eax, eax
00685d08 je 0x685d1c
00685d0a nop word ptr [eax + eax]
00685d10 mov ecx, eax
00685d12 mov eax, dword ptr [ecx + 0x320]
00685d18 test eax, eax
00685d1a jne 0x685d10
00685d1c cmp dword ptr [ecx + 0x28], 1
00685d20 jne 0x685d2c
00685d22 movss xmm1, dword ptr [ecx + 0x14c0]
00685d2a jmp 0x685d34
00685d2c movss xmm1, dword ptr [0xb6a7b0]
00685d34 mov ecx, esi
00685d36 call 0x681710
00685d3b test al, al
00685d3d je 0x685d5c
00685d3f mov eax, dword ptr [esi + 0x314]
00685d45 test eax, eax
00685d47 je 0x685d5c
00685d49 nop dword ptr [eax]
00685d50 mov esi, eax
00685d52 mov eax, dword ptr [esi + 0x314]
00685d58 test eax, eax
00685d5a jne 0x685d50
00685d5c test edx, edx
00685d5e je 0x685e11
00685d64 mov edi, dword ptr [esi + 0x160]
00685d6a mov eax, edi
00685d6c mov ebx, dword ptr [esi + 0x164]
00685d72 and eax, 1
00685d75 or eax, 0
00685d78 jne 0x685e11
00685d7e cmp dword ptr [esi + 0x230], eax
00685d84 jg 0x685e11
00685d8a mov ecx, dword ptr [esi + 0x22c]
00685d90 test edx, edx
00685d92 jle 0x685da3
00685d94 lea eax, [ecx + edx]
00685d97 mov ecx, 0x78
00685d9c cmp eax, ecx
00685d9e cmovl ecx, eax
00685da1 jmp 0x685daa
00685da3 neg edx
00685da5 cmp ecx, edx
00685da7 cmovl ecx, edx
00685daa mov eax, edi
00685dac mov dword ptr [esi + 0x22c], ecx
00685db2 and eax, 0x1000
00685db7 or eax, 0
00685dba jne 0x685dc2
00685dbc mov dword ptr [esi + 0x23c], eax
00685dc2 movss xmm0, dword ptr [esi + 0x27c]
00685dca comiss xmm0, xmm1
00685dcd ja 0x685dd5
00685dcf movss xmm0, xmm1
00685dd3 jmp 0x685dd9
00685dd5 movss xmm0, xmm0
00685dd9 or edi, 0x1000
00685ddf mov ecx, esi
00685de1 movss dword ptr [esi + 0x27c], xmm0
00685de9 mov eax, dword ptr [esi]
00685deb mov dword ptr [esi + 0x160], edi
00685df1 mov dword ptr [esi + 0x164], ebx
00685df7 mov eax, dword ptr [eax + 0x48]
00685dfa call eax
00685dfc test al, al
00685dfe je 0x685e0a
00685e00 mov dword ptr [esi + 0x230], 0xf0
00685e0a mov ecx, esi
00685e0c call 0x681390
00685e11 pop edi
00685e12 pop esi
00685e13 pop ebx
00685e14 mov esp, ebp
00685e16 pop ebp
00685e17 ret 0xc
