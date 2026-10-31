0069eb35 push 0
0069eb37 push 0x20
0069eb39 mov ecx, edi
0069eb3b call 0x4122f0
0069eb40 test al, al
0069eb42 jne 0x69eb4d
0069eb44 cmp dword ptr [edi + 0x348], 0
0069eb4b jle 0x69eb90
0069eb4d cmp dword ptr [edi + 0x348], 0
0069eb54 movss xmm0, dword ptr [edi + 0x2c4]
0069eb5c mulss xmm0, dword ptr [0xb6a214]
0069eb64 movss dword ptr [edi + 0x2c4], xmm0
0069eb6c jle 0x69eb90
0069eb6e lea esi, [edi + 0x34c]
0069eb74 push 0xc02fec
0069eb79 mov ecx, esi
0069eb7b call 0x962ca0
0069eb80 test al, al
0069eb82 je 0x69eb90
0069eb84 push esi
0069eb85 lea ecx, [edi + 0x294]
0069eb8b call 0x962cd0
