0076e140 push ebp
0076e141 mov ebp, esp
0076e143 push -1
0076e145 push 0x9f8ad5
0076e14a mov eax, dword ptr fs:[0]
0076e150 push eax
0076e151 sub esp, 0x88
0076e157 mov eax, dword ptr [0xbaa3b4]
0076e15c xor eax, ebp
0076e15e mov dword ptr [ebp - 0x10], eax
0076e161 push esi
0076e162 push edi
0076e163 push eax
0076e164 lea eax, [ebp - 0xc]
0076e167 mov dword ptr fs:[0], eax
0076e16d mov edi, ecx
0076e16f mov dword ptr [ebp - 0x6c], edi
0076e172 push 0x8f
0076e177 call 0x78d4c0
0076e17c test eax, eax
0076e17e jg 0x76e4a6
0076e184 push 0
0076e186 push 0x287
0076e18b mov ecx, edi
0076e18d call 0x73af30
0076e192 test al, al
0076e194 jne 0x76e4a6
