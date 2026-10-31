004e94a0 push ebx
004e94a1 mov ebx, esp
004e94a3 sub esp, 8
004e94a6 and esp, 0xfffffff8
004e94a9 add esp, 4
004e94ac push ebp
004e94ad mov ebp, dword ptr [ebx + 4]
004e94b0 mov dword ptr [esp + 4], ebp
004e94b4 mov ebp, esp
004e94b6 push -1
004e94b8 push 0x9edc75
004e94bd mov eax, dword ptr fs:[0]
004e94c3 push eax
004e94c4 push ebx
004e94c5 sub esp, 0x140
004e94cb mov eax, dword ptr [0xbaa3b4]
004e94d0 xor eax, ebp
004e94d2 mov dword ptr [ebp - 0x14], eax
004e94d5 push esi
004e94d6 push edi
004e94d7 push eax
004e94d8 lea eax, [ebp - 0xc]
004e94db mov dword ptr fs:[0], eax
004e94e1 mov edi, ecx
004e94e3 mov eax, dword ptr [0xbfd65c]
004e94e8 mov esi, dword ptr [eax + 0x18190]
004e94ee mov eax, dword ptr [edi + 0xab4]
004e94f4 test eax, eax
004e94f6 je 0x4ea1a8
004e94fc cmp eax, 4
004e94ff je 0x4e9dab
004e9505 cmp eax, 8
004e9508 jne 0x4ea2da
004e950e movss xmm0, dword ptr [edi + 0x2c4]
004e9516 mulss xmm0, dword ptr [0xb6a50c]
004e951e movss dword ptr [edi + 0x2c4], xmm0
004e9526 cmp dword ptr [edi + 0x70], 0
004e952a je 0x4e9d9c
004e9530 push 0xb400ac
004e9535 lea ecx, [edi + 0x6c]
004e9538 call 0x405e90
004e953d test al, al
004e953f je 0x4e9d89
004e9545 push ecx
004e9546 mov dword ptr [esp], 0x3f8ccccd
004e954d xorps xmm0, xmm0
004e9550 push 0
004e9552 push 0xa
004e9554 push ecx
004e9555 movups xmmword ptr [ebp - 0x48], xmm0
004e9559 mov ecx, edi
004e955b mov dword ptr [esp], 0x3f800000
004e9562 movaps xmm0, xmmword ptr [0xb6c260]
004e9569 push 0x6c
004e956b mov dword ptr [ebp - 0x38], 0
004e9572 mov dword ptr [ebp - 0x34], 0
004e9579 mov dword ptr [ebp - 0x30], 0
004e9580 movups xmmword ptr [ebp - 0x58], xmm0
004e9584 call 0x6ad720
004e9589 mov ecx, edi
004e958b call 0x695680
004e9590 push 0
004e9592 mov ecx, edi
004e9594 movss xmm0, dword ptr [eax + 0x294]
004e959c movss dword ptr [ebp - 0x104], xmm0
004e95a4 movss dword ptr [ebp - 0x110], xmm0
004e95ac movss xmm0, dword ptr [eax + 0x298]
004e95b4 movss dword ptr [ebp - 0x124], xmm0
004e95bc movss dword ptr [ebp - 0x10c], xmm0
004e95c4 call 0x6afe20
004e95c9 cmp dword ptr [edi + 0xe6c], -1
004e95d0 je 0x4e9614
004e95d2 movss xmm1, dword ptr [edi + 0xe70]
004e95da movss xmm2, dword ptr [edi + 0xe74]
004e95e2 mulss xmm1, dword ptr [0xb6aafc]
004e95ea mulss xmm2, dword ptr [0xb6aafc]
004e95f2 addss xmm1, dword ptr [edi + 0x294]
004e95fa addss xmm2, dword ptr [edi + 0x298]
004e9602 movss dword ptr [ebp - 0x110], xmm1
004e960a movss dword ptr [ebp - 0x10c], xmm2
004e9612 jmp 0x4e9624
004e9614 movss xmm1, dword ptr [ebp - 0x104]
004e961c movss xmm2, dword ptr [ebp - 0x124]
004e9624 subss xmm1, dword ptr [edi + 0x294]
004e962c subss xmm2, dword ptr [edi + 0x298]
004e9634 lea eax, [ebp - 0x120]
004e963a push eax
004e963b lea ecx, [ebp - 0x1c]
004e963e movss dword ptr [ebp - 0x1c], xmm1
004e9643 movss dword ptr [ebp - 0x18], xmm2
004e9648 call 0x962560
004e964d cmp dword ptr [edi + 0x2c], 1
004e9651 jne 0x4e99ad
004e9657 push dword ptr [edi + 0x20]
004e965a lea eax, [ebp - 0x24]
004e965d mov ecx, edi
004e965f push eax
004e9660 call 0x6a6f60
004e9665 mov ecx, 1
004e966a sub ecx, dword ptr [eax + 0xc]
004e966d xor eax, eax
004e966f cmp eax, ecx
004e9671 sbb eax, eax
004e9673 and eax, ecx
004e9675 cmp byte ptr [ebp - 0x24], 0
004e9679 mov dword ptr [ebp - 0x10c], eax
004e967f jne 0x4e968c
004e9681 push dword ptr [ebp - 0x20]
004e9684 call 0x9eace5
004e9689 add esp, 4
004e968c xor esi, esi
004e968e mov dword ptr [ebp - 0x104], esi
004e9694 call 0x6c3d90
004e9699 xorps xmm0, xmm0
004e969c cvtsi2sd xmm0, eax
004e96a0 shr eax, 0x1f
004e96a3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e96ac cvtpd2ps xmm0, xmm0
004e96b0 mulss xmm0, dword ptr [0xb6a19c]
004e96b8 subss xmm0, dword ptr [0xb6a480]
004e96c0 mulss xmm0, dword ptr [0xb6aa0c]
004e96c8 mulss xmm0, dword ptr [0xb6a230]
004e96d0 movss dword ptr [ebp - 0x124], xmm0
004e96d8 call 0x411fe0
004e96dd movss dword ptr [ebp - 0x108], xmm0
004e96e5 movss xmm0, dword ptr [ebp - 0x124]
004e96ed call 0x412010
004e96f2 movaps xmm3, xmm0
004e96f5 movss xmm0, dword ptr [ebp - 0x108]
004e96fd movaps xmm2, xmm0
004e9700 movaps xmm1, xmm3
004e9703 mulss xmm2, dword ptr [ebp - 0x120]
004e970b mulss xmm0, dword ptr [ebp - 0x11c]
004e9713 mulss xmm1, dword ptr [ebp - 0x11c]
004e971b mulss xmm3, dword ptr [ebp - 0x120]
004e9723 subss xmm2, xmm1
004e9727 addss xmm3, xmm0
004e972b movaps xmm0, xmm2
004e972e mulss xmm0, dword ptr [0xb6a8cc]
004e9736 addss xmm0, dword ptr [edi + 0x294]
004e973e movss dword ptr [ebp - 0x1c], xmm0
004e9743 movaps xmm0, xmm3
004e9746 mulss xmm0, dword ptr [0xb6a8cc]
004e974e addss xmm0, dword ptr [edi + 0x298]
004e9756 movss dword ptr [ebp - 0x18], xmm0
004e975b call 0x6c3d90
004e9760 xorps xmm0, xmm0
004e9763 lea edx, [ebp - 0x118]
004e9769 lea ecx, [ebp - 0x1c]
004e976c cvtsi2sd xmm0, eax
004e9770 shr eax, 0x1f
004e9773 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e977c cvtpd2ps xmm1, xmm0
004e9780 mulss xmm1, dword ptr [0xb6a19c]
004e9788 mulss xmm1, dword ptr [0xb6a95c]
004e9790 addss xmm1, dword ptr [0xb6a614]
004e9798 movaps xmm0, xmm1
004e979b mulss xmm1, xmm3
004e979f movss xmm3, dword ptr [0xb6aed0]
004e97a7 mulss xmm0, xmm2
004e97ab movss dword ptr [ebp - 0x114], xmm1
004e97b3 movss dword ptr [ebp - 0x118], xmm0
004e97bb cmp esi, dword ptr [ebp - 0x10c]
004e97c1 jge 0x4e97dc
004e97c3 mov esi, dword ptr [edi + 0x20]
004e97c6 push 2
004e97c8 push edi
004e97c9 call 0x4e70a0
004e97ce mov dword ptr [eax + 0xbcc], esi
004e97d4 mov esi, dword ptr [ebp - 0x104]
004e97da jmp 0x4e97e4
004e97dc push 3
004e97de push edi
004e97df call 0x4e70a0
004e97e4 inc esi
004e97e5 add esp, 8
004e97e8 mov dword ptr [ebp - 0x104], esi
004e97ee cmp esi, 4
004e97f1 jl 0x4e9694
004e97f7 mov esi, 6
004e97fc nop dword ptr [eax]
004e9800 call 0x6c3d90
004e9805 movd xmm0, eax
004e9809 cvtdq2pd xmm0, xmm0
004e980d shr eax, 0x1f
004e9810 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9819 cvtpd2ps xmm0, xmm0
004e981d mulss xmm0, dword ptr [0xb6a19c]
004e9825 subss xmm0, dword ptr [0xb6a480]
004e982d mulss xmm0, dword ptr [0xb6aa0c]
004e9835 mulss xmm0, dword ptr [0xb6a230]
004e983d movss dword ptr [ebp - 0x10c], xmm0
004e9845 call 0x411fe0
004e984a movss dword ptr [ebp - 0x108], xmm0
004e9852 movss xmm0, dword ptr [ebp - 0x10c]
004e985a call 0x412010
004e985f movaps xmm5, xmm0
004e9862 movss xmm0, dword ptr [ebp - 0x108]
004e986a movaps xmm1, xmm5
004e986d movaps xmm4, xmm0
004e9870 mulss xmm4, dword ptr [ebp - 0x120]
004e9878 mulss xmm1, dword ptr [ebp - 0x11c]
004e9880 mulss xmm5, dword ptr [ebp - 0x120]
004e9888 mulss xmm0, dword ptr [ebp - 0x11c]
004e9890 subss xmm4, xmm1
004e9894 addss xmm5, xmm0
004e9898 call 0x6c3d90
004e989d movd xmm0, eax
004e98a1 cvtdq2pd xmm0, xmm0
004e98a5 shr eax, 0x1f
004e98a8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e98b1 cvtpd2ps xmm3, xmm0
004e98b5 mulss xmm3, dword ptr [0xb6a19c]
004e98bd mulss xmm3, dword ptr [0xb6a8cc]
004e98c5 addss xmm3, dword ptr [0xb6a7b0]
004e98cd call 0x6c3d90
004e98d2 movss xmm1, dword ptr [edi + 0x2c8]
004e98da movd xmm0, eax
004e98de cvtdq2pd xmm0, xmm0
004e98e2 shr eax, 0x1f
004e98e5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e98ee cvtpd2ps xmm2, xmm0
004e98f2 movaps xmm0, xmm1
004e98f5 mulss xmm1, xmm5
004e98f9 mulss xmm2, dword ptr [0xb6a19c]
004e9901 mulss xmm0, xmm4
004e9905 mulss xmm1, xmm2
004e9909 mulss xmm0, xmm2
004e990d addss xmm1, dword ptr [edi + 0x298]
004e9915 addss xmm0, dword ptr [edi + 0x294]
004e991d movss dword ptr [ebp - 0x114], xmm1
004e9925 movss dword ptr [ebp - 0x118], xmm0
004e992d call 0x6c3d90
004e9932 mov ecx, dword ptr [0xbfd65c]
004e9938 movaps xmm0, xmm3
004e993b push eax
004e993c push 0
004e993e push 0
004e9940 lea eax, [ebp - 0x1c]
004e9943 mulss xmm0, xmm4
004e9947 push eax
004e9948 lea eax, [ebp - 0x118]
004e994e mulss xmm3, xmm5
004e9952 push eax
004e9953 push 0x42
004e9955 push 0x3e8
004e995a movss dword ptr [ebp - 0x1c], xmm0
004e995f movss dword ptr [ebp - 0x18], xmm3
004e9964 call 0x422e20
004e9969 mov ecx, eax
004e996b xorps xmm0, xmm0
004e996e movss xmm1, dword ptr [ecx + 0x2a4]
004e9976 mov eax, dword ptr [ecx]
004e9978 addss xmm1, xmm0
004e997c movss xmm0, dword ptr [ecx + 0x2a8]
004e9984 subss xmm0, dword ptr [0xb6a9a0]
004e998c movss dword ptr [ecx + 0x2a4], xmm1
004e9994 movss dword ptr [ecx + 0x2a8], xmm0
004e999c call dword ptr [eax + 0xc]
004e999f sub esi, 1
004e99a2 jne 0x4e9800
004e99a8 jmp 0x4e9d89
004e99ad lea ecx, [ebp - 0x100]
004e99b3 call 0x430d70
004e99b8 push dword ptr [edi + 0x20]
004e99bb lea eax, [ebp - 0x24]
004e99be mov dword ptr [ebp - 0x6c], 9
004e99c5 push eax
004e99c6 mov ecx, edi
004e99c8 call 0x6a6f60
004e99cd mov ecx, 2
004e99d2 sub ecx, dword ptr [eax + 0xc]
004e99d5 xor eax, eax
004e99d7 cmp eax, ecx
004e99d9 sbb esi, esi
004e99db and esi, ecx
004e99dd mov dword ptr [ebp - 0x104], esi
004e99e3 cmp byte ptr [ebp - 0x24], al
004e99e6 jne 0x4e99f3
004e99e8 push dword ptr [ebp - 0x20]
004e99eb call 0x9eace5
004e99f0 add esp, 4
004e99f3 lea eax, [ebp - 0x100]
004e99f9 push eax
004e99fa push ecx
004e99fb mov dword ptr [esp], 0x3f800000
004e9a02 lea eax, [ebp - 0x110]
004e9a08 push eax
004e9a09 mov eax, 6
004e9a0e mov ecx, edi
004e9a10 sub eax, esi
004e9a12 push eax
004e9a13 call 0x6a3420
004e9a18 movss xmm1, dword ptr [0xb6a19c]
004e9a20 movss xmm2, dword ptr [0xb6a480]
004e9a28 movss xmm3, dword ptr [0xb6aa0c]
004e9a30 movss xmm4, dword ptr [0xb6a230]
004e9a38 test esi, esi
004e9a3a jle 0x4e9b9f
004e9a40 call 0x6c3d90
004e9a45 movd xmm0, eax
004e9a49 cvtdq2pd xmm0, xmm0
004e9a4d shr eax, 0x1f
004e9a50 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9a59 cvtpd2ps xmm0, xmm0
004e9a5d mulss xmm0, xmm1
004e9a61 subss xmm0, xmm2
004e9a65 mulss xmm0, xmm3
004e9a69 mulss xmm0, xmm4
004e9a6d movss dword ptr [ebp - 0x10c], xmm0
004e9a75 call 0x411fe0
004e9a7a movss dword ptr [ebp - 0x108], xmm0
004e9a82 movss xmm0, dword ptr [ebp - 0x10c]
004e9a8a call 0x412010
004e9a8f movss xmm3, dword ptr [ebp - 0x11c]
004e9a97 movaps xmm2, xmm0
004e9a9a movss xmm4, dword ptr [ebp - 0x120]
004e9aa2 movaps xmm1, xmm3
004e9aa5 mulss xmm4, dword ptr [ebp - 0x108]
004e9aad movss xmm0, dword ptr [ebp - 0x120]
004e9ab5 mulss xmm3, dword ptr [ebp - 0x108]
004e9abd mulss xmm0, xmm2
004e9ac1 mulss xmm1, xmm2
004e9ac5 addss xmm3, xmm0
004e9ac9 subss xmm4, xmm1
004e9acd movaps xmm0, xmm4
004e9ad0 mulss xmm0, dword ptr [0xb6a8cc]
004e9ad8 addss xmm0, dword ptr [edi + 0x294]
004e9ae0 movss dword ptr [ebp - 0x118], xmm0
004e9ae8 movaps xmm0, xmm3
004e9aeb mulss xmm0, dword ptr [0xb6a8cc]
004e9af3 addss xmm0, dword ptr [edi + 0x298]
004e9afb movss dword ptr [ebp - 0x114], xmm0
004e9b03 call 0x6c3d90
004e9b08 mov esi, dword ptr [edi + 0x20]
004e9b0b lea edx, [ebp - 0x1c]
004e9b0e push 0
004e9b10 push edi
004e9b11 movd xmm0, eax
004e9b15 lea ecx, [ebp - 0x118]
004e9b1b cvtdq2pd xmm0, xmm0
004e9b1f shr eax, 0x1f
004e9b22 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9b2b cvtpd2ps xmm1, xmm0
004e9b2f mulss xmm1, dword ptr [0xb6a19c]
004e9b37 mulss xmm1, dword ptr [0xb6a864]
004e9b3f addss xmm1, dword ptr [0xb6a614]
004e9b47 movaps xmm0, xmm1
004e9b4a mulss xmm1, xmm3
004e9b4e movss xmm3, dword ptr [0xb6aed0]
004e9b56 mulss xmm0, xmm4
004e9b5a movss dword ptr [ebp - 0x18], xmm1
004e9b5f movss dword ptr [ebp - 0x1c], xmm0
004e9b64 call 0x4e70a0
004e9b69 movss xmm1, dword ptr [0xb6a19c]
004e9b71 add esp, 8
004e9b74 sub dword ptr [ebp - 0x104], 1
004e9b7b movss xmm2, dword ptr [0xb6a480]
004e9b83 movss xmm3, dword ptr [0xb6aa0c]
004e9b8b movss xmm4, dword ptr [0xb6a230]
004e9b93 mov dword ptr [eax + 0xbcc], esi
004e9b99 jne 0x4e9a40
004e9b9f mov dword ptr [ebp - 0x104], 5
004e9ba9 nop dword ptr [eax]
004e9bb0 call 0x6c3d90
004e9bb5 movd xmm0, eax
004e9bb9 cvtdq2pd xmm0, xmm0
004e9bbd shr eax, 0x1f
004e9bc0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9bc9 cvtpd2ps xmm0, xmm0
004e9bcd mulss xmm0, xmm1
004e9bd1 subss xmm0, xmm2
004e9bd5 mulss xmm0, xmm3
004e9bd9 mulss xmm0, xmm4
004e9bdd movss dword ptr [ebp - 0x10c], xmm0
004e9be5 call 0x411fe0
004e9bea movss dword ptr [ebp - 0x108], xmm0
004e9bf2 movss xmm0, dword ptr [ebp - 0x10c]
004e9bfa call 0x412010
004e9bff movss xmm4, dword ptr [ebp - 0x120]
004e9c07 movss xmm1, dword ptr [ebp - 0x11c]
004e9c0f movaps xmm5, xmm4
004e9c12 mulss xmm5, dword ptr [ebp - 0x108]
004e9c1a mulss xmm1, xmm0
004e9c1e mulss xmm4, xmm0
004e9c22 movss xmm0, dword ptr [ebp - 0x11c]
004e9c2a subss xmm5, xmm1
004e9c2e mulss xmm0, dword ptr [ebp - 0x108]
004e9c36 addss xmm4, xmm0
004e9c3a call 0x6c3d90
004e9c3f movd xmm0, eax
004e9c43 cvtdq2pd xmm0, xmm0
004e9c47 shr eax, 0x1f
004e9c4a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9c53 cvtpd2ps xmm3, xmm0
004e9c57 mulss xmm3, dword ptr [0xb6a19c]
004e9c5f mulss xmm3, dword ptr [0xb6a8cc]
004e9c67 addss xmm3, dword ptr [0xb6a7b0]
004e9c6f call 0x6c3d90
004e9c74 movss xmm1, dword ptr [edi + 0x2c8]
004e9c7c movd xmm0, eax
004e9c80 cvtdq2pd xmm0, xmm0
004e9c84 shr eax, 0x1f
004e9c87 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e9c90 cvtpd2ps xmm2, xmm0
004e9c94 movaps xmm0, xmm5
004e9c97 mulss xmm2, dword ptr [0xb6a19c]
004e9c9f mulss xmm0, xmm1
004e9ca3 mulss xmm0, xmm2
004e9ca7 addss xmm0, dword ptr [edi + 0x294]
004e9caf movss dword ptr [ebp - 0x118], xmm0
004e9cb7 movaps xmm0, xmm4
004e9cba mulss xmm0, xmm1
004e9cbe mulss xmm0, xmm2
004e9cc2 addss xmm0, dword ptr [edi + 0x298]
004e9cca movss dword ptr [ebp - 0x114], xmm0
004e9cd2 call 0x6c3d90
004e9cd7 mov ecx, dword ptr [0xbfd65c]
004e9cdd movaps xmm0, xmm3
004e9ce0 push eax
004e9ce1 push 0x63
004e9ce3 push 0
004e9ce5 lea eax, [ebp - 0x1c]
004e9ce8 mulss xmm0, xmm5
004e9cec push eax
004e9ced lea eax, [ebp - 0x118]
004e9cf3 mulss xmm3, xmm4
004e9cf7 push eax
004e9cf8 push 0x23
004e9cfa push 0x3e8
004e9cff movss dword ptr [ebp - 0x1c], xmm0
004e9d04 movss dword ptr [ebp - 0x18], xmm3
004e9d09 call 0x422e20
004e9d0e mov esi, eax
004e9d10 xorps xmm0, xmm0
004e9d13 push 1
004e9d15 push 0
004e9d17 push 0xff
004e9d1c movss xmm1, dword ptr [esi + 0x2a4]
004e9d24 mov eax, dword ptr [esi]
004e9d26 addss xmm1, xmm0
004e9d2a movss xmm0, dword ptr [esi + 0x2a8]
004e9d32 subss xmm0, dword ptr [0xb6a9a0]
004e9d3a movss dword ptr [esi + 0x2a4], xmm1
004e9d42 movss dword ptr [esi + 0x2a8], xmm0
004e9d4a push -1
004e9d4c lea ecx, [ebp - 0x58]
004e9d4f push ecx
004e9d50 mov ecx, esi
004e9d52 call dword ptr [eax + 0x38]
004e9d55 mov eax, dword ptr [esi]
004e9d57 mov ecx, esi
004e9d59 call dword ptr [eax + 0xc]
004e9d5c sub dword ptr [ebp - 0x104], 1
004e9d63 movss xmm1, dword ptr [0xb6a19c]
004e9d6b movss xmm2, dword ptr [0xb6a480]
004e9d73 movss xmm3, dword ptr [0xb6aa0c]
004e9d7b movss xmm4, dword ptr [0xb6a230]
004e9d83 jne 0x4e9bb0
004e9d89 cmp dword ptr [edi + 0x70], 0
004e9d8d je 0x4e9d9c
004e9d8f cmp byte ptr [edi + 0x80], 0
004e9d96 jne 0x4ea2da
004e9d9c mov dword ptr [edi + 0xab4], 4
004e9da6 jmp 0x4ea2da
004e9dab mov eax, dword ptr [0xb404ec]
004e9db0 mov ecx, dword ptr [0xb404f0]
004e9db6 mov dword ptr [ebp - 0x30], 0xf
004e9dbd mov dword ptr [ebp - 0x34], 8
004e9dc4 mov dword ptr [ebp - 0x44], eax
004e9dc7 mov dword ptr [ebp - 0x40], ecx
004e9dca mov byte ptr [ebp - 0x3c], 0
004e9dce mov dword ptr [ebp - 4], 0
004e9dd5 mov eax, dword ptr [0xb40504]
004e9dda mov ecx, dword ptr [0xb40508]
004e9de0 mov dword ptr [ebp - 0x18], 0xf
004e9de7 mov dword ptr [ebp - 0x1c], 8
004e9dee mov dword ptr [ebp - 0x2c], eax
004e9df1 mov dword ptr [ebp - 0x28], ecx
004e9df4 mov byte ptr [ebp - 0x24], 0
004e9df8 push ecx
004e9df9 mov byte ptr [ebp - 4], 1
004e9dfd lea eax, [ebp - 0x44]
004e9e00 mov dword ptr [esp], 0x3dcccccd
004e9e07 mov ecx, edi
004e9e09 push eax
004e9e0a lea eax, [ebp - 0x2c]
004e9e0d push eax
004e9e0e call 0x6980a0
004e9e13 mov byte ptr [ebp - 4], 0
004e9e17 mov edx, dword ptr [ebp - 0x18]
004e9e1a cmp edx, 0x10
004e9e1d jb 0x4e9e47
004e9e1f mov ecx, dword ptr [ebp - 0x2c]
004e9e22 inc edx
004e9e23 mov eax, ecx
004e9e25 cmp edx, 0x1000
004e9e2b jb 0x4e9e3d
004e9e2d mov ecx, dword ptr [ecx - 4]
004e9e30 add edx, 0x23
004e9e33 sub eax, ecx
004e9e35 add eax, -4
004e9e38 cmp eax, 0x1f
004e9e3b ja 0x4e9e86
004e9e3d push edx
004e9e3e push ecx
004e9e3f call 0x9eb08e
004e9e44 add esp, 8
004e9e47 mov dword ptr [ebp - 4], 0xffffffff
004e9e4e mov edx, dword ptr [ebp - 0x30]
004e9e51 mov dword ptr [ebp - 0x1c], 0
004e9e58 mov dword ptr [ebp - 0x18], 0xf
004e9e5f mov byte ptr [ebp - 0x2c], 0
004e9e63 cmp edx, 0x10
004e9e66 jb 0x4e9e96
004e9e68 mov ecx, dword ptr [ebp - 0x44]
004e9e6b inc edx
004e9e6c mov eax, ecx
004e9e6e cmp edx, 0x1000
004e9e74 jb 0x4e9e8c
004e9e76 mov ecx, dword ptr [ecx - 4]
004e9e79 add edx, 0x23
004e9e7c sub eax, ecx
004e9e7e add eax, -4
004e9e81 cmp eax, 0x1f
004e9e84 jbe 0x4e9e8c
004e9e86 call dword ptr [0xa065ac]
004e9e8c push edx
004e9e8d push ecx
004e9e8e call 0x9eb08e
004e9e93 add esp, 8
004e9e96 mov eax, dword ptr [edi + 0x160]
004e9e9c and eax, 0x1000800
004e9ea1 or eax, 0
004e9ea4 je 0x4e9ef3
004e9ea6 cmp dword ptr [edi + 0xe6c], -1
004e9ead je 0x4e9ef3
004e9eaf mov ecx, edi
004e9eb1 call 0x695680
004e9eb6 push 0
004e9eb8 mov ecx, dword ptr [eax + 0x294]
004e9ebe mov eax, dword ptr [eax + 0x298]
004e9ec4 mov dword ptr [ebp - 0x18], eax
004e9ec7 lea eax, [ebp - 0x1c]
004e9eca mov dword ptr [ebp - 0x1c], ecx
004e9ecd lea ecx, [edi + 0x364]
004e9ed3 push eax
004e9ed4 call 0x7a4830
004e9ed9 movss xmm0, dword ptr [edi + 0x2c4]
004e9ee1 mulss xmm0, dword ptr [0xb6a560]
004e9ee9 movss dword ptr [edi + 0x2c4], xmm0
004e9ef1 jmp 0x4e9f20
004e9ef3 push 1
004e9ef5 push 0
004e9ef7 sub esp, 8
004e9efa lea eax, [ebp - 0x1c]
004e9efd mov ecx, edi
004e9eff mov dword ptr [esp + 4], 0x3f19999a
004e9f07 mov dword ptr [esp], 0
004e9f0e push eax
004e9f0f call 0x695a30
004e9f14 push eax
004e9f15 lea ecx, [edi + 0x364]
004e9f1b call 0x7a3650
004e9f20 cmp byte ptr [edi + 0xa90], 0
004e9f27 je 0x4e9f5a
004e9f29 call 0x6c3d90
004e9f2e xor edx, edx
004e9f30 mov ecx, 3
004e9f35 div ecx
004e9f37 test edx, edx
004e9f39 jne 0x4e9f5a
004e9f3b push ecx
004e9f3c mov dword ptr [esp], 0x3f800000
004e9f43 push edx
004e9f44 push 0x78
004e9f46 push ecx
004e9f47 mov dword ptr [esp], 0x3f4ccccd
004e9f4e mov ecx, edi
004e9f50 push 0xa7
004e9f55 call 0x6ad720
004e9f5a movd xmm3, dword ptr [edi + 0x360]
004e9f62 xorps xmm2, xmm2
004e9f65 movss xmm1, dword ptr [0xb6ab58]
004e9f6d mov ecx, edi
004e9f6f cvtdq2ps xmm3, xmm3
004e9f72 push 1
004e9f74 call 0x6afbd0
004e9f79 mov edx, dword ptr [edi + 0x360]
004e9f7f test edx, edx
004e9f81 jle 0x4e9f9d
004e9f83 cvttss2si eax, dword ptr [edi + 0x2fc]
004e9f8b cvttss2si ecx, dword ptr [edi + 0x2f8]
004e9f93 sub ecx, eax
004e9f95 add edx, ecx
004e9f97 mov dword ptr [edi + 0x360], edx
004e9f9d movss xmm0, dword ptr [edi + 0xb00]
004e9fa5 movss xmm1, dword ptr [0xb6a910]
004e9fad comiss xmm0, xmm1
004e9fb0 jbe 0x4e9fd0
004e9fb2 test edx, edx
004e9fb4 jle 0x4e9fd8
004e9fb6 cvttss2si eax, dword ptr [edi + 0x2fc]
004e9fbe cvttss2si ecx, dword ptr [edi + 0x2f8]
004e9fc6 sub ecx, eax
004e9fc8 add edx, ecx
004e9fca mov dword ptr [edi + 0x360], edx
004e9fd0 test edx, edx
004e9fd2 jg 0x4ea2da
004e9fd8 cmp dword ptr [edi + 0xe6c], -1
004e9fdf je 0x4ea001
004e9fe1 movss xmm1, dword ptr [0xb6accc]
004e9fe9 mov ecx, edi
004e9feb push 7
004e9fed push 0
004e9fef call 0x6a15a0
004e9ff4 movzx eax, al
004e9ff7 test eax, eax
004e9ff9 je 0x4ea2da
004e9fff jmp 0x4ea03a
004ea001 call 0x6c3d90
004ea006 xor edx, edx
004ea008 mov ecx, 0x3c
004ea00d div ecx
004ea00f test edx, edx
004ea011 je 0x4ea03a
004ea013 movss xmm0, dword ptr [edi + 0xb00]
004ea01b comiss xmm0, xmm1
004ea01e jbe 0x4ea2da
004ea024 call 0x6c3d90
004ea029 xor edx, edx
004ea02b mov ecx, 0x14
004ea030 div ecx
004ea032 test edx, edx
004ea034 jne 0x4ea2da
004ea03a push 0
004ea03c push 0x1000a00
004ea041 mov ecx, edi
004ea043 call 0x4122f0
004ea048 test al, al
004ea04a jne 0x4ea2da
004ea050 cmp dword ptr [edi + 0x34], 0x38a
004ea057 je 0x4ea2da
004ea05d mov ecx, edi
004ea05f call 0x695680
004ea064 movss xmm1, dword ptr [eax + 0x294]
004ea06c movss xmm0, dword ptr [eax + 0x298]
004ea074 subss xmm0, dword ptr [edi + 0x298]
004ea07c movss dword ptr [ebp - 0x10c], xmm1
004ea084 subss xmm1, dword ptr [edi + 0x294]
004ea08c mulss xmm0, xmm0
004ea090 mulss xmm1, xmm1
004ea094 addss xmm0, xmm1
004ea098 call 0x4228c0
004ea09d movss xmm1, dword ptr [0xb6aba8]
004ea0a5 comiss xmm1, xmm0
004ea0a8 ja 0x4ea0d6
004ea0aa movss xmm1, dword ptr [0xb6ac60]
004ea0b2 comiss xmm1, xmm0
004ea0b5 jbe 0x4ea0c9
004ea0b7 call 0x6c3d90
004ea0bc xor edx, edx
004ea0be mov ecx, 0xa
004ea0c3 div ecx
004ea0c5 test edx, edx
004ea0c7 je 0x4ea0d6
004ea0c9 cmp dword ptr [edi + 0xe6c], -1
004ea0d0 je 0x4ea2da
004ea0d6 mov eax, dword ptr [esi + 0x1264]
004ea0dc xor ecx, ecx
004ea0de cmp dword ptr [edi + 0x2c], 1
004ea0e2 jne 0x4ea109
004ea0e4 test eax, eax
004ea0e6 je 0x4ea13c
004ea0e8 mov edx, dword ptr [esi + 0x125c]
004ea0ee nop 
004ea0f0 mov esi, dword ptr [edx]
004ea0f2 cmp dword ptr [esi + 0x28], 0x21
004ea0f6 jne 0x4ea0ff
004ea0f8 cmp dword ptr [esi + 0x2c], 2
004ea0fc jne 0x4ea0ff
004ea0fe inc ecx
004ea0ff add edx, 4
004ea102 sub eax, 1
004ea105 jne 0x4ea0f0
004ea107 jmp 0x4ea133
004ea109 test eax, eax
004ea10b je 0x4ea13c
004ea10d mov edx, dword ptr [esi + 0x125c]
004ea113 mov esi, dword ptr [edx]
004ea115 cmp dword ptr [esi + 0x28], 0x55
004ea119 jne 0x4ea121
004ea11b cmp dword ptr [esi + 0x2c], 0
004ea11f jmp 0x4ea128
004ea121 cmp dword ptr [esi + 0x28], 0x332
004ea128 jne 0x4ea12b
004ea12a inc ecx
004ea12b add edx, 4
004ea12e sub eax, 1
004ea131 jne 0x4ea113
004ea133 cmp ecx, 9
004ea136 jge 0x4ea2da
004ea13c push 1
004ea13e mov ecx, edi
004ea140 call 0x6afe20
004ea145 cmp dword ptr [edi + 0xe6c], -1
004ea14c movss xmm1, dword ptr [edi + 0x294]
004ea154 je 0x4ea16c
004ea156 movss xmm0, dword ptr [edi + 0xe70]
004ea15e mulss xmm0, dword ptr [0xb6aafc]
004ea166 addss xmm0, xmm1
004ea16a jmp 0x4ea174
004ea16c movss xmm0, dword ptr [ebp - 0x10c]
004ea174 comiss xmm1, xmm0
004ea177 push 0
004ea179 push 0xb40510
004ea17e lea ecx, [edi + 0x3c]
004ea181 mov dword ptr [edi + 0xab4], 8
004ea18b seta al
004ea18e mov byte ptr [edi + 0x13c], al
004ea194 call 0x4054f0
004ea199 mov dword ptr [edi + 0x360], 0x96
004ea1a3 jmp 0x4ea2da
004ea1a8 mov dword ptr [edi + 0xab4], 4
004ea1b2 mov esi, dword ptr [edi + 0x70]
004ea1b5 test esi, esi
004ea1b7 je 0x4ea203
004ea1b9 cmp dword ptr [esi + 0x14], 0x10
004ea1bd mov eax, esi
004ea1bf jb 0x4ea1c3
004ea1c1 mov eax, dword ptr [esi]
004ea1c3 mov ecx, 0xb404ec
004ea1c8 mov dl, byte ptr [eax]
004ea1ca cmp dl, byte ptr [ecx]
004ea1cc jne 0x4ea1e8
004ea1ce test dl, dl
004ea1d0 je 0x4ea1e4
004ea1d2 mov dl, byte ptr [eax + 1]
004ea1d5 cmp dl, byte ptr [ecx + 1]
004ea1d8 jne 0x4ea1e8
004ea1da add eax, 2
004ea1dd add ecx, 2
004ea1e0 test dl, dl
004ea1e2 jne 0x4ea1c8
004ea1e4 xor eax, eax
004ea1e6 jmp 0x4ea1ed
004ea1e8 sbb eax, eax
004ea1ea or eax, 1
004ea1ed test eax, eax
004ea1ef jne 0x4ea203
004ea1f1 cmp byte ptr [esi + 0x34], al
004ea1f4 je 0x4ea224
004ea1f6 cmp byte ptr [edi + 0x80], al
004ea1fc lea esi, [edi + 0x3c]
004ea1ff jne 0x4ea224
004ea201 jmp 0x4ea206
004ea203 lea esi, [edi + 0x3c]
004ea206 push 1
004ea208 push 0xb404ec
004ea20d mov ecx, esi
004ea20f call 0x405740
004ea214 test al, al
004ea216 je 0x4ea224
004ea218 lea ecx, [esi + 0x30]
004ea21b call 0x405330
004ea220 mov byte ptr [esi + 0x44], 1
004ea224 cmp dword ptr [edi + 0x2c], 1
004ea228 lea ecx, [edi + 0x1dc]
004ea22e jne 0x4ea261
004ea230 cmp ecx, 0xbc514c
004ea236 je 0x4ea2b4
004ea238 movups xmm0, xmmword ptr [0xbc514c]
004ea23f movups xmmword ptr [ecx], xmm0
004ea242 movups xmm0, xmmword ptr [0xbc515c]
004ea249 movups xmmword ptr [ecx + 0x10], xmm0
004ea24d movq xmm0, qword ptr [0xbc516c]
004ea255 movq qword ptr [ecx + 0x20], xmm0
004ea25a mov eax, dword ptr [0xbc5174]
004ea25f jmp 0x4ea2b1
004ea261 movaps xmm0, xmmword ptr [0xb6c610]
004ea268 lea eax, [ebp - 0x150]
004ea26e movaps xmm1, xmmword ptr [0xb6b8e0]
004ea275 mov dword ptr [ebp - 0x130], 0
004ea27f mov dword ptr [ebp - 0x12c], 0
004ea289 mov dword ptr [ebp - 0x128], 0
004ea293 cmp ecx, eax
004ea295 je 0x4ea2b4
004ea297 mov eax, dword ptr [ebp - 0x128]
004ea29d movups xmmword ptr [ecx], xmm0
004ea2a0 movq xmm0, qword ptr [ebp - 0x130]
004ea2a8 movups xmmword ptr [ecx + 0x10], xmm1
004ea2ac movq qword ptr [ecx + 0x20], xmm0
004ea2b1 mov dword ptr [ecx + 0x28], eax
004ea2b4 cmp dword ptr [edi + 0xe6c], -1
004ea2bb je 0x4ea2c4
004ea2bd mov edx, 0xa
004ea2c2 jmp 0x4ea2d4
004ea2c4 call 0x6c3d90
004ea2c9 xor edx, edx
004ea2cb mov ecx, 0xa
004ea2d0 div ecx
004ea2d2 add edx, ecx
004ea2d4 mov dword ptr [edi + 0x360], edx
004ea2da movss xmm1, dword ptr [edi + 0x14]
004ea2df xorps xmm2, xmm2
004ea2e2 comiss xmm1, xmm2
004ea2e5 movss xmm0, dword ptr [edi + 0xb00]
004ea2ed jbe 0x4ea2fd
004ea2ef addss xmm1, xmm0
004ea2f3 movss dword ptr [edi + 0xb00], xmm1
004ea2fb jmp 0x4ea300
004ea2fd movaps xmm1, xmm0
004ea300 comiss xmm1, xmm2
004ea303 jbe 0x4ea325
004ea305 movss xmm0, dword ptr [edi + 0x2f4]
004ea30d mulss xmm0, dword ptr [0xb6a2dc]
004ea315 subss xmm1, xmm0
004ea319 maxss xmm1, xmm2
004ea31d movss dword ptr [edi + 0xb00], xmm1
004ea325 mov ecx, dword ptr [ebp - 0xc]
004ea328 mov dword ptr fs:[0], ecx
004ea32f pop ecx
004ea330 pop edi
004ea331 pop esi
004ea332 mov ecx, dword ptr [ebp - 0x14]
004ea335 xor ecx, ebp
004ea337 call 0x9eacd7
004ea33c mov esp, ebp
004ea33e pop ebp
004ea33f mov esp, ebx
004ea341 pop ebx
004ea342 ret 
