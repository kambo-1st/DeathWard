0068b970 push ebp
0068b971 mov ebp, esp
0068b973 and esp, 0xfffffff8
0068b976 sub esp, 0x80
0068b97c mov eax, dword ptr [0xbaa3b4]
0068b981 xor eax, esp
0068b983 mov dword ptr [esp + 0x7c], eax
0068b987 push esi
0068b988 push edi
0068b989 mov edi, ecx
0068b98b xor eax, eax
0068b98d mov ecx, dword ptr [edi + 0x164]
0068b993 and ecx, 0x40000
0068b999 or eax, ecx
0068b99b je 0x68baef
0068b9a1 mov eax, dword ptr [edi]
0068b9a3 mov ecx, edi
0068b9a5 mov eax, dword ptr [eax + 0x48]
0068b9a8 call eax
0068b9aa test al, al
0068b9ac jne 0x68baef
0068b9b2 mov eax, dword ptr [edi + 0x288]
0068b9b8 cmp byte ptr [eax + 0x2c], 0
0068b9bc jne 0x68baef
0068b9c2 call 0x6c3d90
0068b9c7 mov esi, dword ptr [0xbfd680]
0068b9cd lea ecx, [esp + 8]
0068b9d1 mov dword ptr [esp + 8], 0x1f0
0068b9d9 movd xmm0, eax
0068b9dd cvtdq2pd xmm0, xmm0
0068b9e1 shr eax, 0x1f
0068b9e4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068b9ed cvtpd2ps xmm0, xmm0
0068b9f1 mulss xmm0, dword ptr [0xb6a19c]
0068b9f9 mulss xmm0, dword ptr [0xb6a350]
0068ba01 addss xmm0, dword ptr [0xb6a5a4]
0068ba09 movss dword ptr [esp + 0xc], xmm0
0068ba0f call 0x8b1340
0068ba14 movss xmm0, dword ptr [esp + 0xc]
0068ba1a sub esp, 8
0068ba1d mov dword ptr [esp + 4], 0
0068ba25 movss dword ptr [esp], xmm0
0068ba2a push 0
0068ba2c push 2
0068ba2e push ecx
0068ba2f mov dword ptr [esp], 0x3f800000
0068ba36 lea ecx, [esi + 0x29de0]
0068ba3c push dword ptr [esp + 0x1c]
0068ba40 call 0x888de0
0068ba45 movaps xmm0, xmmword ptr [0xb6c490]
0068ba4c movups xmmword ptr [esp + 0x58], xmm0
0068ba51 mov dword ptr [esp + 0x78], 0x3e99999a
0068ba59 movaps xmm0, xmmword ptr [0xb6ba70]
0068ba60 movups xmmword ptr [esp + 0x68], xmm0
0068ba65 mov dword ptr [esp + 0x7c], 0x3f000000
0068ba6d mov dword ptr [esp + 0x80], 0x3f4ccccd
0068ba78 call 0x6c3d90
0068ba7d movd xmm0, eax
0068ba81 cvtdq2pd xmm0, xmm0
0068ba85 shr eax, 0x1f
0068ba88 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068ba91 cvtpd2ps xmm0, xmm0
0068ba95 mulss xmm0, dword ptr [0xb6a19c]
0068ba9d call 0x6c3d90
0068baa2 push 0
0068baa4 push ecx
0068baa5 addss xmm0, xmm0
0068baa9 mov dword ptr [esp], 0x47c35000
0068bab0 lea ecx, [esp + 0x60]
0068bab4 and eax, 3
0068bab7 push ecx
0068bab8 push ecx
0068bab9 add eax, 3
0068babc addss xmm0, dword ptr [0xb6a864]
0068bac4 movss dword ptr [esp], xmm0
0068bac9 push eax
0068baca push 0x23
0068bacc mov ecx, dword ptr [0xbfd65c]
0068bad2 lea eax, [edi + 0x294]
0068bad8 push eax
0068bad9 call 0x6d57a0
0068bade pop edi
0068badf pop esi
0068bae0 mov ecx, dword ptr [esp + 0x7c]
0068bae4 xor ecx, esp
0068bae6 call 0x9eacd7
0068baeb mov esp, ebp
0068baed pop ebp
0068baee ret 
0068baef mov ecx, dword ptr [edi + 0x164]
0068baf5 xor eax, eax
0068baf7 and ecx, 0x20000
0068bafd or eax, ecx
0068baff je 0x68bc37
0068bb05 call 0x6c3d90
0068bb0a mov esi, dword ptr [0xbfd680]
0068bb10 lea ecx, [esp + 8]
0068bb14 mov dword ptr [esp + 8], 0x1f2
0068bb1c movd xmm0, eax
0068bb20 cvtdq2pd xmm0, xmm0
0068bb24 shr eax, 0x1f
0068bb27 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068bb30 cvtpd2ps xmm0, xmm0
0068bb34 mulss xmm0, dword ptr [0xb6a19c]
0068bb3c mulss xmm0, dword ptr [0xb6a350]
0068bb44 addss xmm0, dword ptr [0xb6a5a4]
0068bb4c movss dword ptr [esp + 0xc], xmm0
0068bb52 call 0x8b1340
0068bb57 movss xmm0, dword ptr [esp + 0xc]
0068bb5d sub esp, 8
0068bb60 mov dword ptr [esp + 4], 0
0068bb68 movss dword ptr [esp], xmm0
0068bb6d push 0
0068bb6f push 2
0068bb71 push ecx
0068bb72 mov dword ptr [esp], 0x3f800000
0068bb79 lea ecx, [esi + 0x29de0]
0068bb7f push dword ptr [esp + 0x1c]
0068bb83 call 0x888de0
0068bb88 mov esi, dword ptr [0xbfd680]
0068bb8e lea ecx, [esp + 8]
0068bb92 mov dword ptr [esp + 8], 0x89
0068bb9a call 0x8b1340
0068bb9f sub esp, 8
0068bba2 mov dword ptr [esp + 4], 0
0068bbaa mov dword ptr [esp], 0x3f800000
0068bbb1 push 0
0068bbb3 push 2
0068bbb5 push ecx
0068bbb6 mov dword ptr [esp], 0x3f800000
0068bbbd lea ecx, [esi + 0x29de0]
0068bbc3 push dword ptr [esp + 0x1c]
0068bbc7 call 0x888de0
0068bbcc movaps xmm0, xmmword ptr [0xb6c490]
0068bbd3 movups xmmword ptr [esp + 0x58], xmm0
0068bbd8 mov dword ptr [esp + 0x78], 0x3e99999a
0068bbe0 movaps xmm0, xmmword ptr [0xb6ba70]
0068bbe7 movups xmmword ptr [esp + 0x68], xmm0
0068bbec mov dword ptr [esp + 0x7c], 0x3f000000
0068bbf4 mov dword ptr [esp + 0x80], 0x3f4ccccd
0068bbff call 0x6c3d90
0068bc04 mov ecx, 3
0068bc09 xor edx, edx
0068bc0b div ecx
0068bc0d push 0
0068bc0f push ecx
0068bc10 mov dword ptr [esp], 0x47c35000
0068bc17 lea eax, [esp + 0x60]
0068bc1b push eax
0068bc1c mov eax, dword ptr [edi + 0x288]
0068bc22 push ecx
0068bc23 mov dword ptr [esp], 0x40a00000
0068bc2a mov eax, dword ptr [eax + 0x5c]
0068bc2d add eax, edx
0068bc2f push eax
0068bc30 push 4
0068bc32 jmp 0x68bacc
0068bc37 mov ecx, dword ptr [edi + 0x28]
0068bc3a cmp ecx, 0x33e
0068bc40 jne 0x68bc55
0068bc42 cmp dword ptr [edi + 0x2c], 0xa
0068bc46 jne 0x68bc55
0068bc48 mov dword ptr [esp + 8], 0x1f4
0068bc50 jmp 0x68bdf1
0068bc55 mov esi, dword ptr [edi + 0x288]
0068bc5b mov edx, dword ptr [esi + 0x60]
0068bc5e mov eax, edx
0068bc60 shr eax, 0xb
0068bc63 test al, 1
0068bc65 je 0x68bc74
0068bc67 mov dword ptr [esp + 8], 0x1f8
0068bc6f jmp 0x68bdf1
0068bc74 cmp dword ptr [edi + 0x210], 0
0068bc7b jg 0x68bde9
0068bc81 test edx, 0x180
0068bc87 jne 0x68bde9
0068bc8d cmp ecx, 0xa
0068bc90 jl 0x68bcb0
0068bc92 cmp ecx, 0x3e8
0068bc98 jge 0x68bcb0
0068bc9a cmp dword ptr [edi + 0xbb4], 0xc
0068bca1 jne 0x68bcb0
0068bca3 mov dword ptr [esp + 8], 0x1e
0068bcab jmp 0x68bdf1
0068bcb0 mov eax, edx
0068bcb2 shr eax, 9
0068bcb5 test al, 1
0068bcb7 je 0x68bcf3
0068bcb9 mov esi, dword ptr [0xbfd680]
0068bcbf lea ecx, [esp + 8]
0068bcc3 mov dword ptr [esp + 8], 0xcf
0068bccb call 0x8b1340
0068bcd0 sub esp, 8
0068bcd3 mov dword ptr [esp + 4], 0
0068bcdb mov dword ptr [esp], 0x3f800000
0068bce2 push 0
0068bce4 push 2
0068bce6 push ecx
0068bce7 mov dword ptr [esp], 0x3fe66666
0068bcee jmp 0x68be1e
0068bcf3 mov eax, edx
0068bcf5 shr eax, 0xa
0068bcf8 test al, 1
0068bcfa je 0x68bd09
0068bcfc mov dword ptr [esp + 8], 0x1b
0068bd04 jmp 0x68bdf1
0068bd09 mov eax, edx
0068bd0b shr eax, 0xd
0068bd0e test al, 1
0068bd10 je 0x68bd1f
0068bd12 mov dword ptr [esp + 8], 0x8d
0068bd1a jmp 0x68bdf1
0068bd1f mov eax, edx
0068bd21 shr eax, 4
0068bd24 test al, 1
0068bd26 je 0x68bd67
0068bd28 cmp byte ptr [edi + 0x16b], 0
0068bd2f je 0x68bd85
0068bd31 cmp byte ptr [esi + 0x2c], 0
0068bd35 je 0x68bd85
0068bd37 cmp ecx, 0x2e
0068bd3a je 0x68bd85
0068bd3c cmp ecx, 0x2f
0068bd3f je 0x68bd85
0068bd41 cmp ecx, 0x30
0068bd44 je 0x68bd85
0068bd46 cmp ecx, 0x31
0068bd49 je 0x68bd85
0068bd4b cmp ecx, 0x32
0068bd4e je 0x68bd85
0068bd50 cmp ecx, 0x33
0068bd53 je 0x68bd85
0068bd55 cmp ecx, 0x34
0068bd58 je 0x68bd85
0068bd5a mov dword ptr [esp + 8], 0x8d
0068bd62 jmp 0x68bdf1
0068bd67 push 0x800000
0068bd6c push 0
0068bd6e mov ecx, edi
0068bd70 call 0x4122f0
0068bd75 test al, al
0068bd77 je 0x68bdbc
0068bd79 cmp dword ptr [esi + 0x5c], 0
0068bd7d jle 0x68bdcc
0068bd7f test byte ptr [esi + 0x60], 1
0068bd83 je 0x68bdbc
0068bd85 mov esi, dword ptr [0xbfd680]
0068bd8b lea ecx, [esp + 8]
0068bd8f mov dword ptr [esp + 8], 0x1c
0068bd97 call 0x8b1340
0068bd9c sub esp, 8
0068bd9f mov dword ptr [esp + 4], 0
0068bda7 mov dword ptr [esp], 0x3f800000
0068bdae push 0
0068bdb0 push 2
0068bdb2 push ecx
0068bdb3 mov dword ptr [esp], 0x3fa00000
0068bdba jmp 0x68be1e
0068bdbc cmp dword ptr [esi + 0x5c], 0
0068bdc0 jle 0x68bdcc
0068bdc2 movss xmm2, dword ptr [0xb6a614]
0068bdca jmp 0x68bdd4
0068bdcc movss xmm2, dword ptr [0xb6a560]
0068bdd4 push ecx
0068bdd5 mov dword ptr [esp], 0x3f800000
0068bddc push 0
0068bdde push 2
0068bde0 push 0x1e
0068bde2 call 0x68d750
0068bde7 jmp 0x68be2d
0068bde9 mov dword ptr [esp + 8], 0x89
0068bdf1 mov esi, dword ptr [0xbfd680]
0068bdf7 lea ecx, [esp + 8]
0068bdfb call 0x8b1340
0068be00 sub esp, 8
0068be03 mov dword ptr [esp + 4], 0
0068be0b mov dword ptr [esp], 0x3f800000
0068be12 push 0
0068be14 push 2
0068be16 push ecx
0068be17 mov dword ptr [esp], 0x3f800000
0068be1e push dword ptr [esp + 0x1c]
0068be22 lea ecx, [esi + 0x29de0]
0068be28 call 0x888de0
0068be2d cmp dword ptr [edi + 0x28], 0x3d
0068be31 jne 0x68bf44
0068be37 cmp dword ptr [edi + 0x2c], 5
0068be3b jne 0x68bf44
0068be41 mov esi, dword ptr [0xbfd680]
0068be47 lea ecx, [esp + 8]
0068be4b mov dword ptr [esp + 8], 0x1ec
0068be53 call 0x8b1340
0068be58 sub esp, 8
0068be5b mov dword ptr [esp + 4], 0
0068be63 mov dword ptr [esp], 0x3f800000
0068be6a push 0
0068be6c push 2
0068be6e push ecx
0068be6f mov dword ptr [esp], 0x3f800000
0068be76 lea ecx, [esi + 0x29de0]
0068be7c push dword ptr [esp + 0x1c]
0068be80 call 0x888de0
0068be85 movaps xmm0, xmmword ptr [0xb6be40]
0068be8c lea ecx, [edi + 0x294]
0068be92 movss xmm2, dword ptr [0xb6a53c]
0068be9a lea edx, [esp + 0x48]
0068be9e push 0
0068bea0 push 3
0068bea2 push 3
0068bea4 movups xmmword ptr [esp + 0x54], xmm0
0068bea9 call 0x5ed3c0
0068beae mov esi, eax
0068beb0 add esp, 0xc
0068beb3 mov dword ptr [esi + 0x2a4], 0
0068bebd mov dword ptr [esi + 0x2a8], 0xc1200000
0068bec7 cmp dword ptr [esi + 0x70], 0
0068becb je 0x68bedd
0068becd movss xmm1, dword ptr [0xb6a614]
0068bed5 lea ecx, [esi + 0x6c]
0068bed8 call 0x403c00
0068bedd cmp byte ptr [0xbc7a4f], 0
0068bee4 mov eax, 6
0068bee9 mov ecx, 1
0068beee cmovne eax, ecx
0068bef1 cmp dword ptr [esi + 0xbc], 0
0068bef8 mov dword ptr [esp + 0xc], eax
0068befc jg 0x68bf1c
0068befe cmp dword ptr [esi + 0x50], 0x10
0068bf02 lea eax, [esi + 0x3c]
0068bf05 jb 0x68bf0a
0068bf07 mov eax, dword ptr [esi + 0x3c]
0068bf0a push 0
0068bf0c push eax
0068bf0d push 0xa0830c
0068bf12 push 3
0068bf14 call 0x95e330
0068bf19 add esp, 0x10
0068bf1c mov eax, dword ptr [esi + 0xb8]
0068bf22 mov ecx, dword ptr [esp + 0xc]
0068bf26 mov dword ptr [eax + 0x78], ecx
0068bf29 mov dword ptr [eax + 0x7c], 1
0068bf30 mov dword ptr [eax + 0x80], 1
0068bf3a mov dword ptr [eax + 0x84], 1
0068bf44 mov eax, dword ptr [edi + 0x288]
0068bf4a mov esi, dword ptr [eax + 0x5c]
0068bf4d mov dword ptr [esp + 8], esi
0068bf51 test esi, esi
0068bf53 jle 0x68bfec
0068bf59 mov eax, dword ptr [edi + 0x164]
0068bf5f xor ecx, ecx
0068bf61 mov edx, eax
0068bf63 and edx, 0x800
0068bf69 or ecx, edx
0068bf6b je 0x68bfe0
0068bf6d mov ecx, dword ptr [edi + 0x164]
0068bf73 mov eax, esi
0068bf75 cdq 
0068bf76 mov esi, 1
0068bf7b and edx, 3
0068bf7e mov dword ptr [esp + 0x2c], 0
0068bf86 add eax, edx
0068bf88 mov dword ptr [esp + 0x28], 0
0068bf90 sar eax, 2
0068bf93 cmp eax, esi
0068bf95 cmovg esi, eax
0068bf98 and ecx, 0x800000
0068bf9e xor eax, eax
0068bfa0 mov dword ptr [esp + 8], esi
0068bfa4 or eax, ecx
0068bfa6 jne 0x68c023
0068bfa8 mov ecx, dword ptr [edi + 0x288]
0068bfae movss xmm0, dword ptr [0xb6a614]
0068bfb6 mov ecx, dword ptr [ecx + 0x60]
0068bfb9 mov eax, ecx
0068bfbb shr eax, 0xd
0068bfbe test al, 1
0068bfc0 je 0x68c4de
0068bfc6 shr ecx, 0xd
0068bfc9 test cl, 1
0068bfcc je 0x68c02e
0068bfce movss xmm0, dword ptr [0xb6a8cc]
0068bfd6 movss dword ptr [esp + 0x14], xmm0
0068bfdc push 0x18
0068bfde jmp 0x68c043
0068bfe0 mov ecx, dword ptr [edi + 0x160]
0068bfe6 mov dword ptr [esp + 0x38], ecx
0068bfea jmp 0x68bffc
0068bfec mov eax, dword ptr [edi + 0x160]
0068bff2 mov dword ptr [esp + 0x38], eax
0068bff6 mov eax, dword ptr [edi + 0x164]
0068bffc and eax, 0x800000
0068c001 mov dword ptr [esp + 0x2c], 0
0068c009 mov dword ptr [esp + 0xc], eax
0068c00d xor eax, eax
0068c00f or eax, dword ptr [esp + 0xc]
0068c013 mov dword ptr [esp + 0x28], 0
0068c01b je 0x68bfa8
0068c01d add esi, esi
0068c01f mov dword ptr [esp + 8], esi
0068c023 mov ecx, dword ptr [edi + 0x288]
0068c029 mov ecx, dword ptr [ecx + 0x60]
0068c02c jmp 0x68bfc6
0068c02e movss xmm0, dword ptr [0xb6a7b0]
0068c036 movss dword ptr [esp + 0x14], xmm0
0068c03c cmp esi, 8
0068c03f jle 0x68c04e
0068c041 push 6
0068c043 mov ecx, dword ptr [0xbfd65c]
0068c049 call 0x6d5ad0
0068c04e mov eax, dword ptr [edi + 8]
0068c051 cmp eax, dword ptr [edi + 0xc]
0068c054 je 0x68c0dc
0068c05a movss xmm1, dword ptr [edi + 0x294]
0068c062 subss xmm1, dword ptr [eax + 0x20]
0068c067 movss xmm2, dword ptr [edi + 0x298]
0068c06f subss xmm2, dword ptr [eax + 0x24]
0068c074 movaps xmm0, xmm1
0068c077 movss dword ptr [esp + 0x10], xmm1
0068c07d mulss xmm0, xmm1
0068c081 movaps xmm1, xmm2
0068c084 movss dword ptr [esp + 0xc], xmm2
0068c08a mulss xmm1, xmm2
0068c08e addss xmm0, xmm1
0068c092 call 0x4228c0
0068c097 comiss xmm0, dword ptr [0xb6a18c]
0068c09e movss xmm2, dword ptr [esp + 0x10]
0068c0a4 movss xmm3, dword ptr [esp + 0xc]
0068c0aa jbe 0x68c0c0
0068c0ac movss xmm1, dword ptr [0xb6a614]
0068c0b4 divss xmm1, xmm0
0068c0b8 mulss xmm2, xmm1
0068c0bc mulss xmm3, xmm1
0068c0c0 mulss xmm2, dword ptr [0xb6a9b0]
0068c0c8 mulss xmm3, dword ptr [0xb6a9b0]
0068c0d0 movss dword ptr [esp + 0x28], xmm2
0068c0d6 movss dword ptr [esp + 0x2c], xmm3
0068c0dc cmp esi, 6
0068c0df jle 0x68c4d8
0068c0e5 mov eax, dword ptr [edi + 0x288]
0068c0eb test byte ptr [eax + 0x60], 1
0068c0ef je 0x68c4d8
0068c0f5 mov eax, esi
0068c0f7 cdq 
0068c0f8 sub eax, edx
0068c0fa sar eax, 1
0068c0fc mov dword ptr [esp + 0xc], eax
0068c100 jne 0x68c106
0068c102 xor edx, edx
0068c104 jmp 0x68c115
0068c106 call 0x6c3d90
0068c10b xor edx, edx
0068c10d div dword ptr [esp + 0xc]
0068c111 mov eax, dword ptr [esp + 0xc]
0068c115 movaps xmm0, xmmword ptr [0xb6bf50]
0068c11c lea ecx, [esp + 0x48]
0068c120 add eax, edx
0068c122 lea edx, [edi + 0x1dc]
0068c128 mov dword ptr [esp + 0x10], eax
0068c12c lea eax, [esp + 0x38]
0068c130 push eax
0068c131 movups xmmword ptr [esp + 0x3c], xmm0
0068c136 call 0x4d1ee0
0068c13b add esp, 4
0068c13e cmp dword ptr [esp + 0x10], 0
0068c143 jle 0x68c4d8
0068c149 movss xmm1, dword ptr [0xb6a19c]
0068c151 call 0x6c3d90
0068c156 movd xmm0, eax
0068c15a cvtdq2pd xmm0, xmm0
0068c15e shr eax, 0x1f
0068c161 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068c16a cvtpd2ps xmm0, xmm0
0068c16e mulss xmm0, xmm1
0068c172 mulss xmm0, dword ptr [0xb6a974]
0068c17a movss dword ptr [esp + 0xc], xmm0
0068c180 call 0x6c3d90
0068c185 movd xmm0, eax
0068c189 cvtdq2pd xmm0, xmm0
0068c18d shr eax, 0x1f
0068c190 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068c199 cvtpd2ps xmm0, xmm0
0068c19d mulss xmm0, xmm1
0068c1a1 mulss xmm0, dword ptr [0xb6a874]
0068c1a9 addss xmm0, xmm0
0068c1ad movss dword ptr [esp + 0x1c], xmm0
0068c1b3 call 0x411fe0
0068c1b8 mulss xmm0, dword ptr [esp + 0xc]
0068c1be movss dword ptr [esp + 0x20], xmm0
0068c1c4 movss dword ptr [esp + 0x38], xmm0
0068c1ca movss xmm0, dword ptr [esp + 0x1c]
0068c1d0 call 0x412010
0068c1d5 mulss xmm0, dword ptr [esp + 0xc]
0068c1db movss dword ptr [esp + 0x18], xmm0
0068c1e1 movss dword ptr [esp + 0x3c], xmm0
0068c1e7 call 0x6c3d90
0068c1ec movd xmm1, eax
0068c1f0 cvtdq2pd xmm1, xmm1
0068c1f4 shr eax, 0x1f
0068c1f7 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
0068c200 cvtpd2ps xmm0, xmm1
0068c204 mulss xmm0, dword ptr [0xb6a19c]
0068c20c mulss xmm0, dword ptr [0xb6a9c8]
0068c214 movss dword ptr [esp + 0xc], xmm0
0068c21a call 0x6c3d90
0068c21f mov esi, eax
0068c221 call 0x6c3d90
0068c226 movd xmm0, eax
0068c22a cvtdq2pd xmm0, xmm0
0068c22e shr eax, 0x1f
0068c231 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068c23a cvtpd2ps xmm0, xmm0
0068c23e mulss xmm0, dword ptr [0xb6a19c]
0068c246 mulss xmm0, dword ptr [0xb6a874]
0068c24e addss xmm0, xmm0
0068c252 movss dword ptr [esp + 0x1c], xmm0
0068c258 call 0x411fe0
0068c25d mulss xmm0, dword ptr [esp + 0xc]
0068c263 addss xmm0, dword ptr [edi + 0x294]
0068c26b movss dword ptr [esp + 0x30], xmm0
0068c271 movss xmm0, dword ptr [esp + 0x1c]
0068c277 call 0x412010
0068c27c mulss xmm0, dword ptr [esp + 0xc]
0068c282 lea eax, [esp + 0x38]
0068c286 mov ecx, dword ptr [0xbfd65c]
0068c28c push 0
0068c28e push esi
0068c28f addss xmm0, dword ptr [edi + 0x298]
0068c297 push 0
0068c299 push edi
0068c29a push eax
0068c29b lea eax, [esp + 0x44]
0068c29f push eax
0068c2a0 push 0x3b
0068c2a2 push 0x3e8
0068c2a7 movss dword ptr [esp + 0x54], xmm0
0068c2ad call 0x6d0ca0
0068c2b2 movss xmm2, dword ptr [esp + 0x20]
0068c2b8 mov esi, eax
