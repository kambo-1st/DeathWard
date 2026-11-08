00724d50 push ebp
00724d51 mov ebp, esp
00724d53 and esp, 0xfffffff8
00724d56 push ecx
00724d57 push ebx
00724d58 push esi
00724d59 mov esi, ecx
00724d5b push edi
00724d5c mov edi, dword ptr [ebp + 8]
00724d5f cmp dword ptr [esi + 0x130c], 0x28
00724d66 jne 0x724d85
00724d68 nop dword ptr [eax + eax]
00724d70 mov eax, dword ptr [esi + 0x1d80]
00724d76 test eax, eax
00724d78 je 0x724d85
00724d7a mov esi, eax
00724d7c cmp dword ptr [esi + 0x130c], 0x28
00724d83 je 0x724d70
00724d85 mov ecx, esi
00724d87 call 0x78cdc0
00724d8c cmp eax, 2
00724d8f je 0x724ef4
00724d95 call 0x78cdc0
00724d9a cmp eax, 1
00724d9d jne 0x724e01
00724d9f push 0
00724da1 push 0x26b
00724da6 call 0x73af30
00724dab test al, al
00724dad je 0x724dcf
00724daf cmp dword ptr [esi + 0x130c], 4
00724db6 jne 0x724dcf
00724db8 test edi, edi
00724dba jle 0x724dcf
00724dbc add edi, edi
00724dbe mov ecx, esi
00724dc0 push edi
00724dc1 call 0x725130
00724dc6 pop edi
00724dc7 pop esi
00724dc8 pop ebx
00724dc9 mov esp, ebp
00724dcb pop ebp
00724dcc ret 8
00724dcf mov eax, dword ptr [esi + 0x130c]
00724dd5 cmp eax, 0xc
00724dd8 je 0x724df0
00724dda cmp eax, 0x18
00724ddd je 0x724df0
00724ddf push edi
00724de0 mov ecx, esi
00724de2 call 0x725130
00724de7 pop edi
00724de8 pop esi
00724de9 pop ebx
00724dea mov esp, ebp
00724dec pop ebp
00724ded ret 8
00724df0 push edi
00724df1 mov ecx, esi
00724df3 call 0x725380
00724df8 pop edi
00724df9 pop esi
00724dfa pop ebx
00724dfb mov esp, ebp
00724dfd pop ebp
00724dfe ret 8
00724e01 call 0x78cdc0
00724e06 mov ecx, esi
00724e08 cmp eax, 4
00724e0b jne 0x724e23
00724e0d mov eax, edi
00724e0f cdq 
00724e10 sub eax, edx
00724e12 sar eax, 1
00724e14 push eax
00724e15 call 0x78c870
00724e1a pop edi
00724e1b pop esi
00724e1c pop ebx
00724e1d mov esp, ebp
00724e1f pop ebp
00724e20 ret 8
00724e23 push dword ptr [ebp + 0xc]
00724e26 call 0x78cc70
00724e2b mov ebx, eax
00724e2d test edi, edi
00724e2f jns 0x724e3d
00724e31 mov ecx, edi
00724e33 neg ecx
00724e35 push ecx
00724e36 mov ecx, esi
00724e38 call 0x724d00
00724e3d mov ecx, dword ptr [esi + 0x1290]
00724e43 lea eax, [ecx + edi]
00724e46 cmp eax, ebx
00724e48 jle 0x724e5c
00724e4a sub ecx, ebx
00724e4c add ecx, edi
00724e4e push ecx
00724e4f mov ecx, esi
00724e51 call 0x724d00
00724e56 mov ecx, dword ptr [esi + 0x1290]
00724e5c add edi, ecx
00724e5e cmp ebx, edi
00724e60 cmovl edi, ebx
00724e63 mov dword ptr [esi + 0x1290], edi
00724e69 test edi, edi
00724e6b jns 0x724e8c
00724e6d mov eax, edi
00724e6f mov dword ptr [esi + 0x1290], 0
00724e79 cdq 
00724e7a mov ecx, esi
00724e7c sub eax, edx
00724e7e sar eax, 1
00724e80 push eax
00724e81 call 0x78c870
00724e86 mov edi, dword ptr [esi + 0x1290]
00724e8c mov ecx, esi
00724e8e call 0x78ce40
00724e93 mov ecx, dword ptr [esi + 0x129c]
00724e99 add ecx, eax
00724e9b cmp ecx, ebx
00724e9d jle 0x724eae
00724e9f sub ebx, eax
00724ea1 xor ecx, ecx
00724ea3 test ebx, ebx
00724ea5 cmovg ecx, ebx
00724ea8 mov dword ptr [esi + 0x129c], ecx
00724eae cmp dword ptr [esi + 0x1294], eax
00724eb4 jle 0x724ebc
00724eb6 mov dword ptr [esi + 0x1294], eax
00724ebc cmp edi, 0xe
00724ebf jl 0x724ed1
00724ec1 mov ecx, dword ptr [0xbfd680]
00724ec7 push 1
00724ec9 lea ecx, [ecx + 0x14]
00724ecc call 0x884c80
00724ed1 mov ecx, esi
00724ed3 call 0x725600
00724ed8 mov ecx, esi
00724eda call 0x78fd00
00724edf mov ecx, esi
00724ee1 call 0x78bf20
00724ee6 mov ecx, esi
00724ee8 call 0x78c810
00724eed mov ecx, esi
00724eef call 0x78cb90
00724ef4 pop edi
00724ef5 pop esi
00724ef6 pop ebx
00724ef7 mov esp, ebp
00724ef9 pop ebp
00724efa ret 8
00724efd int3 
00724efe int3 
00724eff int3 
