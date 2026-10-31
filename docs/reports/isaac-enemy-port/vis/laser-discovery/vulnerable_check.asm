00684630 push ebp
00684631 mov ebp, esp
00684633 and esp, 0xfffffff8
00684636 push esi
00684637 mov esi, ecx
00684639 push edi
0068463a mov edi, dword ptr [esi + 0x28]
0068463d lea eax, [edi - 0xa]
00684640 cmp eax, 0x3dd
00684645 ja 0x6846d0
0068464b mov eax, dword ptr [esi + 0x180]
00684651 cmp eax, 1
00684654 je 0x6846d0
00684656 test eax, eax
00684658 je 0x6846d0
0068465a cmp byte ptr [esi + 0x308], 0
00684661 jne 0x6846d0
00684663 cmp byte ptr [esi + 0x16b], 0
0068466a jne 0x6846d0
0068466c push 0
0068466e push 0x10
00684670 call 0x4122f0
00684675 test al, al
00684677 je 0x684689
00684679 cmp edi, 0x322
0068467f je 0x684689
00684681 cmp edi, 0x362
00684687 jne 0x6846d0
00684689 mov ecx, dword ptr [ebp + 8]
0068468c mov dl, 1
0068468e test ecx, ecx
00684690 je 0x6846d2
00684692 mov eax, dword ptr [esi + 0x160]
00684698 and eax, 0x20000000
0068469d or eax, 0
006846a0 je 0x6846d2
006846a2 call 0x681340
006846a7 mov ecx, eax
006846a9 mov eax, dword ptr [ecx + 0x160]
006846af and eax, 0x20000000
006846b4 or eax, 0
006846b7 jne 0x6846c6
006846b9 mov eax, dword ptr [ecx + 0x28]
006846bc cmp eax, 1
006846bf je 0x6846c6
006846c1 cmp eax, 3
006846c4 jne 0x6846d2
006846c6 xor al, al
006846c8 pop edi
006846c9 pop esi
006846ca mov esp, ebp
006846cc pop ebp
006846cd ret 4
006846d0 xor dl, dl
006846d2 pop edi
006846d3 mov al, dl
006846d5 pop esi
006846d6 mov esp, ebp
006846d8 pop ebp
006846d9 ret 4
006846dc int3 
006846dd int3 
006846de int3 
006846df int3 
006846e0 cmp dword ptr [ecx + 0x180], 0
006846e7 je 0x6846f7
006846e9 mov eax, dword ptr [ecx + 0x28]
006846ec cmp eax, 0x21
006846ef jne 0x6846fa
006846f1 cmp dword ptr [ecx + 0x2c], 0xa
006846f5 jb 0x684730
006846f7 xor al, al
006846f9 ret 
006846fa cmp eax, 0x124
006846ff je 0x684730
00684701 cmp eax, 0xf5
00684706 je 0x684730
00684708 cmp eax, 0x12e
0068470d je 0x684730
0068470f cmp eax, 0x2a
00684712 je 0x684730
00684714 cmp eax, 0xc9
00684719 je 0x684730
0068471b cmp eax, 0xcb
00684720 je 0x684730
00684722 cmp eax, 0xeb
00684727 je 0x684730
00684729 cmp eax, 0xca
0068472e jne 0x6846f7
00684730 mov al, 1
00684732 ret 
00684733 int3 
00684734 int3 
00684735 int3 
00684736 int3 
00684737 int3 
00684738 int3 
00684739 int3 
0068473a int3 
0068473b int3 
0068473c int3 
0068473d int3 
0068473e int3 
0068473f int3 
00684740 mov eax, dword ptr [ecx + 0x17c]
00684746 test eax, eax
00684748 je 0x68475c
0068474a cmp eax, 3
0068474d je 0x68475c
0068474f cmp eax, 1
00684752 je 0x68475c
00684754 cmp eax, 2
00684757 je 0x68475c
00684759 xor al, al
0068475b ret 
0068475c mov al, 1
0068475e ret 
0068475f int3 
00684760 lea eax, [ecx + 0x1b0]
00684766 add ecx, 0xe4
0068476c cmp ecx, eax
0068476e je 0x68478e
00684770 movups xmm0, xmmword ptr [eax]
00684773 movups xmmword ptr [ecx], xmm0
00684776 movups xmm0, xmmword ptr [eax + 0x10]
0068477a movups xmmword ptr [ecx + 0x10], xmm0
0068477e movq xmm0, qword ptr [eax + 0x20]
00684783 movq qword ptr [ecx + 0x20], xmm0
00684788 mov eax, dword ptr [eax + 0x28]
0068478b mov dword ptr [ecx + 0x28], eax
0068478e ret 
0068478f int3 
