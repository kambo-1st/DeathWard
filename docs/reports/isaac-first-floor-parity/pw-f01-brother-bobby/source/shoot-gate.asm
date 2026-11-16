005f6486 lea ecx, [ebp - 0x34]
005f6489 call 0x659400
005f648e push 0
005f6490 lea eax, [ebp - 0x18]
005f6493 mov ecx, esi
005f6495 push eax
005f6496 lea eax, [ebp - 0x34]
005f6499 push eax
005f649a call 0x5f5ed0
005f649f mov ecx, dword ptr [ebp - 0x18]
005f64a2 test ecx, ecx
005f64a4 mov byte ptr [ebp - 0x20], al
005f64a7 sete al
005f64aa cmp dword ptr [esi + 0xc9c], 0
005f64b1 mov byte ptr [esi + 0x13c], al
005f64b7 jg 0x5f6662
005f64bd mov eax, dword ptr [esi + 0x2c]
005f64c0 cmp eax, 0x61
005f64c3 jne 0x5f6550
005f64c9 xor edi, edi
