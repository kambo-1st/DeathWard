006ac370 push ebp
006ac371 mov ebp, esp
006ac373 and esp, 0xfffffff8
006ac376 sub esp, 0x3c
006ac379 movss xmm0, dword ptr [ebp + 8]
006ac37e push ebx
006ac37f mov ebx, dword ptr [ebp + 0x14]
006ac382 push esi
006ac383 push edi
006ac384 push dword ptr [ebp + 0x18]
006ac387 mov edi, ecx
006ac389 push ebx
006ac38a push dword ptr [ebp + 0x10]
006ac38d mov dword ptr [esp + 0x44], edi
006ac391 push dword ptr [ebp + 0xc]
006ac394 push ecx
006ac395 movss dword ptr [esp], xmm0
006ac39a call 0x684bb0
006ac39f mov ecx, dword ptr [edi + 0x160]
006ac3a5 mov esi, dword ptr [0xbfd65c]
006ac3ab and ecx, 0x20000000
006ac3b1 or ecx, 0
006ac3b4 mov byte ptr [esp + 0xf], al
006ac3b8 jne 0x6ac3e0
006ac3ba mov eax, dword ptr [ebx]
006ac3bc cmp eax, 1
006ac3bf je 0x6ac3d3
006ac3c1 cmp eax, 3
006ac3c4 je 0x6ac3d3
006ac3c6 mov eax, dword ptr [ebx + 8]
006ac3c9 cmp eax, 1
006ac3cc je 0x6ac3d3
006ac3ce cmp eax, 3
006ac3d1 jne 0x6ac3e0
006ac3d3 mov eax, dword ptr [esi + 0x18190]
006ac3d9 mov byte ptr [eax + 0x7185], 0
006ac3e0 cmp dword ptr [ebx + 0x24], 0
006ac3e4 je 0x6ac772
006ac3ea push 1
006ac3ec lea ecx, [esi + 0x1ba40]
006ac3f2 push ecx
006ac3f3 push 0x187
006ac3f8 call 0x91d340
006ac3fd test eax, eax
006ac3ff je 0x6ac76c
006ac405 mov ebx, dword ptr [ebx + 0x24]
006ac408 test ebx, ebx
006ac40a je 0x6ac76c
006ac410 mov eax, dword ptr [ebx + 0x28]
006ac413 sub eax, 0xa
006ac416 cmp eax, 0x3dd
006ac41b jbe 0x6ac42c
006ac41d mov ebx, dword ptr [ebx + 0x314]
006ac423 test ebx, ebx
006ac425 jne 0x6ac410
006ac427 jmp 0x6ac76c
006ac42c cmp ebx, edi
006ac42e je 0x6ac76c
006ac434 mov ecx, ebx
006ac436 call 0x681360
006ac43b mov ecx, edi
006ac43d mov esi, eax
006ac43f call 0x681360
006ac444 cmp esi, eax
006ac446 je 0x6ac76c
006ac44c mov esi, dword ptr [0xbfd65c]
006ac452 mov eax, dword ptr [esi + 0x1a30dc]
006ac458 sub eax, dword ptr [ebx + 0x280]
006ac45e test eax, eax
006ac460 jle 0x6ac772
006ac466 push 0
006ac468 mov ecx, ebx
006ac46a call 0x684630
006ac46f test al, al
006ac471 je 0x6ac772
006ac477 mov eax, dword ptr [edi + 0xe88]
006ac47d test eax, eax
006ac47f je 0x6ac492
006ac481 cmp eax, ebx
006ac483 je 0x6ac492
006ac485 call 0x6c3d90
006ac48a test al, 3
006ac48c jne 0x6ac772
006ac492 mov esi, dword ptr [edi + 0xe88]
006ac498 mov ecx, edi
006ac49a push 0x96
006ac49f push ebx
006ac4a0 call 0x6909f0
006ac4a5 test al, al
006ac4a7 je 0x6ac76c
006ac4ad cmp esi, ebx
006ac4af je 0x6ac76c
006ac4b5 movss xmm0, dword ptr [edi + 0x14]
006ac4ba comiss xmm0, dword ptr [edi + 0x2d8]
006ac4c1 jae 0x6ac76c
006ac4c7 mov esi, dword ptr [0xbfd65c]
006ac4cd lea ebx, [edi + 0x294]
006ac4d3 mov dword ptr [esp + 0x30], ebx
006ac4d7 call 0x6c3d90
006ac4dc mov dword ptr [esp + 0x18], eax
006ac4e0 lea eax, [esp + 0x18]
006ac4e4 push eax
006ac4e5 lea eax, [esp + 0x20]
006ac4e9 mov dword ptr [esp + 0x20], 2
006ac4f1 push eax
006ac4f2 push 0
006ac4f4 push 0xc02fec
006ac4f9 push ebx
006ac4fa lea eax, [esp + 0x34]
006ac4fe mov dword ptr [esp + 0x34], 0x31
006ac506 push eax
006ac507 lea eax, [esp + 0x28]
006ac50b mov dword ptr [esp + 0x28], 0x3e8
006ac513 push eax
006ac514 call 0x800fb0
006ac519 mov ecx, dword ptr [esi + 0x1c3198]
006ac51f push 0
006ac521 push dword ptr [esp + 0x14]
006ac525 call 0x6c4b30
006ac52a mov ebx, eax
006ac52c mov dword ptr [esp + 0x14], ebx
006ac530 test ebx, ebx
006ac532 je 0x6ac737
006ac538 call dword ptr [0xa064c0]
006ac53e mov ecx, dword ptr [ebx + 0x320]
006ac544 mov dword ptr [esp + 0x40], eax
006ac548 lea eax, [ebx + 0x320]
006ac54e mov dword ptr [ebx + 0x34], 0
006ac555 mov dword ptr [ebx + 0x38], 0
006ac55c test ecx, ecx
006ac55e je 0x6ac57a
006ac560 mov dword ptr [esp + 0x28], eax
006ac564 add ecx, 0x324
006ac56a lea eax, [esp + 0x28]
006ac56e push eax
006ac56f call 0x4bc3c0
006ac574 lea eax, [ebx + 0x320]
006ac57a push dword ptr [esp + 0x18]
006ac57e mov dword ptr [eax], 0
006ac584 mov ecx, ebx
006ac586 mov eax, dword ptr [edi + 0x294]
006ac58c push dword ptr [esp + 0x20]
006ac590 mov dword ptr [ebx + 0x294], eax
006ac596 mov eax, dword ptr [edi + 0x298]
006ac59c push dword ptr [esp + 0x28]
006ac5a0 mov dword ptr [ebx + 0x298], eax
006ac5a6 movss xmm0, dword ptr [0xc02fec]
006ac5ae mov eax, dword ptr [ebx]
006ac5b0 push dword ptr [esp + 0x1c]
006ac5b4 movss dword ptr [ebx + 0x2b8], xmm0
006ac5bc movss xmm0, dword ptr [0xc02ff0]
006ac5c4 movss dword ptr [ebx + 0x2bc], xmm0
006ac5cc call dword ptr [eax + 4]
006ac5cf mov edx, dword ptr [esi + 0x18190]
006ac5d5 push ebx
006ac5d6 mov ecx, dword ptr [edx + 0x1214]
006ac5dc lea eax, [ecx + 1]
006ac5df mov dword ptr [edx + 0x1214], eax
006ac5e5 mov dword ptr [ebx + 0x20], ecx
006ac5e8 lea ecx, [edx + 0x1218]
006ac5ee call 0x413280
006ac5f3 push ebx
006ac5f4 call 0x6d94d0
006ac5f9 test al, al
006ac5fb je 0x6ac604
006ac5fd push ecx
006ac5fe push ebx
006ac5ff call 0x6d9590
006ac604 cmp byte ptr [ebx + 0x16a], 0
006ac60b je 0x6ac727
006ac611 mov eax, dword ptr [esi + 0x283c20]
006ac617 cmp eax, dword ptr [esi + 0x283c24]
006ac61d je 0x6ac727
006ac623 mov eax, dword ptr [ebx + 0x28]
006ac626 lea ecx, [esi + 0x283c48]
006ac62c mov dword ptr [esp + 0x20], eax
006ac630 mov eax, dword ptr [ebx + 0x2c]
006ac633 mov dword ptr [esp + 0x24], eax
006ac637 lea eax, [esp + 0x20]
006ac63b push eax
006ac63c lea eax, [esp + 0x2c]
006ac640 push eax
006ac641 call 0x937c80
006ac646 mov eax, dword ptr [esi + 0x283c48]
006ac64c cmp dword ptr [esp + 0x28], eax
006ac650 jne 0x6ac684
006ac652 mov eax, dword ptr [ebx + 0x28]
006ac655 lea ecx, [esi + 0x283c48]
006ac65b mov dword ptr [esp + 0x20], eax
006ac65f lea eax, [esp + 0x20]
006ac663 push eax
006ac664 lea eax, [esp + 0x2c]
006ac668 mov dword ptr [esp + 0x28], 0xffffffff
006ac670 push eax
006ac671 call 0x937c80
006ac676 mov ecx, dword ptr [esi + 0x283c48]
006ac67c cmp dword ptr [eax], ecx
006ac67e je 0x6ac727
006ac684 mov esi, dword ptr [0xbfd65c]
006ac68a xor ebx, ebx
006ac68c mov eax, dword ptr [esi + 0x1ba54]
006ac692 sub eax, dword ptr [esi + 0x1ba50]
006ac698 sar eax, 2
006ac69b test eax, eax
006ac69d je 0x6ac723
006ac6a3 mov edi, dword ptr [esp + 0x14]
006ac6a7 nop word ptr [eax + eax]
006ac6b0 mov ecx, dword ptr [esi + 0x1ba54]
006ac6b6 mov eax, ecx
006ac6b8 sub eax, dword ptr [esi + 0x1ba50]
006ac6be test eax, 0xfffffffc
006ac6c3 jne 0x6ac6da
006ac6c5 push 0xb3f4d0
006ac6ca push 3
006ac6cc call 0x95e330
006ac6d1 mov ecx, dword ptr [esi + 0x1ba54]
006ac6d7 add esp, 8
006ac6da mov eax, dword ptr [esi + 0x1ba50]
006ac6e0 sub ecx, eax
006ac6e2 sar ecx, 2
006ac6e5 cmp ebx, ecx
006ac6e7 jae 0x6ac6ec
006ac6e9 lea eax, [eax + ebx*4]
006ac6ec mov ecx, dword ptr [eax]
006ac6ee push 0xc02fec
006ac6f3 push dword ptr [esp + 0x34]
006ac6f7 add ecx, 0x1ec0
006ac6fd push edi
006ac6fe push 6
006ac700 call 0x935fd0
006ac705 mov esi, dword ptr [0xbfd65c]
006ac70b inc ebx
006ac70c mov eax, dword ptr [esi + 0x1ba54]
006ac712 sub eax, dword ptr [esi + 0x1ba50]
006ac718 sar eax, 2
006ac71b cmp ebx, eax
006ac71d jb 0x6ac6b0
006ac71f mov edi, dword ptr [esp + 0x38]
006ac723 mov ebx, dword ptr [esp + 0x14]
006ac727 call dword ptr [0xa064c0]
006ac72d sub eax, dword ptr [esp + 0x40]
006ac731 add dword ptr [0xbffe0c], eax
006ac737 push 0
006ac739 push 0xbeaaec
006ac73e push 0xbeab18
006ac743 push 0
006ac745 push ebx
006ac746 call 0x9ec34c
006ac74b add esp, 0x14
006ac74e mov dword ptr [eax + 0xd0], 0
006ac758 mov dword ptr [eax + 0xd4], 0xc1c00000
006ac762 mov dword ptr [eax + 0x2b0], 0x3f800000
006ac76c mov esi, dword ptr [0xbfd65c]
006ac772 push 1
006ac774 lea ecx, [esi + 0x1ba40]
006ac77a push ecx
006ac77b push 0x1b2
006ac780 call 0x91d340
006ac785 mov ebx, dword ptr [ebp + 0x14]
006ac788 test eax, eax
006ac78a je 0x6ac7db
006ac78c mov ecx, dword ptr [ebx]
006ac78e cmp ecx, 1
006ac791 je 0x6ac7c5
006ac793 cmp dword ptr [ebx + 8], 1
006ac797 jne 0x6ac7a4
006ac799 cmp ecx, 3
006ac79c jne 0x6ac7c5
006ac79e cmp dword ptr [ebx + 4], 0x2b
006ac7a2 jne 0x6ac7c5
006ac7a4 mov eax, dword ptr [ebp + 0xc]
006ac7a7 and eax, 0x8010
006ac7ac or eax, 0
006ac7af jne 0x6ac7c5
006ac7b1 cmp ecx, 0x3e8
006ac7b7 je 0x6ac7c5
006ac7b9 and dword ptr [edi + 0x160], 0xefffffff
006ac7c3 jmp 0x6ac7cf
006ac7c5 or dword ptr [edi + 0x160], 0x10000000
006ac7cf mov eax, dword ptr [edi + 0x164]
006ac7d5 mov dword ptr [edi + 0x164], eax
006ac7db cmp dword ptr [edi + 0xbb4], 0x15
006ac7e2 jne 0x6ac950
006ac7e8 cmp byte ptr [edi + 0x16b], 0
006ac7ef jne 0x6ac950
006ac7f5 movss xmm0, dword ptr [edi + 0x14]
006ac7fa comiss xmm0, dword ptr [edi + 0x2d8]
006ac801 jae 0x6ac950
006ac807 cmp dword ptr [edi + 0xaf8], 0
006ac80e jg 0x6ac950
006ac814 mov eax, dword ptr [ebp + 0xc]
006ac817 and eax, 0x10
006ac81a or eax, 0
006ac81d jne 0x6ac950
006ac823 mov eax, dword ptr [ebx]
006ac825 cmp eax, 1
006ac828 je 0x6ac843
006ac82a cmp dword ptr [ebx + 8], 1
006ac82e jne 0x6ac950
006ac834 cmp eax, 3
006ac837 jne 0x6ac843
006ac839 cmp dword ptr [ebx + 4], 0x2b
006ac83d je 0x6ac950
006ac843 mov eax, dword ptr [0xbfd65c]
006ac848 xor edx, edx
006ac84a mov esi, dword ptr [eax + 0x18190]
006ac850 mov eax, dword ptr [esi + 0x1264]
006ac856 test eax, eax
006ac858 je 0x6ac886
006ac85a mov esi, dword ptr [esi + 0x125c]
006ac860 mov ebx, eax
006ac862 mov eax, dword ptr [esi]
006ac864 lea ecx, [edx + 1]
006ac867 lea esi, [esi + 4]
006ac86a cmp dword ptr [eax + 0x320], edi
006ac870 cmovne ecx, edx
006ac873 mov edx, ecx
006ac875 sub ebx, 1
006ac878 jne 0x6ac862
006ac87a mov ebx, dword ptr [ebp + 0x14]
006ac87d cmp edx, 5
006ac880 jge 0x6ac950
006ac886 call 0x6c3d90
006ac88b mov esi, eax
006ac88d lea eax, [esp + 0x28]
006ac891 push eax
006ac892 call 0x659290
006ac897 movss xmm1, dword ptr [edi + 0x2c8]
006ac89f add esp, 4
006ac8a2 mov ecx, dword ptr [0xbfd65c]
006ac8a8 movaps xmm0, xmm1
006ac8ab movss xmm2, dword ptr [eax + 4]
006ac8b0 mulss xmm0, dword ptr [eax]
006ac8b4 lea eax, [esp + 0x30]
006ac8b8 push 0
006ac8ba push esi
006ac8bb push 0
006ac8bd addss xmm0, dword ptr [edi + 0x294]
006ac8c5 push edi
006ac8c6 mulss xmm2, xmm1
006ac8ca push 0xc02fec
006ac8cf push eax
006ac8d0 push 0
006ac8d2 addss xmm2, dword ptr [edi + 0x298]
006ac8da push 0x12
006ac8dc movss dword ptr [esp + 0x50], xmm0
006ac8e2 movss dword ptr [esp + 0x54], xmm2
006ac8e8 call 0x6d0ca0
006ac8ed push 0
006ac8ef push 0xbeab70
006ac8f4 push 0xbeab18
006ac8f9 push 0
006ac8fb push eax
006ac8fc call 0x9ec34c
006ac901 mov ecx, dword ptr [eax + 0x320]
006ac907 add esp, 0x14
006ac90a mov dword ptr [esp + 0x38], eax
006ac90e mov byte ptr [eax + 0x16c], 1
006ac915 lea esi, [eax + 0x320]
006ac91b test ecx, ecx
006ac91d je 0x6ac933
006ac91f lea eax, [esp + 0x40]
006ac923 mov dword ptr [esp + 0x40], esi
006ac927 push eax
006ac928 add ecx, 0x324
006ac92e call 0x4bc3c0
006ac933 push esi
006ac934 mov ecx, edi
006ac936 mov dword ptr [esi], edi
006ac938 call 0x4bae70
006ac93d mov ecx, dword ptr [esp + 0x38]
006ac941 mov eax, dword ptr [ecx]
006ac943 call dword ptr [eax + 0xc]
006ac946 mov dword ptr [edi + 0xaf8], 0x3c
006ac950 mov cl, byte ptr [esp + 0xf]
006ac954 test cl, cl
006ac956 je 0x6acaf2
006ac95c mov eax, dword ptr [edi + 0x160]
006ac962 and eax, 1
006ac965 or eax, 0
006ac968 jne 0x6ac9d1
006ac96a mov eax, dword ptr [ebp + 0xc]
006ac96d and eax, 0x4000
006ac972 or eax, 0
006ac975 je 0x6ac9d1
006ac977 mov esi, dword ptr [ebx + 0x24]
006ac97a test esi, esi
006ac97c je 0x6ac996
006ac97e cmp dword ptr [esi + 0x28], 1
006ac982 je 0x6ac9aa
006ac984 mov eax, dword ptr [esi + 0x320]
006ac98a mov esi, eax
006ac98c test eax, eax
006ac98e je 0x6ac996
006ac990 cmp dword ptr [esi + 0x28], 1
006ac994 je 0x6ac9aa
006ac996 mov ecx, dword ptr [0xbfd65c]
006ac99c lea eax, [edi + 0x294]
006ac9a2 push eax
006ac9a3 call 0x6d5e30
006ac9a8 mov esi, eax
006ac9aa mov ecx, dword ptr [esi + 0x294]
006ac9b0 lea eax, [esp + 0x40]
006ac9b4 mov edx, dword ptr [esi + 0x298]
006ac9ba push edi
006ac9bb push eax
006ac9bc mov dword ptr [esp + 0x48], ecx
006ac9c0 mov ecx, esi
006ac9c2 push 1
006ac9c4 mov dword ptr [esp + 0x50], edx
006ac9c8 call 0x725cc0
006ac9cd mov cl, byte ptr [esp + 0xf]
006ac9d1 mov eax, dword ptr [edi + 0x160]
006ac9d7 and eax, 1
006ac9da or eax, 0
006ac9dd jne 0x6acaf2
006ac9e3 mov esi, dword ptr [ebx + 0x24]
006ac9e6 test esi, esi
006ac9e8 je 0x6aca02
006ac9ea cmp dword ptr [esi + 0x28], 1
006ac9ee je 0x6aca16
006ac9f0 mov eax, dword ptr [esi + 0x320]
006ac9f6 mov esi, eax
006ac9f8 test eax, eax
006ac9fa je 0x6aca02
006ac9fc cmp dword ptr [esi + 0x28], 1
006aca00 je 0x6aca16
006aca02 mov ecx, dword ptr [0xbfd65c]
006aca08 lea eax, [edi + 0x294]
006aca0e push eax
006aca0f call 0x6d5e30
006aca14 mov esi, eax
006aca16 movss xmm1, dword ptr [edi + 0x298]
006aca1e subss xmm1, dword ptr [esi + 0x298]
006aca26 movss xmm2, dword ptr [edi + 0x294]
006aca2e subss xmm2, dword ptr [esi + 0x294]
006aca36 movaps xmm0, xmm1
006aca39 movss dword ptr [esp + 0x1c], xmm1
006aca3f mulss xmm0, xmm1
006aca43 movss dword ptr [esp + 0x44], xmm1
006aca49 movaps xmm1, xmm2
006aca4c mulss xmm1, xmm2
006aca50 movss dword ptr [esp + 0x20], xmm2
006aca56 movss dword ptr [esp + 0x40], xmm2
006aca5c addss xmm0, xmm1
006aca60 call 0x4228c0
006aca65 movss xmm2, dword ptr [esp + 0x1c]
006aca6b xorps xmm1, xmm1
006aca6e comiss xmm0, xmm1
006aca71 movss xmm1, dword ptr [esp + 0x20]
006aca77 jbe 0x6aca99
006aca79 movss xmm3, dword ptr [0xb6a614]
006aca81 divss xmm3, xmm0
006aca85 mulss xmm1, xmm3
006aca89 mulss xmm2, xmm3
006aca8d movss dword ptr [esp + 0x40], xmm1
006aca93 movss dword ptr [esp + 0x44], xmm2
006aca99 movss xmm0, dword ptr [edi + 0x2c8]
006acaa1 lea eax, [esp + 0x40]
006acaa5 movss xmm3, dword ptr [edi + 0x294]
006acaad lea ecx, [esi + 0x1ec0]
006acab3 mulss xmm1, xmm0
006acab7 push eax
006acab8 mulss xmm2, xmm0
006acabc lea eax, [esp + 0x3c]
006acac0 push eax
006acac1 movss xmm0, dword ptr [edi + 0x298]
006acac9 subss xmm3, xmm1
006acacd push edi
006acace subss xmm0, xmm2
006acad2 push 2
006acad4 movss dword ptr [esp + 0x48], xmm3
006acada movss dword ptr [esp + 0x4c], xmm0
006acae0 call 0x935fd0
006acae5 mov al, byte ptr [esp + 0xf]
006acae9 pop edi
006acaea pop esi
006acaeb pop ebx
006acaec mov esp, ebp
006acaee pop ebp
006acaef ret 0x14
006acaf2 pop edi
006acaf3 pop esi
006acaf4 mov al, cl
006acaf6 pop ebx
006acaf7 mov esp, ebp
006acaf9 pop ebp
006acafa ret 0x14
