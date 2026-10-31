00549d70 push ebp
00549d71 mov ebp, esp
00549d73 and esp, 0xfffffff8
00549d76 sub esp, 0xc
00549d79 push ebx
00549d7a mov ebx, dword ptr [0xbfd65c]
00549d80 push esi
00549d81 push edi
00549d82 movss dword ptr [esp + 0x14], xmm2
00549d88 mov esi, edx
00549d8a mov eax, dword ptr [ebx + 0x18190]
00549d90 mov edi, ecx
00549d92 mov dword ptr [esp + 0x10], eax
00549d96 call 0x6c3d90
00549d9b push 0
00549d9d push eax
00549d9e movzx eax, byte ptr [ebp + 0xc]
00549da2 mov ecx, ebx
00549da4 push eax
00549da5 push esi
00549da6 push 0xc02fec
00549dab push edi
00549dac push 0
00549dae push 0x32a
00549db3 call 0x6d0ca0
00549db8 movss xmm1, dword ptr [0xb6aa3c]
00549dc0 mov esi, eax
00549dc2 mov ecx, dword ptr [esi + 0x164]
00549dc8 and dword ptr [esi + 0x160], 0xfffffffb
00549dcf mov dword ptr [esi + 0x164], ecx
00549dd5 mov ecx, dword ptr [ebp + 8]
00549dd8 movss xmm2, dword ptr [ecx]
00549ddc movss dword ptr [esi + 0x28c], xmm2
00549de4 subss xmm2, xmm1
00549de8 movss xmm3, dword ptr [ecx + 4]
00549ded movss dword ptr [esi + 0x290], xmm3
00549df5 subss xmm3, dword ptr [0xb6ab20]
00549dfd divss xmm2, xmm1
00549e01 divss xmm3, xmm1
00549e05 addss xmm2, dword ptr [0xb6a480]
00549e0d addss xmm3, dword ptr [0xb6a480]
00549e15 cvttss2si edx, xmm2
00549e19 cvttss2si eax, xmm3
00549e1d test edx, edx
00549e1f js 0x549e71
00549e21 mov ebx, dword ptr [esp + 0x10]
00549e25 mov ecx, dword ptr [ebx + 0xc]
00549e28 cmp edx, ecx
00549e2a jge 0x549e71
00549e2c test eax, eax
00549e2e js 0x549e71
00549e30 cmp eax, dword ptr [ebx + 0x10]
00549e33 jge 0x549e71
00549e35 imul ecx, eax
00549e38 add ecx, edx
00549e3a js 0x549e71
00549e3c cmp ecx, 0x1c0
00549e42 jge 0x549e71
00549e44 mov edi, dword ptr [ebx + ecx*4 + 0x76c]
00549e4b mov eax, edi
00549e4d cdq 
00549e4e mov dword ptr [esp + 0x10], 0x3e8
00549e56 idiv dword ptr [esp + 0x10]
00549e5a cmp edx, 0x384
00549e60 jge 0x549e71
00549e62 sub edi, edx
00549e64 add edi, 0x384
00549e6a mov dword ptr [ebx + ecx*4 + 0x76c], edi
00549e71 cmp byte ptr [ebp + 0xc], 0
00549e75 mov eax, esi
00549e77 movss xmm0, dword ptr [esp + 0x14]
00549e7d mov dword ptr [esi + 0xb00], 0xc1000000
00549e87 mov dword ptr [esi + 0xb04], 0
00549e91 movss xmm2, dword ptr [esi + 0x28c]
00549e99 movss xmm1, dword ptr [esi + 0x290]
00549ea1 subss xmm2, dword ptr [esi + 0x294]
00549ea9 subss xmm1, dword ptr [esi + 0x298]
00549eb1 mov dword ptr [esi + 0xab4], 6
00549ebb movss dword ptr [esi + 0x2a8], xmm0
00549ec3 mulss xmm2, dword ptr [0xb6a264]
00549ecb mulss xmm1, dword ptr [0xb6a264]
00549ed3 movss dword ptr [esi + 0xb08], xmm2
00549edb movss dword ptr [esi + 0x2b8], xmm2
00549ee3 movss dword ptr [esi + 0xb0c], xmm1
00549eeb movss dword ptr [esi + 0x2bc], xmm1
00549ef3 je 0x549f41
00549ef5 movss xmm2, dword ptr [0xbc7a28]
00549efd movss xmm1, dword ptr [0xbc7a2c]
00549f05 movss xmm0, dword ptr [esi + 0x2dc]
00549f0d mulss xmm2, dword ptr [0xb6a680]
00549f15 addss xmm0, xmm0
00549f19 mulss xmm1, dword ptr [0xb6a680]
00549f21 movss dword ptr [esi + 0xd8], xmm2
00549f29 movss dword ptr [esi + 0x2dc], xmm0
00549f31 movss dword ptr [esi + 0xdc], xmm1
00549f39 movss dword ptr [esi + 0x2d8], xmm0
00549f41 pop edi
00549f42 pop esi
00549f43 pop ebx
00549f44 mov esp, ebp
00549f46 pop ebp
00549f47 ret 
