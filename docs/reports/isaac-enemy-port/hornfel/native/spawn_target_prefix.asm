; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
006d0ca0 push ebp
006d0ca1 mov ebp, esp
006d0ca3 and esp, 0xfffffff8
006d0ca6 sub esp, 0x6c
006d0ca9 mov eax, dword ptr [ebp + 8]
006d0cac push ebx
006d0cad push esi
006d0cae mov esi, dword ptr [ebp + 0x18]
006d0cb1 push edi
006d0cb2 mov dword ptr [esp + 0x14], eax
006d0cb6 mov edi, ecx
006d0cb8 lea eax, [ebp + 0x20]
006d0cbb mov dword ptr [esp + 0x10], edi
006d0cbf push eax
006d0cc0 lea eax, [ebp + 0x1c]
006d0cc3 push eax
006d0cc4 mov eax, dword ptr [ebp + 0x14]
006d0cc7 push esi
006d0cc8 push eax
006d0cc9 mov eax, dword ptr [ebp + 0x10]
006d0ccc push eax
006d0ccd lea eax, [ebp + 0xc]
006d0cd0 push eax
006d0cd1 lea eax, [esp + 0x2c]
006d0cd5 push eax
006d0cd6 call 0x800fb0
006d0cdb mov ecx, dword ptr [esp + 0x14]
006d0cdf mov dword ptr [esp + 0x1c], ecx
006d0ce3 test esi, esi
006d0ce5 je 0x6d0d2d
006d0ce7 mov eax, dword ptr [esi + 0x160]
006d0ced and eax, 0x20000000
006d0cf2 or eax, 0
006d0cf5 je 0x6d0d2d
006d0cf7 cmp ecx, 0x3e8
006d0cfd jne 0x6d0d2d
006d0cff mov ebx, dword ptr [ebp + 0xc]
006d0d02 lea eax, [ebx - 0x16]
006d0d05 cmp eax, 4
006d0d08 ja 0x6d0d30
006d0d0a jmp dword ptr [eax*4 + 0x6d11a8]
006d0d11 mov ebx, 0x35
006d0d16 jmp 0x6d0d30
006d0d18 mov ebx, 0x2e
006d0d1d jmp 0x6d0d30
