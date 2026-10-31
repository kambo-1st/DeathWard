004f5b1e cmp dword ptr [esi + 0x28], 0xe
004f5b22 jne 0x4f5dc5
004f5b28 cmp byte ptr [esp + 0xb], 0
004f5b2d jne 0x4f5dc5
004f5b33 cmp dword ptr [esi + 0xaf0], 0
004f5b3a jg 0x4f5bd0
004f5b40 movss xmm1, dword ptr [0xb6aba8]
004f5b48 mov ecx, esi
004f5b4a push 7
004f5b4c push 0
004f5b4e call 0x6a15a0
004f5b53 test al, al
004f5b55 je 0x4f5bd0
004f5b57 cmp dword ptr [esi + 0x2c], 2
004f5b5b mov ecx, 0x3f
004f5b60 mov eax, 0x23
004f5b65 cmove eax, ecx
004f5b68 lea ecx, [esi + 0x3c]
004f5b6b push 0
004f5b6d push 0xb40510
004f5b72 mov dword ptr [esi + 0xaf0], eax
004f5b78 call 0x4054f0
004f5b7d push 1
004f5b7f mov ecx, esi
004f5b81 mov dword ptr [esi + 0xab4], 8
004f5b8b call 0x6afe20
004f5b90 lea ecx, [esi + 0xe70]
004f5b96 push 0xc02fec
004f5b9b call 0x962c70
004f5ba0 test al, al
004f5ba2 je 0x4f5bbd
004f5ba4 mov ecx, esi
004f5ba6 call 0x695680
004f5bab movss xmm0, dword ptr [eax + 0x294]
004f5bb3 subss xmm0, dword ptr [esi + 0x294]
004f5bbb jmp 0x4f5bc1
004f5bbd movss xmm0, dword ptr [ecx]
004f5bc1 xorps xmm1, xmm1
004f5bc4 comiss xmm1, xmm0
004f5bc7 seta al
004f5bca mov byte ptr [esi + 0x13c], al
004f5bd0 cmp dword ptr [esi + 0xab4], 8
004f5bd7 jne 0x4f5d59
004f5bdd push 0
004f5bdf mov ecx, esi
004f5be1 call 0x6afe20
004f5be6 push 0xb400ac
004f5beb lea ecx, [esi + 0x3c]
004f5bee call 0x4060f0
004f5bf3 test al, al
004f5bf5 je 0x4f5d59
004f5bfb lea ecx, [esi + 0xe70]
004f5c01 push 0xc02fec
004f5c06 lea edi, [esi + 0x294]
004f5c0c call 0x962c70
004f5c11 test al, al
004f5c13 je 0x4f5c43
004f5c15 mov ecx, esi
004f5c17 call 0x695680
004f5c1c movss xmm0, dword ptr [eax + 0x294]
004f5c24 movss xmm1, dword ptr [eax + 0x298]
004f5c2c subss xmm0, dword ptr [edi]
004f5c30 subss xmm1, dword ptr [edi + 4]
004f5c35 movss dword ptr [esp + 0xc], xmm0
004f5c3b movss dword ptr [esp + 0x10], xmm1
004f5c41 jmp 0x4f5c50
004f5c43 mov eax, dword ptr [ecx]
004f5c45 mov ecx, dword ptr [ecx + 4]
004f5c48 mov dword ptr [esp + 0xc], eax
004f5c4c mov dword ptr [esp + 0x10], ecx
004f5c50 lea ecx, [esp + 0xc]
004f5c54 mov eax, dword ptr [ecx]
004f5c56 mov ecx, dword ptr [ecx + 4]
004f5c59 mov dword ptr [esp + 0x38], ecx
004f5c5d mov ecx, dword ptr [esi + 0x2c]
004f5c60 mov dword ptr [esp + 0x34], eax
004f5c64 cmp ecx, 2
004f5c67 jne 0x4f5cdc
004f5c69 lea ecx, [esp + 0x138]
004f5c70 call 0x430d70
004f5c75 push ecx
004f5c76 lea ecx, [esp + 0x38]
004f5c7a mov dword ptr [esp + 0x150], 0x3fb33333
004f5c85 mov dword ptr [esp + 0x148], 0xbe19999a
004f5c90 mov dword ptr [esp + 0x144], 0x3f800000
004f5c9b mov dword ptr [esp + 0x164], 0x3f99999a
004f5ca6 mov dword ptr [esp + 0x194], 0
004f5cb1 mov dword ptr [esp + 0x198], 0x400000
004f5cbc mov byte ptr [esp + 0x1d4], 1
004f5cc4 mov dword ptr [esp], 0x40e00000
004f5ccb call 0x962860
004f5cd0 lea eax, [esp + 0x138]
004f5cd7 push eax
004f5cd8 push 4
004f5cda jmp 0x4f5d2c
004f5cdc call 0x6af030
004f5ce1 test eax, eax
004f5ce3 jle 0x4f5cfe
004f5ce5 cmp ecx, 1
004f5ce8 jne 0x4f5cf4
004f5cea movss xmm0, dword ptr [0xb6a940]
004f5cf2 jmp 0x4f5d06
004f5cf4 movss xmm0, dword ptr [0xb6a974]
004f5cfc jmp 0x4f5d06
004f5cfe movss xmm0, dword ptr [0xb6a928]
004f5d06 push ecx
004f5d07 lea ecx, [esp + 0x38]
004f5d0b movss dword ptr [esp], xmm0
004f5d10 call 0x962860
004f5d15 lea ecx, [esp + 0x138]
004f5d1c call 0x430d70
004f5d21 push eax
004f5d22 xor eax, eax
004f5d24 cmp dword ptr [esi + 0x2c], 1
004f5d28 sete al
004f5d2b push eax
004f5d2c lea eax, [esp + 0x3c]
004f5d30 mov ecx, esi
004f5d32 push eax
004f5d33 push edi
004f5d34 call 0x6a1a20
004f5d39 push ecx
004f5d3a mov dword ptr [esp], 0x3f800000
004f5d41 push 0
004f5d43 push 2
004f5d45 push ecx
004f5d46 mov dword ptr [esp], 0x3f800000
004f5d4d mov ecx, esi
004f5d4f push 0xb2
004f5d54 call 0x6ad720
004f5d59 mov edx, dword ptr [esi + 0xaf0]
004f5d5f test edx, edx
004f5d61 jle 0x4f5dc5
004f5d63 movss xmm0, dword ptr [esi + 0x2c4]
004f5d6b mulss xmm0, dword ptr [0xb6a560]
004f5d73 cvttss2si eax, dword ptr [esi + 0x2fc]
004f5d7b cvttss2si ecx, dword ptr [esi + 0x2f8]
004f5d83 movss dword ptr [esi + 0x2c4], xmm0
004f5d8b movss xmm0, dword ptr [esi + 0xb00]
004f5d93 sub ecx, eax
004f5d95 mulss xmm0, dword ptr [0xb6a50c]
004f5d9d add ecx, edx
004f5d9f mov dword ptr [esi + 0xaf0], ecx
004f5da5 movss dword ptr [esi + 0xb00], xmm0
004f5dad movss xmm0, dword ptr [esi + 0xb04]
004f5db5 mulss xmm0, dword ptr [0xb6a50c]
004f5dbd movss dword ptr [esi + 0xb04], xmm0
