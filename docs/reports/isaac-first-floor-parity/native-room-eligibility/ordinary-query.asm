0070a5c5 mov dword ptr [ebp - 0x110], ecx
0070a5cb mov eax, ecx
0070a5cd cmp ecx, 1
0070a5d0 jle 0x70a5e3
0070a5d2 test byte ptr [ebx], 7
0070a5d5 mov ecx, 1
0070a5da cmove eax, ecx
0070a5dd mov dword ptr [ebp - 0x110], eax
0070a5e3 mov ecx, dword ptr [esi]
0070a5e5 mov edx, dword ptr [ecx + 8]
0070a5e8 mov eax, dword ptr [ecx + 0xc]
0070a5eb cmp edx, 0xc
0070a5ee ja 0x70a5fc
0070a5f0 cmp eax, 0xc
0070a5f3 ja 0x70a5fc
0070a5f5 imul eax, eax, 0xd
0070a5f8 add eax, edx
0070a5fa jmp 0x70a5ff
0070a5fc or eax, 0xffffffff
0070a5ff cmp eax, dword ptr [edi + 0x18160]
0070a605 jne 0x70a675
0070a607 cmp dword ptr [ecx + 0x40], 0
0070a60b jne 0x70a675
0070a60d cmp dword ptr [edi], 0xb
0070a610 jne 0x70a658
0070a612 mov eax, dword ptr [edi + 4]
0070a615 cmp eax, 1
0070a618 jne 0x70a637
0070a61a push -1
0070a61c xor ecx, ecx
0070a61e mov eax, 0x11
0070a623 push ecx
0070a624 mov ecx, dword ptr [ebp - 0xe0]
0070a62a push 1
0070a62c push eax
0070a62d call 0x7e70e0
0070a632 jmp 0x70a6f9
0070a637 test eax, eax
0070a639 jne 0x70a658
0070a63b push -1
0070a63d xor ecx, ecx
0070a63f mov eax, 0x10
0070a644 push ecx
0070a645 mov ecx, dword ptr [ebp - 0xe0]
0070a64b push 1
0070a64d push eax
0070a64e call 0x7e70e0
0070a653 jmp 0x70a6f9
0070a658 push -1
0070a65a mov ecx, 2
0070a65f xor eax, eax
0070a661 push ecx
0070a662 mov ecx, dword ptr [ebp - 0xe0]
0070a668 push 1
0070a66a push eax
0070a66b call 0x7e70e0
0070a670 jmp 0x70a6f9
0070a675 mov edx, dword ptr [ebx]
0070a677 xor eax, eax
0070a679 cmp dword ptr [edi], 0xb
0070a67c sete al
0070a67f mov dword ptr [ebp - 0xec], eax
0070a685 test edx, edx
0070a687 jne 0x70a69f
0070a689 push 0xb4d6c4
0070a68e push 3
0070a690 call 0x95e330
0070a695 mov edx, dword ptr [ebx]
0070a697 add esp, 8
0070a69a test edx, edx
0070a69c jne 0x70a69f
0070a69e int3
0070a69f mov ecx, dword ptr [ebx + 4]
0070a6a2 mov eax, edx
0070a6a4 shr eax, cl
0070a6a6 mov ecx, dword ptr [ebx + 8]
0070a6a9 xor eax, edx
0070a6ab mov edx, eax
0070a6ad shl edx, cl
0070a6af mov ecx, dword ptr [ebx + 0xc]
0070a6b2 xor edx, eax
0070a6b4 mov edi, edx
0070a6b6 shr edi, cl
0070a6b8 push -1
0070a6ba xor edi, edx
0070a6bc push 0
0070a6be mov dword ptr [ebx], edi
0070a6c0 mov ecx, dword ptr [esi]
0070a6c2 lea eax, [ecx + 0x1c]
0070a6c5 push eax
0070a6c6 push dword ptr [ebp - 0x14c]
0070a6cc push dword ptr [ebp - 0x110]
0070a6d2 push -1
0070a6d4 push dword ptr [ebp - 0xec]
0070a6da push dword ptr [ecx + 0x18]
0070a6dd mov ecx, dword ptr [ebp - 0xe0]
0070a6e3 push 1
0070a6e5 push dword ptr [ebp - 0x10c]
0070a6eb push 1
0070a6ed push edi
0070a6ee call 0x7e7180
0070a6f3 mov edi, dword ptr [ebp - 0x100]
0070a6f9 test eax, eax
0070a6fb je 0x70a8a1
0070a701 push ecx
0070a702 push dword ptr [ebx]
0070a704 mov ecx, edi
0070a706 push eax
0070a707 push dword ptr [esi]
0070a709 call 0x706680
