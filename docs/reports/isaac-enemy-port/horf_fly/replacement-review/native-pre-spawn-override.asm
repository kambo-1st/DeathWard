007aacfa push dword ptr [ebp - 0x5c]
007aacfd mov eax, dword ptr [ebx]
007aacff lea esi, [ebx + 6]
007aad02 push dword ptr [ebp + 0xc]
007aad05 lea edi, [ebx + 4]
007aad08 mov dword ptr [ebp - 0x50], eax
007aad0b push esi
007aad0c push edi
007aad0d lea eax, [ebp - 0x50]
007aad10 mov dword ptr [ebp - 0x2c], esi
007aad13 push eax
007aad14 mov dword ptr [ebp - 0x38], edi
007aad17 call 0x802f30
007aad1c mov byte ptr [ebp - 0x2f], al
007aad1f mov ecx, 0x12c
007aad24 mov eax, dword ptr [ebp - 0x50]
007aad27 mov dword ptr [ebx], eax
007aad29 cmp eax, 5
007aad2c jne 0x7aad83
007aad2e mov eax, 0x12d
007aad33 cmp word ptr [edi], ax
007aad36 jne 0x7aad83
007aad38 mov word ptr [edi], cx
007aad3b lea ecx, [ebp - 0x4c]
007aad3e call 0x7a7e20
007aad43 push 1
007aad45 push 0
007aad47 push 1
007aad49 mov esi, eax
007aad4b push 0
007aad4d push esi
007aad4e call 0x701da0
007aad53 movq xmm0, qword ptr [0xa08c44]
007aad5b mov ecx, eax
007aad5d mov eax, dword ptr [0xa08c4c]
007aad62 push 1
007aad64 push 1
007aad66 push 0
007aad68 mov dword ptr [ebp - 0xc], eax
007aad6b lea eax, [ebp - 0x18]
007aad6e push ecx
007aad6f push eax
007aad70 mov dword ptr [ebp - 0x18], esi
007aad73 movq qword ptr [ebp - 0x14], xmm0
007aad78 call 0x801c10
007aad7d lea esi, [ebx + 6]
007aad80 mov word ptr [esi], ax
007aad83 cmp byte ptr [ebp - 0x2f], 0
007aad87 jne 0x7abbcb
007aad8d mov eax, dword ptr [ebx]
007aad8f mov edx, 0xa
007aad94 cmp eax, 5
007aad97 jne 0x7ab151
