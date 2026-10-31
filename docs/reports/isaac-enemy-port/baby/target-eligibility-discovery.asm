006aeb40 push ebp
006aeb41 mov ebp, esp
006aeb43 sub esp, 8
006aeb46 mov eax, dword ptr [ecx + 0x164]
006aeb4c mov edx, dword ptr [ecx + 0x160]
006aeb52 mov dword ptr [ebp - 4], eax
006aeb55 mov eax, edx
006aeb57 and eax, 0x100
006aeb5c or eax, 0
006aeb5f je 0x6aeb74
006aeb61 and edx, 0x20000000
006aeb67 or edx, 0
006aeb6a jne 0x6aeb7f
006aeb6c mov al, 1
006aeb6e mov esp, ebp
006aeb70 pop ebp
006aeb71 ret 4
006aeb74 and edx, 0x20000000
006aeb7a or edx, 0
006aeb7d je 0x6aeb83
006aeb7f xor dl, dl
006aeb81 jmp 0x6aeb85
006aeb83 mov dl, 1
006aeb85 mov ecx, dword ptr [ebp + 8]
006aeb88 mov eax, dword ptr [ecx + 0x28]
006aeb8b cmp eax, 1
006aeb8e je 0x6aebc4
006aeb90 cmp eax, 4
006aeb93 je 0x6aebc4
006aeb95 cmp eax, 3
006aeb98 jne 0x6aebaa
006aeb9a mov eax, dword ptr [ecx + 0x160]
006aeba0 and eax, 0x100
006aeba5 or eax, 0
006aeba8 je 0x6aebc4
006aebaa mov eax, dword ptr [ecx + 0x160]
006aebb0 and eax, 0x20000000
006aebb5 or eax, 0
006aebb8 jne 0x6aebc4
006aebba mov al, 1
006aebbc xor al, dl
006aebbe mov esp, ebp
006aebc0 pop ebp
006aebc1 ret 4
006aebc4 xor al, al
006aebc6 xor al, dl
006aebc8 mov esp, ebp
006aebca pop ebp
006aebcb ret 4
006aebce int3 
006aebcf int3 
006aebd0 push ebp
006aebd1 mov ebp, esp
006aebd3 sub esp, 0x28
006aebd6 cmp byte ptr [ebp + 8], 0
006aebda push ebx
006aebdb push esi
006aebdc push edi
006aebdd movss dword ptr [ebp - 0xc], xmm2
006aebe2 mov esi, ecx
006aebe4 movss dword ptr [ebp - 4], xmm1
006aebe9 je 0x6aeef0
006aebef cmp dword ptr [esi + 0x314], 0
006aebf6 je 0x6aeef0
006aebfc call 0x4395d0
006aec01 xorps xmm3, xmm3
006aec04 movss dword ptr [ebp - 0x18], xmm3
006aec09 movss xmm0, dword ptr [eax + 0x294]
006aec11 movss xmm2, dword ptr [eax + 0x298]
006aec19 mov ebx, dword ptr [eax + 0xb60]
006aec1f mov edi, dword ptr [eax + 0xb54]
006aec25 mov eax, dword ptr [eax + 0xb64]
006aec2b add eax, ebx
006aec2d movss dword ptr [ebp + 8], xmm0
006aec32 movss dword ptr [ebp - 8], xmm2
006aec37 mov dword ptr [ebp - 0x1c], eax
006aec3a nop word ptr [eax + eax]
006aec40 cmp ebx, eax
006aec42 je 0x6aeef0
006aec48 test edi, edi
006aec4a je 0x6aec50
006aec4c mov eax, dword ptr [edi]
006aec4e jmp 0x6aec52
006aec50 xor eax, eax
006aec52 mov ecx, ebx
006aec54 mov edx, ebx
006aec56 shr ecx, 1
006aec58 and edx, 1
006aec5b mov dword ptr [ebp - 0x14], ecx
006aec5e mov ecx, dword ptr [eax + 8]
006aec61 mov eax, dword ptr [eax + 4]
006aec64 dec ecx
006aec65 and ecx, dword ptr [ebp - 0x14]
006aec68 shl edx, 3
006aec6b mov dword ptr [ebp - 0x24], edx
006aec6e mov eax, dword ptr [eax + ecx*4]
006aec71 movss xmm1, dword ptr [eax + edx]
006aec76 subss xmm1, xmm0
006aec7a movss xmm0, dword ptr [eax + edx + 4]
006aec80 subss xmm0, xmm2
006aec84 movss dword ptr [ebp - 0x10], xmm1
006aec89 movaps xmm2, xmm0
006aec8c movss dword ptr [ebp - 0x20], xmm0
006aec91 mulss xmm2, xmm0
006aec95 movaps xmm0, xmm1
006aec98 mulss xmm0, xmm1
006aec9c addss xmm2, xmm0
006aeca0 movaps xmm0, xmm2
006aeca3 movss dword ptr [ebp - 0x28], xmm2
006aeca8 call 0x4228c0
006aecad addss xmm0, dword ptr [ebp - 0x18]
006aecb2 comiss xmm0, dword ptr [ebp - 4]
006aecb6 ja 0x6aedde
006aecbc movss dword ptr [ebp - 0x18], xmm0
006aecc1 test edi, edi
006aecc3 je 0x6aecc9
006aecc5 mov eax, dword ptr [edi]
006aecc7 jmp 0x6aeccb
006aecc9 xor eax, eax
006aeccb mov ecx, dword ptr [eax + 8]
006aecce inc ebx
006aeccf mov eax, dword ptr [eax + 4]
006aecd2 dec ecx
006aecd3 and ecx, dword ptr [ebp - 0x14]
006aecd6 mov eax, dword ptr [eax + ecx*4]
006aecd9 add eax, dword ptr [ebp - 0x24]
006aecdc movss xmm0, dword ptr [eax]
006aece0 movss xmm2, dword ptr [eax + 4]
006aece5 mov eax, dword ptr [ebp - 0x1c]
006aece8 movss dword ptr [ebp + 8], xmm0
006aeced movss dword ptr [ebp - 8], xmm2
006aecf2 cmp ebx, eax
006aecf4 jne 0x6aec48
006aecfa movaps xmm1, xmm0
006aecfd movaps xmm0, xmm2
006aed00 subss xmm0, dword ptr [esi + 0x298]
006aed08 subss xmm1, dword ptr [esi + 0x294]
006aed10 movaps xmm2, xmm0
006aed13 movss dword ptr [ebp - 0x14], xmm0
006aed18 mulss xmm2, xmm0
006aed1c movaps xmm0, xmm1
006aed1f mulss xmm0, xmm1
006aed23 movss dword ptr [ebp - 0x10], xmm1
006aed28 addss xmm2, xmm0
006aed2c movaps xmm0, xmm2
006aed2f movss dword ptr [ebp - 0x24], xmm2
006aed34 call 0x4228c0
006aed39 comiss xmm0, dword ptr [ebp - 4]
006aed3d mov eax, dword ptr [ebp - 0x1c]
006aed40 movss xmm0, dword ptr [ebp + 8]
006aed45 movss xmm2, dword ptr [ebp - 8]
006aed4a jbe 0x6aec40
006aed50 movss xmm0, dword ptr [ebp - 0xc]
006aed55 comiss xmm0, dword ptr [0xb6a18c]
006aed5c jbe 0x6aedbf
006aed5e movss xmm0, dword ptr [ebp - 0x24]
006aed63 call 0x4228c0
006aed68 movss xmm2, dword ptr [ebp - 0x14]
006aed6d movaps xmm1, xmm0
006aed70 movss xmm0, dword ptr [ebp - 0xc]
006aed75 comiss xmm1, xmm0
006aed78 jbe 0x6aed95
006aed7a xorps xmm3, xmm3
006aed7d comiss xmm1, xmm3
006aed80 jbe 0x6aed95
006aed82 divss xmm0, xmm1
006aed86 movss xmm1, dword ptr [ebp - 0x10]
006aed8b mulss xmm1, xmm0
006aed8f mulss xmm2, xmm0
006aed93 jmp 0x6aed9a
006aed95 movss xmm1, dword ptr [ebp - 0x10]
006aed9a movss xmm0, dword ptr [esi + 0x2c4]
006aeda2 divss xmm1, xmm0
006aeda6 divss xmm2, xmm0
006aedaa movss dword ptr [esi + 0x2b8], xmm1
006aedb2 movss dword ptr [esi + 0x2bc], xmm2
006aedba jmp 0x6aeef0
006aedbf movss xmm3, dword ptr [ebp + 8]
006aedc4 movss xmm0, dword ptr [ebp - 8]
006aedc9 movss dword ptr [esi + 0x294], xmm3
006aedd1 movss dword ptr [esi + 0x298], xmm0
006aedd9 jmp 0x6aeed0
006aedde movss xmm0, dword ptr [ebp - 0x28]
006aede3 call 0x4228c0
006aede8 movss xmm3, dword ptr [ebp - 0x10]
006aeded xorps xmm4, xmm4
006aedf0 comiss xmm0, xmm4
006aedf3 jbe 0x6aee13
006aedf5 movss xmm1, dword ptr [0xb6a614]
006aedfd divss xmm1, xmm0
006aee01 movaps xmm0, xmm1
006aee04 mulss xmm3, xmm0
006aee08 movss xmm0, dword ptr [ebp - 0x20]
006aee0d mulss xmm0, xmm1
006aee11 jmp 0x6aee18
006aee13 movss xmm0, dword ptr [ebp - 0x20]
006aee18 movss xmm1, dword ptr [ebp - 4]
006aee1d subss xmm1, dword ptr [ebp - 0x18]
006aee22 movaps xmm2, xmm1
006aee25 mulss xmm1, xmm0
006aee29 movss xmm0, dword ptr [ebp - 0xc]
