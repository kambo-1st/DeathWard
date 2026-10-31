00695680 push ebp
00695681 mov ebp, esp
00695683 push -1
00695685 push 0x9f4685
0069568a mov eax, dword ptr fs:[0]
00695690 push eax
00695691 sub esp, 0x3c
00695694 push ebx
00695695 push esi
00695696 push edi
00695697 mov eax, dword ptr [0xbaa3b4]
0069569c xor eax, ebp
0069569e push eax
0069569f lea eax, [ebp - 0xc]
006956a2 mov dword ptr fs:[0], eax
006956a8 mov esi, ecx
006956aa cmp dword ptr [esi + 0x28], 0x35
006956ae jne 0x6958bb
006956b4 lea eax, [esi + 0x31c]
006956ba mov dword ptr [ebp - 0x18], eax
006956bd mov eax, dword ptr [esi + 0x31c]
006956c3 test eax, eax
006956c5 jne 0x695a14
006956cb xor ebx, ebx
006956cd mov dword ptr [ebp - 0x14], eax
006956d0 xor edi, edi
006956d2 mov dword ptr [ebp - 0x28], ebx
006956d5 mov dword ptr [ebp - 0x24], edi
006956d8 mov dword ptr [ebp - 0x20], eax
006956db push edi
006956dc push edi
006956dd push -1
006956df push -1
006956e1 push 0x35
006956e3 lea eax, [ebp - 0x38]
006956e6 mov dword ptr [ebp - 4], edi
006956e9 push eax
006956ea mov eax, dword ptr [0xbfd65c]
006956ef mov ecx, dword ptr [eax + 0x18190]
006956f5 add ecx, 0x1218
006956fb call 0x415ed0
00695700 mov byte ptr [ebp - 4], 1
00695704 mov ecx, dword ptr [0xbfd65c]
0069570a mov dword ptr [ebp - 0x10], edi
0069570d mov eax, dword ptr [ecx + 0x1ba54]
00695713 sub eax, dword ptr [ecx + 0x1ba50]
00695719 sar eax, 2
0069571c test eax, eax
0069571e je 0x6957e3
00695724 lea ebx, [ecx + 0x1ba50]
0069572a mov ecx, dword ptr [ebx + 4]
0069572d mov eax, ecx
0069572f sub eax, dword ptr [ebx]
00695731 test eax, 0xfffffffc
00695736 jne 0x69574a
00695738 push 0xb3f4d0
0069573d push 3
0069573f call 0x95e330
00695744 mov ecx, dword ptr [ebx + 4]
00695747 add esp, 8
0069574a mov edx, dword ptr [ebx]
0069574c sub ecx, edx
0069574e mov eax, dword ptr [ebp - 0x10]
00695751 sar ecx, 2
00695754 cmp eax, ecx
00695756 jae 0x69575b
00695758 lea edx, [edx + eax*4]
0069575b mov eax, dword ptr [esi + 0xe6c]
00695761 mov edx, dword ptr [edx]
00695763 mov dword ptr [ebp - 0x1c], edx
00695766 cmp eax, -1
00695769 je 0x695775
0069576b cmp dword ptr [edx + 0x154c], eax
00695771 jne 0x6957bc
00695773 jmp 0x695797
00695775 mov ebx, dword ptr [ebp - 0x2c]
00695778 xor eax, eax
0069577a test ebx, ebx
0069577c je 0x695797
0069577e nop 
00695780 mov ecx, dword ptr [ebp - 0x34]
00695783 mov ecx, dword ptr [ecx + eax*4]
00695786 cmp ecx, esi
00695788 je 0x695792
0069578a cmp dword ptr [ecx + 0x31c], edx
00695790 je 0x6957bc
00695792 inc eax
00695793 cmp eax, ebx
00695795 jb 0x695780
00695797 cmp edi, dword ptr [ebp - 0x14]
0069579a je 0x6957a6
0069579c mov dword ptr [edi], edx
0069579e add edi, 4
006957a1 mov dword ptr [ebp - 0x24], edi
006957a4 jmp 0x6957bc
006957a6 lea eax, [ebp - 0x1c]
006957a9 push eax
006957aa push edi
006957ab lea ecx, [ebp - 0x28]
006957ae call 0x426fb0
006957b3 mov eax, dword ptr [ebp - 0x20]
006957b6 mov edi, dword ptr [ebp - 0x24]
006957b9 mov dword ptr [ebp - 0x14], eax
006957bc mov ecx, dword ptr [0xbfd65c]
006957c2 mov edx, dword ptr [ebp - 0x10]
006957c5 inc edx
006957c6 mov dword ptr [ebp - 0x10], edx
006957c9 mov eax, dword ptr [ecx + 0x1ba54]
006957cf sub eax, dword ptr [ecx + 0x1ba50]
006957d5 sar eax, 2
006957d8 cmp edx, eax
006957da jb 0x695724
006957e0 mov ebx, dword ptr [ebp - 0x28]
006957e3 cmp ebx, edi
006957e5 jne 0x6957ff
006957e7 mov eax, dword ptr [esi]
006957e9 mov ecx, esi
006957eb call dword ptr [eax + 0x24]
006957ee mov ecx, dword ptr [0xbfd65c]
006957f4 push 0
006957f6 call 0x412750
006957fb mov esi, eax
006957fd jmp 0x695831
006957ff mov eax, dword ptr [esi + 0x344]
00695805 lea ecx, [ebp - 0x48]
00695808 movq xmm0, qword ptr [0xa08b24]
00695810 sub edi, ebx
00695812 sar edi, 2
00695815 mov dword ptr [ebp - 0x48], eax
00695818 mov eax, dword ptr [0xa08b2c]
0069581d push edi
0069581e movq qword ptr [ebp - 0x44], xmm0
00695823 mov dword ptr [ebp - 0x3c], eax
00695826 call 0x7a7d50
0069582b mov esi, dword ptr [ebx + eax*4]
0069582e lea eax, [ebx + eax*4]
00695831 mov edi, dword ptr [ebp - 0x18]
00695834 mov ecx, dword ptr [edi]
00695836 test ecx, ecx
00695838 je 0x69584c
0069583a lea eax, [ebp - 0x1c]
0069583d mov dword ptr [ebp - 0x1c], edi
00695840 push eax
00695841 add ecx, 0x324
00695847 call 0x4bc3c0
0069584c mov dword ptr [edi], esi
0069584e test esi, esi
00695850 je 0x69585a
00695852 push edi
00695853 mov ecx, esi
00695855 call 0x4bae70
0069585a cmp byte ptr [ebp - 0x38], 0
0069585e mov esi, dword ptr [edi]
00695860 jne 0x69586d
00695862 push dword ptr [ebp - 0x34]
00695865 call 0x9eace5
0069586a add esp, 4
0069586d test ebx, ebx
0069586f je 0x695a12
00695875 mov ecx, dword ptr [ebp - 0x14]
00695878 mov eax, ebx
0069587a sub ecx, ebx
0069587c and ecx, 0xfffffffc
0069587f cmp ecx, 0x1000
00695885 jb 0x69589d
00695887 mov ebx, dword ptr [ebx - 4]
0069588a add ecx, 0x23
0069588d sub eax, ebx
0069588f add eax, -4
00695892 cmp eax, 0x1f
00695895 jbe 0x69589d
00695897 call dword ptr [0xa065ac]
0069589d push ecx
0069589e push ebx
0069589f call 0x9eb08e
006958a4 add esp, 8
006958a7 mov eax, esi
006958a9 mov ecx, dword ptr [ebp - 0xc]
006958ac mov dword ptr fs:[0], ecx
006958b3 pop ecx
006958b4 pop edi
006958b5 pop esi
006958b6 pop ebx
006958b7 mov esp, ebp
006958b9 pop ebp
006958ba ret 
006958bb mov eax, dword ptr [esi + 0x160]
006958c1 and eax, 0x100
006958c6 or eax, 0
006958c9 je 0x695946
006958cf mov eax, dword ptr [0xbfd65c]
006958d4 mov eax, dword ptr [eax + 0x18190]
006958da cmp byte ptr [eax + 0x7185], 0
006958e1 jne 0x695946
006958e3 push dword ptr [esi + 0x20]
006958e6 push 0xf
006958e8 call 0x684790
006958ed test al, al
006958ef jne 0x6958fa
006958f1 cmp dword ptr [esi + 0x31c], 0
006958f8 jne 0x695946
006958fa movss xmm1, dword ptr [0xb6ad20]
00695902 lea ecx, [esi + 0x294]
00695908 push 0
0069590a mov edx, esi
0069590c call 0x6d90b0
00695911 mov ecx, dword ptr [esi + 0x31c]
00695917 lea edi, [esi + 0x31c]
0069591d add esp, 4
00695920 mov ebx, eax
00695922 test ecx, ecx
00695924 je 0x695938
00695926 lea eax, [ebp - 0x1c]
00695929 mov dword ptr [ebp - 0x1c], edi
0069592c push eax
0069592d add ecx, 0x324
00695933 call 0x4bc3c0
00695938 mov dword ptr [edi], ebx
0069593a test ebx, ebx
0069593c je 0x695946
0069593e push edi
0069593f mov ecx, ebx
00695941 call 0x4bae70
00695946 mov eax, dword ptr [esi + 0x31c]
0069594c lea edi, [esi + 0x31c]
00695952 test eax, eax
00695954 jne 0x695a14
0069595a cmp dword ptr [esi + 0x28], 0xd5
00695961 je 0x69596f
00695963 cmp dword ptr [esi + 0xad4], eax
00695969 jl 0x69596f
0069596b mov cl, 1
0069596d jmp 0x695971
0069596f xor cl, cl
00695971 mov eax, dword ptr [esi + 0x160]
00695977 and eax, 0x20000000
0069597c mov byte ptr [ebp - 0x18], 1
00695980 or eax, 0
00695983 jne 0x695989
00695985 mov byte ptr [ebp - 0x18], 0
00695989 movss xmm1, dword ptr [0xb6ad20]
00695991 mov edx, esi
00695993 push 0
00695995 push ecx
00695996 push dword ptr [ebp - 0x18]
00695999 lea ecx, [esi + 0x294]
0069599f call 0x6d8820
006959a4 mov esi, eax
006959a6 add esp, 0xc
006959a9 test esi, esi
006959ab je 0x695a03
006959ad mov ecx, dword ptr [esi + 0x28]
006959b0 sub ecx, 0xa
006959b3 cmp ecx, 0x3dd
006959b9 ja 0x695a12
006959bb push 0x100000
006959c0 push 0
006959c2 mov ecx, esi
006959c4 call 0x4122f0
006959c9 test al, al
006959cb je 0x695a12
006959cd mov ecx, dword ptr [edi]
006959cf test ecx, ecx
006959d1 je 0x6959e5
006959d3 lea eax, [ebp - 0x1c]
006959d6 mov dword ptr [ebp - 0x1c], edi
006959d9 push eax
006959da add ecx, 0x324
006959e0 call 0x4bc3c0
006959e5 push edi
006959e6 mov ecx, esi
006959e8 mov dword ptr [edi], esi
006959ea call 0x4bae70
006959ef mov eax, esi
006959f1 mov ecx, dword ptr [ebp - 0xc]
006959f4 mov dword ptr fs:[0], ecx
006959fb pop ecx
006959fc pop edi
006959fd pop esi
006959fe pop ebx
006959ff mov esp, ebp
00695a01 pop ebp
00695a02 ret 
00695a03 mov ecx, dword ptr [0xbfd65c]
00695a09 push 0
00695a0b call 0x412750
00695a10 mov esi, eax
00695a12 mov eax, esi
00695a14 mov ecx, dword ptr [ebp - 0xc]
00695a17 mov dword ptr fs:[0], ecx
00695a1e pop ecx
00695a1f pop edi
00695a20 pop esi
00695a21 pop ebx
00695a22 mov esp, ebp
00695a24 pop ebp
00695a25 ret 
