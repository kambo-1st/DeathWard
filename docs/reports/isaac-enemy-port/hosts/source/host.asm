004ff200 push ebp
004ff201 mov ebp, esp
004ff203 and esp, 0xfffffff8
004ff206 sub esp, 0x134
004ff20c mov eax, dword ptr [0xbaa3b4]
004ff211 xor eax, esp
004ff213 mov dword ptr [esp + 0x130], eax
004ff21a push ebx
004ff21b push esi
004ff21c push edi
004ff21d mov edi, ecx
004ff21f cmp dword ptr [edi + 0x28], 0x35b
004ff226 je 0x4ff238
004ff228 cmp dword ptr [edi + 0x2c], 1
004ff22c je 0x4ff234
004ff22e cmp dword ptr [edi + 0x30], 0x63
004ff232 jne 0x4ff238
004ff234 xor bl, bl
004ff236 jmp 0x4ff23a
004ff238 mov bl, 1
004ff23a mov eax, dword ptr [edi + 0xab4]
004ff240 mov byte ptr [esp + 0x13], bl
004ff244 test eax, eax
004ff246 jne 0x4ff2af
004ff248 push 1
004ff24a push 0xb3fd8c
004ff24f lea ecx, [edi + 0x3c]
004ff252 mov dword ptr [edi + 0xab4], 3
004ff25c mov dword ptr [edi + 0x360], eax
004ff262 call 0x405740
004ff267 test al, al
004ff269 je 0x4ff28b
004ff26b mov eax, dword ptr [edi + 0x70]
004ff26e test eax, eax
004ff270 je 0x4ff28b
004ff272 lea ecx, [edi + 0x6c]
004ff275 xorps xmm1, xmm1
004ff278 call 0x403c00
004ff27d mov eax, dword ptr [edi + 0x70]
004ff280 test eax, eax
004ff282 je 0x4ff28b
004ff284 mov byte ptr [edi + 0x80], 0
004ff28b test bl, bl
004ff28d je 0x4fffd2
004ff293 mov byte ptr [edi + 0x308], 1
004ff29a pop edi
004ff29b pop esi
004ff29c pop ebx
004ff29d mov ecx, dword ptr [esp + 0x130]
004ff2a4 xor ecx, esp
004ff2a6 call 0x9eacd7
004ff2ab mov esp, ebp
004ff2ad pop ebp
004ff2ae ret 
004ff2af mov byte ptr [edi + 0x308], 0
004ff2b6 xorps xmm3, xmm3
004ff2b9 test bl, bl
004ff2bb je 0x4ff3dd
004ff2c1 movss xmm0, dword ptr [edi + 0x14]
004ff2c6 comiss xmm0, xmm3
004ff2c9 jbe 0x4ff3dd
004ff2cf xorps xmm0, xmm0
004ff2d2 movss dword ptr [esp + 0x14], xmm0
004ff2d8 cmp eax, 3
004ff2db je 0x4ff30b
004ff2dd cmp dword ptr [edi + 0x70], 0
004ff2e1 je 0x4ff30b
004ff2e3 push 0xb41d80
004ff2e8 lea ecx, [edi + 0x6c]
004ff2eb call 0x405f30
004ff2f0 test al, al
004ff2f2 je 0x4ff305
004ff2f4 push 0xb41d78
004ff2f9 lea ecx, [edi + 0x3c]
004ff2fc call 0x406150
004ff301 test al, al
004ff303 je 0x4ff34c
004ff305 movss xmm0, dword ptr [esp + 0x14]
004ff30b mov eax, dword ptr [edi + 8]
004ff30e cmp eax, dword ptr [edi + 0xc]
004ff311 je 0x4ff34c
004ff313 mov ecx, dword ptr [eax + 0xc]
004ff316 mov edx, dword ptr [eax + 8]
004ff319 mov dword ptr [esp + 0x24], ecx
004ff31d mov ecx, edx
004ff31f and ecx, 0x8000
004ff325 or ecx, 0
004ff328 jne 0x4ff33e
004ff32a and edx, 0x400080
004ff330 or edx, ecx
004ff332 jne 0x4ff338
004ff334 addss xmm0, dword ptr [eax]
004ff338 mov dword ptr [eax], 0
004ff33e add eax, 0x38
004ff341 cmp eax, dword ptr [edi + 0xc]
004ff344 jne 0x4ff313
004ff346 movss dword ptr [esp + 0x14], xmm0
004ff34c cmp dword ptr [edi + 0xab4], 3
004ff353 xorps xmm3, xmm3
004ff356 jne 0x4ff3dd
004ff35c movss xmm2, dword ptr [esp + 0x14]
004ff362 comiss xmm2, xmm3
004ff365 jbe 0x4ff3dd
004ff367 movss xmm1, dword ptr [edi + 0x14]
004ff36c mov ecx, dword ptr [edi + 0x360]
004ff372 movaps xmm0, xmm1
004ff375 addss xmm0, dword ptr [0xb6a480]
004ff37d mulss xmm1, dword ptr [0xb6a274]
004ff385 cvttss2si eax, xmm0
004ff389 movss xmm0, dword ptr [edi + 0xb08]
004ff391 cdq 
004ff392 subss xmm0, xmm1
004ff396 sub eax, edx
004ff398 sar eax, 1
004ff39a add ecx, eax
004ff39c mov eax, 0xa
004ff3a1 cmp ecx, eax
004ff3a3 maxss xmm0, xmm3
004ff3a7 cmovl eax, ecx
004ff3aa comiss xmm2, dword ptr [0xb6a9c8]
004ff3b1 mov dword ptr [edi + 0x360], eax
004ff3b7 movss dword ptr [edi + 0xb08], xmm0
004ff3bf jbe 0x4ff3dd
004ff3c1 push 0
004ff3c3 push 0xb42f20
004ff3c8 lea ecx, [edi + 0x3c]
004ff3cb call 0x4054f0
004ff3d0 mov dword ptr [edi + 0xb08], 0
004ff3da xorps xmm3, xmm3
004ff3dd cmp dword ptr [edi + 0xe6c], -1
004ff3e4 movss xmm0, dword ptr [0xb6a614]
004ff3ec movss xmm1, dword ptr [0xb6a864]
004ff3f4 je 0x4ff50a
004ff3fa mov eax, dword ptr [edi + 0x160]
004ff400 and eax, 0x10
004ff403 or eax, 0
004ff406 je 0x4ff4b3
004ff40c cmp dword ptr [edi + 0x70], 0
004ff410 je 0x4ff459
004ff412 cmp byte ptr [edi + 0x80], 0
004ff419 je 0x4ff459
004ff41b mov eax, dword ptr [edi + 0x70]
004ff41e cmp dword ptr [eax + 0x14], 0x10
004ff422 jb 0x4ff426
004ff424 mov eax, dword ptr [eax]
004ff426 mov ecx, 0xb42f20
004ff42b nop dword ptr [eax + eax]
004ff430 mov dl, byte ptr [eax]
004ff432 cmp dl, byte ptr [ecx]
004ff434 jne 0x4ff450
004ff436 test dl, dl
004ff438 je 0x4ff44c
004ff43a mov dl, byte ptr [eax + 1]
004ff43d cmp dl, byte ptr [ecx + 1]
004ff440 jne 0x4ff450
004ff442 add eax, 2
004ff445 add ecx, 2
004ff448 test dl, dl
004ff44a jne 0x4ff430
004ff44c xor eax, eax
004ff44e jmp 0x4ff455
004ff450 sbb eax, eax
004ff452 or eax, 1
004ff455 test eax, eax
004ff457 je 0x4ff4b3
004ff459 test bl, bl
004ff45b je 0x4ff4b3
004ff45d push 0
004ff45f push 0x1000a00
004ff464 mov ecx, edi
004ff466 movss dword ptr [esp + 0x20], xmm0
004ff46c call 0x4122f0
004ff471 test al, al
004ff473 je 0x4ff47f
004ff475 movss xmm1, dword ptr [0xb6a7b0]
004ff47d jmp 0x4ff485
004ff47f movss xmm1, dword ptr [esp + 0x18]
004ff485 mulss xmm1, dword ptr [edi + 0x2f4]
004ff48d movss xmm0, dword ptr [0xb6a614]
004ff495 divss xmm1, dword ptr [0xb6ab58]
004ff49d addss xmm1, dword ptr [edi + 0xb0c]
004ff4a5 minss xmm1, xmm0
004ff4a9 movss dword ptr [edi + 0xb0c], xmm1
004ff4b1 jmp 0x4ff4f8
004ff4b3 movss xmm0, dword ptr [edi + 0x2f4]
004ff4bb mulss xmm0, xmm1
004ff4bf movss xmm1, dword ptr [edi + 0xb0c]
004ff4c7 divss xmm0, dword ptr [0xb6ab58]
004ff4cf subss xmm1, xmm0
004ff4d3 maxss xmm1, xmm3
004ff4d7 movss dword ptr [edi + 0xb0c], xmm1
004ff4df movss xmm0, dword ptr [0xb6a614]
004ff4e7 test bl, bl
004ff4e9 jne 0x4ff4f8
004ff4eb mov dword ptr [edi + 0xb0c], 0
004ff4f5 movaps xmm1, xmm3
004ff4f8 movaps xmm3, xmm1
004ff4fb xorps xmm2, xmm2
004ff4fe push 1
004ff500 movaps xmm1, xmm0
004ff503 mov ecx, edi
004ff505 call 0x6afbd0
004ff50a cmp dword ptr [edi + 0x28], 0x35b
004ff511 movss xmm2, dword ptr [edi + 0x2c4]
004ff519 jne 0x4ff650
004ff51f mulss xmm2, dword ptr [0xb6a5a4]
004ff527 mov eax, dword ptr [edi + 0x160]
004ff52d and eax, 0x200
004ff532 or eax, 0
004ff535 movss dword ptr [edi + 0x2c4], xmm2
004ff53d je 0x4ff55a
004ff53f cmp dword ptr [edi + 0xe6c], -1
004ff546 jne 0x4ff55a
004ff548 push 0
004ff54a lea ecx, [edi + 0x364]
004ff550 call 0x7a6180
004ff555 jmp 0x4ff660
004ff55a movss xmm3, dword ptr [0xb6a4a0]
004ff562 xorps xmm1, xmm1
004ff565 comiss xmm1, dword ptr [edi + 0x2b8]
004ff56c movss xmm0, dword ptr [0xb6ae24]
004ff574 movaps xmm4, xmm3
004ff577 movss dword ptr [esp + 0x1c], xmm3
004ff57d movss dword ptr [esp + 0x14], xmm4
004ff583 jbe 0x4ff58e
004ff585 movaps xmm3, xmm0
004ff588 movss dword ptr [esp + 0x1c], xmm3
004ff58e comiss xmm1, dword ptr [edi + 0x2bc]
004ff595 jbe 0x4ff5a0
004ff597 movaps xmm4, xmm0
004ff59a movss dword ptr [esp + 0x14], xmm0
004ff5a0 cmp dword ptr [edi + 0xe6c], -1
004ff5a7 je 0x4ff60a
004ff5a9 movaps xmm0, xmm3
004ff5ac movaps xmm1, xmm4
004ff5af mulss xmm0, xmm3
004ff5b3 mulss xmm1, xmm4
004ff5b7 addss xmm0, xmm1
004ff5bb call 0x4228c0
004ff5c0 mulss xmm0, dword ptr [0xb6a480]
004ff5c8 lea eax, [esp + 0x20]
004ff5cc push eax
004ff5cd xorps xmm2, xmm2
004ff5d0 mov ecx, edi
004ff5d2 movss dword ptr [esp + 0x1c], xmm0
004ff5d8 call 0x6af0c0
004ff5dd movss xmm0, dword ptr [esp + 0x18]
004ff5e3 xorps xmm1, xmm1
004ff5e6 movss xmm4, dword ptr [esp + 0x14]
004ff5ec movaps xmm3, xmm0
004ff5ef movss xmm2, dword ptr [edi + 0x2c4]
004ff5f7 mulss xmm3, dword ptr [eax]
004ff5fb mulss xmm0, dword ptr [eax + 4]
004ff600 addss xmm3, dword ptr [esp + 0x1c]
004ff606 addss xmm4, xmm0
004ff60a ucomiss xmm2, xmm1
004ff60d lahf 
004ff60e test ah, 0x44
004ff611 jnp 0x4ff660
004ff613 movss xmm1, dword ptr [edi + 0x2f4]
004ff61b movaps xmm0, xmm1
004ff61e mulss xmm1, xmm4
004ff622 mulss xmm0, xmm3
004ff626 divss xmm1, xmm2
004ff62a divss xmm0, xmm2
004ff62e addss xmm1, dword ptr [edi + 0x2bc]
004ff636 addss xmm0, dword ptr [edi + 0x2b8]
004ff63e movss dword ptr [edi + 0x2bc], xmm1
004ff646 movss dword ptr [edi + 0x2b8], xmm0
004ff64e jmp 0x4ff660
004ff650 mulss xmm2, dword ptr [0xb6a50c]
004ff658 movss dword ptr [edi + 0x2c4], xmm2
004ff660 mov ecx, edi
004ff662 call 0x695680
004ff667 mov ecx, dword ptr [edi + 0x2c]
004ff66a lea ebx, [edi + 0x294]
004ff670 cmp ecx, 1
004ff673 mov edx, 2
004ff678 movss xmm0, dword ptr [eax + 0x294]
004ff680 mov eax, 5
004ff685 subss xmm0, dword ptr [ebx]
004ff689 cmovne eax, edx
004ff68c cmp ecx, 3
004ff68f mov dword ptr [esp + 0x38], eax
004ff693 sete al
004ff696 xor esi, esi
004ff698 mov byte ptr [esp + 0x28], al
004ff69c mov eax, 3
004ff6a1 cmp ecx, eax
004ff6a3 movss dword ptr [esp + 0x18], xmm0
004ff6a9 lea ecx, [esp + 0x90]
004ff6b0 cmovne esi, eax
004ff6b3 call 0x430d70
004ff6b8 cmp dword ptr [edi + 0x28], 0x35b
004ff6bf movss xmm0, dword ptr [esp + 0x9c]
004ff6c8 subss xmm0, dword ptr [0xb6a274]
004ff6d0 mov dword ptr [esp + 0xa0], 0x3f88f5c3
004ff6db movss dword ptr [esp + 0x9c], xmm0
004ff6e4 jne 0x4ff6f9
004ff6e6 mov dword ptr [esp + 0xa0], 0x3f99999a
004ff6f1 mov byte ptr [esp + 0x128], 1
004ff6f9 mov eax, dword ptr [edi + 0xab4]
004ff6ff sub eax, 3
004ff702 je 0x4ffee2
004ff708 sub eax, 5
004ff70b je 0x4ff7e3
004ff711 sub eax, 1
004ff714 jne 0x4fffd2
004ff71a cmp byte ptr [esp + 0x13], al
004ff71e je 0x4ff733
004ff720 mov eax, dword ptr [edi + 0x164]
004ff726 and dword ptr [edi + 0x160], 0xffffffef
004ff72d mov dword ptr [edi + 0x164], eax
004ff733 cmp dword ptr [edi + 0x70], 0
004ff737 je 0x4ff781
004ff739 push 0xb41d80
004ff73e lea ecx, [edi + 0x6c]
004ff741 call 0x405e90
004ff746 test al, al
004ff748 jne 0x4ff761
004ff74a cmp dword ptr [edi + 0x70], 0
004ff74e je 0x4ff781
004ff750 push 0xb41d78
004ff755 lea ecx, [edi + 0x6c]
004ff758 call 0x405e90
004ff75d test al, al
004ff75f je 0x4ff781
004ff761 push ecx
004ff762 mov dword ptr [esp], 0x3f800000
004ff769 push 0
004ff76b push 2
004ff76d push ecx
004ff76e mov dword ptr [esp], 0x3f800000
004ff775 mov ecx, edi
004ff777 push 0xa6
004ff77c call 0x6ad720
004ff781 inc dword ptr [edi + 0x360]
004ff787 lea ecx, [edi + 0x3c]
004ff78a push 0
004ff78c push 0xb400ac
004ff791 call 0x4054f0
004ff796 xorps xmm0, xmm0
004ff799 comiss xmm0, dword ptr [esp + 0x18]
004ff79e seta al
004ff7a1 mov byte ptr [edi + 0x13c], al
004ff7a7 cmp dword ptr [edi + 0x70], 0
004ff7ab je 0x4ff7ba
004ff7ad cmp byte ptr [edi + 0x80], 0
004ff7b4 jne 0x4fffd2
004ff7ba mov dword ptr [edi + 0xab4], 3
004ff7c4 mov dword ptr [edi + 0x360], 0
004ff7ce pop edi
004ff7cf pop esi
004ff7d0 pop ebx
004ff7d1 mov ecx, dword ptr [esp + 0x130]
004ff7d8 xor ecx, esp
004ff7da call 0x9eacd7
004ff7df mov esp, ebp
004ff7e1 pop ebp
004ff7e2 ret 
004ff7e3 cmp byte ptr [esp + 0x13], 0
004ff7e8 je 0x4ff7fd
004ff7ea mov eax, dword ptr [edi + 0x164]
004ff7f0 and dword ptr [edi + 0x160], 0xffffffef
004ff7f7 mov dword ptr [edi + 0x164], eax
004ff7fd cmp dword ptr [edi + 0x70], 0
004ff801 lea esi, [edi + 0x6c]
004ff804 mov dword ptr [esp + 0x14], esi
004ff808 je 0x4ff864
004ff80a push 0xb41d80
004ff80f mov ecx, esi
004ff811 call 0x405e90
004ff816 mov dword ptr [esp + 0x1c], esi
004ff81a test al, al
004ff81c jne 0x4ff83c
004ff81e cmp dword ptr [edi + 0x70], 0
004ff822 je 0x4ff864
004ff824 push 0xb41d78
004ff829 mov ecx, esi
004ff82b call 0x405e90
004ff830 mov dword ptr [esp + 0x1c], esi
004ff834 mov dword ptr [esp + 0x14], esi
004ff838 test al, al
004ff83a je 0x4ff864
004ff83c push ecx
004ff83d mov dword ptr [esp], 0x3f800000
004ff844 push 0
004ff846 push 2
004ff848 push ecx
004ff849 mov dword ptr [esp], 0x3f800000
004ff850 mov ecx, edi
004ff852 push 0xa6
004ff857 call 0x6ad720
004ff85c mov esi, dword ptr [esp + 0x1c]
004ff860 mov dword ptr [esp + 0x14], esi
004ff864 cmp dword ptr [edi + 0xe6c], -1
004ff86b je 0x4ff90c
004ff871 cmp dword ptr [edi + 0x70], 0
004ff875 je 0x4ff8a1
004ff877 push 0xb400ac
004ff87c mov ecx, esi
004ff87e call 0x405f30
004ff883 test al, al
004ff885 jne 0x4ff90c
004ff88b cmp dword ptr [edi + 0x70], 0
004ff88f je 0x4ff8a1
004ff891 push 0xb41d78
004ff896 mov ecx, esi
004ff898 call 0x405f30
004ff89d test al, al
004ff89f jne 0x4ff90c
004ff8a1 push 0
004ff8a3 push 0x1000a00
004ff8a8 mov ecx, edi
004ff8aa call 0x4122f0
004ff8af test al, al
004ff8b1 je 0x4ff8cd
004ff8b3 movss xmm0, dword ptr [0xc02fec]
004ff8bb movss dword ptr [edi + 0xe70], xmm0
004ff8c3 movss xmm0, dword ptr [0xc02ff0]
004ff8cb jmp 0x4ff904
004ff8cd movss xmm2, dword ptr [0xb6ae44]
004ff8d5 mov ecx, edi
004ff8d7 push 0
004ff8d9 call 0x6af8d0
004ff8de lea eax, [esp + 0x20]
004ff8e2 mov ecx, edi
004ff8e4 push eax
004ff8e5 call 0x6afac0
004ff8ea movss xmm1, dword ptr [eax]
004ff8ee subss xmm1, dword ptr [ebx]
004ff8f2 movss xmm0, dword ptr [eax + 4]
004ff8f7 subss xmm0, dword ptr [ebx + 4]
004ff8fc movss dword ptr [edi + 0xe70], xmm1
004ff904 movss dword ptr [edi + 0xe74], xmm0
004ff90c inc dword ptr [edi + 0x360]
004ff912 lea ecx, [edi + 0x3c]
004ff915 push 0
004ff917 push 0xb400ac
004ff91c call 0x4054f0
004ff921 cmp dword ptr [edi + 0xe6c], -1
004ff928 xorps xmm0, xmm0
004ff92b je 0x4ff936
004ff92d comiss xmm0, dword ptr [edi + 0xe70]
004ff934 jmp 0x4ff93b
004ff936 comiss xmm0, dword ptr [esp + 0x18]
004ff93b seta al
004ff93e mov byte ptr [edi + 0x13c], al
004ff944 cmp dword ptr [edi + 0x2c], 3
004ff948 jne 0x4ffd40
004ff94e cmp dword ptr [edi + 0x70], 0
004ff952 je 0x4ffeaa
004ff958 push 0xb41d78
004ff95d mov ecx, esi
004ff95f call 0x405e90
004ff964 test al, al
004ff966 je 0x4ffd40
004ff96c mov esi, dword ptr [0xbfd680]
004ff972 lea ecx, [esp + 0x18]
004ff976 mov dword ptr [esp + 0x18], 0x34
004ff97e call 0x8b1340
004ff983 sub esp, 8
004ff986 mov dword ptr [esp + 4], 0
004ff98e mov dword ptr [esp], 0x3f800000
004ff995 push 0
004ff997 push 0xa
004ff999 push ecx
004ff99a mov dword ptr [esp], 0x3f800000
004ff9a1 lea ecx, [esi + 0x29de0]
004ff9a7 push dword ptr [esp + 0x2c]
004ff9ab call 0x888de0
004ff9b0 mov ecx, edi
004ff9b2 call 0x695680
004ff9b7 lea ecx, [esp + 0x28]
004ff9bb movss xmm0, dword ptr [eax + 0x294]
004ff9c3 movss xmm1, dword ptr [eax + 0x298]
004ff9cb lea eax, [esp + 0x30]
004ff9cf subss xmm0, dword ptr [ebx]
004ff9d3 subss xmm1, dword ptr [ebx + 4]
004ff9d8 push eax
004ff9d9 movss dword ptr [esp + 0x2c], xmm0
004ff9df movss dword ptr [esp + 0x30], xmm1
004ff9e5 call 0x962560
004ff9ea cmp dword ptr [edi + 0xe6c], -1
004ff9f1 je 0x4ffa34
004ff9f3 push 0xc02fec
004ff9f8 lea ecx, [edi + 0xe70]
004ff9fe call 0x962c70
004ffa03 test al, al
004ffa05 je 0x4ffa1f
004ffa07 lea eax, [esp + 0x20]
004ffa0b push eax
004ffa0c call 0x659290
004ffa11 add esp, 4
004ffa14 movss xmm0, dword ptr [eax]
004ffa18 movss xmm1, dword ptr [eax + 4]
004ffa1d jmp 0x4ffa40
004ffa1f lea eax, [esp + 0x28]
004ffa23 push eax
004ffa24 call 0x962560
004ffa29 movss xmm0, dword ptr [eax]
004ffa2d movss xmm1, dword ptr [eax + 4]
004ffa32 jmp 0x4ffa40
004ffa34 movss xmm1, dword ptr [esp + 0x34]
004ffa3a movss xmm0, dword ptr [esp + 0x30]
004ffa40 movss dword ptr [esp + 0x18], xmm0
004ffa46 movss dword ptr [esp + 0x1c], xmm1
004ffa4c call 0x6c3d90
004ffa51 mulss xmm0, dword ptr [0xb6a9c8]
004ffa59 mov ecx, dword ptr [0xbfd65c]
004ffa5f push 0
004ffa61 push eax
004ffa62 addss xmm0, dword ptr [ebx]
004ffa66 push 2
004ffa68 push edi
004ffa69 push 0xc02fec
004ffa6e lea eax, [esp + 0x34]
004ffa72 movss dword ptr [esp + 0x34], xmm0
004ffa78 movaps xmm0, xmm1
004ffa7b mulss xmm0, dword ptr [0xb6a9c8]
004ffa83 push eax
004ffa84 push 0x48
004ffa86 push 0x3e8
004ffa8b addss xmm0, dword ptr [ebx + 4]
004ffa90 movss dword ptr [esp + 0x44], xmm0
004ffa96 call 0x6d0ca0
004ffa9b mov ecx, dword ptr [eax + 0x314]
004ffaa1 mov dword ptr [esp + 0x28], eax
004ffaa5 lea esi, [eax + 0x314]
004ffaab test ecx, ecx
004ffaad je 0x4ffac3
004ffaaf lea eax, [esp + 0x30]
004ffab3 mov dword ptr [esp + 0x30], esi
004ffab7 push eax
004ffab8 add ecx, 0x324
004ffabe call 0x4bc3c0
004ffac3 push esi
004ffac4 mov ecx, edi
004ffac6 mov dword ptr [esi], edi
004ffac8 call 0x4bae70
004ffacd movss xmm1, dword ptr [esp + 0x18]
004ffad3 movss xmm0, dword ptr [esp + 0x1c]
004ffad9 call 0x447a80
004ffade mulss xmm0, dword ptr [0xb6aa84]
004ffae6 mov eax, dword ptr [esp + 0x28]
004ffaea movss xmm3, dword ptr [0xb6a478]
004ffaf2 movss xmm1, dword ptr [0xb6a49c]
004ffafa movaps xmm2, xmm3
004ffafd push ecx
004ffafe lea ecx, [esp + 0x68]
004ffb02 movss dword ptr [eax + 0x3c4], xmm0
004ffb0a mov dword ptr [esp], 0x3f800000
004ffb11 call 0x4325d0
004ffb16 call 0x6c3d90
004ffb1b movd xmm0, eax
004ffb1f cvtdq2pd xmm0, xmm0
004ffb23 shr eax, 0x1f
004ffb26 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004ffb2f cvtpd2ps xmm0, xmm0
004ffb33 mulss xmm0, dword ptr [0xb6a19c]
004ffb3b call 0x6c3d90
004ffb40 mulss xmm0, dword ptr [0xb6a864]
004ffb48 and eax, 3
004ffb4b push 0
004ffb4d push ecx
004ffb4e mov dword ptr [esp], 0x47c35000
004ffb55 lea ecx, [esp + 0x6c]
004ffb59 addss xmm0, dword ptr [0xb6a8cc]
004ffb61 push ecx
004ffb62 push ecx
004ffb63 mov ecx, dword ptr [0xbfd65c]
004ffb69 add eax, 5
004ffb6c movss dword ptr [esp], xmm0
004ffb71 push eax
004ffb72 push 0x23
004ffb74 push ebx
004ffb75 call 0x6d57a0
004ffb7a mov ecx, dword ptr [0xbfd65c]
004ffb80 push 0xc
004ffb82 call 0x6d5ad0
004ffb87 mov ecx, edi
004ffb89 call 0x448100
004ffb8e test al, al
004ffb90 jne 0x4ffd3c
004ffb96 mov ecx, dword ptr [0xbfd65c]
004ffb9c xor esi, esi
004ffb9e mov eax, dword ptr [ecx + 0x1ba54]
004ffba4 sub eax, dword ptr [ecx + 0x1ba50]
004ffbaa sar eax, 2
004ffbad test eax, eax
004ffbaf je 0x4ffd3c
004ffbb5 push esi
004ffbb6 call 0x412750
004ffbbb mov dword ptr [esp + 0x28], eax
004ffbbf movss xmm1, dword ptr [eax + 0x298]
004ffbc7 subss xmm1, dword ptr [ebx + 4]
004ffbcc movss xmm2, dword ptr [eax + 0x294]
004ffbd4 subss xmm2, dword ptr [ebx]
004ffbd8 movaps xmm0, xmm1
004ffbdb movss dword ptr [esp + 0x1c], xmm1
004ffbe1 mulss xmm0, xmm1
004ffbe5 movaps xmm1, xmm2
004ffbe8 movss dword ptr [esp + 0x18], xmm2
004ffbee mulss xmm1, xmm2
004ffbf2 addss xmm0, xmm1
004ffbf6 call 0x4228c0
004ffbfb movss xmm2, dword ptr [esp + 0x18]
004ffc01 movaps xmm4, xmm0
004ffc04 comiss xmm4, dword ptr [0xb6a18c]
004ffc0b movss xmm3, dword ptr [esp + 0x1c]
004ffc11 jbe 0x4ffc2a
004ffc13 movss xmm1, dword ptr [0xb6a614]
004ffc1b divss xmm1, xmm4
004ffc1f movaps xmm0, xmm1
004ffc22 mulss xmm3, xmm1
004ffc26 mulss xmm2, xmm0
004ffc2a movss xmm0, dword ptr [0xb6ab20]
004ffc32 comiss xmm0, xmm4
004ffc35 jbe 0x4ffd1e
004ffc3b mov eax, dword ptr [edi + 0x28]
004ffc3e movss xmm0, dword ptr [ebx]
004ffc42 movss xmm1, dword ptr [ebx + 4]
004ffc47 mov ecx, dword ptr [edi + 0x160]
004ffc4d mov edx, dword ptr [edi + 0x164]
004ffc53 mov dword ptr [esp + 0x3c], eax
004ffc57 mov eax, dword ptr [edi + 0x2c]
004ffc5a mov dword ptr [esp + 0x40], eax
004ffc5e mov eax, dword ptr [edi + 0x34]
004ffc61 mov dword ptr [esp + 0x44], eax
004ffc65 mov eax, dword ptr [edi + 0x38]
004ffc68 mov dword ptr [esp + 0x48], eax
004ffc6c mov eax, ecx
004ffc6e movss dword ptr [esp + 0x4c], xmm0
004ffc74 and eax, 0x100
004ffc79 or eax, 0
004ffc7c movss xmm0, dword ptr [edi + 0x2b8]
004ffc84 movss dword ptr [esp + 0x50], xmm1
004ffc8a movss xmm1, dword ptr [edi + 0x2bc]
004ffc92 movss dword ptr [esp + 0x54], xmm0
004ffc98 movss dword ptr [esp + 0x58], xmm1
004ffc9e mov dword ptr [esp + 0x18], 1
004ffca6 jne 0x4ffcb0
004ffca8 mov dword ptr [esp + 0x18], 0
004ffcb0 and ecx, 0x20000000
004ffcb6 or ecx, 0
004ffcb9 je 0x4ffcc2
004ffcbb mov ecx, 2
004ffcc0 jmp 0x4ffcc4
004ffcc2 xor ecx, ecx
004ffcc4 and edx, 0x400000
004ffcca xor eax, eax
004ffccc or eax, edx
004ffcce je 0x4ffcd7
004ffcd0 mov eax, 4
004ffcd5 jmp 0x4ffcd9
004ffcd7 xor eax, eax
004ffcd9 mulss xmm2, dword ptr [0xb6a864]
004ffce1 lea edx, [esp + 0x20]
004ffce5 or eax, ecx
004ffce7 mov ecx, dword ptr [esp + 0x28]
004ffceb mulss xmm3, dword ptr [0xb6a864]
004ffcf3 or eax, dword ptr [esp + 0x18]
004ffcf7 push ecx
004ffcf8 mov dword ptr [esp], 0x41100000
004ffcff mov dword ptr [esp + 0x60], eax
004ffd03 mov eax, dword ptr [ecx]
004ffd05 push edx
004ffd06 lea edx, [esp + 0x44]
004ffd0a mov dword ptr [esp + 0x68], edi
004ffd0e push edx
004ffd0f movss dword ptr [esp + 0x2c], xmm2
004ffd15 movss dword ptr [esp + 0x30], xmm3
004ffd1b call dword ptr [eax + 0x50]
004ffd1e mov ecx, dword ptr [0xbfd65c]
004ffd24 inc esi
004ffd25 mov eax, dword ptr [ecx + 0x1ba54]
004ffd2b sub eax, dword ptr [ecx + 0x1ba50]
004ffd31 sar eax, 2
004ffd34 cmp esi, eax
004ffd36 jb 0x4ffbb5
004ffd3c mov esi, dword ptr [esp + 0x14]
004ffd40 cmp dword ptr [edi + 0x70], 0
004ffd44 je 0x4ffeaa
004ffd4a push 0xb400ac
004ffd4f mov ecx, esi
004ffd51 call 0x405e90
004ffd56 test al, al
004ffd58 je 0x4ffe97
004ffd5e mov ecx, edi
004ffd60 call 0x695680
004ffd65 cmp dword ptr [edi + 0xe6c], -1
004ffd6c movss xmm2, dword ptr [eax + 0x294]
004ffd74 movss xmm1, dword ptr [eax + 0x298]
004ffd7c subss xmm2, dword ptr [ebx]
004ffd80 subss xmm1, dword ptr [ebx + 4]
004ffd85 movss dword ptr [esp + 0x14], xmm2
004ffd8b movss dword ptr [esp + 0x1c], xmm1
004ffd91 je 0x4ffdaf
004ffd93 movss xmm2, dword ptr [edi + 0xe70]
004ffd9b movss xmm1, dword ptr [edi + 0xe74]
004ffda3 movss dword ptr [esp + 0x14], xmm2
004ffda9 movss dword ptr [esp + 0x1c], xmm1
004ffdaf ucomiss xmm2, dword ptr [0xc02fec]
004ffdb6 lahf 
004ffdb7 test ah, 0x44
004ffdba jp 0x4ffdcd
004ffdbc ucomiss xmm1, dword ptr [0xc02ff0]
004ffdc3 lahf 
004ffdc4 test ah, 0x44
004ffdc7 jnp 0x4ffe97
004ffdcd movaps xmm0, xmm1
004ffdd0 mulss xmm0, xmm1
004ffdd4 movaps xmm1, xmm2
004ffdd7 mulss xmm1, xmm2
004ffddb addss xmm0, xmm1
004ffddf call 0x4228c0
004ffde4 comiss xmm0, dword ptr [0xb6a18c]
004ffdeb jbe 0x4ffe15
004ffded movss xmm1, dword ptr [0xb6a928]
004ffdf5 divss xmm1, xmm0
004ffdf9 movss xmm0, dword ptr [esp + 0x14]
004ffdff mulss xmm0, xmm1
004ffe03 movss dword ptr [esp + 0x28], xmm0
004ffe09 movss xmm0, dword ptr [esp + 0x1c]
004ffe0f mulss xmm0, xmm1
004ffe13 jmp 0x4ffe27
004ffe15 movss xmm0, dword ptr [esp + 0x14]
004ffe1b movss dword ptr [esp + 0x28], xmm0
004ffe21 movss xmm0, dword ptr [esp + 0x1c]
004ffe27 lea eax, [esp + 0x90]
004ffe2e movss dword ptr [esp + 0x2c], xmm0
004ffe34 push eax
004ffe35 push dword ptr [esp + 0x3c]
004ffe39 lea eax, [esp + 0x30]
004ffe3d mov ecx, edi
004ffe3f push eax
004ffe40 push ebx
004ffe41 call 0x6a1a20
004ffe46 push 0xc02fec
004ffe4b lea ecx, [esp + 0x68]
004ffe4f mov dword ptr [esp + 0x24], 0
004ffe57 mov dword ptr [esp + 0x28], 0xc0c00000
004ffe5f call 0x402120
004ffe64 push eax
004ffe65 lea eax, [esp + 0x28]
004ffe69 mov edx, ebx
004ffe6b push eax
004ffe6c mov ecx, 1
004ffe71 call 0x6aead0
004ffe76 add esp, 0xc
004ffe79 mov dword ptr [eax + 0xd8], 0x3f400000
004ffe83 mov dword ptr [eax + 0xdc], 0x3f400000
004ffe8d mov dword ptr [eax + 0x2b0], 0x3f800000
004ffe97 cmp dword ptr [edi + 0x70], 0
004ffe9b je 0x4ffeaa
004ffe9d cmp byte ptr [edi + 0x80], 0
004ffea4 jne 0x4fffd2
004ffeaa push 0
004ffeac push 0xb3fd8c
004ffeb1 lea ecx, [edi + 0x3c]
004ffeb4 mov dword ptr [edi + 0xab4], 3
004ffebe mov dword ptr [edi + 0x360], 0
004ffec8 call 0x4054f0
004ffecd pop edi
004ffece pop esi
004ffecf pop ebx
004ffed0 mov ecx, dword ptr [esp + 0x130]
004ffed7 xor ecx, esp
004ffed9 call 0x9eacd7
004ffede mov esp, ebp
004ffee0 pop ebp
004ffee1 ret 
004ffee2 cmp byte ptr [esp + 0x13], 0
004ffee7 je 0x4ffefc
004ffee9 mov eax, dword ptr [edi + 0x164]
004ffeef or dword ptr [edi + 0x160], 0x10
004ffef6 mov dword ptr [edi + 0x164], eax
004ffefc cmp dword ptr [edi + 0x360], 0
004fff03 jg 0x4fff8b
004fff09 push 0
004fff0b push 0xb3fd8c
004fff10 lea ecx, [edi + 0x3c]
004fff13 call 0x4054f0
004fff18 cmp dword ptr [edi + 0xe6c], -1
004fff1f je 0x4fffe7
004fff25 movss xmm0, dword ptr [edi + 0xb0c]
004fff2d comiss xmm0, dword ptr [0xb6a614]
004fff34 jae 0x4fff4d
004fff36 movss xmm1, dword ptr [0xb6accc]
004fff3e mov ecx, edi
004fff40 push 7
004fff42 push 0
004fff44 call 0x6a15a0
004fff49 test al, al
004fff4b je 0x4fff8b
004fff4d movss xmm0, dword ptr [0xc02fec]
004fff55 movss dword ptr [edi + 0xe70], xmm0
004fff5d movss xmm0, dword ptr [0xc02ff0]
004fff65 movss dword ptr [edi + 0xe74], xmm0
004fff6d mov dword ptr [edi + 0xab4], 8
004fff77 mov dword ptr [edi + 0x360], 0
004fff81 mov dword ptr [edi + 0xaf0], 0x46
004fff8b mov eax, dword ptr [edi + 0x160]
004fff91 and eax, 0x4000
004fff96 or eax, 0
004fff99 jne 0x4fffd2
004fff9b mov esi, dword ptr [0xbfd65c]
004fffa1 mov ecx, esi
004fffa3 call 0x6d0380
004fffa8 test al, al
004fffaa jne 0x4fffd2
004fffac mov eax, dword ptr [esi + 0x1a30dc]
004fffb2 mov ecx, 7
004fffb7 add eax, dword ptr [edi + 0x20]
004fffba cdq 
004fffbb idiv ecx
004fffbd test edx, edx
004fffbf jne 0x4fffd2
004fffc1 mov eax, dword ptr [edi + 0x360]
004fffc7 test eax, eax
004fffc9 jle 0x4fffd2
004fffcb dec eax
004fffcc mov dword ptr [edi + 0x360], eax
004fffd2 pop edi
004fffd3 pop esi
004fffd4 pop ebx
004fffd5 mov ecx, dword ptr [esp + 0x130]
004fffdc xor ecx, esp
004fffde call 0x9eacd7
004fffe3 mov esp, ebp
004fffe5 pop ebp
004fffe6 ret 
004fffe7 push 0
004fffe9 push 0x200
004fffee mov ecx, edi
004ffff0 call 0x4122f0
004ffff5 test al, al
004ffff7 jne 0x5000f7
004ffffd push 0
004fffff push 0x1000800
00500004 mov ecx, edi
00500006 call 0x4122f0
0050000b test al, al
0050000d jne 0x5000f7
00500013 push dword ptr [edi + 0x20]
00500016 mov ecx, edi
00500018 push 7
0050001a call 0x684790
0050001f test al, al
00500021 je 0x4fff8b
00500027 mov eax, dword ptr [edi + 0xaf0]
0050002d test eax, eax
0050002f jle 0x50003d
00500031 dec eax
00500032 mov dword ptr [edi + 0xaf0], eax
00500038 jmp 0x4fff8b
0050003d mov ecx, edi
0050003f call 0x695680
00500044 movss xmm3, dword ptr [ebx]
00500048 movss xmm2, dword ptr [ebx + 4]
0050004d movss xmm0, dword ptr [eax + 0x294]
00500055 movss xmm1, dword ptr [eax + 0x298]
0050005d subss xmm3, xmm0
00500061 subss xmm2, xmm1
00500065 movss dword ptr [esp + 0x20], xmm0
0050006b movss xmm0, dword ptr [0xb6ad68]
00500073 movss dword ptr [esp + 0x24], xmm1
00500079 mulss xmm3, xmm3
0050007d mulss xmm2, xmm2
00500081 addss xmm2, xmm3
00500085 comiss xmm0, xmm2
00500088 jbe 0x4fff8b
0050008e cmp dword ptr [edi + 0xbb4], 8
00500095 je 0x5000c4
00500097 mov ecx, dword ptr [0xbfd65c]
0050009d lea eax, [esp + 0x20]
005000a1 push 0
005000a3 push dword ptr [esp + 0x2c]
005000a7 mov ecx, dword ptr [ecx + 0x18190]
005000ad push 0
005000af push 0x3e7
005000b4 push esi
005000b5 push eax
005000b6 push ebx
005000b7 call 0x7af4b0
005000bc test al, al
005000be je 0x4fff8b
005000c4 mov dword ptr [edi + 0xaf0], 7
005000ce mov dword ptr [edi + 0xab4], 8
005000d8 mov dword ptr [edi + 0x360], 0
005000e2 pop edi
005000e3 pop esi
005000e4 pop ebx
005000e5 mov ecx, dword ptr [esp + 0x130]
005000ec xor ecx, esp
005000ee call 0x9eacd7
005000f3 mov esp, ebp
005000f5 pop ebp
005000f6 ret 
005000f7 call 0x6c3d90
005000fc xor edx, edx
005000fe mov ecx, 0x32
00500103 div ecx
00500105 test edx, edx
00500107 jne 0x4fffd2
0050010d mov ecx, dword ptr [esp + 0x13c]
00500114 mov dword ptr [edi + 0xab4], 9
0050011e mov dword ptr [edi + 0x360], edx
00500124 pop edi
00500125 pop esi
00500126 pop ebx
00500127 xor ecx, esp
00500129 call 0x9eacd7
0050012e mov esp, ebp
00500130 pop ebp
00500131 ret 
