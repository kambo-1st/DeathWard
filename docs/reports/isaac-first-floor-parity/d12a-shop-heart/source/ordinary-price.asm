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
