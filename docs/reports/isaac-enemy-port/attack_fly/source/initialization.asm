004f4e30 push ebp
004f4e31 mov ebp, esp
004f4e33 and esp, 0xfffffff8
004f4e36 sub esp, 0x1e0
004f4e3c mov eax, dword ptr [0xbaa3b4]
004f4e41 xor eax, esp
004f4e43 mov dword ptr [esp + 0x1dc], eax
004f4e4a push esi
004f4e4b mov esi, ecx
004f4e4d push edi
004f4e4e mov dword ptr [esp + 0x24], esi
004f4e52 cmp dword ptr [esi + 0x28], 0x3d
004f4e56 jne 0x4f4e9c
004f4e58 mov eax, dword ptr [esi + 0x2c]
004f4e5b cmp eax, 5
004f4e5e je 0x4f4e83
004f4e60 cmp eax, 6
004f4e63 je 0x4f4e83
004f4e65 cmp eax, 4
004f4e68 jne 0x4f4e9c
004f4e6a call 0x4ca880
004f4e6f pop edi
004f4e70 pop esi
004f4e71 mov ecx, dword ptr [esp + 0x1dc]
004f4e78 xor ecx, esp
004f4e7a call 0x9eacd7
004f4e7f mov esp, ebp
004f4e81 pop ebp
004f4e82 ret 
004f4e83 call 0x5386a0
004f4e88 pop edi
004f4e89 pop esi
004f4e8a mov ecx, dword ptr [esp + 0x1dc]
004f4e91 xor ecx, esp
004f4e93 call 0x9eacd7
004f4e98 mov esp, ebp
004f4e9a pop ebp
004f4e9b ret 
004f4e9c cmp dword ptr [esi + 0xab4], 0
004f4ea3 jne 0x4f4ff6
004f4ea9 mov dword ptr [esi + 0x17c], 3
004f4eb3 movss xmm0, dword ptr [0xc02fec]
004f4ebb movss dword ptr [esi + 0xb08], xmm0
004f4ec3 movss xmm0, dword ptr [0xc02ff0]
004f4ecb movss dword ptr [esi + 0xb0c], xmm0
004f4ed3 mov eax, dword ptr [esi + 0x28]
004f4ed6 mov dword ptr [esi + 0xab4], 3
004f4ee0 cmp eax, 0x3d
004f4ee3 jne 0x4f4f76
004f4ee9 mov eax, dword ptr [esi + 0x2c]
004f4eec cmp eax, 1
004f4eef jne 0x4f4f3b
004f4ef1 xorps xmm0, xmm0
004f4ef4 mov dword ptr [esp + 0x84], 0xbe48c8ca
