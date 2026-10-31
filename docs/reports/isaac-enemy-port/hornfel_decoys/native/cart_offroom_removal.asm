; Installed Repentance 1.7.9b; bounded evidence, names are interpretations.
004bbf75 mov eax, dword ptr [edi + 0x318]
004bbf7b test eax, eax
004bbf7d je 0x4bbf92
004bbf7f cmp dword ptr [eax + 0x28], 0x38a
004bbf86 jne 0x4bbf92
004bbf88 cmp dword ptr [eax + 0x2c], 0
004bbf8c je 0x4bc01a
004bbf92 cmp dword ptr [edi + 0x2c], 0xa
004bbf96 jne 0x4bbfb1
004bbf98 push ecx
004bbf99 mov dword ptr [esp], 0xc3960000
004bbfa0 mov ecx, ebx
004bbfa2 push edx
004bbfa3 call 0x7cf0a0
004bbfa8 xor ecx, ecx
004bbfaa test al, al
004bbfac sete cl
004bbfaf jmp 0x4bbfbe
004bbfb1 push edx
004bbfb2 mov ecx, ebx
004bbfb4 call 0x7ce950
004bbfb9 mov ecx, eax
004bbfbb shr ecx, 0x1f
004bbfbe test ecx, ecx
004bbfc0 je 0x4bc01a
004bbfc2 cmp dword ptr [edi + 0xab4], 0
004bbfc9 jne 0x4bbfd2
004bbfcb mov ecx, edi
004bbfcd call 0x4bba40
004bbfd2 mov ecx, dword ptr [edi + 0x318]
004bbfd8 mov dword ptr [edi + 0xab4], 3
004bbfe2 test ecx, ecx
004bbfe4 je 0x4bbfeb
004bbfe6 mov eax, dword ptr [ecx]
004bbfe8 call dword ptr [eax + 0x28]
004bbfeb mov eax, dword ptr [edi]
004bbfed mov ecx, edi
004bbfef call dword ptr [eax + 0x28]
004bbff2 pop edi
004bbff3 pop esi
004bbff4 pop ebx
004bbff5 mov ecx, dword ptr [esp + 0x40]
004bbff9 xor ecx, esp
004bbffb call 0x9eacd7
004bc000 mov esp, ebp
004bc002 pop ebp
004bc003 ret 
004bc004 cmp eax, 3
004bc007 jne 0x4bc01a
004bc009 mov dword ptr [edi + 0x180], 0
004bc013 mov byte ptr [edi + 0x169], 0
