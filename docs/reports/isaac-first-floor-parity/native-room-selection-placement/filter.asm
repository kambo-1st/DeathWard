007e78a4 mov eax, dword ptr [ebp + 0x10]
007e78a7 add esi, ecx
007e78a9 cmp dword ptr [esi + 8], eax
007e78ac jne 0x7e796b
007e78b2 mov eax, dword ptr [ebp + 0x14]
007e78b5 cmp eax, 0xd
007e78b8 je 0x7e78c3
007e78ba cmp eax, dword ptr [esi + 0x48]
007e78bd jne 0x7e796b
007e78c3 mov eax, dword ptr [esi + 0xc]
007e78c6 cmp eax, dword ptr [ebp + 0x18]
007e78c9 jb 0x7e796b
007e78cf cmp eax, dword ptr [ebp + 0x1c]
007e78d2 ja 0x7e796b
007e78d8 mov eax, dword ptr [esi + 0x2c]
007e78db cmp eax, dword ptr [ebp + 0x20]
007e78de jl 0x7e796b
007e78e4 cmp eax, dword ptr [ebp + 0x24]
007e78e7 jg 0x7e796b
007e78ed mov edx, dword ptr [ebp + 0x28]
007e78f0 mov eax, dword ptr [edx]
007e78f2 and eax, dword ptr [esi + 0x38]
007e78f5 mov dword ptr [ebp - 0x18], eax
007e78f8 lea eax, [ebp - 0x18]
007e78fb mov eax, dword ptr [eax]
007e78fd cmp eax, dword ptr [edx]
007e78ff jne 0x7e796b
007e7901 mov eax, dword ptr [ebp + 0x2c]
007e7904 cmp eax, -1
007e7907 je 0x7e790e
007e7909 cmp dword ptr [esi + 0x10], eax
007e790c jne 0x7e796b
