; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.
00939120 push ebx
00939121 mov ebx, esp
00939123 sub esp, 8
00939126 and esp, 0xfffffff8
00939129 add esp, 4
0093912c push ebp
0093912d mov ebp, dword ptr [ebx + 4]
00939130 mov dword ptr [esp + 4], ebp
00939134 mov ebp, esp
00939136 sub esp, 0x38
00939139 mov eax, dword ptr [ecx]
0093913b movss xmm0, dword ptr [0xb6aa3c] ; f32=40
00939143 push esi
00939144 push edi
00939145 mov ecx, dword ptr [eax + 0xc]
00939148 mov eax, dword ptr [ebx + 0x10]
0093914b cdq 
0093914c idiv ecx
0093914e mov edi, dword ptr [ebx + 0x24]
00939151 movd xmm6, edx
00939155 mov edx, dword ptr [ebx + 0x1c]
00939158 cvtdq2ps xmm6, xmm6
0093915b mov dword ptr [edi], 0
00939161 movd xmm7, eax
00939165 mov eax, dword ptr [ebx + 0x18]
00939168 mulss xmm6, xmm0
0093916c cvtdq2ps xmm7, xmm7
0093916f addss xmm6, xmm0
00939173 mulss xmm7, xmm0
00939177 movss xmm0, dword ptr [0xc02fec]
0093917f movss dword ptr [eax], xmm0
00939183 movss xmm0, dword ptr [0xc02ff0]
0093918b addss xmm7, dword ptr [0xb6ab20] ; f32=120
00939193 movss dword ptr [eax + 4], xmm0
00939198 mov eax, dword ptr [ebx + 0x20]
0093919b movss xmm0, dword ptr [0xc02fec]
009391a3 movss dword ptr [edx], xmm0
009391a7 movss xmm0, dword ptr [0xc02ff0]
009391af mov dword ptr [eax], 0x5a0e1bca
009391b5 mov eax, dword ptr [ebx + 0x14]
009391b8 movss dword ptr [ebp - 0x34], xmm6
009391bd movss dword ptr [ebp - 0x38], xmm7
009391c2 movss dword ptr [edx + 4], xmm0
009391c7 cmp eax, 9
009391ca je 0x9391df
009391cc cmp eax, 0xa
009391cf je 0x9391df
009391d1 cmp eax, 7
009391d4 je 0x9391df
009391d6 mov byte ptr [ebp - 1], 0
009391da cmp eax, 8
009391dd jne 0x9391e3
009391df mov byte ptr [ebp - 1], 1
009391e3 mov ecx, dword ptr [ebx + 0x28]
009391e6 mov esi, eax
009391e8 shl esi, 4
009391eb add esi, eax
009391ed mov byte ptr [ecx], 0
009391f0 xor ecx, ecx
009391f2 mov dword ptr [ebp - 8], ecx
009391f5 mov eax, dword ptr [esi*4 + 0xbc76f0]
009391fc dec eax
009391fd test eax, eax
009391ff jle 0x939504
00939205 movss xmm1, dword ptr [0xbc79e0] ; f32=999
0093920d movss xmm2, dword ptr [0xbc79dc] ; f32=999
00939215 nop word ptr [eax + eax]
00939220 lea edi, [ecx*8]
00939227 movss xmm5, dword ptr [edi + esi*4 + 0xbc76f4]
00939230 ucomiss xmm5, xmm2
00939233 lahf 
00939234 test ah, 0x44
00939237 jp 0x93924b
00939239 movss xmm0, dword ptr [edi + esi*4 + 0xbc76f8]
00939242 ucomiss xmm0, xmm1
00939245 lahf 
00939246 test ah, 0x44
00939249 jnp 0x93926f
0093924b movss xmm3, dword ptr [edi + esi*4 + 0xbc76fc]
00939254 ucomiss xmm3, xmm2
00939257 lahf 
00939258 test ah, 0x44
0093925b jp 0x939275
0093925d movss xmm0, dword ptr [edi + esi*4 + 0xbc7700]
00939266 ucomiss xmm0, xmm1
00939269 lahf 
0093926a test ah, 0x44
0093926d jp 0x939275
0093926f inc ecx
00939270 mov dword ptr [ebp - 8], ecx
00939273 jmp 0x939220
00939275 movss xmm1, dword ptr [edi + esi*4 + 0xbc76f8]
0093927e subss xmm3, xmm5
00939282 movss xmm4, dword ptr [edi + esi*4 + 0xbc7700]
0093928b addss xmm5, xmm6
0093928f mov eax, dword ptr [ebx + 8]
00939292 subss xmm4, xmm1
00939296 addss xmm1, xmm7
0093929a movaps xmm0, xmm3
0093929d movss dword ptr [ebp - 0x1c], xmm3
009392a2 mulss xmm0, xmm3
009392a6 movaps xmm2, xmm4
009392a9 movss dword ptr [ebp - 0x20], xmm4
009392ae mulss xmm2, xmm4
009392b2 movss dword ptr [ebp - 0x2c], xmm1
009392b7 movss dword ptr [ebp - 0x28], xmm5
009392bc addss xmm2, xmm0
009392c0 movss dword ptr [ebp - 0x14], xmm3
009392c5 movss xmm0, dword ptr [eax + 4]
009392ca subss xmm0, xmm1
009392ce movss dword ptr [ebp - 0x18], xmm4
009392d3 movss xmm1, dword ptr [eax]
009392d7 subss xmm1, xmm5
009392db mulss xmm0, xmm4
009392df mulss xmm1, xmm3
009392e3 addss xmm0, xmm1
009392e7 divss xmm0, xmm2
009392eb movss dword ptr [ebp - 0x24], xmm0
009392f0 movaps xmm0, xmm2
009392f3 call 0x4228c0
009392f8 comiss xmm0, dword ptr [0xb6a18c] ; f32=0
009392ff movss dword ptr [ebp - 0x30], xmm0
00939304 jbe 0x93932e
00939306 movss xmm1, dword ptr [0xb6a614] ; f32=1
0093930e divss xmm1, xmm0
00939312 movss xmm3, dword ptr [ebp - 0x1c]
00939317 movss xmm0, dword ptr [ebp - 0x20]
0093931c mulss xmm3, xmm1
00939320 mulss xmm0, xmm1
00939324 movss dword ptr [ebp - 0x14], xmm3
00939329 movss dword ptr [ebp - 0x18], xmm0
0093932e mov eax, dword ptr [ebx + 0xc]
00939331 movss xmm1, dword ptr [eax]
00939335 movss xmm2, dword ptr [eax + 4]
0093933a movaps xmm0, xmm1
0093933d mulss xmm0, xmm1
00939341 movss dword ptr [ebp - 0xc], xmm1
00939346 movaps xmm1, xmm2
00939349 mulss xmm1, xmm2
0093934d movss dword ptr [ebp - 0x10], xmm2
00939352 addss xmm0, xmm1
00939356 call 0x4228c0
0093935b movss xmm4, dword ptr [0xb6a614] ; f32=1
00939363 xorps xmm6, xmm6
00939366 comiss xmm0, xmm6
00939369 movss xmm2, dword ptr [ebp - 0x10]
0093936e jbe 0x939386
00939370 movaps xmm1, xmm4
00939373 divss xmm1, xmm0
00939377 movss xmm0, dword ptr [ebp - 0xc]
0093937c mulss xmm0, xmm1
00939380 mulss xmm2, xmm1
00939384 jmp 0x93938b
00939386 movss xmm0, dword ptr [ebp - 0xc]
0093938b movss xmm3, dword ptr [ebp - 0x14]
00939390 movss xmm5, dword ptr [ebp - 0x24]
00939395 comiss xmm6, xmm5
00939398 mov ecx, dword ptr [ebp - 8]
0093939b mulss xmm3, xmm0
0093939f movss xmm0, dword ptr [ebp - 0x18]
009393a4 mulss xmm0, xmm2
009393a8 movss xmm2, dword ptr [0xbc79dc] ; f32=999
009393b0 addss xmm3, xmm0
009393b4 andps xmm3, xmmword ptr [0xb6c980] ; f32=nan
009393bb jbe 0x9393f2
009393bd test ecx, ecx
009393bf jle 0x9393f2
009393c1 movss xmm0, dword ptr [edi + esi*4 + 0xbc76ec]
009393ca ucomiss xmm0, xmm2
009393cd lahf 
009393ce test ah, 0x44
009393d1 jp 0x9393ed
009393d3 movss xmm0, dword ptr [edi + esi*4 + 0xbc76f0]
009393dc movss xmm1, dword ptr [0xbc79e0] ; f32=999
009393e4 ucomiss xmm0, xmm1
009393e7 lahf 
009393e8 test ah, 0x44
009393eb jnp 0x9393fa
009393ed xorps xmm5, xmm5
009393f0 jmp 0x939434
009393f2 movss xmm1, dword ptr [0xbc79e0] ; f32=999
009393fa comiss xmm5, xmm4
009393fd jbe 0x939434
009393ff mov eax, dword ptr [esi*4 + 0xbc76f0]
00939406 add eax, -2
00939409 cmp ecx, eax
0093940b jge 0x939434
0093940d movss xmm0, dword ptr [edi + esi*4 + 0xbc7704]
00939416 ucomiss xmm0, xmm2
00939419 lahf 
0093941a test ah, 0x44
0093941d jp 0x939431
0093941f movss xmm0, dword ptr [edi + esi*4 + 0xbc7708]
00939428 ucomiss xmm0, xmm1
0093942b lahf 
0093942c test ah, 0x44
0093942f jnp 0x939434
00939431 movaps xmm5, xmm4
00939434 movss xmm1, dword ptr [ebp - 0x1c]
00939439 movss xmm4, dword ptr [ebp - 0x20]
0093943e movaps xmm6, xmm1
00939441 mov eax, dword ptr [ebx + 8]
00939444 movaps xmm7, xmm4
00939447 mulss xmm3, dword ptr [0xb6a974] ; f32=10
0093944f mov edi, dword ptr [ebx + 0x24]
00939452 mulss xmm6, xmm5
00939456 mulss xmm7, xmm5
0093945a addss xmm6, dword ptr [ebp - 0x28]
0093945f addss xmm7, dword ptr [ebp - 0x2c]
00939464 movaps xmm0, xmm6
00939467 subss xmm0, dword ptr [eax]
0093946b movaps xmm2, xmm7
0093946e subss xmm2, dword ptr [eax + 4]
00939473 mov eax, dword ptr [ebx + 0x20]
00939476 mulss xmm0, xmm0
0093947a mulss xmm2, xmm2
0093947e addss xmm2, xmm0
00939482 movss xmm0, dword ptr [eax]
00939486 subss xmm2, xmm3
0093948a comiss xmm0, xmm2
0093948d jbe 0x9394d3
0093948f movss dword ptr [eax], xmm2
00939493 mov eax, dword ptr [ebx + 0x18]
00939496 movss xmm2, dword ptr [ebp - 0x30]
0093949b comiss xmm2, dword ptr [0xb6a18c] ; f32=0
009394a2 movss dword ptr [edi], xmm5
009394a6 movss dword ptr [eax], xmm6
009394aa movss dword ptr [eax + 4], xmm7
009394af jbe 0x9394c5
009394b1 movss xmm0, dword ptr [0xb6a614] ; f32=1
009394b9 divss xmm0, xmm2
009394bd mulss xmm1, xmm0
009394c1 mulss xmm4, xmm0
009394c5 mov edx, dword ptr [ebx + 0x1c]
009394c8 movss dword ptr [edx], xmm1
009394cc movss dword ptr [edx + 4], xmm4
009394d1 jmp 0x9394d6
009394d3 mov edx, dword ptr [ebx + 0x1c]
009394d6 mov eax, dword ptr [esi*4 + 0xbc76f0]
009394dd inc ecx
009394de movss xmm1, dword ptr [0xbc79e0] ; f32=999
009394e6 dec eax
009394e7 movss xmm2, dword ptr [0xbc79dc] ; f32=999
009394ef movss xmm6, dword ptr [ebp - 0x34]
009394f4 movss xmm7, dword ptr [ebp - 0x38]
009394f9 mov dword ptr [ebp - 8], ecx
009394fc cmp ecx, eax
009394fe jl 0x939220
00939504 cmp byte ptr [ebp - 1], 0
00939508 mov eax, dword ptr [ebx + 0xc]
0093950b je 0x93953f
0093950d movss xmm0, dword ptr [edi]
00939511 comiss xmm0, dword ptr [0xb6a614] ; f32=1
00939518 jb 0x93953f
0093951a movss xmm1, dword ptr [eax + 4]
0093951f movss xmm0, dword ptr [edx]
00939523 mulss xmm1, dword ptr [edx + 4]
00939528 mulss xmm0, dword ptr [eax]
0093952c addss xmm1, xmm0
00939530 comiss xmm1, dword ptr [0xb6a18c] ; f32=0
00939537 jbe 0x93953f
00939539 mov ecx, dword ptr [ebx + 0x28]
0093953c mov byte ptr [ecx], 1
0093953f movss xmm3, dword ptr [edx + 4]
00939544 movss xmm2, dword ptr [edx]
00939548 movaps xmm1, xmm3
0093954b mulss xmm1, dword ptr [eax + 4]
00939550 movaps xmm0, xmm2
00939553 mulss xmm0, dword ptr [eax]
00939557 addss xmm1, xmm0
0093955b xorps xmm0, xmm0
0093955e ucomiss xmm1, xmm0
00939561 lahf 
00939562 test ah, 0x44
00939565 jp 0x939578
00939567 test byte ptr [ebx + 0x10], 1
0093956b je 0x93957d
0093956d pop edi
0093956e pop esi
0093956f mov esp, ebp
00939571 pop ebp
00939572 mov esp, ebx
00939574 pop ebx
00939575 ret 0x24
00939578 comiss xmm0, xmm1
0093957b jbe 0x939596
0093957d mulss xmm2, dword ptr [0xb6ae44] ; f32=-1
00939585 mulss xmm3, dword ptr [0xb6ae44] ; f32=-1
0093958d movss dword ptr [edx], xmm2
00939591 movss dword ptr [edx + 4], xmm3
00939596 pop edi
00939597 pop esi
00939598 mov esp, ebp
0093959a pop ebp
0093959b mov esp, ebx
0093959d pop ebx
0093959e ret 0x24
