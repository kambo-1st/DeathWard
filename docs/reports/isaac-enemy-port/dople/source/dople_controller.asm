005135e0 push ebx
005135e1 mov ebx, esp
005135e3 sub esp, 8
005135e6 and esp, 0xfffffff8
005135e9 add esp, 4
005135ec push ebp
005135ed mov ebp, dword ptr [ebx + 4]
005135f0 mov dword ptr [esp + 4], ebp
005135f4 mov ebp, esp
005135f6 sub esp, 0xf8
005135fc mov eax, dword ptr [0xbaa3b4]
00513601 xor eax, ebp
00513603 mov dword ptr [ebp - 4], eax
00513606 push esi
00513607 mov esi, ecx
00513609 push edi
0051360a cvttss2si ecx, dword ptr [esi + 0x2fc]
00513612 cvttss2si eax, dword ptr [esi + 0x2f8]
0051361a sub ecx, eax
0051361c cmp dword ptr [esi + 0xab4], 0
00513623 mov dword ptr [ebp - 0xe0], ecx
00513629 jne 0x5136a8
0051362b and dword ptr [esi + 0x160], 0xfffffffb
00513632 cmp dword ptr [esi + 0x2c], 0
00513636 mov eax, dword ptr [esi + 0x164]
0051363c mov dword ptr [esi + 0xaf4], 0
00513646 mov dword ptr [esi + 0xaf0], 0
00513650 mov dword ptr [esi + 0xab4], 4
0051365a mov dword ptr [esi + 0x164], eax
00513660 jne 0x51368a
00513662 mov eax, 5
00513667 mov dword ptr [esi + 0xb14], 1
00513671 mov dword ptr [esi + 0x17c], eax
00513677 pop edi
00513678 pop esi
00513679 mov ecx, dword ptr [ebp - 4]
0051367c xor ecx, ebp
0051367e call 0x9eacd7
00513683 mov esp, ebp
00513685 pop ebp
00513686 mov esp, ebx
00513688 pop ebx
00513689 ret 
0051368a mov eax, 3
0051368f mov dword ptr [esi + 0x17c], eax
00513695 pop edi
00513696 pop esi
00513697 mov ecx, dword ptr [ebp - 4]
0051369a xor ecx, ebp
0051369c call 0x9eacd7
005136a1 mov esp, ebp
005136a3 pop ebp
005136a4 mov esp, ebx
005136a6 pop ebx
005136a7 ret 
005136a8 mov ecx, esi
005136aa call 0x695680
005136af movss xmm3, dword ptr [0xb6c980]
005136b7 xorps xmm2, xmm2
005136ba mov dword ptr [ebp - 0xcc], eax
005136c0 test eax, eax
005136c2 je 0x5136d8
005136c4 cmp dword ptr [eax + 0x28], 1
005136c8 jne 0x5136d8
005136ca mov edi, dword ptr [eax + 0x155c]
005136d0 mov dword ptr [ebp - 0xd8], eax
005136d6 jmp 0x51372f
005136d8 movss xmm5, dword ptr [eax + 0x2b8]
005136e0 movss xmm4, dword ptr [eax + 0x2bc]
005136e8 movaps xmm1, xmm5
005136eb movaps xmm0, xmm4
005136ee mov dword ptr [ebp - 0xd8], 0
005136f8 andps xmm1, xmm3
005136fb andps xmm0, xmm3
005136fe comiss xmm1, xmm0
00513701 jbe 0x513712
00513703 xor ecx, ecx
00513705 mov edi, 2
0051370a comiss xmm2, xmm5
0051370d cmova edi, ecx
00513710 jmp 0x51372f
00513712 xor eax, eax
00513714 comiss xmm2, xmm4
00513717 setbe al
0051371a lea eax, [eax*2 + 1]
00513721 mov dword ptr [ebp - 0xc4], eax
00513727 mov edi, eax
00513729 mov eax, dword ptr [ebp - 0xcc]
0051372f cmp dword ptr [esi + 0xe6c], -1
00513736 xorps xmm1, xmm1
00513739 movss xmm0, dword ptr [0xb6a614]
00513741 movss dword ptr [ebp - 0xc8], xmm2
00513749 movss dword ptr [ebp - 0xdc], xmm1
00513751 movss dword ptr [ebp - 0xc4], xmm0
00513759 je 0x513b1a
0051375f lea eax, [ebp - 0xc0]
00513765 mov ecx, esi
00513767 push eax
00513768 call 0x6af0c0
0051376d movss xmm0, dword ptr [ebp - 0xbc]
00513775 movss xmm1, dword ptr [ebp - 0xc0]
0051377d movss dword ptr [ebp - 0xc8], xmm0
00513785 movss xmm0, dword ptr [esi + 0x2b8]
0051378d mulss xmm0, dword ptr [0xb6a480]
00513795 movss dword ptr [ebp - 0xdc], xmm1
0051379d movss dword ptr [ebp - 0xcc], xmm0
005137a5 movss dword ptr [esi + 0x2b8], xmm0
005137ad movss xmm0, dword ptr [esi + 0x2bc]
005137b5 mulss xmm0, dword ptr [0xb6a480]
005137bd movss dword ptr [esi + 0x2bc], xmm0
005137c5 movss dword ptr [ebp - 0xb4], xmm0
005137cd movss xmm0, dword ptr [0xb6a544]
005137d5 call 0x4228c0
005137da movss xmm2, dword ptr [ebp - 0xdc]
005137e2 movaps xmm7, xmm0
005137e5 movss xmm6, dword ptr [ebp - 0xc8]
005137ed movaps xmm0, xmm2
005137f0 mulss xmm0, dword ptr [0xb6a480]
005137f8 mov edi, 2
005137fd movss xmm4, dword ptr [ebp - 0xb4]
00513805 xorps xmm5, xmm5
00513808 movss xmm3, dword ptr [ebp - 0xcc]
00513810 movss dword ptr [ebp - 0xd0], xmm0
00513818 movaps xmm0, xmm6
0051381b mulss xmm0, dword ptr [0xb6a480]
00513823 movss dword ptr [ebp - 0xe4], xmm7
0051382b movss dword ptr [ebp - 0xbc], xmm0
00513833 movaps xmm0, xmm4
00513836 movss dword ptr [ebp - 0xb4], xmm0
0051383e jmp 0x513848
00513840 movss xmm2, dword ptr [ebp - 0xdc]
00513848 ucomiss xmm2, xmm5
0051384b lahf 
0051384c test ah, 0x44
0051384f jp 0x51385e
00513851 ucomiss xmm6, xmm5
00513854 lahf 
00513855 test ah, 0x44
00513858 jnp 0x5138eb
0051385e movaps xmm1, xmm0
00513861 movaps xmm0, xmm3
00513864 mulss xmm0, xmm2
00513868 mulss xmm1, xmm6
0051386c addss xmm1, xmm0
00513870 movaps xmm0, xmm1
00513873 mulss xmm1, xmm6
00513877 mulss xmm0, xmm2
0051387b movss dword ptr [ebp - 0xec], xmm1
00513883 movss dword ptr [ebp - 0xf0], xmm0
0051388b movss xmm0, dword ptr [0xb6a560]
00513893 call 0x4228c0
00513898 movss xmm4, dword ptr [ebp - 0xb4]
005138a0 xorps xmm5, xmm5
005138a3 subss xmm4, dword ptr [ebp - 0xec]
005138ab movss xmm3, dword ptr [ebp - 0xcc]
005138b3 subss xmm3, dword ptr [ebp - 0xf0]
005138bb movss xmm7, dword ptr [ebp - 0xe4]
005138c3 movss xmm6, dword ptr [ebp - 0xc8]
005138cb mulss xmm4, xmm0
005138cf mulss xmm3, xmm0
005138d3 addss xmm4, dword ptr [ebp - 0xec]
005138db addss xmm3, dword ptr [ebp - 0xf0]
005138e3 movss dword ptr [ebp - 0xb4], xmm4
005138eb movaps xmm2, xmm3
005138ee mulss xmm4, xmm6
005138f2 movaps xmm0, xmm2
005138f5 movss xmm6, dword ptr [esi + 0x2f4]
005138fd mulss xmm0, dword ptr [ebp - 0xdc]
00513905 ucomiss xmm6, dword ptr [ebp - 0xc4]
0051390c addss xmm0, xmm4
00513910 movss xmm3, dword ptr [ebp - 0xd0]
00513918 movss xmm4, dword ptr [ebp - 0xbc]
00513920 lahf 
00513921 mulss xmm0, dword ptr [0xb6ae00]
00513929 maxss xmm0, xmm5
0051392d addss xmm0, dword ptr [0xb6a864]
00513935 mulss xmm0, dword ptr [0xb6a434]
0051393d movaps xmm1, xmm0
00513940 mulss xmm1, dword ptr [0xb6a38c]
00513948 subss xmm1, xmm0
0051394c mulss xmm1, xmm5
00513950 addss xmm1, xmm0
00513954 mulss xmm3, xmm1
00513958 mulss xmm4, xmm1
0051395c movaps xmm1, xmm7
0051395f mulss xmm3, xmm6
00513963 mulss xmm4, xmm6
00513967 addss xmm3, xmm2
0051396b addss xmm4, dword ptr [ebp - 0xb4]
00513973 test ah, 0x44
00513976 jnp 0x51398b
00513978 movaps xmm0, xmm6
0051397b mulss xmm6, xmm7
0051397f addss xmm0, xmm7
00513983 subss xmm0, xmm6
00513987 divss xmm1, xmm0
0051398b movss xmm6, dword ptr [ebp - 0xc8]
00513993 mulss xmm4, xmm1
00513997 mulss xmm3, xmm1
0051399b movss dword ptr [esi + 0x2bc], xmm4
005139a3 movaps xmm0, xmm4
005139a6 movss dword ptr [ebp - 0xb4], xmm4
005139ae movss dword ptr [ebp - 0xcc], xmm3
005139b6 movss dword ptr [esi + 0x2b8], xmm3
005139be sub edi, 1
005139c1 jne 0x513840
005139c7 movss xmm2, dword ptr [0xb6a2cc]
005139cf addss xmm3, xmm3
005139d3 movaps xmm0, xmm4
005139d6 lea eax, [ebp - 0xc0]
005139dc addss xmm0, xmm0
005139e0 mov ecx, esi
005139e2 push eax
005139e3 movss dword ptr [esi + 0x2b8], xmm3
005139eb movss dword ptr [esi + 0x2bc], xmm0
005139f3 call 0x6af380
005139f8 mov ecx, eax
005139fa movss xmm0, dword ptr [ecx]
005139fe ucomiss xmm0, dword ptr [0xc02fec]
00513a05 lahf 
00513a06 test ah, 0x44
00513a09 jp 0x513aad
00513a0f movss xmm0, dword ptr [ecx + 4]
00513a14 ucomiss xmm0, dword ptr [0xc02ff0]
00513a1b lahf 
00513a1c test ah, 0x44
00513a1f jp 0x513aad
00513a25 movss xmm3, dword ptr [esi + 0x2bc]
00513a2d movss xmm4, dword ptr [esi + 0x2b8]
00513a35 movaps xmm0, xmm3
00513a38 movaps xmm1, xmm4
00513a3b mulss xmm0, xmm3
00513a3f mulss xmm1, xmm4
00513a43 addss xmm1, xmm0
00513a47 comiss xmm1, dword ptr [0xb6a214]
00513a4e jbe 0x513a9e
00513a50 movaps xmm0, xmm3
00513a53 movaps xmm1, xmm4
00513a56 andps xmm0, xmmword ptr [0xb6c980]
00513a5d andps xmm1, xmmword ptr [0xb6c980]
00513a64 comiss xmm1, xmm0
00513a67 xorps xmm0, xmm0
00513a6a jbe 0x513a84
00513a6c xor ecx, ecx
00513a6e mov eax, 2
00513a73 comiss xmm0, xmm4
00513a76 cmova eax, ecx
00513a79 mov dword ptr [ebp - 0xb4], eax
00513a7f jmp 0x513c3a
00513a84 xor eax, eax
00513a86 comiss xmm0, xmm3
00513a89 setbe al
00513a8c lea eax, [eax*2 + 1]
00513a93 mov dword ptr [ebp - 0xb4], eax
00513a99 jmp 0x513c3a
00513a9e mov dword ptr [ebp - 0xb4], 3
00513aa8 jmp 0x513c3a
00513aad movss xmm2, dword ptr [0xb6a2cc]
00513ab5 lea eax, [ebp - 0xc0]
00513abb push eax
00513abc mov ecx, esi
00513abe call 0x6af380
00513ac3 movss xmm4, dword ptr [eax]
00513ac7 movss xmm3, dword ptr [eax + 4]
00513acc movaps xmm1, xmm4
00513acf andps xmm1, xmmword ptr [0xb6c980]
00513ad6 movaps xmm0, xmm3
00513ad9 andps xmm0, xmmword ptr [0xb6c980]
00513ae0 comiss xmm1, xmm0
00513ae3 xorps xmm0, xmm0
00513ae6 jbe 0x513b00
00513ae8 xor eax, eax
00513aea mov edi, 2
00513aef comiss xmm0, xmm4
00513af2 cmova edi, eax
00513af5 mov dword ptr [ebp - 0xb4], edi
00513afb jmp 0x513c40
00513b00 xor ecx, ecx
00513b02 comiss xmm0, xmm3
00513b05 setbe cl
00513b08 lea ecx, [ecx*2 + 1]
00513b0f mov dword ptr [ebp - 0xb4], ecx
00513b15 jmp 0x513c3a
00513b1a movss xmm0, dword ptr [esi + 0x2c4]
00513b22 mulss xmm0, dword ptr [0xb6a53c]
00513b2a mov ecx, dword ptr [0xbfd65c]
00513b30 movss dword ptr [esi + 0x2c4], xmm0
00513b38 movss xmm0, dword ptr [eax + 0x294]
00513b40 mov ecx, dword ptr [ecx + 0x18190]
00513b46 movss dword ptr [ebp - 0xbc], xmm0
00513b4e movss xmm0, dword ptr [eax + 0x298]
00513b56 lea eax, [ebp - 0xe8]
00513b5c push eax
00513b5d movss dword ptr [ebp - 0xd0], xmm0
00513b65 call 0x7ce9c0
00513b6a lea ecx, [edi + 2]
00513b6d and ecx, 0x80000003
00513b73 jns 0x513b7a
00513b75 dec ecx
00513b76 or ecx, 0xfffffffc
00513b79 inc ecx
00513b7a mov eax, dword ptr [esi + 0x160]
00513b80 and eax, 0x200
00513b85 mov dword ptr [ebp - 0xb4], ecx
00513b8b or eax, 0
00513b8e je 0x513ba6
00513b90 add ecx, 2
00513b93 and ecx, 0x80000003
00513b99 jns 0x513ba0
00513b9b dec ecx
00513b9c or ecx, 0xfffffffc
00513b9f inc ecx
00513ba0 mov dword ptr [ebp - 0xb4], ecx
00513ba6 movss xmm0, dword ptr [ebp - 0xe8]
00513bae mulss xmm0, dword ptr [0xb6a7b0]
00513bb6 mov eax, dword ptr [esi + 0x294]
00513bbc mov dword ptr [esi + 0x28c], eax
00513bc2 mov eax, dword ptr [esi + 0x298]
00513bc8 subss xmm0, dword ptr [ebp - 0xbc]
00513bd0 mov dword ptr [esi + 0x290], eax
00513bd6 mov eax, dword ptr [ebp - 0xcc]
00513bdc movss dword ptr [esi + 0x294], xmm0
00513be4 movss xmm0, dword ptr [ebp - 0xe4]
00513bec mulss xmm0, dword ptr [0xb6a7b0]
00513bf4 subss xmm0, dword ptr [ebp - 0xd0]
00513bfc movss dword ptr [esi + 0x298], xmm0
00513c04 movss xmm1, dword ptr [eax + 0x2b8]
00513c0c movss xmm2, dword ptr [eax + 0x2bc]
00513c14 xorps xmm1, xmmword ptr [0xb6c9b0]
00513c1b xorps xmm2, xmmword ptr [0xb6c9b0]
00513c22 addss xmm1, xmm1
00513c26 addss xmm2, xmm2
00513c2a movss dword ptr [esi + 0x2b8], xmm1
00513c32 movss dword ptr [esi + 0x2bc], xmm2
00513c3a mov edi, dword ptr [ebp - 0xb4]
00513c40 mov eax, dword ptr [esi + 0xaf0]
00513c46 mov ecx, dword ptr [ebp - 0xe0]
00513c4c test eax, eax
00513c4e jle 0x513c58
00513c50 sub eax, ecx
00513c52 mov dword ptr [esi + 0xaf0], eax
00513c58 mov eax, dword ptr [esi + 0xaf4]
00513c5e test eax, eax
00513c60 jle 0x513c6a
00513c62 sub eax, ecx
00513c64 mov dword ptr [esi + 0xaf4], eax
00513c6a cmp dword ptr [esi + 0xe6c], -1
00513c71 je 0x513c99
00513c73 movss xmm1, dword ptr [0xb6accc]
00513c7b mov ecx, esi
00513c7d push 7
00513c7f push 0
00513c81 call 0x6a15a0
00513c86 mov ecx, dword ptr [ebp - 0xd8]
00513c8c movzx eax, al
00513c8f test eax, eax
00513c91 je 0x513eec
00513c97 jmp 0x513cc6
00513c99 mov ecx, dword ptr [ebp - 0xd8]
00513c9f test ecx, ecx
00513ca1 je 0x513f09
00513ca7 mov eax, dword ptr [ecx + 0x132c]
00513cad test eax, eax
00513caf je 0x513cb8
00513cb1 cvttss2si eax, dword ptr [eax + 0xc]
00513cb6 jmp 0x513cba
00513cb8 xor eax, eax
00513cba cmp eax, dword ptr [esi + 0xb10]
00513cc0 jle 0x513ef0
00513cc6 mov eax, dword ptr [esi + 0x160]
00513ccc and eax, 0x1000800
00513cd1 or eax, 0
00513cd4 jne 0x513eec
00513cda cmp dword ptr [esi + 0xaf0], eax
00513ce0 jg 0x513eec
00513ce6 lea ecx, [ebp - 0xb0]
00513cec call 0x430d70
00513cf1 mov edx, edi
00513cf3 mov dword ptr [ebp - 0xa8], 0x3f800000
00513cfd lea ecx, [ebp - 0xc0]
00513d03 mov dword ptr [ebp - 0xa4], 0xbdced917
00513d0d mov dword ptr [ebp - 0x9c], 0x3fb33333
00513d17 call 0x659400
00513d1c cmp dword ptr [esi + 0xe6c], -1
00513d23 je 0x513d5b
00513d25 movss xmm2, dword ptr [0xb6a2cc]
00513d2d lea eax, [ebp - 0xe8]
00513d33 push eax
00513d34 mov ecx, esi
00513d36 call 0x6af380
00513d3b mov edx, eax
00513d3d lea ecx, [ebp - 0xf4]
00513d43 call 0x6593a0
00513d48 movss xmm2, dword ptr [eax]
00513d4c movss dword ptr [ebp - 0xc0], xmm2
00513d54 movss xmm3, dword ptr [eax + 4]
00513d59 jmp 0x513d6b
00513d5b movss xmm3, dword ptr [ebp - 0xbc]
00513d63 movss xmm2, dword ptr [ebp - 0xc0]
00513d6b movss xmm4, dword ptr [esi + 0x2b8]
00513d73 movaps xmm1, xmm3
00513d76 movss xmm5, dword ptr [esi + 0x2bc]
00513d7e movaps xmm0, xmm2
00513d81 mulss xmm4, dword ptr [0xb6a4c4]
00513d89 movaps xmm6, xmm2
00513d8c mulss xmm5, dword ptr [0xb6a4c4]
00513d94 movaps xmm7, xmm3
00513d97 mulss xmm0, xmm4
00513d9b mulss xmm1, xmm5
00513d9f addss xmm1, xmm0
00513da3 movaps xmm0, xmm2
00513da6 mulss xmm6, xmm1
00513daa mulss xmm7, xmm1
00513dae movaps xmm1, xmm3
00513db1 mulss xmm0, xmm6
00513db5 mulss xmm1, xmm7
00513db9 addss xmm1, xmm0
00513dbd xorps xmm0, xmm0
00513dc0 comiss xmm0, xmm1
00513dc3 jbe 0x513dcd
00513dc5 subss xmm4, xmm6
00513dc9 subss xmm5, xmm7
00513dcd cmp dword ptr [esi + 0xb14], 0
00513dd4 mulss xmm2, dword ptr [0xb6a974]
00513ddc mulss xmm3, dword ptr [0xb6a974]
00513de4 addss xmm2, xmm4
00513de8 movss xmm4, dword ptr [esi + 0x294]
00513df0 movss dword ptr [ebp - 0xd4], xmm4
00513df8 addss xmm3, xmm5
00513dfc movss xmm5, dword ptr [esi + 0x298]
00513e04 movss dword ptr [ebp - 0xd0], xmm5
00513e0c movss dword ptr [ebp - 0xc0], xmm2
00513e14 movss dword ptr [ebp - 0xbc], xmm3
00513e1c je 0x513e85
00513e1e call 0x6c3d90
00513e23 xorps xmm0, xmm0
00513e26 cvtsi2sd xmm0, eax
00513e2a shr eax, 0x1f
00513e2d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00513e36 cvtpd2ps xmm1, xmm0
00513e3a xorps xmm0, xmm0
00513e3d mulss xmm1, dword ptr [0xb6a19c]
00513e45 cvtsi2ss xmm0, dword ptr [esi + 0xb14]
00513e4d mulss xmm1, dword ptr [0xb6a350]
00513e55 mulss xmm3, xmm0
00513e59 addss xmm1, dword ptr [0xb6a3b0]
00513e61 mulss xmm2, xmm0
00513e65 mulss xmm3, xmm1
00513e69 mulss xmm2, xmm1
00513e6d subss xmm4, xmm3
00513e71 subss xmm5, xmm2
00513e75 movss dword ptr [ebp - 0xd4], xmm4
00513e7d movss dword ptr [ebp - 0xd0], xmm5
00513e85 cmp dword ptr [esi + 0x2c], 1
00513e89 jne 0x513e9c
00513e8b mov dword ptr [esi + 0xaf0], 0x1e
00513e95 mov eax, 2
00513e9a jmp 0x513eb1
00513e9c cmp dword ptr [esi + 0xe6c], -1
00513ea3 je 0x513eaf
00513ea5 mov dword ptr [esi + 0xaf0], 0xa
00513eaf xor eax, eax
00513eb1 lea ecx, [ebp - 0xb0]
00513eb7 push ecx
00513eb8 push eax
00513eb9 lea eax, [ebp - 0xc0]
00513ebf mov ecx, esi
00513ec1 push eax
00513ec2 lea eax, [ebp - 0xd4]
00513ec8 push eax
00513ec9 call 0x6a1a20
00513ece mov ecx, dword ptr [ebp - 0xd8]
00513ed4 mov dword ptr [esi + 0xaf4], 3
00513ede mov eax, dword ptr [esi + 0xb14]
00513ee4 neg eax
00513ee6 mov dword ptr [esi + 0xb14], eax
00513eec test ecx, ecx
00513eee je 0x513f09
00513ef0 mov eax, dword ptr [ecx + 0x132c]
00513ef6 test eax, eax
00513ef8 je 0x513f01
00513efa cvttss2si eax, dword ptr [eax + 0xc]
00513eff jmp 0x513f03
00513f01 xor eax, eax
00513f03 mov dword ptr [esi + 0xb10], eax
00513f09 mov eax, dword ptr [ebp - 0xb4]
00513f0f mov ecx, dword ptr [esi + 0xaf4]
00513f15 mov dword ptr [ebp - 0xe0], ecx
00513f1b push 1
00513f1d cmp eax, 3
00513f20 jne 0x513f71
00513f22 xor edx, edx
00513f24 mov eax, 2
00513f29 test ecx, ecx
00513f2b lea ecx, [esi + 0x3c]
00513f2e push 0xb426f8
00513f33 cmovle eax, edx
00513f36 mov dword ptr [ebp - 0xbc], eax
00513f3c call 0x405bb0
00513f41 test al, al
00513f43 je 0x514033
00513f49 cmp dword ptr [esi + 0x90], 0
00513f50 je 0x514033
00513f56 movd xmm1, dword ptr [ebp - 0xbc]
00513f5e lea ecx, [esi + 0x8c]
00513f64 cvtdq2ps xmm1, xmm1
00513f67 call 0x403c00
00513f6c jmp 0x514033
00513f71 lea ecx, [esi + 0x3c]
00513f74 cmp eax, 1
00513f77 jne 0x513fbc
00513f79 push 0xb42748
00513f7e call 0x405bb0
00513f83 test al, al
00513f85 je 0x514033
00513f8b cmp dword ptr [esi + 0x90], 0
00513f92 je 0x514033
00513f98 xor ecx, ecx
00513f9a mov eax, 2
00513f9f cmp dword ptr [ebp - 0xe0], ecx
00513fa5 cmovle eax, ecx
00513fa8 lea ecx, [esi + 0x8c]
00513fae movd xmm1, eax
00513fb2 cvtdq2ps xmm1, xmm1
00513fb5 call 0x403c00
00513fba jmp 0x514033
00513fbc push 0xb43104
00513fc1 call 0x405bb0
00513fc6 test al, al
00513fc8 je 0x513ff5
00513fca cmp dword ptr [esi + 0x90], 0
00513fd1 je 0x513ff5
00513fd3 xor ecx, ecx
00513fd5 mov eax, 2
00513fda cmp dword ptr [ebp - 0xe0], ecx
00513fe0 cmovle eax, ecx
00513fe3 lea ecx, [esi + 0x8c]
00513fe9 movd xmm1, eax
00513fed cvtdq2ps xmm1, xmm1
00513ff0 call 0x403c00
00513ff5 cmp dword ptr [esi + 0xbc], 1
00513ffc lea eax, [esi + 0x3c]
00513fff jg 0x514020
00514001 cmp dword ptr [eax + 0x14], 0x10
00514005 mov ecx, eax
00514007 jb 0x51400b
00514009 mov ecx, dword ptr [eax]
0051400b push 1
0051400d push ecx
0051400e push 0xa0830c
00514013 push 3
00514015 call 0x95e330
0051401a add esp, 0x10
0051401d lea eax, [esi + 0x3c]
00514020 cmp dword ptr [ebp - 0xb4], 0
00514027 mov eax, dword ptr [eax + 0x7c]
0051402a sete cl
0051402d mov byte ptr [eax + 0xce], cl
00514033 cmp dword ptr [esi + 0xe6c], -1
0051403a je 0x514275
00514040 mov edx, dword ptr [esi + 0x2c]
00514043 mov eax, 0xb404ec
00514048 movss xmm3, dword ptr [ebp - 0xdc]
00514050 cmp edx, 1
00514053 movss xmm4, dword ptr [ebp - 0xc8]
0051405b mov ecx, 0xb40800
00514060 cmovne ecx, eax
00514063 mov byte ptr [ebp - 0xb5], 0
0051406a ucomiss xmm3, dword ptr [0xc02fec]
00514071 lahf 
00514072 test ah, 0x44
00514075 jp 0x5140ba
00514077 ucomiss xmm4, dword ptr [0xc02ff0]
0051407e lahf 
0051407f test ah, 0x44
00514082 jp 0x5140ba
00514084 cmp edx, 1
00514087 je 0x5140ff
00514089 push 1
0051408b push ecx
0051408c lea ecx, [esi + 0x3c]
0051408f call 0x405740
00514094 test al, al
00514096 je 0x51410a
00514098 mov eax, dword ptr [esi + 0x70]
0051409b test eax, eax
0051409d je 0x51410a
0051409f lea ecx, [esi + 0x6c]
005140a2 xorps xmm1, xmm1
005140a5 call 0x403c00
005140aa mov eax, dword ptr [esi + 0x70]
005140ad test eax, eax
005140af je 0x51410a
005140b1 mov byte ptr [esi + 0x80], 0
005140b8 jmp 0x51410a
005140ba movaps xmm1, xmm3
005140bd movaps xmm0, xmm4
005140c0 andps xmm1, xmmword ptr [0xb6c980]
005140c7 andps xmm0, xmmword ptr [0xb6c980]
005140ce comiss xmm1, xmm0
005140d1 jbe 0x5140e7
005140d3 xorps xmm0, xmm0
005140d6 mov ecx, 0xb40504
005140db comiss xmm0, xmm3
005140de seta byte ptr [ebp - 0xb5]
005140e5 jmp 0x5140ff
005140e7 cmp edx, 1
005140ea jne 0x5140ff
005140ec xorps xmm0, xmm0
005140ef mov ecx, 0xb407dc
005140f4 comiss xmm0, xmm4
005140f7 mov eax, 0xb40800
005140fc cmovbe ecx, eax
005140ff push 0
00514101 push ecx
00514102 lea ecx, [esi + 0x3c]
00514105 call 0x4054f0
0051410a cmp dword ptr [esi + 0xbc], 0
00514111 jg 0x514131
00514113 cmp dword ptr [esi + 0x50], 0x10
00514117 lea eax, [esi + 0x3c]
0051411a jb 0x51411f
0051411c mov eax, dword ptr [esi + 0x3c]
0051411f push 0
00514121 push eax
00514122 push 0xa0830c
00514127 push 3
00514129 call 0x95e330
0051412e add esp, 0x10
00514131 mov eax, dword ptr [esi + 0xb8]
00514137 mov cl, byte ptr [ebp - 0xb5]
0051413d movss xmm0, dword ptr [ebp - 0xc4]
00514145 movss dword ptr [ebp - 0xbc], xmm0
0051414d mov byte ptr [eax + 0x32], cl
00514150 cmp dword ptr [esi + 0x70], 0
00514154 je 0x51425a
0051415a cmp byte ptr [esi + 0x80], 0
00514161 je 0x51425a
00514167 movss xmm1, dword ptr [esi + 0x2bc]
0051416f movss xmm0, dword ptr [esi + 0x2b8]
00514177 mulss xmm0, xmm0
0051417b mulss xmm1, xmm1
0051417f addss xmm0, xmm1
00514183 call 0x4228c0
00514188 movss xmm1, dword ptr [0xb6a808]
00514190 movaps xmm3, xmm0
00514193 comiss xmm1, xmm3
00514196 xorps xmm2, xmm2
00514199 jbe 0x5141fb
0051419b movss xmm4, dword ptr [ebp - 0xc4]
005141a3 lea eax, [ebp - 0xbc]
005141a9 movaps xmm1, xmm3
005141ac mov dword ptr [ebp - 0xbc], 0
005141b6 subss xmm1, xmm4
005141ba lea ecx, [ebp - 0xd0]
005141c0 divss xmm1, dword ptr [0xb6a690]
005141c8 comiss xmm2, xmm1
005141cb movss dword ptr [ebp - 0xd0], xmm1
005141d3 cmovbe eax, ecx
005141d6 movss xmm0, dword ptr [eax]
005141da comiss xmm0, xmm4
005141dd ja 0x5141e5
005141df movss xmm0, xmm0
005141e3 jmp 0x5141e9
005141e5 movss xmm0, xmm4
005141e9 mulss xmm0, dword ptr [0xb6a480]
005141f1 addss xmm0, dword ptr [0xb6a480]
005141f9 jmp 0x514206
005141fb movss xmm0, dword ptr [ebp - 0xbc]
00514203 movaps xmm4, xmm0
00514206 movss xmm1, dword ptr [0xb6a910]
0051420e comiss xmm3, xmm1
00514211 jbe 0x51425a
00514213 subss xmm3, xmm1
00514217 mov dword ptr [ebp - 0xbc], 0
00514221 lea eax, [ebp - 0xbc]
00514227 lea ecx, [ebp - 0xd0]
0051422d mulss xmm3, dword ptr [0xb6a38c]
00514235 comiss xmm2, xmm3
00514238 movss dword ptr [ebp - 0xd0], xmm3
00514240 cmovbe eax, ecx
00514243 movss xmm0, dword ptr [eax]
00514247 comiss xmm0, xmm4
0051424a ja 0x514252
0051424c movss xmm0, xmm0
00514250 jmp 0x514256
00514252 movss xmm0, xmm4
00514256 addss xmm0, xmm4
0051425a movss dword ptr [esi + 0x140], xmm0
00514262 pop edi
00514263 pop esi
00514264 mov ecx, dword ptr [ebp - 4]
00514267 xor ecx, ebp
00514269 call 0x9eacd7
0051426e mov esp, ebp
00514270 pop ebp
00514271 mov esp, ebx
00514273 pop ebx
00514274 ret 
00514275 movss xmm2, dword ptr [esi + 0x2b8]
0051427d movss xmm1, dword ptr [esi + 0x2bc]
00514285 movaps xmm0, xmm2
00514288 mulss xmm0, xmm2
0051428c mulss xmm1, xmm1
00514290 addss xmm0, xmm1
00514294 call 0x4228c0
00514299 movss xmm3, dword ptr [ebp - 0xc4]
005142a1 comiss xmm3, xmm0
005142a4 jbe 0x514389
005142aa movss xmm1, dword ptr [esi + 0x294]
005142b2 subss xmm1, dword ptr [esi + 0x28c]
005142ba movss xmm2, dword ptr [0xb6c980]
005142c2 andps xmm1, xmm2
005142c5 comiss xmm3, xmm1
005142c8 jbe 0x51433d
005142ca movss xmm0, dword ptr [esi + 0x298]
005142d2 subss xmm0, dword ptr [esi + 0x290]
005142da andps xmm0, xmm2
005142dd comiss xmm3, xmm0
005142e0 jbe 0x51433d
005142e2 cmp dword ptr [esi + 0x2c], 0
005142e6 jne 0x51430b
005142e8 mov eax, 0xb404ec
005142ed lea ecx, [esi + 0x3c]
005142f0 push 0
005142f2 push eax
005142f3 call 0x405850
005142f8 pop edi
005142f9 pop esi
005142fa mov ecx, dword ptr [ebp - 4]
005142fd xor ecx, ebp
005142ff call 0x9eacd7
00514304 mov esp, ebp
00514306 pop ebp
00514307 mov esp, ebx
00514309 pop ebx
0051430a ret 
0051430b cmp dword ptr [ebp - 0xb4], 1
00514312 mov ecx, 0xb40800
00514317 mov eax, 0xb407dc
0051431c cmovne eax, ecx
0051431f lea ecx, [esi + 0x3c]
00514322 push 0
00514324 push eax
00514325 call 0x405850
0051432a pop edi
0051432b pop esi
0051432c mov ecx, dword ptr [ebp - 4]
0051432f xor ecx, ebp
00514331 call 0x9eacd7
00514336 mov esp, ebp
00514338 pop ebp
00514339 mov esp, ebx
0051433b pop ebx
0051433c ret 
0051433d movss xmm0, dword ptr [esi + 0x298]
00514345 subss xmm0, dword ptr [esi + 0x290]
0051434d andps xmm0, xmm2
00514350 comiss xmm1, xmm0
00514353 ja 0x5143af
00514355 cmp dword ptr [esi + 0x2c], 0
00514359 jne 0x514367
0051435b push 0
0051435d push 0xb404ec
00514362 jmp 0x51442f
00514367 comiss xmm0, dword ptr [0xb6a18c]
0051436e push 0
00514370 lea ecx, [esi + 0x3c]
00514373 jbe 0x51437f
00514375 push 0xb407dc
0051437a jmp 0x514432
0051437f push 0xb40800
00514384 jmp 0x514432
00514389 movss xmm3, dword ptr [esi + 0x2bc]
00514391 movss xmm2, dword ptr [esi + 0x2b8]
00514399 movaps xmm0, xmm3
0051439c andps xmm2, xmmword ptr [0xb6c980]
005143a3 andps xmm0, xmmword ptr [0xb6c980]
005143aa comiss xmm2, xmm0
005143ad jbe 0x51440e
005143af push 0
005143b1 push 0xb40504
005143b6 lea ecx, [esi + 0x3c]
005143b9 call 0x4054f0
005143be cmp dword ptr [esi + 0xbc], 0
005143c5 jg 0x5143e5
005143c7 cmp dword ptr [esi + 0x50], 0x10
005143cb lea eax, [esi + 0x3c]
005143ce jb 0x5143d3
005143d0 mov eax, dword ptr [esi + 0x3c]
005143d3 push 0
005143d5 push eax
005143d6 push 0xa0830c
005143db push 3
005143dd call 0x95e330
005143e2 add esp, 0x10
005143e5 mov eax, dword ptr [esi + 0xb8]
005143eb xorps xmm0, xmm0
005143ee comiss xmm0, dword ptr [esi + 0x2b8]
005143f5 seta cl
005143f8 mov byte ptr [eax + 0x32], cl
005143fb pop edi
005143fc pop esi
005143fd mov ecx, dword ptr [ebp - 4]
00514400 xor ecx, ebp
00514402 call 0x9eacd7
00514407 mov esp, ebp
00514409 pop ebp
0051440a mov esp, ebx
0051440c pop ebx
0051440d ret 
0051440e cmp dword ptr [esi + 0x2c], 0
00514412 je 0x51435b
00514418 comiss xmm3, dword ptr [0xb6a18c]
0051441f push 0
00514421 jbe 0x51442a
00514423 push 0xb40800
00514428 jmp 0x51442f
0051442a push 0xb407dc
0051442f lea ecx, [esi + 0x3c]
00514432 call 0x4054f0
00514437 mov ecx, dword ptr [ebp - 4]
0051443a pop edi
0051443b xor ecx, ebp
0051443d pop esi
0051443e call 0x9eacd7
00514443 mov esp, ebp
00514445 pop ebp
00514446 mov esp, ebx
00514448 pop ebx
00514449 ret 
