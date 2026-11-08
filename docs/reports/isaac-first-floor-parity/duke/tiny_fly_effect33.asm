005d8968 mov edx, dword ptr [ebp - 0xeb8]
005d896e add edx, 0x294
005d8974 push edx
005d8975 mov ecx, dword ptr [0xbfd65c]
005d897b call 0x6d5e30
005d8980 mov dword ptr [ebp - 0x1eec], eax
005d8986 mov eax, dword ptr [ebp - 0xeb8]
005d898c add eax, 0x294
005d8991 push eax
005d8992 lea ecx, [ebp - 0x2450]
005d8998 push ecx
005d8999 lea edx, [ebp - 0x3554]
005d899f push edx
005d89a0 mov ecx, dword ptr [ebp - 0x1eec]
005d89a6 call 0x412130
005d89ab mov ecx, eax
005d89ad call 0x962ac0
005d89b2 lea ecx, [ebp - 0x2450]
005d89b8 call 0x962a00
005d89bd fstp dword ptr [ebp - 0x11c8]
005d89c3 lea ecx, [ebp - 0x1970]
005d89c9 call 0x9624d0
005d89ce movss xmm0, dword ptr [ebp - 0x11c8]
005d89d6 ucomiss xmm0, dword ptr [0xb6a18c]
005d89dd lahf 
005d89de test ah, 0x44
005d89e1 jnp 0x5d8a0a
005d89e3 lea eax, [ebp - 0x11c8]
005d89e9 push eax
005d89ea lea ecx, [ebp - 0x355c]
005d89f0 push ecx
005d89f1 lea ecx, [ebp - 0x2450]
005d89f7 call 0x962c10
005d89fc push eax
005d89fd lea ecx, [ebp - 0x1970]
005d8a03 call 0x962cd0
005d8a08 jmp 0x5d8a3f
005d8a0a movss xmm0, dword ptr [0xb6a214]
005d8a12 movss dword ptr [ebp - 0x1ef0], xmm0
005d8a1a lea edx, [ebp - 0x1ef0]
005d8a20 push edx
005d8a21 lea eax, [ebp - 0x3564]
005d8a27 push eax
005d8a28 lea ecx, [ebp - 0x2450]
005d8a2e call 0x962c10
005d8a33 push eax
005d8a34 lea ecx, [ebp - 0x1970]
005d8a3a call 0x962cd0
005d8a3f mov ecx, dword ptr [ebp - 0xeb8]
005d8a45 movss xmm0, dword ptr [ecx + 0x2c4]
005d8a4d mulss xmm0, dword ptr [0xb6a604]
005d8a55 mov edx, dword ptr [ebp - 0xeb8]
005d8a5b movss dword ptr [edx + 0x2c4], xmm0
005d8a63 mov eax, dword ptr [ebp - 0xeb8]
005d8a69 movzx ecx, byte ptr [eax + 0x16b]
005d8a70 test ecx, ecx
005d8a72 je 0x5d8ca7
005d8a78 push 0
005d8a7a mov ecx, dword ptr [ebp - 0xeb8]
005d8a80 add ecx, 0x3c
005d8a83 call 0x4062c0
005d8a88 movss xmm0, dword ptr [eax + 0x44]
005d8a8d comiss xmm0, dword ptr [0xb6a9b0]
005d8a94 jbe 0x5d8b4a
005d8a9a call 0x659280
005d8a9f push eax
005d8aa0 push 0
005d8aa2 push 0
005d8aa4 push 0xc02fec
005d8aa9 mov edx, dword ptr [ebp - 0xeb8]
005d8aaf add edx, 0x294
005d8ab5 push edx
005d8ab6 push 7
005d8ab8 push 0x3e8
005d8abd mov ecx, dword ptr [0xbfd65c]
005d8ac3 call 0x422e20
005d8ac8 mov dword ptr [ebp - 0x11cc], eax
005d8ace push 1
005d8ad0 push 0
005d8ad2 push 0xff
005d8ad7 push -1
005d8ad9 mov eax, dword ptr [ebp - 0xeb8]
005d8adf add eax, 0x1dc
005d8ae4 push eax
005d8ae5 mov ecx, dword ptr [ebp - 0x11cc]
005d8aeb mov edx, dword ptr [ecx]
005d8aed mov ecx, dword ptr [ebp - 0x11cc]
005d8af3 mov eax, dword ptr [edx + 0x38]
005d8af6 call eax
005d8af8 movss xmm2, dword ptr [0xb6a2cc]
005d8b00 movss xmm1, dword ptr [0xb6a2cc]
005d8b08 lea ecx, [ebp - 0x356c]
005d8b0e call 0x9624e0
005d8b13 push eax
005d8b14 mov ecx, dword ptr [ebp - 0x11cc]
005d8b1a call 0x427330
005d8b1f mov ecx, dword ptr [ebp - 0x11cc]
005d8b25 mov edx, dword ptr [ecx]
005d8b27 mov ecx, dword ptr [ebp - 0x11cc]
005d8b2d mov eax, dword ptr [edx + 0xc]
005d8b30 call eax
005d8b32 mov ecx, dword ptr [ebp - 0xeb8]
005d8b38 mov edx, dword ptr [ecx]
005d8b3a mov ecx, dword ptr [ebp - 0xeb8]
005d8b40 mov eax, dword ptr [edx + 0x28]
005d8b43 call eax
005d8b45 jmp 0x5d8ca7
005d8b4a push 0
005d8b4c mov ecx, dword ptr [ebp - 0xeb8]
005d8b52 add ecx, 0x3c
005d8b55 call 0x4062c0
005d8b5a add eax, 0x44
005d8b5d mov dword ptr [ebp - 0x1698], eax
005d8b63 mov ecx, dword ptr [ebp - 0x1698]
005d8b69 movss xmm0, dword ptr [ecx]
005d8b6d addss xmm0, dword ptr [0xb6a38c]
005d8b75 mov edx, dword ptr [ebp - 0x1698]
005d8b7b movss dword ptr [edx], xmm0
005d8b7f mov eax, dword ptr [ebp - 0xeb8]
005d8b85 mov eax, dword ptr [eax + 0x20]
005d8b88 xor edx, edx
005d8b8a mov ecx, 2
005d8b8f div ecx
005d8b91 mov dword ptr [ebp - 0x169c], edx
005d8b97 cvtsi2sd xmm0, dword ptr [ebp - 0x169c]
005d8b9f mov edx, dword ptr [ebp - 0x169c]
005d8ba5 shr edx, 0x1f
005d8ba8 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
005d8bb1 movsd qword ptr [ebp - 0x2b74], xmm0
005d8bb9 cvtsd2ss xmm0, qword ptr [ebp - 0x2b74]
005d8bc1 mulss xmm0, dword ptr [0xb6a7b0]
005d8bc9 subss xmm0, dword ptr [0xb6a614]
005d8bd1 movss dword ptr [ebp - 0x1efc], xmm0
005d8bd9 movss xmm0, dword ptr [0xb6a864]
005d8be1 movss dword ptr [ebp - 0x1ef4], xmm0
005d8be9 push 0
005d8beb mov ecx, dword ptr [ebp - 0xeb8]
005d8bf1 add ecx, 0x3c
005d8bf4 call 0x4062c0
005d8bf9 movss xmm0, dword ptr [eax + 0x44]
005d8bfe call 0x412000
005d8c03 divss xmm0, dword ptr [0xb6a9b0]
005d8c0b movss dword ptr [ebp - 0x1ef8], xmm0
005d8c13 lea eax, [ebp - 0x1ef4]
005d8c19 push eax
005d8c1a lea ecx, [ebp - 0x3574]
005d8c20 push ecx
005d8c21 lea edx, [ebp - 0x1ef8]
005d8c27 push edx
005d8c28 lea eax, [ebp - 0x357c]
005d8c2e push eax
005d8c2f mov ecx, dword ptr [0xbfd65c]
005d8c35 call 0x402400
005d8c3a cvtsi2ss xmm0, eax
005d8c3e mulss xmm0, dword ptr [0xb6a9ac]
005d8c46 mulss xmm0, dword ptr [ebp - 0x1efc]
005d8c4e push ecx
005d8c4f movss dword ptr [esp], xmm0
005d8c54 lea ecx, [ebp - 0x3584]
005d8c5a push ecx
005d8c5b call 0x9627f0
005d8c60 add esp, 8
005d8c63 mov ecx, eax
005d8c65 call 0x962b50
005d8c6a mov ecx, eax
005d8c6c call 0x962b50
005d8c71 push eax
005d8c72 mov ecx, dword ptr [ebp - 0xeb8]
005d8c78 add ecx, 0x294
005d8c7e call 0x962a90
005d8c83 mov edx, dword ptr [ebp - 0xeb8]
005d8c89 movss xmm0, dword ptr [edx + 0x2c4]
005d8c91 mulss xmm0, dword ptr [0xb6a560]
005d8c99 mov eax, dword ptr [ebp - 0xeb8]
005d8c9f movss dword ptr [eax + 0x2c4], xmm0
005d8ca7 mov ecx, dword ptr [ebp - 0xeb8]
005d8cad movzx edx, byte ptr [ecx + 0x16b]
005d8cb4 test edx, edx
005d8cb6 jne 0x5d93f2
005d8cbc mov ecx, 5
005d8cc1 call 0x659230
005d8cc6 test eax, eax
005d8cc8 jne 0x5d8de9
005d8cce mov eax, dword ptr [ebp - 0xeb8]
005d8cd4 cmp dword ptr [eax + 0x314], 0
005d8cdb jne 0x5d8d1e
005d8cdd call 0x659200
005d8ce2 mulss xmm0, dword ptr [0xb6a480]
005d8cea movss dword ptr [ebp - 0x1f00], xmm0
005d8cf2 push 0
005d8cf4 lea ecx, [ebp - 0x1f00]
005d8cfa push ecx
005d8cfb lea edx, [ebp - 0x358c]
005d8d01 push edx
005d8d02 lea ecx, [ebp - 0x1970]
005d8d08 call 0x962b50
005d8d0d push eax
005d8d0e mov ecx, dword ptr [ebp - 0xeb8]
005d8d14 call 0x422b60
005d8d19 jmp 0x5d8de9
005d8d1e mov eax, dword ptr [ebp - 0xeb8]
005d8d24 add eax, 0x294
005d8d29 push eax
005d8d2a lea ecx, [ebp - 0x2458]
005d8d30 push ecx
005d8d31 lea edx, [ebp - 0x3594]
005d8d37 push edx
005d8d38 mov eax, dword ptr [ebp - 0xeb8]
005d8d3e mov ecx, dword ptr [eax + 0x314]
005d8d44 call 0x412130
005d8d49 mov ecx, eax
005d8d4b call 0x962ac0
005d8d50 lea ecx, [ebp - 0x2458]
005d8d56 call 0x962a00
005d8d5b fstp dword ptr [ebp - 0x1f04]
005d8d61 movss xmm0, dword ptr [ebp - 0x1f04]
005d8d69 mov ecx, dword ptr [ebp - 0xeb8]
005d8d6f mov ecx, dword ptr [ecx + 0x314]
005d8d75 movss dword ptr [ebp - 0x1f08], xmm0
005d8d7d call 0x4121e0
005d8d82 movss xmm1, dword ptr [ebp - 0x1f08]
005d8d8a subss xmm1, xmm0
005d8d8e push ecx
005d8d8f movss dword ptr [esp], xmm1
005d8d94 lea ecx, [ebp - 0x2458]
005d8d9a call 0x962860
005d8d9f call 0x659200
005d8da4 mulss xmm0, dword ptr [0xb6a480]
005d8dac movss dword ptr [ebp - 0x1f0c], xmm0
005d8db4 push 0
005d8db6 lea edx, [ebp - 0x1f0c]
005d8dbc push edx
005d8dbd lea eax, [ebp - 0x359c]
005d8dc3 push eax
005d8dc4 lea ecx, [ebp - 0x35a4]
005d8dca push ecx
005d8dcb lea ecx, [ebp - 0x2458]
005d8dd1 call 0x962560
005d8dd6 mov ecx, eax
005d8dd8 call 0x962b50
005d8ddd push eax
005d8dde mov ecx, dword ptr [ebp - 0xeb8]
005d8de4 call 0x422b60
005d8de9 mov edx, dword ptr [ebp - 0xeb8]
005d8def mov eax, dword ptr [edx + 0x20]
005d8df2 push eax
005d8df3 push 5
005d8df5 mov ecx, dword ptr [ebp - 0xeb8]
005d8dfb call 0x684790
005d8e00 movzx ecx, al
005d8e03 test ecx, ecx
005d8e05 je 0x5d8e4e
005d8e07 call 0x659200
005d8e0c mulss xmm0, dword ptr [0xb6a5a4]
005d8e14 movss dword ptr [ebp - 0x1f10], xmm0
005d8e1c push 0
005d8e1e lea edx, [ebp - 0x1f10]
005d8e24 push edx
005d8e25 lea eax, [ebp - 0x35ac]
005d8e2b push eax
005d8e2c lea ecx, [ebp - 0x35b4]
005d8e32 push ecx
005d8e33 call 0x659290
005d8e38 add esp, 4
005d8e3b mov ecx, eax
005d8e3d call 0x962b50
005d8e42 push eax
005d8e43 mov ecx, dword ptr [ebp - 0xeb8]
005d8e49 call 0x422b60
005d8e4e movss xmm0, dword ptr [0xb6aa8c]
005d8e56 comiss xmm0, dword ptr [ebp - 0x11c8]
005d8e5d jbe 0x5d8eca
005d8e5f movss xmm0, dword ptr [ebp - 0x11c8]
005d8e67 mulss xmm0, dword ptr [ebp - 0x11c8]
005d8e6f divss xmm0, dword ptr [0xb6ad0c]
005d8e77 movss xmm1, dword ptr [0xb6a614]
005d8e7f subss xmm1, xmm0
005d8e83 movss dword ptr [ebp - 0x1f14], xmm1
005d8e8b movss xmm0, dword ptr [ebp - 0x1f14]
005d8e93 mulss xmm0, dword ptr [0xb6ae00]
005d8e9b movss dword ptr [ebp - 0x1f18], xmm0
005d8ea3 push 0
005d8ea5 lea edx, [ebp - 0x1f18]
005d8eab push edx
005d8eac lea eax, [ebp - 0x35bc]
005d8eb2 push eax
005d8eb3 lea ecx, [ebp - 0x1970]
005d8eb9 call 0x962b50
005d8ebe push eax
005d8ebf mov ecx, dword ptr [ebp - 0xeb8]
005d8ec5 call 0x422b60
005d8eca push 4
005d8ecc mov ecx, dword ptr [ebp - 0xeb8]
005d8ed2 add ecx, 0x294
005d8ed8 push ecx
005d8ed9 lea edx, [ebp - 0x29c0]
005d8edf push edx
005d8ee0 mov ecx, dword ptr [0xbfd65c]
005d8ee6 call 0x4023f0
005d8eeb mov ecx, eax
005d8eed call 0x422d70
005d8ef2 movss xmm3, dword ptr [0xb6a480]
005d8efa mov ecx, eax
005d8efc call 0x4157f0
005d8f01 mov dword ptr [ebp - 4], 0x2a
005d8f08 mov byte ptr [ebp - 0xf3d], 0
005d8f0f mov dword ptr [ebp - 0x11fc], 0
005d8f19 jmp 0x5d8f2a
005d8f1b mov eax, dword ptr [ebp - 0x11fc]
005d8f21 add eax, 1
005d8f24 mov dword ptr [ebp - 0x11fc], eax
005d8f2a lea ecx, [ebp - 0x29c0]
005d8f30 call 0x4083d0
005d8f35 cmp dword ptr [ebp - 0x11fc], eax
005d8f3b jae 0x5d8f66
005d8f3d mov ecx, dword ptr [ebp - 0x11fc]
005d8f43 push ecx
005d8f44 lea ecx, [ebp - 0x29c0]
005d8f4a call 0x4124b0
005d8f4f mov ecx, dword ptr [eax]
005d8f51 call 0x412100
005d8f56 cmp eax, 2
005d8f59 jne 0x5d8f64
005d8f5b mov byte ptr [ebp - 0xf3d], 1
005d8f62 jmp 0x5d8f66
005d8f64 jmp 0x5d8f1b
005d8f66 movzx edx, byte ptr [ebp - 0xf3d]
005d8f6d test edx, edx
005d8f6f je 0x5d904c
005d8f75 mov eax, dword ptr [ebp - 0xeb8]
005d8f7b mov byte ptr [eax + 0x16b], 1
005d8f82 call 0x659280
005d8f87 push eax
005d8f88 push 0
005d8f8a push 0
005d8f8c push 0xc02fec
005d8f91 movss xmm2, dword ptr [0xb6aed4]
005d8f99 xorps xmm1, xmm1
005d8f9c lea ecx, [ebp - 0x35c4]
005d8fa2 call 0x9624e0
005d8fa7 push eax
005d8fa8 lea ecx, [ebp - 0x35cc]
005d8fae push ecx
005d8faf mov ecx, dword ptr [ebp - 0xeb8]
005d8fb5 add ecx, 0x294
005d8fbb call 0x962a60
005d8fc0 push eax
005d8fc1 push 2
005d8fc3 push 0x3e8
005d8fc8 mov ecx, dword ptr [0xbfd65c]
005d8fce call 0x422e20
005d8fd3 mov dword ptr [ebp - 0x11c4], eax
005d8fd9 push 1
005d8fdb push 0
005d8fdd push 0xff
005d8fe2 push -1
005d8fe4 mov edx, dword ptr [ebp - 0xeb8]
005d8fea add edx, 0x1dc
005d8ff0 push edx
005d8ff1 mov eax, dword ptr [ebp - 0x11c4]
005d8ff7 mov edx, dword ptr [eax]
005d8ff9 mov ecx, dword ptr [ebp - 0x11c4]
005d8fff mov eax, dword ptr [edx + 0x38]
005d9002 call eax
005d9004 movss xmm2, dword ptr [0xb6a3b0]
005d900c movss xmm1, dword ptr [0xb6a3b0]
005d9014 lea ecx, [ebp - 0x35d4]
005d901a call 0x9624e0
005d901f push eax
005d9020 mov ecx, dword ptr [ebp - 0x11c4]
005d9026 call 0x427330
005d902b mov ecx, dword ptr [ebp - 0x11c4]
005d9031 mov edx, dword ptr [ecx]
005d9033 mov ecx, dword ptr [ebp - 0x11c4]
005d9039 mov eax, dword ptr [edx + 0xc]
005d903c call eax
005d903e mov ecx, dword ptr [ebp - 0xeb8]
005d9044 add ecx, 0x3c
005d9047 call 0x4059d0
005d904c push 0
005d904e push 1
005d9050 push -1
005d9052 push -1
005d9054 push 8
005d9056 lea ecx, [ebp - 0x29b0]
005d905c push ecx
005d905d mov ecx, dword ptr [0xbfd65c]
005d9063 call 0x4023f0
005d9068 mov ecx, eax
005d906a call 0x422d70
005d906f mov ecx, eax
005d9071 call 0x415ed0
005d9076 mov byte ptr [ebp - 4], 0x2b
005d907a mov dword ptr [ebp - 0x1200], 0
005d9084 jmp 0x5d9095
005d9086 mov edx, dword ptr [ebp - 0x1200]
005d908c add edx, 1
005d908f mov dword ptr [ebp - 0x1200], edx
005d9095 lea ecx, [ebp - 0x29b0]
005d909b call 0x4083d0
005d90a0 cmp dword ptr [ebp - 0x1200], eax
005d90a6 jae 0x5d9207
005d90ac mov eax, dword ptr [ebp - 0x1200]
005d90b2 push eax
005d90b3 lea ecx, [ebp - 0x29b0]
005d90b9 call 0x4124b0
005d90be mov ecx, dword ptr [eax]
005d90c0 mov dword ptr [ebp - 0x16a0], ecx
005d90c6 mov ecx, dword ptr [ebp - 0x16a0]
005d90cc call 0x4121e0
005d90d1 mulss xmm0, dword ptr [0xb6a6f0]
005d90d9 movss dword ptr [ebp - 0x16a4], xmm0
005d90e1 mov edx, dword ptr [ebp - 0xeb8]
005d90e7 add edx, 0x294
005d90ed push edx
005d90ee lea eax, [ebp - 0x35dc]
005d90f4 push eax
005d90f5 mov ecx, dword ptr [ebp - 0x16a0]
005d90fb call 0x412130
005d9100 mov ecx, eax
005d9102 call 0x962750
005d9107 fstp dword ptr [ebp - 0x1f1c]
005d910d movss xmm0, dword ptr [ebp - 0x16a4]
005d9115 mulss xmm0, dword ptr [ebp - 0x16a4]
005d911d comiss xmm0, dword ptr [ebp - 0x1f1c]
005d9124 jbe 0x5d9202
005d912a mov ecx, dword ptr [ebp - 0xeb8]
005d9130 mov byte ptr [ecx + 0x16b], 1
005d9137 call 0x659280
005d913c push eax
005d913d push 0
005d913f push 0
005d9141 push 0xc02fec
005d9146 movss xmm2, dword ptr [0xb6aed4]
005d914e xorps xmm1, xmm1
005d9151 lea ecx, [ebp - 0x35e4]
005d9157 call 0x9624e0
005d915c push eax
005d915d lea edx, [ebp - 0x35ec]
005d9163 push edx
005d9164 mov ecx, dword ptr [ebp - 0xeb8]
005d916a add ecx, 0x294
005d9170 call 0x962a60
005d9175 push eax
005d9176 push 2
005d9178 push 0x3e8
005d917d mov ecx, dword ptr [0xbfd65c]
005d9183 call 0x422e20
005d9188 mov dword ptr [ebp - 0x11c0], eax
005d918e push 1
005d9190 push 0
005d9192 push 0xff
005d9197 push -1
005d9199 mov eax, dword ptr [ebp - 0xeb8]
005d919f add eax, 0x1dc
005d91a4 push eax
005d91a5 mov ecx, dword ptr [ebp - 0x11c0]
005d91ab mov edx, dword ptr [ecx]
005d91ad mov ecx, dword ptr [ebp - 0x11c0]
005d91b3 mov eax, dword ptr [edx + 0x38]
005d91b6 call eax
005d91b8 movss xmm2, dword ptr [0xb6a3b0]
005d91c0 movss xmm1, dword ptr [0xb6a3b0]
005d91c8 lea ecx, [ebp - 0x35f4]
005d91ce call 0x9624e0
005d91d3 push eax
005d91d4 mov ecx, dword ptr [ebp - 0x11c0]
005d91da call 0x427330
005d91df mov ecx, dword ptr [ebp - 0x11c0]
005d91e5 mov edx, dword ptr [ecx]
005d91e7 mov ecx, dword ptr [ebp - 0x11c0]
005d91ed mov eax, dword ptr [edx + 0xc]
005d91f0 call eax
005d91f2 mov ecx, dword ptr [ebp - 0xeb8]
005d91f8 add ecx, 0x3c
005d91fb call 0x4059d0
005d9200 jmp 0x5d9207
005d9202 jmp 0x5d9086
005d9207 push 0
005d9209 push 1
005d920b push -1
005d920d push -1
005d920f push 0x21
005d9211 lea ecx, [ebp - 0x29a0]
005d9217 push ecx
005d9218 mov ecx, dword ptr [0xbfd65c]
005d921e call 0x4023f0
005d9223 mov ecx, eax
005d9225 call 0x422d70
005d922a mov ecx, eax
005d922c call 0x415ed0
005d9231 mov byte ptr [ebp - 4], 0x2c
005d9235 mov dword ptr [ebp - 0x1204], 0
005d923f jmp 0x5d9250
005d9241 mov edx, dword ptr [ebp - 0x1204]
005d9247 add edx, 1
005d924a mov dword ptr [ebp - 0x1204], edx
005d9250 lea ecx, [ebp - 0x29a0]
005d9256 call 0x4083d0
005d925b cmp dword ptr [ebp - 0x1204], eax
005d9261 jae 0x5d93c2
005d9267 mov eax, dword ptr [ebp - 0x1204]
005d926d push eax
005d926e lea ecx, [ebp - 0x29a0]
005d9274 call 0x4124b0
005d9279 mov ecx, dword ptr [eax]
005d927b mov dword ptr [ebp - 0x16a8], ecx
005d9281 mov ecx, dword ptr [ebp - 0x16a8]
005d9287 call 0x4121e0
005d928c addss xmm0, dword ptr [0xb6a7b0]
005d9294 movss dword ptr [ebp - 0x16ac], xmm0
005d929c mov edx, dword ptr [ebp - 0xeb8]
005d92a2 add edx, 0x294
005d92a8 push edx
005d92a9 lea eax, [ebp - 0x35fc]
005d92af push eax
005d92b0 mov ecx, dword ptr [ebp - 0x16a8]
005d92b6 call 0x412130
005d92bb mov ecx, eax
005d92bd call 0x962750
005d92c2 fstp dword ptr [ebp - 0x1f20]
005d92c8 movss xmm0, dword ptr [ebp - 0x16ac]
005d92d0 mulss xmm0, dword ptr [ebp - 0x16ac]
005d92d8 comiss xmm0, dword ptr [ebp - 0x1f20]
005d92df jbe 0x5d93bd
005d92e5 mov ecx, dword ptr [ebp - 0xeb8]
005d92eb mov byte ptr [ecx + 0x16b], 1
005d92f2 call 0x659280
005d92f7 push eax
005d92f8 push 0
005d92fa push 0
005d92fc push 0xc02fec
005d9301 movss xmm2, dword ptr [0xb6aed4]
005d9309 xorps xmm1, xmm1
005d930c lea ecx, [ebp - 0x3604]
005d9312 call 0x9624e0
005d9317 push eax
005d9318 lea edx, [ebp - 0x360c]
005d931e push edx
005d931f mov ecx, dword ptr [ebp - 0xeb8]
005d9325 add ecx, 0x294
005d932b call 0x962a60
005d9330 push eax
005d9331 push 2
005d9333 push 0x3e8
005d9338 mov ecx, dword ptr [0xbfd65c]
005d933e call 0x422e20
005d9343 mov dword ptr [ebp - 0x11bc], eax
005d9349 push 1
005d934b push 0
005d934d push 0xff
005d9352 push -1
005d9354 mov eax, dword ptr [ebp - 0xeb8]
005d935a add eax, 0x1dc
005d935f push eax
005d9360 mov ecx, dword ptr [ebp - 0x11bc]
005d9366 mov edx, dword ptr [ecx]
005d9368 mov ecx, dword ptr [ebp - 0x11bc]
005d936e mov eax, dword ptr [edx + 0x38]
005d9371 call eax
005d9373 movss xmm2, dword ptr [0xb6a3b0]
005d937b movss xmm1, dword ptr [0xb6a3b0]
005d9383 lea ecx, [ebp - 0x3614]
005d9389 call 0x9624e0
005d938e push eax
005d938f mov ecx, dword ptr [ebp - 0x11bc]
005d9395 call 0x427330
005d939a mov ecx, dword ptr [ebp - 0x11bc]
005d93a0 mov edx, dword ptr [ecx]
005d93a2 mov ecx, dword ptr [ebp - 0x11bc]
005d93a8 mov eax, dword ptr [edx + 0xc]
005d93ab call eax
005d93ad mov ecx, dword ptr [ebp - 0xeb8]
005d93b3 add ecx, 0x3c
005d93b6 call 0x4059d0
005d93bb jmp 0x5d93c2
005d93bd jmp 0x5d9241
005d93c2 mov byte ptr [ebp - 4], 0x2b
005d93c6 lea ecx, [ebp - 0x29a0]
005d93cc call 0x412490
005d93d1 mov byte ptr [ebp - 4], 0x2a
005d93d5 lea ecx, [ebp - 0x29b0]
005d93db call 0x412490
005d93e0 mov dword ptr [ebp - 4], 0xffffffff
005d93e7 lea ecx, [ebp - 0x29c0]
005d93ed call 0x412490
