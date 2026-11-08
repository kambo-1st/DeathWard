0076e5b2 cmp dword ptr [edi + 0x1cc4], 0
0076e5b9 jle 0x76e643
0076e5bf xor esi, esi
0076e5c1 lea eax, [ebp - 0x50]
0076e5c4 push esi
0076e5c5 push esi
0076e5c6 push -1
0076e5c8 push 0x2b
0076e5ca push 3
0076e5cc push eax
0076e5cd mov eax, dword ptr [0xbfd65c]
0076e5d2 mov ecx, dword ptr [eax + 0x18190]
0076e5d8 add ecx, 0x1218
0076e5de call 0x415ed0
0076e5e3 xor eax, eax
0076e5e5 mov dword ptr [ebp - 4], esi
0076e5e8 cmp dword ptr [ebp - 0x44], eax
0076e5eb jbe 0x76e60c
0076e5ed mov edx, dword ptr [ebp - 0x4c]
0076e5f0 mov ecx, dword ptr [edx + eax*4]
0076e5f3 test ecx, ecx
0076e5f5 je 0x76e606
0076e5f7 cmp dword ptr [ecx + 0x28], 3
0076e5fb jne 0x76e606
0076e5fd cmp dword ptr [ecx + 0x360], edi
0076e603 jne 0x76e606
0076e605 inc esi
0076e606 inc eax
0076e607 cmp eax, dword ptr [ebp - 0x44]
0076e60a jb 0x76e5f0
0076e60c mov ecx, dword ptr [edi + 0x1cc4]
0076e612 add ecx, ecx
0076e614 sub ecx, esi
0076e616 test ecx, ecx
0076e618 jle 0x76e62b
0076e61a push 0
0076e61c lea eax, [edi + 0x294]
0076e622 push eax
0076e623 push ecx
0076e624 mov ecx, edi
0076e626 call 0x725cc0
