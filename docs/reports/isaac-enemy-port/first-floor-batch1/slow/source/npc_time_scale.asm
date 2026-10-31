00690ad0 push ebp
00690ad1 mov ebp, esp
00690ad3 and esp, 0xfffffff8
00690ad6 sub esp, 0xc
00690ad9 push ebx
00690ada push esi
00690adb mov esi, ecx
00690add push edi
00690ade push esi
00690adf push ecx
00690ae0 mov ecx, dword ptr [0xbfd65c]
00690ae6 mov ecx, dword ptr [ecx + 0x18190]
00690aec call 0x7a8ef0
00690af1 mov edi, dword ptr [esi + 0x160]
00690af7 mov eax, edi
00690af9 mov ebx, dword ptr [esi + 0x164]
00690aff and eax, 0x20000000
00690b04 movss xmm1, dword ptr [0xb6a480]
00690b0c or eax, 0
00690b0f mov eax, dword ptr [0xbfd65c]
00690b14 movss dword ptr [esp + 0xc], xmm0
00690b1a mov eax, dword ptr [eax + 0x18190]
00690b20 je 0x690b3e
00690b22 cmp dword ptr [eax + 0x7120], 0
00690b29 jle 0x690c21
00690b2f mulss xmm0, xmm1
00690b33 movss dword ptr [esp + 0xc], xmm0
00690b39 jmp 0x690c21
00690b3e mov dword ptr [esp + 0x10], eax
00690b42 add eax, 0x71f4
00690b47 push 0xe8
00690b4c mov ecx, eax
00690b4e mov dword ptr [esp + 0x18], eax
00690b52 call 0x88b570
00690b57 test al, al
00690b59 jne 0x690bf9
00690b5f mov eax, dword ptr [0xbfd65c]
00690b64 cmp dword ptr [eax + 0x1c319c], 0x16
00690b6b je 0x690b7a
00690b6d mov eax, dword ptr [esp + 0x10]
00690b71 cmp dword ptr [eax + 0x1210], 1
00690b78 je 0x690bf9
00690b7a mov ecx, dword ptr [esp + 0x14]
00690b7e push 0x42
00690b80 call 0x88b7c0
00690b85 test eax, eax
00690b87 je 0x690c13
00690b8d movd xmm1, dword ptr [eax + 8]
00690b92 lea ecx, [esp + 0x10]
00690b96 cvtdq2ps xmm1, xmm1
00690b99 mov dword ptr [esp + 0x14], 0
00690ba1 lea eax, [esp + 0x14]
00690ba5 xorps xmm0, xmm0
00690ba8 subss xmm1, xmm0
00690bac divss xmm1, dword ptr [0xb6aa0c]
00690bb4 comiss xmm0, xmm1
00690bb7 movss dword ptr [esp + 0x10], xmm1
00690bbd movss xmm1, dword ptr [0xb6a614]
00690bc5 cmovbe eax, ecx
00690bc8 movss xmm0, dword ptr [eax]
00690bcc comiss xmm0, xmm1
00690bcf ja 0x690bd7
00690bd1 movss xmm0, xmm0
00690bd5 jmp 0x690bdb
00690bd7 movss xmm0, xmm1
00690bdb mulss xmm0, dword ptr [0xb6a480]
00690be3 subss xmm1, xmm0
00690be7 movss xmm0, dword ptr [esp + 0xc]
00690bed mulss xmm0, xmm1
00690bf1 movss dword ptr [esp + 0xc], xmm0
00690bf7 jmp 0x690c19
00690bf9 movss xmm0, dword ptr [esp + 0xc]
00690bff movss xmm1, dword ptr [0xb6a480]
00690c07 mulss xmm0, xmm1
00690c0b movss dword ptr [esp + 0xc], xmm0
00690c11 jmp 0x690c21
00690c13 movss xmm0, dword ptr [esp + 0xc]
00690c19 movss xmm1, dword ptr [0xb6a480]
00690c21 and edi, 0x80
00690c27 or edi, 0
00690c2a je 0x690c3f
00690c2c cmp dword ptr [esi + 0xab4], 0x12
00690c33 je 0x690c3f
00690c35 mulss xmm0, xmm1
00690c39 movss dword ptr [esp + 0xc], xmm0
00690c3f and ebx, 0x400000
00690c45 xor eax, eax
00690c47 or eax, ebx
00690c49 je 0x690c59
00690c4b mulss xmm0, dword ptr [0xb6a4dc]
00690c53 movss dword ptr [esp + 0xc], xmm0
00690c59 mov eax, dword ptr [esi]
00690c5b mov ecx, esi
00690c5d mov eax, dword ptr [eax + 0x48]
00690c60 call eax
00690c62 test al, al
00690c64 je 0x690caa
00690c66 mov eax, dword ptr [esi + 0x160]
00690c6c and eax, 0x20000000
00690c71 or eax, 0
00690c74 jne 0x690caa
00690c76 mov eax, dword ptr [0xbfd65c]
00690c7b push 0x2b9
00690c80 mov ecx, dword ptr [eax + 0x18190]
00690c86 add ecx, 0x71f4
00690c8c call 0x88b570
00690c91 movss xmm0, dword ptr [esp + 0xc]
00690c97 test al, al
00690c99 je 0x690cb0
00690c9b mulss xmm0, dword ptr [0xb6a53c]
00690ca3 pop edi
00690ca4 pop esi
00690ca5 pop ebx
00690ca6 mov esp, ebp
00690ca8 pop ebp
00690ca9 ret 
00690caa movss xmm0, dword ptr [esp + 0xc]
00690cb0 pop edi
00690cb1 pop esi
00690cb2 pop ebx
00690cb3 mov esp, ebp
00690cb5 pop ebp
00690cb6 ret 
