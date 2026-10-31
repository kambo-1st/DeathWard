00684630 push ebp
00684631 mov ebp, esp
00684633 and esp, 0xfffffff8
00684636 push esi
00684637 mov esi, ecx
00684639 push edi
0068463a mov edi, dword ptr [esi + 0x28]
0068463d lea eax, [edi - 0xa]
00684640 cmp eax, 0x3dd
00684645 ja 0x6846d0
0068464b mov eax, dword ptr [esi + 0x180]
00684651 cmp eax, 1
00684654 je 0x6846d0
00684656 test eax, eax
00684658 je 0x6846d0
0068465a cmp byte ptr [esi + 0x308], 0
00684661 jne 0x6846d0
00684663 cmp byte ptr [esi + 0x16b], 0
0068466a jne 0x6846d0
0068466c push 0
0068466e push 0x10
00684670 call 0x4122f0
00684675 test al, al
00684677 je 0x684689
00684679 cmp edi, 0x322
0068467f je 0x684689
00684681 cmp edi, 0x362
00684687 jne 0x6846d0
00684689 mov ecx, dword ptr [ebp + 8]
0068468c mov dl, 1
0068468e test ecx, ecx
00684690 je 0x6846d2
00684692 mov eax, dword ptr [esi + 0x160]
00684698 and eax, 0x20000000
0068469d or eax, 0
006846a0 je 0x6846d2
006846a2 call 0x681340
006846a7 mov ecx, eax
006846a9 mov eax, dword ptr [ecx + 0x160]
006846af and eax, 0x20000000
006846b4 or eax, 0
006846b7 jne 0x6846c6
006846b9 mov eax, dword ptr [ecx + 0x28]
006846bc cmp eax, 1
006846bf je 0x6846c6
006846c1 cmp eax, 3
006846c4 jne 0x6846d2
006846c6 xor al, al
006846c8 pop edi
006846c9 pop esi
006846ca mov esp, ebp
006846cc pop ebp
006846cd ret 4
006846d0 xor dl, dl
006846d2 pop edi
006846d3 mov al, dl
006846d5 pop esi
006846d6 mov esp, ebp
006846d8 pop ebp
006846d9 ret 4
