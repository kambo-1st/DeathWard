005b8f80 cmp ecx, 0x48
005b8f83 jne 0x5b8fba
005b8f85 mov byte ptr [esi + 0x169], dl
005b8f8b mov dword ptr [esi + 0x3ac], 0xf0
005b8f95 movss xmm0, dword ptr [0xc02fec]
005b8f9d movss dword ptr [esi + 0x28c], xmm0
005b8fa5 movss xmm0, dword ptr [0xc02ff0]
005b8fad movss dword ptr [esi + 0x290], xmm0
005b8fb5 jmp 0x5ba1ff
