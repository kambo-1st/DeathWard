; Repentance1.7.9b bounded native evidence; names are interpretive.
004a65d0 movss xmm0, dword ptr [edi + 0x14]
004a65d5 xorps xmm1, xmm1
004a65d8 comiss xmm0, xmm1
004a65db jbe 0x4a79e8
004a65e1 mov eax, dword ptr [edi + 0x18]
004a65e4 and eax, 4
004a65e7 or eax, 0
004a65ea je 0x4a6602
004a65ec mov dword ptr [edi + 0x2d8], 0x3f800000
004a65f6 mov byte ptr [edi + 0x16b], 1
004a65fd jmp 0x4a79e8
004a6602 mov esi, dword ptr [edi + 8]
004a6605 cmp esi, dword ptr [edi + 0xc]
004a6608 je 0x4a6692
004a660e movss xmm3, dword ptr [0xb6a7b0]
004a6616 movss xmm4, dword ptr [0xb6a864]
004a661e movss xmm5, dword ptr [0xb6a974]
004a6626 movss xmm0, dword ptr [esi]
004a662a comiss xmm5, xmm0
004a662d jb 0x4a665a
004a662f comiss xmm0, xmm1
004a6632 jbe 0x4a6650
004a6634 call 0x6c3d90
004a6639 xor edx, edx
004a663b mov ecx, 3
004a6640 div ecx
004a6642 test edx, edx
004a6644 je 0x4a666c
004a6646 movss xmm0, dword ptr [0xb6a614]
004a664e jmp 0x4a6674
004a6650 movss xmm2, dword ptr [edi + 0x2d8]
004a6658 jmp 0x4a6688
004a665a call 0x6c3d90
004a665f xor edx, edx
004a6661 mov ecx, 3
004a6666 div ecx
004a6668 test edx, edx
004a666a je 0x4a6671
004a666c movaps xmm0, xmm3
004a666f jmp 0x4a6674
004a6671 movaps xmm0, xmm4
004a6674 movss xmm2, dword ptr [edi + 0x2d8]
004a667c subss xmm2, xmm0
004a6680 movss dword ptr [edi + 0x2d8], xmm2
004a6688 add esi, 0x38
004a668b cmp esi, dword ptr [edi + 0xc]
004a668e jne 0x4a6626
004a6690 jmp 0x4a669a
004a6692 movss xmm2, dword ptr [edi + 0x2d8]
004a669a movss xmm0, dword ptr [0xb6a614]
004a66a2 comiss xmm0, xmm2
004a66a5 jbe 0x4a66bd
004a66a7 mov dword ptr [edi + 0x2d8], 0x3f800000
004a66b1 mov byte ptr [edi + 0x16b], 1
004a66b8 jmp 0x4a79e8
004a66bd movss xmm0, dword ptr [0xb6a6f0]
004a66c5 comiss xmm0, xmm2
004a66c8 jbe 0x4a79e8
004a66ce mov byte ptr [edi + 0x16b], 1
004a66d5 jmp 0x4a79e8
