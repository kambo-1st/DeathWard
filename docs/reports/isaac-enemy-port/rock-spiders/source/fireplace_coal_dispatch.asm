006a7ae0 push ebp
006a7ae1 mov ebp, esp
006a7ae3 push -1
006a7ae5 push 0x9f49b0
006a7aea mov eax, dword ptr fs:[0]
006a7af0 push eax
006a7af1 sub esp, 0xdc
006a7af7 mov eax, dword ptr [0xbaa3b4]
006a7afc xor eax, ebp
006a7afe mov dword ptr [ebp - 0x10], eax
006a7b01 push ebx
006a7b02 push esi
006a7b03 push edi
006a7b04 push eax
006a7b05 lea eax, [ebp - 0xc]
006a7b08 mov dword ptr fs:[0], eax
006a7b0e mov edi, ecx
006a7b10 mov dword ptr [ebp - 0x74], edi
006a7b13 mov esi, dword ptr [edi + 0x2c]
006a7b16 movss xmm1, dword ptr [0xb6a350]
006a7b1e cmp esi, 2
006a7b21 je 0x6a7b7d
006a7b23 cmp esi, 3
006a7b26 je 0x6a7b7d
006a7b28 cmp esi, 4
006a7b2b je 0x6a7b7d
006a7b2d mov eax, dword ptr [0xbfd65c]
006a7b32 mov byte ptr [ebp - 0x69], 0
006a7b36 mov eax, dword ptr [eax + 0x18190]
006a7b3c movss xmm0, dword ptr [eax + 0x7134]
006a7b44 comiss xmm0, xmm1
006a7b47 jbe 0x6a7b81
006a7b49 push dword ptr [edi + 0x20]
006a7b4c push 5
006a7b4e call 0x684790
006a7b53 test al, al
006a7b55 je 0x6a7b81
006a7b57 mov edx, dword ptr [edi]
006a7b59 lea ecx, [ebp - 0xe8]
006a7b5f push 0x1e
006a7b61 call 0x427290
006a7b66 push eax
006a7b67 push 0
006a7b69 push 0
006a7b6b push ecx
006a7b6c mov ecx, edi
006a7b6e mov dword ptr [esp], 0x3f800000
006a7b75 call dword ptr [edx + 0x20]
006a7b78 mov esi, dword ptr [edi + 0x2c]
006a7b7b jmp 0x6a7b81
006a7b7d mov byte ptr [ebp - 0x69], 1
006a7b81 cmp esi, 0xb
006a7b84 jne 0x6a7b92
006a7b86 mov ecx, edi
006a7b88 call 0x4e7250
006a7b8d jmp 0x6a8a1d
