004c3fd0 push ebx
004c3fd1 mov ebx, esp
004c3fd3 sub esp, 8
004c3fd6 and esp, 0xfffffff8
004c3fd9 add esp, 4
004c3fdc push ebp
004c3fdd mov ebp, dword ptr [ebx + 4]
004c3fe0 mov dword ptr [esp + 4], ebp
004c3fe4 mov ebp, esp
004c3fe6 sub esp, 0x98
004c3fec mov eax, dword ptr [0xbaa3b4]
004c3ff1 xor eax, ebp
004c3ff3 mov dword ptr [ebp - 4], eax
004c3ff6 mov eax, dword ptr [0xbfd65c]
004c3ffb xorps xmm3, xmm3
004c3ffe movss xmm5, dword ptr [0xb6c9b0]
004c4006 push esi
004c4007 push edi
004c4008 mov esi, dword ptr [eax + 0x18190]
004c400e mov edi, ecx
004c4010 movss xmm0, dword ptr [edi + 0x2b8]
004c4018 lea edx, [edi + 0x2b8]
004c401e movss xmm4, dword ptr [edx + 4]
004c4023 mov dword ptr [ebp - 0x20], esi
004c4026 cvttss2si eax, dword ptr [edi + 0x2f8]
004c402e cvttss2si ecx, dword ptr [edi + 0x2fc]
004c4036 movss dword ptr [ebp - 0xc], xmm0
004c403b sub ecx, eax
004c403d movss dword ptr [ebp - 8], xmm4
004c4042 mov eax, dword ptr [edi + 0xab4]
004c4048 mov dword ptr [ebp - 0x10], ecx
004c404b test eax, eax
004c404d je 0x4c4a78
004c4053 cmp eax, 3
004c4056 je 0x4c43c7
004c405c cmp eax, 0x10
004c405f jne 0x4c418d
004c4065 cmp dword ptr [edi + 0xb10], 0
004c406c jne 0x4c408c
004c406e movss xmm2, dword ptr [edi + 0x28c]
004c4076 mov ecx, 3
004c407b movss dword ptr [edx], xmm2
004c407f mov eax, dword ptr [edi + 0x290]
004c4085 mov dword ptr [edx + 4], eax
004c4088 xor eax, eax
004c408a jmp 0x4c40ab
004c408c cmp dword ptr [edi + 0x34], 0x3b7
004c4093 mov eax, 2
004c4098 mov dword ptr [ebp - 0x10], 0
004c409f mov ecx, 4
004c40a4 cmove eax, dword ptr [ebp - 0x10]
004c40a8 movaps xmm2, xmm0
004c40ab mov dword ptr [edi + 0x180], eax
004c40b1 mov dword ptr [edi + 0x17c], ecx
004c40b7 cmp dword ptr [esi + 8], 0x10
004c40bb jne 0x4c41eb
004c40c1 mov ecx, esi
004c40c3 call 0x7e2590
004c40c8 test al, al
004c40ca je 0x4c40da
004c40cc mov dword ptr [edi + 0x180], 0
004c40d6 xor eax, eax
004c40d8 jmp 0x4c40df
004c40da mov eax, 3
004c40df mov dword ptr [edi + 0x17c], eax
004c40e5 movss xmm1, dword ptr [edi + 0x2f4]
004c40ed movaps xmm0, xmm1
004c40f0 mulss xmm1, dword ptr [0xb6a50c]
004c40f8 mulss xmm0, xmm3
004c40fc addss xmm1, dword ptr [edx + 4]
004c4101 addss xmm0, xmm2
004c4105 movss dword ptr [edx + 4], xmm1
004c410a movss dword ptr [edx], xmm0
004c410e cmp byte ptr [edi + 0x188], 0
004c4115 je 0x4c4cf9
004c411b mov dword ptr [edi + 0x2a8], 0
004c4125 mov dword ptr [edi + 0xb00], 0
004c412f mov dword ptr [edi + 0xab4], 3
004c4139 mov dword ptr [edi + 0x17c], 5
004c4143 push ecx
004c4144 mov dword ptr [esp], 0x3f800000
004c414b push 0
004c414d push 2
004c414f push ecx
004c4150 mov dword ptr [esp], 0x3f800000
004c4157 mov ecx, edi
004c4159 push 0x102
004c415e call 0x6ad720
004c4163 push 0
004c4165 push 0xb4034c
004c416a lea ecx, [edi + 0x3c]
004c416d call 0x4054f0
004c4172 lea edx, [edi + 0x2b8]
004c4178 movss xmm0, dword ptr [ebp - 0xc]
004c417d movss xmm4, dword ptr [ebp - 8]
004c4182 xorps xmm3, xmm3
004c4185 movss xmm5, dword ptr [0xb6c9b0]
004c418d cmp dword ptr [edi + 0xab4], 0x10
004c4194 jne 0x4c4d3f
004c419a comiss xmm3, dword ptr [edx]
004c419d seta al
004c41a0 mov byte ptr [edi + 0x13c], al
004c41a6 mov esi, dword ptr [edi + 0x70]
004c41a9 test esi, esi
004c41ab je 0x4c4d30
004c41b1 cmp dword ptr [esi + 0x14], 0x10
004c41b5 mov eax, esi
004c41b7 jb 0x4c41bb
004c41b9 mov eax, dword ptr [esi]
004c41bb mov ecx, 0xb42410
004c41c0 mov dl, byte ptr [eax]
004c41c2 cmp dl, byte ptr [ecx]
004c41c4 jne 0x4c4d03
004c41ca test dl, dl
004c41cc je 0x4c41e4
004c41ce mov dl, byte ptr [eax + 1]
004c41d1 cmp dl, byte ptr [ecx + 1]
004c41d4 jne 0x4c4d03
004c41da add eax, 2
004c41dd add ecx, 2
004c41e0 test dl, dl
004c41e2 jne 0x4c41c0
004c41e4 xor eax, eax
004c41e6 jmp 0x4c4d08
004c41eb movss xmm2, dword ptr [edi + 0x2a8]
004c41f3 movss xmm0, dword ptr [0xb6af28]
004c41fb comiss xmm0, xmm2
004c41fe jbe 0x4c4214
004c4200 mov dword ptr [edi + 0x180], 0
004c420a mov dword ptr [edi + 0x17c], 3
004c4214 cmp dword ptr [edi + 0xb10], 2
004c421b jne 0x4c4331
004c4221 cmp dword ptr [edi + 0xbc], 0
004c4228 jg 0x4c4248
004c422a cmp dword ptr [edi + 0x50], 0x10
004c422e lea eax, [edi + 0x3c]
004c4231 jb 0x4c4236
004c4233 mov eax, dword ptr [edi + 0x3c]
004c4236 push 0
004c4238 push eax
004c4239 push 0xa0830c
004c423e push 3
004c4240 call 0x95e330
004c4245 add esp, 0x10
004c4248 cvttss2si eax, dword ptr [edi + 0x2fc]
004c4250 mov ecx, 3
004c4255 cdq 
004c4256 idiv ecx
004c4258 mov ecx, dword ptr [edi + 0xb8]
004c425e imul eax, edx, 0x2c
004c4261 add ecx, 0x48
004c4264 add eax, 0xbe9a98
004c4269 push eax
004c426a call 0x4021a0
004c426f movss xmm0, dword ptr [edi + 0xb04]
004c4277 push ecx
004c4278 lea ecx, [edi + 0x2b8]
004c427e mov dword ptr [edi + 0x17c], 6
004c4288 movss dword ptr [esp], xmm0
004c428d call 0x962860
004c4292 cmp byte ptr [edi + 0x188], 0
004c4299 je 0x4c4172
004c429f mov dword ptr [edi + 0xb10], 1
004c42a9 cmp dword ptr [edi + 0xbc], 0
004c42b0 jg 0x4c42d0
004c42b2 cmp dword ptr [edi + 0x50], 0x10
004c42b6 lea eax, [edi + 0x3c]
004c42b9 jb 0x4c42be
004c42bb mov eax, dword ptr [edi + 0x3c]
004c42be push 0
004c42c0 push eax
004c42c1 push 0xa0830c
004c42c6 push 3
004c42c8 call 0x95e330
004c42cd add esp, 0x10
004c42d0 lea ecx, [ebp - 0x94]
004c42d6 call 0x402120
004c42db mov ecx, dword ptr [edi + 0xb8]
004c42e1 push eax
004c42e2 add ecx, 0x48
004c42e5 call 0x4021a0
004c42ea movss xmm0, dword ptr [edi + 0x2b8]
004c42f2 lea edx, [edi + 0x2b8]
004c42f8 mulss xmm0, dword ptr [0xb6a2cc]
004c4300 movss dword ptr [edx], xmm0
004c4304 movss xmm0, dword ptr [edx + 4]
004c4309 mulss xmm0, dword ptr [0xb6a2cc]
004c4311 movss dword ptr [edx + 4], xmm0
004c4316 mov eax, dword ptr [edi + 0x164]
004c431c and dword ptr [edi + 0x160], 0xfbffffff
004c4326 mov dword ptr [edi + 0x164], eax
004c432c jmp 0x4c4178
004c4331 movss xmm1, dword ptr [edi + 0xb00]
004c4339 addss xmm1, dword ptr [0xb6a50c]
004c4341 movaps xmm0, xmm1
004c4344 movss dword ptr [edi + 0xb00], xmm1
004c434c addss xmm0, xmm2
004c4350 xorps xmm1, xmm5
004c4353 comiss xmm0, xmm1
004c4356 movss dword ptr [edi + 0x2a8], xmm0
004c435e jbe 0x4c4cf9
004c4364 cmp dword ptr [edi + 0x17c], 4
004c436b mov dword ptr [edi + 0x2a8], 0
004c4375 mov dword ptr [edi + 0xb00], 0
004c437f mov dword ptr [edi + 0xab4], 3
004c4389 jne 0x4c43ae
004c438b push dword ptr [edi + 0x298]
004c4391 mov ecx, esi
004c4393 push dword ptr [edi + 0x294]
004c4399 call 0x7aee40
004c439e test eax, eax
004c43a0 je 0x4c43ae
004c43a2 mov eax, dword ptr [edi]
004c43a4 mov ecx, edi
004c43a6 call dword ptr [eax + 0x24]
004c43a9 jmp 0x4c4172
004c43ae mov dword ptr [edi + 0x17c], 5
004c43b8 mov dword ptr [edi + 0x180], 4
004c43c2 jmp 0x4c4143
004c43c7 cmp dword ptr [esi + 8], 0x10
004c43cb jne 0x4c43ed
004c43cd mov eax, dword ptr [0xbfd65c]
004c43d2 mov eax, dword ptr [eax + 0x1a30dc]
004c43d8 sub eax, dword ptr [edi + 0x280]
004c43de cmp eax, 1
004c43e1 jg 0x4c43ed
004c43e3 mov dword ptr [edi + 0x38c], 0
004c43ed cmp byte ptr [edi + 0x188], 0
004c43f4 je 0x4c43fc
004c43f6 xor ecx, ecx
004c43f8 xor edx, edx
004c43fa jmp 0x4c4404
004c43fc mov ecx, dword ptr [edi + 0x38c]
004c4402 mov edx, ecx
004c4404 mov eax, dword ptr [edi + 0x160]
004c440a and eax, 0xb00
004c440f or eax, 0
004c4412 jne 0x4c441c
004c4414 cmp dword ptr [edi + 0xe88], eax
004c441a je 0x4c4428
004c441c mov eax, 5
004c4421 mov ecx, edx
004c4423 cmp edx, eax
004c4425 cmovg ecx, eax
004c4428 sub ecx, dword ptr [ebp - 0x10]
004c442b cmp dword ptr [edi + 0xb14], 0
004c4432 mov dword ptr [edi + 0x38c], ecx
004c4438 jne 0x4c4549
004c443e movss xmm0, dword ptr [edi + 0x2dc]
004c4446 comiss xmm0, dword ptr [edi + 0x2d8]
004c444d jbe 0x4c445e
004c444f mov dword ptr [edi + 0xb14], 1
004c4459 jmp 0x4c4561
004c445e push 0
004c4460 push 4
004c4462 mov ecx, edi
004c4464 call 0x684790
004c4469 test al, al
004c446b je 0x4c4561
004c4471 call 0x6c3d90
004c4476 test al, 3
004c4478 jne 0x4c4561
004c447e movss xmm3, dword ptr [0xb6aad4]
004c4486 lea eax, [edi + 0x294]
004c448c push 0x29
004c448e push eax
004c448f lea eax, [ebp - 0x30]
004c4492 push eax
004c4493 lea ecx, [esi + 0x1218]
004c4499 call 0x4157f0
004c449e mov edx, dword ptr [ebp - 0x24]
004c44a1 xor ecx, ecx
004c44a3 mov dword ptr [ebp - 8], ecx
004c44a6 test edx, edx
004c44a8 je 0x4c4536
004c44ae mov eax, dword ptr [edi + 0x160]
004c44b4 and eax, 0x100
004c44b9 mov dword ptr [ebp - 0xc], eax
004c44bc nop dword ptr [eax]
004c44c0 or eax, 0
004c44c3 mov esi, dword ptr [ebp - 0x2c]
004c44c6 mov esi, dword ptr [esi + ecx*4]
004c44c9 je 0x4c44ed
004c44cb push 0
004c44cd mov ecx, esi
004c44cf call 0x684630
004c44d4 test al, al
004c44d6 je 0x4c44e8
004c44d8 mov eax, dword ptr [esi + 0x160]
004c44de and eax, 0x20000000
004c44e3 or eax, 0
004c44e6 je 0x4c4529
004c44e8 mov eax, dword ptr [esi + 0x28]
004c44eb jmp 0x4c4506
004c44ed mov eax, dword ptr [esi + 0x28]
004c44f0 cmp eax, 1
004c44f3 jne 0x4c450c
004c44f5 mov ecx, esi
004c44f7 mov dword ptr [ebp - 0x10], eax
004c44fa call 0x786be0
004c44ff test al, al
004c4501 je 0x4c4529
004c4503 mov eax, dword ptr [ebp - 0x10]
004c4506 mov edx, dword ptr [ebp - 0x24]
004c4509 mov ecx, dword ptr [ebp - 8]
004c450c cmp eax, 0x355
004c4511 jne 0x4c451c
004c4513 cmp dword ptr [esi + 0xb14], 1
004c451a je 0x4c4529
004c451c inc ecx
004c451d mov dword ptr [ebp - 8], ecx
004c4520 cmp ecx, edx
004c4522 jae 0x4c4533
004c4524 mov eax, dword ptr [ebp - 0xc]
004c4527 jmp 0x4c44c0
004c4529 mov dword ptr [edi + 0xb14], 1
004c4533 mov esi, dword ptr [ebp - 0x20]
004c4536 cmp byte ptr [ebp - 0x30], 0
004c453a jne 0x4c4561
004c453c push dword ptr [ebp - 0x2c]
004c453f call 0x9eace5
004c4544 add esp, 4
004c4547 jmp 0x4c4561
004c4549 call 0x6c3d90
004c454e xor edx, edx
004c4550 mov ecx, 0x19
004c4555 div ecx
004c4557 test edx, edx
004c4559 jne 0x4c4561
004c455b mov dword ptr [edi + 0xb14], edx
004c4561 cmp dword ptr [edi + 0x38c], 0
004c4568 movss xmm0, dword ptr [0xb6a614]
004c4570 movss dword ptr [ebp - 0x10], xmm0
004c4575 jg 0x4c4954
004c457b mov ecx, edi
004c457d call 0x695680
004c4582 movss xmm0, dword ptr [eax + 0x294]
004c458a movss xmm2, dword ptr [eax + 0x298]
004c4592 mov eax, dword ptr [edi + 0x160]
004c4598 and eax, 0x100
004c459d movss dword ptr [ebp - 0xc], xmm0
004c45a2 or eax, 0
004c45a5 movss dword ptr [ebp - 0x1c], xmm0
004c45aa movss dword ptr [ebp - 8], xmm2
004c45af movss dword ptr [ebp - 0x18], xmm2
004c45b4 jne 0x4c4697
004c45ba cmp dword ptr [edi + 0xe88], eax
004c45c0 jne 0x4c4697
004c45c6 cmp dword ptr [edi + 0xb14], 1
004c45cd jne 0x4c45ef
004c45cf push eax
004c45d0 push eax
004c45d1 push eax
004c45d2 push eax
004c45d3 push 1
004c45d5 lea eax, [ebp - 0x1c]
004c45d8 mov ecx, esi
004c45da push eax
004c45db lea eax, [edi + 0x294]
004c45e1 push eax
004c45e2 call 0x7af4b0
004c45e7 test al, al
004c45e9 jne 0x4c468d
004c45ef push 0
004c45f1 push 0x800
004c45f6 mov ecx, edi
004c45f8 call 0x4122f0
004c45fd test al, al
004c45ff je 0x4c4655
004c4601 movss xmm1, dword ptr [ebp - 0xc]
004c4606 lea eax, [ebp - 0x58]
004c4609 movss xmm0, dword ptr [ebp - 8]
004c460e lea ecx, [ebp - 0x48]
004c4611 subss xmm1, dword ptr [edi + 0x294]
004c4619 subss xmm0, dword ptr [edi + 0x298]
004c4621 push eax
004c4622 movss dword ptr [ebp - 0x48], xmm1
004c4627 movss dword ptr [ebp - 0x44], xmm0
004c462c call 0x962560
004c4631 movss xmm0, dword ptr [eax + 4]
004c4636 movss xmm1, dword ptr [eax]
004c463a xorps xmm0, xmmword ptr [0xb6c9b0]
004c4641 xorps xmm1, xmmword ptr [0xb6c9b0]
004c4648 movss dword ptr [edi + 0x36c], xmm0
004c4650 jmp 0x4c470e
004c4655 push 0
004c4657 push 0x200
004c465c mov ecx, edi
004c465e call 0x4122f0
004c4663 test al, al
004c4665 je 0x4c4716
004c466b lea eax, [ebp - 0x60]
004c466e push eax
004c466f call 0x659290
004c4674 add esp, 4
004c4677 mov ecx, dword ptr [eax]
004c4679 mov dword ptr [edi + 0x368], ecx
004c467f mov eax, dword ptr [eax + 4]
004c4682 mov dword ptr [edi + 0x36c], eax
004c4688 jmp 0x4c4716
004c468d movss xmm0, dword ptr [ebp - 0xc]
004c4692 movss xmm2, dword ptr [ebp - 8]
004c4697 subss xmm0, dword ptr [edi + 0x294]
004c469f subss xmm2, dword ptr [edi + 0x298]
004c46a7 movaps xmm1, xmm0
004c46aa movss dword ptr [ebp - 0xc], xmm0
004c46af mulss xmm1, xmm0
004c46b3 movaps xmm0, xmm2
004c46b6 mulss xmm0, xmm2
004c46ba movss dword ptr [ebp - 8], xmm2
004c46bf addss xmm0, xmm1
004c46c3 call 0x4228c0
004c46c8 comiss xmm0, dword ptr [0xb6a18c]
004c46cf movss xmm1, dword ptr [ebp - 0xc]
004c46d4 jbe 0x4c46f4
004c46d6 movss xmm2, dword ptr [0xb6a614]
004c46de divss xmm2, xmm0
004c46e2 movaps xmm0, xmm2
004c46e5 mulss xmm1, xmm0
004c46e9 movss xmm0, dword ptr [ebp - 8]
004c46ee mulss xmm0, xmm2
004c46f2 jmp 0x4c46f9
004c46f4 movss xmm0, dword ptr [ebp - 8]
004c46f9 movss dword ptr [edi + 0x36c], xmm0
004c4701 movss xmm0, dword ptr [0xb6a7b0]
004c4709 movss dword ptr [ebp - 0x10], xmm0
004c470e movss dword ptr [edi + 0x368], xmm1
004c4716 movss xmm0, dword ptr [edi + 0x368]
004c471e ucomiss xmm0, dword ptr [0xc02fec]
004c4725 movss xmm5, dword ptr [edi + 0x36c]
004c472d lahf 
004c472e test ah, 0x44
004c4731 jp 0x4c4761
004c4733 ucomiss xmm5, dword ptr [0xc02ff0]
004c473a lahf 
004c473b test ah, 0x44
004c473e jp 0x4c4761
004c4740 lea eax, [ebp - 0x68]
004c4743 push eax
004c4744 call 0x659290
004c4749 add esp, 4
004c474c mov ecx, dword ptr [eax]
004c474e mov dword ptr [edi + 0x368], ecx
004c4754 movss xmm5, dword ptr [eax + 4]
004c4759 movss dword ptr [edi + 0x36c], xmm5
004c4761 movss xmm2, dword ptr [0xb6a910]
004c4769 movss xmm1, dword ptr [0xb6aa3c]
004c4771 movss xmm3, dword ptr [0xb6a480]
004c4779 mov dword ptr [ebp - 8], 0
004c4780 movss xmm0, dword ptr [edi + 0x368]
004c4788 mulss xmm0, xmm2
004c478c mulss xmm5, xmm2
004c4790 addss xmm0, dword ptr [edi + 0x294]
004c4798 addss xmm5, dword ptr [edi + 0x298]
004c47a0 subss xmm0, xmm1
004c47a4 subss xmm5, dword ptr [0xb6ab20]
004c47ac divss xmm0, xmm1
004c47b0 divss xmm5, xmm1
004c47b4 addss xmm0, xmm3
004c47b8 addss xmm5, xmm3
004c47bc cvttss2si edx, xmm0
004c47c0 cvttss2si ecx, xmm5
004c47c4 test edx, edx
004c47c6 js 0x4c47df
004c47c8 mov eax, dword ptr [esi + 0xc]
004c47cb cmp edx, eax
004c47cd jge 0x4c47df
004c47cf test ecx, ecx
004c47d1 js 0x4c47df
004c47d3 cmp ecx, dword ptr [esi + 0x10]
004c47d6 jge 0x4c47df
004c47d8 imul eax, ecx
004c47db add eax, edx
004c47dd jmp 0x4c47e2
004c47df or eax, 0xffffffff
004c47e2 push eax
004c47e3 mov ecx, esi
004c47e5 call 0x7aeec0
004c47ea test eax, eax
004c47ec je 0x4c48ba
004c47f2 call 0x6c3d90
004c47f7 movss xmm1, dword ptr [0xb6aae4]
004c47ff movd xmm0, eax
004c4803 cvtdq2pd xmm0, xmm0
004c4807 shr eax, 0x1f
004c480a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c4813 cvtpd2ps xmm0, xmm0
004c4817 mulss xmm0, dword ptr [0xb6a19c]
004c481f mulss xmm0, dword ptr [0xb6ab88]
004c4827 subss xmm1, xmm0
004c482b mulss xmm1, dword ptr [0xb6a230]
004c4833 movaps xmm0, xmm1
004c4836 movss dword ptr [ebp - 0xc], xmm1
004c483b call 0x411fe0
004c4840 movss dword ptr [ebp - 0x18], xmm0
004c4845 movss xmm0, dword ptr [ebp - 0xc]
004c484a call 0x412010
004c484f movss xmm1, dword ptr [edi + 0x36c]
004c4857 movaps xmm2, xmm0
004c485a movss xmm5, dword ptr [edi + 0x368]
004c4862 movaps xmm0, xmm1
004c4865 mulss xmm1, dword ptr [ebp - 0x18]
004c486a movaps xmm3, xmm5
004c486d mov eax, dword ptr [ebp - 8]
004c4870 mulss xmm3, dword ptr [ebp - 0x18]
004c4875 inc eax
004c4876 mov dword ptr [ebp - 8], eax
004c4879 mulss xmm0, xmm2
004c487d mulss xmm5, xmm2
004c4881 movss xmm2, dword ptr [0xb6a910]
004c4889 subss xmm3, xmm0
004c488d addss xmm5, xmm1
004c4891 movss xmm1, dword ptr [0xb6aa3c]
004c4899 movss dword ptr [edi + 0x368], xmm3
004c48a1 movss xmm3, dword ptr [0xb6a480]
004c48a9 movss dword ptr [edi + 0x36c], xmm5
004c48b1 cmp eax, 0xa
004c48b4 jl 0x4c4780
004c48ba call 0x6c3d90
004c48bf movss xmm2, dword ptr [0xb6a7b0]
004c48c7 movd xmm0, eax
004c48cb cvtdq2pd xmm0, xmm0
004c48cf shr eax, 0x1f
004c48d2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c48db cvtpd2ps xmm0, xmm0
004c48df mulss xmm0, dword ptr [0xb6a19c]
004c48e7 mulss xmm0, dword ptr [0xb6a8cc]
004c48ef subss xmm2, xmm0
004c48f3 movss dword ptr [edi + 0x370], xmm2
004c48fb call 0x6c3d90
004c4900 movd xmm0, eax
004c4904 cvtdq2pd xmm0, xmm0
004c4908 shr eax, 0x1f
004c490b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c4914 cvtpd2ps xmm0, xmm0
004c4918 mulss xmm0, dword ptr [0xb6a19c]
004c4920 mulss xmm0, dword ptr [0xb6a3b0]
004c4928 addss xmm0, dword ptr [0xb6a304]
004c4930 mulss xmm0, dword ptr [ebp - 0x10]
004c4935 movss dword ptr [edi + 0x374], xmm0
004c493d call 0x6c3d90
004c4942 xor edx, edx
004c4944 mov ecx, 0x1e
004c4949 div ecx
004c494b add edx, 0xa
004c494e mov dword ptr [edi + 0x38c], edx
004c4954 movss xmm0, dword ptr [edi + 0x2c4]
004c495c mulss xmm0, dword ptr [0xb6a560]
004c4964 movss xmm1, dword ptr [edi + 0x2f4]
004c496c movss dword ptr [edi + 0x2c4], xmm0
004c4974 movss xmm3, dword ptr [edi + 0x374]
004c497c movaps xmm0, xmm3
004c497f mulss xmm0, dword ptr [edi + 0x368]
004c4987 mulss xmm0, xmm1
004c498b addss xmm0, dword ptr [edi + 0x2b8]
004c4993 movss dword ptr [edi + 0x2b8], xmm0
004c499b mulss xmm3, dword ptr [edi + 0x36c]
004c49a3 movss xmm0, dword ptr [edi + 0x370]
004c49ab mulss xmm0, dword ptr [0xb6a230]
004c49b3 mulss xmm3, xmm1
004c49b7 movss dword ptr [ebp - 0x18], xmm0
004c49bc addss xmm3, dword ptr [edi + 0x2bc]
004c49c4 movss dword ptr [edi + 0x2bc], xmm3
004c49cc call 0x411fe0
004c49d1 movss dword ptr [ebp - 0x10], xmm0
004c49d6 movss xmm0, dword ptr [ebp - 0x18]
004c49db call 0x412010
004c49e0 movss xmm4, dword ptr [edi + 0x368]
004c49e8 movaps xmm2, xmm0
004c49eb movss xmm1, dword ptr [edi + 0x36c]
004c49f3 movaps xmm5, xmm4
004c49f6 mulss xmm5, dword ptr [ebp - 0x10]
004c49fb movaps xmm0, xmm1
004c49fe mulss xmm1, dword ptr [ebp - 0x10]
004c4a03 xorps xmm3, xmm3
004c4a06 mulss xmm0, xmm2
004c4a0a mulss xmm4, xmm2
004c4a0e subss xmm5, xmm0
004c4a12 addss xmm4, xmm1
004c4a16 movss dword ptr [edi + 0x368], xmm5
004c4a1e movss dword ptr [edi + 0x36c], xmm4
004c4a26 cmp dword ptr [esi + 8], 0x10
004c4a2a jne 0x4c4a65
004c4a2c comiss xmm5, xmm3
004c4a2f mov dword ptr [edi + 0x36c], 0
004c4a39 xorps xmm4, xmm4
004c4a3c jbe 0x4c4a5b
004c4a3e mov dword ptr [edi + 0x368], 0x3f800000
004c4a48 lea edx, [edi + 0x2b8]
004c4a4e movss xmm0, dword ptr [edi + 0x368]
004c4a56 jmp 0x4c4185
004c4a5b mov dword ptr [edi + 0x368], 0xbf800000
004c4a65 movss xmm0, dword ptr [edi + 0x368]
004c4a6d lea edx, [edi + 0x2b8]
004c4a73 jmp 0x4c4185
004c4a78 cmp dword ptr [edi + 0x284], 0
004c4a7f movq xmm0, qword ptr [0xa08adc]
004c4a87 mov eax, dword ptr [0xa08ae4]
004c4a8c mov esi, dword ptr [edi + 0x344]
004c4a92 movq qword ptr [ebp - 0x3c], xmm0
004c4a97 mov dword ptr [ebp - 8], eax
004c4a9a jl 0x4c4aaf
004c4a9c mov eax, dword ptr [edi + 0x164]
004c4aa2 and dword ptr [edi + 0x160], 0xfffffffb
004c4aa9 mov dword ptr [edi + 0x164], eax
004c4aaf cmp dword ptr [edi + 0x2c], 0xa
004c4ab3 jne 0x4c4c28
004c4ab9 cmp byte ptr [edi + 0x16b], 0
004c4ac0 jne 0x4c4c28
004c4ac6 and dword ptr [edi + 0x160], 0xfffffffb
004c4acd cmp dword ptr [edi + 0x30], 0
004c4ad1 mov eax, dword ptr [edi + 0x164]
004c4ad7 mov dword ptr [edi + 0x164], eax
004c4add mov dword ptr [ebp - 0x10], 0
004c4ae4 jbe 0x4c5083
004c4aea nop word ptr [eax + eax]
004c4af0 test esi, esi
004c4af2 jne 0x4c4b04
004c4af4 push 0xb4d6c4
004c4af9 push 3
004c4afb call 0x95e330
004c4b00 add esp, 8
004c4b03 int3 
004c4b04 mov ecx, dword ptr [ebp - 0x3c]
004c4b07 mov eax, esi
004c4b09 shr eax, cl
004c4b0b mov ecx, dword ptr [ebp - 0x38]
004c4b0e xor eax, esi
004c4b10 mov edx, eax
004c4b12 shl edx, cl
004c4b14 mov ecx, dword ptr [ebp - 8]
004c4b17 xor edx, eax
004c4b19 mov esi, edx
004c4b1b shr esi, cl
004c4b1d xor esi, edx
004c4b1f mov eax, esi
004c4b21 shr eax, 0x1f
004c4b24 movd xmm0, esi
004c4b28 cvtdq2pd xmm0, xmm0
004c4b2c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c4b35 cvtpd2ps xmm1, xmm0
004c4b39 mulss xmm1, dword ptr [0xb6a198]
004c4b41 movss dword ptr [ebp - 0x18], xmm1
004c4b46 test esi, esi
004c4b48 jne 0x4c4b5f
004c4b4a push 0xb4d6c4
004c4b4f push 3
004c4b51 call 0x95e330
004c4b56 add esp, 8
004c4b59 int3 
004c4b5a movss xmm1, dword ptr [ebp - 0x18]
004c4b5f mov ecx, dword ptr [ebp - 0x3c]
004c4b62 mov eax, esi
004c4b64 shr eax, cl
004c4b66 mov ecx, dword ptr [ebp - 0x38]
004c4b69 xor eax, esi
004c4b6b mov edx, eax
004c4b6d mulss xmm1, dword ptr [0xb6aa34]
004c4b75 shl edx, cl
004c4b77 mov ecx, dword ptr [ebp - 8]
004c4b7a xor edx, eax
004c4b7c mov esi, edx
004c4b7e shr esi, cl
004c4b80 xor esi, edx
004c4b82 subss xmm1, dword ptr [0xb6a9c0]
004c4b8a mov eax, esi
004c4b8c shr eax, 0x1f
004c4b8f movd xmm0, esi
004c4b93 cvtdq2pd xmm0, xmm0
004c4b97 addss xmm1, dword ptr [edi + 0x298]
004c4b9f addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c4ba8 movss dword ptr [ebp - 0x4c], xmm1
004c4bad cvtpd2ps xmm0, xmm0
004c4bb1 mulss xmm0, dword ptr [0xb6a198]
004c4bb9 mulss xmm0, dword ptr [0xb6aa34]
004c4bc1 subss xmm0, dword ptr [0xb6a9c0]
004c4bc9 addss xmm0, dword ptr [edi + 0x294]
004c4bd1 movss dword ptr [ebp - 0x50], xmm0
004c4bd6 call 0x6c3d90
004c4bdb mov ecx, dword ptr [0xbfd65c]
004c4be1 push eax
004c4be2 push 0
004c4be4 push 0
004c4be6 push 0xc02fec
004c4beb lea eax, [ebp - 0x50]
004c4bee push eax
004c4bef push 0
004c4bf1 push dword ptr [edi + 0x28]
004c4bf4 call 0x422e20
004c4bf9 mov ecx, dword ptr [eax + 0x164]
004c4bff mov edx, dword ptr [eax]
004c4c01 and dword ptr [eax + 0x160], 0xfffffffb
004c4c08 mov dword ptr [eax + 0x164], ecx
004c4c0e mov ecx, eax
004c4c10 call dword ptr [edx + 0xc]
004c4c13 mov eax, dword ptr [ebp - 0x10]
004c4c16 inc eax
004c4c17 mov dword ptr [ebp - 0x10], eax
004c4c1a cmp eax, dword ptr [edi + 0x30]
004c4c1d jb 0x4c4af0
004c4c23 jmp 0x4c5083
004c4c28 mov dword ptr [edi + 0xab4], 3
004c4c32 call 0x6c3d90
004c4c37 movd xmm0, eax
004c4c3b cvtdq2pd xmm0, xmm0
004c4c3f shr eax, 0x1f
004c4c42 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c4c4b cvtpd2ps xmm0, xmm0
004c4c4f mulss xmm0, dword ptr [0xb6a19c]
004c4c57 mulss xmm0, dword ptr [0xb6a874]
004c4c5f addss xmm0, xmm0
004c4c63 movss dword ptr [ebp - 0x18], xmm0
004c4c68 call 0x411fe0
004c4c6d movss dword ptr [ebp - 0x10], xmm0
004c4c72 movss xmm0, dword ptr [ebp - 0x18]
004c4c77 call 0x412010
004c4c7c movss xmm1, dword ptr [ebp - 0x10]
004c4c81 movss dword ptr [edi + 0x368], xmm1
004c4c89 movss dword ptr [edi + 0x36c], xmm0
004c4c91 test esi, esi
004c4c93 jne 0x4c4ca5
004c4c95 push 0xb4d6c4
004c4c9a push 3
004c4c9c call 0x95e330
004c4ca1 add esp, 8
004c4ca4 int3 
004c4ca5 mov ecx, dword ptr [ebp - 0x3c]
004c4ca8 mov eax, esi
004c4caa shr eax, cl
004c4cac mov ecx, dword ptr [ebp - 0x38]
004c4caf xor eax, esi
004c4cb1 mov edx, eax
004c4cb3 shl edx, cl
004c4cb5 mov ecx, dword ptr [ebp - 8]
004c4cb8 xor edx, eax
004c4cba mov esi, edx
004c4cbc mov eax, 0x88888889
004c4cc1 shr esi, cl
004c4cc3 xor esi, edx
004c4cc5 mul esi
004c4cc7 shr edx, 4
004c4cca mov eax, edx
004c4ccc shl eax, 4
004c4ccf sub eax, edx
004c4cd1 lea edx, [edi + 0x2b8]
004c4cd7 add eax, eax
004c4cd9 sub esi, eax
004c4cdb add esi, 0xa
004c4cde mov dword ptr [edi + 0x38c], esi
004c4ce4 movss xmm0, dword ptr [edi + 0x368]
004c4cec movss xmm4, dword ptr [edi + 0x36c]
004c4cf4 jmp 0x4c4182
004c4cf9 movss xmm0, dword ptr [ebp - 0xc]
004c4cfe jmp 0x4c418d
004c4d03 sbb eax, eax
004c4d05 or eax, 1
004c4d08 test eax, eax
004c4d0a jne 0x4c4d30
004c4d0c cmp byte ptr [esi + 0x34], al
004c4d0f je 0x4c4ffe
004c4d15 cmp byte ptr [edi + 0x80], al
004c4d1b lea esi, [edi + 0x3c]
004c4d1e jne 0x4c4ffe
004c4d24 push 1
004c4d26 push 0xb42410
004c4d2b jmp 0x4c4fe7
004c4d30 push 1
004c4d32 lea esi, [edi + 0x3c]
004c4d35 push 0xb42410
004c4d3a jmp 0x4c4fe7
004c4d3f mov eax, dword ptr [edi + 0x70]
004c4d42 test eax, eax
004c4d44 je 0x4c4d59
004c4d46 cmp byte ptr [eax + 0x34], 0
004c4d4a jne 0x4c4d59
004c4d4c cmp byte ptr [edi + 0x80], 0
004c4d53 jne 0x4c4ffe
004c4d59 comiss xmm3, xmm0
004c4d5c mov byte ptr [edi + 0x13c], 0
004c4d63 jbe 0x4c4d6f
004c4d65 mov byte ptr [edi + 0x13c], 1
004c4d6c xorps xmm0, xmm5
004c4d6f movaps xmm1, xmm0
004c4d72 movaps xmm0, xmm4
004c4d75 call 0x447a80
004c4d7a mulss xmm0, dword ptr [0xb6aa84]
004c4d82 sub esp, 8
004c4d85 addss xmm0, dword ptr [0xb6a9d4]
004c4d8d divss xmm0, dword ptr [0xb6aa4c]
004c4d95 movss dword ptr [ebp - 0x18], xmm0
004c4d9a fld dword ptr [ebp - 0x18]
004c4d9d fstp qword ptr [esp]
004c4da0 call 0x9ec3b2
004c4da5 fstp dword ptr [ebp - 0x18]
004c4da8 fld dword ptr [ebp - 0x18]
004c4dab add esp, 8
004c4dae fstp dword ptr [ebp - 0x18]
004c4db1 cvttss2si eax, dword ptr [ebp - 0x18]
004c4db6 add eax, 2
004c4db9 cmp eax, 3
004c4dbc ja 0x4c4f8c
004c4dc2 jmp dword ptr [eax*4 + 0x4c50a0]
004c4dc9 mov esi, dword ptr [edi + 0x70]
004c4dcc test esi, esi
004c4dce je 0x4c4e2d
004c4dd0 cmp dword ptr [esi + 0x14], 0x10
004c4dd4 mov eax, esi
004c4dd6 jb 0x4c4dda
004c4dd8 mov eax, dword ptr [esi]
004c4dda mov ecx, 0xb42418
004c4ddf nop 
004c4de0 mov dl, byte ptr [eax]
004c4de2 cmp dl, byte ptr [ecx]
004c4de4 jne 0x4c4e00
004c4de6 test dl, dl
004c4de8 je 0x4c4dfc
004c4dea mov dl, byte ptr [eax + 1]
004c4ded cmp dl, byte ptr [ecx + 1]
004c4df0 jne 0x4c4e00
004c4df2 add eax, 2
004c4df5 add ecx, 2
004c4df8 test dl, dl
004c4dfa jne 0x4c4de0
004c4dfc xor eax, eax
004c4dfe jmp 0x4c4e05
004c4e00 sbb eax, eax
004c4e02 or eax, 1
004c4e05 test eax, eax
004c4e07 jne 0x4c4e2d
004c4e09 cmp byte ptr [esi + 0x34], al
004c4e0c je 0x4c4ffe
004c4e12 cmp byte ptr [edi + 0x80], al
004c4e18 lea esi, [edi + 0x3c]
004c4e1b jne 0x4c4ffe
004c4e21 push 1
004c4e23 push 0xb42418
004c4e28 jmp 0x4c4fe7
004c4e2d push 1
004c4e2f lea esi, [edi + 0x3c]
004c4e32 push 0xb42418
004c4e37 jmp 0x4c4fe7
004c4e3c mov esi, dword ptr [edi + 0x70]
004c4e3f test esi, esi
004c4e41 je 0x4c4e9f
004c4e43 cmp dword ptr [esi + 0x14], 0x10
004c4e47 mov eax, esi
004c4e49 jb 0x4c4e4d
004c4e4b mov eax, dword ptr [esi]
004c4e4d mov ecx, 0xb423f4
004c4e52 mov dl, byte ptr [eax]
004c4e54 cmp dl, byte ptr [ecx]
004c4e56 jne 0x4c4e72
004c4e58 test dl, dl
004c4e5a je 0x4c4e6e
004c4e5c mov dl, byte ptr [eax + 1]
004c4e5f cmp dl, byte ptr [ecx + 1]
004c4e62 jne 0x4c4e72
004c4e64 add eax, 2
004c4e67 add ecx, 2
004c4e6a test dl, dl
004c4e6c jne 0x4c4e52
004c4e6e xor eax, eax
004c4e70 jmp 0x4c4e77
004c4e72 sbb eax, eax
004c4e74 or eax, 1
004c4e77 test eax, eax
004c4e79 jne 0x4c4e9f
004c4e7b cmp byte ptr [esi + 0x34], al
004c4e7e je 0x4c4ffe
004c4e84 cmp byte ptr [edi + 0x80], al
004c4e8a lea esi, [edi + 0x3c]
004c4e8d jne 0x4c4ffe
004c4e93 push 1
004c4e95 push 0xb423f4
004c4e9a jmp 0x4c4fe7
004c4e9f push 1
004c4ea1 lea esi, [edi + 0x3c]
004c4ea4 push 0xb423f4
004c4ea9 jmp 0x4c4fe7
004c4eae mov esi, dword ptr [edi + 0x70]
004c4eb1 test esi, esi
004c4eb3 je 0x4c4f11
004c4eb5 cmp dword ptr [esi + 0x14], 0x10
004c4eb9 mov eax, esi
004c4ebb jb 0x4c4ebf
004c4ebd mov eax, dword ptr [esi]
004c4ebf mov ecx, 0xb42404
004c4ec4 mov dl, byte ptr [eax]
004c4ec6 cmp dl, byte ptr [ecx]
004c4ec8 jne 0x4c4ee4
004c4eca test dl, dl
004c4ecc je 0x4c4ee0
004c4ece mov dl, byte ptr [eax + 1]
004c4ed1 cmp dl, byte ptr [ecx + 1]
004c4ed4 jne 0x4c4ee4
004c4ed6 add eax, 2
004c4ed9 add ecx, 2
004c4edc test dl, dl
004c4ede jne 0x4c4ec4
004c4ee0 xor eax, eax
004c4ee2 jmp 0x4c4ee9
004c4ee4 sbb eax, eax
004c4ee6 or eax, 1
004c4ee9 test eax, eax
004c4eeb jne 0x4c4f11
004c4eed cmp byte ptr [esi + 0x34], al
004c4ef0 je 0x4c4ffe
004c4ef6 cmp byte ptr [edi + 0x80], al
004c4efc lea esi, [edi + 0x3c]
004c4eff jne 0x4c4ffe
004c4f05 push 1
004c4f07 push 0xb42404
004c4f0c jmp 0x4c4fe7
004c4f11 push 1
004c4f13 lea esi, [edi + 0x3c]
004c4f16 push 0xb42404
004c4f1b jmp 0x4c4fe7
004c4f20 mov esi, dword ptr [edi + 0x70]
004c4f23 test esi, esi
004c4f25 je 0x4c4f80
004c4f27 cmp dword ptr [esi + 0x14], 0x10
004c4f2b mov eax, esi
004c4f2d jb 0x4c4f31
004c4f2f mov eax, dword ptr [esi]
004c4f31 mov ecx, 0xb42438
004c4f36 mov dl, byte ptr [eax]
004c4f38 cmp dl, byte ptr [ecx]
004c4f3a jne 0x4c4f56
004c4f3c test dl, dl
004c4f3e je 0x4c4f52
004c4f40 mov dl, byte ptr [eax + 1]
004c4f43 cmp dl, byte ptr [ecx + 1]
004c4f46 jne 0x4c4f56
004c4f48 add eax, 2
004c4f4b add ecx, 2
004c4f4e test dl, dl
004c4f50 jne 0x4c4f36
004c4f52 xor eax, eax
004c4f54 jmp 0x4c4f5b
004c4f56 sbb eax, eax
004c4f58 or eax, 1
004c4f5b test eax, eax
004c4f5d jne 0x4c4f80
004c4f5f cmp byte ptr [esi + 0x34], al
004c4f62 je 0x4c4ffe
004c4f68 cmp byte ptr [edi + 0x80], al
004c4f6e lea esi, [edi + 0x3c]
004c4f71 jne 0x4c4ffe
004c4f77 push 1
004c4f79 push 0xb42438
004c4f7e jmp 0x4c4fe7
004c4f80 push 1
004c4f82 lea esi, [edi + 0x3c]
004c4f85 push 0xb42438
004c4f8a jmp 0x4c4fe7
004c4f8c mov esi, dword ptr [edi + 0x70]
004c4f8f test esi, esi
004c4f91 je 0x4c4fdd
004c4f93 cmp dword ptr [esi + 0x14], 0x10
004c4f97 mov eax, esi
004c4f99 jb 0x4c4f9d
004c4f9b mov eax, dword ptr [esi]
004c4f9d mov ecx, 0xb4244c
004c4fa2 mov dl, byte ptr [eax]
004c4fa4 cmp dl, byte ptr [ecx]
004c4fa6 jne 0x4c4fc2
004c4fa8 test dl, dl
004c4faa je 0x4c4fbe
004c4fac mov dl, byte ptr [eax + 1]
004c4faf cmp dl, byte ptr [ecx + 1]
004c4fb2 jne 0x4c4fc2
004c4fb4 add eax, 2
004c4fb7 add ecx, 2
004c4fba test dl, dl
004c4fbc jne 0x4c4fa2
004c4fbe xor eax, eax
004c4fc0 jmp 0x4c4fc7
004c4fc2 sbb eax, eax
004c4fc4 or eax, 1
004c4fc7 test eax, eax
004c4fc9 jne 0x4c4fdd
004c4fcb cmp byte ptr [esi + 0x34], al
004c4fce je 0x4c4ffe
004c4fd0 cmp byte ptr [edi + 0x80], al
004c4fd6 lea esi, [edi + 0x3c]
004c4fd9 jne 0x4c4ffe
004c4fdb jmp 0x4c4fe0
004c4fdd lea esi, [edi + 0x3c]
004c4fe0 push 1
004c4fe2 push 0xb4244c
004c4fe7 mov ecx, esi
004c4fe9 call 0x405740
004c4fee test al, al
004c4ff0 je 0x4c4ffe
004c4ff2 lea ecx, [esi + 0x30]
004c4ff5 call 0x405330
004c4ffa mov byte ptr [esi + 0x44], 1
004c4ffe mov ecx, dword ptr [ebp - 0x20]
004c5001 mov eax, dword ptr [ecx + 4]
004c5004 mov eax, dword ptr [eax + 0x10]
004c5007 test eax, eax
004c5009 je 0x4c508a
004c500f cmp dword ptr [eax + 8], 0x10
004c5013 jne 0x4c508a
004c5015 cmp dword ptr [eax], 0x23
004c5018 jne 0x4c508a
004c501a movss xmm0, dword ptr [edi + 0x2bc]
004c5022 comiss xmm0, dword ptr [0xb6a18c]
004c5029 jbe 0x4c508a
004c502b movss xmm1, dword ptr [ecx + 0x20]
004c5030 subss xmm1, dword ptr [0xb6aa0c]
004c5038 movss xmm0, dword ptr [edi + 0x298]
004c5040 comiss xmm0, xmm1
004c5043 jbe 0x4c508a
004c5045 movss xmm0, dword ptr [edi + 0x294]
004c504d movss dword ptr [ebp - 0x14], xmm0
004c5052 movss dword ptr [ebp - 0x10], xmm1
004c5057 call 0x6c3d90
004c505c mov ecx, dword ptr [0xbfd65c]
004c5062 push eax
004c5063 push 0x42
004c5065 push 0
004c5067 push 0xc02fec
004c506c lea eax, [ebp - 0x14]
004c506f push eax
004c5070 push 0x10
004c5072 push 0x3e8
004c5077 call 0x422e20
004c507c mov ecx, eax
004c507e mov edx, dword ptr [eax]
004c5080 call dword ptr [edx + 0xc]
004c5083 mov eax, dword ptr [edi]
004c5085 mov ecx, edi
004c5087 call dword ptr [eax + 0x28]
004c508a mov ecx, dword ptr [ebp - 4]
004c508d pop edi
004c508e xor ecx, ebp
004c5090 pop esi
004c5091 call 0x9eacd7
004c5096 mov esp, ebp
004c5098 pop ebp
004c5099 mov esp, ebx
004c509b pop ebx
004c509c ret 
