006d0db2 mov ecx, dword ptr [ebp + 0x10]
006d0db5 push dword ptr [ebp + 0x20]
006d0db8 push dword ptr [ebp + 0x1c]
006d0dbb mov eax, dword ptr [ecx]
006d0dbd mov dword ptr [edi + 0x294], eax
006d0dc3 mov eax, dword ptr [ecx + 4]
006d0dc6 mov ecx, dword ptr [ebp + 0x14]
006d0dc9 mov dword ptr [edi + 0x298], eax
006d0dcf push ebx
006d0dd0 push dword ptr [esp + 0x28]
006d0dd4 mov eax, dword ptr [ecx]
006d0dd6 mov dword ptr [edi + 0x2b8], eax
006d0ddc mov eax, dword ptr [ecx + 4]
006d0ddf mov ecx, edi
006d0de1 mov dword ptr [edi + 0x2bc], eax
006d0de7 mov eax, dword ptr [edi]
006d0de9 call dword ptr [eax + 4]
