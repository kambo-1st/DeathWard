00697510 push ebp
00697511 mov ebp, esp
00697513 mov eax, dword ptr [0xbfd680]
00697518 sub esp, 0x14
0069751b cmp byte ptr [eax + 0x6d], 0
0069751f push ebx
00697520 mov ebx, dword ptr [0xbfd65c]
00697526 push esi
00697527 push edi
00697528 mov edi, edx
0069752a mov esi, ecx
0069752c jne 0x697560
0069752e cmp dword ptr [eax + 8], 2
00697532 jne 0x69754a
00697534 test ebx, ebx
00697536 je 0x69754a
00697538 cmp dword ptr [ebx + 0x1c3204], 0
0069753f ja 0x697560
00697541 cmp byte ptr [ebx + 0x1c31a1], 0
00697548 jne 0x697560
0069754a cmp dword ptr [esi], 0x3d
0069754d jne 0x697560
0069754f cmp dword ptr [edi], 5
00697552 jne 0x697560
00697554 mov dword ptr [esi], 0xd
0069755a mov dword ptr [edi], 0
00697560 cmp byte ptr [eax + 0x1a8], 0
00697567 jne 0x697b53
0069756d cmp dword ptr [eax + 8], 2
00697571 jne 0x697591
00697573 test ebx, ebx
00697575 je 0x697591
00697577 cmp dword ptr [ebx + 0x1c3204], 0
0069757e ja 0x697b53
00697584 cmp byte ptr [ebx + 0x1c31a1], 0
0069758b jne 0x697b53
00697591 mov eax, dword ptr [esi]
00697593 cmp eax, 0x12f
00697598 jne 0x6975d4
0069759a mov eax, dword ptr [ebx + 0x243624]
006975a0 test eax, eax
006975a2 je 0x6975bd
006975a4 cmp eax, 2
006975a7 je 0x6975bd
006975a9 xor eax, eax
006975ab mov ecx, 0xfa
006975b0 mov dword ptr [esi], ecx
006975b2 mov dword ptr [edi], eax
006975b4 mov al, 1
006975b6 pop edi
006975b7 pop esi
006975b8 pop ebx
006975b9 mov esp, ebp
006975bb pop ebp
006975bc ret 
006975bd mov eax, 1
006975c2 mov ecx, 0x1d
006975c7 mov dword ptr [esi], ecx
006975c9 mov dword ptr [edi], eax
006975cb mov al, al
006975cd pop edi
006975ce pop esi
006975cf pop ebx
006975d0 mov esp, ebp
006975d2 pop ebp
006975d3 ret 
006975d4 cmp eax, 0x12c
006975d9 jne 0x6975f0
006975db mov dword ptr [esi], 0x1b
006975e1 mov dword ptr [edi], 0
006975e7 mov al, 1
006975e9 pop edi
006975ea pop esi
006975eb pop ebx
006975ec mov esp, ebp
006975ee pop ebp
006975ef ret 
006975f0 cmp eax, 0x131
006975f5 jne 0x69760c
006975f7 mov dword ptr [esi], 0x1d
006975fd mov al, 1
006975ff mov dword ptr [edi], 0
00697605 pop edi
00697606 pop esi
00697607 pop ebx
00697608 mov esp, ebp
0069760a pop ebp
0069760b ret 
0069760c cmp eax, 0xe7
00697611 je 0x6975e1
00697613 cmp eax, 0x12d
00697618 jne 0x69762f
0069761a mov dword ptr [esi], 0x20
00697620 mov al, 1
00697622 mov dword ptr [edi], 0
00697628 pop edi
00697629 pop esi
0069762a pop ebx
0069762b mov esp, ebp
0069762d pop ebp
0069762e ret 
0069762f cmp eax, 0x12e
00697634 jne 0x697660
00697636 mov eax, dword ptr [ebx + 0x243624]
0069763c test eax, eax
0069763e je 0x69764a
00697640 cmp eax, 2
00697643 mov eax, 0x101
00697648 jne 0x69764f
0069764a mov eax, 0xd0
0069764f mov dword ptr [esi], eax
00697651 mov al, 1
00697653 mov dword ptr [edi], 0
00697659 pop edi
0069765a pop esi
0069765b pop ebx
0069765c mov esp, ebp
0069765e pop ebp
0069765f ret 
00697660 cmp eax, 0x130
00697665 jne 0x697691
00697667 mov eax, dword ptr [ebx + 0x243624]
0069766d test eax, eax
0069766f je 0x69767b
00697671 cmp eax, 2
00697674 mov eax, 0xf2
00697679 jne 0x697680
0069767b mov eax, 0xf0
00697680 mov dword ptr [esi], eax
00697682 mov al, 1
00697684 mov dword ptr [edi], 0
0069768a pop edi
0069768b pop esi
0069768c pop ebx
0069768d mov esp, ebp
0069768f pop ebp
00697690 ret 
00697691 cmp eax, 0x132
00697696 jne 0x697b53
0069769c mov ecx, ebx
0069769e call 0x6cba40
006976a3 test al, al
006976a5 je 0x6977dd
006976ab mov eax, dword ptr [ebx]
006976ad dec eax
006976ae cmp eax, 5
006976b1 ja 0x6977c8
006976b7 jmp dword ptr [eax*4 + 0x697bd4]
006976be mov eax, dword ptr [ebx + 0x243624]
006976c4 test eax, eax
006976c6 je 0x6976d2
006976c8 cmp eax, 2
006976cb mov eax, 0x11c
006976d0 jne 0x6976d7
006976d2 mov eax, 0xa
006976d7 mov dword ptr [esi], eax
006976d9 mov al, 1
006976db mov dword ptr [edi], 0
006976e1 pop edi
006976e2 pop esi
006976e3 pop ebx
006976e4 mov esp, ebp
006976e6 pop ebp
006976e7 ret 
006976e8 mov eax, dword ptr [ebx + 0x243624]
006976ee test eax, eax
006976f0 je 0x6976fc
006976f2 cmp eax, 2
006976f5 mov eax, 0x17
006976fa jne 0x697701
006976fc mov eax, 0x15
00697701 mov dword ptr [esi], eax
00697703 mov al, 1
00697705 mov dword ptr [edi], 0
0069770b pop edi
0069770c pop esi
0069770d pop ebx
0069770e mov esp, ebp
00697710 pop ebp
00697711 ret 
00697712 mov eax, dword ptr [ebx + 0x243624]
00697718 test eax, eax
0069771a je 0x697726
0069771c cmp eax, 2
0069771f mov eax, 0xe3
00697724 jne 0x69772b
00697726 mov eax, 0xd1
0069772b mov dword ptr [esi], eax
0069772d mov al, 1
0069772f mov dword ptr [edi], 0
00697735 pop edi
00697736 pop esi
00697737 pop ebx
00697738 mov esp, ebp
0069773a pop ebp
0069773b ret 
0069773c mov eax, dword ptr [ebx + 0x243624]
00697742 test eax, eax
00697744 je 0x697750
00697746 cmp eax, 2
00697749 mov eax, 0x3a
0069774e jne 0x697755
00697750 mov eax, 0xf
00697755 mov dword ptr [esi], eax
00697757 mov al, 1
00697759 mov dword ptr [edi], 0
0069775f pop edi
00697760 pop esi
00697761 pop ebx
00697762 mov esp, ebp
00697764 pop ebp
00697765 ret 
00697766 mov eax, dword ptr [ebx + 0x243624]
0069776c test eax, eax
0069776e je 0x69777a
00697770 cmp eax, 2
00697773 mov eax, 0xfc
00697778 jne 0x69777f
0069777a mov eax, 0x57
0069777f mov dword ptr [esi], eax
00697781 mov al, 1
00697783 mov dword ptr [edi], 0
00697789 pop edi
0069778a pop esi
0069778b pop ebx
0069778c mov esp, ebp
0069778e pop ebp
0069778f ret 
00697790 mov eax, dword ptr [ebx + 0x243624]
00697796 test eax, eax
00697798 je 0x6977b5
0069779a cmp eax, 2
0069779d je 0x6977b5
0069779f mov eax, 1
006977a4 mov dword ptr [esi], 0x32
006977aa mov dword ptr [edi], eax
006977ac mov al, al
006977ae pop edi
006977af pop esi
006977b0 pop ebx
006977b1 mov esp, ebp
006977b3 pop ebp
006977b4 ret 
006977b5 xor eax, eax
006977b7 mov dword ptr [esi], 0x32
006977bd mov dword ptr [edi], eax
006977bf mov al, 1
006977c1 pop edi
006977c2 pop esi
006977c3 pop ebx
006977c4 mov esp, ebp
006977c6 pop ebp
006977c7 ret 
006977c8 mov dword ptr [esi], 0x12b
006977ce mov al, 1
006977d0 mov dword ptr [edi], 0
006977d6 pop edi
006977d7 pop esi
006977d8 pop ebx
006977d9 mov esp, ebp
006977db pop ebp
006977dc ret 
006977dd mov ecx, dword ptr [ebx + 0x18190]
006977e3 call 0x7ad640
006977e8 cmp eax, 0x1a
006977eb ja 0x697b4d
006977f1 jmp dword ptr [eax*4 + 0x697bec]
006977f8 mov eax, dword ptr [0xbfd65c]
006977fd mov eax, dword ptr [eax + 0x243624]
00697803 test eax, eax
00697805 je 0x697811
00697807 cmp eax, 2
0069780a mov eax, 0x5e
0069780f jne 0x697816
00697811 mov eax, 0x55
00697816 mov dword ptr [esi], eax
00697818 mov al, 1
0069781a mov dword ptr [edi], 0
00697820 pop edi
00697821 pop esi
00697822 pop ebx
00697823 mov esp, ebp
00697825 pop ebp
00697826 ret 
00697827 mov eax, dword ptr [0xbfd65c]
0069782c mov eax, dword ptr [eax + 0x243624]
00697832 jmp 0x6976c4
00697837 mov eax, dword ptr [0xbfd65c]
0069783c mov eax, dword ptr [eax + 0x243624]
00697842 test eax, eax
00697844 je 0x697854
00697846 cmp eax, 2
00697849 mov eax, 0x5e
0069784e jne 0x6976d7
00697854 mov eax, 0x55
00697859 mov dword ptr [esi], eax
0069785b mov al, 1
0069785d mov dword ptr [edi], 0
00697863 pop edi
00697864 pop esi
00697865 pop ebx
00697866 mov esp, ebp
00697868 pop ebp
00697869 ret 
0069786a mov eax, dword ptr [0xbfd65c]
0069786f mov eax, dword ptr [eax + 0x243624]
00697875 test eax, eax
00697877 je 0x697887
00697879 cmp eax, 2
0069787c mov eax, 0x17
00697881 jne 0x6976d7
00697887 mov eax, 0x15
0069788c mov dword ptr [esi], eax
0069788e mov al, 1
00697890 mov dword ptr [edi], 0
00697896 pop edi
00697897 pop esi
00697898 pop ebx
00697899 mov esp, ebp
0069789b pop ebp
0069789c ret 
0069789d mov eax, dword ptr [0xbfd65c]
006978a2 mov eax, dword ptr [eax + 0x243624]
006978a8 test eax, eax
006978aa je 0x6978c7
006978ac cmp eax, 2
006978af je 0x6978c7
006978b1 mov eax, 1
006978b6 mov dword ptr [esi], 0x1a
006978bc mov dword ptr [edi], eax
006978be mov al, al
006978c0 pop edi
006978c1 pop esi
006978c2 pop ebx
006978c3 mov esp, ebp
006978c5 pop ebp
006978c6 ret 
006978c7 xor eax, eax
006978c9 mov dword ptr [esi], 0x1a
006978cf mov dword ptr [edi], eax
006978d1 mov al, 1
006978d3 pop edi
006978d4 pop esi
006978d5 pop ebx
006978d6 mov esp, ebp
006978d8 pop ebp
006978d9 ret 
006978da mov eax, dword ptr [0xbfd65c]
006978df mov eax, dword ptr [eax + 0x243624]
006978e5 test eax, eax
006978e7 je 0x697904
006978e9 cmp eax, 2
006978ec je 0x697904
006978ee mov eax, 1
006978f3 mov dword ptr [esi], 0x17
006978f9 mov dword ptr [edi], eax
006978fb mov al, al
006978fd pop edi
006978fe pop esi
006978ff pop ebx
00697900 mov esp, ebp
00697902 pop ebp
00697903 ret 
00697904 xor eax, eax
00697906 mov dword ptr [esi], 0x17
0069790c mov dword ptr [edi], eax
0069790e mov al, 1
00697910 pop edi
00697911 pop esi
00697912 pop ebx
00697913 mov esp, ebp
00697915 pop ebp
00697916 ret 
00697917 mov eax, dword ptr [0xbfd65c]
0069791c mov eax, dword ptr [eax + 0x243624]
00697922 test eax, eax
00697924 je 0x697934
00697926 cmp eax, 2
00697929 mov eax, 0xe3
0069792e jne 0x6976d7
00697934 mov eax, 0xd1
00697939 mov dword ptr [esi], eax
0069793b mov al, 1
0069793d mov dword ptr [edi], 0
00697943 pop edi
00697944 pop esi
00697945 pop ebx
00697946 mov esp, ebp
00697948 pop ebp
00697949 ret 
0069794a mov eax, dword ptr [0xbfd65c]
0069794f mov eax, dword ptr [eax + 0x243624]
00697955 test eax, eax
00697957 je 0x697975
00697959 cmp eax, 2
0069795c je 0x697975
0069795e mov eax, 1
00697963 mov ecx, 0x18
00697968 mov dword ptr [esi], ecx
0069796a mov dword ptr [edi], eax
0069796c mov al, al
0069796e pop edi
0069796f pop esi
00697970 pop ebx
00697971 mov esp, ebp
00697973 pop ebp
00697974 ret 
00697975 xor eax, eax
00697977 mov ecx, 0xe3
0069797c mov dword ptr [esi], ecx
0069797e mov dword ptr [edi], eax
00697980 mov al, 1
00697982 pop edi
00697983 pop esi
00697984 pop ebx
00697985 mov esp, ebp
00697987 pop ebp
00697988 ret 
00697989 mov eax, dword ptr [0xbfd65c]
0069798e mov eax, dword ptr [eax + 0x243624]
00697994 test eax, eax
00697996 je 0x6979a6
00697998 cmp eax, 2
0069799b mov eax, 0x115
006979a0 jne 0x6976d7
006979a6 mov eax, 0x18
006979ab mov dword ptr [esi], eax
006979ad mov al, 1
006979af mov dword ptr [edi], 0
006979b5 pop edi
006979b6 pop esi
006979b7 pop ebx
006979b8 mov esp, ebp
006979ba pop ebp
006979bb ret 
006979bc mov eax, dword ptr [0xbfd65c]
006979c1 mov eax, dword ptr [eax + 0x243624]
006979c7 test eax, eax
006979c9 je 0x6979d9
006979cb cmp eax, 2
006979ce mov eax, 0x3a
006979d3 jne 0x6976d7
006979d9 mov eax, 0xf
006979de mov dword ptr [esi], eax
006979e0 mov al, 1
006979e2 mov dword ptr [edi], 0
006979e8 pop edi
006979e9 pop esi
006979ea pop ebx
006979eb mov esp, ebp
006979ed pop ebp
006979ee ret 
006979ef mov eax, dword ptr [0xbfd65c]
006979f4 mov eax, dword ptr [eax + 0x243624]
006979fa test eax, eax
006979fc je 0x697a0c
006979fe cmp eax, 2
00697a01 mov eax, 0x27
00697a06 jne 0x6976d7
00697a0c mov eax, 0x3a
00697a11 mov dword ptr [esi], eax
00697a13 mov al, 1
00697a15 mov dword ptr [edi], 0
00697a1b pop edi
00697a1c pop esi
00697a1d pop ebx
00697a1e mov esp, ebp
00697a20 pop ebp
00697a21 ret 
00697a22 mov eax, dword ptr [0xbfd65c]
00697a27 mov eax, dword ptr [eax + 0x243624]
00697a2d test eax, eax
00697a2f je 0x697a4c
00697a31 cmp eax, 2
00697a34 je 0x697a4c
00697a36 mov eax, 1
00697a3b mov dword ptr [esi], 0x27
00697a41 mov dword ptr [edi], eax
00697a43 mov al, al
00697a45 pop edi
00697a46 pop esi
00697a47 pop ebx
00697a48 mov esp, ebp
00697a4a pop ebp
00697a4b ret 
00697a4c xor eax, eax
00697a4e mov dword ptr [esi], 0x27
00697a54 mov dword ptr [edi], eax
00697a56 mov al, 1
00697a58 pop edi
00697a59 pop esi
00697a5a pop ebx
00697a5b mov esp, ebp
00697a5d pop ebp
00697a5e ret 
00697a5f mov dword ptr [esi], 0x129
00697a65 mov al, 1
00697a67 mov dword ptr [edi], 0
00697a6d pop edi
00697a6e pop esi
00697a6f pop ebx
00697a70 mov esp, ebp
00697a72 pop ebp
00697a73 ret 
00697a74 mov eax, dword ptr [0xbfd65c]
00697a79 mov eax, dword ptr [eax + 0x243624]
00697a7f test eax, eax
00697a81 je 0x697a91
00697a83 cmp eax, 2
00697a86 mov eax, 0xfc
00697a8b jne 0x6976d7
00697a91 mov eax, 0x57
00697a96 mov dword ptr [esi], eax
00697a98 mov al, 1
00697a9a mov dword ptr [edi], 0
00697aa0 pop edi
00697aa1 pop esi
00697aa2 pop ebx
00697aa3 mov esp, ebp
00697aa5 pop ebp
00697aa6 ret 
00697aa7 mov eax, dword ptr [0xbfd65c]
00697aac mov eax, dword ptr [eax + 0x243624]
00697ab2 test eax, eax
00697ab4 je 0x697ac0
00697ab6 cmp eax, 2
00697ab9 mov eax, 0x37
00697abe jne 0x697ac5
00697ac0 mov eax, 0x1a
00697ac5 mov dword ptr [esi], eax
00697ac7 mov al, 1
00697ac9 mov dword ptr [edi], 2
00697acf pop edi
00697ad0 pop esi
00697ad1 pop ebx
00697ad2 mov esp, ebp
00697ad4 pop ebp
00697ad5 ret 
00697ad6 mov eax, dword ptr [0xbfd65c]
00697adb mov eax, dword ptr [eax + 0x243624]
00697ae1 test eax, eax
00697ae3 je 0x697aef
00697ae5 cmp eax, 2
00697ae8 mov eax, 0x32
00697aed jne 0x697af4
00697aef mov eax, 0x30
00697af4 mov dword ptr [esi], eax
00697af6 mov al, 1
00697af8 mov dword ptr [edi], 1
00697afe pop edi
00697aff pop esi
00697b00 pop ebx
00697b01 mov esp, ebp
00697b03 pop ebp
00697b04 ret 
00697b05 mov eax, dword ptr [0xbfd65c]
00697b0a mov eax, dword ptr [eax + 0x243624]
00697b10 test eax, eax
00697b12 je 0x697b22
00697b14 cmp eax, 2
00697b17 mov eax, 0x19a
00697b1c jne 0x6976d7
00697b22 mov eax, 0x10b
00697b27 mov dword ptr [esi], eax
00697b29 mov al, 1
00697b2b mov dword ptr [edi], 0
00697b31 pop edi
00697b32 pop esi
00697b33 pop ebx
00697b34 mov esp, ebp
00697b36 pop ebp
00697b37 ret 
00697b38 mov dword ptr [esi], 0x19c
00697b3e mov al, 1
00697b40 mov dword ptr [edi], 0
00697b46 pop edi
00697b47 pop esi
00697b48 pop ebx
00697b49 mov esp, ebp
00697b4b pop ebp
00697b4c ret 
00697b4d mov ebx, dword ptr [0xbfd65c]
00697b53 lea eax, [ebp - 4]
00697b56 mov dword ptr [ebp - 4], 0x4f
00697b5d push eax
00697b5e lea ecx, [ebx + 0x1bb58]
00697b64 mov ebx, dword ptr [ecx]
00697b66 lea eax, [ebp - 0x10]
00697b69 push eax
00697b6a call 0x4206b0
00697b6f mov eax, dword ptr [ebp - 8]
00697b72 cmp byte ptr [eax + 0xd], 0
00697b76 jne 0x697bc8
00697b78 cmp dword ptr [eax + 0x10], 0x4f
00697b7c jg 0x697bc8
00697b7e cmp eax, ebx
00697b80 je 0x697bc8
00697b82 mov eax, dword ptr [esi]
00697b84 cmp eax, 0x1b
00697b87 je 0x697bac
00697b89 cmp eax, 0xcc
00697b8e jne 0x697b9f
00697b90 mov dword ptr [esi], 0xf7
00697b96 xor al, al
00697b98 pop edi
00697b99 pop esi
00697b9a pop ebx
00697b9b mov esp, ebp
00697b9d pop ebp
00697b9e ret 
00697b9f cmp eax, 0x35b
00697ba4 jne 0x697bbb
00697ba6 mov dword ptr [esi], 0x19
00697bac mov dword ptr [edi], 1
00697bb2 xor al, al
00697bb4 pop edi
00697bb5 pop esi
00697bb6 pop ebx
00697bb7 mov esp, ebp
00697bb9 pop ebp
00697bba ret 
00697bbb cmp eax, 0xdd
00697bc0 jne 0x697bc8
00697bc2 mov dword ptr [esi], 0x3a
00697bc8 pop edi
00697bc9 pop esi
00697bca xor al, al
00697bcc pop ebx
00697bcd mov esp, ebp
00697bcf pop ebp
00697bd0 ret 
