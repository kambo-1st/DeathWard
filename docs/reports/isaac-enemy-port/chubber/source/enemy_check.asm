0068cf40 push ebp
0068cf41 mov ebp, esp
0068cf43 mov edx, dword ptr [ecx + 0x28]
0068cf46 lea eax, [edx - 0xa]
0068cf49 cmp eax, 0x3dd
0068cf4e ja 0x68cf9d
0068cf50 cmp edx, 0x21
0068cf53 je 0x68cf9d
0068cf55 cmp edx, 0x11
0068cf58 je 0x68cf9d
0068cf5a cmp edx, 0x124
0068cf60 je 0x68cf9d
0068cf62 cmp edx, 0x375
0068cf68 jne 0x68cf70
0068cf6a cmp dword ptr [ecx + 0x2c], 0xa
0068cf6e jmp 0x68cf86
0068cf70 cmp edx, 0x3c0
0068cf76 je 0x68cf9d
0068cf78 cmp edx, 0x3c5
0068cf7e je 0x68cf9d
0068cf80 cmp edx, 0xf5
0068cf86 je 0x68cf9d
0068cf88 cmp byte ptr [ecx + 0x16b], 0
0068cf8f je 0x68cf97
0068cf91 cmp byte ptr [ebp + 8], 0
0068cf95 je 0x68cf9d
0068cf97 mov al, 1
0068cf99 pop ebp
0068cf9a ret 4
0068cf9d xor al, al
0068cf9f pop ebp
0068cfa0 ret 4
