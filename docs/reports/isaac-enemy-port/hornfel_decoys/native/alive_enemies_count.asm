; Installed Repentance1.7.9b native API function/name pairing.
00448000 mov edx, dword ptr [ecx + 0x12c4]
00448006 xor eax, eax
00448008 mov ecx, dword ptr [ecx + 0x12c0]
0044800e add ecx, edx
00448010 test ecx, ecx
00448012 cmovg eax, ecx
00448015 ret 
