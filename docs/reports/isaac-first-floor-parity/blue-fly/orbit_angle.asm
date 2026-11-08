005f50aa mov eax, dword ptr [0xbfd680]
005f50af mov eax, dword ptr [eax + 0x4a264]
005f50b5 and eax, 0x80000001
005f50ba jns 0x5f50c1
005f50bc dec eax
005f50bd or eax, 0xfffffffe
005f50c0 inc eax
005f50c1 xorps xmm2, xmm2
005f50c4 movss xmm1, dword ptr [0xb6a914]
005f50cc cvtsi2ss xmm2, eax
005f50d0 xorps xmm0, xmm0
005f50d3 cvtsi2ss xmm0, dword ptr [ecx + 0x1a30dc]
005f50db mulss xmm2, dword ptr [0xb6a480]
005f50e3 addss xmm2, xmm0
005f50e7 movss xmm0, dword ptr [ebx + 0xcb0]
005f50ef mulss xmm2, dword ptr [ebx + 0xcbc]
005f50f7 mulss xmm2, dword ptr [0xb6a874]
005f50ff mulss xmm2, dword ptr [0xb6a480]
005f5107 subss xmm0, xmm2
