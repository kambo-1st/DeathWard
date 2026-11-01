007ab683 mov edx, dword ptr [ebp - 0x3c]
007ab686 mov eax, dword ptr [edx + 4]
007ab689 test eax, eax
007ab68b je 0x7ab69c
007ab68d mov eax, dword ptr [eax + 0x10]
007ab690 test eax, eax
007ab692 je 0x7ab69c
007ab694 mov eax, dword ptr [eax + 0x4c]
007ab697 and eax, 1
007ab69a jmp 0x7ab69e
007ab69c xor eax, eax
007ab69e test al, al
007ab6a0 jne 0x7abbcb
007ab6a6 cmp dword ptr [edx + 8], 0x1b
007ab6aa je 0x7abbcb
007ab6b0 mov eax, dword ptr [ecx + 4]
007ab6b3 mov dword ptr [ebp - 0x2c], eax
007ab6b6 cmp edi, 3
007ab6b9 je 0x7ab6c0
007ab6bb cmp edi, 4
007ab6be jne 0x7ab6ce
007ab6c0 cmp eax, 4
007ab6c3 je 0x7ab6ce
007ab6c5 mov byte ptr [ebp - 0x2f], 1
007ab6c9 cmp eax, 5
007ab6cc jne 0x7ab6d2
007ab6ce mov byte ptr [ebp - 0x2f], 0
007ab6d2 cmp eax, 2
007ab6d5 jne 0x7ab6e7
007ab6d7 cmp edi, 1
007ab6da je 0x7ab6e0
007ab6dc cmp edi, eax
007ab6de jne 0x7ab6e7
007ab6e0 mov dh, 1
007ab6e2 mov byte ptr [ebp - 0x32], dh
007ab6e5 jmp 0x7ab6f1
007ab6e7 xor dh, dh
007ab6e9 mov byte ptr [ebp - 0x32], dh
007ab6ec cmp eax, 2
007ab6ef jne 0x7ab701
007ab6f1 cmp edi, 3
007ab6f4 je 0x7ab6fb
007ab6f6 cmp edi, 4
007ab6f9 jne 0x7ab701
007ab6fb mov byte ptr [ebp - 0x31], 1
007ab6ff jmp 0x7ab70a
007ab701 mov byte ptr [ebp - 0x31], 0
007ab705 cmp eax, 2
007ab708 jne 0x7ab71a
007ab70a cmp edi, 5
007ab70d je 0x7ab714
007ab70f cmp edi, 6
007ab712 jne 0x7ab71a
007ab714 mov byte ptr [ebp - 0x2d], 1
007ab718 jmp 0x7ab723
007ab71a mov byte ptr [ebp - 0x2d], 0
007ab71e cmp eax, 2
007ab721 jne 0x7ab733
007ab723 cmp edi, 7
007ab726 je 0x7ab72d
007ab728 cmp edi, 8
007ab72b jne 0x7ab733
007ab72d mov byte ptr [ebp - 0x30], 1
007ab731 jmp 0x7ab737
007ab733 mov byte ptr [ebp - 0x30], 0
007ab737 mov eax, dword ptr [0xbfd680]
007ab73c cmp byte ptr [eax + 0x1a8], 0
007ab743 jne 0x7ab761
007ab745 cmp dword ptr [eax + 8], 2
007ab749 jne 0x7ab75d
007ab74b cmp dword ptr [ecx + 0x1c3204], 0
007ab752 ja 0x7ab761
007ab754 cmp byte ptr [ecx + 0x1c31a1], 0
007ab75b jne 0x7ab761
007ab75d xor dl, dl
007ab75f jmp 0x7ab763
007ab761 mov dl, 1
007ab763 mov eax, dword ptr [esi]
007ab765 mov byte ptr [ebp - 0x2e], dl
007ab768 cmp eax, 0x12e
007ab76d jg 0x7abadd
007ab773 je 0x7aba9c
007ab779 sub eax, 0xa
007ab77c cmp eax, 0xdd
007ab781 ja 0x7abadd
007ab787 movzx eax, byte ptr [eax + 0x7abc28]
007ab78e jmp dword ptr [eax*4 + 0x7abbe0]
