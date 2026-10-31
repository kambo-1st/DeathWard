004f67c1 movss xmm1, dword ptr [0xb6a7b0]
004f67c9 xorps xmm2, xmm2
004f67cc mov ecx, esi
004f67ce call 0x6847e0
004f67d3 test eax, eax
004f67d5 je 0x4f6a3f
004f67db movss xmm3, dword ptr [0xb6aa0c]
004f67e3 mov edi, dword ptr [esi + 0x28]
004f67e6 movss dword ptr [esp + 0x20], xmm3
004f67ec cmp edi, 0x12
004f67ef je 0x4f680e
004f67f1 cmp edi, 0x50
004f67f4 je 0x4f680e
004f67f6 cmp edi, 0xd6
004f67fc je 0x4f680e
004f67fe cmp edi, 0xf9
004f6804 je 0x4f680e
004f6806 cmp edi, 0x333
004f680c jne 0x4f681c
004f680e movss xmm3, dword ptr [0xb6a9ec]
004f6816 movss dword ptr [esp + 0x20], xmm3
004f681c cmp edi, 0x3d
004f681f je 0x4f6832
004f6821 movss xmm0, dword ptr [esi + 0xd8]
004f6829 comiss xmm0, dword ptr [0xb6a64c]
004f6830 jbe 0x4f6840
004f6832 movss xmm0, dword ptr [0xb6a9ac]
004f683a movss dword ptr [esp + 0x20], xmm0
004f6840 cmp dword ptr [esi + 0xe6c], -1
004f6847 movss xmm0, dword ptr [esi + 0x28c]
004f684f subss xmm0, dword ptr [esi + 0x294]
004f6857 movss xmm2, dword ptr [esi + 0x290]
004f685f subss xmm2, dword ptr [esi + 0x298]
004f6867 movaps xmm1, xmm0
004f686a movss dword ptr [esp + 0x14], xmm1
004f6870 je 0x4f689f
004f6872 lea eax, [esp + 0xc]
004f6876 xorps xmm2, xmm2
004f6879 push eax
004f687a mov ecx, esi
004f687c call 0x6af0c0
004f6881 mov edi, dword ptr [esi + 0x28]
004f6884 movss xmm1, dword ptr [eax]
004f6888 movss xmm2, dword ptr [eax + 4]
004f688d mulss xmm1, dword ptr [0xb6aafc]
004f6895 mulss xmm2, dword ptr [0xb6aafc]
004f689d jmp 0x4f6916
004f689f cmp edi, 0xd6
004f68a5 je 0x4f68af
004f68a7 cmp edi, 0x333
004f68ad jne 0x4f68c7
004f68af mov al, byte ptr [esp + 0xb]
004f68b3 test al, al
004f68b5 jne 0x4f68cb
004f68b7 movaps xmm1, xmm2
004f68ba xorps xmm1, xmmword ptr [0xb6c9b0]
004f68c1 addss xmm1, xmm0
004f68c5 jmp 0x4f68e5
004f68c7 mov al, byte ptr [esp + 0xb]
004f68cb cmp edi, 0xf9
004f68d1 jne 0x4f68ef
004f68d3 test al, al
004f68d5 jne 0x4f68ef
004f68d7 movaps xmm1, xmm2
004f68da addss xmm1, xmm0
004f68de xorps xmm0, xmmword ptr [0xb6c9b0]
004f68e5 addss xmm2, xmm0
004f68e9 movss dword ptr [esp + 0x14], xmm1
004f68ef cmp dword ptr [esi + 0x314], 0
004f68f6 mulss xmm2, dword ptr [0xb6a480]
004f68fe movss dword ptr [esp + 0x24], xmm2
004f6904 je 0x4f6922
004f6906 mulss xmm1, dword ptr [0xb6a350]
004f690e mulss xmm2, dword ptr [0xb6a350]
004f6916 movss dword ptr [esp + 0x24], xmm2
004f691c movss dword ptr [esp + 0x14], xmm1
004f6922 movaps xmm0, xmm1
004f6925 mulss xmm0, xmm1
004f6929 movaps xmm1, xmm2
004f692c mulss xmm1, xmm2
004f6930 addss xmm0, xmm1
004f6934 call 0x4228c0
004f6939 movss xmm2, dword ptr [esp + 0x14]
004f693f movaps xmm3, xmm0
004f6942 comiss xmm3, dword ptr [0xb6a18c]
004f6949 movss xmm1, dword ptr [esp + 0x24]
004f694f jbe 0x4f6959
004f6951 divss xmm2, xmm3
004f6955 divss xmm1, xmm3
004f6959 cmp byte ptr [esi + 0x16c], 0
004f6960 je 0x4f697a
004f6962 movss xmm0, dword ptr [esi + 0x2c4]
004f696a mulss xmm0, dword ptr [0xb6a5a4]
004f6972 movss dword ptr [esi + 0x2c4], xmm0
004f697a mov eax, edi
004f697c cmp edi, 0x12
004f697f je 0x4f69d6
004f6981 cmp edi, 0x3d
004f6984 je 0x4f69d6
004f6986 cmp edi, 0x50
004f6989 je 0x4f69d6
004f698b cmp edi, 0xd6
004f6991 je 0x4f69d6
004f6993 cmp edi, 0xf9
004f6999 je 0x4f69d6
004f699b cmp edi, 0x333
004f69a1 je 0x4f69d6
004f69a3 movss xmm0, dword ptr [esi + 0xb00]
004f69ab mulss xmm0, dword ptr [0xb6a50c]
004f69b3 movss dword ptr [esi + 0xb00], xmm0
004f69bb movss xmm0, dword ptr [esi + 0xb04]
004f69c3 mulss xmm0, dword ptr [0xb6a50c]
004f69cb movss dword ptr [esi + 0xb04], xmm0
004f69d3 mov eax, dword ptr [esi + 0x28]
004f69d6 movss xmm0, dword ptr [esp + 0x20]
004f69dc comiss xmm3, xmm0
004f69df jbe 0x4f6a3a
004f69e1 subss xmm3, xmm0
004f69e5 mulss xmm3, dword ptr [0xb6a2ac]
004f69ed minss xmm3, dword ptr [0xb6a670]
004f69f5 cmp eax, 0xd6
004f69fa je 0x4f6a0a
004f69fc cmp eax, 0xf9
004f6a01 je 0x4f6a0a
004f6a03 cmp eax, 0x333
004f6a08 jne 0x4f6a18
004f6a0a cmp byte ptr [esp + 0xb], 0
004f6a0f jne 0x4f6a18
004f6a11 movaps xmm0, xmm3
004f6a14 addss xmm3, xmm0
004f6a18 mulss xmm2, xmm3
004f6a1c lea eax, [esp + 0xc]
004f6a20 mov ecx, esi
004f6a22 mulss xmm1, xmm3
004f6a26 push 0
004f6a28 push eax
004f6a29 movss dword ptr [esp + 0x14], xmm2
004f6a2f movss dword ptr [esp + 0x18], xmm1
004f6a35 call 0x422b60
