00758030 push ebp
00758031 mov ebp, esp
00758033 and esp, 0xfffffff8
00758036 sub esp, 0x1c
00758039 push ebx
0075803a mov ebx, dword ptr [ebp + 0xc]
0075803d push esi
0075803e push edi
0075803f mov edi, ecx
00758041 test ebx, ebx
00758043 jns 0x758077
00758045 xor ebx, ebx
00758047 xor esi, esi
00758049 nop dword ptr [eax]
00758050 push dword ptr [ebp + 0x14]
00758053 mov ecx, edi
00758055 push dword ptr [ebp + 0x10]
00758058 push dword ptr [ebp + 0x18]
0075805b push esi
0075805c push dword ptr [ebp + 8]
0075805f call 0x758030
00758064 inc esi
00758065 add ebx, eax
00758067 cmp esi, 4
0075806a jb 0x758050
0075806c mov eax, ebx
0075806e pop edi
0075806f pop esi
00758070 pop ebx
00758071 mov esp, ebp
00758073 pop ebp
00758074 ret 0x14
00758077 push ebx
00758078 call 0x757c80
0075807d mov dword ptr [esp + 0x24], eax
00758081 xor esi, esi
00758083 lea eax, [ebx*8]
0075808a sub eax, ebx
0075808c mov dword ptr [esp + 0x18], eax
00758090 mov ecx, dword ptr [edi + eax*4 + 0x14c4]
00758097 test ecx, ecx
00758099 je 0x7582c0
0075809f push ecx
007580a0 mov ecx, dword ptr [0xbfd680]
007580a6 lea ecx, [ecx + 0x29e84]
007580ac call 0x6fe5e0
007580b1 mov esi, dword ptr [ebp + 8]
007580b4 mov dword ptr [esp + 0x1c], eax
007580b8 test esi, esi
007580ba jle 0x7580e6
007580bc cmp byte ptr [ebp + 0x18], 0
007580c0 jne 0x7580e6
007580c2 mov eax, dword ptr [eax + 0xac]
007580c8 test eax, eax
007580ca je 0x7580e6
007580cc cmp eax, 1
007580cf je 0x7580dc
007580d1 xor eax, eax
007580d3 pop edi
007580d4 pop esi
007580d5 pop ebx
007580d6 mov esp, ebp
007580d8 pop ebp
007580d9 ret 0x14
007580dc push ebx
007580dd mov ecx, edi
007580df call 0x757e40
007580e4 mov esi, eax
007580e6 push ebx
007580e7 mov ecx, edi
007580e9 call 0x757e40
007580ee mov dword ptr [esp + 0x14], eax
007580f2 test esi, esi
007580f4 jle 0x7583ca
007580fa lea ecx, [ebx + 0xbe]
00758100 lea edx, [ecx*8]
00758107 sub edx, ecx
00758109 xor ecx, ecx
0075810b mov dword ptr [esp + 0x20], edx
0075810f push 0
00758111 push 0x3f
00758113 mov edx, dword ptr [edi + edx*4]
00758116 sub eax, edx
00758118 test eax, eax
0075811a cmovg ecx, eax
0075811d mov eax, esi
0075811f cmp ecx, esi
00758121 cmovl eax, ecx
00758124 mov ecx, dword ptr [esp + 0x28]
00758128 mov dword ptr [esp + 0x18], eax
0075812c add eax, edx
0075812e sub esi, dword ptr [esp + 0x18]
00758132 mov dword ptr [edi + ecx*4], eax
00758135 mov ecx, edi
00758137 call 0x73af30
0075813c test al, al
0075813e jne 0x758149
00758140 cmp byte ptr [ebp + 0x14], al
00758143 je 0x758327
