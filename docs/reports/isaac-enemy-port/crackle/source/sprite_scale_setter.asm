00427330 push ebp
00427331 mov ebp, esp
00427333 mov edx, dword ptr [ebp + 8]
00427336 mov eax, dword ptr [edx]
00427338 mov dword ptr [ecx + 0xd8], eax
0042733e mov eax, dword ptr [edx + 4]
00427341 mov dword ptr [ecx + 0xdc], eax
00427347 pop ebp
00427348 ret 4
