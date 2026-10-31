004f5ab2 cmp dword ptr [esi + 0x28], 0xd
004f5ab6 jne 0x4f5b1e
004f5ab8 call 0x6c3d90
004f5abd xor edx, edx
004f5abf mov ecx, 0x3e8
004f5ac4 div ecx
004f5ac6 test edx, edx
004f5ac8 jne 0x4f5b1e
004f5aca mov eax, dword ptr [0xbfd65c]
004f5acf mov edi, dword ptr [eax + 0x18190]
004f5ad5 lea eax, [esi + 0x294]
004f5adb push eax
004f5adc mov ecx, edi
004f5ade call 0x7ce950
004f5ae3 test eax, eax
004f5ae5 js 0x4f5b1e
004f5ae7 cmp eax, 0x1c0
004f5aec jge 0x4f5b1e
004f5aee mov ecx, dword ptr [edi + eax*4 + 0x24]
004f5af2 test ecx, ecx
004f5af4 je 0x4f5b1e
004f5af6 cmp dword ptr [ecx + 4], 0xe
004f5afa jne 0x4f5b1e
004f5afc mov eax, dword ptr [ecx]
004f5afe push 1
004f5b00 call dword ptr [eax + 0x10]
004f5b03 push -1
004f5b05 push 0
004f5b07 push 0
004f5b09 push 0xe
004f5b0b mov ecx, esi
004f5b0d call 0x697c60
004f5b12 mov eax, dword ptr [esi + 0x2dc]
004f5b18 mov dword ptr [esi + 0x2d8], eax
