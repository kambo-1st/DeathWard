006a7839 xor eax, eax
006a783b mov ecx, dword ptr [esi + 0x164]
006a7841 and ecx, 0x400
006a7847 or eax, ecx
006a7849 jne 0x6a7a08
006a784f mov ecx, dword ptr [esi + 0x2c]
006a7852 cmp ecx, 0xb
006a7855 je 0x6a7a08
006a785b cmp ecx, 0xa
006a785e je 0x6a7a08
006a7864 cmp ecx, 0xc
006a7867 je 0x6a7a08
006a786d cmp ecx, 0xd
006a7870 je 0x6a7a08
006a7876 cmp ecx, 4
006a7879 je 0x6a7a08
006a787f cmp byte ptr [ebx + 0xc], 0
006a7883 lea eax, [esi + 0x334]
006a7889 movups xmm0, xmmword ptr [eax]
006a788c lea esi, [ebp - 0x24]
006a788f cmovne esi, eax
006a7892 movups xmmword ptr [ebp - 0x24], xmm0
006a7896 cmp ecx, 2
006a7899 je 0x6a7960
006a789f cmp ecx, 3
006a78a2 je 0x6a7960
006a78a8 call 0x6cba20
006a78ad test al, al
006a78af je 0x6a78bb
006a78b1 movss xmm0, dword ptr [0xb6a2cc]
006a78b9 jmp 0x6a78c3
006a78bb movss xmm0, dword ptr [0xb6a38c]
006a78c3 mov ecx, esi
006a78c5 movss dword ptr [ebp - 0x2c], xmm0
006a78ca call 0x7a7db0
006a78cf movss xmm0, dword ptr [ebp - 0x2c]
006a78d4 fstp dword ptr [ebp - 0x28]
006a78d7 comiss xmm0, dword ptr [ebp - 0x28]
006a78db jbe 0x6a79f0
006a78e1 mov ecx, esi
006a78e3 call 0x7a7db0
006a78e8 movss xmm0, dword ptr [0xb6a38c]
006a78f0 fstp dword ptr [ebp - 0x28]
006a78f3 comiss xmm0, dword ptr [ebp - 0x28]
006a78f7 jbe 0x6a794d
006a78f9 mov ecx, dword ptr [0xbfd65c]
006a78ff push 1
006a7901 push 0
006a7903 push 0x16
006a7905 lea ecx, [ecx + 0x1ba40]
006a790b call 0x91d550
006a7910 test eax, eax
006a7912 je 0x6a793c
006a7914 mov eax, dword ptr [esi]
006a7916 lea ecx, [ebp - 0x50]
006a7919 movq xmm0, qword ptr [0xa08ad0]
006a7921 mov dword ptr [ebp - 0x50], eax
006a7924 mov eax, dword ptr [0xa08ad8]
006a7929 push 5
006a792b movq qword ptr [ebp - 0x4c], xmm0
006a7930 mov dword ptr [ebp - 0x44], eax
006a7933 call 0x7a7d50
006a7938 test eax, eax
006a793a jne 0x6a794d
006a793c mov ecx, esi
006a793e call 0x7a7e20
006a7943 push 0
006a7945 push eax
006a7946 push 0
006a7948 jmp 0x6a79e4
006a794d mov ecx, esi
006a794f call 0x7a7e20
006a7954 push 0
006a7956 push eax
006a7957 push 0
006a7959 push 0x14
006a795b jmp 0x6a79e6
006a7960 call 0x6cba20
006a7965 test al, al
006a7967 je 0x6a7973
006a7969 movss xmm0, dword ptr [0xb6a2cc]
006a7971 jmp 0x6a797b
006a7973 movss xmm0, dword ptr [0xb6a38c]
006a797b mov ecx, esi
006a797d movss dword ptr [ebp - 0x2c], xmm0
006a7982 call 0x7a7db0
006a7987 movss xmm0, dword ptr [ebp - 0x2c]
006a798c fstp dword ptr [ebp - 0x28]
006a798f comiss xmm0, dword ptr [ebp - 0x28]
006a7993 jbe 0x6a79f0
006a7995 mov ecx, dword ptr [0xbfd65c]
006a799b push 1
006a799d push 0
006a799f push 0x16
006a79a1 lea ecx, [ecx + 0x1ba40]
006a79a7 call 0x91d550
006a79ac test eax, eax
006a79ae je 0x6a79d8
006a79b0 mov eax, dword ptr [esi]
006a79b2 lea ecx, [ebp - 0x50]
006a79b5 movq xmm0, qword ptr [0xa08ad0]
006a79bd mov dword ptr [ebp - 0x50], eax
006a79c0 mov eax, dword ptr [0xa08ad8]
006a79c5 push 5
006a79c7 movq qword ptr [ebp - 0x4c], xmm0
006a79cc mov dword ptr [ebp - 0x44], eax
006a79cf call 0x7a7d50
006a79d4 test eax, eax
006a79d6 jne 0x6a79f0
006a79d8 mov ecx, esi
006a79da call 0x7a7e20
006a79df push 0
006a79e1 push eax
006a79e2 push 3
006a79e4 push 0xa
006a79e6 push 5
006a79e8 lea ecx, [ebp - 0x40]
006a79eb call 0x68f5d0
