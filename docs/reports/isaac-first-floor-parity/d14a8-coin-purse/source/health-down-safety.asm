007876f0 push ebp
007876f1 mov ebp, esp
007876f3 mov eax, dword ptr [ebp + 8]
007876f6 push esi
007876f7 mov esi, ecx
007876f9 cmp eax, 1
007876fc jne 0x78772a
007876fe call 0x79c960
00787703 test al, al
00787705 jne 0x787783
00787707 mov eax, dword ptr [esi + 0x1ca8]
0078770d sub eax, dword ptr [esi + 0x1cc4]
00787713 add eax, dword ptr [esi + 0x129c]
00787719 add eax, dword ptr [esi + 0x1294]
0078771f cmp eax, 2
00787722 pop esi
00787723 setg al
00787726 pop ebp
00787727 ret 4
0078772a cmp eax, 6
0078772d jne 0x78778a
0078772f call 0x79c960
00787734 test al, al
00787736 jne 0x787783
00787738 mov ecx, esi
0078773a call 0x78cdc0
0078773f sub eax, 1
00787742 je 0x787772
00787744 sub eax, 2
00787747 je 0x787783
00787749 sub eax, 1
0078774c je 0x78775f
0078774e mov eax, dword ptr [esi + 0x1290]
00787754 cmp eax, 2
00787757 pop esi
00787758 setg al
0078775b pop ebp
0078775c ret 4
0078775f mov eax, dword ptr [esi + 0x1ca8]
00787765 add eax, eax
00787767 cmp eax, 2
0078776a pop esi
0078776b setg al
0078776e pop ebp
0078776f ret 4
00787772 mov eax, dword ptr [esi + 0x129c]
00787778 cmp eax, 2
0078777b pop esi
0078777c setg al
0078777f pop ebp
00787780 ret 4
00787783 xor al, al
00787785 pop esi
00787786 pop ebp
00787787 ret 4
0078778a mov al, 1
0078778c pop esi
0078778d pop ebp
