008cc300 push ebx
008cc301 mov ebx, esp
008cc303 sub esp, 8
008cc306 and esp, 0xfffffff8
008cc309 add esp, 4
008cc30c push ebp
008cc30d mov ebp, dword ptr [ebx + 4]
008cc310 mov dword ptr [esp + 4], ebp
008cc314 mov ebp, esp
008cc316 push -1
008cc318 push 0x9ff7f8
008cc31d mov eax, dword ptr fs:[0]
008cc323 push eax
008cc324 push ebx
008cc325 sub esp, 0x348
008cc32b mov eax, dword ptr [0xbaa3b4]
008cc330 xor eax, ebp
008cc332 mov dword ptr [ebp - 0x14], eax
008cc335 push esi
008cc336 push edi
008cc337 push eax
008cc338 lea eax, [ebp - 0xc]
008cc33b mov dword ptr fs:[0], eax
008cc341 mov edi, ecx
008cc343 mov dword ptr [ebp - 0xb8], edi
008cc349 call 0x8cc120
008cc34e mov al, byte ptr [edi + 0x3ac]
008cc354 test al, al
008cc356 jne 0x8cc360
008cc358 cmp byte ptr [edi + 0x465], al
008cc35e jne 0x8cc36e
008cc360 movups xmm0, xmmword ptr [edi + 0x378]
008cc367 movups xmmword ptr [edi + 0x388], xmm0
008cc36e cmp dword ptr [edi + 0x2c], 7
008cc372 movss xmm1, dword ptr [0xb6a7b0]
008cc37a movss dword ptr [ebp - 0xc8], xmm1
008cc382 je 0x8cc3cf
008cc384 cmp byte ptr [edi + 0x16d], 0
008cc38b jne 0x8cc3cf
008cc38d cmp byte ptr [edi + 0x16b], 0
008cc394 jne 0x8cc3cf
008cc396 test al, al
008cc398 jne 0x8cc3a8
008cc39a xorps xmm2, xmm2
008cc39d mov ecx, edi
008cc39f call 0x6847e0
008cc3a4 test eax, eax
008cc3a6 je 0x8cc3cf
008cc3a8 cmp dword ptr [edi + 0x47c], 0
008cc3af mov byte ptr [ebp - 0xa6], 1
008cc3b6 jne 0x8cc3d6
008cc3b8 cmp byte ptr [edi + 0x465], 0
008cc3bf jne 0x8cc3d6
008cc3c1 mov eax, dword ptr [edi + 0x470]
008cc3c7 mov dword ptr [edi + 0x474], eax
008cc3cd jmp 0x8cc3d6
008cc3cf mov byte ptr [ebp - 0xa6], 0
008cc3d6 mov eax, dword ptr [edi + 0x314]
008cc3dc test eax, eax
008cc3de je 0x8cc447
008cc3e0 cmp byte ptr [edi + 0x434], 0
008cc3e7 jne 0x8cc447
008cc3e9 cmp dword ptr [eax + 0x28], 1
008cc3ed movss xmm0, dword ptr [eax + 0x294]
008cc3f5 movss xmm1, dword ptr [eax + 0x298]
008cc3fd jne 0x8cc421
008cc3ff addss xmm0, dword ptr [edi + 0x360]
008cc407 addss xmm1, dword ptr [edi + 0x364]
008cc40f addss xmm0, dword ptr [eax + 0x1580]
008cc417 addss xmm1, dword ptr [eax + 0x1584]
008cc41f jmp 0x8cc437
008cc421 cmp dword ptr [edi + 0x34], 1
008cc425 je 0x8cc437
008cc427 addss xmm0, dword ptr [edi + 0x360]
008cc42f addss xmm1, dword ptr [edi + 0x364]
008cc437 movss dword ptr [edi + 0x298], xmm1
008cc43f movss dword ptr [edi + 0x294], xmm0
008cc447 xor al, al
008cc449 mov byte ptr [ebp - 0xe1], 0
008cc450 mov byte ptr [ebp - 0xa5], al
008cc456 mov byte ptr [ebp - 0x9c], al
008cc45c mov dword ptr [ebp - 0xe8], eax
008cc462 mov byte ptr [ebp - 0xbc], al
008cc468 cmp byte ptr [edi + 0x16d], al
008cc46e jne 0x8cc4c3
008cc470 cmp dword ptr [edi + 0x3a8], 0
008cc477 je 0x8cc4c3
008cc479 mov edx, dword ptr [edi + 0x2c]
008cc47c cmp edx, 6
008cc47f je 0x8cc4b6
008cc481 cmp edx, 0xf
008cc484 je 0x8cc4b6
008cc486 cmp edx, 0xb
008cc489 je 0x8cc490
008cc48b cmp edx, 0xe
008cc48e jne 0x8cc4ad
008cc490 mov esi, dword ptr [0xbfd65c]
008cc496 mov eax, dword ptr [esi + 0x1a30dc]
008cc49c sub eax, dword ptr [edi + 0x280]
008cc4a2 cmp eax, 1
008cc4a5 jne 0x8cc4ad
008cc4a7 push 0xa
008cc4a9 mov ecx, esi
008cc4ab jmp 0x8cc4be
008cc4ad cmp edx, 0xd
008cc4b0 jne 0x8cc4c3
008cc4b2 push 0xa
008cc4b4 jmp 0x8cc4b8
008cc4b6 push 4
008cc4b8 mov ecx, dword ptr [0xbfd65c]
008cc4be call 0x6d5ad0
008cc4c3 cmp byte ptr [edi + 0x410], 0
008cc4ca movss xmm3, dword ptr [0xb6a480]
008cc4d2 movss xmm2, dword ptr [0xb6aae4]
008cc4da je 0x8cc5fa
008cc4e0 mov eax, dword ptr [edi + 0x414]
008cc4e6 test eax, eax
008cc4e8 jne 0x8cc5f3
008cc4ee movss xmm1, dword ptr [edi + 0x418]
008cc4f6 lea ecx, [edi + 0x418]
008cc4fc xorps xmm0, xmm0
008cc4ff comiss xmm0, xmm1
008cc502 seta al
008cc505 test al, al
008cc507 je 0x8cc580
008cc509 comiss xmm0, xmm1
008cc50c jbe 0x8cc56e
008cc50e movss xmm0, dword ptr [edi + 0x41c]
008cc516 lea eax, [ebp - 0xac]
008cc51c mulss xmm0, xmm3
008cc520 comiss xmm1, xmm0
008cc523 movss dword ptr [ebp - 0xac], xmm0
008cc52b cmova eax, ecx
008cc52e movss xmm0, dword ptr [eax]
008cc532 subss xmm1, xmm0
008cc536 addss xmm0, dword ptr [edi + 0x36c]
008cc53e movss dword ptr [ebp - 0xa0], xmm1
008cc546 movss dword ptr [edi + 0x36c], xmm0
008cc54e subss xmm0, xmm2
008cc552 movss dword ptr [ecx], xmm1
008cc556 call 0x65a640
008cc55b movss xmm1, dword ptr [ebp - 0xa0]
008cc563 movss dword ptr [edi + 0xe0], xmm0
008cc56b xorps xmm0, xmm0
008cc56e comiss xmm1, xmm0
008cc571 jb 0x8cc5fa
008cc577 mov byte ptr [edi + 0x410], 0
008cc57e jmp 0x8cc5fa
008cc580 comiss xmm1, xmm0
008cc583 jbe 0x8cc5e5
008cc585 movss xmm0, dword ptr [edi + 0x41c]
008cc58d lea eax, [ebp - 0xac]
008cc593 mulss xmm0, xmm3
008cc597 comiss xmm0, xmm1
008cc59a movss dword ptr [ebp - 0xac], xmm0
008cc5a2 cmova eax, ecx
008cc5a5 movss xmm0, dword ptr [eax]
008cc5a9 subss xmm1, xmm0
008cc5ad addss xmm0, dword ptr [edi + 0x36c]
008cc5b5 movss dword ptr [ebp - 0xa0], xmm1
008cc5bd movss dword ptr [edi + 0x36c], xmm0
008cc5c5 subss xmm0, xmm2
008cc5c9 movss dword ptr [ecx], xmm1
008cc5cd call 0x65a640
008cc5d2 movss xmm1, dword ptr [ebp - 0xa0]
008cc5da movss dword ptr [edi + 0xe0], xmm0
008cc5e2 xorps xmm0, xmm0
008cc5e5 comiss xmm0, xmm1
008cc5e8 jb 0x8cc5fa
008cc5ea mov byte ptr [edi + 0x410], 0
008cc5f1 jmp 0x8cc5fa
008cc5f3 dec eax
008cc5f4 mov dword ptr [edi + 0x414], eax
008cc5fa cmp byte ptr [edi + 0x3ad], 0
008cc601 movss xmm2, dword ptr [0xb6a230]
008cc609 je 0x8ced3f
008cc60f cmp dword ptr [edi + 0x424], 1
008cc616 je 0x8cc621
008cc618 cmp byte ptr [edi + 0x465], 0
008cc61f je 0x8cc636
008cc621 cmp byte ptr [edi + 0x3ac], 0
008cc628 jne 0x8cc636
008cc62a mov byte ptr [ebp - 0xe1], 0
008cc631 jmp 0x8cec06
008cc636 movss xmm1, dword ptr [edi + 0x36c]
008cc63e ucomiss xmm1, dword ptr [edi + 0x370]
008cc645 mov byte ptr [ebp - 0xe1], 1
008cc64c mov byte ptr [edi + 0x466], 0
008cc653 movaps xmm0, xmm1
008cc656 lahf 
008cc657 test ah, 0x44
008cc65a jnp 0x8cc6a5
008cc65c mov ecx, edi
008cc65e call 0x8c5940
008cc663 test al, al
008cc665 jne 0x8cc6a5
008cc667 cmp dword ptr [edi + 0x2c], 5
008cc66b je 0x8cc6a5
008cc66d mov eax, dword ptr [edi + 0x3fc]
008cc673 mov dword ptr [edi + 0x400], eax
008cc679 mov eax, dword ptr [edi + 0x3d0]
008cc67f mov dword ptr [edi + 0x3d4], eax
008cc685 mov eax, dword ptr [edi + 0x3e8]
008cc68b mov dword ptr [edi + 0x3ec], eax
008cc691 mov eax, dword ptr [edi + 0x3dc]
008cc697 mov dword ptr [edi + 0x3e0], eax
008cc69d movss xmm0, dword ptr [edi + 0x36c]
008cc6a5 mulss xmm0, xmm2
008cc6a9 movss dword ptr [ebp - 0x9c], xmm0
008cc6b1 call 0x412010
008cc6b6 movss dword ptr [ebp - 0xc4], xmm0
008cc6be movss xmm0, dword ptr [ebp - 0x9c]
008cc6c6 call 0x411fe0
008cc6cb cmp dword ptr [edi + 0xbc], 1
008cc6d2 movss xmm3, dword ptr [0xc02fec]
008cc6da movss xmm2, dword ptr [0xc02ff0]
008cc6e2 movss dword ptr [ebp - 0xd8], xmm0
008cc6ea movss xmm0, dword ptr [ebp - 0xc4]
008cc6f2 movss dword ptr [ebp - 0xd4], xmm0
008cc6fa movss dword ptr [ebp - 0xa0], xmm3
008cc702 movss dword ptr [ebp - 0xa4], xmm2
008cc70a jbe 0x8cc76c
008cc70c lea ecx, [edi + 0x6c]
008cc70f push 0
008cc711 call 0x4053a0
008cc716 test eax, eax
008cc718 je 0x8cc75c
008cc71a movss xmm1, dword ptr [eax + 0x14]
008cc71f addss xmm1, dword ptr [eax + 0xc]
008cc724 movss xmm2, dword ptr [edi + 0xdc]
008cc72c movaps xmm3, xmm2
008cc72f movaps xmm0, xmm1
008cc732 mulss xmm1, dword ptr [ebp - 0xc4]
008cc73a mulss xmm0, dword ptr [ebp - 0xd8]
008cc742 mulss xmm2, xmm1
008cc746 mulss xmm3, xmm0
008cc74a movss dword ptr [ebp - 0xa4], xmm2
008cc752 movss dword ptr [ebp - 0xa0], xmm3
008cc75a jmp 0x8cc76c
008cc75c movss xmm2, dword ptr [ebp - 0xa4]
008cc764 movss xmm3, dword ptr [ebp - 0xa0]
008cc76c mov esi, dword ptr [edi + 0x320]
008cc772 movaps xmm0, xmm3
008cc775 movaps xmm1, xmm2
008cc778 addss xmm0, dword ptr [edi + 0x294]
008cc780 addss xmm1, dword ptr [edi + 0x298]
008cc788 movss dword ptr [ebp - 0xb0], xmm0
008cc790 movss dword ptr [ebp - 0xb4], xmm1
008cc798 movss dword ptr [ebp - 0xf0], xmm0
008cc7a0 movss dword ptr [ebp - 0xec], xmm1
008cc7a8 test esi, esi
008cc7aa je 0x8cc7b2
008cc7ac cmp dword ptr [esi + 0x28], 1
008cc7b0 je 0x8cc7b4
008cc7b2 xor esi, esi
008cc7b4 lea eax, [ebp - 0xd8]
008cc7ba mov ecx, edi
008cc7bc push eax
008cc7bd lea eax, [ebp - 0xf0]
008cc7c3 push eax
008cc7c4 lea eax, [ebp - 0x118]
008cc7ca push eax
008cc7cb call 0x8c7e90
008cc7d0 movss xmm3, dword ptr [ebp - 0xb0]
008cc7d8 xorps xmm7, xmm7
008cc7db movss xmm4, dword ptr [ebp - 0xb4]
008cc7e3 movss xmm1, dword ptr [eax]
008cc7e7 movss dword ptr [edi + 0x428], xmm1
008cc7ef movss xmm0, dword ptr [eax + 4]
008cc7f4 movss dword ptr [edi + 0x42c], xmm0
008cc7fc movss xmm2, dword ptr [edi + 0x420]
008cc804 comiss xmm2, xmm7
008cc807 movss dword ptr [ebp - 0x9c], xmm2
008cc80f jbe 0x8cc8b7
008cc815 subss xmm0, xmm4
008cc819 subss xmm1, xmm3
008cc81d movaps xmm5, xmm0
008cc820 movss dword ptr [ebp - 0xfc], xmm0
008cc828 mulss xmm5, xmm0
008cc82c movaps xmm0, xmm1
008cc82f mulss xmm0, xmm1
008cc833 movss dword ptr [ebp - 0x10c], xmm1
008cc83b movaps xmm1, xmm2
008cc83e mulss xmm1, xmm2
008cc842 addss xmm5, xmm0
008cc846 comiss xmm5, xmm1
008cc849 jbe 0x8cc8b7
008cc84b movaps xmm0, xmm5
008cc84e call 0x4228c0
008cc853 movaps xmm1, xmm0
008cc856 xorps xmm7, xmm7
008cc859 comiss xmm1, xmm7
008cc85c jbe 0x8cc87f
008cc85e movss xmm0, dword ptr [ebp - 0x9c]
008cc866 divss xmm0, xmm1
008cc86a movaps xmm1, xmm0
008cc86d mulss xmm0, dword ptr [ebp - 0xfc]
008cc875 mulss xmm1, dword ptr [ebp - 0x10c]
008cc87d jmp 0x8cc88f
008cc87f movss xmm1, dword ptr [ebp - 0x10c]
008cc887 movss xmm0, dword ptr [ebp - 0xfc]
008cc88f movss xmm3, dword ptr [ebp - 0xb0]
008cc897 movss xmm4, dword ptr [ebp - 0xb4]
008cc89f addss xmm1, xmm3
008cc8a3 addss xmm0, xmm4
008cc8a7 movss dword ptr [edi + 0x428], xmm1
008cc8af movss dword ptr [edi + 0x42c], xmm0
008cc8b7 mov eax, dword ptr [edi + 0x3fc]
008cc8bd mov dword ptr [edi + 0x400], eax
008cc8c3 mov eax, dword ptr [edi + 0x2c]
008cc8c6 cmp eax, 6
008cc8c9 je 0x8cc8d4
008cc8cb cmp eax, 0xf
008cc8ce jne 0x8cc9cd
008cc8d4 cmp dword ptr [edi + 0x34], 1
008cc8d8 jne 0x8cc9cd
008cc8de movss xmm2, dword ptr [edi + 0x428]
008cc8e6 movss xmm1, dword ptr [edi + 0x42c]
008cc8ee subss xmm2, xmm3
008cc8f2 movss xmm5, dword ptr [ebp - 0xd8]
008cc8fa subss xmm1, xmm4
008cc8fe movss xmm6, dword ptr [ebp - 0xc4]
008cc906 mulss xmm5, dword ptr [0xb6aa60]
008cc90e mulss xmm6, dword ptr [0xb6aa60]
008cc916 movss xmm3, dword ptr [ebp - 0xa4]
008cc91e subss xmm2, xmm5
008cc922 movss xmm4, dword ptr [ebp - 0xa0]
008cc92a movaps xmm0, xmm3
008cc92d subss xmm1, xmm6
008cc931 mulss xmm2, xmm4
008cc935 mulss xmm0, xmm1
008cc939 addss xmm2, xmm0
008cc93d comiss xmm7, xmm2
008cc940 jbe 0x8cca09
008cc946 movaps xmm0, xmm3
008cc949 movaps xmm1, xmm4
008cc94c mulss xmm0, xmm3
008cc950 mulss xmm1, xmm4
008cc954 addss xmm0, xmm1
008cc958 call 0x4228c0
008cc95d comiss xmm0, dword ptr [0xb6a18c]
008cc964 movss xmm4, dword ptr [ebp - 0xa0]
008cc96c movss xmm3, dword ptr [ebp - 0xa4]
008cc974 jbe 0x8cc98f
008cc976 movss xmm2, dword ptr [0xb6a2cc]
008cc97e divss xmm2, xmm0
008cc982 movaps xmm7, xmm2
008cc985 mulss xmm2, xmm3
008cc989 mulss xmm7, xmm4
008cc98d jmp 0x8cc995
008cc98f movaps xmm7, xmm4
008cc992 movaps xmm2, xmm3
008cc995 movss xmm5, dword ptr [ebp - 0xb0]
008cc99d movaps xmm0, xmm4
008cc9a0 movss xmm6, dword ptr [ebp - 0xb4]
008cc9a8 addss xmm0, xmm5
008cc9ac movaps xmm1, xmm3
008cc9af addss xmm1, xmm6
008cc9b3 addss xmm7, xmm0
008cc9b7 addss xmm2, xmm1
008cc9bb movss dword ptr [edi + 0x428], xmm7
008cc9c3 movss dword ptr [edi + 0x42c], xmm2
008cc9cb jmp 0x8cca19
008cc9cd movss xmm1, dword ptr [edi + 0x428]
008cc9d5 movss xmm0, dword ptr [edi + 0x42c]
008cc9dd subss xmm1, xmm3
008cc9e1 movss xmm3, dword ptr [ebp - 0xa4]
008cc9e9 subss xmm0, xmm4
008cc9ed movss xmm4, dword ptr [ebp - 0xa0]
008cc9f5 mulss xmm1, xmm4
008cc9f9 mulss xmm0, xmm3
008cc9fd addss xmm0, xmm1
008cca01 comiss xmm7, xmm0
008cca04 jmp 0x8cc940
008cca09 movss xmm6, dword ptr [ebp - 0xb4]
008cca11 movss xmm5, dword ptr [ebp - 0xb0]
008cca19 addss xmm4, xmm5
008cca1d addss xmm3, xmm6
008cca21 lea edx, [edi + 0x378]
008cca27 push 0xbc4bf0
008cca2c lea ecx, [ebp - 0x130]
008cca32 movss dword ptr [edi + 0x3b8], xmm4
008cca3a movss dword ptr [edi + 0x3bc], xmm3
008cca42 mov eax, dword ptr [edi + 0x428]
008cca48 mov dword ptr [edi + 0x3c0], eax
008cca4e mov eax, dword ptr [edi + 0x42c]
008cca54 mov dword ptr [edi + 0x3c4], eax
008cca5a call 0x412050
008cca5f movss xmm0, dword ptr [0xb6aa8c]
008cca67 add esp, 4
008cca6a mov ecx, dword ptr [eax]
008cca6c or ecx, dword ptr [eax + 4]
008cca6f jne 0x8cca79
008cca71 mov ecx, dword ptr [eax + 8]
008cca74 or ecx, dword ptr [eax + 0xc]
008cca77 je 0x8cca8f
008cca79 movaps xmm1, xmm0
008cca7c lea ecx, [edi + 0x3b4]
008cca82 call 0x8f7860
008cca87 movss xmm0, dword ptr [0xb6aa8c]
008cca8f push 0xbc4920
008cca94 lea edx, [edi + 0x378]
008cca9a lea ecx, [ebp - 0x130]
008ccaa0 call 0x412050
008ccaa5 movss xmm2, dword ptr [0xb6ab20]
008ccaad add esp, 4
008ccab0 mov ecx, dword ptr [eax]
008ccab2 or ecx, dword ptr [eax + 4]
008ccab5 jne 0x8ccabf
008ccab7 mov ecx, dword ptr [eax + 8]
008ccaba or ecx, dword ptr [eax + 0xc]
008ccabd je 0x8ccb17
008ccabf movaps xmm1, xmm2
008ccac2 test esi, esi
008ccac4 je 0x8ccae0
008ccac6 cmp dword ptr [esi + 0x28], 1
008ccaca jne 0x8ccae0
008ccacc movss xmm1, dword ptr [esi + 0x13ac]
008ccad4 divss xmm1, dword ptr [0xb6a70c]
008ccadc mulss xmm1, xmm2
008ccae0 movss xmm3, dword ptr [edi + 0x420]
008ccae8 movaps xmm2, xmm0
008ccaeb push ecx
008ccaec lea ecx, [edi + 0x3b4]
008ccaf2 call 0x8f7cd0
008ccaf7 mov ecx, dword ptr [edi + 0x400]
008ccafd cmp dword ptr [edi + 0x3fc], ecx
008ccb03 je 0x8ccb17
008ccb05 mov eax, dword ptr [ecx - 0x18]
008ccb08 mov dword ptr [edi + 0x428], eax
008ccb0e mov eax, dword ptr [ecx - 0x14]
008ccb11 mov dword ptr [edi + 0x42c], eax
008ccb17 push 0xbc4860
008ccb1c lea edx, [edi + 0x378]
008ccb22 lea ecx, [ebp - 0x130]
008ccb28 call 0x412050
008ccb2d add esp, 4
008ccb30 mov ecx, dword ptr [eax]
008ccb32 or ecx, dword ptr [eax + 4]
008ccb35 jne 0x8ccb3f
008ccb37 mov ecx, dword ptr [eax + 8]
008ccb3a or ecx, dword ptr [eax + 0xc]
008ccb3d je 0x8ccb6b
008ccb3f push ecx
008ccb40 lea ecx, [edi + 0x3b4]
008ccb46 call 0x8f7100
008ccb4b mov ecx, dword ptr [edi + 0x400]
008ccb51 cmp dword ptr [edi + 0x3fc], ecx
008ccb57 je 0x8ccb6b
008ccb59 mov eax, dword ptr [ecx - 0x18]
008ccb5c mov dword ptr [edi + 0x428], eax
008ccb62 mov eax, dword ptr [ecx - 0x14]
008ccb65 mov dword ptr [edi + 0x42c], eax
008ccb6b push 0xbc4cb0
008ccb70 lea edx, [edi + 0x378]
008ccb76 lea ecx, [ebp - 0x130]
008ccb7c call 0x412050
008ccb81 add esp, 4
008ccb84 mov ecx, dword ptr [eax]
008ccb86 or ecx, dword ptr [eax + 4]
008ccb89 jne 0x8ccbb2
008ccb8b mov ecx, dword ptr [eax + 8]
008ccb8e or ecx, dword ptr [eax + 0xc]
008ccb91 jne 0x8ccbb2
008ccb93 mov eax, dword ptr [edi + 0x424]
008ccb99 cmp eax, 1
008ccb9c jne 0x8ccba3
008ccb9e lea ecx, [eax + 3]
008ccba1 jmp 0x8ccbb7
008ccba3 xor ecx, ecx
008ccba5 mov edx, 5
008ccbaa cmp eax, 2
008ccbad cmove ecx, edx
008ccbb0 jmp 0x8ccbb7
008ccbb2 mov ecx, 1
008ccbb7 mov eax, dword ptr [edi + 0x314]
008ccbbd push eax
008ccbbe push ecx
008ccbbf lea ecx, [edi + 0x3b4]
008ccbc5 call 0x8f4540
008ccbca mov eax, dword ptr [edi + 0x2c]
008ccbcd cmp eax, 2
008ccbd0 je 0x8ccc0f
008ccbd2 cmp eax, 0xa
008ccbd5 je 0x8ccc0f
008ccbd7 cmp dword ptr [edi + 0x424], 2
008ccbde jne 0x8ccbea
008ccbe0 movss xmm1, dword ptr [0xb6a614]
008ccbe8 jmp 0x8ccc17
008ccbea movss xmm0, dword ptr [edi + 0x420]
008ccbf2 comiss xmm0, dword ptr [0xb6a18c]
008ccbf9 jbe 0x8ccc05
008ccbfb movss xmm1, dword ptr [0xb6a4d4]
008ccc03 jmp 0x8ccc17
008ccc05 movss xmm1, dword ptr [0xb6a5a4]
008ccc0d jmp 0x8ccc17
008ccc0f movss xmm1, dword ptr [0xb6a50c]
008ccc17 lea ecx, [edi + 0x3b4]
008ccc1d call 0x8f61a0
008ccc22 push 0xbc49d0
008ccc27 lea edx, [edi + 0x378]
008ccc2d lea ecx, [ebp - 0x130]
008ccc33 call 0x412050
008ccc38 add esp, 4
008ccc3b mov ecx, dword ptr [eax]
008ccc3d or ecx, dword ptr [eax + 4]
008ccc40 jne 0x8ccc4a
008ccc42 mov ecx, dword ptr [eax + 8]
008ccc45 or ecx, dword ptr [eax + 0xc]
008ccc48 je 0x8cccb2
008ccc4a push 0xbc4bf0
008ccc4f lea edx, [edi + 0x378]
008ccc55 lea ecx, [ebp - 0x130]
008ccc5b call 0x412050
008ccc60 add esp, 4
008ccc63 mov ecx, dword ptr [eax]
008ccc65 or ecx, dword ptr [eax + 4]
008ccc68 jne 0x8cccb2
008ccc6a mov ecx, dword ptr [eax + 8]
008ccc6d or ecx, dword ptr [eax + 0xc]
008ccc70 jne 0x8cccb2
008ccc72 test esi, esi
008ccc74 je 0x8ccc84
008ccc76 push 0x1e
008ccc78 mov ecx, esi
008ccc7a call 0x7866b0
008ccc7f movaps xmm1, xmm0
008ccc82 jmp 0x8ccc8c
008ccc84 movss xmm1, dword ptr [0xb6a614]
008ccc8c mov eax, dword ptr [edi + 0x20]
008ccc8f lea ecx, [edi + 0x3b4]
008ccc95 movd xmm0, eax
008ccc99 cvtdq2pd xmm0, xmm0
008ccc9d shr eax, 0x1f
008ccca0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008ccca9 cvtpd2ps xmm2, xmm0
008cccad call 0x8f8d80
008cccb2 push 0xbc4930
008cccb7 lea edx, [edi + 0x378]
008cccbd lea ecx, [ebp - 0x130]
008cccc3 call 0x412050
008cccc8 add esp, 4
008ccccb mov ecx, dword ptr [eax]
008ccccd or ecx, dword ptr [eax + 4]
008cccd0 jne 0x8cccda
008cccd2 mov ecx, dword ptr [eax + 8]
008cccd5 or ecx, dword ptr [eax + 0xc]
008cccd8 je 0x8ccd1a
008cccda test esi, esi
008cccdc je 0x8cccec
008cccde push 0xa
008ccce0 mov ecx, esi
008ccce2 call 0x7866b0
008ccce7 movaps xmm1, xmm0
008cccea jmp 0x8cccf4
008cccec movss xmm1, dword ptr [0xb6a614]
008cccf4 mov eax, dword ptr [edi + 0x20]
008cccf7 lea ecx, [edi + 0x3b4]
008cccfd movd xmm0, eax
008ccd01 cvtdq2pd xmm0, xmm0
008ccd05 shr eax, 0x1f
008ccd08 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008ccd11 cvtpd2ps xmm2, xmm0
008ccd15 call 0x8f6a40
008ccd1a push 0xbc4a20
008ccd1f lea edx, [edi + 0x378]
008ccd25 lea ecx, [ebp - 0x130]
008ccd2b call 0x412050
008ccd30 add esp, 4
008ccd33 mov ecx, dword ptr [eax]
008ccd35 or ecx, dword ptr [eax + 4]
008ccd38 jne 0x8ccdb2
008ccd3a mov ecx, dword ptr [eax + 8]
008ccd3d or ecx, dword ptr [eax + 0xc]
008ccd40 jne 0x8ccdb2
008ccd42 push 0xbc4960
008ccd47 lea edx, [edi + 0x378]
008ccd4d lea ecx, [ebp - 0x130]
008ccd53 call 0x412050
008ccd58 add esp, 4
008ccd5b mov ecx, dword ptr [eax]
008ccd5d or ecx, dword ptr [eax + 4]
008ccd60 jne 0x8ccd6e
008ccd62 mov edx, dword ptr [eax + 8]
008ccd65 or edx, dword ptr [eax + 0xc]
008ccd68 je 0x8ccdfe
008ccd6e test esi, esi
008ccd70 je 0x8ccd80
008ccd72 push 0x1a
008ccd74 mov ecx, esi
008ccd76 call 0x7866b0
008ccd7b movaps xmm1, xmm0
008ccd7e jmp 0x8ccd88
008ccd80 movss xmm1, dword ptr [0xb6a614]
008ccd88 mov eax, dword ptr [edi + 0x20]
008ccd8b lea esi, [edi + 0x3b4]
008ccd91 mov ecx, esi
008ccd93 movd xmm0, eax
008ccd97 cvtdq2pd xmm0, xmm0
008ccd9b shr eax, 0x1f
008ccd9e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008ccda7 cvtpd2ps xmm2, xmm0
008ccdab call 0x8f6e00
008ccdb0 jmp 0x8cce04
008ccdb2 test esi, esi
008ccdb4 je 0x8ccdc4
008ccdb6 push 0x2e
008ccdb8 mov ecx, esi
008ccdba call 0x7866b0
008ccdbf movaps xmm1, xmm0
008ccdc2 jmp 0x8ccdcc
008ccdc4 movss xmm1, dword ptr [0xb6a614]
008ccdcc mov eax, dword ptr [edi + 0x20]
008ccdcf lea esi, [edi + 0x3b4]
008ccdd5 mulss xmm1, dword ptr [0xb6a864]
008ccddd mov ecx, esi
008ccddf movd xmm0, eax
008ccde3 cvtdq2pd xmm0, xmm0
008ccde7 shr eax, 0x1f
008ccdea addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008ccdf3 cvtpd2ps xmm2, xmm0
008ccdf7 call 0x8f6e00
008ccdfc jmp 0x8cce04
008ccdfe lea esi, [edi + 0x3b4]
008cce04 push 0xbc4890
008cce09 mov edx, 0xbc4790
008cce0e lea ecx, [ebp - 0x130]
008cce14 call 0x427220
008cce19 add esp, 4
008cce1c lea edx, [edi + 0x378]
008cce22 lea ecx, [ebp - 0xf8]
008cce28 push eax
008cce29 call 0x412050
008cce2e add esp, 4
008cce31 mov ecx, dword ptr [eax]
008cce33 or ecx, dword ptr [eax + 4]
008cce36 jne 0x8cce40
008cce38 mov ecx, dword ptr [eax + 8]
008cce3b or ecx, dword ptr [eax + 0xc]
008cce3e je 0x8cce5b
008cce40 movss xmm1, dword ptr [0xb6ab20]
008cce48 mov ecx, esi
008cce4a call 0x8f93a0
008cce4f mov dword ptr [ebp - 0xe8], eax
008cce55 mov byte ptr [ebp - 0xbc], al
008cce5b cmp dword ptr [edi + 0x17c], 0
008cce62 je 0x8ccf1e
008cce68 push 0xbc4cc0
008cce6d lea edx, [edi + 0x378]
008cce73 lea ecx, [ebp - 0x120]
008cce79 call 0x412050
008cce7e add esp, 4
008cce81 mov ecx, dword ptr [eax]
008cce83 or ecx, dword ptr [eax + 4]
008cce86 jne 0x8ccf1e
008cce8c mov ecx, dword ptr [eax + 8]
008cce8f or ecx, dword ptr [eax + 0xc]
008cce92 jne 0x8ccf1e
008cce98 movss xmm1, dword ptr [edi + 0x2a4]
008ccea0 lea esi, [edi + 0x2a4]
008ccea6 movss xmm0, dword ptr [esi + 4]
008cceab lea eax, [ebp - 0xd8]
008cceb1 mulss xmm1, dword ptr [0xb6a434]
008cceb9 lea ecx, [edi + 0x3b4]
008ccebf mulss xmm0, dword ptr [0xb6a434]
008ccec7 push dword ptr [edi + 0x17c]
008ccecd movss dword ptr [ebp - 0xd8], xmm1
008cced5 push eax
008cced6 movss dword ptr [ebp - 0xd4], xmm0
008ccede call 0x8f8350
008ccee3 mov ecx, dword ptr [ebp - 0xe8]
008ccee9 xor edx, edx
008cceeb test al, al
008cceed movzx ecx, cl
008ccef0 mov byte ptr [edi + 0x466], al
008ccef6 cmovne ecx, edx
008ccef9 cmp dword ptr [edi + 0x424], 2
008ccf00 mov dword ptr [ebp - 0xe8], ecx
008ccf06 mov byte ptr [ebp - 0xbc], cl
008ccf0c jne 0x8ccf1e
008ccf0e push esi
008ccf0f lea esi, [edi + 0x3b4]
008ccf15 mov ecx, esi
008ccf17 call 0x8f8a30
008ccf1c jmp 0x8ccf24
008ccf1e lea esi, [edi + 0x3b4]
008ccf24 mov eax, dword ptr [0xbfd65c]
008ccf29 cmp dword ptr [eax + 0x1c319c], 0x1e
008ccf30 jne 0x8ccf50
008ccf32 mov eax, dword ptr [edi + 0x314]
008ccf38 test eax, eax
008ccf3a je 0x8ccf49
008ccf3c mov eax, dword ptr [eax + 0x28]
008ccf3f cmp eax, 1
008ccf42 je 0x8ccf50
008ccf44 cmp eax, 3
008ccf47 je 0x8ccf50
008ccf49 mov ecx, esi
008ccf4b call 0x8f8570
008ccf50 mov eax, dword ptr [edi + 0x34]
008ccf53 cmp eax, 1
008ccf56 je 0x8ccf6b
008ccf58 cmp eax, 3
008ccf5b jne 0x8cd4b1
008ccf61 cmp dword ptr [edi + 0x38], 0x7b
008ccf65 je 0x8cd4b1
008ccf6b cmp byte ptr [edi + 0x450], 0
008ccf72 jne 0x8cd4b1
008ccf78 push 0x65
008ccf7a push 3
008ccf7c lea eax, [ebp - 0xf0]
008ccf82 mov dword ptr [ebp - 0xd4], 0
008ccf8c push eax
008ccf8d lea eax, [ebp - 0xd8]
008ccf93 mov dword ptr [ebp - 0xd8], 0
008ccf9d lea esi, [edi + 0x448]
008ccfa3 mov dword ptr [ebp - 0xec], 0
008ccfad push eax
008ccfae lea ecx, [edi + 0x3b4]
008ccfb4 mov dword ptr [ebp - 0xf0], 0
008ccfbe mov dword ptr [ebp - 0xb4], esi
008ccfc4 call 0x8f90c0
008ccfc9 test eax, eax
008ccfcb je 0x8cd43f
008ccfd1 cmp dword ptr [esi], 0
008ccfd4 movss xmm4, dword ptr [ebp - 0xf0]
008ccfdc movss xmm5, dword ptr [ebp - 0xec]
008ccfe4 movaps xmm0, xmm4
008ccfe7 xorps xmm0, xmmword ptr [0xb6c9b0]
008ccfee movaps xmm2, xmm5
008ccff1 movss dword ptr [ebp - 0xa4], xmm0
008ccff9 movss dword ptr [ebp - 0xa0], xmm2
008cd001 je 0x8cd12c
008cd007 cmp dword ptr [edi + 0x44c], 0
008cd00e je 0x8cd12c
008cd014 movaps xmm1, xmm4
008cd017 movaps xmm0, xmm2
008cd01a call 0x447a80
008cd01f movaps xmm5, xmm0
008cd022 mov dword ptr [ebp - 0x10c], 2
008cd02c mulss xmm5, dword ptr [0xb6aa84]
008cd034 mov eax, esi
008cd036 mov dword ptr [ebp - 0xfc], eax
008cd03c movaps xmm0, xmm5
008cd03f movss dword ptr [ebp - 0x9c], xmm5
008cd047 subss xmm0, dword ptr [0xb6aae4]
008cd04f movss dword ptr [ebp - 0xac], xmm0
008cd057 mov esi, dword ptr [eax]
008cd059 test esi, esi
008cd05b je 0x8cd063
008cd05d cmp dword ptr [esi + 0x28], 7
008cd061 je 0x8cd065
008cd063 xor esi, esi
008cd065 push 0
008cd067 push edi
008cd068 mov ecx, esi
008cd06a call 0x8c72b0
008cd06f movss xmm0, dword ptr [ebp - 0x9c]
008cd077 mov eax, dword ptr [esi + 0x36c]
008cd07d movss xmm4, dword ptr [ebp - 0xa0]
008cd085 movss xmm3, dword ptr [ebp - 0xa4]
008cd08d movss xmm1, dword ptr [ebp - 0xd8]
008cd095 movaps xmm2, xmm3
008cd098 mulss xmm2, dword ptr [0xb6a8f4]
008cd0a0 mov dword ptr [esi + 0x370], eax
008cd0a6 mov eax, dword ptr [ebp - 0xfc]
008cd0ac xorps xmm3, xmmword ptr [0xb6c9b0]
008cd0b3 add eax, 4
008cd0b6 sub dword ptr [ebp - 0x10c], 1
008cd0bd addss xmm2, dword ptr [ebp - 0xd4]
008cd0c5 movss dword ptr [esi + 0x368], xmm0
008cd0cd movss dword ptr [esi + 0x36c], xmm0
008cd0d5 movss xmm0, dword ptr [ebp - 0xac]
008cd0dd movss dword ptr [esi + 0xe0], xmm0
008cd0e5 movaps xmm0, xmm4
008cd0e8 mulss xmm0, dword ptr [0xb6a8f4]
008cd0f0 mov dword ptr [ebp - 0xfc], eax
008cd0f6 xorps xmm4, xmmword ptr [0xb6c9b0]
008cd0fd movss dword ptr [esi + 0x298], xmm2
008cd105 addss xmm1, xmm0
008cd109 movss dword ptr [ebp - 0xa0], xmm4
008cd111 movss dword ptr [ebp - 0xa4], xmm3
008cd119 movss dword ptr [esi + 0x294], xmm1
008cd121 jne 0x8cd057
008cd127 jmp 0x8cd302
008cd12c movss xmm3, dword ptr [0xb6a8f4]
008cd134 mov eax, esi
008cd136 mov ecx, 2
008cd13b mov dword ptr [ebp - 0xb0], eax
008cd141 mov dword ptr [ebp - 0xfc], ecx
008cd147 cmp dword ptr [eax], 0
008cd14a jne 0x8cd2e0
008cd150 movaps xmm1, xmm2
008cd153 mulss xmm0, xmm3
008cd157 mulss xmm1, xmm3
008cd15b addss xmm0, dword ptr [ebp - 0xd4]
008cd163 addss xmm1, dword ptr [ebp - 0xd8]
008cd16b movss dword ptr [ebp - 0x114], xmm0
008cd173 movaps xmm0, xmm5
008cd176 movss dword ptr [ebp - 0x118], xmm1
008cd17e movaps xmm1, xmm4
008cd181 call 0x447a80
008cd186 mulss xmm0, dword ptr [0xb6aa84]
008cd18e lea eax, [edi + 0x2a4]
008cd194 push 1
008cd196 push dword ptr [edi + 0x314]
008cd19c push eax
008cd19d push dword ptr [edi + 0x3a8]
008cd1a3 lea eax, [ebp - 0x118]
008cd1a9 push ecx
008cd1aa movss dword ptr [esp], xmm0
008cd1af push eax
008cd1b0 push dword ptr [edi + 0x2c]
008cd1b3 call 0x8c7550
008cd1b8 mov esi, eax
008cd1ba add esp, 0x1c
008cd1bd test esi, esi
008cd1bf je 0x8cd28e
008cd1c5 push 1
008cd1c7 push edi
008cd1c8 mov ecx, esi
008cd1ca mov byte ptr [esi + 0x434], 1
008cd1d1 call 0x8c72b0
008cd1d6 movups xmm0, xmmword ptr [edi + 0x378]
008cd1dd lea eax, [ebp - 0x140]
008cd1e3 mov ecx, 0xbc4770
008cd1e8 push eax
008cd1e9 movups xmmword ptr [ebp - 0x130], xmm0
008cd1f0 call 0x57f3a0
008cd1f5 push eax
008cd1f6 lea edx, [ebp - 0x130]
008cd1fc lea ecx, [ebp - 0x158]
008cd202 call 0x412050
008cd207 mov ecx, dword ptr [esi + 0x314]
008cd20d add esp, 4
008cd210 movups xmm0, xmmword ptr [eax]
008cd213 mov byte ptr [esi + 0x450], 1
008cd21a lea eax, [esi + 0x314]
008cd220 movups xmmword ptr [esi + 0x378], xmm0
008cd227 test ecx, ecx
008cd229 je 0x8cd249
008cd22b mov dword ptr [ebp - 0x9c], eax
008cd231 add ecx, 0x324
008cd237 lea eax, [ebp - 0x9c]
008cd23d push eax
008cd23e call 0x4bc3c0
008cd243 lea eax, [esi + 0x314]
008cd249 push eax
008cd24a mov ecx, edi
008cd24c mov dword ptr [eax], edi
008cd24e call 0x4bae70
008cd253 mov eax, dword ptr [esi]
008cd255 mov ecx, esi
008cd257 call dword ptr [eax + 0xc]
008cd25a mov eax, dword ptr [ebp - 0xb0]
008cd260 mov ecx, dword ptr [eax]
008cd262 test ecx, ecx
008cd264 je 0x8cd284
008cd266 mov dword ptr [ebp - 0x9c], eax
008cd26c add ecx, 0x324
008cd272 lea eax, [ebp - 0x9c]
008cd278 push eax
008cd279 call 0x4bc3c0
008cd27e mov eax, dword ptr [ebp - 0xb0]
008cd284 push eax
008cd285 mov ecx, esi
008cd287 mov dword ptr [eax], esi
008cd289 call 0x4bae70
008cd28e movss xmm2, dword ptr [ebp - 0xa0]
008cd296 movss xmm0, dword ptr [ebp - 0xa4]
008cd29e xorps xmm2, xmmword ptr [0xb6c9b0]
008cd2a5 xorps xmm0, xmmword ptr [0xb6c9b0]
008cd2ac movss xmm3, dword ptr [0xb6a8f4]
008cd2b4 movss xmm4, dword ptr [ebp - 0xf0]
008cd2bc movss xmm5, dword ptr [ebp - 0xec]
008cd2c4 mov eax, dword ptr [ebp - 0xb0]
008cd2ca mov ecx, dword ptr [ebp - 0xfc]
008cd2d0 movss dword ptr [ebp - 0xa0], xmm2
008cd2d8 movss dword ptr [ebp - 0xa4], xmm0
008cd2e0 add eax, 4
008cd2e3 sub ecx, 1
008cd2e6 mov dword ptr [ebp - 0xb0], eax
008cd2ec mov dword ptr [ebp - 0xfc], ecx
008cd2f2 jne 0x8cd147
008cd2f8 mov dword ptr [edi + 0x4b0], 0
008cd302 mov eax, 2
008cd307 lea esi, [edi + 0x448]
008cd30d mov dword ptr [ebp - 0xc4], eax
008cd313 mov esi, dword ptr [esi]
008cd315 test esi, esi
008cd317 je 0x8cd31f
008cd319 cmp dword ptr [esi + 0x28], 7
008cd31d je 0x8cd321
008cd31f xor esi, esi
008cd321 test esi, esi
008cd323 je 0x8cd40a
008cd329 mov eax, dword ptr [0xbfd65c]
008cd32e mov ecx, dword ptr [eax + 0x1a30dc]
008cd334 sub ecx, dword ptr [edi + 0x280]
008cd33a and ecx, 0x8000000f
008cd340 jns 0x8cd347
008cd342 dec ecx
008cd343 or ecx, 0xfffffff0
008cd346 inc ecx
008cd347 movaps xmm0, xmmword ptr [0xb6c610]
008cd34e mov eax, 0x10
008cd353 sub eax, ecx
008cd355 mov dword ptr [ebp - 0x24], 0x3f800000
008cd35c cmp ecx, 8
008cd35f movups xmmword ptr [ebp - 0x40], xmm0
008cd363 cmovl eax, ecx
008cd366 lea ecx, [ebp - 0x40]
008cd369 push 1
008cd36b push 0
008cd36d push 0xff
008cd372 movd xmm1, eax
008cd376 mov eax, dword ptr [esi]
008cd378 cvtdq2ps xmm1, xmm1
008cd37b push -1
008cd37d push ecx
008cd37e mov ecx, esi
008cd380 mulss xmm1, dword ptr [0xb6a2ec]
008cd388 movaps xmm0, xmm1
008cd38b addss xmm0, xmm1
008cd38f mulss xmm1, dword ptr [0xb6a434]
008cd397 subss xmm1, dword ptr [0xb6a350]
008cd39f addss xmm0, dword ptr [0xb6a3b0]
008cd3a7 movss dword ptr [ebp - 0x20], xmm1
008cd3ac movss dword ptr [ebp - 0x30], xmm0
008cd3b1 movss dword ptr [ebp - 0x2c], xmm0
008cd3b6 movss dword ptr [ebp - 0x28], xmm0
008cd3bb movss dword ptr [ebp - 0x1c], xmm1
008cd3c0 movss dword ptr [ebp - 0x18], xmm1
008cd3c5 call dword ptr [eax + 0x38]
008cd3c8 mov ecx, dword ptr [esi + 0x318]
008cd3ce test ecx, ecx
008cd3d0 je 0x8cd3e6
008cd3d2 mov eax, dword ptr [ecx]
008cd3d4 lea edx, [ebp - 0x40]
008cd3d7 push 1
008cd3d9 push 0
008cd3db push 0xff
008cd3e0 push -1
008cd3e2 push edx
008cd3e3 call dword ptr [eax + 0x38]
008cd3e6 mov ecx, dword ptr [esi + 0x48c]
008cd3ec test ecx, ecx
008cd3ee je 0x8cd404
008cd3f0 mov eax, dword ptr [ecx]
008cd3f2 lea edx, [ebp - 0x40]
008cd3f5 push 1
008cd3f7 push 0
008cd3f9 push 0xff
008cd3fe push -1
008cd400 push edx
008cd401 call dword ptr [eax + 0x38]
008cd404 mov eax, dword ptr [ebp - 0xc4]
008cd40a mov esi, dword ptr [ebp - 0xb4]
008cd410 add esi, 4
008cd413 sub eax, 1
008cd416 mov dword ptr [ebp - 0xb4], esi
008cd41c mov dword ptr [ebp - 0xc4], eax
008cd422 jne 0x8cd313
008cd428 xor al, al
008cd42a mov byte ptr [ebp - 0xa5], 1
008cd431 mov dword ptr [ebp - 0xe8], eax
008cd437 mov byte ptr [ebp - 0xbc], al
008cd43d jmp 0x8cd4b1
008cd43f mov eax, 2
008cd444 mov dword ptr [ebp - 0xfc], eax
008cd44a nop word ptr [eax + eax]
008cd450 mov ecx, dword ptr [esi]
008cd452 test ecx, ecx
008cd454 je 0x8cd461
008cd456 mov eax, dword ptr [ecx]
008cd458 call dword ptr [eax + 0x28]
008cd45b mov eax, dword ptr [ebp - 0xfc]
008cd461 add esi, 4
008cd464 sub eax, 1
008cd467 mov dword ptr [ebp - 0xfc], eax
008cd46d jne 0x8cd450
008cd46f mov ecx, dword ptr [edi + 0x318]
008cd475 test ecx, ecx
008cd477 je 0x8cd4a9
008cd479 cmp dword ptr [edi + 0x438], 0
008cd480 je 0x8cd4b1
008cd482 cmp dword ptr [ecx + 0x28], 0x3e8
008cd489 jne 0x8cd4b1
008cd48b cmp dword ptr [ecx + 0x2c], 0x32
008cd48f jne 0x8cd4b1
008cd491 cmp dword ptr [ecx + 0x30], 4
008cd495 je 0x8cd4b1
008cd497 mov eax, dword ptr [edi + 0x2c]
008cd49a cmp eax, 6
008cd49d je 0x8cd4a4
008cd49f cmp eax, 0xf
008cd4a2 jne 0x8cd4b1
008cd4a4 mov eax, dword ptr [ecx]
008cd4a6 call dword ptr [eax + 0x28]
008cd4a9 push ecx
008cd4aa mov ecx, edi
008cd4ac call 0x8d79b0
008cd4b1 mov eax, dword ptr [edi + 0x34]
008cd4b4 mov byte ptr [ebp - 0xbd], 0
008cd4bb cmp eax, 1
008cd4be je 0x8cd81d
008cd4c4 cmp eax, 3
008cd4c7 je 0x8cd81d
008cd4cd push 0xbc
008cd4d2 push 0x3e8
008cd4d7 lea eax, [ebp - 0xf0]
008cd4dd mov dword ptr [ebp - 0xd4], 0
008cd4e7 push eax
008cd4e8 lea eax, [ebp - 0xd8]
008cd4ee mov dword ptr [ebp - 0xd8], 0
008cd4f8 push eax
008cd4f9 lea ecx, [edi + 0x3b4]
008cd4ff mov dword ptr [ebp - 0xec], 0
008cd509 mov dword ptr [ebp - 0xf0], 0
008cd513 call 0x8f90c0
008cd518 mov esi, eax
008cd51a mov dword ptr [ebp - 0xcc], esi
008cd520 test esi, esi
008cd522 je 0x8cd7fe
008cd528 movss xmm0, dword ptr [esi + 0x3c4]
008cd530 mulss xmm0, dword ptr [0xb6a230]
008cd538 movss dword ptr [ebp - 0x9c], xmm0
008cd540 call 0x412010
008cd545 movss dword ptr [ebp - 0xac], xmm0
008cd54d movss xmm0, dword ptr [ebp - 0x9c]
008cd555 call 0x411fe0
008cd55a movss xmm5, dword ptr [ebp - 0xf0]
008cd562 movss xmm4, dword ptr [ebp - 0xec]
008cd56a movaps xmm3, xmm5
008cd56d movss xmm6, dword ptr [ebp - 0xac]
008cd575 movaps xmm1, xmm4
008cd578 mulss xmm3, xmm0
008cd57c addss xmm0, xmm0
008cd580 mulss xmm1, xmm6
008cd584 addss xmm6, xmm6
008cd588 addss xmm3, xmm1
008cd58c movaps xmm2, xmm3
008cd58f mulss xmm6, xmm3
008cd593 mulss xmm2, xmm0
008cd597 subss xmm4, xmm6
008cd59b subss xmm5, xmm2
008cd59f movaps xmm0, xmm4
008cd5a2 movaps xmm1, xmm5
008cd5a5 call 0x447a80
008cd5aa mulss xmm0, dword ptr [0xb6aa84]
008cd5b2 lea ecx, [ebp - 0x98]
008cd5b8 movss dword ptr [ebp - 0xfc], xmm0
008cd5c0 call 0x402120
008cd5c5 mov edx, dword ptr [edi + 0x2c]
008cd5c8 cmp edx, 5
008cd5cb je 0x8cd60e
008cd5cd cmp edx, 0xa
008cd5d0 je 0x8cd60e
008cd5d2 movaps xmm0, xmmword ptr [0xb6c610]
008cd5d9 lea eax, [ebp - 0x40]
008cd5dc movups xmmword ptr [ebp - 0x40], xmm0
008cd5e0 push eax
008cd5e1 movaps xmm0, xmmword ptr [0xb6c850]
008cd5e8 movups xmmword ptr [ebp - 0x30], xmm0
008cd5ec mov dword ptr [ebp - 0x20], 0
008cd5f3 mov dword ptr [ebp - 0x1c], 0
008cd5fa mov dword ptr [ebp - 0x18], 0
008cd601 call 0x4021a0
008cd606 movss xmm0, dword ptr [ebp - 0xfc]
008cd60e mov eax, dword ptr [esi + 0x314]
008cd614 test eax, eax
008cd616 je 0x8cd61e
008cd618 cmp dword ptr [eax + 0x28], 1
008cd61c je 0x8cd620
008cd61e xor eax, eax
008cd620 mov ecx, dword ptr [edi + 0x438]
008cd626 test ecx, ecx
008cd628 jne 0x8cd6ef
008cd62e push 1
008cd630 push eax
008cd631 lea eax, [edi + 0x2a4]
008cd637 push eax
008cd638 push dword ptr [edi + 0x3a8]
008cd63e lea eax, [ebp - 0xd8]
008cd644 push ecx
008cd645 movss dword ptr [esp], xmm0
008cd64a push eax
008cd64b push edx
008cd64c call 0x8c7550
008cd651 mov esi, eax
008cd653 add esp, 0x1c
008cd656 test esi, esi
008cd658 je 0x8cd7a7
008cd65e mov edx, dword ptr [esi]
008cd660 lea eax, [ebp - 0x98]
008cd666 push 1
008cd668 push 0
008cd66a push 0xff
008cd66f push -1
008cd671 push eax
008cd672 mov ecx, esi
008cd674 mov byte ptr [esi + 0x434], 1
008cd67b mov byte ptr [esi + 0x464], 1
008cd682 call dword ptr [edx + 0x38]
008cd685 mov eax, dword ptr [esi]
008cd687 push ecx
008cd688 mov ecx, esi
008cd68a mov dword ptr [esp], 0x40e00000
008cd691 call dword ptr [eax + 0x3c]
008cd694 movss xmm0, dword ptr [edi + 0x2b0]
008cd69c addss xmm0, dword ptr [0xb6aafc]
008cd6a4 movss dword ptr [esi + 0x2b0], xmm0
008cd6ac mov eax, dword ptr [edi + 0x3a8]
008cd6b2 mov dword ptr [esi + 0x3a8], eax
008cd6b8 cmp byte ptr [edi + 0x3ae], 0
008cd6bf jne 0x8cd6ce
008cd6c1 cmp byte ptr [edi + 0x16b], 0
008cd6c8 jne 0x8cd6ce
008cd6ca xor al, al
008cd6cc jmp 0x8cd6d0
008cd6ce mov al, 1
008cd6d0 mov byte ptr [esi + 0x3ae], al
008cd6d6 mov ecx, esi
008cd6d8 mov eax, dword ptr [esi]
008cd6da call dword ptr [eax + 0xc]
008cd6dd mov edx, esi
008cd6df lea ecx, [edi + 0x438]
008cd6e5 call 0x68cf00
008cd6ea jmp 0x8cd7a7
008cd6ef push 0
008cd6f1 push 0xbeabc8
008cd6f6 push 0xbeab18
008cd6fb push 0
008cd6fd push ecx
008cd6fe call 0x9ec34c
008cd703 add esp, 0x14
008cd706 mov esi, eax
008cd708 lea eax, [ebp - 0x98]
008cd70e mov ecx, esi
008cd710 mov edx, dword ptr [esi]
008cd712 push 1
008cd714 push 0
008cd716 push 0xff
008cd71b push -1
008cd71d push eax
008cd71e call dword ptr [edx + 0x38]
008cd721 mov eax, dword ptr [esi]
008cd723 push ecx
008cd724 mov ecx, esi
008cd726 mov dword ptr [esp], 0x40e00000
008cd72d call dword ptr [eax + 0x3c]
008cd730 movss xmm0, dword ptr [edi + 0x2b0]
008cd738 addss xmm0, dword ptr [0xb6aafc]
008cd740 movss dword ptr [esi + 0x2b0], xmm0
008cd748 mov eax, dword ptr [edi + 0x3a8]
008cd74e mov dword ptr [esi + 0x3a8], eax
008cd754 cmp byte ptr [edi + 0x3ae], 0
008cd75b jne 0x8cd76a
008cd75d cmp byte ptr [edi + 0x16b], 0
008cd764 jne 0x8cd76a
008cd766 xor al, al
008cd768 jmp 0x8cd76c
008cd76a mov al, 1
008cd76c movss xmm0, dword ptr [ebp - 0xfc]
008cd774 push ecx
008cd775 mov ecx, esi
008cd777 mov byte ptr [esi + 0x3ae], al
008cd77d movss dword ptr [esp], xmm0
008cd782 call 0x8c59a0
008cd787 movss xmm0, dword ptr [ebp - 0xd8]
008cd78f movss dword ptr [esi + 0x294], xmm0
008cd797 movss xmm0, dword ptr [ebp - 0xd4]
008cd79f movss dword ptr [esi + 0x298], xmm0
008cd7a7 mov eax, dword ptr [0xbfd65c]
008cd7ac mov edx, dword ptr [ebp - 0xcc]
008cd7b2 mov eax, dword ptr [eax + 0x1a30dc]
008cd7b8 sub eax, dword ptr [edx + 0x280]
008cd7be cmp eax, 0x96
008cd7c3 jge 0x8cd7e1
008cd7c5 mov eax, dword ptr [edx + 0x3ac]
008cd7cb mov ecx, 0x1e
008cd7d0 cmp eax, ecx
008cd7d2 cmovg ecx, eax
008cd7d5 mov dword ptr [edx + 0x3ac], ecx
008cd7db mov dword ptr [edx + 0x3b0], ecx
008cd7e1 mov al, 1
008cd7e3 mov byte ptr [ebp - 0xa5], 1
008cd7ea mov dword ptr [ebp - 0xe8], eax
008cd7f0 mov byte ptr [ebp - 0xbc], al
008cd7f6 mov byte ptr [ebp - 0xbd], al
008cd7fc jmp 0x8cd81d
008cd7fe mov ecx, dword ptr [edi + 0x438]
008cd804 test ecx, ecx
008cd806 je 0x8cd81d
008cd808 mov eax, dword ptr [ecx + 0x314]
008cd80e test eax, eax
008cd810 je 0x8cd81d
008cd812 cmp dword ptr [eax + 0x28], 1
008cd816 jne 0x8cd81d
008cd818 mov eax, dword ptr [ecx]
008cd81a call dword ptr [eax + 0x28]
008cd81d mov eax, dword ptr [edi + 0x34]
008cd820 cmp eax, 1
008cd823 je 0x8cd838
008cd825 cmp eax, 3
008cd828 jne 0x8cdcb1
008cd82e cmp dword ptr [edi + 0x38], 0x65
008cd832 je 0x8cdcb1
008cd838 cmp byte ptr [edi + 0x464], 0
008cd83f jne 0x8cdcb1
008cd845 push 0x7b
008cd847 push 3
008cd849 lea eax, [ebp - 0xd8]
008cd84f mov dword ptr [ebp - 0xec], 0
008cd859 push eax
008cd85a lea eax, [ebp - 0xf0]
008cd860 mov dword ptr [ebp - 0xf0], 0
008cd86a push eax
008cd86b lea ecx, [edi + 0x3b4]
008cd871 mov dword ptr [ebp - 0xd4], 0
008cd87b mov dword ptr [ebp - 0xd8], 0
008cd885 lea esi, [edi + 0x454]
008cd88b call 0x8f90c0
008cd890 test eax, eax
008cd892 je 0x8cdc40
008cd898 cmp dword ptr [esi], 0
008cd89b je 0x8cdaff
008cd8a1 cmp dword ptr [edi + 0x458], 0
008cd8a8 je 0x8cdaff
008cd8ae cmp dword ptr [edi + 0x45c], 0
008cd8b5 je 0x8cdaff
008cd8bb cmp dword ptr [edi + 0x460], 0
008cd8c2 je 0x8cdaff
008cd8c8 movss xmm1, dword ptr [ebp - 0xd8]
008cd8d0 xor esi, esi
008cd8d2 movss xmm0, dword ptr [ebp - 0xd4]
008cd8da mov dword ptr [ebp - 0xfc], esi
008cd8e0 call 0x447a80
008cd8e5 movss xmm1, dword ptr [0xb6aa0c]
008cd8ed movaps xmm2, xmm0
008cd8f0 mulss xmm2, dword ptr [0xb6aa84]
008cd8f8 movss dword ptr [ebp - 0x9c], xmm2
008cd900 movaps xmm0, xmm2
008cd903 lea ecx, [ebp - 0x6c]
008cd906 movss dword ptr [ebp - 0xa0], xmm0
008cd90e call 0x402120
008cd913 test esi, esi
008cd915 jne 0x8cd928
008cd917 subss xmm0, xmm1
008cd91b movss dword ptr [ebp - 0xa0], xmm0
008cd923 jmp 0x8cda2c
008cd928 cmp esi, 1
008cd92b jne 0x8cd983
008cd92d subss xmm0, dword ptr [0xb6a974]
008cd935 lea ecx, [ebp - 0x1b4]
008cd93b movss dword ptr [ebp - 0xa0], xmm0
008cd943 call 0x65add0
008cd948 movaps xmm0, xmmword ptr [0xb6c630]
008cd94f movss xmm1, dword ptr [0xb6a550]
008cd957 movups xmmword ptr [ebp - 0x6c], xmm0
008cd95b mov dword ptr [ebp - 0x18c], 0
008cd965 movups xmm0, xmmword ptr [ebp - 0x1a4]
008cd96c mov eax, dword ptr [ebp - 0x18c]
008cd972 movups xmmword ptr [ebp - 0x5c], xmm0
008cd976 movss xmm0, dword ptr [0xb6a428]
008cd97e jmp 0x8cda21
008cd983 cmp esi, 2
008cd986 jne 0x8cd9cf
008cd988 addss xmm0, dword ptr [0xb6a974]
008cd990 lea ecx, [ebp - 0x1e0]
008cd996 movss dword ptr [ebp - 0xa0], xmm0
008cd99e call 0x65add0
008cd9a3 movaps xmm0, xmmword ptr [0xb6c630]
008cd9aa movss xmm1, dword ptr [0xb6a550]
008cd9b2 mov dword ptr [ebp - 0x1b8], 0x3ec8c8ca
008cd9bc mov eax, dword ptr [ebp - 0x1b8]
008cd9c2 movups xmmword ptr [ebp - 0x6c], xmm0
008cd9c6 movups xmm0, xmmword ptr [ebp - 0x1d0]
008cd9cd jmp 0x8cda15
008cd9cf cmp esi, 3
008cd9d2 jne 0x8cda2c
008cd9d4 addss xmm0, xmm1
008cd9d8 lea ecx, [ebp - 0x20c]
008cd9de movss dword ptr [ebp - 0xa0], xmm0
008cd9e6 call 0x65add0
008cd9eb movaps xmm0, xmmword ptr [0xb6c740]
008cd9f2 movss xmm1, dword ptr [0xb6a428]
008cd9fa mov dword ptr [ebp - 0x1e4], 0x3f48c8ca
008cda04 mov eax, dword ptr [ebp - 0x1e4]
008cda0a movups xmmword ptr [ebp - 0x6c], xmm0
008cda0e movups xmm0, xmmword ptr [ebp - 0x1fc]
008cda15 movups xmmword ptr [ebp - 0x5c], xmm0
008cda19 movss xmm0, dword ptr [0xb6ae38]
008cda21 unpcklps xmm0, xmm1
008cda24 movq qword ptr [ebp - 0x4c], xmm0
008cda29 mov dword ptr [ebp - 0x44], eax
008cda2c push 0
008cda2e push 0xbeabc8
008cda33 push 0xbeab18
008cda38 push 0
008cda3a push dword ptr [edi + esi*4 + 0x454]
008cda41 call 0x9ec34c
008cda46 add esp, 0x14
008cda49 mov esi, eax
008cda4b mov ecx, esi
008cda4d push 0
008cda4f push edi
008cda50 call 0x8c72b0
008cda55 mov edx, dword ptr [esi]
008cda57 lea eax, [ebp - 0x6c]
008cda5a push 1
008cda5c push 0
008cda5e push 0xff
008cda63 push -1
008cda65 push eax
008cda66 mov ecx, esi
008cda68 call dword ptr [edx + 0x38]
008cda6b movss xmm0, dword ptr [ebp - 0xa0]
008cda73 mov eax, dword ptr [esi + 0x36c]
008cda79 movss xmm1, dword ptr [0xb6aa0c]
008cda81 movss xmm2, dword ptr [ebp - 0x9c]
008cda89 movss dword ptr [esi + 0x368], xmm0
008cda91 movss dword ptr [esi + 0x36c], xmm0
008cda99 subss xmm0, dword ptr [0xb6aae4]
008cdaa1 mov dword ptr [esi + 0x370], eax
008cdaa7 movss dword ptr [esi + 0xe0], xmm0
008cdaaf movss xmm0, dword ptr [ebp - 0xf0]
008cdab7 movss dword ptr [esi + 0x294], xmm0
008cdabf movss xmm0, dword ptr [ebp - 0xec]
008cdac7 movss dword ptr [esi + 0x298], xmm0
008cdacf mov esi, dword ptr [ebp - 0xfc]
008cdad5 inc esi
008cdad6 mov dword ptr [ebp - 0xfc], esi
008cdadc cmp esi, 4
008cdadf jl 0x8cd900
008cdae5 xor al, al
008cdae7 mov byte ptr [ebp - 0xa5], 1
008cdaee mov dword ptr [ebp - 0xe8], eax
008cdaf4 mov byte ptr [ebp - 0xbc], al
008cdafa jmp 0x8cdcb1
008cdaff xor esi, esi
008cdb01 mov dword ptr [ebp - 0xc4], esi
008cdb07 nop word ptr [eax + eax]
008cdb10 cmp dword ptr [edi + esi*4 + 0x454], 0
008cdb18 lea eax, [edi + 0x454]
008cdb1e lea eax, [eax + esi*4]
008cdb21 mov dword ptr [ebp - 0xfc], eax
008cdb27 jne 0x8cdc0f
008cdb2d movss xmm1, dword ptr [ebp - 0xd8]
008cdb35 movss xmm0, dword ptr [ebp - 0xd4]
008cdb3d call 0x447a80
008cdb42 mulss xmm0, dword ptr [0xb6aa84]
008cdb4a test esi, esi
008cdb4c jne 0x8cdb58
008cdb4e subss xmm0, dword ptr [0xb6aa0c]
008cdb56 jmp 0x8cdb83
008cdb58 cmp esi, 1
008cdb5b jne 0x8cdb67
008cdb5d subss xmm0, dword ptr [0xb6a974]
008cdb65 jmp 0x8cdb83
008cdb67 cmp esi, 2
008cdb6a jne 0x8cdb76
008cdb6c addss xmm0, dword ptr [0xb6a974]
008cdb74 jmp 0x8cdb83
008cdb76 cmp esi, 3
008cdb79 jne 0x8cdb83
008cdb7b addss xmm0, dword ptr [0xb6aa0c]
008cdb83 push 1
008cdb85 push dword ptr [edi + 0x314]
008cdb8b lea eax, [edi + 0x2a4]
008cdb91 push eax
008cdb92 push dword ptr [edi + 0x3a8]
008cdb98 lea eax, [ebp - 0xf0]
008cdb9e push ecx
008cdb9f movss dword ptr [esp], xmm0
008cdba4 push eax
008cdba5 push dword ptr [edi + 0x2c]
008cdba8 call 0x8c7550
008cdbad mov esi, eax
008cdbaf add esp, 0x1c
008cdbb2 test esi, esi
008cdbb4 je 0x8cdc09
008cdbb6 push 1
008cdbb8 push edi
008cdbb9 mov ecx, esi
008cdbbb mov byte ptr [esi + 0x434], 1
008cdbc2 call 0x8c72b0
008cdbc7 mov eax, dword ptr [esi]
008cdbc9 mov ecx, esi
008cdbcb mov byte ptr [esi + 0x464], 1
008cdbd2 call dword ptr [eax + 0xc]
008cdbd5 mov eax, dword ptr [ebp - 0xfc]
008cdbdb mov ecx, dword ptr [eax]
008cdbdd test ecx, ecx
008cdbdf je 0x8cdbff
008cdbe1 mov dword ptr [ebp - 0x9c], eax
008cdbe7 add ecx, 0x324
008cdbed lea eax, [ebp - 0x9c]
008cdbf3 push eax
008cdbf4 call 0x4bc3c0
008cdbf9 mov eax, dword ptr [ebp - 0xfc]
008cdbff push eax
008cdc00 mov ecx, esi
008cdc02 mov dword ptr [eax], esi
008cdc04 call 0x4bae70
008cdc09 mov esi, dword ptr [ebp - 0xc4]
008cdc0f inc esi
008cdc10 mov dword ptr [ebp - 0xc4], esi
008cdc16 cmp esi, 4
008cdc19 jl 0x8cdb10
008cdc1f xor al, al
008cdc21 mov dword ptr [edi + 0x4b0], 0
008cdc2b mov byte ptr [ebp - 0xa5], 1
008cdc32 mov dword ptr [ebp - 0xe8], eax
008cdc38 mov byte ptr [ebp - 0xbc], al
008cdc3e jmp 0x8cdcb1
008cdc40 mov eax, 4
008cdc45 mov dword ptr [ebp - 0xfc], eax
008cdc4b nop dword ptr [eax + eax]
008cdc50 mov ecx, dword ptr [esi]
008cdc52 test ecx, ecx
008cdc54 je 0x8cdc61
008cdc56 mov eax, dword ptr [ecx]
008cdc58 call dword ptr [eax + 0x28]
008cdc5b mov eax, dword ptr [ebp - 0xfc]
008cdc61 add esi, 4
008cdc64 sub eax, 1
008cdc67 mov dword ptr [ebp - 0xfc], eax
008cdc6d jne 0x8cdc50
008cdc6f mov ecx, dword ptr [edi + 0x318]
008cdc75 test ecx, ecx
008cdc77 je 0x8cdca9
008cdc79 cmp dword ptr [edi + 0x438], 0
008cdc80 je 0x8cdcb1
008cdc82 cmp dword ptr [ecx + 0x28], 0x3e8
008cdc89 jne 0x8cdcb1
008cdc8b cmp dword ptr [ecx + 0x2c], 0x32
008cdc8f jne 0x8cdcb1
008cdc91 cmp dword ptr [ecx + 0x30], 4
008cdc95 je 0x8cdcb1
008cdc97 mov eax, dword ptr [edi + 0x2c]
008cdc9a cmp eax, 6
008cdc9d je 0x8cdca4
008cdc9f cmp eax, 0xf
008cdca2 jne 0x8cdcb1
008cdca4 mov eax, dword ptr [ecx]
008cdca6 call dword ptr [eax + 0x28]
008cdca9 push ecx
008cdcaa mov ecx, edi
008cdcac call 0x8d79b0
008cdcb1 lea esi, [edi + 0x378]
008cdcb7 push 0xbc4940
008cdcbc mov edx, esi
008cdcbe lea ecx, [ebp - 0x130]
008cdcc4 call 0x412050
008cdcc9 add esp, 4
008cdccc mov ecx, dword ptr [eax]
008cdcce or ecx, dword ptr [eax + 4]
008cdcd1 jne 0x8cdcdf
008cdcd3 mov ecx, dword ptr [eax + 8]
008cdcd6 or ecx, dword ptr [eax + 0xc]
008cdcd9 je 0x8ce6fa
008cdcdf cmp byte ptr [ebp - 0xa5], 0
008cdce6 jne 0x8ce6fa
008cdcec cmp byte ptr [edi + 0x466], 0
008cdcf3 jne 0x8ce6fa
008cdcf9 mov ecx, dword ptr [edi + 0x3d0]
008cdcff mov eax, dword ptr [edi + 0x3d4]
008cdd05 sub eax, ecx
008cdd07 sar eax, 3
008cdd0a movss xmm1, dword ptr [ecx + eax*8 - 8]
008cdd10 movss xmm0, dword ptr [ecx + eax*8 - 4]
008cdd16 mov eax, dword ptr [edi + 0x400]
008cdd1c movss dword ptr [ebp - 0x10c], xmm0
008cdd24 subss xmm0, dword ptr [ecx + 4]
008cdd29 movss dword ptr [ebp - 0xfc], xmm1
008cdd31 movss xmm2, dword ptr [eax - 8]
008cdd36 subss xmm2, dword ptr [eax - 0x10]
008cdd3b subss xmm1, dword ptr [ecx]
008cdd3f mulss xmm0, xmm0
008cdd43 movss dword ptr [ebp - 0xc4], xmm2
008cdd4b movss xmm2, dword ptr [eax - 4]
008cdd50 subss xmm2, dword ptr [eax - 0xc]
008cdd55 mulss xmm1, xmm1
008cdd59 addss xmm0, xmm1
008cdd5d movss dword ptr [ebp - 0xa0], xmm2
008cdd65 call 0x4228c0
008cdd6a movss xmm2, dword ptr [ebp - 0xfc]
008cdd72 lea eax, [edi + 0x2a4]
008cdd78 addss xmm2, dword ptr [eax]
008cdd7c movss xmm1, dword ptr [ebp - 0x10c]
008cdd84 sub esp, 0xc
008cdd87 addss xmm1, dword ptr [eax + 4]
008cdd8c mov edi, dword ptr [0xbfd65c]
008cdd92 movss xmm3, dword ptr [0xb6af64]
008cdd9a mov dword ptr [esp + 8], 0xc3030000
008cdda2 mov dword ptr [ebp - 0x9c], eax
008cdda8 lea eax, [ebp - 0xd8]
008cddae mov ecx, dword ptr [edi + 0x18190]
008cddb4 mov dword ptr [esp + 4], 0xc3030000
008cddbc mov dword ptr [esp], 0xc3030000
008cddc3 push eax
008cddc4 lea eax, [ebp - 0xf0]
008cddca movss dword ptr [ebp - 0xcc], xmm0
008cddd2 push eax
008cddd3 movss dword ptr [ebp - 0xd8], xmm2
008cdddb movss dword ptr [ebp - 0xd4], xmm1
008cdde3 call 0x7cec10
008cdde8 xor esi, esi
008cddea nop word ptr [eax + eax]
008cddf0 movss xmm3, dword ptr [0xb6af60]
008cddf8 lea eax, [ebp - 0xf0]
008cddfe mov ecx, dword ptr [edi + 0x18190]
008cde04 sub esp, 0xc
008cde07 mov dword ptr [esp + 8], 0xc3020000
008cde0f mov dword ptr [esp + 4], 0xc3020000
008cde17 mov dword ptr [esp], 0xc3020000
008cde1e push eax
008cde1f lea eax, [ebp - 0xd8]
008cde25 push eax
008cde26 call 0x7cef20
008cde2b movss xmm3, dword ptr [ebp - 0xd8]
008cde33 movss xmm1, dword ptr [ebp - 0xf0]
008cde3b movss xmm2, dword ptr [ebp - 0xd4]
008cde43 ucomiss xmm3, xmm1
008cde46 lahf 
008cde47 test ah, 0x44
008cde4a jp 0x8cde5d
008cde4c movss xmm0, dword ptr [ebp - 0xec]
008cde54 ucomiss xmm2, xmm0
008cde57 lahf 
008cde58 test ah, 0x44
008cde5b jnp 0x8cde7d
008cde5d inc esi
008cde5e movaps xmm1, xmm3
008cde61 movss dword ptr [ebp - 0xf0], xmm1
008cde69 movaps xmm0, xmm2
008cde6c movss dword ptr [ebp - 0xec], xmm0
008cde74 cmp esi, 4
008cde77 jb 0x8cddf0
008cde7d mov esi, dword ptr [ebp - 0x9c]
008cde83 mov edi, dword ptr [ebp - 0xb8]
008cde89 subss xmm1, dword ptr [esi]
008cde8d subss xmm0, dword ptr [esi + 4]
008cde92 ucomiss xmm1, dword ptr [ebp - 0xfc]
008cde99 movss dword ptr [ebp - 0xf0], xmm1
008cdea1 movss dword ptr [ebp - 0xec], xmm0
008cdea9 lahf 
008cdeaa test ah, 0x44
008cdead jp 0x8ce42b
008cdeb3 ucomiss xmm0, dword ptr [ebp - 0x10c]
008cdeba lahf 
008cdebb test ah, 0x44
008cdebe jp 0x8ce42b
008cdec4 mov ecx, dword ptr [edi + 0x488]
008cdeca test ecx, ecx
008cdecc je 0x8cded3
008cdece mov eax, dword ptr [ecx]
008cded0 call dword ptr [eax + 0x28]
008cded3 lea esi, [edi + 0x378]
008cded9 cmp byte ptr [ebp - 0xbd], 0
008cdee0 jne 0x8ce888
008cdee6 push 0xbc4c10
008cdeeb mov edx, esi
008cdeed lea ecx, [ebp - 0x130]
008cdef3 call 0x412050
008cdef8 add esp, 4
008cdefb mov ecx, dword ptr [eax]
008cdefd or ecx, dword ptr [eax + 4]
008cdf00 jne 0x8cdf0e
008cdf02 mov ecx, dword ptr [eax + 8]
008cdf05 or ecx, dword ptr [eax + 0xc]
008cdf08 je 0x8ce871
008cdf0e cmp byte ptr [ebp - 0xa5], 0
008cdf15 jne 0x8ce871
008cdf1b movss xmm0, dword ptr [edi + 0x2a4]
008cdf23 mulss xmm0, dword ptr [0xb6a434]
008cdf2b push 0
008cdf2d push 0xbeabc8
008cdf32 push 0xbeab18
008cdf37 movss dword ptr [ebp - 0xac], xmm0
008cdf3f movss xmm0, dword ptr [edi + 0x2a8]
008cdf47 mulss xmm0, dword ptr [0xb6a434]
008cdf4f push 0
008cdf51 push dword ptr [edi + 0x438]
008cdf57 movss dword ptr [ebp - 0xcc], xmm0
008cdf5f call 0x9ec34c
008cdf64 mov edx, dword ptr [edi + 0x3d0]
008cdf6a add esp, 0x14
008cdf6d mov ecx, dword ptr [edi + 0x3d4]
008cdf73 sub ecx, edx
008cdf75 mov dword ptr [ebp - 0xc4], eax
008cdf7b sar ecx, 3
008cdf7e movss xmm1, dword ptr [edx + ecx*8 - 8]
008cdf84 movss dword ptr [ebp - 0x138], xmm1
008cdf8c movss xmm0, dword ptr [edx + ecx*8 - 4]
008cdf92 movss dword ptr [ebp - 0x134], xmm0
008cdf9a subss xmm0, dword ptr [edx + 4]
008cdf9f subss xmm1, dword ptr [edx]
008cdfa3 mulss xmm0, xmm0
008cdfa7 mulss xmm1, xmm1
008cdfab addss xmm0, xmm1
008cdfaf call 0x4228c0
008cdfb4 movss dword ptr [ebp - 0xb4], xmm0
008cdfbc xor esi, esi
008cdfbe movss xmm0, dword ptr [0xc02fec]
008cdfc6 movss dword ptr [ebp - 0xa0], xmm0
008cdfce movss xmm0, dword ptr [0xc02ff0]
008cdfd6 movss dword ptr [ebp - 0xa4], xmm0
008cdfde nop 
008cdfe0 movd xmm0, esi
008cdfe4 cvtdq2ps xmm0, xmm0
008cdfe7 mulss xmm0, dword ptr [0xb6a230]
008cdfef movss dword ptr [ebp - 0x9c], xmm0
008cdff7 call 0x412010
008cdffc movss dword ptr [ebp - 0xb0], xmm0
008ce004 movss xmm0, dword ptr [ebp - 0x9c]
008ce00c call 0x411fe0
008ce011 mov edx, dword ptr [edi + 0x3d0]
008ce017 sub esp, 0xc
008ce01a mov ecx, dword ptr [edi + 0x3d4]
008ce020 xorps xmm3, xmm3
008ce023 mulss xmm0, dword ptr [0xb6a9c8]
008ce02b sub ecx, edx
008ce02d sar ecx, 3
008ce030 mov dword ptr [esp + 8], 0
008ce038 mov dword ptr [esp + 4], 0
008ce040 mov dword ptr [esp], 0
008ce047 mov eax, dword ptr [edx + ecx*8 - 8]
008ce04b mov ecx, dword ptr [edx + ecx*8 - 4]
008ce04f mov dword ptr [ebp - 0xf0], eax
008ce055 lea eax, [ebp - 0xf0]
008ce05b push eax
008ce05c movss dword ptr [ebp - 0xfc], xmm0
008ce064 lea eax, [ebp - 0x118]
008ce06a movss xmm0, dword ptr [ebp - 0xb0]
008ce072 mulss xmm0, dword ptr [0xb6a9c8]
008ce07a push eax
008ce07b mov eax, dword ptr [0xbfd65c]
008ce080 mov dword ptr [ebp - 0xec], ecx
008ce086 movss dword ptr [ebp - 0xb0], xmm0
008ce08e mov ecx, dword ptr [eax + 0x18190]
008ce094 call 0x7cec10
008ce099 movss xmm2, dword ptr [ebp - 0x114]
008ce0a1 addss xmm2, dword ptr [ebp - 0xb0]
008ce0a9 movss xmm0, dword ptr [ebp - 0x118]
008ce0b1 addss xmm0, dword ptr [ebp - 0xfc]
008ce0b9 movss xmm1, dword ptr [ebp - 0xac]
008ce0c1 mov eax, dword ptr [0xbfd65c]
008ce0c6 addss xmm2, dword ptr [ebp - 0xcc]
008ce0ce addss xmm1, xmm0
008ce0d2 mov ecx, dword ptr [eax + 0x18190]
008ce0d8 movss dword ptr [ebp - 0xd4], xmm2
008ce0e0 push dword ptr [ebp - 0xd4]
008ce0e6 movss dword ptr [ebp - 0xd8], xmm1
008ce0ee push dword ptr [ebp - 0xd8]
008ce0f4 call 0x7aee40
008ce0f9 mov ecx, dword ptr [edi + 0x17c]
008ce0ff mov edx, eax
008ce101 call 0x6dc5a0
008ce106 movss xmm2, dword ptr [ebp - 0xa0]
008ce10e movss xmm1, dword ptr [ebp - 0xa4]
008ce116 test al, al
008ce118 je 0x8ce13a
008ce11a addss xmm2, dword ptr [ebp - 0xfc]
008ce122 addss xmm1, dword ptr [ebp - 0xb0]
008ce12a movss dword ptr [ebp - 0xa0], xmm2
008ce132 movss dword ptr [ebp - 0xa4], xmm1
008ce13a add esi, 6
008ce13d cmp esi, 0x168
008ce143 jl 0x8cdfe0
008ce149 mov eax, dword ptr [edi + 0x3d0]
008ce14f mov ecx, dword ptr [edi + 0x3d4]
008ce155 sub ecx, eax
008ce157 sar ecx, 3
008ce15a movss xmm0, dword ptr [eax + ecx*8 - 8]
008ce160 subss xmm0, dword ptr [eax + ecx*8 - 0x10]
008ce166 movss dword ptr [ebp - 0x10c], xmm0
008ce16e movss xmm0, dword ptr [eax + ecx*8 - 4]
008ce174 subss xmm0, dword ptr [eax + ecx*8 - 0xc]
008ce17a movss dword ptr [ebp - 0xfc], xmm0
008ce182 movaps xmm0, xmm1
008ce185 mulss xmm0, xmm1
008ce189 movaps xmm1, xmm2
008ce18c mulss xmm1, xmm2
008ce190 addss xmm0, xmm1
008ce194 call 0x4228c0
008ce199 comiss xmm0, dword ptr [0xb6a18c]
008ce1a0 mov esi, dword ptr [ebp - 0xc4]
008ce1a6 jbe 0x8ce1d7
008ce1a8 movss xmm1, dword ptr [0xb6a614]
008ce1b0 divss xmm1, xmm0
008ce1b4 movaps xmm0, xmm1
008ce1b7 mulss xmm1, dword ptr [ebp - 0xa4]
008ce1bf mulss xmm0, dword ptr [ebp - 0xa0]
008ce1c7 movss dword ptr [ebp - 0xa4], xmm1
008ce1cf movss dword ptr [ebp - 0xa0], xmm0
008ce1d7 mov eax, dword ptr [edi + 0x314]
008ce1dd test eax, eax
008ce1df je 0x8ce29e
008ce1e5 cmp dword ptr [eax + 0x28], 0x104
008ce1ec jne 0x8ce29e
008ce1f2 cmp dword ptr [eax + 0x30], 2
008ce1f6 jne 0x8ce29e
008ce1fc movss xmm1, dword ptr [edi + 0x294]
008ce204 movss xmm0, dword ptr [edi + 0x298]
008ce20c subss xmm0, dword ptr [ebp - 0x134]
008ce214 subss xmm1, dword ptr [ebp - 0x138]
008ce21c mulss xmm0, xmm0
008ce220 mulss xmm1, xmm1
008ce224 addss xmm0, xmm1
008ce228 call 0x4228c0
008ce22d xorps xmm1, xmm1
008ce230 movss dword ptr [ebp - 0xac], xmm0
008ce238 comiss xmm1, xmm0
008ce23b lea eax, [ebp - 0xac]
008ce241 mov dword ptr [ebp - 0x9c], 0
008ce24b lea ecx, [ebp - 0x9c]
008ce251 mov dword ptr [ebp - 0xcc], 0x437a0000
008ce25b cmovbe ecx, eax
008ce25e lea eax, [ebp - 0xcc]
008ce264 movss xmm0, dword ptr [ecx]
008ce268 comiss xmm0, dword ptr [0xb6abec]
008ce26f movss xmm0, dword ptr [0xb6a614]
008ce277 cmovbe eax, ecx
008ce27a movss xmm1, dword ptr [eax]
008ce27e divss xmm1, dword ptr [0xb6abec]
008ce286 subss xmm0, xmm1
008ce28a movss xmm1, dword ptr [ebp - 0xc8]
008ce292 subss xmm1, xmm0
008ce296 movss dword ptr [ebp - 0xc8], xmm1
008ce29e movss xmm5, dword ptr [ebp - 0xfc]
008ce2a6 movss xmm4, dword ptr [ebp - 0x10c]
008ce2ae movaps xmm1, xmm5
008ce2b1 movss xmm3, dword ptr [ebp - 0xa4]
008ce2b9 movaps xmm0, xmm4
008ce2bc movss xmm2, dword ptr [ebp - 0xa0]
008ce2c4 mulss xmm1, xmm3
008ce2c8 mulss xmm0, xmm2
008ce2cc addss xmm1, xmm0
008ce2d0 mulss xmm2, xmm1
008ce2d4 mulss xmm3, xmm1
008ce2d8 mulss xmm2, dword ptr [ebp - 0xc8]
008ce2e0 mulss xmm3, dword ptr [ebp - 0xc8]
008ce2e8 subss xmm4, xmm2
008ce2ec subss xmm5, xmm3
008ce2f0 movaps xmm1, xmm4
008ce2f3 movaps xmm0, xmm5
008ce2f6 call 0x447a80
008ce2fb movaps xmm1, xmm0
008ce2fe mulss xmm1, dword ptr [0xb6aa84]
008ce306 movss dword ptr [ebp - 0xac], xmm1
008ce30e test esi, esi
008ce310 jne 0x8ce762
008ce316 movss xmm2, dword ptr [ebp - 0xa0]
008ce31e ucomiss xmm2, dword ptr [0xc02fec]
008ce325 lahf 
008ce326 test ah, 0x44
008ce329 jp 0x8ce344
008ce32b movss xmm0, dword ptr [ebp - 0xa4]
008ce333 ucomiss xmm0, dword ptr [0xc02ff0]
008ce33a lahf 
008ce33b test ah, 0x44
008ce33e jnp 0x8ce888
008ce344 push 1
008ce346 push dword ptr [edi + 0x314]
008ce34c lea eax, [edi + 0x2a4]
008ce352 push eax
008ce353 push dword ptr [edi + 0x3a8]
008ce359 lea eax, [ebp - 0x138]
008ce35f push ecx
008ce360 movss dword ptr [esp], xmm1
008ce365 push eax
008ce366 push dword ptr [edi + 0x2c]
008ce369 call 0x8c7550
008ce36e mov esi, eax
008ce370 add esp, 0x1c
008ce373 mov dword ptr [ebp - 0xc4], esi
008ce379 test esi, esi
008ce37b je 0x8ce888
008ce381 mov ecx, dword ptr [edi + 0x438]
008ce387 lea eax, [edi + 0x438]
008ce38d test ecx, ecx
008ce38f je 0x8ce3af
008ce391 mov dword ptr [ebp - 0x9c], eax
008ce397 add ecx, 0x324
008ce39d lea eax, [ebp - 0x9c]
008ce3a3 push eax
008ce3a4 call 0x4bc3c0
008ce3a9 lea eax, [edi + 0x438]
008ce3af push eax
008ce3b0 mov ecx, esi
008ce3b2 mov dword ptr [eax], esi
008ce3b4 call 0x4bae70
008ce3b9 push 1
008ce3bb push edi
008ce3bc mov ecx, esi
008ce3be mov byte ptr [esi + 0x434], 1
008ce3c5 mov byte ptr [esi + 0x468], 1
008ce3cc call 0x8c72b0
008ce3d1 mov ecx, dword ptr [esi + 0x47c]
008ce3d7 lea eax, [esi + 0x47c]
008ce3dd cmp ecx, edi
008ce3df je 0x8ce40d
008ce3e1 test ecx, ecx
008ce3e3 je 0x8ce403
008ce3e5 mov dword ptr [ebp - 0x9c], eax
008ce3eb add ecx, 0x324
008ce3f1 lea eax, [ebp - 0x9c]
008ce3f7 push eax
008ce3f8 call 0x4bc3c0
008ce3fd lea eax, [esi + 0x47c]
008ce403 push eax
008ce404 mov ecx, edi
008ce406 mov dword ptr [eax], edi
008ce408 call 0x4bae70
008ce40d cmp byte ptr [edi + 0x465], 0
008ce414 je 0x8ce712
008ce41a mov eax, dword ptr [edi + 0x314]
008ce420 mov dword ptr [ebp - 0xfc], eax
008ce426 jmp 0x8ce718
008ce42b cmp dword ptr [edi + 0x488], 0
008ce432 jne 0x8ce58e
008ce438 movss xmm1, dword ptr [ebp - 0xc4]
008ce440 movss xmm0, dword ptr [ebp - 0xa0]
008ce448 call 0x447a80
008ce44d mulss xmm0, dword ptr [0xb6aa84]
008ce455 lea eax, [ebp - 0xf0]
008ce45b push 1
008ce45d push dword ptr [edi + 0x314]
008ce463 push esi
008ce464 push dword ptr [edi + 0x3a8]
008ce46a push ecx
008ce46b movss dword ptr [esp], xmm0
008ce470 push eax
008ce471 push dword ptr [edi + 0x2c]
008ce474 call 0x8c7550
008ce479 mov ecx, dword ptr [edi + 0x488]
008ce47f lea esi, [edi + 0x488]
008ce485 add esp, 0x1c
008ce488 mov dword ptr [ebp - 0xac], eax
008ce48e cmp ecx, eax
008ce490 je 0x8ce4cc
008ce492 test ecx, ecx
008ce494 je 0x8ce4b4
008ce496 lea eax, [ebp - 0x9c]
008ce49c mov dword ptr [ebp - 0x9c], esi
008ce4a2 push eax
008ce4a3 add ecx, 0x324
008ce4a9 call 0x4bc3c0
008ce4ae mov eax, dword ptr [ebp - 0xac]
008ce4b4 mov dword ptr [esi], eax
008ce4b6 test eax, eax
008ce4b8 je 0x8ce58e
008ce4be push esi
008ce4bf mov ecx, eax
008ce4c1 call 0x4bae70
008ce4c6 mov ecx, dword ptr [edi + 0x488]
008ce4cc test ecx, ecx
008ce4ce je 0x8ce58e
008ce4d4 mov byte ptr [ecx + 0x468], 1
008ce4db mov eax, dword ptr [esi]
008ce4dd push 1
008ce4df push edi
008ce4e0 mov byte ptr [eax + 0x434], 1
008ce4e7 mov ecx, dword ptr [esi]
008ce4e9 call 0x8c72b0
008ce4ee mov eax, dword ptr [esi]
008ce4f0 add eax, 0x47c
008ce4f5 mov dword ptr [ebp - 0xac], eax
008ce4fb mov ecx, dword ptr [eax]
008ce4fd cmp ecx, edi
008ce4ff je 0x8ce52d
008ce501 test ecx, ecx
008ce503 je 0x8ce523
008ce505 mov dword ptr [ebp - 0x9c], eax
008ce50b add ecx, 0x324
008ce511 lea eax, [ebp - 0x9c]
008ce517 push eax
008ce518 call 0x4bc3c0
008ce51d mov eax, dword ptr [ebp - 0xac]
008ce523 push eax
008ce524 mov ecx, edi
008ce526 mov dword ptr [eax], edi
008ce528 call 0x4bae70
008ce52d cmp byte ptr [edi + 0x465], 0
008ce534 je 0x8ce544
008ce536 mov eax, dword ptr [edi + 0x314]
008ce53c mov dword ptr [ebp - 0xfc], eax
008ce542 jmp 0x8ce54a
008ce544 mov dword ptr [ebp - 0xfc], edi
008ce54a mov esi, dword ptr [esi]
008ce54c add esi, 0x314
008ce552 mov ecx, dword ptr [esi]
008ce554 test ecx, ecx
008ce556 je 0x8ce570
008ce558 lea eax, [ebp - 0x9c]
008ce55e mov dword ptr [ebp - 0x9c], esi
008ce564 push eax
008ce565 add ecx, 0x324
008ce56b call 0x4bc3c0
008ce570 mov eax, dword ptr [ebp - 0xfc]
008ce576 mov dword ptr [esi], eax
008ce578 test eax, eax
008ce57a je 0x8ce584
008ce57c push esi
008ce57d mov ecx, eax
008ce57f call 0x4bae70
008ce584 mov dword ptr [edi + 0x4b0], 0
008ce58e mov ecx, dword ptr [edi + 0x488]
008ce594 test ecx, ecx
008ce596 je 0x8cded3
008ce59c push 0
008ce59e push edi
008ce59f call 0x8c72b0
008ce5a4 mov esi, dword ptr [edi + 0x488]
008ce5aa lea eax, [ebp - 0x130]
008ce5b0 push eax
008ce5b1 mov ecx, 0xbc4940
008ce5b6 call 0x57f3a0
008ce5bb push eax
008ce5bc lea edx, [esi + 0x378]
008ce5c2 lea ecx, [ebp - 0xe0]
008ce5c8 call 0x412050
008ce5cd movss xmm1, dword ptr [ebp - 0xc4]
008ce5d5 add esp, 4
008ce5d8 movss xmm0, dword ptr [ebp - 0xa0]
008ce5e0 movups xmm2, xmmword ptr [eax]
008ce5e3 movups xmmword ptr [esi + 0x378], xmm2
008ce5ea mov eax, dword ptr [edi + 0x488]
008ce5f0 movss xmm2, dword ptr [ebp - 0xf0]
008ce5f8 movss dword ptr [eax + 0x294], xmm2
008ce600 movss xmm2, dword ptr [ebp - 0xec]
008ce608 movss dword ptr [eax + 0x298], xmm2
008ce610 call 0x447a80
008ce615 mov ecx, dword ptr [edi + 0x488]
008ce61b xorps xmm1, xmm1
008ce61e mulss xmm0, dword ptr [0xb6aa84]
008ce626 mov eax, dword ptr [ecx + 0x36c]
008ce62c movss dword ptr [ecx + 0x368], xmm0
008ce634 movss dword ptr [ecx + 0x36c], xmm0
008ce63c subss xmm0, dword ptr [0xb6aae4]
008ce644 mov dword ptr [ecx + 0x370], eax
008ce64a movss dword ptr [ecx + 0xe0], xmm0
008ce652 movss xmm0, dword ptr [edi + 0x420]
008ce65a comiss xmm0, xmm1
008ce65d mov ecx, dword ptr [edi + 0x488]
008ce663 jbe 0x8ce69b
008ce665 subss xmm0, dword ptr [ebp - 0xcc]
008ce66d lea eax, [ebp - 0x9c]
008ce673 mov dword ptr [ebp - 0xac], 0x41200000
008ce67d lea edx, [ebp - 0xac]
008ce683 comiss xmm0, dword ptr [0xb6a974]
008ce68a movss dword ptr [ebp - 0x9c], xmm0
008ce692 cmovbe eax, edx
008ce695 movss xmm0, dword ptr [eax]
008ce699 jmp 0x8ce69e
008ce69b xorps xmm0, xmm0
008ce69e movss dword ptr [ecx + 0x420], xmm0
008ce6a6 cmp byte ptr [edi + 0x465], 0
008ce6ad je 0x8ce6cc
008ce6af mov eax, dword ptr [edi + 0x488]
008ce6b5 mov dword ptr [eax + 0x490], 2
008ce6bf mov eax, dword ptr [edi + 0x488]
008ce6c5 mov byte ptr [eax + 0x169], 0
008ce6cc mov ecx, dword ptr [edi + 0x488]
008ce6d2 cmp byte ptr [ecx + 0x3ac], 0
008ce6d9 je 0x8ce6e0
008ce6db mov eax, dword ptr [ecx]
008ce6dd call dword ptr [eax + 0xc]
008ce6e0 xor al, al
008ce6e2 mov byte ptr [ebp - 0xa5], 1
008ce6e9 mov dword ptr [ebp - 0xe8], eax
008ce6ef mov byte ptr [ebp - 0xbc], al
008ce6f5 jmp 0x8cded3
008ce6fa mov ecx, dword ptr [edi + 0x488]
008ce700 test ecx, ecx
008ce702 je 0x8cded9
008ce708 mov eax, dword ptr [ecx]
008ce70a call dword ptr [eax + 0x28]
008ce70d jmp 0x8cded9
008ce712 mov dword ptr [ebp - 0xfc], edi
008ce718 mov ecx, dword ptr [esi + 0x314]
008ce71e lea eax, [esi + 0x314]
008ce724 test ecx, ecx
008ce726 je 0x8ce746
008ce728 mov dword ptr [ebp - 0x9c], eax
008ce72e add ecx, 0x324
008ce734 lea eax, [ebp - 0x9c]
008ce73a push eax
008ce73b call 0x4bc3c0
008ce740 lea eax, [esi + 0x314]
008ce746 mov ecx, dword ptr [ebp - 0xfc]
008ce74c mov dword ptr [eax], ecx
008ce74e test ecx, ecx
008ce750 je 0x8ce758
008ce752 push eax
008ce753 call 0x4bae70
008ce758 mov dword ptr [edi + 0x4b0], 0
008ce762 push 0
008ce764 push edi
008ce765 mov ecx, esi
008ce767 call 0x8c72b0
008ce76c lea eax, [ebp - 0x130]
008ce772 mov ecx, 0xbc4c10
008ce777 push eax
008ce778 call 0x57f3a0
008ce77d push eax
008ce77e lea edx, [esi + 0x378]
008ce784 lea ecx, [ebp - 0xe0]
008ce78a call 0x412050
008ce78f mov ecx, dword ptr [ebp - 0xc4]
008ce795 xorps xmm1, xmm1
008ce798 add esp, 4
008ce79b movups xmm0, xmmword ptr [eax]
008ce79e mov eax, dword ptr [ecx + 0x36c]
008ce7a4 movups xmmword ptr [esi + 0x378], xmm0
008ce7ab movss xmm0, dword ptr [ebp - 0x138]
008ce7b3 movss dword ptr [ecx + 0x294], xmm0
008ce7bb movss xmm0, dword ptr [ebp - 0x134]
008ce7c3 movss dword ptr [ecx + 0x298], xmm0
008ce7cb movss xmm0, dword ptr [ebp - 0xac]
008ce7d3 movss dword ptr [ecx + 0x368], xmm0
008ce7db movss dword ptr [ecx + 0x36c], xmm0
008ce7e3 subss xmm0, dword ptr [0xb6aae4]
008ce7eb mov dword ptr [ecx + 0x370], eax
008ce7f1 movss dword ptr [ecx + 0xe0], xmm0
008ce7f9 movss xmm0, dword ptr [edi + 0x420]
008ce801 comiss xmm0, xmm1
008ce804 jbe 0x8ce83c
008ce806 subss xmm0, dword ptr [ebp - 0xb4]
008ce80e lea eax, [ebp - 0x9c]
008ce814 mov dword ptr [ebp - 0xac], 0x41200000
008ce81e lea edx, [ebp - 0xac]
008ce824 comiss xmm0, dword ptr [0xb6a974]
008ce82b movss dword ptr [ebp - 0x9c], xmm0
008ce833 cmovbe eax, edx
008ce836 movss xmm0, dword ptr [eax]
008ce83a jmp 0x8ce83f
008ce83c xorps xmm0, xmm0
008ce83f movss dword ptr [ecx + 0x420], xmm0
008ce847 cmp byte ptr [edi + 0x465], 0
008ce84e je 0x8ce861
008ce850 mov dword ptr [ecx + 0x490], 2
008ce85a mov byte ptr [ecx + 0x169], 0
008ce861 cmp byte ptr [ecx + 0x3ac], 0
008ce868 je 0x8ce888
008ce86a mov eax, dword ptr [ecx]
008ce86c call dword ptr [eax + 0xc]
008ce86f jmp 0x8ce888
008ce871 mov ecx, dword ptr [edi + 0x438]
008ce877 test ecx, ecx
008ce879 je 0x8ce880
008ce87b mov eax, dword ptr [ecx]
008ce87d call dword ptr [eax + 0x28]
008ce880 push ecx
008ce881 mov ecx, edi
008ce883 call 0x8d79b0
008ce888 cmp byte ptr [edi + 0x466], 0
008ce88f je 0x8ce89d
008ce891 mov dword ptr [edi + 0x4b0], 0
008ce89b jmp 0x8ce8c1
008ce89d mov eax, dword ptr [ebp - 0xe8]
008ce8a3 mov ecx, 1
008ce8a8 cmp dword ptr [edi + 0x4b0], 0
008ce8af movzx eax, al
008ce8b2 cmovg eax, ecx
008ce8b5 mov dword ptr [ebp - 0xe8], eax
008ce8bb mov byte ptr [ebp - 0xbc], al
008ce8c1 push dword ptr [ebp - 0xbc]
008ce8c7 mov ecx, edi
008ce8c9 call 0x8d8000
008ce8ce mov eax, dword ptr [edi + 0x318]
008ce8d4 xor edx, edx
008ce8d6 test eax, eax
008ce8d8 je 0x8ce929
008ce8da movss xmm1, dword ptr [eax + 0x298]
008ce8e2 addss xmm1, dword ptr [eax + 0x2a8]
008ce8ea movss xmm0, dword ptr [eax + 0x294]
008ce8f2 addss xmm0, dword ptr [eax + 0x2a4]
008ce8fa mov ecx, dword ptr [0xbfd65c]
008ce900 movss dword ptr [ebp - 0xd4], xmm1
008ce908 push dword ptr [ebp - 0xd4]
008ce90e mov ecx, dword ptr [ecx + 0x18190]
008ce914 movss dword ptr [ebp - 0xd8], xmm0
008ce91c push dword ptr [ebp - 0xd8]
008ce922 call 0x7aee40
008ce927 mov edx, eax
008ce929 mov ecx, dword ptr [edi + 0x2c]
008ce92c cmp ecx, 1
008ce92f je 0x8ce953
008ce931 cmp ecx, 6
008ce934 je 0x8ce953
008ce936 cmp ecx, 9
008ce939 je 0x8ce953
008ce93b cmp ecx, 0xb
008ce93e je 0x8ce953
008ce940 cmp ecx, 0xc
008ce943 je 0x8ce953
008ce945 cmp ecx, 0xe
008ce948 je 0x8ce953
008ce94a cmp ecx, 0xf
008ce94d jne 0x8cec06
008ce953 movss xmm0, dword ptr [edi + 0xd8]
008ce95b comiss xmm0, dword ptr [0xb6a480]
008ce962 jbe 0x8cec06
008ce968 cmp dword ptr [edi + 0x34], 1
008ce96c jne 0x8cec06
008ce972 movss xmm0, dword ptr [edi + 0x420]
008ce97a ucomiss xmm0, dword ptr [0xb6a18c]
008ce981 lahf 
008ce982 test ah, 0x44
008ce985 jnp 0x8ce998
008ce987 test edx, edx
008ce989 je 0x8cec06
008ce98f cmp edx, 1
008ce992 je 0x8cec06
008ce998 cmp byte ptr [edi + 0x16d], 0
008ce99f jne 0x8cec06
008ce9a5 mov eax, dword ptr [edi + 0x14c]
008ce9ab shr eax, 5
008ce9ae test al, 1
008ce9b0 jne 0x8cec06
008ce9b6 mov eax, dword ptr [edi + 0x3d4]
008ce9bc mov ecx, dword ptr [edi + 0x3d0]
008ce9c2 sub eax, ecx
008ce9c4 sar eax, 3
008ce9c7 cmp eax, 2
008ce9ca jb 0x8cec06
008ce9d0 movss xmm1, dword ptr [ecx + eax*8 - 0x10]
008ce9d6 movss xmm0, dword ptr [ecx + eax*8 - 0xc]
008ce9dc subss xmm1, dword ptr [ecx + eax*8 - 8]
008ce9e2 subss xmm0, dword ptr [ecx + eax*8 - 4]
008ce9e8 call 0x447a80
008ce9ed movaps xmm2, xmm0
008ce9f0 call 0x6c3d90
008ce9f5 mulss xmm2, dword ptr [0xb6aa84]
008ce9fd movd xmm1, eax
008cea01 cvtdq2pd xmm1, xmm1
008cea05 shr eax, 0x1f
008cea08 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
008cea11 cvtpd2ps xmm0, xmm1
008cea15 mulss xmm0, dword ptr [0xb6a19c]
008cea1d mulss xmm0, dword ptr [0xb6ab88]
008cea25 addss xmm0, xmm2
008cea29 subss xmm0, dword ptr [0xb6aae4]
008cea31 call 0x65a640
008cea36 movaps xmm1, xmm0
008cea39 call 0x6c3d90
008cea3e movd xmm0, eax
008cea42 cvtdq2pd xmm0, xmm0
008cea46 shr eax, 0x1f
008cea49 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cea52 cvtpd2ps xmm0, xmm0
008cea56 mulss xmm0, dword ptr [0xb6a19c]
008cea5e mulss xmm0, dword ptr [0xb6a974]
008cea66 addss xmm0, dword ptr [0xb6a614]
008cea6e movss dword ptr [ebp - 0xac], xmm0
008cea76 call 0x6c3d90
008cea7b movd xmm0, eax
008cea7f cvtdq2pd xmm0, xmm0
008cea83 shr eax, 0x1f
008cea86 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cea8f cvtpd2ps xmm0, xmm0
008cea93 mulss xmm0, dword ptr [0xb6a19c]
008cea9b mulss xmm0, dword ptr [0xb6a9c8]
008ceaa3 movss dword ptr [ebp - 0xfc], xmm0
008ceaab call 0x6c3d90
008ceab0 mulss xmm1, dword ptr [0xb6a230]
008ceab8 mov esi, eax
008ceaba movaps xmm0, xmm1
008ceabd movss dword ptr [ebp - 0x9c], xmm1
008ceac5 call 0x412010
008ceaca movss dword ptr [ebp - 0xcc], xmm0
008cead2 movss xmm0, dword ptr [ebp - 0x9c]
008ceada call 0x411fe0
008ceadf movss xmm1, dword ptr [ebp - 0xcc]
008ceae7 lea eax, [ebp - 0x118]
008ceaed mulss xmm0, dword ptr [ebp - 0xac]
008ceaf5 push eax
008ceaf6 mulss xmm1, dword ptr [ebp - 0xac]
008ceafe movss dword ptr [ebp - 0xd8], xmm0
008ceb06 movss dword ptr [ebp - 0xd4], xmm1
008ceb0e call 0x659290
008ceb13 movss xmm1, dword ptr [ebp - 0xfc]
008ceb1b add esp, 4
008ceb1e mov ecx, dword ptr [edi + 0x3d0]
008ceb24 movaps xmm0, xmm1
008ceb27 mulss xmm0, dword ptr [eax]
008ceb2b push esi
008ceb2c mulss xmm1, dword ptr [eax + 4]
008ceb31 mov eax, dword ptr [edi + 0x3d4]
008ceb37 sub eax, ecx
008ceb39 sar eax, 3
008ceb3c push 0
008ceb3e push 0
008ceb40 addss xmm0, dword ptr [ecx + eax*8 - 8]
008ceb46 addss xmm1, dword ptr [ecx + eax*8 - 4]
008ceb4c mov ecx, dword ptr [0xbfd65c]
008ceb52 lea eax, [ebp - 0xd8]
008ceb58 push eax
008ceb59 lea eax, [ebp - 0xf0]
008ceb5f push eax
008ceb60 push 0x46
008ceb62 push 0x3e8
008ceb67 movss dword ptr [ebp - 0xf0], xmm0
008ceb6f movss dword ptr [ebp - 0xec], xmm1
008ceb77 call 0x422e20
008ceb7c mov esi, eax
008ceb7e mov dword ptr [ebp - 0x9c], esi
008ceb84 mov ecx, dword ptr [edi + 0x318]
008ceb8a test ecx, ecx
008ceb8c je 0x8cebce
008ceb8e add ecx, 0x3c
008ceb91 push ecx
008ceb92 lea ecx, [ebp - 0x358]
008ceb98 call 0x402680
008ceb9d lea edx, [ebp - 0x358]
008ceba3 lea ecx, [esi + 0x3c]
008ceba6 call 0x402b00
008cebab mov ecx, edx
008cebad call 0x403130
008cebb2 call 0x6c3d90
008cebb7 xor edx, edx
008cebb9 mov ecx, 3
008cebbe div ecx
008cebc0 lea ecx, [esi + 0x3c]
008cebc3 push edx
008cebc4 push 0xb45338
008cebc9 call 0x405850
008cebce mov eax, dword ptr [edi + 0x2a4]
008cebd4 mov ecx, esi
008cebd6 push 1
008cebd8 mov dword ptr [esi + 0x2a4], eax
008cebde mov eax, dword ptr [edi + 0x2a8]
008cebe4 push 0
008cebe6 mov dword ptr [esi + 0x2a8], eax
008cebec lea eax, [edi + 0xe4]
008cebf2 mov edx, dword ptr [esi]
008cebf4 push 0xff
008cebf9 push -1
008cebfb push eax
008cebfc call dword ptr [edx + 0x38]
008cebff mov eax, dword ptr [esi]
008cec01 mov ecx, esi
008cec03 call dword ptr [eax + 0xc]
008cec06 cmp byte ptr [edi + 0x3ad], 0
008cec0d je 0x8cf7aa
008cec13 push 0xbc4bb0
008cec18 lea edx, [edi + 0x378]
008cec1e lea ecx, [ebp - 0x240]
008cec24 call 0x412050
008cec29 add esp, 4
008cec2c mov ecx, dword ptr [eax]
008cec2e or ecx, dword ptr [eax + 4]
008cec31 jne 0x8cec3f
008cec33 mov ecx, dword ptr [eax + 8]
008cec36 or ecx, dword ptr [eax + 0xc]
008cec39 je 0x8cf7aa
008cec3f push dword ptr [edi + 0x20]
008cec42 mov ecx, edi
008cec44 push 5
008cec46 call 0x684790
008cec4b test al, al
008cec4d je 0x8cf7aa
008cec53 mov ecx, dword ptr [edi + 0x3d4]
008cec59 sub esp, 0xc
008cec5c mov esi, dword ptr [0xbfd65c]
008cec62 movss xmm3, dword ptr [0xb6a9ac]
008cec6a mov eax, dword ptr [ecx - 8]
008cec6d mov ecx, dword ptr [ecx - 4]
008cec70 mov dword ptr [esp + 8], 0x41700000
008cec78 mov dword ptr [ebp - 0x110], eax
008cec7e lea eax, [ebp - 0x110]
008cec84 mov dword ptr [esp + 4], 0x41700000
008cec8c mov dword ptr [esp], 0x41700000
008cec93 push eax
008cec94 lea eax, [ebp - 0xd8]
008cec9a mov dword ptr [ebp - 0x10c], ecx
008ceca0 mov ecx, dword ptr [esi + 0x18190]
008ceca6 push eax
008ceca7 call 0x7cec10
008cecac mov eax, dword ptr [ebp - 0xd8]
008cecb2 mov ecx, dword ptr [ebp - 0xd4]
008cecb8 mov dword ptr [ebp - 0x110], eax
008cecbe mov dword ptr [ebp - 0x10c], ecx
008cecc4 call 0x6c3d90
008cecc9 push 0
008ceccb push 0xbeaaec
008cecd0 push 0xbeab18
008cecd5 push 0
008cecd7 push eax
008cecd8 push 0
008cecda push dword ptr [edi + 0x320]
008cece0 lea eax, [ebp - 0x110]
008cece6 mov ecx, esi
008cece8 push 0xc02fec
008ceced push eax
008cecee push 0x35
008cecf0 push 0x3e8
008cecf5 call 0x422e20
008cecfa push eax
008cecfb call 0x9ec34c
008ced00 movss xmm1, dword ptr [0xbc7a28]
008ced08 mov ecx, eax
008ced0a movss xmm0, dword ptr [0xbc7a2c]
008ced12 add esp, 0x14
008ced15 mulss xmm1, dword ptr [0xb6a434]
008ced1d mulss xmm0, dword ptr [0xb6a434]
008ced25 mov eax, dword ptr [ecx]
008ced27 movss dword ptr [ecx + 0xd8], xmm1
008ced2f movss dword ptr [ecx + 0xdc], xmm0
008ced37 call dword ptr [eax + 0xc]
008ced3a jmp 0x8cf7aa
008ced3f mov ecx, edi
008ced41 mov byte ptr [edi + 0x466], 0
008ced48 call 0x8c5940
008ced4d test al, al
008ced4f jne 0x8ced71
008ced51 mov eax, dword ptr [edi + 0x2c]
008ced54 cmp eax, 2
008ced57 je 0x8ced71
008ced59 cmp eax, 0xa
008ced5c je 0x8ced71
008ced5e cmp eax, 5
008ced61 je 0x8ced71
008ced63 cmp eax, 7
008ced66 je 0x8ced71
008ced68 cmp eax, 8
008ced6b jne 0x8cf7aa
008ced71 movss xmm0, dword ptr [edi + 0x2a4]
008ced79 lea eax, [edi + 0x2a4]
008ced7f addss xmm0, dword ptr [edi + 0x294]
008ced87 lea esi, [edi + 0x294]
008ced8d mov dword ptr [ebp - 0xd4], eax
008ced93 movss dword ptr [ebp - 0xbc], xmm0
008ced9b movss xmm0, dword ptr [esi + 4]
008ceda0 addss xmm0, dword ptr [eax + 4]
008ceda5 movss dword ptr [ebp - 0xa4], xmm0
008cedad movss xmm0, dword ptr [edi + 0x36c]
008cedb5 mulss xmm0, xmm2
008cedb9 movss dword ptr [ebp - 0xac], xmm0
008cedc1 call 0x412010
008cedc6 movss dword ptr [ebp - 0xcc], xmm0
008cedce movss xmm0, dword ptr [ebp - 0xac]
008cedd6 call 0x411fe0
008ceddb movss xmm5, dword ptr [ebp - 0xcc]
008cede3 movaps xmm4, xmm0
008cede6 mov eax, dword ptr [edi + 0x17c]
008cedec movss dword ptr [ebp - 0xf0], xmm4
008cedf4 movss dword ptr [ebp - 0xec], xmm5
008cedfc cmp eax, 6
008cedff jne 0x8cee87
008cee05 mulss xmm4, dword ptr [0xb6a8cc]
008cee0d lea eax, [ebp - 0xf0]
008cee13 mov ecx, dword ptr [0xbfd65c]
008cee19 mulss xmm5, dword ptr [0xb6a8cc]
008cee21 push eax
008cee22 movss xmm1, dword ptr [ebp - 0xbc]
008cee2a lea eax, [ebp - 0x118]
008cee30 movss xmm0, dword ptr [ebp - 0xa4]
008cee38 subss xmm1, xmm4
008cee3c mov ecx, dword ptr [ecx + 0x18190]
008cee42 subss xmm0, xmm5
008cee46 push eax
008cee47 lea eax, [ebp - 0x150]
008cee4d push eax
008cee4e movss dword ptr [ebp - 0x118], xmm1
008cee56 movss dword ptr [ebp - 0x114], xmm0
008cee5e call 0x7af200
008cee63 movss xmm2, dword ptr [ebp - 0xa4]
008cee6b lea esi, [edi + 0x428]
008cee71 movss xmm3, dword ptr [ebp - 0xbc]
008cee79 mov ecx, dword ptr [eax]
008cee7b mov dword ptr [esi], ecx
008cee7d movss xmm1, dword ptr [eax + 4]
008cee82 jmp 0x8cef0c
008cee87 cmp eax, 3
008cee8a jne 0x8ceed7
008cee8c lea eax, [ebp - 0xf0]
008cee92 mov ecx, edi
008cee94 push eax
008cee95 push esi
008cee96 lea eax, [ebp - 0x118]
008cee9c push eax
008cee9d call 0x8c7e90
008ceea2 movss xmm1, dword ptr [edi + 0x2a8]
008ceeaa lea esi, [edi + 0x428]
008ceeb0 movss xmm2, dword ptr [ebp - 0xa4]
008ceeb8 movss xmm3, dword ptr [ebp - 0xbc]
008ceec0 movss xmm0, dword ptr [eax]
008ceec4 addss xmm0, dword ptr [edi + 0x2a4]
008ceecc addss xmm1, dword ptr [eax + 4]
008ceed1 movss dword ptr [esi], xmm0
008ceed5 jmp 0x8cef0c
008ceed7 mulss xmm4, dword ptr [0xb6accc]
008ceedf lea esi, [edi + 0x428]
008ceee5 movss xmm3, dword ptr [ebp - 0xbc]
008ceeed mulss xmm5, dword ptr [0xb6accc]
008ceef5 movss xmm2, dword ptr [ebp - 0xa4]
008ceefd addss xmm4, xmm3
008cef01 movaps xmm1, xmm2
008cef04 addss xmm1, xmm5
008cef08 movss dword ptr [esi], xmm4
008cef0c mov eax, esi
008cef0e movss dword ptr [eax + 4], xmm1
008cef13 movss xmm6, dword ptr [edi + 0x420]
008cef1b comiss xmm6, dword ptr [0xb6a18c]
008cef22 jbe 0x8cefb7
008cef28 movss xmm4, dword ptr [esi]
008cef2c movaps xmm5, xmm1
008cef2f subss xmm4, xmm3
008cef33 movss dword ptr [ebp - 0xa0], xmm1
008cef3b subss xmm5, xmm2
008cef3f movaps xmm0, xmm4
008cef42 movaps xmm1, xmm5
008cef45 mulss xmm0, xmm4
008cef49 mulss xmm1, xmm5
008cef4d addss xmm1, xmm0
008cef51 movaps xmm0, xmm6
008cef54 mulss xmm0, xmm6
008cef58 comiss xmm1, xmm0
008cef5b jbe 0x8cefaf
008cef5d push ecx
008cef5e lea eax, [ebp - 0x138]
008cef64 movss dword ptr [esp], xmm6
008cef69 push eax
008cef6a lea ecx, [ebp - 0xf0]
008cef70 movss dword ptr [ebp - 0xf0], xmm4
008cef78 movss dword ptr [ebp - 0xec], xmm5
008cef80 call 0x9628d0
008cef85 movss xmm3, dword ptr [ebp - 0xbc]
008cef8d movss xmm2, dword ptr [ebp - 0xa4]
008cef95 movaps xmm0, xmm3
008cef98 movaps xmm1, xmm2
008cef9b addss xmm0, dword ptr [eax]
008cef9f addss xmm1, dword ptr [eax + 4]
008cefa4 movss dword ptr [esi], xmm0
008cefa8 movss dword ptr [esi + 4], xmm1
008cefad jmp 0x8cefb7
008cefaf movss xmm1, dword ptr [ebp - 0xa0]
008cefb7 mov eax, dword ptr [edi + 0x2c]
008cefba cmp eax, 6
008cefbd je 0x8cefc4
008cefbf cmp eax, 0xf
008cefc2 jne 0x8cefcd
008cefc4 cmp dword ptr [edi + 0x34], 0x112
008cefcb je 0x8cefd6
008cefcd cmp eax, 0xd
008cefd0 jne 0x8cf053
008cefd6 movss xmm4, dword ptr [esi]
008cefda subss xmm1, xmm2
008cefde subss xmm4, xmm3
008cefe2 movaps xmm0, xmm1
008cefe5 movss dword ptr [ebp - 0xa0], xmm1
008cefed mulss xmm0, xmm1
008ceff1 movaps xmm1, xmm4
008ceff4 mulss xmm1, xmm4
008ceff8 movss dword ptr [ebp - 0xfc], xmm4
008cf000 addss xmm0, xmm1
008cf004 call 0x4228c0
008cf009 movss xmm2, dword ptr [ebp - 0xfc]
008cf011 xorps xmm3, xmm3
008cf014 comiss xmm0, xmm3
008cf017 jbe 0x8cf037
008cf019 movss xmm1, dword ptr [0xb6aafc]
008cf021 divss xmm1, xmm0
008cf025 movss xmm0, dword ptr [ebp - 0xa0]
008cf02d mulss xmm2, xmm1
008cf031 mulss xmm0, xmm1
008cf035 jmp 0x8cf03f
008cf037 movss xmm0, dword ptr [ebp - 0xa0]
008cf03f addss xmm2, dword ptr [esi]
008cf043 addss xmm0, dword ptr [esi + 4]
008cf048 movss dword ptr [esi], xmm2
008cf04c movss dword ptr [esi + 4], xmm0
008cf051 jmp 0x8cf056
008cf053 xorps xmm3, xmm3
008cf056 mov eax, dword ptr [edi + 0x34]
008cf059 cmp eax, 1
008cf05c je 0x8cf75f
008cf062 cmp eax, 3
008cf065 je 0x8cf75f
008cf06b xor eax, eax
008cf06d movss dword ptr [ebp - 0xa0], xmm3
008cf075 push eax
008cf076 push eax
008cf077 push -1
008cf079 push 0xbc
008cf07e mov dword ptr [ebp - 0xb0], eax
008cf084 xorps xmm0, xmm0
008cf087 push 0x3e8
008cf08c lea eax, [ebp - 0x130]
008cf092 movss dword ptr [ebp - 0xb4], xmm0
008cf09a push eax
008cf09b mov eax, dword ptr [0xbfd65c]
008cf0a0 mov ecx, dword ptr [eax + 0x18190]
008cf0a6 add ecx, 0x1218
008cf0ac call 0x415ed0
008cf0b1 xor eax, eax
008cf0b3 mov dword ptr [ebp - 4], 0
008cf0ba mov dword ptr [ebp - 0xac], eax
008cf0c0 cmp dword ptr [ebp - 0x124], eax
008cf0c6 jbe 0x8cf732
008cf0cc nop dword ptr [eax]
008cf0d0 mov ecx, dword ptr [ebp - 0x12c]
008cf0d6 mov eax, dword ptr [ecx + eax*4]
008cf0d9 mov dword ptr [ebp - 0xfc], eax
008cf0df test eax, eax
008cf0e1 je 0x8cf413
008cf0e7 cmp dword ptr [eax + 0x28], 0x3e8
008cf0ee jne 0x8cf413
008cf0f4 movss xmm0, dword ptr [eax + 0x3c4]
008cf0fc mulss xmm0, dword ptr [0xb6a230]
008cf104 movss dword ptr [ebp - 0xcc], xmm0
008cf10c call 0x412010
008cf111 movss dword ptr [ebp - 0xc8], xmm0
008cf119 movss xmm0, dword ptr [ebp - 0xcc]
008cf121 call 0x411fe0
008cf126 movss xmm7, dword ptr [ebp - 0xbc]
008cf12e movaps xmm3, xmm0
008cf131 movss xmm0, dword ptr [esi]
008cf135 movss xmm1, dword ptr [esi + 4]
008cf13a subss xmm0, xmm7
008cf13e movss xmm6, dword ptr [ebp - 0xa4]
008cf146 movss xmm2, dword ptr [ebp - 0xc8]
008cf14e subss xmm1, xmm6
008cf152 movss dword ptr [ebp - 0xcc], xmm3
008cf15a movss dword ptr [ebp - 0x14c], xmm0
008cf162 mulss xmm0, xmm3
008cf166 mulss xmm1, xmm2
008cf16a addss xmm1, xmm0
008cf16e xorps xmm0, xmm0
008cf171 comiss xmm1, xmm0
008cf174 jae 0x8cf423
008cf17a mov eax, dword ptr [ebp - 0xfc]
008cf180 movaps xmm0, xmm3
008cf183 mulss xmm0, dword ptr [0xb6a9c8]
008cf18b movaps xmm1, xmm2
008cf18e mulss xmm1, dword ptr [0xb6a9c8]
008cf196 movss xmm2, dword ptr [eax + 0x294]
008cf19e movss xmm3, dword ptr [eax + 0x298]
008cf1a6 addss xmm2, xmm0
008cf1aa movss xmm0, dword ptr [0xb6a704]
008cf1b2 addss xmm3, xmm1
008cf1b6 movss dword ptr [ebp - 0xc4], xmm2
008cf1be movss dword ptr [ebp - 0x15c], xmm3
008cf1c6 call 0x411fe0
008cf1cb movss dword ptr [ebp - 0x10c], xmm0
008cf1d3 movss xmm0, dword ptr [0xb6a704]
008cf1db call 0x412010
008cf1e0 movss xmm3, dword ptr [ebp - 0x10c]
008cf1e8 movaps xmm1, xmm0
008cf1eb mulss xmm0, dword ptr [ebp - 0xcc]
008cf1f3 movaps xmm2, xmm3
008cf1f6 mov eax, dword ptr [ebp - 0xfc]
008cf1fc mulss xmm3, dword ptr [ebp - 0xc8]
008cf204 mulss xmm1, dword ptr [ebp - 0xc8]
008cf20c movss xmm6, dword ptr [eax + 0x2c8]
008cf214 addss xmm3, xmm0
008cf218 movss xmm5, dword ptr [ebp - 0x15c]
008cf220 movaps xmm4, xmm6
008cf223 mulss xmm2, dword ptr [ebp - 0xcc]
008cf22b movss xmm7, dword ptr [ebp - 0xbc]
008cf233 mulss xmm6, xmm3
008cf237 movaps xmm0, xmm7
008cf23a movss xmm3, dword ptr [ebp - 0xc4]
008cf242 subss xmm2, xmm1
008cf246 subss xmm0, dword ptr [esi]
008cf24a subss xmm5, xmm6
008cf24e addss xmm6, dword ptr [ebp - 0x15c]
008cf256 mulss xmm4, xmm2
008cf25a movss xmm2, dword ptr [edi + 0x42c]
008cf262 movaps xmm1, xmm5
008cf265 subss xmm1, xmm6
008cf269 movss dword ptr [ebp - 0x114], xmm6
008cf271 movss xmm6, dword ptr [ebp - 0xa4]
008cf279 subss xmm3, xmm4
008cf27d addss xmm4, dword ptr [ebp - 0xc4]
008cf285 movss dword ptr [ebp - 0x15c], xmm0
008cf28d movss dword ptr [ebp - 0xec], xmm5
008cf295 movss dword ptr [ebp - 0xfc], xmm1
008cf29d movaps xmm1, xmm6
008cf2a0 subss xmm1, xmm2
008cf2a4 movss dword ptr [ebp - 0x134], xmm3
008cf2ac movss dword ptr [ebp - 0xc4], xmm1
008cf2b4 movaps xmm1, xmm3
008cf2b7 subss xmm1, xmm4
008cf2bb movss dword ptr [ebp - 0x10c], xmm1
008cf2c3 movaps xmm1, xmm0
008cf2c6 movss xmm0, dword ptr [ebp - 0xc4]
008cf2ce mulss xmm1, dword ptr [ebp - 0xfc]
008cf2d6 mulss xmm0, dword ptr [ebp - 0x10c]
008cf2de subss xmm1, xmm0
008cf2e2 movaps xmm0, xmm1
008cf2e5 movss dword ptr [ebp - 0x144], xmm1
008cf2ed andps xmm0, xmmword ptr [0xb6c980]
008cf2f4 movss xmm1, dword ptr [0xb6a1b0]
008cf2fc comiss xmm1, xmm0
008cf2ff jae 0x8cf423
008cf305 movaps xmm1, xmm7
008cf308 subss xmm1, xmm3
008cf30c movaps xmm3, xmm6
008cf30f subss xmm3, xmm5
008cf313 movaps xmm5, xmm1
008cf316 mulss xmm1, dword ptr [ebp - 0xc4]
008cf31e movaps xmm0, xmm3
008cf321 mulss xmm5, dword ptr [ebp - 0xfc]
008cf329 mulss xmm3, dword ptr [ebp - 0x15c]
008cf331 mulss xmm0, dword ptr [ebp - 0x10c]
008cf339 subss xmm3, xmm1
008cf33d subss xmm5, xmm0
008cf341 xorps xmm0, xmm0
008cf344 xorps xmm3, xmmword ptr [0xb6c9b0]
008cf34b divss xmm3, dword ptr [ebp - 0x144]
008cf353 divss xmm5, dword ptr [ebp - 0x144]
008cf35b comiss xmm3, xmm0
008cf35e jb 0x8cf423
008cf364 movss xmm1, dword ptr [0xb6a614]
008cf36c comiss xmm1, xmm3
008cf36f jb 0x8cf423
008cf375 comiss xmm5, xmm0
008cf378 jb 0x8cf423
008cf37e comiss xmm1, xmm5
008cf381 jb 0x8cf423
008cf387 comiss xmm5, xmm3
008cf38a jbe 0x8cf39d
008cf38c movaps xmm4, xmm5
008cf38f mulss xmm4, dword ptr [ebp - 0x14c]
008cf397 addss xmm4, xmm7
008cf39b jmp 0x8cf3b1
008cf39d subss xmm4, dword ptr [ebp - 0x134]
008cf3a5 mulss xmm4, xmm3
008cf3a9 addss xmm4, dword ptr [ebp - 0x134]
008cf3b1 jbe 0x8cf3c1
008cf3b3 subss xmm2, xmm6
008cf3b7 mulss xmm2, xmm5
008cf3bb addss xmm2, xmm6
008cf3bf jmp 0x8cf3dd
008cf3c1 movss xmm2, dword ptr [ebp - 0x114]
008cf3c9 subss xmm2, dword ptr [ebp - 0xec]
008cf3d1 mulss xmm2, xmm3
008cf3d5 addss xmm2, dword ptr [ebp - 0xec]
008cf3dd movss xmm5, dword ptr [ebp - 0xcc]
008cf3e5 mov ecx, eax
008cf3e7 movss dword ptr [edi + 0x42c], xmm2
008cf3ef movss xmm2, dword ptr [ebp - 0xc8]
008cf3f7 movss dword ptr [esi], xmm4
008cf3fb mov dword ptr [ebp - 0xb0], ecx
008cf401 movss dword ptr [ebp - 0xa0], xmm5
008cf409 movss dword ptr [ebp - 0xb4], xmm2
008cf411 jmp 0x8cf439
008cf413 movss xmm7, dword ptr [ebp - 0xbc]
008cf41b movss xmm6, dword ptr [ebp - 0xa4]
008cf423 mov ecx, dword ptr [ebp - 0xb0]
008cf429 movss xmm2, dword ptr [ebp - 0xb4]
008cf431 movss xmm5, dword ptr [ebp - 0xa0]
008cf439 mov eax, dword ptr [ebp - 0xac]
008cf43f inc eax
008cf440 mov dword ptr [ebp - 0xac], eax
008cf446 cmp eax, dword ptr [ebp - 0x124]
008cf44c jb 0x8cf0d0
008cf452 test ecx, ecx
008cf454 je 0x8cf732
008cf45a movss xmm1, dword ptr [esi]
008cf45e movaps xmm3, xmm2
008cf461 movss xmm4, dword ptr [esi + 4]
008cf466 subss xmm1, xmm7
008cf46a subss xmm4, xmm6
008cf46e addss xmm2, xmm2
008cf472 movaps xmm0, xmm1
008cf475 mulss xmm3, xmm4
008cf479 mulss xmm0, xmm5
008cf47d addss xmm5, xmm5
008cf481 movss dword ptr [ebp - 0xb4], xmm2
008cf489 addss xmm3, xmm0
008cf48d movaps xmm2, xmm3
008cf490 mulss xmm3, dword ptr [ebp - 0xb4]
008cf498 mulss xmm2, xmm5
008cf49c subss xmm4, xmm3
008cf4a0 subss xmm1, xmm2
008cf4a4 movaps xmm0, xmm4
008cf4a7 call 0x447a80
008cf4ac movaps xmm1, xmm0
008cf4af lea ecx, [ebp - 0x98]
008cf4b5 mulss xmm1, dword ptr [0xb6aa84]
008cf4bd movss dword ptr [ebp - 0xec], xmm1
008cf4c5 call 0x402120
008cf4ca mov edx, dword ptr [edi + 0x2c]
008cf4cd cmp edx, 5
008cf4d0 je 0x8cf50b
008cf4d2 cmp edx, 0xa
008cf4d5 je 0x8cf50b
008cf4d7 movaps xmm0, xmmword ptr [0xb6c610]
008cf4de lea eax, [ebp - 0x40]
008cf4e1 movups xmmword ptr [ebp - 0x40], xmm0
008cf4e5 push eax
008cf4e6 movaps xmm0, xmmword ptr [0xb6c850]
008cf4ed movups xmmword ptr [ebp - 0x30], xmm0
008cf4f1 mov dword ptr [ebp - 0x20], 0
008cf4f8 mov dword ptr [ebp - 0x1c], 0
008cf4ff mov dword ptr [ebp - 0x18], 0
008cf506 call 0x4021a0
008cf50b mov eax, dword ptr [ebp - 0xb0]
008cf511 mov eax, dword ptr [eax + 0x314]
008cf517 test eax, eax
008cf519 je 0x8cf521
008cf51b cmp dword ptr [eax + 0x28], 1
008cf51f je 0x8cf523
008cf521 xor eax, eax
008cf523 mov ecx, dword ptr [edi + 0x438]
008cf529 test ecx, ecx
008cf52b jne 0x8cf634
008cf531 mov ecx, dword ptr [ebp - 0xd4]
008cf537 movss xmm0, dword ptr [esi]
008cf53b movss xmm2, dword ptr [esi + 4]
008cf540 push 1
008cf542 subss xmm0, dword ptr [ecx]
008cf546 subss xmm2, dword ptr [ecx + 4]
008cf54b push eax
008cf54c push ecx
008cf54d push dword ptr [edi + 0x3a8]
008cf553 lea eax, [ebp - 0xd8]
008cf559 movss dword ptr [ebp - 0xd8], xmm0
008cf561 push ecx
008cf562 movss dword ptr [esp], xmm1
008cf567 push eax
008cf568 push edx
008cf569 movss dword ptr [ebp - 0xd4], xmm2
008cf571 call 0x8c7550
008cf576 add esp, 0x1c
008cf579 mov dword ptr [ebp - 0xc8], eax
008cf57f test eax, eax
008cf581 je 0x8cf722
008cf587 mov edx, dword ptr [eax]
008cf589 lea ecx, [ebp - 0x98]
008cf58f push 1
008cf591 push 0
008cf593 push 0xff
008cf598 push -1
008cf59a push ecx
008cf59b mov ecx, eax
008cf59d mov byte ptr [eax + 0x434], 1
008cf5a4 mov byte ptr [eax + 0x464], 1
008cf5ab call dword ptr [edx + 0x38]
008cf5ae mov edx, dword ptr [ebp - 0xc8]
008cf5b4 push ecx
008cf5b5 mov ecx, edx
008cf5b7 mov dword ptr [esp], 0x40e00000
008cf5be mov eax, dword ptr [edx]
008cf5c0 call dword ptr [eax + 0x3c]
008cf5c3 movss xmm0, dword ptr [edi + 0x2b0]
008cf5cb addss xmm0, dword ptr [0xb6aafc]
008cf5d3 mov ecx, dword ptr [ebp - 0xc8]
008cf5d9 movss dword ptr [ecx + 0x2b0], xmm0
008cf5e1 mov eax, dword ptr [edi + 0x3a8]
008cf5e7 mov dword ptr [ecx + 0x3a8], eax
008cf5ed cmp byte ptr [edi + 0x3ae], 0
008cf5f4 jne 0x8cf603
008cf5f6 cmp byte ptr [edi + 0x16b], 0
008cf5fd jne 0x8cf603
008cf5ff xor al, al
008cf601 jmp 0x8cf605
008cf603 mov al, 1
008cf605 mov byte ptr [ecx + 0x3ae], al
008cf60b mov eax, dword ptr [ecx]
008cf60d call dword ptr [eax + 0xc]
008cf610 mov edx, dword ptr [ebp - 0xc8]
008cf616 lea ecx, [edi + 0x438]
008cf61c call 0x68cf00
008cf621 mov al, 1
008cf623 mov byte ptr [ebp - 0xa5], al
008cf629 mov byte ptr [ebp - 0x9c], al
008cf62f jmp 0x8cf741
008cf634 push 0
008cf636 push 0xbeabc8
008cf63b push 0xbeab18
008cf640 push 0
008cf642 push ecx
008cf643 call 0x9ec34c
008cf648 add esp, 0x14
008cf64b mov dword ptr [ebp - 0xac], eax
008cf651 lea ecx, [ebp - 0x98]
008cf657 mov edx, dword ptr [eax]
008cf659 push 1
008cf65b push 0
008cf65d push 0xff
008cf662 push -1
008cf664 push ecx
008cf665 mov ecx, eax
008cf667 call dword ptr [edx + 0x38]
008cf66a mov ecx, dword ptr [ebp - 0xac]
008cf670 push ecx
008cf671 mov dword ptr [esp], 0x40e00000
008cf678 mov eax, dword ptr [ecx]
008cf67a call dword ptr [eax + 0x3c]
008cf67d movss xmm0, dword ptr [edi + 0x2b0]
008cf685 addss xmm0, dword ptr [0xb6aafc]
008cf68d mov ecx, dword ptr [ebp - 0xac]
008cf693 movss dword ptr [ecx + 0x2b0], xmm0
008cf69b mov eax, dword ptr [edi + 0x3a8]
008cf6a1 mov dword ptr [ecx + 0x3a8], eax
008cf6a7 cmp byte ptr [edi + 0x3ae], 0
008cf6ae jne 0x8cf6bd
008cf6b0 cmp byte ptr [edi + 0x16b], 0
008cf6b7 jne 0x8cf6bd
008cf6b9 xor al, al
008cf6bb jmp 0x8cf6bf
008cf6bd mov al, 1
008cf6bf movss xmm0, dword ptr [ebp - 0xec]
008cf6c7 mov byte ptr [ecx + 0x3ae], al
008cf6cd mov eax, dword ptr [ecx + 0x36c]
008cf6d3 movss dword ptr [ecx + 0x368], xmm0
008cf6db movss dword ptr [ecx + 0x36c], xmm0
008cf6e3 subss xmm0, dword ptr [0xb6aae4]
008cf6eb mov dword ptr [ecx + 0x370], eax
008cf6f1 movss dword ptr [ecx + 0xe0], xmm0
008cf6f9 movss xmm1, dword ptr [esi]
008cf6fd movss xmm0, dword ptr [esi + 4]
008cf702 subss xmm1, dword ptr [edi + 0x2a4]
008cf70a subss xmm0, dword ptr [edi + 0x2a8]
008cf712 movss dword ptr [ecx + 0x294], xmm1
008cf71a movss dword ptr [ecx + 0x298], xmm0
008cf722 mov al, 1
008cf724 mov byte ptr [ebp - 0xa5], al
008cf72a mov byte ptr [ebp - 0x9c], al
008cf730 jmp 0x8cf741
008cf732 mov ecx, dword ptr [edi + 0x438]
008cf738 test ecx, ecx
008cf73a je 0x8cf741
008cf73c mov eax, dword ptr [ecx]
008cf73e call dword ptr [eax + 0x28]
008cf741 mov dword ptr [ebp - 4], 0xffffffff
008cf748 cmp byte ptr [ebp - 0x130], 0
008cf74f jne 0x8cf75f
008cf751 push dword ptr [ebp - 0x12c]
008cf757 call 0x9eace5
008cf75c add esp, 4
008cf75f movss xmm1, dword ptr [esi]
008cf763 movss xmm0, dword ptr [esi + 4]
008cf768 subss xmm0, dword ptr [ebp - 0xa4]
008cf770 subss xmm1, dword ptr [ebp - 0xbc]
008cf778 mulss xmm0, xmm0
008cf77c mulss xmm1, xmm1
008cf780 addss xmm0, xmm1
008cf784 call 0x4228c0
008cf789 push dword ptr [ebp - 0x9c]
008cf78f mov ecx, edi
008cf791 movss dword ptr [edi + 0x3b0], xmm0
008cf799 call 0x8d8000
008cf79e mov al, byte ptr [ebp - 0xa5]
008cf7a4 mov byte ptr [ebp - 0xe8], al
008cf7aa mov ecx, dword ptr [edi + 0x314]
008cf7b0 test ecx, ecx
008cf7b2 je 0x8cf7e5
008cf7b4 cmp byte ptr [ecx + 0x16b], 0
008cf7bb je 0x8cf7e5
008cf7bd cmp dword ptr [ecx + 0x28], 0x3e8
008cf7c4 je 0x8cf7e5
008cf7c6 mov byte ptr [edi + 0x16b], 1
008cf7cd mov eax, dword ptr [ecx + 0x28]
008cf7d0 cmp eax, dword ptr [edi + 0x28]
008cf7d3 jne 0x8cf7e5
008cf7d5 cmp byte ptr [ecx + 0x16a], 0
008cf7dc jne 0x8cf7e5
008cf7de mov eax, dword ptr [edi]
008cf7e0 mov ecx, edi
008cf7e2 call dword ptr [eax + 0x28]
008cf7e5 cmp byte ptr [edi + 0x16b], 0
008cf7ec jne 0x8cf7fb
008cf7ee cmp byte ptr [edi + 0x3ae], 0
008cf7f5 je 0x8cf8f7
008cf7fb mov eax, dword ptr [edi + 0x2c]
008cf7fe cmp eax, 2
008cf801 jne 0x8cf8af
008cf807 mov eax, dword ptr [edi + 0x70]
008cf80a test eax, eax
008cf80c je 0x8cf8f0
008cf812 cmp byte ptr [eax + 0x34], 0
008cf816 je 0x8cf8a4
008cf81c lea eax, [ebp - 0x2c]
008cf81f push eax
008cf820 lea ecx, [edi + 0x6c]
008cf823 call 0x444be0
008cf828 push 4
008cf82a push 0xb43774
008cf82f lea ecx, [ebp - 0x2c]
008cf832 mov dword ptr [ebp - 4], 1
008cf839 call 0x417820
008cf83e cmp dword ptr [ebp - 0x18], 0x10
008cf842 lea eax, [ebp - 0x2c]
008cf845 push 0
008cf847 cmovae eax, dword ptr [ebp - 0x2c]
008cf84b lea ecx, [edi + 0x3c]
008cf84e push eax
008cf84f call 0x4054f0
008cf854 mov ecx, dword ptr [edi + 0x318]
008cf85a test ecx, ecx
008cf85c je 0x8cf86d
008cf85e push 0
008cf860 push 0xb3fb40
008cf865 add ecx, 0x3c
008cf868 call 0x4054f0
008cf86d test dword ptr [edi + 0x344], 0x1000
008cf877 je 0x8cf88f
008cf879 cmp dword ptr [edi + 0x70], 0
008cf87d je 0x8cf88f
008cf87f movss xmm1, dword ptr [0xb6a614]
008cf887 lea ecx, [edi + 0x6c]
008cf88a call 0x403c00
008cf88f lea ecx, [ebp - 0x2c]
008cf892 mov dword ptr [ebp - 4], 0xffffffff
008cf899 call 0x407be0
008cf89e cmp dword ptr [edi + 0x70], 0
008cf8a2 je 0x8cf8f0
008cf8a4 cmp byte ptr [edi + 0x80], 0
008cf8ab jne 0x8cf8f7
008cf8ad jmp 0x8cf8f0
008cf8af cmp eax, 0xa
008cf8b2 je 0x8cf8f0
008cf8b4 cmp eax, 4
008cf8b7 je 0x8cf8f0
008cf8b9 movss xmm1, dword ptr [edi + 0xd8]
008cf8c1 mulss xmm1, dword ptr [0xb6a5a0]
008cf8c9 dec dword ptr [edi + 0x3a8]
008cf8cf movss xmm0, dword ptr [edi + 0xdc]
008cf8d7 movss dword ptr [edi + 0xdc], xmm0
008cf8df movss dword ptr [edi + 0xd8], xmm1
008cf8e7 cmp dword ptr [edi + 0x3a8], -0x12
008cf8ee jge 0x8cf8f7
008cf8f0 mov eax, dword ptr [edi]
008cf8f2 mov ecx, edi
008cf8f4 call dword ptr [eax + 0x28]
008cf8f7 cmp byte ptr [ebp - 0xe1], 0
008cf8fe je 0x8cf913
008cf900 movss xmm1, dword ptr [0xb6a1c8]
008cf908 lea ecx, [edi + 0x3b4]
008cf90e call 0x8f8bb0
008cf913 cmp byte ptr [ebp - 0xa6], 0
008cf91a je 0x8cf923
008cf91c mov ecx, edi
008cf91e call 0x8cbe80
008cf923 cmp byte ptr [edi + 0x3ad], 0
008cf92a je 0x8d099f
008cf930 cmp byte ptr [edi + 0x16a], 0
008cf937 je 0x8d099f
008cf93d cmp byte ptr [ebp - 0xe1], 0
008cf944 je 0x8d03a9
008cf94a movss xmm0, dword ptr [edi + 0x494]
008cf952 movss dword ptr [ebp - 0xc8], xmm0
008cf95a fld dword ptr [ebp - 0xc8]
008cf960 push ecx
008cf961 fstp dword ptr [esp]
008cf964 call 0x9ec36a
008cf969 add esp, 4
008cf96c test ax, ax
008cf96f jle 0x8cf998
008cf971 cmp byte ptr [edi + 0x466], 0
008cf978 jne 0x8cf998
008cf97a mov eax, dword ptr [ebp - 0xe8]
008cf980 test al, al
008cf982 jne 0x8cf994
008cf984 mov eax, dword ptr [edi + 0x314]
008cf98a test eax, eax
008cf98c je 0x8cf998
008cf98e cmp dword ptr [eax + 0x28], 2
008cf992 jne 0x8cf998
008cf994 xor al, al
008cf996 jmp 0x8cf99a
008cf998 mov al, 1
008cf99a cmp byte ptr [ebp - 0xa6], 0
008cf9a1 mov byte ptr [ebp - 0xbd], al
008cf9a7 je 0x8cfe91
008cf9ad movss xmm3, dword ptr [edi + 0x494]
008cf9b5 movss dword ptr [ebp - 0x9c], xmm3
008cf9bd test al, al
008cf9bf je 0x8cf9e6
008cf9c1 lea eax, [edi + 0x4a0]
008cf9c7 mov ecx, edi
008cf9c9 push eax
008cf9ca lea eax, [edi + 0x498]
008cf9d0 push eax
008cf9d1 call 0x8c5e80
008cf9d6 movss xmm0, dword ptr [edi + 0x494]
008cf9de movss dword ptr [ebp - 0x9c], xmm0
008cf9e6 fld dword ptr [ebp - 0x9c]
008cf9ec push ecx
008cf9ed fstp dword ptr [esp]
008cf9f0 call 0x9ec36a
008cf9f5 add esp, 4
008cf9f8 test ax, ax
008cf9fb jle 0x8cfa13
008cf9fd cmp byte ptr [edi + 0x466], 0
008cfa04 jne 0x8cfa13
008cfa06 cmp dword ptr [edi + 0x4b0], 0
008cfa0d jne 0x8cfe91
008cfa13 push 0xbc4890
008cfa18 mov edx, 0xbc4790
008cfa1d lea ecx, [ebp - 0x220]
008cfa23 call 0x427220
008cfa28 add esp, 4
008cfa2b lea edx, [edi + 0x388]
008cfa31 lea ecx, [ebp - 0x230]
008cfa37 push eax
008cfa38 call 0x412050
008cfa3d add esp, 4
008cfa40 mov ecx, dword ptr [eax]
008cfa42 or ecx, dword ptr [eax + 4]
008cfa45 jne 0x8cfa53
008cfa47 mov ecx, dword ptr [eax + 8]
008cfa4a or ecx, dword ptr [eax + 0xc]
008cfa4d je 0x8cfe91
008cfa53 cmp byte ptr [ebp - 0xa5], 0
008cfa5a jne 0x8cfe91
008cfa60 cmp byte ptr [edi + 0x466], 0
008cfa67 jne 0x8cfe91
008cfa6d mov ecx, dword ptr [edi + 0x3d0]
008cfa73 mov eax, dword ptr [edi + 0x3d4]
008cfa79 sub eax, ecx
008cfa7b sar eax, 3
008cfa7e movss xmm0, dword ptr [ecx + eax*8 - 8]
008cfa84 movss xmm1, dword ptr [ecx + eax*8 - 4]
008cfa8a movss dword ptr [ebp - 0x134], xmm0
008cfa92 subss xmm0, dword ptr [ecx + eax*8 - 0x10]
008cfa98 movss dword ptr [ebp - 0x144], xmm1
008cfaa0 movss dword ptr [ebp - 0xd8], xmm0
008cfaa8 movaps xmm0, xmm1
008cfaab subss xmm0, dword ptr [ecx + eax*8 - 0xc]
008cfab1 lea eax, [ebp - 0x160]
008cfab7 push eax
008cfab8 lea ecx, [ebp - 0xd8]
008cfabe movss dword ptr [ebp - 0xd4], xmm0
008cfac6 call 0x962560
008cfacb movss xmm1, dword ptr [ebp - 0x160]
008cfad3 mov ecx, edi
008cfad5 movss xmm2, dword ptr [ebp - 0x15c]
008cfadd mulss xmm1, dword ptr [0xb6a9c8]
008cfae5 mulss xmm2, dword ptr [0xb6a9c8]
008cfaed movss xmm3, dword ptr [edi + 0x430]
008cfaf5 movss dword ptr [ebp - 0xcc], xmm3
008cfafd movss dword ptr [ebp - 0x9c], xmm1
008cfb05 movss dword ptr [ebp - 0x160], xmm1
008cfb0d movss dword ptr [ebp - 0xac], xmm2
008cfb15 movss dword ptr [ebp - 0x15c], xmm2
008cfb1d call 0x8c5940
008cfb22 test al, al
008cfb24 je 0x8cfbc6
008cfb2a call 0x6c3d90
008cfb2f xorps xmm0, xmm0
008cfb32 cvtsi2sd xmm0, eax
008cfb36 shr eax, 0x1f
008cfb39 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cfb42 cvtpd2ps xmm0, xmm0
008cfb46 mulss xmm0, dword ptr [0xb6a19c]
008cfb4e mulss xmm0, dword ptr [0xb6a64c]
008cfb56 addss xmm0, dword ptr [0xb6a5a4]
008cfb5e mulss xmm3, xmm0
008cfb62 movss dword ptr [ebp - 0xcc], xmm3
008cfb6a call 0x6c3d90
008cfb6f xorps xmm0, xmm0
008cfb72 cvtsi2sd xmm0, eax
008cfb76 shr eax, 0x1f
008cfb79 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cfb82 cvtpd2ps xmm0, xmm0
008cfb86 mulss xmm0, dword ptr [0xb6a19c]
008cfb8e mulss xmm0, dword ptr [0xb6a3b0]
008cfb96 addss xmm0, dword ptr [0xb6a560]
008cfb9e mulss xmm1, xmm0
008cfba2 mulss xmm2, xmm0
008cfba6 movss dword ptr [ebp - 0x9c], xmm1
008cfbae movss dword ptr [ebp - 0x160], xmm1
008cfbb6 movss dword ptr [ebp - 0xac], xmm2
008cfbbe movss dword ptr [ebp - 0x15c], xmm2
008cfbc6 lea eax, [ebp - 0xe0]
008cfbcc mov edx, 0xbc4a00
008cfbd1 push eax
008cfbd2 push ecx
008cfbd3 push 0xbc46b0
008cfbd8 push ecx
008cfbd9 push 0xbc46c0
008cfbde push ecx
008cfbdf push 0xbc4a30
008cfbe4 push ecx
008cfbe5 push 0xbc4ce0
008cfbea push ecx
008cfbeb push 0xbc49e0
008cfbf0 lea ecx, [ebp - 0xf8]
008cfbf6 call 0x427220
008cfbfb add esp, 8
008cfbfe lea ecx, [ebp - 0x120]
008cfc04 mov edx, eax
008cfc06 call 0x427220
008cfc0b add esp, 8
008cfc0e lea ecx, [ebp - 0x158]
008cfc14 mov edx, eax
008cfc16 call 0x427220
008cfc1b add esp, 8
008cfc1e lea ecx, [ebp - 0x108]
008cfc24 mov edx, eax
008cfc26 call 0x427220
008cfc2b add esp, 8
008cfc2e lea ecx, [ebp - 0x188]
008cfc34 mov edx, eax
008cfc36 call 0x427220
008cfc3b add esp, 8
008cfc3e mov ecx, eax
008cfc40 call 0x57f3a0
008cfc45 push eax
008cfc46 push ecx
008cfc47 push 0xbc4be0
008cfc4c lea edx, [edi + 0x388]
008cfc52 lea ecx, [ebp - 0x178]
008cfc58 call 0x427220
008cfc5d add esp, 8
008cfc60 lea ecx, [ebp - 0x130]
008cfc66 mov edx, eax
008cfc68 call 0x412050
008cfc6d add esp, 4
008cfc70 lea edx, [edi + 0x388]
008cfc76 lea ecx, [ebp - 0x178]
008cfc7c push 0xbc4890
008cfc81 call 0x412050
008cfc86 add esp, 4
008cfc89 mov ecx, eax
008cfc8b call 0x412090
008cfc90 movss xmm0, dword ptr [edi + 0x2c8]
008cfc98 subss xmm0, dword ptr [0xb6a910]
008cfca0 mov byte ptr [ebp - 0xa6], al
008cfca6 mov dword ptr [ebp - 0xec], 0
008cfcb0 movss dword ptr [ebp - 0x114], xmm0
008cfcb8 movss dword ptr [ebp - 0xd4], xmm0
008cfcc0 call 0x6c3d90
008cfcc5 movd xmm0, eax
008cfcc9 cvtdq2pd xmm0, xmm0
008cfccd shr eax, 0x1f
008cfcd0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cfcd9 cvtpd2ps xmm0, xmm0
008cfcdd mulss xmm0, dword ptr [0xb6a19c]
008cfce5 movss dword ptr [ebp - 0x14c], xmm0
008cfced call 0x6c3d90
008cfcf2 mov esi, eax
008cfcf4 lea eax, [ebp - 0x100]
008cfcfa push eax
008cfcfb call 0x659290
008cfd00 movss xmm0, dword ptr [ebp - 0x114]
008cfd08 lea ecx, [ebp - 0xd4]
008cfd0e movss xmm4, dword ptr [ebp - 0x134]
008cfd16 lea edx, [ebp - 0xec]
008cfd1c add esp, 4
008cfd1f comiss xmm0, dword ptr [0xb6a18c]
008cfd26 movss xmm0, dword ptr [ebp - 0x9c]
008cfd2e movss xmm2, dword ptr [eax + 4]
008cfd33 mulss xmm0, dword ptr [0xb6a50c]
008cfd3b cmovbe ecx, edx
008cfd3e movss xmm3, dword ptr [ebp - 0x14c]
008cfd46 subss xmm4, xmm0
008cfd4a cmp byte ptr [ebp - 0xa6], 0
008cfd51 movaps xmm0, xmm3
008cfd54 mulss xmm0, dword ptr [eax]
008cfd58 lea eax, [ebp - 0x160]
008cfd5e push esi
008cfd5f push 0
008cfd61 push dword ptr [edi + 0x320]
008cfd67 mulss xmm0, dword ptr [ecx]
008cfd6b push eax
008cfd6c mulss xmm3, xmm2
008cfd70 lea eax, [ebp - 0x138]
008cfd76 push eax
008cfd77 addss xmm4, xmm0
008cfd7b mov eax, 0x24
008cfd80 movss xmm0, dword ptr [ebp - 0xac]
008cfd88 mulss xmm0, dword ptr [0xb6a50c]
008cfd90 mulss xmm3, dword ptr [ecx]
008cfd94 mov ecx, 0x21
008cfd99 cmove eax, ecx
008cfd9c mov ecx, dword ptr [0xbfd65c]
008cfda2 movss dword ptr [ebp - 0x138], xmm4
008cfdaa movss xmm4, dword ptr [ebp - 0x144]
008cfdb2 subss xmm4, xmm0
008cfdb6 push eax
008cfdb7 push 2
008cfdb9 addss xmm4, xmm3
008cfdbd movss dword ptr [ebp - 0x134], xmm4
008cfdc5 call 0x422e20
008cfdca movups xmm0, xmmword ptr [ebp - 0x130]
008cfdd1 sub esp, 0x10
008cfdd4 mov esi, eax
008cfdd6 mov ecx, esp
008cfdd8 mov dword ptr [ebp - 0xc8], esi
008cfdde movups xmmword ptr [ecx], xmm0
008cfde1 mov ecx, esi
008cfde3 call 0x650280
008cfde8 mov esi, dword ptr [esi]
008cfdea lea eax, [ebp - 0x98]
008cfdf0 push 1
008cfdf2 push 0
008cfdf4 push 0xff
008cfdf9 push -1
008cfdfb push eax
008cfdfc mov ecx, edi
008cfdfe call 0x8c7070
008cfe03 mov ecx, dword ptr [ebp - 0xc8]
008cfe09 push eax
008cfe0a call dword ptr [esi + 0x38]
008cfe0d mov esi, dword ptr [ebp - 0xc8]
008cfe13 movss xmm0, dword ptr [edi + 0x2e0]
008cfe1b push ecx
008cfe1c mov ecx, esi
008cfe1e movss dword ptr [esp], xmm0
008cfe23 mov eax, dword ptr [esi]
008cfe25 call dword ptr [eax + 0x3c]
008cfe28 movss xmm0, dword ptr [ebp - 0xcc]
008cfe30 push ecx
008cfe31 mov ecx, esi
008cfe33 movss dword ptr [esp], xmm0
008cfe38 call 0x650250
008cfe3d mov eax, dword ptr [esi + 0x164]
008cfe43 mov ecx, edi
008cfe45 or dword ptr [esi + 0x160], 0x80000
008cfe4f mov dword ptr [esi + 0x164], eax
008cfe55 call 0x8c5980
008cfe5a mov dword ptr [ebp - 0xd4], eax
008cfe60 mov esi, dword ptr [eax]
008cfe62 cmp esi, dword ptr [eax + 4]
008cfe65 je 0x8cfe91
008cfe67 mov edi, dword ptr [ebp - 0xc8]
008cfe6d nop dword ptr [eax]
008cfe70 push dword ptr [esi]
008cfe72 lea ecx, [edi + 0x394]
008cfe78 call 0x422c30
008cfe7d mov eax, dword ptr [ebp - 0xd4]
008cfe83 add esi, 4
008cfe86 cmp esi, dword ptr [eax + 4]
008cfe89 jne 0x8cfe70
008cfe8b mov edi, dword ptr [ebp - 0xb8]
008cfe91 cmp byte ptr [ebp - 0xbd], 0
008cfe98 je 0x8d036d
008cfe9e push 0xbc49e0
008cfea3 lea edx, [edi + 0x388]
008cfea9 lea ecx, [ebp - 0x178]
008cfeaf call 0x412050
008cfeb4 add esp, 4
008cfeb7 mov ecx, dword ptr [eax]
008cfeb9 or ecx, dword ptr [eax + 4]
008cfebc jne 0x8cfeca
008cfebe mov ecx, dword ptr [eax + 8]
008cfec1 or ecx, dword ptr [eax + 0xc]
008cfec4 je 0x8d036d
008cfeca movss xmm0, dword ptr [edi + 0x494]
008cfed2 movss dword ptr [ebp - 0xc8], xmm0
008cfeda fld dword ptr [ebp - 0xc8]
008cfee0 push ecx
008cfee1 fstp dword ptr [esp]
008cfee4 mov dword ptr [ebp - 0x114], 0
008cfeee mov dword ptr [ebp - 0x118], 0
008cfef8 mov dword ptr [ebp - 0x14c], 0
008cff02 mov dword ptr [ebp - 0x150], 0
008cff0c movss dword ptr [ebp - 0xb8], xmm0
008cff14 call 0x9ec36a
008cff19 add esp, 4
008cff1c test ax, ax
008cff1f jg 0x8cffc4
008cff25 movss xmm0, dword ptr [edi + 0x4a8]
008cff2d movss dword ptr [ebp - 0xd4], xmm0
008cff35 fld dword ptr [ebp - 0xd4]
008cff3b push ecx
008cff3c fstp dword ptr [esp]
008cff3f call 0x9ec36a
008cff44 movss xmm0, dword ptr [ebp - 0xb8]
008cff4c add esp, 4
008cff4f test ax, ax
008cff52 jg 0x8cff75
008cff54 movss xmm1, dword ptr [edi + 0x4a8]
008cff5c subss xmm0, xmm1
008cff60 mov byte ptr [ebp - 0xa6], 1
008cff67 mulss xmm0, dword ptr [0xb6a3b0]
008cff6f addss xmm0, xmm1
008cff73 jmp 0x8cff7c
008cff75 mov byte ptr [ebp - 0xa6], 0
008cff7c movss dword ptr [edi + 0x4a8], xmm0
008cff84 comiss xmm0, dword ptr [0xb6a18c]
008cff8b ja 0x8cffdd
008cff8d mov eax, 2
008cff92 lea esi, [edi + 0x480]
008cff98 mov dword ptr [ebp - 0xb8], eax
008cff9e nop 
008cffa0 mov ecx, dword ptr [esi]
008cffa2 test ecx, ecx
008cffa4 je 0x8cffb1
008cffa6 mov eax, dword ptr [ecx]
008cffa8 call dword ptr [eax + 0x28]
008cffab mov eax, dword ptr [ebp - 0xb8]
008cffb1 add esi, 4
008cffb4 sub eax, 1
008cffb7 mov dword ptr [ebp - 0xb8], eax
008cffbd jne 0x8cffa0
008cffbf jmp 0x8d039f
008cffc4 movss xmm0, dword ptr [0xb6adc4]
008cffcc mov dword ptr [edi + 0x4a8], 0x7f800000
008cffd6 mov byte ptr [ebp - 0xa6], 0
008cffdd lea eax, [ebp - 0x150]
008cffe3 movaps xmm1, xmm0
008cffe6 push eax
008cffe7 lea eax, [ebp - 0x118]
008cffed mov ecx, edi
008cffef push eax
008cfff0 call 0x8c5bf0
008cfff5 movss xmm1, dword ptr [ebp - 0x150]
008cfffd movss xmm0, dword ptr [ebp - 0x14c]
008d0005 call 0x447a80
008d000a cmp byte ptr [ebp - 0xa6], 0
008d0011 mulss xmm0, dword ptr [0xb6aa84]
008d0019 movss dword ptr [ebp - 0x9c], xmm0
008d0021 movaps xmm1, xmm0
008d0024 je 0x8d0056
008d0026 movss xmm0, dword ptr [edi + 0x4ac]
008d002e call 0x65a6a0
008d0033 mulss xmm0, dword ptr [0xb6a434]
008d003b movss xmm1, dword ptr [ebp - 0x9c]
008d0043 movaps xmm2, xmm0
008d0046 movss xmm0, dword ptr [edi + 0x4ac]
008d004e call 0x65a950
008d0053 movaps xmm1, xmm0
008d0056 movss dword ptr [edi + 0x4ac], xmm1
008d005e mulss xmm1, dword ptr [0xb6a230]
008d0066 movaps xmm0, xmm1
008d0069 movss dword ptr [ebp - 0xd4], xmm1
008d0071 call 0x411fe0
008d0076 mulss xmm0, dword ptr [0xb6a38c]
008d007e movss xmm1, dword ptr [ebp - 0x118]
008d0086 mulss xmm0, dword ptr [edi + 0x2c8]
008d008e subss xmm1, xmm0
008d0092 movss xmm0, dword ptr [ebp - 0xd4]
008d009a movss dword ptr [ebp - 0x118], xmm1
008d00a2 call 0x412010
008d00a7 mulss xmm0, dword ptr [0xb6a38c]
008d00af xor esi, esi
008d00b1 mov dword ptr [ebp - 0xc8], esi
008d00b7 movss xmm1, dword ptr [ebp - 0x114]
008d00bf mulss xmm0, dword ptr [edi + 0x2c8]
008d00c7 subss xmm1, xmm0
008d00cb movss dword ptr [ebp - 0x114], xmm1
008d00d3 lea esi, [esi + 0x120]
008d00d9 cmp dword ptr [edi + esi*4], 0
008d00dd lea esi, [edi + esi*4]
008d00e0 jne 0x8d023a
008d00e6 push 1
008d00e8 push dword ptr [edi + 0x314]
008d00ee lea eax, [edi + 0x2a4]
008d00f4 push eax
008d00f5 push dword ptr [edi + 0x3a8]
008d00fb lea eax, [ebp - 0x118]
008d0101 push ecx
008d0102 mov dword ptr [esp], 0
008d0109 push eax
008d010a push dword ptr [edi + 0x2c]
008d010d call 0x8c7550
008d0112 mov ecx, dword ptr [esi]
008d0114 add esp, 0x1c
008d0117 mov dword ptr [ebp - 0xec], eax
008d011d cmp ecx, eax
008d011f je 0x8d0153
008d0121 test ecx, ecx
008d0123 je 0x8d0143
008d0125 lea eax, [ebp - 0xd4]
008d012b mov dword ptr [ebp - 0xd4], esi
008d0131 push eax
008d0132 add ecx, 0x324
008d0138 call 0x4bc3c0
008d013d mov eax, dword ptr [ebp - 0xec]
008d0143 mov dword ptr [esi], eax
008d0145 mov ecx, eax
008d0147 test eax, eax
008d0149 je 0x8d0153
008d014b push esi
008d014c call 0x4bae70
008d0151 mov ecx, dword ptr [esi]
008d0153 test ecx, ecx
008d0155 je 0x8d023a
008d015b mov byte ptr [ecx + 0x468], 1
008d0162 mov eax, dword ptr [esi]
008d0164 push 1
008d0166 push edi
008d0167 mov byte ptr [eax + 0x434], 1
008d016e mov ecx, dword ptr [esi]
008d0170 call 0x8c72b0
008d0175 mov eax, dword ptr [esi]
008d0177 add eax, 0x47c
008d017c mov dword ptr [ebp - 0xec], eax
008d0182 mov ecx, dword ptr [eax]
008d0184 cmp ecx, edi
008d0186 je 0x8d01b8
008d0188 test ecx, ecx
008d018a je 0x8d01aa
008d018c mov dword ptr [ebp - 0xd4], eax
008d0192 add ecx, 0x324
008d0198 lea eax, [ebp - 0xd4]
008d019e push eax
008d019f call 0x4bc3c0
008d01a4 mov eax, dword ptr [ebp - 0xec]
008d01aa mov dword ptr [eax], edi
008d01ac test edi, edi
008d01ae je 0x8d01b8
008d01b0 push eax
008d01b1 mov ecx, edi
008d01b3 call 0x4bae70
008d01b8 cmp byte ptr [edi + 0x465], 0
008d01bf je 0x8d01cf
008d01c1 mov eax, dword ptr [edi + 0x314]
008d01c7 mov dword ptr [ebp - 0xb8], eax
008d01cd jmp 0x8d01d5
008d01cf mov dword ptr [ebp - 0xb8], edi
008d01d5 mov ecx, dword ptr [esi]
008d01d7 add ecx, 0x314
008d01dd mov dword ptr [ebp - 0xec], ecx
008d01e3 mov eax, dword ptr [ecx]
008d01e5 test eax, eax
008d01e7 je 0x8d0207
008d01e9 mov dword ptr [ebp - 0xd4], ecx
008d01ef lea ecx, [ebp - 0xd4]
008d01f5 push ecx
008d01f6 lea ecx, [eax + 0x324]
008d01fc call 0x4bc3c0
008d0201 mov ecx, dword ptr [ebp - 0xec]
008d0207 mov eax, dword ptr [ebp - 0xb8]
008d020d mov dword ptr [ecx], eax
008d020f test eax, eax
008d0211 je 0x8d021b
008d0213 push ecx
008d0214 mov ecx, eax
008d0216 call 0x4bae70
008d021b movss xmm0, dword ptr [edi + 0x430]
008d0223 mov ecx, dword ptr [esi]
008d0225 mulss xmm0, dword ptr [0xb6a560]
008d022d movss dword ptr [ecx + 0x430], xmm0
008d0235 call 0x8d7d90
008d023a mov ecx, dword ptr [esi]
008d023c test ecx, ecx
008d023e je 0x8d0355
008d0244 push 0
008d0246 push edi
008d0247 call 0x8c72b0
008d024c mov esi, dword ptr [esi]
008d024e lea eax, [ebp - 0x188]
008d0254 push eax
008d0255 push ecx
008d0256 push 0xbc4c10
008d025b mov edx, 0xbc4940
008d0260 lea ecx, [ebp - 0x130]
008d0266 call 0x427220
008d026b add esp, 8
008d026e mov ecx, eax
008d0270 call 0x57f3a0
008d0275 push eax
008d0276 lea edx, [esi + 0x378]
008d027c lea ecx, [ebp - 0x158]
008d0282 call 0x412050
008d0287 add esp, 4
008d028a movups xmm0, xmmword ptr [eax]
008d028d movups xmmword ptr [esi + 0x378], xmm0
008d0294 mov esi, dword ptr [ebp - 0xc8]
008d029a movss xmm0, dword ptr [ebp - 0x118]
008d02a2 mov eax, dword ptr [edi + esi*4 + 0x480]
008d02a9 movss dword ptr [eax + 0x294], xmm0
008d02b1 movss xmm0, dword ptr [ebp - 0x114]
008d02b9 movss dword ptr [eax + 0x298], xmm0
008d02c1 test esi, esi
008d02c3 jne 0x8d02cf
008d02c5 movss xmm1, dword ptr [0xb6af48]
008d02cd jmp 0x8d02d7
008d02cf movss xmm1, dword ptr [0xb6aae4]
008d02d7 mov ecx, dword ptr [edi + esi*4 + 0x480]
008d02de movss xmm0, dword ptr [ebp - 0x9c]
008d02e6 addss xmm0, xmm1
008d02ea mov eax, dword ptr [ecx + 0x36c]
008d02f0 mov dword ptr [ecx + 0x370], eax
008d02f6 movss dword ptr [ecx + 0x368], xmm0
008d02fe movss dword ptr [ecx + 0x36c], xmm0
008d0306 subss xmm0, dword ptr [0xb6aae4]
008d030e movss dword ptr [ecx + 0xe0], xmm0
008d0316 cmp byte ptr [edi + 0x465], 0
008d031d je 0x8d033e
008d031f mov eax, dword ptr [edi + esi*4 + 0x480]
008d0326 mov dword ptr [eax + 0x490], 2
008d0330 mov eax, dword ptr [edi + esi*4 + 0x480]
008d0337 mov byte ptr [eax + 0x169], 0
008d033e mov ecx, dword ptr [edi + esi*4 + 0x480]
008d0345 cmp byte ptr [ecx + 0x3ac], 0
008d034c je 0x8d035b
008d034e mov eax, dword ptr [ecx]
008d0350 call dword ptr [eax + 0xc]
008d0353 jmp 0x8d035b
008d0355 mov esi, dword ptr [ebp - 0xc8]
008d035b inc esi
008d035c mov dword ptr [ebp - 0xc8], esi
008d0362 cmp esi, 2
008d0365 jb 0x8d00d3
008d036b jmp 0x8d03a9
008d036d mov eax, 2
008d0372 lea esi, [edi + 0x480]
008d0378 mov dword ptr [ebp - 0xb8], eax
008d037e nop 
008d0380 mov ecx, dword ptr [esi]
008d0382 test ecx, ecx
008d0384 je 0x8d0391
008d0386 mov eax, dword ptr [ecx]
008d0388 call dword ptr [eax + 0x28]
008d038b mov eax, dword ptr [ebp - 0xb8]
008d0391 add esi, 4
008d0394 sub eax, 1
008d0397 mov dword ptr [ebp - 0xb8], eax
008d039d jne 0x8d0380
008d039f mov dword ptr [edi + 0x4a8], 0x7f800000
008d03a9 mov eax, dword ptr [0xbfd65c]
008d03ae mov eax, dword ptr [eax + 0x1a30dc]
008d03b4 sub eax, dword ptr [edi + 0x280]
008d03ba cmp eax, 1
008d03bd jle 0x8d099f
008d03c3 cmp dword ptr [edi + 0x4b0], 0
008d03ca jle 0x8d099f
008d03d0 mov eax, dword ptr [edi + 0x3d4]
008d03d6 mov ecx, dword ptr [edi + 0x3d0]
008d03dc sub eax, ecx
008d03de sar eax, 3
008d03e1 cmp eax, 2
008d03e4 jb 0x8d0995
008d03ea movss xmm0, dword ptr [ecx + eax*8 - 8]
008d03f0 movss dword ptr [ebp - 0x138], xmm0
008d03f8 movss dword ptr [ebp - 0xcc], xmm0
008d0400 movss xmm0, dword ptr [ecx + eax*8 - 4]
008d0406 movss dword ptr [ebp - 0x134], xmm0
008d040e movss xmm1, dword ptr [ecx + eax*8 - 8]
008d0414 subss xmm1, dword ptr [ecx + eax*8 - 0x10]
008d041a movss xmm2, dword ptr [ecx + eax*8 - 4]
008d0420 subss xmm2, dword ptr [ecx + eax*8 - 0xc]
008d0426 movss dword ptr [ebp - 0xfc], xmm0
008d042e movaps xmm0, xmm1
008d0431 movss dword ptr [ebp - 0xb4], xmm1
008d0439 mulss xmm0, xmm1
008d043d movaps xmm1, xmm2
008d0440 movss dword ptr [ebp - 0xe8], xmm2
008d0448 mulss xmm1, xmm2
008d044c addss xmm0, xmm1
008d0450 call 0x4228c0
008d0455 comiss xmm0, dword ptr [0xb6a18c]
008d045c jbe 0x8d0491
008d045e movss xmm1, dword ptr [0xb6a614]
008d0466 divss xmm1, xmm0
008d046a movaps xmm0, xmm1
008d046d mulss xmm0, dword ptr [ebp - 0xb4]
008d0475 movss dword ptr [ebp - 0xb4], xmm0
008d047d movss xmm0, dword ptr [ebp - 0xe8]
008d0485 mulss xmm0, xmm1
008d0489 movss dword ptr [ebp - 0xe8], xmm0
008d0491 call 0x6c3d90
008d0496 movd xmm0, eax
008d049a cvtdq2pd xmm0, xmm0
008d049e shr eax, 0x1f
008d04a1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008d04aa cvtpd2ps xmm0, xmm0
008d04ae mulss xmm0, dword ptr [0xb6a19c]
008d04b6 mulss xmm0, dword ptr [0xb6aa38]
008d04be movss dword ptr [ebp - 0xb8], xmm0
008d04c6 call 0x6c3d90
008d04cb movd xmm0, eax
008d04cf cvtdq2pd xmm0, xmm0
008d04d3 shr eax, 0x1f
008d04d6 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008d04df cvtpd2ps xmm0, xmm0
008d04e3 mulss xmm0, dword ptr [0xb6a19c]
008d04eb mulss xmm0, dword ptr [0xb6a874]
008d04f3 addss xmm0, xmm0
008d04f7 movss dword ptr [ebp - 0xd4], xmm0
008d04ff call 0x411fe0
008d0504 movss xmm1, dword ptr [ebp - 0xb4]
008d050c mulss xmm0, dword ptr [ebp - 0xb8]
008d0514 mulss xmm1, dword ptr [0xb6aa3c]
008d051c addss xmm0, xmm1
008d0520 movss dword ptr [ebp - 0xa4], xmm0
008d0528 movss xmm0, dword ptr [ebp - 0xd4]
008d0530 call 0x412010
008d0535 movss xmm1, dword ptr [ebp - 0xe8]
008d053d lea edx, [edi + 0x378]
008d0543 mulss xmm0, dword ptr [ebp - 0xb8]
008d054b lea ecx, [ebp - 0xe0]
008d0551 push 0xbc4cb0
008d0556 mulss xmm1, dword ptr [0xb6aa3c]
008d055e addss xmm0, xmm1
008d0562 movss dword ptr [ebp - 0xa0], xmm0
008d056a call 0x412050
008d056f add esp, 4
008d0572 mov ecx, dword ptr [eax]
008d0574 or ecx, dword ptr [eax + 4]
008d0577 jne 0x8d0585
008d0579 mov ecx, dword ptr [eax + 8]
008d057c or ecx, dword ptr [eax + 0xc]
008d057f je 0x8d07d0
008d0585 mov eax, dword ptr [0xbfd65c]
008d058a movss xmm1, dword ptr [0xb6adb0]
008d0592 movss xmm2, dword ptr [0xc02ff0]
008d059a movss dword ptr [ebp - 0xb8], xmm1
008d05a2 movaps xmm3, xmm2
008d05a5 mov ecx, dword ptr [eax + 0x18190]
008d05ab movss xmm1, dword ptr [0xc02fec]
008d05b3 movaps xmm4, xmm1
008d05b6 movss dword ptr [ebp - 0xbc], xmm3
008d05be movss dword ptr [ebp - 0xb0], xmm4
008d05c6 mov eax, dword ptr [ecx + 0x1264]
008d05cc mov dword ptr [ebp - 0xac], eax
008d05d2 test eax, eax
008d05d4 je 0x8d06ea
008d05da mov eax, dword ptr [ecx + 0x125c]
008d05e0 mov dword ptr [ebp - 0x9c], eax
008d05e6 mov esi, dword ptr [eax]
008d05e8 mov ecx, esi
008d05ea push 0
008d05ec call 0x684630
008d05f1 test al, al
008d05f3 je 0x8d06a6
008d05f9 mov eax, dword ptr [esi + 0x160]
008d05ff and eax, 0x20000010
008d0604 or eax, 0
008d0607 jne 0x8d06a6
008d060d cmp esi, dword ptr [edi + 0x314]
008d0613 je 0x8d06a6
008d0619 movss xmm3, dword ptr [esi + 0x294]
008d0621 movss xmm0, dword ptr [esi + 0x298]
008d0629 subss xmm3, dword ptr [ebp - 0xcc]
008d0631 subss xmm0, dword ptr [ebp - 0xfc]
008d0639 movss xmm2, dword ptr [ebp - 0xe8]
008d0641 movss xmm1, dword ptr [ebp - 0xb4]
008d0649 mulss xmm1, xmm3
008d064d mulss xmm2, xmm0
008d0651 addss xmm2, xmm1
008d0655 comiss xmm2, dword ptr [0xb6a18c]
008d065c jbe 0x8d06a6
008d065e mulss xmm0, xmm0
008d0662 mulss xmm3, xmm3
008d0666 addss xmm0, xmm3
008d066a call 0x4228c0
008d066f movss xmm1, dword ptr [ebp - 0xb8]
008d0677 comiss xmm1, xmm0
008d067a jbe 0x8d06a6
008d067c movss xmm4, dword ptr [esi + 0x294]
008d0684 movss xmm3, dword ptr [esi + 0x298]
008d068c movss dword ptr [ebp - 0xb8], xmm0
008d0694 movss dword ptr [ebp - 0xb0], xmm4
008d069c movss dword ptr [ebp - 0xbc], xmm3
008d06a4 jmp 0x8d06b6
008d06a6 movss xmm3, dword ptr [ebp - 0xbc]
008d06ae movss xmm4, dword ptr [ebp - 0xb0]
008d06b6 mov eax, dword ptr [ebp - 0x9c]
008d06bc add eax, 4
008d06bf sub dword ptr [ebp - 0xac], 1
008d06c6 mov dword ptr [ebp - 0x9c], eax
008d06cc jne 0x8d05e6
008d06d2 movss xmm0, dword ptr [ebp - 0xa0]
008d06da movss xmm1, dword ptr [0xc02fec]
008d06e2 movss xmm2, dword ptr [0xc02ff0]
008d06ea ucomiss xmm4, xmm1
008d06ed lahf 
008d06ee test ah, 0x44
008d06f1 jp 0x8d0700
008d06f3 ucomiss xmm3, xmm2
008d06f6 lahf 
008d06f7 test ah, 0x44
008d06fa jnp 0x8d07d0
008d0700 movss xmm2, dword ptr [ebp - 0xa4]
008d0708 movaps xmm1, xmm0
008d070b addss xmm1, xmm3
008d070f addss xmm2, xmm4
008d0713 subss xmm1, dword ptr [ebp - 0xfc]
008d071b subss xmm2, dword ptr [ebp - 0xcc]
008d0723 movaps xmm0, xmm1
008d0726 movss dword ptr [ebp - 0x9c], xmm1
008d072e mulss xmm0, xmm1
008d0732 movaps xmm1, xmm2
008d0735 mulss xmm1, xmm2
008d0739 movss dword ptr [ebp - 0xb8], xmm2
008d0741 addss xmm0, xmm1
008d0745 call 0x4228c0
008d074a comiss xmm0, dword ptr [0xb6a18c]
008d0751 movss dword ptr [ebp - 0xd4], xmm0
008d0759 jbe 0x8d07ae
008d075b movss xmm2, dword ptr [ebp - 0xa0]
008d0763 movss xmm0, dword ptr [ebp - 0xa4]
008d076b mulss xmm0, xmm0
008d076f mulss xmm2, xmm2
008d0773 addss xmm0, xmm2
008d0777 call 0x4228c0
008d077c divss xmm0, dword ptr [ebp - 0xd4]
008d0784 movss xmm1, dword ptr [ebp - 0xb8]
008d078c movss xmm2, dword ptr [ebp - 0x9c]
008d0794 mulss xmm1, xmm0
008d0798 mulss xmm2, xmm0
008d079c movss dword ptr [ebp - 0xa4], xmm1
008d07a4 movss dword ptr [ebp - 0xa0], xmm2
008d07ac jmp 0x8d07d8
008d07ae movss xmm1, dword ptr [ebp - 0xb8]
008d07b6 movss xmm2, dword ptr [ebp - 0x9c]
008d07be movss dword ptr [ebp - 0xa4], xmm1
008d07c6 movss dword ptr [ebp - 0xa0], xmm2
008d07ce jmp 0x8d07e0
008d07d0 movss xmm1, dword ptr [ebp - 0xa4]
008d07d8 movss xmm2, dword ptr [ebp - 0xa0]
008d07e0 push 1
008d07e2 push dword ptr [edi + 0x314]
008d07e8 lea eax, [edi + 0x2a4]
008d07ee movaps xmm0, xmm2
008d07f1 push eax
008d07f2 push 3
008d07f4 call 0x447a80
008d07f9 mulss xmm0, dword ptr [0xb6aa84]
008d0801 lea eax, [ebp - 0x138]
008d0807 push ecx
008d0808 movss dword ptr [esp], xmm0
008d080d push eax
008d080e push dword ptr [edi + 0x2c]
008d0811 call 0x8c7550
008d0816 mov esi, eax
008d0818 add esp, 0x1c
008d081b test esi, esi
008d081d je 0x8d0995
008d0823 push 1
008d0825 push edi
008d0826 mov ecx, esi
008d0828 mov byte ptr [esi + 0x434], 1
008d082f call 0x8c72b0
008d0834 lea eax, [ebp - 0xe0]
008d083a mov byte ptr [esi + 0x468], 1
008d0841 push eax
008d0842 push ecx
008d0843 push 0xbc4920
008d0848 push ecx
008d0849 push 0xbc47f0
008d084e mov edx, 0xbc4bf0
008d0853 lea ecx, [ebp - 0xf8]
008d0859 call 0x427220
008d085e add esp, 8
008d0861 lea ecx, [ebp - 0x168]
008d0867 mov edx, eax
008d0869 call 0x427220
008d086e add esp, 8
008d0871 mov ecx, eax
008d0873 call 0x57f3a0
008d0878 push eax
008d0879 lea edx, [edi + 0x388]
008d087f lea ecx, [ebp - 0x108]
008d0885 call 0x412050
008d088a mov edx, dword ptr [esi + 0x314]
008d0890 add esp, 4
008d0893 movups xmm0, xmmword ptr [eax]
008d0896 mov dword ptr [esi + 0x3a8], 3
008d08a0 lea eax, [esi + 0x314]
008d08a6 movups xmmword ptr [esi + 0x378], xmm0
008d08ad mov ecx, dword ptr [edi + 0x314]
008d08b3 mov dword ptr [ebp - 0xec], ecx
008d08b9 test edx, edx
008d08bb je 0x8d08e1
008d08bd mov dword ptr [ebp - 0xd4], eax
008d08c3 lea ecx, [edx + 0x324]
008d08c9 lea eax, [ebp - 0xd4]
008d08cf push eax
008d08d0 call 0x4bc3c0
008d08d5 mov ecx, dword ptr [ebp - 0xec]
008d08db lea eax, [esi + 0x314]
008d08e1 mov dword ptr [eax], ecx
008d08e3 test ecx, ecx
008d08e5 je 0x8d08ed
008d08e7 push eax
008d08e8 call 0x4bae70
008d08ed movss xmm1, dword ptr [ebp - 0xa0]
008d08f5 movss xmm0, dword ptr [ebp - 0xa4]
008d08fd mulss xmm0, xmm0
008d0901 mulss xmm1, xmm1
008d0905 addss xmm0, xmm1
008d0909 call 0x4228c0
008d090e movss dword ptr [esi + 0x420], xmm0
008d0916 mov ecx, esi
008d0918 mov eax, dword ptr [edi + 0x4b0]
008d091e dec eax
008d091f mov dword ptr [esi + 0x4b0], eax
008d0925 mov eax, dword ptr [esi]
008d0927 call dword ptr [eax + 0xc]
008d092a movd xmm0, dword ptr [edi + 0x4b0]
008d0932 lea ecx, [ebp - 0xb8]
008d0938 mov esi, dword ptr [0xbfd680]
008d093e cvtdq2ps xmm0, xmm0
008d0941 mov dword ptr [ebp - 0xb8], 0x86
008d094b mulss xmm0, dword ptr [0xb6a304]
008d0953 movss dword ptr [ebp - 0xd4], xmm0
008d095b call 0x8b1340
008d0960 movss xmm0, dword ptr [ebp - 0xd4]
008d0968 sub esp, 8
008d096b mov dword ptr [esp + 4], 0
008d0973 mov dword ptr [esp], 0x3f800000
008d097a push 0
008d097c push 2
008d097e push ecx
008d097f movss dword ptr [esp], xmm0
008d0984 lea ecx, [esi + 0x29de0]
008d098a push dword ptr [ebp - 0xb8]
008d0990 call 0x888de0
008d0995 mov dword ptr [edi + 0x4b0], 0
008d099f mov eax, dword ptr [edi + 0x3a8]
008d09a5 test eax, eax
008d09a7 jle 0x8d0a6f
008d09ad cmp byte ptr [edi + 0x16d], 0
008d09b4 jne 0x8d0a6f
008d09ba dec eax
008d09bb mov dword ptr [edi + 0x3a8], eax
008d09c1 test eax, eax
008d09c3 jg 0x8d0a6f
008d09c9 mov eax, dword ptr [edi + 0x2c]
008d09cc cmp eax, 6
008d09cf je 0x8d09d6
008d09d1 cmp eax, 0xf
008d09d4 jne 0x8d0a32
008d09d6 cmp byte ptr [edi + 0x3ae], 0
008d09dd jne 0x8d0a32
008d09df cmp byte ptr [edi + 0x16b], 0
008d09e6 jne 0x8d0a32
008d09e8 mov esi, dword ptr [0xbfd680]
008d09ee lea ecx, [ebp - 0xb8]
008d09f4 mov dword ptr [ebp - 0xb8], 0x118
008d09fe call 0x8b1340
008d0a03 sub esp, 8
008d0a06 mov dword ptr [esp + 4], 0
008d0a0e mov dword ptr [esp], 0x3f800000
008d0a15 push 0
008d0a17 push 2
008d0a19 push ecx
008d0a1a mov dword ptr [esp], 0x3f800000
008d0a21 lea ecx, [esi + 0x29de0]
008d0a27 push dword ptr [ebp - 0xb8]
008d0a2d call 0x888de0
008d0a32 mov ecx, edi
008d0a34 call 0x8c5940
008d0a39 test al, al
008d0a3b je 0x8d0a68
008d0a3d mov eax, dword ptr [edi + 0x2c]
008d0a40 cmp eax, 0xd
008d0a43 je 0x8d0a68
008d0a45 cmp eax, 6
008d0a48 je 0x8d0a4f
008d0a4a cmp eax, 0xf
008d0a4d jne 0x8d0a55
008d0a4f cmp dword ptr [edi + 0x34], 1
008d0a53 jne 0x8d0a68
008d0a55 mov byte ptr [edi + 0x3ae], 1
008d0a5c mov dword ptr [edi + 0x3a8], 0
008d0a66 jmp 0x8d0a6f
008d0a68 mov byte ptr [edi + 0x16b], 1
008d0a6f mov eax, dword ptr [edi + 0x36c]
008d0a75 mov dword ptr [edi + 0x370], eax
008d0a7b mov ecx, dword ptr [ebp - 0xc]
008d0a7e mov dword ptr fs:[0], ecx
008d0a85 pop ecx
008d0a86 pop edi
008d0a87 pop esi
008d0a88 mov ecx, dword ptr [ebp - 0x14]
008d0a8b xor ecx, ebp
008d0a8d call 0x9eacd7
008d0a92 mov esp, ebp
008d0a94 pop ebp
008d0a95 mov esp, ebx
008d0a97 pop ebx
008d0a98 ret 
