005c1fdc mov ecx, dword ptr [ebp - 0xeb8]
005c1fe2 call 0x682200
005c1fe7 mov dword ptr [ebp - 0x14d0], eax
005c1fed cmp dword ptr [ebp - 0x14d0], 1
005c1ff4 jne 0x5c202c
005c1ff6 mov ecx, dword ptr [ebp - 0xeb8]
005c1ffc cmp dword ptr [ecx + 0x30], 0
005c2000 jne 0x5c202c
005c2002 push ecx
005c2003 movss xmm0, dword ptr [0xb6a614]
005c200b movss dword ptr [esp], xmm0
005c2010 push 0
005c2012 push 2
005c2014 push 0x1d7
005c2019 movss xmm2, dword ptr [0xb6a614]
005c2021 mov ecx, dword ptr [0xbfd680]
005c2027 call 0x8b1480
005c202c cmp dword ptr [ebp - 0x14d0], 2
005c2033 je 0x5c2042
005c2035 cmp dword ptr [ebp - 0x14d0], 4
005c203c jne 0x5c2144
005c2042 mov edx, dword ptr [ebp - 0xeb8]
005c2048 movss xmm0, dword ptr [edx + 0x2e0]
005c2050 comiss xmm0, dword ptr [0xb6a18c]
005c2057 jbe 0x5c2144
005c205d mov eax, dword ptr [ebp - 0xeb8]
005c2063 cmp dword ptr [eax + 0x320], 0
005c206a je 0x5c208b
005c206c push 0
005c206e push 0x20000000
005c2073 mov ecx, dword ptr [ebp - 0xeb8]
005c2079 mov ecx, dword ptr [ecx + 0x320]
005c207f call 0x4122f0
005c2084 movzx edx, al
005c2087 test edx, edx
005c2089 jne 0x5c20b0
005c208b push 0
005c208d push 0x20000000
005c2092 mov ecx, dword ptr [ebp - 0xeb8]
005c2098 call 0x4122f0
005c209d movzx eax, al
005c20a0 test eax, eax
005c20a2 jne 0x5c20b0
005c20a4 mov dword ptr [ebp - 0x1880], 0
005c20ae jmp 0x5c20ba
005c20b0 mov dword ptr [ebp - 0x1880], 1
005c20ba mov cl, byte ptr [ebp - 0x1880]
005c20c0 mov byte ptr [ebp - 0xffc], cl
005c20c6 sub esp, 0x10
005c20c9 mov edx, esp
005c20cb mov eax, dword ptr [0xbfec58]
005c20d0 mov dword ptr [edx], eax
005c20d2 mov ecx, dword ptr [0xbfec5c]
005c20d8 mov dword ptr [edx + 4], ecx
005c20db mov eax, dword ptr [0xbfec60]
005c20e0 mov dword ptr [edx + 8], eax
005c20e3 mov ecx, dword ptr [0xbfec64]
005c20e9 mov dword ptr [edx + 0xc], ecx
005c20ec push ecx
005c20ed movss xmm0, dword ptr [0xb6aa0c]
005c20f5 movss dword ptr [esp], xmm0
005c20fa push 0
005c20fc movzx edx, byte ptr [ebp - 0xffc]
005c2103 test edx, edx
005c2105 sete al
005c2108 movzx ecx, al
005c210b push ecx
005c210c push 0
005c210e push 2
005c2110 mov edx, dword ptr [ebp - 0xeb8]
005c2116 push edx
005c2117 mov eax, dword ptr [ebp - 0xeb8]
005c211d add eax, 0x294
005c2122 push eax
005c2123 movss xmm3, dword ptr [0xb6a9c8]
005c212b mov ecx, dword ptr [ebp - 0xeb8]
005c2131 movss xmm2, dword ptr [ecx + 0x2e0]
005c2139 mov ecx, dword ptr [0xbfd65c]
005c213f call 0x6d1240
005c2144 push 0xa081d4
005c2149 mov ecx, dword ptr [ebp - 0xeb8]
005c214f add ecx, 0x3c
005c2152 call 0x4056c0
005c2157 movzx edx, al
005c215a test edx, edx
005c215c je 0x5c2171
005c215e mov eax, dword ptr [ebp - 0xeb8]
005c2164 mov edx, dword ptr [eax]
005c2166 mov ecx, dword ptr [ebp - 0xeb8]
005c216c mov eax, dword ptr [edx + 0x28]
005c216f call eax
005c2171 jmp 0x5e9122
