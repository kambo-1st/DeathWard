004fa226 mov eax, dword ptr [edi + 0xab4]
004fa22c test eax, eax
004fa22e jne 0x4fa27a
004fa230 cmp dword ptr [edi + 0x28], 0x331
004fa237 jne 0x4fa261
004fa239 push eax
004fa23a push 0xb41e88
004fa23f lea ecx, [edi + 0x3c]
004fa242 call 0x405a00
004fa247 cmp dword ptr [edi + 0x2c], 1
004fa24b jne 0x4fa261
004fa24d mov dword ptr [edi + 0x2a8], 0xc0c00000
004fa257 mov dword ptr [edi + 0x17c], 6
004fa261 mov dword ptr [edi + 0xab4], 4
004fa26b mov dword ptr [edi + 0xb00], 0
004fa275 jmp 0x4fb1a7
