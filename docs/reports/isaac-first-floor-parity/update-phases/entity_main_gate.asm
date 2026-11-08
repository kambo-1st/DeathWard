00413714 mov al, byte ptr [esi + 0x16a]
0041371a movss dword ptr [ebp - 0x60], xmm0
0041371f test al, al
00413721 je 0x4138e9
00413727 mov ecx, dword ptr [esi + 0x160]
0041372d mov eax, ecx
0041372f mov edx, dword ptr [esi + 0x164]
00413735 and eax, 8
00413738 or eax, 0
0041373b je 0x413748
0041373d and ecx, 0x20000
00413743 or ecx, 0
00413746 je 0x41376f
00413748 cmp byte ptr [ebx + 8], 0
0041374c je 0x41375a
0041374e and edx, 0x1000
00413754 xor eax, eax
00413756 or eax, edx
00413758 je 0x41376f
0041375a mov eax, dword ptr [esi]
0041375c mov ecx, esi
0041375e call dword ptr [eax + 0xc]
00413761 mov al, byte ptr [esi + 0x16a]
00413767 test al, al
00413769 je 0x4138e9
