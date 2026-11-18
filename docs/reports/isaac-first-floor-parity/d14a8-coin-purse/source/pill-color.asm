00702590 push ebp
00702591 mov ebp, esp
00702593 sub esp, 0x18
00702596 movq xmm0, qword ptr [0xa08b30]
0070259e push ebx
0070259f mov ebx, dword ptr [ebp + 8]
007025a2 movq qword ptr [ebp - 0x14], xmm0
007025a7 push esi
007025a8 push edi
007025a9 mov edi, dword ptr [0xa08b38]
007025af mov dword ptr [ebp - 8], edi
007025b2 test ebx, ebx
007025b4 jne 0x7025c6
007025b6 push 0xb4d6c4
007025bb push 3
007025bd call 0x95e330
007025c2 add esp, 8
007025c5 int3
007025c6 mov ecx, dword ptr [ebp - 0x14]
007025c9 mov edx, ebx
007025cb shr edx, cl
007025cd mov ecx, dword ptr [ebp - 0x10]
007025d0 xor edx, ebx
007025d2 mov eax, edx
007025d4 shl eax, cl
007025d6 mov ecx, edi
007025d8 xor eax, edx
007025da mov esi, eax
007025dc shr esi, cl
007025de xor esi, eax
007025e0 mov eax, 0x4ec4ec4f
007025e5 mul esi
007025e7 mov ebx, esi
007025e9 shr edx, 2
007025ec imul eax, edx, 0xd
007025ef sub ebx, eax
007025f1 inc ebx
007025f2 test esi, esi
007025f4 jne 0x702606
007025f6 push 0xb4d6c4
007025fb push 3
007025fd call 0x95e330
00702602 add esp, 8
00702605 int3
00702606 mov ecx, dword ptr [ebp - 0x14]
00702609 mov eax, esi
0070260b shr eax, cl
0070260d mov ecx, dword ptr [ebp - 0x10]
00702610 xor eax, esi
00702612 mov edx, eax
00702614 shl edx, cl
00702616 mov ecx, edi
00702618 xor edx, eax
0070261a mov eax, 0xd41d41d5
0070261f mov esi, edx
00702621 shr esi, cl
00702623 xor esi, edx
00702625 mul esi
00702627 mov eax, esi
00702629 mov ecx, esi
0070262b sub eax, edx
0070262d shr eax, 1
0070262f add eax, edx
00702631 shr eax, 7
00702634 imul eax, eax, 0x8c
0070263a sub ecx, eax
0070263c jne 0x70266f
0070263e mov eax, dword ptr [0xbfd680]
00702643 cmp byte ptr [eax + 0x2a7], cl
00702649 jne 0x70266a
0070264b cmp dword ptr [eax + 8], 2
0070264f jne 0x70266f
00702651 mov eax, dword ptr [0xbfd65c]
00702656 test eax, eax
00702658 je 0x70266f
0070265a cmp dword ptr [eax + 0x1c3204], ecx
00702660 ja 0x70266a
00702662 cmp byte ptr [eax + 0x1c31a1], cl
00702668 je 0x70266f
0070266a mov ebx, 0xe
0070266f test esi, esi
00702671 jne 0x702683
00702673 push 0xb4d6c4
00702678 push 3
0070267a call 0x95e330
0070267f add esp, 8
00702682 int3
00702683 mov ecx, dword ptr [ebp - 0x14]
00702686 mov edx, esi
00702688 shr edx, cl
0070268a mov eax, 0xd41d41d5
0070268f mov ecx, dword ptr [ebp - 0x10]
00702692 xor edx, esi
00702694 mov esi, edx
00702696 shl esi, cl
00702698 mov ecx, dword ptr [ebp - 8]
0070269b xor esi, edx
0070269d mov edi, esi
0070269f shr edi, cl
007026a1 xor edi, esi
007026a3 mul edi
007026a5 mov eax, edi
007026a7 sub eax, edx
007026a9 shr eax, 1
007026ab add eax, edx
007026ad shr eax, 6
007026b0 imul eax, eax, 0x46
007026b3 sub edi, eax
007026b5 jne 0x7026eb
007026b7 mov eax, dword ptr [0xbfd680]
007026bc cmp byte ptr [eax + 0x2aa], 0
007026c3 jne 0x7026e5
007026c5 cmp dword ptr [eax + 8], 2
007026c9 jne 0x7026eb
007026cb mov eax, dword ptr [0xbfd65c]
007026d0 test eax, eax
007026d2 je 0x7026eb
007026d4 cmp dword ptr [eax + 0x1c3204], edi
007026da ja 0x7026e5
007026dc cmp byte ptr [eax + 0x1c31a1], 0
007026e3 je 0x7026eb
007026e5 or ebx, 0x800
007026eb push dword ptr [ebp + 8]
007026ee push ecx
007026ef call 0x802790
007026f4 test eax, eax
007026f6 pop edi
007026f7 cmovne ebx, eax
007026fa pop esi
007026fb mov eax, ebx
007026fd pop ebx
007026fe mov esp, ebp
00702700 pop ebp
00702701 ret 4
