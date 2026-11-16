007d03e0 push ebp
007d03e1 mov ebp, esp
007d03e3 and esp, 0xfffffff8
007d03e6 sub esp, 0xc
007d03e9 push ebx
007d03ea mov ebx, ecx
007d03ec push esi
007d03ed push edi
007d03ee mov eax, dword ptr [ebx + 4]
007d03f1 cmp word ptr [eax + 0xac], 0
007d03f9 jge 0x7d0400
007d03fb call 0x7cf800
007d0400 mov eax, dword ptr [ebx + 0x6f74]
007d0406 mov dword ptr [esp + 0x14], eax
007d040a test eax, eax
007d040c je 0x7d0433
007d040e mov edx, dword ptr [ebx + 0x6f70]
007d0414 mov ecx, edx
007d0416 mov eax, dword ptr [ebx + 0x6f6c]
007d041c dec eax
007d041d shr ecx, 1
007d041f and ecx, eax
007d0421 mov eax, dword ptr [ebx + 0x6f68]
007d0427 and edx, 1
007d042a mov eax, dword ptr [eax + ecx*4]
007d042d mov eax, dword ptr [eax + edx*8 + 4]
007d0431 jmp 0x7d043d
007d0433 mov eax, dword ptr [ebx + 4]
007d0436 movsx eax, word ptr [eax + 0xac]
007d043d push dword ptr [ebp + 0x14]
007d0440 mov esi, dword ptr [ebp + 0xc]
007d0443 mov ecx, ebx
007d0445 mov edi, dword ptr [ebp + 8]
007d0448 push esi
007d0449 push edi
007d044a push eax
007d044b mov dword ptr [esp + 0x20], eax
007d044f call 0x7d04a0
007d0454 push dword ptr [esp + 0x10]
007d0458 mov ecx, ebx
007d045a push dword ptr [esi]
007d045c push dword ptr [edi]
007d045e call 0x7d0950
007d0463 mov esi, dword ptr [ebp + 0x10]
007d0466 mov ecx, ebx
007d0468 mov edi, dword ptr [esp + 0x10]
007d046c push eax
007d046d push edi
007d046e mov dword ptr [esi], eax
007d0470 call 0x7d16f0
007d0475 cmp dword ptr [esp + 0x14], 0
007d047a mov dword ptr [esi], eax
007d047c mov eax, edi
007d047e jne 0x7d0495
007d0480 mov ecx, dword ptr [ebx + 4]
007d0483 inc word ptr [ecx + 0xac]
007d048a mov ecx, dword ptr [ebx + 4]
007d048d and word ptr [ecx + 0xac], 7
007d0495 pop edi
007d0496 pop esi
007d0497 pop ebx
007d0498 mov esp, ebp
007d049a pop ebp
