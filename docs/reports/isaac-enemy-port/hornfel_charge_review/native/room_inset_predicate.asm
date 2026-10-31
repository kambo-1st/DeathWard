; Repentance 1.7.9b bounded evidence. Interpretive names are not exported symbols.
007cf0a0 push ebp
007cf0a1 mov ebp, esp
007cf0a3 and esp, 0xfffffff8
007cf0a6 mov eax, dword ptr [ecx + 4]
007cf0a9 sub esp, 0xc
007cf0ac mov eax, dword ptr [eax + 0x10]
007cf0af push esi
007cf0b0 mov eax, dword ptr [eax + 0x48]
007cf0b3 add eax, -9
007cf0b6 cmp eax, 3
007cf0b9 ja 0x7cf10a
007cf0bb movss xmm3, dword ptr [ebp + 0xc]
007cf0c0 lea eax, [esp + 8]
007cf0c4 mov esi, dword ptr [ebp + 8]
007cf0c7 sub esp, 0xc
007cf0ca movss dword ptr [esp + 8], xmm3
007cf0d0 movss dword ptr [esp + 4], xmm3
007cf0d6 movss dword ptr [esp], xmm3
007cf0db push esi
007cf0dc push eax
007cf0dd call 0x7cec10
007cf0e2 movss xmm0, dword ptr [esp + 8]
007cf0e8 ucomiss xmm0, dword ptr [esi]
007cf0eb lahf 
007cf0ec test ah, 0x44
007cf0ef jp 0x7cf101
007cf0f1 movss xmm0, dword ptr [esp + 0xc]
007cf0f7 ucomiss xmm0, dword ptr [esi + 4]
007cf0fb lahf 
007cf0fc test ah, 0x44
007cf0ff jnp 0x7cf151
007cf101 xor al, al
007cf103 pop esi
007cf104 mov esp, ebp
007cf106 pop ebp
007cf107 ret 8
007cf10a movss xmm1, dword ptr [ebp + 0xc]
007cf10f mov eax, dword ptr [ebp + 8]
007cf112 movaps xmm0, xmm1
007cf115 addss xmm0, dword ptr [ecx + 0x14]
007cf11a movss xmm2, dword ptr [eax]
007cf11e comiss xmm2, xmm0
007cf121 jb 0x7cf101
007cf123 movss xmm0, dword ptr [ecx + 0x1c]
007cf128 subss xmm0, xmm1
007cf12c comiss xmm0, xmm2
007cf12f jb 0x7cf101
007cf131 movss xmm2, dword ptr [eax + 4]
007cf136 movaps xmm0, xmm1
007cf139 addss xmm0, dword ptr [ecx + 0x18]
007cf13e comiss xmm2, xmm0
007cf141 jb 0x7cf101
007cf143 movss xmm0, dword ptr [ecx + 0x20]
007cf148 subss xmm0, xmm1
007cf14c comiss xmm0, xmm2
007cf14f jb 0x7cf101
007cf151 mov al, 1
007cf153 pop esi
007cf154 mov esp, ebp
007cf156 pop ebp
