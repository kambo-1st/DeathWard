007a7bb0 push ebp
007a7bb1 mov ebp, esp
007a7bb3 and esp, 0xfffffff8
007a7bb6 sub esp, 0x10
007a7bb9 push esi
007a7bba mov esi, ecx
007a7bbc push edi
007a7bbd mov ecx, dword ptr [esi + 4]
007a7bc0 cmp ecx, dword ptr [esi + 8]
007a7bc3 je 0x7a7bd8
007a7bc5 mov eax, dword ptr [ebp + 8]
007a7bc8 mov edx, dword ptr [eax]
007a7bca mov eax, dword ptr [eax + 4]
007a7bcd mov dword ptr [ecx], edx
007a7bcf mov dword ptr [ecx + 4], eax
007a7bd2 add dword ptr [esi + 4], 8
007a7bd6 jmp 0x7a7be3
007a7bd8 push dword ptr [ebp + 8]
007a7bdb push ecx
007a7bdc mov ecx, esi
007a7bde call 0x71f570
007a7be3 mov eax, dword ptr [esi + 0xc]
007a7be6 mov ecx, dword ptr [esi + 0x10]
007a7be9 mov edx, dword ptr [esi + 4]
007a7bec mov edi, dword ptr [esi]
007a7bee mov esi, edx
007a7bf0 sub esi, edi
007a7bf2 mov dword ptr [esp + 8], eax
007a7bf6 sar esi, 3
007a7bf9 mov dword ptr [esp + 0xc], ecx
007a7bfd cmp esi, 2
007a7c00 jl 0x7a7c28
007a7c02 mov eax, dword ptr [edx - 8]
007a7c05 mov edx, dword ptr [edx - 4]
007a7c08 mov dword ptr [esp + 0x10], eax
007a7c0c lea eax, [esp + 8]
007a7c10 push eax
007a7c11 lea eax, [esp + 0x14]
007a7c15 mov dword ptr [esp + 0x18], edx
007a7c19 push eax
007a7c1a push ecx
007a7c1b lea edx, [esi - 1]
007a7c1e mov ecx, edi
007a7c20 call 0x7a7c60
007a7c25 add esp, 0xc
007a7c28 pop edi
007a7c29 pop esi
007a7c2a mov esp, ebp
007a7c2c pop ebp
007a7c2d ret 4
