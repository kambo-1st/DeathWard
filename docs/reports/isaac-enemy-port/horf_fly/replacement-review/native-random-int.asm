007a7d50 push ebp
007a7d51 mov ebp, esp
007a7d53 push esi
007a7d54 mov esi, ecx
007a7d56 mov edx, dword ptr [esi]
007a7d58 test edx, edx
007a7d5a jne 0x7a7d72
007a7d5c push 0xb4d6c4
007a7d61 push 3
007a7d63 call 0x95e330
007a7d68 mov edx, dword ptr [esi]
007a7d6a add esp, 8
007a7d6d test edx, edx
007a7d6f jne 0x7a7d72
007a7d71 int3 
007a7d72 mov ecx, dword ptr [esi + 4]
007a7d75 mov eax, edx
007a7d77 shr eax, cl
007a7d79 mov ecx, dword ptr [esi + 8]
007a7d7c xor eax, edx
007a7d7e mov edx, eax
007a7d80 shl edx, cl
007a7d82 mov ecx, dword ptr [esi + 0xc]
007a7d85 xor edx, eax
007a7d87 mov eax, edx
007a7d89 shr eax, cl
007a7d8b mov ecx, dword ptr [ebp + 8]
007a7d8e xor eax, edx
007a7d90 mov dword ptr [esi], eax
007a7d92 test ecx, ecx
007a7d94 jne 0x7a7d9d
007a7d96 xor eax, eax
007a7d98 pop esi
007a7d99 pop ebp
007a7d9a ret 4
007a7d9d xor edx, edx
007a7d9f div ecx
007a7da1 pop esi
007a7da2 mov eax, edx
007a7da4 pop ebp
007a7da5 ret 4
