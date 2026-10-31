0052fcb0 push ebp
0052fcb1 mov ebp, esp
0052fcb3 sub esp, 0xbc
0052fcb9 mov eax, dword ptr [0xbaa3b4]
0052fcbe xor eax, ebp
0052fcc0 mov dword ptr [ebp - 4], eax
0052fcc3 push esi
0052fcc4 mov esi, ecx
0052fcc6 mov eax, dword ptr [esi + 0xab4]
0052fccc test eax, eax
0052fcce jne 0x52fd2f
0052fcd0 cmp dword ptr [esi + 0xe6c], -1
0052fcd7 mov dword ptr [esi + 0xab4], 3
0052fce1 je 0x52fcea
0052fce3 mov eax, 0x1e
0052fce8 jmp 0x52fd02
0052fcea call 0x6c3d90
0052fcef xor edx, edx
0052fcf1 mov ecx, 5
0052fcf6 div ecx
0052fcf8 inc edx
0052fcf9 mov eax, edx
0052fcfb shl eax, 4
0052fcfe sub eax, edx
0052fd00 add eax, eax
0052fd02 mov dword ptr [esi + 0x360], eax
0052fd08 mov eax, dword ptr [esi + 0x294]
0052fd0e mov dword ptr [esi + 0x28c], eax
0052fd14 mov eax, dword ptr [esi + 0x298]
0052fd1a mov dword ptr [esi + 0x290], eax
0052fd20 pop esi
0052fd21 mov ecx, dword ptr [ebp - 4]
0052fd24 xor ecx, ebp
0052fd26 call 0x9eacd7
0052fd2b mov esp, ebp
0052fd2d pop ebp
0052fd2e ret 
0052fd2f movss xmm1, dword ptr [esi + 0x14]
0052fd34 xorps xmm0, xmm0
0052fd37 comiss xmm1, xmm0
0052fd3a mov edx, eax
0052fd3c jbe 0x52fd79
0052fd3e cmp eax, 3
0052fd41 jne 0x52fd79
0052fd43 mov eax, dword ptr [esi + 8]
0052fd46 mov ecx, dword ptr [esi + 0xc]
0052fd49 cmp eax, ecx
0052fd4b je 0x52fd79
0052fd4d movss xmm1, dword ptr [0xb6a38c]
0052fd55 nop word ptr [eax + eax]
0052fd60 movss xmm0, dword ptr [eax]
0052fd64 mulss xmm0, xmm1
0052fd68 movss dword ptr [eax], xmm0
0052fd6c add eax, 0x38
0052fd6f cmp eax, ecx
0052fd71 jne 0x52fd60
0052fd73 mov edx, dword ptr [esi + 0xab4]
0052fd79 add edx, -3
0052fd7c cmp edx, 0xd
0052fd7f ja 0x530125
0052fd85 movzx eax, byte ptr [edx + 0x53018c]
0052fd8c jmp dword ptr [eax*4 + 0x53017c]
0052fd93 cmp dword ptr [esi + 0xb10], 0
0052fd9a lea ecx, [esi + 0x3c]
0052fd9d push 0
0052fd9f jne 0x52fdc9
0052fda1 push 0xb421d4
0052fda6 call 0x4054f0
0052fdab cmp dword ptr [esi + 0x70], 0
0052fdaf je 0x52fdbe
0052fdb1 cmp byte ptr [esi + 0x80], 0
0052fdb8 jne 0x530125
0052fdbe inc dword ptr [esi + 0xb10]
0052fdc4 jmp 0x530125
0052fdc9 push 0xb433d0
0052fdce call 0x4054f0
0052fdd3 cvttss2si eax, dword ptr [esi + 0x2fc]
0052fddb cvttss2si ecx, dword ptr [esi + 0x2f8]
0052fde3 sub ecx, eax
0052fde5 add dword ptr [esi + 0x360], ecx
0052fdeb cmp dword ptr [esi + 0x360], 0
0052fdf2 jg 0x530125
0052fdf8 cmp dword ptr [esi + 0xe6c], -1
0052fdff je 0x52fe29
0052fe01 movss xmm1, dword ptr [0xb6accc]
0052fe09 mov ecx, esi
0052fe0b push 7
0052fe0d push 0
0052fe0f call 0x6a15a0
0052fe14 test al, al
0052fe16 jne 0x52fe29
0052fe18 push 9
0052fe1a mov ecx, esi
0052fe1c call 0x6af050
0052fe21 test al, al
0052fe23 je 0x530125
0052fe29 call 0x6c3d90
0052fe2e and eax, 1
0052fe31 or eax, 8
0052fe34 cmp dword ptr [esi + 0xe6c], -1
0052fe3b mov dword ptr [esi + 0xab4], eax
0052fe41 je 0x530125
0052fe47 push 9
0052fe49 mov ecx, esi
0052fe4b call 0x6af050
0052fe50 xor ecx, ecx
0052fe52 test al, al
0052fe54 push 1
0052fe56 setne cl
0052fe59 add ecx, 8
0052fe5c mov dword ptr [esi + 0xab4], ecx
0052fe62 mov ecx, esi
0052fe64 call 0x6afe20
0052fe69 jmp 0x530125
0052fe6e cmp dword ptr [esi + 0xe6c], -1
0052fe75 jne 0x52fe91
0052fe77 movss xmm0, dword ptr [0xc02fec]
0052fe7f movss dword ptr [esi + 0xe70], xmm0
0052fe87 movss xmm0, dword ptr [0xc02ff0]
0052fe8f jmp 0x52fed9
0052fe91 movss xmm2, dword ptr [0xb6a2cc]
0052fe99 lea eax, [ebp - 0xb8]
0052fe9f push eax
0052fea0 mov ecx, esi
0052fea2 call 0x6af380
0052fea7 movss xmm1, dword ptr [ebp - 0xb8]
0052feaf ucomiss xmm1, dword ptr [0xc02fec]
0052feb6 movss xmm0, dword ptr [ebp - 0xb4]
0052febe lahf 
0052febf test ah, 0x44
0052fec2 jp 0x52fed1
0052fec4 ucomiss xmm0, dword ptr [0xc02ff0]
0052fecb lahf 
0052fecc test ah, 0x44
0052fecf jnp 0x52fee1
0052fed1 movss dword ptr [esi + 0xe70], xmm1
0052fed9 movss dword ptr [esi + 0xe74], xmm0
0052fee1 cmp dword ptr [esi + 0xe6c], -1
0052fee8 je 0x52ff51
0052feea movss xmm1, dword ptr [esi + 0xe70]
0052fef2 ucomiss xmm1, dword ptr [0xc02fec]
0052fef9 lahf 
0052fefa test ah, 0x44
0052fefd jp 0x52ff14
0052feff movss xmm0, dword ptr [esi + 0xe74]
0052ff07 ucomiss xmm0, dword ptr [0xc02ff0]
0052ff0e lahf 
0052ff0f test ah, 0x44
0052ff12 jnp 0x52ff51
0052ff14 movss xmm0, dword ptr [esi + 0xe74]
0052ff1c call 0x447a80
0052ff21 mulss xmm0, dword ptr [0xb6aa84]
0052ff29 addss xmm0, dword ptr [0xb6ac40]
0052ff31 addss xmm0, dword ptr [0xb6a9d4]
0052ff39 divss xmm0, dword ptr [0xb6aa4c]
0052ff41 cvttss2si eax, xmm0
0052ff45 and eax, 1
0052ff48 add eax, 8
0052ff4b mov dword ptr [esi + 0xab4], eax
0052ff51 push 0
0052ff53 push 0xb42214
0052ff58 lea ecx, [esi + 0x3c]
0052ff5b call 0x4054f0
0052ff60 cmp dword ptr [esi + 0x70], 0
0052ff64 je 0x52fff0
0052ff6a push 0xb400ac
0052ff6f lea ecx, [esi + 0x6c]
0052ff72 call 0x405e90
0052ff77 test al, al
0052ff79 je 0x52ffdd
0052ff7b push ecx
0052ff7c mov dword ptr [esp], 0x3f800000
0052ff83 push 0
0052ff85 push 2
0052ff87 push ecx
0052ff88 mov dword ptr [esp], 0x3f800000
0052ff8f mov ecx, esi
0052ff91 push 0x48
0052ff93 call 0x6ad720
0052ff98 lea ecx, [ebp - 0xb0]
0052ff9e mov dword ptr [ebp - 0xb8], 0x40e00000
0052ffa8 mov dword ptr [ebp - 0xb4], 0
0052ffb2 call 0x430d70
0052ffb7 push eax
0052ffb8 xor eax, eax
0052ffba mov ecx, esi
0052ffbc cmp dword ptr [esi + 0xab4], 9
0052ffc3 sete al
0052ffc6 add eax, 6
0052ffc9 push eax
0052ffca lea eax, [ebp - 0xb8]
0052ffd0 push eax
0052ffd1 lea eax, [esi + 0x294]
0052ffd7 push eax
0052ffd8 call 0x6a1a20
0052ffdd cmp dword ptr [esi + 0x70], 0
0052ffe1 je 0x52fff0
0052ffe3 cmp byte ptr [esi + 0x80], 0
0052ffea jne 0x530125
0052fff0 cmp dword ptr [esi + 0xe6c], -1
0052fff7 je 0x53000d
0052fff9 mov eax, 0x1e
0052fffe mov dword ptr [esi + 0xab4], 0x10
00530008 jmp 0x53011f
0053000d call 0x6c3d90
00530012 xor edx, edx
00530014 mov dword ptr [esi + 0xab4], 0x10
0053001e mov ecx, 3
00530023 div ecx
00530025 inc edx
00530026 mov eax, edx
00530028 shl eax, 4
0053002b sub eax, edx
0053002d add eax, eax
0053002f jmp 0x53011f
00530034 cmp dword ptr [esi + 0x360], 0
0053003b lea ecx, [esi + 0x3c]
0053003e push 0
00530040 jle 0x5300d4
00530046 push 0xb433ac
0053004b call 0x4054f0
00530050 cvttss2si eax, dword ptr [esi + 0x2fc]
00530058 cvttss2si ecx, dword ptr [esi + 0x2f8]
00530060 sub ecx, eax
00530062 add dword ptr [esi + 0x360], ecx
00530068 cmp dword ptr [esi + 0x360], 0
0053006f jg 0x530125
00530075 cmp dword ptr [esi + 0xe6c], -1
0053007c je 0x5300ac
0053007e movss xmm1, dword ptr [0xb6accc]
00530086 mov ecx, esi
00530088 push 7
0053008a push 0
0053008c call 0x6a15a0
00530091 test al, al
00530093 jne 0x5300a2
00530095 push 9
00530097 mov ecx, esi
00530099 call 0x6af050
0053009e test al, al
005300a0 je 0x5300ac
005300a2 mov dword ptr [esi + 0x360], 1
005300ac cmp dword ptr [esi + 0x360], 0
005300b3 jg 0x530125
005300b5 push ecx
005300b6 mov dword ptr [esp], 0x3f800000
005300bd push 0
005300bf push 2
005300c1 push ecx
005300c2 mov dword ptr [esp], 0x3f000000
005300c9 mov ecx, esi
005300cb push 0x26
005300cd call 0x6ad720
005300d2 jmp 0x530125
005300d4 push 0xb421d4
005300d9 call 0x4054f0
005300de cmp dword ptr [esi + 0x70], 0
005300e2 je 0x5300ed
005300e4 cmp byte ptr [esi + 0x80], 0
005300eb jne 0x530125
005300ed cmp dword ptr [esi + 0xe6c], -1
005300f4 mov dword ptr [esi + 0xab4], 3
005300fe je 0x530107
00530100 mov eax, 0x1e
00530105 jmp 0x53011f
00530107 call 0x6c3d90
0053010c xor edx, edx
0053010e mov ecx, 5
00530113 div ecx
00530115 inc edx
00530116 mov eax, edx
00530118 shl eax, 4
0053011b sub eax, edx
0053011d add eax, eax
0053011f mov dword ptr [esi + 0x360], eax
00530125 movss xmm0, dword ptr [esi + 0x2c4]
0053012d mulss xmm0, dword ptr [0xb6a560]
00530135 mov ecx, dword ptr [ebp - 4]
00530138 xor ecx, ebp
0053013a movss dword ptr [esi + 0x2c4], xmm0
00530142 movss xmm1, dword ptr [esi + 0x28c]
0053014a movss xmm0, dword ptr [esi + 0x290]
00530152 subss xmm1, dword ptr [esi + 0x294]
0053015a subss xmm0, dword ptr [esi + 0x298]
00530162 movss dword ptr [esi + 0x2b8], xmm1
0053016a movss dword ptr [esi + 0x2bc], xmm0
00530172 pop esi
00530173 call 0x9eacd7
00530178 mov esp, ebp
0053017a pop ebp
0053017b ret 
