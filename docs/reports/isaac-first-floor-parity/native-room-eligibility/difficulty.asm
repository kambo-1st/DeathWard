0070e775 mov eax, dword ptr [0xbfd65c]
0070e77a mov esi, dword ptr [eax + 0x1c3170]
0070e780 mov ecx, dword ptr [eax + 0x243624]
0070e786 or esi, dword ptr [edi + 0xc]
0070e789 mov dword ptr [ebp - 0x3fc], ecx
0070e78f call 0x6ccc80
0070e794 mov edi, eax
0070e796 or edi, esi
0070e798 call 0x6cce10
0070e79d not eax
0070e79f and eax, edi
0070e7a1 mov edi, dword ptr [ebp - 0x404]
0070e7a7 test al, 2
0070e7a9 jne 0x70e826
0070e7ab mov eax, dword ptr [edi]
0070e7ad mov dword ptr [ebp - 0x400], eax
0070e7b3 cmp eax, 9
0070e7b6 jge 0x70e826
0070e7b8 mov ecx, eax
0070e7ba and ecx, 1
0070e7bd cmp dword ptr [ebp - 0x3fc], 1
0070e7c4 jne 0x70e7f6
0070e7c6 test ecx, ecx
0070e7c8 jne 0x70e7e0
0070e7ca mov dword ptr [ebp - 0x410], 0xf
0070e7d4 mov dword ptr [ebp - 0x3fc], 0xa
0070e7de jmp 0x70e85a
0070e7e0 mov dword ptr [ebp - 0x410], 0xa
0070e7ea mov dword ptr [ebp - 0x3fc], 5
0070e7f4 jmp 0x70e85a
0070e7f6 test ecx, ecx
0070e7f8 jne 0x70e810
0070e7fa mov dword ptr [ebp - 0x410], 0xa
0070e804 mov dword ptr [ebp - 0x3fc], 5
0070e80e jmp 0x70e854
0070e810 mov dword ptr [ebp - 0x410], 5
0070e81a mov dword ptr [ebp - 0x3fc], 1
0070e824 jmp 0x70e854
0070e826 mov eax, dword ptr [edi]
0070e828 xor ecx, ecx
0070e82a cmp dword ptr [ebp - 0x3fc], 1
0070e831 mov edx, 0xf
0070e836 sete cl
0070e839 lea ecx, [ecx*4 + 1]
0070e840 mov dword ptr [ebp - 0x3fc], ecx
0070e846 mov ecx, 0xa
0070e84b cmove ecx, edx
0070e84e mov dword ptr [ebp - 0x410], ecx
0070e854 mov dword ptr [ebp - 0x400], eax
