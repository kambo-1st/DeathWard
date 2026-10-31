004f4ff6 mov ecx, dword ptr [0xbfd65c]
004f4ffc push 1
004f4ffe add ecx, 0x1ba40
004f5004 push ecx
004f5005 push 9
004f5007 call 0x91d340
004f500c test eax, eax
004f500e je 0x4f503a
004f5010 mov eax, dword ptr [esi + 0x160]
004f5016 and eax, 0x20000000
004f501b or eax, 0
004f501e jne 0x4f503a
004f5020 cmp dword ptr [esi + 0x28], 0x12
004f5024 mov byte ptr [esp + 0xb], 1
004f5029 jne 0x4f503f
004f502b push -1
004f502d push eax
004f502e push eax
004f502f push 0xd
004f5031 mov ecx, esi
004f5033 call 0x697c60
004f5038 jmp 0x4f503f
004f503a mov byte ptr [esp + 0xb], 0
