006d28bb mov eax, dword ptr [ebp + 0x1c]
006d28be and eax, dword ptr [0xbc48cc]
006d28c4 mov ecx, dword ptr [ebp + 0x10]
006d28c7 mov edx, dword ptr [ebp + 0x18]
006d28ca and ecx, dword ptr [0xbc48c0]
006d28d0 and edx, dword ptr [0xbc48c8]
006d28d6 mov dword ptr [esp + 0x20], eax
006d28da mov eax, dword ptr [ebp + 0x14]
006d28dd and eax, dword ptr [0xbc48c4]
006d28e3 or ecx, eax
006d28e5 jne 0x6d28ed
006d28e7 or edx, dword ptr [esp + 0x20]
006d28eb je 0x6d28fa
006d28ed mulss xmm1, dword ptr [0xb6a53c]
006d28f5 movss dword ptr [ebp + 0xc], xmm1
006d28fa movss xmm3, dword ptr [esp + 0x14]
006d2900 push dword ptr [ebp + 0x38]
006d2903 movaps xmm2, xmm3
006d2906 mov ecx, dword ptr [esp + 0x40]
006d290a push dword ptr [ebp + 0x34]
006d290d divss xmm2, xmm0
006d2911 push dword ptr [ebp + 0x30]
006d2914 mulss xmm3, dword ptr [ebp + 0x28]
006d2919 sub esp, 0x10
006d291c movups xmm0, xmmword ptr [ebp + 0x10]
006d2920 mov eax, esp
006d2922 mulss xmm2, dword ptr [ebp + 0x28]
006d2927 push edi
006d2928 push dword ptr [ebp + 0x2c]
006d292b movups xmmword ptr [eax], xmm0
006d292e sub esp, 8
006d2931 movss dword ptr [esp + 0x38], xmm2
006d2937 movss dword ptr [esp + 0x40], xmm3
006d293d movss dword ptr [esp + 4], xmm3
006d2943 movss dword ptr [esp], xmm1
006d2948 push esi
006d2949 call 0x6d1750
