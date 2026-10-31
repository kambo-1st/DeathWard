008d6600 push ebp
008d6601 mov ebp, esp
008d6603 sub esp, 0x58
008d6606 mov eax, dword ptr [0xbaa3b4]
008d660b xor eax, ebp
008d660d mov dword ptr [ebp - 8], eax
008d6610 push ebx
008d6611 mov ebx, ecx
008d6613 movss dword ptr [ebp - 0xc], xmm2
008d6618 push esi
008d6619 push edi
008d661a mov ecx, dword ptr [ebx + 0x47c]
008d6620 test ecx, ecx
008d6622 je 0x8d662d
008d6624 call 0x8c5980
008d6629 mov esi, eax
008d662b jmp 0x8d6633
008d662d lea esi, [ebx + 0x470]
008d6633 mov edi, dword ptr [ebp + 8]
008d6636 mov ecx, edi
008d6638 call 0x68d5a0
008d663d push eax
008d663e mov ecx, esi
008d6640 call 0x422c30
008d6645 mov edx, dword ptr [edi + 0x28]
008d6648 cmp edx, 4
008d664b je 0x8d687c
008d6651 mov eax, dword ptr [ebx + 0x320]
008d6657 mov ecx, ebx
008d6659 test eax, eax
008d665b cmovne ecx, eax
008d665e mov dword ptr [ebp - 0x20], ecx
008d6661 cmp edx, 1
008d6664 jne 0x8d66b2
008d6666 push ecx
008d6667 lea ecx, [ebp - 0x58]
008d666a call 0x4229a0
008d666f push 0
008d6671 push 0xbeab9c
008d6676 push 0xbeab18
008d667b push 0
008d667d push edi
008d667e call 0x9ec34c
008d6683 add esp, 0x14
008d6686 lea ecx, [ebp - 0x58]
008d6689 mov edx, dword ptr [eax]
008d668b push 0x1e
008d668d push ecx
008d668e push 0
008d6690 push 8
008d6692 push ecx
008d6693 mov ecx, eax
008d6695 mov dword ptr [esp], 0x3f800000
008d669c call dword ptr [edx + 0x20]
008d669f pop edi
008d66a0 pop esi
008d66a1 pop ebx
008d66a2 mov ecx, dword ptr [ebp - 8]
008d66a5 xor ecx, ebp
008d66a7 call 0x9eacd7
008d66ac mov esp, ebp
008d66ae pop ebp
008d66af ret 4
008d66b2 cmp edx, 3
008d66b5 jne 0x8d6714
008d66b7 mov edx, dword ptr [edi + 0x2c]
008d66ba cmp edx, 0x3e
008d66bd je 0x8d66d2
008d66bf mov eax, dword ptr [0xbfd65c]
008d66c4 cmp dword ptr [eax + 0x1c319c], 0x1e
008d66cb jne 0x8d6714
008d66cd cmp edx, 0x43
008d66d0 jne 0x8d6714
008d66d2 push ecx
008d66d3 lea ecx, [ebp - 0x58]
008d66d6 call 0x4229a0
008d66db push 0
008d66dd push 0xbeab40
008d66e2 push 0xbeab18
008d66e7 push 0
008d66e9 push edi
008d66ea call 0x9ec34c
008d66ef add esp, 0x14
008d66f2 lea edx, [ebp - 0x58]
008d66f5 mov ecx, dword ptr [eax + 0x360]
008d66fb push 0x1e
008d66fd push edx
008d66fe push 0
008d6700 mov eax, dword ptr [ecx]
008d6702 push 0x808
008d6707 push ecx
008d6708 mov dword ptr [esp], 0x3f800000
008d670f jmp 0x8d6879
008d6714 movups xmm0, xmmword ptr [ebx + 0x378]
008d671b push ebx
008d671c sub esp, 0x14
008d671f mov dword ptr [ebp - 0x1c], 8
008d6726 mov eax, esp
008d6728 mov dword ptr [ebp - 0x18], 0
008d672f lea edx, [ebp - 0x1c]
008d6732 push ecx
008d6733 movups xmmword ptr [eax], xmm0
008d6736 call 0x656c90
008d673b movss xmm0, dword ptr [ebp - 0xc]
008d6740 lea edx, [ebx + 0x294]
008d6746 add esp, 0x18
008d6749 mov ecx, edi
008d674b movss dword ptr [esp], xmm0
008d6750 movups xmm0, xmmword ptr [ebx + 0x378]
008d6757 push ebx
008d6758 sub esp, 0x10
008d675b mov eax, esp
008d675d movups xmmword ptr [eax], xmm0
008d6760 call 0x654de0
008d6765 mov ecx, dword ptr [edi + 0x164]
008d676b xor eax, eax
008d676d and ecx, 0x1000000
008d6773 add esp, 0x18
008d6776 or eax, ecx
008d6778 je 0x8d67f2
008d677a mov ecx, ebx
008d677c call 0x8c5940
008d6781 test al, al
008d6783 je 0x8d67f2
008d6785 mov esi, dword ptr [0xbfd680]
008d678b lea ecx, [ebp - 0x10]
008d678e mov dword ptr [ebp - 0x10], 0x4d
008d6795 call 0x8b1340
008d679a sub esp, 8
008d679d mov dword ptr [esp + 4], 0
008d67a5 mov dword ptr [esp], 0x3f800000
008d67ac push 0
008d67ae push 8
008d67b0 push ecx
008d67b1 mov dword ptr [esp], 0x3f333333
008d67b8 lea ecx, [esi + 0x29de0]
008d67be push dword ptr [ebp - 0x10]
008d67c1 call 0x888de0
008d67c6 movss xmm0, dword ptr [ebp - 0xc]
008d67cb mov eax, dword ptr [edi + 0x160]
008d67d1 addss xmm0, xmm0
008d67d5 or dword ptr [edi + 0x164], 0x800000
008d67df mov dword ptr [edi + 0x160], eax
008d67e5 addss xmm0, dword ptr [0xb6a864]
008d67ed movss dword ptr [ebp - 0xc], xmm0
008d67f2 movss xmm0, dword ptr [ebx + 0x444]
008d67fa xorps xmm1, xmm1
008d67fd comiss xmm0, xmm1
008d6800 jbe 0x8d6851
008d6802 push 0
008d6804 mov ecx, edi
008d6806 call 0x68cf40
008d680b test al, al
008d680d je 0x8d6851
008d680f mov eax, dword ptr [edi + 0x344]
008d6815 lea ecx, [ebp - 0x30]
008d6818 movq xmm0, qword ptr [0xa08ab8]
008d6820 mov dword ptr [ebp - 0x30], eax
008d6823 mov eax, dword ptr [0xa08ac0]
008d6828 movq qword ptr [ebp - 0x2c], xmm0
008d682d mov dword ptr [ebp - 0x24], eax
008d6830 call 0x7a7db0
008d6835 movss xmm0, dword ptr [ebx + 0x444]
008d683d fstp dword ptr [ebp - 0x10]
008d6840 comiss xmm0, dword ptr [ebp - 0x10]
008d6844 jbe 0x8d6851
008d6846 mov esi, dword ptr [ebp - 0x1c]
008d6849 or esi, 0x800000
008d684f jmp 0x8d6854
008d6851 mov esi, dword ptr [ebp - 0x1c]
008d6854 push dword ptr [ebp - 0x20]
008d6857 mov ebx, dword ptr [ebp - 0x18]
008d685a lea ecx, [ebp - 0x58]
008d685d call 0x4229a0
008d6862 movss xmm0, dword ptr [ebp - 0xc]
008d6867 lea ecx, [ebp - 0x58]
008d686a mov eax, dword ptr [edi]
008d686c push 0x1e
008d686e push ecx
008d686f push ebx
008d6870 push esi
008d6871 push ecx
008d6872 movss dword ptr [esp], xmm0
008d6877 mov ecx, edi
008d6879 call dword ptr [eax + 0x20]
008d687c mov ecx, dword ptr [ebp - 8]
008d687f pop edi
008d6880 pop esi
008d6881 xor ecx, ebp
008d6883 pop ebx
008d6884 call 0x9eacd7
008d6889 mov esp, ebp
008d688b pop ebp
008d688c ret 4
