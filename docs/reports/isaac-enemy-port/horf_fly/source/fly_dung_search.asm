004f6383 cmp byte ptr [esp + 0xb], 0
004f6388 jne 0x4f64f5
004f638e call 0x6c3d90
004f6393 movd xmm0, eax
004f6397 cvtdq2pd xmm0, xmm0
004f639b shr eax, 0x1f
004f639e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f63a7 cvtpd2ps xmm1, xmm0
004f63ab mulss xmm1, dword ptr [0xb6a19c]
004f63b3 call 0x6c3d90
004f63b8 movd xmm0, eax
004f63bc cvtdq2pd xmm0, xmm0
004f63c0 shr eax, 0x1f
004f63c3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f63cc lea eax, [esp + 0x2c]
004f63d0 push eax
004f63d1 cvtpd2ps xmm0, xmm0
004f63d5 mulss xmm0, dword ptr [0xb6a19c]
004f63dd mulss xmm0, xmm1
004f63e1 mulss xmm0, dword ptr [0xb6abe4]
004f63e9 movss dword ptr [esp + 0x10], xmm0
004f63ef call 0x659290
004f63f4 movss xmm1, dword ptr [esp + 0x10]
004f63fa add esp, 4
004f63fd mov edi, dword ptr [0xbfd65c]
004f6403 movaps xmm0, xmm1
004f6406 mulss xmm0, dword ptr [eax]
004f640a mulss xmm1, dword ptr [eax + 4]
004f640f lea eax, [esp + 0xc]
004f6413 mov edi, dword ptr [edi + 0x18190]
004f6419 mov ecx, edi
004f641b addss xmm0, dword ptr [esi + 0x294]
004f6423 push eax
004f6424 addss xmm1, dword ptr [esi + 0x298]
004f642c movss dword ptr [esp + 0x10], xmm0
004f6432 movss dword ptr [esp + 0x14], xmm1
004f6438 call 0x7ce950
004f643d test eax, eax
004f643f js 0x4f6474
004f6441 cmp eax, 0x1c0
004f6446 jge 0x4f6474
004f6448 mov edx, dword ptr [edi + eax*4 + 0x24]
004f644c test edx, edx
004f644e je 0x4f6474
004f6450 cmp dword ptr [edx + 4], 0xe
004f6454 jne 0x4f6474
004f6456 push eax
004f6457 lea eax, [esp + 0x10]
004f645b mov ecx, edi
004f645d push eax
004f645e call 0x7cebc0
004f6463 mov ecx, dword ptr [eax]
004f6465 mov dword ptr [esi + 0x28c], ecx
004f646b mov eax, dword ptr [eax + 4]
004f646e mov dword ptr [esi + 0x290], eax
004f6474 call 0x6c3d90
004f6479 xor edx, edx
004f647b mov ecx, 0x64
004f6480 div ecx
004f6482 test edx, edx
004f6484 jne 0x4f651a
004f648a push edx
004f648b push edx
004f648c push -1
004f648e push -1
004f6490 push 0x21
004f6492 lea eax, [esp + 0x60]
004f6496 push eax
004f6497 mov eax, dword ptr [0xbfd65c]
004f649c mov ecx, dword ptr [eax + 0x18190]
004f64a2 add ecx, 0x1218
004f64a8 call 0x415ed0
004f64ad mov ecx, dword ptr [esp + 0x58]
004f64b1 mov edi, dword ptr [esp + 0x50]
004f64b5 test ecx, ecx
004f64b7 je 0x4f64e3
004f64b9 call 0x659230
004f64be lea eax, [edi + eax*4]
004f64c1 mov eax, dword ptr [eax]
004f64c3 movss xmm0, dword ptr [eax + 0x294]
004f64cb movss xmm1, dword ptr [eax + 0x298]
004f64d3 movss dword ptr [esi + 0x28c], xmm0
004f64db movss dword ptr [esi + 0x290], xmm1
004f64e3 cmp byte ptr [esp + 0x4c], 0
004f64e8 jne 0x4f651a
004f64ea push edi
004f64eb call 0x9eace5
004f64f0 add esp, 4
004f64f3 jmp 0x4f651a
004f64f5 push ecx
004f64f6 lea eax, [esp + 0x60]
004f64fa mov dword ptr [esp], 0
004f6501 push eax
004f6502 mov ecx, esi
004f6504 call 0x695a30
004f6509 mov ecx, dword ptr [eax]
004f650b mov dword ptr [esi + 0x28c], ecx
004f6511 mov eax, dword ptr [eax + 4]
004f6514 mov dword ptr [esi + 0x290], eax
