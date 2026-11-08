00689840 push ebp
00689841 mov ebp, esp
00689843 and esp, 0xfffffff8
00689846 sub esp, 0xc
00689849 push ebx
0068984a push esi
0068984b mov esi, dword ptr [edx + 0x180]
00689851 push edi
00689852 mov edi, ecx
00689854 mov dword ptr [esp + 0x14], edx
00689858 mov ebx, dword ptr [edi + 0x180]
0068985e cmp ebx, 2
00689861 je 0x689868
00689863 cmp ebx, 1
00689866 jne 0x68988a
00689868 mov eax, dword ptr [edi + 0x28]
0068986b sub eax, 0xa
0068986e cmp eax, 0x3dd
00689873 ja 0x68988a
00689875 mov eax, dword ptr [edi + 0x160]
0068987b and eax, 0x20000100
00689880 or eax, 0
00689883 je 0x68988a
00689885 mov ebx, 4
0068988a cmp esi, 2
0068988d je 0x689894
0068988f cmp esi, 1
00689892 jne 0x6898b6
00689894 mov eax, dword ptr [edx + 0x28]
00689897 sub eax, 0xa
0068989a cmp eax, 0x3dd
0068989f ja 0x6898b6
006898a1 mov eax, dword ptr [edx + 0x160]
006898a7 and eax, 0x20000100
006898ac or eax, 0
006898af je 0x6898b6
006898b1 mov esi, 4
006898b6 test ebx, ebx
006898b8 je 0x6898c2
006898ba test esi, esi
006898bc je 0x6898c2
006898be xor al, al
006898c0 jmp 0x6898c4
006898c2 mov al, 1
006898c4 mov byte ptr [esp + 0x13], al
006898c8 cmp ebx, 2
006898cb jne 0x6898d8
006898cd mov ecx, edx
006898cf call 0x6897c0
006898d4 test al, al
006898d6 je 0x6898e8
006898d8 cmp esi, 2
006898db jne 0x6898ec
006898dd mov ecx, edi
006898df call 0x6897c0
006898e4 test al, al
006898e6 jne 0x6898ec
006898e8 mov al, 1
006898ea jmp 0x6898ee
006898ec xor al, al
006898ee mov cl, byte ptr [esp + 0x13]
006898f2 or cl, al
006898f4 cmp ebx, 1
006898f7 je 0x689903
006898f9 cmp esi, 1
006898fc jne 0x689905
006898fe cmp dword ptr [edi + 0x28], esi
00689901 je 0x689905
00689903 mov cl, 1
00689905 cmp ebx, 3
00689908 jne 0x68991b
0068990a mov eax, dword ptr [esp + 0x14]
0068990e mov eax, dword ptr [eax + 0x28]
00689911 sub eax, 0xa
00689914 cmp eax, 0x3dd
00689919 ja 0x68992d
0068991b cmp esi, 3
0068991e jne 0x689931
00689920 mov eax, dword ptr [edi + 0x28]
00689923 sub eax, 0xa
00689926 cmp eax, 0x3dd
0068992b jbe 0x689931
0068992d mov al, 1
0068992f jmp 0x689933
00689931 xor al, al
00689933 or al, cl
00689935 cmp byte ptr [edi + 0x16b], 0
0068993c jne 0x689972
0068993e mov esi, dword ptr [esp + 0x14]
00689942 cmp byte ptr [esi + 0x16b], 0
00689949 jne 0x689972
0068994b test al, al
0068994d jne 0x689974
0068994f mov eax, dword ptr [edi]
00689951 mov ecx, edi
00689953 push 1
00689955 push esi
00689956 mov eax, dword ptr [eax + 0x58]
00689959 call eax
0068995b mov bl, al
0068995d mov ecx, esi
0068995f mov eax, dword ptr [esi]
00689961 push 0
00689963 push edi
00689964 mov eax, dword ptr [eax + 0x58]
00689967 call eax
00689969 or al, bl
0068996b pop edi
0068996c pop esi
0068996d pop ebx
0068996e mov esp, ebp
00689970 pop ebp
00689971 ret 
00689972 mov al, 1
00689974 pop edi
00689975 pop esi
00689976 pop ebx
00689977 mov esp, ebp
00689979 pop ebp
0068997a ret 
