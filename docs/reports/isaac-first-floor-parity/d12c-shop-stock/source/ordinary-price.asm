007d0950 push ebp
007d0951 mov ebp, esp
007d0953 sub esp, 0x30
007d0956 movq xmm0, qword ptr [0xa08c44]
007d095e mov eax, ecx
007d0960 mov ecx, dword ptr [0xbfd65c]
007d0966 push ebx
007d0967 push esi
007d0968 mov esi, dword ptr [ebp + 0xc]
007d096b add ecx, 0x1ba40
007d0971 mov dword ptr [ebp - 8], eax
007d0974 mov eax, dword ptr [eax + 4]
007d0977 push edi
007d0978 mov edi, dword ptr [ebp + 8]
007d097b push 1
007d097d mov ebx, dword ptr [eax + 0x58]
007d0980 and ebx, 0xfffff800
007d0986 movq qword ptr [ebp - 0x18], xmm0
007d098b lea eax, [edi + esi]
007d098e or ebx, eax
007d0990 mov eax, dword ptr [0xa08c4c]
007d0995 push ecx
007d0996 push 0x2a0
007d099b mov dword ptr [ebp - 0x1c], ebx
007d099e mov dword ptr [ebp - 0xc], eax
007d09a1 mov dword ptr [ebp - 0x10], eax
007d09a4 call 0x91d340
007d09a9 mov ecx, dword ptr [0xbfd65c]
007d09af test eax, eax
007d09b1 setne byte ptr [ebp + 0xb]
007d09b5 add ecx, 0x1ba40
007d09bb mov dword ptr [ebp + 0xc], ecx
007d09be mov eax, dword ptr [ecx + 0x10]
007d09c1 mov edx, dword ptr [ecx + 0x14]
007d09c4 cmp eax, edx
007d09c6 je 0x7d0a06
007d09c8 mov ecx, eax
007d09ca nop word ptr [eax + eax]
007d09d0 mov ebx, dword ptr [ecx]
007d09d2 cmp dword ptr [ebx + 0x2c], 0
007d09d6 jne 0x7d09e1
007d09d8 cmp dword ptr [ebx + 0x130c], 0xe
007d09df je 0x7d0a60
007d09e1 add ecx, 4
007d09e4 cmp ecx, edx
007d09e6 jne 0x7d09d0
007d09e8 mov ecx, dword ptr [eax]
007d09ea cmp dword ptr [ecx + 0x2c], 0
007d09ee jne 0x7d09f9
007d09f0 cmp dword ptr [ecx + 0x130c], 0x21
007d09f7 je 0x7d0a60
007d09f9 add eax, 4
007d09fc cmp eax, edx
007d09fe jne 0x7d09e8
007d0a00 mov ebx, dword ptr [ebp - 0x1c]
007d0a03 mov ecx, dword ptr [ebp + 0xc]
007d0a06 push 1
007d0a08 push 0
007d0a0a push 0xab
007d0a0f call 0x91d550
007d0a14 test eax, eax
007d0a16 je 0x7d0a64
007d0a18 movq xmm0, qword ptr [0xa08e3c]
007d0a20 mov eax, dword ptr [0xa08e44]
007d0a25 movq qword ptr [ebp - 0x28], xmm0
007d0a2a mov dword ptr [ebp + 0xc], eax
007d0a2d test ebx, ebx
007d0a2f jne 0x7d0a41
007d0a31 push 0xb4d6c4
007d0a36 push 3
007d0a38 call 0x95e330
007d0a3d add esp, 8
007d0a40 int3
007d0a41 mov ecx, dword ptr [ebp - 0x28]
007d0a44 mov eax, ebx
007d0a46 shr eax, cl
007d0a48 mov ecx, dword ptr [ebp - 0x24]
007d0a4b xor eax, ebx
007d0a4d mov edx, eax
007d0a4f shl edx, cl
007d0a51 mov ecx, dword ptr [ebp + 0xc]
007d0a54 xor edx, eax
007d0a56 mov eax, edx
007d0a58 shr eax, cl
007d0a5a xor eax, edx
007d0a5c test al, 1
007d0a5e jne 0x7d0a64
007d0a60 mov bl, 1
007d0a62 jmp 0x7d0a66
007d0a64 xor bl, bl
007d0a66 mov edx, dword ptr [0xbfd65c]
007d0a6c cmp dword ptr [edx + 0x18194], -0xd
007d0a73 jne 0x7d0baa
007d0a79 cmp edi, 0x12c
007d0a7f ja 0x7d0b82
007d0a85 je 0x7d0b6a
007d0a8b cmp edi, 0xa
007d0a8e je 0x7d0b28
007d0a94 cmp edi, 0x64
007d0a97 jne 0x7d0de8
007d0a9d cmp byte ptr [ebp + 0xb], 0
007d0aa1 je 0x7d0abf
007d0aa3 test bl, bl
007d0aa5 jne 0x7d0abf
007d0aa7 push 2
007d0aa9 lea ecx, [ebp - 0x1c]
007d0aac call 0x7a7d50
007d0ab1 neg eax
007d0ab3 sbb eax, eax
007d0ab5 dec eax
007d0ab6 pop edi
007d0ab7 pop esi
007d0ab8 pop ebx
007d0ab9 mov esp, ebp
007d0abb pop ebp
007d0abc ret 0xc
007d0abf mov edx, dword ptr [ebp + 0x10]
007d0ac2 mov esi, 0xf
007d0ac7 lea ecx, [esi + 0xf]
007d0aca test edx, edx
007d0acc js 0x7d0b11
007d0ace mov eax, dword ptr [ebp - 8]
007d0ad1 mov eax, dword ptr [eax + 4]
007d0ad4 movsx eax, word ptr [eax + edx*2 + 0x94]
007d0adc sub eax, 0xc
007d0adf je 0x7d0b0c
007d0ae1 sub eax, 1
007d0ae4 je 0x7d0b0c
007d0ae6 sub eax, 1
007d0ae9 jne 0x7d0b11
007d0aeb mov esi, 0x14
007d0af0 mov ecx, 0x63
007d0af5 sub ecx, esi
007d0af7 inc ecx
007d0af8 push ecx
007d0af9 lea ecx, [ebp - 0x1c]
007d0afc call 0x7a7d50
007d0b01 add eax, esi
007d0b03 pop edi
007d0b04 pop esi
007d0b05 pop ebx
007d0b06 mov esp, ebp
007d0b08 pop ebp
007d0b09 ret 0xc
007d0b0c mov ecx, 0x32
007d0b11 sub ecx, esi
007d0b13 inc ecx
007d0b14 push ecx
007d0b15 lea ecx, [ebp - 0x1c]
007d0b18 call 0x7a7d50
007d0b1d add eax, esi
007d0b1f pop edi
007d0b20 pop esi
007d0b21 pop ebx
007d0b22 mov esp, ebp
007d0b24 pop ebp
007d0b25 ret 0xc
007d0b28 cmp byte ptr [ebp + 0xb], 0
007d0b2c je 0x7d0b36
007d0b2e test bl, bl
007d0b30 je 0x7d0c4d
007d0b36 cmp esi, 4
007d0b39 je 0x7d0b9c
007d0b3b cmp esi, 0xb
007d0b3e je 0x7d0b45
007d0b40 cmp esi, 6
007d0b43 jne 0x7d0b53
007d0b45 mov eax, 8
007d0b4a pop edi
007d0b4b pop esi
007d0b4c pop ebx
007d0b4d mov esp, ebp
007d0b4f pop ebp
007d0b50 ret 0xc
007d0b53 cmp esi, 3
007d0b56 jne 0x7d0de8
007d0b5c mov eax, 6
007d0b61 pop edi
007d0b62 pop esi
007d0b63 pop ebx
007d0b64 mov esp, ebp
007d0b66 pop ebp
007d0b67 ret 0xc
007d0b6a cmp byte ptr [ebp + 0xb], 0
007d0b6e je 0x7d0b5c
007d0b70 test bl, bl
007d0b72 jne 0x7d0b5c
007d0b74 mov eax, 0xfffffffb
007d0b79 pop edi
007d0b7a pop esi
007d0b7b pop ebx
007d0b7c mov esp, ebp
007d0b7e pop ebp
007d0b7f ret 0xc
007d0b82 cmp edi, 0x15e
007d0b88 jne 0x7d0de8
007d0b8e cmp byte ptr [ebp + 0xb], 0
007d0b92 je 0x7d0b9c
007d0b94 test bl, bl
007d0b96 je 0x7d0c4d
007d0b9c mov eax, 0xf
007d0ba1 pop edi
007d0ba2 pop esi
007d0ba3 pop ebx
007d0ba4 mov esp, ebp
007d0ba6 pop ebp
007d0ba7 ret 0xc
007d0baa mov eax, dword ptr [ebp - 8]
007d0bad mov ecx, dword ptr [eax + 8]
007d0bb0 cmp ecx, 0xe
007d0bb3 je 0x7d0d33
007d0bb9 cmp ecx, 0x16
007d0bbc je 0x7d0d33
007d0bc2 mov eax, dword ptr [eax + 4]
007d0bc5 mov eax, dword ptr [eax + 0x44]
007d0bc8 shr eax, 0xb
007d0bcb test al, 1
007d0bcd jne 0x7d0d33
007d0bd3 cmp ecx, 5
007d0bd6 jne 0x7d0bfe
007d0bd8 mov eax, dword ptr [edx + 0x1822c]
007d0bde shr eax, 0x11
007d0be1 test al, 1
007d0be3 jne 0x7d0d33
007d0be9 push 0x21
007d0beb lea ecx, [edx + 0x1ba40]
007d0bf1 call 0x5ef580
007d0bf6 test al, al
007d0bf8 jne 0x7d0d33
007d0bfe cmp dword ptr [ebp + 0x10], -2
007d0c02 je 0x7d0d33
007d0c08 cmp edi, 0xa
007d0c0b jne 0x7d0c31
007d0c0d cmp esi, 1
007d0c10 je 0x7d0c17
007d0c12 cmp esi, 2
007d0c15 jne 0x7d0c3b
007d0c17 cmp byte ptr [ebp + 0xb], 0
007d0c1b je 0x7d0c21
007d0c1d test bl, bl
007d0c1f je 0x7d0c4d
007d0c21 mov edx, 3
007d0c26 mov eax, edx
007d0c28 pop edi
007d0c29 pop esi
007d0c2a pop ebx
007d0c2b mov esp, ebp
007d0c2d pop ebp
007d0c2e ret 0xc
007d0c31 cmp edi, 0x28
007d0c34 jne 0x7d0c5b
007d0c36 cmp esi, 4
007d0c39 je 0x7d0c65
007d0c3b cmp byte ptr [ebp + 0xb], 0
007d0c3f je 0x7d0d19
007d0c45 test bl, bl
007d0c47 jne 0x7d0d19
007d0c4d mov eax, 0xfffffffb
007d0c52 pop edi
007d0c53 pop esi
007d0c54 pop ebx
007d0c55 mov esp, ebp
007d0c57 pop ebp
007d0c58 ret 0xc
007d0c5b cmp edi, 0x1e
007d0c5e jne 0x7d0c7f
007d0c60 cmp esi, 2
007d0c63 jne 0x7d0c3b
007d0c65 cmp byte ptr [ebp + 0xb], 0
007d0c69 je 0x7d0c6f
007d0c6b test bl, bl
007d0c6d je 0x7d0c4d
007d0c6f mov edx, 0xa
007d0c74 mov eax, edx
007d0c76 pop edi
007d0c77 pop esi
007d0c78 pop ebx
007d0c79 mov esp, ebp
007d0c7b pop ebp
007d0c7c ret 0xc
007d0c7f cmp edi, 0x64
007d0c82 jne 0x7d0c3b
007d0c84 mov ecx, dword ptr [0xbfd680]
007d0c8a push esi
007d0c8b lea ecx, [ecx + 0x29e84]
007d0c91 call 0x6fe5e0
007d0c96 cmp byte ptr [ebp + 0xb], 0
007d0c9a mov ecx, eax
007d0c9c je 0x7d0cc1
007d0c9e test bl, bl
007d0ca0 jne 0x7d0cc1
007d0ca2 test ecx, ecx
007d0ca4 je 0x7d0cb5
007d0ca6 movsx eax, word ptr [ecx + 0x7c]
007d0caa neg eax
007d0cac pop edi
007d0cad pop esi
007d0cae pop ebx
007d0caf mov esp, ebp
007d0cb1 pop ebp
007d0cb2 ret 0xc
007d0cb5 or eax, 0xffffffff
007d0cb8 pop edi
007d0cb9 pop esi
007d0cba pop ebx
007d0cbb mov esp, ebp
007d0cbd pop ebp
007d0cbe ret 0xc
007d0cc1 test ecx, ecx
007d0cc3 jne 0x7d0ce4
007d0cc5 push esi
007d0cc6 push 0xb4e034
007d0ccb push ecx
007d0ccc call 0x95e330
007d0cd1 mov edx, 0xf
007d0cd6 add esp, 0xc
007d0cd9 mov eax, edx
007d0cdb pop edi
007d0cdc pop esi
007d0cdd pop ebx
007d0cde mov esp, ebp
007d0ce0 pop ebp
007d0ce1 ret 0xc
007d0ce4 mov eax, dword ptr [ebp - 8]
007d0ce7 movsx edx, word ptr [ecx + 0x7e]
007d0ceb cmp dword ptr [eax + 8], 0xf
007d0cef jne 0x7d0c26
007d0cf5 cmp edx, 0xf
007d0cf8 jne 0x7d0c26
007d0cfe cmp word ptr [ecx + 0x7c], 2
007d0d03 jne 0x7d0c26
007d0d09 mov edx, 0x1e
007d0d0e mov eax, edx
007d0d10 pop edi
007d0d11 pop esi
007d0d12 pop ebx
007d0d13 mov esp, ebp
007d0d15 pop ebp
007d0d16 ret 0xc
007d0d19 xor edx, edx
007d0d1b cmp edi, 0x45
007d0d1e sete dl
007d0d21 lea edx, [edx*2 + 5]
007d0d28 mov eax, edx
007d0d2a pop edi
007d0d2b pop esi
007d0d2c pop ebx
007d0d2d mov esp, ebp
007d0d2f pop ebp
007d0d30 ret 0xc
007d0d33 movzx eax, byte ptr [ebp + 0xb]
007d0d37 test bl, bl
007d0d39 mov ecx, 1
007d0d3e cmovne eax, ecx
007d0d41 mov dword ptr [ebp + 0x10], eax
007d0d44 cmp edi, 0x64
007d0d47 jne 0x7d0ddb
007d0d4d mov ecx, dword ptr [0xbfd680]
007d0d53 push esi
007d0d54 lea ecx, [ecx + 0x29e84]
007d0d5a call 0x6fe5e0
007d0d5f test eax, eax
007d0d61 jne 0x7d0dab
007d0d63 push esi
007d0d64 push 0xb4e034
007d0d69 push eax
007d0d6a call 0x95e330
007d0d6f mov esi, dword ptr [ebp - 0x1c]
007d0d72 add esp, 0xc
007d0d75 test esi, esi
007d0d77 jne 0x7d0d89
007d0d79 push 0xb4d6c4
007d0d7e push 3
007d0d80 call 0x95e330
007d0d85 add esp, 8
007d0d88 int3
007d0d89 mov ecx, dword ptr [ebp - 0x18]
007d0d8c mov edx, esi
007d0d8e shr edx, cl
007d0d90 mov ecx, dword ptr [ebp - 0x14]
007d0d93 xor edx, esi
007d0d95 mov eax, edx
007d0d97 shl eax, cl
007d0d99 mov ecx, dword ptr [ebp - 0xc]
007d0d9c xor eax, edx
007d0d9e mov edx, eax
007d0da0 shr edx, cl
007d0da2 xor edx, eax
007d0da4 not edx
007d0da6 or edx, 0xfffffffe
007d0da9 jmp 0x7d0db8
007d0dab xor edx, edx
007d0dad cmp word ptr [eax + 0x7c], 1
007d0db2 setle dl
007d0db5 add edx, -2
007d0db8 cmp byte ptr [ebp + 0x10], 0
007d0dbc je 0x7d0c26
007d0dc2 cmp edx, -2
007d0dc5 mov eax, 0xf
007d0dca mov ecx, 0x1e
007d0dcf cmove eax, ecx
007d0dd2 pop edi
007d0dd3 pop esi
007d0dd4 pop ebx
007d0dd5 mov esp, ebp
007d0dd7 pop ebp
007d0dd8 ret 0xc
007d0ddb mov edx, 0xfffffffb
007d0de0 test al, al
007d0de2 je 0x7d0c26
007d0de8 pop edi
007d0de9 pop esi
007d0dea mov eax, 5
007d0def pop ebx
007d0df0 mov esp, ebp
007d0df2 pop ebp
