006ad7a0 push ebp
006ad7a1 mov ebp, esp
006ad7a3 and esp, 0xfffffff8
006ad7a6 push ecx
006ad7a7 mov eax, dword ptr [ecx + 0x160]
006ad7ad and eax, 0x20000000
006ad7b2 or eax, 0
006ad7b5 mov eax, dword ptr [0xbfd65c]
006ad7ba push ebx
006ad7bb push esi
006ad7bc push edi
006ad7bd mov eax, dword ptr [eax + 0x18190]
006ad7c3 je 0x6ad851
006ad7c9 mov ebx, dword ptr [eax + 0x1264]
006ad7cf xor edi, edi
006ad7d1 xor esi, esi
006ad7d3 test ebx, ebx
006ad7d5 je 0x6ad848
006ad7d7 mov eax, dword ptr [eax + 0x125c]
006ad7dd mov dword ptr [esp + 0xc], eax
006ad7e1 mov edx, dword ptr [eax + esi*4]
006ad7e4 mov eax, dword ptr [edx + 0x28]
006ad7e7 lea ecx, [eax - 0xa]
006ad7ea cmp ecx, 0x3dd
006ad7f0 ja 0x6ad83f
006ad7f2 cmp eax, 0x21
006ad7f5 je 0x6ad83f
006ad7f7 cmp eax, 0x11
006ad7fa je 0x6ad83f
006ad7fc cmp eax, 0x124
006ad801 je 0x6ad83f
006ad803 cmp eax, 0x375
006ad808 jne 0x6ad810
006ad80a cmp dword ptr [edx + 0x2c], 0xa
006ad80e jmp 0x6ad823
006ad810 cmp eax, 0x3c0
006ad815 je 0x6ad83f
006ad817 cmp eax, 0x3c5
006ad81c je 0x6ad83f
006ad81e cmp eax, 0xf5
006ad823 je 0x6ad83f
006ad825 cmp byte ptr [edx + 0x16b], 0
006ad82c jne 0x6ad83f
006ad82e mov eax, dword ptr [edx + 0x160]
006ad834 and eax, 0x20000000
006ad839 or eax, 0
006ad83c je 0x6ad83f
006ad83e inc edi
006ad83f mov eax, dword ptr [esp + 0xc]
006ad843 inc esi
006ad844 cmp esi, ebx
006ad846 jb 0x6ad7e1
006ad848 mov eax, edi
006ad84a pop edi
006ad84b pop esi
006ad84c pop ebx
006ad84d mov esp, ebp
006ad84f pop ebp
006ad850 ret 
006ad851 mov ecx, dword ptr [eax + 0x12c4]
006ad857 mov eax, dword ptr [eax + 0x12c0]
006ad85d add ecx, eax
006ad85f xor eax, eax
006ad861 test ecx, ecx
006ad863 pop edi
006ad864 pop esi
006ad865 cmovg eax, ecx
006ad868 pop ebx
006ad869 mov esp, ebp
006ad86b pop ebp
006ad86c ret 
