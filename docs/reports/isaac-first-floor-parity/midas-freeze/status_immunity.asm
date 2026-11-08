00684b00 push ebp
00684b01 mov ebp, esp
00684b03 and esp, 0xfffffff8
00684b06 sub esp, 8
00684b09 mov eax, dword ptr [ecx + 0x164]
00684b0f mov edx, dword ptr [ecx + 0x160]
00684b15 mov dword ptr [esp + 4], eax
00684b19 mov eax, edx
00684b1b and eax, 0x20000000
00684b20 push ebx
00684b21 or eax, 0
00684b24 mov eax, dword ptr [ecx + 0x28]
00684b27 push esi
00684b28 jne 0x684b3a
00684b2a cmp eax, 3
00684b2d jne 0x684b3e
00684b2f and edx, 0x100
00684b35 or edx, 0
00684b38 jne 0x684b3e
00684b3a mov bl, 1
00684b3c jmp 0x684b40
00684b3e xor bl, bl
00684b40 mov edx, dword ptr [ebp + 8]
00684b43 lea esi, [eax - 0xa]
00684b46 mov eax, dword ptr [edx + 8]
00684b49 cmp eax, 1
00684b4c je 0x684b88
00684b4e mov ecx, dword ptr [edx]
00684b50 cmp ecx, 1
00684b53 je 0x684b88
00684b55 cmp ecx, 8
00684b58 je 0x684b88
00684b5a cmp eax, 3
00684b5d je 0x684b88
00684b5f cmp ecx, 3
00684b62 je 0x684b88
00684b64 mov eax, dword ptr [edx + 0x20]
00684b67 shr eax, 1
00684b69 test al, 1
00684b6b jne 0x684b88
00684b6d cmp ecx, 0x3e8
00684b73 jne 0x684b84
00684b75 push dword ptr [edx + 4]
00684b78 call 0x5ed040
00684b7d add esp, 4
00684b80 test al, al
00684b82 jne 0x684b88
00684b84 xor al, al
00684b86 jmp 0x684b8a
00684b88 mov al, 1
00684b8a test bl, bl
00684b8c je 0x684ba4
00684b8e cmp esi, 0x3dd
00684b94 ja 0x684ba4
00684b96 test al, al
00684b98 je 0x684ba4
00684b9a mov al, 1
00684b9c pop esi
00684b9d pop ebx
00684b9e mov esp, ebp
00684ba0 pop ebp
00684ba1 ret 4
00684ba4 pop esi
00684ba5 xor al, al
00684ba7 pop ebx
00684ba8 mov esp, ebp
00684baa pop ebp
00684bab ret 4
