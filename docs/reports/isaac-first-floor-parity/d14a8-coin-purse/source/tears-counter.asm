0072f8d8 lea edi, [eax + 0x15fc]
0072f8de push 0x10
0072f8e0 mov ecx, edi
0072f8e2 call 0x430970
0072f8e7 push 0xf
0072f8e9 mov ecx, edi
0072f8eb mov esi, dword ptr [eax]
0072f8ed call 0x430970
0072f8f2 movd xmm1, esi
0072f8f6 cvtdq2ps xmm1, xmm1
0072f8f9 movd xmm0, dword ptr [eax]
0072f8fd mulss xmm1, dword ptr [0xb6a480]
0072f905 mov eax, dword ptr [ebp - 0x428]
0072f90b cvtdq2ps xmm0, xmm0
0072f90e mulss xmm0, dword ptr [0xb6a434]
0072f916 subss xmm1, xmm0
0072f91a movss dword ptr [ebp - 0x438], xmm1
