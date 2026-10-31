007a6e20 movss xmm1, dword ptr [0xb6aa3c]
007a6e28 mov edx, ecx
007a6e2a push esi
007a6e2b push edi
007a6e2c mov eax, dword ptr [edx]
007a6e2e movss xmm2, dword ptr [eax + 0x294]
007a6e36 movss xmm3, dword ptr [eax + 0x298]
007a6e3e subss xmm2, xmm1
007a6e42 subss xmm3, dword ptr [0xb6ab20]
007a6e4a mov eax, dword ptr [0xbfd65c]
007a6e4f divss xmm2, xmm1
007a6e53 mov edi, dword ptr [eax + 0x18190]
007a6e59 divss xmm3, xmm1
007a6e5d addss xmm2, dword ptr [0xb6a480]
007a6e65 addss xmm3, dword ptr [0xb6a480]
007a6e6d cvttss2si esi, xmm2
007a6e71 cvttss2si ecx, xmm3
007a6e75 test esi, esi
007a6e77 js 0x7a6e94
007a6e79 mov eax, dword ptr [edi + 0xc]
007a6e7c cmp esi, eax
007a6e7e jge 0x7a6e94
007a6e80 test ecx, ecx
007a6e82 js 0x7a6e94
007a6e84 cmp ecx, dword ptr [edi + 0x10]
007a6e87 jge 0x7a6e94
007a6e89 imul eax, ecx
007a6e8c add eax, esi
007a6e8e mov dword ptr [edx + 0x20], eax
007a6e91 pop edi
007a6e92 pop esi
007a6e93 ret 
007a6e94 pop edi
007a6e95 mov dword ptr [edx + 0x20], 0xffffffff
007a6e9c pop esi
007a6e9d ret 
