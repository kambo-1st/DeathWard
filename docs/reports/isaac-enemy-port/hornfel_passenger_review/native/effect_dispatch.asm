; Installed-binary disassembly; field interpretations require the source review.
005be281 mov eax, dword ptr [ebp - 0xeb8]
005be287 mov ecx, dword ptr [eax + 0x2c]
005be28a mov dword ptr [ebp - 0x1250], ecx
005be290 mov edx, dword ptr [ebp - 0x1250]
005be296 sub edx, 1
005be299 mov dword ptr [ebp - 0x1250], edx
005be29f cmp dword ptr [ebp - 0x1250], 0xc8
005be2a9 ja 0x5be2b8
005be2ab mov eax, dword ptr [ebp - 0x1250]
005be2b1 jmp dword ptr [eax*4 + 0x5e9214]
