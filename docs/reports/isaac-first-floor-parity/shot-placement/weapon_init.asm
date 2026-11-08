00942db0 push ebp
00942db1 mov ebp, esp
00942db3 push esi
00942db4 mov esi, ecx
00942db6 mov eax, dword ptr [esi]
00942db8 call dword ptr [eax + 0x10]
00942dbb mov eax, dword ptr [ebp + 0xc]
00942dbe mov dword ptr [esi + 4], eax
00942dc1 mov eax, dword ptr [ebp + 8]
00942dc4 mov dword ptr [esi + 0x2c], eax
00942dc7 pop esi
00942dc8 pop ebp
00942dc9 ret 8
