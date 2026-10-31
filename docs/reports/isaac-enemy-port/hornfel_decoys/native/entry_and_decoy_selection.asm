; Installed Repentance 1.7.9b; bounded evidence, names are interpretations.
004a5120 push ebx
004a5121 mov ebx, esp
004a5123 sub esp, 8
004a5126 and esp, 0xfffffff8
004a5129 add esp, 4
004a512c push ebp
004a512d mov ebp, dword ptr [ebx + 4]
004a5130 mov dword ptr [esp + 4], ebp
004a5134 mov ebp, esp
004a5136 push -1
004a5138 push 0x9ee24d
004a513d mov eax, dword ptr fs:[0]
004a5143 push eax
004a5144 push ebx
004a5145 sub esp, 0x48
004a5148 mov eax, dword ptr [0xbaa3b4]
004a514d xor eax, ebp
004a514f mov dword ptr [ebp - 0x14], eax
004a5152 push esi
004a5153 push edi
004a5154 push eax
004a5155 lea eax, [ebp - 0xc]
004a5158 mov dword ptr fs:[0], eax
004a515e mov edi, ecx
004a5160 mov dword ptr [ebp - 0x44], edi
004a5163 cmp dword ptr [edi + 0xab4], 7
004a516a jne 0x4a5588
004a5170 mov esi, dword ptr [edi + 0xb3c]
004a5176 lea eax, [edi + 0xb3c]
004a517c mov dword ptr [ebp - 0x3c], esi
004a517f test esi, esi
004a5181 je 0x4a5588
004a5187 mov dword ptr [ebp - 0x30], eax
004a518a lea ecx, [esi + 0x324]
004a5190 lea eax, [ebp - 0x30]
004a5193 push eax
004a5194 call 0x4bc3c0
004a5199 mov dword ptr [edi + 0xb3c], 0
004a51a3 lea eax, [ebp - 0x4c]
004a51a6 mov ecx, esi
004a51a8 push eax
004a51a9 call 0x4a8340
004a51ae movss xmm1, dword ptr [ebp - 0x4c]
004a51b3 movss xmm0, dword ptr [0xc02fec]
004a51bb ucomiss xmm1, xmm0
004a51be movss xmm1, dword ptr [ebp - 0x48]
004a51c3 lahf 
004a51c4 test ah, 0x44
004a51c7 jp 0x4a51f2
004a51c9 ucomiss xmm1, dword ptr [0xc02ff0]
004a51d0 lahf 
004a51d1 test ah, 0x44
004a51d4 jp 0x4a51f2
004a51d6 push 0xb41ca0
004a51db push 3
004a51dd call 0x95e330
004a51e2 movss xmm0, dword ptr [0xc02fec]
004a51ea add esp, 8
004a51ed movss xmm1, dword ptr [ebp - 0x48]
004a51f2 movss xmm2, dword ptr [ebp - 0x4c]
004a51f7 ucomiss xmm2, xmm0
004a51fa lahf 
004a51fb test ah, 0x44
004a51fe jp 0x4a5211
004a5200 ucomiss xmm1, dword ptr [0xc02ff0]
004a5207 lahf 
004a5208 test ah, 0x44
004a520b jnp 0x4a59e6
004a5211 mov eax, dword ptr [edi + 0x32c]
004a5217 mov ecx, eax
004a5219 push 1
004a521b mov dword ptr [ebp - 0x34], eax
004a521e call 0x4bc2a0
004a5223 mov ecx, dword ptr [ebp - 0x34]
004a5226 lea eax, [ebp - 0x4c]
004a5229 push eax
004a522a lea eax, [esi + 0x28c]
004a5230 push eax
004a5231 call 0x4bc1e0
004a5236 mov eax, dword ptr [ebp - 0x34]
004a5239 movss xmm0, dword ptr [eax + 0x294]
004a5241 movss xmm1, dword ptr [eax + 0x298]
004a5249 mov eax, dword ptr [edi + 0x288]
004a524f movss dword ptr [edi + 0x294], xmm0
004a5257 movss dword ptr [edi + 0x298], xmm1
004a525f mov byte ptr [edi + 0x169], 1
004a5266 mov dword ptr [edi + 0x180], 4
004a5270 mov eax, dword ptr [eax + 0x24]
004a5273 mov dword ptr [edi + 0x150], eax
004a5279 cmp dword ptr [esi + 0x31c], 0
004a5280 jne 0x4a52db
004a5282 mov eax, dword ptr [esi + 0x314]
004a5288 test eax, eax
004a528a je 0x4a5295
004a528c cmp dword ptr [eax + 0x31c], 0
004a5293 jne 0x4a52db
004a5295 lea eax, [esi + 0x31c]
004a529b mov ecx, edi
004a529d mov dword ptr [eax], edi
004a529f push eax
004a52a0 call 0x4bae70
004a52a5 mov esi, dword ptr [esi + 0x314]
004a52ab test esi, esi
004a52ad je 0x4a52db
004a52af mov ecx, dword ptr [esi + 0x31c]
004a52b5 add esi, 0x31c
004a52bb test ecx, ecx
004a52bd je 0x4a52d1
004a52bf lea eax, [ebp - 0x50]
004a52c2 mov dword ptr [ebp - 0x50], esi
004a52c5 push eax
004a52c6 add ecx, 0x324
004a52cc call 0x4bc3c0
004a52d1 push esi
004a52d2 mov ecx, edi
004a52d4 mov dword ptr [esi], edi
004a52d6 call 0x4bae70
004a52db cmp dword ptr [edi + 0xab4], 6
004a52e2 mov esi, dword ptr [edi + 0x314]
004a52e8 mov dword ptr [ebp - 0x38], esi
004a52eb jne 0x4a5731
004a52f1 cmp byte ptr [edi + 0xaf1], 0
004a52f8 ja 0x4a5695
004a52fe call 0x6c3d90
004a5303 and eax, 7
004a5306 jne 0x4a5695
004a530c test esi, esi
004a530e je 0x4a531d
004a5310 cmp dword ptr [esi + 0x3ac], 4
004a5317 jle 0x4a5695
004a531d mov ecx, dword ptr [0xbfd65c]
004a5323 xor esi, esi
004a5325 mov edx, dword ptr [ecx + 0x18190]
004a532b mov eax, dword ptr [edx + 0x12c0]
004a5331 add eax, dword ptr [edx + 0x12c4]
004a5337 test eax, eax
004a5339 cmovg esi, eax
004a533c mov eax, dword ptr [edx + 0x12c8]
004a5342 add eax, dword ptr [edx + 0x12cc]
004a5348 xor ecx, ecx
004a534a test eax, eax
004a534c cmovg ecx, eax
004a534f sub esi, ecx
004a5351 cmp esi, 2
004a5354 jge 0x4a5695
004a535a call 0x4a8150
004a535f test eax, eax
004a5361 je 0x4a5695
004a5367 mov eax, dword ptr [0xbfd65c]
004a536c mov dword ptr [ebp - 0x30], 0
004a5373 mov eax, dword ptr [eax + 0x18190]
004a5379 mov ecx, dword ptr [eax + 0x10]
004a537c imul ecx, dword ptr [eax + 0xc]
004a5380 xor eax, eax
004a5382 cmp ecx, 0x87
004a5388 setg al
004a538b add eax, 2
004a538e mov dword ptr [ebp - 0x44], eax
004a5391 call 0x4a8150
004a5396 mov dword ptr [ebp - 0x34], eax
004a5399 test eax, eax
004a539b je 0x4a552c
004a53a1 call 0x6c3d90
004a53a6 mov ecx, dword ptr [0xbfd65c]
004a53ac push eax
004a53ad push 0
004a53af push edi
004a53b0 push 0xc02fec
004a53b5 push 0xc02fec
004a53ba push 1
004a53bc push 0x38a
004a53c1 call 0x422e20
004a53c6 mov esi, eax
004a53c8 mov ecx, dword ptr [esi + 0x164]
004a53ce mov edx, dword ptr [esi]
004a53d0 and dword ptr [esi + 0x160], 0xfffffffb
004a53d7 mov dword ptr [esi + 0x164], ecx
004a53dd mov ecx, esi
004a53df call dword ptr [edx + 0xc]
004a53e2 mov ecx, dword ptr [ebp - 0x34]
004a53e5 lea eax, [ebp - 0x4c]
004a53e8 push eax
004a53e9 call 0x4a8340
004a53ee push eax
004a53ef mov eax, dword ptr [ebp - 0x34]
004a53f2 mov ecx, esi
004a53f4 add eax, 0x28c
004a53f9 push eax
004a53fa call 0x68eff0
004a53ff mov dword ptr [ebp - 0x2c], 0
004a5406 push 0x30
004a5408 mov dword ptr [ebp - 0x3c], eax
004a540b mov dword ptr [ebp - 0x1c], 0
004a5412 mov dword ptr [ebp - 0x18], 0xf
004a5419 mov byte ptr [ebp - 0x2c], 0
004a541d call 0x407de0
004a5422 movups xmm0, xmmword ptr [0xb41c38]
004a5429 mov dword ptr [ebp - 0x1c], 0x21
004a5430 mov dword ptr [ebp - 0x18], 0x2f
004a5437 movups xmmword ptr [eax], xmm0
004a543a movups xmm0, xmmword ptr [0xb41c48]
004a5441 movups xmmword ptr [eax + 0x10], xmm0
004a5445 mov cl, byte ptr [0xb41c58]
004a544b mov byte ptr [eax + 0x20], cl
004a544e mov byte ptr [eax + 0x21], 0
004a5452 mov dword ptr [ebp - 0x2c], eax
004a5455 mov dword ptr [ebp - 4], 0
004a545c lea eax, [ebp - 0x2c]
004a545f mov ecx, dword ptr [ebp - 0x3c]
004a5462 push 1
004a5464 push eax
004a5465 add ecx, 0x3c
004a5468 call 0x407160
004a546d mov dword ptr [ebp - 4], 0xffffffff
004a5474 mov edx, dword ptr [ebp - 0x18]
004a5477 cmp edx, 0x10
004a547a jb 0x4a54a8
004a547c mov ecx, dword ptr [ebp - 0x2c]
004a547f inc edx
004a5480 mov eax, ecx
004a5482 cmp edx, 0x1000
004a5488 jb 0x4a549e
004a548a mov ecx, dword ptr [ecx - 4]
004a548d add edx, 0x23
004a5490 sub eax, ecx
004a5492 add eax, -4
004a5495 cmp eax, 0x1f
004a5498 ja 0x4a568f
004a549e push edx
004a549f push ecx
004a54a0 call 0x9eb08e
004a54a5 add esp, 8
004a54a8 mov ecx, dword ptr [ebp - 0x3c]
004a54ab mov eax, dword ptr [ecx]
004a54ad call dword ptr [eax + 0xc]
004a54b0 mov eax, dword ptr [ebp - 0x34]
004a54b3 cmp dword ptr [eax + 0x31c], 0
004a54ba jne 0x4a551c
004a54bc mov ecx, dword ptr [eax + 0x314]
004a54c2 test ecx, ecx
004a54c4 je 0x4a54cf
004a54c6 cmp dword ptr [ecx + 0x31c], 0
004a54cd jne 0x4a551c
004a54cf add eax, 0x31c
004a54d4 mov ecx, esi
004a54d6 push eax
004a54d7 mov dword ptr [eax], esi
004a54d9 call 0x4bae70
004a54de mov eax, dword ptr [ebp - 0x34]
004a54e1 mov eax, dword ptr [eax + 0x314]
004a54e7 test eax, eax
004a54e9 je 0x4a551c
004a54eb mov ecx, dword ptr [eax + 0x31c]
004a54f1 add eax, 0x31c
004a54f6 mov dword ptr [ebp - 0x3c], eax
004a54f9 test ecx, ecx
004a54fb je 0x4a5512
004a54fd mov dword ptr [ebp - 0x50], eax
004a5500 add ecx, 0x324
004a5506 lea eax, [ebp - 0x50]
004a5509 push eax
004a550a call 0x4bc3c0
004a550f mov eax, dword ptr [ebp - 0x3c]
004a5512 push eax
004a5513 mov ecx, esi
004a5515 mov dword ptr [eax], esi
004a5517 call 0x4bae70
004a551c mov esi, dword ptr [ebp - 0x30]
004a551f inc esi
004a5520 mov dword ptr [ebp - 0x30], esi
004a5523 cmp esi, dword ptr [ebp - 0x44]
004a5526 jl 0x4a5391
004a552c mov dword ptr [edi + 0xab4], 0xe
004a5536 call 0x6c3d90
004a553b xor edx, edx
004a553d mov byte ptr [edi + 0xaf1], 0x64
004a5544 mov ecx, 0x1e
004a5549 div ecx
004a554b mov eax, dword ptr [ebp - 0x38]
004a554e add edx, ecx
004a5550 mov word ptr [edi + 0xaf4], dx
004a5557 test eax, eax
004a5559 je 0x4a59e6
004a555f cmp dword ptr [eax + 0x3ac], 0x96
004a5569 jge 0x4a59e6
004a556f mov dword ptr [eax + 0x3ac], 0x96
004a5579 mov dword ptr [eax + 0x3b0], 0x96
004a5583 jmp 0x4a59e6
004a5588 call 0x4a8150
004a558d mov ecx, dword ptr [0xbfd65c]
004a5593 mov esi, eax
004a5595 mov dword ptr [ebp - 0x3c], esi
004a5598 mov eax, dword ptr [ecx + 0x18190]
004a559e xor ecx, ecx
004a55a0 mov dword ptr [ebp - 0x50], eax
004a55a3 mov dword ptr [ebp - 0x34], ecx
004a55a6 cmp dword ptr [eax + 0x1264], ecx
004a55ac jbe 0x4a5667
004a55b2 nop dword ptr [eax]
004a55b6 nop word ptr [eax + eax]
004a55c0 mov eax, dword ptr [eax + 0x125c]
004a55c6 mov esi, dword ptr [eax + ecx*4]
004a55c9 cmp dword ptr [esi + 0x28], 0x3c7
004a55d0 jne 0x4a5651
004a55d2 mov eax, dword ptr [esi + 0x31c]
004a55d8 lea edx, [esi + 0x31c]
004a55de cmp eax, edi
004a55e0 jne 0x4a5651
004a55e2 test eax, eax
004a55e4 jne 0x4a55fb
004a55e6 mov eax, dword ptr [esi + 0x314]
004a55ec test eax, eax
004a55ee je 0x4a5651
004a55f0 cmp dword ptr [eax + 0x31c], 0
004a55f7 jne 0x4a5616
004a55f9 jmp 0x4a5651
004a55fb lea ecx, [ebp - 0x30]
004a55fe mov dword ptr [ebp - 0x30], edx
004a5601 push ecx
004a5602 lea ecx, [eax + 0x324]
004a5608 call 0x4bc3c0
004a560d mov ecx, dword ptr [ebp - 0x34]
004a5610 lea edx, [esi + 0x31c]
004a5616 mov esi, dword ptr [esi + 0x314]
004a561c mov dword ptr [edx], 0
004a5622 test esi, esi
004a5624 je 0x4a5651
004a5626 mov ecx, dword ptr [esi + 0x31c]
004a562c add esi, 0x31c
004a5632 test ecx, ecx
004a5634 je 0x4a5648
004a5636 lea eax, [ebp - 0x30]
004a5639 mov dword ptr [ebp - 0x30], esi
004a563c push eax
004a563d add ecx, 0x324
004a5643 call 0x4bc3c0
004a5648 mov ecx, dword ptr [ebp - 0x34]
004a564b mov dword ptr [esi], 0
004a5651 mov eax, dword ptr [ebp - 0x50]
004a5654 inc ecx
004a5655 mov dword ptr [ebp - 0x34], ecx
004a5658 cmp ecx, dword ptr [eax + 0x1264]
004a565e jb 0x4a55c0
004a5664 mov esi, dword ptr [ebp - 0x3c]
004a5667 test esi, esi
004a5669 jne 0x4a51a3
004a566f push 0xb41cb8
004a5674 push 1
004a5676 call 0x95e330
004a567b mov eax, 0xf
004a5680 add esp, 8
004a5683 mov word ptr [edi + 0x360], ax
004a568a jmp 0x4a59e6
004a568f call dword ptr [0xa065ac]
004a5695 cmp dword ptr [edi + 0xab4], 6
004a569c jne 0x4a5731
004a56a2 cmp byte ptr [edi + 0xaf2], 0
004a56a9 ja 0x4a5731
004a56af call 0x6c3d90
004a56b4 test al, 7
004a56b6 jne 0x4a5731
004a56b8 mov esi, dword ptr [ebp - 0x3c]
004a56bb mov eax, dword ptr [esi + 0x314]
004a56c1 test eax, eax
004a56c3 je 0x4a5731
004a56c5 cmp eax, esi
004a56c7 je 0x4a5731
004a56c9 mov eax, dword ptr [ebp - 0x34]
004a56cc mov dword ptr [edi + 0xab4], 0xa
004a56d6 mov dword ptr [eax + 0xb08], 0x3dcccccd
004a56e0 lea eax, [edi + 0xb3c]
004a56e6 mov ecx, dword ptr [eax]
004a56e8 test ecx, ecx
004a56ea je 0x4a5704
004a56ec mov dword ptr [ebp - 0x38], eax
004a56ef add ecx, 0x324
004a56f5 lea eax, [ebp - 0x38]
004a56f8 push eax
004a56f9 call 0x4bc3c0
004a56fe lea eax, [edi + 0xb3c]
004a5704 push eax
004a5705 mov ecx, esi
004a5707 mov dword ptr [eax], esi
004a5709 call 0x4bae70
004a570e mov byte ptr [edi + 0xaf2], 0x64
004a5715 call 0x6c3d90
004a571a xor edx, edx
004a571c mov ecx, 3
004a5721 div ecx
004a5723 add dl, 6
004a5726 mov byte ptr [edi + 0xaf6], dl
004a572c jmp 0x4a59e6
004a5731 cmp dword ptr [edi + 0xab4], 7
004a5738 jne 0x4a5749
004a573a mov dword ptr [edi + 0xab4], 0xb
004a5744 jmp 0x4a59e6
004a5749 mov dword ptr [edi + 0xab4], 3
004a5753 call 0x6c3d90
004a5758 xor edx, edx
004a575a mov ecx, 0xf
004a575f div ecx
004a5761 add edx, ecx
004a5763 mov word ptr [edi + 0xaf4], dx
004a576a call 0x6c3d90
004a576f xor edx, edx
004a5771 mov ecx, 3
004a5776 div ecx
004a5778 test edx, edx
004a577a jne 0x4a59e6
004a5780 mov ecx, dword ptr [0xbfd65c]
004a5786 mov edx, dword ptr [ecx + 0x18190]
004a578c mov eax, dword ptr [edx + 0x1264]
004a5792 mov dword ptr [ebp - 0x38], eax
004a5795 test eax, eax
004a5797 je 0x4a57d7
004a5799 mov eax, dword ptr [edx + 0x125c]
004a579f xor ecx, ecx
004a57a1 mov edi, dword ptr [ebp - 0x38]
004a57a4 mov esi, dword ptr [eax]
004a57a6 mov edx, dword ptr [esi + 0x28]
004a57a9 cmp edx, 0x333
004a57af je 0x4a57bc
004a57b1 cmp edx, 4
004a57b4 jne 0x4a57bd
004a57b6 cmp dword ptr [esi + 0x2c], 0xe
004a57ba jne 0x4a57bd
004a57bc inc ecx
004a57bd add eax, 4
004a57c0 sub edi, 1
004a57c3 jne 0x4a57a4
004a57c5 mov edi, dword ptr [ebp - 0x44]
004a57c8 cmp ecx, 4
004a57cb mov ecx, dword ptr [0xbfd65c]
004a57d1 jae 0x4a59e6
004a57d7 mov eax, dword ptr [ecx + 0x1ba54]
004a57dd xor esi, esi
004a57df sub eax, dword ptr [ecx + 0x1ba50]
004a57e5 movss xmm0, dword ptr [0xb6adc0]
004a57ed sar eax, 2
004a57f0 movss dword ptr [ebp - 0x30], xmm0
004a57f5 test eax, eax
004a57f7 je 0x4a5863
004a57f9 nop dword ptr [eax]
004a5800 push esi
004a5801 call 0x412750
004a5806 mov ecx, dword ptr [0xbfd65c]
004a580c inc esi
004a580d movss xmm0, dword ptr [eax + 0x294]
004a5815 movss xmm1, dword ptr [eax + 0x298]
004a581d subss xmm0, dword ptr [edi + 0x294]
004a5825 subss xmm1, dword ptr [edi + 0x298]
004a582d mov eax, dword ptr [ecx + 0x1ba54]
004a5833 sub eax, dword ptr [ecx + 0x1ba50]
004a5839 sar eax, 2
004a583c mulss xmm0, xmm0
004a5840 mulss xmm1, xmm1
004a5844 addss xmm0, xmm1
004a5848 minss xmm0, dword ptr [ebp - 0x30]
004a584d movss dword ptr [ebp - 0x30], xmm0
004a5852 cmp esi, eax
004a5854 jb 0x4a5800
004a5856 comiss xmm0, dword ptr [0xb6ad68]
004a585d jbe 0x4a59e6
004a5863 mov dword ptr [ebp - 0x30], 2
004a586a nop word ptr [eax + eax]
004a5870 call 0x6c3d90
004a5875 mov esi, eax
004a5877 call 0x6c3d90
004a587c movd xmm0, eax
004a5880 cvtdq2pd xmm0, xmm0
004a5884 shr eax, 0x1f
004a5887 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a5890 cvtpd2ps xmm0, xmm0
004a5894 mulss xmm0, dword ptr [0xb6a19c]
004a589c mulss xmm0, dword ptr [0xb6aa3c]
004a58a4 subss xmm0, dword ptr [0xb6a9c8]
004a58ac mulss xmm0, dword ptr [0xb6a230]
004a58b4 movss dword ptr [ebp - 0x38], xmm0
004a58b9 call 0x411fe0
004a58be movss dword ptr [ebp - 0x44], xmm0
004a58c3 movss xmm0, dword ptr [ebp - 0x38]
004a58c8 call 0x412010
004a58cd movss xmm1, dword ptr [ebp - 0x48]
004a58d2 movaps xmm3, xmm0
004a58d5 movss xmm2, dword ptr [ebp - 0x4c]
004a58da mulss xmm2, dword ptr [ebp - 0x44]
004a58df movss xmm0, dword ptr [ebp - 0x4c]
004a58e4 mulss xmm1, xmm3
004a58e8 mulss xmm0, xmm3
004a58ec subss xmm2, xmm1
004a58f0 movss xmm1, dword ptr [ebp - 0x48]
004a58f5 mulss xmm1, dword ptr [ebp - 0x44]
004a58fa addss xmm1, xmm0
004a58fe movss dword ptr [ebp - 0x54], xmm2
004a5903 movss dword ptr [ebp - 0x50], xmm1
004a5908 call 0x6c3d90
004a590d movd xmm0, eax
004a5911 cvtdq2pd xmm0, xmm0
004a5915 shr eax, 0x1f
004a5918 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a5921 cvtpd2ps xmm0, xmm0
004a5925 mulss xmm0, dword ptr [0xb6a19c]
004a592d mulss xmm0, dword ptr [0xb6a874]
004a5935 addss xmm0, xmm0
004a5939 movss dword ptr [ebp - 0x38], xmm0
004a593e call 0x411fe0
004a5943 mulss xmm0, dword ptr [0xb6a910]
004a594b addss xmm0, dword ptr [edi + 0x294]
004a5953 movss dword ptr [ebp - 0x40], xmm0
004a5958 movss xmm0, dword ptr [ebp - 0x38]
004a595d call 0x412010
004a5962 mulss xmm0, dword ptr [0xb6a910]
004a596a lea eax, [ebp - 0x54]
004a596d mov ecx, dword ptr [0xbfd65c]
004a5973 push esi
004a5974 push 0
004a5976 addss xmm0, dword ptr [edi + 0x298]
004a597e push edi
004a597f push eax
004a5980 lea eax, [ebp - 0x40]
004a5983 push eax
004a5984 push 0
004a5986 push 0x333
004a598b movss dword ptr [ebp - 0x3c], xmm0
004a5990 call 0x422e20
004a5995 mov esi, eax
004a5997 mov ecx, dword ptr [esi + 0x314]
004a599d lea eax, [esi + 0x314]
004a59a3 test ecx, ecx
004a59a5 je 0x4a59bf
004a59a7 mov dword ptr [ebp - 0x38], eax
004a59aa add ecx, 0x324
004a59b0 lea eax, [ebp - 0x38]
004a59b3 push eax
004a59b4 call 0x4bc3c0
004a59b9 lea eax, [esi + 0x314]
004a59bf push eax
004a59c0 mov ecx, edi
004a59c2 mov dword ptr [eax], edi
004a59c4 call 0x4bae70
004a59c9 and dword ptr [esi + 0x160], 0xfffffffb
004a59d0 sub dword ptr [ebp - 0x30], 1
004a59d4 mov eax, dword ptr [esi + 0x164]
004a59da mov dword ptr [esi + 0x164], eax
004a59e0 jne 0x4a5870
004a59e6 mov ecx, dword ptr [ebp - 0xc]
004a59e9 mov dword ptr fs:[0], ecx
004a59f0 pop ecx
004a59f1 pop edi
004a59f2 pop esi
004a59f3 mov ecx, dword ptr [ebp - 0x14]
004a59f6 xor ecx, ebp
004a59f8 call 0x9eacd7
004a59fd mov esp, ebp
004a59ff pop ebp
004a5a00 mov esp, ebx
004a5a02 pop ebx
004a5a03 ret 
004a5a04 int3 
004a5a05 int3 
004a5a06 int3 
004a5a07 int3 
004a5a08 int3 
004a5a09 int3 
004a5a0a int3 
004a5a0b int3 
004a5a0c int3 
004a5a0d int3 
004a5a0e int3 
004a5a0f int3 
