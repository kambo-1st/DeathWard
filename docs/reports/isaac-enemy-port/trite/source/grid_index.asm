007ce950 push ebp
007ce951 mov ebp, esp
007ce953 movss xmm1, dword ptr [0xb6aa3c]
007ce95b push esi
007ce95c mov esi, ecx
007ce95e movss xmm2, dword ptr [0xb6a480]
007ce966 mov ecx, dword ptr [ebp + 8]
007ce969 movss xmm0, dword ptr [ecx]
007ce96d subss xmm0, xmm1
007ce971 divss xmm0, xmm1
007ce975 addss xmm0, xmm2
007ce979 cvttss2si edx, xmm0
007ce97d test edx, edx
007ce97f js 0x7ce9b4
007ce981 mov eax, dword ptr [esi + 0xc]
007ce984 cmp edx, eax
007ce986 jge 0x7ce9b4
007ce988 movss xmm0, dword ptr [ecx + 4]
007ce98d subss xmm0, dword ptr [0xb6ab20]
007ce995 divss xmm0, xmm1
007ce999 addss xmm0, xmm2
007ce99d cvttss2si ecx, xmm0
007ce9a1 test ecx, ecx
007ce9a3 js 0x7ce9b4
007ce9a5 cmp ecx, dword ptr [esi + 0x10]
007ce9a8 jge 0x7ce9b4
007ce9aa imul eax, ecx
007ce9ad pop esi
007ce9ae add eax, edx
007ce9b0 pop ebp
007ce9b1 ret 4
007ce9b4 or eax, 0xffffffff
007ce9b7 pop esi
007ce9b8 pop ebp
007ce9b9 ret 4
