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
006acafd int3 
006acafe int3 
006acaff int3 
006acb00 push ebp
006acb01 mov ebp, esp
006acb03 movss xmm1, dword ptr [ebp + 8]
006acb08 movss dword ptr [ecx + 0xb88], xmm1
006acb10 mulss xmm1, dword ptr [ecx + 0x30c]
006acb18 movaps xmm0, xmm1
006acb1b mulss xmm1, dword ptr [0xbc7a2c]
006acb23 mulss xmm0, dword ptr [0xbc7a28]
006acb2b movss dword ptr [ecx + 0xdc], xmm1
006acb33 movss dword ptr [ecx + 0xd8], xmm0
006acb3b pop ebp
006acb3c ret 4
006acb3f int3 
006acb40 movss xmm1, dword ptr [ecx + 0xb88]
006acb48 mulss xmm1, dword ptr [ecx + 0x30c]
006acb50 movaps xmm0, xmm1
006acb53 mulss xmm1, dword ptr [0xbc7a2c]
006acb5b mulss xmm0, dword ptr [0xbc7a28]
006acb63 movss dword ptr [ecx + 0xdc], xmm1
006acb6b movss dword ptr [ecx + 0xd8], xmm0
006acb73 ret 
006acb74 int3 
006acb75 int3 
006acb76 int3 
006acb77 int3 
006acb78 int3 
006acb79 int3 
006acb7a int3 
006acb7b int3 
006acb7c int3 
006acb7d int3 
006acb7e int3 
006acb7f int3 
006acb80 push ebp
006acb81 mov ebp, esp
006acb83 and esp, 0xfffffff8
006acb86 sub esp, 0xcc
006acb8c mov eax, dword ptr [0xbaa3b4]
006acb91 xor eax, esp
006acb93 mov dword ptr [esp + 0xc8], eax
006acb9a push ebx
006acb9b push esi
006acb9c push edi
006acb9d mov edi, ecx
006acb9f mov dword ptr [esp + 0x30], edi
006acba3 mov eax, dword ptr [edi + 0xab4]
006acba9 test eax, eax
006acbab jne 0x6acc1c
006acbad mov ecx, dword ptr [edi + 0x160]
006acbb3 movss xmm0, dword ptr [edi + 0x2d8]
006acbbb and ecx, 0xfffffffb
006acbbe mov eax, dword ptr [edi + 0x164]
006acbc4 or ecx, 0x20d0011
006acbca comiss xmm0, dword ptr [0xb6a614]
006acbd1 mov dword ptr [edi + 0x164], eax
006acbd7 mov eax, 0x10
006acbdc mov dword ptr [edi + 0x160], ecx
006acbe2 mov ecx, 3
006acbe7 cmova eax, ecx
006acbea cmp dword ptr [edi + 0x32c], 0
006acbf1 mov dword ptr [edi + 0xab4], eax
006acbf7 jne 0x6ad700
006acbfd mov dword ptr [edi + 0x2ac], 0x64
006acc07 pop edi
006acc08 pop esi
006acc09 pop ebx
006acc0a mov ecx, dword ptr [esp + 0xc8]
006acc11 xor ecx, esp
006acc13 call 0x9eacd7
006acc18 mov esp, ebp
006acc1a pop ebp
006acc1b ret 
006acc1c movss xmm0, dword ptr [edi + 0x14]
006acc21 xorps xmm2, xmm2
006acc24 comiss xmm0, xmm2
006acc27 mov ecx, eax
006acc29 mov ebx, 3
006acc2e movss xmm4, dword ptr [0xb6a7b0]
006acc36 movss xmm3, dword ptr [0xb6a614]
006acc3e jbe 0x6acca8
006acc40 movaps xmm1, xmm3
006acc43 call 0x6c3d90
006acc48 xor edx, edx
006acc4a div ebx
006acc4c test edx, edx
006acc4e jne 0x6acc53
006acc50 movaps xmm1, xmm4
006acc53 mov eax, dword ptr [edi + 0x18]
006acc56 and eax, 4
006acc59 or eax, 0
006acc5c je 0x6acc68
006acc5e movss xmm1, dword ptr [0xb6a8cc]
006acc66 jmp 0x6acc6d
006acc68 comiss xmm1, xmm2
006acc6b jbe 0x6acc85
006acc6d movss xmm0, dword ptr [edi + 0x2d8]
006acc75 subss xmm0, xmm1
006acc79 maxss xmm0, xmm3
006acc7d movss dword ptr [edi + 0x2d8], xmm0
006acc85 mov eax, dword ptr [edi + 8]
006acc88 mov dword ptr [edi + 0xc], eax
006acc8b mov dword ptr [edi + 0x14], 0
006acc92 mov dword ptr [edi + 0x18], 0
006acc99 mov dword ptr [edi + 0x1c], 0
006acca0 mov eax, dword ptr [edi + 0xab4]
006acca6 mov ecx, eax
006acca8 cmp byte ptr [edi + 0x16b], 0
006accaf jne 0x6accbe
006accb1 comiss xmm3, dword ptr [edi + 0x2d8]
006accb8 jb 0x6ad62d
006accbe cmp ecx, 0x10
006accc1 je 0x6ad603
006accc7 call 0x6c3d90
006acccc movss xmm0, dword ptr [edi + 0x294]
006accd4 lea ecx, [edi + 0x294]
006accda mov esi, dword ptr [0xbfd65c]
006acce0 mov dword ptr [esp + 0x40], eax
006acce4 lea eax, [esp + 0x40]
006acce8 push eax
006acce9 lea eax, [esp + 0x48]
006acced movss dword ptr [esp + 0x58], xmm0
006accf3 movss xmm0, dword ptr [ecx + 4]
006accf8 push eax
006accf9 push 0
006accfb push 0xc02fec
006acd00 lea eax, [esp + 0x64]
006acd04 mov dword ptr [esp + 0x60], ecx
006acd08 push eax
006acd09 lea eax, [esp + 0x5c]
006acd0d movss dword ptr [esp + 0x6c], xmm0
006acd13 push eax
006acd14 lea eax, [esp + 0x44]
006acd18 mov dword ptr [esp + 0x5c], 0
006acd20 push eax
006acd21 mov dword ptr [esp + 0x64], 1
006acd29 mov dword ptr [esp + 0x48], 0x3e8
006acd31 call 0x800fb0
006acd36 mov ecx, dword ptr [esi + 0x1c3198]
006acd3c push 0
006acd3e push dword ptr [esp + 0x30]
006acd42 call 0x6c4b30
006acd47 mov ebx, eax
006acd49 mov dword ptr [esp + 0x18], ebx
006acd4d test ebx, ebx
006acd4f je 0x6acf54
006acd55 call dword ptr [0xa064c0]
006acd5b mov ecx, dword ptr [ebx + 0x320]
006acd61 mov dword ptr [esp + 0x14], eax
006acd65 lea eax, [ebx + 0x320]
006acd6b mov dword ptr [ebx + 0x34], 0
006acd72 mov dword ptr [ebx + 0x38], 0
006acd79 test ecx, ecx
006acd7b je 0x6acd97
006acd7d mov dword ptr [esp + 0x6c], eax
006acd81 add ecx, 0x324
006acd87 lea eax, [esp + 0x6c]
006acd8b push eax
006acd8c call 0x4bc3c0
006acd91 lea eax, [ebx + 0x320]
006acd97 push dword ptr [esp + 0x40]
006acd9b mov dword ptr [eax], 0
006acda1 mov ecx, ebx
006acda3 movss xmm0, dword ptr [esp + 0x58]
006acda9 push dword ptr [esp + 0x48]
006acdad mov eax, dword ptr [ebx]
006acdaf push dword ptr [esp + 0x50]
006acdb3 movss dword ptr [ebx + 0x294], xmm0
006acdbb movss xmm0, dword ptr [esp + 0x64]
006acdc1 push dword ptr [esp + 0x38]
006acdc5 movss dword ptr [ebx + 0x298], xmm0
006acdcd movss xmm0, dword ptr [0xc02fec]
006acdd5 movss dword ptr [ebx + 0x2b8], xmm0
006acddd movss xmm0, dword ptr [0xc02ff0]
006acde5 movss dword ptr [ebx + 0x2bc], xmm0
006acded call dword ptr [eax + 4]
006acdf0 mov edx, dword ptr [esi + 0x18190]
006acdf6 push ebx
006acdf7 mov ecx, dword ptr [edx + 0x1214]
006acdfd lea eax, [ecx + 1]
006ace00 mov dword ptr [edx + 0x1214], eax
006ace06 mov dword ptr [ebx + 0x20], ecx
006ace09 lea ecx, [edx + 0x1218]
006ace0f call 0x413280
006ace14 push ebx
006ace15 call 0x6d94d0
006ace1a test al, al
006ace1c je 0x6ace25
006ace1e push ecx
006ace1f push ebx
006ace20 call 0x6d9590
006ace25 cmp byte ptr [ebx + 0x16a], 0
006ace2c je 0x6acf44
006ace32 mov eax, dword ptr [esi + 0x283c20]
006ace38 cmp eax, dword ptr [esi + 0x283c24]
006ace3e je 0x6acf44
006ace44 mov eax, dword ptr [ebx + 0x28]
006ace47 lea ecx, [esi + 0x283c48]
006ace4d mov dword ptr [esp + 0x74], eax
006ace51 mov eax, dword ptr [ebx + 0x2c]
006ace54 mov dword ptr [esp + 0x78], eax
006ace58 lea eax, [esp + 0x74]
006ace5c push eax
006ace5d lea eax, [esp + 0x50]
006ace61 push eax
006ace62 call 0x937c80
006ace67 mov eax, dword ptr [esi + 0x283c48]
006ace6d cmp dword ptr [esp + 0x4c], eax
006ace71 jne 0x6aceaf
006ace73 mov eax, dword ptr [ebx + 0x28]
006ace76 lea ecx, [esi + 0x283c48]
006ace7c mov dword ptr [esp + 0x7c], eax
006ace80 lea eax, [esp + 0x7c]
006ace84 push eax
006ace85 lea eax, [esp + 0xa0]
006ace8c mov dword ptr [esp + 0x84], 0xffffffff
006ace97 push eax
006ace98 call 0x937c80
006ace9d mov eax, dword ptr [eax]
006ace9f mov dword ptr [esp + 0x4c], eax
006acea3 cmp eax, dword ptr [esi + 0x283c48]
006acea9 je 0x6acf44
006aceaf mov esi, dword ptr [0xbfd65c]
006aceb5 xor ebx, ebx
006aceb7 mov eax, dword ptr [esi + 0x1ba54]
006acebd sub eax, dword ptr [esi + 0x1ba50]
006acec3 sar eax, 2
006acec6 test eax, eax
006acec8 je 0x6acf44
006aceca mov edi, dword ptr [esp + 0x18]
006acece nop 
006aced0 mov ecx, dword ptr [esi + 0x1ba54]
006aced6 mov eax, ecx
006aced8 sub eax, dword ptr [esi + 0x1ba50]
006acede test eax, 0xfffffffc
006acee3 jne 0x6acefa
006acee5 push 0xb3f4d0
006aceea push 3
006aceec call 0x95e330
006acef1 mov ecx, dword ptr [esi + 0x1ba54]
006acef7 add esp, 8
006acefa mov eax, dword ptr [esi + 0x1ba50]
006acf00 sub ecx, eax
006acf02 sar ecx, 2
006acf05 cmp ebx, ecx
006acf07 jae 0x6acf0c
006acf09 lea eax, [eax + ebx*4]
006acf0c push 0xc02fec
006acf11 lea ecx, [esp + 0x58]
006acf15 push ecx
006acf16 mov ecx, dword ptr [eax]
006acf18 push edi
006acf19 push 6
006acf1b add ecx, 0x1ec0
006acf21 call 0x935fd0
006acf26 mov esi, dword ptr [0xbfd65c]
006acf2c inc ebx
006acf2d mov eax, dword ptr [esi + 0x1ba54]
006acf33 sub eax, dword ptr [esi + 0x1ba50]
006acf39 sar eax, 2
006acf3c cmp ebx, eax
006acf3e jb 0x6aced0
006acf40 mov edi, dword ptr [esp + 0x30]
006acf44 call dword ptr [0xa064c0]
006acf4a sub eax, dword ptr [esp + 0x14]
006acf4e add dword ptr [0xbffe0c], eax
006acf54 mov eax, dword ptr [edi + 0x294]
006acf5a lea ebx, [edi + 0x294]
006acf60 mov ecx, dword ptr [ebx + 4]
006acf63 movss xmm2, dword ptr [0xb6a614]
006acf6b mov dword ptr [esp + 0x84], eax
006acf72 lea eax, [esp + 0x84]
006acf79 mov dword ptr [esp + 0x88], ecx
006acf80 mov ecx, dword ptr [0xbfd65c]
006acf86 push eax
006acf87 call 0x6d5600
006acf8c mov eax, dword ptr [ebx]
006acf8e movups xmm0, xmmword ptr [0xbfec58]
006acf95 mov ecx, dword ptr [ebx + 4]
006acf98 push 0
006acf9a push 0
006acf9c push 0x1004
006acfa1 sub esp, 0x10
006acfa4 mov dword ptr [esp + 0xa8], eax
006acfab mov eax, esp
006acfad mov dword ptr [esp + 0xac], ecx
006acfb4 mov ecx, dword ptr [0xbfd65c]
006acfba push 0
006acfbc push 0
006acfbe sub esp, 8
006acfc1 movups xmmword ptr [eax], xmm0
006acfc4 lea eax, [esp + 0xb8]
006acfcb mov dword ptr [esp + 4], 0x42960000
006acfd3 mov dword ptr [esp], 0x42c80000
006acfda push eax
006acfdb call 0x6d1750
006acfe0 call 0x6c3d90
006acfe5 movd xmm0, eax
006acfe9 cvtdq2pd xmm0, xmm0
006acfed shr eax, 0x1f
006acff0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006acff9 cvtpd2ps xmm0, xmm0
006acffd mulss xmm0, dword ptr [0xb6a19c]
006ad005 call 0x6c3d90
006ad00a mov ecx, 3
006ad00f xor edx, edx
006ad011 div ecx
006ad013 mov ecx, dword ptr [ebx + 4]
006ad016 mov eax, dword ptr [ebx]
006ad018 push 0
006ad01a push ecx
006ad01b mov dword ptr [esp + 0xa0], ecx
006ad022 lea ecx, [esp + 0xb0]
006ad029 mov dword ptr [esp + 0x9c], eax
006ad030 mov dword ptr [esp], 0x47c35000
006ad037 call 0x402120
006ad03c mulss xmm0, dword ptr [0xb6a8cc]
006ad044 push eax
006ad045 push ecx
006ad046 mov ecx, dword ptr [0xbfd65c]
006ad04c lea eax, [edx + 2]
006ad04f addss xmm0, dword ptr [0xb6a7b0]
006ad057 movss dword ptr [esp], xmm0
006ad05c push eax
006ad05d push 0x1b
006ad05f lea eax, [esp + 0xac]
006ad066 push eax
006ad067 call 0x6d57a0
006ad06c push 0
006ad06e push 1
006ad070 mov edx, ebx
006ad072 lea ecx, [esp + 0xa8]
006ad079 call 0x6c3450
006ad07e mov edx, dword ptr [edi + 0x334]
006ad084 add esp, 8
006ad087 test edx, edx
006ad089 jne 0x6ad0a5
006ad08b push 0xb4d6c4
006ad090 push 3
006ad092 call 0x95e330
006ad097 mov edx, dword ptr [edi + 0x334]
006ad09d add esp, 8
006ad0a0 test edx, edx
006ad0a2 jne 0x6ad0a5
006ad0a4 int3 
006ad0a5 mov ecx, dword ptr [edi + 0x338]
006ad0ab mov eax, edx
006ad0ad shr eax, cl
006ad0af mov ecx, dword ptr [edi + 0x33c]
006ad0b5 xor eax, edx
006ad0b7 mov edx, eax
006ad0b9 shl edx, cl
006ad0bb mov ecx, dword ptr [edi + 0x340]
006ad0c1 xor edx, eax
006ad0c3 mov esi, edx
006ad0c5 mov eax, 0x51eb851f
006ad0ca shr esi, cl
006ad0cc xor esi, edx
006ad0ce mul esi
006ad0d0 mov dword ptr [edi + 0x334], esi
006ad0d6 shr edx, 5
006ad0d9 imul eax, edx, 0x64
006ad0dc sub esi, eax
006ad0de jne 0x6ad603
006ad0e4 push 2
006ad0e6 lea ecx, [edi + 0x334]
006ad0ec call 0x7a7d50
006ad0f1 mov esi, dword ptr [0xbfd65c]
006ad0f7 test eax, eax
006ad0f9 jne 0x6ad382
006ad0ff push 0x32
006ad101 lea ecx, [esi + 0x1a5cc]
006ad107 call 0x701d40
006ad10c test al, al
006ad10e je 0x6ad382
006ad114 push 0
006ad116 push 1
006ad118 mov edx, ebx
006ad11a lea ecx, [esp + 0x2c]
006ad11e call 0x6c3450
006ad123 mov esi, dword ptr [0xbfd65c]
006ad129 add esp, 8
006ad12c call 0x6c3d90
006ad131 mov dword ptr [esp + 0x1c], eax
006ad135 lea eax, [esp + 0x1c]
006ad139 push eax
006ad13a lea eax, [esp + 0x24]
006ad13e mov dword ptr [esp + 0x24], 0x32
006ad146 push eax
006ad147 push 0
006ad149 lea eax, [esp + 0x30]
006ad14d mov dword ptr [esp + 0x20], 0x15e
006ad155 push eax
006ad156 push ebx
006ad157 lea eax, [esp + 0x28]
006ad15b mov dword ptr [esp + 0x24], 5
006ad163 push eax
006ad164 lea eax, [esp + 0x28]
006ad168 push eax
006ad169 call 0x800fb0
006ad16e mov ecx, dword ptr [esi + 0x1c3198]
006ad174 push 0
006ad176 push dword ptr [esp + 0x14]
006ad17a call 0x6c4b30
006ad17f mov ebx, eax
006ad181 mov dword ptr [esp + 0x38], ebx
006ad185 test ebx, ebx
006ad187 je 0x6ad603
006ad18d call dword ptr [0xa064c0]
006ad193 mov ecx, dword ptr [ebx + 0x320]
006ad199 mov dword ptr [esp + 0x3c], eax
006ad19d lea eax, [ebx + 0x320]
006ad1a3 mov dword ptr [ebx + 0x34], 0
006ad1aa mov dword ptr [ebx + 0x38], 0
006ad1b1 test ecx, ecx
006ad1b3 je 0x6ad1cf
006ad1b5 mov dword ptr [esp + 0x34], eax
006ad1b9 add ecx, 0x324
006ad1bf lea eax, [esp + 0x34]
006ad1c3 push eax
006ad1c4 call 0x4bc3c0
006ad1c9 lea eax, [ebx + 0x320]
006ad1cf push dword ptr [esp + 0x1c]
006ad1d3 movss xmm0, dword ptr [esp + 0x28]
006ad1d9 mov ecx, ebx
006ad1db push dword ptr [esp + 0x24]
006ad1df mov dword ptr [eax], 0
006ad1e5 mov eax, dword ptr [edi + 0x294]
006ad1eb push dword ptr [esp + 0x1c]
006ad1ef mov dword ptr [ebx + 0x294], eax
006ad1f5 mov eax, dword ptr [edi + 0x298]
006ad1fb push dword ptr [esp + 0x1c]
006ad1ff mov dword ptr [ebx + 0x298], eax
006ad205 mov eax, dword ptr [ebx]
006ad207 movss dword ptr [ebx + 0x2b8], xmm0
006ad20f movss xmm0, dword ptr [esp + 0x38]
006ad215 movss dword ptr [ebx + 0x2bc], xmm0
006ad21d call dword ptr [eax + 4]
006ad220 mov edx, dword ptr [esi + 0x18190]
006ad226 push ebx
006ad227 mov ecx, dword ptr [edx + 0x1214]
006ad22d lea eax, [ecx + 1]
006ad230 mov dword ptr [edx + 0x1214], eax
006ad236 mov dword ptr [ebx + 0x20], ecx
006ad239 lea ecx, [edx + 0x1218]
006ad23f call 0x413280
006ad244 push ebx
006ad245 call 0x6d94d0
006ad24a test al, al
006ad24c je 0x6ad255
006ad24e push ecx
006ad24f push ebx
006ad250 call 0x6d9590
006ad255 cmp byte ptr [ebx + 0x16a], 0
006ad25c je 0x6ad373
006ad262 mov eax, dword ptr [esi + 0x283c20]
006ad268 cmp eax, dword ptr [esi + 0x283c24]
006ad26e je 0x6ad373
006ad274 mov eax, dword ptr [ebx + 0x28]
006ad277 lea ecx, [esi + 0x283c48]
006ad27d mov dword ptr [esp + 0x5c], eax
006ad281 mov eax, dword ptr [ebx + 0x2c]
006ad284 mov dword ptr [esp + 0x60], eax
006ad288 lea eax, [esp + 0x5c]
006ad28c push eax
006ad28d lea eax, [esp + 0x1c]
006ad291 push eax
006ad292 call 0x937c80
006ad297 mov eax, dword ptr [esi + 0x283c48]
006ad29d cmp dword ptr [esp + 0x18], eax
006ad2a1 jne 0x6ad2d9
006ad2a3 mov eax, dword ptr [ebx + 0x28]
006ad2a6 lea ecx, [esi + 0x283c48]
006ad2ac mov dword ptr [esp + 0x64], eax
006ad2b0 lea eax, [esp + 0x64]
006ad2b4 push eax
006ad2b5 lea eax, [esp + 0x74]
006ad2b9 mov dword ptr [esp + 0x6c], 0xffffffff
006ad2c1 push eax
006ad2c2 call 0x937c80
006ad2c7 mov eax, dword ptr [eax]
006ad2c9 mov dword ptr [esp + 0x18], eax
006ad2cd cmp eax, dword ptr [esi + 0x283c48]
006ad2d3 je 0x6ad373
006ad2d9 mov esi, dword ptr [0xbfd65c]
006ad2df xor ebx, ebx
006ad2e1 mov eax, dword ptr [esi + 0x1ba54]
006ad2e7 sub eax, dword ptr [esi + 0x1ba50]
006ad2ed sar eax, 2
006ad2f0 test eax, eax
006ad2f2 je 0x6ad373
006ad2f4 mov edi, dword ptr [esp + 0x38]
006ad2f8 nop dword ptr [eax + eax]
006ad300 mov ecx, dword ptr [esi + 0x1ba54]
006ad306 mov eax, ecx
006ad308 sub eax, dword ptr [esi + 0x1ba50]
006ad30e test eax, 0xfffffffc
006ad313 jne 0x6ad32a
006ad315 push 0xb3f4d0
006ad31a push 3
006ad31c call 0x95e330
006ad321 mov ecx, dword ptr [esi + 0x1ba54]
006ad327 add esp, 8
006ad32a mov eax, dword ptr [esi + 0x1ba50]
006ad330 sub ecx, eax
006ad332 sar ecx, 2
006ad335 cmp ebx, ecx
006ad337 jae 0x6ad33c
006ad339 lea eax, [eax + ebx*4]
006ad33c lea ecx, [esp + 0x24]
006ad340 push ecx
006ad341 push dword ptr [esp + 0x54]
006ad345 mov ecx, dword ptr [eax]
006ad347 push edi
006ad348 push 6
006ad34a add ecx, 0x1ec0
006ad350 call 0x935fd0
006ad355 mov esi, dword ptr [0xbfd65c]
006ad35b inc ebx
006ad35c mov eax, dword ptr [esi + 0x1ba54]
006ad362 sub eax, dword ptr [esi + 0x1ba50]
006ad368 sar eax, 2
006ad36b cmp ebx, eax
006ad36d jb 0x6ad300
006ad36f mov edi, dword ptr [esp + 0x30]
006ad373 call dword ptr [0xa064c0]
006ad379 sub eax, dword ptr [esp + 0x3c]
006ad37d jmp 0x6ad5fd
006ad382 push 0x29
006ad384 lea ecx, [esi + 0x1a5cc]
006ad38a call 0x701d40
006ad38f test al, al
006ad391 je 0x6ad603
006ad397 push 0
006ad399 push 1
006ad39b mov edx, ebx
006ad39d lea ecx, [esp + 0x2c]
006ad3a1 call 0x6c3450
006ad3a6 mov esi, dword ptr [0xbfd65c]
006ad3ac add esp, 8
006ad3af call 0x6c3d90
006ad3b4 mov dword ptr [esp + 0x18], eax
006ad3b8 lea eax, [esp + 0x18]
006ad3bc push eax
006ad3bd lea eax, [esp + 0x18]
006ad3c1 mov dword ptr [esp + 0x18], 0x29
006ad3c9 push eax
006ad3ca push 0
006ad3cc lea eax, [esp + 0x30]
006ad3d0 mov dword ptr [esp + 0x2c], 0x15e
006ad3d8 push eax
006ad3d9 push ebx
006ad3da lea eax, [esp + 0x34]
006ad3de mov dword ptr [esp + 0x24], 5
006ad3e6 push eax
006ad3e7 lea eax, [esp + 0x28]
006ad3eb push eax
006ad3ec call 0x800fb0
006ad3f1 mov ecx, dword ptr [esi + 0x1c3198]
006ad3f7 push 0
006ad3f9 push dword ptr [esp + 0x14]
006ad3fd call 0x6c4b30
006ad402 mov ebx, eax
006ad404 mov dword ptr [esp + 0x38], ebx
006ad408 test ebx, ebx
006ad40a je 0x6ad603
006ad410 call dword ptr [0xa064c0]
006ad416 mov ecx, dword ptr [ebx + 0x320]
006ad41c mov dword ptr [esp + 0x34], eax
006ad420 lea eax, [ebx + 0x320]
006ad426 mov dword ptr [ebx + 0x34], 0
006ad42d mov dword ptr [ebx + 0x38], 0
006ad434 test ecx, ecx
006ad436 je 0x6ad452
006ad438 mov dword ptr [esp + 0x3c], eax
006ad43c add ecx, 0x324
006ad442 lea eax, [esp + 0x3c]
006ad446 push eax
006ad447 call 0x4bc3c0
006ad44c lea eax, [ebx + 0x320]
006ad452 push dword ptr [esp + 0x18]
006ad456 movss xmm0, dword ptr [esp + 0x28]
006ad45c mov ecx, ebx
006ad45e push dword ptr [esp + 0x18]
006ad462 mov dword ptr [eax], 0
006ad468 mov eax, dword ptr [edi + 0x294]
006ad46e push dword ptr [esp + 0x28]
006ad472 mov dword ptr [ebx + 0x294], eax
006ad478 mov eax, dword ptr [edi + 0x298]
006ad47e push dword ptr [esp + 0x1c]
006ad482 mov dword ptr [ebx + 0x298], eax
006ad488 mov eax, dword ptr [ebx]
006ad48a movss dword ptr [ebx + 0x2b8], xmm0
006ad492 movss xmm0, dword ptr [esp + 0x38]
006ad498 movss dword ptr [ebx + 0x2bc], xmm0
006ad4a0 call dword ptr [eax + 4]
006ad4a3 mov edx, dword ptr [esi + 0x18190]
006ad4a9 push ebx
006ad4aa mov ecx, dword ptr [edx + 0x1214]
006ad4b0 lea eax, [ecx + 1]
006ad4b3 mov dword ptr [edx + 0x1214], eax
006ad4b9 mov dword ptr [ebx + 0x20], ecx
006ad4bc lea ecx, [edx + 0x1218]
006ad4c2 call 0x413280
006ad4c7 push ebx
006ad4c8 call 0x6d94d0
006ad4cd test al, al
006ad4cf je 0x6ad4d8
006ad4d1 push ecx
006ad4d2 push ebx
006ad4d3 call 0x6d9590
006ad4d8 cmp byte ptr [ebx + 0x16a], 0
006ad4df je 0x6ad5f3
006ad4e5 mov eax, dword ptr [esi + 0x283c20]
006ad4eb cmp eax, dword ptr [esi + 0x283c24]
006ad4f1 je 0x6ad5f3
006ad4f7 mov eax, dword ptr [ebx + 0x28]
006ad4fa lea ecx, [esi + 0x283c48]
006ad500 mov dword ptr [esp + 0x64], eax
006ad504 mov eax, dword ptr [ebx + 0x2c]
006ad507 mov dword ptr [esp + 0x68], eax
006ad50b lea eax, [esp + 0x64]
006ad50f push eax
006ad510 lea eax, [esp + 0x20]
006ad514 push eax
006ad515 call 0x937c80
006ad51a mov eax, dword ptr [esi + 0x283c48]
006ad520 cmp dword ptr [esp + 0x1c], eax
006ad524 jne 0x6ad55c
006ad526 mov eax, dword ptr [ebx + 0x28]
006ad529 lea ecx, [esi + 0x283c48]
006ad52f mov dword ptr [esp + 0x5c], eax
006ad533 lea eax, [esp + 0x5c]
006ad537 push eax
006ad538 lea eax, [esp + 0x74]
006ad53c mov dword ptr [esp + 0x64], 0xffffffff
006ad544 push eax
006ad545 call 0x937c80
006ad54a mov eax, dword ptr [eax]
006ad54c mov dword ptr [esp + 0x1c], eax
006ad550 cmp eax, dword ptr [esi + 0x283c48]
006ad556 je 0x6ad5f3
006ad55c mov esi, dword ptr [0xbfd65c]
006ad562 xor ebx, ebx
006ad564 mov eax, dword ptr [esi + 0x1ba54]
006ad56a sub eax, dword ptr [esi + 0x1ba50]
006ad570 sar eax, 2
006ad573 test eax, eax
006ad575 je 0x6ad5f3
006ad577 mov edi, dword ptr [esp + 0x38]
006ad57b nop dword ptr [eax + eax]
006ad580 mov ecx, dword ptr [esi + 0x1ba54]
006ad586 mov eax, ecx
006ad588 sub eax, dword ptr [esi + 0x1ba50]
006ad58e test eax, 0xfffffffc
006ad593 jne 0x6ad5aa
006ad595 push 0xb3f4d0
006ad59a push 3
006ad59c call 0x95e330
006ad5a1 mov ecx, dword ptr [esi + 0x1ba54]
006ad5a7 add esp, 8
006ad5aa mov eax, dword ptr [esi + 0x1ba50]
006ad5b0 sub ecx, eax
006ad5b2 sar ecx, 2
006ad5b5 cmp ebx, ecx
006ad5b7 jae 0x6ad5bc
006ad5b9 lea eax, [eax + ebx*4]
006ad5bc lea ecx, [esp + 0x24]
006ad5c0 push ecx
006ad5c1 push dword ptr [esp + 0x54]
006ad5c5 mov ecx, dword ptr [eax]
006ad5c7 push edi
006ad5c8 push 6
006ad5ca add ecx, 0x1ec0
006ad5d0 call 0x935fd0
006ad5d5 mov esi, dword ptr [0xbfd65c]
006ad5db inc ebx
006ad5dc mov eax, dword ptr [esi + 0x1ba54]
006ad5e2 sub eax, dword ptr [esi + 0x1ba50]
006ad5e8 sar eax, 2
006ad5eb cmp ebx, eax
006ad5ed jb 0x6ad580
006ad5ef mov edi, dword ptr [esp + 0x30]
006ad5f3 call dword ptr [0xa064c0]
006ad5f9 sub eax, dword ptr [esp + 0x34]
006ad5fd add dword ptr [0xbffe0c], eax
006ad603 cmp dword ptr [edi + 0x32c], 0
006ad60a je 0x6ad6b4
006ad610 mov eax, dword ptr [edi]
006ad612 mov ecx, edi
006ad614 call dword ptr [eax + 0x28]
006ad617 mov eax, dword ptr [edi + 0xab4]
006ad61d movss xmm3, dword ptr [0xb6a614]
006ad625 movss xmm4, dword ptr [0xb6a7b0]
006ad62d cmp eax, 3
006ad630 jne 0x6ad6ad
006ad632 movss xmm0, dword ptr [edi + 0x2d8]
006ad63a comiss xmm0, dword ptr [0xb6a864]
006ad641 jbe 0x6ad64c
006ad643 push 0
006ad645 push 0xb3fd8c
006ad64a jmp 0x6ad666
006ad64c comiss xmm0, xmm4
006ad64f jbe 0x6ad65a
006ad651 push 0
006ad653 push 0xb49290
006ad658 jmp 0x6ad666
006ad65a comiss xmm0, xmm3
006ad65d jbe 0x6ad66e
006ad65f push 0
006ad661 push 0xb4929c
006ad666 lea ecx, [edi + 0x3c]
006ad669 call 0x4054f0
006ad66e movss xmm0, dword ptr [edi + 0x2c4]
006ad676 mulss xmm0, dword ptr [0xb6a560]
006ad67e mov eax, dword ptr [edi + 0xb10]
006ad684 movss dword ptr [edi + 0x2c4], xmm0
006ad68c cmp eax, -4
006ad68f jle 0x6ad700
006ad691 dec eax
006ad692 mov dword ptr [edi + 0xb10], eax
006ad698 pop edi
006ad699 pop esi
006ad69a pop ebx
006ad69b mov ecx, dword ptr [esp + 0xc8]
006ad6a2 xor ecx, esp
006ad6a4 call 0x9eacd7
006ad6a9 mov esp, ebp
006ad6ab pop ebp
006ad6ac ret 
006ad6ad cmp eax, 0x10
006ad6b0 jne 0x6ad700
006ad6b2 jmp 0x6ad6cf
006ad6b4 mov byte ptr [edi + 0x16b], 0
006ad6bb mov dword ptr [edi + 0xab4], 0x10
006ad6c5 mov dword ptr [edi + 0x2d8], 0x3f000000
006ad6cf push 0
006ad6d1 push 0xb492ac
006ad6d6 lea ecx, [edi + 0x3c]
006ad6d9 mov dword ptr [edi + 0x180], 0
006ad6e3 call 0x4054f0
006ad6e8 movss xmm0, dword ptr [edi + 0x2c4]
006ad6f0 mulss xmm0, dword ptr [0xb6a3b0]
006ad6f8 movss dword ptr [edi + 0x2c4], xmm0
006ad700 mov ecx, dword ptr [esp + 0xd4]
006ad707 pop edi
006ad708 pop esi
006ad709 pop ebx
006ad70a xor ecx, esp
006ad70c call 0x9eacd7
006ad711 mov esp, ebp
006ad713 pop ebp
006ad714 ret 
006ad715 int3 
006ad716 int3 
006ad717 int3 
006ad718 int3 
006ad719 int3 
006ad71a int3 
006ad71b int3 
006ad71c int3 
006ad71d int3 
006ad71e int3 
006ad71f int3 
006ad720 push ebp
006ad721 mov ebp, esp
006ad723 mov eax, dword ptr [ecx + 0xbb4]
006ad729 movss xmm0, dword ptr [ebp + 0x18]
006ad72e push esi
006ad72f cmp eax, 0x12
006ad732 jne 0x6ad73e
006ad734 addss xmm0, dword ptr [0xb6a480]
006ad73c jmp 0x6ad74b
006ad73e cmp eax, 0x13
006ad741 jne 0x6ad74b
006ad743 mulss xmm0, dword ptr [0xb6a480]
006ad74b mov eax, dword ptr [ebp + 8]
006ad74e lea ecx, [ebp + 8]
006ad751 mov esi, dword ptr [0xbfd680]
006ad757 movss dword ptr [ebp + 0x18], xmm0
006ad75c mov dword ptr [ebp + 8], eax
006ad75f call 0x8b1340
006ad764 movss xmm0, dword ptr [ebp + 0x18]
006ad769 sub esp, 8
006ad76c mov dword ptr [esp + 4], 0
006ad774 movss dword ptr [esp], xmm0
006ad779 push dword ptr [ebp + 0x14]
006ad77c movss xmm0, dword ptr [ebp + 0xc]
006ad781 push dword ptr [ebp + 0x10]
006ad784 push ecx
006ad785 movss dword ptr [esp], xmm0
006ad78a lea ecx, [esi + 0x29de0]
006ad790 push dword ptr [ebp + 8]
006ad793 call 0x888de0
006ad798 pop esi
006ad799 pop ebp
006ad79a ret 0x14
006ad79d int3 
006ad79e int3 
006ad79f int3 
006ad7a0 push ebp
006ad7a1 mov ebp, esp
006ad7a3 and esp, 0xfffffff8
006ad7a6 push ecx
006ad7a7 mov eax, dword ptr [ecx + 0x160]
006ad7ad and eax, 0x20000000
006ad7b2 or eax, 0
006ad7b5 mov eax, dword ptr [0xbfd65c]
006ad7ba push ebx
006ad7bb push esi
006ad7bc push edi
006ad7bd mov eax, dword ptr [eax + 0x18190]
006ad7c3 je 0x6ad851
006ad7c9 mov ebx, dword ptr [eax + 0x1264]
006ad7cf xor edi, edi
006ad7d1 xor esi, esi
006ad7d3 test ebx, ebx
006ad7d5 je 0x6ad848
006ad7d7 mov eax, dword ptr [eax + 0x125c]
006ad7dd mov dword ptr [esp + 0xc], eax
006ad7e1 mov edx, dword ptr [eax + esi*4]
006ad7e4 mov eax, dword ptr [edx + 0x28]
006ad7e7 lea ecx, [eax - 0xa]
006ad7ea cmp ecx, 0x3dd
006ad7f0 ja 0x6ad83f
006ad7f2 cmp eax, 0x21
006ad7f5 je 0x6ad83f
006ad7f7 cmp eax, 0x11
006ad7fa je 0x6ad83f
006ad7fc cmp eax, 0x124
006ad801 je 0x6ad83f
006ad803 cmp eax, 0x375
006ad808 jne 0x6ad810
006ad80a cmp dword ptr [edx + 0x2c], 0xa
006ad80e jmp 0x6ad823
006ad810 cmp eax, 0x3c0
006ad815 je 0x6ad83f
006ad817 cmp eax, 0x3c5
006ad81c je 0x6ad83f
006ad81e cmp eax, 0xf5
006ad823 je 0x6ad83f
006ad825 cmp byte ptr [edx + 0x16b], 0
006ad82c jne 0x6ad83f
006ad82e mov eax, dword ptr [edx + 0x160]
006ad834 and eax, 0x20000000
006ad839 or eax, 0
006ad83c je 0x6ad83f
006ad83e inc edi
006ad83f mov eax, dword ptr [esp + 0xc]
006ad843 inc esi
006ad844 cmp esi, ebx
006ad846 jb 0x6ad7e1
006ad848 mov eax, edi
006ad84a pop edi
006ad84b pop esi
006ad84c pop ebx
006ad84d mov esp, ebp
006ad84f pop ebp
006ad850 ret 
006ad851 mov ecx, dword ptr [eax + 0x12c4]
006ad857 mov eax, dword ptr [eax + 0x12c0]
006ad85d add ecx, eax
006ad85f xor eax, eax
006ad861 test ecx, ecx
006ad863 pop edi
006ad864 pop esi
006ad865 cmovg eax, ecx
006ad868 pop ebx
006ad869 mov esp, ebp
006ad86b pop ebp
006ad86c ret 
006ad86d int3 
006ad86e int3 
006ad86f int3 
006ad870 push esi
006ad871 mov esi, ecx
006ad873 mov eax, dword ptr [esi + 0x28]
006ad876 cmp eax, 0x24
006ad879 je 0x6ad8c0
006ad87b cmp eax, 0x54
006ad87e je 0x6ad8c0
006ad880 cmp eax, 0x3b7
006ad885 jne 0x6ad8ca
006ad887 mov eax, dword ptr [esi + 0x2c]
006ad88a sub eax, 0x66
006ad88d cmp eax, 2
006ad890 ja 0x6ad8ca
006ad892 cmp dword ptr [esi + 0xab4], 3
006ad899 jne 0x6ad8ca
006ad89b mov dword ptr [esi + 0xab4], 8
006ad8a5 call 0x6c3d90
006ad8aa xor edx, edx
006ad8ac mov ecx, 0xf
006ad8b1 div ecx
006ad8b3 add edx, 2
006ad8b6 mov dword ptr [esi + 0x360], edx
006ad8bc pop esi
006ad8bd ret 0x10
006ad8c0 mov dword ptr [esi + 0xb00], 0x3f800000
006ad8ca pop esi
006ad8cb ret 0x10
006ad8ce int3 
006ad8cf int3 
006ad8d0 push ebp
006ad8d1 mov ebp, esp
006ad8d3 and esp, 0xfffffff8
006ad8d6 sub esp, 0x44
006ad8d9 mov eax, dword ptr [0xbaa3b4]
006ad8de xor eax, esp
006ad8e0 mov dword ptr [esp + 0x40], eax
006ad8e4 push ebx
006ad8e5 push esi
006ad8e6 mov esi, ecx
006ad8e8 push edi
006ad8e9 mov eax, dword ptr [esi + 0x28]
006ad8ec cmp eax, 0x362
006ad8f1 jne 0x6ad8f9
006ad8f3 cmp dword ptr [esi + 0x2c], 0
006ad8f7 jmp 0x6ad8fe
006ad8f9 cmp eax, 0x363
006ad8fe jne 0x6adb23
006ad904 mov ecx, dword ptr [0xbfd65c]
006ad90a mov eax, dword ptr [ecx + 0x1a30dc]
006ad910 sub eax, dword ptr [esi + 0x280]
006ad916 cmp eax, 1
006ad919 jle 0x6adb23
006ad91f push dword ptr [ecx + 0x181a0]
006ad925 push dword ptr [ecx + 0x18198]
006ad92b call 0x70e0f0
006ad930 mov ecx, dword ptr [0xbfd65c]
006ad936 mov edi, dword ptr [eax]
006ad938 push dword ptr [ecx + 0x1819c]
006ad93e mov dword ptr [esp + 0x10], edi
006ad942 push dword ptr [ecx + 0x18194]
006ad948 call 0x70e0f0
006ad94d mov ebx, dword ptr [eax]
006ad94f test edi, edi
006ad951 js 0x6ad98d
006ad953 test ebx, ebx
006ad955 js 0x6ad98d
006ad957 mov eax, 0x4ec4ec4f
006ad95c imul ebx
006ad95e mov eax, 0x4ec4ec4f
006ad963 sar edx, 2
006ad966 mov ecx, edx
006ad968 shr ecx, 0x1f
006ad96b add ecx, edx
006ad96d imul edi
006ad96f mov eax, ecx
006ad971 sar edx, 2
006ad974 mov edi, edx
006ad976 shr edi, 0x1f
006ad979 add edi, edx
006ad97b sub eax, edi
006ad97d imul eax, eax, 0xd
006ad980 sub eax, ebx
006ad982 add eax, dword ptr [esp + 0xc]
006ad986 sub edi, ecx
006ad988 jmp 0x6ada2b
006ad98d mov ecx, dword ptr [0xbfd65c]
006ad993 mov edx, dword ptr [ecx + 0x181ac]
006ad999 test edx, edx
006ad99b jns 0x6ad9f8
006ad99d push dword ptr [ecx + 0x1819c]
006ad9a3 push dword ptr [ecx + 0x18194]
006ad9a9 call 0x70e0f0
006ad9ae movq xmm0, qword ptr [0xa08adc]
006ad9b6 mov ebx, dword ptr [0xa08ae4]
006ad9bc movq qword ptr [esp + 0x14], xmm0
006ad9c2 mov edi, dword ptr [eax + 0x58]
006ad9c5 test edi, edi
006ad9c7 jne 0x6ad9d9
006ad9c9 push 0xb4d6c4
006ad9ce push 3
006ad9d0 call 0x95e330
006ad9d5 add esp, 8
006ad9d8 int3 
006ad9d9 mov ecx, dword ptr [esp + 0x14]
006ad9dd mov edx, edi
006ad9df shr edx, cl
006ad9e1 mov ecx, dword ptr [esp + 0x18]
006ad9e5 xor edx, edi
006ad9e7 mov eax, edx
006ad9e9 shl eax, cl
006ad9eb mov ecx, ebx
006ad9ed xor eax, edx
006ad9ef mov edx, eax
006ad9f1 shr edx, cl
006ad9f3 xor edx, eax
006ad9f5 and edx, 3
006ad9f8 xor edi, edi
006ad9fa xor eax, eax
006ad9fc and edx, 0x80000003
006ada02 jns 0x6ada09
006ada04 dec edx
006ada05 or edx, 0xfffffffc
006ada08 inc edx
006ada09 cmp edx, 3
006ada0c ja 0x6ada2b
006ada0e jmp dword ptr [edx*4 + 0x6adb38]
006ada15 or eax, 0xffffffff
006ada18 jmp 0x6ada2b
006ada1a mov eax, 1
006ada1f jmp 0x6ada2b
006ada21 or edi, 0xffffffff
006ada24 jmp 0x6ada2b
006ada26 mov edi, 1
006ada2b movd xmm0, eax
006ada2f lea ebx, [esi + 0x294]
006ada35 cvtdq2ps xmm0, xmm0
006ada38 mulss xmm0, dword ptr [0xb6ac90]
006ada40 addss xmm0, dword ptr [ebx]
006ada44 movss dword ptr [ebx], xmm0
006ada48 movd xmm0, edi
006ada4c cvtdq2ps xmm0, xmm0
006ada4f mulss xmm0, dword ptr [0xb6ac04]
006ada57 addss xmm0, dword ptr [ebx + 4]
006ada5c movss dword ptr [ebx + 4], xmm0
006ada61 cmp dword ptr [esi + 0x28], 0x362
006ada68 jne 0x6adb23
006ada6e cmp dword ptr [esi + 0x2c], 0
006ada72 jne 0x6adb23
006ada78 cmp dword ptr [esi + 0x30], 1
006ada7c jne 0x6adb23
006ada82 mov eax, dword ptr [esi + 0x314]
006ada88 test eax, eax
006ada8a je 0x6adb23
006ada90 cmp dword ptr [eax + 0x28], 0x362
006ada97 jne 0x6adb23
006ada9d mov ecx, dword ptr [esi + 0x320]
006adaa3 test ecx, ecx
006adaa5 je 0x6adb23
006adaa7 cmp dword ptr [ecx + 0x28], 1
006adaab jne 0x6adb23
006adaad mov eax, dword ptr [ecx + 0x130c]
006adab3 cmp eax, 0x25
006adab6 je 0x6adabd
006adab8 cmp eax, 0x27
006adabb jne 0x6adb23
006adabd push 0
006adabf push 0x26b
006adac4 call 0x73af30
006adac9 test al, al
006adacb jne 0x6adb23
006adacd mov eax, dword ptr [esi]
006adacf mov ecx, esi
006adad1 call dword ptr [eax + 0x28]
006adad4 call 0x6c3d90
006adad9 mov ecx, dword ptr [0xbfd65c]
006adadf push 0
006adae1 push eax
006adae2 push 0
006adae4 push esi
006adae5 push 0xc02fec
006adaea push ebx
006adaeb push 0xf
006adaed push 0x3e8
006adaf2 call 0x6d0ca0
006adaf7 movss xmm3, dword ptr [0xb6a2cc]
006adaff lea ecx, [esp + 0x20]
006adb03 push 1
006adb05 push 0
006adb07 mov edx, eax
006adb09 movaps xmm2, xmm3
006adb0c push 0xff
006adb11 push -1
006adb13 movaps xmm1, xmm3
006adb16 mov esi, dword ptr [edx]
006adb18 call 0x427080
006adb1d push eax
006adb1e mov ecx, edx
006adb20 call dword ptr [esi + 0x38]
006adb23 mov ecx, dword ptr [esp + 0x4c]
006adb27 pop edi
006adb28 pop esi
006adb29 pop ebx
006adb2a xor ecx, esp
006adb2c call 0x9eacd7
006adb31 mov esp, ebp
006adb33 pop ebp
006adb34 ret 
006adb35 nop dword ptr [eax]
006adb38 adc eax, 0x21006ada
006adb3d fisubr dword ptr [edx]
006adb40 sbb bl, dl
006adb42 push 0
006adb44 fisubr dword ptr es:[edx]
006adb48 int3 
006adb49 int3 
006adb4a int3 
006adb4b int3 
006adb4c int3 
006adb4d int3 
006adb4e int3 
006adb4f int3 
006adb50 push ebp
006adb51 mov ebp, esp
006adb53 and esp, 0xffffffc0
006adb56 sub esp, 0x74
006adb59 push ebx
006adb5a mov ebx, ecx
006adb5c push esi
006adb5d push edi
006adb5e mov dword ptr [esp + 0x48], ebx
006adb62 cmp dword ptr [ebx + 0x28], 0x3c4
006adb69 je 0x6adb9d
006adb6b mov ecx, dword ptr [0xbfd65c]
006adb71 push 1
006adb73 add ecx, 0x1ba40
006adb79 push ecx
006adb7a push 0x193
006adb7f call 0x91d340
006adb84 test eax, eax
006adb86 je 0x6adfc2
006adb8c push 0
006adb8e mov ecx, ebx
006adb90 call 0x68cf40
006adb95 test al, al
006adb97 je 0x6adfc2
006adb9d cmp byte ptr [ebx + 0x169], 0
006adba4 je 0x6adfc2
006adbaa movss xmm0, dword ptr [ebx + 0xf0]
006adbb2 xorps xmm2, xmm2
006adbb5 comiss xmm0, xmm2
006adbb8 jbe 0x6adfc2
006adbbe movss xmm0, dword ptr [ebx + 0x2d8]
006adbc6 comiss xmm0, xmm2
006adbc9 jbe 0x6adfc2
006adbcf mov ecx, ebx
006adbd1 call 0x681360
006adbd6 cmp eax, ebx
006adbd8 jne 0x6adfc2
006adbde cmp byte ptr [ebx + 0x308], 0
006adbe5 jne 0x6adfc2
006adbeb mov esi, dword ptr [ebx + 8]
006adbee mov dword ptr [esp + 0x4c], esi
006adbf2 cmp esi, dword ptr [ebx + 0xc]
006adbf5 je 0x6adfc2
006adbfb nop dword ptr [eax + eax]
006adc00 movss xmm0, dword ptr [esi]
006adc04 comiss xmm0, xmm2
006adc07 jbe 0x6adfb2
006adc0d call 0x6c3d90
006adc12 mov edi, eax
006adc14 mov dword ptr [esp + 0x68], 0
006adc1c call 0x6c3d90
006adc21 movss xmm1, dword ptr [0xb6ae7c]
006adc29 mov dword ptr [esp + 0x38], edi
006adc2d mov dword ptr [esp + 0x3c], 0
006adc35 movd xmm0, eax
006adc39 cvtdq2pd xmm0, xmm0
006adc3d shr eax, 0x1f
006adc40 mov dword ptr [esp + 0x40], 1
006adc48 mov dword ptr [esp + 0x30], 0x2329
006adc50 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006adc59 mov eax, dword ptr [0xbfd65c]
006adc5e mov dword ptr [esp + 0x34], eax
006adc62 lea eax, [esp + 0x38]
006adc66 push eax
006adc67 lea eax, [esp + 0x40]
006adc6b cvtpd2ps xmm0, xmm0
006adc6f push eax
006adc70 push 0
006adc72 lea eax, [esp + 0x74]
006adc76 push eax
006adc77 lea eax, [esp + 0x70]
006adc7b push eax
006adc7c mulss xmm0, dword ptr [0xb6a19c]
006adc84 lea eax, [esp + 0x54]
006adc88 push eax
006adc89 lea eax, [esp + 0x48]
006adc8d push eax
006adc8e addss xmm0, xmm0
006adc92 subss xmm1, xmm0
006adc96 movss xmm0, dword ptr [ebx + 0x294]
006adc9e subss xmm0, xmm2
006adca2 movss dword ptr [esp + 0x70], xmm1
006adca8 movss dword ptr [esp + 0x7c], xmm0
006adcae movss xmm0, dword ptr [ebx + 0x298]
006adcb6 subss xmm0, dword ptr [0xb6a9c8]
006adcbe movss dword ptr [esp + 0x88], xmm1
006adcc7 movss dword ptr [esp + 0x80], xmm0
006adcd0 call 0x800fb0
006adcd5 mov edi, dword ptr [esp + 0x34]
006adcd9 push 0
006adcdb push dword ptr [esp + 0x34]
006adcdf mov ecx, dword ptr [edi + 0x1c3198]
006adce5 call 0x6c4b30
006adcea mov ebx, eax
006adcec mov dword ptr [esp + 0x34], ebx
006adcf0 test ebx, ebx
006adcf2 je 0x6adef8
006adcf8 call dword ptr [0xa064c0]
006adcfe mov ecx, dword ptr [ebx + 0x320]
006add04 mov dword ptr [esp + 0x58], eax
006add08 lea eax, [ebx + 0x320]
006add0e mov dword ptr [ebx + 0x34], 0
006add15 mov dword ptr [ebx + 0x38], 0
006add1c test ecx, ecx
006add1e je 0x6add3a
006add20 mov dword ptr [esp + 0x50], eax
006add24 add ecx, 0x324
006add2a lea eax, [esp + 0x50]
006add2e push eax
006add2f call 0x4bc3c0
006add34 lea eax, [ebx + 0x320]
006add3a push dword ptr [esp + 0x38]
006add3e mov dword ptr [eax], 0
006add44 mov ecx, ebx
006add46 movss xmm0, dword ptr [esp + 0x64]
006add4c push dword ptr [esp + 0x40]
006add50 mov eax, dword ptr [ebx]
006add52 push dword ptr [esp + 0x48]
006add56 movss dword ptr [ebx + 0x294], xmm0
006add5e movss xmm0, dword ptr [esp + 0x70]
006add64 push dword ptr [esp + 0x3c]
006add68 movss dword ptr [ebx + 0x298], xmm0
006add70 movss xmm0, dword ptr [esp + 0x64]
006add76 mov dword ptr [ebx + 0x2b8], 0
006add80 movss dword ptr [ebx + 0x2bc], xmm0
006add88 call dword ptr [eax + 4]
006add8b mov edx, dword ptr [edi + 0x18190]
006add91 push ebx
006add92 mov ecx, dword ptr [edx + 0x1214]
006add98 lea eax, [ecx + 1]
006add9b mov dword ptr [edx + 0x1214], eax
006adda1 mov dword ptr [ebx + 0x20], ecx
006adda4 lea ecx, [edx + 0x1218]
006addaa call 0x413280
006addaf push ebx
006addb0 call 0x6d94d0
006addb5 test al, al
006addb7 je 0x6addc0
006addb9 push ecx
006addba push ebx
006addbb call 0x6d9590
006addc0 cmp byte ptr [ebx + 0x16a], 0
006addc7 je 0x6adee8
006addcd mov eax, dword ptr [edi + 0x283c20]
006addd3 cmp eax, dword ptr [edi + 0x283c24]
006addd9 je 0x6adee8
006adddf mov eax, dword ptr [ebx + 0x2c]
006adde2 mov ecx, dword ptr [ebx + 0x28]
006adde5 mov dword ptr [esp + 0x74], eax
006adde9 lea eax, [esp + 0x70]
006added push eax
006addee lea eax, [esp + 0x48]
006addf2 mov dword ptr [esp + 0x74], ecx
006addf6 push eax
006addf7 lea ecx, [edi + 0x283c48]
006addfd call 0x937c80
006ade02 mov eax, dword ptr [edi + 0x283c48]
006ade08 cmp dword ptr [esp + 0x44], eax
006ade0c jne 0x6ade47
006ade0e mov eax, dword ptr [ebx + 0x28]
006ade11 lea ecx, [edi + 0x283c48]
006ade17 mov dword ptr [esp + 0x78], eax
006ade1b lea eax, [esp + 0x78]
006ade1f push eax
006ade20 lea eax, [esp + 0x60]
006ade24 mov dword ptr [esp + 0x80], 0xffffffff
006ade2f push eax
006ade30 call 0x937c80
006ade35 mov eax, dword ptr [eax]
006ade37 mov dword ptr [esp + 0x44], eax
006ade3b cmp eax, dword ptr [edi + 0x283c48]
006ade41 je 0x6adee8
006ade47 mov edi, dword ptr [0xbfd65c]
006ade4d xor ebx, ebx
006ade4f mov eax, dword ptr [edi + 0x1ba54]
006ade55 sub eax, dword ptr [edi + 0x1ba50]
006ade5b sar eax, 2
006ade5e test eax, eax
006ade60 je 0x6adee4
006ade66 mov esi, dword ptr [esp + 0x34]
006ade6a nop word ptr [eax + eax]
006ade70 mov ecx, dword ptr [edi + 0x1ba54]
006ade76 mov eax, ecx
006ade78 sub eax, dword ptr [edi + 0x1ba50]
006ade7e test eax, 0xfffffffc
006ade83 jne 0x6ade9a
006ade85 push 0xb3f4d0
006ade8a push 3
006ade8c call 0x95e330
006ade91 mov ecx, dword ptr [edi + 0x1ba54]
006ade97 add esp, 8
006ade9a mov eax, dword ptr [edi + 0x1ba50]
006adea0 sub ecx, eax
006adea2 sar ecx, 2
006adea5 cmp ebx, ecx
006adea7 jae 0x6adeac
006adea9 lea eax, [eax + ebx*4]
006adeac lea ecx, [esp + 0x68]
006adeb0 push ecx
006adeb1 lea ecx, [esp + 0x64]
006adeb5 push ecx
006adeb6 mov ecx, dword ptr [eax]
006adeb8 push esi
006adeb9 push 6
006adebb add ecx, 0x1ec0
006adec1 call 0x935fd0
006adec6 mov edi, dword ptr [0xbfd65c]
006adecc inc ebx
006adecd mov eax, dword ptr [edi + 0x1ba54]
006aded3 sub eax, dword ptr [edi + 0x1ba50]
006aded9 sar eax, 2
006adedc cmp ebx, eax
006adede jb 0x6ade70
006adee0 mov esi, dword ptr [esp + 0x4c]
006adee4 mov ebx, dword ptr [esp + 0x34]
006adee8 call dword ptr [0xa064c0]
006adeee sub eax, dword ptr [esp + 0x58]
006adef2 add dword ptr [0xbffe0c], eax
006adef8 movss xmm0, dword ptr [esi]
006adefc sub esp, 8
006adeff mulss xmm0, dword ptr [0xb6a974]
006adf07 addss xmm0, dword ptr [0xb6a480]
006adf0f movss dword ptr [esp + 0x60], xmm0
006adf15 fld dword ptr [esp + 0x60]
006adf19 fstp qword ptr [esp]
006adf1c call 0x9ec3b2
006adf21 fstp dword ptr [esp + 0x60]
006adf25 fld dword ptr [esp + 0x60]
006adf29 add esp, 8
006adf2c fstp dword ptr [esp + 0x58]
006adf30 movss xmm0, dword ptr [esp + 0x58]
006adf36 divss xmm0, dword ptr [0xb6a974]
006adf3e movss xmm1, dword ptr [0xb6ad34]
006adf46 minss xmm1, xmm0
006adf4a xorps xmm0, xmm0
006adf4d comiss xmm0, xmm1
006adf50 jb 0x6adf5a
006adf52 movss xmm1, dword ptr [0xb6a2cc]
006adf5a mov edi, dword ptr [esp + 0x48]
006adf5e lea eax, [ebx + 0x314]
006adf64 movss xmm0, dword ptr [edi + 0x2dc]
006adf6c movss dword ptr [ebx + 0x28c], xmm1
006adf74 movss dword ptr [ebx + 0x290], xmm0
006adf7c mov ecx, dword ptr [eax]
006adf7e test ecx, ecx
006adf80 je 0x6adf9c
006adf82 mov dword ptr [esp + 0x58], eax
006adf86 add ecx, 0x324
006adf8c lea eax, [esp + 0x58]
006adf90 push eax
006adf91 call 0x4bc3c0
006adf96 lea eax, [ebx + 0x314]
006adf9c push eax
006adf9d mov ecx, edi
006adf9f mov dword ptr [eax], edi
006adfa1 call 0x4bae70
006adfa6 mov eax, dword ptr [ebx]
006adfa8 mov ecx, ebx
006adfaa call dword ptr [eax + 0xc]
006adfad xorps xmm2, xmm2
006adfb0 mov ebx, edi
006adfb2 add esi, 0x38
006adfb5 mov dword ptr [esp + 0x4c], esi
006adfb9 cmp esi, dword ptr [ebx + 0xc]
006adfbc jne 0x6adc00
006adfc2 pop edi
006adfc3 pop esi
006adfc4 pop ebx
006adfc5 mov esp, ebp
006adfc7 pop ebp
006adfc8 ret 
006adfc9 int3 
006adfca int3 
006adfcb int3 
006adfcc int3 
006adfcd int3 
006adfce int3 
006adfcf int3 
006adfd0 push ebp
006adfd1 mov ebp, esp
006adfd3 and esp, 0xfffffff8
006adfd6 sub esp, 0x1c
006adfd9 push ebx
006adfda push esi
006adfdb mov ebx, ecx
006adfdd mov esi, ebx
006adfdf mov dword ptr [esp + 0x20], ebx
006adfe3 push edi
006adfe4 mov dword ptr [esp + 0xc], esi
006adfe8 call 0x681710
006adfed test al, al
006adfef je 0x6ae010
006adff1 mov eax, dword ptr [ebx + 0x314]
006adff7 mov dword ptr [esp + 0xc], esi
006adffb test eax, eax
006adffd je 0x6ae010
006adfff nop 
