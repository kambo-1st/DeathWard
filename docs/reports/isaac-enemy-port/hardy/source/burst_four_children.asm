0063315b lea eax, [ebp - 0x39c]
00633161 push eax
00633162 call 0x659290
00633167 add esp, 4
0063316a lea esi, [edi + 0x2b8]
00633170 mov ecx, esi
00633172 call 0x962a00
00633177 lea eax, [ebp - 0x310]
0063317d push eax
0063317e lea ecx, [ebp - 0x39c]
00633184 fstp dword ptr [ebp - 0x310]
0063318a call 0x962bb0
0063318f lea eax, [edi + 0x3c]
00633192 mov dword ptr [ebp - 0x314], 0
0063319c mov dword ptr [ebp - 0x31c], eax
006331a2 lea ecx, [ebp - 0x358]
006331a8 call 0x9624d0
006331ad cmp dword ptr [ebp - 0x314], 2
006331b4 jae 0x6331be
006331b6 lea eax, [ebp - 0x39c]
006331bc jmp 0x6331e0
006331be movss xmm2, dword ptr [ebp - 0x39c]
006331c6 lea ecx, [ebp - 0x368]
006331cc xorps xmm2, xmmword ptr [0xb6c9b0]
006331d3 movss xmm1, dword ptr [ebp - 0x398]
006331db call 0x9624e0
006331e0 push eax
006331e1 lea ecx, [ebp - 0x358]
006331e7 call 0x962cd0
006331ec test byte ptr [ebp - 0x314], 1
006331f3 je 0x633213
006331f5 lea eax, [ebp - 0x32c]
006331fb push eax
006331fc lea ecx, [ebp - 0x358]
00633202 call 0x962b20
00633207 push eax
00633208 lea ecx, [ebp - 0x358]
0063320e call 0x962cd0
00633213 call 0x6c3d90
00633218 push 0
0063321a push 0xbeabf4
0063321f push 0xbeab18
00633224 push 0
00633226 push eax
00633227 push 0
00633229 push dword ptr [edi + 0x314]
0063322f lea eax, [ebp - 0x358]
00633235 push eax
00633236 push esi
00633237 lea eax, [ebp - 0x350]
0063323d push eax
0063323e lea ecx, [edi + 0x294]
00633244 call 0x962ac0
00633249 mov ecx, dword ptr [0xbfd65c]
0063324f push eax
00633250 push dword ptr [edi + 0x2c]
00633253 push dword ptr [edi + 0x28]
00633256 call 0x422e20
0063325b push eax
0063325c call 0x9ec34c
00633261 add esp, 0x10
00633264 mov edi, eax
00633266 mov ecx, edi
00633268 mov dword ptr [esp], 0xc13e0000
0063326f call 0x4424c0
00633274 mov esi, dword ptr [ebp - 0x320]
0063327a mov ecx, dword ptr [esi + 0x368]
00633280 mov dword ptr [edi + 0x368], ecx
00633286 call 0x659200
0063328b mulss xmm0, dword ptr [0xb6a350]
00633293 push ecx
00633294 mov ecx, edi
00633296 subss xmm0, dword ptr [0xb6a27c]
0063329e movss dword ptr [esp], xmm0
006332a3 call 0x436b70
006332a8 mov eax, dword ptr [edi]
006332aa push ecx
006332ab mov ecx, edi
006332ad mov dword ptr [esp], 0x3f800000
006332b4 call dword ptr [eax + 0x3c]
006332b7 mov ecx, dword ptr [esi + 0x388]
006332bd mov eax, dword ptr [esi + 0x38c]
006332c3 and ecx, 0xfffeffff
006332c9 mov dword ptr [edi + 0x388], ecx
006332cf mov dword ptr [edi + 0x38c], eax
006332d5 movss xmm0, dword ptr [esi + 0x370]
006332dd mulss xmm0, dword ptr [0xb6a4c4]
006332e5 push ecx
006332e6 mov ecx, edi
006332e8 movss dword ptr [esp], xmm0
006332ed call 0x4424e0
006332f2 mov ecx, dword ptr [ebp - 0x31c]
006332f8 mov esi, dword ptr [edi]
006332fa push 1
006332fc push 0
006332fe push 0xff
00633303 push -1
00633305 call 0x4023b0
0063330a push eax
0063330b mov ecx, edi
0063330d call dword ptr [esi + 0x38]
00633310 mov eax, dword ptr [ebp - 0x320]
00633316 mov ecx, edi
00633318 push dword ptr [eax + 0x314]
0063331e call 0x6818e0
00633323 mov eax, dword ptr [edi]
00633325 mov ecx, edi
00633327 call dword ptr [eax + 0xc]
0063332a mov eax, dword ptr [ebp - 0x314]
00633330 mov edi, dword ptr [ebp - 0x320]
00633336 inc eax
00633337 mov dword ptr [ebp - 0x314], eax
0063333d lea esi, [edi + 0x2b8]
00633343 cmp eax, 4
00633346 jl 0x6331a2
