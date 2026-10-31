0053c8f0 push ebp
0053c8f1 mov ebp, esp
0053c8f3 sub esp, 0x104
0053c8f9 mov eax, dword ptr [0xbaa3b4]
0053c8fe xor eax, ebp
0053c900 mov dword ptr [ebp - 4], eax
0053c903 push ebx
0053c904 push esi
0053c905 push edi
0053c906 mov edi, ecx
0053c908 cvttss2si eax, dword ptr [edi + 0x2f8]
0053c910 cvttss2si ebx, dword ptr [edi + 0x2fc]
0053c918 sub ebx, eax
0053c91a mov eax, dword ptr [edi + 0xab4]
0053c920 mov dword ptr [ebp - 0xbc], ebx
0053c926 cmp eax, 8
0053c929 ja 0x53d04d
0053c92f jmp dword ptr [eax*4 + 0x53d49c]
0053c936 xorps xmm0, xmm0
0053c939 mov dword ptr [edi + 0xab4], 4
0053c943 movups xmmword ptr [ebp - 0xf0], xmm0
0053c94a lea eax, [ebp - 0x100]
0053c950 mov dword ptr [ebp - 0xe0], 0
0053c95a movaps xmm0, xmmword ptr [0xb6bfa0]
0053c961 lea ecx, [edi + 0x1dc]
0053c967 push eax
0053c968 movups xmmword ptr [ebp - 0x100], xmm0
0053c96f mov dword ptr [ebp - 0xdc], 0x3dcccccd
0053c979 mov dword ptr [ebp - 0xd8], 0x3dcccccd
0053c983 call 0x4021a0
0053c988 cmp dword ptr [edi + 0xe6c], -1
0053c98f je 0x53c9ad
0053c991 mov edx, 5
0053c996 mov dword ptr [edi + 0xb14], edx
0053c99c pop edi
0053c99d pop esi
0053c99e pop ebx
0053c99f mov ecx, dword ptr [ebp - 4]
0053c9a2 xor ecx, ebp
0053c9a4 call 0x9eacd7
0053c9a9 mov esp, ebp
0053c9ab pop ebp
0053c9ac ret 
0053c9ad call 0x6c3d90
0053c9b2 xor edx, edx
0053c9b4 mov ecx, 0xa
0053c9b9 div ecx
0053c9bb add edx, 5
0053c9be mov dword ptr [edi + 0xb14], edx
0053c9c4 pop edi
0053c9c5 pop esi
0053c9c6 pop ebx
0053c9c7 mov ecx, dword ptr [ebp - 4]
0053c9ca xor ecx, ebp
0053c9cc call 0x9eacd7
0053c9d1 mov esp, ebp
0053c9d3 pop ebp
0053c9d4 ret 
0053c9d5 movss xmm0, dword ptr [edi + 0x2c4]
0053c9dd lea ecx, [edi + 0x3c]
0053c9e0 mulss xmm0, dword ptr [0xb6a50c]
0053c9e8 push 0
0053c9ea push 0xb404a0
0053c9ef mov dword ptr [edi + 0x180], 4
0053c9f9 movss dword ptr [edi + 0x2c4], xmm0
0053ca01 call 0x4054f0
0053ca06 mov ecx, edi
0053ca08 call 0x695680
0053ca0d push ecx
0053ca0e mov dword ptr [ebp - 0xc0], eax
0053ca14 mov ecx, edi
0053ca16 lea eax, [ebp - 0xb8]
0053ca1c mov dword ptr [esp], 0
0053ca23 push eax
0053ca24 call 0x695a30
0053ca29 movss xmm2, dword ptr [ebp - 0xb8]
0053ca31 movss xmm3, dword ptr [ebp - 0xb4]
0053ca39 movaps xmm0, xmm2
0053ca3c movss xmm4, dword ptr [edi + 0x294]
0053ca44 movaps xmm1, xmm3
0053ca47 movss xmm5, dword ptr [edi + 0x298]
0053ca4f subss xmm0, xmm4
0053ca53 subss xmm1, xmm5
0053ca57 movss dword ptr [ebp - 0xcc], xmm4
0053ca5f movss dword ptr [ebp - 0xd0], xmm5
0053ca67 mulss xmm0, xmm0
0053ca6b mulss xmm1, xmm1
0053ca6f addss xmm1, xmm0
0053ca73 movss xmm0, dword ptr [0xb6ad44]
0053ca7b comiss xmm0, xmm1
0053ca7e jbe 0x53cb17
0053ca84 movaps xmm1, xmm5
0053ca87 subss xmm4, xmm2
0053ca8b subss xmm1, xmm3
0053ca8f movss dword ptr [ebp - 0xc8], xmm4
0053ca97 movaps xmm0, xmm1
0053ca9a movss dword ptr [ebp - 0xbc], xmm1
0053caa2 mulss xmm0, xmm1
0053caa6 movaps xmm1, xmm4
0053caa9 mulss xmm1, xmm4
0053caad addss xmm0, xmm1
0053cab1 call 0x4228c0
0053cab6 xorps xmm6, xmm6
0053cab9 comiss xmm0, xmm6
0053cabc jbe 0x53cadf
0053cabe movss xmm1, dword ptr [0xb6ab20]
0053cac6 divss xmm1, xmm0
0053caca movaps xmm0, xmm1
0053cacd mulss xmm1, dword ptr [ebp - 0xbc]
0053cad5 mulss xmm0, dword ptr [ebp - 0xc8]
0053cadd jmp 0x53caef
0053cadf movss xmm0, dword ptr [ebp - 0xc8]
0053cae7 movss xmm1, dword ptr [ebp - 0xbc]
0053caef movss xmm2, dword ptr [ebp - 0xb8]
0053caf7 movss xmm3, dword ptr [ebp - 0xb4]
0053caff addss xmm2, xmm0
0053cb03 movss xmm4, dword ptr [ebp - 0xcc]
0053cb0b addss xmm3, xmm1
0053cb0f movss xmm5, dword ptr [ebp - 0xd0]
0053cb17 cmp dword ptr [edi + 0xe6c], -1
0053cb1e je 0x53cb8f
0053cb20 lea eax, [ebp - 0xb8]
0053cb26 xorps xmm2, xmm2
0053cb29 push eax
0053cb2a mov ecx, edi
0053cb2c call 0x6af0c0
0053cb31 movss xmm3, dword ptr [edi + 0x2c4]
0053cb39 xorps xmm0, xmm0
0053cb3c ucomiss xmm3, xmm0
0053cb3f movss xmm1, dword ptr [eax]
0053cb43 movss xmm2, dword ptr [eax + 4]
0053cb48 mulss xmm1, dword ptr [0xb6a3d4]
0053cb50 mulss xmm2, dword ptr [0xb6a3d4]
0053cb58 lahf 
0053cb59 test ah, 0x44
0053cb5c jnp 0x53cc34
0053cb62 movss xmm0, dword ptr [edi + 0x2f4]
0053cb6a mulss xmm2, xmm0
0053cb6e mulss xmm1, xmm0
0053cb72 divss xmm2, xmm3
0053cb76 divss xmm1, xmm3
0053cb7a addss xmm2, dword ptr [edi + 0x2bc]
0053cb82 movss dword ptr [edi + 0x2bc], xmm2
0053cb8a jmp 0x53cc24
0053cb8f ucomiss xmm2, xmm4
0053cb92 lahf 
0053cb93 test ah, 0x44
0053cb96 jp 0x53cba5
0053cb98 ucomiss xmm3, xmm5
0053cb9b lahf 
0053cb9c test ah, 0x44
0053cb9f jnp 0x53cc34
0053cba5 subss xmm2, xmm4
0053cba9 subss xmm3, xmm5
0053cbad lea eax, [ebp - 0xd4]
0053cbb3 push eax
0053cbb4 lea ecx, [ebp - 0xb8]
0053cbba movss dword ptr [ebp - 0xb8], xmm2
0053cbc2 movss dword ptr [ebp - 0xb4], xmm3
0053cbca call 0x962560
0053cbcf movss xmm2, dword ptr [edi + 0x2c4]
0053cbd7 xorps xmm0, xmm0
0053cbda ucomiss xmm2, xmm0
0053cbdd movss xmm1, dword ptr [eax]
0053cbe1 movss xmm3, dword ptr [eax + 4]
0053cbe6 mulss xmm1, dword ptr [0xb6a3d4]
0053cbee mulss xmm3, dword ptr [0xb6a3d4]
0053cbf6 lahf 
0053cbf7 test ah, 0x44
0053cbfa jnp 0x53cc34
0053cbfc movss xmm0, dword ptr [edi + 0x2f4]
0053cc04 mulss xmm1, xmm0
0053cc08 mulss xmm0, xmm3
0053cc0c divss xmm1, xmm2
0053cc10 divss xmm0, xmm2
0053cc14 addss xmm0, dword ptr [edi + 0x2bc]
0053cc1c movss dword ptr [edi + 0x2bc], xmm0
0053cc24 addss xmm1, dword ptr [edi + 0x2b8]
0053cc2c movss dword ptr [edi + 0x2b8], xmm1
0053cc34 mov eax, dword ptr [ebp - 0xc0]
0053cc3a movss xmm1, dword ptr [eax + 0x294]
0053cc42 movss xmm0, dword ptr [eax + 0x298]
0053cc4a subss xmm0, dword ptr [edi + 0x298]
0053cc52 subss xmm1, dword ptr [edi + 0x294]
0053cc5a mulss xmm0, xmm0
0053cc5e mulss xmm1, xmm1
0053cc62 addss xmm0, xmm1
0053cc66 call 0x4228c0
0053cc6b mov eax, dword ptr [edi + 0x160]
0053cc71 and eax, 0x1000a00
0053cc76 movss dword ptr [ebp - 0xc0], xmm0
0053cc7e or eax, 0
0053cc81 jne 0x53d04d
0053cc87 cmp dword ptr [edi + 0xb14], eax
0053cc8d jg 0x53d04d
0053cc93 cmp dword ptr [edi + 0xe6c], -1
0053cc9a mov ecx, edi
0053cc9c je 0x53cd1a
0053cc9e call 0x6afb10
0053cca3 test al, al
0053cca5 je 0x53cce7
0053cca7 lea eax, [ebp - 0xd4]
0053ccad mov ecx, edi
0053ccaf push eax
0053ccb0 call 0x6afac0
0053ccb5 movss xmm1, dword ptr [eax]
0053ccb9 movss xmm0, dword ptr [eax + 4]
0053ccbe subss xmm0, dword ptr [edi + 0x298]
0053ccc6 subss xmm1, dword ptr [edi + 0x294]
0053ccce mulss xmm0, xmm0
0053ccd2 mulss xmm1, xmm1
0053ccd6 addss xmm0, xmm1
0053ccda comiss xmm0, dword ptr [0xb6aafc]
0053cce1 ja 0x53cd96
0053cce7 cmp dword ptr [edi + 0xe78], 0
0053ccee jne 0x53d04d
0053ccf4 movss xmm1, dword ptr [0xb6accc]
0053ccfc mov ecx, edi
0053ccfe push 7
0053cd00 push 0
0053cd02 call 0x6a15a0
0053cd07 test al, al
0053cd09 je 0x53d04d
0053cd0f push 1
0053cd11 mov ecx, edi
0053cd13 call 0x6afe20
0053cd18 jmp 0x53cd51
0053cd1a call 0x695680
0053cd1f push eax
0053cd20 mov ecx, edi
0053cd22 call 0x6aeb40
0053cd27 test al, al
0053cd29 je 0x53d04d
0053cd2f call 0x6c3d90
0053cd34 test al, 3
0053cd36 jne 0x53d04d
0053cd3c movss xmm1, dword ptr [ebp - 0xc0]
0053cd44 movss xmm0, dword ptr [0xb6ab20]
0053cd4c comiss xmm0, xmm1
0053cd4f jbe 0x53cd85
0053cd51 push 0
0053cd53 push 0xb40510
0053cd58 lea ecx, [edi + 0x3c]
0053cd5b call 0x4054f0
0053cd60 cmp dword ptr [edi + 0x70], 0
0053cd64 je 0x53cd76
0053cd66 movss xmm1, dword ptr [0xb6a864]
0053cd6e lea ecx, [edi + 0x6c]
0053cd71 call 0x403c00
0053cd76 mov dword ptr [edi + 0xab4], 8
0053cd80 jmp 0x53d04d
0053cd85 movss xmm0, dword ptr [0xb6ac04]
0053cd8d comiss xmm0, xmm1
0053cd90 jbe 0x53d04d
0053cd96 push 0
0053cd98 push 0xb401e0
0053cd9d lea ecx, [edi + 0x3c]
0053cda0 call 0x4054f0
0053cda5 mov dword ptr [edi + 0xab4], 7
0053cdaf jmp 0x53d04d
0053cdb4 movss xmm0, dword ptr [edi + 0x2c4]
0053cdbc mov dword ptr [edi + 0x180], 2
0053cdc6 mov eax, dword ptr [edi + 0x70]
0053cdc9 test eax, eax
0053cdcb je 0x53d0f3
0053cdd1 mov al, byte ptr [eax + 0x34]
0053cdd4 test al, al
0053cdd6 je 0x53d027
0053cddc mulss xmm0, dword ptr [0xb6a588]
0053cde4 movss xmm1, dword ptr [edi + 0x2f4]
0053cdec movss dword ptr [edi + 0x2c4], xmm0
0053cdf4 movss xmm3, dword ptr [edi + 0xb04]
0053cdfc movss xmm2, dword ptr [edi + 0xb00]
0053ce04 mulss xmm2, dword ptr [0xb6a8c0]
0053ce0c mulss xmm3, dword ptr [0xb6a8c0]
0053ce14 movss xmm0, dword ptr [0xb6a704]
0053ce1c mulss xmm2, xmm1
0053ce20 mulss xmm3, xmm1
0053ce24 addss xmm2, dword ptr [edi + 0x2b8]
0053ce2c addss xmm3, dword ptr [edi + 0x2bc]
0053ce34 movss dword ptr [ebp - 0xcc], xmm2
0053ce3c movss dword ptr [edi + 0x2b8], xmm2
0053ce44 movss dword ptr [ebp - 0xd0], xmm3
0053ce4c movss dword ptr [edi + 0x2bc], xmm3
0053ce54 call 0x411fe0
0053ce59 movss dword ptr [ebp - 0xc0], xmm0
0053ce61 movss xmm0, dword ptr [0xb6a704]
0053ce69 call 0x412010
0053ce6e movss xmm5, dword ptr [edi + 0xb00]
0053ce76 movaps xmm2, xmm0
0053ce79 movss xmm6, dword ptr [edi + 0xb04]
0053ce81 movaps xmm0, xmm5
0053ce84 mulss xmm0, xmm2
0053ce88 movaps xmm1, xmm6
0053ce8b mulss xmm1, xmm2
0053ce8f movaps xmm4, xmm5
0053ce92 mulss xmm4, dword ptr [ebp - 0xc0]
0053ce9a movaps xmm3, xmm6
0053ce9d mulss xmm3, dword ptr [ebp - 0xc0]
0053cea5 subss xmm4, xmm1
0053cea9 movss xmm1, dword ptr [ebp - 0xd0]
0053ceb1 mulss xmm1, xmm6
0053ceb5 addss xmm3, xmm0
0053ceb9 movaps xmm0, xmm5
0053cebc mulss xmm0, dword ptr [ebp - 0xcc]
0053cec4 addss xmm1, xmm0
0053cec8 mulss xmm5, xmm1
0053cecc mulss xmm6, xmm1
0053ced0 movss dword ptr [edi + 0x2b8], xmm5
0053ced8 movss dword ptr [edi + 0x2bc], xmm6
0053cee0 movss xmm1, dword ptr [edi + 0x298]
0053cee8 subss xmm1, dword ptr [edi + 0x290]
0053cef0 movss xmm0, dword ptr [edi + 0x294]
0053cef8 subss xmm0, dword ptr [edi + 0x28c]
0053cf00 mulss xmm1, xmm3
0053cf04 mulss xmm0, xmm4
0053cf08 addss xmm1, xmm0
0053cf0c movaps xmm0, xmm1
0053cf0f mulss xmm1, xmm3
0053cf13 mulss xmm0, xmm4
0053cf17 subss xmm6, xmm1
0053cf1b subss xmm5, xmm0
0053cf1f movss dword ptr [edi + 0x2bc], xmm6
0053cf27 movss dword ptr [edi + 0x2b8], xmm5
0053cf2f movss xmm0, dword ptr [edi + 0x28c]
0053cf37 movss xmm1, dword ptr [edi + 0x290]
0053cf3f subss xmm1, dword ptr [edi + 0x298]
0053cf47 subss xmm0, dword ptr [edi + 0x294]
0053cf4f mulss xmm1, dword ptr [edi + 0xb04]
0053cf57 mulss xmm0, dword ptr [edi + 0xb00]
0053cf5f addss xmm1, xmm0
0053cf63 movss xmm0, dword ptr [0xb6a9c8]
0053cf6b comiss xmm0, xmm1
0053cf6e jbe 0x53d04d
0053cf74 cmp dword ptr [edi + 0xe6c], -1
0053cf7b mov dword ptr [edi + 0x180], 4
0053cf85 je 0x53d003
0053cf87 movss xmm1, dword ptr [0xb6accc]
0053cf8f mov ecx, edi
0053cf91 push 7
0053cf93 push 0
0053cf95 call 0x6a15a0
0053cf9a test al, al
0053cf9c jne 0x53d003
0053cf9e movss xmm0, dword ptr [0xc02fec]
0053cfa6 movss dword ptr [edi + 0xb00], xmm0
0053cfae movss xmm0, dword ptr [0xc02ff0]
0053cfb6 movss dword ptr [edi + 0xb04], xmm0
0053cfbe movss xmm0, dword ptr [0xc02fec]
0053cfc6 movss dword ptr [edi + 0x28c], xmm0
0053cfce movss xmm0, dword ptr [0xc02ff0]
0053cfd6 movss dword ptr [edi + 0x290], xmm0
0053cfde mov dword ptr [edi + 0xb14], 0xf
0053cfe8 push 0
0053cfea push 0xb404a0
0053cfef lea ecx, [edi + 0x3c]
0053cff2 call 0x4054f0
0053cff7 mov dword ptr [edi + 0xab4], 4
0053d001 jmp 0x53d04d
0053d003 push 1
0053d005 mov ecx, edi
0053d007 call 0x6afe20
0053d00c push 0
0053d00e push 0xb40510
0053d013 lea ecx, [edi + 0x3c]
0053d016 mov dword ptr [edi + 0xab4], 8
0053d020 call 0x4054f0
0053d025 jmp 0x53d04d
0053d027 mulss xmm0, dword ptr [0xb6a50c]
0053d02f lea ebx, [edi + 0x3c]
0053d032 movss dword ptr [edi + 0x2c4], xmm0
0053d03a cmp byte ptr [edi + 0x80], 0
0053d041 je 0x53d106
0053d047 mov ebx, dword ptr [ebp - 0xbc]
0053d04d cmp dword ptr [edi + 0xab4], 4
0053d054 je 0x53d063
0053d056 mov eax, dword ptr [edi + 0x70]
0053d059 test eax, eax
0053d05b je 0x53d063
0053d05d cmp byte ptr [eax + 0x34], 0
0053d061 jne 0x53d0d0
0053d063 cmp dword ptr [edi + 0xe78], 0
0053d06a jne 0x53d0bf
0053d06c mov eax, dword ptr [edi + 0xe6c]
0053d072 cmp eax, -1
0053d075 je 0x53d0d0
0053d077 push edi
0053d078 push eax
0053d079 push 9
0053d07b call 0x8b10b0
0053d080 test al, al
0053d082 je 0x53d0d0
0053d084 movss xmm2, dword ptr [0xb6a2cc]
0053d08c lea eax, [ebp - 0xb8]
0053d092 push eax
0053d093 mov ecx, edi
0053d095 call 0x6af0c0
0053d09a mov ecx, eax
0053d09c movss xmm0, dword ptr [ecx]
0053d0a0 ucomiss xmm0, dword ptr [0xc02fec]
0053d0a7 lahf 
0053d0a8 test ah, 0x44
0053d0ab jp 0x53d0bf
0053d0ad movss xmm0, dword ptr [ecx + 4]
0053d0b2 ucomiss xmm0, dword ptr [0xc02ff0]
0053d0b9 lahf 
0053d0ba test ah, 0x44
0053d0bd jnp 0x53d0d0
0053d0bf movss xmm2, dword ptr [0xb6ae44]
0053d0c7 mov ecx, edi
0053d0c9 push 1
0053d0cb call 0x6af8d0
0053d0d0 mov eax, dword ptr [edi + 0xb14]
0053d0d6 test eax, eax
0053d0d8 jle 0x53d0e2
0053d0da sub eax, ebx
0053d0dc mov dword ptr [edi + 0xb14], eax
0053d0e2 mov ecx, dword ptr [ebp - 4]
0053d0e5 pop edi
0053d0e6 pop esi
0053d0e7 xor ecx, ebp
0053d0e9 pop ebx
0053d0ea call 0x9eacd7
0053d0ef mov esp, ebp
0053d0f1 pop ebp
0053d0f2 ret 
0053d0f3 mulss xmm0, dword ptr [0xb6a50c]
0053d0fb lea ebx, [edi + 0x3c]
0053d0fe movss dword ptr [edi + 0x2c4], xmm0
0053d106 call 0x695680
0053d10b movss xmm0, dword ptr [eax + 0x294]
0053d113 movss xmm1, dword ptr [eax + 0x298]
0053d11b movss dword ptr [edi + 0x28c], xmm0
0053d123 movss dword ptr [edi + 0x290], xmm1
0053d12b cmp dword ptr [edi + 0xe6c], -1
0053d132 je 0x53d162
0053d134 lea eax, [ebp - 0xb8]
0053d13a mov ecx, edi
0053d13c push eax
0053d13d call 0x6afac0
0053d142 mov ecx, dword ptr [eax]
0053d144 mov dword ptr [edi + 0x28c], ecx
0053d14a mov ecx, edi
0053d14c mov eax, dword ptr [eax + 4]
0053d14f mov dword ptr [edi + 0x290], eax
0053d155 call 0x6afa80
0053d15a movss xmm1, dword ptr [edi + 0x290]
0053d162 movss xmm0, dword ptr [edi + 0x28c]
0053d16a lea eax, [ebp - 0xc4]
0053d170 subss xmm0, dword ptr [edi + 0x294]
0053d178 subss xmm1, dword ptr [edi + 0x298]
0053d180 push eax
0053d181 lea ecx, [ebp - 0xb8]
0053d187 movss dword ptr [ebp - 0xb8], xmm0
0053d18f movss dword ptr [ebp - 0xb4], xmm1
0053d197 call 0x962560
0053d19c lea ecx, [edi + 0xb00]
0053d1a2 mov edx, dword ptr [eax]
0053d1a4 mov dword ptr [ecx], edx
0053d1a6 mov eax, dword ptr [eax + 4]
0053d1a9 mov dword ptr [ecx + 4], eax
0053d1ac call 0x659490
0053d1b1 mov esi, eax
0053d1b3 mov ecx, ebx
0053d1b5 push 0
0053d1b7 push dword ptr [esi*4 + 0xb42d70]
0053d1be call 0x4054f0
0053d1c3 test esi, esi
0053d1c5 sete al
0053d1c8 mov byte ptr [edi + 0x13c], al
0053d1ce jmp 0x53d047
0053d1d3 cmp dword ptr [edi + 0xe6c], -1
0053d1da movss xmm0, dword ptr [edi + 0x2c4]
0053d1e2 mulss xmm0, dword ptr [0xb6a50c]
0053d1ea movss dword ptr [edi + 0x2c4], xmm0
0053d1f2 je 0x53d269
0053d1f4 lea eax, [ebp - 0xb8]
0053d1fa xorps xmm2, xmm2
0053d1fd push eax
0053d1fe call 0x6af0c0
0053d203 movss xmm2, dword ptr [edi + 0x2c4]
0053d20b ucomiss xmm2, dword ptr [0xb6a18c]
0053d212 movss xmm1, dword ptr [eax]
0053d216 movss xmm3, dword ptr [eax + 4]
0053d21b mulss xmm1, dword ptr [0xb6a2cc]
0053d223 mulss xmm3, dword ptr [0xb6a2cc]
0053d22b lahf 
0053d22c test ah, 0x44
0053d22f jnp 0x53d269
0053d231 movss xmm0, dword ptr [edi + 0x2f4]
0053d239 mulss xmm1, xmm0
0053d23d mulss xmm0, xmm3
0053d241 divss xmm1, xmm2
0053d245 divss xmm0, xmm2
0053d249 addss xmm1, dword ptr [edi + 0x2b8]
0053d251 addss xmm0, dword ptr [edi + 0x2bc]
0053d259 movss dword ptr [edi + 0x2b8], xmm1
0053d261 movss dword ptr [edi + 0x2bc], xmm0
0053d269 push 0
0053d26b mov ecx, edi
0053d26d call 0x6afe20
0053d272 cmp dword ptr [edi + 0x70], 0
0053d276 je 0x53d425
0053d27c push 0xb400ac
0053d281 lea ecx, [edi + 0x6c]
0053d284 call 0x405e90
0053d289 test al, al
0053d28b je 0x53d412
0053d291 mov ecx, edi
0053d293 call 0x695680
0053d298 lea ecx, [ebp - 0xb8]
0053d29e movss xmm0, dword ptr [eax + 0x294]
0053d2a6 movss xmm1, dword ptr [eax + 0x298]
0053d2ae lea eax, [ebp - 0xc4]
0053d2b4 subss xmm0, dword ptr [edi + 0x294]
0053d2bc subss xmm1, dword ptr [edi + 0x298]
0053d2c4 push eax
0053d2c5 movss dword ptr [ebp - 0xb8], xmm0
0053d2cd movss dword ptr [ebp - 0xb4], xmm1
0053d2d5 call 0x962560
0053d2da cmp dword ptr [edi + 0xe6c], -1
0053d2e1 je 0x53d30e
0053d2e3 lea ecx, [edi + 0xe70]
0053d2e9 push 0xc02fec
0053d2ee call 0x962ca0
0053d2f3 test al, al
0053d2f5 je 0x53d30e
0053d2f7 lea eax, [ebp - 0xb8]
0053d2fd push eax
0053d2fe call 0x962560
0053d303 movss xmm0, dword ptr [eax]
0053d307 movss xmm1, dword ptr [eax + 4]
0053d30c jmp 0x53d31e
0053d30e movss xmm1, dword ptr [ebp - 0xc0]
0053d316 movss xmm0, dword ptr [ebp - 0xc4]
0053d31e movss dword ptr [ebp - 0xc8], xmm1
0053d326 xorps xmm1, xmm1
0053d329 push ecx
0053d32a comiss xmm1, xmm0
0053d32d mov dword ptr [esp], 0x3f666666
0053d334 push 0
0053d336 push 2
0053d338 push ecx
0053d339 mov dword ptr [esp], 0x3f59999a
0053d340 mov ecx, edi
0053d342 push 0x2c
0053d344 movss dword ptr [ebp - 0xbc], xmm0
0053d34c seta al
0053d34f mov byte ptr [edi + 0x13c], al
0053d355 call 0x6ad720
0053d35a lea ecx, [ebp - 0xb0]
0053d360 call 0x430d70
0053d365 mov dword ptr [ebp - 0x88], 0x3f19999a
0053d36f call 0x6af030
0053d374 movd xmm0, eax
0053d378 cvtdq2ps xmm0, xmm0
0053d37b comiss xmm0, dword ptr [0xb6a18c]
0053d382 jbe 0x53d38e
0053d384 movss xmm3, dword ptr [0xb6a974]
0053d38c jmp 0x53d396
0053d38e movss xmm3, dword ptr [0xb6a940]
0053d396 movss xmm1, dword ptr [ebp - 0xbc]
0053d39e lea eax, [ebp - 0xb0]
0053d3a4 movss xmm2, dword ptr [ebp - 0xc8]
0053d3ac movaps xmm0, xmm3
0053d3af mulss xmm0, xmm1
0053d3b3 mov ecx, edi
0053d3b5 push eax
0053d3b6 mulss xmm1, dword ptr [0xb6a8cc]
0053d3be lea eax, [ebp - 0xb8]
0053d3c4 push 2
0053d3c6 movss dword ptr [ebp - 0xb8], xmm0
0053d3ce movaps xmm0, xmm2
0053d3d1 mulss xmm2, dword ptr [0xb6a8cc]
0053d3d9 push eax
0053d3da addss xmm1, dword ptr [edi + 0x294]
0053d3e2 mulss xmm0, xmm3
0053d3e6 lea eax, [ebp - 0xc4]
0053d3ec push eax
0053d3ed addss xmm2, dword ptr [edi + 0x298]
0053d3f5 movss dword ptr [ebp - 0xb4], xmm0
0053d3fd movss dword ptr [ebp - 0xc4], xmm1
0053d405 movss dword ptr [ebp - 0xc0], xmm2
0053d40d call 0x6a1a20
0053d412 cmp dword ptr [edi + 0x70], 0
0053d416 je 0x53d425
0053d418 cmp byte ptr [edi + 0x80], 0
0053d41f jne 0x53d04d
0053d425 movss xmm0, dword ptr [0xc02fec]
0053d42d movss dword ptr [edi + 0xb00], xmm0
0053d435 movss xmm0, dword ptr [0xc02ff0]
0053d43d movss dword ptr [edi + 0xb04], xmm0
0053d445 movss xmm0, dword ptr [0xc02fec]
0053d44d movss dword ptr [edi + 0x28c], xmm0
0053d455 movss xmm0, dword ptr [0xc02ff0]
0053d45d movss dword ptr [edi + 0x290], xmm0
0053d465 cmp dword ptr [edi + 0xe6c], -1
0053d46c je 0x53d47e
0053d46e mov edx, 0xf
0053d473 mov dword ptr [edi + 0xb14], edx
0053d479 jmp 0x53cfe8
0053d47e call 0x6c3d90
0053d483 xor edx, edx
0053d485 mov ecx, 0x1e
0053d48a div ecx
0053d48c add edx, 0xf
0053d48f mov dword ptr [edi + 0xb14], edx
0053d495 jmp 0x53cfe8
