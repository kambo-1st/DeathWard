008cbe80 push ebp
008cbe81 mov ebp, esp
008cbe83 and esp, 0xfffffff8
008cbe86 sub esp, 0x1c
008cbe89 push ebx
008cbe8a push esi
008cbe8b mov esi, ecx
008cbe8d push edi
008cbe8e mov dword ptr [esi + 0x494], 0x7f800000
008cbe98 mov ecx, dword ptr [esi + 0x3d4]
008cbe9e mov edx, dword ptr [esi + 0x3d0]
008cbea4 sub ecx, edx
008cbea6 sar ecx, 3
008cbea9 cmp ecx, 2
008cbeac jb 0x8cbf52
008cbeb2 mov eax, dword ptr [edx + ecx*8 - 8]
008cbeb6 mov dword ptr [esi + 0x498], eax
008cbebc mov eax, dword ptr [edx + ecx*8 - 4]
008cbec0 mov dword ptr [esi + 0x49c], eax
008cbec6 mov eax, edx
008cbec8 mov ecx, dword ptr [esi + 0x3d4]
008cbece sub ecx, edx
008cbed0 sar ecx, 3
008cbed3 movss xmm1, dword ptr [eax + ecx*8 - 8]
008cbed9 subss xmm1, dword ptr [eax + ecx*8 - 0x10]
008cbedf movss xmm2, dword ptr [eax + ecx*8 - 4]
008cbee5 subss xmm2, dword ptr [eax + ecx*8 - 0xc]
008cbeeb movaps xmm0, xmm1
008cbeee movss dword ptr [esp + 0x10], xmm1
008cbef4 mulss xmm0, xmm1
008cbef8 movaps xmm1, xmm2
008cbefb movss dword ptr [esp + 0x14], xmm2
008cbf01 mulss xmm1, xmm2
008cbf05 addss xmm0, xmm1
008cbf09 call 0x4228c0
008cbf0e comiss xmm0, dword ptr [0xb6a18c]
008cbf15 movss xmm2, dword ptr [esp + 0x10]
008cbf1b jbe 0x8cbf3c
008cbf1d movss xmm1, dword ptr [0xb6a614]
008cbf25 divss xmm1, xmm0
008cbf29 movaps xmm0, xmm1
008cbf2c mulss xmm2, xmm0
008cbf30 movss xmm0, dword ptr [esp + 0x14]
008cbf36 mulss xmm0, xmm1
008cbf3a jmp 0x8cbf42
008cbf3c movss xmm0, dword ptr [esp + 0x14]
008cbf42 movss dword ptr [esi + 0x4a0], xmm2
008cbf4a movss dword ptr [esi + 0x4a4], xmm0
008cbf52 cmp byte ptr [esi + 0x465], 0
008cbf59 je 0x8cbf64
008cbf5b cmp byte ptr [esi + 0x3ac], 0
008cbf62 je 0x8cbf9d
008cbf64 movss xmm0, dword ptr [esi + 0x2a4]
008cbf6c lea eax, [esp + 0x20]
008cbf70 mulss xmm0, dword ptr [0xb6a434]
008cbf78 push eax
008cbf79 push ecx
008cbf7a mov ecx, esi
008cbf7c movss dword ptr [esp + 0x28], xmm0
008cbf82 movss xmm0, dword ptr [esi + 0x2a8]
008cbf8a mulss xmm0, dword ptr [0xb6a434]
008cbf92 movss dword ptr [esp + 0x2c], xmm0
008cbf98 call 0x8c8f00
008cbf9d movss xmm2, dword ptr [esi + 0x2e0]
008cbfa5 mov ecx, dword ptr [esi + 0x320]
008cbfab movss dword ptr [esp + 0x20], xmm2
008cbfb1 test ecx, ecx
008cbfb3 je 0x8cbfbe
008cbfb5 xor eax, eax
008cbfb7 cmp dword ptr [ecx + 0x28], 1
008cbfbb cmovne ecx, eax
008cbfbe mov eax, dword ptr [esi + 0x37c]
008cbfc4 and eax, dword ptr [0xbc4c64]
008cbfca mov ebx, dword ptr [esi + 0x378]
008cbfd0 and ebx, dword ptr [0xbc4c60]
008cbfd6 mov edx, dword ptr [esi + 0x380]
008cbfdc mov edi, edx
008cbfde and edi, dword ptr [0xbc4c68]
008cbfe4 mov dword ptr [esp + 0x14], eax
008cbfe8 mov eax, dword ptr [esi + 0x384]
008cbfee and eax, dword ptr [0xbc4c6c]
008cbff4 mov dword ptr [esp + 0x10], eax
008cbff8 mov eax, ebx
008cbffa or eax, dword ptr [esp + 0x14]
008cbffe mov dword ptr [esp + 0x18], ebx
008cc002 jne 0x8cc04c
008cc004 mov eax, edi
008cc006 or eax, dword ptr [esp + 0x10]
008cc00a jne 0x8cc04c
008cc00c mov eax, dword ptr [esi + 0x384]
008cc012 and eax, dword ptr [0xbc4bcc]
008cc018 mov ebx, dword ptr [esi + 0x37c]
008cc01e and ebx, dword ptr [0xbc4bc4]
008cc024 and edx, dword ptr [0xbc4bc8]
008cc02a mov dword ptr [esp + 0x1c], eax
008cc02e mov eax, dword ptr [esi + 0x378]
008cc034 and eax, dword ptr [0xbc4bc0]
008cc03a or eax, ebx
008cc03c mov ebx, dword ptr [esp + 0x18]
008cc040 jne 0x8cc04c
008cc042 or edx, dword ptr [esp + 0x1c]
008cc046 je 0x8cc109
008cc04c mov eax, dword ptr [esi + 0x30]
008cc04f cmp eax, 1
008cc052 je 0x8cc05d
008cc054 cmp eax, 2
008cc057 jne 0x8cc109
008cc05d test ecx, ecx
008cc05f je 0x8cc09d
008cc061 movss xmm1, dword ptr [ecx + 0x294]
008cc069 movss xmm0, dword ptr [ecx + 0x298]
008cc071 subss xmm0, dword ptr [esi + 0x298]
008cc079 subss xmm1, dword ptr [esi + 0x294]
008cc081 mulss xmm0, xmm0
008cc085 mulss xmm1, xmm1
008cc089 addss xmm0, xmm1
008cc08d call 0x4228c0
008cc092 movss xmm2, dword ptr [esp + 0x20]
008cc098 movaps xmm3, xmm0
008cc09b jmp 0x8cc0a0
008cc09d xorps xmm3, xmm3
008cc0a0 or ebx, dword ptr [esp + 0x14]
008cc0a4 jne 0x8cc0e5
008cc0a6 or edi, dword ptr [esp + 0x10]
008cc0aa jne 0x8cc0e5
008cc0ac movss xmm1, dword ptr [0xb6accc]
008cc0b4 mov ecx, esi
008cc0b6 minss xmm1, xmm3
008cc0ba divss xmm1, dword ptr [0xb6accc]
008cc0c2 mulss xmm1, dword ptr [0xb6a480]
008cc0ca addss xmm1, dword ptr [0xb6a614]
008cc0d2 mulss xmm2, xmm1
008cc0d6 movaps xmm1, xmm2
008cc0d9 call 0x8c99f0
008cc0de pop edi
008cc0df pop esi
008cc0e0 pop ebx
008cc0e1 mov esp, ebp
008cc0e3 pop ebp
008cc0e4 ret 
008cc0e5 movss xmm1, dword ptr [0xb6ac8c]
008cc0ed minss xmm1, xmm3
008cc0f1 movss xmm0, dword ptr [0xb6a6f0]
008cc0f9 divss xmm1, dword ptr [0xb6ac8c]
008cc101 subss xmm0, xmm1
008cc105 mulss xmm2, xmm0
008cc109 movaps xmm1, xmm2
008cc10c mov ecx, esi
008cc10e call 0x8c99f0
008cc113 pop edi
008cc114 pop esi
008cc115 pop ebx
008cc116 mov esp, ebp
008cc118 pop ebp
008cc119 ret 
