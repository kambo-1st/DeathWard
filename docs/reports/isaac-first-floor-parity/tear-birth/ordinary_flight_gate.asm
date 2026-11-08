0064d43b cmp dword ptr [edi + 0x388], 0
0064d442 jg 0x64d794
0064d448 push 0xbc4ce0
0064d44d lea edx, [edi + 0x378]
0064d453 lea ecx, [ebp - 0x1eb4]
0064d459 call 0x412050
0064d45e add esp, 4
0064d461 mov ecx, eax
0064d463 call 0x427260
0064d468 test al, al
0064d46a je 0x64d794
0064d470 cmp byte ptr [edi + 0x16b], 0
0064d477 jne 0x64d794
0064d47d cmp dword ptr [edi + 0x3c8], 0
0064d484 jne 0x64d794
0064d48a push 0xbc4820
0064d48f lea edx, [edi + 0x378]
0064d495 lea ecx, [ebp - 0x1ec4]
0064d49b call 0x412050
0064d4a0 add esp, 4
0064d4a3 mov ecx, eax
0064d4a5 call 0x427260
0064d4aa test al, al
0064d4ac je 0x64d794
0064d4b2 push 0xbc4790
0064d4b7 lea edx, [edi + 0x378]
0064d4bd lea ecx, [ebp - 0x1ed4]
0064d4c3 call 0x412050
0064d4c8 add esp, 4
0064d4cb mov ecx, eax
0064d4cd call 0x427260
0064d4d2 test al, al
0064d4d4 jne 0x64d506
0064d4d6 cmp word ptr [edi + 0x3bc], 8
0064d4de jg 0x64d506
0064d4e0 lea ecx, [edi + 0x2b8]
0064d4e6 call 0x962a30
0064d4eb movss xmm0, dword ptr [0xb6a214]
0064d4f3 fstp dword ptr [ebp - 0x668]
0064d4f9 comiss xmm0, dword ptr [ebp - 0x668]
0064d500 jbe 0x64d794
0064d506 push 0xbc48a0
0064d50b lea edx, [edi + 0x378]
0064d511 lea ecx, [ebp - 0x1ee4]
0064d517 call 0x412050
0064d51c add esp, 4
0064d51f mov ecx, eax
0064d521 call 0x412090
0064d526 test al, al
0064d528 je 0x64d5eb
