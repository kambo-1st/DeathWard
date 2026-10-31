004ee860 push ebp
004ee861 mov ebp, esp
004ee863 and esp, 0xfffffff8
004ee866 sub esp, 0x180
004ee86c mov eax, dword ptr [0xbaa3b4]
004ee871 xor eax, esp
004ee873 mov dword ptr [esp + 0x17c], eax
004ee87a mov eax, dword ptr [0xbfd65c]
004ee87f push esi
004ee880 push edi
004ee881 mov edi, ecx
004ee883 mov eax, dword ptr [eax + 0x18190]
004ee889 mov dword ptr [esp + 0x10], eax
004ee88d mov dword ptr [esp + 0x5c], edi
004ee891 movss xmm0, dword ptr [edi + 0x2c4]
004ee899 mulss xmm0, dword ptr [0xb6a5d8]
004ee8a1 mov eax, dword ptr [edi + 0xab4]
004ee8a7 movss dword ptr [edi + 0x2c4], xmm0
004ee8af cmp eax, 0x10
004ee8b2 ja 0x4ef795
004ee8b8 movzx eax, byte ptr [eax + 0x4efae8]
004ee8bf jmp dword ptr [eax*4 + 0x4efad0]
004ee8c6 movaps xmm0, xmmword ptr [0xb6bd30]
004ee8cd lea eax, [esp + 0x60]
004ee8d1 movups xmmword ptr [esp + 0x60], xmm0
004ee8d6 mov dword ptr [edi + 0x360], 0
004ee8e0 lea ecx, [edi + 0x1dc]
004ee8e6 xorps xmm0, xmm0
004ee8e9 mov dword ptr [edi + 0xab4], 3
004ee8f3 push eax
004ee8f4 movups xmmword ptr [esp + 0x74], xmm0
004ee8f9 mov dword ptr [esp + 0x84], 0x3df0f0f1
004ee904 mov dword ptr [esp + 0x88], 0x3df0f0f1
004ee90f mov dword ptr [esp + 0x8c], 0x3df0f0f1
004ee91a call 0x4021a0
004ee91f jmp 0x4ef795
004ee924 mov eax, dword ptr [edi + 0x30]
004ee927 inc eax
004ee928 push eax
004ee929 lea eax, [esp + 0x168]
004ee930 push 0xb40c58
004ee935 push eax
004ee936 call 0x4e6170
004ee93b add esp, 0xc
004ee93e lea eax, [esp + 0x164]
004ee945 lea ecx, [edi + 0x3c]
004ee948 push 0
004ee94a push eax
004ee94b call 0x4054f0
004ee950 mov eax, dword ptr [edi + 0x360]
004ee956 test eax, eax
004ee958 jle 0x4ee961
004ee95a dec eax
004ee95b mov dword ptr [edi + 0x360], eax
004ee961 call 0x6c3d90
004ee966 xor edx, edx
004ee968 mov ecx, 5
004ee96d div ecx
004ee96f test edx, edx
004ee971 jne 0x4eeaae
004ee977 push dword ptr [edi + 0x20]
004ee97a push ecx
004ee97b mov ecx, edi
004ee97d call 0x684790
004ee982 test al, al
004ee984 je 0x4eeaae
004ee98a cmp dword ptr [edi + 0x360], 0
004ee991 jg 0x4eeaae
004ee997 push 0
004ee999 push 0x1000800
004ee99e mov ecx, edi
004ee9a0 mov dword ptr [edi + 0xb14], 0
004ee9aa call 0x4122f0
004ee9af test al, al
004ee9b1 je 0x4eea32
004ee9b3 mov eax, dword ptr [edi + 0x30]
004ee9b6 inc eax
004ee9b7 mov dword ptr [edi + 0xb10], 0
004ee9c1 push eax
004ee9c2 lea eax, [esp + 0x168]
004ee9c9 mov dword ptr [edi + 0xab4], 6
004ee9d3 push 0xb42ae8
004ee9d8 push eax
004ee9d9 call 0x4e6170
004ee9de add esp, 0xc
004ee9e1 lea eax, [esp + 0x164]
004ee9e8 lea ecx, [edi + 0x3c]
004ee9eb push 0
004ee9ed push eax
004ee9ee call 0x4054f0
004ee9f3 push ecx
004ee9f4 lea eax, [esp + 0x18]
004ee9f8 mov dword ptr [esp], 0x3f800000
004ee9ff push eax
004eea00 mov ecx, edi
004eea02 call 0x695a30
004eea07 movss xmm1, dword ptr [eax]
004eea0b movss xmm0, dword ptr [eax + 4]
004eea10 subss xmm1, dword ptr [edi + 0x294]
004eea18 subss xmm0, dword ptr [edi + 0x298]
004eea20 movss dword ptr [edi + 0x2b8], xmm1
004eea28 movss dword ptr [edi + 0x2bc], xmm0
004eea30 jmp 0x4eeaae
004eea32 push 0
004eea34 push 0x200
004eea39 mov ecx, edi
004eea3b call 0x4122f0
004eea40 test al, al
004eea42 je 0x4eeaa4
004eea44 mov eax, dword ptr [edi + 0x30]
004eea47 inc eax
004eea48 mov dword ptr [edi + 0xb10], 0
004eea52 push eax
004eea53 lea eax, [esp + 0x168]
004eea5a mov dword ptr [edi + 0xab4], 6
004eea64 push 0xb42ae8
004eea69 push eax
004eea6a call 0x4e6170
004eea6f add esp, 0xc
004eea72 lea eax, [esp + 0x164]
004eea79 lea ecx, [edi + 0x3c]
004eea7c push 0
004eea7e push eax
004eea7f call 0x4054f0
004eea84 lea eax, [esp + 0x14]
004eea88 push eax
004eea89 call 0x659290
004eea8e add esp, 4
004eea91 mov ecx, dword ptr [eax]
004eea93 mov dword ptr [edi + 0x2b8], ecx
004eea99 mov eax, dword ptr [eax + 4]
004eea9c mov dword ptr [edi + 0x2bc], eax
004eeaa2 jmp 0x4eeaae
004eeaa4 mov dword ptr [edi + 0xab4], 8
004eeaae movss xmm0, dword ptr [edi + 0x2c4]
004eeab6 mulss xmm0, dword ptr [0xb6a480]
004eeabe movss dword ptr [edi + 0x2c4], xmm0
004eeac6 jmp 0x4ef795
004eeacb cmp dword ptr [edi + 0x70], 0
004eeacf je 0x4eeada
004eead1 cmp byte ptr [edi + 0x80], 0
004eead8 jne 0x4eeaf4
004eeada mov eax, dword ptr [edi + 0x30]
004eeadd inc eax
004eeade push eax
004eeadf lea eax, [esp + 0x168]
004eeae6 push 0xb42ae8
004eeaeb push eax
004eeaec call 0x4e6170
004eeaf1 add esp, 0xc
004eeaf4 push 0
004eeaf6 lea eax, [esp + 0x168]
004eeafd push eax
004eeafe lea ecx, [edi + 0x3c]
004eeb01 call 0x4054f0
004eeb06 mov eax, dword ptr [edi + 0xb10]
004eeb0c inc eax
004eeb0d cmp dword ptr [edi + 0xb14], 0
004eeb14 mov dword ptr [edi + 0xb10], eax
004eeb1a jle 0x4eeb88
004eeb1c cmp eax, 0x1e
004eeb1f jl 0x4eeb88
004eeb21 movss xmm1, dword ptr [edi + 0x2bc]
004eeb29 movss xmm0, dword ptr [edi + 0x2b8]
004eeb31 mulss xmm0, xmm0
004eeb35 mulss xmm1, xmm1
004eeb39 addss xmm0, xmm1
004eeb3d call 0x4228c0
004eeb42 comiss xmm0, dword ptr [0xb6a614]
004eeb49 jb 0x4eeb79
004eeb4b movss xmm1, dword ptr [0xb6a95c]
004eeb53 comiss xmm1, xmm0
004eeb56 jbe 0x4eec45
004eeb5c movss xmm0, dword ptr [edi + 0x2c4]
004eeb64 mulss xmm0, dword ptr [0xb6a560]
004eeb6c movss dword ptr [edi + 0x2c4], xmm0
004eeb74 jmp 0x4eec45
004eeb79 mov dword ptr [edi + 0xab4], 3
004eeb83 jmp 0x4eec45
004eeb88 movss xmm1, dword ptr [edi + 0x2b8]
004eeb90 movss xmm2, dword ptr [edi + 0x2bc]
004eeb98 movaps xmm0, xmm1
004eeb9b mulss xmm0, xmm1
004eeb9f movss dword ptr [esp + 0xc], xmm1
004eeba5 movaps xmm1, xmm2
004eeba8 mulss xmm1, xmm2
004eebac movss dword ptr [esp + 0x20], xmm2
004eebb2 addss xmm0, xmm1
004eebb6 call 0x4228c0
004eebbb xorps xmm4, xmm4
004eebbe comiss xmm0, xmm4
004eebc1 jbe 0x4eebe0
004eebc3 movss xmm1, dword ptr [0xb6a614]
004eebcb divss xmm1, xmm0
004eebcf movaps xmm2, xmm1
004eebd2 mulss xmm1, dword ptr [esp + 0x20]
004eebd8 mulss xmm2, dword ptr [esp + 0xc]
004eebde jmp 0x4eebec
004eebe0 movss xmm1, dword ptr [esp + 0x20]
004eebe6 movss xmm2, dword ptr [esp + 0xc]
004eebec movss xmm3, dword ptr [edi + 0x2c4]
004eebf4 mulss xmm2, dword ptr [0xb6a50c]
004eebfc mulss xmm1, dword ptr [0xb6a50c]
004eec04 ucomiss xmm3, xmm4
004eec07 lahf 
004eec08 test ah, 0x44
004eec0b jnp 0x4eec45
004eec0d movss xmm0, dword ptr [edi + 0x2f4]
004eec15 mulss xmm2, xmm0
004eec19 mulss xmm1, xmm0
004eec1d divss xmm2, xmm3
004eec21 divss xmm1, xmm3
004eec25 addss xmm2, dword ptr [edi + 0x2b8]
004eec2d addss xmm1, dword ptr [edi + 0x2bc]
004eec35 movss dword ptr [edi + 0x2b8], xmm2
004eec3d movss dword ptr [edi + 0x2bc], xmm1
004eec45 call 0x6c3d90
004eec4a test al, 1
004eec4c jne 0x4ef00f
004eec52 xorps xmm0, xmm0
004eec55 mov dword ptr [esp + 0xac], 0
004eec60 movups xmmword ptr [esp + 0x9c], xmm0
004eec68 lea eax, [esp + 0x14]
004eec6c mov dword ptr [esp + 0xb0], 0
004eec77 movaps xmm0, xmmword ptr [0xb6c260]
004eec7e push eax
004eec7f mov dword ptr [esp + 0xb8], 0
004eec8a movups xmmword ptr [esp + 0x90], xmm0
004eec92 call 0x659290
004eec97 add esp, 4
004eec9a call 0x6c3d90
004eec9f movd xmm0, eax
004eeca3 cvtdq2pd xmm0, xmm0
004eeca7 shr eax, 0x1f
004eecaa addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004eecb3 cvtpd2ps xmm3, xmm0
004eecb7 mulss xmm3, dword ptr [0xb6a19c]
004eecbf addss xmm3, xmm3
004eecc3 addss xmm3, dword ptr [0xb6a614]
004eeccb call 0x6c3d90
004eecd0 movss xmm4, dword ptr [esp + 0x14]
004eecd6 movss xmm1, dword ptr [edi + 0x2c8]
004eecde movss xmm5, dword ptr [esp + 0x18]
004eece4 movd xmm0, eax
004eece8 cvtdq2pd xmm0, xmm0
004eecec shr eax, 0x1f
004eecef mov esi, dword ptr [0xbfd65c]
004eecf5 mov dword ptr [esp + 0x34], esi
004eecf9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004eed02 cvtpd2ps xmm2, xmm0
004eed06 movaps xmm0, xmm4
004eed09 mulss xmm4, xmm3
004eed0d mulss xmm2, dword ptr [0xb6a19c]
004eed15 movss dword ptr [esp + 0x40], xmm4
004eed1b movss dword ptr [esp + 0x14], xmm4
004eed21 mulss xmm0, xmm2
004eed25 mulss xmm0, xmm1
004eed29 addss xmm0, dword ptr [edi + 0x294]
004eed31 movss dword ptr [esp + 0x54], xmm0
004eed37 movaps xmm0, xmm5
004eed3a mulss xmm0, xmm2
004eed3e mulss xmm5, xmm3
004eed42 mulss xmm0, xmm1
004eed46 movss dword ptr [esp + 0x24], xmm5
004eed4c movss dword ptr [esp + 0x18], xmm5
004eed52 addss xmm0, dword ptr [edi + 0x298]
004eed5a movss dword ptr [esp + 0x58], xmm0
004eed60 call 0x6c3d90
004eed65 mov dword ptr [esp + 0x20], eax
004eed69 lea eax, [esp + 0x20]
004eed6d push eax
004eed6e lea eax, [esp + 0x54]
004eed72 mov dword ptr [esp + 0x54], 0
004eed7a push eax
004eed7b push 0
004eed7d lea eax, [esp + 0x20]
004eed81 mov dword ptr [esp + 0x48], 0x23
004eed89 push eax
004eed8a lea eax, [esp + 0x64]
004eed8e mov dword ptr [esp + 0x2c], 0x3e8
004eed96 push eax
004eed97 lea eax, [esp + 0x50]
004eed9b push eax
004eed9c lea eax, [esp + 0x34]
004eeda0 push eax
004eeda1 call 0x800fb0
004eeda6 mov ecx, dword ptr [esi + 0x1c3198]
004eedac push 0
004eedae push dword ptr [esp + 0x20]
004eedb2 call 0x6c4b30
004eedb7 mov esi, eax
004eedb9 mov dword ptr [esp + 0xc], esi
004eedbd test esi, esi
004eedbf je 0x4eefd6
004eedc5 call dword ptr [0xa064c0]
004eedcb mov ecx, dword ptr [esi + 0x320]
004eedd1 mov dword ptr [esp + 0x2c], eax
004eedd5 lea eax, [esi + 0x320]
004eeddb mov dword ptr [esi + 0x34], 0
004eede2 mov dword ptr [esi + 0x38], 0
004eede9 test ecx, ecx
004eedeb je 0x4eee07
004eeded mov dword ptr [esp + 0x48], eax
004eedf1 add ecx, 0x324
004eedf7 lea eax, [esp + 0x48]
004eedfb push eax
004eedfc call 0x4bc3c0
004eee01 lea eax, [esi + 0x320]
004eee07 push dword ptr [esp + 0x20]
004eee0b mov dword ptr [eax], 0
004eee11 mov ecx, esi
004eee13 movss xmm0, dword ptr [esp + 0x58]
004eee19 push dword ptr [esp + 0x54]
004eee1d mov eax, dword ptr [esi]
004eee1f push dword ptr [esp + 0x44]
004eee23 movss dword ptr [esi + 0x294], xmm0
004eee2b movss xmm0, dword ptr [esp + 0x64]
004eee31 push dword ptr [esp + 0x28]
004eee35 movss dword ptr [esi + 0x298], xmm0
004eee3d movss xmm0, dword ptr [esp + 0x50]
004eee43 movss dword ptr [esi + 0x2b8], xmm0
004eee4b movss xmm0, dword ptr [esp + 0x34]
004eee51 movss dword ptr [esi + 0x2bc], xmm0
004eee59 call dword ptr [eax + 4]
004eee5c mov eax, dword ptr [esp + 0x34]
004eee60 push esi
004eee61 mov edx, dword ptr [eax + 0x18190]
004eee67 mov ecx, dword ptr [edx + 0x1214]
004eee6d lea eax, [ecx + 1]
004eee70 mov dword ptr [edx + 0x1214], eax
004eee76 mov dword ptr [esi + 0x20], ecx
004eee79 lea ecx, [edx + 0x1218]
004eee7f call 0x413280
004eee84 push esi
004eee85 call 0x6d94d0
004eee8a test al, al
004eee8c je 0x4eee95
004eee8e push ecx
004eee8f push esi
004eee90 call 0x6d9590
004eee95 cmp byte ptr [esi + 0x16a], 0
004eee9c je 0x4eefc6
004eeea2 mov ecx, dword ptr [esp + 0x34]
004eeea6 mov eax, dword ptr [ecx + 0x283c20]
004eeeac cmp eax, dword ptr [ecx + 0x283c24]
004eeeb2 je 0x4eefc6
004eeeb8 mov eax, dword ptr [esi + 0x28]
004eeebb mov dword ptr [esp + 0x48], eax
004eeebf mov eax, dword ptr [esi + 0x2c]
004eeec2 mov dword ptr [esp + 0x4c], eax
004eeec6 lea eax, [ecx + 0x283c48]
004eeecc lea ecx, [esp + 0x48]
004eeed0 mov dword ptr [esp + 0x24], eax
004eeed4 push ecx
004eeed5 lea ecx, [esp + 0x44]
004eeed9 push ecx
004eeeda mov ecx, eax
004eeedc call 0x937c80
004eeee1 mov ecx, dword ptr [esp + 0x24]
004eeee5 mov eax, dword ptr [ecx]
004eeee7 mov dword ptr [esp + 0x24], eax
004eeeeb cmp dword ptr [esp + 0x40], eax
004eeeef jne 0x4eef1b
004eeef1 mov eax, dword ptr [esi + 0x28]
004eeef4 mov dword ptr [esp + 0x40], eax
004eeef8 lea eax, [esp + 0x40]
004eeefc push eax
004eeefd lea eax, [esp + 0x54]
004eef01 mov dword ptr [esp + 0x48], 0xffffffff
004eef09 push eax
004eef0a call 0x937c80
004eef0f mov ecx, dword ptr [esp + 0x24]
004eef13 cmp dword ptr [eax], ecx
004eef15 je 0x4eefc6
004eef1b mov esi, dword ptr [0xbfd65c]
004eef21 xor edx, edx
004eef23 mov dword ptr [esp + 0x1c], edx
004eef27 mov eax, dword ptr [esi + 0x1ba54]
004eef2d sub eax, dword ptr [esi + 0x1ba50]
004eef33 sar eax, 2
004eef36 test eax, eax
004eef38 je 0x4eefc2
004eef3e mov edi, dword ptr [esp + 0xc]
004eef42 mov ecx, dword ptr [esi + 0x1ba54]
004eef48 mov eax, ecx
004eef4a sub eax, dword ptr [esi + 0x1ba50]
004eef50 test eax, 0xfffffffc
004eef55 jne 0x4eef70
004eef57 push 0xb3f4d0
004eef5c push 3
004eef5e call 0x95e330
004eef63 mov ecx, dword ptr [esi + 0x1ba54]
004eef69 add esp, 8
004eef6c mov edx, dword ptr [esp + 0x1c]
004eef70 mov eax, dword ptr [esi + 0x1ba50]
004eef76 sub ecx, eax
004eef78 sar ecx, 2
004eef7b cmp edx, ecx
004eef7d jae 0x4eef82
004eef7f lea eax, [eax + edx*4]
004eef82 lea ecx, [esp + 0x14]
004eef86 push ecx
004eef87 lea ecx, [esp + 0x58]
004eef8b push ecx
004eef8c mov ecx, dword ptr [eax]
004eef8e push edi
004eef8f push 6
004eef91 add ecx, 0x1ec0
004eef97 call 0x935fd0
004eef9c mov esi, dword ptr [0xbfd65c]
004eefa2 mov edx, dword ptr [esp + 0x1c]
004eefa6 inc edx
004eefa7 mov dword ptr [esp + 0x1c], edx
004eefab mov eax, dword ptr [esi + 0x1ba54]
004eefb1 sub eax, dword ptr [esi + 0x1ba50]
004eefb7 sar eax, 2
004eefba cmp edx, eax
004eefbc jb 0x4eef42
004eefbe mov edi, dword ptr [esp + 0x5c]
004eefc2 mov esi, dword ptr [esp + 0xc]
004eefc6 call dword ptr [0xa064c0]
004eefcc sub eax, dword ptr [esp + 0x2c]
004eefd0 add dword ptr [0xbffe0c], eax
004eefd6 mov eax, dword ptr [edi + 0x2a4]
004eefdc lea ecx, [esp + 0x8c]
004eefe3 push 1
004eefe5 push 0
004eefe7 mov dword ptr [esi + 0x2a4], eax
004eefed mov eax, dword ptr [edi + 0x2a8]
004eeff3 push 0xff
004eeff8 mov dword ptr [esi + 0x2a8], eax
004eeffe mov eax, dword ptr [esi]
004ef000 push -1
004ef002 push ecx
004ef003 mov ecx, esi
004ef005 call dword ptr [eax + 0x38]
004ef008 mov eax, dword ptr [esi]
004ef00a mov ecx, esi
004ef00c call dword ptr [eax + 0xc]
004ef00f cmp byte ptr [edi + 0x188], 0
004ef016 je 0x4ef5df
004ef01c movss xmm0, dword ptr [edi + 0x18c]
004ef024 movss xmm2, dword ptr [edi + 0x2c8]
004ef02c movss xmm1, dword ptr [edi + 0x194]
004ef034 addss xmm0, dword ptr [edi + 0x294]
004ef03c mulss xmm1, xmm2
004ef040 mov ecx, dword ptr [esp + 0x10]
004ef044 addss xmm1, xmm0
004ef048 movss xmm0, dword ptr [edi + 0x198]
004ef050 mulss xmm0, xmm2
004ef054 movss dword ptr [esp + 0x24], xmm1
004ef05a movss xmm1, dword ptr [edi + 0x190]
004ef062 addss xmm1, dword ptr [edi + 0x298]
004ef06a addss xmm1, xmm0
004ef06e movss dword ptr [esp + 0x28], xmm1
004ef074 push dword ptr [esp + 0x28]
004ef078 push dword ptr [esp + 0x28]
004ef07c call 0x7aee40
004ef081 cmp dword ptr [edi + 0xab4], 6
004ef088 mov dword ptr [esp + 0x2c], eax
004ef08c je 0x4ef5d9
004ef092 lea eax, [esp + 0x14]
004ef096 push eax
004ef097 lea ecx, [edi + 0x18c]
004ef09d call 0x962560
004ef0a2 movss xmm0, dword ptr [edi + 0x198]
004ef0aa movss xmm1, dword ptr [edi + 0x194]
004ef0b2 mulss xmm0, dword ptr [eax + 4]
004ef0b7 mulss xmm1, dword ptr [eax]
004ef0bb addss xmm0, xmm1
004ef0bf comiss xmm0, dword ptr [0xb6a480]
004ef0c6 jbe 0x4ef5d9
004ef0cc mov eax, dword ptr [esp + 0x2c]
004ef0d0 cmp eax, 3
004ef0d3 je 0x4ef0de
004ef0d5 cmp eax, 4
004ef0d8 jne 0x4ef5d9
004ef0de mov esi, dword ptr [0xbfd680]
004ef0e4 lea ecx, [esp + 0x34]
004ef0e8 mov dword ptr [esp + 0x34], 0x34
004ef0f0 call 0x8b1340
004ef0f5 sub esp, 8
004ef0f8 mov dword ptr [esp + 4], 0
004ef100 mov dword ptr [esp], 0x3f800000
004ef107 push 0
004ef109 push 0x1e
004ef10b push ecx
004ef10c mov dword ptr [esp], 0x3f800000
004ef113 lea ecx, [esi + 0x29de0]
004ef119 push dword ptr [esp + 0x48]
004ef11d call 0x888de0
004ef122 mov ecx, dword ptr [0xbfd65c]
004ef128 push 0xc
004ef12a call 0x6d5ad0
004ef12f mov ecx, dword ptr [esp + 0x10]
004ef133 lea eax, [esp + 0x24]
004ef137 push eax
004ef138 call 0x447f80
004ef13d test eax, eax
004ef13f je 0x4ef14a
004ef141 mov edx, dword ptr [eax]
004ef143 mov ecx, eax
004ef145 push 0
004ef147 call dword ptr [edx + 0x14]
004ef14a mov ecx, edi
004ef14c call 0x695680
004ef151 mov ecx, dword ptr [eax + 0x294]
004ef157 mov eax, dword ptr [eax + 0x298]
004ef15d mov dword ptr [esp + 0x14], ecx
004ef161 mov ecx, edi
004ef163 mov dword ptr [esp + 0x18], eax
004ef167 call 0x448100
004ef16c test al, al
004ef16e jne 0x4ef32e
004ef174 mov ecx, dword ptr [0xbfd65c]
004ef17a xor esi, esi
004ef17c mov eax, dword ptr [ecx + 0x1ba54]
004ef182 sub eax, dword ptr [ecx + 0x1ba50]
004ef188 sar eax, 2
004ef18b test eax, eax
004ef18d je 0x4ef32e
004ef193 push esi
004ef194 call 0x412750
004ef199 mov dword ptr [esp + 0x2c], eax
004ef19d movss xmm1, dword ptr [eax + 0x298]
004ef1a5 subss xmm1, dword ptr [edi + 0x298]
004ef1ad movss xmm2, dword ptr [eax + 0x294]
004ef1b5 subss xmm2, dword ptr [edi + 0x294]
004ef1bd movaps xmm0, xmm1
004ef1c0 movss dword ptr [esp + 0x34], xmm1
004ef1c6 mulss xmm0, xmm1
004ef1ca movaps xmm1, xmm2
004ef1cd movss dword ptr [esp + 0x10], xmm2
004ef1d3 mulss xmm1, xmm2
004ef1d7 addss xmm0, xmm1
004ef1db call 0x4228c0
004ef1e0 movss xmm2, dword ptr [esp + 0x10]
004ef1e6 movaps xmm4, xmm0
004ef1e9 comiss xmm4, dword ptr [0xb6a18c]
004ef1f0 movss xmm3, dword ptr [esp + 0x34]
004ef1f6 jbe 0x4ef20f
004ef1f8 movss xmm1, dword ptr [0xb6a614]
004ef200 divss xmm1, xmm4
004ef204 movaps xmm0, xmm1
004ef207 mulss xmm3, xmm1
004ef20b mulss xmm2, xmm0
004ef20f movss xmm0, dword ptr [0xb6aae4]
004ef217 comiss xmm0, xmm4
004ef21a jbe 0x4ef310
004ef220 mov eax, dword ptr [edi + 0x28]
004ef223 movss xmm0, dword ptr [edi + 0x294]
004ef22b movss xmm1, dword ptr [edi + 0x298]
004ef233 mov ecx, dword ptr [edi + 0x160]
004ef239 mov edx, dword ptr [edi + 0x164]
004ef23f mov dword ptr [esp + 0x60], eax
004ef243 mov eax, dword ptr [edi + 0x2c]
004ef246 mov dword ptr [esp + 0x64], eax
004ef24a mov eax, dword ptr [edi + 0x34]
004ef24d mov dword ptr [esp + 0x68], eax
004ef251 mov eax, dword ptr [edi + 0x38]
004ef254 mov dword ptr [esp + 0x6c], eax
004ef258 mov eax, ecx
004ef25a movss dword ptr [esp + 0x70], xmm0
004ef260 and eax, 0x100
004ef265 or eax, 0
004ef268 movss xmm0, dword ptr [edi + 0x2b8]
004ef270 movss dword ptr [esp + 0x74], xmm1
004ef276 movss xmm1, dword ptr [edi + 0x2bc]
004ef27e movss dword ptr [esp + 0x78], xmm0
004ef284 movss dword ptr [esp + 0x7c], xmm1
004ef28a mov dword ptr [esp + 0x10], 1
004ef292 jne 0x4ef29c
004ef294 mov dword ptr [esp + 0x10], 0
004ef29c and ecx, 0x20000000
004ef2a2 or ecx, 0
004ef2a5 je 0x4ef2ae
004ef2a7 mov ecx, 2
004ef2ac jmp 0x4ef2b0
004ef2ae xor ecx, ecx
004ef2b0 and edx, 0x400000
004ef2b6 xor eax, eax
004ef2b8 or eax, edx
004ef2ba je 0x4ef2c3
004ef2bc mov eax, 4
004ef2c1 jmp 0x4ef2c5
004ef2c3 xor eax, eax
004ef2c5 mulss xmm2, dword ptr [0xb6a864]
004ef2cd lea edx, [esp + 0x24]
004ef2d1 or eax, ecx
004ef2d3 mov ecx, dword ptr [esp + 0x2c]
004ef2d7 mulss xmm3, dword ptr [0xb6a864]
004ef2df or eax, dword ptr [esp + 0x10]
004ef2e3 push ecx
004ef2e4 mov dword ptr [esp], 0x40c00000
004ef2eb mov dword ptr [esp + 0x84], eax
004ef2f2 mov eax, dword ptr [ecx]
004ef2f4 push edx
004ef2f5 lea edx, [esp + 0x68]
004ef2f9 mov dword ptr [esp + 0x8c], edi
004ef300 push edx
004ef301 movss dword ptr [esp + 0x30], xmm2
004ef307 movss dword ptr [esp + 0x34], xmm3
004ef30d call dword ptr [eax + 0x50]
004ef310 mov ecx, dword ptr [0xbfd65c]
004ef316 inc esi
004ef317 mov eax, dword ptr [ecx + 0x1ba54]
004ef31d sub eax, dword ptr [ecx + 0x1ba50]
004ef323 sar eax, 2
004ef326 cmp esi, eax
004ef328 jb 0x4ef193
004ef32e mov eax, dword ptr [edi + 0x30]
004ef331 test eax, eax
004ef333 jne 0x4ef385
004ef335 lea ecx, [esp + 0xb8]
004ef33c mov dword ptr [edi + 0x30], 1
004ef343 call 0x430d70
004ef348 lea eax, [esp + 0xb8]
004ef34f mov dword ptr [esp + 0x14c], 9
004ef35a push eax
004ef35b push 8
004ef35d lea eax, [esp + 0x1c]
004ef361 mov dword ptr [esp + 0x1c], 0x41200000
004ef369 push eax
004ef36a lea esi, [edi + 0x294]
004ef370 mov dword ptr [esp + 0x24], 0
004ef378 push esi
004ef379 mov ecx, edi
004ef37b call 0x6a1a20
004ef380 jmp 0x4ef5cf
004ef385 cmp eax, 1
004ef388 jne 0x4ef3f8
004ef38a lea ecx, [esp + 0xb8]
004ef391 mov dword ptr [edi + 0x30], 2
004ef398 call 0x430d70
004ef39d lea eax, [esp + 0xb8]
004ef3a4 mov dword ptr [esp + 0x14c], 9
004ef3af push eax
004ef3b0 push 8
004ef3b2 lea eax, [esp + 0x34]
004ef3b6 mov dword ptr [esp + 0x34], 0x41200000
004ef3be push eax
004ef3bf lea esi, [edi + 0x294]
004ef3c5 mov dword ptr [esp + 0x3c], 0
004ef3cd push esi
004ef3ce mov ecx, edi
004ef3d0 call 0x6a1a20
004ef3d5 lea eax, [esp + 0xb8]
004ef3dc push eax
004ef3dd push ecx
004ef3de mov dword ptr [esp], 0
004ef3e5 lea eax, [esp + 0x1c]
004ef3e9 push eax
004ef3ea push 6
004ef3ec mov ecx, edi
004ef3ee call 0x6a3420
004ef3f3 jmp 0x4ef5cf
004ef3f8 mov eax, dword ptr [edi]
004ef3fa mov ecx, edi
004ef3fc call dword ptr [eax + 0x24]
004ef3ff lea ecx, [esp + 0xb8]
004ef406 call 0x430d70
004ef40b movss xmm0, dword ptr [esp + 0xcc]
004ef414 lea eax, [esp + 0xb8]
004ef41b mulss xmm0, dword ptr [0xb6a670]
004ef423 push eax
004ef424 push ecx
004ef425 mov dword ptr [esp], 0
004ef42c lea eax, [esp + 0x1c]
004ef430 push eax
004ef431 push 8
004ef433 mov ecx, edi
004ef435 mov dword ptr [esp + 0x15c], 9
004ef440 movss dword ptr [esp + 0xdc], xmm0
004ef449 mov dword ptr [esp + 0x120], 0x10000
004ef454 mov dword ptr [esp + 0x124], 0
004ef45f call 0x6a3420
004ef464 call 0x6c3d90
004ef469 movss xmm2, dword ptr [0xb6c9b0]
004ef471 and eax, 1
004ef474 add eax, 2
004ef477 mov dword ptr [esp + 0x10], eax
004ef47b nop dword ptr [eax + eax]
004ef480 call 0x6c3d90
004ef485 movss xmm1, dword ptr [edi + 0x194]
004ef48d xorps xmm1, xmm2
004ef490 movss dword ptr [esp + 0x40], xmm1
004ef496 movd xmm0, eax
004ef49a cvtdq2pd xmm0, xmm0
004ef49e shr eax, 0x1f
004ef4a1 movss xmm1, dword ptr [edi + 0x198]
004ef4a9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004ef4b2 xorps xmm1, xmm2
004ef4b5 movss dword ptr [esp + 0x48], xmm1
004ef4bb cvtpd2ps xmm0, xmm0
004ef4bf mulss xmm0, dword ptr [0xb6a19c]
004ef4c7 subss xmm0, dword ptr [0xb6a480]
004ef4cf mulss xmm0, dword ptr [0xb6ab20]
004ef4d7 mulss xmm0, dword ptr [0xb6a230]
004ef4df movss dword ptr [esp + 0x2c], xmm0
004ef4e5 call 0x411fe0
004ef4ea movss dword ptr [esp + 0x24], xmm0
004ef4f0 movss xmm0, dword ptr [esp + 0x2c]
004ef4f6 call 0x412010
004ef4fb movss xmm5, dword ptr [esp + 0x24]
004ef501 movaps xmm1, xmm0
004ef504 mulss xmm0, dword ptr [esp + 0x40]
004ef50a movaps xmm4, xmm5
004ef50d mulss xmm4, dword ptr [esp + 0x40]
004ef513 mulss xmm1, dword ptr [esp + 0x48]
004ef519 mulss xmm5, dword ptr [esp + 0x48]
004ef51f subss xmm4, xmm1
004ef523 addss xmm5, xmm0
004ef527 movaps xmm0, xmm4
004ef52a mulss xmm0, dword ptr [0xb6a9c8]
004ef532 addss xmm0, dword ptr [edi + 0x294]
004ef53a movss dword ptr [esp + 0x34], xmm0
004ef540 movaps xmm0, xmm5
004ef543 mulss xmm0, dword ptr [0xb6a9c8]
004ef54b addss xmm0, dword ptr [edi + 0x298]
004ef553 movss dword ptr [esp + 0x38], xmm0
004ef559 call 0x6c3d90
004ef55e movss xmm3, dword ptr [0xb6aeb8]
004ef566 lea edx, [esp + 0x14]
004ef56a push 0
004ef56c push edi
004ef56d movd xmm0, eax
004ef571 lea ecx, [esp + 0x3c]
004ef575 cvtdq2pd xmm0, xmm0
004ef579 shr eax, 0x1f
004ef57c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004ef585 cvtpd2ps xmm1, xmm0
004ef589 mulss xmm1, dword ptr [0xb6a19c]
004ef591 addss xmm1, xmm1
004ef595 addss xmm1, dword ptr [0xb6a614]
004ef59d movaps xmm0, xmm1
004ef5a0 mulss xmm1, xmm5
004ef5a4 mulss xmm0, xmm4
004ef5a8 movss dword ptr [esp + 0x20], xmm1
004ef5ae movss dword ptr [esp + 0x1c], xmm0
004ef5b4 call 0x4e70a0
004ef5b9 movss xmm2, dword ptr [0xb6c9b0]
004ef5c1 add esp, 8
004ef5c4 sub dword ptr [esp + 0x10], 1
004ef5c9 jne 0x4ef480
004ef5cf mov dword ptr [edi + 0xab4], 0x10
004ef5d9 inc dword ptr [edi + 0xb14]
004ef5df cmp dword ptr [edi + 0xb14], 4
004ef5e6 jle 0x4ef795
004ef5ec movss xmm0, dword ptr [edi + 0x2c4]
004ef5f4 mulss xmm0, dword ptr [0xb6a4c4]
004ef5fc movss dword ptr [edi + 0x2c4], xmm0
004ef604 jmp 0x4ef795
004ef609 mov eax, dword ptr [edi + 0x30]
004ef60c inc eax
004ef60d push eax
004ef60e lea eax, [esp + 0x168]
004ef615 push 0xb40c4c
004ef61a push eax
004ef61b call 0x4e6170
004ef620 add esp, 0xc
004ef623 lea eax, [esp + 0x164]
004ef62a lea ecx, [edi + 0x3c]
004ef62d push 0
004ef62f push eax
004ef630 call 0x4054f0
004ef635 cmp dword ptr [edi + 0x70], 0
004ef639 je 0x4ef795
004ef63f push 0xb40de4
004ef644 lea ecx, [edi + 0x6c]
004ef647 call 0x405e90
004ef64c test al, al
004ef64e je 0x4ef795
004ef654 mov ecx, edi
004ef656 call 0x695680
004ef65b lea ecx, [esp + 0x14]
004ef65f movss xmm0, dword ptr [eax + 0x294]
004ef667 movss xmm1, dword ptr [eax + 0x298]
004ef66f lea eax, [esp + 0x54]
004ef673 subss xmm0, dword ptr [edi + 0x294]
004ef67b subss xmm1, dword ptr [edi + 0x298]
004ef683 push eax
004ef684 movss dword ptr [esp + 0x18], xmm0
004ef68a movss dword ptr [esp + 0x1c], xmm1
004ef690 call 0x962560
004ef695 movss xmm3, dword ptr [edi + 0x2c4]
004ef69d ucomiss xmm3, dword ptr [0xb6a18c]
004ef6a4 movss xmm1, dword ptr [eax]
004ef6a8 movss xmm2, dword ptr [eax + 4]
004ef6ad mulss xmm1, dword ptr [0xb6a9c8]
004ef6b5 mulss xmm2, dword ptr [0xb6a9c8]
004ef6bd lahf 
004ef6be test ah, 0x44
004ef6c1 jnp 0x4ef6fb
004ef6c3 movss xmm0, dword ptr [edi + 0x2f4]
004ef6cb mulss xmm1, xmm0
004ef6cf mulss xmm2, xmm0
004ef6d3 divss xmm1, xmm3
004ef6d7 divss xmm2, xmm3
004ef6db addss xmm1, dword ptr [edi + 0x2b8]
004ef6e3 addss xmm2, dword ptr [edi + 0x2bc]
004ef6eb movss dword ptr [edi + 0x2b8], xmm1
004ef6f3 movss dword ptr [edi + 0x2bc], xmm2
004ef6fb push ecx
004ef6fc mov dword ptr [esp], 0x3f8ccccd
004ef703 push 0
004ef705 push 2
004ef707 push ecx
004ef708 mov dword ptr [esp], 0x3f800000
004ef70f mov ecx, edi
004ef711 push 0x73
004ef713 call 0x6ad720
004ef718 mov dword ptr [edi + 0xb10], 0
004ef722 mov dword ptr [edi + 0xab4], 4
004ef72c jmp 0x4ef795
004ef72e mov eax, dword ptr [edi + 0x30]
004ef731 inc eax
004ef732 push eax
004ef733 lea eax, [esp + 0x168]
004ef73a push 0xb42af0
004ef73f push eax
004ef740 call 0x4e6170
004ef745 add esp, 0xc
004ef748 lea eax, [esp + 0x164]
004ef74f lea ecx, [edi + 0x3c]
004ef752 push 0
004ef754 push eax
004ef755 call 0x4054f0
004ef75a movss xmm0, dword ptr [edi + 0x2c4]
004ef762 mulss xmm0, dword ptr [0xb6a4c4]
004ef76a movss dword ptr [edi + 0x2c4], xmm0
004ef772 cmp dword ptr [edi + 0x70], 0
004ef776 je 0x4ef781
004ef778 cmp byte ptr [edi + 0x80], 0
004ef77f jne 0x4ef795
004ef781 mov dword ptr [edi + 0x360], 0x3c
004ef78b mov dword ptr [edi + 0xab4], 3
004ef795 mov eax, dword ptr [edi + 8]
004ef798 mov ecx, dword ptr [edi + 0xc]
004ef79b cmp eax, ecx
004ef79d je 0x4ef7e9
004ef79f movss xmm1, dword ptr [0xb6a820]
004ef7a7 nop word ptr [eax + eax]
004ef7b0 mov edx, dword ptr [eax + 8]
004ef7b3 and edx, 0x1000004
004ef7b9 or edx, 0
004ef7bc je 0x4ef7e2
004ef7be movss xmm0, dword ptr [edi + 0x14]
004ef7c3 subss xmm0, dword ptr [eax]
004ef7c7 movss dword ptr [edi + 0x14], xmm0
004ef7cc movss xmm0, dword ptr [eax]
004ef7d0 mulss xmm0, xmm1
004ef7d4 movss dword ptr [eax], xmm0
004ef7d8 addss xmm0, dword ptr [edi + 0x14]
004ef7dd movss dword ptr [edi + 0x14], xmm0
004ef7e2 add eax, 0x38
004ef7e5 cmp eax, ecx
004ef7e7 jne 0x4ef7b0
004ef7e9 cmp byte ptr [edi + 0x16b], 0
004ef7f0 je 0x4efa9f
004ef7f6 mov eax, dword ptr [0xbfd65c]
004ef7fb lea esi, [edi + 0x294]
004ef801 mov dword ptr [esp + 0x40], esi
004ef805 mov dword ptr [esp + 0x1c], eax
004ef809 call 0x6c3d90
004ef80e mov dword ptr [esp + 0x10], eax
004ef812 lea eax, [esp + 0x10]
004ef816 push eax
004ef817 lea eax, [esp + 0x38]
004ef81b mov dword ptr [esp + 0x38], 0
004ef823 push eax
004ef824 push 0
004ef826 push 0xc02fec
004ef82b push esi
004ef82c lea eax, [esp + 0x50]
004ef830 mov dword ptr [esp + 0x50], 0
004ef838 push eax
004ef839 lea eax, [esp + 0x24]
004ef83d mov dword ptr [esp + 0x24], 0xd9
004ef845 push eax
004ef846 call 0x800fb0
004ef84b mov ecx, dword ptr [esp + 0x1c]
004ef84f push 0
004ef851 push dword ptr [esp + 0x10]
004ef855 mov ecx, dword ptr [ecx + 0x1c3198]
004ef85b call 0x6c4b30
004ef860 mov esi, eax
004ef862 mov dword ptr [esp + 0x20], esi
004ef866 test esi, esi
004ef868 je 0x4efa83
004ef86e call dword ptr [0xa064c0]
004ef874 mov ecx, dword ptr [esi + 0x320]
004ef87a mov dword ptr [esp + 0x48], eax
004ef87e lea eax, [esi + 0x320]
004ef884 mov dword ptr [esi + 0x34], 0
004ef88b mov dword ptr [esi + 0x38], 0
004ef892 test ecx, ecx
004ef894 je 0x4ef8b0
004ef896 mov dword ptr [esp + 0x2c], eax
004ef89a add ecx, 0x324
004ef8a0 lea eax, [esp + 0x2c]
004ef8a4 push eax
004ef8a5 call 0x4bc3c0
004ef8aa lea eax, [esi + 0x320]
004ef8b0 push dword ptr [esp + 0x10]
004ef8b4 mov dword ptr [eax], 0
004ef8ba mov ecx, esi
004ef8bc mov eax, dword ptr [edi + 0x294]
004ef8c2 push dword ptr [esp + 0x38]
004ef8c6 mov dword ptr [esi + 0x294], eax
004ef8cc mov eax, dword ptr [edi + 0x298]
004ef8d2 push dword ptr [esp + 0x44]
004ef8d6 mov dword ptr [esi + 0x298], eax
004ef8dc movss xmm0, dword ptr [0xc02fec]
004ef8e4 mov eax, dword ptr [esi]
004ef8e6 push dword ptr [esp + 0x18]
004ef8ea movss dword ptr [esi + 0x2b8], xmm0
004ef8f2 movss xmm0, dword ptr [0xc02ff0]
004ef8fa movss dword ptr [esi + 0x2bc], xmm0
004ef902 call dword ptr [eax + 4]
004ef905 mov eax, dword ptr [esp + 0x1c]
004ef909 push esi
004ef90a mov edx, dword ptr [eax + 0x18190]
004ef910 mov ecx, dword ptr [edx + 0x1214]
004ef916 lea eax, [ecx + 1]
004ef919 mov dword ptr [edx + 0x1214], eax
004ef91f mov dword ptr [esi + 0x20], ecx
004ef922 lea ecx, [edx + 0x1218]
004ef928 call 0x413280
004ef92d push esi
004ef92e call 0x6d94d0
004ef933 test al, al
004ef935 je 0x4ef93e
004ef937 push ecx
004ef938 push esi
004ef939 call 0x6d9590
004ef93e cmp byte ptr [esi + 0x16a], 0
004ef945 je 0x4efa73
004ef94b mov ecx, dword ptr [esp + 0x1c]
004ef94f mov eax, dword ptr [ecx + 0x283c20]
004ef955 cmp eax, dword ptr [ecx + 0x283c24]
004ef95b je 0x4efa73
004ef961 mov eax, dword ptr [esi + 0x28]
004ef964 mov dword ptr [esp + 0x14], eax
004ef968 mov eax, dword ptr [esi + 0x2c]
004ef96b mov dword ptr [esp + 0x18], eax
004ef96f lea eax, [ecx + 0x283c48]
004ef975 lea ecx, [esp + 0x14]
004ef979 mov dword ptr [esp + 0x2c], eax
004ef97d push ecx
004ef97e lea ecx, [esp + 0x28]
004ef982 push ecx
004ef983 mov ecx, eax
004ef985 call 0x937c80
004ef98a mov ecx, dword ptr [esp + 0x2c]
004ef98e mov eax, dword ptr [ecx]
004ef990 mov dword ptr [esp + 0x2c], eax
004ef994 cmp dword ptr [esp + 0x24], eax
004ef998 jne 0x4ef9c4
004ef99a mov eax, dword ptr [esi + 0x28]
004ef99d mov dword ptr [esp + 0x14], eax
004ef9a1 lea eax, [esp + 0x14]
004ef9a5 push eax
004ef9a6 lea eax, [esp + 0x28]
004ef9aa mov dword ptr [esp + 0x1c], 0xffffffff
004ef9b2 push eax
004ef9b3 call 0x937c80
004ef9b8 mov ecx, dword ptr [esp + 0x2c]
004ef9bc cmp dword ptr [eax], ecx
004ef9be je 0x4efa73
004ef9c4 mov esi, dword ptr [0xbfd65c]
004ef9ca xor edx, edx
004ef9cc mov dword ptr [esp + 0xc], edx
004ef9d0 mov eax, dword ptr [esi + 0x1ba54]
004ef9d6 sub eax, dword ptr [esi + 0x1ba50]
004ef9dc sar eax, 2
004ef9df test eax, eax
004ef9e1 je 0x4efa6f
004ef9e7 mov edi, dword ptr [esp + 0x20]
004ef9eb nop dword ptr [eax + eax]
004ef9f0 mov ecx, dword ptr [esi + 0x1ba54]
004ef9f6 mov eax, ecx
004ef9f8 sub eax, dword ptr [esi + 0x1ba50]
004ef9fe test eax, 0xfffffffc
004efa03 jne 0x4efa1e
004efa05 push 0xb3f4d0
004efa0a push 3
004efa0c call 0x95e330
004efa11 mov ecx, dword ptr [esi + 0x1ba54]
004efa17 add esp, 8
004efa1a mov edx, dword ptr [esp + 0xc]
004efa1e mov eax, dword ptr [esi + 0x1ba50]
004efa24 sub ecx, eax
004efa26 sar ecx, 2
004efa29 cmp edx, ecx
004efa2b jae 0x4efa30
004efa2d lea eax, [eax + edx*4]
004efa30 mov ecx, dword ptr [eax]
004efa32 push 0xc02fec
004efa37 push dword ptr [esp + 0x44]
004efa3b add ecx, 0x1ec0
004efa41 push edi
004efa42 push 6
004efa44 call 0x935fd0
004efa49 mov esi, dword ptr [0xbfd65c]
004efa4f mov edx, dword ptr [esp + 0xc]
004efa53 inc edx
004efa54 mov dword ptr [esp + 0xc], edx
004efa58 mov eax, dword ptr [esi + 0x1ba54]
004efa5e sub eax, dword ptr [esi + 0x1ba50]
004efa64 sar eax, 2
004efa67 cmp edx, eax
004efa69 jb 0x4ef9f0
004efa6b mov edi, dword ptr [esp + 0x5c]
004efa6f mov esi, dword ptr [esp + 0x20]
004efa73 call dword ptr [0xa064c0]
004efa79 sub eax, dword ptr [esp + 0x48]
004efa7d add dword ptr [0xbffe0c], eax
004efa83 movss xmm0, dword ptr [esi + 0x2dc]
004efa8b addss xmm0, xmm0
004efa8f movss dword ptr [esi + 0x2dc], xmm0
004efa97 movss dword ptr [esi + 0x2d8], xmm0
004efa9f cmp dword ptr [edi + 0xab4], 0x10
004efaa6 je 0x4efabb
004efaa8 xorps xmm0, xmm0
004efaab comiss xmm0, dword ptr [edi + 0x2b8]
004efab2 seta al
004efab5 mov byte ptr [edi + 0x13c], al
004efabb mov ecx, dword ptr [esp + 0x184]
004efac2 pop edi
004efac3 pop esi
004efac4 xor ecx, esp
004efac6 call 0x9eacd7
004efacb mov esp, ebp
004efacd pop ebp
004eface ret 
