00700c60 push ebp
00700c61 mov ebp, esp
00700c63 and esp, 0xfffffff8
00700c66 sub esp, 0x24
00700c69 mov eax, dword ptr [ebp + 0xc]
00700c6c xorps xmm0, xmm0
00700c6f push ebx
00700c70 mov bl, al
00700c72 mov dword ptr [esp + 0xc], ecx
00700c76 mov ecx, dword ptr [ebp + 8]
00700c79 mov edx, eax
00700c7b shr eax, 3
00700c7e not bl
00700c80 push esi
00700c81 and al, 1
00700c83 shr edx, 1
00700c85 push edi
00700c86 mov edi, dword ptr [ecx + 4]
00700c89 and bl, 1
00700c8c mov esi, edi
00700c8e mov dword ptr [ebp + 0xc], eax
00700c91 mov eax, dword ptr [ecx + 8]
00700c94 and edx, 0xffffff01
00700c9a mov byte ptr [esp + 0xe], bl
00700c9e xorps xmm2, xmm2
00700ca1 mov dword ptr [esp + 0x1c], edx
00700ca5 mov dword ptr [esp + 0x10], esi
00700ca9 cmp esi, eax
00700cab je 0x700e3c
00700cb1 mov edi, eax
00700cb3 test dl, dl
00700cb5 mov eax, 0x14
00700cba mov ecx, 0xa
00700cbf cmove eax, ecx
00700cc2 mov dword ptr [esp + 0x18], eax
00700cc6 movss xmm3, dword ptr [esi + 4]
00700ccb mov eax, edi
00700ccd movaps xmm0, xmm3
00700cd0 mov dword ptr [esp + 0x2c], eax
00700cd4 addss xmm2, xmm0
00700cd8 comiss xmm2, xmm1
00700cdb jbe 0x700e21
00700ce1 subss xmm2, xmm1
00700ce5 movss xmm0, dword ptr [0xb6a614]
00700ced mov eax, dword ptr [0xbfd65c]
00700cf2 mov ecx, dword ptr [esi]
00700cf4 mov edx, dword ptr [0xbfd680]
00700cfa divss xmm2, xmm3
00700cfe movaps xmm1, xmm2
00700d01 movss dword ptr [esp + 0x28], xmm1
00700d07 subss xmm0, xmm1
00700d0b movss dword ptr [esp + 0x24], xmm0
00700d11 movss xmm0, dword ptr [esi + 8]
00700d16 divss xmm0, xmm3
00700d1a movss dword ptr [esp + 0x20], xmm0
00700d20 test eax, eax
00700d22 je 0x700d4e
00700d24 test ecx, ecx
00700d26 jns 0x700d52
00700d28 not ecx
00700d2a test ecx, ecx
00700d2c js 0x700d4a
00700d2e mov edx, dword ptr [eax + 0x283c20]
00700d34 mov eax, dword ptr [eax + 0x283c24]
00700d3a sub eax, edx
00700d3c sar eax, 2
00700d3f cmp ecx, eax
00700d41 jge 0x700d4a
00700d43 mov eax, dword ptr [edx + ecx*4]
00700d46 mov ebx, dword ptr [eax]
00700d48 jmp 0x700d6a
00700d4a xor ebx, ebx
00700d4c jmp 0x700d6a
00700d4e test ecx, ecx
00700d50 js 0x700d99
00700d52 mov eax, dword ptr [edx + 0x29e88]
00700d58 mov ebx, dword ptr [edx + 0x29e84]
00700d5e sub eax, ebx
00700d60 sar eax, 2
00700d63 cmp ecx, eax
00700d65 jge 0x700d99
00700d67 mov ebx, dword ptr [ebx + ecx*4]
00700d6a test ebx, ebx
00700d6c je 0x700d99
00700d6e push -1
00700d70 mov ecx, ebx
00700d72 call 0x6fe950
00700d77 test al, al
00700d79 je 0x700d99
00700d7b cmp byte ptr [esp + 0x1c], 0
00700d80 je 0x700d87
00700d82 cmp dword ptr [ebx], 3
00700d85 je 0x700d99
00700d87 cmp byte ptr [ebp + 0xc], 0
00700d8b je 0x700d92
00700d8d cmp dword ptr [ebx], 3
00700d90 jne 0x700d99
00700d92 mov byte ptr [esp + 0xf], 1
00700d97 jmp 0x700d9e
00700d99 mov byte ptr [esp + 0xf], 0
00700d9e movss xmm0, dword ptr [esp + 0x20]
00700da4 comiss xmm0, dword ptr [esp + 0x24]
00700da9 jbe 0x700de1
00700dab mov eax, dword ptr [esp + 0x14]
00700daf mov ebx, 1
00700db4 mov ecx, dword ptr [esi]
00700db6 mov edx, ecx
00700db8 shr edx, 5
00700dbb and ecx, 0x1f
00700dbe shl ebx, cl
00700dc0 mov eax, dword ptr [eax + 0x67c]
00700dc6 test dword ptr [eax + edx*4], ebx
00700dc9 jne 0x700de1
00700dcb mov eax, dword ptr [esp + 0x14]
00700dcf mov eax, dword ptr [eax + 0x68c]
00700dd5 test dword ptr [eax + edx*4], ebx
00700dd8 jne 0x700de1
00700dda cmp byte ptr [esp + 0xf], 0
00700ddf jne 0x700e50
00700de1 mov edx, dword ptr [esp + 0x18]
00700de5 test edx, edx
00700de7 jle 0x700e54
00700de9 mov ecx, dword ptr [ebp + 8]
00700dec xorps xmm2, xmm2
00700def movss xmm0, dword ptr [ecx]
00700df3 movaps xmm1, xmm0
00700df6 mulss xmm1, dword ptr [esp + 0x28]
00700dfc ucomiss xmm1, xmm0
00700dff lahf
00700e00 test ah, 0x44
00700e03 jp 0x700e10
00700e05 movaps xmm1, xmm0
00700e08 divss xmm1, dword ptr [0xb6a880]
00700e10 mov esi, dword ptr [ecx + 4]
00700e13 dec edx
00700e14 mov edi, dword ptr [ecx + 8]
00700e17 mov eax, dword ptr [esp + 0x2c]
00700e1b mov dword ptr [esp + 0x18], edx
00700e1f jmp 0x700e24
00700e21 add esi, 0x18
00700e24 mov dword ptr [esp + 0x10], esi
00700e28 cmp esi, edi
00700e2a jne 0x700cc6
00700e30 mov edi, eax
00700e32 mov ecx, dword ptr [ebp + 8]
00700e35 mov bl, byte ptr [esp + 0xe]
00700e39 xorps xmm0, xmm0
00700e3c cmp edi, dword ptr [ecx + 8]
00700e3f jne 0x700f88
00700e45 xor eax, eax
00700e47 pop edi
00700e48 pop esi
00700e49 pop ebx
00700e4a mov esp, ebp
00700e4c pop ebp
00700e4d ret 8
00700e50 mov edi, esi
00700e52 jmp 0x700e32
