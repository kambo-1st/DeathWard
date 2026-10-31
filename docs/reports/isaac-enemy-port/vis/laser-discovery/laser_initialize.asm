008c86d0 push ebp
008c86d1 mov ebp, esp
008c86d3 and esp, 0xfffffff8
008c86d6 sub esp, 0x70
008c86d9 push esi
008c86da mov esi, ecx
008c86dc push edi
008c86dd mov dword ptr [esp + 0x4c], esi
008c86e1 call 0x8c7ac0
008c86e6 cmp dword ptr [esi + 0x2c], 4
008c86ea movss xmm0, dword ptr [esi + 0x36c]
008c86f2 movaps xmm1, xmm0
008c86f5 mulss xmm1, dword ptr [0xb6a230]
008c86fd movss dword ptr [esp + 0x2c], xmm1
008c8703 jne 0x8c878f
008c8709 movss dword ptr [esi + 0xe0], xmm0
008c8711 movaps xmm0, xmm1
008c8714 mov dword ptr [esi + 0x3b0], 0x43960000
008c871e call 0x411fe0
008c8723 movss xmm1, dword ptr [esi + 0x294]
008c872b mulss xmm0, dword ptr [0xb6ac14]
008c8733 addss xmm1, dword ptr [esi + 0x2a4]
008c873b addss xmm0, xmm1
008c873f movss dword ptr [esp + 0x38], xmm0
008c8745 movss xmm0, dword ptr [esp + 0x2c]
008c874b call 0x412010
008c8750 movss xmm1, dword ptr [esi + 0x298]
008c8758 addss xmm1, dword ptr [esi + 0x2a8]
008c8760 mulss xmm0, dword ptr [0xb6ac14]
008c8768 addss xmm0, xmm1
008c876c movss xmm1, dword ptr [esp + 0x38]
008c8772 movss dword ptr [esi + 0x428], xmm1
008c877a movss dword ptr [esi + 0x42c], xmm0
008c8782 mov byte ptr [esi + 0x3ad], 0
008c8789 pop edi
008c878a pop esi
008c878b mov esp, ebp
008c878d pop ebp
008c878e ret 
008c878f movaps xmm0, xmm1
008c8792 call 0x411fe0
008c8797 movss dword ptr [esp + 0x50], xmm0
008c879d movss xmm0, dword ptr [esp + 0x2c]
008c87a3 call 0x412010
008c87a8 movss xmm1, dword ptr [esp + 0x50]
008c87ae movss xmm2, dword ptr [0xb6c980]
008c87b6 movss xmm3, dword ptr [0xb6a1b8]
008c87be andps xmm1, xmm2
008c87c1 comiss xmm3, xmm1
008c87c4 movss dword ptr [esp + 0x54], xmm0
008c87ca xorps xmm1, xmm1
008c87cd jbe 0x8c87d5
008c87cf movss dword ptr [esp + 0x50], xmm1
008c87d5 andps xmm0, xmm2
008c87d8 comiss xmm3, xmm0
008c87db jbe 0x8c87e6
008c87dd xorps xmm0, xmm0
008c87e0 movss dword ptr [esp + 0x54], xmm0
008c87e6 mov eax, dword ptr [esi + 0x344]
008c87ec mov ecx, esi
008c87ee shr eax, 8
008c87f1 and al, 1
008c87f3 mov byte ptr [esi + 0x13c], al
008c87f9 call 0x8d7d90
008c87fe push ecx
008c87ff mov ecx, esi
008c8801 call 0x8d79b0
008c8806 mov al, byte ptr [esi + 0x3ad]
008c880c test al, al
008c880e jns 0x8c896a
008c8814 mov ecx, dword ptr [esi + 0x314]
008c881a test ecx, ecx
008c881c je 0x8c8960
008c8822 mov eax, dword ptr [ecx + 0x28]
008c8825 cmp eax, 1
008c8828 je 0x8c8956
008c882e cmp dword ptr [esi + 0x34], 1
008c8832 je 0x8c8956
008c8838 cmp eax, 0x3e
008c883b je 0x8c8956
008c8841 cmp eax, 0x3e8
008c8846 jne 0x8c885a
008c8848 cmp dword ptr [ecx + 0x2c], 0xb2
008c884f jne 0x8c88f5
008c8855 jmp 0x8c8956
008c885a cmp eax, 0x107
008c885f je 0x8c8956
008c8865 cmp eax, 0x10c
008c886a je 0x8c8956
008c8870 cmp eax, 0x19a
008c8875 je 0x8c8956
008c887b cmp eax, 0x104
008c8880 jne 0x8c888e
008c8882 cmp dword ptr [ecx + 0x30], 2
008c8886 je 0x8c8956
008c888c jmp 0x8c88f5
008c888e cmp eax, 3
008c8891 jne 0x8c88f5
008c8893 mov eax, dword ptr [ecx + 0x2c]
008c8896 cmp eax, 0x50
008c8899 je 0x8c8956
008c889f cmp eax, 0x78
008c88a2 je 0x8c8956
008c88a8 mov ecx, dword ptr [esi + 0x378]
008c88ae and ecx, dword ptr [0xbc4cb0]
008c88b4 mov eax, dword ptr [esi + 0x37c]
008c88ba and eax, dword ptr [0xbc4cb4]
008c88c0 mov dword ptr [esp + 0x68], ecx
008c88c4 mov ecx, dword ptr [esi + 0x380]
008c88ca and ecx, dword ptr [0xbc4cb8]
008c88d0 mov dword ptr [esp + 0x6c], eax
008c88d4 mov eax, dword ptr [esi + 0x384]
008c88da and eax, dword ptr [0xbc4cbc]
008c88e0 mov dword ptr [esp + 0x70], ecx
008c88e4 lea ecx, [esp + 0x68]
008c88e8 mov dword ptr [esp + 0x74], eax
008c88ec call 0x412090
008c88f1 test al, al
008c88f3 jne 0x8c8956
008c88f5 cmp byte ptr [esi + 0x410], 0
008c88fc jne 0x8c8956
008c88fe mov ecx, esi
008c8900 call 0x4275d0
008c8905 test al, al
008c8907 jne 0x8c8956
008c8909 mov ecx, dword ptr [esi + 0x378]
008c890f and ecx, dword ptr [0xbc4c00]
008c8915 mov eax, dword ptr [esi + 0x37c]
008c891b and eax, dword ptr [0xbc4c04]
008c8921 mov dword ptr [esp + 0x68], ecx
008c8925 mov ecx, dword ptr [esi + 0x380]
008c892b and ecx, dword ptr [0xbc4c08]
008c8931 mov dword ptr [esp + 0x6c], eax
008c8935 mov eax, dword ptr [esi + 0x384]
008c893b and eax, dword ptr [0xbc4c0c]
008c8941 mov dword ptr [esp + 0x70], ecx
008c8945 lea ecx, [esp + 0x68]
008c8949 mov dword ptr [esp + 0x74], eax
008c894d call 0x412090
008c8952 test al, al
008c8954 je 0x8c8960
008c8956 cmp dword ptr [esi + 0x2c], 7
008c895a je 0x8c8960
008c895c mov al, 1
008c895e jmp 0x8c8962
008c8960 xor al, al
008c8962 mov byte ptr [esi + 0x3ad], al
008c8968 test al, al
008c896a je 0x8c8994
008c896c mov ecx, esi
008c896e call 0x8c7720
008c8973 mov eax, dword ptr [esi + 0x30]
008c8976 cmp eax, 1
008c8979 je 0x8c8989
008c897b cmp eax, 2
008c897e je 0x8c8989
008c8980 cmp eax, 3
008c8983 jne 0x8c8ef2
008c8989 call 0x8d4160
008c898e pop edi
008c898f pop esi
008c8990 mov esp, ebp
008c8992 pop ebp
008c8993 ret 
008c8994 movss xmm5, dword ptr [esi + 0x294]
008c899c movss xmm3, dword ptr [esi + 0x2a8]
008c89a4 addss xmm5, dword ptr [esi + 0x2a4]
008c89ac addss xmm3, dword ptr [esi + 0x298]
008c89b4 mov eax, dword ptr [esi + 0x17c]
008c89ba movss dword ptr [esp + 0xc], xmm5
008c89c0 movss dword ptr [esp + 0x60], xmm5
008c89c6 movss dword ptr [esp + 0x10], xmm3
008c89cc movss dword ptr [esp + 0x64], xmm3
008c89d2 cmp eax, 6
008c89d5 jne 0x8c8db9
008c89db movss xmm2, dword ptr [esp + 0x50]
008c89e1 lea edi, [esi + 0x428]
008c89e7 movss xmm1, dword ptr [esp + 0x54]
008c89ed movaps xmm6, xmm2
008c89f0 mulss xmm6, dword ptr [0xb6ad38]
008c89f8 mov eax, dword ptr [0xbfd65c]
008c89fd mulss xmm2, dword ptr [0xb6a8cc]
008c8a05 movss xmm4, dword ptr [esp + 0xc]
008c8a0b addss xmm6, xmm5
008c8a0f movaps xmm5, xmm1
008c8a12 mov edx, dword ptr [eax + 0x18190]
008c8a18 mulss xmm5, dword ptr [0xb6ad38]
008c8a20 subss xmm4, xmm2
008c8a24 mov dword ptr [esp + 0x30], edx
008c8a28 mulss xmm1, dword ptr [0xb6a8cc]
008c8a30 movss xmm2, dword ptr [0xb6aa3c]
008c8a38 addss xmm5, xmm3
008c8a3c movaps xmm0, xmm4
008c8a3f movss dword ptr [esp + 0x68], xmm6
008c8a45 movss dword ptr [esp + 0x28], xmm0
008c8a4b subss xmm3, xmm1
008c8a4f movss dword ptr [esp + 0x58], xmm0
008c8a55 subss xmm6, xmm4
008c8a59 movss dword ptr [esp + 0x34], xmm4
008c8a5f movss dword ptr [esp + 0x6c], xmm5
008c8a65 movaps xmm0, xmm3
008c8a68 movss dword ptr [esp + 0x38], xmm3
008c8a6e movss dword ptr [esp + 0x2c], xmm0
008c8a74 subss xmm5, xmm3
008c8a78 movss dword ptr [esp + 0x5c], xmm0
008c8a7e movaps xmm0, xmm4
008c8a81 subss xmm0, xmm2
008c8a85 movss dword ptr [esp + 0x3c], xmm6
008c8a8b movss dword ptr [esp + 0x40], xmm5
008c8a91 divss xmm0, xmm2
008c8a95 addss xmm0, dword ptr [0xb6a480]
008c8a9d cvttss2si eax, xmm0
008c8aa1 movaps xmm0, xmm3
008c8aa4 subss xmm0, dword ptr [0xb6ab20]
008c8aac mov dword ptr [esp + 0x18], eax
008c8ab0 xor eax, eax
008c8ab2 divss xmm0, xmm2
008c8ab6 xorps xmm2, xmm2
008c8ab9 comiss xmm6, xmm2
008c8abc addss xmm0, dword ptr [0xb6a480]
008c8ac4 seta al
008c8ac7 cvttss2si ecx, xmm0
008c8acb lea eax, [eax*2 - 1]
008c8ad2 mov dword ptr [esp + 0x14], eax
008c8ad6 xor eax, eax
008c8ad8 xorps xmm0, xmm0
008c8adb comiss xmm5, xmm2
008c8ade mov dword ptr [esp + 0x20], ecx
008c8ae2 movss dword ptr [esp + 8], xmm0
008c8ae8 seta al
008c8aeb ucomiss xmm6, dword ptr [0xc02fec]
008c8af2 lea eax, [eax*2 - 1]
008c8af9 mov dword ptr [esp + 0x1c], eax
008c8afd lahf 
008c8afe test ah, 0x44
008c8b01 jp 0x8c8b14
008c8b03 ucomiss xmm5, dword ptr [0xc02ff0]
008c8b0a lahf 
008c8b0b test ah, 0x44
008c8b0e jnp 0x8c8cc5
008c8b14 mov esi, dword ptr [esp + 0x18]
008c8b18 lea eax, [ecx + ecx*4]
008c8b1b shl eax, 3
008c8b1e mov dword ptr [esp + 0x24], eax
008c8b22 lea eax, [esi + esi*4]
008c8b25 shl eax, 3
008c8b28 mov dword ptr [esp + 0x18], eax
008c8b2c mov eax, dword ptr [esp + 0x1c]
008c8b30 lea eax, [eax + eax*4]
008c8b33 shl eax, 3
008c8b36 mov dword ptr [esp + 0x48], eax
008c8b3a mov eax, dword ptr [esp + 0x14]
008c8b3e lea eax, [eax + eax*4]
008c8b41 shl eax, 3
008c8b44 mov dword ptr [esp + 0x44], eax
008c8b48 test esi, esi
008c8b4a js 0x8c8b7d
008c8b4c mov eax, dword ptr [edx + 0xc]
008c8b4f cmp esi, eax
008c8b51 jge 0x8c8b7d
008c8b53 test ecx, ecx
008c8b55 js 0x8c8b7d
008c8b57 cmp ecx, dword ptr [edx + 0x10]
008c8b5a jge 0x8c8b7d
008c8b5c mov edi, ecx
008c8b5e mov ecx, edx
008c8b60 imul edi, eax
008c8b63 add edi, esi
008c8b65 push edi
008c8b66 call 0x7aeec0
008c8b6b cmp edi, 0x1bf
008c8b71 ja 0x8c8b86
008c8b73 mov edx, dword ptr [esp + 0x30]
008c8b77 mov ecx, dword ptr [edx + edi*4 + 0x24]
008c8b7b jmp 0x8c8b8c
008c8b7d push -1
008c8b7f mov ecx, edx
008c8b81 call 0x7aeec0
008c8b86 mov edx, dword ptr [esp + 0x30]
008c8b8a xor ecx, ecx
008c8b8c cmp eax, 2
008c8b8f je 0x8c8ba0
008c8b91 cmp eax, 3
008c8b94 je 0x8c8ba0
008c8b96 cmp eax, 4
008c8b99 je 0x8c8ba0
008c8b9b cmp eax, 5
008c8b9e jne 0x8c8bb9
008c8ba0 test ecx, ecx
008c8ba2 je 0x8c8cb5
008c8ba8 mov eax, dword ptr [ecx + 4]
008c8bab cmp eax, 0xf
008c8bae je 0x8c8bb9
008c8bb0 cmp eax, 0x10
008c8bb3 jne 0x8c8cb5
008c8bb9 movss xmm6, dword ptr [esp + 0x3c]
008c8bbf xorps xmm2, xmm2
008c8bc2 mov ecx, dword ptr [esp + 0x18]
008c8bc6 movss xmm7, dword ptr [0xb6adc4]
008c8bce ucomiss xmm6, xmm2
008c8bd1 lahf 
008c8bd2 test ah, 0x44
008c8bd5 jnp 0x8c8bf7
008c8bd7 mov eax, dword ptr [esp + 0x14]
008c8bdb lea eax, [eax + eax*4]
008c8bde add eax, 0xa
008c8be1 lea eax, [ecx + eax*4]
008c8be4 movd xmm1, eax
008c8be8 cvtdq2ps xmm1, xmm1
008c8beb subss xmm1, dword ptr [esp + 0x28]
008c8bf1 divss xmm1, xmm6
008c8bf5 jmp 0x8c8bfa
008c8bf7 movaps xmm1, xmm7
008c8bfa movss xmm5, dword ptr [esp + 0x40]
008c8c00 mov edi, dword ptr [esp + 0x24]
008c8c04 ucomiss xmm5, xmm2
008c8c07 lahf 
008c8c08 test ah, 0x44
008c8c0b jnp 0x8c8c2d
008c8c0d mov eax, dword ptr [esp + 0x1c]
008c8c11 lea eax, [eax + eax*4]
008c8c14 add eax, 0x1e
008c8c17 lea eax, [edi + eax*4]
008c8c1a movd xmm0, eax
008c8c1e cvtdq2ps xmm0, xmm0
008c8c21 subss xmm0, dword ptr [esp + 0x2c]
008c8c27 divss xmm0, xmm5
008c8c2b jmp 0x8c8c30
008c8c2d movaps xmm0, xmm7
008c8c30 comiss xmm0, xmm1
008c8c33 jbe 0x8c8c50
008c8c35 addss xmm1, dword ptr [esp + 8]
008c8c3b add esi, dword ptr [esp + 0x14]
008c8c3f add ecx, dword ptr [esp + 0x44]
008c8c43 mov dword ptr [esp + 0x18], ecx
008c8c47 mov ecx, dword ptr [esp + 0x20]
008c8c4b movaps xmm0, xmm1
008c8c4e jmp 0x8c8c6a
008c8c50 mov ecx, dword ptr [esp + 0x20]
008c8c54 add ecx, dword ptr [esp + 0x1c]
008c8c58 add edi, dword ptr [esp + 0x48]
008c8c5c addss xmm0, dword ptr [esp + 8]
008c8c62 mov dword ptr [esp + 0x20], ecx
008c8c66 mov dword ptr [esp + 0x24], edi
008c8c6a movss xmm1, dword ptr [0xb6a614]
008c8c72 movaps xmm4, xmm0
008c8c75 comiss xmm1, xmm0
008c8c78 movaps xmm3, xmm0
008c8c7b mulss xmm4, xmm5
008c8c7f mulss xmm3, xmm6
008c8c83 addss xmm4, dword ptr [esp + 0x38]
008c8c89 movss dword ptr [esp + 8], xmm0
008c8c8f addss xmm3, dword ptr [esp + 0x34]
008c8c95 movss dword ptr [esp + 0x5c], xmm4
008c8c9b movss dword ptr [esp + 0x2c], xmm4
008c8ca1 movss dword ptr [esp + 0x58], xmm3
008c8ca7 movss dword ptr [esp + 0x28], xmm3
008c8cad ja 0x8c8b48
008c8cb3 jmp 0x8c8cbb
008c8cb5 movss xmm0, dword ptr [esp + 8]
008c8cbb mov esi, dword ptr [esp + 0x4c]
008c8cbf lea edi, [esi + 0x428]
008c8cc5 movss xmm1, dword ptr [0xb6a614]
008c8ccd test edi, edi
008c8ccf je 0x8c8ce9
008c8cd1 comiss xmm0, xmm1
008c8cd4 lea eax, [esp + 0x58]
008c8cd8 lea ecx, [esp + 0x68]
008c8cdc cmovb ecx, eax
008c8cdf mov eax, dword ptr [ecx]
008c8ce1 mov dword ptr [edi], eax
008c8ce3 mov eax, dword ptr [ecx + 4]
008c8ce6 mov dword ptr [edi + 4], eax
008c8ce9 comiss xmm0, xmm1
008c8cec jb 0x8c8d26
008c8cee lea eax, [esp + 0x50]
008c8cf2 mov ecx, esi
008c8cf4 push eax
008c8cf5 lea eax, [esp + 0x64]
008c8cf9 push eax
008c8cfa lea eax, [esp + 0x70]
008c8cfe push eax
008c8cff call 0x8c7e90
008c8d04 movss xmm0, dword ptr [esi + 0x2a8]
008c8d0c movss xmm1, dword ptr [eax]
008c8d10 addss xmm1, dword ptr [esi + 0x2a4]
008c8d18 addss xmm0, dword ptr [eax + 4]
008c8d1d movss dword ptr [edi], xmm1
008c8d21 movss dword ptr [edi + 4], xmm0
008c8d26 movss xmm5, dword ptr [esp + 0xc]
008c8d2c movss xmm2, dword ptr [esi + 0x420]
008c8d34 xorps xmm0, xmm0
008c8d37 comiss xmm2, xmm0
008c8d3a movss dword ptr [esp + 0x4c], xmm2
008c8d40 jbe 0x8c8e5e
008c8d46 movss xmm0, dword ptr [edi + 4]
008c8d4b subss xmm0, dword ptr [esp + 0x10]
008c8d51 movss xmm1, dword ptr [edi]
008c8d55 subss xmm1, xmm5
008c8d59 movaps xmm3, xmm0
008c8d5c movss dword ptr [esp + 0x34], xmm0
008c8d62 mulss xmm3, xmm0
008c8d66 movaps xmm0, xmm1
008c8d69 movss dword ptr [esp + 0x38], xmm1
008c8d6f mulss xmm0, xmm1
008c8d73 movaps xmm1, xmm2
008c8d76 mulss xmm1, xmm2
008c8d7a addss xmm3, xmm0
008c8d7e comiss xmm3, xmm1
008c8d81 jbe 0x8c8e5e
008c8d87 movaps xmm0, xmm3
008c8d8a call 0x4228c0
008c8d8f xorps xmm1, xmm1
008c8d92 comiss xmm0, xmm1
008c8d95 jbe 0x8c8e30
008c8d9b movss xmm1, dword ptr [esp + 0x4c]
008c8da1 divss xmm1, xmm0
008c8da5 movaps xmm2, xmm1
008c8da8 mulss xmm1, dword ptr [esp + 0x34]
008c8dae mulss xmm2, dword ptr [esp + 0x38]
008c8db4 jmp 0x8c8e3c
008c8db9 cmp eax, 3
008c8dbc jne 0x8c8df8
008c8dbe lea eax, [esp + 0x50]
008c8dc2 mov ecx, esi
008c8dc4 push eax
008c8dc5 lea eax, [esp + 0x64]
008c8dc9 push eax
008c8dca lea eax, [esp + 0x70]
008c8dce push eax
008c8dcf call 0x8c7e90
008c8dd4 movss xmm1, dword ptr [esi + 0x2a4]
008c8ddc lea edi, [esi + 0x428]
008c8de2 movss xmm0, dword ptr [esi + 0x2a8]
008c8dea addss xmm1, dword ptr [eax]
008c8dee addss xmm0, dword ptr [eax + 4]
008c8df3 jmp 0x8c8d1d
008c8df8 movss xmm2, dword ptr [esp + 0x50]
008c8dfe lea edi, [esi + 0x428]
008c8e04 movss xmm1, dword ptr [esp + 0x54]
008c8e0a mulss xmm2, dword ptr [0xb6accc]
008c8e12 mulss xmm1, dword ptr [0xb6accc]
008c8e1a addss xmm2, xmm5
008c8e1e addss xmm1, xmm3
008c8e22 movss dword ptr [edi], xmm2
008c8e26 movss dword ptr [edi + 4], xmm1
008c8e2b jmp 0x8c8d2c
008c8e30 movss xmm2, dword ptr [esp + 0x38]
008c8e36 movss xmm1, dword ptr [esp + 0x34]
008c8e3c movss xmm5, dword ptr [esp + 0xc]
008c8e42 movaps xmm0, xmm5
008c8e45 addss xmm0, xmm2
008c8e49 movss xmm2, dword ptr [esp + 0x10]
008c8e4f addss xmm1, xmm2
008c8e53 movss dword ptr [edi], xmm0
008c8e57 movss dword ptr [edi + 4], xmm1
008c8e5c jmp 0x8c8e64
008c8e5e movss xmm2, dword ptr [esp + 0x10]
008c8e64 movss xmm1, dword ptr [edi]
008c8e68 movss xmm0, dword ptr [edi + 4]
008c8e6d subss xmm1, xmm5
008c8e71 subss xmm0, xmm2
008c8e75 mulss xmm1, xmm1
008c8e79 mulss xmm0, xmm0
008c8e7d addss xmm0, xmm1
008c8e81 call 0x4228c0
008c8e86 mov eax, dword ptr [esi + 0x2c]
008c8e89 movaps xmm1, xmm0
008c8e8c movss dword ptr [esi + 0x3b0], xmm1
008c8e94 cmp eax, 6
008c8e97 je 0x8c8e9e
008c8e99 cmp eax, 0xf
008c8e9c jne 0x8c8ed8
008c8e9e cmp dword ptr [esi + 0x34], 0x19a
008c8ea5 jne 0x8c8ec8
008c8ea7 movss xmm0, dword ptr [0xb6aae0]
008c8eaf comiss xmm0, xmm1
008c8eb2 ja 0x8c8eba
008c8eb4 movss xmm0, xmm1
008c8eb8 jmp 0x8c8ebe
008c8eba movss xmm0, xmm0
008c8ebe movss dword ptr [esi + 0x3b0], xmm0
008c8ec6 jmp 0x8c8ed8
008c8ec8 addss xmm1, dword ptr [0xb6aafc]
008c8ed0 movss dword ptr [esi + 0x3b0], xmm1
008c8ed8 movss xmm0, dword ptr [esi + 0x36c]
008c8ee0 mov ecx, esi
008c8ee2 subss xmm0, dword ptr [0xb6aae4]
008c8eea movss dword ptr [esi + 0xe0], xmm0
008c8ef2 call 0x8cc300
008c8ef7 pop edi
008c8ef8 pop esi
008c8ef9 mov esp, ebp
008c8efb pop ebp
008c8efc ret 
008c8efd int3 
008c8efe int3 
008c8eff int3 
008c8f00 push ebx
008c8f01 mov ebx, esp
008c8f03 sub esp, 8
008c8f06 and esp, 0xfffffff8
008c8f09 add esp, 4
008c8f0c push ebp
008c8f0d mov ebp, dword ptr [ebx + 4]
008c8f10 mov dword ptr [esp + 4], ebp
008c8f14 mov ebp, esp
008c8f16 push -1
008c8f18 push 0x9ff77d
008c8f1d mov eax, dword ptr fs:[0]
008c8f23 push eax
008c8f24 push ebx
008c8f25 sub esp, 0xb0
008c8f2b push esi
008c8f2c push edi
008c8f2d mov eax, dword ptr [0xbaa3b4]
008c8f32 xor eax, ebp
008c8f34 push eax
008c8f35 lea eax, [ebp - 0xc]
008c8f38 mov dword ptr fs:[0], eax
008c8f3e mov edi, ecx
008c8f40 cmp byte ptr [edi + 0x3ad], 0
008c8f47 je 0x8c95da
008c8f4d push 0x1c
008c8f4f mov dword ptr [ebp - 0x38], 0
008c8f56 mov dword ptr [ebp - 0x34], 0
008c8f5d call 0x9eacf8
008c8f62 add esp, 4
008c8f65 mov dword ptr [eax], eax
008c8f67 mov dword ptr [eax + 4], eax
008c8f6a mov dword ptr [eax + 8], eax
008c8f6d mov word ptr [eax + 0xc], 0x101
008c8f73 mov dword ptr [ebp - 0x38], eax
008c8f76 mov dword ptr [ebp - 4], 0
008c8f7d mov esi, dword ptr [edi + 0x3e0]
008c8f83 mov ecx, dword ptr [edi + 0x3dc]
008c8f89 sub esi, ecx
008c8f8b sar esi, 3
008c8f8e mov dword ptr [ebp - 0x6c], esi
008c8f91 cmp esi, 2
008c8f94 jb 0x8c95ba
008c8f9a mov eax, dword ptr [ebx + 0xc]
008c8f9d xorps xmm0, xmm0
008c8fa0 movss xmm3, dword ptr [ecx + 4]
008c8fa5 xorps xmm1, xmm1
008c8fa8 xor edx, edx
008c8faa movss dword ptr [ebp - 0x5c], xmm0
008c8faf movss dword ptr [ebp - 0x58], xmm0
008c8fb4 movss xmm2, dword ptr [eax]
008c8fb8 addss xmm2, dword ptr [ecx]
008c8fbc addss xmm3, dword ptr [eax + 4]
008c8fc1 movss dword ptr [ebp - 0x4c], xmm1
008c8fc6 mov dword ptr [ebp - 0x48], edx
008c8fc9 movss dword ptr [ebp - 0x40], xmm2
008c8fce movss dword ptr [ebp - 0x50], xmm2
008c8fd3 xorps xmm2, xmm2
008c8fd6 movss dword ptr [ebp - 0x28], xmm3
008c8fdb movss dword ptr [ebp - 0x54], xmm3
008c8fe0 movss dword ptr [ebp - 0x24], xmm2
008c8fe5 mov ecx, dword ptr [edi + 0x3dc]
008c8feb cmp edx, esi
008c8fed jae 0x8c9046
008c8fef movss xmm1, dword ptr [ecx + edx*8]
008c8ff4 movss xmm0, dword ptr [ecx + edx*8 + 4]
008c8ffa addss xmm1, dword ptr [eax]
008c8ffe addss xmm0, dword ptr [eax + 4]
008c9003 lea eax, [esi - 1]
008c9006 movss dword ptr [ebp - 0x20], xmm1
008c900b movss dword ptr [ebp - 0x1c], xmm0
008c9010 cmp edx, eax
008c9012 jae 0x8c902d
008c9014 movss xmm2, dword ptr [ecx + edx*8 + 0xc]
008c901a movss xmm1, dword ptr [ecx + edx*8 + 8]
008c9020 subss xmm2, dword ptr [ecx + edx*8 + 4]
008c9026 subss xmm1, dword ptr [ecx + edx*8]
008c902b jmp 0x8c9095
008c902d movss xmm2, dword ptr [ecx + edx*8 + 4]
008c9033 movss xmm1, dword ptr [ecx + edx*8]
008c9038 subss xmm2, dword ptr [ecx + edx*8 - 4]
008c903e subss xmm1, dword ptr [ecx + edx*8 - 8]
008c9044 jmp 0x8c9095
008c9046 movss xmm2, dword ptr [ecx + esi*8 - 8]
008c904c subss xmm2, dword ptr [ecx + esi*8 - 0x10]
008c9052 movss xmm0, dword ptr [ecx + esi*8 - 4]
008c9058 subss xmm0, dword ptr [ecx + esi*8 - 0xc]
008c905e movss xmm1, dword ptr [ecx + esi*8 - 8]
008c9064 subss xmm1, dword ptr [ecx + esi*8 - 0x10]
008c906a addss xmm2, dword ptr [ecx + esi*8 - 8]
008c9070 addss xmm0, dword ptr [ecx + esi*8 - 4]
008c9076 addss xmm2, dword ptr [eax]
008c907a addss xmm0, dword ptr [eax + 4]
008c907f movss dword ptr [ebp - 0x20], xmm2
008c9084 movss xmm2, dword ptr [ecx + esi*8 - 4]
008c908a subss xmm2, dword ptr [ecx + esi*8 - 0xc]
008c9090 movss dword ptr [ebp - 0x1c], xmm0
008c9095 movaps xmm0, xmm1
008c9098 movss dword ptr [ebp - 0x18], xmm1
008c909d mulss xmm0, xmm1
008c90a1 movaps xmm1, xmm2
008c90a4 mulss xmm1, xmm2
008c90a8 movss dword ptr [ebp - 0x14], xmm2
008c90ad addss xmm0, xmm1
008c90b1 call 0x4228c0
008c90b6 movss xmm1, dword ptr [ebp - 0x18]
008c90bb lea eax, [ebp - 0x20]
008c90be movaps xmm2, xmm0
008c90c1 movss xmm0, dword ptr [ebp - 0x14]
008c90c6 divss xmm0, xmm2
008c90ca push ecx
008c90cb mov ecx, dword ptr [0xbfd65c]
008c90d1 mov dword ptr [esp], 0
008c90d8 push eax
008c90d9 mov ecx, dword ptr [ecx + 0x18190]
008c90df divss xmm1, xmm2
008c90e3 movss dword ptr [ebp - 0x14], xmm0
008c90e8 movaps xmm0, xmm1
008c90eb movss dword ptr [ebp - 0x44], xmm2
008c90f0 xorps xmm0, xmmword ptr [0xb6c9b0]
008c90f7 movss dword ptr [ebp - 0x18], xmm1
008c90fc movss dword ptr [ebp - 0x60], xmm0
008c9101 call 0x7cf0a0
008c9106 movss xmm3, dword ptr [ebp - 0x1c]
008c910b movss xmm4, dword ptr [ebp - 0x20]
008c9110 movss xmm1, dword ptr [ebp - 0x14]
008c9115 test al, al
008c9117 je 0x8c913c
008c9119 movss xmm0, dword ptr [ebp - 0x24]
008c911e movss dword ptr [ebp - 0x4c], xmm0
008c9123 movss xmm0, dword ptr [ebp - 0x18]
008c9128 movss dword ptr [ebp - 0x50], xmm4
008c912d movss dword ptr [ebp - 0x54], xmm3
008c9132 movss dword ptr [ebp - 0x58], xmm0
008c9137 movss dword ptr [ebp - 0x5c], xmm1
008c913c movss xmm0, dword ptr [edi + 0x2c8]
008c9144 xorps xmm2, xmm2
008c9147 comiss xmm0, xmm2
008c914a movss dword ptr [ebp - 0x3c], xmm2
008c914f jbe 0x8c94a2
008c9155 nop word ptr [eax + eax]
008c9160 movss xmm2, dword ptr [ebp - 0x60]
008c9165 lea eax, [ebp - 0x30]
008c9168 mulss xmm1, dword ptr [ebp - 0x3c]
008c916d mov esi, dword ptr [0xbfd65c]
008c9173 mulss xmm2, dword ptr [ebp - 0x3c]
008c9178 push ecx
008c9179 addss xmm4, xmm1
008c917d mov dword ptr [esp], 0x41000000
008c9184 mov ecx, dword ptr [esi + 0x18190]
008c918a addss xmm3, xmm2
008c918e movss dword ptr [ebp - 0x64], xmm1
008c9193 push eax
008c9194 movss dword ptr [ebp - 0x68], xmm2
008c9199 movss dword ptr [ebp - 0x30], xmm4
008c919e movss dword ptr [ebp - 0x2c], xmm3
008c91a3 call 0x7cf0a0
008c91a8 test al, al
008c91aa je 0x8c9266
008c91b0 movss xmm1, dword ptr [0xb6aa3c]
008c91b8 movss xmm0, dword ptr [ebp - 0x30]
008c91bd subss xmm0, xmm1
008c91c1 mov ecx, dword ptr [esi + 0x18190]
008c91c7 divss xmm0, xmm1
008c91cb addss xmm0, dword ptr [0xb6a480]
008c91d3 cvttss2si edx, xmm0
008c91d7 movss xmm0, dword ptr [ebp - 0x2c]
008c91dc subss xmm0, dword ptr [0xb6ab20]
008c91e4 divss xmm0, xmm1
008c91e8 addss xmm0, dword ptr [0xb6a480]
008c91f0 cvttss2si eax, xmm0
008c91f4 test edx, edx
008c91f6 js 0x8c92dc
008c91fc mov esi, dword ptr [ecx + 0xc]
008c91ff cmp edx, esi
008c9201 jge 0x8c92dc
008c9207 test eax, eax
008c9209 js 0x8c92dc
008c920f cmp eax, dword ptr [ecx + 0x10]
008c9212 jge 0x8c92dc
008c9218 imul esi, eax
008c921b add esi, edx
008c921d js 0x8c92dc
008c9223 push esi
008c9224 call 0x7aeec0
008c9229 cmp eax, 1
008c922c je 0x8c92dc
008c9232 test eax, eax
008c9234 je 0x8c92dc
008c923a movss xmm0, dword ptr [ebp - 0x18]
008c923f lea eax, [ebp - 0x80]
008c9242 push eax
008c9243 movss dword ptr [ebp - 0x7c], xmm0
008c9248 lea eax, [ebp - 0x94]
008c924e movss xmm0, dword ptr [ebp - 0x14]
008c9253 lea ecx, [ebp - 0x38]
008c9256 push eax
008c9257 mov dword ptr [ebp - 0x80], esi
008c925a movss dword ptr [ebp - 0x78], xmm0
008c925f call 0x8d8740
008c9264 jmp 0x8c928e
008c9266 push 0xbc4940
008c926b lea edx, [edi + 0x378]
008c9271 lea ecx, [ebp - 0xb0]
008c9277 call 0x412050
008c927c add esp, 4
008c927f mov ecx, dword ptr [eax]
008c9281 or ecx, dword ptr [eax + 4]
008c9284 jne 0x8c928e
008c9286 mov ecx, dword ptr [eax + 8]
008c9289 or ecx, dword ptr [eax + 0xc]
008c928c je 0x8c92dc
008c928e movss xmm1, dword ptr [ebp - 0x24]
008c9293 movss xmm0, dword ptr [edi + 0x494]
008c929b comiss xmm0, xmm1
008c929e jbe 0x8c92dc
008c92a0 movss xmm0, dword ptr [ebp - 0x40]
008c92a5 movss dword ptr [edi + 0x494], xmm1
008c92ad movss dword ptr [edi + 0x498], xmm0
008c92b5 movss xmm0, dword ptr [ebp - 0x28]
008c92ba movss dword ptr [edi + 0x49c], xmm0
008c92c2 movss xmm0, dword ptr [ebp - 0x18]
008c92c7 movss dword ptr [edi + 0x4a0], xmm0
008c92cf movss xmm0, dword ptr [ebp - 0x14]
008c92d4 movss dword ptr [edi + 0x4a4], xmm0
008c92dc movss xmm1, dword ptr [ebp - 0x3c]
008c92e1 ucomiss xmm1, dword ptr [0xb6a18c]
008c92e8 lahf 
008c92e9 test ah, 0x44
008c92ec jnp 0x8c946d
008c92f2 movss xmm1, dword ptr [ebp - 0x20]
008c92f7 lea eax, [ebp - 0x30]
008c92fa movss xmm0, dword ptr [ebp - 0x1c]
008c92ff subss xmm1, dword ptr [ebp - 0x64]
008c9304 subss xmm0, dword ptr [ebp - 0x68]
008c9309 mov esi, dword ptr [0xbfd65c]
008c930f push ecx
008c9310 mov dword ptr [esp], 0x41000000
008c9317 push eax
008c9318 mov ecx, dword ptr [esi + 0x18190]
008c931e movss dword ptr [ebp - 0x30], xmm1
008c9323 movss dword ptr [ebp - 0x2c], xmm0
008c9328 call 0x7cf0a0
008c932d test al, al
008c932f je 0x8c9445
008c9335 movss xmm1, dword ptr [0xb6aa3c]
008c933d movss xmm0, dword ptr [ebp - 0x30]
008c9342 subss xmm0, xmm1
008c9346 mov ecx, dword ptr [esi + 0x18190]
008c934c divss xmm0, xmm1
008c9350 addss xmm0, dword ptr [0xb6a480]
008c9358 cvttss2si edx, xmm0
008c935c movss xmm0, dword ptr [ebp - 0x2c]
008c9361 subss xmm0, dword ptr [0xb6ab20]
008c9369 divss xmm0, xmm1
008c936d addss xmm0, dword ptr [0xb6a480]
008c9375 cvttss2si eax, xmm0
008c9379 test edx, edx
008c937b js 0x8c946d
008c9381 mov esi, dword ptr [ecx + 0xc]
008c9384 cmp edx, esi
008c9386 jge 0x8c946d
008c938c test eax, eax
008c938e js 0x8c946d
008c9394 cmp eax, dword ptr [ecx + 0x10]
008c9397 jge 0x8c946d
008c939d imul esi, eax
008c93a0 add esi, edx
008c93a2 js 0x8c946d
008c93a8 push esi
008c93a9 call 0x7aeec0
008c93ae cmp eax, 1
008c93b1 je 0x8c946d
008c93b7 test eax, eax
008c93b9 je 0x8c946d
008c93bf movss xmm0, dword ptr [ebp - 0x18]
008c93c4 lea eax, [ebp - 0x8c]
008c93ca push eax
008c93cb movss dword ptr [ebp - 0x88], xmm0
008c93d3 lea eax, [ebp - 0x9c]
008c93d9 movss xmm0, dword ptr [ebp - 0x14]
008c93de lea ecx, [ebp - 0x38]
008c93e1 push eax
008c93e2 mov dword ptr [ebp - 0x8c], esi
008c93e8 movss dword ptr [ebp - 0x84], xmm0
008c93f0 call 0x8d8740
008c93f5 movss xmm0, dword ptr [edi + 0x494]
008c93fd movss xmm2, dword ptr [ebp - 0x24]
008c9402 comiss xmm0, xmm2
008c9405 movss xmm1, dword ptr [ebp - 0x14]
008c940a jbe 0x8c9472
008c940c movss xmm0, dword ptr [ebp - 0x30]
008c9411 movss dword ptr [edi + 0x494], xmm2
008c9419 movss dword ptr [edi + 0x498], xmm0
008c9421 movss xmm0, dword ptr [ebp - 0x2c]
008c9426 movss dword ptr [edi + 0x49c], xmm0
008c942e movss xmm0, dword ptr [ebp - 0x18]
008c9433 movss dword ptr [edi + 0x4a0], xmm0
008c943b movss dword ptr [edi + 0x4a4], xmm1
008c9443 jmp 0x8c9472
008c9445 push 0xbc4940
008c944a lea edx, [edi + 0x378]
008c9450 lea ecx, [ebp - 0xc0]
008c9456 call 0x412050
008c945b add esp, 4
008c945e mov ecx, dword ptr [eax]
008c9460 or ecx, dword ptr [eax + 4]
008c9463 jne 0x8c93f5
008c9465 mov ecx, dword ptr [eax + 8]
008c9468 or ecx, dword ptr [eax + 0xc]
008c946b jne 0x8c93f5
008c946d movss xmm1, dword ptr [ebp - 0x14]
008c9472 movss xmm2, dword ptr [ebp - 0x3c]
008c9477 addss xmm2, dword ptr [0xb6a9c8]
008c947f movss xmm0, dword ptr [edi + 0x2c8]
008c9487 movss xmm3, dword ptr [ebp - 0x1c]
008c948c movss xmm4, dword ptr [ebp - 0x20]
008c9491 comiss xmm0, xmm2
008c9494 movss dword ptr [ebp - 0x3c], xmm2
008c9499 ja 0x8c9160
008c949f mov esi, dword ptr [ebp - 0x6c]
008c94a2 movss xmm1, dword ptr [ebp - 0x24]
008c94a7 movaps xmm0, xmm4
008c94aa addss xmm1, dword ptr [ebp - 0x44]
008c94af mov edx, dword ptr [ebp - 0x48]
008c94b2 mov eax, dword ptr [ebx + 0xc]
008c94b5 inc edx
008c94b6 movss dword ptr [ebp - 0x40], xmm0
008c94bb movss dword ptr [ebp - 0x74], xmm0
008c94c0 movaps xmm0, xmm3
008c94c3 movss dword ptr [ebp - 0x28], xmm0
008c94c8 movss dword ptr [ebp - 0x70], xmm0
008c94cd movss dword ptr [ebp - 0x24], xmm1
008c94d2 mov dword ptr [ebp - 0x48], edx
008c94d5 cmp edx, esi
008c94d7 jbe 0x8c8fe5
008c94dd mov eax, dword ptr [ebp - 0x38]
008c94e0 mov esi, dword ptr [eax]
008c94e2 cmp esi, eax
008c94e4 je 0x8c9536
008c94e6 lea eax, [esi + 0x14]
008c94e9 push eax
008c94ea push ecx
008c94eb push dword ptr [esi + 0x10]
008c94ee mov ecx, edi
008c94f0 call 0x8c97a0
008c94f5 mov eax, dword ptr [esi + 8]
008c94f8 cmp byte ptr [eax + 0xd], 0
008c94fc je 0x8c951b
008c94fe mov eax, dword ptr [esi + 4]
008c9501 cmp byte ptr [eax + 0xd], 0
008c9505 jne 0x8c9517
008c9507 cmp esi, dword ptr [eax + 8]
008c950a jne 0x8c9517
008c950c mov esi, eax
008c950e mov eax, dword ptr [eax + 4]
008c9511 cmp byte ptr [eax + 0xd], 0
008c9515 je 0x8c9507
008c9517 mov esi, eax
008c9519 jmp 0x8c9531
008c951b mov esi, eax
008c951d mov ecx, dword ptr [esi]
008c951f cmp byte ptr [ecx + 0xd], 0
008c9523 jne 0x8c9531
008c9525 mov eax, dword ptr [ecx]
008c9527 mov esi, ecx
008c9529 mov ecx, eax
008c952b cmp byte ptr [eax + 0xd], 0
008c952f je 0x8c9525
008c9531 cmp esi, dword ptr [ebp - 0x38]
008c9534 jne 0x8c94e6
008c9536 push ecx
008c9537 mov ecx, dword ptr [0xbfd65c]
008c953d lea eax, [ebp - 0x74]
008c9540 mov dword ptr [esp], 0
008c9547 push eax
008c9548 mov ecx, dword ptr [ecx + 0x18190]
008c954e call 0x7cf0a0
008c9553 test al, al
008c9555 jne 0x8c95b7
008c9557 movss xmm0, dword ptr [edi + 0x494]
008c955f movss xmm1, dword ptr [ebp - 0x4c]
008c9564 comiss xmm0, xmm1
008c9567 jbe 0x8c95b7
008c9569 mov eax, dword ptr [edi + 0x30]
008c956c cmp eax, 1
008c956f je 0x8c95b7
008c9571 cmp eax, 2
008c9574 je 0x8c95b7
008c9576 cmp eax, 3
008c9579 je 0x8c95b7
008c957b movss xmm0, dword ptr [ebp - 0x58]
008c9580 movss xmm2, dword ptr [ebp - 0x50]
008c9585 movss xmm3, dword ptr [ebp - 0x54]
008c958a movss dword ptr [edi + 0x4a0], xmm0
008c9592 movss xmm0, dword ptr [ebp - 0x5c]
008c9597 movss dword ptr [edi + 0x494], xmm1
008c959f movss dword ptr [edi + 0x498], xmm2
008c95a7 movss dword ptr [edi + 0x49c], xmm3
008c95af movss dword ptr [edi + 0x4a4], xmm0
008c95b7 mov eax, dword ptr [ebp - 0x38]
008c95ba push dword ptr [eax + 4]
008c95bd lea eax, [ebp - 0x38]
008c95c0 push eax
008c95c1 mov ecx, eax
008c95c3 call 0x62ee90
008c95c8 push 0x1c
008c95ca push dword ptr [ebp - 0x38]
008c95cd call 0x9eb08e
008c95d2 add esp, 8
008c95d5 jmp 0x8c9783
008c95da movss xmm0, dword ptr [edi + 0x36c]
008c95e2 mulss xmm0, dword ptr [0xb6a230]
008c95ea movss dword ptr [ebp - 0x44], xmm0
008c95ef call 0x411fe0
008c95f4 movss dword ptr [ebp - 0x20], xmm0
008c95f9 movss xmm0, dword ptr [ebp - 0x44]
008c95fe call 0x412010
008c9603 mov ecx, dword ptr [edi + 0x314]
008c9609 movaps xmm7, xmm0
008c960c movss dword ptr [ebp - 0x1c], xmm7
008c9611 test ecx, ecx
008c9613 je 0x8c963e
008c9615 mov eax, dword ptr [ecx + 0x28]
008c9618 cmp eax, 2
008c961b jne 0x8c9625
008c961d cmp dword ptr [ecx + 0x34], 1
008c9621 jne 0x8c963e
008c9623 jmp 0x8c964f
008c9625 cmp eax, 0x3e8
008c962a jne 0x8c9634
008c962c cmp dword ptr [ecx + 0x34], 1
008c9630 jne 0x8c963e
008c9632 jmp 0x8c964f
008c9634 cmp eax, 1
008c9637 je 0x8c964f
008c9639 cmp eax, 3
008c963c je 0x8c964f
008c963e mov eax, dword ptr [edi + 0x34]
008c9641 cmp eax, 1
008c9644 je 0x8c964f
008c9646 cmp eax, 3
008c9649 jne 0x8c9783
008c964f mov ecx, dword ptr [0xbfd65c]
008c9655 xor esi, esi
008c9657 mov ecx, dword ptr [ecx + 0x18190]
008c965d mov eax, dword ptr [ecx + 0x10]
008c9660 imul eax, dword ptr [ecx + 0xc]
008c9664 test eax, eax
008c9666 jle 0x8c9783
008c966c movss xmm0, dword ptr [0xb6aa3c]
008c9674 mov eax, 0x24
008c9679 mov dword ptr [ebp - 0x28], eax
008c967c nop dword ptr [eax]
008c9680 cmp esi, 0x1bf
008c9686 ja 0x8c9761
008c968c cmp dword ptr [ecx + eax], 0
008c9690 je 0x8c9761
008c9696 mov ecx, dword ptr [ecx + 0xc]
008c9699 mov eax, esi
008c969b cdq 
008c969c xorps xmm2, xmm2
008c969f idiv ecx
008c96a1 mov ecx, dword ptr [ebx + 0xc]
008c96a4 xorps xmm1, xmm1
008c96a7 movss xmm4, dword ptr [edi + 0x420]
008c96af xorps xmm3, xmm3
008c96b2 comiss xmm3, xmm4
008c96b5 cvtsi2ss xmm2, edx
008c96b9 cvtsi2ss xmm1, eax
008c96bd mulss xmm2, xmm0
008c96c1 mulss xmm1, xmm0
008c96c5 addss xmm2, xmm0
008c96c9 movss xmm0, dword ptr [edi + 0x2c8]
008c96d1 movaps xmm5, xmm0
008c96d4 addss xmm1, dword ptr [0xb6ab20]
008c96dc addss xmm5, dword ptr [0xb6a9ac]
008c96e4 subss xmm2, dword ptr [edi + 0x294]
008c96ec subss xmm1, dword ptr [edi + 0x298]
008c96f4 addss xmm2, dword ptr [ecx]
008c96f8 addss xmm1, dword ptr [ecx + 4]
008c96fd jb 0x8c9709
008c96ff movss xmm4, dword ptr [0xb6adc4]
008c9707 jmp 0x8c970d
008c9709 addss xmm4, xmm0
008c970d movaps xmm3, xmm1
008c9710 movaps xmm0, xmm2
008c9713 mulss xmm1, dword ptr [ebp - 0x20]
008c9718 mulss xmm0, dword ptr [ebp - 0x20]
008c971d mulss xmm2, xmm7
008c9721 mulss xmm3, xmm7
008c9725 addss xmm1, xmm2
008c9729 addss xmm3, xmm0
008c972d andps xmm1, xmmword ptr [0xb6c980]
008c9734 comiss xmm5, xmm1
008c9737 jbe 0x8c9759
008c9739 comiss xmm3, dword ptr [0xb6a18c]
008c9740 jbe 0x8c9759
008c9742 comiss xmm4, xmm3
008c9745 jb 0x8c9759
008c9747 lea eax, [ebp - 0x20]
008c974a push eax
008c974b push ecx
008c974c push esi
008c974d mov ecx, edi
008c974f call 0x8c97a0
008c9754 movss xmm7, dword ptr [ebp - 0x1c]
008c9759 movss xmm0, dword ptr [0xb6aa3c]
008c9761 mov eax, dword ptr [0xbfd65c]
008c9766 inc esi
008c9767 add dword ptr [ebp - 0x28], 4
008c976b mov ecx, dword ptr [eax + 0x18190]
008c9771 mov eax, dword ptr [ecx + 0x10]
008c9774 imul eax, dword ptr [ecx + 0xc]
008c9778 cmp esi, eax
008c977a mov eax, dword ptr [ebp - 0x28]
008c977d jl 0x8c9680
008c9783 mov ecx, dword ptr [ebp - 0xc]
008c9786 mov dword ptr fs:[0], ecx
008c978d pop ecx
008c978e pop edi
008c978f pop esi
008c9790 mov esp, ebp
008c9792 pop ebp
008c9793 mov esp, ebx
008c9795 pop ebx
008c9796 ret 8
008c9799 int3 
008c979a int3 
008c979b int3 
008c979c int3 
008c979d int3 
008c979e int3 
008c979f int3 
008c97a0 push ebp
008c97a1 mov ebp, esp
008c97a3 sub esp, 0xa8
008c97a9 mov eax, dword ptr [0xbaa3b4]
008c97ae xor eax, ebp
008c97b0 mov dword ptr [ebp - 8], eax
008c97b3 push ebx
008c97b4 push esi
008c97b5 mov esi, dword ptr [ebp + 8]
008c97b8 push edi
008c97b9 mov edi, ecx
008c97bb xor cl, cl
008c97bd cmp esi, 0x1bf
008c97c3 ja 0x8c99d6
008c97c9 mov eax, dword ptr [0xbfd65c]
008c97ce mov eax, dword ptr [eax + 0x18190]
008c97d4 mov esi, dword ptr [eax + esi*4 + 0x24]
008c97d8 test esi, esi
008c97da je 0x8c99d6
008c97e0 mov eax, dword ptr [esi + 0x3c]
008c97e3 cmp eax, 1
008c97e6 je 0x8c99b8
008c97ec test eax, eax
008c97ee je 0x8c99b8
008c97f4 call 0x6c3d90
008c97f9 test al, 3
008c97fb jne 0x8c99b8
008c9801 movups xmm0, xmmword ptr [edi + 0x378]
008c9808 mov eax, dword ptr [edi + 0x320]
008c980e movups xmmword ptr [ebp - 0x84], xmm0
008c9815 test eax, eax
008c9817 je 0x8c9870
008c9819 cmp dword ptr [eax + 0x28], 1
008c981d jne 0x8c9823
008c981f mov ecx, eax
008c9821 jmp 0x8c983d
008c9823 test eax, eax
008c9825 je 0x8c9870
008c9827 cmp dword ptr [eax + 0x28], 3
008c982b jne 0x8c9870
008c982d cmp dword ptr [eax + 0x2c], 0x50
008c9831 jne 0x8c9870
008c9833 mov ecx, dword ptr [eax + 0x360]
008c9839 test ecx, ecx
008c983b je 0x8c9870
008c983d push eax
008c983e push 0
008c9840 push ecx
008c9841 mov dword ptr [esp], 0x3f800000
008c9848 lea eax, [ebp - 0x74]
008c984b push 3
008c984d push eax
008c984e call 0x7836a0
008c9853 mov ecx, eax
008c9855 mov eax, dword ptr [ecx + 0x38]
008c9858 or dword ptr [ebp - 0x84], eax
008c985e mov eax, dword ptr [ecx + 0x3c]
008c9861 or dword ptr [ebp - 0x80], eax
008c9864 mov eax, dword ptr [ecx + 0x40]
008c9867 or dword ptr [ebp - 0x7c], eax
008c986a mov eax, dword ptr [ecx + 0x44]
008c986d or dword ptr [ebp - 0x78], eax
008c9870 push 0xbc4640
008c9875 mov edx, 0xbc4b00
008c987a lea ecx, [ebp - 0xa4]
008c9880 call 0x427220
008c9885 add esp, 4
008c9888 lea edx, [ebp - 0x84]
008c988e lea ecx, [ebp - 0x94]
008c9894 push eax
008c9895 call 0x412050
008c989a add esp, 4
008c989d mov ecx, eax
008c989f call 0x412090
008c98a4 test al, al
008c98a6 je 0x8c99b8
008c98ac mov eax, dword ptr [esi]
008c98ae mov ecx, esi
008c98b0 mov eax, dword ptr [eax + 0x1c]
008c98b3 call eax
008c98b5 test al, al
008c98b7 je 0x8c99b8
008c98bd mov eax, dword ptr [esi]
008c98bf mov ecx, esi
008c98c1 push 0
008c98c3 mov eax, dword ptr [eax + 0x14]
008c98c6 call eax
008c98c8 test al, al
008c98ca je 0x8c99b8
008c98d0 mov edx, dword ptr [ebp + 0x10]
008c98d3 lea ecx, [ebp - 0x8c]
008c98d9 mov bl, 1
008c98db call 0x6593a0
008c98e0 movss xmm0, dword ptr [ebp - 0x8c]
008c98e8 ucomiss xmm0, dword ptr [0xc02fec]
008c98ef movss xmm0, dword ptr [ebp - 0x88]
008c98f7 lahf 
008c98f8 test ah, 0x44
008c98fb jp 0x8c990e
008c98fd ucomiss xmm0, dword ptr [0xc02ff0]
008c9904 lahf 
008c9905 test ah, 0x44
008c9908 jnp 0x8c99a3
008c990e lea eax, [ebp - 0x7c]
008c9911 mov ecx, esi
008c9913 push eax
008c9914 call 0x6dae90
008c9919 movss xmm1, dword ptr [ebp - 0x8c]
008c9921 mulss xmm1, dword ptr [0xb6aa3c]
008c9929 addss xmm1, dword ptr [eax]
008c992d movss dword ptr [ebp - 0x9c], xmm1
008c9935 movss xmm1, dword ptr [ebp - 0x88]
008c993d mulss xmm1, dword ptr [0xb6aa3c]
008c9945 addss xmm1, dword ptr [eax + 4]
008c994a mov eax, dword ptr [0xbfd65c]
008c994f mov edi, dword ptr [eax + 0x18190]
008c9955 lea eax, [ebp - 0x9c]
008c995b push eax
008c995c mov ecx, edi
008c995e movss dword ptr [ebp - 0x98], xmm1
008c9966 call 0x7ce950
008c996b test eax, eax
008c996d js 0x8c99a3
008c996f cmp eax, 0x1c0
008c9974 jge 0x8c9998
008c9976 mov eax, dword ptr [edi + eax*4 + 0x24]
008c997a mov ecx, edi
008c997c push esi
008c997d push eax
008c997e call 0x7d9890
008c9983 mov al, bl
008c9985 pop edi
008c9986 pop esi
008c9987 pop ebx
008c9988 mov ecx, dword ptr [ebp - 8]
008c998b xor ecx, ebp
008c998d call 0x9eacd7
008c9992 mov esp, ebp
008c9994 pop ebp
008c9995 ret 0xc
008c9998 xor eax, eax
008c999a mov ecx, edi
008c999c push esi
008c999d push eax
008c999e call 0x7d9890
008c99a3 mov al, bl
008c99a5 pop edi
008c99a6 pop esi
008c99a7 pop ebx
008c99a8 mov ecx, dword ptr [ebp - 8]
008c99ab xor ecx, ebp
008c99ad call 0x9eacd7
008c99b2 mov esp, ebp
008c99b4 pop ebp
008c99b5 ret 0xc
008c99b8 mov eax, dword ptr [esi]
008c99ba mov ecx, esi
008c99bc push 1
008c99be mov eax, dword ptr [eax + 0x10]
008c99c1 call eax
008c99c3 pop edi
008c99c4 pop esi
008c99c5 pop ebx
008c99c6 mov ecx, dword ptr [ebp - 8]
008c99c9 xor ecx, ebp
008c99cb call 0x9eacd7
008c99d0 mov esp, ebp
008c99d2 pop ebp
008c99d3 ret 0xc
008c99d6 mov al, cl
008c99d8 mov ecx, dword ptr [ebp - 8]
008c99db pop edi
008c99dc pop esi
008c99dd xor ecx, ebp
008c99df pop ebx
008c99e0 call 0x9eacd7
008c99e5 mov esp, ebp
008c99e7 pop ebp
008c99e8 ret 0xc
008c99eb int3 
008c99ec int3 
008c99ed int3 
008c99ee int3 
008c99ef int3 
008c99f0 push ebx
008c99f1 mov ebx, esp
008c99f3 sub esp, 8
008c99f6 and esp, 0xfffffff0
008c99f9 add esp, 4
008c99fc push ebp
008c99fd mov ebp, dword ptr [ebx + 4]
008c9a00 mov dword ptr [esp + 4], ebp
008c9a04 mov ebp, esp
008c9a06 push -1
008c9a08 push 0x9ff7b0
008c9a0d mov eax, dword ptr fs:[0]
008c9a13 push eax
008c9a14 push ebx
008c9a15 sub esp, 0x2b8
008c9a1b mov eax, dword ptr [0xbaa3b4]
008c9a20 xor eax, ebp
008c9a22 mov dword ptr [ebp - 0x14], eax
008c9a25 push esi
008c9a26 push edi
008c9a27 push eax
008c9a28 lea eax, [ebp - 0xc]
008c9a2b mov dword ptr fs:[0], eax
008c9a31 movss dword ptr [ebp - 0xcc], xmm1
008c9a39 mov edi, ecx
008c9a3b mov dword ptr [ebp - 0x74], edi
008c9a3e cmp byte ptr [edi + 0x3ad], 0
008c9a45 je 0x8cb72d
008c9a4b mov dword ptr [ebp - 0xb4], 0
008c9a55 mov dword ptr [ebp - 0xb0], 0
008c9a5f mov dword ptr [ebp - 0xac], 0
008c9a69 push 0xa
008c9a6b lea ecx, [ebp - 0xb4]
008c9a71 mov dword ptr [ebp - 4], 0
008c9a78 call 0x4309f0
008c9a7d lea eax, [edi + 0x378]
008c9a83 push 0xbc4cf0
008c9a88 mov edx, eax
008c9a8a mov dword ptr [ebp - 0x94], eax
008c9a90 lea ecx, [ebp - 0x1b0]
008c9a96 call 0x412050
008c9a9b add esp, 4
008c9a9e mov ecx, dword ptr [eax]
008c9aa0 or ecx, dword ptr [eax + 4]
008c9aa3 jne 0x8c9ab4
008c9aa5 mov ecx, dword ptr [eax + 8]
008c9aa8 or ecx, dword ptr [eax + 0xc]
008c9aab mov byte ptr [ebp - 0xa1], 0
008c9ab2 je 0x8c9abb
008c9ab4 mov byte ptr [ebp - 0xa1], 1
008c9abb mov eax, dword ptr [0xbfd65c]
008c9ac0 xor ecx, ecx
008c9ac2 mov esi, dword ptr [ebp - 0xb0]
008c9ac8 mov dword ptr [ebp - 0x78], ecx
008c9acb mov eax, dword ptr [eax + 0x18190]
008c9ad1 mov dword ptr [ebp - 0xb8], eax
008c9ad7 cmp dword ptr [eax + 0x1264], ecx
008c9add jbe 0x8c9fd0
008c9ae3 nop dword ptr [eax]
008c9ae7 nop word ptr [eax + eax]
008c9af0 mov eax, dword ptr [eax + 0x125c]
008c9af6 mov eax, dword ptr [eax + ecx*4]
008c9af9 mov dword ptr [ebp - 0x88], eax
008c9aff mov dword ptr [ebp - 0x84], eax
008c9b05 mov ecx, dword ptr [eax + 0x28]
008c9b08 mov dword ptr [ebp - 0xa0], ecx
008c9b0e cmp ecx, 0x3e8
008c9b14 jne 0x8c9bc1
008c9b1a mov ecx, dword ptr [eax + 0x2c]
008c9b1d cmp ecx, 0x15
008c9b20 je 0x8c9b3d
008c9b22 cmp ecx, 0x21
008c9b25 je 0x8c9b3d
008c9b27 cmp ecx, 0x3f
008c9b2a je 0x8c9b3d
008c9b2c cmp ecx, 0x40
008c9b2f je 0x8c9b3d
008c9b31 cmp ecx, 0x9f
008c9b37 jne 0x8c9bc1
008c9b3d cmp esi, dword ptr [ebp - 0xac]
008c9b43 jne 0x8c9c9e
008c9b49 lea eax, [ebp - 0x84]
008c9b4f push eax
008c9b50 push esi
008c9b51 lea ecx, [ebp - 0xb4]
008c9b57 call 0x426fb0
008c9b5c mov esi, dword ptr [ebp - 0xb0]
008c9b62 push 0xbc4b80
008c9b67 lea edx, [edi + 0x378]
008c9b6d lea ecx, [ebp - 0x1b0]
008c9b73 call 0x412050
008c9b78 add esp, 4
008c9b7b mov ecx, dword ptr [eax]
008c9b7d or ecx, dword ptr [eax + 4]
008c9b80 jne 0x8c9b8e
008c9b82 mov ecx, dword ptr [eax + 8]
008c9b85 or ecx, dword ptr [eax + 0xc]
008c9b88 je 0x8c9fb7
008c9b8e mov ecx, dword ptr [ebp - 0x88]
008c9b94 push 0
008c9b96 call 0x684630
008c9b9b mov edx, dword ptr [ebp - 0x88]
008c9ba1 test al, al
008c9ba3 jne 0x8c9cae
008c9ba9 cmp dword ptr [edx + 0x28], 5
008c9bad jne 0x8c9fb7
008c9bb3 mov eax, dword ptr [edx + 0x28]
008c9bb6 mov dword ptr [ebp - 0x98], eax
008c9bbc jmp 0x8c9cbc
008c9bc1 push eax
008c9bc2 mov ecx, edi
008c9bc4 call 0x8c5a90
008c9bc9 test al, al
008c9bcb jne 0x8c9c8c
008c9bd1 mov edx, dword ptr [ebp - 0xa0]
008c9bd7 cmp edx, 4
008c9bda jne 0x8c9c22
008c9bdc mov ecx, dword ptr [edi + 0x314]
008c9be2 test ecx, ecx
008c9be4 je 0x8c9c15
008c9be6 mov eax, dword ptr [ecx + 0x28]
008c9be9 cmp eax, 2
008c9bec jne 0x8c9bf9
008c9bee cmp dword ptr [ecx + 0x34], 1
008c9bf2 jne 0x8c9c15
008c9bf4 jmp 0x8c9c8c
008c9bf9 cmp eax, 0x3e8
008c9bfe jne 0x8c9c0b
008c9c00 cmp dword ptr [ecx + 0x34], 1
008c9c04 jne 0x8c9c15
008c9c06 jmp 0x8c9c8c
008c9c0b cmp eax, 1
008c9c0e je 0x8c9c8c
008c9c10 cmp eax, 3
008c9c13 je 0x8c9c8c
008c9c15 mov eax, dword ptr [edi + 0x34]
008c9c18 cmp eax, 1
008c9c1b je 0x8c9c8c
008c9c1d cmp eax, 3
008c9c20 je 0x8c9c8c
008c9c22 cmp byte ptr [ebp - 0xa1], 0
008c9c29 je 0x8c9b62
008c9c2f cmp edx, 9
008c9c32 jne 0x8c9b62
008c9c38 mov eax, dword ptr [ebp - 0x88]
008c9c3e mov eax, dword ptr [eax + 0x388]
008c9c44 and eax, 0x80000000
008c9c49 or eax, 0
008c9c4c jne 0x8c9b62
008c9c52 mov eax, dword ptr [edi + 0x30]
008c9c55 cmp eax, 1
008c9c58 je 0x8c9c64
008c9c5a cmp eax, 2
008c9c5d je 0x8c9c64
008c9c5f cmp eax, 3
008c9c62 jne 0x8c9c76
008c9c64 call 0x6c3d90
008c9c69 xor edx, edx
008c9c6b mov ecx, 0x32
008c9c70 div ecx
008c9c72 test edx, edx
008c9c74 je 0x8c9c8c
008c9c76 call 0x6c3d90
008c9c7b xor edx, edx
008c9c7d mov ecx, 5
008c9c82 div ecx
008c9c84 test edx, edx
008c9c86 jne 0x8c9b62
008c9c8c cmp esi, dword ptr [ebp - 0xac]
008c9c92 je 0x8c9b49
008c9c98 mov eax, dword ptr [ebp - 0x88]
008c9c9e mov dword ptr [esi], eax
008c9ca0 add esi, 4
008c9ca3 mov dword ptr [ebp - 0xb0], esi
008c9ca9 jmp 0x8c9b62
008c9cae mov eax, dword ptr [edx + 0x28]
008c9cb1 mov dword ptr [ebp - 0x98], eax
008c9cb7 cmp eax, 5
008c9cba jne 0x8c9cdf
008c9cbc cmp dword ptr [edx + 0x480], 0
008c9cc3 jne 0x8c9fb7
008c9cc9 mov ecx, dword ptr [edx + 0x2c]
008c9ccc call 0x6c3350
008c9cd1 test al, al
008c9cd3 je 0x8c9cdf
008c9cd5 cmp dword ptr [edx + 0x30], 0
008c9cd9 je 0x8c9fb7
008c9cdf mov eax, dword ptr [edi + 0x3d4]
008c9ce5 mov ecx, dword ptr [edi + 0x3d0]
008c9ceb sub eax, ecx
008c9ced movss xmm2, dword ptr [0xb6ada0]
008c9cf5 movss xmm1, dword ptr [0xc02fec]
008c9cfd movss xmm4, dword ptr [0xc02ff0]
008c9d05 sar eax, 3
008c9d08 add eax, -1
008c9d0b movss dword ptr [ebp - 0x8c], xmm2
008c9d13 movss dword ptr [ebp - 0x84], xmm1
008c9d1b movss dword ptr [ebp - 0x7c], xmm4
008c9d20 mov dword ptr [ebp - 0x9c], 0
008c9d2a mov dword ptr [ebp - 0xa0], eax
008c9d30 je 0x8c9fb7
008c9d36 add ecx, 8
008c9d39 xorps xmm6, xmm6
008c9d3c nop dword ptr [eax]
008c9d40 movss xmm7, dword ptr [ecx]
008c9d44 movss xmm3, dword ptr [ecx + 4]
008c9d49 subss xmm3, dword ptr [ecx - 4]
008c9d4e subss xmm7, dword ptr [ecx - 8]
008c9d53 movss xmm5, dword ptr [edx + 0x294]
008c9d5b subss xmm5, dword ptr [ecx - 8]
008c9d60 movaps xmm2, xmm3
008c9d63 movss dword ptr [ebp - 0x70], xmm3
008c9d68 movaps xmm0, xmm7
008c9d6b mulss xmm2, xmm3
008c9d6f mulss xmm0, xmm7
008c9d73 addss xmm2, xmm0
008c9d77 movss dword ptr [ebp - 0x80], xmm2
008c9d7c movss xmm0, dword ptr [ebp - 0x80]
008c9d81 movss xmm2, dword ptr [edx + 0x298]
008c9d89 subss xmm2, dword ptr [ecx - 4]
008c9d8e ucomiss xmm0, xmm6
008c9d91 lahf 
008c9d92 test ah, 0x44
008c9d95 jnp 0x8c9db0
008c9d97 movaps xmm0, xmm7
008c9d9a mulss xmm3, xmm2
008c9d9e mulss xmm0, xmm5
008c9da2 addss xmm3, xmm0
008c9da6 divss xmm3, dword ptr [ebp - 0x80]
008c9dab comiss xmm6, xmm3
008c9dae jbe 0x8c9dc9
008c9db0 mulss xmm5, xmm5
008c9db4 movaps xmm3, xmm6
008c9db7 mulss xmm2, xmm2
008c9dbb addss xmm2, xmm5
008c9dbf movss xmm5, dword ptr [ebp - 0x70]
008c9dc4 jmp 0x8c9e46
008c9dc9 movss xmm5, dword ptr [0xb6a614]
008c9dd1 comiss xmm3, xmm5
008c9dd4 movss xmm2, dword ptr [edx + 0x298]
008c9ddc jbe 0x8c9e05
008c9dde movss xmm0, dword ptr [edx + 0x294]
008c9de6 movaps xmm3, xmm5
008c9de9 subss xmm2, dword ptr [ecx + 4]
008c9dee subss xmm0, dword ptr [ecx]
008c9df2 movss xmm5, dword ptr [ebp - 0x70]
008c9df7 mulss xmm2, xmm2
008c9dfb mulss xmm0, xmm0
008c9dff addss xmm2, xmm0
008c9e03 jmp 0x8c9e46
008c9e05 movss xmm1, dword ptr [edx + 0x294]
008c9e0d movaps xmm0, xmm7
008c9e10 movss xmm5, dword ptr [ebp - 0x70]
008c9e15 mulss xmm0, xmm3
008c9e19 addss xmm0, dword ptr [ecx - 8]
008c9e1e subss xmm1, xmm0
008c9e22 movaps xmm0, xmm5
008c9e25 mulss xmm0, xmm3
008c9e29 addss xmm0, dword ptr [ecx - 4]
008c9e2e mulss xmm1, xmm1
008c9e32 subss xmm2, xmm0
008c9e36 mulss xmm2, xmm2
008c9e3a addss xmm2, xmm1
008c9e3e movss xmm1, dword ptr [ebp - 0x84]
008c9e46 movss xmm0, dword ptr [0xb6ad60]
008c9e4e comiss xmm0, xmm2
008c9e51 jbe 0x8c9e9d
008c9e53 movss xmm0, dword ptr [ebp - 0x8c]
008c9e5b comiss xmm0, xmm2
008c9e5e jbe 0x8c9e9d
008c9e60 movaps xmm1, xmm7
008c9e63 movss dword ptr [ebp - 0x8c], xmm2
008c9e6b movaps xmm4, xmm5
008c9e6e mulss xmm1, xmm3
008c9e72 mulss xmm4, xmm3
008c9e76 addss xmm1, dword ptr [ecx - 8]
008c9e7b addss xmm4, dword ptr [ecx - 4]
008c9e80 subss xmm1, dword ptr [edx + 0x294]
008c9e88 subss xmm4, dword ptr [edx + 0x298]
008c9e90 movss dword ptr [ebp - 0x84], xmm1
008c9e98 movss dword ptr [ebp - 0x7c], xmm4
008c9e9d ucomiss xmm1, dword ptr [0xc02fec]
008c9ea4 lahf 
008c9ea5 test ah, 0x44
008c9ea8 jp 0x8c9ed8
008c9eaa ucomiss xmm4, dword ptr [0xc02ff0]
008c9eb1 lahf 
008c9eb2 test ah, 0x44
008c9eb5 jp 0x8c9ed8
008c9eb7 mov eax, dword ptr [ebp - 0x9c]
008c9ebd add ecx, 8
008c9ec0 inc eax
008c9ec1 mov dword ptr [ebp - 0x9c], eax
008c9ec7 cmp eax, dword ptr [ebp - 0xa0]
008c9ecd jb 0x8c9d40
008c9ed3 jmp 0x8c9fb7
008c9ed8 mulss xmm1, dword ptr [ebp - 0x84]
008c9ee0 movaps xmm0, xmm4
008c9ee3 mulss xmm0, xmm4
008c9ee7 addss xmm0, xmm1
008c9eeb call 0x4228c0
008c9ef0 movss xmm1, dword ptr [ebp - 0x84]
008c9ef8 movaps xmm3, xmm0
008c9efb movss xmm2, dword ptr [ebp - 0x7c]
008c9f00 xorps xmm6, xmm6
008c9f03 comiss xmm3, xmm6
008c9f06 jbe 0x8c9f1c
008c9f08 movss xmm0, dword ptr [0xb6a614]
008c9f10 divss xmm0, xmm3
008c9f14 mulss xmm1, xmm0
008c9f18 mulss xmm2, xmm0
008c9f1c movss xmm4, dword ptr [0xb6a974]
008c9f24 mov eax, dword ptr [ebp - 0x98]
008c9f2a movaps xmm0, xmm4
008c9f2d cmp eax, 0xa
008c9f30 jl 0x8c9f41
008c9f32 cmp eax, 0x3e8
008c9f37 jge 0x8c9f41
008c9f39 movss xmm0, dword ptr [0xb6aa3c]
008c9f41 comiss xmm4, xmm3
008c9f44 mov ecx, dword ptr [ebp - 0x88]
008c9f4a mulss xmm1, xmm0
008c9f4e mulss xmm2, xmm0
008c9f52 jbe 0x8c9f66
008c9f54 divss xmm3, dword ptr [0xb6aafc]
008c9f5c mulss xmm1, xmm3
008c9f60 mulss xmm2, xmm3
008c9f64 jmp 0x8c9f6e
008c9f66 divss xmm1, xmm3
008c9f6a divss xmm2, xmm3
008c9f6e movss xmm3, dword ptr [ecx + 0x2c4]
008c9f76 ucomiss xmm3, xmm6
008c9f79 lahf 
008c9f7a test ah, 0x44
008c9f7d jnp 0x8c9fb7
008c9f7f movss xmm0, dword ptr [ecx + 0x2f4]
008c9f87 mulss xmm2, xmm0
008c9f8b mulss xmm1, xmm0
008c9f8f divss xmm2, xmm3
008c9f93 divss xmm1, xmm3
008c9f97 addss xmm2, dword ptr [ecx + 0x2bc]
008c9f9f addss xmm1, dword ptr [ecx + 0x2b8]
008c9fa7 movss dword ptr [ecx + 0x2bc], xmm2
008c9faf movss dword ptr [ecx + 0x2b8], xmm1
008c9fb7 mov ecx, dword ptr [ebp - 0x78]
008c9fba mov eax, dword ptr [ebp - 0xb8]
008c9fc0 inc ecx
008c9fc1 mov dword ptr [ebp - 0x78], ecx
008c9fc4 cmp ecx, dword ptr [eax + 0x1264]
008c9fca jb 0x8c9af0
008c9fd0 mov ecx, dword ptr [ebp - 0xb4]
008c9fd6 mov edi, ecx
008c9fd8 mov dword ptr [ebp - 0xa0], ecx
008c9fde cmp edi, esi
008c9fe0 je 0x8cb709
008c9fe6 mov edx, dword ptr [ebp - 0x74]
008c9fe9 xorps xmm3, xmm3
008c9fec nop dword ptr [eax]
008c9ff0 mov eax, dword ptr [edx + 0x3d4]
008c9ff6 xor ecx, ecx
008c9ff8 mov dword ptr [ebp - 0xb8], eax
008c9ffe mov eax, dword ptr [edx + 0x3d0]
008ca004 mov dword ptr [ebp - 0x7c], eax
008ca007 mov eax, dword ptr [edx + 0x3d4]
008ca00d sub eax, dword ptr [edx + 0x3d0]
008ca013 sar eax, 3
008ca016 add eax, -1
008ca019 movss dword ptr [ebp - 0x80], xmm3
008ca01e mov dword ptr [ebp - 0x88], ecx
008ca024 mov dword ptr [ebp - 0x90], eax
008ca02a je 0x8cb6f2
008ca030 mov eax, dword ptr [edi]
008ca032 mov dword ptr [ebp - 0x70], eax
008ca035 movss xmm0, dword ptr [eax + 0x2c8]
008ca03d addss xmm0, dword ptr [edx + 0x2c8]
008ca045 mov eax, dword ptr [edx + 0x3d0]
008ca04b movss dword ptr [ebp - 0xbc], xmm0
008ca053 nop dword ptr [eax]
008ca057 nop word ptr [eax + eax]
008ca060 movss xmm0, dword ptr [eax + ecx*8 + 8]
008ca066 movss dword ptr [ebp - 0x98], xmm0
008ca06e movss xmm0, dword ptr [eax + ecx*8 + 0xc]
008ca074 mov ecx, edx
008ca076 movss dword ptr [ebp - 0x78], xmm0
008ca07b call 0x4275d0
008ca080 mov edx, dword ptr [ebp - 0x7c]
008ca083 mov ecx, dword ptr [ebp - 0x88]
008ca089 test al, al
008ca08b jne 0x8ca15f
008ca091 mov eax, dword ptr [ebp - 0xb8]
008ca097 sub eax, edx
008ca099 sar eax, 3
008ca09c sub eax, 2
008ca09f cmp ecx, eax
008ca0a1 jne 0x8ca15f
008ca0a7 mov eax, dword ptr [ebp - 0x74]
008ca0aa cmp byte ptr [eax + 0x466], 0
008ca0b1 jne 0x8ca15f
008ca0b7 xorps xmm0, xmm0
008ca0ba comiss xmm0, dword ptr [eax + 0x420]
008ca0c1 jb 0x8ca15f
008ca0c7 movss xmm1, dword ptr [ebp - 0x78]
008ca0cc subss xmm1, dword ptr [edx + ecx*8 + 4]
008ca0d2 movss xmm2, dword ptr [ebp - 0x98]
008ca0da subss xmm2, dword ptr [edx + ecx*8]
008ca0df movaps xmm0, xmm1
008ca0e2 movss dword ptr [ebp - 0x84], xmm1
008ca0ea mulss xmm0, xmm1
008ca0ee movaps xmm1, xmm2
008ca0f1 movss dword ptr [ebp - 0x8c], xmm2
008ca0f9 mulss xmm1, xmm2
008ca0fd addss xmm0, xmm1
008ca101 call 0x4228c0
008ca106 comiss xmm0, dword ptr [0xb6a18c]
008ca10d jbe 0x8ca130
008ca10f movss xmm1, dword ptr [0xb6aa3c]
008ca117 divss xmm1, xmm0
008ca11b movaps xmm0, xmm1
008ca11e mulss xmm1, dword ptr [ebp - 0x84]
008ca126 mulss xmm0, dword ptr [ebp - 0x8c]
008ca12e jmp 0x8ca140
008ca130 movss xmm0, dword ptr [ebp - 0x8c]
008ca138 movss xmm1, dword ptr [ebp - 0x84]
008ca140 addss xmm1, dword ptr [ebp - 0x78]
008ca145 movss xmm5, dword ptr [ebp - 0x98]
008ca14d mov ecx, dword ptr [ebp - 0x88]
008ca153 addss xmm5, xmm0
008ca157 mov edx, dword ptr [ebp - 0x7c]
008ca15a movaps xmm6, xmm1
008ca15d jmp 0x8ca16c
008ca15f movss xmm6, dword ptr [ebp - 0x78]
008ca164 movss xmm5, dword ptr [ebp - 0x98]
008ca16c mov eax, dword ptr [ebp - 0x70]
008ca16f movaps xmm1, xmm5
008ca172 subss xmm1, dword ptr [edx + ecx*8]
008ca177 movaps xmm7, xmm6
008ca17a subss xmm7, dword ptr [edx + ecx*8 + 4]
008ca180 movss xmm3, dword ptr [eax + 0x294]
008ca188 subss xmm3, dword ptr [edx + ecx*8]
008ca18d movaps xmm0, xmm1
008ca190 movss dword ptr [ebp - 0x78], xmm1
008ca195 mulss xmm0, xmm1
008ca199 movss xmm1, dword ptr [eax + 0x298]
008ca1a1 movaps xmm4, xmm7
008ca1a4 subss xmm1, dword ptr [edx + ecx*8 + 4]
008ca1aa mulss xmm4, xmm7
008ca1ae movss dword ptr [ebp - 0x98], xmm7
008ca1b6 addss xmm4, xmm0
008ca1ba xorps xmm0, xmm0
008ca1bd ucomiss xmm4, xmm0
008ca1c0 lahf 
008ca1c1 test ah, 0x44
008ca1c4 jnp 0x8ca1ed
008ca1c6 movaps xmm0, xmm3
008ca1c9 movaps xmm2, xmm1
008ca1cc mulss xmm0, dword ptr [ebp - 0x78]
008ca1d1 mulss xmm2, xmm7
008ca1d5 addss xmm2, xmm0
008ca1d9 xorps xmm0, xmm0
008ca1dc divss xmm2, xmm4
008ca1e0 comiss xmm0, xmm2
008ca1e3 movss dword ptr [ebp - 0x84], xmm2
008ca1eb jbe 0x8ca20e
008ca1ed mulss xmm1, xmm1
008ca1f1 mulss xmm3, xmm3
008ca1f5 movss dword ptr [ebp - 0x84], xmm0
008ca1fd addss xmm1, xmm3
008ca201 movss dword ptr [ebp - 0x9c], xmm1
008ca209 jmp 0x8ca29a
008ca20e movss xmm3, dword ptr [0xb6a614]
008ca216 comiss xmm2, xmm3
008ca219 mov eax, dword ptr [ebp - 0x70]
008ca21c jbe 0x8ca254
008ca21e movss xmm0, dword ptr [eax + 0x294]
008ca226 movss xmm1, dword ptr [eax + 0x298]
008ca22e subss xmm0, xmm5
008ca232 subss xmm1, xmm6
008ca236 movss dword ptr [ebp - 0x84], xmm3
008ca23e mulss xmm0, xmm0
008ca242 mulss xmm1, xmm1
008ca246 addss xmm1, xmm0
008ca24a movss dword ptr [ebp - 0x9c], xmm1
008ca252 jmp 0x8ca29a
008ca254 movss xmm1, dword ptr [eax + 0x294]
008ca25c movaps xmm0, xmm2
008ca25f mulss xmm0, dword ptr [ebp - 0x78]
008ca264 addss xmm0, dword ptr [edx + ecx*8]
008ca269 subss xmm1, xmm0
008ca26d movaps xmm0, xmm2
008ca270 movss xmm2, dword ptr [eax + 0x298]
008ca278 mulss xmm0, xmm7
008ca27c mulss xmm1, xmm1
008ca280 addss xmm0, dword ptr [edx + ecx*8 + 4]
008ca286 subss xmm2, xmm0
008ca28a mulss xmm2, xmm2
008ca28e addss xmm2, xmm1
008ca292 movss dword ptr [ebp - 0x9c], xmm2
008ca29a movaps xmm0, xmm4
008ca29d call 0x4228c0
008ca2a2 mov ecx, dword ptr [ebp - 0x88]
008ca2a8 movaps xmm2, xmm0
008ca2ab mov edx, dword ptr [ebp - 0x74]
008ca2ae movss dword ptr [ebp - 0x8c], xmm2
008ca2b6 test ecx, ecx
008ca2b8 jne 0x8ca3c8
008ca2be mov ecx, edx
008ca2c0 call 0x8c5940
008ca2c5 test al, al
008ca2c7 je 0x8ca3af
008ca2cd movss xmm0, dword ptr [edx + 0x36c]
008ca2d5 mulss xmm0, dword ptr [0xb6a230]
008ca2dd movss dword ptr [ebp - 0xc4], xmm0
008ca2e5 call 0x411fe0
008ca2ea mov eax, dword ptr [ebp - 0x7c]
008ca2ed mulss xmm0, dword ptr [0xb6a9b0]
008ca2f5 movss xmm1, dword ptr [eax]
008ca2f9 mov eax, dword ptr [ebp - 0x70]
008ca2fc subss xmm1, xmm0
008ca300 movss xmm0, dword ptr [ebp - 0xc4]
008ca308 subss xmm1, dword ptr [eax + 0x294]
008ca310 movss dword ptr [ebp - 0xc8], xmm1
008ca318 call 0x412010
008ca31d mulss xmm0, dword ptr [0xb6a9b0]
008ca325 xorps xmm3, xmm3
008ca328 mov eax, dword ptr [ebp - 0x7c]
008ca32b mov ecx, dword ptr [ebp - 0x70]
008ca32e movss xmm1, dword ptr [ebp - 0x9c]
008ca336 mov edx, dword ptr [ebp - 0x74]
008ca339 movss xmm2, dword ptr [eax + 4]
008ca33e subss xmm2, xmm0
008ca342 movss xmm0, dword ptr [ebp - 0xc8]
008ca34a mulss xmm0, xmm0
008ca34e subss xmm2, dword ptr [ecx + 0x298]
008ca356 mov ecx, dword ptr [ebp - 0x88]
008ca35c mulss xmm2, xmm2
008ca360 addss xmm2, xmm0
008ca364 comiss xmm1, xmm2
008ca367 jbe 0x8ca374
008ca369 movaps xmm1, xmm2
008ca36c movss dword ptr [ebp - 0x84], xmm3
008ca374 movss xmm2, dword ptr [ebp - 0x8c]
008ca37c movss xmm0, dword ptr [ebp - 0xbc]
008ca384 mulss xmm0, xmm0
008ca388 comiss xmm0, xmm1
008ca38b ja 0x8ca3d8
008ca38d addss xmm2, dword ptr [ebp - 0x80]
008ca392 inc ecx
008ca393 mov dword ptr [ebp - 0x88], ecx
008ca399 movss dword ptr [ebp - 0x80], xmm2
008ca39e cmp ecx, dword ptr [ebp - 0x90]
008ca3a4 jb 0x8ca060
008ca3aa jmp 0x8cb6f2
008ca3af movss xmm1, dword ptr [ebp - 0x9c]
008ca3b7 xorps xmm3, xmm3
008ca3ba mov ecx, dword ptr [ebp - 0x88]
008ca3c0 mov eax, dword ptr [edx + 0x3d0]
008ca3c6 jmp 0x8ca37c
008ca3c8 movss xmm1, dword ptr [ebp - 0x9c]
008ca3d0 xorps xmm3, xmm3
008ca3d3 mov eax, dword ptr [ebp - 0x7c]
008ca3d6 jmp 0x8ca37c
008ca3d8 mov ecx, dword ptr [ebp - 0x70]
008ca3db mov eax, dword ptr [ecx + 0x28]
008ca3de cmp eax, 9
008ca3e1 jne 0x8ca403
008ca3e3 mov dword ptr [ecx + 0x388], 0
008ca3ed mov dword ptr [ecx + 0x38c], 0
008ca3f7 mov byte ptr [ecx + 0x16b], 1
008ca3fe jmp 0x8cb6f2
008ca403 cmp eax, 0x3e8
008ca408 jne 0x8ca416
008ca40a mov byte ptr [ecx + 0x16b], 1
008ca411 jmp 0x8cb6f2
008ca416 movss xmm0, dword ptr [ecx + 0x2c8]
008ca41e mulss xmm0, xmm0
008ca422 movss dword ptr [ebp - 0x90], xmm0
008ca42a movaps xmm0, xmm1
008ca42d call 0x4228c0
008ca432 mov eax, dword ptr [ebp - 0x74]
008ca435 movaps xmm1, xmm0
008ca438 movss xmm0, dword ptr [ebp - 0x90]
008ca440 subss xmm1, dword ptr [eax + 0x2c8]
008ca448 mulss xmm1, xmm1
008ca44c comiss xmm0, xmm1
008ca44f jbe 0x8ca462
008ca451 subss xmm0, xmm1
008ca455 call 0x4228c0
008ca45a mov eax, dword ptr [ebp - 0x74]
008ca45d movaps xmm5, xmm0
008ca460 jmp 0x8ca465
008ca462 xorps xmm5, xmm5
008ca465 movss xmm0, dword ptr [ebp - 0x8c]
008ca46d movss xmm3, dword ptr [ebp - 0x78]
008ca472 movaps xmm4, xmm0
008ca475 mulss xmm4, dword ptr [ebp - 0x84]
008ca47d mov ecx, dword ptr [ebp - 0x88]
008ca483 divss xmm3, xmm0
008ca487 mov edx, dword ptr [eax + 0x3d0]
008ca48d movaps xmm2, xmm4
008ca490 subss xmm4, xmm5
008ca494 addss xmm2, dword ptr [ebp - 0x80]
008ca499 movss dword ptr [ebp - 0x78], xmm3
008ca49e movaps xmm6, xmm2
008ca4a1 movss dword ptr [ebp - 0x8c], xmm2
008ca4a9 movss xmm2, dword ptr [ebp - 0x98]
008ca4b1 subss xmm6, xmm5
008ca4b5 divss xmm2, xmm0
008ca4b9 movss xmm0, dword ptr [eax + 0x494]
008ca4c1 movaps xmm5, xmm4
008ca4c4 comiss xmm0, xmm6
008ca4c7 mulss xmm5, xmm3
008ca4cb mulss xmm4, xmm2
008ca4cf addss xmm5, dword ptr [edx + ecx*8]
008ca4d4 movss dword ptr [ebp - 0x98], xmm2
008ca4dc addss xmm4, dword ptr [edx + ecx*8 + 4]
008ca4e2 movss dword ptr [ebp - 0x70], xmm5
008ca4e7 movss dword ptr [ebp - 0x7c], xmm4
008ca4ec jbe 0x8ca516
008ca4ee movss dword ptr [eax + 0x494], xmm6
008ca4f6 movss dword ptr [eax + 0x498], xmm5
008ca4fe movss dword ptr [eax + 0x49c], xmm4
008ca506 movss dword ptr [eax + 0x4a0], xmm3
008ca50e movss dword ptr [eax + 0x4a4], xmm2
008ca516 mov edx, dword ptr [ebp - 0x94]
008ca51c lea ecx, [ebp - 0x1e0]
008ca522 push 0xbc4bb0
008ca527 call 0x412050
008ca52c add esp, 4
008ca52f mov ecx, dword ptr [eax]
008ca531 or ecx, dword ptr [eax + 4]
008ca534 jne 0x8ca542
008ca536 mov ecx, dword ptr [eax + 8]
008ca539 or ecx, dword ptr [eax + 0xc]
008ca53c je 0x8ca658
008ca542 mov eax, dword ptr [ebp - 0x74]
008ca545 cmp byte ptr [eax + 0x3ac], 0
008ca54c jne 0x8ca572
008ca54e movss xmm1, dword ptr [0xb6a8cc]
008ca556 xorps xmm2, xmm2
008ca559 mov ecx, eax
008ca55b call 0x6847e0
008ca560 test eax, eax
008ca562 je 0x8ca658
008ca568 movss xmm4, dword ptr [ebp - 0x7c]
008ca56d movss xmm5, dword ptr [ebp - 0x70]
008ca572 mov ecx, dword ptr [0xbfd65c]
008ca578 lea eax, [ebp - 0x148]
008ca57e movss xmm3, dword ptr [0xb6a9ac]
008ca586 sub esp, 0xc
008ca589 movss dword ptr [ebp - 0x148], xmm5
008ca591 movss dword ptr [ebp - 0x144], xmm4
008ca599 mov ecx, dword ptr [ecx + 0x18190]
008ca59f mov dword ptr [esp + 8], 0x41700000
008ca5a7 mov dword ptr [esp + 4], 0x41700000
008ca5af mov dword ptr [esp], 0x41700000
008ca5b6 push eax
008ca5b7 lea eax, [ebp - 0x190]
008ca5bd push eax
008ca5be call 0x7cec10
008ca5c3 mov eax, dword ptr [ebp - 0x190]
008ca5c9 mov ecx, dword ptr [ebp - 0x18c]
008ca5cf mov dword ptr [ebp - 0x148], eax
008ca5d5 mov dword ptr [ebp - 0x144], ecx
008ca5db call 0x6c3d90
008ca5e0 mov edx, dword ptr [ebp - 0x74]
008ca5e3 mov ecx, dword ptr [0xbfd65c]
008ca5e9 push 0
008ca5eb push 0xbeaaec
008ca5f0 push 0xbeab18
008ca5f5 push 0
008ca5f7 push eax
008ca5f8 push 0
008ca5fa push dword ptr [edx + 0x320]
008ca600 lea eax, [ebp - 0x148]
008ca606 push 0xc02fec
008ca60b push eax
008ca60c push 0x35
008ca60e push 0x3e8
008ca613 call 0x422e20
008ca618 push eax
008ca619 call 0x9ec34c
008ca61e movss xmm1, dword ptr [0xbc7a28]
008ca626 mov ecx, eax
008ca628 movss xmm0, dword ptr [0xbc7a2c]
008ca630 add esp, 0x14
008ca633 mulss xmm1, dword ptr [0xb6a434]
008ca63b mulss xmm0, dword ptr [0xb6a434]
008ca643 mov eax, dword ptr [ecx]
008ca645 movss dword ptr [ecx + 0xd8], xmm1
008ca64d movss dword ptr [ecx + 0xdc], xmm0
008ca655 call dword ptr [eax + 0xc]
008ca658 mov edx, dword ptr [edi]
008ca65a mov ecx, dword ptr [edx + 0x28]
008ca65d lea eax, [ecx - 0xa]
008ca660 cmp eax, 0x3dd
008ca665 ja 0x8ca9bc
008ca66b cmp ecx, 0x21
008ca66e je 0x8ca9bc
008ca674 cmp ecx, 0x11
008ca677 je 0x8ca9bc
008ca67d cmp ecx, 0x124
008ca683 je 0x8ca9bc
008ca689 cmp ecx, 0x375
008ca68f jne 0x8ca697
008ca691 cmp dword ptr [edx + 0x2c], 0xa
008ca695 jmp 0x8ca6b5
008ca697 cmp ecx, 0x3c0
008ca69d je 0x8ca9bc
008ca6a3 cmp ecx, 0x3c5
008ca6a9 je 0x8ca9bc
008ca6af cmp ecx, 0xf5
008ca6b5 je 0x8ca9bc
008ca6bb cmp byte ptr [edx + 0x16b], 0
008ca6c2 jne 0x8ca9bc
008ca6c8 push 0xbc4830
008ca6cd push ecx
008ca6ce push 0xbc4b50
008ca6d3 mov edx, 0xbc4950
008ca6d8 lea ecx, [ebp - 0x1f0]
008ca6de call 0x427220
008ca6e3 add esp, 8
008ca6e6 lea ecx, [ebp - 0x200]
008ca6ec mov edx, eax
008ca6ee call 0x427220
008ca6f3 mov edx, dword ptr [ebp - 0x94]
008ca6f9 lea ecx, [ebp - 0x210]
008ca6ff add esp, 4
008ca702 push eax
008ca703 call 0x412050
008ca708 add esp, 4
008ca70b mov ecx, dword ptr [eax]
008ca70d or ecx, dword ptr [eax + 4]
008ca710 jne 0x8ca71e
008ca712 mov ecx, dword ptr [eax + 8]
008ca715 or ecx, dword ptr [eax + 0xc]
008ca718 je 0x8ca9bc
008ca71e mov eax, dword ptr [ebp - 0x74]
008ca721 cmp byte ptr [eax + 0x3ac], 0
008ca728 jne 0x8ca744
008ca72a movss xmm1, dword ptr [0xb6a8cc]
008ca732 xorps xmm2, xmm2
008ca735 mov ecx, eax
008ca737 call 0x6847e0
008ca73c test eax, eax
008ca73e je 0x8ca9bc
008ca744 mov eax, dword ptr [edi]
008ca746 movss xmm1, dword ptr [ebp - 0x7c]
008ca74b movss xmm2, dword ptr [ebp - 0x70]
008ca750 subss xmm1, dword ptr [eax + 0x298]
008ca758 subss xmm2, dword ptr [eax + 0x294]
008ca760 movaps xmm0, xmm1
008ca763 movss dword ptr [ebp - 0x7c], xmm1
008ca768 mulss xmm0, xmm1
008ca76c movaps xmm1, xmm2
008ca76f mulss xmm1, xmm2
008ca773 movss dword ptr [ebp - 0x70], xmm2
008ca778 addss xmm0, xmm1
008ca77c call 0x4228c0
008ca781 mov eax, dword ptr [edi]
008ca783 movss xmm1, dword ptr [eax + 0x2c8]
008ca78b comiss xmm0, xmm1
008ca78e jbe 0x8ca7b8
008ca790 comiss xmm0, dword ptr [0xb6a18c]
008ca797 jbe 0x8ca7b8
008ca799 divss xmm1, xmm0
008ca79d movaps xmm0, xmm1
008ca7a0 mulss xmm0, dword ptr [ebp - 0x70]
008ca7a5 movss dword ptr [ebp - 0x70], xmm0
008ca7aa movss xmm0, dword ptr [ebp - 0x7c]
008ca7af mulss xmm0, xmm1
008ca7b3 movss dword ptr [ebp - 0x7c], xmm0
008ca7b8 mov edx, dword ptr [ebp - 0x94]
008ca7be lea ecx, [ebp - 0x220]
008ca7c4 push 0xbc4b50
008ca7c9 call 0x412050
008ca7ce add esp, 4
008ca7d1 mov ecx, dword ptr [eax]
008ca7d3 or ecx, dword ptr [eax + 4]
008ca7d6 jne 0x8ca81a
008ca7d8 mov ecx, dword ptr [eax + 8]
008ca7db or ecx, dword ptr [eax + 0xc]
008ca7de jne 0x8ca81a
008ca7e0 mov edx, dword ptr [ebp - 0x94]
008ca7e6 lea ecx, [ebp - 0x230]
008ca7ec push 0xbc4830
008ca7f1 call 0x412050
008ca7f6 add esp, 4
008ca7f9 mov ecx, dword ptr [eax]
008ca7fb or ecx, dword ptr [eax + 4]
008ca7fe jne 0x8ca811
008ca800 mov ecx, dword ptr [eax + 8]
008ca803 or ecx, dword ptr [eax + 0xc]
008ca806 jne 0x8ca811
008ca808 mov dword ptr [ebp - 0x80], 0x13
008ca80f jmp 0x8ca821
008ca811 mov dword ptr [ebp - 0x80], 0x30
008ca818 jmp 0x8ca821
008ca81a mov dword ptr [ebp - 0x80], 0x1a
008ca821 lea eax, [ebp - 0x240]
008ca827 mov edx, 0xbc4a00
008ca82c push eax
008ca82d push ecx
008ca82e push 0xbc46b0
008ca833 push ecx
008ca834 push 0xbc46c0
008ca839 push ecx
008ca83a push 0xbc4890
008ca83f push ecx
008ca840 push 0xbc4a30
008ca845 push ecx
008ca846 push 0xbc4ce0
008ca84b push ecx
008ca84c push 0xbc49e0
008ca851 lea ecx, [ebp - 0x250]
008ca857 call 0x427220
008ca85c add esp, 8
008ca85f lea ecx, [ebp - 0x2b0]
008ca865 mov edx, eax
008ca867 call 0x427220
008ca86c add esp, 8
008ca86f lea ecx, [ebp - 0x260]
008ca875 mov edx, eax
008ca877 call 0x427220
008ca87c add esp, 8
008ca87f lea ecx, [ebp - 0x270]
008ca885 mov edx, eax
008ca887 call 0x427220
008ca88c add esp, 8
008ca88f lea ecx, [ebp - 0x280]
008ca895 mov edx, eax
008ca897 call 0x427220
008ca89c add esp, 8
008ca89f lea ecx, [ebp - 0x290]
008ca8a5 mov edx, eax
008ca8a7 call 0x427220
008ca8ac add esp, 8
008ca8af mov ecx, eax
008ca8b1 call 0x57f3a0
008ca8b6 mov edx, dword ptr [ebp - 0x94]
008ca8bc lea ecx, [ebp - 0x1c0]
008ca8c2 push eax
008ca8c3 call 0x412050
008ca8c8 add esp, 4
008ca8cb call 0x6c3d90
008ca8d0 mov ecx, dword ptr [edi]
008ca8d2 push eax
008ca8d3 mov eax, dword ptr [ebp - 0x74]
008ca8d6 push 0
008ca8d8 movss xmm0, dword ptr [ecx + 0x294]
008ca8e0 movss xmm1, dword ptr [ecx + 0x298]
008ca8e8 push dword ptr [eax + 0x320]
008ca8ee addss xmm0, dword ptr [ebp - 0x70]
008ca8f3 addss xmm1, dword ptr [ebp - 0x7c]
008ca8f8 mov ecx, dword ptr [0xbfd65c]
008ca8fe lea eax, [ebp - 0x188]
008ca904 push 0xc02fec
008ca909 push eax
008ca90a push dword ptr [ebp - 0x80]
008ca90d movss dword ptr [ebp - 0x188], xmm0
008ca915 push 2
008ca917 movss dword ptr [ebp - 0x184], xmm1
008ca91f call 0x422e20
008ca924 mov ecx, eax
008ca926 mov dword ptr [ebp - 0x70], eax
008ca929 mov edx, dword ptr [eax]
008ca92b call dword ptr [edx + 0xc]
008ca92e movups xmm0, xmmword ptr [ebp - 0x1c0]
008ca935 sub esp, 0x10
008ca938 mov ecx, esp
008ca93a movups xmmword ptr [ecx], xmm0
008ca93d mov ecx, dword ptr [ebp - 0x70]
008ca940 call 0x650280
008ca945 mov ecx, dword ptr [ebp - 0x70]
008ca948 mov edx, dword ptr [ebp - 0x74]
008ca94b push ecx
008ca94c mov eax, dword ptr [ecx]
008ca94e movss xmm0, dword ptr [edx + 0x2e0]
008ca956 movss dword ptr [esp], xmm0
008ca95b call dword ptr [eax + 0x3c]
008ca95e mov eax, dword ptr [ebp - 0x74]
008ca961 movss xmm0, dword ptr [eax + 0x430]
008ca969 maxss xmm0, dword ptr [0xb6a214]
008ca971 mov eax, dword ptr [ebp - 0x70]
008ca974 mov ecx, eax
008ca976 movss dword ptr [eax + 0x374], xmm0
008ca97e movss dword ptr [eax + 0x370], xmm0
008ca986 call 0x651770
008ca98b mov edx, dword ptr [ebp - 0x70]
008ca98e mov ecx, dword ptr [edi]
008ca990 inc dword ptr [0xbffe08]
008ca996 push 1
008ca998 mov eax, dword ptr [edx]
008ca99a mov dword ptr [ebp - 0x90], ecx
008ca9a0 push ecx
008ca9a1 mov ecx, edx
008ca9a3 call dword ptr [eax + 0x58]
008ca9a6 mov ecx, dword ptr [ebp - 0x90]
008ca9ac push 0
008ca9ae push dword ptr [ebp - 0x70]
008ca9b1 mov eax, dword ptr [ecx]
008ca9b3 call dword ptr [eax + 0x58]
008ca9b6 dec dword ptr [0xbffe08]
008ca9bc movss xmm0, dword ptr [ebp - 0xcc]
008ca9c4 mov ecx, dword ptr [ebp - 0x74]
008ca9c7 movss dword ptr [ebp - 0x90], xmm0
008ca9cf call 0x4275d0
008ca9d4 test al, al
008ca9d6 jne 0x8caaa3
008ca9dc mov edx, dword ptr [ebp - 0x94]
008ca9e2 lea ecx, [ebp - 0x2a0]
008ca9e8 push 0xbc4bc0
008ca9ed call 0x412050
008ca9f2 add esp, 4
008ca9f5 mov ecx, dword ptr [eax]
008ca9f7 or ecx, dword ptr [eax + 4]
008ca9fa jne 0x8caa1e
008ca9fc mov ecx, dword ptr [eax + 8]
008ca9ff or ecx, dword ptr [eax + 0xc]
008caa02 jne 0x8caa1e
008caa04 movss xmm1, dword ptr [ebp - 0xcc]
008caa0c movss xmm2, dword ptr [ebp - 0x8c]
008caa14 movss xmm0, dword ptr [0xb6a614]
008caa1c jmp 0x8caa55
008caa1e movss xmm2, dword ptr [ebp - 0x8c]
008caa26 movaps xmm1, xmm2
008caa29 movss xmm0, dword ptr [0xb6a614]
008caa31 minss xmm1, dword ptr [0xb6accc]
008caa39 mulss xmm1, dword ptr [0xb6a8f4]
008caa41 divss xmm1, dword ptr [0xb6accc]
008caa49 addss xmm1, xmm0
008caa4d mulss xmm1, dword ptr [ebp - 0xcc]
008caa55 mov edx, dword ptr [ebp - 0x94]
008caa5b lea ecx, [ebp - 0x2c0]
008caa61 push 0xbc4c60
008caa66 call 0x412050
008caa6b add esp, 4
008caa6e mov ecx, dword ptr [eax]
008caa70 or ecx, dword ptr [eax + 4]
008caa73 jne 0x8caa7d
008caa75 mov ecx, dword ptr [eax + 8]
008caa78 or ecx, dword ptr [eax + 0xc]
008caa7b je 0x8caa99
008caa7d minss xmm2, dword ptr [0xb6ac14]
008caa85 divss xmm2, dword ptr [0xb6ac14]
008caa8d subss xmm0, xmm2
008caa91 addss xmm0, xmm0
008caa95 mulss xmm1, xmm0
008caa99 maxss xmm1, dword ptr [0xb6a2cc]
008caaa1 jmp 0x8caaab
008caaa3 movss xmm1, dword ptr [ebp - 0x90]
008caaab push dword ptr [edi]
008caaad mov ecx, dword ptr [ebp - 0x74]
008caab0 movaps xmm2, xmm1
008caab3 call 0x8d6600
008caab8 mov ecx, dword ptr [ebp - 0x74]
008caabb call 0x4275d0
008caac0 mov ecx, dword ptr [ebp - 0x74]
008caac3 test al, al
008caac5 je 0x8caad1
008caac7 cmp dword ptr [ecx + 0x30], 2
008caacb jne 0x8cac88
008caad1 mov edx, dword ptr [edi]
008caad3 mov eax, dword ptr [edx + 0x160]
008caad9 and eax, 0x4000000
008caade or eax, 0
008caae1 je 0x8cab01
008caae3 cmp dword ptr [edx + 0x28], 4
008caae7 jne 0x8cac88
008caaed mov eax, dword ptr [ecx + 0x320]
008caaf3 test eax, eax
008caaf5 je 0x8cac88
008caafb cmp dword ptr [eax + 0x28], 1
008caaff jmp 0x8cab1f
008cab01 cmp dword ptr [edx + 0x28], 1
008cab05 jne 0x8cab25
008cab07 mov eax, dword ptr [ecx + 0x320]
008cab0d test eax, eax
008cab0f je 0x8cab25
008cab11 mov eax, dword ptr [eax + 0x160]
008cab17 and eax, 0x20000000
008cab1c or eax, 0
008cab1f jne 0x8cac88
008cab25 cmp dword ptr [ecx + 0x30], 2
008cab29 movss xmm2, dword ptr [ebp - 0x78]
008cab2e movss xmm1, dword ptr [ebp - 0x98]
008cab36 movss dword ptr [ebp - 0x70], xmm2
008cab3b movss dword ptr [ebp - 0x7c], xmm1
008cab40 jne 0x8caba9
008cab42 movss xmm1, dword ptr [ecx + 0x2bc]
008cab4a movss xmm2, dword ptr [ecx + 0x2b8]
008cab52 movaps xmm0, xmm1
008cab55 mulss xmm0, xmm1
008cab59 movss dword ptr [ebp - 0x7c], xmm1
008cab5e movaps xmm1, xmm2
008cab61 mulss xmm1, xmm2
008cab65 movss dword ptr [ebp - 0x70], xmm2
008cab6a addss xmm0, xmm1
008cab6e call 0x4228c0
008cab73 comiss xmm0, dword ptr [0xb6a18c]
008cab7a jbe 0x8caba4
008cab7c movss xmm1, dword ptr [0xb6a614]
008cab84 divss xmm1, xmm0
008cab88 movss xmm0, dword ptr [ebp - 0x70]
008cab8d mulss xmm0, xmm1
008cab91 movss dword ptr [ebp - 0x70], xmm0
008cab96 movss xmm0, dword ptr [ebp - 0x7c]
008cab9b mulss xmm0, xmm1
008cab9f movss dword ptr [ebp - 0x7c], xmm0
008caba4 mov ecx, dword ptr [ebp - 0x74]
008caba7 mov edx, dword ptr [edi]
008caba9 push ecx
008cabaa mov ecx, edx
008cabac call 0x689640
008cabb1 movss xmm1, dword ptr [ebp - 0x70]
008cabb6 xorps xmm3, xmm3
008cabb9 comiss xmm0, xmm3
008cabbc movss xmm2, dword ptr [ebp - 0x7c]
008cabc1 jbe 0x8cabcb
008cabc3 divss xmm1, xmm0
008cabc7 divss xmm2, xmm0
008cabcb mov eax, dword ptr [ebp - 0x74]
008cabce movss xmm0, dword ptr [eax + 0x2d4]
008cabd6 mov eax, dword ptr [edi]
008cabd8 mulss xmm0, dword ptr [0xb6a758]
008cabe0 mov eax, dword ptr [eax + 0x28]
008cabe3 mulss xmm1, xmm0
008cabe7 mulss xmm2, xmm0
008cabeb cmp eax, 1
008cabee je 0x8cabf5
008cabf0 cmp eax, 3
008cabf3 jne 0x8cac05
008cabf5 mulss xmm1, dword ptr [0xb6a350]
008cabfd mulss xmm2, dword ptr [0xb6a350]
008cac05 mov edx, dword ptr [ebp - 0x94]
008cac0b lea ecx, [ebp - 0x1d0]
008cac11 push 0xbc4ae0
008cac16 call 0x412050
008cac1b add esp, 4
008cac1e mov ecx, dword ptr [eax]
008cac20 or ecx, dword ptr [eax + 4]
008cac23 jne 0x8cac2d
008cac25 mov ecx, dword ptr [eax + 8]
008cac28 or ecx, dword ptr [eax + 0xc]
008cac2b je 0x8cac3b
008cac2d movaps xmm0, xmm1
008cac30 addss xmm1, xmm0
008cac34 movaps xmm0, xmm2
008cac37 addss xmm2, xmm0
008cac3b mov ecx, dword ptr [edi]
008cac3d movss xmm4, dword ptr [ecx + 0x2c4]
008cac45 ucomiss xmm4, xmm3
008cac48 lahf 
008cac49 test ah, 0x44
008cac4c jnp 0x8cac8b
008cac4e movss xmm0, dword ptr [ecx + 0x2f4]
008cac56 mulss xmm1, xmm0
008cac5a mulss xmm2, xmm0
008cac5e divss xmm1, xmm4
008cac62 divss xmm2, xmm4
008cac66 addss xmm1, dword ptr [ecx + 0x2b8]
008cac6e addss xmm2, dword ptr [ecx + 0x2bc]
008cac76 movss dword ptr [ecx + 0x2b8], xmm1
008cac7e movss dword ptr [ecx + 0x2bc], xmm2
008cac86 jmp 0x8cac8b
008cac88 xorps xmm3, xmm3
008cac8b mov edx, dword ptr [ebp - 0x74]
008cac8e mov ecx, edx
008cac90 call 0x8c5940
008cac95 test al, al
008cac97 je 0x8cb6f2
008cac9d mov eax, dword ptr [edx + 0x3d0]
008caca3 mov edx, dword ptr [ebp - 0x88]
008caca9 mov ecx, dword ptr [edi]
008cacab movss xmm1, dword ptr [ebp - 0x78]
008cacb0 xorps xmm1, xmmword ptr [0xb6c9b0]
008cacb7 movss xmm0, dword ptr [eax + edx*8 + 0xc]
008cacbd subss xmm0, dword ptr [eax + edx*8 + 4]
008cacc3 movss xmm5, dword ptr [eax + edx*8 + 8]
008cacc9 subss xmm5, dword ptr [eax + edx*8]
008cacce movss xmm3, dword ptr [ecx + 0x294]
008cacd6 movss xmm2, dword ptr [ecx + 0x298]
008cacde mulss xmm0, dword ptr [ebp - 0x84]
008cace6 mulss xmm5, dword ptr [ebp - 0x84]
008cacee addss xmm0, dword ptr [eax + edx*8 + 4]
008cacf4 movss dword ptr [ebp - 0x7c], xmm1
008cacf9 addss xmm5, dword ptr [eax + edx*8]
008cacfe mov edx, dword ptr [ebp - 0x74]
008cad01 subss xmm2, xmm0
008cad05 movss dword ptr [ebp - 0x9c], xmm0
008cad0d subss xmm3, xmm5
008cad11 movss dword ptr [ebp - 0x70], xmm5
008cad16 mulss xmm2, xmm1
008cad1a mulss xmm3, dword ptr [ebp - 0x98]
008cad22 movss xmm1, dword ptr [ecx + 0x2c8]
008cad2a addss xmm3, xmm2
008cad2e movss xmm2, dword ptr [edx + 0x2c8]
008cad36 movaps xmm0, xmm2
008cad39 xorps xmm0, xmmword ptr [0xb6c9b0]
008cad40 movaps xmm4, xmm3
008cad43 addss xmm3, xmm1
008cad47 subss xmm4, xmm1
008cad4b comiss xmm2, xmm3
008cad4e maxss xmm4, xmm0
008cad52 movss dword ptr [ebp - 0x8c], xmm4
008cad5a ja 0x8cad62
008cad5c movss xmm1, xmm2
008cad60 jmp 0x8cad66
008cad62 movss xmm1, xmm3
008cad66 movaps xmm0, xmm4
008cad69 movss dword ptr [ebp - 0x84], xmm1
008cad71 addss xmm0, dword ptr [0xb6a7b0]
008cad79 comiss xmm1, xmm0
008cad7c jbe 0x8cb728
008cad82 cmp dword ptr [edx + 0x70], 0
008cad86 jne 0x8cad9a
008cad88 push 0xa081ec
008cad8d push 3
008cad8f call 0x95e330
008cad94 mov edx, dword ptr [ebp - 0x74]
008cad97 add esp, 8
008cad9a mov eax, dword ptr [edx + 0x6c]
008cad9d cmp dword ptr [eax + 0x80], 0
008cada4 jg 0x8cadb8
008cada6 push 0xa0824c
008cadab push 3
008cadad call 0x95e330
008cadb2 mov edx, dword ptr [ebp - 0x74]
008cadb5 add esp, 8
008cadb8 mov ecx, dword ptr [edx + 0x70]
008cadbb mov eax, dword ptr [ecx + 0x38]
008cadbe test eax, eax
008cadc0 js 0x8cadfe
008cadc2 cmp eax, dword ptr [ecx + 0x1c]
008cadc5 jge 0x8cadfe
008cadc7 mov ecx, eax
008cadc9 mov eax, dword ptr [edx + 0x70]
008cadcc shl ecx, 4
008cadcf add ecx, dword ptr [eax + 0x18]
008cadd2 mov eax, dword ptr [edx + 0x74]
008cadd5 mov dword ptr [ebp - 0xbc], ecx
008caddb mov ecx, dword ptr [edx + 0x70]
008cadde mov edx, dword ptr [ecx + 0x38]
008cade1 mov ecx, dword ptr [ebp - 0xbc]
008cade7 mov eax, dword ptr [eax + edx*4]
008cadea mov edx, dword ptr [ebp - 0x74]
008caded test eax, eax
008cadef js 0x8cadfe
008cadf1 cmp eax, dword ptr [ecx + 8]
008cadf4 jge 0x8cadfe
008cadf6 imul eax, eax, 0x6c
008cadf9 add eax, dword ptr [ecx + 4]
008cadfc jmp 0x8cae00
008cadfe xor eax, eax
008cae00 cmp dword ptr [edx + 0xbc], 0
008cae07 mov dword ptr [ebp - 0x80], eax
008cae0a lea eax, [edx + 0x3c]
008cae0d mov dword ptr [ebp - 0x90], eax
008cae13 jg 0x8cae3a
008cae15 cmp dword ptr [eax + 0x14], 0x10
008cae19 mov ecx, eax
008cae1b jb 0x8cae1f
008cae1d mov ecx, dword ptr [eax]
008cae1f push 0
008cae21 push ecx
008cae22 push 0xa0830c
008cae27 push 3
008cae29 call 0x95e330
008cae2e mov edx, dword ptr [ebp - 0x74]
008cae31 add esp, 0x10
008cae34 mov eax, dword ptr [ebp - 0x90]
008cae3a mov ecx, dword ptr [eax + 0x7c]
008cae3d xorps xmm3, xmm3
008cae40 movups xmm0, xmmword ptr [edx + 0xf4]
008cae47 mov eax, dword ptr [edx + 0x10c]
008cae4d movups xmm7, xmmword ptr [edx + 0xe4]
008cae54 mov dword ptr [ebp - 0x108], eax
008cae5a movups xmmword ptr [ebp - 0x120], xmm0
008cae61 movq xmm0, qword ptr [edx + 0x104]
008cae69 movss xmm2, dword ptr [ecx + 0x58]
008cae6e movq qword ptr [ebp - 0x110], xmm0
008cae76 movups xmmword ptr [ebp - 0x130], xmm7
008cae7d movss xmm0, dword ptr [ebp - 0x12c]
008cae85 mulss xmm0, dword ptr [ecx + 0x4c]
008cae8a movss xmm4, dword ptr [ecx + 0x5c]
008cae8f movss xmm5, dword ptr [ecx + 0x60]
008cae94 movss dword ptr [ebp - 0x12c], xmm0
008cae9c movss xmm0, dword ptr [ebp - 0x128]
008caea4 mulss xmm0, dword ptr [ecx + 0x50]
008caea9 mulss xmm7, dword ptr [ecx + 0x48]
008caeae movss dword ptr [ebp - 0x128], xmm0
008caeb6 movss xmm0, dword ptr [ebp - 0x124]
008caebe mulss xmm0, dword ptr [ecx + 0x54]
008caec3 movss dword ptr [ebp - 0x130], xmm7
008caecb movss dword ptr [ebp - 0x124], xmm0
008caed3 movaps xmm0, xmm2
008caed6 addss xmm0, xmm4
008caeda addss xmm0, xmm5
008caede ucomiss xmm0, xmm3
008caee1 lahf 
008caee2 test ah, 0x44
008caee5 jnp 0x8caf8c
008caeeb movss xmm6, dword ptr [ebp - 0x120]
008caef3 movss xmm1, dword ptr [ecx + 0x64]
008caef8 movaps xmm0, xmm6
008caefb addss xmm0, dword ptr [ebp - 0x11c]
008caf03 addss xmm0, dword ptr [ebp - 0x118]
008caf0b ucomiss xmm0, xmm3
008caf0e lahf 
008caf0f test ah, 0x44
008caf12 jp 0x8caf36
008caf14 movss dword ptr [ebp - 0x120], xmm2
008caf1c movss dword ptr [ebp - 0x11c], xmm4
008caf24 movss dword ptr [ebp - 0x118], xmm5
008caf2c movss dword ptr [ebp - 0x114], xmm1
008caf34 jmp 0x8cafa4
008caf36 addss xmm4, dword ptr [ebp - 0x11c]
008caf3e addss xmm5, dword ptr [ebp - 0x118]
008caf46 addss xmm1, dword ptr [ebp - 0x114]
008caf4e movss xmm0, dword ptr [0xb6a480]
008caf56 addss xmm2, xmm6
008caf5a mulss xmm4, xmm0
008caf5e mulss xmm5, xmm0
008caf62 mulss xmm2, xmm0
008caf66 mulss xmm1, xmm0
008caf6a movss dword ptr [ebp - 0x120], xmm2
008caf72 movss dword ptr [ebp - 0x11c], xmm4
008caf7a movss dword ptr [ebp - 0x118], xmm5
008caf82 movss dword ptr [ebp - 0x114], xmm1
008caf8a jmp 0x8cafa4
008caf8c movss xmm5, dword ptr [ebp - 0x118]
008caf94 movss xmm4, dword ptr [ebp - 0x11c]
008caf9c movss xmm2, dword ptr [ebp - 0x120]
008cafa4 movss xmm0, dword ptr [ebp - 0x108]
008cafac addss xmm0, dword ptr [ecx + 0x70]
008cafb1 movss xmm6, dword ptr [ebp - 0x110]
008cafb9 addss xmm6, dword ptr [ecx + 0x68]
008cafbe movss xmm1, dword ptr [ebp - 0x10c]
008cafc6 addss xmm1, dword ptr [ecx + 0x6c]
008cafcb mov ecx, dword ptr [ebp - 0x80]
008cafce movss dword ptr [ebp - 0x108], xmm0
008cafd6 movups xmm0, xmmword ptr [ebp - 0x130]
008cafdd mov eax, dword ptr [ebp - 0x108]
008cafe3 mulss xmm7, dword ptr [ecx + 0x30]
008cafe8 mov dword ptr [ebp - 0xd8], eax
008cafee movups xmmword ptr [ebp - 0x100], xmm0
008caff5 movups xmm0, xmmword ptr [ebp - 0x120]
