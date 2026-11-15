006e1947 cmp ecx, -0x64
006e194a je 0x6e19c8
006e194c mov ebx, dword ptr [esi + 0x158]
006e1952 cmp ebx, 7
006e1955 je 0x6e1a1b
006e195b cmp ebx, 8
006e195e je 0x6e1a1b
006e1964 cmp ebx, 0x1d
006e1967 je 0x6e1a1b
006e196d cmp ebx, 0xa
006e1970 je 0x6e1a1b
006e1976 mov eax, dword ptr [esi + 0x15c]
006e197c cmp eax, 9
006e197f je 0x6e19c5
006e1981 cmp dword ptr [edi + 0x1c319c], 0x18
006e1988 jne 0x6e199e
006e198a cmp eax, 7
006e198d je 0x6e19d9
006e198f cmp eax, 8
006e1992 je 0x6e19d9
006e1994 cmp eax, 0xb
006e1997 je 0x6e19d9
006e1999 cmp eax, 0x1d
006e199c jne 0x6e19c5
006e199e cmp eax, 4
006e19a1 jne 0x6e19d4
006e19a3 cmp byte ptr [ebp + 0xb], 0
006e19a7 jne 0x6e1a1b
006e19a9 cmp dword ptr [edi], 1
006e19ac jne 0x6e19bf
006e19ae mov ecx, edi
006e19b0 call 0x718ae0
006e19b5 mov ecx, dword ptr [esi + 0x27c]
006e19bb test al, al
006e19bd je 0x6e1a1b
006e19bf cmp byte ptr [ebp - 1], 0
006e19c3 jne 0x6e1a21
006e19c5 mov ebx, dword ptr [ebp + 0xc]
006e19c8 mov dword ptr [esi + 8], 1
006e19cf jmp 0x6e1864
006e19d4 cmp eax, 0x18
006e19d7 je 0x6e19c5
006e19d9 cmp eax, 0xc
006e19dc je 0x6e19c5
006e19de cmp eax, 2
006e19e1 jne 0x6e1a4b
006e19e3 cmp byte ptr [ebp + 0xb], 0
006e19e7 jne 0x6e1a1b
006e19e9 cmp dword ptr [edi], 1
006e19ec jne 0x6e19f9
006e19ee mov ecx, edi
006e19f0 call 0x718ae0
006e19f5 test al, al
006e19f7 je 0x6e1a15
006e19f9 mov ecx, edi
006e19fb call 0x6cba40
006e1a00 test al, al
006e1a02 jne 0x6e1a15
006e1a04 push 0x21
006e1a06 lea ecx, [edi + 0x1ba40]
006e1a0c call 0x5ef580
006e1a11 test al, al
006e1a13 je 0x6e19c5
006e1a15 mov ecx, dword ptr [esi + 0x27c]
006e1a1b cmp byte ptr [ebp - 1], 0
006e1a1f je 0x6e1a5f
006e1a21 cmp dword ptr [esi + 0x15c], 4
006e1a28 jne 0x6e1a5f
006e1a2a cmp ebx, 7
006e1a2d je 0x6e1a8d
006e1a2f cmp ebx, 8
006e1a32 je 0x6e1a8d
006e1a34 cmp ecx, dword ptr [edi + 0x18200]
006e1a3a jne 0x6e1a69
006e1a3c mov ebx, dword ptr [ebp + 0xc]
006e1a3f mov dword ptr [esi + 8], 1
006e1a46 jmp 0x6e1864
006e1a4b cmp eax, 5
006e1a4e jne 0x6e1a1b
006e1a50 test ecx, ecx
006e1a52 js 0x6e1a1b
006e1a54 cmp dword ptr [edi], 9
006e1a57 je 0x6e19c5
006e1a5d jmp 0x6e1a1b
006e1a5f cmp ebx, 7
006e1a62 je 0x6e1a8d
006e1a64 cmp ebx, 8
006e1a67 je 0x6e1a8d
