0041c430 push ebp
0041c431 mov ebp, esp
0041c433 push esi
0041c434 mov esi, dword ptr [ebp + 8]
0041c437 xor edx, edx
0041c439 push edi
0041c43a xor edi, edi
0041c43c mov eax, esi
0041c43e and eax, 0x3f
0041c441 bts edi, eax
0041c444 cmp eax, 0x20
0041c447 cmovae edx, edi
0041c44a xor edi, edx
0041c44c cmp eax, 0x40
0041c44f cmovae edx, edi
0041c452 shr esi, 6
0041c455 and edi, dword ptr [ecx + esi*8 + 0x1c3168]
0041c45c and edx, dword ptr [ecx + esi*8 + 0x1c316c]
0041c463 or edi, edx
0041c465 pop edi
0041c466 pop esi
0041c467 je 0x41c46f
0041c469 mov al, 1
0041c46b pop ebp
0041c46c ret 4
0041c46f xor al, al
0041c471 pop ebp
0041c472 ret 4
