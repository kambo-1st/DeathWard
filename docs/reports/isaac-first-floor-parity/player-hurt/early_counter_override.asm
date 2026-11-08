007415d6 movss xmm0, dword ptr [ebp + 8]
007415db lea edx, [ebp - 0x130]
007415e1 addss xmm0, dword ptr [0xb6a480]
007415e9 lea ecx, [ebp - 0x2c]
007415ec mov dword ptr [ebp - 0x2c], 2
007415f3 cvttss2si eax, xmm0
007415f7 mov dword ptr [ebp - 0x130], eax
007415fd call 0x417c60
00741602 mov eax, dword ptr [eax]
00741604 mov ecx, eax
00741606 shl ecx, 4
00741609 sub ecx, eax
0074160b shl ecx, 2
0074160e mov dword ptr [edi + 0x1308], ecx
