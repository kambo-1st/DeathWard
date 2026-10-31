008d5090 push ebp
008d5091 mov ebp, esp
008d5093 push -1
008d5095 push 0x9ff930
008d509a mov eax, dword ptr fs:[0]
008d50a0 push eax
008d50a1 sub esp, 0x1a4
008d50a7 push esi
008d50a8 push edi
008d50a9 mov eax, dword ptr [0xbaa3b4]
008d50ae xor eax, ebp
008d50b0 push eax
008d50b1 lea eax, [ebp - 0xc]
008d50b4 mov dword ptr fs:[0], eax
008d50ba mov edi, ecx
008d50bc mov dword ptr [ebp - 0x58], edi
008d50bf cmp byte ptr [edi + 0x169], 0
008d50c6 je 0x8d65b9
008d50cc mov al, byte ptr [edi + 0x3ad]
008d50d2 test al, al
008d50d4 js 0x8d65b9
008d50da je 0x8d65b9
008d50e0 cmp dword ptr [edi + 0xbc], 0
008d50e7 jg 0x8d5107
008d50e9 cmp dword ptr [edi + 0x50], 0x10
008d50ed lea eax, [edi + 0x3c]
008d50f0 jb 0x8d50f5
008d50f2 mov eax, dword ptr [edi + 0x3c]
008d50f5 push 0
008d50f7 push eax
008d50f8 push 0xa0830c
008d50fd push 3
008d50ff call 0x95e330
008d5104 add esp, 0x10
008d5107 mov ecx, dword ptr [edi + 0xb8]
008d510d lea eax, [ebp - 0x30]
008d5110 push eax
008d5111 call 0x403540
008d5116 mov ecx, dword ptr [eax]
008d5118 mov dword ptr [ebp - 0x34], ecx
008d511b mov dword ptr [ebp - 4], 0
008d5122 mov ecx, dword ptr [ebp - 0x2c]
008d5125 test ecx, ecx
008d5127 je 0x8d5146
008d5129 mov eax, dword ptr [ecx]
008d512b mov eax, dword ptr [eax + 0xc]
008d512e call eax
008d5130 test al, al
008d5132 je 0x8d5146
008d5134 mov eax, dword ptr [0xbfd62c]
008d5139 test eax, eax
008d513b je 0x8d5146
008d513d lea ecx, [ebp - 0x30]
008d5140 push ecx
008d5141 call eax
008d5143 add esp, 4
008d5146 cmp dword ptr [ebp - 0x34], 0
008d514a mov dword ptr [ebp - 4], 0xffffffff
008d5151 jne 0x8d5164
008d5153 push 0xb59354
008d5158 push 0
008d515a call 0x95e330
008d515f jmp 0x8d65b6
008d5164 mov eax, 1
008d5169 lea ecx, [edi + 0x6c]
008d516c cmp eax, dword ptr [edi + 0xbc]
008d5172 sbb eax, eax
008d5174 neg eax
008d5176 push eax
008d5177 mov dword ptr [ebp - 0x34], eax
008d517a call 0x4053a0
008d517f test eax, eax
008d5181 jne 0x8d5193
008d5183 push 0xb593e4
008d5188 push eax
008d5189 call 0x95e330
008d518e jmp 0x8d65b6
008d5193 push eax
008d5194 lea ecx, [ebp - 0x170]
008d519a call 0x4069d0
008d519f push dword ptr [ebp - 0x34]
008d51a2 lea ecx, [edi + 0x3c]
008d51a5 call 0x4062c0
008d51aa movss xmm1, dword ptr [ebp - 0x158]
008d51b2 mov dword ptr [ebp - 0x44], 0
008d51b9 mov dword ptr [ebp - 0x40], 0
008d51c0 movss xmm0, dword ptr [eax + 0x34]
008d51c5 mulss xmm0, dword ptr [edi + 0xd8]
008d51cd mov dword ptr [ebp - 0x3c], 0
008d51d4 mulss xmm1, xmm0
008d51d8 movss dword ptr [ebp - 0x38], xmm1
008d51dd mov dword ptr [ebp - 4], 1
008d51e4 lea ecx, [ebp - 0x44]
008d51e7 mov eax, dword ptr [edi + 0x3d4]
008d51ed sub eax, dword ptr [edi + 0x3d0]
008d51f3 sar eax, 3
008d51f6 shl eax, 2
008d51f9 push eax
008d51fa call 0x7a7c30
008d51ff cmp dword ptr [edi + 0xbc], 0
008d5206 jg 0x8d5226
008d5208 cmp dword ptr [edi + 0x50], 0x10
008d520c lea eax, [edi + 0x3c]
008d520f jb 0x8d5214
008d5211 mov eax, dword ptr [edi + 0x3c]
008d5214 push 0
008d5216 push eax
008d5217 push 0xa0830c
008d521c push 3
008d521e call 0x95e330
008d5223 add esp, 0x10
008d5226 mov eax, dword ptr [edi + 0xb8]
008d522c mov dword ptr [eax + 0x28], 0
008d5233 cmp dword ptr [edi + 0xbc], 0
008d523a jg 0x8d525a
008d523c cmp dword ptr [edi + 0x50], 0x10
008d5240 lea eax, [edi + 0x3c]
008d5243 jb 0x8d5248
008d5245 mov eax, dword ptr [edi + 0x3c]
008d5248 push 0
008d524a push eax
008d524b push 0xa0830c
008d5250 push 3
008d5252 call 0x95e330
008d5257 add esp, 0x10
008d525a mov eax, dword ptr [edi + 0xb8]
008d5260 mov dword ptr [eax + 0x2c], 0
008d5267 cmp dword ptr [edi + 0xbc], 0
008d526e jg 0x8d528e
008d5270 cmp dword ptr [edi + 0x50], 0x10
008d5274 lea eax, [edi + 0x3c]
008d5277 jb 0x8d527c
008d5279 mov eax, dword ptr [edi + 0x3c]
008d527c push 0
008d527e push eax
008d527f push 0xa0830c
008d5284 push 3
008d5286 call 0x95e330
008d528b add esp, 0x10
008d528e mov ecx, dword ptr [edi + 0xb8]
008d5294 lea eax, [ebp - 0x84]
008d529a push eax
008d529b call 0x403540
008d52a0 mov byte ptr [ebp - 4], 2
008d52a4 xor edx, edx
008d52a6 movss xmm0, dword ptr [edi + 0x2a4]
008d52ae movss xmm1, dword ptr [ebp - 0x168]
008d52b6 mov ecx, dword ptr [edi + 0x3d0]
008d52bc mov eax, dword ptr [edi + 0x3d4]
008d52c2 mulss xmm0, dword ptr [0xb6a4dc]
008d52ca sub eax, ecx
008d52cc mov esi, dword ptr [ebp - 0x40]
008d52cf mulss xmm1, dword ptr [0xb6a480]
008d52d7 sar eax, 3
008d52da movss dword ptr [ebp - 0x5c], xmm0
008d52df mov dword ptr [ebp - 0x50], edx
008d52e2 movss dword ptr [ebp - 0x34], xmm1
008d52e7 mov dword ptr [ebp - 0x14], ecx
008d52ea add eax, -1
008d52ed je 0x8d5878
008d52f3 xorps xmm1, xmmword ptr [0xb6c9b0]
008d52fa movss dword ptr [ebp - 0x4c], xmm1
008d52ff nop 
008d5300 lea eax, [edx*8]
008d5307 movss xmm1, dword ptr [eax + ecx + 0xc]
008d530d subss xmm1, dword ptr [eax + ecx + 4]
008d5313 movss xmm2, dword ptr [eax + ecx + 8]
008d5319 subss xmm2, dword ptr [eax + ecx]
008d531e mov dword ptr [ebp - 0x20], eax
008d5321 movaps xmm0, xmm1
008d5324 movss dword ptr [ebp - 0x1c], xmm1
008d5329 mulss xmm0, xmm1
008d532d movaps xmm1, xmm2
008d5330 movss dword ptr [ebp - 0x18], xmm2
008d5335 mulss xmm1, xmm2
008d5339 addss xmm0, xmm1
008d533d call 0x4228c0
008d5342 movss xmm2, dword ptr [ebp - 0x1c]
008d5347 sub esp, 8
008d534a movss xmm1, dword ptr [ebp - 0x18]
008d534f divss xmm2, xmm0
008d5353 mov ecx, dword ptr [ebp - 0x14]
008d5356 mov eax, dword ptr [ebp - 0x20]
008d5359 divss xmm1, xmm0
008d535d movss xmm3, dword ptr [0xb6a480]
008d5365 movaps xmm0, xmm2
008d5368 mulss xmm0, dword ptr [ebp - 0x34]
008d536d xorps xmm1, xmmword ptr [0xb6c9b0]
008d5374 movss dword ptr [ebp - 0x1c], xmm2
008d5379 mulss xmm0, dword ptr [ebp - 0x38]
008d537e movss xmm2, dword ptr [eax + ecx]
008d5383 subss xmm2, dword ptr [0xb6aa8c]
008d538b movss dword ptr [ebp - 0x60], xmm0
008d5390 movss xmm0, dword ptr [0xbfec08]
008d5398 subss xmm0, dword ptr [0xb6ac30]
008d53a0 movss dword ptr [ebp - 0x18], xmm1
008d53a5 mulss xmm1, dword ptr [ebp - 0x34]
008d53aa mulss xmm2, dword ptr [0xb6a4dc]
008d53b2 mulss xmm1, dword ptr [ebp - 0x38]
008d53b7 mulss xmm0, xmm3
008d53bb movss dword ptr [ebp - 0x54], xmm1
008d53c0 movss xmm1, dword ptr [0xbfec68]
008d53c8 subss xmm1, dword ptr [0xb6ab8c]
008d53d0 addss xmm2, xmm0
008d53d4 movss xmm0, dword ptr [eax + ecx + 4]
008d53da subss xmm0, dword ptr [0xb6ab44]
008d53e2 mulss xmm1, xmm3
008d53e6 mulss xmm0, dword ptr [0xb6a4dc]
008d53ee addss xmm0, xmm1
008d53f2 movss dword ptr [ebp - 0x28], xmm0
008d53f7 movss xmm0, dword ptr [0xbaa554]
008d53ff mulss xmm0, dword ptr [0xbaa920]
008d5407 mulss xmm2, xmm0
008d540b movss dword ptr [ebp - 0x14], xmm0
008d5410 addss xmm2, xmm3
008d5414 movss dword ptr [ebp - 0x10], xmm2
008d5419 fld dword ptr [ebp - 0x10]
008d541c fstp qword ptr [esp]
008d541f call 0x9ec3b2
008d5424 fstp dword ptr [ebp - 0x10]
008d5427 movss xmm0, dword ptr [ebp - 0x10]
008d542c divss xmm0, dword ptr [ebp - 0x14]
008d5431 movss dword ptr [ebp - 0x24], xmm0
008d5436 movss xmm0, dword ptr [ebp - 0x28]
008d543b mulss xmm0, dword ptr [ebp - 0x14]
008d5440 addss xmm0, dword ptr [0xb6a480]
008d5448 movss dword ptr [ebp - 0x10], xmm0
008d544d fld dword ptr [ebp - 0x10]
008d5450 fstp qword ptr [esp]
008d5453 call 0x9ec3b2
008d5458 fstp dword ptr [ebp - 0x10]
008d545b movss xmm0, dword ptr [ebp - 0x10]
008d5460 add esp, 8
008d5463 divss xmm0, dword ptr [ebp - 0x14]
008d5468 movss xmm1, dword ptr [ebp - 0x60]
008d546d movss xmm2, dword ptr [ebp - 0x54]
008d5472 addss xmm2, xmm0
008d5476 addss xmm1, dword ptr [ebp - 0x24]
008d547b movss dword ptr [ebp - 0x2c], xmm2
008d5480 movss dword ptr [ebp - 0x30], xmm1
008d5485 cmp esi, dword ptr [ebp - 0x3c]
008d5488 je 0x8d549b
008d548a movss dword ptr [esi], xmm1
008d548e movss dword ptr [esi + 4], xmm2
008d5493 add esi, 8
008d5496 mov dword ptr [ebp - 0x40], esi
008d5499 jmp 0x8d54ab
008d549b lea eax, [ebp - 0x30]
008d549e push eax
008d549f push esi
008d54a0 lea ecx, [ebp - 0x44]
008d54a3 call 0x422130
008d54a8 mov esi, dword ptr [ebp - 0x40]
008d54ab movss xmm0, dword ptr [ebp - 0x18]
008d54b0 sub esp, 8
008d54b3 mulss xmm0, dword ptr [ebp - 0x4c]
008d54b8 mov eax, dword ptr [edi + 0x3d0]
008d54be add eax, dword ptr [ebp - 0x20]
008d54c1 movss xmm1, dword ptr [ebp - 0x1c]
008d54c6 mulss xmm0, dword ptr [ebp - 0x38]
008d54cb mulss xmm1, dword ptr [ebp - 0x4c]
008d54d0 movss xmm2, dword ptr [eax]
008d54d4 subss xmm2, dword ptr [0xb6aa8c]
008d54dc movss xmm3, dword ptr [0xb6a480]
008d54e4 mulss xmm1, dword ptr [ebp - 0x38]
008d54e9 movss dword ptr [ebp - 0x18], xmm0
008d54ee movss xmm0, dword ptr [0xbfec08]
008d54f6 subss xmm0, dword ptr [0xb6ac30]
008d54fe mulss xmm2, dword ptr [0xb6a4dc]
008d5506 movss dword ptr [ebp - 0x1c], xmm1
008d550b movss xmm1, dword ptr [0xbfec68]
008d5513 subss xmm1, dword ptr [0xb6ab8c]
008d551b mulss xmm0, xmm3
008d551f addss xmm2, xmm0
008d5523 mulss xmm1, xmm3
008d5527 movss xmm0, dword ptr [eax + 4]
008d552c subss xmm0, dword ptr [0xb6ab44]
008d5534 mulss xmm0, dword ptr [0xb6a4dc]
008d553c addss xmm0, xmm1
008d5540 movss dword ptr [ebp - 0x28], xmm0
008d5545 movss xmm0, dword ptr [0xbaa554]
008d554d mulss xmm0, dword ptr [0xbaa920]
008d5555 mulss xmm2, xmm0
008d5559 movss dword ptr [ebp - 0x14], xmm0
008d555e addss xmm2, xmm3
008d5562 movss dword ptr [ebp - 0x10], xmm2
008d5567 fld dword ptr [ebp - 0x10]
008d556a fstp qword ptr [esp]
008d556d call 0x9ec3b2
008d5572 fstp dword ptr [ebp - 0x10]
008d5575 movss xmm0, dword ptr [ebp - 0x10]
008d557a divss xmm0, dword ptr [ebp - 0x14]
008d557f movss dword ptr [ebp - 0x24], xmm0
008d5584 movss xmm0, dword ptr [ebp - 0x28]
008d5589 mulss xmm0, dword ptr [ebp - 0x14]
008d558e addss xmm0, dword ptr [0xb6a480]
008d5596 movss dword ptr [ebp - 0x10], xmm0
008d559b fld dword ptr [ebp - 0x10]
008d559e fstp qword ptr [esp]
008d55a1 call 0x9ec3b2
008d55a6 fstp dword ptr [ebp - 0x10]
008d55a9 movss xmm0, dword ptr [ebp - 0x10]
008d55ae add esp, 8
008d55b1 divss xmm0, dword ptr [ebp - 0x14]
008d55b6 movss xmm2, dword ptr [ebp - 0x1c]
008d55bb movss xmm1, dword ptr [ebp - 0x18]
008d55c0 addss xmm1, xmm0
008d55c4 addss xmm2, dword ptr [ebp - 0x24]
008d55c9 movss dword ptr [ebp - 0x68], xmm1
008d55ce movss dword ptr [ebp - 0x6c], xmm2
008d55d3 cmp esi, dword ptr [ebp - 0x3c]
008d55d6 je 0x8d55e9
008d55d8 movss dword ptr [esi], xmm2
008d55dc movss dword ptr [esi + 4], xmm1
008d55e1 add esi, 8
008d55e4 mov dword ptr [ebp - 0x40], esi
008d55e7 jmp 0x8d55f9
008d55e9 lea eax, [ebp - 0x6c]
008d55ec push eax
008d55ed push esi
008d55ee lea ecx, [ebp - 0x44]
008d55f1 call 0x422130
008d55f6 mov esi, dword ptr [ebp - 0x40]
008d55f9 mov eax, dword ptr [edi + 0x3d0]
008d55ff sub esp, 8
008d5602 mov ecx, dword ptr [ebp - 0x20]
008d5605 movss xmm0, dword ptr [0xbfec08]
008d560d subss xmm0, dword ptr [0xb6ac30]
008d5615 movss xmm3, dword ptr [0xb6a480]
008d561d movss xmm2, dword ptr [ecx + eax + 8]
008d5623 subss xmm2, dword ptr [0xb6aa8c]
008d562b movss xmm1, dword ptr [0xbfec68]
008d5633 subss xmm1, dword ptr [0xb6ab8c]
008d563b mulss xmm0, xmm3
008d563f mulss xmm2, dword ptr [0xb6a4dc]
008d5647 mulss xmm1, xmm3
008d564b addss xmm2, xmm0
008d564f movss xmm0, dword ptr [ecx + eax + 0xc]
008d5655 subss xmm0, dword ptr [0xb6ab44]
008d565d mulss xmm0, dword ptr [0xb6a4dc]
008d5665 addss xmm0, xmm1
008d5669 movss dword ptr [ebp - 0x28], xmm0
008d566e movss xmm0, dword ptr [0xbaa554]
008d5676 mulss xmm0, dword ptr [0xbaa920]
008d567e mulss xmm2, xmm0
008d5682 movss dword ptr [ebp - 0x14], xmm0
008d5687 addss xmm2, xmm3
008d568b movss dword ptr [ebp - 0x10], xmm2
008d5690 fld dword ptr [ebp - 0x10]
008d5693 fstp qword ptr [esp]
008d5696 call 0x9ec3b2
008d569b fstp dword ptr [ebp - 0x10]
008d569e movss xmm0, dword ptr [ebp - 0x10]
008d56a3 divss xmm0, dword ptr [ebp - 0x14]
008d56a8 movss dword ptr [ebp - 0x24], xmm0
008d56ad movss xmm0, dword ptr [ebp - 0x28]
008d56b2 mulss xmm0, dword ptr [ebp - 0x14]
008d56b7 addss xmm0, dword ptr [0xb6a480]
008d56bf movss dword ptr [ebp - 0x10], xmm0
008d56c4 fld dword ptr [ebp - 0x10]
008d56c7 fstp qword ptr [esp]
008d56ca call 0x9ec3b2
008d56cf fstp dword ptr [ebp - 0x10]
008d56d2 movss xmm0, dword ptr [ebp - 0x10]
008d56d7 add esp, 8
008d56da divss xmm0, dword ptr [ebp - 0x14]
008d56df movss xmm1, dword ptr [ebp - 0x60]
008d56e4 movss xmm2, dword ptr [ebp - 0x54]
008d56e9 addss xmm2, xmm0
008d56ed addss xmm1, dword ptr [ebp - 0x24]
008d56f2 movss dword ptr [ebp - 0x88], xmm2
008d56fa movss dword ptr [ebp - 0x8c], xmm1
008d5702 cmp esi, dword ptr [ebp - 0x3c]
008d5705 je 0x8d5718
008d5707 movss dword ptr [esi], xmm1
008d570b movss dword ptr [esi + 4], xmm2
008d5710 add esi, 8
008d5713 mov dword ptr [ebp - 0x40], esi
008d5716 jmp 0x8d572b
008d5718 lea eax, [ebp - 0x8c]
008d571e push eax
008d571f push esi
008d5720 lea ecx, [ebp - 0x44]
008d5723 call 0x422130
008d5728 mov esi, dword ptr [ebp - 0x40]
008d572b mov ecx, dword ptr [ebp - 0x20]
008d572e sub esp, 8
008d5731 mov eax, dword ptr [edi + 0x3d0]
008d5737 movss xmm0, dword ptr [0xbfec08]
008d573f subss xmm0, dword ptr [0xb6ac30]
008d5747 movss xmm3, dword ptr [0xb6a480]
008d574f movss xmm2, dword ptr [ecx + eax + 8]
008d5755 subss xmm2, dword ptr [0xb6aa8c]
008d575d movss xmm1, dword ptr [0xbfec68]
008d5765 subss xmm1, dword ptr [0xb6ab8c]
008d576d mulss xmm0, xmm3
008d5771 mulss xmm2, dword ptr [0xb6a4dc]
008d5779 mulss xmm1, xmm3
008d577d addss xmm2, xmm0
008d5781 movss xmm0, dword ptr [ecx + eax + 0xc]
008d5787 subss xmm0, dword ptr [0xb6ab44]
008d578f mulss xmm0, dword ptr [0xb6a4dc]
008d5797 addss xmm0, xmm1
008d579b movss dword ptr [ebp - 0x20], xmm0
008d57a0 movss xmm0, dword ptr [0xbaa554]
008d57a8 mulss xmm0, dword ptr [0xbaa920]
008d57b0 mulss xmm2, xmm0
008d57b4 movss dword ptr [ebp - 0x14], xmm0
008d57b9 addss xmm2, xmm3
008d57bd movss dword ptr [ebp - 0x10], xmm2
008d57c2 fld dword ptr [ebp - 0x10]
008d57c5 fstp qword ptr [esp]
008d57c8 call 0x9ec3b2
008d57cd fstp dword ptr [ebp - 0x10]
008d57d0 movss xmm0, dword ptr [ebp - 0x10]
008d57d5 divss xmm0, dword ptr [ebp - 0x14]
008d57da movss dword ptr [ebp - 0x60], xmm0
008d57df movss xmm0, dword ptr [ebp - 0x20]
008d57e4 mulss xmm0, dword ptr [ebp - 0x14]
008d57e9 addss xmm0, dword ptr [0xb6a480]
008d57f1 movss dword ptr [ebp - 0x10], xmm0
008d57f6 fld dword ptr [ebp - 0x10]
008d57f9 fstp qword ptr [esp]
008d57fc call 0x9ec3b2
008d5801 fstp dword ptr [ebp - 0x10]
008d5804 movss xmm0, dword ptr [ebp - 0x10]
008d5809 add esp, 8
008d580c divss xmm0, dword ptr [ebp - 0x14]
008d5811 movss xmm2, dword ptr [ebp - 0x1c]
008d5816 movss xmm1, dword ptr [ebp - 0x18]
008d581b addss xmm1, xmm0
008d581f addss xmm2, dword ptr [ebp - 0x60]
008d5824 movss dword ptr [ebp - 0x70], xmm1
008d5829 movss dword ptr [ebp - 0x74], xmm2
008d582e cmp esi, dword ptr [ebp - 0x3c]
008d5831 je 0x8d5844
008d5833 movss dword ptr [esi], xmm2
008d5837 movss dword ptr [esi + 4], xmm1
008d583c add esi, 8
008d583f mov dword ptr [ebp - 0x40], esi
008d5842 jmp 0x8d5854
008d5844 lea eax, [ebp - 0x74]
008d5847 push eax
008d5848 push esi
008d5849 lea ecx, [ebp - 0x44]
008d584c call 0x422130
008d5851 mov esi, dword ptr [ebp - 0x40]
008d5854 mov ecx, dword ptr [edi + 0x3d0]
008d585a mov eax, dword ptr [edi + 0x3d4]
008d5860 mov edx, dword ptr [ebp - 0x50]
008d5863 sub eax, ecx
008d5865 sar eax, 3
008d5868 inc edx
008d5869 dec eax
008d586a mov dword ptr [ebp - 0x50], edx
008d586d mov dword ptr [ebp - 0x14], ecx
008d5870 cmp edx, eax
008d5872 jb 0x8d5300
008d5878 mov eax, dword ptr [edi + 0x30]
008d587b cmp eax, 1
008d587e je 0x8d588a
008d5880 cmp eax, 2
008d5883 je 0x8d588a
008d5885 cmp eax, 3
008d5888 jne 0x8d58b4
008d588a push esi
008d588b lea eax, [esi - 0x10]
008d588e push eax
008d588f lea eax, [ebp - 0x2c]
008d5892 push eax
008d5893 lea ecx, [ebp - 0x44]
008d5896 call 0x8d8580
008d589b mov ecx, dword ptr [ebp - 0x44]
008d589e push dword ptr [ebp + 8]
008d58a1 lea eax, [ecx + 0x10]
008d58a4 push eax
008d58a5 push ecx
008d58a6 push dword ptr [ebp - 0x40]
008d58a9 lea ecx, [ebp - 0x44]
008d58ac call 0x8d85d0
008d58b1 mov esi, dword ptr [ebp - 0x40]
008d58b4 xorps xmm0, xmm0
008d58b7 mov ecx, edi
008d58b9 movss dword ptr [ebp - 0x28], xmm0
008d58be call 0x8c5940
008d58c3 test al, al
008d58c5 jne 0x8d58d8
008d58c7 mov eax, dword ptr [edi + 0x2c]
008d58ca cmp eax, 5
008d58cd je 0x8d58d8
008d58cf cmp eax, 8
008d58d2 jne 0x8d6039
008d58d8 mov eax, dword ptr [0xa08910]
008d58dd mov ecx, dword ptr [ebp - 0x84]
008d58e3 push 0
008d58e5 mov dword ptr [0xbc7a44], eax
008d58ea call 0x95f690
008d58ef mov eax, dword ptr [ebp - 0x44]
008d58f2 xor ecx, ecx
008d58f4 sub esi, eax
008d58f6 mov dword ptr [ebp - 0x34], ecx
008d58f9 sar esi, 3
008d58fc test esi, esi
008d58fe je 0x8d602e
008d5904 lea edi, [eax + 0x2c]
008d5907 nop word ptr [eax + eax]
008d5910 movss xmm2, dword ptr [0xb6a480]
008d5918 lea eax, [esi - 4]
008d591b cmp ecx, eax
008d591d jae 0x8d596a
008d591f movss xmm1, dword ptr [edi - 0xc]
008d5924 addss xmm1, dword ptr [edi - 0x1c]
008d5929 movss xmm0, dword ptr [edi - 8]
008d592e addss xmm0, dword ptr [edi - 0x18]
008d5933 mulss xmm1, xmm2
008d5937 mulss xmm0, xmm2
008d593b movss dword ptr [edi - 0x1c], xmm1
008d5940 movss dword ptr [edi - 0x18], xmm0
008d5945 movss xmm1, dword ptr [edi - 4]
008d594a movss xmm0, dword ptr [edi]
008d594e addss xmm1, dword ptr [edi - 0x14]
008d5953 addss xmm0, dword ptr [edi - 0x10]
008d5958 mulss xmm1, xmm2
008d595c mulss xmm0, xmm2
008d5960 movss dword ptr [edi - 0x14], xmm1
008d5965 movss dword ptr [edi - 0x10], xmm0
008d596a test ecx, ecx
008d596c je 0x8d598c
008d596e mov eax, dword ptr [edi - 0x3c]
008d5971 mov dword ptr [edi - 0x2c], eax
008d5974 movss xmm0, dword ptr [edi - 0x38]
008d5979 movss dword ptr [edi - 0x28], xmm0
008d597e mov eax, dword ptr [edi - 0x34]
008d5981 mov dword ptr [edi - 0x24], eax
008d5984 mov eax, dword ptr [edi - 0x30]
008d5987 mov dword ptr [edi - 0x20], eax
008d598a jmp 0x8d5991
008d598c movss xmm0, dword ptr [edi - 0x28]
008d5991 mov eax, dword ptr [0xbfd65c]
008d5996 sub esp, 8
008d5999 movss dword ptr [ebp - 0x4c], xmm0
008d599e movss xmm0, dword ptr [0xbfec68]
008d59a6 subss xmm0, dword ptr [0xb6ab8c]
008d59ae mov eax, dword ptr [eax + 0x18190]
008d59b4 movss xmm1, dword ptr [eax + 0x20]
008d59b9 addss xmm1, dword ptr [0xb6a9c8]
008d59c1 mulss xmm0, xmm2
008d59c5 subss xmm1, dword ptr [0xb6ab44]
008d59cd mulss xmm1, dword ptr [0xb6a4dc]
008d59d5 addss xmm1, xmm0
008d59d9 movss xmm0, dword ptr [0xbaa554]
008d59e1 mulss xmm0, dword ptr [0xbaa920]
008d59e9 mulss xmm1, xmm0
008d59ed movss dword ptr [ebp - 0x14], xmm0
008d59f2 addss xmm1, xmm2
008d59f6 movss dword ptr [ebp - 0x10], xmm1
008d59fb fld dword ptr [ebp - 0x10]
008d59fe fstp qword ptr [esp]
008d5a01 call 0x9ec3b2
008d5a06 fstp dword ptr [ebp - 0x10]
008d5a09 movss xmm2, dword ptr [ebp - 0x10]
008d5a0e add esp, 8
008d5a11 divss xmm2, dword ptr [ebp - 0x14]
008d5a16 movss xmm0, dword ptr [ebp - 0x4c]
008d5a1b comiss xmm0, xmm2
008d5a1e ja 0x8d6017
008d5a24 movss xmm1, dword ptr [edi - 0x20]
008d5a29 comiss xmm1, xmm2
008d5a2c movss dword ptr [ebp - 0x50], xmm1
008d5a31 ja 0x8d6017
008d5a37 movss xmm5, dword ptr [edi - 0x24]
008d5a3c movss xmm4, dword ptr [edi - 0x2c]
008d5a41 movss xmm2, dword ptr [edi - 0x18]
008d5a46 movss xmm6, dword ptr [edi - 0x1c]
008d5a4b movss xmm3, dword ptr [edi - 0x10]
008d5a50 movss xmm7, dword ptr [edi - 0x14]
008d5a55 movss dword ptr [ebp - 0x1c], xmm5
008d5a5a movss dword ptr [ebp - 0x18], xmm4
008d5a5f addss xmm4, xmm5
008d5a63 movaps xmm5, xmm0
008d5a66 movss dword ptr [ebp - 0x54], xmm2
008d5a6b movss xmm0, dword ptr [0xb6a480]
008d5a73 addss xmm5, xmm1
008d5a77 movaps xmm1, xmm6
008d5a7a movss dword ptr [ebp - 0x24], xmm6
008d5a7f addss xmm1, xmm7
008d5a83 movss dword ptr [ebp - 0x48], xmm7
008d5a88 addss xmm2, xmm3
008d5a8c mulss xmm4, xmm0
008d5a90 mulss xmm5, xmm0
008d5a94 mulss xmm1, xmm0
008d5a98 mulss xmm2, xmm0
008d5a9c movss dword ptr [ebp - 0x20], xmm1
008d5aa1 subss xmm1, xmm4
008d5aa5 movss dword ptr [ebp - 0x60], xmm3
008d5aaa movaps xmm0, xmm2
008d5aad movss dword ptr [ebp - 0x14], xmm4
008d5ab2 subss xmm0, xmm5
008d5ab6 movss dword ptr [ebp - 0x38], xmm5
008d5abb movss dword ptr [ebp - 0x70], xmm2
008d5ac0 mulss xmm1, xmm1
008d5ac4 mulss xmm0, xmm0
008d5ac8 addss xmm0, xmm1
008d5acc call 0x4228c0
008d5ad1 mov eax, dword ptr [ebp - 0x58]
008d5ad4 lea ecx, [ebp - 0x1a0]
008d5ada add eax, 0x378
008d5adf movaps xmm6, xmm0
008d5ae2 push 0xbc4bc0
008d5ae7 mov edx, eax
008d5ae9 movss dword ptr [ebp - 0x10], xmm6
008d5aee mov dword ptr [ebp - 0x2c], eax
008d5af1 call 0x412050
008d5af6 add esp, 4
008d5af9 mov ecx, dword ptr [eax]
008d5afb or ecx, dword ptr [eax + 4]
008d5afe jne 0x8d5b0c
008d5b00 mov ecx, dword ptr [eax + 8]
008d5b03 or ecx, dword ptr [eax + 0xc]
008d5b06 je 0x8d5c7e
008d5b0c mov eax, dword ptr [ebp - 0x58]
008d5b0f mov eax, dword ptr [eax + 0x30]
008d5b12 cmp eax, 1
008d5b15 je 0x8d5c7e
008d5b1b cmp eax, 2
008d5b1e je 0x8d5c7e
008d5b24 movss xmm4, dword ptr [ebp - 0x4c]
008d5b29 movss xmm5, dword ptr [ebp - 0x50]
008d5b2e cmp eax, 3
008d5b31 je 0x8d5c88
008d5b37 movss xmm0, dword ptr [ebp - 0x28]
008d5b3c lea ecx, [ebp - 0x68]
008d5b3f divss xmm0, dword ptr [0xb6accc]
008d5b47 lea eax, [ebp - 0x88]
008d5b4d mov dword ptr [ebp - 0x68], 0x3f800000
008d5b54 movss xmm1, dword ptr [0xb6a614]
008d5b5c comiss xmm1, xmm0
008d5b5f movss xmm2, dword ptr [ebp - 0x14]
008d5b64 movss dword ptr [ebp - 0x88], xmm0
008d5b6c cmovbe eax, ecx
008d5b6f movss xmm3, dword ptr [ebp - 0x38]
008d5b74 subss xmm4, xmm3
008d5b78 movss xmm7, dword ptr [ebp - 0x20]
008d5b7d subss xmm5, xmm3
008d5b81 lea ecx, [ebp - 0x88]
008d5b87 movss xmm0, dword ptr [eax]
008d5b8b lea eax, [ebp - 0x68]
008d5b8e mulss xmm0, dword ptr [0xb6a6f0]
008d5b96 mov dword ptr [ebp - 0x88], 0x3f800000
008d5ba0 addss xmm0, xmm1
008d5ba4 movss xmm1, dword ptr [ebp - 0x18]
008d5ba9 subss xmm1, xmm2
008d5bad mulss xmm4, xmm0
008d5bb1 mulss xmm1, xmm0
008d5bb5 mulss xmm5, xmm0
008d5bb9 addss xmm4, xmm3
008d5bbd addss xmm1, xmm2
008d5bc1 addss xmm5, xmm3
008d5bc5 movss dword ptr [ebp - 0x18], xmm1
008d5bca movss xmm1, dword ptr [ebp - 0x1c]
008d5bcf subss xmm1, xmm2
008d5bd3 mulss xmm1, xmm0
008d5bd7 movaps xmm0, xmm6
008d5bda addss xmm0, dword ptr [ebp - 0x28]
008d5bdf addss xmm1, xmm2
008d5be3 divss xmm0, dword ptr [0xb6accc]
008d5beb movss dword ptr [ebp - 0x1c], xmm1
008d5bf0 movss xmm1, dword ptr [0xb6a614]
008d5bf8 comiss xmm1, xmm0
008d5bfb movss dword ptr [ebp - 0x68], xmm0
008d5c00 movss xmm0, dword ptr [ebp - 0x24]
008d5c05 cmovbe eax, ecx
008d5c08 subss xmm0, xmm7
008d5c0c movss xmm2, dword ptr [eax]
008d5c10 mulss xmm2, dword ptr [0xb6a6f0]
008d5c18 addss xmm2, xmm1
008d5c1c movss xmm1, dword ptr [ebp - 0x54]
008d5c21 subss xmm1, dword ptr [ebp - 0x70]
008d5c26 movaps xmm3, xmm2
008d5c29 movaps xmm6, xmm2
008d5c2c mulss xmm3, xmm0
008d5c30 movss xmm0, dword ptr [ebp - 0x48]
008d5c35 subss xmm0, xmm7
008d5c39 mulss xmm6, xmm1
008d5c3d movss xmm1, dword ptr [ebp - 0x60]
008d5c42 addss xmm3, xmm7
008d5c46 subss xmm1, dword ptr [ebp - 0x70]
008d5c4b addss xmm6, dword ptr [ebp - 0x70]
008d5c50 movaps xmm7, xmm2
008d5c53 mulss xmm7, xmm0
008d5c57 movss dword ptr [ebp - 0x24], xmm3
008d5c5c movss dword ptr [ebp - 0x48], xmm7
008d5c61 movaps xmm7, xmm2
008d5c64 movss xmm0, dword ptr [ebp - 0x48]
008d5c69 addss xmm0, dword ptr [ebp - 0x20]
008d5c6e mulss xmm7, xmm1
008d5c72 addss xmm7, dword ptr [ebp - 0x70]
008d5c77 movss dword ptr [ebp - 0x48], xmm0
008d5c7c jmp 0x8d5c97
008d5c7e movss xmm4, dword ptr [ebp - 0x4c]
008d5c83 movss xmm5, dword ptr [ebp - 0x50]
008d5c88 movss xmm3, dword ptr [ebp - 0x24]
008d5c8d movss xmm7, dword ptr [ebp - 0x60]
008d5c92 movss xmm6, dword ptr [ebp - 0x54]
008d5c97 mov edx, dword ptr [ebp - 0x2c]
008d5c9a lea ecx, [ebp - 0x1b0]
008d5ca0 push 0xbc4c60
008d5ca5 call 0x412050
008d5caa add esp, 4
008d5cad mov ecx, dword ptr [eax]
008d5caf or ecx, dword ptr [eax + 4]
008d5cb2 jne 0x8d5cc0
008d5cb4 mov ecx, dword ptr [eax + 8]
008d5cb7 or ecx, dword ptr [eax + 0xc]
008d5cba je 0x8d5e3b
008d5cc0 mov eax, dword ptr [ebp - 0x58]
008d5cc3 mov eax, dword ptr [eax + 0x30]
008d5cc6 cmp eax, 1
008d5cc9 je 0x8d5e3b
008d5ccf cmp eax, 2
008d5cd2 je 0x8d5e3b
008d5cd8 cmp eax, 3
008d5cdb je 0x8d5e3b
008d5ce1 movss xmm0, dword ptr [ebp - 0x28]
008d5ce6 lea ecx, [ebp - 0x68]
008d5ce9 divss xmm0, dword ptr [0xb6ac14]
008d5cf1 lea eax, [ebp - 0x2c]
008d5cf4 mov dword ptr [ebp - 0x68], 0x3f800000
008d5cfb movss xmm1, dword ptr [0xb6a614]
008d5d03 comiss xmm1, xmm0
008d5d06 subss xmm4, dword ptr [ebp - 0x38]
008d5d0b movss dword ptr [ebp - 0x2c], xmm0
008d5d10 movaps xmm2, xmm1
008d5d13 cmovbe eax, ecx
008d5d16 lea ecx, [ebp - 0x68]
008d5d19 subss xmm5, dword ptr [ebp - 0x38]
008d5d1e subss xmm6, dword ptr [ebp - 0x70]
008d5d23 movaps xmm1, xmm4
008d5d26 movss xmm0, dword ptr [eax]
008d5d2a lea eax, [ebp - 0x2c]
008d5d2d mulss xmm0, dword ptr [0xb6a480]
008d5d35 mov dword ptr [ebp - 0x68], 0x3f800000
008d5d3c subss xmm7, dword ptr [ebp - 0x70]
008d5d41 subss xmm2, xmm0
008d5d45 movss xmm0, dword ptr [ebp - 0x18]
008d5d4a subss xmm0, dword ptr [ebp - 0x14]
008d5d4f movaps xmm4, xmm2
008d5d52 mulss xmm4, xmm0
008d5d56 movss dword ptr [ebp - 0x18], xmm4
008d5d5b movaps xmm4, xmm2
008d5d5e movss xmm0, dword ptr [ebp - 0x18]
008d5d63 addss xmm0, dword ptr [ebp - 0x14]
008d5d68 mulss xmm4, xmm1
008d5d6c movaps xmm1, xmm5
008d5d6f movaps xmm5, xmm2
008d5d72 movss dword ptr [ebp - 0x18], xmm0
008d5d77 movss xmm0, dword ptr [ebp - 0x1c]
008d5d7c subss xmm0, dword ptr [ebp - 0x14]
008d5d81 addss xmm4, dword ptr [ebp - 0x38]
008d5d86 mulss xmm5, xmm0
008d5d8a movss dword ptr [ebp - 0x1c], xmm5
008d5d8f movaps xmm5, xmm2
008d5d92 movss xmm0, dword ptr [ebp - 0x1c]
008d5d97 addss xmm0, dword ptr [ebp - 0x14]
008d5d9c mulss xmm5, xmm1
008d5da0 movss xmm1, dword ptr [0xb6a614]
008d5da8 movaps xmm2, xmm1
008d5dab movss dword ptr [ebp - 0x1c], xmm0
008d5db0 movss xmm0, dword ptr [ebp - 0x10]
008d5db5 addss xmm0, dword ptr [ebp - 0x28]
008d5dba addss xmm5, dword ptr [ebp - 0x38]
008d5dbf divss xmm0, dword ptr [0xb6ac14]
008d5dc7 comiss xmm1, xmm0
008d5dca movss dword ptr [ebp - 0x2c], xmm0
008d5dcf movaps xmm1, xmm6
008d5dd2 cmovbe eax, ecx
008d5dd5 movss xmm0, dword ptr [eax]
008d5dd9 mulss xmm0, dword ptr [0xb6a480]
008d5de1 subss xmm2, xmm0
008d5de5 movss xmm0, dword ptr [ebp - 0x24]
008d5dea subss xmm0, dword ptr [ebp - 0x20]
008d5def movaps xmm3, xmm2
008d5df2 movaps xmm6, xmm2
008d5df5 mulss xmm3, xmm0
008d5df9 movss xmm0, dword ptr [ebp - 0x48]
008d5dfe subss xmm0, dword ptr [ebp - 0x20]
008d5e03 addss xmm3, dword ptr [ebp - 0x20]
008d5e08 mulss xmm6, xmm1
008d5e0c movaps xmm1, xmm7
008d5e0f movaps xmm7, xmm2
008d5e12 mulss xmm7, xmm0
008d5e16 addss xmm6, dword ptr [ebp - 0x70]
008d5e1b movss dword ptr [ebp - 0x48], xmm7
008d5e20 movaps xmm7, xmm2
008d5e23 movss xmm0, dword ptr [ebp - 0x48]
008d5e28 addss xmm0, dword ptr [ebp - 0x20]
008d5e2d mulss xmm7, xmm1
008d5e31 addss xmm7, dword ptr [ebp - 0x70]
008d5e36 movss dword ptr [ebp - 0x48], xmm0
008d5e3b movss xmm0, dword ptr [ebp - 0x170]
008d5e43 lea ecx, [ebp - 0x190]
008d5e49 addss xmm0, dword ptr [ebp - 0x168]
008d5e51 movss xmm1, dword ptr [ebp - 0x10]
008d5e56 addss xmm1, dword ptr [ebp - 0x28]
008d5e5b mov eax, dword ptr [ebp + 8]
008d5e5e movss xmm2, dword ptr [ebp - 0x170]
008d5e66 addss xmm6, dword ptr [0xb6a18c]
008d5e6e movss dword ptr [ebp - 0xc0], xmm0
008d5e76 movss dword ptr [ebp - 0xd0], xmm0
008d5e7e movss xmm0, dword ptr [ebp - 0x5c]
008d5e83 addss xmm0, xmm3
008d5e87 movss dword ptr [ebp - 0xbc], xmm1
008d5e8f movss xmm3, dword ptr [eax]
008d5e93 movss dword ptr [ebp - 0xc4], xmm1
008d5e9b movss dword ptr [ebp - 0xc8], xmm2
008d5ea3 movss dword ptr [ebp - 0xd8], xmm2
008d5eab movss xmm2, dword ptr [ebp - 0x28]
008d5eb0 movss dword ptr [ebp - 0x28], xmm1
008d5eb5 movaps xmm1, xmm3
008d5eb8 addss xmm1, xmm0
008d5ebc movss dword ptr [ebp - 0xcc], xmm2
008d5ec4 movss dword ptr [ebp - 0xd4], xmm2
008d5ecc movss xmm2, dword ptr [eax + 4]
008d5ed1 lea eax, [ebp - 0x9c]
008d5ed7 movaps xmm0, xmm2
008d5eda mov dword ptr [ebp - 0xb8], 0
008d5ee4 addss xmm0, xmm6
008d5ee8 xorps xmm6, xmm6
008d5eeb movss dword ptr [ebp - 0x9c], xmm1
008d5ef3 addss xmm7, xmm6
008d5ef7 movaps xmm1, xmm3
008d5efa addss xmm4, xmm6
008d5efe push eax
008d5eff addss xmm5, xmm6
008d5f03 movss dword ptr [ebp - 0x98], xmm0
008d5f0b lea eax, [ebp - 0xa4]
008d5f11 movss xmm0, dword ptr [ebp - 0x5c]
008d5f16 addss xmm0, dword ptr [ebp - 0x48]
008d5f1b push eax
008d5f1c lea eax, [ebp - 0xac]
008d5f22 push eax
008d5f23 lea eax, [ebp - 0x7c]
008d5f26 addss xmm1, xmm0
008d5f2a movaps xmm0, xmm2
008d5f2d addss xmm0, xmm7
008d5f31 push eax
008d5f32 movss dword ptr [ebp - 0xa4], xmm1
008d5f3a movaps xmm1, xmm3
008d5f3d movss dword ptr [ebp - 0xa0], xmm0
008d5f45 movss xmm0, dword ptr [ebp - 0x5c]
008d5f4a addss xmm0, dword ptr [ebp - 0x18]
008d5f4f addss xmm1, xmm0
008d5f53 movaps xmm0, xmm2
008d5f56 addss xmm0, xmm4
008d5f5a addss xmm2, xmm5
008d5f5e movss dword ptr [ebp - 0xac], xmm1
008d5f66 movss dword ptr [ebp - 0xa8], xmm0
008d5f6e movss xmm0, dword ptr [ebp - 0x5c]
008d5f73 addss xmm0, dword ptr [ebp - 0x1c]
008d5f78 movss dword ptr [ebp - 0x78], xmm2
008d5f7d addss xmm3, xmm0
008d5f81 movss dword ptr [ebp - 0x7c], xmm3
008d5f86 call 0x95e620
008d5f8b mov ecx, dword ptr [ebp - 0x84]
008d5f91 lea edx, [ebp - 0x94]
008d5f97 xorps xmm0, xmm0
008d5f9a mov dword ptr [ebp - 0xe4], 0
008d5fa4 push edx
008d5fa5 movups xmmword ptr [ebp - 0xf4], xmm0
008d5fac lea edx, [ebp - 0x190]
008d5fb2 mov dword ptr [ebp - 0xe0], 0
008d5fbc movaps xmm0, xmmword ptr [0xb6ba00]
008d5fc3 movups xmmword ptr [ebp - 0x104], xmm0
008d5fca push edx
008d5fcb movaps xmm0, xmmword ptr [0xb6ba00]
008d5fd2 lea edx, [ebp - 0xd8]
008d5fd8 movups xmmword ptr [ebp - 0x94], xmm0
008d5fdf mov eax, dword ptr [ecx]
008d5fe1 mov dword ptr [ebp - 0xdc], 0
008d5feb push edx
008d5fec mov eax, dword ptr [eax + 0xc]
008d5fef call eax
008d5ff1 mov dword ptr [ebp - 0x2c], eax
008d5ff4 test eax, eax
008d5ff6 je 0x8d6017
008d5ff8 sub esp, 8
008d5ffb lea eax, [ebp - 0x84]
008d6001 mov ecx, esp
008d6003 push eax
008d6004 call 0x4078a0
008d6009 push dword ptr [ebp - 0x2c]
008d600c lea ecx, [ebp - 0x104]
008d6012 call 0x65af60
008d6017 mov ecx, dword ptr [ebp - 0x34]
008d601a add edi, 0x20
008d601d add ecx, 4
008d6020 mov dword ptr [ebp - 0x34], ecx
008d6023 cmp ecx, esi
008d6025 jb 0x8d5910
008d602b mov edi, dword ptr [ebp - 0x58]
008d602e mov ecx, dword ptr [ebp - 0x84]
008d6034 call 0x95f6d0
008d6039 cmp dword ptr [edi + 0xbc], 1
008d6040 jbe 0x8d6573
008d6046 mov eax, dword ptr [edi + 0x2c]
008d6049 dec eax
008d604a cmp eax, 0xe
008d604d ja 0x8d6573
008d6053 movzx eax, byte ptr [eax + 0x8d65d8]
008d605a jmp dword ptr [eax*4 + 0x8d65d0]
008d6061 cmp dword ptr [edi + 0x30], 0
008d6065 jne 0x8d6573
008d606b push 0
008d606d lea ecx, [edi + 0x6c]
008d6070 call 0x4053a0
008d6075 test eax, eax
008d6077 jne 0x8d60cd
008d6079 push 0xb59390
008d607e push eax
008d607f call 0x95e330
008d6084 add esp, 8
008d6087 lea ecx, [ebp - 0x84]
008d608d call 0x407790
008d6092 mov ecx, dword ptr [ebp - 0x44]
008d6095 test ecx, ecx
008d6097 je 0x8d65b9
008d609d mov edx, dword ptr [ebp - 0x3c]
008d60a0 mov eax, ecx
008d60a2 sub edx, ecx
008d60a4 and edx, 0xfffffff8
008d60a7 cmp edx, 0x1000
008d60ad jb 0x8d65af
008d60b3 mov ecx, dword ptr [ecx - 4]
008d60b6 add edx, 0x23
008d60b9 sub eax, ecx
008d60bb add eax, -4
008d60be cmp eax, 0x1f
008d60c1 jbe 0x8d65af
008d60c7 call dword ptr [0xa065ac]
008d60cd push eax
008d60ce lea ecx, [ebp - 0x170]
008d60d4 call 0x4069d0
008d60d9 cmp dword ptr [edi + 0xbc], 0
008d60e0 lea esi, [edi + 0x3c]
008d60e3 jg 0x8d6101
008d60e5 cmp dword ptr [esi + 0x14], 0x10
008d60e9 mov eax, esi
008d60eb jb 0x8d60ef
008d60ed mov eax, dword ptr [esi]
008d60ef push 0
008d60f1 push eax
008d60f2 push 0xa0830c
008d60f7 push 3
008d60f9 call 0x95e330
008d60fe add esp, 0x10
008d6101 mov eax, dword ptr [esi + 0x7c]
008d6104 lea ecx, [ebp - 0xd8]
008d610a movss xmm2, dword ptr [ebp - 0x158]
008d6112 push 0
008d6114 movss xmm0, dword ptr [eax + 0x34]
008d6119 mulss xmm0, dword ptr [edi + 0xd8]
008d6121 movss xmm1, dword ptr [eax + 0x38]
008d6126 lea eax, [ebp - 0x2c]
008d6129 mulss xmm1, dword ptr [edi + 0xdc]
008d6131 push eax
008d6132 mulss xmm2, xmm0
008d6136 lea eax, [ebp - 0x68]
008d6139 push eax
008d613a movss xmm0, dword ptr [ebp - 0x154]
008d6142 lea eax, [ebp - 0x88]
008d6148 mulss xmm0, xmm1
008d614c push eax
008d614d movss xmm1, dword ptr [ebp - 0x16c]
008d6155 lea eax, [ebp - 0x170]
008d615b push eax
008d615c movss dword ptr [ebp - 0x154], xmm0
008d6164 movss xmm0, dword ptr [ebp - 0x164]
008d616c addss xmm0, xmm1
008d6170 movss dword ptr [ebp - 0x14], xmm2
008d6175 addss xmm1, dword ptr [0xb6a214]
008d617d movss dword ptr [ebp - 0x158], xmm2
008d6185 movss dword ptr [ebp - 0x2c], xmm0
008d618a movss xmm0, dword ptr [ebp - 0x168]
008d6192 addss xmm0, dword ptr [ebp - 0x170]
008d619a movss dword ptr [ebp - 0x88], xmm1
008d61a2 movss dword ptr [ebp - 0x68], xmm0
008d61a7 call 0x95e9e0
008d61ac mov eax, dword ptr [edi + 0x3d0]
008d61b2 lea ecx, [ebp - 0x7c]
008d61b5 movss xmm0, dword ptr [eax]
008d61b9 movss xmm1, dword ptr [eax + 4]
008d61be lea eax, [ebp - 0x64]
008d61c1 subss xmm0, dword ptr [edi + 0x294]
008d61c9 subss xmm1, dword ptr [edi + 0x298]
008d61d1 push eax
008d61d2 movss dword ptr [ebp - 0x7c], xmm0
008d61d7 movss dword ptr [ebp - 0x78], xmm1
008d61dc call 0x962560
008d61e1 movss xmm4, dword ptr [ebp - 0x64]
008d61e6 movss xmm7, dword ptr [ebp - 0x168]
008d61ee movaps xmm0, xmm4
008d61f1 xorps xmm0, xmmword ptr [0xb6c9b0]
008d61f8 movaps xmm5, xmm4
008d61fb mulss xmm7, dword ptr [0xb6a480]
008d6203 mov eax, dword ptr [ebp - 0x44]
008d6206 mov ecx, dword ptr [ebp + 8]
008d6209 movss xmm3, dword ptr [ebp - 0x60]
008d620e mulss xmm3, dword ptr [0xb6a1fc]
008d6216 movss xmm1, dword ptr [eax + 4]
008d621b addss xmm1, dword ptr [0xb6a18c]
008d6223 movss xmm2, dword ptr [ecx]
008d6227 movss dword ptr [ebp - 0x10], xmm0
008d622c movaps xmm0, xmm7
008d622f xorps xmm0, xmmword ptr [0xb6c9b0]
008d6236 mulss xmm4, dword ptr [0xb6a1fc]
008d623e movss dword ptr [ebp - 0x38], xmm0
008d6243 movss xmm0, dword ptr [ebp - 0x5c]
008d6248 addss xmm0, dword ptr [eax]
008d624c movss xmm6, dword ptr [ebp - 0x60]
008d6251 mulss xmm5, dword ptr [ebp - 0x15c]
008d6259 mulss xmm6, dword ptr [ebp - 0x15c]
008d6261 addss xmm2, xmm0
008d6265 movss xmm0, dword ptr [ecx + 4]
008d626a addss xmm0, xmm1
008d626e movss xmm1, dword ptr [eax + 0xc]
008d6273 addss xmm1, dword ptr [0xb6a18c]
008d627b addss xmm2, xmm4
008d627f addss xmm0, xmm3
008d6283 movss dword ptr [ebp - 0x7c], xmm2
008d6288 movss xmm2, dword ptr [ecx]
008d628c movss dword ptr [ebp - 0x78], xmm0
008d6291 movss xmm0, dword ptr [ebp - 0x5c]
008d6296 addss xmm0, dword ptr [eax + 8]
008d629b addss xmm2, xmm0
008d629f movss xmm0, dword ptr [ecx + 4]
008d62a4 addss xmm0, xmm1
008d62a8 addss xmm5, dword ptr [edi + 0x294]
008d62b0 addss xmm0, xmm3
008d62b4 movaps xmm1, xmm7
008d62b7 addss xmm6, dword ptr [edi + 0x298]
008d62bf addss xmm2, xmm4
008d62c3 sub esp, 8
008d62c6 subss xmm5, dword ptr [0xb6aa8c]
008d62ce movss dword ptr [ebp - 0xa8], xmm0
008d62d6 movaps xmm0, xmm1
008d62d9 mulss xmm0, dword ptr [ebp - 0x60]
008d62de mulss xmm1, dword ptr [ebp - 0x10]
008d62e3 mulss xmm5, dword ptr [0xb6a4dc]
008d62eb subss xmm6, dword ptr [0xb6ab44]
008d62f3 movss dword ptr [ebp - 0x88], xmm0
008d62fb movss xmm0, dword ptr [0xbfec08]
008d6303 subss xmm0, dword ptr [0xb6ac30]
008d630b movss dword ptr [ebp - 0x58], xmm1
008d6310 movss xmm1, dword ptr [0xb6a480]
008d6318 mulss xmm6, dword ptr [0xb6a4dc]
008d6320 mulss xmm0, xmm1
008d6324 movss dword ptr [ebp - 0xac], xmm2
008d632c addss xmm5, xmm0
008d6330 movss xmm0, dword ptr [0xbfec68]
008d6338 subss xmm0, dword ptr [0xb6ab8c]
008d6340 mulss xmm0, xmm1
008d6344 addss xmm6, xmm0
008d6348 movss xmm0, dword ptr [0xbaa554]
008d6350 mulss xmm0, dword ptr [0xbaa920]
008d6358 mulss xmm5, xmm0
008d635c movss dword ptr [ebp - 0x68], xmm6
008d6361 movss dword ptr [ebp - 0x34], xmm0
008d6366 addss xmm5, xmm1
008d636a movss dword ptr [ebp - 0x2c], xmm5
008d636f fld dword ptr [ebp - 0x2c]
008d6372 fstp qword ptr [esp]
008d6375 call 0x9ec3b2
008d637a fstp dword ptr [ebp - 0x2c]
008d637d movss xmm1, dword ptr [ebp - 0x2c]
008d6382 divss xmm1, dword ptr [ebp - 0x34]
008d6387 movss dword ptr [ebp - 0x20], xmm1
008d638c movss xmm1, dword ptr [ebp - 0x68]
008d6391 mulss xmm1, dword ptr [ebp - 0x34]
008d6396 addss xmm1, dword ptr [0xb6a480]
008d639e movss dword ptr [ebp - 0x2c], xmm1
008d63a3 fld dword ptr [ebp - 0x2c]
008d63a6 fstp qword ptr [esp]
008d63a9 call 0x9ec3b2
008d63ae movss xmm2, dword ptr [ebp - 0x14]
008d63b3 add esp, 8
008d63b6 fstp dword ptr [ebp - 0x2c]
008d63b9 movss xmm3, dword ptr [ebp - 0x2c]
008d63be movaps xmm0, xmm2
008d63c1 divss xmm3, dword ptr [ebp - 0x34]
008d63c6 mov eax, dword ptr [ebp + 8]
008d63c9 mulss xmm2, dword ptr [ebp - 0x58]
008d63ce mulss xmm0, dword ptr [ebp - 0x88]
008d63d6 movss xmm1, dword ptr [ebp - 0x5c]
008d63db addss xmm2, xmm3
008d63df movss xmm7, dword ptr [ebp - 0x14]
008d63e4 addss xmm0, dword ptr [ebp - 0x20]
008d63e9 addss xmm2, dword ptr [0xb6a18c]
008d63f1 addss xmm1, xmm0
008d63f5 movaps xmm0, xmm7
008d63f8 addss xmm2, dword ptr [eax + 4]
008d63fd addss xmm1, dword ptr [eax]
008d6401 movss dword ptr [ebp - 0xa0], xmm2
008d6409 movss xmm2, dword ptr [ebp - 0x38]
008d640e movss dword ptr [ebp - 0xa4], xmm1
008d6416 movss xmm1, dword ptr [ebp - 0x60]
008d641b mulss xmm1, xmm2
008d641f mulss xmm2, dword ptr [ebp - 0x10]
008d6424 mulss xmm0, xmm1
008d6428 movss xmm1, dword ptr [ebp - 0x5c]
008d642d mulss xmm7, xmm2
008d6431 addss xmm0, dword ptr [ebp - 0x20]
008d6436 addss xmm7, xmm3
008d643a addss xmm1, xmm0
008d643e addss xmm7, dword ptr [0xb6a18c]
008d6446 addss xmm1, dword ptr [eax]
008d644a addss xmm7, dword ptr [eax + 4]
008d644f movss dword ptr [ebp - 0x9c], xmm1
008d6457 lea eax, [ebp - 0x7c]
008d645a movss dword ptr [ebp - 0x98], xmm7
008d6462 push eax
008d6463 lea eax, [ebp - 0xac]
008d6469 push eax
008d646a lea eax, [ebp - 0xa4]
008d6470 push eax
008d6471 lea eax, [ebp - 0x9c]
008d6477 push eax
008d6478 lea ecx, [ebp - 0x190]
008d647e call 0x95e620
008d6483 mov eax, dword ptr [0xa08910]
008d6488 xorps xmm0, xmm0
008d648b movups xmmword ptr [ebp - 0xf4], xmm0
008d6492 mov dword ptr [0xbc7a44], eax
008d6497 cmp dword ptr [esi + 0x80], 0
008d649e movaps xmm0, xmmword ptr [0xb6ba00]
008d64a5 movups xmmword ptr [ebp - 0x104], xmm0
008d64ac mov dword ptr [ebp - 0xe4], 0
008d64b6 mov dword ptr [ebp - 0xe0], 0
008d64c0 mov dword ptr [ebp - 0xdc], 0
008d64ca jg 0x8d64e8
008d64cc cmp dword ptr [esi + 0x14], 0x10
008d64d0 mov eax, esi
008d64d2 jb 0x8d64d6
008d64d4 mov eax, dword ptr [esi]
008d64d6 push 0
008d64d8 push eax
008d64d9 push 0xa0830c
008d64de push 3
008d64e0 call 0x95e330
008d64e5 add esp, 0x10
008d64e8 mov ecx, dword ptr [esi + 0x7c]
008d64eb lea eax, [ebp - 0x7c]
008d64ee push eax
008d64ef call 0x403540
008d64f4 mov byte ptr [ebp - 4], 3
008d64f8 lea edx, [ebp - 0xb4]
008d64fe mov ecx, dword ptr [eax]
008d6500 movaps xmm0, xmmword ptr [0xb6ba00]
008d6507 push edx
008d6508 movups xmmword ptr [ebp - 0xb4], xmm0
008d650f mov eax, dword ptr [ecx]
008d6511 lea edx, [ebp - 0x190]
008d6517 push edx
008d6518 lea edx, [ebp - 0xd8]
008d651e push edx
008d651f mov eax, dword ptr [eax + 0xc]
008d6522 call eax
008d6524 lea ecx, [ebp - 0x7c]
008d6527 mov byte ptr [ebp - 4], 2
008d652b mov edi, eax
008d652d call 0x407790
008d6532 test edi, edi
008d6534 je 0x8d6573
008d6536 cmp dword ptr [esi + 0x80], 0
008d653d jg 0x8d655b
008d653f cmp dword ptr [esi + 0x14], 0x10
008d6543 mov eax, esi
008d6545 jb 0x8d6549
008d6547 mov eax, dword ptr [esi]
008d6549 push 0
008d654b push eax
008d654c push 0xa0830c
008d6551 push 3
008d6553 call 0x95e330
008d6558 add esp, 0x10
008d655b mov ecx, dword ptr [esi + 0x7c]
008d655e sub esp, 8
008d6561 push esp
008d6562 call 0x403540
008d6567 push edi
008d6568 lea ecx, [ebp - 0x104]
008d656e call 0x65af60
008d6573 mov byte ptr [ebp - 4], 4
008d6577 mov ecx, dword ptr [ebp - 0x80]
008d657a test ecx, ecx
008d657c je 0x8d6092
008d6582 mov eax, dword ptr [ecx]
008d6584 mov eax, dword ptr [eax + 0xc]
008d6587 call eax
008d6589 test al, al
008d658b je 0x8d6092
008d6591 mov eax, dword ptr [0xbfd62c]
008d6596 test eax, eax
008d6598 je 0x8d6092
008d659e lea ecx, [ebp - 0x84]
008d65a4 push ecx
008d65a5 call eax
008d65a7 add esp, 4
008d65aa jmp 0x8d6092
008d65af push edx
008d65b0 push ecx
008d65b1 call 0x9eb08e
008d65b6 add esp, 8
008d65b9 mov al, 1
008d65bb mov ecx, dword ptr [ebp - 0xc]
008d65be mov dword ptr fs:[0], ecx
008d65c5 pop ecx
008d65c6 pop edi
008d65c7 pop esi
008d65c8 mov esp, ebp
008d65ca pop ebp
008d65cb ret 4
008d65ce nop 
008d65d0 popal 
008d65d1 pushal 
008d65d2 lea eax, [eax]
008d65d4 jae 0x8d663b
008d65d6 lea eax, [eax]
008d65d8 add byte ptr [ecx], al
008d65da add byte ptr [ecx], al
008d65dc add dword ptr [eax], eax
008d65de add dword ptr [ecx], eax
008d65e0 add byte ptr [ecx], al
008d65e2 add byte ptr [eax], al
008d65e4 add byte ptr [eax], al
008d65e6 add ah, cl
008d65e8 int3 
008d65e9 int3 
008d65ea int3 
008d65eb int3 
008d65ec int3 
008d65ed int3 
008d65ee int3 
008d65ef int3 
008d65f0 lea eax, [ecx + 0x3d0]
008d65f6 ret 
008d65f7 int3 
008d65f8 int3 
008d65f9 int3 
008d65fa int3 
008d65fb int3 
008d65fc int3 
008d65fd int3 
008d65fe int3 
008d65ff int3 
008d6600 push ebp
008d6601 mov ebp, esp
008d6603 sub esp, 0x58
008d6606 mov eax, dword ptr [0xbaa3b4]
008d660b xor eax, ebp
008d660d mov dword ptr [ebp - 8], eax
008d6610 push ebx
008d6611 mov ebx, ecx
008d6613 movss dword ptr [ebp - 0xc], xmm2
008d6618 push esi
008d6619 push edi
008d661a mov ecx, dword ptr [ebx + 0x47c]
008d6620 test ecx, ecx
008d6622 je 0x8d662d
008d6624 call 0x8c5980
008d6629 mov esi, eax
008d662b jmp 0x8d6633
008d662d lea esi, [ebx + 0x470]
008d6633 mov edi, dword ptr [ebp + 8]
008d6636 mov ecx, edi
008d6638 call 0x68d5a0
008d663d push eax
008d663e mov ecx, esi
008d6640 call 0x422c30
008d6645 mov edx, dword ptr [edi + 0x28]
008d6648 cmp edx, 4
008d664b je 0x8d687c
008d6651 mov eax, dword ptr [ebx + 0x320]
008d6657 mov ecx, ebx
008d6659 test eax, eax
008d665b cmovne ecx, eax
008d665e mov dword ptr [ebp - 0x20], ecx
008d6661 cmp edx, 1
008d6664 jne 0x8d66b2
008d6666 push ecx
008d6667 lea ecx, [ebp - 0x58]
008d666a call 0x4229a0
008d666f push 0
008d6671 push 0xbeab9c
008d6676 push 0xbeab18
008d667b push 0
008d667d push edi
008d667e call 0x9ec34c
008d6683 add esp, 0x14
008d6686 lea ecx, [ebp - 0x58]
008d6689 mov edx, dword ptr [eax]
008d668b push 0x1e
008d668d push ecx
008d668e push 0
008d6690 push 8
008d6692 push ecx
008d6693 mov ecx, eax
008d6695 mov dword ptr [esp], 0x3f800000
008d669c call dword ptr [edx + 0x20]
008d669f pop edi
008d66a0 pop esi
008d66a1 pop ebx
008d66a2 mov ecx, dword ptr [ebp - 8]
008d66a5 xor ecx, ebp
008d66a7 call 0x9eacd7
008d66ac mov esp, ebp
008d66ae pop ebp
008d66af ret 4
008d66b2 cmp edx, 3
008d66b5 jne 0x8d6714
008d66b7 mov edx, dword ptr [edi + 0x2c]
008d66ba cmp edx, 0x3e
008d66bd je 0x8d66d2
008d66bf mov eax, dword ptr [0xbfd65c]
008d66c4 cmp dword ptr [eax + 0x1c319c], 0x1e
008d66cb jne 0x8d6714
008d66cd cmp edx, 0x43
008d66d0 jne 0x8d6714
008d66d2 push ecx
008d66d3 lea ecx, [ebp - 0x58]
008d66d6 call 0x4229a0
008d66db push 0
008d66dd push 0xbeab40
008d66e2 push 0xbeab18
008d66e7 push 0
008d66e9 push edi
008d66ea call 0x9ec34c
008d66ef add esp, 0x14
008d66f2 lea edx, [ebp - 0x58]
008d66f5 mov ecx, dword ptr [eax + 0x360]
008d66fb push 0x1e
008d66fd push edx
008d66fe push 0
008d6700 mov eax, dword ptr [ecx]
008d6702 push 0x808
008d6707 push ecx
008d6708 mov dword ptr [esp], 0x3f800000
008d670f jmp 0x8d6879
008d6714 movups xmm0, xmmword ptr [ebx + 0x378]
008d671b push ebx
008d671c sub esp, 0x14
008d671f mov dword ptr [ebp - 0x1c], 8
008d6726 mov eax, esp
008d6728 mov dword ptr [ebp - 0x18], 0
008d672f lea edx, [ebp - 0x1c]
008d6732 push ecx
008d6733 movups xmmword ptr [eax], xmm0
008d6736 call 0x656c90
008d673b movss xmm0, dword ptr [ebp - 0xc]
008d6740 lea edx, [ebx + 0x294]
008d6746 add esp, 0x18
008d6749 mov ecx, edi
008d674b movss dword ptr [esp], xmm0
008d6750 movups xmm0, xmmword ptr [ebx + 0x378]
008d6757 push ebx
008d6758 sub esp, 0x10
008d675b mov eax, esp
008d675d movups xmmword ptr [eax], xmm0
008d6760 call 0x654de0
008d6765 mov ecx, dword ptr [edi + 0x164]
008d676b xor eax, eax
008d676d and ecx, 0x1000000
008d6773 add esp, 0x18
008d6776 or eax, ecx
008d6778 je 0x8d67f2
008d677a mov ecx, ebx
008d677c call 0x8c5940
008d6781 test al, al
008d6783 je 0x8d67f2
008d6785 mov esi, dword ptr [0xbfd680]
008d678b lea ecx, [ebp - 0x10]
008d678e mov dword ptr [ebp - 0x10], 0x4d
008d6795 call 0x8b1340
008d679a sub esp, 8
008d679d mov dword ptr [esp + 4], 0
008d67a5 mov dword ptr [esp], 0x3f800000
008d67ac push 0
008d67ae push 8
008d67b0 push ecx
008d67b1 mov dword ptr [esp], 0x3f333333
008d67b8 lea ecx, [esi + 0x29de0]
008d67be push dword ptr [ebp - 0x10]
008d67c1 call 0x888de0
008d67c6 movss xmm0, dword ptr [ebp - 0xc]
008d67cb mov eax, dword ptr [edi + 0x160]
008d67d1 addss xmm0, xmm0
008d67d5 or dword ptr [edi + 0x164], 0x800000
008d67df mov dword ptr [edi + 0x160], eax
008d67e5 addss xmm0, dword ptr [0xb6a864]
008d67ed movss dword ptr [ebp - 0xc], xmm0
008d67f2 movss xmm0, dword ptr [ebx + 0x444]
008d67fa xorps xmm1, xmm1
008d67fd comiss xmm0, xmm1
008d6800 jbe 0x8d6851
008d6802 push 0
008d6804 mov ecx, edi
008d6806 call 0x68cf40
008d680b test al, al
008d680d je 0x8d6851
008d680f mov eax, dword ptr [edi + 0x344]
008d6815 lea ecx, [ebp - 0x30]
008d6818 movq xmm0, qword ptr [0xa08ab8]
008d6820 mov dword ptr [ebp - 0x30], eax
008d6823 mov eax, dword ptr [0xa08ac0]
008d6828 movq qword ptr [ebp - 0x2c], xmm0
008d682d mov dword ptr [ebp - 0x24], eax
008d6830 call 0x7a7db0
008d6835 movss xmm0, dword ptr [ebx + 0x444]
008d683d fstp dword ptr [ebp - 0x10]
008d6840 comiss xmm0, dword ptr [ebp - 0x10]
008d6844 jbe 0x8d6851
008d6846 mov esi, dword ptr [ebp - 0x1c]
008d6849 or esi, 0x800000
008d684f jmp 0x8d6854
008d6851 mov esi, dword ptr [ebp - 0x1c]
008d6854 push dword ptr [ebp - 0x20]
008d6857 mov ebx, dword ptr [ebp - 0x18]
008d685a lea ecx, [ebp - 0x58]
008d685d call 0x4229a0
008d6862 movss xmm0, dword ptr [ebp - 0xc]
008d6867 lea ecx, [ebp - 0x58]
008d686a mov eax, dword ptr [edi]
008d686c push 0x1e
008d686e push ecx
008d686f push ebx
008d6870 push esi
008d6871 push ecx
008d6872 movss dword ptr [esp], xmm0
008d6877 mov ecx, edi
008d6879 call dword ptr [eax + 0x20]
008d687c mov ecx, dword ptr [ebp - 8]
008d687f pop edi
008d6880 pop esi
008d6881 xor ecx, ebp
008d6883 pop ebx
008d6884 call 0x9eacd7
008d6889 mov esp, ebp
008d688b pop ebp
008d688c ret 4
008d688f int3 
008d6890 lea eax, [ecx + 0x3dc]
008d6896 ret 
008d6897 int3 
008d6898 int3 
008d6899 int3 
008d689a int3 
008d689b int3 
008d689c int3 
008d689d int3 
008d689e int3 
008d689f int3 
