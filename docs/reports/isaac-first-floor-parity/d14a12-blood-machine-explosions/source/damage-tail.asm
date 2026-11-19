00640df4 mov eax, dword ptr [ebx + 0x2c]
00640df7 cmp eax, 4
00640dfa je 0x640e23
00640dfc cmp eax, 5
00640dff je 0x640e23
00640e01 cmp eax, 7
00640e04 je 0x640e23
00640e06 cmp eax, 6
00640e09 je 0x640e23
00640e0b cmp eax, 9
00640e0e je 0x640e23
00640e10 cmp eax, 0xf
00640e13 je 0x640e23
00640e15 cmp eax, 0xd
00640e18 je 0x640e23
00640e1a cmp eax, 0x12
00640e1d jne 0x640eda
00640e23 call 0x6c3d90
00640e28 mov ecx, dword ptr [0xbfd65c]
00640e2e push 0
00640e30 push eax
00640e31 push 0
00640e33 push 0
00640e35 push 0xc02fec
00640e3a lea eax, [ebx + 0x294]
00640e40 push eax
00640e41 push 2
00640e43 push 0x3e8
00640e48 call 0x6d0ca0
00640e4d push 0
00640e4f push 0xbeaaec
00640e54 push 0xbeab18
00640e59 push 0
00640e5b push eax
00640e5c call 0x9ec34c
00640e61 add esp, 0x14
00640e64 mov ecx, ebx
00640e66 mov dword ptr [eax + 0xd0], 0
00640e70 mov dword ptr [eax + 0xd4], 0xc1200000
00640e7a call 0x68b970
00640e7f mov eax, dword ptr [ebx]
00640e81 mov ecx, ebx
00640e83 call dword ptr [eax + 0x28]
00640e86 mov eax, dword ptr [ebx + 0x2c]
00640e89 cmp eax, 4
00640e8c je 0x640ece
00640e8e cmp eax, 5
00640e91 jne 0x640ea1
00640e93 mov eax, dword ptr [0xbfd65c]
00640e98 or dword ptr [eax + 0x1822c], 2
00640e9f jmp 0x640eda
00640ea1 cmp eax, 0xd
00640ea4 jne 0x640ec9
00640ea6 mov ecx, dword ptr [0xbfd680]
00640eac mov eax, dword ptr [0xbfd65c]
00640eb1 push 1
00640eb3 push 0x1ee
00640eb8 lea ecx, [ecx + 0x14]
00640ebb or dword ptr [eax + 0x1822c], 1
00640ec2 call 0x884e40
00640ec7 jmp 0x640eda
00640ec9 cmp eax, 0x12
00640ecc jne 0x640eda
00640ece mov eax, dword ptr [0xbfd65c]
00640ed3 or dword ptr [eax + 0x1822c], 1
00640eda cmp dword ptr [ebx + 0x2c], 0xc
00640ede jne 0x640ef9
00640ee0 push 0
00640ee2 push 0xb454ec
00640ee7 lea ecx, [ebx + 0x3c]
00640eea call 0x4054f0
00640eef mov dword ptr [ebx + 0x360], 3
00640ef9 mov ecx, ebx
00640efb call 0x63f660
00640f00 pop edi
00640f01 pop esi
00640f02 mov al, 1
00640f04 pop ebx
00640f05 mov esp, ebp
00640f07 pop ebp
00640f08 ret 0x14
