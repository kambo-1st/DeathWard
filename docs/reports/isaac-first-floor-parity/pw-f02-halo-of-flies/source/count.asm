0073880b push 0
0073880d push 0xa
0073880f mov ecx, edi
00738811 call 0x73b3b0
00738816 mov ecx, dword ptr [ebp - 0x42c]
0073881c push 0x6b
0073881e mov dword ptr [ebp - 0x4ec], 0xa
00738828 lea eax, [ecx + eax*2]
0073882b mov ecx, esi
0073882d mov dword ptr [ebp - 0x4e8], eax
00738833 call 0x88b920
00738838 mov edi, eax
0073883a lea edx, [ebp - 0x4e8]
00738840 lea ecx, [ebp - 0x4ec]
00738846 add edi, edi
00738848 call 0x417c60
0073884d mov ecx, dword ptr [0xbfd680]
00738853 mov esi, eax
00738855 push -1
00738857 push 0xa
00738859 call 0x427930
0073885e mov ecx, eax
00738860 call 0x6fe5e0
00738865 mov ecx, dword ptr [ebp - 0x428]
0073886b push eax
0073886c push 0xa
0073886e lea ecx, [ecx + 0x16b0]
00738874 call 0x5b60b0
00738879 push eax
0073887a mov eax, dword ptr [esi]
0073887c sub eax, edi
0073887e mov edi, dword ptr [ebp - 0x428]
00738884 push eax
00738885 push 0x21
00738887 mov ecx, edi
00738889 call 0x72eb50
