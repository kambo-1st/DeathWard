00786be0 push esi
00786be1 mov esi, ecx
00786be3 push edi
00786be4 cmp byte ptr [esi + 0x1461], 0
00786beb jne 0x786c14
00786bed mov eax, dword ptr [esi + 0x1454]
00786bf3 mov edx, dword ptr [esi + 0x1458]
00786bf9 cmp eax, edx
00786bfb je 0x786c14
00786bfd nop dword ptr [eax]
00786c00 mov ecx, dword ptr [eax]
00786c02 cmp dword ptr [ecx], 2
00786c05 jne 0x786c0d
00786c07 cmp dword ptr [ecx + 4], 0x45
00786c0b je 0x786c34
00786c0d add eax, 0xc
00786c10 cmp eax, edx
00786c12 jne 0x786c00
00786c14 push 0x1f1
00786c19 lea ecx, [esi + 0x1450]
00786c1f call 0x88b570
00786c24 test al, al
00786c26 jne 0x786c34
00786c28 cmp dword ptr [esi + 0x130c], 0x23
00786c2f je 0x786c34
00786c31 pop edi
00786c32 pop esi
00786c33 ret 
00786c34 pop edi
00786c35 mov al, 1
00786c37 pop esi
00786c38 ret 
