0063937a mov eax, dword ptr [0xbfd680]
0063937f lea ecx, [ebx + 0x3c]
00639382 mov dword ptr [ebx + 0x2a8], 0xc1000000
0063938c push 0
0063938e mov dword ptr [ebx + 0x2cc], 0x3fc00000
00639398 mov dword ptr [ebx + 0x2d0], 0x3f400000
006393a2 mov edi, dword ptr [eax + 0x31c]
006393a8 push 0xb46840
006393ad call 0x405850
006393b2 mov eax, 0x51eb851f
006393b7 mov ecx, 0xa
006393bc imul edi
006393be sar edx, 5
006393c1 mov eax, edx
006393c3 shr eax, 0x1f
006393c6 add eax, edx
006393c8 cdq
006393c9 idiv ecx
006393cb lea ecx, [ebx + 0x3c]
006393ce push edx
006393cf push 1
006393d1 call 0x405950
006393d6 mov eax, 0x66666667
006393db mov ecx, 0xa
006393e0 imul edi
006393e2 sar edx, 2
006393e5 mov esi, edx
006393e7 shr esi, 0x1f
006393ea add esi, edx
006393ec mov eax, esi
006393ee cdq
006393ef idiv ecx
006393f1 lea ecx, [ebx + 0x3c]
006393f4 push edx
006393f5 push 2
006393f7 call 0x405950
006393fc lea eax, [esi + esi*4]
006393ff add eax, eax
00639401 lea ecx, [ebx + 0x3c]
00639404 sub edi, eax
00639406 push edi
00639407 push 3
00639409 call 0x405950
0063940e mov edi, dword ptr [0xbfd65c]
00639414 mov ecx, edi
00639416 push 0x11
00639418 call 0x41c430
0063941d test al, al
0063941f jne 0x63942c
00639421 mov ecx, edi
00639423 call 0x6d7180
00639428 test al, al
0063942a je 0x639433
0063942c mov eax, dword ptr [ebx]
0063942e mov ecx, ebx
00639430 call dword ptr [eax + 0x28]
00639433 mov ecx, dword ptr [0xbfd65c]
00639439 push 0x12
0063943b call 0x41c430
00639440 test al, al
00639442 je 0x639593
00639448 call 0x6c3d90
0063944d and eax, 3
00639450 lea ecx, [ebx + 0x3c]
00639453 push 0
00639455 push dword ptr [eax*4 + 0xb469c8]
0063945c call 0x4054f0
00639461 mov dword ptr [ebx + 0x360], 3
