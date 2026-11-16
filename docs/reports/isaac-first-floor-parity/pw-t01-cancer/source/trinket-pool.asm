00701880 push ebp
00701881 mov ebp, esp
00701883 sub esp, 0x40
00701886 mov eax, dword ptr [0xbaa3b4]
0070188b xor eax, ebp
0070188d mov dword ptr [ebp - 8], eax
00701890 push ebx
00701891 push esi
00701892 mov esi, ecx
00701894 push edi
00701895 cmp dword ptr [esi + 0x798], 0
0070189c jg 0x7018a3
0070189e call 0x7045a0
007018a3 movups xmm0, xmmword ptr [esi + 0x664]
007018aa cmp byte ptr [ebp + 8], 0
007018ae lea eax, [esi + 0x664]
007018b4 mov dword ptr [ebp - 0x38], eax
007018b7 lea ebx, [ebp - 0x18]
007018ba cmove ebx, eax
007018bd mov dword ptr [ebp - 0x24], 0
007018c4 mov eax, dword ptr [esi + 0x790]
007018ca mov ecx, ebx
007018cc sub eax, dword ptr [esi + 0x78c]
007018d2 sar eax, 3
007018d5 push eax
007018d6 movups xmmword ptr [ebp - 0x18], xmm0
007018da mov dword ptr [ebp - 0x3c], ebx
007018dd call 0x7a7d50
007018e2 mov ecx, dword ptr [esi + 0x790]
007018e8 mov edi, eax
007018ea sub ecx, dword ptr [esi + 0x78c]
007018f0 movq xmm0, qword ptr [0xa08c44]
007018f8 mov eax, dword ptr [0xa08c4c]
007018fd mov ebx, dword ptr [ebx]
007018ff sar ecx, 3
00701902 shr ecx, 1
00701904 mov dword ptr [ebp - 0x34], ebx
00701907 movq qword ptr [ebp - 0x30], xmm0
0070190c mov dword ptr [ebp - 0x20], eax
0070190f mov dword ptr [ebp - 0x28], eax
00701912 mov dword ptr [ebp - 0x1c], ecx
00701915 nop word ptr [eax + eax]
00701920 mov eax, dword ptr [esi + 0x78c]
00701926 cmp byte ptr [eax + edi*8 + 4], 0
0070192b je 0x70196d
0070192d cmp byte ptr [eax + edi*8 + 5], 0
00701932 je 0x70196d
00701934 mov ecx, dword ptr [eax + edi*8]
00701937 mov eax, dword ptr [0xbfd680]
0070193c and ecx, 0x7fff
00701942 mov edx, dword ptr [eax + 0x29e90]
00701948 mov eax, dword ptr [eax + 0x29e94]
0070194e sub eax, edx
00701950 sar eax, 2
00701953 cmp ecx, eax
00701955 jge 0x70195c
00701957 mov ecx, dword ptr [edx + ecx*4]
0070195a jmp 0x70195e
0070195c xor ecx, ecx
0070195e push -1
00701960 call 0x6fe950
00701965 test al, al
00701967 jne 0x701a5b
0070196d mov edi, dword ptr [esi + 0x790]
00701973 sub edi, dword ptr [esi + 0x78c]
00701979 sar edi, 3
0070197c test ebx, ebx
0070197e jne 0x701990
00701980 push 0xb4d6c4
00701985 push 3
00701987 call 0x95e330
0070198c add esp, 8
0070198f int3
00701990 mov ecx, dword ptr [ebp - 0x30]
00701993 mov eax, ebx
00701995 shr eax, cl
00701997 mov ecx, dword ptr [ebp - 0x2c]
0070199a xor eax, ebx
0070199c mov edx, eax
0070199e shl edx, cl
007019a0 mov ecx, dword ptr [ebp - 0x20]
007019a3 xor edx, eax
007019a5 mov ebx, edx
007019a7 shr ebx, cl
007019a9 xor ebx, edx
007019ab mov dword ptr [ebp - 0x34], ebx
007019ae test edi, edi
007019b0 je 0x7019ba
007019b2 mov eax, ebx
007019b4 xor edx, edx
007019b6 div edi
007019b8 mov edi, edx
007019ba mov eax, dword ptr [ebp - 0x1c]
007019bd dec eax
007019be mov dword ptr [ebp - 0x1c], eax
007019c1 test eax, eax
007019c3 jg 0x701920
007019c9 push 0xb4ba98
007019ce push 0
007019d0 call 0x95e330
007019d5 mov eax, dword ptr [esi + 0x790]
007019db lea ecx, [ebp - 0x34]
007019de sub eax, dword ptr [esi + 0x78c]
007019e4 add esp, 8
007019e7 sar eax, 3
007019ea push eax
007019eb call 0x7a7d50
007019f0 mov edi, dword ptr [esi + 0x790]
007019f6 mov edx, eax
007019f8 mov ebx, dword ptr [esi + 0x78c]
007019fe mov ecx, edi
00701a00 sub ecx, ebx
00701a02 mov dword ptr [ebp - 0x20], 0
00701a09 sar ecx, 3
00701a0c test ecx, ecx
00701a0e je 0x701abe
00701a14 xor ecx, ecx
00701a16 sub edi, ebx
00701a18 lea eax, [edx + 1]
00701a1b sar edi, 3
00701a1e xor edx, edx
00701a20 div edi
00701a22 mov dword ptr [ebp - 0x1c], edx
00701a25 cmp byte ptr [ebx + edx*8 + 4], 0
00701a2a je 0x701a9f
00701a2c cmp byte ptr [ebx + edx*8 + 5], 0
00701a31 je 0x701a9f
00701a33 mov eax, dword ptr [0xbfd680]
00701a38 mov ecx, dword ptr [ebx + edx*8]
00701a3b and ecx, 0x7fff
00701a41 mov edx, dword ptr [eax + 0x29e90]
00701a47 mov eax, dword ptr [eax + 0x29e94]
00701a4d sub eax, edx
00701a4f sar eax, 2
00701a52 cmp ecx, eax
00701a54 jge 0x701a88
00701a56 mov ecx, dword ptr [edx + ecx*4]
00701a59 jmp 0x701a8a
00701a5b test edi, edi
00701a5d js 0x7019c9
00701a63 cmp byte ptr [ebp + 8], 0
00701a67 jne 0x701a7a
00701a69 mov eax, dword ptr [esi + 0x78c]
00701a6f mov byte ptr [eax + edi*8 + 4], 0
00701a74 dec dword ptr [esi + 0x798]
00701a7a mov eax, dword ptr [esi + 0x78c]
00701a80 mov eax, dword ptr [eax + edi*8]
00701a83 mov dword ptr [ebp - 0x24], eax
00701a86 jmp 0x701ac0
00701a88 xor ecx, ecx
00701a8a push -1
00701a8c call 0x6fe950
00701a91 test al, al
00701a93 jne 0x701b77
00701a99 mov ecx, dword ptr [ebp - 0x20]
00701a9c mov edx, dword ptr [ebp - 0x1c]
00701a9f mov edi, dword ptr [esi + 0x790]
00701aa5 inc ecx
00701aa6 mov ebx, dword ptr [esi + 0x78c]
00701aac mov eax, edi
00701aae sub eax, ebx
00701ab0 mov dword ptr [ebp - 0x20], ecx
00701ab3 sar eax, 3
00701ab6 cmp ecx, eax
00701ab8 jb 0x701a16
00701abe xor eax, eax
00701ac0 push dword ptr [ebp - 0x38]
00701ac3 push eax
00701ac4 call 0x8023d0
00701ac9 test eax, eax
00701acb jne 0x701bb2
00701ad1 mov eax, dword ptr [0xbfd680]
00701ad6 mov edi, dword ptr [0xbfd65c]
00701adc cmp byte ptr [eax + 0x2b5], 0
00701ae3 jne 0x701b09
00701ae5 cmp dword ptr [eax + 8], 2
00701ae9 jne 0x701b73
00701aef test edi, edi
00701af1 je 0x701b73
00701af7 cmp dword ptr [edi + 0x1c3204], 0
00701afe ja 0x701b09
00701b00 cmp byte ptr [edi + 0x1c31a1], 0
00701b07 je 0x701b73
00701b09 mov esi, dword ptr [ebp - 0x3c]
00701b0c movq xmm0, qword ptr [0xa08b84]
00701b14 mov ebx, dword ptr [0xa08b8c]
00701b1a movq qword ptr [ebp - 0x30], xmm0
00701b1f mov esi, dword ptr [esi]
00701b21 test esi, esi
00701b23 jne 0x701b3b
00701b25 push 0xb4d6c4
00701b2a push 3
00701b2c call 0x95e330
00701b31 add esp, 8
00701b34 int3
00701b35 mov edi, dword ptr [0xbfd65c]
00701b3b mov ecx, dword ptr [ebp - 0x30]
00701b3e mov eax, esi
00701b40 shr eax, cl
00701b42 mov ecx, dword ptr [ebp - 0x2c]
00701b45 xor eax, esi
00701b47 mov edx, eax
00701b49 shl edx, cl
00701b4b mov ecx, ebx
00701b4d xor edx, eax
00701b4f mov eax, 0x51eb851f
00701b54 mov esi, edx
00701b56 shr esi, cl
00701b58 xor esi, edx
00701b5a mul esi
00701b5c shr edx, 4
00701b5f imul eax, edx, 0x32
00701b62 sub esi, eax
00701b64 je 0x701ba2
00701b66 mov eax, dword ptr [edi + 0x1c3164]
00701b6c shr eax, 3
00701b6f test al, 1
00701b71 jne 0x701ba2
00701b73 xor cl, cl
00701b75 jmp 0x701ba4
00701b77 cmp byte ptr [ebp + 8], 0
00701b7b mov ecx, dword ptr [ebp - 0x1c]
00701b7e jne 0x701b91
00701b80 mov eax, dword ptr [esi + 0x78c]
00701b86 mov byte ptr [eax + ecx*8 + 4], 0
00701b8b dec dword ptr [esi + 0x798]
00701b91 mov eax, dword ptr [esi + 0x78c]
00701b97 mov eax, dword ptr [eax + ecx*8]
00701b9a mov dword ptr [ebp - 0x24], eax
00701b9d jmp 0x701ac0
00701ba2 mov cl, 1
00701ba4 mov eax, dword ptr [ebp - 0x24]
00701ba7 or eax, 0x8000
00701bac test cl, cl
00701bae cmove eax, dword ptr [ebp - 0x24]
00701bb2 mov ecx, dword ptr [ebp - 8]
00701bb5 pop edi
00701bb6 pop esi
00701bb7 xor ecx, ebp
00701bb9 pop ebx
00701bba call 0x9eacd7
00701bbf mov esp, ebp
00701bc1 pop ebp
00701bc2 ret 4
00701bc5 int3
00701bc6 int3
00701bc7 int3
