0069b644 movss xmm0, dword ptr [edi + 0x2b8]
0069b64c mov ecx, edi
0069b64e mulss xmm0, xmm1
0069b652 movss dword ptr [edi + 0x2b8], xmm0
0069b65a movss xmm0, dword ptr [edi + 0x2bc]
0069b662 mulss xmm0, xmm1
0069b666 movss dword ptr [edi + 0x2bc], xmm0
0069b66e mov al, byte ptr [edi + 0x16b]
0069b674 mov byte ptr [ebp - 0x269], al
0069b67a call 0x6adb50
0069b67f mov ecx, edi
0069b681 call 0x6adfd0
0069b686 test byte ptr [edi + 0xe68], 1
0069b68d je 0x69b6aa
0069b68f mov ecx, edi
0069b691 mov dword ptr [edi + 0xac4], 1
0069b69b call 0x699730
0069b6a0 mov dword ptr [edi + 0xac4], 0
0069b6aa mov edx, dword ptr [edi + 0x164]
0069b6b0 xor eax, eax
0069b6b2 movss xmm0, dword ptr [edi + 0x2d8]
0069b6ba mov ecx, edx
0069b6bc and ecx, 1
0069b6bf movss dword ptr [ebp - 0x270], xmm0
0069b6c7 or eax, ecx
0069b6c9 mov ecx, edi
0069b6cb je 0x69b6d4
0069b6cd call 0x6860a0
0069b6d2 jmp 0x69b6f7
0069b6d4 xor dword ptr [edi + 0x160], 0
0069b6db xor edx, 1
0069b6de mov dword ptr [edi + 0x164], edx
0069b6e4 call 0x6860a0
0069b6e9 xor dword ptr [edi + 0x160], 0
0069b6f0 xor dword ptr [edi + 0x164], 1
0069b6f7 movss xmm0, dword ptr [ebp - 0x270]
0069b6ff lea edx, [ebp - 0x270]
0069b705 subss xmm0, dword ptr [edi + 0x2d8]
0069b70d lea ecx, [ebp - 0x288]
0069b713 mov dword ptr [ebp - 0x288], 0
0069b71d movss dword ptr [ebp - 0x270], xmm0
0069b725 call 0x417c70
0069b72a movss xmm0, dword ptr [edi + 0xbac]
0069b732 addss xmm0, dword ptr [eax]
0069b736 mov al, byte ptr [edi + 0x16b]
0069b73c mov byte ptr [ebp - 0x299], al
0069b742 movss dword ptr [edi + 0xbac], xmm0
0069b74a cmp byte ptr [ebp - 0x269], al
0069b750 je 0x6a088c
0069b756 push 0
0069b758 push 4
0069b75a mov ecx, edi
0069b75c call 0x4122f0
0069b761 mov ecx, dword ptr [edi + 0xab4]
0069b767 mov edx, 1
0069b76c test al, al
0069b76e jne 0x69b789
0069b770 cmp ecx, edx
0069b772 jne 0x69be56
0069b778 mov eax, dword ptr [edi + 0xab8]
0069b77e mov dword ptr [edi + 0xab4], eax
0069b784 jmp 0x69cda8
0069b789 cmp ecx, 1
0069b78c jne 0x69be56
0069b792 mov eax, dword ptr [edi + 0xac0]
0069b798 test eax, eax
0069b79a jne 0x69b9eb
0069b7a0 cmp dword ptr [edi + 0xbb4], 6
0069b7a7 mov dword ptr [edi + 0xab4], eax
0069b7ad jne 0x69b7be
0069b7af push eax
0069b7b0 push ecx
0069b7b1 mov ecx, edi
0069b7b3 mov byte ptr [edi + 0x308], dl
0069b7b9 call 0x4122a0
0069b7be mov ecx, edi
0069b7c0 call 0x699730
0069b7c5 mov eax, dword ptr [edi + 0xbb4]
0069b7cb cmp eax, 0x11
0069b7ce je 0x69b7d5
0069b7d0 cmp eax, 0x19
0069b7d3 jne 0x69b801
0069b7d5 call 0x6c3d90
0069b7da mov ecx, dword ptr [0xbfd65c]
0069b7e0 push eax
0069b7e1 push 0
0069b7e3 push edi
0069b7e4 push 0xc02fec
0069b7e9 lea eax, [edi + 0x294]
0069b7ef push eax
0069b7f0 push 0
0069b7f2 push 0x60
0069b7f4 call 0x422e20
0069b7f9 push edi
0069b7fa mov ecx, eax
0069b7fc call 0x6818e0
0069b801 push 0
0069b803 push 4
0069b805 mov ecx, edi
0069b807 call 0x4122f0
0069b80c test al, al
0069b80e je 0x69b82d
0069b810 mov eax, dword ptr [edi + 0xab4]
0069b816 mov byte ptr [edi + 0x169], 0
