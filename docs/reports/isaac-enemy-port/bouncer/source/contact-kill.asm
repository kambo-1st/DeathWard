006a43a5 mov eax, dword ptr [edi + 0x28]
006a43a8 cmp eax, 0x336
006a43ad jne 0x6a43d0
006a43af cmp dword ptr [edi + 0xab4], 0x10
006a43b6 jne 0x6a43f1
006a43b8 cmp dword ptr [esi + 0x28], 1
006a43bc je 0x6a43c6
006a43be cmp esi, dword ptr [edi + 0x31c]
006a43c4 jne 0x6a43f1
006a43c6 mov eax, dword ptr [edi]
006a43c8 mov ecx, edi
006a43ca call dword ptr [eax + 0x24]
006a43cd mov eax, dword ptr [edi + 0x28]
