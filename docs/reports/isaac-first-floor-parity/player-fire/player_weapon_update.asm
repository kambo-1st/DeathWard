007459aa mov ecx, 4
007459af mov dword ptr [ebp - 0x164], ecx
007459b5 mov eax, dword ptr [esi]
007459b7 test eax, eax
007459b9 je 0x7459e6
007459bb mov esi, dword ptr [eax]
007459bd mov ecx, edi
007459bf push 0
007459c1 push 0x4000
007459c6 call 0x4122f0
007459cb mov ecx, dword ptr [ebp - 0x14c]
007459d1 movzx eax, al
007459d4 push eax
007459d5 mov ecx, dword ptr [ecx]
007459d7 call dword ptr [esi + 8]
007459da mov ecx, dword ptr [ebp - 0x164]
007459e0 mov esi, dword ptr [ebp - 0x14c]
007459e6 add esi, 4
007459e9 sub ecx, 1
007459ec mov dword ptr [ebp - 0x14c], esi
007459f2 mov dword ptr [ebp - 0x164], ecx
007459f8 jne 0x7459b5
