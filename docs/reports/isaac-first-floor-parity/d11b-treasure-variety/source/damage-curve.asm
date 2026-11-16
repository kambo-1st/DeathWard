00731b25 movss xmm0, dword ptr [edi + 0x13b8]
00731b2d lea edx, [ebp - 0x4b4]
00731b33 mulss xmm0, dword ptr [0xb6a670]
00731b3b lea ecx, [ebp - 0x4b8]
00731b41 mov dword ptr [ebp - 0x4b8], 0
00731b4b addss xmm0, dword ptr [0xb6a614]
00731b53 movss dword ptr [ebp - 0x4b4], xmm0
00731b5b call 0x417c70
00731b60 movss xmm0, dword ptr [eax]
00731b64 call 0x4228f0
00731b69 mulss xmm0, dword ptr [0xb6a8a0]
00731b71 mov ecx, edi
00731b73 push 0
00731b75 push 0xa9
00731b7a movss dword ptr [edi + 0x13b8], xmm0
