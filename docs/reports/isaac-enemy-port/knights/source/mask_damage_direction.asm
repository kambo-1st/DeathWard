006aa830 push ebp
006aa831 mov ebp, esp
006aa833 push -1
006aa835 push 0x9f4a2d
006aa83a mov eax, dword ptr fs:[0]
006aa840 push eax
006aa841 sub esp, 0x2c
006aa844 mov eax, dword ptr [0xbaa3b4]
006aa849 xor eax, ebp
006aa84b mov dword ptr [ebp - 0x10], eax
006aa84e push ebx
006aa84f push esi
006aa850 push edi
006aa851 push eax
006aa852 lea eax, [ebp - 0xc]
006aa855 mov dword ptr fs:[0], eax
006aa85b mov edi, ecx
006aa85d mov eax, dword ptr [edi + 0x28]
006aa860 cmp eax, 0x29
006aa863 je 0x6aaa22
006aa869 cmp eax, 0x61
006aa86c je 0x6aaa16
006aa872 cmp eax, 0xfe
006aa877 je 0x6aaa22
006aa87d cmp eax, 0x11b
006aa882 je 0x6aaa22
006aa888 cmp eax, 0x387
006aa88d jne 0x6aa8ed
006aa88f cmp dword ptr [edi + 0x2c], 1
006aa893 jne 0x6aa8cd
006aa895 movss xmm0, dword ptr [ebp + 8]
006aa89a ucomiss xmm0, dword ptr [0xc02fec]
006aa8a1 lahf 
006aa8a2 test ah, 0x44
006aa8a5 jp 0x6aa8b9
006aa8a7 movss xmm0, dword ptr [ebp + 0xc]
006aa8ac ucomiss xmm0, dword ptr [0xc02ff0]
006aa8b3 lahf 
006aa8b4 test ah, 0x44
006aa8b7 jnp 0x6aa8cd
006aa8b9 lea ecx, [ebp + 8]
006aa8bc call 0x659490
006aa8c1 cmp eax, dword ptr [edi + 0xb10]
006aa8c7 jne 0x6aabd2
006aa8cd mov al, 1
006aa8cf mov ecx, dword ptr [ebp - 0xc]
006aa8d2 mov dword ptr fs:[0], ecx
006aa8d9 pop ecx
006aa8da pop edi
006aa8db pop esi
006aa8dc pop ebx
006aa8dd mov ecx, dword ptr [ebp - 0x10]
006aa8e0 xor ecx, ebp
006aa8e2 call 0x9eacd7
006aa8e7 mov esp, ebp
006aa8e9 pop ebp
006aa8ea ret 8
006aa8ed cmp eax, 0x17
006aa8f0 jne 0x6aa8cd
006aa8f2 cmp dword ptr [edi + 0x2c], 3
006aa8f6 jne 0x6aa8cd
006aa8f8 lea eax, [ebp - 0x28]
006aa8fb push eax
006aa8fc lea ecx, [edi + 0x6c]
006aa8ff call 0x444be0
006aa904 mov dword ptr [ebp - 4], 0
006aa90b lea ecx, [ebp - 0x28]
006aa90e mov eax, dword ptr [ebp - 0x18]
006aa911 push 0xb406e4
006aa916 push 2
006aa918 add eax, -2
006aa91b push eax
006aa91c call 0x6b1540
006aa921 test eax, eax
006aa923 jne 0x6aa92a
006aa925 lea esi, [eax + 1]
006aa928 jmp 0x6aa959
006aa92a mov eax, dword ptr [ebp - 0x18]
006aa92d lea ecx, [ebp - 0x28]
006aa930 push 0xb406f0
006aa935 push 4
006aa937 add eax, -4
006aa93a push eax
006aa93b call 0x6b1540
006aa940 test eax, eax
006aa942 jne 0x6aa949
006aa944 lea esi, [eax + 3]
006aa947 jmp 0x6aa959
006aa949 xor eax, eax
006aa94b mov esi, 2
006aa950 cmp byte ptr [edi + 0x13c], al
006aa956 cmovne esi, eax
006aa959 mov edx, esi
006aa95b lea ecx, [ebp - 0x34]
006aa95e call 0x659400
006aa963 mov ebx, dword ptr [ebp - 0x28]
006aa966 lea ecx, [ebp - 0x28]
006aa969 mov edx, 6
006aa96e cmp dword ptr [ebp - 0x18], edx
006aa971 push 6
006aa973 cmovb edx, dword ptr [ebp - 0x18]
006aa977 cmp dword ptr [ebp - 0x14], 0x10
006aa97b push 0xb40510
006aa980 cmovae ecx, ebx
006aa983 call 0x41e2b0
006aa988 add esp, 8
006aa98b test eax, eax
006aa98d jne 0x6aa9b8
006aa98f movss xmm1, dword ptr [0xb6a524]
006aa997 movss xmm2, dword ptr [0xb6ae30]
006aa99f movaps xmm0, xmm1
006aa9a2 cmp esi, 1
006aa9a5 jne 0x6aa9aa
006aa9a7 movaps xmm0, xmm2
006aa9aa cmp byte ptr [edi + 0x13c], 0
006aa9b1 je 0x6aa9c2
006aa9b3 movaps xmm1, xmm2
006aa9b6 jmp 0x6aa9c2
006aa9b8 movss xmm0, dword ptr [ebp - 0x30]
006aa9bd movss xmm1, dword ptr [ebp - 0x34]
006aa9c2 mulss xmm0, dword ptr [ebp + 0xc]
006aa9c7 mov eax, dword ptr [ebp - 0x14]
006aa9ca mulss xmm1, dword ptr [ebp + 8]
006aa9cf addss xmm0, xmm1
006aa9d3 comiss xmm0, dword ptr [0xb6a18c]
006aa9da setae byte ptr [ebp - 0x29]
006aa9de cmp eax, 0x10
006aa9e1 jb 0x6aaa0e
006aa9e3 lea ecx, [eax + 1]
006aa9e6 mov eax, ebx
006aa9e8 cmp ecx, 0x1000
006aa9ee jb 0x6aaa04
006aa9f0 mov ebx, dword ptr [ebx - 4]
006aa9f3 add ecx, 0x23
006aa9f6 sub eax, ebx
006aa9f8 add eax, -4
006aa9fb cmp eax, 0x1f
006aa9fe ja 0x6aab86
006aaa04 push ecx
006aaa05 push ebx
006aaa06 call 0x9eb08e
006aaa0b add esp, 8
006aaa0e mov al, byte ptr [ebp - 0x29]
006aaa11 jmp 0x6aa8cf
006aaa16 call 0x684860
006aaa1b mov esi, eax
006aaa1d jmp 0x6aab96
006aaa22 mov eax, dword ptr [edi + 0x70]
006aaa25 test eax, eax
006aaa27 je 0x6aaa3a
006aaa29 push eax
006aaa2a lea ecx, [ebp - 0x28]
006aaa2d call 0x4079f0
006aaa32 mov ebx, dword ptr [ebp - 0x18]
006aaa35 mov eax, dword ptr [ebp - 0x28]
006aaa38 jmp 0x6aaa4b
006aaa3a xor eax, eax
006aaa3c mov dword ptr [ebp - 0x14], 0xf
006aaa43 xor ebx, ebx
006aaa45 mov dword ptr [ebp - 0x28], eax
006aaa48 mov dword ptr [ebp - 0x18], ebx
006aaa4b cmp dword ptr [ebp - 0x14], 0x10
006aaa4f lea ecx, [ebp - 0x28]
006aaa52 mov dword ptr [ebp - 0x30], eax
006aaa55 mov esi, ebx
006aaa57 cmovae ecx, eax
006aaa5a mov edx, 0xb406e4
006aaa5f mov eax, 2
006aaa64 cmp ebx, eax
006aaa66 cmova esi, eax
006aaa69 sub esi, 4
006aaa6c jb 0x6aaa81
006aaa6e nop 
006aaa70 mov eax, dword ptr [ecx]
006aaa72 cmp eax, dword ptr [edx]
006aaa74 jne 0x6aaa86
006aaa76 add ecx, 4
006aaa79 add edx, 4
006aaa7c sub esi, 4
006aaa7f jae 0x6aaa70
006aaa81 cmp esi, -4
006aaa84 je 0x6aaaba
006aaa86 mov al, byte ptr [ecx]
006aaa88 cmp al, byte ptr [edx]
006aaa8a jne 0x6aaab3
006aaa8c cmp esi, -3
006aaa8f je 0x6aaaba
006aaa91 mov al, byte ptr [ecx + 1]
006aaa94 cmp al, byte ptr [edx + 1]
006aaa97 jne 0x6aaab3
006aaa99 cmp esi, -2
006aaa9c je 0x6aaaba
006aaa9e mov al, byte ptr [ecx + 2]
006aaaa1 cmp al, byte ptr [edx + 2]
006aaaa4 jne 0x6aaab3
006aaaa6 cmp esi, -1
006aaaa9 je 0x6aaaba
006aaaab mov al, byte ptr [ecx + 3]
006aaaae cmp al, byte ptr [edx + 3]
006aaab1 je 0x6aaaba
006aaab3 sbb eax, eax
006aaab5 or eax, 1
006aaab8 jmp 0x6aaabc
006aaaba xor eax, eax
006aaabc test eax, eax
006aaabe jne 0x6aaacf
006aaac0 cmp ebx, 2
006aaac3 jb 0x6aaacf
006aaac5 ja 0x6aaacf
006aaac7 lea esi, [eax + 1]
006aaaca jmp 0x6aab5e
006aaacf cmp dword ptr [ebp - 0x14], 0x10
006aaad3 lea ecx, [ebp - 0x28]
006aaad6 mov eax, 4
006aaadb mov esi, ebx
006aaadd cmovae ecx, dword ptr [ebp - 0x30]
006aaae1 mov edx, 0xb42f28
006aaae6 cmp ebx, eax
006aaae8 cmova esi, eax
006aaaeb sub esi, eax
006aaaed jb 0x6aab01
006aaaef nop 
006aaaf0 mov eax, dword ptr [ecx]
006aaaf2 cmp eax, dword ptr [edx]
006aaaf4 jne 0x6aab06
006aaaf6 add ecx, 4
006aaaf9 add edx, 4
006aaafc sub esi, 4
006aaaff jae 0x6aaaf0
006aab01 cmp esi, -4
006aab04 je 0x6aab3a
006aab06 mov al, byte ptr [ecx]
006aab08 cmp al, byte ptr [edx]
006aab0a jne 0x6aab33
006aab0c cmp esi, -3
006aab0f je 0x6aab3a
006aab11 mov al, byte ptr [ecx + 1]
006aab14 cmp al, byte ptr [edx + 1]
006aab17 jne 0x6aab33
006aab19 cmp esi, -2
006aab1c je 0x6aab3a
006aab1e mov al, byte ptr [ecx + 2]
006aab21 cmp al, byte ptr [edx + 2]
006aab24 jne 0x6aab33
006aab26 cmp esi, -1
006aab29 je 0x6aab3a
006aab2b mov al, byte ptr [ecx + 3]
006aab2e cmp al, byte ptr [edx + 3]
006aab31 je 0x6aab3a
006aab33 sbb eax, eax
006aab35 or eax, 1
006aab38 jmp 0x6aab3c
006aab3a xor eax, eax
006aab3c test eax, eax
006aab3e jne 0x6aab59
006aab40 cmp ebx, 4
006aab43 jb 0x6aab59
006aab45 ja 0x6aab59
006aab47 xor esi, esi
006aab49 cmp byte ptr [edi + 0x13c], al
006aab4f mov eax, 2
006aab54 cmove esi, eax
006aab57 jmp 0x6aab5e
006aab59 mov esi, 3
006aab5e mov eax, dword ptr [ebp - 0x14]
006aab61 cmp eax, 0x10
006aab64 jb 0x6aab96
006aab66 mov ecx, dword ptr [ebp - 0x30]
006aab69 lea edx, [eax + 1]
006aab6c mov eax, ecx
006aab6e cmp edx, 0x1000
006aab74 jb 0x6aab8c
006aab76 mov ecx, dword ptr [ecx - 4]
006aab79 add edx, 0x23
006aab7c sub eax, ecx
006aab7e add eax, -4
006aab81 cmp eax, 0x1f
006aab84 jbe 0x6aab8c
006aab86 call dword ptr [0xa065ac]
006aab8c push edx
006aab8d push ecx
006aab8e call 0x9eb08e
006aab93 add esp, 8
006aab96 movss xmm1, dword ptr [ebp + 8]
006aab9b xorps xmm0, xmm0
006aab9e comiss xmm0, xmm1
006aaba1 jbe 0x6aaba8
006aaba3 cmp esi, 2
006aaba6 je 0x6aabd2
006aaba8 comiss xmm1, xmm0
006aabab jbe 0x6aabb1
006aabad test esi, esi
006aabaf je 0x6aabd2
006aabb1 movss xmm1, dword ptr [ebp + 0xc]
006aabb6 comiss xmm1, xmm0
006aabb9 jbe 0x6aabc0
006aabbb cmp esi, 1
006aabbe je 0x6aabd2
006aabc0 comiss xmm0, xmm1
006aabc3 jbe 0x6aa8cd
006aabc9 cmp esi, 3
006aabcc jne 0x6aa8cd
006aabd2 xor al, al
006aabd4 jmp 0x6aa8cf
