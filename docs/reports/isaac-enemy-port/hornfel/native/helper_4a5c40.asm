; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a5c40 push ebx
004a5c41 mov ebx, esp
004a5c43 sub esp, 8
004a5c46 and esp, 0xfffffff8
004a5c49 add esp, 4
004a5c4c push ebp
004a5c4d mov ebp, dword ptr [ebx + 4]
004a5c50 mov dword ptr [esp + 4], ebp
004a5c54 mov ebp, esp
004a5c56 push -1
004a5c58 push 0x9ee5bd
004a5c5d mov eax, dword ptr fs:[0]
004a5c63 push eax
004a5c64 push ebx
004a5c65 sub esp, 0x30
004a5c68 mov eax, dword ptr [0xbaa3b4] ; [0xbaa3b4] f32=-0.00294341473
004a5c6d xor eax, ebp
004a5c6f mov dword ptr [ebp - 0x14], eax
004a5c72 push esi
004a5c73 push edi
004a5c74 push eax
004a5c75 lea eax, [ebp - 0xc]
004a5c78 mov dword ptr fs:[0], eax
004a5c7e mov esi, ecx
004a5c80 mov dword ptr [ebp - 0x28], 0
004a5c87 mov dword ptr [ebp - 0x24], 0
004a5c8e mov dword ptr [ebp - 0x20], 0
004a5c95 lea eax, [ebp - 0x34]
004a5c98 mov dword ptr [ebp - 4], 0
004a5c9f push eax
004a5ca0 push 0
004a5ca2 lea ecx, [ebp - 0x28]
004a5ca5 mov dword ptr [ebp - 0x34], 0
004a5cac mov dword ptr [ebp - 0x30], 3
004a5cb3 call 0x48d900
004a5cb8 mov edx, dword ptr [ebp - 0x24]
004a5cbb xor eax, eax
004a5cbd mov ecx, dword ptr [ebp - 0x28]
004a5cc0 mov edi, edx
004a5cc2 sub edi, ecx
004a5cc4 sar edi, 3
004a5cc7 test edi, edi
004a5cc9 je 0x4a5cdb
004a5ccb nop dword ptr [eax + eax]
004a5cd0 cmp dword ptr [ecx + eax*8], 1
004a5cd4 je 0x4a5d03
004a5cd6 inc eax
004a5cd7 cmp eax, edi
004a5cd9 jb 0x4a5cd0
004a5cdb mov dword ptr [ebp - 0x34], 1
004a5ce2 mov dword ptr [ebp - 0x30], 1
004a5ce9 cmp edx, dword ptr [ebp - 0x20]
004a5cec je 0x4a5d14
004a5cee mov dword ptr [edx], 1
004a5cf4 mov dword ptr [edx + 4], 1
004a5cfb add edx, 8
004a5cfe mov dword ptr [ebp - 0x24], edx
004a5d01 jmp 0x4a5d27
004a5d03 add dword ptr [ecx + eax*8 + 4], 1
004a5d08 jns 0x4a5d27
004a5d0a mov dword ptr [ecx + eax*8 + 4], 0
004a5d12 jmp 0x4a5d27
004a5d14 lea eax, [ebp - 0x34]
004a5d17 push eax
004a5d18 push edx
004a5d19 lea ecx, [ebp - 0x28]
004a5d1c call 0x48d900
004a5d21 mov edx, dword ptr [ebp - 0x24]
004a5d24 mov ecx, dword ptr [ebp - 0x28]
004a5d27 cmp byte ptr [esi + 0xaf0], 0
004a5d2e ja 0x4a5d91
004a5d30 mov edi, edx
004a5d32 xor eax, eax
004a5d34 sub edi, ecx
004a5d36 sar edi, 3
004a5d39 test edi, edi
004a5d3b je 0x4a5d4b
004a5d3d nop dword ptr [eax]
004a5d40 cmp dword ptr [ecx + eax*8], 2
004a5d44 je 0x4a5d73
004a5d46 inc eax
004a5d47 cmp eax, edi
004a5d49 jb 0x4a5d40
004a5d4b mov dword ptr [ebp - 0x34], 2
004a5d52 mov dword ptr [ebp - 0x30], 1
004a5d59 cmp edx, dword ptr [ebp - 0x20]
004a5d5c je 0x4a5d84
004a5d5e mov dword ptr [edx], 2
004a5d64 mov dword ptr [edx + 4], 1
004a5d6b add edx, 8
004a5d6e mov dword ptr [ebp - 0x24], edx
004a5d71 jmp 0x4a5d91
004a5d73 add dword ptr [ecx + eax*8 + 4], 1
004a5d78 jns 0x4a5d91
004a5d7a mov dword ptr [ecx + eax*8 + 4], 0
004a5d82 jmp 0x4a5d91
004a5d84 lea eax, [ebp - 0x34]
004a5d87 push eax
004a5d88 push edx
004a5d89 lea ecx, [ebp - 0x28]
004a5d8c call 0x48d900
004a5d91 call 0x6c3d90
004a5d96 movq xmm0, qword ptr [0xa08c44] ; [0xa08c44] f32=7.00649232e-45
004a5d9e lea ecx, [ebp - 0x28]
004a5da1 or eax, 1
004a5da4 movq qword ptr [ebp - 0x38], xmm0
004a5da9 mov dword ptr [ebp - 0x3c], eax
004a5dac sub esp, 0x10
004a5daf mov eax, dword ptr [0xa08c4c] ; [0xa08c4c] f32=9.80908925e-45
004a5db4 mov dword ptr [ebp - 0x30], eax
004a5db7 mov eax, esp
004a5db9 movups xmm0, xmmword ptr [ebp - 0x3c]
004a5dbd movups xmmword ptr [eax], xmm0
004a5dc0 call 0x489420 ; PickOutcome
004a5dc5 mov ecx, esi
004a5dc7 mov edi, eax
004a5dc9 call 0x695680
004a5dce movss xmm1, dword ptr [eax + 0x294]
004a5dd6 subss xmm1, dword ptr [esi + 0x294]
004a5dde movss xmm2, dword ptr [eax + 0x298]
004a5de6 subss xmm2, dword ptr [esi + 0x298]
004a5dee movaps xmm0, xmm1
004a5df1 movss dword ptr [ebp - 0x18], xmm1
004a5df6 mulss xmm0, xmm1
004a5dfa movaps xmm1, xmm2
004a5dfd movss dword ptr [ebp - 0x2c], xmm2
004a5e02 mulss xmm1, xmm2
004a5e06 addss xmm0, xmm1
004a5e0a call 0x4228c0
004a5e0f comiss xmm0, dword ptr [0xb6a18c] ; [0xb6a18c] f32=0
004a5e16 jbe 0x4a5e40
004a5e18 movss xmm1, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a5e20 divss xmm1, xmm0
004a5e24 movss xmm0, dword ptr [ebp - 0x18]
004a5e29 mulss xmm0, xmm1
004a5e2d movss dword ptr [ebp - 0x18], xmm0
004a5e32 movss xmm0, dword ptr [ebp - 0x2c]
004a5e37 mulss xmm0, xmm1
004a5e3b movss dword ptr [ebp - 0x2c], xmm0
004a5e40 mov byte ptr [esi + 0xaf7], 1
004a5e47 sub edi, 0
004a5e4a je 0x4a5f66
004a5e50 sub edi, 1
004a5e53 je 0x4a5e82
004a5e55 sub edi, 1
004a5e58 jne 0x4a6014
004a5e5e push edi
004a5e5f push 0xb400bc ; string='Attack2'
004a5e64 lea ecx, [esi + 0x3c]
004a5e67 call 0x4054f0
004a5e6c mov dword ptr [esi + 0xab4], 9
004a5e76 mov byte ptr [esi + 0xaf0], 0x96
004a5e7d jmp 0x4a6014
004a5e82 mov edx, dword ptr [esi + 0xb4c]
004a5e88 mov ecx, edx
004a5e8a mov eax, dword ptr [esi + 0xb48]
004a5e90 and edx, 3
004a5e93 dec eax
004a5e94 shr ecx, 2
004a5e97 and ecx, eax
004a5e99 mov eax, dword ptr [esi + 0xb44]
004a5e9f push ecx
004a5ea0 mov eax, dword ptr [eax + ecx*4]
004a5ea3 mov ecx, esi
004a5ea5 lea edi, [eax + edx*4]
004a5ea8 call 0x4a4e70
004a5ead mov ecx, dword ptr [edi]
004a5eaf mov dword ptr [ebp - 0x1c], eax
004a5eb2 test ecx, ecx
004a5eb4 je 0x4a5ecb
004a5eb6 lea eax, [ebp - 0x18]
004a5eb9 mov dword ptr [ebp - 0x18], edi
004a5ebc push eax
004a5ebd add ecx, 0x324
004a5ec3 call 0x4bc3c0
004a5ec8 mov eax, dword ptr [ebp - 0x1c]
004a5ecb mov dword ptr [edi], eax
004a5ecd test eax, eax
004a5ecf je 0x4a5ed9
004a5ed1 push edi
004a5ed2 mov ecx, eax
004a5ed4 call 0x4bae70
004a5ed9 mov eax, dword ptr [esi + 0xb4c]
004a5edf lea edx, [eax + 1]
004a5ee2 mov eax, dword ptr [esi + 0xb48]
004a5ee8 mov ecx, edx
004a5eea dec eax
004a5eeb shr ecx, 2
004a5eee and edx, 3
004a5ef1 and ecx, eax
004a5ef3 mov eax, dword ptr [esi + 0xb44]
004a5ef9 push ecx
004a5efa mov eax, dword ptr [eax + ecx*4]
004a5efd mov ecx, esi
004a5eff lea edi, [eax + edx*4]
004a5f02 call 0x4a4e70
004a5f07 mov ecx, dword ptr [edi]
004a5f09 mov dword ptr [ebp - 0x18], eax
004a5f0c test ecx, ecx
004a5f0e je 0x4a5f25
004a5f10 lea eax, [ebp - 0x1c]
004a5f13 mov dword ptr [ebp - 0x1c], edi
004a5f16 push eax
004a5f17 add ecx, 0x324
004a5f1d call 0x4bc3c0
004a5f22 mov eax, dword ptr [ebp - 0x18]
004a5f25 mov dword ptr [edi], eax
004a5f27 test eax, eax
004a5f29 je 0x4a5f33
004a5f2b push edi
004a5f2c mov ecx, eax
004a5f2e call 0x4bae70
004a5f33 movss xmm0, dword ptr [0xb6ae00] ; [0xb6ae00] f32=-0.200000003
004a5f3b lea ecx, [esi + 0x3c]
004a5f3e comiss xmm0, dword ptr [ebp - 0x2c]
004a5f42 push 0
004a5f44 jbe 0x4a5f5c
004a5f46 push 0xb41d28 ; string='Attack1Double_Back'
004a5f4b call 0x4054f0
004a5f50 mov byte ptr [esi + 0xaf7], 0
004a5f57 jmp 0x4a600a
004a5f5c push 0xb41d18 ; string='Attack1Double'
004a5f61 jmp 0x4a6005
004a5f66 mov edx, dword ptr [esi + 0xb4c]
004a5f6c mov eax, edx
004a5f6e mov ecx, dword ptr [esi + 0xb48]
004a5f74 and edx, 3
004a5f77 shr eax, 2
004a5f7a dec ecx
004a5f7b and ecx, eax
004a5f7d mov eax, dword ptr [esi + 0xb44]
004a5f83 push ecx
004a5f84 mov eax, dword ptr [eax + ecx*4]
004a5f87 mov ecx, esi
004a5f89 lea edi, [eax + edx*4]
004a5f8c call 0x4a4e70
004a5f91 mov ecx, dword ptr [edi]
004a5f93 mov dword ptr [ebp - 0x30], eax
004a5f96 test ecx, ecx
004a5f98 je 0x4a5faf
004a5f9a lea eax, [ebp - 0x1c]
004a5f9d mov dword ptr [ebp - 0x1c], edi
004a5fa0 push eax
004a5fa1 add ecx, 0x324
004a5fa7 call 0x4bc3c0
004a5fac mov eax, dword ptr [ebp - 0x30]
004a5faf mov dword ptr [edi], eax
004a5fb1 test eax, eax
004a5fb3 je 0x4a5fbd
004a5fb5 push edi
004a5fb6 mov ecx, eax
004a5fb8 call 0x4bae70
004a5fbd movss xmm0, dword ptr [0xb6ae00] ; [0xb6ae00] f32=-0.200000003
004a5fc5 lea ecx, [esi + 0x3c]
004a5fc8 comiss xmm0, dword ptr [ebp - 0x2c]
004a5fcc push 0
004a5fce xorps xmm0, xmm0
004a5fd1 jbe 0x4a5ff3
004a5fd3 comiss xmm0, dword ptr [ebp - 0x18]
004a5fd7 mov edx, 0xb41cd4 ; string='Attack1Right_Back'
004a5fdc mov eax, 0xb41ce8 ; string='Attack1Left_Back'
004a5fe1 cmovbe eax, edx
004a5fe4 push eax
004a5fe5 call 0x4054f0
004a5fea mov byte ptr [esi + 0xaf7], 0
004a5ff1 jmp 0x4a600a
004a5ff3 comiss xmm0, dword ptr [ebp - 0x18]
004a5ff7 jbe 0x4a6000
004a5ff9 push 0xb41d0c ; string='Attack1Left'
004a5ffe jmp 0x4a6005
004a6000 push 0xb41cfc ; string='Attack1Right'
004a6005 call 0x4054f0
004a600a mov dword ptr [esi + 0xab4], 8
004a6014 mov edx, dword ptr [ebp - 0x28]
004a6017 mov byte ptr [esi + 0xaf6], 0
004a601e test edx, edx
004a6020 je 0x4a6054
004a6022 mov ecx, dword ptr [ebp - 0x20]
004a6025 mov eax, edx
004a6027 sub ecx, edx
004a6029 and ecx, 0xfffffff8
004a602c cmp ecx, 0x1000
004a6032 jb 0x4a604a
004a6034 mov edx, dword ptr [edx - 4]
004a6037 add ecx, 0x23
004a603a sub eax, edx
004a603c add eax, -4
004a603f cmp eax, 0x1f
004a6042 jbe 0x4a604a
004a6044 call dword ptr [0xa065ac] ; [0xa065ac] f32=1.12523062e-38
004a604a push ecx
004a604b push edx
004a604c call 0x9eb08e
004a6051 add esp, 8
004a6054 mov ecx, dword ptr [ebp - 0xc]
004a6057 mov dword ptr fs:[0], ecx
004a605e pop ecx
004a605f pop edi
004a6060 pop esi
004a6061 mov ecx, dword ptr [ebp - 0x14]
004a6064 xor ecx, ebp
004a6066 call 0x9eacd7
004a606b mov esp, ebp
004a606d pop ebp
004a606e mov esp, ebx
004a6070 pop ebx
004a6071 ret 
004a6072 int3 
004a6073 int3 
004a6074 int3 
004a6075 int3 
004a6076 int3 
004a6077 int3 
004a6078 int3 
004a6079 int3 
004a607a int3 
004a607b int3 
004a607c int3 
004a607d int3 
004a607e int3 
004a607f int3 
