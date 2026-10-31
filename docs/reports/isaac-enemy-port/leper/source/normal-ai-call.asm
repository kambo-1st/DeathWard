0069ce57 cmp byte ptr [edi + 0x16b], 0
0069ce5e je 0x69ce88
0069ce60 cmp dword ptr [edi + 0xab4], 1
0069ce67 jne 0x69ce88
0069ce69 mov eax, dword ptr [edi + 0x2c0]
0069ce6f mov dword ptr [edi + 0x2c4], eax
0069ce75 mov eax, dword ptr [edi + 0xab8]
0069ce7b mov dword ptr [edi + 0xab4], eax
0069ce81 mov byte ptr [edi + 0x169], 1
0069ce88 cmp word ptr [edi + 0xbc4], 0
0069ce90 jne 0x69ce99
0069ce92 mov ecx, edi
0069ce94 call 0x699730
