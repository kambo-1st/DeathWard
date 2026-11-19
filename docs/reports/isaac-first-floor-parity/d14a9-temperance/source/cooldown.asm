00639fae movzx ecx, word ptr [edi + 0x36a]
00639fb5 mov eax, ecx
00639fb7 test cx, cx
00639fba jle 0x639ff7
00639fbc lea eax, [ecx - 1]
00639fbf movzx ecx, ax
00639fc2 mov word ptr [edi + 0x36a], cx
00639fc9 mov edx, ecx
00639fcb mov eax, ecx
00639fcd test cx, cx
00639fd0 jne 0x639ff7
