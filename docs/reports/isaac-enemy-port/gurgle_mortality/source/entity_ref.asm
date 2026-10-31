004229a0 push ebp
004229a1 mov ebp, esp
004229a3 and esp, 0xfffffff8
004229a6 mov edx, dword ptr [ebp + 8]
004229a9 sub esp, 0xc
004229ac push ebx
004229ad push esi
004229ae mov esi, ecx
004229b0 push edi
004229b1 test edx, edx
004229b3 je 0x4229da
004229b5 mov eax, dword ptr [edx + 0x28]
004229b8 mov dword ptr [esi], eax
004229ba mov eax, dword ptr [edx + 0x2c]
004229bd mov dword ptr [esi + 4], eax
004229c0 mov eax, dword ptr [edx + 0x34]
004229c3 mov dword ptr [esi + 8], eax
004229c6 mov eax, dword ptr [edx + 0x38]
004229c9 mov dword ptr [esi + 0xc], eax
004229cc mov eax, dword ptr [edx + 0x294]
004229d2 mov ecx, dword ptr [edx + 0x298]
004229d8 jmp 0x422a00
004229da mov dword ptr [esi], 0
004229e0 mov dword ptr [esi + 4], 0
004229e7 mov dword ptr [esi + 8], 0
004229ee mov dword ptr [esi + 0xc], 0
004229f5 mov eax, dword ptr [0xc02fec]
004229fa mov ecx, dword ptr [0xc02ff0]
00422a00 mov dword ptr [esp + 0x14], ecx
00422a04 lea ecx, [esp + 0x10]
00422a08 mov dword ptr [esp + 0x10], eax
00422a0c mov eax, dword ptr [ecx]
00422a0e mov ecx, dword ptr [ecx + 4]
00422a11 mov dword ptr [esi + 0x10], eax
00422a14 mov dword ptr [esi + 0x14], ecx
00422a17 test edx, edx
00422a19 je 0x422a29
00422a1b mov eax, dword ptr [edx + 0x2b8]
00422a21 mov ecx, dword ptr [edx + 0x2bc]
00422a27 jmp 0x422a34
00422a29 mov eax, dword ptr [0xc02fec]
00422a2e mov ecx, dword ptr [0xc02ff0]
00422a34 mov dword ptr [esp + 0x14], ecx
00422a38 lea ecx, [esp + 0x10]
00422a3c mov dword ptr [esp + 0x10], eax
00422a40 mov eax, dword ptr [ecx]
00422a42 mov ecx, dword ptr [ecx + 4]
00422a45 mov dword ptr [esi + 0x18], eax
00422a48 mov dword ptr [esi + 0x1c], ecx
00422a4b test edx, edx
00422a4d je 0x422a66
00422a4f mov eax, dword ptr [edx + 0x160]
00422a55 and eax, 0x100
00422a5a or eax, 0
00422a5d je 0x422a66
00422a5f mov edi, 1
00422a64 jmp 0x422a6c
00422a66 xor edi, edi
00422a68 test edx, edx
00422a6a je 0x422a83
00422a6c mov eax, dword ptr [edx + 0x160]
00422a72 and eax, 0x20000000
00422a77 or eax, 0
00422a7a je 0x422a85
00422a7c mov ebx, 2
00422a81 jmp 0x422a8b
00422a83 xor edi, edi
00422a85 xor ebx, ebx
00422a87 test edx, edx
00422a89 je 0x422aa4
00422a8b mov ecx, dword ptr [edx + 0x164]
00422a91 xor eax, eax
00422a93 and ecx, 0x400000
00422a99 or eax, ecx
00422a9b je 0x422aa4
00422a9d mov eax, 4
00422aa2 jmp 0x422aa6
00422aa4 xor eax, eax
00422aa6 or eax, ebx
00422aa8 mov dword ptr [esi + 0x24], edx
00422aab or eax, edi
00422aad mov dword ptr [esi + 0x20], eax
00422ab0 mov eax, esi
00422ab2 pop edi
00422ab3 pop esi
00422ab4 pop ebx
00422ab5 mov esp, ebp
00422ab7 pop ebp
00422ab8 ret 4
