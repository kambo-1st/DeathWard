0063e928 cmp ecx, 0xf
0063e92b jne 0x63e941
0063e92d mov eax, dword ptr [edi + 0x360]
0063e933 cmp eax, 2
0063e936 je 0x63ea6a
0063e93c cmp eax, 1
0063e93f jne 0x63e94c
0063e941 mov ecx, ebx
0063e943 call 0x638fe0
0063e948 test al, al
0063e94a je 0x63e957
0063e94c xor al, al
0063e94e pop edi
0063e94f pop esi
0063e950 pop ebx
0063e951 mov esp, ebp
0063e953 pop ebp
0063e954 ret 8
0063e957 cmp dword ptr [ebx + 0x1308], 0xf
0063e95e jge 0x63ee90
0063e964 mov eax, dword ptr [0xbfd65c]
0063e969 mov dword ptr [esp + 0x10], 0x20
0063e971 cmp dword ptr [eax + 0x1c319c], 0x1e
0063e978 jne 0x63e982
0063e97a mov dword ptr [esp + 0x10], 0x820
0063e982 mov dword ptr [ebx + 0x1308], 0
0063e98c mov eax, dword ptr [edi + 0x28]
0063e98f movss xmm0, dword ptr [edi + 0x294]
0063e997 movss xmm1, dword ptr [edi + 0x298]
0063e99f mov ecx, dword ptr [edi + 0x160]
0063e9a5 mov edx, dword ptr [edi + 0x164]
0063e9ab mov dword ptr [esp + 0x20], eax
0063e9af mov eax, dword ptr [edi + 0x2c]
0063e9b2 mov dword ptr [esp + 0x24], eax
0063e9b6 mov eax, dword ptr [edi + 0x34]
0063e9b9 mov dword ptr [esp + 0x28], eax
0063e9bd mov eax, dword ptr [edi + 0x38]
0063e9c0 mov dword ptr [esp + 0x2c], eax
0063e9c4 mov eax, ecx
0063e9c6 movss dword ptr [esp + 0x30], xmm0
0063e9cc and eax, 0x100
0063e9d1 or eax, 0
0063e9d4 movss xmm0, dword ptr [edi + 0x2b8]
0063e9dc movss dword ptr [esp + 0x34], xmm1
0063e9e2 movss xmm1, dword ptr [edi + 0x2bc]
0063e9ea movss dword ptr [esp + 0x38], xmm0
0063e9f0 movss dword ptr [esp + 0x3c], xmm1
0063e9f6 je 0x63e9ff
0063e9f8 mov esi, 1
0063e9fd jmp 0x63ea01
0063e9ff xor esi, esi
0063ea01 and ecx, 0x20000000
0063ea07 or ecx, 0
0063ea0a je 0x63ea13
0063ea0c mov ecx, 2
0063ea11 jmp 0x63ea15
0063ea13 xor ecx, ecx
0063ea15 and edx, 0x400000
0063ea1b xor eax, eax
0063ea1d or eax, edx
0063ea1f je 0x63ea28
0063ea21 mov eax, 4
0063ea26 jmp 0x63ea2a
0063ea28 xor eax, eax
0063ea2a or eax, ecx
0063ea2c mov dword ptr [esp + 0x44], edi
0063ea30 push 0x1e
0063ea32 lea ecx, [esp + 0x24]
0063ea36 or eax, esi
0063ea38 push ecx
0063ea39 push 0
0063ea3b push dword ptr [esp + 0x1c]
0063ea3f mov dword ptr [esp + 0x50], eax
0063ea43 mov eax, dword ptr [ebx]
0063ea45 push ecx
0063ea46 mov ecx, ebx
0063ea48 mov dword ptr [esp], 0x3f800000
0063ea4f call dword ptr [eax + 0x20]
0063ea52 jmp 0x63ea6a
0063ea54 cmp dword ptr [ebx + 0x12b8], 5
0063ea5b jl 0x63ee90
0063ea61 push -5
0063ea63 mov ecx, ebx
0063ea65 call 0x725740
