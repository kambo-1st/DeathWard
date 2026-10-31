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
