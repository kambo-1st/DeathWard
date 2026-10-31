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
