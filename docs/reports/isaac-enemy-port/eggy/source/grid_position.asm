007cebc0 push ebp
007cebc1 mov ebp, esp
007cebc3 mov eax, dword ptr [ebp + 0xc]
007cebc6 cdq 
007cebc7 idiv dword ptr [ecx + 0xc]
007cebca movss xmm1, dword ptr [0xb6aa3c]
007cebd2 mov ecx, eax
007cebd4 mov eax, dword ptr [ebp + 8]
007cebd7 movd xmm0, edx
007cebdb cvtdq2ps xmm0, xmm0
007cebde mulss xmm0, xmm1
007cebe2 addss xmm0, xmm1
007cebe6 movss dword ptr [eax], xmm0
007cebea movd xmm0, ecx
007cebee cvtdq2ps xmm0, xmm0
007cebf1 mulss xmm0, xmm1
007cebf5 addss xmm0, dword ptr [0xb6ab20]
007cebfd movss dword ptr [eax + 4], xmm0
007cec02 pop ebp
007cec03 ret 8
