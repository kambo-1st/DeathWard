006d26e0 push ebp
006d26e1 mov ebp, esp
006d26e3 and esp, 0xfffffff0
006d26e6 sub esp, 0xd8
006d26ec mov eax, dword ptr [0xbaa3b4]
006d26f1 xor eax, esp
006d26f3 mov dword ptr [esp + 0xd4], eax
006d26fa movss xmm1, dword ptr [ebp + 0xc]
006d26ff comiss xmm1, dword ptr [0xb6ab80]
006d2706 mov eax, dword ptr [ebp + 0x20]
006d2709 push esi
006d270a mov esi, dword ptr [ebp + 8]
006d270d push edi
006d270e mov edi, dword ptr [ebp + 0x24]
006d2711 mov dword ptr [esp + 0x3c], ecx
006d2715 mov dword ptr [esp + 0x34], esi
006d2719 mov dword ptr [esp + 0x30], eax
006d271d movss xmm0, dword ptr [0xb6aac4]
006d2725 mov dword ptr [esp + 0x38], edi
006d2729 movss dword ptr [esp + 0x14], xmm0
006d272f jb 0x6d273b
006d2731 movss xmm2, dword ptr [0xb6ab08]
006d2739 jmp 0x6d274c
006d273b comiss xmm1, dword ptr [0xb6ab44]
006d2742 jbe 0x6d2752
006d2744 movss xmm2, dword ptr [0xb6aae4]
006d274c movss dword ptr [esp + 0x14], xmm2
