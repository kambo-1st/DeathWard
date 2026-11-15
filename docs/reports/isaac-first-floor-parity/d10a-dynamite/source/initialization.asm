0067abbd mov eax, dword ptr [edi + 0x2c]
0067abc0 mov dword ptr [edi + 0x368], 0x42c80000
0067abca mov dword ptr [edi + 0x360], 0x2d
0067abd4 mov dword ptr [edi + 0x3a8], 0
0067abde mov dword ptr [edi + 0x3ac], 0
0067abe8 cmp eax, 3
0067abeb je 0x67abfc
0067abed cmp eax, 4
0067abf0 je 0x67abfc
0067abf2 cmp eax, 8
0067abf5 je 0x67abfc
0067abf7 cmp eax, 0x12
0067abfa jne 0x67ac65
0067abfc mov edx, dword ptr [edi + 0x334]
0067ac02 test edx, edx
0067ac04 jne 0x67ac20
0067ac06 push 0xb4d6c4
0067ac0b push 3
0067ac0d call 0x95e330
0067ac12 mov edx, dword ptr [edi + 0x334]
0067ac18 add esp, 8
0067ac1b test edx, edx
0067ac1d jne 0x67ac20
0067ac1f int3 
0067ac20 mov ecx, dword ptr [edi + 0x338]
0067ac26 mov eax, edx
0067ac28 shr eax, cl
0067ac2a mov ecx, dword ptr [edi + 0x33c]
0067ac30 xor eax, edx
0067ac32 mov edx, eax
0067ac34 shl edx, cl
0067ac36 mov ecx, dword ptr [edi + 0x340]
0067ac3c xor edx, eax
0067ac3e mov esi, edx
0067ac40 mov eax, 0x88888889
0067ac45 shr esi, cl
0067ac47 xor esi, edx
0067ac49 mul esi
0067ac4b mov dword ptr [edi + 0x334], esi
0067ac51 shr edx, 4
0067ac54 mov eax, edx
0067ac56 shl eax, 4
0067ac59 sub eax, edx
0067ac5b add eax, eax
0067ac5d sub esi, eax
0067ac5f add dword ptr [edi + 0x360], esi
0067ac65 mov eax, dword ptr [edi + 0x2c]
0067ac68 cmp eax, 0xf
0067ac6b jne 0x67ac83
0067ac6d mov dword ptr [edi + 0x360], 0x5e
0067ac77 mov dword ptr [edi + 0x368], 0x41a00000
0067ac81 jmp 0x67aca1
0067ac83 cmp eax, 0x11
0067ac86 je 0x67ac8d
0067ac88 cmp eax, 0x14
0067ac8b jne 0x67aca1
0067ac8d mov dword ptr [edi + 0x360], 0x57
0067ac97 mov dword ptr [edi + 0x368], 0x43960000
0067aca1 mov dword ptr [edi + 0x384], 0x3f800000
0067acab mov dword ptr [edi + 0x37c], 0
0067acb5 mov dword ptr [edi + 0x370], 0
0067acbf mov dword ptr [edi + 0x17c], 5
0067acc9 mov dword ptr [edi + 0x380], 0x40004
0067acd3 mov byte ptr [edi + 0x398], 0
0067acda mov dword ptr [edi + 0x388], 0
0067ace4 mov dword ptr [edi + 0x38c], 0
0067acee mov dword ptr [edi + 0x390], 0
0067acf8 mov dword ptr [edi + 0x394], 0
0067ad02 mov eax, dword ptr [edi + 0x288]
0067ad08 mov byte ptr [edi + 0x3b0], 0
0067ad0f mov dword ptr [edi + 0x374], 0
0067ad19 mov dword ptr [edi + 0x36c], 0
0067ad23 mov dword ptr [edi + 0x39c], 0x3f800000
0067ad2d mov dword ptr [edi + 0x3a0], 0
