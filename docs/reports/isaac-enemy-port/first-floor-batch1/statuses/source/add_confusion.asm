006857d0 push ebp
006857d1 mov ebp, esp
006857d3 and esp, 0xfffffff8
006857d6 sub esp, 0x3c
006857d9 mov eax, dword ptr [0xbaa3b4]
006857de xor eax, esp
006857e0 mov dword ptr [esp + 0x38], eax
006857e4 push ebx
006857e5 push esi
006857e6 push edi
006857e7 mov edi, dword ptr [ebp + 8]
006857ea mov esi, ecx
006857ec push edi
006857ed call 0x684b00
006857f2 test al, al
006857f4 jne 0x685976
006857fa cmp dword ptr [esi + 0x28], 1
006857fe jne 0x685816
00685800 push 0
00685802 push 0x278
00685807 mov ecx, esi
00685809 call 0x73af30
0068580e test al, al
00685810 jne 0x685976
00685816 push edi
00685817 push dword ptr [ebp + 0xc]
0068581a mov ecx, esi
0068581c call 0x685020
00685821 mov ecx, esi
00685823 mov edi, eax
00685825 call 0x681710
0068582a test al, al
0068582c je 0x68584c
0068582e mov ecx, dword ptr [esi + 0x314]
00685834 test ecx, ecx
00685836 je 0x68584c
00685838 nop dword ptr [eax + eax]
00685840 mov esi, ecx
00685842 mov ecx, dword ptr [esi + 0x314]
00685848 test ecx, ecx
0068584a jne 0x685840
0068584c mov ecx, dword ptr [esi + 0x160]
00685852 mov eax, ecx
00685854 and eax, 0x200
00685859 or eax, 0
0068585c je 0x685862
0068585e mov bl, 1
00685860 jmp 0x685864
00685862 xor bl, bl
00685864 test edi, edi
00685866 je 0x685933
0068586c mov eax, ecx
0068586e and eax, 1
00685871 or eax, 0
00685874 jne 0x685933
0068587a mov bh, byte ptr [ebp + 0x10]
0068587d cmp dword ptr [esi + 0x230], eax
00685883 jle 0x68588d
00685885 test bh, bh
00685887 je 0x685933
0068588d mov edx, dword ptr [esi + 0x220]
00685893 test edi, edi
00685895 jle 0x6858b1
00685897 lea eax, [edx + edi]
0068589a mov ecx, 0x78
0068589f cmp eax, ecx
006858a1 cmovl ecx, eax
006858a4 cmp edx, ecx
006858a6 cmovl edx, ecx
006858a9 mov ecx, dword ptr [esi + 0x160]
006858af jmp 0x6858b8
006858b1 neg edi
006858b3 cmp edx, edi
006858b5 cmovl edx, edi
006858b8 mov dword ptr [esi + 0x220], edx
006858be or ecx, 0x200
006858c4 mov eax, dword ptr [esi + 0x164]
006858ca xorps xmm0, xmm0
006858cd push 1
006858cf push 0
006858d1 push 0xff
006858d6 mov dword ptr [esi + 0x160], ecx
006858dc lea ecx, [esp + 0x24]
006858e0 mov dword ptr [esi + 0x164], eax
006858e6 mov eax, dword ptr [esi]
006858e8 push edx
006858e9 movups xmmword ptr [esp + 0x38], xmm0
006858ee push ecx
006858ef movaps xmm0, xmmword ptr [0xb6c290]
006858f6 mov ecx, esi
006858f8 movups xmmword ptr [esp + 0x2c], xmm0
006858fd mov dword ptr [esp + 0x4c], 0x3e20a0a1
00685905 mov dword ptr [esp + 0x50], 0x3e20a0a1
0068590d mov dword ptr [esp + 0x54], 0x3e20a0a1
00685915 call dword ptr [eax + 0x38]
00685918 test bh, bh
0068591a jne 0x685933
0068591c mov eax, dword ptr [esi]
0068591e mov ecx, esi
00685920 mov eax, dword ptr [eax + 0x48]
00685923 call eax
00685925 test al, al
00685927 je 0x685933
00685929 mov dword ptr [esi + 0x230], 0xf0
00685933 mov ecx, esi
00685935 call 0x681390
0068593a cmp dword ptr [esi + 0x220], 0
00685941 jle 0x685976
00685943 test bl, bl
00685945 jne 0x685976
00685947 mov eax, dword ptr [esi + 0x28]
0068594a sub eax, 0xa
0068594d cmp eax, 0x3dd
00685952 ja 0x685976
00685954 push 0
00685956 push 0xbeab70
0068595b push 0xbeab18
00685960 push 0
00685962 push esi
00685963 call 0x9ec34c
00685968 add esp, 0x14
0068596b test eax, eax
0068596d je 0x685976
0068596f mov ecx, eax
00685971 call 0x680df0
00685976 mov ecx, dword ptr [esp + 0x44]
0068597a pop edi
0068597b pop esi
0068597c pop ebx
0068597d xor ecx, esp
0068597f call 0x9eacd7
00685984 mov esp, ebp
00685986 pop ebp
00685987 ret 0xc
