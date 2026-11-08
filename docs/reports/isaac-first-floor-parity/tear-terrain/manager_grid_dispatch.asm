004157ab mov esi, dword ptr [esp + 0x18]
004157af xor edi, edi
004157b1 cmp dword ptr [esi + 0x4c], edi
004157b4 jbe 0x4157dd
004157b6 mov eax, dword ptr [esi + 0x44]
004157b9 mov ecx, dword ptr [eax + edi*4]
004157bc mov eax, dword ptr [ecx + 0x28]
004157bf cmp eax, 7
004157c2 je 0x4157d7
004157c4 push 0
004157c6 cmp eax, 1
004157c9 jne 0x4157d2
004157cb call 0x683850
004157d0 jmp 0x4157d7
004157d2 call 0x682280
004157d7 inc edi
004157d8 cmp edi, dword ptr [esi + 0x4c]
004157db jb 0x4157b6
004157dd pop edi
004157de pop esi
004157df mov esp, ebp
004157e1 pop ebp
004157e2 ret 
