004f64f5 push ecx
004f64f6 lea eax, [esp + 0x60]
004f64fa mov dword ptr [esp], 0
004f6501 push eax
004f6502 mov ecx, esi
004f6504 call 0x695a30
004f6509 mov ecx, dword ptr [eax]
004f650b mov dword ptr [esi + 0x28c], ecx
004f6511 mov eax, dword ptr [eax + 4]
004f6514 mov dword ptr [esi + 0x290], eax
