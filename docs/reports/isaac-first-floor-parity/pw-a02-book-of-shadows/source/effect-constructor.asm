00427600 push ebp
00427601 mov ebp, esp
00427603 mov eax, dword ptr [ebp + 8]
00427606 mov dword ptr [ecx], eax
00427608 mov dword ptr [ecx + 4], 0
0042760f mov eax, dword ptr [eax + 0x78]
00427612 mov dword ptr [ecx + 8], eax
00427615 mov eax, ecx
00427617 pop ebp
00427618 ret 4
