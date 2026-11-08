0073d963 cmp dword ptr [edi + 0x1308], 0
0073d96a jg 0x73d97e
0073d96c movss xmm0, dword ptr [ebp + 8]
0073d971 comiss xmm0, dword ptr [0xb6a18c]
0073d978 jbe 0x73d97e
0073d97a test al, al
0073d97c je 0x73d98a
0073d97e mov eax, dword ptr [ebp - 0x14]
0073d981 or eax, 0
0073d984 je 0x741614
