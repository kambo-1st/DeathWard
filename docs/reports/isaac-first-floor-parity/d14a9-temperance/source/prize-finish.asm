0063e3fe cmp dword ptr [edi + 0x360], 2
0063e405 jne 0x63e448
0063e407 push 0xa081d4
0063e40c lea ecx, [edi + 0x3c]
0063e40f call 0x4056c0
0063e414 test al, al
0063e416 je 0x63e448
0063e418 mov eax, dword ptr [edi + 0x2c]
0063e41b cmp eax, 1
0063e41e je 0x63e448
0063e420 cmp eax, 8
0063e423 je 0x63e448
0063e425 cmp eax, 0xa
0063e428 je 0x63e448
0063e42a cmp eax, 0xb
0063e42d je 0x63e448
0063e42f push 0
0063e431 push 0xb3fd8c
0063e436 lea ecx, [edi + 0x3c]
0063e439 mov dword ptr [edi + 0x360], 1
0063e443 call 0x4054f0
