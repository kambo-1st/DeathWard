00683650 push ebp
00683651 mov ebp, esp
00683653 sub esp, 0x20
00683656 mov eax, dword ptr [ecx + 0x17c]
0068365c mov dword ptr [ebp - 0x14], eax
0068365f push ebx
00683660 push esi
00683661 push edi
00683662 test eax, eax
00683664 je 0x68383d
0068366a mov esi, dword ptr [ecx + 0x170]
00683670 mov edx, dword ptr [ecx + 0x174]
00683676 mov dword ptr [ebp - 0x10], esi
00683679 cmp esi, edx
0068367b je 0x68383d
00683681 mov eax, dword ptr [0xbfd65c]
00683686 sub edx, esi
00683688 movss xmm1, dword ptr [0xc02ff0]
00683690 xor edi, edi
00683692 movss xmm2, dword ptr [0xc02fec]
0068369a movaps xmm0, xmm1
0068369d sar edx, 3
006836a0 mov ebx, dword ptr [eax + 0x18190]
006836a6 movss dword ptr [ebp - 0xc], xmm2
006836ab movss dword ptr [ebp - 4], xmm0
006836b0 mov dword ptr [ebp - 8], edx
006836b3 test edx, edx
006836b5 je 0x6837cd
006836bb mov eax, dword ptr [ebp + 8]
006836be movss xmm1, dword ptr [ecx + 0x294]
006836c6 movss xmm5, dword ptr [ecx + 0x298]
006836ce movss xmm3, dword ptr [0xb6aa3c]
006836d6 addss xmm1, dword ptr [eax]
006836da addss xmm5, dword ptr [eax + 4]
006836df movss xmm4, dword ptr [0xb6a480]
006836e7 mov eax, edx
006836e9 movss dword ptr [ebp - 0x20], xmm1
006836ee movss dword ptr [ebp + 8], xmm5
006836f3 nop dword ptr [eax]
006836f7 nop word ptr [eax + eax]
00683700 movss xmm0, dword ptr [esi + edi*8]
00683705 movss dword ptr [ebp - 0x18], xmm0
0068370a addss xmm0, xmm1
0068370e movss xmm1, dword ptr [esi + edi*8 + 4]
00683714 movss dword ptr [ebp - 0x1c], xmm1
00683719 addss xmm1, xmm5
0068371d subss xmm0, xmm3
00683721 divss xmm0, xmm3
00683725 addss xmm0, xmm4
00683729 cvttss2si edx, xmm0
0068372d test edx, edx
0068372f js 0x683833
00683735 mov eax, dword ptr [ebx + 0xc]
00683738 cmp edx, eax
0068373a jge 0x6837af
0068373c subss xmm1, dword ptr [0xb6ab20]
00683744 divss xmm1, xmm3
00683748 addss xmm1, xmm4
0068374c cvttss2si ecx, xmm1
00683750 test ecx, ecx
00683752 js 0x6837af
00683754 cmp ecx, dword ptr [ebx + 0x10]
00683757 jge 0x6837af
00683759 imul eax, ecx
0068375c add eax, edx
0068375e js 0x6837af
00683760 cmp eax, 0x1c0
00683765 jge 0x68376d
00683767 mov esi, dword ptr [ebx + eax*4 + 0x24]
0068376b jmp 0x68376f
0068376d xor esi, esi
0068376f push eax
00683770 mov ecx, ebx
00683772 call 0x7aeec0
00683777 mov ecx, dword ptr [ebp - 0x14]
0068377a cmp ecx, 3
0068377d jne 0x6837ee
0068377f cmp eax, 4
00683782 je 0x6837fb
00683784 cmp eax, ecx
00683786 jne 0x683792
00683788 test esi, esi
0068378a je 0x683792
0068378c cmp dword ptr [esi + 4], 0x10
00683790 je 0x6837fb
00683792 mov esi, dword ptr [ebp - 0x10]
00683795 movss xmm5, dword ptr [ebp + 8]
0068379a movss xmm4, dword ptr [0xb6a480]
006837a2 movss xmm3, dword ptr [0xb6aa3c]
006837aa movss xmm2, dword ptr [ebp - 0xc]
006837af movss xmm0, dword ptr [ebp - 4]
006837b4 mov eax, dword ptr [ebp - 8]
006837b7 movss xmm1, dword ptr [ebp - 0x20]
006837bc inc edi
006837bd cmp edi, eax
006837bf jb 0x683700
006837c5 movss xmm1, dword ptr [0xc02ff0]
006837cd ucomiss xmm2, dword ptr [0xc02fec]
006837d4 lahf 
006837d5 test ah, 0x44
006837d8 jp 0x6837e3
006837da ucomiss xmm0, xmm1
006837dd lahf 
006837de test ah, 0x44
006837e1 jnp 0x68383d
006837e3 mov al, 1
006837e5 pop edi
006837e6 pop esi
006837e7 pop ebx
006837e8 mov esp, ebp
006837ea pop ebp
006837eb ret 4
006837ee cmp ecx, 5
006837f1 jne 0x683792
006837f3 test eax, eax
006837f5 je 0x683792
006837f7 cmp eax, ecx
006837f9 je 0x683792
006837fb movss xmm2, dword ptr [ebp - 0x18]
00683800 movss xmm0, dword ptr [ebp - 0x1c]
00683805 addss xmm2, dword ptr [ebp - 0xc]
0068380a addss xmm0, dword ptr [ebp - 4]
0068380f movss xmm3, dword ptr [0xb6aa3c]
00683817 movss xmm4, dword ptr [0xb6a480]
0068381f movss xmm5, dword ptr [ebp + 8]
00683824 mov esi, dword ptr [ebp - 0x10]
00683827 movss dword ptr [ebp - 0xc], xmm2
0068382c movss dword ptr [ebp - 4], xmm0
00683831 jmp 0x6837b4
00683833 movss xmm0, dword ptr [ebp - 4]
00683838 jmp 0x6837b7
0068383d pop edi
0068383e pop esi
0068383f xor al, al
00683841 pop ebx
00683842 mov esp, ebp
00683844 pop ebp
00683845 ret 4
00683848 int3 
00683849 int3 
0068384a int3 
0068384b int3 
0068384c int3 
