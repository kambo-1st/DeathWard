0062f1b0 push ebp
0062f1b1 mov ebp, esp
0062f1b3 and esp, 0xfffffff8
0062f1b6 push ecx
0062f1b7 push ebx
0062f1b8 push esi
0062f1b9 push edi
0062f1ba push dword ptr [ebp + 0x14]
0062f1bd mov esi, ecx
0062f1bf push dword ptr [ebp + 0x10]
0062f1c2 push dword ptr [ebp + 0xc]
0062f1c5 push dword ptr [ebp + 8]
0062f1c8 call 0x6819e0
0062f1cd mov eax, dword ptr [esi + 0x288]
0062f1d3 mov dword ptr [esi + 0x17c], 4
0062f1dd test eax, eax
0062f1df je 0x62f1ef
0062f1e1 push 1
0062f1e3 add eax, 0x74
0062f1e6 lea ecx, [esi + 0x3c]
0062f1e9 push eax
0062f1ea call 0x407160
0062f1ef mov dword ptr [esi + 0x360], 0xc1b80000
0062f1f9 call 0x6c3d90
0062f1fe mov dword ptr [esi + 0x368], 0
0062f208 mov dword ptr [esi + 0x370], 0x3f800000
0062f212 mov dword ptr [esi + 0x388], 0
0062f21c movd xmm0, eax
0062f220 cvtdq2pd xmm0, xmm0
0062f224 shr eax, 0x1f
0062f227 cmp dword ptr [esi + 0x2c], 2
0062f22b mov dword ptr [esi + 0x38c], 0
0062f235 mov dword ptr [esi + 0x374], 0x3f800000
0062f23f mov dword ptr [esi + 0x378], 0x3c75c28f
0062f249 mov dword ptr [esi + 0x37c], 0x3f8147ae
0062f253 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0062f25c mov dword ptr [esi + 0x380], 0
0062f266 mov dword ptr [esi + 0x390], 0xffffffff
0062f270 mov dword ptr [esi + 0x2e0], 0x3f800000
0062f27a mov dword ptr [esi + 0x398], 0
0062f284 cvtpd2ps xmm0, xmm0
0062f288 mov dword ptr [esi + 0x39c], 0
0062f292 mov dword ptr [esi + 0x3a0], 0
0062f29c mov dword ptr [esi + 0x3a4], 0x1e
0062f2a6 mov dword ptr [esi + 0x2dc], 0
0062f2b0 mulss xmm0, dword ptr [0xb6a19c]
0062f2b8 subss xmm0, dword ptr [0xb6a480]
0062f2c0 mulss xmm0, dword ptr [0xb6a350]
0062f2c8 movss dword ptr [esi + 0x364], xmm0
0062f2d0 movss xmm0, dword ptr [0xc02fec]
0062f2d8 movss dword ptr [esi + 0x3a8], xmm0
0062f2e0 movss xmm0, dword ptr [0xc02ff0]
0062f2e8 movss dword ptr [esi + 0x3ac], xmm0
0062f2f0 mov dword ptr [esi + 0x3b8], 0
0062f2fa jne 0x62f3ab
