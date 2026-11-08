00794930 push ebp
00794931 mov ebp, esp
00794933 and esp, 0xfffffff8
00794936 push ecx
00794937 push ebx
00794938 mov bl, byte ptr [ebp + 0xc]
0079493b push esi
0079493c push edi
0079493d mov edi, dword ptr [ebp + 8]
00794940 mov esi, ecx
00794942 mov ecx, dword ptr [0xbfd65c]
00794948 nop dword ptr [eax + eax]
00794950 mov edx, dword ptr [esi + 0x130c]
00794956 cmp edx, 0x28
00794959 jne 0x794969
0079495b mov eax, dword ptr [esi + 0x1d80]
00794961 test eax, eax
00794963 je 0x794969
00794965 mov esi, eax
00794967 jmp 0x794950
00794969 test edi, edi
0079496b jle 0x79497e
0079496d test bl, bl
0079496f jne 0x79497e
00794971 cmp dword ptr [ecx + 0x1c319c], 0x19
00794978 je 0x794ab3
0079497e cmp edx, 0x11
00794981 jne 0x794993
00794983 mov eax, dword ptr [esi + 0x1cb8]
00794989 test eax, eax
0079498b je 0x794993
0079498d xor bl, bl
0079498f mov esi, eax
00794991 jmp 0x794950
00794993 mov ecx, esi
00794995 call 0x78cdc0
0079499a cmp eax, 1
0079499d je 0x794ab3
007949a3 call 0x78cdc0
007949a8 cmp eax, 2
007949ab je 0x794ab3
007949b1 call 0x78cdc0
007949b6 cmp eax, 3
007949b9 jne 0x7949e9
007949bb test edi, edi
007949bd jle 0x794ab3
007949c3 push 0
007949c5 lea eax, [esi + 0x294]
007949cb push eax
007949cc lea eax, [edi*2 + 1]
007949d3 add eax, edi
007949d5 cdq 
007949d6 sub eax, edx
007949d8 sar eax, 1
007949da push eax
007949db call 0x725cc0
007949e0 pop edi
007949e1 pop esi
007949e2 pop ebx
007949e3 mov esp, ebp
007949e5 pop ebp
007949e6 ret 8
007949e9 cmp edx, 0x16
007949ec jne 0x7949f8
007949ee test bl, bl
007949f0 jne 0x7949f8
007949f2 test edi, edi
007949f4 jle 0x7949f8
007949f6 add edi, edi
007949f8 mov eax, dword ptr [esi + 0x1290]
007949fe mov ecx, dword ptr [esi + 0x1ca8]
00794a04 mov ebx, dword ptr [esi + 0x1cc4]
00794a0a lea ecx, [eax + ecx*2]
00794a0d mov eax, dword ptr [esi + 0x1294]
00794a13 add eax, edi
00794a15 cmp eax, ecx
00794a17 cmovl ecx, eax
00794a1a xor eax, eax
00794a1c test ecx, ecx
00794a1e cmovs ecx, eax
00794a21 mov dword ptr [esi + 0x1294], ecx
00794a27 mov ecx, esi
00794a29 test edi, edi
00794a2b jle 0x794a90
00794a2d and dword ptr [esi + 0x164], 0xfffffffb
00794a34 lea eax, [edi + 1]
00794a37 cdq 
00794a38 sub eax, edx
00794a3a mov dword ptr [esi + 0x12dc], 0
00794a44 sar eax, 1
00794a46 add eax, ebx
00794a48 mov dword ptr [esi + 0x1cc4], eax
00794a4e mov eax, dword ptr [esi + 0x160]
00794a54 mov dword ptr [esi + 0x160], eax
00794a5a call 0x78bf20
00794a5f mov ecx, esi
00794a61 call 0x78c810
00794a66 mov ecx, esi
00794a68 call 0x78cb90
00794a6d cmp dword ptr [esi + 0x1cc4], ebx
00794a73 jle 0x794ab3
00794a75 mov ecx, dword ptr [0xbfd65c]
00794a7b push esi
00794a7c lea ecx, [ecx + 0x3da4c]
00794a82 call 0x909fd0
00794a87 pop edi
00794a88 pop esi
00794a89 pop ebx
00794a8a mov esp, ebp
00794a8c pop ebp
00794a8d ret 8
00794a90 lea eax, [edi - 1]
00794a93 cdq 
00794a94 sub eax, edx
00794a96 sar eax, 1
00794a98 add eax, ebx
00794a9a mov dword ptr [esi + 0x1cc4], eax
00794aa0 call 0x78bf20
00794aa5 mov ecx, esi
00794aa7 call 0x78c810
00794aac mov ecx, esi
00794aae call 0x78cb90
00794ab3 pop edi
00794ab4 pop esi
00794ab5 pop ebx
00794ab6 mov esp, ebp
00794ab8 pop ebp
00794ab9 ret 8
00794abc int3 
00794abd int3 
00794abe int3 
00794abf int3 
