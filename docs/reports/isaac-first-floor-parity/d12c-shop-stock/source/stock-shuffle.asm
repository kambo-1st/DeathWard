005b6400 push ebp
005b6401 mov ebp, esp
005b6403 push ecx
005b6404 push ebx
005b6405 push esi
005b6406 mov esi, dword ptr [ebp + 8]
005b6409 mov ebx, ecx
005b640b push edi
005b640c mov edi, dword ptr [ebp + 0xc]
005b640f sub edi, esi
005b6411 sar edi, 2
005b6414 dec edi
005b6415 test edi, edi
005b6417 jle 0x5b6486
005b6419 lea eax, [edi + 1]
005b641c mov dword ptr [ebp - 4], eax
005b641f nop
005b6420 mov eax, dword ptr [ebx]
005b6422 test eax, eax
005b6424 jne 0x5b643f
005b6426 push 0xb4d6c4
005b642b push 3
005b642d call 0x95e330
005b6432 mov eax, dword ptr [ebx]
005b6434 add esp, 8
005b6437 mov esi, dword ptr [ebp + 8]
005b643a test eax, eax
005b643c jne 0x5b643f
005b643e int3
005b643f mov ecx, dword ptr [ebx + 4]
005b6442 mov edx, eax
005b6444 shr edx, cl
005b6446 mov ecx, dword ptr [ebx + 8]
005b6449 xor edx, eax
005b644b mov eax, edx
005b644d shl eax, cl
005b644f mov ecx, dword ptr [ebx + 0xc]
005b6452 xor eax, edx
005b6454 mov edx, eax
005b6456 shr edx, cl
005b6458 mov ecx, dword ptr [ebp - 4]
005b645b xor edx, eax
005b645d mov dword ptr [ebx], edx
005b645f test ecx, ecx
005b6461 jne 0x5b6467
005b6463 xor edx, edx
005b6465 jmp 0x5b646d
005b6467 mov eax, edx
005b6469 xor edx, edx
005b646b div ecx
005b646d mov ecx, dword ptr [esi + edi*4]
005b6470 mov eax, dword ptr [esi + edx*4]
005b6473 dec dword ptr [ebp - 4]
005b6476 mov dword ptr [esi + edi*4], eax
005b6479 dec edi
005b647a mov dword ptr [esi + edx*4], ecx
005b647d test edi, edi
005b647f jle 0x5b6486
005b6481 mov esi, dword ptr [ebp + 8]
005b6484 jmp 0x5b6420
005b6486 pop edi
005b6487 pop esi
005b6488 pop ebx
005b6489 mov esp, ebp
005b648b pop ebp
005b648c ret
