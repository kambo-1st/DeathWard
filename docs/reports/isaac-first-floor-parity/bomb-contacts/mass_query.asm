00689640 push ebp
00689641 mov ebp, esp
00689643 and esp, 0xfffffff8
00689646 push ecx
00689647 movss xmm2, dword ptr [0xb6a974]
0068964f xor eax, eax
00689651 push ebx
00689652 mov ebx, dword ptr [ebp + 8]
00689655 push esi
00689656 push edi
00689657 mov edi, ecx
00689659 mov edx, dword ptr [edi + 0x164]
0068965f movss xmm0, dword ptr [edi + 0x2d4]
00689667 and edx, 0x80000
0068966d or eax, edx
0068966f movss dword ptr [esp + 0xc], xmm0
00689675 je 0x68968e
00689677 mov eax, dword ptr [ebx + 0x28]
0068967a sub eax, 0xa
0068967d cmp eax, 0x3dd
00689682 ja 0x68968e
00689684 mulss xmm0, xmm2
00689688 movss dword ptr [esp + 0xc], xmm0
0068968e mov esi, dword ptr [edi + 0x28]
00689691 movaps xmm1, xmm0
00689694 cmp esi, 1
00689697 jne 0x6896dc
00689699 cmp dword ptr [ebx + 0x28], 3
0068969d jne 0x6896b2
0068969f cmp dword ptr [ebx + 0x2c], 0xef
006896a6 jne 0x6896b2
006896a8 mulss xmm0, xmm2
006896ac movss dword ptr [esp + 0xc], xmm0
006896b2 push 0x271
006896b7 lea ecx, [edi + 0x1450]
006896bd call 0x88b570
006896c2 movss xmm0, dword ptr [esp + 0xc]
006896c8 test al, al
006896ca je 0x6896ef
006896cc mulss xmm0, dword ptr [0xb6a974]
006896d4 movss dword ptr [esp + 0xc], xmm0
006896da jmp 0x6896ef
006896dc lea eax, [esi - 0xa]
006896df movaps xmm0, xmm1
006896e2 movss dword ptr [esp + 0xc], xmm0
006896e8 cmp eax, 0x3dd
006896ed jbe 0x689754
006896ef cmp esi, 1
006896f2 jne 0x6897aa
006896f8 cmp dword ptr [ebx + 0x28], 9
006896fc jne 0x6897aa
00689702 push 0
00689704 push 0x114
00689709 mov ecx, edi
0068970b call 0x73af30
00689710 test al, al
00689712 jne 0x68973d
00689714 push 0x3b
00689716 lea ecx, [edi + 0x1450]
0068971c call 0x88b600
00689721 test al, al
00689723 jne 0x68973d
00689725 cmp dword ptr [edi + 0x130c], 0x23
0068972c je 0x68973d
0068972e movss xmm0, dword ptr [esp + 0xc]
00689734 pop edi
00689735 pop esi
00689736 pop ebx
00689737 mov esp, ebp
00689739 pop ebp
0068973a ret 4
0068973d movss xmm0, dword ptr [esp + 0xc]
00689743 mulss xmm0, dword ptr [0xb6a9c8]
0068974b pop edi
0068974c pop esi
0068974d pop ebx
0068974e mov esp, ebp
00689750 pop ebp
00689751 ret 4
00689754 mov eax, dword ptr [ebx + 0x28]
00689757 cmp eax, 2
0068975a je 0x689761
0068975c cmp eax, 7
0068975f jne 0x6897a7
00689761 cmp esi, 0x19
00689764 je 0x68979f
00689766 cmp esi, 0x3e
00689769 je 0x68979f
0068976b cmp esi, 0x29
0068976e je 0x68979f
00689770 cmp esi, 0xfe
00689776 je 0x68979f
00689778 cmp esi, 0x5b
0068977b je 0x68979f
0068977d cmp esi, 0x17
00689780 je 0x68979f
00689782 cmp esi, 0x124
00689788 je 0x68979f
0068978a cmp esi, 0xf5
00689790 je 0x68979f
00689792 cmp esi, 0x37
00689795 je 0x68979f
00689797 cmp esi, 0x11b
0068979d jne 0x6897a7
0068979f mulss xmm1, dword ptr [0xb6aafc]
006897a7 movaps xmm0, xmm1
006897aa pop edi
006897ab pop esi
006897ac pop ebx
006897ad mov esp, ebp
006897af pop ebp
006897b0 ret 4
