00695560 push ebp
00695561 mov ebp, esp
00695563 and esp, 0xfffffff8
00695566 push ecx
00695567 push esi
00695568 mov esi, ecx
0069556a mov eax, dword ptr [esi + 0xad8]
00695570 lea edx, [esi + 0xad8]
00695576 mov dword ptr [edx + 4], eax
00695579 mov dword ptr [edx + 0xc], 0
00695580 mov eax, dword ptr [esi + 0x14]
00695583 mov ecx, dword ptr [esi + 0x1c]
00695586 mov dword ptr [esi + 0xae4], eax
0069558c mov eax, dword ptr [esi + 0x18]
0069558f mov dword ptr [edx + 0x10], 0
00695596 mov dword ptr [esi + 0xae8], eax
0069559c lea eax, [esi + 8]
0069559f mov dword ptr [edx + 0x14], 0
006955a6 mov dword ptr [esi + 0xaec], ecx
006955ac cmp edx, eax
006955ae je 0x6955c0
006955b0 push dword ptr [esp + 4]
006955b4 mov ecx, edx
006955b6 push dword ptr [eax + 4]
006955b9 push dword ptr [eax]
006955bb call 0x497490
006955c0 cmp byte ptr [esi + 0x16b], 0
006955c7 jne 0x6955f0
006955c9 mov eax, dword ptr [esi]
006955cb mov ecx, esi
006955cd mov byte ptr [esi + 0x16b], 1
006955d4 mov eax, dword ptr [eax + 0x48]
006955d7 call eax
006955d9 test al, al
006955db jne 0x6955ea
006955dd cmp dword ptr [esi + 0x28], 3
006955e1 je 0x6955ea
006955e3 mov ecx, esi
006955e5 call 0x68b970
006955ea push esi
006955eb call 0x802c50
006955f0 pop esi
006955f1 mov esp, ebp
006955f3 pop ebp
006955f4 ret 
