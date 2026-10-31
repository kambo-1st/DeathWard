004c5b50 push ebp
004c5b51 mov ebp, esp
004c5b53 sub esp, 8
004c5b56 push esi
004c5b57 push edi
004c5b58 mov edi, edx
004c5b5a mov esi, ecx
004c5b5c call 0x6c3d90
004c5b61 movd xmm0, eax
004c5b65 cvtdq2pd xmm0, xmm0
004c5b69 shr eax, 0x1f
004c5b6c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c5b75 cvtpd2ps xmm0, xmm0
004c5b79 mulss xmm0, dword ptr [0xb6a19c]
004c5b81 subss xmm0, dword ptr [0xb6a480]
004c5b89 mulss xmm0, dword ptr [0xb6aae4]
004c5b91 mulss xmm0, dword ptr [0xb6a230]
004c5b99 movss dword ptr [ebp - 4], xmm0
004c5b9e call 0x411fe0
004c5ba3 movss dword ptr [esi], xmm0
004c5ba7 movss xmm0, dword ptr [ebp - 4]
004c5bac call 0x412010
004c5bb1 movss dword ptr [esi + 4], xmm0
004c5bb6 call 0x6c3d90
004c5bbb movss xmm4, dword ptr [0xb6ae44]
004c5bc3 test al, 1
004c5bc5 jne 0x4c5bd3
004c5bc7 movss xmm0, dword ptr [esi]
004c5bcb mulss xmm0, xmm4
004c5bcf movss dword ptr [esi], xmm0
004c5bd3 call 0x6c3d90
004c5bd8 test al, 1
004c5bda jne 0x4c5c0e
004c5bdc movss xmm0, dword ptr [esi + 4]
004c5be1 xorps xmm3, xmm3
004c5be4 comiss xmm3, xmm0
004c5be7 movss xmm1, dword ptr [edi + 0x298]
004c5bef movss xmm2, dword ptr [ebp + 0xc]
004c5bf4 jbe 0x4c5bfb
004c5bf6 comiss xmm1, xmm2
004c5bf9 ja 0x4c5c05
004c5bfb comiss xmm0, xmm3
004c5bfe jbe 0x4c5c0e
004c5c00 comiss xmm2, xmm1
004c5c03 jbe 0x4c5c0e
004c5c05 mulss xmm0, xmm4
004c5c09 movss dword ptr [esi + 4], xmm0
004c5c0e pop edi
004c5c0f mov eax, esi
004c5c11 pop esi
004c5c12 mov esp, ebp
004c5c14 pop ebp
004c5c15 ret 
