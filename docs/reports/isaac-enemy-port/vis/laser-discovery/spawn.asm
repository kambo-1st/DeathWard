008c7550 push ebp
008c7551 mov ebp, esp
008c7553 and esp, 0xfffffff8
008c7556 push ecx
008c7557 push ebx
008c7558 push esi
008c7559 push edi
008c755a call 0x6c3d90
008c755f movzx ecx, byte ptr [ebp + 0x20]
008c7563 mov ebx, dword ptr [ebp + 0x1c]
008c7566 push ecx
008c7567 mov ecx, dword ptr [0xbfd65c]
008c756d push eax
008c756e push 0
008c7570 push ebx
008c7571 push 0xc02fec
008c7576 push dword ptr [ebp + 0xc]
008c7579 push dword ptr [ebp + 8]
008c757c push 7
008c757e call 0x6d0ca0
008c7583 mov esi, eax
008c7585 test esi, esi
008c7587 jne 0x8c7590
008c7589 pop edi
008c758a pop esi
008c758b pop ebx
008c758c mov esp, ebp
008c758e pop ebp
008c758f ret 
008c7590 mov ecx, dword ptr [ebp + 0x18]
008c7593 movss xmm0, dword ptr [ebp + 0x10]
008c7598 mov eax, dword ptr [ebp + 0x14]
008c759b movss dword ptr [esi + 0x36c], xmm0
008c75a3 movss dword ptr [esi + 0x368], xmm0
008c75ab mov dword ptr [esi + 0x3a8], eax
008c75b1 mov eax, dword ptr [ecx]
008c75b3 mov dword ptr [esi + 0x2a4], eax
008c75b9 mov eax, dword ptr [ecx + 4]
008c75bc mov dword ptr [esi + 0x2a8], eax
008c75c2 test ebx, ebx
008c75c4 je 0x8c7656
008c75ca mov ecx, dword ptr [esi + 0x320]
008c75d0 lea edi, [esi + 0x320]
008c75d6 test ecx, ecx
008c75d8 je 0x8c75ee
008c75da lea eax, [esp + 0xc]
008c75de mov dword ptr [esp + 0xc], edi
008c75e2 push eax
008c75e3 add ecx, 0x324
008c75e9 call 0x4bc3c0
008c75ee push edi
008c75ef mov ecx, ebx
008c75f1 mov dword ptr [edi], ebx
008c75f3 call 0x4bae70
008c75f8 mov ecx, dword ptr [esi + 0x314]
008c75fe lea edi, [esi + 0x314]
008c7604 test ecx, ecx
008c7606 je 0x8c761c
008c7608 lea eax, [esp + 0xc]
008c760c mov dword ptr [esp + 0xc], edi
008c7610 push eax
008c7611 add ecx, 0x324
008c7617 call 0x4bc3c0
008c761c push edi
008c761d mov ecx, ebx
008c761f mov dword ptr [edi], ebx
008c7621 call 0x4bae70
008c7626 movss xmm1, dword ptr [esi + 0x294]
008c762e movss xmm0, dword ptr [esi + 0x298]
008c7636 subss xmm1, dword ptr [ebx + 0x294]
008c763e subss xmm0, dword ptr [ebx + 0x298]
008c7646 movss dword ptr [esi + 0x360], xmm1
008c764e movss dword ptr [esi + 0x364], xmm0
008c7656 pop edi
008c7657 mov eax, esi
008c7659 pop esi
008c765a pop ebx
008c765b mov esp, ebp
008c765d pop ebp
008c765e ret 
008c765f int3 
008c7660 push ebp
008c7661 mov ebp, esp
008c7663 cmp byte ptr [ebp + 0x14], 0
008c7667 movss xmm0, dword ptr [ebp + 0xc]
008c766c movss xmm1, dword ptr [ebp + 0x10]
008c7671 push esi
008c7672 mov esi, ecx
008c7674 push edi
008c7675 mov edi, dword ptr [ebp + 8]
008c7678 mov byte ptr [esi + 0x410], 1
008c767f mov dword ptr [esi + 0x414], edi
008c7685 movss dword ptr [esi + 0x418], xmm0
008c768d movss dword ptr [esi + 0x41c], xmm1
008c7695 je 0x8c76a9
008c7697 divss xmm0, xmm1
008c769b call 0x9eb8a0
008c76a0 inc eax
008c76a1 add eax, edi
008c76a3 mov dword ptr [esi + 0x3a8], eax
008c76a9 pop edi
008c76aa pop esi
008c76ab pop ebp
008c76ac ret 0x10
008c76af int3 
008c76b0 push ebx
008c76b1 mov ebx, esp
008c76b3 sub esp, 8
008c76b6 and esp, 0xfffffff8
008c76b9 add esp, 4
008c76bc push ebp
008c76bd mov ebp, dword ptr [ebx + 4]
008c76c0 mov dword ptr [esp + 4], ebp
008c76c4 mov ebp, esp
008c76c6 push ecx
008c76c7 push esi
008c76c8 mov esi, ecx
008c76ca movss dword ptr [ebp - 4], xmm2
008c76cf movss xmm0, dword ptr [esi + 0x36c]
008c76d7 mov byte ptr [esi + 0x410], 1
008c76de mov dword ptr [esi + 0x414], 0
008c76e8 call 0x65a6a0
008c76ed xorps xmm1, xmm1
008c76f0 movss dword ptr [esi + 0x418], xmm0
008c76f8 comiss xmm1, xmm0
008c76fb movss xmm0, dword ptr [ebp - 4]
008c7700 jbe 0x8c7709
008c7702 xorps xmm0, xmmword ptr [0xb6c9b0]
008c7709 movss dword ptr [esi + 0x41c], xmm0
008c7711 pop esi
008c7712 mov esp, ebp
008c7714 pop ebp
008c7715 mov esp, ebx
008c7717 pop ebx
008c7718 ret 
008c7719 int3 
008c771a int3 
008c771b int3 
008c771c int3 
008c771d int3 
008c771e int3 
008c771f int3 
008c7720 mov edx, dword ptr [ecx + 0x3fc]
008c7726 push ebx
008c7727 mov ebx, dword ptr [ecx + 0x3dc]
008c772d push esi
008c772e mov esi, dword ptr [ecx + 0x3d0]
008c7734 push edi
008c7735 mov edi, dword ptr [ecx + 0x3e8]
008c773b mov dword ptr [ecx + 0x400], edx
008c7741 mov dword ptr [ecx + 0x3d4], esi
008c7747 mov dword ptr [ecx + 0x3ec], edi
008c774d mov dword ptr [ecx + 0x3e0], ebx
008c7753 mov eax, dword ptr [ecx + 0x30]
008c7756 cmp eax, 1
008c7759 je 0x8c7771
008c775b cmp eax, 2
008c775e je 0x8c7771
008c7760 cmp eax, 3
008c7763 je 0x8c7771
008c7765 movss xmm0, dword ptr [0xb6ab20]
008c776d xor eax, eax
008c776f jmp 0x8c7788
008c7771 movss xmm0, dword ptr [0xb6aa8c]
008c7779 mov eax, 1
008c777e mov dword ptr [ecx + 0x17c], 0
008c7788 mov dword ptr [ecx + 0x400], edx
008c778e mov dword ptr [ecx + 0x3d4], esi
008c7794 mov dword ptr [ecx + 0x3ec], edi
008c779a mov dword ptr [ecx + 0x3e0], ebx
008c77a0 mov dword ptr [ecx + 0x3cc], 0x32
008c77aa pop edi
008c77ab mov dword ptr [ecx + 0x3f4], eax
008c77b1 movss dword ptr [ecx + 0x3c8], xmm0
008c77b9 cmp dword ptr [ecx + 0x424], 1
008c77c0 pop esi
008c77c1 pop ebx
008c77c2 jne 0x8c77ce
008c77c4 mov dword ptr [ecx + 0x3c8], 0x43c80000
008c77ce ret 
008c77cf int3 
008c77d0 push ebp
008c77d1 mov ebp, esp
008c77d3 and esp, 0xfffffff8
008c77d6 push ecx
008c77d7 push ebx
008c77d8 push esi
008c77d9 push edi
008c77da push dword ptr [ebp + 0x14]
008c77dd mov edi, ecx
008c77df push dword ptr [ebp + 0x10]
008c77e2 push dword ptr [ebp + 0xc]
008c77e5 push dword ptr [ebp + 8]
008c77e8 call 0x6819e0
008c77ed mov eax, dword ptr [edi + 0x288]
008c77f3 test eax, eax
008c77f5 je 0x8c7888
008c77fb push 1
008c77fd add eax, 0x74
008c7800 lea ecx, [edi + 0x3c]
008c7803 push eax
008c7804 call 0x407160
008c7809 cmp dword ptr [edi + 0x68], 0x10
008c780d lea ecx, [edi + 0x54]
008c7810 mov dword ptr [esp + 0xc], ecx
008c7814 jb 0x8c781c
008c7816 mov ecx, dword ptr [ecx]
008c7818 mov dword ptr [esp + 0xc], ecx
008c781c mov esi, dword ptr [edi + 0x70]
008c781f test esi, esi
008c7821 je 0x8c786a
008c7823 cmp dword ptr [esi + 0x14], 0x10
008c7827 mov eax, esi
008c7829 jb 0x8c7830
008c782b mov eax, dword ptr [esi]
008c782d nop dword ptr [eax]
008c7830 mov dl, byte ptr [eax]
008c7832 cmp dl, byte ptr [ecx]
008c7834 jne 0x8c7850
008c7836 test dl, dl
008c7838 je 0x8c784c
008c783a mov dl, byte ptr [eax + 1]
008c783d cmp dl, byte ptr [ecx + 1]
008c7840 jne 0x8c7850
008c7842 add eax, 2
008c7845 add ecx, 2
008c7848 test dl, dl
008c784a jne 0x8c7830
008c784c xor eax, eax
008c784e jmp 0x8c7855
008c7850 sbb eax, eax
008c7852 or eax, 1
008c7855 test eax, eax
008c7857 jne 0x8c7866
008c7859 cmp byte ptr [esi + 0x34], al
008c785c je 0x8c7888
008c785e cmp byte ptr [edi + 0x80], al
008c7864 jne 0x8c7888
008c7866 mov ecx, dword ptr [esp + 0xc]
008c786a push 1
008c786c push ecx
008c786d lea ecx, [edi + 0x3c]
008c7870 call 0x405740
008c7875 test al, al
008c7877 je 0x8c7888
008c7879 lea ecx, [edi + 0x6c]
008c787c call 0x405330
008c7881 mov byte ptr [edi + 0x80], 1
008c7888 mov word ptr [edi + 0x467], 0
008c7891 mov dword ptr [edi + 0x46c], 0x3f800000
008c789b mov dword ptr [edi + 0x490], 0
008c78a5 movss xmm0, dword ptr [0xc02fec]
008c78ad movss dword ptr [edi + 0x360], xmm0
008c78b5 movss xmm0, dword ptr [0xc02ff0]
008c78bd movss dword ptr [edi + 0x364], xmm0
008c78c5 mov dword ptr [edi + 0x430], 0x3f800000
008c78cf mov dword ptr [edi + 0x36c], 0
008c78d9 mov dword ptr [edi + 0x368], 0
008c78e3 mov dword ptr [edi + 0x370], 0
008c78ed mov dword ptr [edi + 0x2b0], 0
008c78f7 mov dword ptr [edi + 0x378], 0
008c7901 mov dword ptr [edi + 0x37c], 0
008c790b mov dword ptr [edi + 0x380], 0
008c7915 mov dword ptr [edi + 0x384], 0
008c791f mov dword ptr [edi + 0x388], 0
008c7929 mov dword ptr [edi + 0x38c], 0
008c7933 mov dword ptr [edi + 0x390], 0
008c793d mov dword ptr [edi + 0x394], 0
