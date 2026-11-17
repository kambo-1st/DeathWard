005f072a add esi, -0x1e
005f072d cmp esi, 0xcf
005f0733 ja 0x5f07ec
005f0739 movzx eax, byte ptr [esi + 0x5f20dc]
005f0740 jmp dword ptr [eax*4 + 0x5f20b0]
005f0747 mov dword ptr [edi + 0xcc0], 0
005f0751 jmp 0x5f07ec
005f0756 mov dword ptr [edi + 0xcc0], 1
005f0760 jmp 0x5f07ec
005f0765 mov dword ptr [edi + 0xcc0], 3
005f076f jmp 0x5f07ec
005f0771 mov dword ptr [edi + 0xcc0], 4
005f077b jmp 0x5f07ec
005f077d mov dword ptr [edi + 0xcc0], 5
005f0787 jmp 0x5f07ec
005f0789 mov dword ptr [edi + 0xcc0], 6
005f0793 jmp 0x5f07ec
005f0795 mov dword ptr [edi + 0xcc0], 2
005f079f jmp 0x5f07ec
005f07a1 mov ecx, edi
005f07a3 call 0x427940
005f07a8 cmp word ptr [eax + 0x18c], 0
005f07b0 jl 0x5f07cb
005f07b2 mov ecx, edi
005f07b4 call 0x427940
005f07b9 movsx eax, word ptr [eax + 0x18c]
005f07c0 add eax, 7
005f07c3 mov dword ptr [edi + 0xcc0], eax
005f07c9 jmp 0x5f07ec
005f07cb or eax, 0xffffffff
005f07ce mov dword ptr [edi + 0xcc0], eax
005f07d4 jmp 0x5f07ec
005f07d6 mov dword ptr [edi + 0xcc0], 8
005f07e0 jmp 0x5f07ec
005f07e2 mov dword ptr [edi + 0xcc0], 0xa
