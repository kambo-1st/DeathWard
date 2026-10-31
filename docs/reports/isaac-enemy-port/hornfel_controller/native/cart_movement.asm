; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.
004bb2b0 push ebp
004bb2b1 mov ebp, esp
004bb2b3 sub esp, 0x40
004bb2b6 cmp byte ptr [ebp + 8], 0
004bb2ba push ebx
004bb2bb mov ebx, ecx
004bb2bd push esi
004bb2be push edi
004bb2bf mov edi, dword ptr [0xbfd65c]
004bb2c5 movss xmm2, dword ptr [ebx + 0x2c4]
004bb2cd movaps xmm1, xmm2
004bb2d0 mulss xmm2, dword ptr [ebx + 0x2bc]
004bb2d8 mulss xmm1, dword ptr [ebx + 0x2b8]
004bb2e0 mov eax, dword ptr [edi + 0x18190]
004bb2e6 mov dword ptr [ebp - 0x14], eax
004bb2e9 movss dword ptr [ebp - 0x10], xmm2
004bb2ee movss dword ptr [ebp - 0xc], xmm1
004bb2f3 jne 0x4bb311
004bb2f5 mov eax, dword ptr [ebx + 0x2c0]
004bb2fb movss dword ptr [ebx + 0x2b8], xmm1
004bb303 movss dword ptr [ebx + 0x2bc], xmm2
004bb30b mov dword ptr [ebx + 0x2c4], eax
004bb311 movaps xmm0, xmm1
004bb314 mulss xmm0, xmm1
004bb318 movaps xmm1, xmm2
004bb31b mulss xmm1, xmm2
004bb31f addss xmm0, xmm1
004bb323 call 0x4228c0
004bb328 cmp dword ptr [ebx + 0x2c], 0xa
004bb32c movaps xmm1, xmm0
004bb32f movss xmm2, dword ptr [0xb6a480] ; f32=0.5
004bb337 jne 0x4bb346
004bb339 cmp dword ptr [ebx + 0xab4], 4
004bb340 jne 0x4bb346
004bb342 addss xmm1, xmm2
004bb346 movss xmm0, dword ptr [0xb6aa3c] ; f32=40
004bb34e xorps xmm3, xmm3
004bb351 minss xmm0, xmm1
004bb355 movss xmm1, dword ptr [0xc034c8]
004bb35d comiss xmm1, xmm3
004bb360 movss dword ptr [ebp - 0x18], xmm0
004bb365 jbe 0x4bb373
004bb367 minss xmm1, xmm0
004bb36b movaps xmm0, xmm1
004bb36e movss dword ptr [ebp - 0x18], xmm1
004bb373 cmp byte ptr [ebp + 8], 0
004bb377 movss dword ptr [ebp - 0x1c], xmm0
004bb37c je 0x4bb38c
004bb37e mulss xmm0, xmm2
004bb382 movss dword ptr [ebp - 0x18], xmm0
004bb387 movss dword ptr [ebp - 0x1c], xmm0
004bb38c movss xmm1, dword ptr [ebp - 0x10]
004bb391 movss xmm2, dword ptr [ebp - 0xc]
004bb396 movaps xmm0, xmm1
004bb399 mulss xmm0, xmm1
004bb39d movss dword ptr [ebp - 0x3c], xmm1
004bb3a2 movaps xmm1, xmm2
004bb3a5 mulss xmm1, xmm2
004bb3a9 movss dword ptr [ebp - 0x40], xmm2
004bb3ae addss xmm0, xmm1
004bb3b2 call 0x4228c0
004bb3b7 movss xmm3, dword ptr [ebp - 0xc]
004bb3bc xorps xmm1, xmm1
004bb3bf comiss xmm0, xmm1
004bb3c2 movss xmm2, dword ptr [ebp - 0x10]
004bb3c7 jbe 0x4bb3f1
004bb3c9 movss xmm1, dword ptr [0xb6a614] ; f32=1
004bb3d1 divss xmm1, xmm0
004bb3d5 mulss xmm3, xmm1
004bb3d9 mulss xmm2, xmm1
004bb3dd movss dword ptr [ebp - 0xc], xmm3
004bb3e2 movss dword ptr [ebp - 0x40], xmm3
004bb3e7 movss dword ptr [ebp - 0x10], xmm2
004bb3ec movss dword ptr [ebp - 0x3c], xmm2
004bb3f1 movss xmm1, dword ptr [ebx + 0x294]
004bb3f9 lea esi, [ebx + 0x294]
004bb3ff movss xmm4, dword ptr [0xb6aa3c] ; f32=40
004bb407 movaps xmm0, xmm1
004bb40a subss xmm0, xmm4
004bb40e movss xmm5, dword ptr [0xb6a480] ; f32=0.5
004bb416 mov dword ptr [ebp - 0x34], 0
004bb41d mov dword ptr [ebp - 0x38], 0
004bb424 mov dword ptr [ebp - 0x2c], 0
004bb42b mov dword ptr [ebp - 0x30], 0
004bb432 divss xmm0, xmm4
004bb436 addss xmm0, xmm5
004bb43a cvttss2si edx, xmm0
004bb43e test edx, edx
004bb440 js 0x4bb842
004bb446 mov eax, dword ptr [ebp - 0x14]
004bb449 mov ecx, dword ptr [eax + 0xc]
004bb44c cmp edx, ecx
004bb44e jge 0x4bb842
004bb454 movss xmm0, dword ptr [esi + 4]
004bb459 subss xmm0, dword ptr [0xb6ab20] ; f32=120
004bb461 divss xmm0, xmm4
004bb465 addss xmm0, xmm5
004bb469 cvttss2si eax, xmm0
004bb46d test eax, eax
004bb46f js 0x4bb842
004bb475 mov edi, dword ptr [ebp - 0x14]
004bb478 cmp eax, dword ptr [edi + 0x10]
004bb47b mov edi, dword ptr [0xbfd65c]
004bb481 jge 0x4bb842
004bb487 imul ecx, eax
004bb48a mov eax, dword ptr [edi + 0x18190]
004bb490 add ecx, edx
004bb492 cmp ecx, 0x1bf
004bb498 ja 0x4bb842
004bb49e mov al, byte ptr [eax + ecx + 0x7350]
004bb4a5 cmp al, 0xff
004bb4a7 je 0x4bb842
004bb4ad mov edx, dword ptr [ebp - 0x14]
004bb4b0 lea edi, [ebp - 5]
004bb4b3 push edi
004bb4b4 lea edi, [ebp - 0x18]
004bb4b7 movzx eax, al
004bb4ba push edi
004bb4bb lea edi, [ebp - 0x20]
004bb4be and eax, 0xf
004bb4c1 push edi
004bb4c2 lea edi, [ebp - 0x30]
004bb4c5 add edx, 0x734c
004bb4cb push edi
004bb4cc lea edi, [ebp - 0x38]
004bb4cf mov dword ptr [ebp - 0x24], edx
004bb4d2 push edi
004bb4d3 push eax
004bb4d4 push ecx
004bb4d5 lea eax, [ebp - 0x40]
004bb4d8 mov ecx, edx
004bb4da push eax
004bb4db push esi
004bb4dc call 0x939120
004bb4e1 movss xmm0, dword ptr [ebp - 0x38]
004bb4e6 movss xmm1, dword ptr [ebp - 0x30]
004bb4eb movss xmm4, dword ptr [ebp - 0xc]
004bb4f0 movss xmm3, dword ptr [ebp - 0x10]
004bb4f5 mov edi, dword ptr [0xbfd65c]
004bb4fb movss dword ptr [esi], xmm0
004bb4ff movss xmm0, dword ptr [ebp - 0x34]
004bb504 movss dword ptr [esi + 4], xmm0
004bb509 movss xmm0, dword ptr [ebp - 0x2c]
004bb50e mulss xmm1, xmm4
004bb512 mulss xmm0, xmm3
004bb516 addss xmm1, xmm0
004bb51a xorps xmm0, xmm0
004bb51d mulss xmm1, dword ptr [ebp - 0x1c]
004bb522 comiss xmm1, xmm0
004bb525 movss dword ptr [ebp - 0x28], xmm1
004bb52a movaps xmm7, xmm1
004bb52d jbe 0x4bb795
004bb533 movss xmm5, dword ptr [0xb6aa3c] ; f32=40
004bb53b movss xmm6, dword ptr [0xb6a480] ; f32=0.5
004bb543 nop dword ptr [eax]
004bb547 nop word ptr [eax + eax]
004bb550 movss xmm0, dword ptr [0xb6a864] ; f32=3
004bb558 movaps xmm1, xmm4
004bb55b minss xmm0, xmm7
004bb55f movaps xmm2, xmm3
004bb562 mulss xmm1, xmm0
004bb566 subss xmm7, xmm0
004bb56a mulss xmm2, xmm0
004bb56e addss xmm1, dword ptr [esi]
004bb572 movss dword ptr [ebp - 0x1c], xmm7
004bb577 addss xmm2, dword ptr [esi + 4]
004bb57c movss dword ptr [esi], xmm1
004bb580 subss xmm1, xmm5
004bb584 movss dword ptr [esi + 4], xmm2
004bb589 divss xmm1, xmm5
004bb58d addss xmm1, xmm6
004bb591 cvttss2si edx, xmm1
004bb595 test edx, edx
004bb597 js 0x4bb5f6
004bb599 mov eax, dword ptr [ebp - 0x14]
004bb59c mov eax, dword ptr [eax + 0xc]
004bb59f cmp edx, eax
004bb5a1 jge 0x4bb5f6
004bb5a3 subss xmm2, dword ptr [0xb6ab20] ; f32=120
004bb5ab divss xmm2, xmm5
004bb5af addss xmm2, xmm6
004bb5b3 cvttss2si ecx, xmm2
004bb5b7 test ecx, ecx
004bb5b9 js 0x4bb5f6
004bb5bb mov edi, dword ptr [ebp - 0x14]
004bb5be cmp ecx, dword ptr [edi + 0x10]
004bb5c1 mov edi, dword ptr [0xbfd65c]
004bb5c7 jge 0x4bb5f6
004bb5c9 imul eax, ecx
004bb5cc mov ecx, dword ptr [edi + 0x18190]
004bb5d2 add eax, edx
004bb5d4 cmp eax, 0x1bf
004bb5d9 ja 0x4bb5f9
004bb5db mov cl, byte ptr [ecx + eax + 0x7350]
004bb5e2 cmp cl, 0xff
004bb5e5 jne 0x4bb5ee
004bb5e7 mov ecx, 0xffffffff
004bb5ec jmp 0x4bb5fc
004bb5ee movzx ecx, cl
004bb5f1 and ecx, 0xf
004bb5f4 jmp 0x4bb5fc
004bb5f6 or eax, 0xffffffff
004bb5f9 or ecx, 0xffffffff
004bb5fc test eax, eax
004bb5fe jle 0x4bb80f
004bb604 test ecx, ecx
004bb606 js 0x4bb80f
004bb60c cmp byte ptr [ebp + 8], 0
004bb610 jne 0x4bb618
004bb612 mov dword ptr [ebx + 0xb14], eax
004bb618 lea edx, [ebp - 5]
004bb61b push edx
004bb61c lea edx, [ebp - 0x18]
004bb61f push edx
004bb620 lea edx, [ebp - 0x20]
004bb623 push edx
004bb624 lea edx, [ebp - 0x30]
004bb627 push edx
004bb628 lea edx, [ebp - 0x38]
004bb62b push edx
004bb62c push ecx
004bb62d mov ecx, dword ptr [ebp - 0x24]
004bb630 push eax
004bb631 lea eax, [ebp - 0x40]
004bb634 push eax
004bb635 push esi
004bb636 call 0x939120
004bb63b cmp byte ptr [ebp - 5], 0
004bb63f movss xmm2, dword ptr [ebp - 0x30]
004bb644 movss xmm1, dword ptr [ebp - 0x2c]
004bb649 je 0x4bb665
004bb64b mulss xmm2, dword ptr [0xb6ae44] ; f32=-1
004bb653 mulss xmm1, dword ptr [0xb6ae44] ; f32=-1
004bb65b movss dword ptr [ebp - 0x30], xmm2
004bb660 movss dword ptr [ebp - 0x2c], xmm1
004bb665 ucomiss xmm2, dword ptr [0xc02fec]
004bb66c lahf 
004bb66d test ah, 0x44
004bb670 jp 0x4bb683
004bb672 ucomiss xmm1, dword ptr [0xc02ff0]
004bb679 lahf 
004bb67a test ah, 0x44
004bb67d jnp 0x4bb7d0
004bb683 movss xmm0, dword ptr [ebp - 0x38]
004bb688 movaps xmm4, xmm2
004bb68b movss xmm5, dword ptr [0xb6aa3c] ; f32=40
004bb693 movaps xmm3, xmm1
004bb696 movss xmm6, dword ptr [0xb6a480] ; f32=0.5
004bb69e movss dword ptr [esi], xmm0
004bb6a2 movss xmm0, dword ptr [ebp - 0x34]
004bb6a7 movss dword ptr [esi + 4], xmm0
004bb6ac cmp dword ptr [ebx + 0x2c], 0xa
004bb6b0 movss dword ptr [ebp - 0xc], xmm4
004bb6b5 movss dword ptr [ebp - 0x40], xmm4
004bb6ba movss dword ptr [ebp - 0x10], xmm3
004bb6bf movss dword ptr [ebp - 0x3c], xmm3
004bb6c4 jne 0x4bb77f
004bb6ca cmp dword ptr [ebx + 0xab4], 4
004bb6d1 jne 0x4bb77f
004bb6d7 mulss xmm2, dword ptr [0xb6a974] ; f32=10
004bb6df mov edi, dword ptr [edi + 0x18190]
004bb6e5 mulss xmm1, dword ptr [0xb6a974] ; f32=10
004bb6ed addss xmm2, dword ptr [esi]
004bb6f1 subss xmm2, xmm5
004bb6f5 divss xmm2, xmm5
004bb6f9 addss xmm2, xmm6
004bb6fd cvttss2si edx, xmm2
004bb701 test edx, edx
004bb703 js 0x4bb779
004bb705 mov eax, dword ptr [edi + 0xc]
004bb708 cmp edx, eax
004bb70a jge 0x4bb779
004bb70c addss xmm1, xmm0
004bb710 subss xmm1, dword ptr [0xb6ab20] ; f32=120
004bb718 divss xmm1, xmm5
004bb71c addss xmm1, xmm6
004bb720 cvttss2si ecx, xmm1
004bb724 test ecx, ecx
004bb726 js 0x4bb779
004bb728 cmp ecx, dword ptr [edi + 0x10]
004bb72b jge 0x4bb779
004bb72d imul eax, ecx
004bb730 add eax, edx
004bb732 js 0x4bb779
004bb734 mov edi, dword ptr [edi + eax*4 + 0x24]
004bb738 test edi, edi
004bb73a je 0x4bb779
004bb73c cmp dword ptr [edi + 4], 0x10
004bb740 jne 0x4bb779
004bb742 mov ecx, edi
004bb744 call 0x6e1450
004bb749 push 0
004bb74b push 1
004bb74d mov ecx, edi
004bb74f call 0x6e02b0
004bb754 push 0
004bb756 push 1
004bb758 mov ecx, edi
004bb75a call 0x6e02b0
004bb75f movss xmm3, dword ptr [ebp - 0x10]
004bb764 movss xmm4, dword ptr [ebp - 0xc]
004bb769 movss xmm5, dword ptr [0xb6aa3c] ; f32=40
004bb771 movss xmm6, dword ptr [0xb6a480] ; f32=0.5
004bb779 mov edi, dword ptr [0xbfd65c]
004bb77f movss xmm7, dword ptr [ebp - 0x1c]
004bb784 xorps xmm0, xmm0
004bb787 comiss xmm7, xmm0
004bb78a ja 0x4bb550
004bb790 movss xmm1, dword ptr [ebp - 0x28]
004bb795 cmp byte ptr [ebp + 8], 0
004bb799 jne 0x4bb85e
004bb79f mulss xmm4, xmm1
004bb7a3 mulss xmm3, xmm1
004bb7a7 movss dword ptr [ebx + 0x2b8], xmm4
004bb7af movss dword ptr [ebx + 0xb00], xmm4
004bb7b7 movss dword ptr [ebx + 0x2bc], xmm3
004bb7bf movss dword ptr [ebx + 0xb04], xmm3
004bb7c7 pop edi
004bb7c8 pop esi
004bb7c9 pop ebx
004bb7ca mov esp, ebp
004bb7cc pop ebp
004bb7cd ret 4
004bb7d0 cmp byte ptr [ebp + 8], 0
004bb7d4 jne 0x4bb7e0
004bb7d6 mov dword ptr [ebx + 0xb14], 0xffffffff
004bb7e0 movss xmm2, dword ptr [ebp - 0xc]
004bb7e5 movss xmm1, dword ptr [ebp - 0x10]
004bb7ea mulss xmm2, dword ptr [ebp - 0x1c]
004bb7ef mulss xmm1, dword ptr [ebp - 0x1c]
004bb7f4 addss xmm2, dword ptr [esi]
004bb7f8 addss xmm1, dword ptr [esi + 4]
004bb7fd movss dword ptr [esi], xmm2
004bb801 movss dword ptr [esi + 4], xmm1
004bb806 pop edi
004bb807 pop esi
004bb808 pop ebx
004bb809 mov esp, ebp
004bb80b pop ebp
004bb80c ret 4
004bb80f cmp byte ptr [ebp + 8], 0
004bb813 jne 0x4bb81f
004bb815 mov dword ptr [ebx + 0xb14], 0xffffffff
004bb81f mulss xmm4, xmm7
004bb823 mulss xmm3, xmm7
004bb827 addss xmm4, dword ptr [esi]
004bb82b addss xmm3, dword ptr [esi + 4]
004bb830 movss dword ptr [esi], xmm4
004bb834 movss dword ptr [esi + 4], xmm3
004bb839 pop edi
004bb83a pop esi
004bb83b pop ebx
004bb83c mov esp, ebp
004bb83e pop ebp
004bb83f ret 4
004bb842 mulss xmm3, dword ptr [ebp - 0x18]
004bb847 mulss xmm2, dword ptr [ebp - 0x1c]
004bb84c addss xmm3, xmm1
004bb850 addss xmm2, dword ptr [esi + 4]
004bb855 movss dword ptr [esi], xmm3
004bb859 movss dword ptr [esi + 4], xmm2
004bb85e pop edi
004bb85f pop esi
004bb860 pop ebx
004bb861 mov esp, ebp
004bb863 pop ebp
004bb864 ret 4
