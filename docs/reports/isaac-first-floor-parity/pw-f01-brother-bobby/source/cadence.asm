005f6350 mov eax, dword ptr [esi + 0xc9c]
005f6356 test eax, eax
005f6358 jle 0x5f6361
005f635a dec eax
005f635b mov dword ptr [esi + 0xc9c], eax
005f6361 push 0x8d
005f6366 call 0x78d4c0
005f636b test eax, eax
005f636d jle 0x5f6380
005f636f mov eax, dword ptr [esi + 0xc9c]
005f6375 test eax, eax
005f6377 jle 0x5f6380
005f6379 dec eax
005f637a mov dword ptr [esi + 0xc9c], eax
005f6380 mov ecx, dword ptr [esi + 0x2c]
005f6383 mov edi, 0x16
005f6388 cmp ecx, 0x4a
005f638b mov eax, 0xb
005f6390 cmove edi, eax
005f6393 cmp ecx, 1
005f6396 je 0x5f639d
005f6398 cmp ecx, 8
005f639b jne 0x5f63a2
005f639d mov edi, 0x10
005f63a2 cmp ecx, 0x51
005f63a5 mov eax, 0x2c
005f63aa cmove edi, eax
005f63ad mov eax, dword ptr [esi + 0x160]
005f63b3 and eax, 0x100
005f63b8 mov dword ptr [ebp - 0x14], edi
005f63bb or eax, 0
005f63be je 0x5f63d6
005f63c0 movd xmm0, edi
005f63c4 cvtdq2ps xmm0, xmm0
005f63c7 mulss xmm0, dword ptr [0xb6a6c8]
005f63cf cvttss2si edi, xmm0
005f63d3 mov dword ptr [ebp - 0x14], edi
