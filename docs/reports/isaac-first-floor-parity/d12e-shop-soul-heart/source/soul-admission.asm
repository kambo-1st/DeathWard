00786d80 push ebp
00786d81 mov ebp, esp
00786d83 and esp, 0xfffffff8
00786d86 push ecx
00786d87 push ebx
00786d88 push esi
00786d89 push edi
00786d8a mov esi, ecx
00786d8c nop dword ptr [eax]
00786d90 mov eax, dword ptr [esi + 0x130c]
00786d96 cmp eax, 0x28
00786d99 jne 0x786da9
00786d9b mov eax, dword ptr [esi + 0x1d80]
00786da1 test eax, eax
00786da3 je 0x786dbc
00786da5 mov esi, eax
00786da7 jmp 0x786d90
00786da9 cmp eax, 0x10
00786dac jne 0x786dbc
00786dae mov eax, dword ptr [esi + 0x1cb8]
00786db4 test eax, eax
00786db6 je 0x786dbc
00786db8 mov esi, eax
00786dba jmp 0x786d90
00786dbc xor edi, edi
00786dbe nop
00786dc0 lea eax, [edi*8]
00786dc7 sub eax, edi
00786dc9 cmp dword ptr [esi + eax*4 + 0x14c4], 0x249
00786dd4 lea edx, [esi + eax*4]
00786dd7 jne 0x786e0a
00786dd9 lea ecx, [edi + 0xbe]
00786ddf lea eax, [ecx*8]
00786de6 sub eax, ecx
00786de8 mov ebx, dword ptr [esi + eax*4]
00786deb cmp edi, 3
00786dee jne 0x786df4
00786df0 xor eax, eax
00786df2 jmp 0x786e06
00786df4 push dword ptr [edx + 0x14dc]
00786dfa mov ecx, esi
00786dfc push 0x249
00786e01 call 0x757d80
00786e06 cmp ebx, eax
00786e08 jl 0x786e24
00786e0a inc edi
00786e0b cmp edi, 4
00786e0e jb 0x786dc0
00786e10 mov eax, dword ptr [esi + 0x130c]
00786e16 cmp eax, 0x12
00786e19 jne 0x786e2d
00786e1b cmp dword ptr [esi + 0x1cc8], 0x63
00786e22 jge 0x786e32
00786e24 mov al, 1
00786e26 pop edi
00786e27 pop esi
00786e28 pop ebx
00786e29 mov esp, ebp
00786e2b pop ebp
00786e2c ret
00786e2d cmp eax, 0x10
00786e30 je 0x786e54
00786e32 push 0
00786e34 mov ecx, esi
00786e36 call 0x78cc70
00786e3b mov edx, dword ptr [esi + 0x1ca8]
00786e41 mov ecx, dword ptr [esi + 0x129c]
00786e47 lea ecx, [ecx + edx*2]
00786e4a add ecx, dword ptr [esi + 0x1290]
00786e50 cmp ecx, eax
00786e52 jl 0x786e24
00786e54 pop edi
00786e55 pop esi
00786e56 xor al, al
00786e58 pop ebx
00786e59 mov esp, ebp
00786e5b pop ebp
00786e5c ret
00786e5d int3
00786e5e int3
00786e5f int3
