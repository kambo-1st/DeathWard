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
008cc11a int3 
008cc11b int3 
008cc11c int3 
008cc11d int3 
008cc11e int3 
008cc11f int3 
008cc120 push ebp
008cc121 mov ebp, esp
008cc123 and esp, 0xfffffff0
008cc126 sub esp, 0x88
008cc12c mov eax, dword ptr [0xbaa3b4]
008cc131 xor eax, esp
008cc133 mov dword ptr [esp + 0x84], eax
008cc13a push esi
008cc13b push edi
008cc13c mov edi, ecx
008cc13e cmp byte ptr [edi + 0x467], 0
008cc145 je 0x8cc2dd
008cc14b cmp byte ptr [edi + 0x465], 0
008cc152 jne 0x8cc2dd
008cc158 cmp byte ptr [edi + 0x16d], 0
008cc15f jne 0x8cc2dd
008cc165 cmp byte ptr [edi + 0x3ac], 0
008cc16c jne 0x8cc186
008cc16e movss xmm1, dword ptr [0xb6a7b0]
008cc176 xorps xmm2, xmm2
008cc179 call 0x6847e0
008cc17e test eax, eax
008cc180 je 0x8cc2dd
008cc186 mov esi, dword ptr [edi + 0x320]
008cc18c test esi, esi
008cc18e je 0x8cc2dd
008cc194 cmp dword ptr [esi + 0x28], 1
008cc198 je 0x8cc1db
008cc19a test esi, esi
008cc19c je 0x8cc2dd
008cc1a2 cmp dword ptr [esi + 0x28], 3
008cc1a6 jne 0x8cc2dd
008cc1ac mov eax, dword ptr [esi + 0x2c]
008cc1af cmp eax, 0x50
008cc1b2 je 0x8cc1cd
008cc1b4 cmp eax, 0xeb
008cc1b9 je 0x8cc1cd
008cc1bb cmp eax, 0xf0
008cc1c0 je 0x8cc1cd
008cc1c2 cmp eax, 0xee
008cc1c7 jne 0x8cc2dd
008cc1cd mov esi, dword ptr [esi + 0x360]
008cc1d3 test esi, esi
008cc1d5 je 0x8cc2dd
008cc1db call 0x6c3d90
008cc1e0 push dword ptr [edi + 0x320]
008cc1e6 movss xmm0, dword ptr [edi + 0x46c]
008cc1ee and eax, 1
008cc1f1 lea eax, [eax*2 - 1]
008cc1f8 push eax
008cc1f9 push ecx
008cc1fa movss dword ptr [esp], xmm0
008cc1ff lea eax, [esp + 0x2c]
008cc203 push 3
008cc205 push eax
008cc206 mov ecx, esi
008cc208 call 0x7836a0
008cc20d mov ecx, dword ptr [0xbc4bd0]
008cc213 mov eax, dword ptr [0xbc4bd4]
008cc218 not ecx
008cc21a and ecx, dword ptr [esp + 0x58]
008cc21e not eax
008cc220 and eax, dword ptr [esp + 0x5c]
008cc224 mov dword ptr [esp + 0x10], ecx
008cc228 mov ecx, dword ptr [0xbc4bd8]
008cc22e mov dword ptr [esp + 0x14], eax
008cc232 not ecx
008cc234 mov eax, dword ptr [0xbc4bdc]
008cc239 and ecx, dword ptr [esp + 0x60]
008cc23d not eax
008cc23f and eax, dword ptr [esp + 0x64]
008cc243 cmp dword ptr [edi + 0x3a8], 0
008cc24a mov dword ptr [esp + 0x18], ecx
008cc24e mov dword ptr [esp + 0x1c], eax
008cc252 movups xmm0, xmmword ptr [esp + 0x10]
008cc257 movups xmmword ptr [edi + 0x378], xmm0
008cc25e jge 0x8cc297
008cc260 mov esi, dword ptr [0xbc4ca8]
008cc266 mov ecx, dword ptr [0xbc4ca0]
008cc26c not esi
008cc26e mov eax, dword ptr [0xbc4ca4]
008cc273 not ecx
008cc275 mov edx, dword ptr [0xbc4cac]
008cc27b not eax
008cc27d and dword ptr [edi + 0x378], ecx
008cc283 not edx
008cc285 and dword ptr [edi + 0x37c], eax
008cc28b and dword ptr [edi + 0x380], esi
008cc291 and dword ptr [edi + 0x384], edx
008cc297 mov edx, dword ptr [edi + 0x3a0]
008cc29d mov ecx, dword ptr [edi + 0x398]
008cc2a3 not edx
008cc2a5 mov eax, dword ptr [edi + 0x39c]
008cc2ab not ecx
008cc2ad mov esi, dword ptr [edi + 0x3a4]
008cc2b3 not eax
008cc2b5 movss xmm0, dword ptr [esp + 0x68]
008cc2bb not esi
008cc2bd and dword ptr [edi + 0x378], ecx
008cc2c3 and dword ptr [edi + 0x37c], eax
008cc2c9 and dword ptr [edi + 0x380], edx
008cc2cf and dword ptr [edi + 0x384], esi
008cc2d5 movss dword ptr [edi + 0x2e0], xmm0
008cc2dd mov ecx, dword ptr [esp + 0x8c]
008cc2e4 pop edi
008cc2e5 pop esi
008cc2e6 xor ecx, esp
008cc2e8 call 0x9eacd7
008cc2ed mov esp, ebp
008cc2ef pop ebp
008cc2f0 ret 
008cc2f1 int3 
008cc2f2 int3 
008cc2f3 int3 
008cc2f4 int3 
008cc2f5 int3 
008cc2f6 int3 
008cc2f7 int3 
008cc2f8 int3 
008cc2f9 int3 
008cc2fa int3 
008cc2fb int3 
008cc2fc int3 
008cc2fd int3 
008cc2fe int3 
008cc2ff int3 
