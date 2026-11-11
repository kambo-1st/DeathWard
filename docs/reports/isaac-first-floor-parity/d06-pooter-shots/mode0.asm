006a3090 mov ecx, dword ptr [ebp - 0x4c]
006a3093 mov eax, dword ptr [ecx + esi*4]
006a3096 mov dword ptr [eax + 0x364], 0xc0400000
006a30a0 mov eax, dword ptr [ecx + esi*4]
006a30a3 inc esi
006a30a4 mov dword ptr [eax + 0x368], 0x3dcccccd
006a30ae cmp esi, edx
006a30b0 jb 0x6a3090
