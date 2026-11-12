00705d10 push ebp
00705d11 mov ebp, esp
00705d13 and esp, 0xfffffff8
00705d16 sub esp, 0x14
00705d19 push ebx
00705d1a push esi
00705d1b mov esi, dword ptr [ebp + 8]
00705d1e mov ebx, ecx
00705d20 push edi
00705d21 mov eax, dword ptr [esi]
00705d23 test eax, eax
00705d25 jne 0x705d3d
00705d27 push 0xb4d6c4
00705d2c push 3
00705d2e call 0x95e330
00705d33 mov eax, dword ptr [esi]
00705d35 add esp, 8
00705d38 test eax, eax
00705d3a jne 0x705d3d
00705d3c int3
00705d3d mov ecx, dword ptr [esi + 4]
00705d40 mov edx, eax
00705d42 shr edx, cl
00705d44 mov ecx, dword ptr [esi + 8]
00705d47 xor edx, eax
00705d49 mov eax, edx
00705d4b shl eax, cl
00705d4d mov ecx, dword ptr [esi + 0xc]
00705d50 xor edx, eax
00705d52 mov eax, edx
00705d54 shr eax, cl
00705d56 xor edx, eax
00705d58 mov dword ptr [esi], edx
00705d5a mov dword ptr [ebx + 0x58], edx
00705d5d mov eax, dword ptr [esi]
00705d5f test eax, eax
00705d61 jne 0x705d79
00705d63 push 0xb4d6c4
00705d68 push 3
00705d6a call 0x95e330
00705d6f mov eax, dword ptr [esi]
00705d71 add esp, 8
00705d74 test eax, eax
00705d76 jne 0x705d79
00705d78 int3
00705d79 mov ecx, dword ptr [esi + 4]
00705d7c mov edx, eax
00705d7e shr edx, cl
00705d80 mov ecx, dword ptr [esi + 8]
00705d83 xor edx, eax
00705d85 mov eax, edx
00705d87 shl eax, cl
00705d89 mov ecx, dword ptr [esi + 0xc]
00705d8c xor edx, eax
00705d8e mov eax, edx
00705d90 shr eax, cl
00705d92 xor edx, eax
00705d94 mov dword ptr [esi], edx
00705d96 mov dword ptr [ebx + 0x5c], edx
00705d99 mov eax, dword ptr [esi]
00705d9b test eax, eax
00705d9d jne 0x705db5
00705d9f push 0xb4d6c4
00705da4 push 3
00705da6 call 0x95e330
00705dab mov eax, dword ptr [esi]
00705dad add esp, 8
00705db0 test eax, eax
00705db2 jne 0x705db5
00705db4 int3
00705db5 mov ecx, dword ptr [esi + 4]
00705db8 mov edi, eax
00705dba movq xmm0, qword ptr [0xa08db8]
00705dc2 shr edi, cl
00705dc4 mov ecx, dword ptr [esi + 8]
00705dc7 xor edi, eax
00705dc9 mov eax, edi
00705dcb movq qword ptr [esp + 0x14], xmm0
00705dd1 shl eax, cl
00705dd3 mov ecx, dword ptr [esi + 0xc]
00705dd6 xor edi, eax
00705dd8 mov eax, edi
00705dda shr eax, cl
00705ddc xor edi, eax
00705dde mov dword ptr [esi], edi
00705de0 mov esi, dword ptr [0xa08dc0]
00705de6 mov dword ptr [ebx + 0x60], edi
00705de9 jne 0x705dfb
00705deb push 0xb4d6c4
00705df0 push 3
00705df2 call 0x95e330
00705df7 add esp, 8
00705dfa int3
00705dfb mov ecx, dword ptr [esp + 0x14]
00705dff mov eax, edi
00705e01 shr eax, cl
00705e03 mov ecx, dword ptr [esp + 0x18]
00705e07 xor eax, edi
00705e09 mov edx, eax
00705e0b shl edx, cl
00705e0d mov ecx, esi
00705e0f xor edx, eax
00705e11 mov eax, edx
00705e13 shr eax, cl
00705e15 pop edi
00705e16 xor eax, edx
00705e18 pop esi
00705e19 mov dword ptr [ebx + 0x64], eax
00705e1c pop ebx
00705e1d mov esp, ebp
00705e1f pop ebp
00705e20 ret 4
