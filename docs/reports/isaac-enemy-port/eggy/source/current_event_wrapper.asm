004060f0 push ebp
004060f1 mov ebp, esp
004060f3 push ecx
004060f4 cmp dword ptr [ecx + 0x34], 0
004060f8 jne 0x406101
004060fa xor al, al
004060fc pop ecx
004060fd pop ebp
004060fe ret 4
00406101 push dword ptr [ebp + 8]
00406104 add ecx, 0x30
00406107 call 0x405e90
0040610c pop ecx
0040610d pop ebp
