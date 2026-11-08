006c0b81 mov eax, dword ptr [esi + 0x30]
006c0b84 cmp eax, 1
006c0b87 jne 0x6c0bed
006c0b89 mov eax, dword ptr [0xbfd65c]
006c0b8e cmp dword ptr [eax + 0x1c319c], 0x20
006c0b95 jne 0x6c0bda
006c0b97 push 5
006c0b99 lea ecx, [esi + 0x334]
006c0b9f call 0x7a7d50
006c0ba4 cmp eax, 4
006c0ba7 ja 0x6c097b
006c0bad jmp dword ptr [eax*4 + 0x6c2890]
006c0bb4 push 1
006c0bb6 mov ecx, edi
006c0bb8 call 0x725740
006c0bbd mov al, 1
006c0bbf mov byte ptr [ebp - 0x6d], al
006c0bc2 jmp 0x6c02a5
006c0bc7 push 1
006c0bc9 mov ecx, edi
006c0bcb call 0x7258c0
006c0bd0 mov al, 1
006c0bd2 mov byte ptr [ebp - 0x6d], al
006c0bd5 jmp 0x6c02a5
006c0bda push 1
006c0bdc mov ecx, edi
006c0bde call 0x725810
006c0be3 mov al, 1
006c0be5 mov byte ptr [ebp - 0x6d], al
006c0be8 jmp 0x6c02a5
006c0bed cmp eax, 2
006c0bf0 jne 0x6c0c56
006c0bf2 mov eax, dword ptr [0xbfd65c]
006c0bf7 cmp dword ptr [eax + 0x1c319c], 0x20
006c0bfe jne 0x6c0c43
006c0c00 push 5
006c0c02 lea ecx, [esi + 0x334]
006c0c08 call 0x7a7d50
006c0c0d cmp eax, 4
006c0c10 ja 0x6c097b
006c0c16 jmp dword ptr [eax*4 + 0x6c28a4]
006c0c1d push 2
006c0c1f mov ecx, edi
006c0c21 call 0x725740
006c0c26 mov al, 1
006c0c28 mov byte ptr [ebp - 0x6d], al
006c0c2b jmp 0x6c02a5
006c0c30 push 2
006c0c32 mov ecx, edi
006c0c34 call 0x7258c0
006c0c39 mov al, 1
006c0c3b mov byte ptr [ebp - 0x6d], al
006c0c3e jmp 0x6c02a5
006c0c43 push 2
006c0c45 mov ecx, edi
006c0c47 call 0x725810
006c0c4c mov al, 1
006c0c4e mov byte ptr [ebp - 0x6d], al
006c0c51 jmp 0x6c02a5
006c0c56 cmp eax, 4
006c0c59 jne 0x6c0cc2
006c0c5b mov eax, dword ptr [0xbfd65c]
006c0c60 cmp dword ptr [eax + 0x1c319c], 0x20
006c0c67 jne 0x6c0cb1
006c0c69 push 3
006c0c6b lea ecx, [esi + 0x334]
006c0c71 call 0x7a7d50
006c0c76 sub eax, 0
006c0c79 je 0x6c0ca0
006c0c7b sub eax, 1
006c0c7e je 0x6c0b05
006c0c84 sub eax, 1
006c0c87 jne 0x6c097b
006c0c8d push 1
006c0c8f mov ecx, edi
006c0c91 call 0x7250a0
006c0c96 mov al, 1
006c0c98 mov byte ptr [ebp - 0x6d], al
006c0c9b jmp 0x6c02a5
006c0ca0 mov ecx, edi
006c0ca2 call 0x725930
006c0ca7 mov al, 1
006c0ca9 mov byte ptr [ebp - 0x6d], al
006c0cac jmp 0x6c02a5
006c0cb1 mov ecx, edi
006c0cb3 call 0x78b1d0
006c0cb8 mov al, 1
006c0cba mov byte ptr [ebp - 0x6d], al
006c0cbd jmp 0x6c02a5
006c0cc2 cmp eax, 7
006c0cc5 jne 0x6c1f4c
006c0ccb mov eax, dword ptr [0xbfd65c]
006c0cd0 cmp dword ptr [eax + 0x1c319c], 0x20
006c0cd7 je 0x6c0c69
006c0cd9 push 1
006c0cdb mov ecx, edi
006c0cdd call 0x725810
006c0ce2 push 1
006c0ce4 mov ecx, edi
006c0ce6 call 0x794cf0
006c0ceb mov al, 1
006c0ced mov byte ptr [ebp - 0x6d], al
006c0cf0 jmp 0x6c02a5
