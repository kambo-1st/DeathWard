006d0400 push ebp
006d0401 mov ebp, esp
006d0403 sub esp, 0xc
006d0406 push ebx
006d0407 mov ebx, dword ptr [0xbfd65c]
006d040d push esi
006d040e push edi
006d040f mov dword ptr [ebp - 4], ebx
006d0412 lea ecx, [ebx + 0x1bb60]
006d0418 call 0x663d10
006d041d test al, al
006d041f jne 0x6d07c1
006d0425 mov eax, dword ptr [ebx + 0x1b6c0]
006d042b test eax, eax
006d042d je 0x6d04fb
006d0433 mov ecx, dword ptr [ebx + 0x1b6c8]
006d0439 cmp dword ptr [ebx + 0x1b6c4], ecx
006d043f je 0x6d0464
006d0441 movss xmm1, dword ptr [0xb6a480]
006d0449 movd xmm0, ecx
006d044d cvtdq2ps xmm0, xmm0
006d0450 divss xmm1, xmm0
006d0454 addss xmm1, dword ptr [ebx + 0x1b6cc]
006d045c movss dword ptr [ebx + 0x1b6cc], xmm1
006d0464 cmp eax, 1
006d0467 je 0x6d0472
006d0469 cmp eax, 4
006d046c jne 0x6d05a7
006d0472 mov eax, dword ptr [0xbfd65c]
006d0477 xor edi, edi
006d0479 mov ebx, dword ptr [eax + 0x18190]
006d047f cmp dword ptr [ebx + 0x1264], edi
006d0485 jbe 0x6d05a4
006d048b nop dword ptr [eax + eax]
006d0490 mov eax, dword ptr [ebx + 0x125c]
006d0496 mov esi, dword ptr [eax + edi*4]
006d0499 cmp dword ptr [esi + 0x28], 1
006d049d jne 0x6d04d4
006d049f mov eax, dword ptr [esi + 0x164]
006d04a5 mov ecx, esi
006d04a7 or dword ptr [esi + 0x160], 0x4000
006d04b1 mov dword ptr [esi + 0x164], eax
006d04b7 mov eax, dword ptr [esi]
006d04b9 call dword ptr [eax + 0xc]
006d04bc mov eax, dword ptr [esi + 0x164]
006d04c2 and dword ptr [esi + 0x160], 0xffffbfff
006d04cc mov dword ptr [esi + 0x164], eax
006d04d2 jmp 0x6d04ed
006d04d4 mov ecx, dword ptr [esi + 0x164]
006d04da xor eax, eax
006d04dc and ecx, 0x1000
006d04e2 or eax, ecx
006d04e4 je 0x6d04ed
006d04e6 mov eax, dword ptr [esi]
006d04e8 mov ecx, esi
006d04ea call dword ptr [eax + 0x10]
006d04ed inc edi
006d04ee cmp edi, dword ptr [ebx + 0x1264]
006d04f4 jb 0x6d0490
006d04f6 jmp 0x6d05a4
006d04fb lea eax, [ebx + 0x1ba0c]
006d0501 mov dword ptr [ebp - 0xc], eax
006d0504 mov eax, dword ptr [eax]
006d0506 test eax, eax
006d0508 je 0x6d05a7
006d050e cmp eax, 1
006d0511 je 0x6d051c
006d0513 cmp eax, 4
006d0516 jne 0x6d05a7
006d051c mov eax, dword ptr [0xbfd65c]
006d0521 xor edi, edi
006d0523 mov eax, dword ptr [eax + 0x18190]
006d0529 cmp dword ptr [eax + 0x1264], edi
006d052f jbe 0x6d05a7
006d0531 mov ebx, eax
006d0533 mov eax, dword ptr [ebx + 0x125c]
006d0539 mov esi, dword ptr [eax + edi*4]
006d053c cmp dword ptr [esi + 0x28], 1
006d0540 jne 0x6d0582
006d0542 mov eax, dword ptr [esi + 0x164]
006d0548 mov ecx, esi
006d054a or dword ptr [esi + 0x160], 0x4000
006d0554 mov dword ptr [esi + 0x164], eax
006d055a mov eax, dword ptr [esi]
006d055c call dword ptr [eax + 0xc]
006d055f mov eax, dword ptr [esi + 0x164]
006d0565 mov ecx, dword ptr [ebp - 0xc]
006d0568 and dword ptr [esi + 0x160], 0xffffbfff
006d0572 push 1
006d0574 push esi
006d0575 mov dword ptr [esi + 0x164], eax
006d057b call 0x88a230
006d0580 jmp 0x6d059b
006d0582 mov edx, dword ptr [esi + 0x164]
006d0588 xor eax, eax
006d058a and edx, 0x1000
006d0590 or eax, edx
006d0592 je 0x6d059b
006d0594 mov eax, dword ptr [esi]
006d0596 mov ecx, esi
006d0598 call dword ptr [eax + 0x10]
006d059b inc edi
006d059c cmp edi, dword ptr [ebx + 0x1264]
006d05a2 jb 0x6d0533
006d05a4 mov ebx, dword ptr [ebp - 4]
006d05a7 mov ecx, ebx
006d05a9 call 0x6d0380
006d05ae test al, al
006d05b0 jne 0x6d07c1
006d05b6 mov ecx, dword ptr [0xbfd680]
006d05bc cmp byte ptr [ecx + 0x1ea962], al
006d05c2 jne 0x6d05de
006d05c4 cmp byte ptr [ecx + 0x29e4f], al
006d05ca je 0x6d05de
006d05cc mov eax, dword ptr [ecx + 0x20a9ac]
006d05d2 cmp eax, dword ptr [ecx + 0x20a9b0]
006d05d8 je 0x6d07c1
006d05de mov ebx, dword ptr [ebx + 0x18190]
006d05e4 xor edi, edi
006d05e6 cmp dword ptr [ebx + 0x1264], edi
006d05ec jbe 0x6d0649
006d05ee nop 
006d05f0 mov eax, dword ptr [ebx + 0x125c]
006d05f6 mov esi, dword ptr [eax + edi*4]
006d05f9 mov ecx, esi
006d05fb cmp dword ptr [esi + 0x28], 1
006d05ff mov edx, dword ptr [esi]
006d0601 jne 0x6d063d
006d0603 mov eax, dword ptr [esi + 0x164]
006d0609 or dword ptr [esi + 0x160], 0x4000
006d0613 mov dword ptr [esi + 0x164], eax
006d0619 call dword ptr [edx + 0xc]
006d061c push 0
006d061e mov ecx, esi
006d0620 call 0x683850
006d0625 mov eax, dword ptr [esi + 0x164]
006d062b and dword ptr [esi + 0x160], 0xffffbfff
006d0635 mov dword ptr [esi + 0x164], eax
006d063b jmp 0x6d0640
006d063d call dword ptr [edx + 0x10]
006d0640 inc edi
006d0641 cmp edi, dword ptr [ebx + 0x1264]
006d0647 jb 0x6d05f0
006d0649 cmp byte ptr [ebx + 0x7768], 0
006d0650 je 0x6d0746
006d0656 movss xmm0, dword ptr [ebx + 0x7770]
006d065e xor edi, edi
006d0660 movss xmm4, dword ptr [0xb6a480]
006d0668 mov eax, dword ptr [ebx + 0x7650]
006d066e mulss xmm0, xmm4
006d0672 mov dword ptr [ebp - 0xc], eax
006d0675 addss xmm0, dword ptr [ebx + 0x776c]
006d067d movss dword ptr [ebx + 0x776c], xmm0
006d0685 cmp dword ptr [eax + 0x1264], edi
006d068b jbe 0x6d0746
006d0691 xorps xmm3, xmm3
006d0694 mov eax, dword ptr [eax + 0x125c]
006d069a mov esi, dword ptr [eax + edi*4]
006d069d mov eax, dword ptr [esi + 0x28]
006d06a0 cmp eax, 1
006d06a3 je 0x6d06f6
006d06a5 cmp eax, 3
006d06a8 je 0x6d06f1
006d06aa movss xmm0, dword ptr [esi + 0x298]
006d06b2 movss xmm1, dword ptr [ebx + 0x7770]
006d06ba addss xmm0, xmm3
006d06be movss xmm2, dword ptr [esi + 0x294]
006d06c6 cmp dword ptr [esi + 0x2b4], 0
006d06cd movss dword ptr [esi + 0x298], xmm0
006d06d5 jne 0x6d06e1
006d06d7 mulss xmm1, dword ptr [0xb6a274]
006d06df jmp 0x6d06e5
006d06e1 mulss xmm1, xmm4
006d06e5 addss xmm1, xmm2
006d06e9 movss dword ptr [esi + 0x294], xmm1
006d06f1 cmp eax, 1
006d06f4 jne 0x6d0736
006d06f6 mov eax, dword ptr [esi + 0x164]
006d06fc mov ecx, esi
006d06fe or dword ptr [esi + 0x160], 0x4000
006d0708 push 0
006d070a mov dword ptr [esi + 0x164], eax
006d0710 call 0x683850
006d0715 mov eax, dword ptr [esi + 0x164]
006d071b xorps xmm3, xmm3
006d071e and dword ptr [esi + 0x160], 0xffffbfff
006d0728 movss xmm4, dword ptr [0xb6a480]
006d0730 mov dword ptr [esi + 0x164], eax
006d0736 mov eax, dword ptr [ebp - 0xc]
006d0739 inc edi
006d073a cmp edi, dword ptr [eax + 0x1264]
006d0740 jb 0x6d0694
006d0746 mov eax, dword ptr [0xbfd65c]
006d074b xor edi, edi
006d074d mov byte ptr [ebx + 0x7114], 1
006d0754 mov ecx, dword ptr [eax + 0x1ba5c]
006d075a mov eax, dword ptr [eax + 0x1ba60]
006d0760 sub eax, ecx
006d0762 sar eax, 2
006d0765 test eax, eax
006d0767 je 0x6d07c1
006d0769 nop dword ptr [eax]
006d0770 mov esi, dword ptr [ecx + edi*4]
006d0773 mov ecx, esi
006d0775 mov eax, dword ptr [esi + 0x164]
006d077b or dword ptr [esi + 0x160], 0x4000
006d0785 mov dword ptr [esi + 0x164], eax
006d078b mov eax, dword ptr [esi]
006d078d call dword ptr [eax + 0xc]
006d0790 mov eax, dword ptr [esi + 0x164]
006d0796 inc edi
006d0797 and dword ptr [esi + 0x160], 0xffffbfff
006d07a1 mov dword ptr [esi + 0x164], eax
006d07a7 mov eax, dword ptr [0xbfd65c]
006d07ac mov ecx, dword ptr [eax + 0x1ba5c]
006d07b2 mov eax, dword ptr [eax + 0x1ba60]
006d07b8 sub eax, ecx
006d07ba sar eax, 2
006d07bd cmp edi, eax
006d07bf jb 0x6d0770
006d07c1 pop edi
006d07c2 pop esi
006d07c3 pop ebx
006d07c4 mov esp, ebp
006d07c6 pop ebp
006d07c7 ret 
