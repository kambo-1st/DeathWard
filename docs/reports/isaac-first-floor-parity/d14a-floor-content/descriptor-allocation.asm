00706680 push ebp
00706681 mov ebp, esp
00706683 sub esp, 0x1c
00706686 push ebx
00706687 push esi
00706688 mov esi, dword ptr [ebp + 0xc]
0070668b push edi
0070668c mov edi, ecx
0070668e mov dword ptr [ebp - 8], edi
00706691 mov eax, dword ptr [edi + 0x1819c]
00706697 mov dword ptr [ebp - 4], eax
0070669a test esi, esi
0070669c jne 0x7066ad
0070669e push 0xb4be98
007066a3 push 3
007066a5 call 0x95e330
007066aa add esp, 8
007066ad mov eax, dword ptr [edi + 0x1815c]
007066b3 cmp eax, 0x1fb
007066b8 jl 0x7066d9
007066ba push 0x1fb
007066bf push 0xb4bee8
007066c4 push 0
007066c6 call 0x95e330
007066cb add esp, 0xc
007066ce xor al, al
007066d0 pop edi
007066d1 pop esi
007066d2 pop ebx
007066d3 mov esp, ebp
007066d5 pop ebp
007066d6 ret 0x10
007066d9 movq xmm0, qword ptr [0xa08b30]
007066e1 lea ebx, [edi + 0x14]
007066e4 imul eax, eax, 0xb8
007066ea movq qword ptr [ebp - 0x18], xmm0
007066ef add ebx, eax
007066f1 mov eax, dword ptr [ebp + 0x10]
007066f4 mov dword ptr [ebp - 0x1c], eax
007066f7 mov ecx, ebx
007066f9 mov eax, dword ptr [0xa08b38]
007066fe mov dword ptr [ebp - 0x10], eax
00706701 lea eax, [ebp - 0x1c]
00706704 push eax
00706705 mov dword ptr [ebp - 0xc], ebx
00706708 call 0x705d10
0070670d mov eax, dword ptr [ebp + 8]
00706710 mov dword ptr [ebx + 0x10], esi
00706713 mov edx, dword ptr [eax + 8]
00706716 cmp edx, 0xc
00706719 ja 0x70672a
0070671b mov eax, dword ptr [eax + 0xc]
0070671e cmp eax, 0xc
00706721 ja 0x70672a
00706723 imul ecx, eax, 0xd
00706726 add ecx, edx
00706728 jmp 0x70672d
0070672a or ecx, 0xffffffff
0070672d mov dword ptr [ebx], ecx
0070672f lea eax, [ecx + 1]
00706732 cmp dword ptr [esi + 0x48], 9
00706736 mov esi, dword ptr [ebp + 8]
00706739 cmovne eax, ecx
0070673c mov dword ptr [ebx + 0x14], 0
00706743 mov ecx, dword ptr [0xbfd65c]
00706749 push 1
0070674b mov dword ptr [ebx + 4], eax
0070674e mov eax, dword ptr [ebp - 4]
00706751 push 0
00706753 mov dword ptr [ebx + 0xc], eax
00706756 lea ecx, [ecx + 0x1ba40]
0070675c mov eax, dword ptr [esi + 0x1c]
0070675f push 0x92
00706764 mov dword ptr [ebx + 0x18], eax
00706767 call 0x91d550
