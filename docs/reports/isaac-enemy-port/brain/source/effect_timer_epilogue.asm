005e9122 mov eax, dword ptr [ebp - 0xeb8]
005e9128 cmp dword ptr [eax + 0x3ac], 0
005e912f jle 0x5e9168
005e9131 mov ecx, dword ptr [ebp - 0xeb8]
005e9137 mov edx, dword ptr [ecx + 0x3ac]
005e913d sub edx, 1
005e9140 mov eax, dword ptr [ebp - 0xeb8]
005e9146 mov dword ptr [eax + 0x3ac], edx
005e914c mov ecx, dword ptr [ebp - 0xeb8]
005e9152 cmp dword ptr [ecx + 0x3ac], 0
005e9159 jg 0x5e9168
005e915b mov edx, dword ptr [ebp - 0xeb8]
005e9161 mov byte ptr [edx + 0x16b], 1
