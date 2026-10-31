006aeb40 push ebp
006aeb41 mov ebp, esp
006aeb43 sub esp, 8
006aeb46 mov eax, dword ptr [ecx + 0x164]
006aeb4c mov edx, dword ptr [ecx + 0x160]
006aeb52 mov dword ptr [ebp - 4], eax
006aeb55 mov eax, edx
006aeb57 and eax, 0x100
006aeb5c or eax, 0
006aeb5f je 0x6aeb74
006aeb61 and edx, 0x20000000
006aeb67 or edx, 0
006aeb6a jne 0x6aeb7f
006aeb6c mov al, 1
006aeb6e mov esp, ebp
006aeb70 pop ebp
006aeb71 ret 4
006aeb74 and edx, 0x20000000
006aeb7a or edx, 0
006aeb7d je 0x6aeb83
006aeb7f xor dl, dl
006aeb81 jmp 0x6aeb85
006aeb83 mov dl, 1
006aeb85 mov ecx, dword ptr [ebp + 8]
006aeb88 mov eax, dword ptr [ecx + 0x28]
006aeb8b cmp eax, 1
006aeb8e je 0x6aebc4
006aeb90 cmp eax, 4
006aeb93 je 0x6aebc4
006aeb95 cmp eax, 3
006aeb98 jne 0x6aebaa
006aeb9a mov eax, dword ptr [ecx + 0x160]
006aeba0 and eax, 0x100
006aeba5 or eax, 0
006aeba8 je 0x6aebc4
006aebaa mov eax, dword ptr [ecx + 0x160]
006aebb0 and eax, 0x20000000
006aebb5 or eax, 0
006aebb8 jne 0x6aebc4
006aebba mov al, 1
006aebbc xor al, dl
006aebbe mov esp, ebp
006aebc0 pop ebp
006aebc1 ret 4
006aebc4 xor al, al
006aebc6 xor al, dl
006aebc8 mov esp, ebp
006aebca pop ebp
006aebcb ret 4
