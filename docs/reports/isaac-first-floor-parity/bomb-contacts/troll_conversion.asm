006ba6dc cmp dword ptr [edi + 0x2c], 0x28
006ba6e0 jne 0x6ba7cd
006ba6e6 mov eax, dword ptr [edi + 0x30]
006ba6e9 cmp eax, 3
006ba6ec jne 0x6ba71f
006ba6ee call 0x6c3d90
006ba6f3 push eax
006ba6f4 push 0
006ba6f6 push 0
006ba6f8 push 0xc02fec
006ba6fd lea eax, [edi + 0x294]
006ba703 push eax
006ba704 push 3
006ba706 push 4
006ba708 mov ecx, dword ptr [0xbfd65c]
006ba70e call 0x422e20
006ba713 mov eax, dword ptr [edi]
006ba715 mov ecx, edi
006ba717 call dword ptr [eax + 0x28]
006ba71a jmp 0x6bcedd
006ba71f cmp eax, 5
006ba722 jne 0x6ba755
006ba724 call 0x6c3d90
006ba729 mov ecx, dword ptr [0xbfd65c]
006ba72f push eax
006ba730 push 0
006ba732 push 0
006ba734 push 0xc02fec
006ba739 lea eax, [edi + 0x294]
006ba73f push eax
006ba740 push 4
006ba742 push 4
006ba744 call 0x422e20
006ba749 mov eax, dword ptr [edi]
006ba74b mov ecx, edi
006ba74d call dword ptr [eax + 0x28]
006ba750 jmp 0x6bcedd
006ba755 cmp eax, 6
006ba758 jne 0x6ba78b
006ba75a call 0x6c3d90
006ba75f mov ecx, dword ptr [0xbfd65c]
006ba765 push eax
006ba766 push 0
006ba768 push 0
006ba76a push 0xc02fec
006ba76f lea eax, [edi + 0x294]
006ba775 push eax
006ba776 push 0x12
006ba778 push 4
006ba77a call 0x422e20
006ba77f mov eax, dword ptr [edi]
006ba781 mov ecx, edi
006ba783 call dword ptr [eax + 0x28]
006ba786 jmp 0x6bcedd
006ba78b cmp dword ptr [edi + 0x34], 4
006ba78f jne 0x6ba7cd
006ba791 mov eax, dword ptr [edi + 0x38]
006ba794 cmp eax, 3
006ba797 je 0x6ba7a3
006ba799 cmp eax, 4
006ba79c je 0x6ba7a3
006ba79e cmp eax, 0x12
006ba7a1 jne 0x6ba7cd
006ba7a3 push 0xb40360
006ba7a8 lea ecx, [edi + 0x3c]
006ba7ab call 0x405640
006ba7b0 test al, al
006ba7b2 je 0x6ba7cd
006ba7b4 push 0
006ba7b6 push 0xb3fd8c
006ba7bb lea ecx, [edi + 0x3c]
006ba7be call 0x4054f0
006ba7c3 mov dword ptr [edi + 0x180], 4
