006994f0 push ebp
006994f1 mov ebp, esp
006994f3 and esp, 0xfffffff8
006994f6 movss xmm3, dword ptr [ebp + 0x10]
006994fb sub esp, 0xc
006994fe ucomiss xmm3, dword ptr [0xc02fec]
00699505 push ebx
00699506 mov ebx, dword ptr [ebp + 8]
00699509 push esi
0069950a push edi
0069950b lahf 
0069950c test ah, 0x44
0069950f jp 0x699559
00699511 movss xmm0, dword ptr [ebp + 0x14]
00699516 ucomiss xmm0, dword ptr [0xc02ff0]
0069951d lahf 
0069951e test ah, 0x44
00699521 jp 0x699559
00699523 push 0
00699525 push 0
00699527 push ecx
00699528 mov ecx, dword ptr [0xbfd65c]
0069952e lea eax, [esp + 0x1c]
00699532 mov dword ptr [esp], 0x42c80000
00699539 push ebx
0069953a push eax
0069953b mov ecx, dword ptr [ecx + 0x18190]
00699541 call 0x7cf240
00699546 movss xmm3, dword ptr [eax]
0069954a movss dword ptr [ebp + 0x10], xmm3
0069954f movss xmm0, dword ptr [eax + 4]
00699554 movss dword ptr [ebp + 0x14], xmm0
00699559 mov esi, dword ptr [0xbfd65c]
0069955f cmp dword ptr [esi + 0x1c319c], 0x2c
00699566 jne 0x699584
00699568 push dword ptr [esi + 0x18194]
0069956e mov ecx, esi
00699570 call 0x71c300
00699575 movss xmm3, dword ptr [ebp + 0x10]
0069957a mov ecx, esi
0069957c mov esi, dword ptr [0xbfd65c]
00699582 jmp 0x699592
00699584 cmp dword ptr [esi + 0x1819c], 2
0069958b je 0x6995d9
0069958d mov eax, dword ptr [esi + 4]
00699590 mov ecx, esi
00699592 mov ecx, dword ptr [ecx]
00699594 mov edx, eax
00699596 push -1
00699598 call 0x7e79c0
0069959d add esp, 4
006995a0 cmp eax, 0x1b
006995a3 je 0x6995aa
006995a5 cmp eax, 0x1c
006995a8 jne 0x6995d9
006995aa mov eax, dword ptr [esi + 0x18190]
006995b0 movss xmm0, dword ptr [eax + 0x7134]
006995b8 comiss xmm0, dword ptr [0xb6a2cc]
006995bf jbe 0x6995d9
006995c1 mov edx, dword ptr [ebp + 0xc]
006995c4 lea eax, [ebp + 0x10]
006995c7 push eax
006995c8 mov ecx, ebx
006995ca call 0x54a7a0
006995cf add esp, 4
006995d2 pop edi
006995d3 pop esi
006995d4 pop ebx
006995d5 mov esp, ebp
006995d7 pop ebp
006995d8 ret 
006995d9 movss xmm2, dword ptr [0xb6aa3c]
006995e1 movss xmm0, dword ptr [ebp + 0x14]
006995e6 subss xmm3, xmm2
006995ea subss xmm0, dword ptr [0xb6ab20]
006995f2 mov ecx, dword ptr [esi + 0x18190]
006995f8 divss xmm3, xmm2
006995fc divss xmm0, xmm2
00699600 addss xmm3, dword ptr [0xb6a480]
00699608 addss xmm0, dword ptr [0xb6a480]
00699610 cvttss2si edi, xmm3
00699614 cvttss2si edx, xmm0
00699618 test edi, edi
0069961a js 0x699650
0069961c mov eax, dword ptr [ecx + 0xc]
0069961f cmp edi, eax
00699621 jge 0x699650
00699623 test edx, edx
00699625 js 0x699650
00699627 cmp edx, dword ptr [ecx + 0x10]
0069962a jge 0x699650
0069962c imul eax, edx
0069962f add eax, edi
00699631 cmp eax, 0x1bf
00699636 ja 0x699650
00699638 cmp dword ptr [ecx + eax*4 + 0x76c], 0x3b6
00699643 jg 0x699650
00699645 mov dword ptr [ecx + eax*4 + 0x76c], 0x384
00699650 call 0x6c3d90
00699655 cmp byte ptr [ebp + 0x18], 0
00699659 mov ecx, 0x5e
0069965e push 0
00699660 push eax
00699661 push 0
00699663 push dword ptr [ebp + 0xc]
00699666 mov eax, 0x55
0069966b push 0xc02fec
00699670 push ebx
00699671 cmovne eax, ecx
00699674 mov ecx, esi
00699676 push 0
00699678 push eax
00699679 call 0x6d0ca0
0069967e push 0
00699680 push 0xbeab70
00699685 push 0xbeab18
0069968a push 0
0069968c push eax
0069968d call 0x9ec34c
00699692 add esp, 0x14
00699695 mov dword ptr [eax + 0xab4], 6
0069969f movss xmm0, dword ptr [ebp + 0x10]
006996a4 movss dword ptr [eax + 0x28c], xmm0
006996ac movss xmm0, dword ptr [ebp + 0x14]
006996b1 movss dword ptr [eax + 0x290], xmm0
006996b9 movaps xmm1, xmm0
006996bc movss xmm2, dword ptr [eax + 0x28c]
006996c4 subss xmm2, dword ptr [eax + 0x294]
006996cc subss xmm1, dword ptr [eax + 0x298]
006996d4 movss xmm0, dword ptr [ebp + 0x1c]
006996d9 pop edi
006996da pop esi
006996db mulss xmm2, dword ptr [0xb6a264]
006996e3 mov dword ptr [eax + 0xb0c], 0xc1000000
006996ed mulss xmm1, dword ptr [0xb6a264]
006996f5 mov dword ptr [eax + 0x180], 0
006996ff movss dword ptr [eax + 0x2b8], xmm2
00699707 movss dword ptr [eax + 0xb00], xmm2
0069970f movss dword ptr [eax + 0x2bc], xmm1
00699717 movss dword ptr [eax + 0xb04], xmm1
0069971f movss dword ptr [eax + 0x2a8], xmm0
00699727 pop ebx
00699728 mov esp, ebp
0069972a pop ebp
0069972b ret 
