007a4570 cmp byte ptr [ebx + 0x72d], 0
007a4577 je 0x7a46b7
007a457d mov eax, dword ptr [0xbfd65c]
007a4582 mov edi, dword ptr [eax + 0x18190]
007a4588 mov eax, dword ptr [ebx + 0x20]
007a458b mov dword ptr [ebp - 0x3c], eax
007a458e cdq
007a458f mov esi, dword ptr [edi + 0xc]
007a4592 idiv esi
007a4594 mov dword ptr [ebp - 0x60], esi
007a4597 mov ecx, eax
007a4599 lea ebx, [edx - 1]
007a459c test ebx, ebx
007a459e js 0x7a45ba
007a45a0 cmp ebx, esi
007a45a2 jge 0x7a45ba
007a45a4 test ecx, ecx
007a45a6 js 0x7a45ba
007a45a8 cmp ecx, dword ptr [edi + 0x10]
007a45ab jge 0x7a45ba
007a45ad imul eax, esi
007a45b0 lea esi, [ecx - 1]
007a45b3 add eax, ebx
007a45b5 mov dword ptr [ebp - 0x20], eax
007a45b8 jmp 0x7a45c8
007a45ba mov dword ptr [ebp - 0x20], 0xffffffff
007a45c1 lea esi, [ecx - 1]
007a45c4 test edx, edx
007a45c6 js 0x7a45df
007a45c8 mov eax, dword ptr [edi + 0xc]
007a45cb cmp edx, eax
007a45cd jge 0x7a45e2
007a45cf test esi, esi
007a45d1 js 0x7a45e2
007a45d3 cmp esi, dword ptr [edi + 0x10]
007a45d6 jge 0x7a45e2
007a45d8 imul esi, eax
007a45db add esi, edx
007a45dd jmp 0x7a45e5
007a45df mov eax, dword ptr [edi + 0xc]
007a45e2 or esi, 0xffffffff
007a45e5 lea ebx, [edx + 1]
007a45e8 mov dword ptr [ebp - 0x1c], esi
007a45eb mov dword ptr [ebp - 0x30], ebx
007a45ee test ebx, ebx
007a45f0 mov ebx, dword ptr [ebp - 0x58]
007a45f3 js 0x7a460e
007a45f5 cmp dword ptr [ebp - 0x30], eax
007a45f8 jge 0x7a460e
007a45fa test ecx, ecx
007a45fc js 0x7a460e
007a45fe cmp ecx, dword ptr [edi + 0x10]
007a4601 jge 0x7a460e
007a4603 mov eax, ecx
007a4605 imul eax, dword ptr [edi + 0xc]
007a4609 add eax, dword ptr [ebp - 0x30]
007a460c jmp 0x7a4611
007a460e or eax, 0xffffffff
007a4611 inc ecx
007a4612 mov dword ptr [ebp - 0x18], eax
007a4615 test edx, edx
007a4617 js 0x7a4630
007a4619 mov eax, dword ptr [edi + 0xc]
007a461c cmp edx, eax
007a461e jge 0x7a4630
007a4620 test ecx, ecx
007a4622 js 0x7a4630
007a4624 cmp ecx, dword ptr [edi + 0x10]
007a4627 jge 0x7a4630
007a4629 imul ecx, eax
007a462c add ecx, edx
007a462e jmp 0x7a4633
007a4630 or ecx, 0xffffffff
007a4633 mov dword ptr [ebp - 0x14], ecx
007a4636 xor ecx, ecx
007a4638 mov dword ptr [ebp - 0x30], 0xfffffc18
007a463f nop
007a4640 cmp dword ptr [edi + 8], 0x10
007a4644 jne 0x7a4661
007a4646 cmp ecx, 1
007a4649 jne 0x7a4661
007a464b cmp esi, 0x1bf
007a4651 ja 0x7a4661
007a4653 mov eax, dword ptr [edi + esi*4 + 0x24]
007a4657 test eax, eax
007a4659 je 0x7a4661
007a465b cmp dword ptr [eax + 4], 0x13
007a465f je 0x7a467e
007a4661 mov eax, dword ptr [ebp + ecx*4 - 0x20]
007a4665 test eax, eax
007a4667 js 0x7a467e
007a4669 mov edx, dword ptr [ebx + eax*4 + 0x2c]
007a466d test edx, edx
007a466f jns 0x7a467e
007a4671 cmp edx, dword ptr [ebp - 0x30]
007a4674 jle 0x7a467e
007a4676 mov dword ptr [ebp - 0x3c], eax
007a4679 mov dword ptr [ebp - 0x30], edx
007a467c jmp 0x7a4681
007a467e mov eax, dword ptr [ebp - 0x3c]
007a4681 inc ecx
007a4682 cmp ecx, 4
007a4685 jb 0x7a4640
007a4687 cdq
007a4688 idiv dword ptr [ebp - 0x60]
007a468b movss xmm0, dword ptr [0xb6aa3c]
007a4693 movd xmm2, edx
007a4697 movd xmm1, eax
007a469b cvtdq2ps xmm2, xmm2
007a469e cvtdq2ps xmm1, xmm1
007a46a1 mulss xmm2, xmm0
007a46a5 mulss xmm1, xmm0
007a46a9 addss xmm2, xmm0
007a46ad addss xmm1, dword ptr [0xb6ab20]
007a46b5 jmp 0x7a46c1
007a46b7 movss xmm2, dword ptr [ebp - 0x54]
007a46bc movss xmm1, dword ptr [ebp - 0x68]
007a46c1 ucomiss xmm2, dword ptr [0xc02fec]
007a46c8 lahf
007a46c9 test ah, 0x44
007a46cc jp 0x7a46fa
007a46ce ucomiss xmm1, dword ptr [0xc02ff0]
007a46d5 lahf
007a46d6 test ah, 0x44
007a46d9 jp 0x7a46fa
007a46db mov eax, dword ptr [ebx]
007a46dd movss xmm0, dword ptr [eax + 0x2c4]
007a46e5 mulss xmm0, dword ptr [0xb6a588]
007a46ed movss dword ptr [eax + 0x2c4], xmm0
007a46f5 jmp 0x7a47f5
007a46fa subss xmm1, dword ptr [ebp - 0x74]
007a46ff subss xmm2, dword ptr [ebp - 0x78]
007a4704 mov esi, dword ptr [ebx]
007a4706 movaps xmm0, xmm1
007a4709 movss dword ptr [ebp - 0x68], xmm1
007a470e mulss xmm0, xmm1
007a4712 movaps xmm1, xmm2
007a4715 mulss xmm1, xmm2
007a4719 movss dword ptr [ebp - 0x54], xmm2
007a471e addss xmm0, xmm1
007a4722 call 0x4228c0
007a4727 movaps xmm2, xmm0
007a472a comiss xmm2, dword ptr [0xb6a614]
007a4731 jbe 0x7a47dd
007a4737 movss xmm0, dword ptr [ebp - 0x50]
007a473c movaps xmm1, xmm2
007a473f mulss xmm1, dword ptr [0xb6a2cc]
007a4747 mulss xmm0, dword ptr [ebp + 0xc]
007a474c movss xmm3, dword ptr [ebp - 0x54]
007a4751 movss xmm4, dword ptr [ebp - 0x68]
007a4756 minss xmm1, dword ptr [0xb6a7b0]
007a475e divss xmm3, xmm2
007a4762 divss xmm4, xmm2
007a4766 mulss xmm1, xmm0
007a476a movss xmm0, dword ptr [esi + 0x2c4]
007a4772 mulss xmm0, dword ptr [0xb6a50c]
007a477a mulss xmm3, xmm1
007a477e movss dword ptr [esi + 0x2c4], xmm0
007a4786 xorps xmm0, xmm0
007a4789 mov ecx, dword ptr [ebx]
007a478b mulss xmm4, xmm1
007a478f movss xmm2, dword ptr [ecx + 0x2c4]
007a4797 ucomiss xmm2, xmm0
007a479a lahf
007a479b test ah, 0x44
007a479e jnp 0x7a47f5
007a47a0 movss xmm1, dword ptr [ecx + 0x2f4]
007a47a8 movaps xmm0, xmm1
007a47ab mulss xmm1, xmm4
007a47af mulss xmm0, xmm3
007a47b3 divss xmm1, xmm2
007a47b7 divss xmm0, xmm2
007a47bb addss xmm1, dword ptr [ecx + 0x2bc]
007a47c3 addss xmm0, dword ptr [ecx + 0x2b8]
007a47cb movss dword ptr [ecx + 0x2bc], xmm1
007a47d3 movss dword ptr [ecx + 0x2b8], xmm0
007a47db jmp 0x7a47f5
007a47dd movss xmm0, dword ptr [esi + 0x2c4]
007a47e5 mulss xmm0, dword ptr [0xb6a480]
007a47ed movss dword ptr [esi + 0x2c4], xmm0
