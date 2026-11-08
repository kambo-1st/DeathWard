007ff160 push ebp
007ff161 mov ebp, esp
007ff163 push -1
007ff165 push 0x9fb3c0
007ff16a mov eax, dword ptr fs:[0]
007ff170 push eax
007ff171 sub esp, 0x1c
007ff174 push ebx
007ff175 push esi
007ff176 push edi
007ff177 mov eax, dword ptr [0xbaa3b4]
007ff17c xor eax, ebp
007ff17e push eax
007ff17f lea eax, [ebp - 0xc]
007ff182 mov dword ptr fs:[0], eax
007ff188 mov dword ptr [ebp - 0x10], esp
007ff18b mov edx, dword ptr [0xbfd674]
007ff191 mov esi, dword ptr [ebp + 8]
007ff194 mov dword ptr [ebp - 0x24], 0x28
007ff19b mov eax, dword ptr [edx + 0x10]
007ff19e mov ecx, dword ptr [esi + 0x2c]
007ff1a1 mov dword ptr [ebp - 0x28], eax
007ff1a4 mov eax, dword ptr [edx]
007ff1a6 mov dword ptr [ebp - 0x20], ecx
007ff1a9 test dword ptr [eax + 4], 0x100
007ff1b0 je 0x7ff1db
007ff1b2 push esi
007ff1b3 push ecx
007ff1b4 lea eax, [ebp - 0x18]
007ff1b7 mov dword ptr [ebp - 4], 0
007ff1be push eax
007ff1bf lea ecx, [ebp - 0x28]
007ff1c2 call 0x80fca0
007ff1c7 push dword ptr [ebp - 0x14]
007ff1ca push 0xfff0b9d8
007ff1cf push dword ptr [ebp - 0x18]
007ff1d2 call dword ptr [0xa06248]
007ff1d8 add esp, 0xc
007ff1db mov ecx, dword ptr [ebp - 0xc]
007ff1de mov dword ptr fs:[0], ecx
007ff1e5 pop ecx
007ff1e6 pop edi
007ff1e7 pop esi
007ff1e8 pop ebx
007ff1e9 mov esp, ebp
007ff1eb pop ebp
