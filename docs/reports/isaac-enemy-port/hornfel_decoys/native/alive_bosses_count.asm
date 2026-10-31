; Installed Repentance1.7.9b native API function/name pairing.
00448020 mov edx, dword ptr [ecx + 0x12cc]
00448026 xor eax, eax
00448028 mov ecx, dword ptr [ecx + 0x12c8]
0044802e add ecx, edx
00448030 test ecx, ecx
00448032 cmovg eax, ecx
00448035 ret 
