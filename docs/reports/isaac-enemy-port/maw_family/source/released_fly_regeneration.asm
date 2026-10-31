004f58ec mov eax, dword ptr [esi + 0xb10]
004f58f2 test eax, eax
004f58f4 jle 0x4f592f
004f58f6 movss xmm1, dword ptr [esi + 0x2dc]
004f58fe movaps xmm0, xmm1
004f5901 divss xmm0, dword ptr [0xb6aa8c]
004f5909 addss xmm0, dword ptr [esi + 0x2d8]
004f5911 comiss xmm1, xmm0
004f5914 ja 0x4f591c
004f5916 movss xmm0, xmm1
004f591a jmp 0x4f5920
004f591c movss xmm0, xmm0
004f5920 dec eax
004f5921 mov dword ptr [esi + 0xb10], eax
004f5927 movss dword ptr [esi + 0x2d8], xmm0
