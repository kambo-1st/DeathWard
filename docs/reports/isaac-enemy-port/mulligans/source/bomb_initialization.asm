0067aba0 push ebp
0067aba1 mov ebp, esp
0067aba3 and esp, 0xfffffff8
0067aba6 push ecx
0067aba7 push ebx
0067aba8 push esi
0067aba9 push edi
0067abaa push dword ptr [ebp + 0x14]
0067abad mov edi, ecx
0067abaf push dword ptr [ebp + 0x10]
0067abb2 push dword ptr [ebp + 0xc]
0067abb5 push dword ptr [ebp + 8]
0067abb8 call 0x6819e0
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
0067ad37 test eax, eax
0067ad39 je 0x67ad49
0067ad3b push 1
0067ad3d add eax, 0x74
0067ad40 lea ecx, [edi + 0x3c]
0067ad43 push eax
0067ad44 call 0x407160
0067ad49 mov eax, dword ptr [edi + 0x918]
0067ad4f mov dword ptr [edi + 0x91c], eax
0067ad55 mov eax, dword ptr [edi + 0x2c]
0067ad58 mov word ptr [edi + 0x3b2], 0
0067ad61 cmp eax, 2
0067ad64 jne 0x67adc3
0067ad66 mov esi, dword ptr [edi + 0x70]
0067ad69 test esi, esi
0067ad6b je 0x67adba
0067ad6d cmp dword ptr [esi + 0x14], 0x10
0067ad71 mov eax, esi
0067ad73 jb 0x67ad77
0067ad75 mov eax, dword ptr [esi]
0067ad77 mov ecx, 0xb3fd8c
0067ad7c nop dword ptr [eax]
0067ad80 mov dl, byte ptr [eax]
0067ad82 cmp dl, byte ptr [ecx]
0067ad84 jne 0x67ada0
0067ad86 test dl, dl
0067ad88 je 0x67ad9c
0067ad8a mov dl, byte ptr [eax + 1]
0067ad8d cmp dl, byte ptr [ecx + 1]
0067ad90 jne 0x67ada0
0067ad92 add eax, 2
0067ad95 add ecx, 2
0067ad98 test dl, dl
0067ad9a jne 0x67ad80
0067ad9c xor eax, eax
0067ad9e jmp 0x67ada5
0067ada0 sbb eax, eax
0067ada2 or eax, 1
0067ada5 test eax, eax
0067ada7 jne 0x67adba
0067ada9 cmp byte ptr [esi + 0x34], al
0067adac je 0x67ae36
0067adb2 cmp byte ptr [edi + 0x80], al
0067adb8 jne 0x67ae36
0067adba push 1
0067adbc push 0xb3fd8c
0067adc1 jmp 0x67ae1b
0067adc3 cmp eax, 4
0067adc6 je 0x67ade5
0067adc8 cmp eax, 3
0067adcb je 0x67ade5
0067adcd cmp eax, 8
0067add0 je 0x67ade5
0067add2 cmp eax, 0x11
0067add5 je 0x67ade5
0067add7 cmp eax, 0x12
0067adda je 0x67ade5
0067addc push 1
0067adde push 0xb402f8
0067ade3 jmp 0x67ae1b
0067ade5 cmp dword ptr [edi + 0x30], 1
0067ade9 push 1
0067adeb jne 0x67ae16
0067aded push 0xb48cb8
0067adf2 lea ecx, [edi + 0x3c]
0067adf5 call 0x405740
0067adfa test al, al
0067adfc je 0x67ae0d
0067adfe lea ecx, [edi + 0x6c]
0067ae01 call 0x405330
0067ae06 mov byte ptr [edi + 0x80], 1
0067ae0d mov ecx, edi
0067ae0f call 0x67f1b0
0067ae14 jmp 0x67ae36
0067ae16 push 0xb40360
0067ae1b lea ecx, [edi + 0x3c]
0067ae1e call 0x405740
0067ae23 test al, al
0067ae25 je 0x67ae36
0067ae27 lea ecx, [edi + 0x6c]
0067ae2a call 0x405330
0067ae2f mov byte ptr [edi + 0x80], 1
0067ae36 mov eax, dword ptr [edi + 0x2c]
0067ae39 mov dword ptr [edi + 0x378], 0
0067ae43 mov byte ptr [edi + 0x3b1], 0
0067ae4a cmp eax, 0x13
0067ae4d je 0x67ae54
0067ae4f cmp eax, 0x14
0067ae52 jne 0x67ae74
0067ae54 mov eax, dword ptr [edi + 0x164]
0067ae5a or dword ptr [edi + 0x160], 0x4000000
0067ae64 mov dword ptr [edi + 0x164], eax
0067ae6a mov dword ptr [edi + 0x2a8], 0xc1600000
0067ae74 push edi
0067ae75 call 0x7fe540
0067ae7a pop edi
0067ae7b pop esi
0067ae7c pop ebx
0067ae7d mov esp, ebp
0067ae7f pop ebp
0067ae80 ret 0x10
