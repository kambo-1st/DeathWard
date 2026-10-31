; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a4dc0 cmp dword ptr [ecx + 0xab4], 0xa
004a4dc7 lea edx, [ecx + 0x3c]
004a4dca mov eax, dword ptr [ecx + 0x32c]
004a4dd0 xorps xmm0, xmm0
004a4dd3 movss xmm3, dword ptr [eax + 0x2b8]
004a4ddb movss xmm4, dword ptr [eax + 0x2bc]
004a4de3 movaps xmm2, xmm3
004a4de6 andps xmm2, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a4ded movaps xmm1, xmm4
004a4df0 andps xmm1, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a4df7 jne 0x4a4e34
004a4df9 comiss xmm2, xmm1
004a4dfc jbe 0x4a4e19
004a4dfe comiss xmm0, xmm3
004a4e01 mov ecx, 0xb41bd8 ; string='ChargeRight'
004a4e06 mov eax, 0xb41bcc ; string='ChargeLeft'
004a4e0b push 0
004a4e0d cmovbe eax, ecx
004a4e10 mov ecx, edx
004a4e12 push eax
004a4e13 call 0x4054f0
004a4e18 ret 
004a4e19 comiss xmm0, xmm4
004a4e1c mov ecx, 0xb41c5c ; string='ChargeDown'
004a4e21 mov eax, 0xb41c68 ; string='ChargeUp'
004a4e26 push 0
004a4e28 cmovbe eax, ecx
004a4e2b mov ecx, edx
004a4e2d push eax
004a4e2e call 0x4054f0
004a4e33 ret 
004a4e34 comiss xmm2, xmm1
004a4e37 jbe 0x4a4e54
004a4e39 comiss xmm0, xmm3
004a4e3c mov ecx, 0xb41c74 ; string='IdleRight'
004a4e41 mov eax, 0xb41c80 ; string='IdleLeft'
004a4e46 push 0
004a4e48 cmovbe eax, ecx
004a4e4b mov ecx, edx
004a4e4d push eax
004a4e4e call 0x4054f0
004a4e53 ret 
004a4e54 comiss xmm0, xmm4
004a4e57 mov ecx, 0xb41c8c ; string='IdleDown'
004a4e5c mov eax, 0xb41c98 ; string='IdleUp'
004a4e61 push 0
004a4e63 cmovbe eax, ecx
004a4e66 mov ecx, edx
004a4e68 push eax
004a4e69 call 0x4054f0
004a4e6e ret 
