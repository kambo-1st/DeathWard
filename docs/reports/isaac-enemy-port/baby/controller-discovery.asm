005185e0 push ebx
005185e1 mov ebx, esp
005185e3 sub esp, 8
005185e6 and esp, 0xfffffff8
005185e9 add esp, 4
005185ec push ebp
005185ed mov ebp, dword ptr [ebx + 4]
005185f0 mov dword ptr [esp + 4], ebp
005185f4 mov ebp, esp
005185f6 sub esp, 0x100
005185fc mov eax, dword ptr [0xbaa3b4]
00518601 xor eax, ebp
00518603 mov dword ptr [ebp - 4], eax
00518606 push esi
00518607 push edi
00518608 mov edi, ecx
0051860a mov dword ptr [ebp - 0xe8], edi
00518610 cmp dword ptr [edi + 0x28], 0x26
00518614 jne 0x518634
00518616 cmp dword ptr [edi + 0x2c], 3
0051861a jne 0x518634
0051861c call 0x53c8f0
00518621 pop edi
00518622 pop esi
00518623 mov ecx, dword ptr [ebp - 4]
00518626 xor ecx, ebp
00518628 call 0x9eacd7
0051862d mov esp, ebp
0051862f pop ebp
00518630 mov esp, ebx
00518632 pop ebx
00518633 ret 
00518634 cmp dword ptr [edi + 0xab4], 0
0051863b jne 0x518669
0051863d push 0
0051863f push 0xb404a0
00518644 lea ecx, [edi + 0x3c]
00518647 call 0x4054f0
0051864c mov dword ptr [edi + 0xab4], 4
00518656 pop edi
00518657 pop esi
00518658 mov ecx, dword ptr [ebp - 4]
0051865b xor ecx, ebp
0051865d call 0x9eacd7
00518662 mov esp, ebp
00518664 pop ebp
00518665 mov esp, ebx
00518667 pop ebx
00518668 ret 
00518669 movss xmm1, dword ptr [0xb6aa3c]
00518671 lea esi, [edi + 0x294]
00518677 movss xmm0, dword ptr [esi]
0051867b subss xmm0, xmm1
0051867f movss xmm2, dword ptr [0xb6a480]
00518687 cvttss2si eax, dword ptr [edi + 0x2f8]
0051868f divss xmm0, xmm1
00518693 cvttss2si ecx, dword ptr [edi + 0x2fc]
0051869b addss xmm0, xmm2
0051869f sub ecx, eax
005186a1 mov eax, dword ptr [0xbfd65c]
005186a6 mov dword ptr [ebp - 0xd4], ecx
005186ac mov ecx, dword ptr [eax + 0x18190]
005186b2 cvttss2si edx, xmm0
005186b6 mov dword ptr [ebp - 0xbc], edx
005186bc test edx, edx
005186be js 0x518711
005186c0 mov eax, dword ptr [ecx + 0xc]
005186c3 cmp edx, eax
005186c5 jge 0x518711
005186c7 movss xmm0, dword ptr [esi + 4]
005186cc subss xmm0, dword ptr [0xb6ab20]
005186d4 divss xmm0, xmm1
005186d8 addss xmm0, xmm2
005186dc cvttss2si edx, xmm0
005186e0 test edx, edx
005186e2 js 0x518711
005186e4 cmp edx, dword ptr [ecx + 0x10]
005186e7 jge 0x518711
005186e9 imul eax, edx
005186ec add eax, dword ptr [ebp - 0xbc]
005186f2 cmp eax, 0x1bf
005186f7 ja 0x518711
005186f9 cmp dword ptr [ecx + eax*4 + 0x76c], 0x3b6
00518704 jg 0x518711
00518706 mov dword ptr [ecx + eax*4 + 0x76c], 0x384
00518711 movss xmm0, dword ptr [edi + 0x2c4]
00518719 lea eax, [ebp - 0xd0]
0051871f mulss xmm0, dword ptr [0xb6a50c]
00518727 push ecx
00518728 mov dword ptr [esp], 0
0051872f mov ecx, edi
00518731 push eax
00518732 movss dword ptr [edi + 0x2c4], xmm0
0051873a call 0x695a30
0051873f cmp dword ptr [edi + 0xe6c], -1
00518746 movss xmm1, dword ptr [ebp - 0xd0]
0051874e movss xmm0, dword ptr [ebp - 0xcc]
00518756 subss xmm1, dword ptr [esi]
0051875a subss xmm0, dword ptr [esi + 4]
0051875f movss dword ptr [ebp - 0xc4], xmm1
00518767 movss dword ptr [ebp - 0xc0], xmm0
0051876f je 0x5187ab
00518771 lea eax, [ebp - 0xd0]
00518777 xorps xmm2, xmm2
0051877a push eax
0051877b mov ecx, edi
0051877d call 0x6af0c0
00518782 movss xmm0, dword ptr [eax]
00518786 mulss xmm0, dword ptr [0xb6aafc]
0051878e movss dword ptr [ebp - 0xc4], xmm0
00518796 movss xmm0, dword ptr [eax + 4]
0051879b mulss xmm0, dword ptr [0xb6aafc]
005187a3 movss dword ptr [ebp - 0xc0], xmm0
005187ab mov eax, dword ptr [edi + 0xab4]
005187b1 movss xmm1, dword ptr [0xb6ae44]
005187b9 cmp eax, 4
005187bc jne 0x5190b9
005187c2 cmp dword ptr [edi + 0x28], 0x103
005187c9 mov dword ptr [edi + 0x180], 4
005187d3 jne 0x51888f
005187d9 cmp dword ptr [edi + 0xaf4], 0
005187e0 jg 0x518870
005187e6 cmp dword ptr [edi + 0xe6c], -1
005187ed je 0x518809
005187ef movss xmm1, dword ptr [0xb6accc]
005187f7 mov ecx, edi
005187f9 push 7
005187fb push 0
005187fd call 0x6a15a0
00518802 movzx eax, al
00518805 test eax, eax
00518807 jmp 0x51882c
00518809 call 0x6c3d90
0051880e xor edx, edx
00518810 mov ecx, 0x14
00518815 div ecx
00518817 test edx, edx
00518819 jne 0x518870
0051881b mov ecx, edi
0051881d call 0x695680
00518822 push eax
00518823 mov ecx, edi
00518825 call 0x6aeb40
0051882a test al, al
0051882c je 0x518870
0051882e cmp dword ptr [edi + 0xe6c], -1
00518835 mov dword ptr [edi + 0xab4], 8
0051883f je 0x518848
00518841 mov edx, 0x32
00518846 jmp 0x518859
00518848 call 0x6c3d90
0051884d xor edx, edx
0051884f mov ecx, 0x1e
00518854 div ecx
00518856 add edx, 0x14
00518859 movss xmm2, dword ptr [0xb6ae44]
00518861 mov ecx, edi
00518863 push 0
00518865 mov dword ptr [edi + 0xaf0], edx
0051886b call 0x6af8d0
00518870 mov eax, dword ptr [edi + 0xaf4]
00518876 test eax, eax
00518878 jle 0x518acf
0051887e sub eax, dword ptr [ebp - 0xd4]
00518884 mov dword ptr [edi + 0xaf4], eax
0051888a jmp 0x518acf
0051888f call 0x6c3d90
00518894 xor edx, edx
00518896 mov ecx, 0xa
0051889b div ecx
0051889d test edx, edx
0051889f jne 0x5188e3
005188a1 call 0x6c3d90
005188a6 push ecx
005188a7 mov ecx, edi
005188a9 movd xmm0, eax
005188ad cvtdq2pd xmm0, xmm0
005188b1 shr eax, 0x1f
005188b4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005188bd cvtpd2ps xmm0, xmm0
005188c1 mulss xmm0, dword ptr [0xb6a19c]
005188c9 mulss xmm0, dword ptr [0xb6a3b0]
005188d1 addss xmm0, dword ptr [0xb6a350]
005188d9 movss dword ptr [esp], xmm0
005188de call 0x68d7b0
005188e3 cmp dword ptr [edi + 0xaf0], 0
005188ea jg 0x51893e
005188ec movss xmm1, dword ptr [0xb6aba8]
005188f4 mov ecx, edi
005188f6 push 7
005188f8 push 0
005188fa call 0x6a15a0
005188ff test al, al
00518901 je 0x51893e
00518903 push 1
00518905 lea ecx, [edi + 0x3c]
00518908 mov dword ptr [edi + 0xaf0], 0x23
00518912 push 0xb40510
00518917 call 0x405740
0051891c test al, al
0051891e je 0x518935
00518920 lea ecx, [edi + 0x6c]
00518923 call 0x405330
00518928 mov byte ptr [edi + 0x80], 1
0051892f lea esi, [edi + 0x294]
00518935 push 1
00518937 mov ecx, edi
00518939 call 0x6afe20
0051893e cmp dword ptr [edi + 0x70], 0
00518942 je 0x518ab9
00518948 push 0xb400ac
0051894d lea ecx, [edi + 0x6c]
00518950 call 0x405e90
00518955 test al, al
00518957 je 0x518ab9
0051895d push 0
0051895f mov ecx, edi
00518961 call 0x6afe20
00518966 push ecx
00518967 mov dword ptr [esp], 0x3f800000
0051896e push 0
00518970 push 2
00518972 push ecx
00518973 mov dword ptr [esp], 0x3f59999a
0051897a mov ecx, edi
0051897c push 0x2c
0051897e call 0x6ad720
00518983 lea ecx, [ebp - 0xb0]
00518989 call 0x430d70
0051898e mov eax, dword ptr [edi + 0x2c]
00518991 mov dword ptr [ebp - 0xa4], 0xbd4ccccd
0051899b mov dword ptr [ebp - 0xa0], 0x3f88f5c3
005189a5 cmp eax, 2
005189a8 jne 0x5189dd
005189aa mov eax, dword ptr [ebp - 0x54]
005189ad or dword ptr [ebp - 0x58], 1
005189b1 mov dword ptr [ebp - 0x9c], 0x3fc00000
005189bb mov dword ptr [ebp - 0x54], eax
005189be xor ecx, ecx
005189c0 mov dword ptr [ebp - 0xb4], ecx
005189c6 call 0x6af030
005189cb test eax, eax
005189cd jle 0x5189ec
005189cf test ecx, ecx
005189d1 jne 0x5189ec
005189d3 movss xmm0, dword ptr [0xb6a974]
005189db jmp 0x5189f4
005189dd cmp eax, 1
005189e0 jne 0x5189be
005189e2 cmp dword ptr [edi + 0x30], eax
005189e5 je 0x5189be
005189e7 lea ecx, [eax + 1]
005189ea jmp 0x5189c0
005189ec movss xmm0, dword ptr [0xb6a940]
005189f4 mov ecx, edi
005189f6 movss dword ptr [ebp - 0xb8], xmm0
005189fe call 0x695680
00518a03 cmp dword ptr [edi + 0xe6c], -1
00518a0a movss xmm0, dword ptr [eax + 0x294]
00518a12 movss xmm1, dword ptr [eax + 0x298]
00518a1a subss xmm0, dword ptr [esi]
00518a1e subss xmm1, dword ptr [esi + 4]
00518a23 movss dword ptr [ebp - 0xd0], xmm0
00518a2b movss dword ptr [ebp - 0xcc], xmm1
00518a33 je 0x518a62
00518a35 lea ecx, [edi + 0xe70]
00518a3b push 0xc02fec
00518a40 call 0x962ca0
00518a45 test al, al
00518a47 je 0x518a62
00518a49 movss xmm0, dword ptr [ecx]
00518a4d movss dword ptr [ebp - 0xd0], xmm0
00518a55 movss xmm0, dword ptr [ecx + 4]
00518a5a movss dword ptr [ebp - 0xcc], xmm0
00518a62 lea ecx, [ebp - 0xd0]
00518a68 call 0x9624f0
00518a6d movss xmm0, dword ptr [ebp - 0xd0]
00518a75 lea eax, [ebp - 0xb0]
00518a7b mulss xmm0, dword ptr [ebp - 0xb8]
00518a83 mov ecx, edi
00518a85 push eax
00518a86 push dword ptr [ebp - 0xb4]
00518a8c lea eax, [ebp - 0xe4]
00518a92 movss dword ptr [ebp - 0xe4], xmm0
00518a9a movss xmm0, dword ptr [ebp - 0xcc]
00518aa2 mulss xmm0, dword ptr [ebp - 0xb8]
00518aaa push eax
00518aab push esi
00518aac movss dword ptr [ebp - 0xe0], xmm0
00518ab4 call 0x6a1a20
00518ab9 mov eax, dword ptr [edi + 0xaf0]
00518abf test eax, eax
00518ac1 jle 0x518acf
00518ac3 sub eax, dword ptr [ebp - 0xd4]
00518ac9 mov dword ptr [edi + 0xaf0], eax
00518acf cmp dword ptr [edi + 0x70], 0
00518ad3 je 0x518ade
00518ad5 cmp byte ptr [edi + 0x80], 0
00518adc jne 0x518b50
00518ade mov esi, dword ptr [edi + 0x70]
00518ae1 test esi, esi
00518ae3 je 0x518b2f
00518ae5 cmp dword ptr [esi + 0x14], 0x10
00518ae9 mov eax, esi
00518aeb jb 0x518aef
00518aed mov eax, dword ptr [esi]
00518aef mov ecx, 0xb404a0
00518af4 mov dl, byte ptr [eax]
00518af6 cmp dl, byte ptr [ecx]
00518af8 jne 0x518b14
00518afa test dl, dl
00518afc je 0x518b10
00518afe mov dl, byte ptr [eax + 1]
00518b01 cmp dl, byte ptr [ecx + 1]
00518b04 jne 0x518b14
00518b06 add eax, 2
00518b09 add ecx, 2
00518b0c test dl, dl
00518b0e jne 0x518af4
00518b10 xor eax, eax
00518b12 jmp 0x518b19
00518b14 sbb eax, eax
00518b16 or eax, 1
00518b19 test eax, eax
00518b1b jne 0x518b2f
00518b1d cmp byte ptr [esi + 0x34], al
00518b20 je 0x518b50
00518b22 cmp byte ptr [edi + 0x80], al
00518b28 lea esi, [edi + 0x3c]
00518b2b jne 0x518b50
00518b2d jmp 0x518b32
00518b2f lea esi, [edi + 0x3c]
00518b32 push 1
00518b34 push 0xb404a0
00518b39 mov ecx, esi
00518b3b call 0x405740
00518b40 test al, al
00518b42 je 0x518b50
00518b44 lea ecx, [esi + 0x30]
00518b47 call 0x405330
00518b4c mov byte ptr [esi + 0x44], 1
00518b50 movss xmm0, dword ptr [edi + 0x14]
00518b55 xorps xmm4, xmm4
00518b58 comiss xmm0, xmm4
00518b5b jbe 0x518b67
00518b5d mov dword ptr [edi + 0xb00], 0x41a00000
00518b67 movss xmm3, dword ptr [ebp - 0xc4]
00518b6f movss xmm5, dword ptr [0xb6c980]
00518b77 movaps xmm0, xmm3
00518b7a movss xmm4, dword ptr [0xb6a9c8]
00518b82 andps xmm0, xmm5
00518b85 comiss xmm4, xmm0
00518b88 movss xmm2, dword ptr [ebp - 0xc0]
00518b90 ja 0x518b9d
00518b92 movaps xmm0, xmm2
00518b95 andps xmm0, xmm5
00518b98 comiss xmm4, xmm0
00518b9b jbe 0x518be1
00518b9d movaps xmm0, xmm2
00518ba0 movaps xmm1, xmm3
00518ba3 mulss xmm0, xmm2
00518ba7 mulss xmm1, xmm3
00518bab addss xmm0, xmm1
00518baf call 0x4228c0
00518bb4 movss xmm1, dword ptr [0xb6ac60]
00518bbc comiss xmm1, xmm0
00518bbf movss xmm4, dword ptr [0xb6a9c8]
00518bc7 jbe 0x518be1
00518bc9 movss xmm0, dword ptr [edi + 0xb00]
00518bd1 addss xmm0, dword ptr [0xb6a614]
00518bd9 movss dword ptr [edi + 0xb00], xmm0
00518be1 call 0x6c3d90
00518be6 movss xmm1, dword ptr [0xb6a19c]
00518bee movss xmm5, dword ptr [0xb6a2cc]
00518bf6 movd xmm0, eax
00518bfa cvtdq2pd xmm0, xmm0
00518bfe shr eax, 0x1f
00518c01 cmp dword ptr [edi + 0xe6c], -1
00518c08 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00518c11 cvtpd2ps xmm0, xmm0
00518c15 mulss xmm0, xmm1
00518c19 mulss xmm0, xmm5
00518c1d addss xmm0, dword ptr [edi + 0xb00]
00518c25 movss dword ptr [edi + 0xb00], xmm0
00518c2d je 0x518ca4
00518c2f push 9
00518c31 mov ecx, edi
00518c33 call 0x6af050
00518c38 test al, al
00518c3a je 0x519009
00518c40 push 1
00518c42 push 0xb43148
00518c47 lea ecx, [edi + 0x3c]
00518c4a mov dword ptr [edi + 0xab4], 6
00518c54 mov dword ptr [edi + 0x360], 0
00518c5e call 0x405740
00518c63 test al, al
00518c65 je 0x518c76
00518c67 lea ecx, [edi + 0x6c]
00518c6a call 0x405330
00518c6f mov byte ptr [edi + 0x80], 1
00518c76 movss xmm5, dword ptr [0xb6a2cc]
00518c7e lea esi, [edi + 0x294]
00518c84 mov dword ptr [edi + 0x150], 0
00518c8e mov eax, dword ptr [esi]
00518c90 mov dword ptr [edi + 0x28c], eax
00518c96 mov eax, dword ptr [esi + 4]
00518c99 mov dword ptr [edi + 0x290], eax
00518c9f jmp 0x519017
00518ca4 comiss xmm0, xmm4
00518ca7 jbe 0x518fa4
00518cad xor ecx, ecx
00518caf jmp 0x518cce
00518cb1 movss xmm1, dword ptr [0xb6a19c]
00518cb9 jmp 0x518cce
00518cbb nop dword ptr [eax + eax]
00518cc0 movss xmm1, dword ptr [0xb6a19c]
00518cc8 mov ecx, dword ptr [ebp - 0xb4]
00518cce movss xmm0, dword ptr [edi + 0x28c]
00518cd6 ucomiss xmm0, dword ptr [0xc02fec]
00518cdd lahf 
00518cde test ah, 0x44
00518ce1 jp 0x518f9c
00518ce7 movss xmm0, dword ptr [edi + 0x290]
00518cef ucomiss xmm0, dword ptr [0xc02ff0]
00518cf6 lahf 
00518cf7 test ah, 0x44
00518cfa jp 0x518f9c
00518d00 mov eax, ecx
00518d02 inc ecx
00518d03 mov dword ptr [ebp - 0xb4], ecx
00518d09 cmp eax, 2
00518d0c jge 0x518f9c
00518d12 call 0x6c3d90
00518d17 xorps xmm0, xmm0
00518d1a cvtsi2sd xmm0, eax
00518d1e shr eax, 0x1f
00518d21 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00518d2a cvtpd2ps xmm0, xmm0
00518d2e mulss xmm0, xmm1
00518d32 mulss xmm0, dword ptr [0xb6abec]
00518d3a addss xmm0, dword ptr [0xb6aa8c]
00518d42 movss dword ptr [ebp - 0xb8], xmm0
00518d4a call 0x6c3d90
00518d4f xorps xmm0, xmm0
00518d52 cvtsi2sd xmm0, eax
00518d56 shr eax, 0x1f
00518d59 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00518d62 cvtpd2ps xmm0, xmm0
00518d66 mulss xmm0, xmm1
00518d6a mulss xmm0, dword ptr [0xb6a874]
00518d72 addss xmm0, xmm0
00518d76 movss dword ptr [ebp - 0xbc], xmm0
00518d7e call 0x411fe0
00518d83 mulss xmm0, dword ptr [ebp - 0xb8]
00518d8b addss xmm0, dword ptr [edi + 0x294]
00518d93 movss dword ptr [ebp - 0xc8], xmm0
00518d9b movss xmm0, dword ptr [ebp - 0xbc]
00518da3 call 0x412010
00518da8 mulss xmm0, dword ptr [ebp - 0xb8]
00518db0 mov ecx, edi
00518db2 addss xmm0, dword ptr [edi + 0x298]
00518dba movss dword ptr [ebp - 0xb8], xmm0
00518dc2 call 0x695680
00518dc7 cmp dword ptr [edi + 0x2c], 1
00518dcb movss xmm2, dword ptr [eax + 0x294]
00518dd3 movss xmm1, dword ptr [eax + 0x298]
00518ddb subss xmm2, dword ptr [ebp - 0xc8]
00518de3 subss xmm1, dword ptr [ebp - 0xb8]
00518deb jne 0x518e21
00518ded mulss xmm1, xmm1
00518df1 mulss xmm2, xmm2
00518df5 addss xmm1, xmm2
00518df9 movaps xmm0, xmm1
00518dfc call 0x4228c0
00518e01 comiss xmm0, dword ptr [0xb6aa60]
00518e08 jbe 0x518cc0
00518e0e movss xmm1, dword ptr [0xb6ab20]
00518e16 comiss xmm1, xmm0
00518e19 jbe 0x518cc0
00518e1f jmp 0x518e78
00518e21 movss xmm5, dword ptr [0xb6c980]
00518e29 movaps xmm0, xmm2
00518e2c movss xmm4, dword ptr [0xb6a9c8]
00518e34 andps xmm0, xmm5
00518e37 comiss xmm0, xmm4
00518e3a jbe 0x518cc0
00518e40 movaps xmm0, xmm1
00518e43 andps xmm0, xmm5
00518e46 comiss xmm0, xmm4
00518e49 jbe 0x518cc0
00518e4f mulss xmm1, xmm1
00518e53 mulss xmm2, xmm2
00518e57 addss xmm1, xmm2
00518e5b movaps xmm0, xmm1
00518e5e call 0x4228c0
00518e63 comiss xmm0, dword ptr [0xb6aba8]
00518e6a jbe 0x518cc0
00518e70 movss xmm1, dword ptr [0xb6ab20]
00518e78 movss xmm2, dword ptr [0xb6aa3c]
00518e80 movss xmm0, dword ptr [ebp - 0xc8]
00518e88 subss xmm0, xmm2
00518e8c movss xmm3, dword ptr [0xb6a480]
00518e94 mov eax, dword ptr [0xbfd65c]
00518e99 mov ecx, dword ptr [ebp - 0xb4]
00518e9f divss xmm0, xmm2
00518ea3 mov esi, dword ptr [eax + 0x18190]
00518ea9 addss xmm0, xmm3
00518ead cvttss2si edx, xmm0
00518eb1 mov dword ptr [ebp - 0xd8], edx
00518eb7 test edx, edx
00518eb9 js 0x518cb1
00518ebf mov eax, dword ptr [esi + 0xc]
00518ec2 cmp edx, eax
00518ec4 jge 0x518cb1
00518eca movss xmm0, dword ptr [ebp - 0xb8]
00518ed2 subss xmm0, xmm1
00518ed6 movss xmm1, dword ptr [0xb6a19c]
00518ede divss xmm0, xmm2
00518ee2 addss xmm0, xmm3
00518ee6 cvttss2si ecx, xmm0
00518eea test ecx, ecx
00518eec js 0x518cc8
00518ef2 cmp ecx, dword ptr [esi + 0x10]
00518ef5 jge 0x518cc8
00518efb imul eax, ecx
00518efe mov ecx, dword ptr [ebp - 0xb4]
00518f04 mov dword ptr [ebp - 0xbc], eax
00518f0a add eax, edx
00518f0c js 0x518cce
00518f12 cmp eax, 0x1c0
00518f17 jge 0x518f2a
00518f19 cmp dword ptr [esi + eax*4 + 0x76c], 0x1f4
00518f24 jge 0x518cce
00518f2a mov ecx, esi
00518f2c push eax
00518f2d call 0x7aeec0
00518f32 movss xmm1, dword ptr [0xb6a19c]
00518f3a mov ecx, dword ptr [ebp - 0xb4]
00518f40 test eax, eax
00518f42 jne 0x518cce
00518f48 mov ecx, dword ptr [esi + 0xc]
00518f4b mov eax, dword ptr [ebp - 0xbc]
00518f51 mov esi, dword ptr [ebp - 0xd8]
00518f57 movss xmm2, dword ptr [0xb6aa3c]
00518f5f lea eax, [eax + esi]
00518f62 cdq 
00518f63 idiv ecx
00518f65 movd xmm1, edx
00518f69 movd xmm0, eax
00518f6d cvtdq2ps xmm1, xmm1
00518f70 cvtdq2ps xmm0, xmm0
00518f73 mulss xmm1, xmm2
00518f77 mulss xmm0, xmm2
00518f7b addss xmm1, xmm2
00518f7f addss xmm0, dword ptr [0xb6ab20]
00518f87 movss dword ptr [edi + 0x28c], xmm1
00518f8f movss dword ptr [edi + 0x290], xmm0
00518f97 jmp 0x518cc0
00518f9c movss xmm5, dword ptr [0xb6a2cc]
00518fa4 movss xmm0, dword ptr [edi + 0xb00]
00518fac comiss xmm0, dword ptr [0xb6aa3c]
00518fb3 jbe 0x519011
00518fb5 push 0xc02fec
00518fba lea ecx, [edi + 0x28c]
00518fc0 call 0x962ca0
00518fc5 test al, al
00518fc7 je 0x519011
00518fc9 push 1
00518fcb push 0xb43148
00518fd0 lea ecx, [edi + 0x3c]
00518fd3 mov dword ptr [edi + 0xab4], 6
00518fdd mov dword ptr [edi + 0x360], 0
00518fe7 call 0x405740
00518fec test al, al
00518fee je 0x518fff
00518ff0 lea ecx, [edi + 0x6c]
00518ff3 call 0x405330
00518ff8 mov byte ptr [edi + 0x80], 1
00518fff mov dword ptr [edi + 0x150], 0
00519009 movss xmm5, dword ptr [0xb6a2cc]
00519011 lea esi, [edi + 0x294]
00519017 cmp dword ptr [edi + 0x28], 0x103
0051901e jne 0x51904c
00519020 movss xmm2, dword ptr [edi + 0xb08]
00519028 xorps xmm1, xmm1
0051902b comiss xmm1, xmm2
0051902e jbe 0x51904c
00519030 movss xmm0, dword ptr [edi + 0x2f4]
00519038 mulss xmm0, xmm5
0051903c addss xmm0, xmm2
00519040 minss xmm0, xmm1
00519044 movss dword ptr [edi + 0xb08], xmm0
0051904c cmp dword ptr [edi + 0xaf0], 0
00519053 jg 0x5198aa
00519059 movss xmm1, dword ptr [ebp - 0xc0]
00519061 movss xmm0, dword ptr [ebp - 0xc4]
00519069 mulss xmm1, xmm1
0051906d mulss xmm0, xmm0
00519071 addss xmm1, xmm0
00519075 movaps xmm0, xmm1
00519078 movss dword ptr [ebp - 0xbc], xmm1
00519080 call 0x4228c0
00519085 movss xmm3, dword ptr [ebp - 0xc4]
0051908d xorps xmm4, xmm4
00519090 comiss xmm0, xmm4
00519093 jbe 0x519458
00519099 movss xmm1, dword ptr [0xb6a614]
005190a1 divss xmm1, xmm0
005190a5 movaps xmm0, xmm1
005190a8 mulss xmm1, dword ptr [ebp - 0xc0]
005190b0 mulss xmm3, xmm0
005190b4 jmp 0x519460
005190b9 cmp eax, 6
005190bc jne 0x519213
005190c2 cmp dword ptr [edi + 0xe6c], -1
005190c9 je 0x519118
005190cb lea ecx, [edi + 0x28c]
005190d1 push 0xc02fec
005190d6 call 0x962ca0
005190db test al, al
005190dd je 0x519118
005190df push 2
005190e1 movaps xmm2, xmm1
005190e4 mov ecx, edi
005190e6 call 0x6af8d0
005190eb push 1
005190ed push 0
005190ef push ecx
005190f0 mov dword ptr [esp], 0x40800000
005190f7 lea ecx, [edi + 0x364]
005190fd push 0xc02fec
00519102 call 0x7a3650
00519107 mov eax, dword ptr [esi]
00519109 mov dword ptr [edi + 0x28c], eax
0051910f mov eax, dword ptr [esi + 4]
00519112 mov dword ptr [edi + 0x290], eax
00519118 cmp dword ptr [edi + 0x360], 0x18
0051911f lea ecx, [edi + 0x28c]
00519125 mov dword ptr [edi + 0x180], 0
0051912f jle 0x5191d7
00519135 push 0xc02fec
0051913a call 0x962ca0
0051913f test al, al
00519141 je 0x5191d7
00519147 mov eax, dword ptr [edi + 0x288]
0051914d lea ecx, [edi + 0x3c]
00519150 push 1
00519152 push 0xb43130
00519157 mov eax, dword ptr [eax + 0x24]
0051915a mov dword ptr [edi + 0x150], eax
00519160 call 0x405740
00519165 test al, al
00519167 je 0x51917e
00519169 lea ecx, [edi + 0x6c]
0051916c call 0x405330
00519171 mov byte ptr [edi + 0x80], 1
00519178 lea esi, [edi + 0x294]
0051917e mov dword ptr [edi + 0x360], 0
00519188 mov ecx, edi
0051918a mov eax, dword ptr [edi + 0x28c]
00519190 mov dword ptr [esi], eax
00519192 mov eax, dword ptr [edi + 0x290]
00519198 mov dword ptr [esi + 4], eax
0051919b movss xmm0, dword ptr [0xc02fec]
005191a3 movss dword ptr [edi + 0x28c], xmm0
005191ab movss xmm0, dword ptr [0xc02ff0]
005191b3 movss dword ptr [edi + 0x290], xmm0
005191bb mov dword ptr [edi + 0xb00], 0
005191c5 call 0x6afa80
005191ca movss xmm5, dword ptr [0xb6a2cc]
005191d2 jmp 0x519017
005191d7 cmp dword ptr [edi + 0x70], 0
005191db je 0x5191ea
005191dd cmp byte ptr [edi + 0x80], 0
005191e4 jne 0x51942a
005191ea push 0xc02fec
005191ef call 0x962c70
005191f4 movss xmm5, dword ptr [0xb6a2cc]
005191fc test al, al
005191fe je 0x519017
00519204 mov dword ptr [edi + 0xab4], 4
0051920e jmp 0x519017
00519213 cmp eax, 8
00519216 jne 0x51942a
0051921c push 0
0051921e movaps xmm2, xmm1
00519221 mov ecx, edi
00519223 call 0x6af8d0
00519228 xor ecx, ecx
0051922a mov dword ptr [ebp - 0xc8], ecx
00519230 cmp dword ptr [ebp - 0xd4], ecx
00519236 jle 0x51942a
0051923c mov dword ptr [ebp - 0xbc], 0xa
00519246 nop word ptr [eax + eax]
00519250 mov eax, dword ptr [edi + 0xaf0]
00519256 test eax, eax
00519258 jle 0x519437
0051925e dec eax
0051925f mov dword ptr [edi + 0xaf0], eax
00519265 cdq 
00519266 idiv dword ptr [ebp - 0xbc]
0051926c test edx, edx
0051926e jne 0x519417
00519274 push 1
00519276 lea ecx, [edi + 0x3c]
00519279 push 0xb40510
0051927e call 0x405740
00519283 test al, al
00519285 je 0x51929c
00519287 lea ecx, [edi + 0x6c]
0051928a call 0x405330
0051928f mov byte ptr [edi + 0x80], 1
00519296 lea esi, [edi + 0x294]
0051929c mov ecx, edi
0051929e call 0x695680
005192a3 mov ecx, edi
005192a5 movss xmm0, dword ptr [eax + 0x2b8]
005192ad movss xmm2, dword ptr [eax + 0x2bc]
005192b5 movss dword ptr [ebp - 0xb4], xmm0
005192bd movss dword ptr [ebp - 0xb8], xmm2
005192c5 call 0x695680
005192ca cmp dword ptr [edi + 0xe6c], -1
005192d1 movss xmm1, dword ptr [ebp - 0xb4]
005192d9 movss xmm2, dword ptr [ebp - 0xb8]
005192e1 mulss xmm1, dword ptr [0xb6a8f4]
005192e9 mulss xmm2, dword ptr [0xb6a8f4]
005192f1 addss xmm1, dword ptr [eax + 0x294]
005192f9 movss xmm0, dword ptr [esi]
005192fd addss xmm2, dword ptr [eax + 0x298]
00519305 movss xmm3, dword ptr [esi + 4]
0051930a subss xmm1, xmm0
0051930e subss xmm2, xmm3
00519312 movss dword ptr [ebp - 0xb4], xmm1
0051931a movss dword ptr [ebp - 0xb8], xmm2
00519322 je 0x519386
00519324 mov ecx, dword ptr [edi + 0xe78]
0051932a test ecx, ecx
0051932c je 0x51934e
0051932e mov eax, dword ptr [ecx + 0x294]
00519334 mov ecx, dword ptr [ecx + 0x298]
0051933a mov dword ptr [ebp - 0xd0], eax
00519340 lea eax, [ebp - 0xd0]
00519346 mov dword ptr [ebp - 0xcc], ecx
0051934c jmp 0x519365
0051934e mov eax, dword ptr [esi]
00519350 mov ecx, dword ptr [esi + 4]
00519353 mov dword ptr [ebp - 0xe4], eax
00519359 lea eax, [ebp - 0xe4]
0051935f mov dword ptr [ebp - 0xe0], ecx
00519365 movss xmm1, dword ptr [eax]
00519369 movss xmm2, dword ptr [eax + 4]
0051936e subss xmm1, xmm0
00519372 subss xmm2, xmm3
00519376 movss dword ptr [ebp - 0xb4], xmm1
0051937e movss dword ptr [ebp - 0xb8], xmm2
00519386 movaps xmm0, xmm1
00519389 mulss xmm0, xmm1
0051938d movaps xmm1, xmm2
00519390 mulss xmm1, xmm2
00519394 addss xmm0, xmm1
00519398 call 0x4228c0
0051939d comiss xmm0, dword ptr [0xb6a18c]
005193a4 movss xmm2, dword ptr [ebp - 0xb8]
005193ac jbe 0x5193cc
005193ae movss xmm1, dword ptr [0xb6a614]
005193b6 divss xmm1, xmm0
005193ba movss xmm0, dword ptr [ebp - 0xb4]
005193c2 mulss xmm0, xmm1
005193c6 mulss xmm2, xmm1
005193ca jmp 0x5193d4
005193cc movss xmm0, dword ptr [ebp - 0xb4]
005193d4 mulss xmm0, dword ptr [0xb6a974]
005193dc lea ecx, [ebp - 0xb0]
005193e2 mulss xmm2, dword ptr [0xb6a974]
005193ea movss dword ptr [ebp - 0xdc], xmm0
005193f2 movss dword ptr [ebp - 0xd8], xmm2
005193fa call 0x430d70
005193ff push eax
00519400 push 0
00519402 lea eax, [ebp - 0xdc]
00519408 mov ecx, edi
0051940a push eax
0051940b push esi
0051940c call 0x6a1a20
00519411 mov ecx, dword ptr [ebp - 0xc8]
00519417 inc ecx
00519418 mov dword ptr [ebp - 0xc8], ecx
0051941e cmp ecx, dword ptr [ebp - 0xd4]
00519424 jl 0x519250
0051942a movss xmm5, dword ptr [0xb6a2cc]
00519432 jmp 0x519017
00519437 movss xmm5, dword ptr [0xb6a2cc]
0051943f mov dword ptr [edi + 0xab4], 4
00519449 mov dword ptr [edi + 0xaf4], 0x1e
00519453 jmp 0x519017
00519458 movss xmm1, dword ptr [ebp - 0xc0]
00519460 movss xmm2, dword ptr [edi + 0x2c4]
00519468 mulss xmm3, dword ptr [0xb6a3d4]
00519470 mulss xmm1, dword ptr [0xb6a3d4]
00519478 ucomiss xmm2, xmm4
0051947b lahf 
0051947c test ah, 0x44
0051947f jnp 0x5194b9
00519481 movss xmm0, dword ptr [edi + 0x2f4]
00519489 mulss xmm3, xmm0
0051948d mulss xmm1, xmm0
00519491 divss xmm3, xmm2
00519495 divss xmm1, xmm2
00519499 addss xmm3, dword ptr [edi + 0x2b8]
005194a1 addss xmm1, dword ptr [edi + 0x2bc]
005194a9 movss dword ptr [edi + 0x2b8], xmm3
005194b1 movss dword ptr [edi + 0x2bc], xmm1
005194b9 mov eax, dword ptr [edi + 0x28]
005194bc cmp eax, 0x103
005194c1 jne 0x519960
005194c7 cmp dword ptr [edi + 0xe6c], -1
005194ce je 0x5195e3
005194d4 push 8
005194d6 mov ecx, edi
005194d8 call 0x6af050
005194dd movss xmm1, dword ptr [edi + 0xb08]
005194e5 test al, al
005194e7 je 0x5195c7
005194ed comiss xmm1, dword ptr [0xb6a18c]
005194f4 jb 0x519960
005194fa movss xmm0, dword ptr [edi + 0x2f4]
00519502 lea eax, [ebp - 0xec]
00519508 movss dword ptr [ebp - 0xd8], xmm0
00519510 lea ecx, [ebp - 0xc4]
00519516 mulss xmm0, dword ptr [0xb6a274]
0051951e push eax
0051951f addss xmm0, xmm1
00519523 movss xmm1, dword ptr [0xb6a614]
0051952b minss xmm0, xmm1
0051952f subss xmm1, xmm0
00519533 movss dword ptr [edi + 0xb08], xmm0
0051953b movss dword ptr [ebp - 0xbc], xmm1
00519543 call 0x962560
00519548 movss xmm3, dword ptr [edi + 0x2c4]
00519550 ucomiss xmm3, dword ptr [0xb6a18c]
00519557 movss xmm1, dword ptr [eax]
0051955b movss xmm2, dword ptr [eax + 4]
00519560 mulss xmm1, dword ptr [0xb6a70c]
00519568 mulss xmm2, dword ptr [0xb6a70c]
00519570 mulss xmm1, dword ptr [ebp - 0xbc]
00519578 mulss xmm2, dword ptr [ebp - 0xbc]
00519580 lahf 
00519581 test ah, 0x44
00519584 jnp 0x519960
0051958a movss xmm0, dword ptr [ebp - 0xd8]
00519592 mulss xmm1, xmm0
00519596 mulss xmm0, xmm2
0051959a divss xmm1, xmm3
0051959e divss xmm0, xmm3
005195a2 addss xmm1, dword ptr [edi + 0x2b8]
005195aa addss xmm0, dword ptr [edi + 0x2bc]
005195b2 movss dword ptr [edi + 0x2b8], xmm1
005195ba movss dword ptr [edi + 0x2bc], xmm0
005195c2 jmp 0x519960
005195c7 comiss xmm1, dword ptr [0xb6a18c]
005195ce jbe 0x519960
005195d4 mov dword ptr [edi + 0xb08], 0xbf800000
005195de jmp 0x519960
005195e3 movss xmm3, dword ptr [0xb6aafc]
005195eb lea eax, [ebp - 0xfc]
005195f1 push 4
005195f3 push esi
005195f4 push eax
005195f5 mov eax, dword ptr [0xbfd65c]
005195fa mov ecx, dword ptr [eax + 0x18190]
00519600 add ecx, 0x1218
00519606 call 0x4157f0
0051960b mov edx, dword ptr [ebp - 0xf0]
00519611 test edx, edx
00519613 je 0x51988a
00519619 movss xmm0, dword ptr [ebp - 0xbc]
00519621 lea eax, [ebp - 0xd8]
00519627 xorps xmm1, xmm1
0051962a mov dword ptr [ebp - 0xd8], 0
00519634 comiss xmm1, xmm0
00519637 lea ecx, [ebp - 0xbc]
0051963d movss xmm1, dword ptr [0xb6ad38]
00519645 movss dword ptr [ebp - 0xbc], xmm0
0051964d cmovbe eax, ecx
00519650 movss xmm0, dword ptr [eax]
00519654 comiss xmm0, xmm1
00519657 ja 0x51965f
00519659 movss xmm0, xmm0
0051965d jmp 0x519663
0051965f movss xmm0, xmm1
00519663 xor ecx, ecx
00519665 mov dword ptr [ebp - 0xbc], ecx
0051966b movss xmm7, dword ptr [0xc02fec]
00519673 movss xmm4, dword ptr [0xc02ff0]
0051967b movss dword ptr [ebp - 0xc8], xmm7
00519683 movss dword ptr [ebp - 0xd8], xmm4
0051968b divss xmm0, xmm1
0051968f movss dword ptr [ebp - 0xc0], xmm0
00519697 test edx, edx
00519699 je 0x51988a
0051969f xor edi, edi
005196a1 mov eax, dword ptr [ebp - 0xf8]
005196a7 movss xmm5, dword ptr [esi]
005196ab movss xmm6, dword ptr [esi + 4]
005196b0 mov eax, dword ptr [eax + edi*4]
005196b3 subss xmm5, dword ptr [eax + 0x294]
005196bb subss xmm6, dword ptr [eax + 0x298]
005196c3 movss xmm2, dword ptr [eax + 0x2bc]
005196cb movss xmm3, dword ptr [eax + 0x2b8]
005196d3 movaps xmm1, xmm2
005196d6 movaps xmm0, xmm3
005196d9 movss dword ptr [ebp - 0xb8], xmm2
005196e1 mulss xmm0, xmm5
005196e5 mulss xmm1, xmm6
005196e9 addss xmm1, xmm0
005196ed comiss xmm1, dword ptr [0xb6a18c]
005196f4 jbe 0x519838
005196fa movaps xmm1, xmm5
005196fd movaps xmm0, xmm6
00519700 mulss xmm0, xmm6
00519704 xorps xmm4, xmm4
00519707 mulss xmm1, xmm5
0051970b mulss xmm5, xmm2
0051970f addss xmm1, xmm0
00519713 movss xmm0, dword ptr [0xb6a614]
0051971b divss xmm1, dword ptr [0xb6ad38]
00519723 subss xmm0, xmm1
00519727 movss xmm1, dword ptr [0xb6c9b0]
0051972f xorps xmm3, xmm1
00519732 movss dword ptr [ebp - 0xb4], xmm3
0051973a movss dword ptr [ebp - 0xcc], xmm0
00519742 movaps xmm0, xmm3
00519745 mulss xmm0, xmm6
00519749 addss xmm0, xmm5
0051974d comiss xmm4, xmm0
00519750 jbe 0x519768
00519752 xorps xmm2, xmm1
00519755 xorps xmm3, xmm1
00519758 movss dword ptr [ebp - 0xb8], xmm2
00519760 movss dword ptr [ebp - 0xb4], xmm3
00519768 call 0x6c3d90
0051976d xorps xmm0, xmm0
00519770 movaps xmm1, xmm3
00519773 mulss xmm1, xmm3
00519777 cvtsi2sd xmm0, eax
0051977b shr eax, 0x1f
0051977e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00519787 cvtpd2ps xmm0, xmm0
0051978b mulss xmm0, dword ptr [0xb6a19c]
00519793 movss dword ptr [ebp - 0xe0], xmm0
0051979b movaps xmm0, xmm2
0051979e mulss xmm0, xmm2
005197a2 addss xmm0, xmm1
005197a6 call 0x4228c0
005197ab comiss xmm0, dword ptr [0xb6a18c]
005197b2 movss xmm2, dword ptr [ebp - 0xb4]
005197ba jbe 0x5197f6
005197bc movss xmm1, dword ptr [ebp - 0xe0]
005197c4 addss xmm1, xmm1
005197c8 addss xmm1, dword ptr [0xb6a7b0]
005197d0 mulss xmm1, dword ptr [ebp - 0xcc]
005197d8 mulss xmm1, dword ptr [ebp - 0xc0]
005197e0 divss xmm1, xmm0
005197e4 movss xmm0, dword ptr [ebp - 0xb8]
005197ec mulss xmm0, xmm1
005197f0 mulss xmm2, xmm1
005197f4 jmp 0x5197fe
005197f6 movss xmm0, dword ptr [ebp - 0xb8]
005197fe addss xmm0, dword ptr [ebp - 0xc8]
00519806 movss xmm4, dword ptr [ebp - 0xd8]
0051980e mov ecx, dword ptr [ebp - 0xbc]
00519814 addss xmm4, xmm2
00519818 mov edx, dword ptr [ebp - 0xf0]
0051981e inc ecx
0051981f mov dword ptr [ebp - 0xbc], ecx
00519825 movaps xmm7, xmm0
00519828 movss dword ptr [ebp - 0xc8], xmm7
00519830 movss dword ptr [ebp - 0xd8], xmm4
00519838 inc edi
00519839 cmp edi, edx
0051983b jb 0x5196a1
00519841 mov edi, dword ptr [ebp - 0xe8]
00519847 test ecx, ecx
00519849 jle 0x51988a
0051984b movd xmm1, ecx
0051984f cvtdq2ps xmm1, xmm1
00519852 movss xmm0, dword ptr [edi + 0x2f4]
0051985a divss xmm7, xmm1
0051985e divss xmm4, xmm1
00519862 mulss xmm7, xmm0
00519866 mulss xmm4, xmm0
0051986a addss xmm7, dword ptr [edi + 0x2b8]
00519872 addss xmm4, dword ptr [edi + 0x2bc]
0051987a movss dword ptr [edi + 0x2b8], xmm7
00519882 movss dword ptr [edi + 0x2bc], xmm4
0051988a cmp byte ptr [ebp - 0xfc], 0
00519891 jne 0x519960
00519897 push dword ptr [ebp - 0xf8]
0051989d call 0x9eace5
005198a2 add esp, 4
005198a5 jmp 0x519960
005198aa cmp dword ptr [edi + 0xe6c], -1
005198b1 je 0x519960
005198b7 movss xmm1, dword ptr [ebp - 0xc4]
005198bf movss xmm0, dword ptr [ebp - 0xc0]
005198c7 mulss xmm0, xmm0
005198cb mulss xmm1, xmm1
005198cf addss xmm0, xmm1
005198d3 call 0x4228c0
005198d8 movss xmm2, dword ptr [ebp - 0xc4]
005198e0 xorps xmm3, xmm3
005198e3 comiss xmm0, xmm3
005198e6 movss xmm1, dword ptr [ebp - 0xc0]
005198ee jbe 0x519907
005198f0 movss xmm4, dword ptr [0xb6a614]
005198f8 divss xmm4, xmm0
005198fc movaps xmm0, xmm4
005198ff mulss xmm1, xmm4
00519903 mulss xmm2, xmm0
00519907 movss xmm4, dword ptr [edi + 0x2c4]
0051990f mulss xmm2, dword ptr [0xb6a2cc]
00519917 mulss xmm1, dword ptr [0xb6a2cc]
0051991f ucomiss xmm4, xmm3
00519922 lahf 
00519923 test ah, 0x44
00519926 jnp 0x519960
00519928 movss xmm0, dword ptr [edi + 0x2f4]
00519930 mulss xmm2, xmm0
00519934 mulss xmm1, xmm0
00519938 divss xmm2, xmm4
0051993c divss xmm1, xmm4
00519940 addss xmm2, dword ptr [edi + 0x2b8]
00519948 addss xmm1, dword ptr [edi + 0x2bc]
00519950 movss dword ptr [edi + 0x2b8], xmm2
00519958 movss dword ptr [edi + 0x2bc], xmm1
00519960 mov eax, dword ptr [ebp - 0xd4]
00519966 add dword ptr [edi + 0x360], eax
0051996c mov ecx, dword ptr [ebp - 4]
0051996f pop edi
00519970 xor ecx, ebp
00519972 pop esi
00519973 call 0x9eacd7
00519978 mov esp, ebp
0051997a pop ebp
0051997b mov esp, ebx
0051997d pop ebx
0051997e ret 
0051997f int3 
00519980 push ebx
00519981 mov ebx, esp
00519983 sub esp, 8
00519986 and esp, 0xfffffff8
00519989 add esp, 4
0051998c push ebp
0051998d mov ebp, dword ptr [ebx + 4]
00519990 mov dword ptr [esp + 4], ebp
00519994 mov ebp, esp
00519996 sub esp, 0x10
00519999 push esi
0051999a mov esi, ecx
0051999c push edi
0051999d cmp dword ptr [esi + 0xab4], 0
005199a4 jne 0x519a00
005199a6 mov eax, dword ptr [esi + 0x2b8]
005199ac mov dword ptr [esi + 0xb00], eax
005199b2 mov eax, dword ptr [esi + 0x2bc]
005199b8 mov dword ptr [esi + 0xb04], eax
005199be mov dword ptr [esi + 0xab4], 4
005199c8 mov dword ptr [esi + 0x360], 0
005199d2 mov dword ptr [esi + 0x2d8], 0
005199dc mov dword ptr [esi + 0x2dc], 0
005199e6 mov dword ptr [esi + 0x17c], 0
005199f0 mov byte ptr [esi + 0xb8c], 0
005199f7 pop edi
005199f8 pop esi
005199f9 mov esp, ebp
005199fb pop ebp
005199fc mov esp, ebx
005199fe pop ebx
005199ff ret 
