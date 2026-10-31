006593a0 movss xmm3, dword ptr [edx]
006593a4 mov eax, ecx
006593a6 movss xmm4, dword ptr [edx + 4]
006593ab movaps xmm2, xmm3
006593ae andps xmm2, xmmword ptr [0xb6c980]
006593b5 movaps xmm0, xmm4
006593b8 andps xmm0, xmmword ptr [0xb6c980]
006593bf comiss xmm2, xmm0
006593c2 xorps xmm0, xmm0
006593c5 jbe 0x6593e1
006593c7 comiss xmm0, xmm3
006593ca mov dword ptr [ecx + 4], 0
006593d1 jbe 0x6593da
006593d3 mov dword ptr [ecx], 0xbf800000
006593d9 ret 
006593da mov dword ptr [ecx], 0x3f800000
006593e0 ret 
006593e1 comiss xmm0, xmm4
006593e4 mov dword ptr [ecx], 0
006593ea jbe 0x6593f4
006593ec mov dword ptr [ecx + 4], 0xbf800000
006593f3 ret 
006593f4 mov dword ptr [ecx + 4], 0x3f800000
006593fb ret 
