0063334c mov ecx, dword ptr [edi + 0x38c]
00633352 xor eax, eax
00633354 and ecx, 8
00633357 or eax, ecx
00633359 je 0x633433
0063335f movss xmm3, dword ptr [0xb6a614]
00633367 lea eax, [edi + 0x294]
0063336d push ecx
0063336e mov ecx, dword ptr [0xbfd680]
00633374 mov dword ptr [esp], 0x3f800000
0063337b push 0
0063337d push 0x2d
0063337f push eax
00633380 push 0x1e3
00633385 call 0x8b14e0
0063338a xor esi, esi
0063338c nop dword ptr [eax]
00633390 call 0x6c3d90
00633395 mov ecx, dword ptr [0xbfd65c]
0063339b push eax
0063339c push 0
0063339e push dword ptr [edi + 0x320]
006333a4 lea eax, [edi + 0x294]
006333aa push 0xc02fec
006333af push eax
006333b0 push 0x94
006333b5 push 0x3e8
006333ba call 0x422e20
006333bf push edi
006333c0 mov ecx, eax
006333c2 mov dword ptr [ebp - 0x314], eax
006333c8 call 0x6818e0
006333cd movd xmm0, esi
006333d1 cvtdq2ps xmm0, xmm0
006333d4 push ecx
006333d5 mov ecx, dword ptr [ebp - 0x314]
006333db mulss xmm0, dword ptr [0xb6aae4]
006333e3 addss xmm0, dword ptr [0xb6a18c]
006333eb movss dword ptr [esp], xmm0
006333f0 call 0x427510
006333f5 push 0
006333f7 push 0x20000000
006333fc mov ecx, edi
006333fe call 0x4122f0
00633403 test al, al
00633405 jne 0x633417
00633407 mov eax, dword ptr [edi + 0x388]
0063340d and eax, 0x80000000
00633412 or eax, 0
00633415 je 0x633429
00633417 mov ecx, dword ptr [ebp - 0x314]
0063341d push 0
0063341f push 0x20000000
00633424 call 0x4122a0
00633429 inc esi
0063342a cmp esi, 4
0063342d jl 0x633390
