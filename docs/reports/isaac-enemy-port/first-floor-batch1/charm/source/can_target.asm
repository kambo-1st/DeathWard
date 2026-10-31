00681840 push ebp
00681841 mov ebp, esp
00681843 push esi
00681844 mov esi, dword ptr [ebp + 8]
00681847 push edi
00681848 mov edi, ecx
0068184a cmp esi, edi
0068184c je 0x681872
0068184e push esi
0068184f call 0x6815c0
00681854 test al, al
00681856 jne 0x681872
00681858 cmp dword ptr [edi + 0x28], 0xde
0068185f jne 0x68186a
00681861 cmp dword ptr [esi + 0x28], 0xde
00681868 je 0x681872
0068186a pop edi
0068186b mov al, 1
0068186d pop esi
0068186e pop ebp
0068186f ret 4
00681872 pop edi
00681873 xor al, al
00681875 pop esi
00681876 pop ebp
00681877 ret 4
