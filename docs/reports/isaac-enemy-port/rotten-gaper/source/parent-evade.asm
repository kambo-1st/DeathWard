007a4830 push ebx
007a4831 mov ebx, esp
007a4833 sub esp, 8
007a4836 and esp, 0xfffffff8
007a4839 add esp, 4
007a483c push ebp
007a483d mov ebp, dword ptr [ebx + 4]
007a4840 mov dword ptr [esp + 4], ebp
007a4844 mov ebp, esp
007a4846 push -1
007a4848 push 0x9f972d
007a484d mov eax, dword ptr fs:[0]
007a4853 push eax
007a4854 push ebx
007a4855 sub esp, 0x68
007a4858 push esi
007a4859 push edi
007a485a mov eax, dword ptr [0xbaa3b4]
007a485f xor eax, ebp
007a4861 push eax
007a4862 lea eax, [ebp - 0xc]
007a4865 mov dword ptr fs:[0], eax
007a486b mov esi, ecx
007a486d mov dword ptr [ebp - 0x20], esi
007a4870 cmp byte ptr [ebx + 0xc], 0
007a4874 jne 0x7a48cc
007a4876 call 0x7a35d0
007a487b test al, al
007a487d je 0x7a48cc
007a487f push 0
007a4881 push 0xbeab70
007a4886 push 0xbeab18
007a488b push 0
007a488d push dword ptr [esi]
007a488f call 0x9ec34c
007a4894 add esp, 0x14
007a4897 mov ecx, eax
007a4899 call 0x695680
007a489e push 1
007a48a0 push 0
007a48a2 mov ecx, dword ptr [eax + 0x294]
007a48a8 mov eax, dword ptr [eax + 0x298]
007a48ae push ecx
007a48af mov dword ptr [ebp - 0x38], eax
007a48b2 lea eax, [ebp - 0x3c]
007a48b5 mov dword ptr [ebp - 0x3c], ecx
007a48b8 mov ecx, esi
007a48ba mov dword ptr [esp], 0x3f8a1cac
007a48c1 push eax
007a48c2 call 0x7a3650
007a48c7 jmp 0x7a51bb
007a48cc mov ecx, dword ptr [ebx + 8]
007a48cf mov edi, dword ptr [esi]
007a48d1 lea eax, [edi + 0x294]
007a48d7 mov dword ptr [ebp - 0x24], eax
007a48da movss xmm1, dword ptr [ecx]
007a48de subss xmm1, dword ptr [eax]
007a48e2 movss xmm2, dword ptr [ecx + 4]
007a48e7 subss xmm2, dword ptr [eax + 4]
007a48ec movaps xmm0, xmm1
007a48ef movss dword ptr [ebp - 0x18], xmm1
007a48f4 mulss xmm0, xmm1
007a48f8 movaps xmm1, xmm2
007a48fb movss dword ptr [ebp - 0x2c], xmm2
007a4900 mulss xmm1, xmm2
007a4904 addss xmm0, xmm1
007a4908 call 0x4228c0
007a490d movss xmm1, dword ptr [esi + 0x744]
007a4915 lea ecx, [esi + 0x744]
007a491b comiss xmm1, dword ptr [0xb6a9c8]
007a4922 lea eax, [ebp - 0x28]
007a4925 mov dword ptr [ebp - 0x28], 0x41a00000
007a492c movss dword ptr [ebp - 0x1c], xmm0
007a4931 cmovbe eax, ecx
007a4934 mov eax, dword ptr [eax]
007a4936 mov dword ptr [ecx], eax
007a4938 mov eax, dword ptr [edi + 0x20]
007a493b mov dword ptr [ebp - 0x28], eax
007a493e mov eax, dword ptr [edi + 0x160]
007a4944 and eax, 0x4000
007a4949 or eax, 0
007a494c jne 0x7a4a18
007a4952 mov ecx, dword ptr [0xbfd65c]
007a4958 call 0x6d0380
007a495d test al, al
007a495f jne 0x7a4a18
007a4965 mov ecx, dword ptr [0xbfd65c]
007a496b mov eax, dword ptr [ecx + 0x1a30dc]
007a4971 add eax, dword ptr [ebp - 0x28]
007a4974 cdq 
007a4975 mov dword ptr [ebp - 0x28], 0xe
007a497c idiv dword ptr [ebp - 0x28]
007a497f test edx, edx
007a4981 jne 0x7a4a18
007a4987 mov edx, dword ptr [ebp - 0x24]
007a498a mov ecx, dword ptr [ecx + 0x18190]
007a4990 push 0
007a4992 push 0
007a4994 mov eax, dword ptr [edx]
007a4996 mov edx, dword ptr [edx + 4]
007a4999 push 0
007a499b push 0
007a499d push 1
007a499f push dword ptr [ebx + 8]
007a49a2 mov dword ptr [ebp - 0x3c], eax
007a49a5 lea eax, [ebp - 0x3c]
007a49a8 push eax
007a49a9 mov dword ptr [ebp - 0x38], edx
007a49ac call 0x7af4b0
007a49b1 test al, al
007a49b3 je 0x7a49bf
007a49b5 movss xmm0, dword ptr [0xb6abec]
007a49bd jmp 0x7a49c7
007a49bf movss xmm0, dword ptr [0xb6ab7c]
007a49c7 comiss xmm0, dword ptr [ebp - 0x1c]
007a49cb jbe 0x7a49fe
007a49cd cmp dword ptr [esi + 0x73c], 0
007a49d4 jg 0x7a49f0
007a49d6 movss xmm0, dword ptr [0xc02fec]
007a49de movss dword ptr [esi + 4], xmm0
007a49e3 movss xmm0, dword ptr [0xc02ff0]
007a49eb movss dword ptr [esi + 8], xmm0
007a49f0 mov edi, dword ptr [esi]
007a49f2 mov dword ptr [esi + 0x73c], 3
007a49fc jmp 0x7a4a18
007a49fe mov edi, dword ptr [esi]
007a4a00 cvttss2si eax, dword ptr [edi + 0x2fc]
007a4a08 cvttss2si ecx, dword ptr [edi + 0x2f8]
007a4a10 sub ecx, eax
007a4a12 add dword ptr [esi + 0x73c], ecx
007a4a18 mov eax, dword ptr [edi + 0x20]
007a4a1b mov dword ptr [ebp - 0x28], eax
007a4a1e mov eax, dword ptr [edi + 0x160]
007a4a24 and eax, 0x4000
007a4a29 or eax, 0
007a4a2c jne 0x7a4a79
007a4a2e mov edi, dword ptr [0xbfd65c]
007a4a34 mov ecx, edi
007a4a36 call 0x6d0380
007a4a3b test al, al
007a4a3d jne 0x7a4a79
007a4a3f mov eax, dword ptr [edi + 0x1a30dc]
007a4a45 mov ecx, 0x1e
007a4a4a add eax, dword ptr [ebp - 0x28]
007a4a4d cdq 
007a4a4e idiv ecx
007a4a50 test edx, edx
007a4a52 jne 0x7a4a79
007a4a54 lea edi, [esi + 0x748]
007a4a5a mov esi, dword ptr [edi]
007a4a5c mov ecx, edi
007a4a5e push dword ptr [esi + 4]
007a4a61 push edi
007a4a62 call 0x420480
007a4a67 mov dword ptr [esi + 4], esi
007a4a6a mov dword ptr [esi], esi
007a4a6c mov dword ptr [esi + 8], esi
007a4a6f mov esi, dword ptr [ebp - 0x20]
007a4a72 mov dword ptr [edi + 4], 0
007a4a79 cmp dword ptr [esi + 0x73c], 0
007a4a80 jle 0x7a5176
007a4a86 movss xmm0, dword ptr [esi + 4]
007a4a8b lea edi, [esi + 4]
007a4a8e ucomiss xmm0, dword ptr [0xc02fec]
007a4a95 movss xmm5, dword ptr [0xb6c980]
007a4a9d lahf 
007a4a9e test ah, 0x44
007a4aa1 jp 0x7a4ab5
007a4aa3 movss xmm0, dword ptr [edi + 4]
007a4aa8 ucomiss xmm0, dword ptr [0xc02ff0]
007a4aaf lahf 
007a4ab0 test ah, 0x44
007a4ab3 jnp 0x7a4aca
007a4ab5 movss xmm0, dword ptr [esi + 0x744]
007a4abd comiss xmm0, dword ptr [0xb6a9c8]
007a4ac4 jbe 0x7a5019
007a4aca movss xmm0, dword ptr [ebp - 0x1c]
007a4acf xorps xmm2, xmm2
007a4ad2 comiss xmm0, xmm2
007a4ad5 movss xmm3, dword ptr [0xc02fec]
007a4add movss xmm4, dword ptr [0xc02ff0]
007a4ae5 movss dword ptr [ebp - 0x14], xmm2
007a4aea jbe 0x7a4b05
007a4aec xorps xmm0, xmmword ptr [0xb6c9b0]
007a4af3 movss xmm3, dword ptr [ebp - 0x18]
007a4af8 movss xmm4, dword ptr [ebp - 0x2c]
007a4afd divss xmm3, xmm0
007a4b01 divss xmm4, xmm0
007a4b05 movaps xmm1, xmm3
007a4b08 movaps xmm0, xmm4
007a4b0b andps xmm1, xmm5
007a4b0e andps xmm0, xmm5
007a4b11 subss xmm1, xmm0
007a4b15 movss xmm0, dword ptr [0xb6a38c]
007a4b1d andps xmm1, xmm5
007a4b20 comiss xmm0, xmm1
007a4b23 movss xmm1, dword ptr [0xb6a480]
007a4b2b jbe 0x7a4b41
007a4b2d call 0x6c3d90
007a4b32 and eax, 1
007a4b35 jne 0x7a4b3d
007a4b37 mulss xmm3, xmm1
007a4b3b jmp 0x7a4b41
007a4b3d mulss xmm4, xmm1
007a4b41 mov ecx, dword ptr [esi]
007a4b43 movaps xmm1, xmm3
007a4b46 mulss xmm1, dword ptr [0xb6a6f0]
007a4b4e movaps xmm5, xmm4
007a4b51 mulss xmm5, dword ptr [0xb6a6f0]
007a4b59 movss xmm6, dword ptr [ecx + 0x2c4]
007a4b61 ucomiss xmm6, xmm2
007a4b64 lahf 
007a4b65 test ah, 0x44
007a4b68 jnp 0x7a4ba4
007a4b6a movss xmm0, dword ptr [ecx + 0x2f4]
007a4b72 mulss xmm1, xmm0
007a4b76 mulss xmm5, xmm0
007a4b7a divss xmm1, xmm6
007a4b7e divss xmm5, xmm6
007a4b82 addss xmm1, dword ptr [ecx + 0x2b8]
007a4b8a addss xmm5, dword ptr [ecx + 0x2bc]
007a4b92 movss dword ptr [ecx + 0x2b8], xmm1
007a4b9a movss dword ptr [ecx + 0x2bc], xmm5
007a4ba2 mov ecx, dword ptr [esi]
007a4ba4 movss xmm5, dword ptr [0xb6aa0c]
007a4bac movss xmm1, dword ptr [ecx + 0x298]
007a4bb4 movss xmm0, dword ptr [ecx + 0x294]
007a4bbc mulss xmm4, xmm5
007a4bc0 mulss xmm3, xmm5
007a4bc4 addss xmm1, xmm4
007a4bc8 addss xmm0, xmm3
007a4bcc movss dword ptr [ebp - 0x34], xmm1
007a4bd1 movss xmm1, dword ptr [esi + 0x744]
007a4bd9 mulss xmm1, dword ptr [0xb6a3b0]
007a4be1 movss dword ptr [ebp - 0x30], xmm0
007a4be6 movss xmm0, dword ptr [0xb6a928]
007a4bee subss xmm0, xmm1
007a4bf2 comiss xmm0, xmm2
007a4bf5 jbe 0x7a5019
007a4bfb movss xmm1, dword ptr [0xb6a19c]
007a4c03 call 0x6c3d90
007a4c08 xorps xmm0, xmm0
007a4c0b cvtsi2sd xmm0, eax
007a4c0f shr eax, 0x1f
007a4c12 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007a4c1b cvtpd2ps xmm0, xmm0
007a4c1f mulss xmm0, xmm1
007a4c23 mulss xmm0, dword ptr [0xb6ac80]
007a4c2b addss xmm0, xmm5
007a4c2f movss dword ptr [ebp - 0x24], xmm0
007a4c34 call 0x6c3d90
007a4c39 xorps xmm0, xmm0
007a4c3c cvtsi2sd xmm0, eax
007a4c40 shr eax, 0x1f
007a4c43 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007a4c4c cvtpd2ps xmm0, xmm0
007a4c50 mulss xmm0, xmm1
007a4c54 mulss xmm0, dword ptr [0xb6a874]
007a4c5c addss xmm0, xmm0
007a4c60 movss dword ptr [ebp - 0x2c], xmm0
007a4c65 call 0x412010
007a4c6a movss dword ptr [ebp - 0x28], xmm0
007a4c6f movss xmm0, dword ptr [ebp - 0x2c]
007a4c74 call 0x411fe0
007a4c79 mulss xmm0, dword ptr [ebp - 0x24]
007a4c7e mov eax, dword ptr [0xbfd65c]
007a4c83 movss xmm3, dword ptr [0xb6a480]
007a4c8b movss xmm1, dword ptr [ebp - 0x28]
007a4c90 addss xmm0, dword ptr [ebp - 0x30]
007a4c95 movss xmm2, dword ptr [0xb6aa3c]
007a4c9d movss xmm4, dword ptr [0xb6ab20]
007a4ca5 mulss xmm1, xmm3
007a4ca9 mov ecx, dword ptr [eax + 0x18190]
007a4caf movss dword ptr [ebp - 0x3c], xmm0
007a4cb4 subss xmm0, xmm2
007a4cb8 mulss xmm1, dword ptr [ebp - 0x24]
007a4cbd divss xmm0, xmm2
007a4cc1 addss xmm1, dword ptr [ebp - 0x34]
007a4cc6 addss xmm0, xmm3
007a4cca movss dword ptr [ebp - 0x38], xmm1
007a4ccf subss xmm1, xmm4
007a4cd3 cvttss2si edx, xmm0
007a4cd7 divss xmm1, xmm2
007a4cdb addss xmm1, xmm3
007a4cdf cvttss2si eax, xmm1
007a4ce3 test edx, edx
007a4ce5 js 0x7a4cfe
007a4ce7 mov edi, dword ptr [ecx + 0xc]
007a4cea cmp edx, edi
007a4cec jge 0x7a4cfe
007a4cee test eax, eax
007a4cf0 js 0x7a4cfe
007a4cf2 cmp eax, dword ptr [ecx + 0x10]
007a4cf5 jge 0x7a4cfe
007a4cf7 imul edi, eax
007a4cfa add edi, edx
007a4cfc jmp 0x7a4d01
007a4cfe or edi, 0xffffffff
007a4d01 mov eax, dword ptr [esi + 0x748]
007a4d07 lea ecx, [esi + 0x748]
007a4d0d mov dword ptr [ebp - 0x20], eax
007a4d10 lea eax, [ebp - 0x18]
007a4d13 push eax
007a4d14 lea eax, [ebp - 0x6c]
007a4d17 mov dword ptr [ebp - 0x18], edi
007a4d1a push eax
007a4d1b call 0x4206b0
007a4d20 mov eax, dword ptr [ebp - 0x64]
007a4d23 cmp byte ptr [eax + 0xd], 0
007a4d27 jne 0x7a4d45
007a4d29 cmp edi, dword ptr [eax + 0x10]
007a4d2c jl 0x7a4d45
007a4d2e cmp eax, dword ptr [ebp - 0x20]
007a4d31 je 0x7a4d45
007a4d33 movss xmm2, dword ptr [ebp - 0x14]
007a4d38 subss xmm2, dword ptr [0xb6a50c]
007a4d40 jmp 0x7a4f9f
007a4d45 lea eax, [ebp - 0x18]
007a4d48 push eax
007a4d49 lea eax, [ebp - 0x78]
007a4d4c push eax
007a4d4d lea ecx, [esi + 0x748]
007a4d53 call 0x4206b0
007a4d58 movq xmm0, qword ptr [eax]
007a4d5c mov eax, dword ptr [eax + 8]
007a4d5f movq qword ptr [ebp - 0x60], xmm0
007a4d64 cmp byte ptr [eax + 0xd], 0
007a4d68 jne 0x7a4d6f
007a4d6a cmp edi, dword ptr [eax + 0x10]
007a4d6d jge 0x7a4dec
007a4d6f cmp dword ptr [esi + 0x74c], 0xccccccc
007a4d79 lea eax, [esi + 0x748]
007a4d7f je 0x7a51d1
007a4d85 mov dword ptr [ebp - 0x44], eax
007a4d88 mov dword ptr [ebp - 4], 0
007a4d8f push 0x14
007a4d91 mov dword ptr [ebp - 0x40], 0
007a4d98 call 0x9eacf8
007a4d9d mov ecx, dword ptr [ebp - 0x20]
007a4da0 add esp, 4
007a4da3 mov dword ptr [ebp - 4], 0xffffffff
007a4daa mov dword ptr [ebp - 0x40], 0
007a4db1 mov dword ptr [eax + 0x10], edi
007a4db4 push eax
007a4db5 push dword ptr [ebp - 0x5c]
007a4db8 mov dword ptr [eax], ecx
007a4dba push dword ptr [ebp - 0x60]
007a4dbd mov dword ptr [eax + 4], ecx
007a4dc0 mov dword ptr [eax + 8], ecx
007a4dc3 lea ecx, [esi + 0x748]
007a4dc9 mov word ptr [eax + 0xc], 0
007a4dcf call 0x4d1da0
007a4dd4 movss xmm2, dword ptr [0xb6aa3c]
007a4ddc movss xmm3, dword ptr [0xb6a480]
007a4de4 movss xmm4, dword ptr [0xb6ab20]
007a4dec mov ecx, dword ptr [0xbfd65c]
007a4df2 mov eax, dword ptr [ecx + 0x18190]
007a4df8 mov dword ptr [ebp - 0x18], eax
007a4dfb mov ecx, dword ptr [eax + 0xc]
007a4dfe mov eax, edi
007a4e00 cdq 
007a4e01 idiv ecx
007a4e03 mov edi, dword ptr [ebp - 0x18]
007a4e06 movd xmm0, edx
007a4e0a cvtdq2ps xmm0, xmm0
007a4e0d movd xmm1, eax
007a4e11 mulss xmm0, xmm2
007a4e15 cvtdq2ps xmm1, xmm1
007a4e18 addss xmm0, xmm2
007a4e1c mulss xmm1, xmm2
007a4e20 movss dword ptr [ebp - 0x20], xmm0
007a4e25 addss xmm1, xmm4
007a4e29 movss dword ptr [ebp - 0x3c], xmm0
007a4e2e subss xmm0, xmm2
007a4e32 movss dword ptr [ebp - 0x28], xmm1
007a4e37 divss xmm0, xmm2
007a4e3b movss dword ptr [ebp - 0x38], xmm1
007a4e40 addss xmm0, xmm3
007a4e44 cvttss2si edx, xmm0
007a4e48 movaps xmm0, xmm1
007a4e4b subss xmm0, xmm4
007a4e4f divss xmm0, xmm2
007a4e53 addss xmm0, xmm3
007a4e57 cvttss2si eax, xmm0
007a4e5b test edx, edx
007a4e5d js 0x7a4e73
007a4e5f cmp edx, ecx
007a4e61 jge 0x7a4e73
007a4e63 test eax, eax
007a4e65 js 0x7a4e73
007a4e67 cmp eax, dword ptr [edi + 0x10]
007a4e6a jge 0x7a4e73
007a4e6c imul ecx, eax
007a4e6f add ecx, edx
007a4e71 jmp 0x7a4e76
007a4e73 or ecx, 0xffffffff
007a4e76 push ecx
007a4e77 mov ecx, edi
007a4e79 call 0x7aeec0
007a4e7e test eax, eax
007a4e80 jne 0x7a4f9a
007a4e86 mov eax, dword ptr [esi]
007a4e88 push 0
007a4e8a push 0
007a4e8c mov ecx, dword ptr [eax + 0x294]
007a4e92 mov eax, dword ptr [eax + 0x298]
007a4e98 mov dword ptr [ebp - 0x48], eax
007a4e9b movzx eax, byte ptr [esi + 0x738]
007a4ea2 push eax
007a4ea3 push 0
007a4ea5 push 1
007a4ea7 lea eax, [ebp - 0x3c]
007a4eaa mov dword ptr [ebp - 0x4c], ecx
007a4ead push eax
007a4eae lea eax, [ebp - 0x4c]
007a4eb1 mov ecx, edi
007a4eb3 push eax
007a4eb4 call 0x7af4b0
007a4eb9 test al, al
007a4ebb je 0x7a4f9a
007a4ec1 mov eax, dword ptr [esi]
007a4ec3 mov edi, dword ptr [ebx + 8]
007a4ec6 push 0
007a4ec8 push 0
007a4eca mov ecx, dword ptr [eax + 0x294]
007a4ed0 mov eax, dword ptr [eax + 0x298]
007a4ed6 mov dword ptr [ebp - 0x50], eax
007a4ed9 movzx eax, byte ptr [esi + 0x738]
007a4ee0 push eax
007a4ee1 push 0
007a4ee3 mov dword ptr [ebp - 0x54], ecx
007a4ee6 lea eax, [ebp - 0x54]
007a4ee9 mov ecx, dword ptr [0xbfd65c]
007a4eef push 1
007a4ef1 push eax
007a4ef2 push edi
007a4ef3 mov ecx, dword ptr [ecx + 0x18190]
007a4ef9 call 0x7af4b0
007a4efe test al, al
007a4f00 je 0x7a4f25
007a4f02 movss xmm0, dword ptr [esi + 0x744]
007a4f0a comiss xmm0, dword ptr [0xb6a9c8]
007a4f11 jae 0x7a4f25
007a4f13 addss xmm0, dword ptr [0xb6a3f8]
007a4f1b movss dword ptr [esi + 0x744], xmm0
007a4f23 jmp 0x7a4f9a
007a4f25 movss xmm1, dword ptr [edi]
007a4f29 movss xmm0, dword ptr [edi + 4]
007a4f2e subss xmm0, dword ptr [ebp - 0x28]
007a4f33 subss xmm1, dword ptr [ebp - 0x20]
007a4f38 movss xmm2, dword ptr [esi + 0x740]
007a4f40 movss dword ptr [ebp - 0x2c], xmm2
007a4f45 mulss xmm0, xmm0
007a4f49 mulss xmm1, xmm1
007a4f4d addss xmm0, xmm1
007a4f51 call 0x4228c0
007a4f56 movss xmm2, dword ptr [ebp - 0x24]
007a4f5b divss xmm2, dword ptr [0xb6a864]
007a4f63 movss xmm1, dword ptr [ebp - 0x1c]
007a4f68 addss xmm1, dword ptr [0xb6aafc]
007a4f70 addss xmm2, xmm1
007a4f74 movss xmm1, dword ptr [ebp - 0x2c]
007a4f79 addss xmm2, dword ptr [esi + 0x744]
007a4f81 subss xmm2, xmm1
007a4f85 comiss xmm2, xmm0
007a4f88 jbe 0x7a4fde
007a4f8a addss xmm1, dword ptr [0xb6a974]
007a4f92 movss dword ptr [esi + 0x740], xmm1
007a4f9a movss xmm2, dword ptr [ebp - 0x14]
007a4f9f movss xmm1, dword ptr [esi + 0x744]
007a4fa7 mulss xmm1, dword ptr [0xb6a3b0]
007a4faf movss xmm0, dword ptr [0xb6a928]
007a4fb7 addss xmm2, dword ptr [0xb6a614]
007a4fbf subss xmm0, xmm1
007a4fc3 movss dword ptr [ebp - 0x14], xmm2
007a4fc8 comiss xmm0, xmm2
007a4fcb jbe 0x7a5114
007a4fd1 movss xmm5, dword ptr [0xb6aa0c]
007a4fd9 jmp 0x7a4bfb
007a4fde movss xmm0, dword ptr [ebp - 0x20]
007a4fe3 lea edi, [esi + 4]
007a4fe6 movss xmm1, dword ptr [0xb6a9c8]
007a4fee movss dword ptr [edi], xmm0
007a4ff2 movss xmm0, dword ptr [ebp - 0x28]
007a4ff7 movss dword ptr [edi + 4], xmm0
007a4ffc movss xmm0, dword ptr [esi + 0x744]
007a5004 comiss xmm1, xmm0
007a5007 jbe 0x7a5019
007a5009 mulss xmm0, dword ptr [0xb6a480]
007a5011 movss dword ptr [esi + 0x744], xmm0
007a5019 movss xmm0, dword ptr [edi]
007a501d ucomiss xmm0, dword ptr [0xc02fec]
007a5024 lahf 
007a5025 test ah, 0x44
007a5028 jp 0x7a5040
007a502a movss xmm0, dword ptr [edi + 4]
007a502f ucomiss xmm0, dword ptr [0xc02ff0]
007a5036 lahf 
007a5037 test ah, 0x44
007a503a jnp 0x7a51bb
007a5040 mov eax, dword ptr [esi]
007a5042 mov ecx, dword ptr [eax + 0x20]
007a5045 mov eax, dword ptr [eax + 0x160]
007a504b and eax, 0x4000
007a5050 mov dword ptr [ebp - 0x34], ecx
007a5053 or eax, 0
007a5056 jne 0x7a513d
007a505c mov edi, dword ptr [0xbfd65c]
007a5062 mov ecx, edi
007a5064 call 0x6d0380
007a5069 test al, al
007a506b jne 0x7a513a
007a5071 mov eax, dword ptr [edi + 0x1a30dc]
007a5077 mov ecx, 0xa
007a507c add eax, dword ptr [ebp - 0x34]
007a507f cdq 
007a5080 idiv ecx
007a5082 test edx, edx
007a5084 jne 0x7a513a
007a508a movzx eax, byte ptr [esi + 0x738]
007a5091 mov ecx, dword ptr [edi + 0x18190]
007a5097 push edx
007a5098 push edx
007a5099 push eax
007a509a push edx
007a509b push 1
007a509d lea eax, [esi + 4]
007a50a0 push eax
007a50a1 push dword ptr [ebx + 8]
007a50a4 call 0x7af4b0
007a50a9 movss xmm4, dword ptr [0xb6a9c8]
007a50b1 test al, al
007a50b3 je 0x7a50be
007a50b5 comiss xmm4, dword ptr [esi + 0x744]
007a50bc ja 0x7a511c
007a50be mov eax, dword ptr [ebx + 8]
007a50c1 lea edi, [esi + 4]
007a50c4 movss xmm2, dword ptr [eax]
007a50c8 movss xmm3, dword ptr [eax + 4]
007a50cd subss xmm2, dword ptr [edi]
007a50d1 movaps xmm1, xmm3
007a50d4 subss xmm1, dword ptr [edi + 4]
007a50d9 movaps xmm0, xmm2
007a50dc mulss xmm0, xmm2
007a50e0 mulss xmm1, xmm1
007a50e4 addss xmm1, xmm0
007a50e8 movss xmm0, dword ptr [0xb6ad60]
007a50f0 comiss xmm0, xmm1
007a50f3 ja 0x7a511f
007a50f5 movss xmm0, dword ptr [0xb6c980]
007a50fd andps xmm2, xmm0
007a5100 comiss xmm4, xmm2
007a5103 ja 0x7a511f
007a5105 subss xmm3, dword ptr [esi + 8]
007a510a andps xmm3, xmm0
007a510d comiss xmm4, xmm3
007a5110 jbe 0x7a513d
007a5112 jmp 0x7a511f
007a5114 lea edi, [esi + 4]
007a5117 jmp 0x7a5019
007a511c lea edi, [esi + 4]
007a511f movss xmm0, dword ptr [0xc02fec]
007a5127 movss dword ptr [edi], xmm0
007a512b movss xmm0, dword ptr [0xc02ff0]
007a5133 movss dword ptr [edi + 4], xmm0
007a5138 jmp 0x7a513d
007a513a lea edi, [esi + 4]
007a513d movss xmm0, dword ptr [edi]
007a5141 ucomiss xmm0, dword ptr [0xc02fec]
007a5148 lahf 
007a5149 test ah, 0x44
007a514c jp 0x7a5160
007a514e movss xmm0, dword ptr [edi + 4]
007a5153 ucomiss xmm0, dword ptr [0xc02ff0]
007a515a lahf 
007a515b test ah, 0x44
007a515e jnp 0x7a51bb
007a5160 push 1
007a5162 push 0
007a5164 push ecx
007a5165 mov dword ptr [esp], 0x3f8a1cac
007a516c mov ecx, esi
007a516e push edi
007a516f call 0x7a3650
007a5174 jmp 0x7a51bb
007a5176 movss xmm0, dword ptr [esi + 0x744]
007a517e mov ecx, esi
007a5180 mulss xmm0, dword ptr [0xb6a5a4]
007a5188 push 1
007a518a mov dword ptr [esi + 0x740], 0
007a5194 movss dword ptr [esi + 0x744], xmm0
007a519c call 0x7a6180
007a51a1 mov eax, dword ptr [esi]
007a51a3 movss xmm0, dword ptr [eax + 0x2c4]
007a51ab mulss xmm0, dword ptr [0xb6a5a4]
007a51b3 movss dword ptr [eax + 0x2c4], xmm0
007a51bb mov ecx, dword ptr [ebp - 0xc]
007a51be mov dword ptr fs:[0], ecx
007a51c5 pop ecx
007a51c6 pop edi
007a51c7 pop esi
007a51c8 mov esp, ebp
007a51ca pop ebp
007a51cb mov esp, ebx
007a51cd pop ebx
007a51ce ret 8
