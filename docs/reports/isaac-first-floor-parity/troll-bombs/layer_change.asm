00403740 push ebp
00403741 mov ebp, esp
00403743 mov eax, dword ptr [ebp + 8]
00403746 push esi
00403747 mov esi, ecx
00403749 push edi
0040374a mov dword ptr [esi + 4], eax
0040374d mov eax, dword ptr [esi + 8]
00403750 test eax, eax
00403752 je 0x403764
00403754 push eax
00403755 call 0x9eace5
0040375a add esp, 4
0040375d mov dword ptr [esi + 8], 0
00403764 mov eax, dword ptr [esi + 0xc]
00403767 test eax, eax
00403769 je 0x40377b
0040376b push eax
0040376c call 0x9eace5
00403771 add esp, 4
00403774 mov dword ptr [esi + 0xc], 0
0040377b mov ecx, dword ptr [esi + 4]
0040377e mov edi, 4
00403783 test ecx, ecx
00403785 je 0x4037f4
00403787 mov eax, dword ptr [ecx + 0x1c]
0040378a test eax, eax
0040378c je 0x4037bd
0040378e xor ecx, ecx
00403790 mul edi
00403792 seto cl
00403795 neg ecx
00403797 or ecx, eax
00403799 push ecx
0040379a call 0x9eb09c
0040379f mov ecx, dword ptr [esi + 4]
004037a2 mov dword ptr [esi + 8], eax
004037a5 mov ecx, dword ptr [ecx + 0x1c]
004037a8 shl ecx, 2
004037ab push ecx
004037ac push 0xff
004037b1 push eax
004037b2 call 0x9ec152
004037b7 mov ecx, dword ptr [esi + 4]
004037ba add esp, 0x10
004037bd test ecx, ecx
004037bf je 0x4037f4
004037c1 mov eax, dword ptr [ecx + 0x24]
004037c4 test eax, eax
004037c6 je 0x4037f4
004037c8 xor ecx, ecx
004037ca mul edi
004037cc seto cl
004037cf neg ecx
004037d1 or ecx, eax
004037d3 push ecx
004037d4 call 0x9eb09c
004037d9 mov ecx, dword ptr [esi + 4]
004037dc mov dword ptr [esi + 0xc], eax
004037df mov ecx, dword ptr [ecx + 0x24]
004037e2 shl ecx, 2
004037e5 push ecx
004037e6 push 0xff
004037eb push eax
004037ec call 0x9ec152
004037f1 add esp, 0x10
004037f4 pop edi
004037f5 mov dword ptr [esi + 0x10], 0xbf800000
004037fc mov byte ptr [esi + 0x14], 0
00403800 mov dword ptr [esi + 0x18], 0
00403807 mov dword ptr [esi + 0x1c], 0
0040380e pop esi
0040380f pop ebp
00403810 ret 4
