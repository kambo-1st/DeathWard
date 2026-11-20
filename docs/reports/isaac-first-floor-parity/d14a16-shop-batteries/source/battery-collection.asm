006c0cf5 cmp eax, 0x5a
006c0cf8 jne 0x6c0f9e
006c0cfe lea edx, [edi + 0x14c4]
006c0d04 mov dword ptr [ebp - 0x80], 0
006c0d0b mov dword ptr [ebp - 0x14], edx
006c0d0e nop
006c0d10 mov ecx, dword ptr [0xbfd680]
006c0d16 push dword ptr [edx]
006c0d18 lea ecx, [ecx + 0x29e84]
006c0d1e call 0x6fe5e0
006c0d23 push dword ptr [ebp - 0x80]
006c0d26 mov ecx, edi
006c0d28 mov dword ptr [ebp - 0x8c], eax
006c0d2e call 0x757e40
006c0d33 mov edx, eax
006c0d35 mov eax, dword ptr [ebp - 0x8c]
006c0d3b test eax, eax
006c0d3d je 0x6c0d94
006c0d3f mov ecx, dword ptr [eax + 0xac]
006c0d45 cmp ecx, 1
006c0d48 je 0x6c0d4e
006c0d4a test ecx, ecx
006c0d4c jne 0x6c0d94
006c0d4e mov eax, dword ptr [esi + 0x30]
006c0d51 cmp eax, 3
006c0d54 jne 0x6c0d5b
006c0d56 lea ecx, [edx + edx]
006c0d59 jmp 0x6c0d6a
006c0d5b xor ecx, ecx
006c0d5d cmp eax, 2
006c0d60 setne cl
006c0d63 lea ecx, [ecx*4 + 2]
006c0d6a cmp eax, 3
006c0d6d push 0
006c0d6f sete al
006c0d72 movzx eax, al
006c0d75 push eax
006c0d76 push 1
006c0d78 push dword ptr [ebp - 0x80]
006c0d7b push ecx
006c0d7c mov ecx, edi
006c0d7e call 0x758030
006c0d83 test eax, eax
006c0d85 je 0x6c0d94
006c0d87 cmp dword ptr [esi + 0x30], 3
006c0d8b mov al, 1
006c0d8d mov byte ptr [ebp - 0x6d], al
006c0d90 jne 0x6c0db8
006c0d92 jmp 0x6c0d97
006c0d94 mov al, byte ptr [ebp - 0x6d]
006c0d97 mov ecx, dword ptr [ebp - 0x80]
006c0d9a mov edx, dword ptr [ebp - 0x14]
006c0d9d inc ecx
006c0d9e add edx, 0x1c
006c0da1 mov dword ptr [ebp - 0x80], ecx
006c0da4 mov dword ptr [ebp - 0x14], edx
006c0da7 cmp ecx, 4
006c0daa jb 0x6c0d10
006c0db0 test al, al
006c0db2 je 0x6c1f4c
006c0db8 mov ecx, dword ptr [0xbfd680]
006c0dbe push 1
006c0dc0 push 0xc3
006c0dc5 lea ecx, [ecx + 0x14]
006c0dc8 call 0x884e40
006c0dcd cmp dword ptr [esi + 0x30], 4
006c0dd1 jne 0x6c02a2
