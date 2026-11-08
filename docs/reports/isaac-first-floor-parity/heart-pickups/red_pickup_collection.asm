006bfa0c dec eax
006bfa0d mov dword ptr [ebp - 0xb8], 0
006bfa17 mov dword ptr [ebp - 0xd8], 0
006bfa21 cmp eax, 8
006bfa24 ja 0x6bfa74
006bfa26 movzx eax, byte ptr [eax + 0x6c2854]
006bfa2d jmp dword ptr [eax*4 + 0x6c2844]
006bfa34 mov dword ptr [ebp - 0xb8], 2
006bfa3e mov dword ptr [ebp - 0xd8], 3
006bfa48 jmp 0x6bfa74
006bfa4a mov dword ptr [ebp - 0xb8], 1
006bfa54 mov dword ptr [ebp - 0xd8], 1
006bfa5e jmp 0x6bfa74
006bfa60 mov dword ptr [ebp - 0xb8], 4
006bfa6a mov dword ptr [ebp - 0xd8], 6
006bfa74 push 0
006bfa76 push 0x138
006bfa7b mov ecx, edi
006bfa7d call 0x73af30
006bfa82 push 0x8c
006bfa87 mov ecx, edi
006bfa89 mov byte ptr [ebp - 0x75], al
006bfa8c call 0x78d4c0
006bfa91 test eax, eax
006bfa93 setg cl
006bfa96 cmp byte ptr [ebp - 0x75], 0
006bfa9a mov byte ptr [ebp - 0x70], cl
006bfa9d je 0x6bfabb
006bfa9f mov eax, dword ptr [ebp - 0xb8]
006bfaa5 add eax, eax
006bfaa7 mov dword ptr [ebp - 0xb8], eax
006bfaad mov eax, dword ptr [ebp - 0xd8]
006bfab3 add eax, eax
006bfab5 mov dword ptr [ebp - 0xd8], eax
006bfabb test cl, cl
006bfabd je 0x6bfaef
006bfabf mov eax, dword ptr [esi + 0x334]
006bfac5 lea ecx, [ebp - 0x20]
006bfac8 movq xmm0, qword ptr [0xa08c5c]
006bfad0 mov dword ptr [ebp - 0x20], eax
006bfad3 mov eax, dword ptr [0xa08c64]
006bfad8 push 2
006bfada movq qword ptr [ebp - 0x1c], xmm0
006bfadf mov dword ptr [ebp - 0x14], eax
006bfae2 call 0x7a7d50
006bfae7 test eax, eax
006bfae9 je 0x6bfeb3
006bfaef cmp dword ptr [edi + 0x130c], 0x24
006bfaf6 jne 0x6bfb3a
006bfaf8 mov ecx, edi
006bfafa call 0x786d30
006bfaff test al, al
006bfb01 je 0x6bfb3a
006bfb03 mov esi, dword ptr [ebp - 0xb8]
006bfb09 mov eax, 0x63
006bfb0e sub eax, dword ptr [edi + 0x1ccc]
006bfb14 mov ecx, edi
006bfb16 cmp eax, esi
006bfb18 push 0
006bfb1a cmovl esi, eax
006bfb1d push esi
006bfb1e call 0x724f00
006bfb23 mov ecx, dword ptr [ebp - 0xb8]
006bfb29 sub ecx, esi
006bfb2b mov byte ptr [ebp - 0x6d], 1
006bfb2f mov esi, dword ptr [ebp - 0x7c]
006bfb32 mov dword ptr [ebp - 0xb8], ecx
006bfb38 jmp 0x6bfb40
006bfb3a mov ecx, dword ptr [ebp - 0xb8]
006bfb40 mov edx, dword ptr [0xbfd65c]
006bfb46 mov dword ptr [ebp - 0x9c], 0
006bfb50 mov eax, dword ptr [edx + 0x1ba54]
006bfb56 sub eax, dword ptr [edx + 0x1ba50]
006bfb5c sar eax, 2
006bfb5f test eax, eax
006bfb61 je 0x6bfd5f
006bfb67 test ecx, ecx
006bfb69 jle 0x6bfd5f
006bfb6f push dword ptr [ebp - 0x9c]
006bfb75 mov ecx, edx
006bfb77 call 0x412750
006bfb7c mov dword ptr [ebp - 0x2c], eax
006bfb7f cmp byte ptr [eax + 0x16b], 0
006bfb86 jne 0x6bfd32
006bfb8c mov ecx, eax
006bfb8e call 0x786d30
006bfb93 test al, al
006bfb95 je 0x6bfd32
006bfb9b mov edx, dword ptr [ebp - 0x2c]
006bfb9e cmp edx, edi
006bfba0 je 0x6bfbe2
006bfba2 cmp dword ptr [edx + 0x2c], 1
006bfba6 jne 0x6bfd32
006bfbac mov eax, dword ptr [ebp - 0xb8]
006bfbb2 mov dword ptr [ebp - 0xac], eax
006bfbb8 mov ecx, edx
006bfbba call 0x78cdc0
006bfbbf cmp eax, 1
006bfbc2 je 0x6bfc4e
006bfbc8 cmp eax, 2
006bfbcb je 0x6bfc4e
006bfbd1 mov ecx, dword ptr [edx + 0x1ca8]
006bfbd7 mov eax, dword ptr [edx + 0x1290]
006bfbdd lea eax, [eax + ecx*2]
006bfbe0 jmp 0x6bfc54
006bfbe2 cmp dword ptr [edx + 0x2c], 0
006bfbe6 mov eax, dword ptr [ebp - 0xb8]
006bfbec mov dword ptr [ebp - 0xac], eax
006bfbf2 jne 0x6bfbb8
006bfbf4 cmp dword ptr [edx + 0x130c], 0x11
006bfbfb jne 0x6bfbb8
006bfbfd mov ecx, dword ptr [edx + 0x1cb8]
006bfc03 test ecx, ecx
006bfc05 je 0x6bfbb8
006bfc07 call 0x78cdc0
006bfc0c cmp eax, 1
006bfc0f je 0x6bfc2d
006bfc11 cmp eax, 2
006bfc14 je 0x6bfc2d
