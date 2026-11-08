0066e326 mov edx, 0xb48824
0066e32b cmovne ecx, eax
0066e32e nop 
0066e330 mov al, byte ptr [ecx]
0066e332 cmp al, byte ptr [edx]
0066e334 mov byte ptr [ebp - 0x10209], al
0066e33a mov eax, dword ptr [esi]
0066e33c jne 0x66e36a
0066e33e cmp byte ptr [ebp - 0x10209], 0
0066e345 je 0x66e366
0066e347 mov al, byte ptr [ecx + 1]
0066e34a cmp al, byte ptr [edx + 1]
0066e34d mov byte ptr [ebp - 0x10209], al
0066e353 mov eax, dword ptr [esi]
0066e355 jne 0x66e36a
0066e357 add ecx, 2
0066e35a add edx, 2
0066e35d cmp byte ptr [ebp - 0x10209], 0
0066e364 jne 0x66e330
0066e366 xor ecx, ecx
0066e368 jmp 0x66e36f
0066e36a sbb ecx, ecx
0066e36c or ecx, 1
0066e36f test ecx, ecx
0066e371 mov ecx, 0xbfd630
0066e376 jne 0x66e395
0066e378 mov eax, dword ptr [esi + 4]
0066e37b test eax, eax
0066e37d cmovne ecx, eax
0066e380 push ecx
0066e381 call dword ptr [0xa064dc]
0066e387 fstp dword ptr [ebp - 0x101d0]
0066e38d add esp, 4
0066e390 jmp 0x66dfb1
0066e395 test eax, eax
0066e397 mov edx, 0xb48834
0066e39c cmovne ecx, eax
0066e39f nop 
0066e3a0 mov al, byte ptr [ecx]
0066e3a2 cmp al, byte ptr [edx]
0066e3a4 mov byte ptr [ebp - 0x10209], al
0066e3aa mov eax, dword ptr [esi]
0066e3ac jne 0x66e3da
0066e3ae cmp byte ptr [ebp - 0x10209], 0
0066e3b5 je 0x66e3d6
0066e3b7 mov al, byte ptr [ecx + 1]
0066e3ba cmp al, byte ptr [edx + 1]
0066e3bd mov byte ptr [ebp - 0x10209], al
0066e3c3 mov eax, dword ptr [esi]
0066e3c5 jne 0x66e3da
0066e3c7 add ecx, 2
0066e3ca add edx, 2
0066e3cd cmp byte ptr [ebp - 0x10209], 0
0066e3d4 jne 0x66e3a0
0066e3d6 xor ecx, ecx
0066e3d8 jmp 0x66e3df
0066e3da sbb ecx, ecx
0066e3dc or ecx, 1
0066e3df test ecx, ecx
0066e3e1 mov ecx, 0xbfd630
0066e3e6 jne 0x66e405
0066e3e8 mov eax, dword ptr [esi + 4]
0066e3eb test eax, eax
0066e3ed cmovne ecx, eax
0066e3f0 push ecx
0066e3f1 call dword ptr [0xa064dc]
0066e3f7 fstp dword ptr [ebp - 0x101cc]
0066e3fd add esp, 4
0066e400 jmp 0x66dfb1
0066e405 test eax, eax
0066e407 mov edx, 0xb4884c
0066e40c cmovne ecx, eax
0066e40f nop 
0066e410 mov al, byte ptr [ecx]
0066e412 cmp al, byte ptr [edx]
0066e414 mov byte ptr [ebp - 0x10209], al
0066e41a mov eax, dword ptr [esi]
0066e41c jne 0x66e44a
0066e41e cmp byte ptr [ebp - 0x10209], 0
0066e425 je 0x66e446
0066e427 mov al, byte ptr [ecx + 1]
0066e42a cmp al, byte ptr [edx + 1]
0066e42d mov byte ptr [ebp - 0x10209], al
0066e433 mov eax, dword ptr [esi]
0066e435 jne 0x66e44a
0066e437 add ecx, 2
0066e43a add edx, 2
0066e43d cmp byte ptr [ebp - 0x10209], 0
0066e444 jne 0x66e410
0066e446 xor ecx, ecx
0066e448 jmp 0x66e44f
0066e44a sbb ecx, ecx
0066e44c or ecx, 1
0066e44f test ecx, ecx
0066e451 mov ecx, 0xbfd630
0066e456 jne 0x66e475
0066e458 mov eax, dword ptr [esi + 4]
0066e45b test eax, eax
0066e45d cmovne ecx, eax
0066e460 push ecx
0066e461 call dword ptr [0xa064dc]
0066e467 fstp dword ptr [ebp - 0x101c8]
0066e46d add esp, 4
