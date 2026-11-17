0072fbcd push 0
0072fbcf push 0xff
0072fbd4 mov ecx, edi
0072fbd6 add esi, eax
0072fbd8 call 0x73b3b0
0072fbdd push 0
0072fbdf push 0x73
0072fbe1 mov ecx, edi
0072fbe3 add esi, eax
0072fbe5 call 0x73b3b0
0072fbea add esi, eax
0072fbec push 0
0072fbee push 0x48
0072fbf0 mov ecx, edi
0072fbf2 call 0x73b3b0
0072fbf7 add eax, esi
0072fbf9 mov ecx, edi
0072fbfb push 0
0072fbfd push 0xc4
0072fc02 movd xmm0, eax
0072fc06 cvtdq2ps xmm0, xmm0
0072fc09 mulss xmm0, dword ptr [0xb6a480]
0072fc11 addss xmm0, dword ptr [ebp - 0x42c]
0072fc19 movss dword ptr [ebp - 0x42c], xmm0
