; Repentance 1.7.9b bounded evidence. Interpretive names are not exported symbols.
006a3420 push ebp
006a3421 mov ebp, esp
006a3423 and esp, 0xfffffff8
006a3426 sub esp, 0x2c
006a3429 movss xmm0, dword ptr [0xb6a614] ; f32=1
006a3431 xor eax, eax
006a3433 push ebx
006a3434 mov ebx, ecx
006a3436 movss dword ptr [esp + 0x10], xmm0
006a343c push esi
006a343d push edi
006a343e mov edx, dword ptr [ebx + 0x164]
006a3444 and edx, 0x400000
006a344a or eax, edx
006a344c je 0x6a345c
006a344e movss xmm0, dword ptr [0xb6a560] ; f32=0.800000012
006a3456 movss dword ptr [esp + 0x18], xmm0
006a345c cmp dword ptr [ebp + 8], 0
006a3460 jle 0x6a395a
006a3466 movss xmm0, dword ptr [ebp + 0x10]
006a346b mulss xmm0, dword ptr [0xb6a2cc] ; f32=0.100000001
006a3473 mov esi, dword ptr [ebp + 0x14]
006a3476 movss xmm2, dword ptr [0xb6a19c] ; f32=2.32830644e-10
