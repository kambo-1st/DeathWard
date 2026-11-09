007a7aa0 push ebp
007a7aa1 mov ebp, esp
007a7aa3 and esp, 0xfffffff8
007a7aa6 sub esp, 0x1c
007a7aa9 mov eax, dword ptr [ecx]
007a7aab push ebx
007a7aac mov ebx, dword ptr [ecx + 4]
007a7aaf mov edx, ebx
007a7ab1 sub edx, eax
007a7ab3 mov dword ptr [esp + 0x14], ecx
007a7ab7 and edx, 0xfffffff8
007a7aba push esi
007a7abb push edi
007a7abc cmp edx, 0x10
007a7abf jl 0x7a7b98
007a7ac5 mov ecx, dword ptr [ebx - 8]
007a7ac8 add ebx, -8
007a7acb mov edx, dword ptr [eax + 4]
007a7ace xor edi, edi
007a7ad0 mov dword ptr [esp + 0x18], ecx
007a7ad4 xor esi, esi
007a7ad6 mov ecx, dword ptr [ebx + 4]
007a7ad9 mov dword ptr [esp + 0x10], ecx
007a7add mov ecx, dword ptr [eax]
007a7adf mov dword ptr [ebx], ecx
007a7ae1 mov dword ptr [ebx + 4], edx
007a7ae4 sub ebx, eax
007a7ae6 sar ebx, 3
007a7ae9 mov dword ptr [esp + 0x14], ebx
007a7aed lea ecx, [ebx - 1]
007a7af0 sar ecx, 1
007a7af2 mov dword ptr [esp + 0xc], ecx
007a7af6 test ecx, ecx
007a7af8 jle 0x7a7b3e
007a7afa mov ebx, ecx
007a7afc nop dword ptr [eax]
007a7b00 add esi, esi
007a7b02 mov ecx, dword ptr [eax + esi*8 + 8]
007a7b06 mov edx, dword ptr [eax + esi*8 + 0xc]
007a7b0a mov dword ptr [esp + 0x20], ecx
007a7b0e mov ecx, dword ptr [eax + esi*8 + 0x10]
007a7b12 mov dword ptr [esp + 0x20], ecx
007a7b16 xor ecx, ecx
007a7b18 cmp dword ptr [eax + esi*8 + 0x14], edx
007a7b1c setle cl
007a7b1f inc ecx
007a7b20 add esi, ecx
007a7b22 mov ecx, dword ptr [eax + esi*8]
007a7b25 mov edx, dword ptr [eax + esi*8 + 4]
007a7b29 mov dword ptr [eax + edi*8], ecx
007a7b2c mov dword ptr [eax + edi*8 + 4], edx
007a7b30 mov edi, esi
007a7b32 cmp esi, ebx
007a7b34 jl 0x7a7b00
007a7b36 mov ebx, dword ptr [esp + 0x14]
007a7b3a mov ecx, dword ptr [esp + 0xc]
007a7b3e cmp edi, ecx
007a7b40 jne 0x7a7b59
007a7b42 test bl, 1
007a7b45 jne 0x7a7b59
007a7b47 mov ecx, dword ptr [eax + ebx*8 - 8]
007a7b4b mov edx, dword ptr [eax + ebx*8 - 4]
007a7b4f mov dword ptr [eax + edi*8], ecx
007a7b52 mov dword ptr [eax + edi*8 + 4], edx
007a7b56 lea edi, [ebx - 1]
007a7b59 mov ebx, dword ptr [esp + 0x10]
007a7b5d test edi, edi
007a7b5f jle 0x7a7b7e
007a7b61 lea ecx, [edi - 1]
007a7b64 sar ecx, 1
007a7b66 mov edx, dword ptr [eax + ecx*8 + 4]
007a7b6a mov esi, dword ptr [eax + ecx*8]
007a7b6d cmp edx, ebx
007a7b6f jle 0x7a7b7e
007a7b71 mov dword ptr [eax + edi*8], esi
007a7b74 mov dword ptr [eax + edi*8 + 4], edx
007a7b78 mov edi, ecx
007a7b7a test ecx, ecx
007a7b7c jg 0x7a7b61
007a7b7e mov ecx, dword ptr [esp + 0x18]
007a7b82 mov dword ptr [eax + edi*8], ecx
007a7b85 mov dword ptr [eax + edi*8 + 4], ebx
007a7b89 mov eax, dword ptr [esp + 0x1c]
007a7b8d add dword ptr [eax + 4], -8
007a7b91 pop edi
007a7b92 pop esi
007a7b93 pop ebx
007a7b94 mov esp, ebp
007a7b96 pop ebp
007a7b97 ret
007a7b98 add dword ptr [ecx + 4], -8
007a7b9c pop edi
007a7b9d pop esi
007a7b9e pop ebx
007a7b9f mov esp, ebp
007a7ba1 pop ebp
007a7ba2 ret
007a7ba3 int3
007a7ba4 int3
007a7ba5 int3
007a7ba6 int3
007a7ba7 int3
007a7ba8 int3
007a7ba9 int3
007a7baa int3
007a7bab int3
007a7bac int3
007a7bad int3
007a7bae int3
007a7baf int3
