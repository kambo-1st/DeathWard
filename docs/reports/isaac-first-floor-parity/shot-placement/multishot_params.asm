0074a910 push ebp
0074a911 mov ebp, esp
0074a913 and esp, 0xfffffff8
0074a916 sub esp, 0x14
0074a919 mov eax, dword ptr [ebp + 8]
0074a91c push ebx
0074a91d push esi
0074a91e mov esi, ecx
0074a920 xor ecx, ecx
0074a922 push edi
0074a923 push ecx
0074a924 mov word ptr [eax + 0x20], cx
0074a928 mov dword ptr [eax + 4], ecx
0074a92b mov dword ptr [eax + 8], ecx
0074a92e mov dword ptr [eax + 0xc], ecx
0074a931 mov dword ptr [eax + 0x18], ecx
0074a934 mov ecx, esi
0074a936 push 0x44
0074a938 mov dword ptr [esp + 0x1c], esi
0074a93c mov dword ptr [eax + 0x10], 0
0074a943 mov word ptr [eax + 0x1c], 0
0074a949 mov byte ptr [eax + 0x1e], 0
0074a94d mov dword ptr [eax], 1
0074a953 mov dword ptr [eax + 0x14], 1
0074a95a call 0x73b3b0
0074a95f push 0
0074a961 dec eax
0074a962 mov ecx, esi
0074a964 push 0x72
0074a966 mov dword ptr [esp + 0x24], eax
0074a96a call 0x73b3b0
0074a96f push 0
0074a971 dec eax
0074a972 mov ecx, esi
0074a974 push 0x34
0074a976 mov dword ptr [esp + 0x20], eax
0074a97a call 0x73b3b0
0074a97f push 0
0074a981 push 0xa8
0074a986 mov ecx, esi
0074a988 lea ebx, [eax - 1]
0074a98b call 0x73b3b0
0074a990 push 0
0074a992 push 0x149
0074a997 mov ecx, esi
0074a999 lea edi, [eax - 1]
0074a99c call 0x73b3b0
0074a9a1 mov ecx, dword ptr [esp + 0x14]
0074a9a5 push 0
0074a9a7 push 0x18b
0074a9ac lea esi, [eax - 1]
0074a9af call 0x73b3b0
0074a9b4 lea ecx, [eax - 1]
0074a9b7 xor eax, eax
0074a9b9 test ecx, ecx
0074a9bb cmovs ecx, eax
0074a9be test esi, esi
0074a9c0 cmovs esi, eax
0074a9c3 add ecx, esi
0074a9c5 test edi, edi
0074a9c7 cmovs edi, eax
0074a9ca add ecx, edi
0074a9cc test ebx, ebx
0074a9ce cmovs ebx, eax
0074a9d1 mov eax, dword ptr [esp + 0x18]
0074a9d5 add ecx, ebx
0074a9d7 xor edx, edx
0074a9d9 mov ebx, dword ptr [ebp + 8]
0074a9dc test eax, eax
0074a9de cmovs eax, edx
0074a9e1 add ecx, eax
0074a9e3 mov eax, dword ptr [esp + 0x1c]
0074a9e7 test eax, eax
0074a9e9 cmovs eax, edx
0074a9ec add ecx, eax
0074a9ee je 0x74aa21
0074a9f0 add word ptr [ebx], cx
0074a9f3 movd xmm1, ecx
0074a9f7 cvtdq2ps xmm1, xmm1
0074a9fa movaps xmm0, xmm1
0074a9fd mulss xmm1, dword ptr [0xb6a810]
0074aa05 mulss xmm0, dword ptr [0xb6a7f4]
0074aa0d addss xmm1, dword ptr [ebx + 8]
0074aa12 addss xmm0, dword ptr [ebx + 4]
0074aa17 movss dword ptr [ebx + 8], xmm1
0074aa1c movss dword ptr [ebx + 4], xmm0
0074aa21 mov edi, dword ptr [esp + 0x14]
0074aa25 mov ecx, edi
0074aa27 push 0
0074aa29 push 0xe5
0074aa2e call 0x73b3b0
0074aa33 movss xmm2, dword ptr [0xb6a818]
0074aa3b lea ecx, [eax - 1]
0074aa3e xor eax, eax
0074aa40 test ecx, ecx
0074aa42 cmovs ecx, eax
0074aa45 test ecx, ecx
0074aa47 je 0x74aa79
0074aa49 movd xmm1, ecx
0074aa4d lea eax, [ecx + ecx*4]
0074aa50 add word ptr [ebx], ax
0074aa53 cvtdq2ps xmm1, xmm1
0074aa56 movaps xmm0, xmm1
0074aa59 mulss xmm1, dword ptr [0xb6a840]
0074aa61 mulss xmm0, xmm2
0074aa65 addss xmm1, dword ptr [ebx + 8]
0074aa6a addss xmm0, dword ptr [ebx + 4]
0074aa6f movss dword ptr [ebx + 8], xmm1
0074aa74 movss dword ptr [ebx + 4], xmm0
0074aa79 push 0
0074aa7b push 0x99
0074aa80 mov ecx, edi
0074aa82 call 0x73b3b0
0074aa87 mov ecx, eax
0074aa89 xor eax, eax
0074aa8b cmp dword ptr [edi + 0x130c], 0x21
0074aa92 sete al
0074aa95 add ecx, eax
0074aa97 cmp byte ptr [edi + 0x1461], 0
0074aa9e mov dword ptr [esp + 0x18], ecx
0074aaa2 jne 0x74aacc
0074aaa4 mov eax, dword ptr [edi + 0x1454]
0074aaaa mov ecx, dword ptr [edi + 0x1458]
0074aab0 cmp eax, ecx
0074aab2 je 0x74aacc
0074aab4 mov edx, dword ptr [eax]
0074aab6 cmp dword ptr [edx], 0
0074aab9 jne 0x74aac5
0074aabb cmp dword ptr [edx + 4], 0x41
0074aabf je 0x74abcf
0074aac5 add eax, 0xc
0074aac8 cmp eax, ecx
0074aaca jne 0x74aab4
0074aacc mov dword ptr [esp + 0x14], 0
0074aad4 push 2
0074aad6 lea ecx, [edi + 0x1450]
0074aadc call 0x88b570
0074aae1 push 0
0074aae3 push 2
0074aae5 mov ecx, edi
0074aae7 movzx esi, al
0074aaea call 0x73b3b0
0074aaef xor ecx, ecx
0074aaf1 add eax, esi
0074aaf3 cmp dword ptr [edi + 0x130c], 0xe
0074aafa push 0xf5
0074aaff sete cl
0074ab02 add ecx, dword ptr [esp + 0x18]
0074ab06 add ecx, eax
0074ab08 mov dword ptr [esp + 0x18], ecx
0074ab0c lea ecx, [edi + 0x1450]
0074ab12 call 0x88b570
0074ab17 push 0
0074ab19 push 0xf5
0074ab1e mov ecx, edi
0074ab20 movzx esi, al
0074ab23 call 0x73b3b0
0074ab28 mov edx, dword ptr [esp + 0x14]
0074ab2c add esi, eax
0074ab2e xor eax, eax
0074ab30 cmp dword ptr [edi + 0x1a0c], 0x41
0074ab37 sete al
0074ab3a add esi, eax
0074ab3c mov eax, dword ptr [esp + 0x18]
0074ab40 test eax, eax
0074ab42 jne 0x74ab48
0074ab44 test edx, edx
0074ab46 je 0x74ab86
0074ab48 lea eax, [eax*2 + 1]
0074ab4f add eax, edx
0074ab51 add word ptr [ebx], ax
0074ab54 movd xmm1, eax
0074ab58 mov eax, dword ptr [esp + 0x18]
0074ab5c cvtdq2ps xmm1, xmm1
0074ab5f movaps xmm0, xmm1
0074ab62 mulss xmm1, dword ptr [0xb6a80c]
0074ab6a mulss xmm0, dword ptr [0xb6a7f8]
0074ab72 addss xmm1, dword ptr [ebx + 8]
0074ab77 addss xmm0, dword ptr [ebx + 4]
0074ab7c movss dword ptr [ebx + 8], xmm1
0074ab81 movss dword ptr [ebx + 4], xmm0
0074ab86 movzx ecx, word ptr [ebx]
0074ab89 test esi, esi
0074ab8b je 0x74aba0
0074ab8d add ecx, esi
0074ab8f mov word ptr [ebx], cx
0074ab92 test eax, eax
0074ab94 jne 0x74ab9a
0074ab96 test edx, edx
0074ab98 je 0x74aba0
0074ab9a lea eax, [ecx - 1]
0074ab9d mov word ptr [ebx], ax
0074aba0 cmp dword ptr [ebp + 0xc], 8
0074aba4 je 0x74abdc
0074aba6 cmp byte ptr [edi + 0x1f1c], 0
0074abad jne 0x74abdc
0074abaf cmp byte ptr [edi + 0x1f88], 0
0074abb6 jne 0x74abdc
0074abb8 cmp dword ptr [edi + 0x1728], 3
0074abbf jl 0x74abdc
0074abc1 call 0x6c3d90
0074abc6 test al, 3
0074abc8 jne 0x74abdc
0074abca inc word ptr [ebx]
0074abcd jmp 0x74abe0
0074abcf mov dword ptr [esp + 0x14], 1
0074abd7 jmp 0x74aad4
0074abdc test esi, esi
0074abde je 0x74ac07
0074abe0 movss xmm0, dword ptr [ebx + 4]
0074abe5 mulss xmm0, dword ptr [0xb6a434]
0074abed movss dword ptr [ebx + 4], xmm0
0074abf2 movd xmm0, esi
0074abf6 cvtdq2ps xmm0, xmm0
0074abf9 addss xmm0, xmm0
0074abfd addss xmm0, dword ptr [ebx + 8]
0074ac02 movss dword ptr [ebx + 8], xmm0
0074ac07 push 0x166
0074ac0c lea ecx, [edi + 0x1450]
0074ac12 call 0x88b570
0074ac17 push 0
0074ac19 push 0x166
0074ac1e mov ecx, edi
0074ac20 movzx esi, al
0074ac23 call 0x73b3b0
0074ac28 add esi, eax
0074ac2a je 0x74aca6
0074ac2c add dword ptr [ebx + 0x14], esi
0074ac2f mov ecx, dword ptr [ebx + 0x14]
0074ac32 movd xmm1, esi
0074ac36 cvtdq2ps xmm1, xmm1
0074ac39 movaps xmm0, xmm1
0074ac3c mulss xmm0, dword ptr [0xb6a864]
0074ac44 addss xmm0, dword ptr [ebx + 8]
0074ac49 movss dword ptr [ebx + 8], xmm0
0074ac4e cmp ecx, 8
0074ac51 jle 0x74ac5f
0074ac53 mov dword ptr [ebx + 0x14], 8
0074ac5a mov ecx, 8
0074ac5f mov ax, word ptr [ebx]
0074ac62 add ax, si
0074ac65 mov dword ptr [esp + 0x1c], eax
0074ac69 cwde 
0074ac6a cdq 
0074ac6b idiv ecx
0074ac6d mov eax, dword ptr [esp + 0x1c]
0074ac71 mov dword ptr [esp + 0x18], edx
0074ac75 cmp dword ptr [esp + 0x18], 0
0074ac7a movzx edx, ax
0074ac7d je 0x74ac88
0074ac7f sub ecx, dword ptr [esp + 0x18]
0074ac83 add ecx, eax
0074ac85 movzx edx, cx
0074ac88 mulss xmm1, dword ptr [0xb6aa4c]
0074ac90 movzx eax, dx
0074ac93 movss xmm0, dword ptr [0xb6aa78]
0074ac9b minss xmm0, xmm1
0074ac9f movss dword ptr [ebx + 0x18], xmm0
0074aca4 jmp 0x74aca9
0074aca6 movzx eax, word ptr [ebx]
0074aca9 cmp byte ptr [edi + 0x1f1c], 0
0074acb0 movzx eax, ax
0074acb3 jne 0x74acd4
0074acb5 cmp byte ptr [edi + 0x1f88], 0
0074acbc jne 0x74acd4
0074acbe cmp dword ptr [edi + 0x171c], 3
0074acc5 jl 0x74acd4
0074acc7 test esi, esi
0074acc9 sete cl
0074accc add eax, 2
0074accf movzx eax, ax
0074acd2 jmp 0x74acd6
0074acd4 xor cl, cl
0074acd6 mov byte ptr [ebx + 0x1c], cl
0074acd9 mov edx, 0x10
0074acde mov esi, dword ptr [ebx + 0x14]
0074ace1 movzx eax, ax
0074ace4 cmp ax, dx
0074ace7 movss xmm3, dword ptr [ebx + 8]
0074acec mov ecx, eax
0074acee movss xmm1, dword ptr [ebx + 4]
0074acf3 cmovg ecx, edx
0074acf6 movaps xmm0, xmm3
0074acf9 movsx eax, cx
0074acfc movaps xmm2, xmm1
0074acff cdq 
0074ad00 idiv esi
0074ad02 mulss xmm0, dword ptr [0xb6a7e0]
0074ad0a movzx eax, ax
0074ad0d mulss xmm2, dword ptr [0xb6a818]
0074ad15 mov word ptr [ebx + 2], ax
0074ad19 imul esi, eax
0074ad1c movss dword ptr [ebx + 0x10], xmm0
0074ad21 movss xmm0, dword ptr [0xb6aae4]
0074ad29 comiss xmm1, xmm0
0074ad2c mov word ptr [ebx], si
0074ad2f movss dword ptr [ebx + 0xc], xmm2
0074ad34 jbe 0x74ad3d
0074ad36 mov dword ptr [ebx + 4], 0x42b40000
0074ad3d comiss xmm3, xmm0
0074ad40 jbe 0x74ad49
0074ad42 mov dword ptr [ebx + 8], 0x42b40000
0074ad49 comiss xmm2, xmm0
0074ad4c jbe 0x74ad55
0074ad4e mov dword ptr [ebx + 0xc], 0x42b40000
0074ad55 push 0
0074ad57 push 0x37
0074ad59 mov ecx, edi
0074ad5b call 0x73af30
0074ad60 push 0
0074ad62 push 0x57
0074ad64 mov ecx, edi
0074ad66 mov byte ptr [esp + 0x1a], al
0074ad6a call 0x73af30
0074ad6f push 0
0074ad71 push 0xe5
0074ad76 mov ecx, edi
0074ad78 mov byte ptr [esp + 0x19], al
0074ad7c call 0x73af30
0074ad81 mov esi, dword ptr [ebp + 0xc]
0074ad84 mov byte ptr [esp + 0x13], al
0074ad88 cmp esi, 8
0074ad8b jne 0x74adb0
0074ad8d cmp byte ptr [esp + 0x12], 0
0074ad92 mov al, byte ptr [esp + 0x11]
0074ad96 jne 0x74ada6
0074ad98 test al, al
0074ad9a jne 0x74ada6
0074ad9c xor cl, cl
0074ad9e mov byte ptr [ebx + 0x1d], cl
0074ada1 jmp 0x74ae4a
0074ada6 mov cl, 1
0074ada8 mov byte ptr [ebx + 0x1d], cl
0074adab jmp 0x74ae4a
0074adb0 cmp byte ptr [esp + 0x12], 0
0074adb5 movss xmm2, dword ptr [0xb6a19c]
0074adbd je 0x74adfd
0074adbf call 0x6c3d90
0074adc4 movd xmm0, eax
0074adc8 cvtdq2pd xmm0, xmm0
0074adcc shr eax, 0x1f
0074adcf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0074add8 cvtpd2ps xmm1, xmm0
0074addc movss xmm0, dword ptr [edi + 0x14b0]
0074ade4 mulss xmm0, dword ptr [0xb6a2cc]
0074adec mulss xmm1, xmm2
0074adf0 addss xmm0, dword ptr [0xb6a480]
0074adf8 comiss xmm0, xmm1
0074adfb ja 0x74ae42
0074adfd cmp byte ptr [esp + 0x11], 0
0074ae02 je 0x74ae4d
0074ae04 call 0x6c3d90
0074ae09 movd xmm0, eax
0074ae0d cvtdq2pd xmm0, xmm0
0074ae11 shr eax, 0x1f
0074ae14 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0074ae1d cvtpd2ps xmm1, xmm0
0074ae21 movss xmm0, dword ptr [edi + 0x14b0]
0074ae29 mulss xmm0, dword ptr [0xb6a274]
0074ae31 mulss xmm1, xmm2
0074ae35 addss xmm0, dword ptr [0xb6a38c]
0074ae3d comiss xmm0, xmm1
0074ae40 jbe 0x74ae4d
0074ae42 mov al, byte ptr [esp + 0x11]
0074ae46 mov byte ptr [ebx + 0x1d], 1
0074ae4a mov byte ptr [ebx + 0x1e], al
0074ae4d push 0
0074ae4f push 0x22e
0074ae54 mov ecx, edi
0074ae56 call 0x73af30
0074ae5b test al, al
0074ae5d je 0x74ae8f
0074ae5f call 0x6c3d90
0074ae64 mov esi, eax
0074ae66 and esi, 3
0074ae69 call 0x6c3d90
0074ae6e and eax, 3
0074ae71 lea edx, [esi - 3]
0074ae74 add edx, eax
0074ae76 xor esi, esi
0074ae78 test edx, edx
0074ae7a movzx ecx, dx
0074ae7d mov eax, ebx
0074ae7f cmovg esi, ecx
0074ae82 mov word ptr [ebx + 0x20], si
0074ae86 pop edi
0074ae87 pop esi
0074ae88 pop ebx
0074ae89 mov esp, ebp
0074ae8b pop ebp
0074ae8c ret 8
0074ae8f cmp byte ptr [esp + 0x13], 0
0074ae94 je 0x74aed9
0074ae96 cmp esi, 6
0074ae99 jne 0x74aebb
0074ae9b call 0x6c3d90
0074aea0 xor edx, edx
0074aea2 mov ecx, 3
0074aea7 div ecx
0074aea9 mov eax, ebx
0074aeab add edx, 2
0074aeae mov word ptr [ebx + 0x20], dx
0074aeb2 pop edi
0074aeb3 pop esi
0074aeb4 pop ebx
0074aeb5 mov esp, ebp
0074aeb7 pop ebp
0074aeb8 ret 8
0074aebb cmp esi, 2
0074aebe je 0x74aec5
0074aec0 cmp esi, 9
0074aec3 jne 0x74aed9
0074aec5 call 0x6c3d90
0074aeca xor edx, edx
0074aecc mov ecx, 3
0074aed1 div ecx
0074aed3 add edx, ecx
0074aed5 mov word ptr [ebx + 0x20], dx
0074aed9 pop edi
0074aeda pop esi
0074aedb mov eax, ebx
0074aedd pop ebx
0074aede mov esp, ebp
0074aee0 pop ebp
0074aee1 ret 8
0074aee4 int3 
0074aee5 int3 
0074aee6 int3 
0074aee7 int3 
0074aee8 int3 
0074aee9 int3 
0074aeea int3 
0074aeeb int3 
0074aeec int3 
0074aeed int3 
0074aeee int3 
0074aeef int3 
