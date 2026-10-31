00519980 push ebx
00519981 mov ebx, esp
00519983 sub esp, 8
00519986 and esp, 0xfffffff8
00519989 add esp, 4
0051998c push ebp
0051998d mov ebp, dword ptr [ebx + 4]
00519990 mov dword ptr [esp + 4], ebp
00519994 mov ebp, esp
00519996 sub esp, 0x10
00519999 push esi
0051999a mov esi, ecx
0051999c push edi
0051999d cmp dword ptr [esi + 0xab4], 0
005199a4 jne 0x519a00
005199a6 mov eax, dword ptr [esi + 0x2b8]
005199ac mov dword ptr [esi + 0xb00], eax
005199b2 mov eax, dword ptr [esi + 0x2bc]
005199b8 mov dword ptr [esi + 0xb04], eax
005199be mov dword ptr [esi + 0xab4], 4
005199c8 mov dword ptr [esi + 0x360], 0
005199d2 mov dword ptr [esi + 0x2d8], 0
005199dc mov dword ptr [esi + 0x2dc], 0
005199e6 mov dword ptr [esi + 0x17c], 0
005199f0 mov byte ptr [esi + 0xb8c], 0
005199f7 pop edi
005199f8 pop esi
005199f9 mov esp, ebp
005199fb pop ebp
005199fc mov esp, ebx
005199fe pop ebx
005199ff ret 
