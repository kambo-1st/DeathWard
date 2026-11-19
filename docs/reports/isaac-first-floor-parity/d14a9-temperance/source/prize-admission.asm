0063aa21 cmp dword ptr [edi + 0x360], 2
0063aa28 jne 0x63aa89
0063aa2a cmp word ptr [edi + 0x36a], 0
0063aa32 jne 0x63aa89
0063aa34 mov eax, dword ptr [edi + 0x2c]
0063aa37 cmp eax, 4
0063aa3a je 0x63aa5a
0063aa3c cmp eax, 5
0063aa3f je 0x63aa5a
0063aa41 cmp eax, 7
0063aa44 je 0x63aa5a
0063aa46 cmp eax, 9
0063aa49 je 0x63aa5a
0063aa4b cmp eax, 0xd
0063aa4e je 0x63aa5a
0063aa50 cmp eax, 0x12
0063aa53 je 0x63aa5a
0063aa55 cmp eax, 0xe
0063aa58 jne 0x63aa7c
0063aa5a push 0xb4688c
0063aa5f lea ecx, [edi + 0x3c]
0063aa62 call 0x405640
0063aa67 test al, al
0063aa69 je 0x63aa7c
0063aa6b push 0xa081d4
0063aa70 lea ecx, [edi + 0x3c]
0063aa73 call 0x4056c0
0063aa78 test al, al
0063aa7a je 0x63aa89
0063aa7c mov eax, dword ptr [edi + 0x2c]
0063aa7f cmp eax, 6
0063aa82 je 0x63aa89
0063aa84 cmp eax, 0xf
0063aa87 jne 0x63aafc
0063aa89 mov eax, dword ptr [edi + 0x360]
0063aa8f cmp eax, 5
0063aa92 jne 0x63e45c
0063aa98 mov eax, dword ptr [edi + 0x2c]
0063aa9b cmp eax, 6
0063aa9e je 0x63aafc
0063aaa0 cmp eax, 0xf
0063aaa3 je 0x63aafc
0063aaa5 cmp eax, 9
0063aaa8 jne 0x63e643
0063aaae push 0xb46840
0063aab3 lea ecx, [edi + 0x3c]
0063aab6 call 0x4060f0
0063aabb test al, al
0063aabd je 0x63aac9
0063aabf mov dword ptr [edi + 0x370], 0x1e
0063aac9 push 0xa081d4
0063aace lea ecx, [edi + 0x3c]
0063aad1 call 0x4056c0
0063aad6 test al, al
0063aad8 je 0x63e643
0063aade push 0
0063aae0 push 0xb3fd8c
0063aae5 lea ecx, [edi + 0x3c]
0063aae8 mov dword ptr [edi + 0x360], 1
0063aaf2 call 0x4054f0
0063aaf7 jmp 0x63e643
0063aafc lea ebx, [edi + 0x334]
0063ab02 push 3
0063ab04 mov ecx, ebx
0063ab06 call 0x4076f0
0063ab0b push eax
0063ab0c lea ecx, [ebp - 0x30]
0063ab0f call 0x7a7cd0
0063ab14 mov dword ptr [ebp - 4], 0
0063ab1b mov eax, dword ptr [edi + 0x2c]
0063ab1e lea ecx, [eax - 1]
0063ab21 cmp ecx, 0x11
0063ab24 ja 0x63e3ee
0063ab2a jmp dword ptr [ecx*4 + 0x63e738]
