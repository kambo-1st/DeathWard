004d1fd0 push ebp
004d1fd1 mov ebp, esp
004d1fd3 sub esp, 0xc
004d1fd6 cmp byte ptr [ebp + 8], 0
004d1fda je 0x4d2035
004d1fdc lea eax, [ebp - 0xc]
004d1fdf cmp eax, ecx
004d1fe1 je 0x4d203a
004d1fe3 mov eax, dword ptr [ecx]
004d1fe5 mov edx, dword ptr [ecx + 8]
004d1fe8 mov dword ptr [ecx], 0
004d1fee mov dword ptr [ecx + 4], 0
004d1ff5 mov dword ptr [ecx + 8], 0
004d1ffc test eax, eax
004d1ffe je 0x4d203a
004d2000 sub edx, eax
004d2002 and edx, 0xfffffffc
004d2005 cmp edx, 0x1000
004d200b jb 0x4d201f
004d200d mov ecx, dword ptr [eax - 4]
004d2010 add edx, 0x23
004d2013 sub eax, ecx
004d2015 add eax, -4
004d2018 cmp eax, 0x1f
004d201b ja 0x4d202f
004d201d mov eax, ecx
004d201f push edx
004d2020 push eax
004d2021 call 0x9eb08e
004d2026 add esp, 8
004d2029 mov esp, ebp
004d202b pop ebp
004d202c ret 4
004d202f call dword ptr [0xa065ac]
004d2035 mov eax, dword ptr [ecx]
004d2037 mov dword ptr [ecx + 4], eax
004d203a mov esp, ebp
004d203c pop ebp
004d203d ret 4
