00609a35 mov eax, dword ptr [edi + 0x2c]
00609a38 cmp eax, 0x79
00609a3b jne 0x609a60
00609a3d mov eax, dword ptr [edi + 0xcd4]
00609a43 add eax, 0xa
00609a46 mov dword ptr [edi + 0xcd4], eax
00609a4c cmp eax, 0x1e
00609a4f jl 0x609a90
00609a51 mov eax, dword ptr [edi + 0x360]
00609a57 dec word ptr [eax + 0x12d4]
00609a5e jmp 0x609a89
00609a60 cmp eax, 0x80
00609a65 je 0x609a89
00609a67 cmp eax, 0xe5
00609a6c je 0x609a89
00609a6e cmp eax, 0xea
00609a73 jne 0x609a90
00609a75 mov eax, dword ptr [edi + 0xcd4]
00609a7b add eax, 3
00609a7e mov dword ptr [edi + 0xcd4], eax
00609a84 cmp eax, 6
00609a87 jl 0x609a90
00609a89 mov eax, dword ptr [edi]
00609a8b mov ecx, edi
00609a8d call dword ptr [eax + 0x24]
00609a90 mov eax, dword ptr [edi + 0x2c]
00609a93 cmp eax, 0xe4
00609a98 je 0x609aec
00609a9a cmp eax, 0xee
00609a9f je 0x609aec
00609aa1 cmp eax, 0xc9
00609aa6 je 0x609ab6
00609aa8 cmp eax, 0xd8
00609aad je 0x609ab6
00609aaf cmp eax, 0xd9
00609ab4 jne 0x609b16
00609ab6 push esi
00609ab7 lea ecx, [esp + 0xb8]
00609abe call 0x4229a0
00609ac3 mov eax, dword ptr [edi]
00609ac5 lea ecx, [esp + 0xb4]
00609acc push 1
00609ace push ecx
00609acf push 0
00609ad1 push 0
00609ad3 push ecx
00609ad4 mov ecx, edi
00609ad6 mov dword ptr [esp], 0x40600000
00609add call dword ptr [eax + 0x20]
00609ae0 mov byte ptr [esi + 0x16b], 1
00609ae7 jmp 0x609cf4
00609aec push esi
00609aed lea ecx, [esp + 0xb8]
00609af4 call 0x4229a0
00609af9 mov eax, dword ptr [edi]
00609afb lea ecx, [esp + 0xb4]
00609b02 push 1
00609b04 push ecx
00609b05 push 0
00609b07 push 0
00609b09 push ecx
00609b0a mov ecx, edi
00609b0c mov dword ptr [esp], 0x3f800000
00609b13 call dword ptr [eax + 0x20]
00609b16 mov byte ptr [esi + 0x16b], 1
00609b1d jmp 0x609cf4
