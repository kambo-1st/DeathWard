007cec10 push ebp
007cec11 mov ebp, esp
007cec13 and esp, 0xfffffff8
007cec16 sub esp, 0x44
007cec19 push esi
007cec1a mov esi, ecx
007cec1c movss dword ptr [esp + 8], xmm3
007cec22 mov eax, dword ptr [esi + 4]
007cec25 test eax, eax
007cec27 je 0x7ceefc
007cec2d mov eax, dword ptr [eax + 0x10]
007cec30 test eax, eax
007cec32 je 0x7ceefc
007cec38 mov eax, dword ptr [eax + 0x48]
007cec3b add eax, -9
007cec3e cmp eax, 3
007cec41 ja 0x7cee79
007cec47 mov eax, dword ptr [ebp + 0xc]
007cec4a movss xmm0, dword ptr [eax]
007cec4e movss dword ptr [esp + 0xc], xmm0
007cec54 movss dword ptr [esp + 0x20], xmm0
007cec5a movss xmm0, dword ptr [eax + 4]
007cec5f lea eax, [esp + 0x28]
007cec63 push eax
007cec64 movss dword ptr [esp + 0x18], xmm0
007cec6a movss dword ptr [esp + 0x28], xmm0
007cec70 call 0x7da8e0
007cec75 movss xmm1, dword ptr [0xb6c9b0]
007cec7d movss xmm2, dword ptr [ebp + 0x18]
007cec82 movss xmm5, dword ptr [ebp + 0x14]
007cec87 xorps xmm2, xmm1
007cec8a movss xmm4, dword ptr [esp + 8]
007cec90 xorps xmm5, xmm1
007cec93 addss xmm2, dword ptr [esp + 0x34]
007cec99 movss xmm6, dword ptr [esp + 0x28]
007cec9f movaps xmm0, xmm4
007ceca2 movss xmm3, dword ptr [esp + 0x38]
007ceca8 xorps xmm0, xmm1
007cecab subss xmm6, xmm0
007cecaf movaps xmm7, xmm5
007cecb2 addss xmm7, dword ptr [esp + 0x30]
007cecb8 addss xmm5, dword ptr [esp + 0x40]
007cecbe subss xmm3, xmm0
007cecc2 movss dword ptr [esp + 8], xmm2
007cecc8 movss xmm0, dword ptr [ebp + 0x10]
007ceccd movss xmm2, dword ptr [esp + 0x3c]
007cecd3 xorps xmm0, xmm1
007cecd6 subss xmm2, xmm0
007cecda movaps xmm1, xmm7
007cecdd movaps xmm0, xmm5
007cece0 subss xmm1, xmm6
007cece4 subss xmm0, xmm3
007cece8 movss dword ptr [esp + 0x1c], xmm3
007cecee comiss xmm0, xmm1
007cecf1 ja 0x7cecf9
007cecf3 movss xmm2, dword ptr [esp + 8]
007cecf9 movss xmm0, dword ptr [ebp + 0x10]
007cecfe lea edx, [esp + 8]
007ced02 addss xmm0, dword ptr [esi + 0x18]
007ced07 mov eax, dword ptr [esi + 4]
007ced0a movss xmm1, dword ptr [esi + 0x20]
007ced0f addss xmm4, dword ptr [esi + 0x14]
007ced14 subss xmm1, dword ptr [ebp + 0x18]
007ced19 mov eax, dword ptr [eax + 0x10]
007ced1c movss dword ptr [esp + 0x18], xmm0
007ced22 movss xmm0, dword ptr [esi + 0x1c]
007ced27 subss xmm0, dword ptr [ebp + 0x14]
007ced2c mov ecx, dword ptr [eax + 0x48]
007ced2f lea eax, [esp + 0x20]
007ced33 movss dword ptr [esp + 0x10], xmm1
007ced39 comiss xmm0, dword ptr [esp + 0xc]
007ced3e movss dword ptr [esp + 8], xmm0
007ced44 cmovbe eax, edx
007ced47 movss xmm0, dword ptr [eax]
007ced4b comiss xmm0, xmm4
007ced4e ja 0x7ced56
007ced50 movss xmm3, xmm4
007ced54 jmp 0x7ced5a
007ced56 movss xmm3, xmm0
007ced5a lea eax, [esp + 0x24]
007ced5e lea edx, [esp + 0x10]
007ced62 comiss xmm1, dword ptr [esp + 0x14]
007ced67 movss xmm1, dword ptr [esp + 0x18]
007ced6d movss dword ptr [esp + 0x20], xmm3
007ced73 cmovbe eax, edx
007ced76 movss xmm0, dword ptr [eax]
007ced7a comiss xmm0, xmm1
007ced7d ja 0x7ced85
007ced7f movss xmm4, xmm1
007ced83 jmp 0x7ced89
007ced85 movss xmm4, xmm0
007ced89 cmp ecx, 9
007ced8c jne 0x7cedcd
007ced8e comiss xmm6, xmm3
007ced91 jbe 0x7cee66
007ced97 comiss xmm2, xmm4
007ced9a jbe 0x7cee66
007ceda0 movaps xmm1, xmm6
007ceda3 movaps xmm0, xmm2
007ceda6 subss xmm1, xmm3
007cedaa subss xmm0, xmm4
007cedae comiss xmm0, xmm1
007cedb1 jbe 0x7cee63
007cedb7 mov eax, dword ptr [ebp + 8]
007cedba movaps xmm3, xmm6
007cedbd movss dword ptr [eax], xmm3
007cedc1 movss dword ptr [eax + 4], xmm4
007cedc6 pop esi
007cedc7 mov esp, ebp
007cedc9 pop ebp
007cedca ret 0x14
007cedcd cmp ecx, 0xa
007cedd0 jne 0x7cee0d
007cedd2 comiss xmm3, xmm7
007cedd5 jbe 0x7cee66
007ceddb comiss xmm2, xmm4
007cedde jbe 0x7cee66
007cede4 movaps xmm1, xmm3
007cede7 movaps xmm0, xmm2
007cedea subss xmm1, xmm7
007cedee subss xmm0, xmm4
007cedf2 comiss xmm0, xmm1
007cedf5 jbe 0x7cee63
007cedf7 mov eax, dword ptr [ebp + 8]
007cedfa movaps xmm3, xmm7
007cedfd movss dword ptr [eax], xmm3
007cee01 movss dword ptr [eax + 4], xmm4
007cee06 pop esi
007cee07 mov esp, ebp
007cee09 pop ebp
007cee0a ret 0x14
007cee0d cmp ecx, 0xb
007cee10 jne 0x7cee2b
007cee12 movss xmm5, dword ptr [esp + 0x1c]
007cee18 comiss xmm5, xmm3
007cee1b jbe 0x7cee66
007cee1d comiss xmm4, xmm2
007cee20 jbe 0x7cee66
007cee22 movaps xmm1, xmm5
007cee25 subss xmm1, xmm3
007cee29 jmp 0x7cee41
007cee2b cmp ecx, 0xc
007cee2e jne 0x7cee66
007cee30 comiss xmm3, xmm5
007cee33 jbe 0x7cee66
007cee35 comiss xmm4, xmm2
007cee38 jbe 0x7cee66
007cee3a movaps xmm1, xmm3
007cee3d subss xmm1, xmm5
007cee41 movaps xmm0, xmm4
007cee44 subss xmm0, xmm2
007cee48 comiss xmm0, xmm1
007cee4b jbe 0x7cee63
007cee4d mov eax, dword ptr [ebp + 8]
007cee50 movaps xmm3, xmm5
007cee53 movss dword ptr [eax], xmm3
007cee57 movss dword ptr [eax + 4], xmm4
007cee5c pop esi
007cee5d mov esp, ebp
007cee5f pop ebp
007cee60 ret 0x14
007cee63 movaps xmm4, xmm2
007cee66 mov eax, dword ptr [ebp + 8]
007cee69 movss dword ptr [eax], xmm3
007cee6d movss dword ptr [eax + 4], xmm4
007cee72 pop esi
007cee73 mov esp, ebp
007cee75 pop ebp
007cee76 ret 0x14
007cee79 movss xmm0, dword ptr [esi + 0x20]
007cee7e lea edx, [esp + 0x1c]
007cee82 mov ecx, dword ptr [ebp + 0xc]
007cee85 subss xmm0, dword ptr [ebp + 0x18]
007cee8a movss xmm1, dword ptr [esi + 0x1c]
007cee8f lea eax, [ecx + 4]
007cee92 subss xmm1, dword ptr [ebp + 0x14]
007cee97 movss xmm2, dword ptr [ebp + 0x10]
007cee9c addss xmm3, dword ptr [esi + 0x14]
007ceea1 comiss xmm0, dword ptr [eax]
007ceea4 addss xmm2, dword ptr [esi + 0x18]
007ceea9 movss dword ptr [esp + 0x18], xmm1
007ceeaf cmova edx, eax
007ceeb2 movss dword ptr [esp + 0x1c], xmm0
007ceeb8 comiss xmm1, dword ptr [ecx]
007ceebb lea eax, [esp + 0x18]
007ceebf movss dword ptr [esp + 0x14], xmm2
007ceec5 cmova eax, ecx
007ceec8 movss xmm0, dword ptr [eax]
007ceecc comiss xmm0, xmm3
007ceecf ja 0x7ceed7
007ceed1 movss xmm0, xmm3
007ceed5 jmp 0x7ceedb
007ceed7 movss xmm0, xmm0
007ceedb mov eax, dword ptr [ebp + 8]
007ceede lea ecx, [esp + 0x14]
007ceee2 movss dword ptr [eax], xmm0
007ceee6 movss xmm0, dword ptr [edx]
007ceeea comiss xmm0, xmm2
007ceeed cmova ecx, edx
007ceef0 mov ecx, dword ptr [ecx]
007ceef2 mov dword ptr [eax + 4], ecx
007ceef5 pop esi
007ceef6 mov esp, ebp
007ceef8 pop ebp
007ceef9 ret 0x14
007ceefc mov eax, dword ptr [ebp + 0xc]
007ceeff pop esi
007cef00 mov ecx, dword ptr [eax]
007cef02 mov edx, dword ptr [eax + 4]
007cef05 mov eax, dword ptr [ebp + 8]
007cef08 mov dword ptr [eax], ecx
007cef0a mov dword ptr [eax + 4], edx
007cef0d mov esp, ebp
007cef0f pop ebp
007cef10 ret 0x14
