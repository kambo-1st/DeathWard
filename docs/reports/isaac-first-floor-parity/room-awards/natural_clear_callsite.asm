007ae343 test byte ptr [ecx + 0x44], 1
007ae347 jne 0x7ae3c0
007ae349 mov dword ptr [esi + 0x11ec], 0
007ae353 or dword ptr [ecx + 0x44], 1
007ae357 mov eax, dword ptr [esi + 4]
007ae35a inc word ptr [eax + 0x4a]
007ae35e mov ecx, dword ptr [esi + 4]
007ae361 movzx eax, word ptr [ecx + 0x4a]
007ae365 push eax
007ae366 mov eax, dword ptr [ecx + 0x10]
007ae369 lea ecx, [edi + 0x1c32b8]
007ae36f push dword ptr [eax + 0x48]
007ae372 push dword ptr [esi + 8]
007ae375 call 0x93aa40
007ae37a mov ecx, edi
007ae37c call 0x6cba40
007ae381 test al, al
007ae383 je 0x7ae38b
007ae385 cmp dword ptr [esi + 8], 1
007ae389 je 0x7ae396
007ae38b lea ecx, [edi + 0x1ba40]
007ae391 call 0x91aa70
007ae396 mov ecx, esi
007ae398 call 0x7b8b10
