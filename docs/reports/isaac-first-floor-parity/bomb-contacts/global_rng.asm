006c3d50 mov dword ptr [0xbffe10], ecx
006c3d56 mov eax, 1
006c3d5b nop dword ptr [eax + eax]
006c3d60 mov ecx, dword ptr [eax*4 + 0xbffe0c]
006c3d67 mov edx, ecx
006c3d69 shr edx, 0x1e
006c3d6c xor edx, ecx
006c3d6e imul ecx, edx, 0x6c078965
006c3d74 add ecx, eax
006c3d76 mov dword ptr [eax*4 + 0xbffe10], ecx
006c3d7d inc eax
006c3d7e cmp eax, 0x270
006c3d83 jl 0x6c3d60
006c3d85 mov dword ptr [0xbc5304], eax
006c3d8a ret 
006c3d8b int3 
006c3d8c int3 
006c3d8d int3 
006c3d8e int3 
006c3d8f int3 
006c3d90 mov eax, dword ptr [0xbc5304]
006c3d95 cmp eax, 0x270
006c3d9a jl 0x6c3e7a
006c3da0 cmp eax, 0x271
006c3da5 jne 0x6c3db1
006c3da7 mov ecx, 0x1571
006c3dac call 0x6c3d50
006c3db1 xor eax, eax
006c3db3 nop dword ptr [eax]
006c3db7 nop word ptr [eax + eax]
006c3dc0 mov edx, dword ptr [eax*4 + 0xbffe14]
006c3dc7 xor edx, dword ptr [eax*4 + 0xbffe10]
006c3dce and edx, 0x7fffffff
006c3dd4 xor edx, dword ptr [eax*4 + 0xbffe10]
006c3ddb mov ecx, edx
006c3ddd shr edx, 1
006c3ddf and ecx, 1
006c3de2 xor edx, dword ptr [ecx*4 + 0xb49b28]
006c3de9 xor edx, dword ptr [eax*4 + 0xc00444]
006c3df0 mov dword ptr [eax*4 + 0xbffe10], edx
006c3df7 inc eax
006c3df8 cmp eax, 0xe3
006c3dfd jl 0x6c3dc0
006c3dff push esi
006c3e00 push edi
006c3e01 lea edi, [eax*4 + 0xbffe10]
006c3e08 mov eax, dword ptr [edi]
006c3e0a nop word ptr [eax + eax]
006c3e10 mov ecx, dword ptr [edi + 4]
006c3e13 lea edx, [edi + 4]
006c3e16 xor ecx, eax
006c3e18 and ecx, 0x7fffffff
006c3e1e xor ecx, eax
006c3e20 mov eax, ecx
006c3e22 shr ecx, 1
006c3e24 and eax, 1
006c3e27 mov eax, dword ptr [eax*4 + 0xb49b28]
006c3e2e xor eax, dword ptr [edx - 0x390]
006c3e34 xor eax, ecx
006c3e36 mov dword ptr [edi], eax
006c3e38 mov edi, edx
006c3e3a mov eax, dword ptr [edx]
006c3e3c cmp edi, 0xc007cc
006c3e42 jl 0x6c3e10
006c3e44 mov ecx, dword ptr [0xbffe10]
006c3e4a xor ecx, dword ptr [0xc007cc]
006c3e50 and ecx, 0x7fffffff
006c3e56 xor ecx, dword ptr [0xc007cc]
006c3e5c mov eax, ecx
006c3e5e shr ecx, 1
006c3e60 and eax, 1
006c3e63 pop edi
006c3e64 pop esi
006c3e65 xor ecx, dword ptr [eax*4 + 0xb49b28]
006c3e6c xor ecx, dword ptr [0xc00440]
006c3e72 xor eax, eax
006c3e74 mov dword ptr [0xc007cc], ecx
006c3e7a mov ecx, dword ptr [eax*4 + 0xbffe10]
006c3e81 inc eax
006c3e82 mov dword ptr [0xbc5304], eax
006c3e87 mov eax, ecx
006c3e89 shr eax, 0xb
006c3e8c xor ecx, eax
006c3e8e mov eax, ecx
006c3e90 and eax, 0xff3a58ad
006c3e95 shl eax, 7
006c3e98 xor ecx, eax
006c3e9a mov eax, ecx
006c3e9c and eax, 0xffffdf8c
006c3ea1 shl eax, 0xf
006c3ea4 xor ecx, eax
006c3ea6 mov eax, ecx
006c3ea8 shr eax, 0x12
006c3eab xor eax, ecx
006c3ead ret 
006c3eae int3 
006c3eaf int3 
