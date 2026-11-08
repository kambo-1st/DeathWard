00724f00 push ebp
00724f01 mov ebp, esp
00724f03 and esp, 0xfffffff8
00724f06 push ecx
00724f07 mov dl, byte ptr [ebp + 0xc]
00724f0a push ebx
00724f0b mov ebx, dword ptr [0xbfd65c]
00724f11 push esi
00724f12 push edi
00724f13 mov edi, dword ptr [ebp + 8]
00724f16 mov esi, ecx
00724f18 nop dword ptr [eax + eax]
00724f20 mov eax, dword ptr [esi + 0x130c]
00724f26 cmp eax, 0x28
00724f29 jne 0x724f39
00724f2b mov ecx, dword ptr [esi + 0x1d80]
00724f31 test ecx, ecx
00724f33 je 0x724f39
00724f35 mov esi, ecx
00724f37 jmp 0x724f20
00724f39 test edi, edi
00724f3b jle 0x724f4e
00724f3d test dl, dl
00724f3f jne 0x724f4e
00724f41 cmp dword ptr [ebx + 0x1c319c], 0x19
00724f48 je 0x725044
00724f4e cmp eax, 0x11
00724f51 jne 0x724f63
00724f53 mov eax, dword ptr [esi + 0x1cb8]
00724f59 test eax, eax
00724f5b je 0x724f88
00724f5d xor dl, dl
00724f5f mov esi, eax
00724f61 jmp 0x724f20
00724f63 cmp eax, 0x24
00724f66 jne 0x724f79
00724f68 push edi
00724f69 mov ecx, esi
00724f6b call 0x7946a0
00724f70 pop edi
00724f71 pop esi
00724f72 pop ebx
00724f73 mov esp, ebp
00724f75 pop ebp
00724f76 ret 8
00724f79 cmp eax, 0x16
00724f7c jne 0x724f88
00724f7e test dl, dl
00724f80 jne 0x724f88
00724f82 test edi, edi
00724f84 jle 0x724f88
00724f86 add edi, edi
00724f88 mov ecx, esi
00724f8a call 0x78cdc0
00724f8f cmp eax, 1
00724f92 je 0x725044
00724f98 call 0x78cdc0
00724f9d cmp eax, 2
00724fa0 je 0x725044
00724fa6 call 0x78cdc0
00724fab cmp eax, 3
00724fae jne 0x724fc2
00724fb0 lea eax, [edi + 1]
00724fb3 test edi, edi
00724fb5 jg 0x724fba
00724fb7 lea eax, [edi - 1]
00724fba cdq 
00724fbb sub eax, edx
00724fbd mov edi, eax
00724fbf and edi, 0xfffffffe
00724fc2 mov eax, dword ptr [esi + 0x1290]
00724fc8 mov ebx, dword ptr [esi + 0x1294]
00724fce mov ecx, dword ptr [esi + 0x1ca8]
00724fd4 lea ecx, [eax + ecx*2]
00724fd7 lea eax, [ebx + edi]
00724fda cmp eax, ecx
00724fdc cmovl ecx, eax
00724fdf xor eax, eax
00724fe1 test ecx, ecx
00724fe3 cmovs ecx, eax
00724fe6 mov dword ptr [esi + 0x1294], ecx
00724fec test edi, edi
00724fee jle 0x72500d
00724ff0 mov eax, dword ptr [esi + 0x160]
00724ff6 and dword ptr [esi + 0x164], 0xfffffffb
00724ffd mov dword ptr [esi + 0x160], eax
00725003 mov dword ptr [esi + 0x12dc], 0
0072500d cmp ecx, ebx
0072500f je 0x725018
00725011 mov ecx, esi
00725013 call 0x78bf20
00725018 mov ecx, esi
0072501a call 0x78c810
0072501f mov ecx, esi
00725021 call 0x78cb90
00725026 test edi, edi
00725028 jle 0x725044
0072502a cmp dword ptr [esi + 0x1294], ebx
00725030 jle 0x725044
00725032 mov ecx, dword ptr [0xbfd65c]
00725038 push esi
00725039 lea ecx, [ecx + 0x3da4c]
0072503f call 0x909fd0
00725044 pop edi
00725045 pop esi
00725046 pop ebx
00725047 mov esp, ebp
00725049 pop ebp
0072504a ret 8
0072504d int3 
0072504e int3 
0072504f int3 
