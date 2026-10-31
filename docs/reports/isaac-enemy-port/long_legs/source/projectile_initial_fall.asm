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
