005106d0 push ebx
005106d1 mov ebx, esp
005106d3 sub esp, 8
005106d6 and esp, 0xfffffff8
005106d9 add esp, 4
005106dc push ebp
005106dd mov ebp, dword ptr [ebx + 4]
005106e0 mov dword ptr [esp + 4], ebp
005106e4 mov ebp, esp
005106e6 sub esp, 0x100
005106ec mov eax, dword ptr [0xbaa3b4]
005106f1 xor eax, ebp
005106f3 mov dword ptr [ebp - 4], eax
005106f6 push esi
005106f7 push edi
005106f8 mov edi, ecx
005106fa mov eax, dword ptr [edi + 0xab4]
00510700 test eax, eax
00510702 jne 0x51073c
00510704 mov dword ptr [edi + 0xb00], 0x42b40000
0051070e mov eax, dword ptr [edi + 0x294]
00510714 mov dword ptr [edi + 0x28c], eax
0051071a mov eax, dword ptr [edi + 0x298]
00510720 mov dword ptr [edi + 0x290], eax
00510726 mov dword ptr [edi + 0xab4], 3
00510730 mov byte ptr [ebp - 0xdc], 1
00510737 jmp 0x51113c
0051073c movss xmm0, dword ptr [edi + 0x2c4]
00510744 mulss xmm0, dword ptr [0xb6a50c]
0051074c mov byte ptr [ebp - 0xe1], 1
00510753 movss dword ptr [edi + 0x2c4], xmm0
0051075b cmp eax, 3
0051075e jne 0x5107dd
00510760 push 0
00510762 push 0xb41e80
00510767 lea ecx, [edi + 0x3c]
0051076a call 0x4054f0
0051076f mov eax, dword ptr [edi + 0xab4]
00510775 cmp eax, 3
00510778 jne 0x5107dd
0051077a cmp dword ptr [edi + 0xaf0], 0
00510781 jg 0x5107dd
00510783 cmp dword ptr [edi + 0xe6c], -1
0051078a je 0x5107c1
0051078c push 9
0051078e mov ecx, edi
00510790 call 0x6af050
00510795 test al, al
00510797 jne 0x5107d3
00510799 movss xmm2, dword ptr [0xb6a434]
005107a1 lea eax, [ebp - 0xe0]
005107a7 push 0xc02fec
005107ac push eax
005107ad mov ecx, edi
005107af call 0x6af0c0
005107b4 mov ecx, eax
005107b6 call 0x962ca0
005107bb test al, al
005107bd jne 0x5107d3
005107bf jmp 0x5107dd
005107c1 call 0x6c3d90
005107c6 xor edx, edx
005107c8 mov ecx, 0x32
005107cd div ecx
005107cf test edx, edx
005107d1 jne 0x5107dd
005107d3 mov dword ptr [edi + 0xab4], 4
005107dd cmp dword ptr [edi + 0xe6c], -1
005107e4 movss xmm1, dword ptr [0xb6aa3c]
005107ec je 0x5107f7
005107ee cmp byte ptr [edi + 0x169], 0
005107f5 je 0x510876
005107f7 movss xmm0, dword ptr [edi + 0x294]
005107ff subss xmm0, xmm1
00510803 movss xmm2, dword ptr [0xb6a480]
0051080b mov eax, dword ptr [0xbfd65c]
00510810 divss xmm0, xmm1
00510814 mov ecx, dword ptr [eax + 0x18190]
0051081a addss xmm0, xmm2
0051081e cvttss2si esi, xmm0
00510822 test esi, esi
00510824 js 0x510876
00510826 mov eax, dword ptr [ecx + 0xc]
00510829 cmp esi, eax
0051082b jge 0x510876
0051082d movss xmm0, dword ptr [edi + 0x298]
00510835 subss xmm0, dword ptr [0xb6ab20]
0051083d divss xmm0, xmm1
00510841 addss xmm0, xmm2
00510845 cvttss2si edx, xmm0
00510849 test edx, edx
0051084b js 0x510876
0051084d cmp edx, dword ptr [ecx + 0x10]
00510850 jge 0x510876
00510852 imul eax, edx
00510855 add eax, esi
00510857 cmp eax, 0x1bf
0051085c ja 0x510876
0051085e cmp dword ptr [ecx + eax*4 + 0x76c], 0x3b6
00510869 jg 0x510876
0051086b mov dword ptr [ecx + eax*4 + 0x76c], 0x384
00510876 cmp dword ptr [edi + 0xe6c], -1
0051087d movss xmm0, dword ptr [0xb6aae4]
00510885 je 0x5108b8
00510887 movss xmm3, dword ptr [edi + 0xb00]
0051088f comiss xmm3, xmm0
00510892 jb 0x5108a9
00510894 cmp byte ptr [edi + 0xe45], 0
0051089b je 0x5108b8
0051089d mov dword ptr [edi + 0xdf0], 0
005108a7 jmp 0x5108b8
005108a9 push 1
005108ab movaps xmm2, xmm0
005108ae xorps xmm1, xmm1
005108b1 mov ecx, edi
005108b3 call 0x6afbd0
005108b8 mov edx, dword ptr [edi + 0xaf0]
005108be test edx, edx
005108c0 jle 0x5108e4
005108c2 cvttss2si eax, dword ptr [edi + 0x2fc]
005108ca cvttss2si ecx, dword ptr [edi + 0x2f8]
005108d2 sub ecx, eax
005108d4 add edx, ecx
005108d6 mov dword ptr [edi + 0xaf0], edx
005108dc test edx, edx
005108de jg 0x5109e0
005108e4 movss xmm1, dword ptr [0xb6abf8]
005108ec mov ecx, edi
005108ee push 7
005108f0 push 0
005108f2 call 0x6a15a0
005108f7 test al, al
005108f9 je 0x5109e0
005108ff cmp dword ptr [edi + 0xe6c], -1
00510906 je 0x510915
00510908 cmp dword ptr [edi + 0xab4], 3
0051090f jne 0x5109e0
00510915 push 0
00510917 push 0xb40254
0051091c lea ecx, [edi + 0x3c]
0051091f call 0x4054f0
00510924 mov ecx, edi
00510926 mov byte ptr [edi + 0x169], 1
0051092d call 0x695680
00510932 cmp dword ptr [edi + 0xe6c], -1
00510939 movss xmm1, dword ptr [eax + 0x294]
00510941 subss xmm1, dword ptr [edi + 0x294]
00510949 movss dword ptr [ebp - 0xdc], xmm1
00510951 jne 0x51096d
00510953 movss xmm0, dword ptr [0xc02fec]
0051095b movss dword ptr [edi + 0xe70], xmm0
00510963 movss xmm0, dword ptr [0xc02ff0]
0051096b jmp 0x5109a3
0051096d movss xmm2, dword ptr [0xb6a2cc]
00510975 lea eax, [ebp - 0xf4]
0051097b push eax
0051097c mov ecx, edi
0051097e call 0x6af380
00510983 movss xmm0, dword ptr [ebp - 0xf4]
0051098b movss xmm1, dword ptr [ebp - 0xdc]
00510993 movss dword ptr [edi + 0xe70], xmm0
0051099b movss xmm0, dword ptr [ebp - 0xf0]
005109a3 movss dword ptr [edi + 0xe74], xmm0
005109ab cmp dword ptr [edi + 0xe6c], -1
005109b2 je 0x5109bc
005109b4 movss xmm1, dword ptr [edi + 0xe70]
005109bc comiss xmm1, dword ptr [0xb6a18c]
005109c3 mov dword ptr [edi + 0xab4], 8
005109cd mov dword ptr [edi + 0xaf0], 0x3f
005109d7 seta al
005109da mov byte ptr [edi + 0x13c], al
005109e0 lea esi, [edi + 0x364]
005109e6 mov ecx, esi
005109e8 call 0x7a6e20
005109ed cmp byte ptr [edi + 0x169], 0
005109f4 je 0x510a53
005109f6 movss xmm0, dword ptr [edi + 0x2f4]
005109fe lea eax, [ebp - 0xf0]
00510a04 addss xmm0, dword ptr [edi + 0xb00]
00510a0c xorps xmm1, xmm1
00510a0f mov dword ptr [ebp - 0xdc], 0
00510a19 lea ecx, [ebp - 0xdc]
00510a1f mov dword ptr [ebp - 0xe8], 0x42b40000
00510a29 comiss xmm1, xmm0
00510a2c movss dword ptr [ebp - 0xf0], xmm0
00510a34 cmovbe ecx, eax
00510a37 lea eax, [ebp - 0xe8]
00510a3d movss xmm0, dword ptr [ecx]
00510a41 comiss xmm0, dword ptr [0xb6aae4]
00510a48 cmovbe eax, ecx
00510a4b mov eax, dword ptr [eax]
00510a4d mov dword ptr [edi + 0xb00], eax
00510a53 cmp dword ptr [edi + 0xab4], 4
00510a5a movss xmm0, dword ptr [0xb6a614]
00510a62 movss dword ptr [ebp - 0xf0], xmm0
00510a6a jne 0x510e16
00510a70 push 0
00510a72 lea ecx, [edi + 0x3c]
00510a75 push 0xb421d4
00510a7a call 0x4054f0
00510a7f cmp dword ptr [edi + 0x70], 0
00510a83 je 0x510a92
00510a85 cmp byte ptr [edi + 0x80], 0
00510a8c jne 0x510bf5
00510a92 cmp dword ptr [edi + 0xe6c], -1
00510a99 mov byte ptr [edi + 0x169], 0
00510aa0 mov dword ptr [edi + 0x180], 0
00510aaa jne 0x510c02
00510ab0 mov esi, dword ptr [0xbfd65c]
00510ab6 lea eax, [ebp - 0xe0]
00510abc push ecx
00510abd mov dword ptr [esp], 0x41a00000
00510ac4 push eax
00510ac5 mov ecx, dword ptr [esi + 0x18190]
00510acb call 0x7d9b50
00510ad0 lea eax, [ebp - 0xe0]
00510ad6 mov ecx, esi
00510ad8 push eax
00510ad9 call 0x6d5e30
00510ade movss xmm1, dword ptr [ebp - 0xe0]
00510ae6 movss xmm2, dword ptr [ebp - 0xdc]
00510aee movss xmm4, dword ptr [0xb6c980]
00510af6 subss xmm1, dword ptr [eax + 0x294]
00510afe subss xmm2, dword ptr [eax + 0x298]
00510b06 movaps xmm0, xmm1
00510b09 movaps xmm3, xmm2
00510b0c mulss xmm0, xmm1
00510b10 mulss xmm3, xmm2
00510b14 andps xmm1, xmm4
00510b17 addss xmm3, xmm0
00510b1b movss xmm0, dword ptr [0xb6a9c8]
00510b23 comiss xmm0, xmm1
00510b26 ja 0x510b30
00510b28 andps xmm2, xmm4
00510b2b comiss xmm0, xmm2
00510b2e jbe 0x510b3d
00510b30 movss xmm0, dword ptr [0xb6ad88]
00510b38 comiss xmm0, xmm3
00510b3b ja 0x510bb5
00510b3d movss xmm0, dword ptr [0xb6ad60]
00510b45 comiss xmm0, xmm3
00510b48 ja 0x510bb5
00510b4a mov eax, dword ptr [0xbfd65c]
00510b4f mov esi, dword ptr [eax + 0x18190]
00510b55 lea eax, [ebp - 0xe0]
00510b5b push eax
00510b5c mov ecx, esi
00510b5e call 0x7ceaa0
00510b63 cmp eax, 0x1bf
00510b68 ja 0x510b77
00510b6a cmp dword ptr [esi + eax*4 + 0x76c], 0x1f4
00510b75 jge 0x510bb5
00510b77 cdq 
00510b78 idiv dword ptr [esi + 0xc]
00510b7b movss xmm2, dword ptr [0xb6aa3c]
00510b83 movd xmm1, edx
00510b87 movd xmm0, eax
00510b8b cvtdq2ps xmm1, xmm1
00510b8e cvtdq2ps xmm0, xmm0
00510b91 mulss xmm1, xmm2
00510b95 mulss xmm0, xmm2
00510b99 addss xmm1, xmm2
00510b9d addss xmm0, dword ptr [0xb6ab20]
00510ba5 movss dword ptr [edi + 0x28c], xmm1
00510bad movss dword ptr [edi + 0x290], xmm0
00510bb5 call 0x6c3d90
00510bba xor edx, edx
00510bbc mov ecx, 0x14
00510bc1 div ecx
00510bc3 test edx, edx
00510bc5 jne 0x510bef
00510bc7 push edx
00510bc8 push 0xb40360
00510bcd lea ecx, [edi + 0x3c]
00510bd0 mov dword ptr [edi + 0xab4], 6
00510bda call 0x4054f0
00510bdf push 1
00510be1 mov ecx, edi
00510be3 mov byte ptr [edi + 0x169], 1
00510bea call 0x6971a0
00510bef lea esi, [edi + 0x364]
00510bf5 cmp dword ptr [edi + 0xe6c], -1
00510bfc je 0x510e20
00510c02 cmp byte ptr [edi + 0x169], 0
00510c09 je 0x510c4b
00510c0b push 0xb40e34
00510c10 lea eax, [ebp - 0xfc]
00510c16 mov ecx, edi
00510c18 push eax
00510c19 call 0x68e000
00510c1e mov ecx, eax
00510c20 movss xmm0, dword ptr [ecx]
00510c24 ucomiss xmm0, dword ptr [0xc02fec]
00510c2b lahf 
00510c2c test ah, 0x44
00510c2f jp 0x510e20
00510c35 movss xmm0, dword ptr [ecx + 4]
00510c3a ucomiss xmm0, dword ptr [0xc02ff0]
00510c41 lahf 
00510c42 test ah, 0x44
00510c45 jp 0x510e20
00510c4b movss xmm2, dword ptr [0xb6ae44]
00510c53 mov ecx, edi
00510c55 push 2
00510c57 call 0x6af8d0
00510c5c movss xmm1, dword ptr [edi + 0xb00]
00510c64 subss xmm1, dword ptr [edi + 0x2f4]
00510c6c movss xmm0, dword ptr [0xb6af0c]
00510c74 comiss xmm0, xmm1
00510c77 movss dword ptr [edi + 0xb00], xmm1
00510c7f jb 0x510d0c
00510c85 mov edx, dword ptr [edi]
00510c87 lea ecx, [ebp - 0x2c]
00510c8a push 0x1e
00510c8c mov dword ptr [edi + 0xb00], 0
00510c96 call 0x427290
00510c9b push eax
00510c9c push 0
00510c9e push 0
00510ca0 push ecx
00510ca1 mov ecx, edi
00510ca3 mov dword ptr [esp], 0x40a00000
00510caa call dword ptr [edx + 0x20]
00510cad push ecx
00510cae mov dword ptr [esp], 0x3f800000
00510cb5 lea ecx, [ebp - 0x30]
00510cb8 push 0xc02fec
00510cbd mov dword ptr [ebp - 0xdc], 1
00510cc7 call 0x402120
00510ccc movss xmm3, dword ptr [0xb6a9c8]
00510cd4 lea ecx, [edi + 0x294]
00510cda push eax
00510cdb lea eax, [ebp - 0xdc]
00510ce1 mov edx, 1
00510ce6 push edi
00510ce7 push eax
00510ce8 call 0x68a580
00510ced add esp, 0x10
00510cf0 mov dword ptr [esp], 0x40000000
00510cf7 push 0
00510cf9 push 2
00510cfb push ecx
00510cfc mov dword ptr [esp], 0x3f000000
00510d03 mov ecx, edi
00510d05 push 0x4d
00510d07 call 0x6ad720
00510d0c push 1
00510d0e push 0
00510d10 push ecx
00510d11 mov dword ptr [esp], 0x40400000
00510d18 mov ecx, esi
00510d1a push 0xc02fec
00510d1f call 0x7a3650
00510d24 mov eax, dword ptr [edi + 0xe6c]
00510d2a mov byte ptr [ebp - 0xe1], 0
00510d31 cmp eax, -1
00510d34 je 0x510d43
00510d36 push edi
00510d37 push eax
00510d38 push 9
00510d3a call 0x8b10b0
00510d3f test al, al
00510d41 jne 0x510d5e
00510d43 movss xmm1, dword ptr [0xb6accc]
00510d4b mov ecx, edi
00510d4d push 7
00510d4f push 0
00510d51 call 0x6a15a0
00510d56 test al, al
00510d58 je 0x510de9
00510d5e mov eax, dword ptr [0xbfd65c]
00510d63 lea esi, [edi + 0x294]
00510d69 push dword ptr [esi + 4]
00510d6c push dword ptr [esi]
00510d6e mov eax, dword ptr [eax + 0x18190]
00510d74 mov ecx, eax
00510d76 mov dword ptr [ebp - 0xdc], eax
00510d7c call 0x7aee40
00510d81 test eax, eax
00510d83 jne 0x510de9
00510d85 mov ecx, dword ptr [ebp - 0xdc]
00510d8b push esi
00510d8c call 0x7ce8d0
00510d91 cmp eax, 0x384
00510d96 jge 0x510de9
00510d98 movss xmm2, dword ptr [0xb6aa8c]
00510da0 sub esp, 8
00510da3 mov ecx, edi
00510da5 push esi
00510da6 call 0x690880
00510dab test al, al
00510dad jne 0x510de9
00510daf mov eax, dword ptr [esi]
00510db1 lea ecx, [edi + 0x3c]
00510db4 mov dword ptr [edi + 0x28c], eax
00510dba mov eax, dword ptr [esi + 4]
00510dbd push 0
00510dbf mov dword ptr [edi + 0x290], eax
00510dc5 push 0xb40360
00510dca mov dword ptr [edi + 0xab4], 6
00510dd4 call 0x4054f0
00510dd9 push 1
00510ddb mov ecx, edi
00510ddd mov byte ptr [edi + 0x169], 1
00510de4 call 0x6971a0
00510de9 movss xmm1, dword ptr [edi + 0x2b8]
00510df1 movaps xmm0, xmm1
00510df4 andps xmm0, xmmword ptr [0xb6c980]
00510dfb comiss xmm0, dword ptr [0xb6a614]
00510e02 jbe 0x510e20
00510e04 comiss xmm1, dword ptr [0xb6a18c]
00510e0b seta al
00510e0e mov byte ptr [edi + 0x13c], al
00510e14 jmp 0x510e20
00510e16 mov dword ptr [edi + 0x180], 4
00510e20 cmp dword ptr [edi + 0x70], 0
00510e24 je 0x510ec9
00510e2a push 0xb400b4
00510e2f lea ecx, [edi + 0x6c]
00510e32 call 0x405e90
00510e37 test al, al
00510e39 je 0x510ec9
00510e3f movss xmm0, dword ptr [0xb6a614]
00510e47 mov eax, dword ptr [edi + 0xbb4]
00510e4d movss dword ptr [ebp - 0xe8], xmm0
00510e55 cmp eax, 0x12
00510e58 jne 0x510e64
00510e5a movss xmm0, dword ptr [0xb6a6f0]
00510e62 jmp 0x510e71
00510e64 cmp eax, 0x13
00510e67 jne 0x510e79
00510e69 movss xmm0, dword ptr [0xb6a480]
00510e71 movss dword ptr [ebp - 0xe8], xmm0
00510e79 mov esi, dword ptr [0xbfd680]
00510e7f lea ecx, [ebp - 0xdc]
00510e85 mov dword ptr [ebp - 0xdc], 0x48
00510e8f call 0x8b1340
00510e94 movss xmm0, dword ptr [ebp - 0xe8]
00510e9c sub esp, 8
00510e9f mov dword ptr [esp + 4], 0
00510ea7 movss dword ptr [esp], xmm0
00510eac push 0
00510eae push 2
00510eb0 push ecx
00510eb1 mov dword ptr [esp], 0x3f800000
00510eb8 lea ecx, [esi + 0x29de0]
00510ebe push dword ptr [ebp - 0xdc]
00510ec4 call 0x888de0
00510ec9 cmp dword ptr [edi + 0xab4], 8
00510ed0 jne 0x510ef2
00510ed2 cmp dword ptr [edi + 0x70], 0
00510ed6 je 0x510ee9
00510ed8 push 0xb400ac
00510edd lea ecx, [edi + 0x6c]
00510ee0 call 0x405f30
00510ee5 test al, al
00510ee7 jne 0x510ef2
00510ee9 push 0
00510eeb mov ecx, edi
00510eed call 0x6afe20
00510ef2 cmp dword ptr [edi + 0xe6c], -1
00510ef9 je 0x510f39
00510efb cmp dword ptr [edi + 0xab4], 6
00510f02 jne 0x510f39
00510f04 cmp dword ptr [edi + 0x70], 0
00510f08 je 0x5110d6
00510f0e push 0xb400ac
00510f13 lea ecx, [edi + 0x6c]
00510f16 call 0x405f30
00510f1b test al, al
00510f1d je 0x510f39
00510f1f cmp dword ptr [edi + 0x70], 0
00510f23 je 0x5110d6
00510f29 mov eax, dword ptr [edi + 0x70]
00510f2c lea ecx, [edi + 0x6c]
00510f2f mov eax, dword ptr [eax + 0x30]
00510f32 dec eax
00510f33 push eax
00510f34 call 0x403b00
00510f39 cmp dword ptr [edi + 0x70], 0
00510f3d je 0x5110d6
00510f43 push 0xb400ac
00510f48 lea ecx, [edi + 0x6c]
00510f4b call 0x405e90
00510f50 test al, al
00510f52 je 0x5110c7
00510f58 mov eax, dword ptr [edi + 0xbb4]
00510f5e cmp eax, 0x12
00510f61 jne 0x510f6d
00510f63 movss xmm0, dword ptr [0xb6a6f0]
00510f6b jmp 0x510f7a
00510f6d cmp eax, 0x13
00510f70 jne 0x510f82
00510f72 movss xmm0, dword ptr [0xb6a480]
00510f7a movss dword ptr [ebp - 0xf0], xmm0
00510f82 mov esi, dword ptr [0xbfd680]
00510f88 lea ecx, [ebp - 0xdc]
00510f8e mov dword ptr [ebp - 0xdc], 0xe2
00510f98 call 0x8b1340
00510f9d movss xmm0, dword ptr [ebp - 0xf0]
00510fa5 sub esp, 8
00510fa8 mov dword ptr [esp + 4], 0
00510fb0 movss dword ptr [esp], xmm0
00510fb5 push 0
00510fb7 push 2
00510fb9 push ecx
00510fba mov dword ptr [esp], 0x3f800000
00510fc1 lea ecx, [esi + 0x29de0]
00510fc7 push dword ptr [ebp - 0xdc]
00510fcd call 0x888de0
00510fd2 mov ecx, edi
00510fd4 call 0x695680
00510fd9 cmp dword ptr [edi + 0xe6c], -1
00510fe0 lea esi, [edi + 0x294]
00510fe6 movss xmm1, dword ptr [eax + 0x294]
00510fee movss xmm2, dword ptr [eax + 0x298]
00510ff6 subss xmm1, dword ptr [esi]
00510ffa subss xmm2, dword ptr [esi + 4]
00510fff movss dword ptr [ebp - 0xdc], xmm1
00511007 movss dword ptr [ebp - 0xec], xmm1
0051100f movss dword ptr [ebp - 0xf0], xmm2
00511017 movss dword ptr [ebp - 0xe8], xmm2
0051101f je 0x511051
00511021 movss xmm1, dword ptr [edi + 0xe70]
00511029 movss xmm2, dword ptr [edi + 0xe74]
00511031 movss dword ptr [ebp - 0xdc], xmm1
00511039 movss dword ptr [ebp - 0xec], xmm1
00511041 movss dword ptr [ebp - 0xf0], xmm2
00511049 movss dword ptr [ebp - 0xe8], xmm2
00511051 movaps xmm0, xmm1
00511054 mulss xmm0, xmm1
00511058 movaps xmm1, xmm2
0051105b mulss xmm1, xmm2
0051105f addss xmm0, xmm1
00511063 call 0x4228c0
00511068 comiss xmm0, dword ptr [0xb6a18c]
0051106f jbe 0x5110a4
00511071 movss xmm1, dword ptr [0xb6a928]
00511079 divss xmm1, xmm0
0051107d movaps xmm0, xmm1
00511080 mulss xmm0, dword ptr [ebp - 0xdc]
00511088 movss dword ptr [ebp - 0xec], xmm0
00511090 movss xmm0, dword ptr [ebp - 0xf0]
00511098 mulss xmm0, xmm1
0051109c movss dword ptr [ebp - 0xe8], xmm0
005110a4 lea ecx, [ebp - 0xd8]
005110aa call 0x430d70
005110af lea eax, [ebp - 0xd8]
005110b5 mov ecx, edi
005110b7 push eax
005110b8 push 2
005110ba lea eax, [ebp - 0xec]
005110c0 push eax
005110c1 push esi
005110c2 call 0x6a1a20
005110c7 cmp dword ptr [edi + 0x70], 0
005110cb je 0x5110d6
005110cd cmp byte ptr [edi + 0x80], 0
005110d4 jne 0x5110fc
005110d6 mov eax, dword ptr [edi + 0xab4]
005110dc cmp eax, 6
005110df jne 0x5110ed
005110e1 mov dword ptr [edi + 0xab4], 3
005110eb jmp 0x5110fc
005110ed cmp eax, 8
005110f0 jne 0x5110fc
005110f2 mov dword ptr [edi + 0xab4], 4
005110fc cmp byte ptr [ebp - 0xe1], 0
00511103 je 0x511135
00511105 movss xmm1, dword ptr [edi + 0x28c]
0051110d movss xmm0, dword ptr [edi + 0x290]
00511115 subss xmm1, dword ptr [edi + 0x294]
0051111d subss xmm0, dword ptr [edi + 0x298]
00511125 movss dword ptr [edi + 0x2b8], xmm1
0051112d movss dword ptr [edi + 0x2bc], xmm0
00511135 mov byte ptr [ebp - 0xdc], 0
0051113c push dword ptr [ebp - 0xdc]
00511142 mov ecx, edi
00511144 call 0x6971a0
00511149 mov ecx, dword ptr [ebp - 4]
0051114c pop edi
0051114d xor ecx, ebp
0051114f pop esi
00511150 call 0x9eacd7
00511155 mov esp, ebp
00511157 pop ebp
00511158 mov esp, ebx
0051115a pop ebx
0051115b ret 
