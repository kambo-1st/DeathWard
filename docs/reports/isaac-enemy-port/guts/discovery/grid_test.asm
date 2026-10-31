00502e00 movss xmm1, dword ptr [0xb6aa3c]
00502e08 mov edx, ecx
00502e0a movss xmm2, dword ptr [0xb6a480]
00502e12 mov eax, dword ptr [0xbfd65c]
00502e17 push esi
00502e18 movss xmm0, dword ptr [edx]
00502e1c subss xmm0, xmm1
00502e20 push edi
00502e21 mov edi, dword ptr [eax + 0x18190]
00502e27 divss xmm0, xmm1
00502e2b addss xmm0, xmm2
00502e2f cvttss2si ecx, xmm0
00502e33 test ecx, ecx
00502e35 js 0x502e8b
00502e37 mov esi, dword ptr [edi + 0xc]
00502e3a cmp ecx, esi
00502e3c jge 0x502e8b
00502e3e movss xmm0, dword ptr [edx + 4]
00502e43 subss xmm0, dword ptr [0xb6ab20]
00502e4b divss xmm0, xmm1
00502e4f addss xmm0, xmm2
00502e53 cvttss2si eax, xmm0
00502e57 test eax, eax
00502e59 js 0x502e8b
00502e5b cmp eax, dword ptr [edi + 0x10]
00502e5e jge 0x502e8b
00502e60 imul esi, eax
00502e63 add esi, ecx
00502e65 mov ecx, edi
00502e67 push esi
00502e68 call 0x7aeec0
00502e6d cmp esi, 0x1bf
00502e73 ja 0x502e94
00502e75 cmp dword ptr [edi + esi*4 + 0x76c], 0x3b6
00502e80 mov ecx, 3
00502e85 pop edi
00502e86 cmove eax, ecx
00502e89 pop esi
00502e8a ret 
00502e8b push -1
00502e8d mov ecx, edi
00502e8f call 0x7aeec0
00502e94 pop edi
00502e95 pop esi
00502e96 ret 
