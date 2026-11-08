00725810 push ebp
00725811 mov ebp, esp
00725813 and esp, 0xfffffff8
00725816 mov edx, dword ptr [ebp + 8]
00725819 sub esp, 0xc
0072581c push esi
0072581d mov esi, ecx
0072581f cmp dword ptr [esi + 0x130c], 0x19
00725826 jne 0x725850
00725828 test edx, edx
0072582a jle 0x725850
0072582c mov eax, 0x18
00725831 cmp edx, eax
00725833 cmovg edx, eax
00725836 test edx, edx
00725838 je 0x7258b7
0072583a push 0
0072583c lea eax, [esi + 0x294]
00725842 push eax
00725843 push edx
00725844 call 0x725cc0
00725849 pop esi
0072584a mov esp, ebp
0072584c pop ebp
0072584d ret 4
00725850 mov eax, dword ptr [esi + 0x12b4]
00725856 lea ecx, [esp + 4]
0072585a add eax, edx
0072585c mov dword ptr [esp + 8], 0x63
00725864 cmp eax, 0x63
00725867 mov dword ptr [esp + 4], eax
0072586b lea edx, [esp + 8]
0072586f mov dword ptr [esp + 0xc], 0
00725877 cmovge ecx, edx
0072587a lea eax, [esp + 0xc]
0072587e push 4
00725880 cmp dword ptr [ecx], 0
00725883 cmovg eax, ecx
00725886 mov ecx, esi
00725888 mov eax, dword ptr [eax]
0072588a mov dword ptr [esi + 0x12b4], eax
00725890 call 0x725af0
00725895 mov eax, dword ptr [0xbfd65c]
0072589a cmp dword ptr [eax + 0x101904], 2
007258a1 je 0x7258b7
007258a3 mov dword ptr [eax + 0x101904], 1
007258ad mov dword ptr [eax + 0x10190c], 2
007258b7 pop esi
007258b8 mov esp, ebp
007258ba pop ebp
007258bb ret 4
007258be int3 
007258bf int3 
