007af4b0 push ebp
007af4b1 mov ebp, esp
007af4b3 and esp, 0xfffffff8
007af4b6 sub esp, 0x4c
007af4b9 mov eax, dword ptr [0xbaa3b4]
007af4be xor eax, esp
007af4c0 mov dword ptr [esp + 0x48], eax
007af4c4 mov eax, dword ptr [ebp + 8]
007af4c7 push ebx
007af4c8 mov ebx, dword ptr [ebp + 0x20]
007af4cb push esi
007af4cc movss xmm1, dword ptr [eax]
007af4d0 movss xmm0, dword ptr [eax + 4]
007af4d5 movaps xmm2, xmm1
007af4d8 mov esi, dword ptr [ebp + 0xc]
007af4db movaps xmm3, xmm0
007af4de movss dword ptr [esp + 0xc], xmm0
007af4e4 movss dword ptr [esp + 0x10], xmm1
007af4ea push edi
007af4eb subss xmm2, dword ptr [esi]
007af4ef subss xmm3, dword ptr [esi + 4]
007af4f4 mov edi, ecx
007af4f6 mov dword ptr [esp + 0x20], ebx
007af4fa movaps xmm1, xmm2
007af4fd movss dword ptr [esp + 0x18], xmm2
007af503 movaps xmm0, xmm3
007af506 mulss xmm1, xmm2
007af50a mulss xmm0, xmm3
007af50e movss dword ptr [esp + 0x1c], xmm3
007af514 addss xmm0, xmm1
007af518 call 0x4228c0
007af51d xorps xmm1, xmm1
007af520 movss dword ptr [esp + 0x30], xmm0
007af526 comiss xmm0, xmm1
007af529 movss dword ptr [esp + 0x2c], xmm1
007af52f jbe 0x7afa13
007af535 movss xmm5, dword ptr [esp + 0x18]
007af53b movss xmm6, dword ptr [esp + 0x1c]
007af541 movss xmm3, dword ptr [esp + 0x14]
007af547 movss xmm4, dword ptr [0xb6aa3c]
007af54f divss xmm5, xmm0
007af553 divss xmm6, xmm0
007af557 movaps xmm0, xmm3
007af55a movss xmm7, dword ptr [0xb6a480]
007af562 subss xmm0, xmm4
007af566 mulss xmm5, dword ptr [0xb6a974]
007af56e mulss xmm6, dword ptr [0xb6a974]
007af576 movss xmm2, dword ptr [esp + 0x10]
007af57c divss xmm0, xmm4
007af580 movss dword ptr [esp + 0x18], xmm5
007af586 addss xmm0, xmm7
007af58a movss dword ptr [esp + 0x1c], xmm6
007af590 cvttss2si ecx, xmm0
007af594 test ecx, ecx
007af596 js 0x7af5ca
007af598 mov edx, dword ptr [edi + 0xc]
007af59b cmp ecx, edx
007af59d jge 0x7af5ca
007af59f movaps xmm0, xmm2
007af5a2 subss xmm0, dword ptr [0xb6ab20]
007af5aa divss xmm0, xmm4
007af5ae addss xmm0, xmm7
007af5b2 cvttss2si eax, xmm0
007af5b6 test eax, eax
007af5b8 js 0x7af5ca
007af5ba cmp eax, dword ptr [edi + 0x10]
007af5bd jge 0x7af5ca
007af5bf imul edx, eax
007af5c2 add edx, ecx
007af5c4 mov dword ptr [esp + 0x24], edx
007af5c8 jmp 0x7af5d2
007af5ca mov dword ptr [esp + 0x24], 0xffffffff
007af5d2 movss xmm0, dword ptr [esp + 0x30]
007af5d8 comiss xmm0, xmm1
007af5db mov dword ptr [esp + 0xc], 0
007af5e3 jbe 0x7afa13
007af5e9 mov edx, dword ptr [ebp + 0x10]
007af5ec subss xmm3, xmm5
007af5f0 subss xmm2, xmm6
007af5f4 movss dword ptr [esp + 0x14], xmm3
007af5fa movss dword ptr [esp + 0x10], xmm2
007af600 test edx, edx
007af602 je 0x7af83b
007af608 cmp edx, 3
007af60b je 0x7af83b
007af611 movaps xmm0, xmm3
007af614 subss xmm0, xmm4
007af618 divss xmm0, xmm4
007af61c addss xmm0, xmm7
007af620 cvttss2si ebx, xmm0
007af624 movaps xmm0, xmm2
007af627 subss xmm0, dword ptr [0xb6ab20]
007af62f divss xmm0, xmm4
007af633 addss xmm0, xmm7
007af637 cvttss2si esi, xmm0
007af63b test ebx, ebx
007af63d js 0x7af656
007af63f mov eax, dword ptr [edi + 0xc]
007af642 cmp ebx, eax
007af644 jge 0x7af656
007af646 test esi, esi
007af648 js 0x7af656
007af64a cmp esi, dword ptr [edi + 0x10]
007af64d jge 0x7af656
007af64f imul eax, esi
007af652 add eax, ebx
007af654 jmp 0x7af659
007af656 or eax, 0xffffffff
007af659 push eax
007af65a mov ecx, edi
007af65c call 0x7aeec0
007af661 mov ecx, eax
007af663 mov eax, dword ptr [ebp + 0x10]
007af666 mov dword ptr [esp + 0x28], ecx
007af66a cmp eax, 1
007af66d jne 0x7af6c9
007af66f test ecx, ecx
007af671 jne 0x7af9da
007af677 test ebx, ebx
007af679 js 0x7af692
007af67b mov eax, dword ptr [edi + 0xc]
007af67e cmp ebx, eax
007af680 jge 0x7af692
007af682 test esi, esi
007af684 js 0x7af692
007af686 cmp esi, dword ptr [edi + 0x10]
007af689 jge 0x7af692
007af68b imul eax, esi
007af68e add eax, ebx
007af690 jmp 0x7af695
007af692 or eax, 0xffffffff
007af695 cmp eax, dword ptr [esp + 0x24]
007af699 je 0x7af7b4
007af69f cmp eax, 0x1bf
007af6a4 ja 0x7af6af
007af6a6 mov ecx, dword ptr [edi + eax*4 + 0x76c]
007af6ad jmp 0x7af6b1
007af6af xor ecx, ecx
007af6b1 mov esi, dword ptr [esp + 0xc]
007af6b5 cmp ecx, dword ptr [ebp + 0x14]
007af6b8 lea eax, [esi + 1]
007af6bb cmovle eax, esi
007af6be mov esi, eax
007af6c0 mov dword ptr [esp + 0xc], esi
007af6c4 jmp 0x7af7b8
007af6c9 cmp eax, 2
007af6cc jne 0x7af7b4
007af6d2 test ebx, ebx
007af6d4 js 0x7af6f3
007af6d6 mov eax, dword ptr [edi + 0xc]
007af6d9 cmp ebx, eax
007af6db jge 0x7af6f3
007af6dd test esi, esi
007af6df js 0x7af6f3
007af6e1 cmp esi, dword ptr [edi + 0x10]
007af6e4 jge 0x7af6f3
007af6e6 imul eax, esi
007af6e9 add eax, ebx
007af6eb js 0x7af6f3
007af6ed mov esi, dword ptr [edi + eax*4 + 0x24]
007af6f1 jmp 0x7af6f5
007af6f3 xor esi, esi
007af6f5 test ecx, ecx
007af6f7 je 0x7af74a
007af6f9 test esi, esi
007af6fb je 0x7af789
007af701 cmp dword ptr [esi + 4], 3
007af705 jne 0x7af74e
007af707 mov eax, dword ptr [esp + 0x20]
007af70b test eax, eax
007af70d je 0x7af825
007af713 movss xmm1, dword ptr [esp + 0x14]
007af719 movss xmm0, dword ptr [esp + 0x10]
007af71f addss xmm1, dword ptr [esp + 0x18]
007af725 addss xmm0, dword ptr [esp + 0x1c]
007af72b movss dword ptr [eax], xmm1
007af72f movss dword ptr [eax + 4], xmm0
007af734 xor al, al
007af736 pop edi
007af737 pop esi
007af738 pop ebx
007af739 mov ecx, dword ptr [esp + 0x48]
007af73d xor ecx, esp
007af73f call 0x9eacd7
007af744 mov esp, ebp
007af746 pop ebp
007af747 ret 0x1c
007af74a test esi, esi
007af74c je 0x7af789
007af74e cmp dword ptr [esi + 4], 0xb
007af752 jne 0x7af776
007af754 mov ecx, dword ptr [0xbfd65c]
007af75a push 1
007af75c push 0
007af75e push 0x88
007af763 lea ecx, [ecx + 0x1ba40]
007af769 call 0x91d550
007af76e test eax, eax
007af770 jne 0x7af7b4
007af772 mov ecx, dword ptr [esp + 0x28]
007af776 mov eax, dword ptr [esi + 4]
007af779 cmp eax, 0x10
007af77c je 0x7af796
007af77e cmp eax, 0xf
007af781 jne 0x7af789
007af783 cmp byte ptr [ebp + 0x18], 0
007af787 jne 0x7af796
007af789 cmp ecx, 4
007af78c je 0x7af707
007af792 test esi, esi
007af794 je 0x7af7b4
007af796 mov ecx, esi
007af798 call 0x6dc600
007af79d test al, al
007af79f jne 0x7af7aa
007af7a1 call 0x6dc650
007af7a6 test al, al
007af7a8 je 0x7af7b4
007af7aa cmp byte ptr [ebp + 0x1c], 0
007af7ae jne 0x7af707
007af7b4 mov esi, dword ptr [esp + 0xc]
007af7b8 movss xmm2, dword ptr [esp + 0x10]
007af7be movss xmm3, dword ptr [esp + 0x14]
007af7c4 movss xmm4, dword ptr [0xb6aa3c]
007af7cc movss xmm5, dword ptr [esp + 0x18]
007af7d2 movss xmm6, dword ptr [esp + 0x1c]
007af7d8 movss xmm7, dword ptr [0xb6a480]
007af7e0 movss xmm1, dword ptr [esp + 0x2c]
007af7e6 addss xmm1, dword ptr [0xb6a974]
007af7ee movss xmm0, dword ptr [esp + 0x30]
007af7f4 comiss xmm0, xmm1
007af7f7 movss dword ptr [esp + 0x2c], xmm1
007af7fd ja 0x7af5e9
007af803 cmp esi, 8
007af806 jle 0x7afa0c
007af80c mov eax, dword ptr [esp + 0x20]
007af810 test eax, eax
007af812 je 0x7af825
007af814 addss xmm2, xmm6
007af818 addss xmm3, xmm5
007af81c movss dword ptr [eax + 4], xmm2
007af821 movss dword ptr [eax], xmm3
007af825 xor al, al
007af827 pop edi
007af828 pop esi
007af829 pop ebx
007af82a mov ecx, dword ptr [esp + 0x48]
007af82e xor ecx, esp
007af830 call 0x9eacd7
007af835 mov esp, ebp
007af837 pop ebp
007af838 ret 0x1c
007af83b movaps xmm0, xmmword ptr [0xb6c8c0]
007af842 xor ebx, ebx
007af844 mov eax, dword ptr [edi + 4]
007af847 movups xmmword ptr [esp + 0x34], xmm0
007af84c movaps xmm0, xmmword ptr [0xb6ca10]
007af853 mov eax, dword ptr [eax + 0x10]
007af856 movups xmmword ptr [esp + 0x44], xmm0
007af85b mov dword ptr [esp + 0x28], eax
007af85f nop 
007af860 movaps xmm0, xmm3
007af863 movaps xmm1, xmm2
007af866 addss xmm0, dword ptr [esp + ebx*8 + 0x34]
007af86c addss xmm1, dword ptr [esp + ebx*8 + 0x38]
007af872 subss xmm0, xmm4
007af876 subss xmm1, dword ptr [0xb6ab20]
007af87e divss xmm0, xmm4
007af882 divss xmm1, xmm4
007af886 addss xmm0, xmm7
007af88a addss xmm1, xmm7
007af88e cvttss2si esi, xmm0
007af892 cvttss2si ecx, xmm1
007af896 test esi, esi
007af898 js 0x7af8b3
007af89a mov edx, dword ptr [edi + 0xc]
007af89d cmp esi, edx
007af89f jge 0x7af8b3
007af8a1 test ecx, ecx
007af8a3 js 0x7af8b3
007af8a5 cmp ecx, dword ptr [edi + 0x10]
007af8a8 jge 0x7af8b3
007af8aa mov eax, ecx
007af8ac imul eax, edx
007af8af add eax, esi
007af8b1 jmp 0x7af8b6
007af8b3 or eax, 0xffffffff
007af8b6 mov edx, dword ptr [esp + 0x28]
007af8ba test edx, edx
007af8bc je 0x7af8cd
007af8be cmp dword ptr [edx + 8], 0x10
007af8c2 jne 0x7af8cd
007af8c4 cmp dword ptr [edx], 0x23
007af8c7 jne 0x7af8cd
007af8c9 xor eax, eax
007af8cb jmp 0x7af910
007af8cd test eax, eax
007af8cf jns 0x7af8d8
007af8d1 mov eax, 4
007af8d6 jmp 0x7af910
007af8d8 mov edx, dword ptr [edi + eax*4 + 0x24]
007af8dc test edx, edx
007af8de jne 0x7af90d
007af8e0 mov edx, dword ptr [edi + eax*4 + 0x76c]
007af8e7 lea eax, [edx - 0xbb8]
007af8ed cmp eax, 0x3e7
007af8f2 ja 0x7af8fb
007af8f4 mov eax, 1
007af8f9 jmp 0x7af910
007af8fb xor eax, eax
007af8fd cmp edx, 0x3e8
007af903 mov edx, 3
007af908 cmovge eax, edx
007af90b jmp 0x7af910
007af90d mov eax, dword ptr [edx + 0x3c]
007af910 mov edx, dword ptr [ebp + 0x10]
007af913 cmp edx, 3
007af916 jne 0x7af91d
007af918 cmp eax, 1
007af91b je 0x7af97c
007af91d test eax, eax
007af91f je 0x7af98f
007af921 cmp byte ptr [ebp + 0x1c], 0
007af925 je 0x7af80c
007af92b test esi, esi
007af92d js 0x7af80c
007af933 mov eax, dword ptr [edi + 0xc]
007af936 cmp esi, eax
007af938 jge 0x7af80c
007af93e test ecx, ecx
007af940 js 0x7af80c
007af946 cmp ecx, dword ptr [edi + 0x10]
007af949 jge 0x7af80c
007af94f imul ecx, eax
007af952 add ecx, esi
007af954 js 0x7af80c
007af95a mov ecx, dword ptr [edi + ecx*4 + 0x24]
007af95e test ecx, ecx
007af960 je 0x7af80c
007af966 call 0x6dc600
007af96b test al, al
007af96d jne 0x7af97c
007af96f call 0x6dc650
007af974 test al, al
007af976 je 0x7af80c
007af97c mov esi, dword ptr [esp + 0xc]
007af980 inc ebx
007af981 cmp ebx, 4
007af984 jb 0x7af860
007af98a jmp 0x7af7e0
007af98f test esi, esi
007af991 js 0x7af9aa
007af993 mov eax, dword ptr [edi + 0xc]
007af996 cmp esi, eax
007af998 jge 0x7af9aa
007af99a test ecx, ecx
007af99c js 0x7af9aa
007af99e cmp ecx, dword ptr [edi + 0x10]
007af9a1 jge 0x7af9aa
007af9a3 imul ecx, eax
007af9a6 add ecx, esi
007af9a8 jmp 0x7af9ad
007af9aa or ecx, 0xffffffff
007af9ad cmp ecx, dword ptr [esp + 0x24]
007af9b1 je 0x7af97c
007af9b3 cmp ecx, 0x1bf
007af9b9 ja 0x7af9c4
007af9bb mov eax, dword ptr [edi + ecx*4 + 0x76c]
007af9c2 jmp 0x7af9c6
007af9c4 xor eax, eax
007af9c6 mov esi, dword ptr [esp + 0xc]
007af9ca test edx, edx
007af9cc jne 0x7af980
007af9ce cmp eax, dword ptr [ebp + 0x14]
007af9d1 jle 0x7af980
007af9d3 inc esi
007af9d4 mov dword ptr [esp + 0xc], esi
007af9d8 jmp 0x7af980
007af9da mov eax, dword ptr [esp + 0x20]
007af9de test eax, eax
007af9e0 je 0x7af825
007af9e6 movss xmm2, dword ptr [esp + 0x18]
007af9ec movss xmm0, dword ptr [esp + 0x10]
007af9f2 addss xmm2, dword ptr [esp + 0x14]
007af9f8 addss xmm0, dword ptr [esp + 0x1c]
007af9fe movss dword ptr [eax], xmm2
007afa02 movss dword ptr [eax + 4], xmm0
007afa07 jmp 0x7af825
007afa0c mov ebx, dword ptr [esp + 0x20]
007afa10 mov esi, dword ptr [ebp + 0xc]
007afa13 test ebx, ebx
007afa15 je 0x7afa21
007afa17 mov eax, dword ptr [esi]
007afa19 mov dword ptr [ebx], eax
007afa1b mov eax, dword ptr [esi + 4]
007afa1e mov dword ptr [ebx + 4], eax
007afa21 mov ecx, dword ptr [esp + 0x54]
007afa25 mov al, 1
007afa27 pop edi
007afa28 pop esi
007afa29 pop ebx
007afa2a xor ecx, esp
007afa2c call 0x9eacd7
007afa31 mov esp, ebp
007afa33 pop ebp
007afa34 ret 0x1c
