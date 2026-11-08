00959500 push ebp
00959501 mov ebp, esp
00959503 push -1
00959505 push 0xa027e5
0095950a mov eax, dword ptr fs:[0]
00959510 push eax
00959511 sub esp, 0x200
00959517 mov eax, dword ptr [0xbaa3b4]
0095951c xor eax, ebp
0095951e mov dword ptr [ebp - 0x10], eax
00959521 push esi
00959522 push edi
00959523 push eax
00959524 lea eax, [ebp - 0xc]
00959527 mov dword ptr fs:[0], eax
0095952d mov esi, ecx
0095952f mov dword ptr [ebp - 0x108], esi
00959535 push dword ptr [ebp + 0x10]
00959538 mov edi, dword ptr [ebp + 8]
0095953b push dword ptr [ebp + 0xc]
0095953e push edi
0095953f call 0x942e20
00959544 mov eax, dword ptr [esi + 4]
00959547 movss xmm0, dword ptr [0xb6a614]
0095954f test eax, eax
00959551 je 0x9595b1
00959553 mov ecx, dword ptr [eax + 0x28]
00959556 cmp ecx, 1
00959559 jne 0x959576
0095955b movss xmm0, dword ptr [eax + 0x13ac]
00959563 mov edx, eax
00959565 mov dword ptr [ebp - 0xe0], eax
0095956b mov dword ptr [ebp - 0xcc], eax
00959571 jmp 0x959616
00959576 cmp ecx, 3
00959579 jne 0x9595b1
0095957b mov edx, dword ptr [eax + 0x360]
00959581 mov dword ptr [ebp - 0xe0], edx
00959587 mov ecx, edx
00959589 test eax, eax
0095958b je 0x95960c
0095958d mov edx, dword ptr [eax + 0x28]
00959590 mov dword ptr [ebp - 0xcc], 0
0095959a mov dword ptr [ebp - 0xe0], ecx
009595a0 cmp edx, 1
009595a3 jne 0x9595d5
009595a5 movss xmm0, dword ptr [eax + 0x13ac]
009595ad mov edx, ecx
009595af jmp 0x959616
009595b1 mov ecx, eax
009595b3 xor edx, edx
009595b5 mov dword ptr [ebp - 0xcc], ecx
009595bb test ecx, ecx
009595bd je 0x959581
009595bf cmp dword ptr [ecx + 0x28], 1
009595c3 mov dword ptr [ebp - 0xe0], edx
009595c9 jne 0x959587
009595cb movss xmm0, dword ptr [eax + 0x13ac]
009595d3 jmp 0x959616
009595d5 mov dword ptr [ebp - 0xe0], ecx
009595db cmp edx, 3
009595de jne 0x959606
009595e0 mov eax, dword ptr [eax + 0x360]
009595e6 mov edx, ecx
009595e8 mov dword ptr [ebp - 0xcc], 0
009595f2 mov dword ptr [ebp - 0xe0], edx
009595f8 test eax, eax
009595fa je 0x95960c
009595fc movss xmm0, dword ptr [eax + 0x13ac]
00959604 jmp 0x959616
00959606 mov edx, dword ptr [ebp - 0xe0]
0095960c mov dword ptr [ebp - 0xcc], 0
00959616 mov ecx, dword ptr [esi + 0x30]
00959619 mov al, byte ptr [esi + 0x30]
0095961c shr ecx, 1
0095961e and al, 1
00959620 and ecx, 0xffffff01
00959626 movss dword ptr [ebp - 0x104], xmm0
0095962e mov byte ptr [ebp - 0xa5], al
00959634 mov dword ptr [ebp - 0x128], ecx
0095963a test al, al
0095963c jne 0x959648
0095963e mov byte ptr [ebp - 0x9d], al
00959644 test cl, cl
00959646 je 0x95964f
00959648 mov byte ptr [ebp - 0x9d], 1
0095964f test edx, edx
00959651 je 0x95966c
00959653 push 0
00959655 push 0x18a
0095965a mov ecx, edx
0095965c call 0x73af30
00959661 mov byte ptr [ebp - 0xf7], 1
00959668 test al, al
0095966a jne 0x959673
0095966c mov byte ptr [ebp - 0xf7], 0
00959673 mov ecx, dword ptr [esi + 0x30]
00959676 mov eax, ecx
00959678 shr eax, 7
0095967b test al, 1
0095967d jne 0x95968c
0095967f xorps xmm0, xmm0
00959682 comiss xmm0, dword ptr [esi + 0x10]
00959686 jae 0x95968c
00959688 xor dl, dl
0095968a jmp 0x959691
0095968c mov edx, 1
00959691 movzx eax, byte ptr [ebp - 0x9d]
00959698 shr ecx, 8
0095969b and cl, 1
0095969e mov dword ptr [ebp - 0xd8], edx
009596a4 mov dword ptr [ebp - 0x124], ecx
009596aa mov ecx, 0
009596af cmove ecx, eax
009596b2 mov eax, dword ptr [ebp - 0xcc]
009596b8 mov dword ptr [ebp - 0x120], ecx
009596be test eax, eax
009596c0 je 0x9596e3
009596c2 mov ecx, eax
009596c4 call 0x79cb80
009596c9 mov edx, dword ptr [ebp - 0xd8]
009596cf cmp eax, -1
009596d2 movzx edx, dl
009596d5 mov eax, 1
009596da cmovne edx, eax
009596dd mov dword ptr [ebp - 0xd8], edx
009596e3 mov ecx, dword ptr [esi + 4]
009596e6 movss xmm3, dword ptr [0xb6a820]
009596ee test ecx, ecx
009596f0 je 0x959767
009596f2 cmp dword ptr [ecx + 0x28], 1
009596f6 jne 0x959767
009596f8 cmp dword ptr [ecx + 0x1818], 0
009596ff jle 0x959767
00959701 cmp byte ptr [ebp - 0xa5], 0
00959708 je 0x95974f
0095970a movss xmm0, dword ptr [esi + 0x10]
0095970f lea edx, [ebp - 0xa4]
00959715 movss xmm1, dword ptr [0xb6a8f4]
0095971d lea eax, [ebp - 0xc4]
00959723 mulss xmm0, xmm3
00959727 mov dword ptr [ebp - 0xa4], 0x40a00000
00959731 comiss xmm1, xmm0
00959734 movss dword ptr [ebp - 0xc4], xmm0
0095973c movss xmm0, dword ptr [esi + 0x14]
00959741 cmovbe eax, edx
00959744 mov edx, dword ptr [ebp - 0xd8]
0095974a comiss xmm0, dword ptr [eax]
0095974d jae 0x95975e
0095974f cmp byte ptr [ebp - 0x128], 0
00959756 je 0x959767
00959758 cmp dword ptr [esi + 0x40], 0
0095975c jle 0x959767
0095975e mov byte ptr [ebp - 0x9d], 0
00959765 jmp 0x959774
00959767 mov al, byte ptr [ebp + 0xc]
0095976a mov byte ptr [ebp - 0x9d], al
00959770 test ecx, ecx
00959772 je 0x9597ae
00959774 mov eax, dword ptr [ecx + 0x28]
00959777 cmp eax, 1
0095977a je 0x95978d
0095977c cmp eax, 3
0095977f jne 0x9597ae
00959781 mov eax, dword ptr [ecx + 0x360]
00959787 mov ecx, eax
00959789 test eax, eax
0095978b je 0x9597ae
0095978d mov ecx, dword ptr [ecx + 0x1354]
00959793 test ecx, ecx
00959795 je 0x9597ae
00959797 cmp byte ptr [ebp - 0xf7], 0
0095979e je 0x9597ae
009597a0 mov eax, dword ptr [ecx + 0x294]
009597a6 mov ecx, dword ptr [ecx + 0x298]
009597ac jmp 0x9597b4
009597ae mov eax, dword ptr [esi + 0x24]
009597b1 mov ecx, dword ptr [esi + 0x28]
009597b4 mov dword ptr [ebp - 0x11c], eax
009597ba lea eax, [ebp - 0x11c]
009597c0 mov dword ptr [ebp - 0x118], ecx
009597c6 movss xmm1, dword ptr [eax]
009597ca ucomiss xmm1, dword ptr [0xc02fec]
009597d1 movss xmm0, dword ptr [eax + 4]
009597d6 lahf 
009597d7 test ah, 0x44
009597da jp 0x9597ed
009597dc ucomiss xmm0, dword ptr [0xc02ff0]
009597e3 lahf 
009597e4 test ah, 0x44
009597e7 jp 0x9597ed
009597e9 xor al, al
009597eb jmp 0x9597ef
009597ed mov al, 1
009597ef cmp byte ptr [ebp + 0x10], 0
009597f3 jne 0x9599c8
009597f9 cmp byte ptr [ebp - 0x9d], 0
00959800 je 0x9599c8
00959806 test al, al
00959808 je 0x959a75
0095980e lea eax, [ebp - 0x144]
00959814 mov ecx, esi
00959816 push eax
00959817 call 0x9434a0
0095981c subss xmm0, dword ptr [eax + 4]
00959821 subss xmm1, dword ptr [eax]
00959825 mulss xmm0, xmm0
00959829 mulss xmm1, xmm1
0095982d addss xmm0, xmm1
00959831 call 0x4228c0
00959836 movaps xmm2, xmm0
00959839 movss xmm5, dword ptr [0xb6a614]
00959841 subss xmm2, dword ptr [0xb6aa60]
00959849 movss xmm1, dword ptr [esi + 0x10]
0095984e lea eax, [ebp - 0xa4]
00959854 mulss xmm1, dword ptr [0xb6a820]
0095985c lea ecx, [ebp - 0xc4]
00959862 mov dword ptr [ebp - 0xc4], 0
0095986c xorps xmm4, xmm4
0095986f movss xmm3, dword ptr [esi + 0x14]
00959874 divss xmm2, dword ptr [0xb6abec]
0095987c mov dword ptr [ebp - 0xe4], 0x3f800000
00959886 subss xmm1, dword ptr [0xb6a8f4]
0095988e comiss xmm4, xmm2
00959891 movss dword ptr [ebp - 0xa4], xmm2
00959899 cmovbe ecx, eax
0095989c lea eax, [ebp - 0xe4]
009598a2 movss xmm0, dword ptr [ecx]
009598a6 comiss xmm0, xmm5
009598a9 cmovbe eax, ecx
009598ac comiss xmm3, xmm4
009598af mulss xmm1, dword ptr [eax]
009598b3 addss xmm1, dword ptr [0xb6a8f4]
009598bb subss xmm1, xmm5
009598bf jbe 0x959915
009598c1 comiss xmm4, xmm2
009598c4 lea eax, [ebp - 0xa4]
009598ca mov dword ptr [ebp - 0xc4], 0
009598d4 lea ecx, [ebp - 0xc4]
009598da mov dword ptr [ebp - 0xe4], 0x3f800000
009598e4 movss dword ptr [ebp - 0xa4], xmm2
009598ec cmovbe ecx, eax
009598ef lea eax, [ebp - 0xe4]
009598f5 movss xmm0, dword ptr [ecx]
009598f9 comiss xmm0, xmm5
009598fc cmovbe eax, ecx
009598ff movss xmm0, dword ptr [eax]
00959903 mulss xmm0, dword ptr [0xb6a8cc]
0095990b addss xmm0, xmm5
0095990f cvttss2si eax, xmm0
00959913 jmp 0x95991a
00959915 mov eax, 1
0095991a mov cl, byte ptr [ebp - 0xa5]
00959920 test cl, cl
00959922 je 0x95992d
00959924 comiss xmm3, xmm1
00959927 ja 0x9599c1
0095992d cmp byte ptr [ebp - 0x128], 0
00959934 je 0x95993f
00959936 cmp dword ptr [esi + 0x40], eax
00959939 jge 0x9599c1
0095993f mov edx, dword ptr [ebp - 0xd8]
00959945 movss xmm3, dword ptr [0xb6a820]
0095994d test dl, dl
0095994f je 0x9599c8
00959951 cmp byte ptr [ebp - 0x120], 0
00959958 je 0x9599c8
0095995a test cl, cl
0095995c lea ecx, [esi + 0x14]
0095995f je 0x959973
00959961 movss xmm0, dword ptr [esi + 0x10]
00959966 movss xmm1, dword ptr [ecx]
0095996a mulss xmm0, xmm3
0095996e comiss xmm1, xmm0
00959971 jae 0x959996
00959973 cmp byte ptr [ebp - 0x128], 0
0095997a je 0x9599c8
0095997c movss xmm1, dword ptr [ecx]
00959980 comiss xmm1, xmm4
00959983 jbe 0x95998b
00959985 cmp dword ptr [esi + 0x40], 5
00959989 jge 0x959996
0095998b comiss xmm4, xmm1
0095998e jb 0x9599c8
00959990 cmp dword ptr [esi + 0x40], 0
00959994 jle 0x9599c8
00959996 movss xmm0, dword ptr [0xb6a1b0]
0095999e lea eax, [ebp - 0xc4]
009599a4 comiss xmm0, xmm1
009599a7 mov dword ptr [ebp - 0xc4], 0x3727c5ac
009599b1 cmovbe eax, ecx
009599b4 movss xmm0, dword ptr [eax]
009599b8 movss dword ptr [esi + 0x44], xmm0
009599bd movss dword ptr [ecx], xmm0
009599c1 mov byte ptr [ebp - 0x9d], 0
009599c8 cmp byte ptr [ebp + 0xc], 0
009599cc movss xmm0, dword ptr [edi]
009599d0 movss dword ptr [ebp - 0xd0], xmm0
009599d8 movss dword ptr [ebp - 0xf4], xmm0
009599e0 movss xmm0, dword ptr [edi + 4]
009599e5 movss dword ptr [ebp - 0xd4], xmm0
009599ed movss dword ptr [ebp - 0xf0], xmm0
009599f5 jne 0x959a21
009599f7 movss xmm0, dword ptr [esi + 0x1c]
009599fc movss dword ptr [ebp - 0xd0], xmm0
00959a04 movss dword ptr [ebp - 0xf4], xmm0
00959a0c movss xmm0, dword ptr [esi + 0x20]
00959a11 movss dword ptr [ebp - 0xd4], xmm0
00959a19 movss dword ptr [ebp - 0xf0], xmm0
00959a21 mov ecx, esi
00959a23 call 0x942c40
00959a28 movss xmm5, dword ptr [0xb6ae44]
00959a30 test al, al
00959a32 je 0x959aa4
00959a34 movss xmm3, dword ptr [ebp - 0xd0]
00959a3c xorps xmm0, xmm0
00959a3f movss xmm4, dword ptr [ebp - 0xd4]
00959a47 movaps xmm2, xmm3
00959a4a andps xmm2, xmmword ptr [0xb6c980]
00959a51 movaps xmm1, xmm4
00959a54 andps xmm1, xmmword ptr [0xb6c980]
00959a5b comiss xmm2, xmm1
00959a5e jbe 0x959a8d
00959a60 comiss xmm0, xmm3
00959a63 movss dword ptr [ebp - 0xd4], xmm0
00959a6b jbe 0x959a83
00959a6d movaps xmm2, xmm5
00959a70 jmp 0x959afa
00959a75 mov cl, byte ptr [ebp - 0xa5]
00959a7b xorps xmm4, xmm4
00959a7e jmp 0x95994d
00959a83 movss xmm2, dword ptr [0xb6a614]
00959a8b jmp 0x959afa
00959a8d comiss xmm0, xmm4
00959a90 xorps xmm2, xmm2
00959a93 jbe 0x959a9a
00959a95 movaps xmm0, xmm5
00959a98 jmp 0x959af2
00959a9a movss xmm0, dword ptr [0xb6a614]
00959aa2 jmp 0x959af2
00959aa4 movss xmm1, dword ptr [ebp - 0xd0]
00959aac movss xmm0, dword ptr [ebp - 0xd4]
00959ab4 mulss xmm0, xmm0
00959ab8 mulss xmm1, xmm1
00959abc addss xmm0, xmm1
00959ac0 call 0x4228c0
00959ac5 comiss xmm0, dword ptr [0xb6a18c]
00959acc jbe 0x959b12
00959ace movss xmm1, dword ptr [0xb6a614]
00959ad6 divss xmm1, xmm0
00959ada movss xmm2, dword ptr [ebp - 0xd0]
00959ae2 movss xmm0, dword ptr [ebp - 0xd4]
00959aea mulss xmm2, xmm1
00959aee mulss xmm0, xmm1
00959af2 movss dword ptr [ebp - 0xd4], xmm0
00959afa movss dword ptr [ebp - 0xf0], xmm0
00959b02 movss dword ptr [ebp - 0xf4], xmm2
00959b0a movss dword ptr [ebp - 0xd0], xmm2
00959b12 mov edi, dword ptr [ebp - 0xcc]
00959b18 mov dword ptr [ebp - 0x130], 0
00959b22 test edi, edi
00959b24 je 0x959b8d
00959b26 cmp byte ptr [ebp - 0x128], 0
00959b2d jne 0x959b83
00959b2f cmp dword ptr [edi + 0x130c], 2
00959b36 je 0x959b83
00959b38 push 0
00959b3a push 0x1bc
00959b3f mov ecx, edi
00959b41 call 0x73af30
00959b46 test al, al
00959b48 jne 0x959b83
00959b4a push 0
00959b4c push 0x2c4
00959b51 mov ecx, edi
00959b53 call 0x73af30
00959b58 test al, al
00959b5a jne 0x959b83
00959b5c cmp dword ptr [edi + 0x130c], 0x17
00959b63 je 0x959b83
00959b65 push 0
00959b67 push 0x98
00959b6c mov ecx, edi
00959b6e call 0x73af30
00959b73 test al, al
00959b75 je 0x959b8d
00959b77 mov dword ptr [ebp - 0x130], 0xffffffff
00959b81 jmp 0x959b8d
00959b83 mov dword ptr [ebp - 0x130], 1
00959b8d mov edx, dword ptr [ebp - 0x120]
00959b93 mov ecx, 1
00959b98 mov dword ptr [ebp - 0xe4], ecx
00959b9e test dl, dl
00959ba0 jne 0x959bd8
00959ba2 test edi, edi
00959ba4 je 0x959bd8
00959ba6 push 0
00959ba8 push 0x258
00959bad mov ecx, edi
00959baf call 0x73af30
00959bb4 mov edx, dword ptr [ebp - 0x120]
00959bba mov ecx, 1
00959bbf test al, al
00959bc1 je 0x959bd8
00959bc3 cmp dword ptr [ebp - 0x130], 0
00959bca mov eax, 2
00959bcf cmove ecx, eax
00959bd2 mov dword ptr [ebp - 0xe4], ecx
00959bd8 xor eax, eax
00959bda mov dword ptr [ebp - 0x1b0], 0x48
00959be4 mov dword ptr [ebp - 0xc4], eax
00959bea movss xmm0, dword ptr [esi + 0x10]
00959bef test eax, eax
00959bf1 movss xmm2, dword ptr [0xb6aa0c]
00959bf9 mov edi, 0xc
00959bfe cmovne edi, dword ptr [ebp - 0x1b0]
00959c05 movss xmm3, dword ptr [0xb6a614]
00959c0d add edi, esi
00959c0f movss dword ptr [ebp - 0xc0], xmm0
00959c17 cmp ecx, 2
00959c1a jne 0x959c5e
00959c1c addss xmm0, xmm3
00959c20 movaps xmm1, xmm2
00959c23 divss xmm1, xmm0
00959c27 test eax, eax
00959c29 jne 0x959c35
00959c2b movss xmm0, dword ptr [0xb6a4bc]
00959c33 jmp 0x959c3d
00959c35 movss xmm0, dword ptr [0xb6a444]
00959c3d mulss xmm0, xmm1
00959c41 movaps xmm4, xmm2
00959c44 divss xmm4, xmm0
00959c48 movss xmm0, dword ptr [ebp - 0xc0]
00959c50 subss xmm4, xmm3
00959c54 movss dword ptr [ebp - 0x12c], xmm4
00959c5c jmp 0x959c69
00959c5e movaps xmm4, xmm0
00959c61 movss dword ptr [ebp - 0x12c], xmm0
00959c69 cmp byte ptr [ebp - 0x124], 0
00959c70 je 0x959d8c
00959c76 mulss xmm0, dword ptr [0xb6a98c]
00959c7e xorps xmm2, xmm2
00959c81 movss xmm1, dword ptr [esi + 0x14]
00959c86 movss dword ptr [ebp - 0xa4], xmm1
00959c8e ucomiss xmm2, xmm0
00959c91 movss dword ptr [ebp - 0xc0], xmm0
00959c99 lahf 
00959c9a test ah, 0x44
00959c9d jp 0x959cc1
00959c9f push 0xb5d590
00959ca4 push 3
00959ca6 call 0x95e330
00959cab movss xmm0, dword ptr [ebp - 0xc0]
00959cb3 add esp, 8
00959cb6 movss xmm1, dword ptr [ebp - 0xa4]
00959cbe xorps xmm2, xmm2
00959cc1 subss xmm0, xmm2
00959cc5 mov dword ptr [ebp - 0xa4], 0
00959ccf subss xmm1, xmm2
00959cd3 mov dword ptr [ebp - 0x10c], 0x3f800000
00959cdd lea eax, [ebp - 0xc0]
00959ce3 lea ecx, [ebp - 0xa4]
00959ce9 divss xmm1, xmm0
00959ced comiss xmm2, xmm1
00959cf0 movss dword ptr [ebp - 0xc0], xmm1
00959cf8 movss xmm1, dword ptr [0xb6a7b0]
00959d00 cmovbe ecx, eax
00959d03 lea eax, [ebp - 0x10c]
00959d09 movss xmm0, dword ptr [ecx]
00959d0d comiss xmm0, dword ptr [0xb6a614]
00959d14 cmovbe eax, ecx
00959d17 movss xmm0, dword ptr [eax]
00959d1b mulss xmm0, dword ptr [0xb6a6d0]
00959d23 addss xmm0, dword ptr [0xb6a614]
00959d2b call 0x4c3f60
00959d30 movss xmm1, dword ptr [ebp - 0x12c]
00959d38 lea ecx, [ebp - 0x12c]
00959d3e movss xmm3, dword ptr [0xb6a614]
00959d46 lea eax, [ebp - 0xa4]
00959d4c addss xmm1, xmm3
00959d50 mov edx, dword ptr [ebp - 0x120]
00959d56 mov dword ptr [ebp - 0x12c], 0x3e800000
00959d60 divss xmm1, xmm0
00959d64 comiss xmm1, dword ptr [0xb6a38c]
00959d6b movss dword ptr [ebp - 0xa4], xmm1
00959d73 cmovbe eax, ecx
00959d76 mov ecx, dword ptr [ebp - 0xe4]
00959d7c movss xmm4, dword ptr [eax]
00959d80 subss xmm4, xmm3
00959d84 movss dword ptr [ebp - 0x12c], xmm4
00959d8c xor eax, eax
00959d8e xorps xmm2, xmm2
00959d91 movss dword ptr [ebp - 0xd8], xmm2
00959d99 test dl, dl
00959d9b je 0x959dee
00959d9d cmp byte ptr [ebp - 0x9d], al
00959da3 jne 0x959dd1
00959da5 cmp byte ptr [ebp - 0xa5], al
00959dab je 0x959dbe
00959dad movss xmm0, dword ptr [esi + 0x14]
00959db2 comiss xmm0, xmm2
00959db5 jbe 0x959dbe
00959db7 mov eax, 1
00959dbc jmp 0x959dd1
00959dbe cmp byte ptr [ebp - 0x128], al
00959dc4 je 0x959dd1
00959dc6 cmp dword ptr [esi + 0x40], eax
00959dc9 mov edi, 1
00959dce cmovg eax, edi
00959dd1 cmp byte ptr [ebp + 0x10], 0
00959dd5 je 0x959e39
00959dd7 test eax, eax
00959dd9 je 0x95c703
00959ddf push ecx
00959de0 push 1
00959de2 mov ecx, esi
00959de4 call 0x944fc0
00959de9 jmp 0x95c703
00959dee cmp byte ptr [ebp - 0x9d], al
00959df4 je 0x959e39
00959df6 cmp byte ptr [ebp + 0x10], al
00959df9 jne 0x95c703
00959dff comiss xmm2, dword ptr [edi]
00959e02 movss xmm1, dword ptr [0xb6ae44]
00959e0a subss xmm1, dword ptr [edi]
00959e0e movss dword ptr [ebp - 0xd8], xmm1
00959e16 jbe 0x959e32
00959e18 cmp eax, 8
00959e1b jae 0x959e32
00959e1d movaps xmm0, xmm4
00959e20 inc eax
00959e21 addss xmm0, xmm3
00959e25 addss xmm0, dword ptr [edi]
00959e29 comiss xmm2, xmm0
00959e2c movss dword ptr [edi], xmm0
00959e30 ja 0x959e18
00959e32 mov dword ptr [esi + 0x44], 0
00959e39 test eax, eax
00959e3b je 0x95c227
00959e41 jmp 0x959e46
00959e43 xorps xmm2, xmm2
00959e46 mov edx, dword ptr [esi + 4]
00959e49 dec eax
00959e4a mov dword ptr [ebp - 0x134], eax
00959e50 test edx, edx
00959e52 je 0x959e9f
00959e54 mov eax, dword ptr [edx + 0x28]
00959e57 cmp eax, 1
00959e5a jne 0x959e60
00959e5c mov ecx, edx
00959e5e jmp 0x959e6f
00959e60 cmp eax, 3
00959e63 jne 0x959e9f
00959e65 mov ecx, dword ptr [edx + 0x360]
00959e6b test ecx, ecx
00959e6d je 0x959e9f
00959e6f push dword ptr [esi + 0x2c]
00959e72 lea eax, [ebp - 0x34]
00959e75 push eax
00959e76 call 0x74a910
00959e7b movzx eax, word ptr [ebp - 0x14]
00959e7f xorps xmm2, xmm2
00959e82 mov edx, dword ptr [esi + 4]
00959e85 movss xmm3, dword ptr [0xb6a614]
00959e8d mov dword ptr [ebp - 0xa4], eax
00959e93 mov ax, word ptr [ebp - 0x34]
00959e97 mov dword ptr [ebp - 0x10c], eax
00959e9d jmp 0x959ece
00959e9f xor ecx, ecx
00959ea1 mov dword ptr [ebp - 0x20], 1
00959ea8 xor eax, eax
00959eaa mov dword ptr [ebp - 0x10c], ecx
00959eb0 xorps xmm0, xmm0
00959eb3 mov dword ptr [ebp - 0x34], ecx
00959eb6 movups xmmword ptr [ebp - 0x30], xmm0
00959eba mov dword ptr [ebp - 0x1c], ecx
00959ebd mov word ptr [ebp - 0x18], cx
00959ec1 mov byte ptr [ebp - 0x16], cl
00959ec4 mov dword ptr [ebp - 0xa4], eax
00959eca mov word ptr [ebp - 0x14], ax
00959ece cmp byte ptr [ebp - 0xa5], 0
00959ed5 movss xmm0, dword ptr [ebp - 0xd0]
00959edd movss dword ptr [ebp - 0x13c], xmm0
00959ee5 movss xmm0, dword ptr [ebp - 0xd4]
00959eed mov dword ptr [ebp - 0xc0], 0
00959ef7 movss dword ptr [ebp - 0x138], xmm0
00959eff je 0x959f49
00959f01 mov dword ptr [ebp - 0xb0], 0xc
00959f0b test edx, edx
00959f0d je 0x959f19
00959f0f cmp dword ptr [edx + 0x28], 1
00959f13 jne 0x959f19
00959f15 mov ecx, edx
00959f17 jmp 0x959f25
00959f19 xor ecx, ecx
00959f1b test edx, edx
00959f1d je 0x959f25
00959f1f cmp dword ptr [edx + 0x28], 3
00959f23 je 0x959f27
00959f25 xor edx, edx
00959f27 test ecx, ecx
00959f29 je 0x959f36
00959f2b add ecx, 0x1288
00959f31 cmp dword ptr [ecx], 0xc
00959f34 jmp 0x959fa5
00959f36 test edx, edx
00959f38 je 0x959fb2
00959f3a cmp dword ptr [edx + 0xca0], 0xc
00959f41 lea ecx, [edx + 0xca0]
00959f47 jmp 0x959fa5
00959f49 movss xmm0, dword ptr [esi + 0x10]
00959f4e mov ecx, 7
00959f53 mulss xmm0, dword ptr [0xb6ae1c]
00959f5b mov edi, 0xb
00959f60 cvttss2si eax, xmm0
00959f64 sub ecx, eax
00959f66 cmp ecx, edi
00959f68 cmovg edi, ecx
00959f6b mov dword ptr [ebp - 0xb0], edi
00959f71 test edx, edx
00959f73 je 0x959f7f
00959f75 cmp dword ptr [edx + 0x28], 1
00959f79 jne 0x959f7f
00959f7b mov ecx, edx
00959f7d jmp 0x959f8b
00959f7f xor ecx, ecx
00959f81 test edx, edx
00959f83 je 0x959f8b
00959f85 cmp dword ptr [edx + 0x28], 3
00959f89 je 0x959f8d
00959f8b xor edx, edx
00959f8d test ecx, ecx
00959f8f je 0x959f99
00959f91 add ecx, 0x1288
00959f97 jmp 0x959fa3
00959f99 test edx, edx
00959f9b je 0x959fb2
00959f9d lea ecx, [edx + 0xca0]
00959fa3 cmp dword ptr [ecx], edi
00959fa5 lea eax, [ebp - 0xb0]
00959fab cmovge eax, ecx
00959fae mov eax, dword ptr [eax]
00959fb0 mov dword ptr [ecx], eax
00959fb2 cmp byte ptr [ebp - 0x124], 0
00959fb9 je 0x95a033
00959fbb movss xmm0, dword ptr [esi + 0x10]
00959fc0 mulss xmm0, dword ptr [0xb6a98c]
00959fc8 movss xmm1, dword ptr [esi + 0x14]
00959fcd addss xmm1, xmm3
00959fd1 addss xmm0, xmm3
00959fd5 divss xmm1, xmm0
00959fd9 mulss xmm1, dword ptr [0xb6a9bc]
00959fe1 ucomiss xmm1, xmm2
00959fe4 lahf 
00959fe5 test ah, 0x44
00959fe8 jp 0x959ff8
00959fea push 0x255
00959fef mov ecx, esi
00959ff1 call 0x944910
00959ff6 jmp 0x95a033
00959ff8 push ecx
00959ff9 movss dword ptr [esp], xmm1
00959ffe lea eax, [ebp - 0xf4]
0095a004 push eax
0095a005 push 2
0095a007 push 0x255
0095a00c mov ecx, esi
0095a00e call 0x943ad0
0095a013 movss xmm0, dword ptr [ebp - 0xf0]
0095a01b movss dword ptr [ebp - 0xd4], xmm0
0095a023 movss xmm0, dword ptr [ebp - 0xf4]
0095a02b movss dword ptr [ebp - 0xd0], xmm0
0095a033 push 1
0095a035 lea eax, [ebp - 0x13c]
0095a03b mov ecx, esi
0095a03d push eax
0095a03e call 0x9471c0
0095a043 mov edi, dword ptr [ebp - 0xcc]
0095a049 test edi, edi
0095a04b je 0x95a267
0095a051 mov ecx, dword ptr [ebp - 0x130]
0095a057 test ecx, ecx
0095a059 je 0x95a070
0095a05b mov eax, dword ptr [esi + 4]
0095a05e test eax, eax
0095a060 je 0x95a0b5
0095a062 cmp dword ptr [eax + 0x28], 1
0095a066 jne 0x95a0b5
0095a068 mov byte ptr [eax + 0x14bc], cl
0095a06e jmp 0x95a0b5
0095a070 cmp dword ptr [ebp - 0xe4], 1
0095a077 jbe 0x95a099
0095a079 mov ecx, dword ptr [esi + 4]
0095a07c test ecx, ecx
0095a07e je 0x95a0b5
0095a080 cmp dword ptr [ecx + 0x28], 1
0095a084 jne 0x95a0b5
0095a086 cmp dword ptr [ebp - 0xc4], 0
0095a08d setne al
0095a090 lea eax, [eax*2 - 1]
0095a097 jmp 0x95a0af
0095a099 mov ecx, esi
0095a09b call 0x9450f0
0095a0a0 mov ecx, dword ptr [esi + 4]
0095a0a3 neg eax
0095a0a5 test ecx, ecx
0095a0a7 je 0x95a0b5
0095a0a9 cmp dword ptr [ecx + 0x28], 1
0095a0ad jne 0x95a0b5
0095a0af mov byte ptr [ecx + 0x14bc], al
0095a0b5 mov ecx, esi
0095a0b7 call 0x9450f0
0095a0bc movzx edi, ax
0095a0bf mov dword ptr [ebp - 0xc0], edi
0095a0c5 call 0x9453a0
0095a0ca test al, al
0095a0cc je 0x95a157
0095a0d2 movsx eax, di
0095a0d5 movd xmm0, eax
0095a0d9 cvtdq2ps xmm0, xmm0
0095a0dc mulss xmm0, dword ptr [0xb6aa4c]
0095a0e4 mulss xmm0, dword ptr [0xb6a230]
0095a0ec movss dword ptr [ebp - 0xb0], xmm0
0095a0f4 call 0x411fe0
0095a0f9 movss dword ptr [ebp - 0xb8], xmm0
0095a101 movss xmm0, dword ptr [ebp - 0xb0]
0095a109 call 0x412010
0095a10e movaps xmm5, xmm0
0095a111 movss xmm0, dword ptr [ebp - 0xb8]
0095a119 movaps xmm1, xmm5
0095a11c movaps xmm4, xmm0
0095a11f mulss xmm4, dword ptr [ebp - 0x13c]
0095a127 mulss xmm1, dword ptr [ebp - 0x138]
0095a12f mulss xmm5, dword ptr [ebp - 0x13c]
0095a137 mulss xmm0, dword ptr [ebp - 0x138]
0095a13f subss xmm4, xmm1
0095a143 addss xmm5, xmm0
0095a147 movss dword ptr [ebp - 0x13c], xmm4
0095a14f movss dword ptr [ebp - 0x138], xmm5
0095a157 cmp byte ptr [ebp - 0xa5], 0
0095a15e jne 0x95a19f
0095a160 cmp byte ptr [ebp - 0x124], 0
0095a167 jne 0x95a19f
0095a169 cmp word ptr [ebp - 0x10c], 1
0095a171 mov edi, dword ptr [ebp - 0xe0]
0095a177 jg 0x95a1a5
0095a179 push 0
0095a17b push 0xa9
0095a180 mov ecx, edi
0095a182 call 0x73af30
0095a187 test al, al
0095a189 jne 0x95a1a5
0095a18b push 0
0095a18d push 0x95
0095a192 mov ecx, edi
0095a194 call 0x73af30
0095a199 test al, al
0095a19b je 0x95a1af
0095a19d jmp 0x95a1a5
0095a19f mov edi, dword ptr [ebp - 0xe0]
0095a1a5 mov dword ptr [ebp - 0xc0], 0
0095a1af push 0
0095a1b1 push 6
0095a1b3 mov ecx, edi
0095a1b5 call 0x73af30
0095a1ba test al, al
0095a1bc jne 0x95a20e
0095a1be cmp byte ptr [edi + 0x1461], al
0095a1c4 jne 0x95a1fc
0095a1c6 mov eax, dword ptr [edi + 0x1454]
0095a1cc mov edi, dword ptr [edi + 0x1458]
0095a1d2 cmp eax, edi
0095a1d4 je 0x95a1f6
0095a1d6 mov edx, dword ptr [eax]
0095a1d8 mov ecx, dword ptr [edx]
0095a1da cmp ecx, 1
0095a1dd je 0x95a1e9
0095a1df cmp ecx, 3
0095a1e2 je 0x95a1e9
0095a1e4 cmp ecx, 4
0095a1e7 jne 0x95a1ef
0095a1e9 cmp dword ptr [edx + 4], 6
0095a1ed je 0x95a20e
0095a1ef add eax, 0xc
0095a1f2 cmp eax, edi
0095a1f4 jne 0x95a1d6
0095a1f6 mov edi, dword ptr [ebp - 0xe0]
0095a1fc push 0
0095a1fe push 0x1b8
0095a203 mov ecx, edi
0095a205 call 0x73af30
0095a20a test al, al
0095a20c je 0x95a261
0095a20e mov ecx, dword ptr [esi + 4]
0095a211 mov dword ptr [ebp - 0xc0], 0
0095a21b mov dword ptr [ebp - 0xb0], 0x10
0095a225 test ecx, ecx
0095a227 je 0x95a22f
0095a229 cmp dword ptr [ecx + 0x28], 1
0095a22d je 0x95a23d
0095a22f mov eax, ecx
0095a231 xor ecx, ecx
0095a233 test eax, eax
0095a235 je 0x95a23d
0095a237 cmp dword ptr [eax + 0x28], 3
0095a23b je 0x95a24b
0095a23d xor eax, eax
0095a23f test ecx, ecx
0095a241 je 0x95a261
0095a243 add ecx, 0x1288
0095a249 jmp 0x95a251
0095a24b lea ecx, [eax + 0xca0]
0095a251 cmp dword ptr [ecx], 0x10
0095a254 lea eax, [ebp - 0xb0]
0095a25a cmovge eax, ecx
0095a25d mov eax, dword ptr [eax]
0095a25f mov dword ptr [ecx], eax
0095a261 mov edi, dword ptr [ebp - 0xcc]
0095a267 mov eax, dword ptr [esi + 4]
0095a26a test eax, eax
0095a26c je 0x95a288
0095a26e movss xmm0, dword ptr [eax + 0x294]
0095a276 movss dword ptr [ebp - 0xec], xmm0
0095a27e movss xmm0, dword ptr [eax + 0x298]
0095a286 jmp 0x95a2a0
0095a288 movss xmm0, dword ptr [0xc02fec]
0095a290 movss dword ptr [ebp - 0xec], xmm0
0095a298 movss xmm0, dword ptr [0xc02ff0]
0095a2a0 movss dword ptr [ebp - 0xe8], xmm0
0095a2a8 lea eax, [ebp - 0x13c]
0095a2ae movss xmm0, dword ptr [ebp - 0x13c]
0095a2b6 mov ecx, esi
0095a2b8 mulss xmm0, dword ptr [0xb6a974]
0095a2c0 push eax
0095a2c1 lea eax, [ebp - 0x20c]
0095a2c7 push eax
0095a2c8 movss dword ptr [ebp - 0xc8], xmm0
0095a2d0 movss xmm0, dword ptr [ebp - 0x138]
0095a2d8 mulss xmm0, dword ptr [0xb6a974]
0095a2e0 movss dword ptr [ebp - 0xb8], xmm0
0095a2e8 call 0x945190
0095a2ed movss xmm0, dword ptr [ebp - 0xc8]
0095a2f5 addss xmm0, dword ptr [eax]
0095a2f9 movss dword ptr [ebp - 0xc8], xmm0
0095a301 movss dword ptr [ebp - 0x14c], xmm0
0095a309 movss xmm0, dword ptr [ebp - 0xb8]
0095a311 addss xmm0, dword ptr [eax + 4]
0095a316 mov eax, dword ptr [ebp - 0xe0]
0095a31c movss dword ptr [ebp - 0xb8], xmm0
0095a324 movss dword ptr [ebp - 0x148], xmm0
0095a32c test eax, eax
0095a32e je 0x95a3b1
0095a334 push 0
0095a336 push 0x95
0095a33b mov ecx, eax
0095a33d call 0x73af30
0095a342 test al, al
0095a344 je 0x95a3b1
0095a346 call 0x6c3d90
0095a34b movd xmm0, eax
0095a34f cvtdq2pd xmm0, xmm0
0095a353 shr eax, 0x1f
0095a356 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095a35f cvtpd2ps xmm1, xmm0
0095a363 mulss xmm1, dword ptr [0xb6a19c]
0095a36b mulss xmm1, dword ptr [0xb6a350]
0095a373 addss xmm1, dword ptr [0xb6a5a4]
0095a37b movaps xmm0, xmm1
0095a37e mulss xmm1, dword ptr [ebp - 0xb8]
0095a386 mulss xmm0, dword ptr [ebp - 0xc8]
0095a38e movss dword ptr [ebp - 0xb8], xmm1
0095a396 movss dword ptr [ebp - 0xc8], xmm0
0095a39e movss dword ptr [ebp - 0x14c], xmm0
0095a3a6 movaps xmm0, xmm1
0095a3a9 movss dword ptr [ebp - 0x148], xmm0
0095a3b1 cmp byte ptr [ebp - 0xa5], 0
0095a3b8 movss xmm2, dword ptr [0xb6a614]
0095a3c0 movss dword ptr [ebp - 0xb0], xmm2
0095a3c8 je 0x95a4ae
0095a3ce cmp byte ptr [ebp - 0x124], 0
0095a3d5 movss xmm1, dword ptr [esi + 0x10]
0095a3da addss xmm1, xmm2
0095a3de je 0x95a43b
0095a3e0 movss xmm0, dword ptr [esi + 0x14]
0095a3e5 lea eax, [ebp - 0xb4]
0095a3eb mulss xmm1, dword ptr [0xb6a98c]
0095a3f3 addss xmm0, xmm2
0095a3f7 lea ecx, [ebp - 0xb0]
0095a3fd mov dword ptr [ebp - 0xb0], 0x3dcccccd
0095a407 mov dword ptr [ebp - 0xbc], 0x40800000
0095a411 mulss xmm0, dword ptr [0xb6a8cc]
0095a419 divss xmm0, xmm1
0095a41d movss xmm1, dword ptr [0xb6a2cc]
0095a425 comiss xmm1, xmm0
0095a428 movss dword ptr [ebp - 0xb4], xmm0
0095a430 cmovbe ecx, eax
0095a433 lea eax, [ebp - 0xbc]
0095a439 jmp 0x95a494
0095a43b movss xmm0, dword ptr [esi + 0x44]
0095a440 lea eax, [ebp - 0xb0]
0095a446 mulss xmm1, dword ptr [0xb6a820]
0095a44e addss xmm0, xmm2
0095a452 lea ecx, [ebp - 0xbc]
0095a458 mov dword ptr [ebp - 0xbc], 0x3dcccccd
0095a462 mov dword ptr [ebp - 0xb4], 0x40800000
0095a46c mulss xmm0, dword ptr [0xb6a8cc]
0095a474 divss xmm0, xmm1
0095a478 movss xmm1, dword ptr [0xb6a2cc]
0095a480 comiss xmm1, xmm0
0095a483 movss dword ptr [ebp - 0xb0], xmm0
0095a48b cmovbe ecx, eax
0095a48e lea eax, [ebp - 0xb4]
0095a494 movss xmm0, dword ptr [ecx]
0095a498 comiss xmm0, dword ptr [0xb6a8cc]
0095a49f cmovbe eax, ecx
0095a4a2 movss xmm0, dword ptr [eax]
0095a4a6 movss dword ptr [ebp - 0xb0], xmm0
0095a4ae xorps xmm2, xmm2
0095a4b1 xorps xmm3, xmm3
0095a4b4 movss dword ptr [ebp - 0xb4], xmm2
0095a4bc test edi, edi
0095a4be je 0x95a5b9
0095a4c4 mov ecx, esi
0095a4c6 call 0x945170
0095a4cb mov ecx, dword ptr [ebp - 0xcc]
0095a4d1 mov edi, eax
0095a4d3 push 0
0095a4d5 push 0x170
0095a4da call 0x73af30
0095a4df test al, al
0095a4e1 je 0x95a523
0095a4e3 test edi, edi
0095a4e5 jle 0x95a523
0095a4e7 mov eax, 0xb60b60b7
0095a4ec imul edi
0095a4ee add edx, edi
0095a4f0 sar edx, 6
0095a4f3 mov eax, edx
0095a4f5 shr eax, 0x1f
0095a4f8 add eax, edx
0095a4fa movd xmm2, eax
0095a4fe cvtdq2ps xmm2, xmm2
0095a501 mulss xmm2, dword ptr [0xb6a9b0]
0095a509 divss xmm2, dword ptr [0xb6a864]
0095a511 addss xmm2, dword ptr [0xb6a18c]
0095a519 movss dword ptr [ebp - 0xb4], xmm2
0095a521 jmp 0x95a52b
0095a523 movss xmm2, dword ptr [ebp - 0xb4]
0095a52b mov ecx, esi
0095a52d call 0x945130
0095a532 mov edx, eax
0095a534 call 0x945150
0095a539 test edx, edx
0095a53b jle 0x95a56e
0095a53d test eax, eax
0095a53f jle 0x95a56e
0095a541 lea ecx, [eax - 1]
0095a544 cmp edx, ecx
0095a546 jge 0x95a56e
0095a548 movd xmm1, edx
0095a54c cvtdq2ps xmm1, xmm1
0095a54f movd xmm0, eax
0095a553 mulss xmm1, dword ptr [0xb6a9e8]
0095a55b cvtdq2ps xmm0, xmm0
0095a55e divss xmm1, xmm0
0095a562 addss xmm2, xmm1
0095a566 movss dword ptr [ebp - 0xb4], xmm2
0095a56e mov edi, dword ptr [ebp - 0xcc]
0095a574 mov ecx, edi
0095a576 call 0x79cb80
0095a57b cmp eax, 2
0095a57e jne 0x95a592
0095a580 movss xmm2, dword ptr [ebp - 0xb4]
0095a588 addss xmm2, dword ptr [0xb6a9e8]
0095a590 jmp 0x95a5ae
0095a592 mov ecx, edi
0095a594 call 0x79cb80
0095a599 movss xmm2, dword ptr [ebp - 0xb4]
0095a5a1 cmp eax, 4
0095a5a4 jne 0x95a5b6
0095a5a6 addss xmm2, dword ptr [0xb6a940]
0095a5ae movss dword ptr [ebp - 0xb4], xmm2
0095a5b6 xorps xmm3, xmm3
0095a5b9 cmp byte ptr [ebp - 0x124], 0
0095a5c0 je 0x95a62e
0095a5c2 movss xmm0, dword ptr [esi + 0x10]
0095a5c7 lea eax, [ebp - 0xb4]
0095a5cd movss xmm1, dword ptr [esi + 0x14]
0095a5d2 lea ecx, [ebp - 0xbc]
0095a5d8 mulss xmm0, dword ptr [0xb6a98c]
0095a5e0 mov dword ptr [ebp - 0xbc], 0
0095a5ea mulss xmm1, dword ptr [0xb6a9b0]
0095a5f2 mov dword ptr [ebp - 0xac], 0x41800000
0095a5fc divss xmm1, xmm0
0095a600 comiss xmm3, xmm1
0095a603 movss dword ptr [ebp - 0xb4], xmm1
0095a60b cmovbe ecx, eax
0095a60e lea eax, [ebp - 0xac]
0095a614 movss xmm0, dword ptr [ecx]
0095a618 comiss xmm0, dword ptr [0xb6a9b0]
0095a61f cmovbe eax, ecx
0095a622 addss xmm2, dword ptr [eax]
0095a626 movss dword ptr [ebp - 0xb4], xmm2
0095a62e cmp word ptr [ebp - 0xc0], 0
0095a636 je 0x95af3c
0095a63c cmp dword ptr [ebp - 0x130], 1
0095a643 jne 0x95af3c
0095a649 test edi, edi
0095a64b je 0x95af3c
0095a651 push 0
0095a653 push 0x98
0095a658 mov ecx, edi
0095a65a call 0x73af30
0095a65f test al, al
0095a661 je 0x95af34
0095a667 movss xmm1, dword ptr [ebp - 0x13c]
0095a66f movss xmm2, dword ptr [ebp - 0x138]
0095a677 movaps xmm0, xmm1
0095a67a mulss xmm0, xmm1
0095a67e movss dword ptr [ebp - 0x114], xmm1
0095a686 movaps xmm1, xmm2
0095a689 mulss xmm1, xmm2
0095a68d movss dword ptr [ebp - 0x110], xmm2
0095a695 addss xmm0, xmm1
0095a699 call 0x4228c0
0095a69e xorps xmm3, xmm3
0095a6a1 comiss xmm0, xmm3
0095a6a4 jbe 0x95a6d9
0095a6a6 movss xmm1, dword ptr [0xb6a614]
0095a6ae divss xmm1, xmm0
0095a6b2 movaps xmm0, xmm1
0095a6b5 mulss xmm0, dword ptr [ebp - 0x114]
0095a6bd movss dword ptr [ebp - 0x114], xmm0
0095a6c5 movss xmm0, dword ptr [ebp - 0x110]
0095a6cd mulss xmm0, xmm1
0095a6d1 movss dword ptr [ebp - 0x110], xmm0
0095a6d9 mov eax, dword ptr fs:[0x2c]
0095a6df mov ecx, dword ptr [eax]
0095a6e1 mov eax, dword ptr [0xc07190]
0095a6e6 cmp eax, dword ptr [ecx + 0xc]
0095a6ec jg 0x95c720
0095a6f2 jmp 0x95a6f7
0095a6f4 xorps xmm3, xmm3
0095a6f7 cmp byte ptr [ebp - 0x17], 0
0095a6fb mov eax, dword ptr [0xc07194]
0095a700 mov dword ptr [0xc07198], eax
0095a705 je 0x95a85a
0095a70b movss xmm1, dword ptr [ebp - 0xb4]
0095a713 movss xmm0, dword ptr [ebp - 0x114]
0095a71b movss xmm2, dword ptr [ebp - 0x110]
0095a723 xorps xmm0, xmmword ptr [0xb6c9b0]
0095a72a xorps xmm2, xmmword ptr [0xb6c9b0]
0095a731 ucomiss xmm1, xmm3
0095a734 movss dword ptr [ebp - 0xc0], xmm0
0095a73c movss dword ptr [ebp - 0xb8], xmm2
0095a744 lahf 
0095a745 test ah, 0x44
0095a748 jnp 0x95a7f0
0095a74e call 0x6c3d90
0095a753 xorps xmm0, xmm0
0095a756 cvtsi2sd xmm0, eax
0095a75a shr eax, 0x1f
0095a75d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095a766 cvtpd2ps xmm0, xmm0
0095a76a mulss xmm0, dword ptr [0xb6a19c]
0095a772 subss xmm0, dword ptr [0xb6a480]
0095a77a mulss xmm0, xmm1
0095a77e mulss xmm0, dword ptr [0xb6a230]
0095a786 movss dword ptr [ebp - 0xac], xmm0
0095a78e call 0x411fe0
0095a793 movss dword ptr [ebp - 0xbc], xmm0
0095a79b movss xmm0, dword ptr [ebp - 0xac]
0095a7a3 call 0x412010
0095a7a8 movss xmm3, dword ptr [ebp - 0xbc]
0095a7b0 movaps xmm1, xmm0
0095a7b3 mulss xmm1, dword ptr [ebp - 0xb8]
0095a7bb movaps xmm2, xmm3
0095a7be mulss xmm2, dword ptr [ebp - 0xc0]
0095a7c6 mulss xmm3, dword ptr [ebp - 0xb8]
0095a7ce mulss xmm0, dword ptr [ebp - 0xc0]
0095a7d6 subss xmm2, xmm1
0095a7da addss xmm3, xmm0
0095a7de movss dword ptr [ebp - 0x184], xmm2
0095a7e6 movss dword ptr [ebp - 0x180], xmm3
0095a7ee jmp 0x95a800
0095a7f0 movss dword ptr [ebp - 0x184], xmm0
0095a7f8 movss dword ptr [ebp - 0x180], xmm2
0095a800 movss xmm0, dword ptr [ebp - 0xb0]
0095a808 lea eax, [ebp - 0x184]
0095a80e push ecx
0095a80f movss dword ptr [esp], xmm0
0095a814 mov ecx, esi
0095a816 push 1
0095a818 push 0
0095a81a push eax
0095a81b push 1
0095a81d lea eax, [ebp - 0xec]
0095a823 push eax
0095a824 call 0x945e40
0095a829 mov ecx, dword ptr [0xc07198]
0095a82f mov dword ptr [ebp - 0xac], eax
0095a835 cmp ecx, dword ptr [0xc0719c]
0095a83b je 0x95a848
0095a83d mov dword ptr [ecx], eax
0095a83f add dword ptr [0xc07198], 4
0095a846 jmp 0x95a85a
0095a848 lea eax, [ebp - 0xac]
0095a84e push eax
0095a84f push ecx
0095a850 mov ecx, 0xc07194
0095a855 call 0x426fb0
0095a85a cmp byte ptr [ebp - 0x16], 0
0095a85e je 0x95aaf4
0095a864 movss xmm1, dword ptr [ebp - 0xb4]
0095a86c ucomiss xmm1, dword ptr [0xb6a18c]
0095a873 movss xmm0, dword ptr [ebp - 0x110]
0095a87b xorps xmm0, xmmword ptr [0xb6c9b0]
0095a882 lahf 
0095a883 movss dword ptr [ebp - 0xbc], xmm0
0095a88b test ah, 0x44
0095a88e jnp 0x95a93a
0095a894 call 0x6c3d90
0095a899 xorps xmm0, xmm0
0095a89c cvtsi2sd xmm0, eax
0095a8a0 shr eax, 0x1f
0095a8a3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095a8ac cvtpd2ps xmm0, xmm0
0095a8b0 mulss xmm0, dword ptr [0xb6a19c]
0095a8b8 subss xmm0, dword ptr [0xb6a480]
0095a8c0 mulss xmm0, xmm1
0095a8c4 mulss xmm0, dword ptr [0xb6a230]
0095a8cc movss dword ptr [ebp - 0xac], xmm0
0095a8d4 call 0x411fe0
0095a8d9 movss dword ptr [ebp - 0xc0], xmm0
0095a8e1 movss xmm0, dword ptr [ebp - 0xac]
0095a8e9 call 0x412010
0095a8ee movss xmm2, dword ptr [ebp - 0xbc]
0095a8f6 movaps xmm3, xmm0
0095a8f9 movss xmm0, dword ptr [ebp - 0x114]
0095a901 movaps xmm1, xmm3
0095a904 mulss xmm2, dword ptr [ebp - 0xc0]
0095a90c mulss xmm3, dword ptr [ebp - 0xbc]
0095a914 mulss xmm1, xmm0
0095a918 mulss xmm0, dword ptr [ebp - 0xc0]
0095a920 subss xmm2, xmm1
0095a924 addss xmm3, xmm0
0095a928 movss dword ptr [ebp - 0x18c], xmm2
0095a930 movss dword ptr [ebp - 0x188], xmm3
0095a938 jmp 0x95a952
0095a93a movss dword ptr [ebp - 0x18c], xmm0
0095a942 movss xmm0, dword ptr [ebp - 0x114]
0095a94a movss dword ptr [ebp - 0x188], xmm0
0095a952 movss xmm0, dword ptr [ebp - 0xb0]
0095a95a lea eax, [ebp - 0x18c]
0095a960 push ecx
0095a961 movss dword ptr [esp], xmm0
0095a966 mov ecx, esi
0095a968 push 1
0095a96a push 0
0095a96c push eax
0095a96d push 1
0095a96f lea eax, [ebp - 0xec]
0095a975 push eax
0095a976 call 0x945e40
0095a97b mov ecx, dword ptr [0xc07198]
0095a981 mov dword ptr [ebp - 0xac], eax
0095a987 cmp ecx, dword ptr [0xc0719c]
0095a98d je 0x95a99a
0095a98f mov dword ptr [ecx], eax
0095a991 add dword ptr [0xc07198], 4
0095a998 jmp 0x95a9ac
0095a99a lea eax, [ebp - 0xac]
0095a9a0 push eax
0095a9a1 push ecx
0095a9a2 mov ecx, 0xc07194
0095a9a7 call 0x426fb0
0095a9ac movss xmm1, dword ptr [ebp - 0xb4]
0095a9b4 ucomiss xmm1, dword ptr [0xb6a18c]
0095a9bb movss xmm2, dword ptr [ebp - 0x114]
0095a9c3 xorps xmm2, xmmword ptr [0xb6c9b0]
0095a9ca lahf 
0095a9cb movss dword ptr [ebp - 0xc0], xmm2
0095a9d3 test ah, 0x44
0095a9d6 jnp 0x95aa82
0095a9dc call 0x6c3d90
0095a9e1 xorps xmm0, xmm0
0095a9e4 cvtsi2sd xmm0, eax
0095a9e8 shr eax, 0x1f
0095a9eb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095a9f4 cvtpd2ps xmm0, xmm0
0095a9f8 mulss xmm0, dword ptr [0xb6a19c]
0095aa00 subss xmm0, dword ptr [0xb6a480]
0095aa08 mulss xmm0, xmm1
0095aa0c mulss xmm0, dword ptr [0xb6a230]
0095aa14 movss dword ptr [ebp - 0xac], xmm0
0095aa1c call 0x411fe0
0095aa21 movss dword ptr [ebp - 0xbc], xmm0
0095aa29 movss xmm0, dword ptr [ebp - 0xac]
0095aa31 call 0x412010
0095aa36 movss xmm4, dword ptr [ebp - 0xbc]
0095aa3e movaps xmm3, xmm0
0095aa41 movss xmm0, dword ptr [ebp - 0x110]
0095aa49 movaps xmm2, xmm4
0095aa4c movss xmm1, dword ptr [ebp - 0xc0]
0095aa54 mulss xmm4, dword ptr [ebp - 0xc0]
0095aa5c mulss xmm2, xmm0
0095aa60 mulss xmm1, xmm3
0095aa64 mulss xmm0, xmm3
0095aa68 subss xmm2, xmm1
0095aa6c addss xmm4, xmm0
0095aa70 movss dword ptr [ebp - 0x1ac], xmm2
0095aa78 movss dword ptr [ebp - 0x1a8], xmm4
0095aa80 jmp 0x95aa9a
0095aa82 movss xmm0, dword ptr [ebp - 0x110]
0095aa8a movss dword ptr [ebp - 0x1ac], xmm0
0095aa92 movss dword ptr [ebp - 0x1a8], xmm2
0095aa9a movss xmm0, dword ptr [ebp - 0xb0]
0095aaa2 lea eax, [ebp - 0x1ac]
0095aaa8 push ecx
0095aaa9 movss dword ptr [esp], xmm0
0095aaae mov ecx, esi
0095aab0 push 1
0095aab2 push 0
0095aab4 push eax
0095aab5 push 1
0095aab7 lea eax, [ebp - 0xec]
0095aabd push eax
0095aabe call 0x945e40
0095aac3 mov ecx, dword ptr [0xc07198]
0095aac9 mov dword ptr [ebp - 0xac], eax
0095aacf cmp ecx, dword ptr [0xc0719c]
0095aad5 je 0x95aae2
0095aad7 mov dword ptr [ecx], eax
0095aad9 add dword ptr [0xc07198], 4
0095aae0 jmp 0x95aaf4
0095aae2 lea eax, [ebp - 0xac]
0095aae8 push eax
0095aae9 push ecx
0095aaea mov ecx, 0xc07194
0095aaef call 0x426fb0
0095aaf4 mov eax, dword ptr [ebp - 0xa4]
0095aafa movzx edi, ax
0095aafd test edi, edi
0095aaff je 0x95acd0
0095ab05 call 0x6c3d90
0095ab0a movd xmm0, eax
0095ab0e cvtdq2pd xmm0, xmm0
0095ab12 shr eax, 0x1f
0095ab15 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095ab1e cvtpd2ps xmm0, xmm0
0095ab22 mulss xmm0, dword ptr [0xb6a19c]
0095ab2a mulss xmm0, dword ptr [0xb6ac40]
0095ab32 mulss xmm0, dword ptr [0xb6a230]
0095ab3a movss dword ptr [ebp - 0xac], xmm0
0095ab42 call 0x411fe0
0095ab47 movss dword ptr [ebp - 0xbc], xmm0
0095ab4f movss xmm0, dword ptr [ebp - 0xac]
0095ab57 call 0x412010
0095ab5c movss xmm4, dword ptr [ebp - 0x114]
0095ab64 movaps xmm3, xmm0
0095ab67 mulss xmm4, dword ptr [ebp - 0xbc]
0095ab6f movaps xmm1, xmm3
0095ab72 mulss xmm1, dword ptr [ebp - 0x110]
0095ab7a movss xmm0, dword ptr [ebp - 0x110]
0095ab82 mulss xmm3, dword ptr [ebp - 0x114]
0095ab8a mulss xmm0, dword ptr [ebp - 0xbc]
0095ab92 subss xmm4, xmm1
0095ab96 movss xmm1, dword ptr [ebp - 0xb4]
0095ab9e ucomiss xmm1, dword ptr [0xb6a18c]
0095aba5 addss xmm3, xmm0
0095aba9 movss dword ptr [ebp - 0xa4], xmm4
0095abb1 lahf 
0095abb2 movss dword ptr [ebp - 0xc0], xmm3
0095abba test ah, 0x44
0095abbd jnp 0x95ac5d
0095abc3 call 0x6c3d90
0095abc8 xorps xmm0, xmm0
0095abcb cvtsi2sd xmm0, eax
0095abcf shr eax, 0x1f
0095abd2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095abdb cvtpd2ps xmm0, xmm0
0095abdf mulss xmm0, dword ptr [0xb6a19c]
0095abe7 subss xmm0, dword ptr [0xb6a480]
0095abef mulss xmm0, xmm1
0095abf3 mulss xmm0, dword ptr [0xb6a230]
0095abfb movss dword ptr [ebp - 0xac], xmm0
0095ac03 call 0x411fe0
0095ac08 movss dword ptr [ebp - 0xbc], xmm0
0095ac10 movss xmm0, dword ptr [ebp - 0xac]
0095ac18 call 0x412010
0095ac1d movss xmm3, dword ptr [ebp - 0xbc]
0095ac25 movaps xmm1, xmm0
0095ac28 mulss xmm1, dword ptr [ebp - 0xc0]
0095ac30 movaps xmm2, xmm3
0095ac33 mulss xmm2, dword ptr [ebp - 0xa4]
0095ac3b mulss xmm3, dword ptr [ebp - 0xc0]
0095ac43 mulss xmm0, dword ptr [ebp - 0xa4]
0095ac4b subss xmm2, xmm1
0095ac4f addss xmm3, xmm0
0095ac53 movss dword ptr [ebp - 0x16c], xmm2
0095ac5b jmp 0x95ac65
0095ac5d movss dword ptr [ebp - 0x16c], xmm4
0095ac65 movss xmm0, dword ptr [ebp - 0xb0]
0095ac6d lea eax, [ebp - 0x16c]
0095ac73 push ecx
0095ac74 movss dword ptr [esp], xmm0
0095ac79 mov ecx, esi
0095ac7b push 1
0095ac7d push 0
0095ac7f push eax
0095ac80 push 1
0095ac82 lea eax, [ebp - 0xec]
0095ac88 movss dword ptr [ebp - 0x168], xmm3
0095ac90 push eax
0095ac91 call 0x945e40
0095ac96 mov ecx, dword ptr [0xc07198]
0095ac9c mov dword ptr [ebp - 0xac], eax
0095aca2 cmp ecx, dword ptr [0xc0719c]
0095aca8 je 0x95acb5
0095acaa mov dword ptr [ecx], eax
0095acac add dword ptr [0xc07198], 4
0095acb3 jmp 0x95acc7
0095acb5 lea eax, [ebp - 0xac]
0095acbb push eax
0095acbc push ecx
0095acbd mov ecx, 0xc07194
0095acc2 call 0x426fb0
0095acc7 sub edi, 1
0095acca jne 0x95ab05
0095acd0 mov eax, dword ptr [ebp - 0x10c]
0095acd6 xor edi, edi
0095acd8 cwde 
0095acd9 test eax, eax
0095acdb jle 0x95aee6
0095ace1 movups xmm0, xmmword ptr [ebp - 0x24]
0095ace5 movups xmm1, xmmword ptr [ebp - 0x34]
0095ace9 nop dword ptr [eax]
0095acf0 mov ecx, dword ptr [ebp - 0x14]
0095acf3 sub esp, 0x24
0095acf6 mov eax, esp
0095acf8 push ecx
0095acf9 movups xmmword ptr [eax], xmm1
0095acfc movups xmmword ptr [eax + 0x10], xmm0
0095ad00 mov dword ptr [eax + 0x20], ecx
0095ad03 lea eax, [ebp - 0x1c8]
0095ad09 movss xmm0, dword ptr [ebp - 0x104]
0095ad11 movss dword ptr [esp], xmm0
0095ad16 push dword ptr [ebp - 0x110]
0095ad1c push dword ptr [ebp - 0x114]
0095ad22 push 3
0095ad24 push edi
0095ad25 push eax
0095ad26 call 0x943a80
0095ad2b movss xmm1, dword ptr [ebp - 0x1bc]
0095ad33 movss xmm2, dword ptr [ebp - 0x1c0]
0095ad3b movaps xmm0, xmm1
0095ad3e mulss xmm0, xmm1
0095ad42 movss dword ptr [ebp - 0xb8], xmm1
0095ad4a movaps xmm1, xmm2
0095ad4d mulss xmm1, xmm2
0095ad51 movss dword ptr [ebp - 0xc0], xmm2
0095ad59 addss xmm0, xmm1
0095ad5d call 0x4228c0
0095ad62 xorps xmm3, xmm3
0095ad65 comiss xmm0, xmm3
0095ad68 jbe 0x95ad9b
0095ad6a movss xmm1, dword ptr [0xb6a614]
0095ad72 divss xmm1, xmm0
0095ad76 movaps xmm0, xmm1
0095ad79 mulss xmm1, dword ptr [ebp - 0xb8]
0095ad81 mulss xmm0, dword ptr [ebp - 0xc0]
0095ad89 movss dword ptr [ebp - 0xb8], xmm1
0095ad91 movss dword ptr [ebp - 0xc0], xmm0
0095ad99 jmp 0x95adab
0095ad9b movss xmm0, dword ptr [ebp - 0x1c0]
0095ada3 movss xmm1, dword ptr [ebp - 0x1bc]
0095adab movss xmm2, dword ptr [ebp - 0xb4]
0095adb3 ucomiss xmm2, xmm3
0095adb6 lahf 
0095adb7 test ah, 0x44
0095adba jnp 0x95ae62
0095adc0 call 0x6c3d90
0095adc5 xorps xmm0, xmm0
0095adc8 cvtsi2sd xmm0, eax
0095adcc shr eax, 0x1f
0095adcf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095add8 cvtpd2ps xmm0, xmm0
0095addc mulss xmm0, dword ptr [0xb6a19c]
0095ade4 subss xmm0, dword ptr [0xb6a480]
0095adec mulss xmm0, xmm2
0095adf0 mulss xmm0, dword ptr [0xb6a230]
0095adf8 movss dword ptr [ebp - 0xac], xmm0
0095ae00 call 0x411fe0
0095ae05 movss dword ptr [ebp - 0xbc], xmm0
0095ae0d movss xmm0, dword ptr [ebp - 0xac]
0095ae15 call 0x412010
0095ae1a movss xmm3, dword ptr [ebp - 0xbc]
0095ae22 movaps xmm1, xmm0
0095ae25 mulss xmm1, dword ptr [ebp - 0xb8]
0095ae2d movaps xmm2, xmm3
0095ae30 mulss xmm2, dword ptr [ebp - 0xc0]
0095ae38 mulss xmm0, dword ptr [ebp - 0xc0]
0095ae40 mulss xmm3, dword ptr [ebp - 0xb8]
0095ae48 subss xmm2, xmm1
0095ae4c addss xmm0, xmm3
0095ae50 movss dword ptr [ebp - 0x194], xmm2
0095ae58 movss dword ptr [ebp - 0x190], xmm0
0095ae60 jmp 0x95ae72
0095ae62 movss dword ptr [ebp - 0x194], xmm0
0095ae6a movss dword ptr [ebp - 0x190], xmm1
0095ae72 movss xmm0, dword ptr [ebp - 0xb0]
0095ae7a lea eax, [ebp - 0x194]
0095ae80 push ecx
0095ae81 movss dword ptr [esp], xmm0
0095ae86 mov ecx, esi
0095ae88 push 1
0095ae8a push 0
0095ae8c push eax
0095ae8d push 1
0095ae8f lea eax, [ebp - 0xec]
0095ae95 push eax
0095ae96 call 0x945e40
0095ae9b mov ecx, dword ptr [0xc07198]
0095aea1 mov dword ptr [ebp - 0xac], eax
0095aea7 cmp ecx, dword ptr [0xc0719c]
0095aead je 0x95aeba
0095aeaf mov dword ptr [ecx], eax
0095aeb1 add dword ptr [0xc07198], 4
0095aeb8 jmp 0x95aecc
0095aeba lea eax, [ebp - 0xac]
0095aec0 push eax
0095aec1 push ecx
0095aec2 mov ecx, 0xc07194
0095aec7 call 0x426fb0
0095aecc mov ecx, dword ptr [ebp - 0x10c]
0095aed2 inc edi
0095aed3 movups xmm0, xmmword ptr [ebp - 0x24]
0095aed7 movsx eax, cx
0095aeda movups xmm1, xmmword ptr [ebp - 0x34]
0095aede cmp edi, eax
0095aee0 jl 0x95acf0
0095aee6 mov eax, dword ptr [0xc07198]
0095aeeb xor esi, esi
0095aeed sub eax, dword ptr [0xc07194]
0095aef3 sar eax, 2
0095aef6 test eax, eax
0095aef8 je 0x95c1df
0095aefe nop 
0095af00 mov eax, dword ptr [0xc07194]
0095af05 mov eax, dword ptr [eax + esi*4]
0095af08 mov byte ptr [eax + 0x434], 0
0095af0f mov eax, dword ptr [0xc07194]
0095af14 mov ecx, dword ptr [eax + esi*4]
0095af17 mov eax, dword ptr [ecx]
0095af19 call dword ptr [eax + 0xc]
0095af1c mov eax, dword ptr [0xc07198]
0095af21 inc esi
0095af22 sub eax, dword ptr [0xc07194]
0095af28 sar eax, 2
0095af2b cmp esi, eax
0095af2d jb 0x95af00
0095af2f jmp 0x95c1df
0095af34 movss xmm2, dword ptr [ebp - 0xb4]
0095af3c cmp byte ptr [ebp - 0x17], 0
0095af40 je 0x95b085
0095af46 ucomiss xmm2, dword ptr [0xb6a18c]
0095af4d movss xmm0, dword ptr [ebp - 0xc8]
0095af55 xorps xmm0, xmmword ptr [0xb6c9b0]
0095af5c movss xmm3, dword ptr [ebp - 0x104]
0095af64 movss xmm1, dword ptr [ebp - 0xb8]
0095af6c xorps xmm1, xmmword ptr [0xb6c9b0]
0095af73 mulss xmm3, xmm0
0095af77 movss xmm0, dword ptr [ebp - 0x104]
0095af7f mulss xmm0, xmm1
0095af83 lahf 
0095af84 movss dword ptr [ebp - 0xbc], xmm3
0095af8c movss dword ptr [ebp - 0xfc], xmm0
0095af94 test ah, 0x44
0095af97 jnp 0x95b03f
0095af9d call 0x6c3d90
0095afa2 xorps xmm0, xmm0
0095afa5 cvtsi2sd xmm0, eax
0095afa9 shr eax, 0x1f
0095afac addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095afb5 cvtpd2ps xmm0, xmm0
0095afb9 mulss xmm0, dword ptr [0xb6a19c]
0095afc1 subss xmm0, dword ptr [0xb6a480]
0095afc9 mulss xmm0, xmm2
0095afcd mulss xmm0, dword ptr [0xb6a230]
0095afd5 movss dword ptr [ebp - 0xac], xmm0
0095afdd call 0x411fe0
0095afe2 movss dword ptr [ebp - 0xdc], xmm0
0095afea movss xmm0, dword ptr [ebp - 0xac]
0095aff2 call 0x412010
0095aff7 movss xmm4, dword ptr [ebp - 0xbc]
0095afff movaps xmm1, xmm0
0095b002 movss xmm3, dword ptr [ebp - 0xdc]
0095b00a movaps xmm2, xmm4
0095b00d mulss xmm1, dword ptr [ebp - 0xfc]
0095b015 mulss xmm2, xmm3
0095b019 mulss xmm3, dword ptr [ebp - 0xfc]
0095b021 mulss xmm4, xmm0
0095b025 subss xmm2, xmm1
0095b029 addss xmm4, xmm3
0095b02d movss dword ptr [ebp - 0x174], xmm2
0095b035 movss dword ptr [ebp - 0x170], xmm4
0095b03d jmp 0x95b04f
0095b03f movss dword ptr [ebp - 0x174], xmm3
0095b047 movss dword ptr [ebp - 0x170], xmm0
0095b04f movss xmm0, dword ptr [ebp - 0xd8]
0095b057 lea eax, [ebp - 0x174]
0095b05d sub esp, 0xc
0095b060 mov ecx, esi
0095b062 movss dword ptr [esp + 8], xmm0
0095b068 movss xmm0, dword ptr [ebp - 0xb0]
0095b070 movss dword ptr [esp + 4], xmm0
0095b076 push 6
0095b078 push eax
0095b079 lea eax, [ebp - 0xec]
0095b07f push eax
0095b080 call 0x9453d0
0095b085 cmp byte ptr [ebp - 0x16], 0
0095b089 je 0x95b2ed
0095b08f movss xmm1, dword ptr [ebp - 0xb4]
0095b097 ucomiss xmm1, dword ptr [0xb6a18c]
0095b09e movss xmm0, dword ptr [ebp - 0xb8]
0095b0a6 xorps xmm0, xmmword ptr [0xb6c9b0]
0095b0ad movss xmm2, dword ptr [ebp - 0x104]
0095b0b5 mulss xmm2, xmm0
0095b0b9 movss xmm0, dword ptr [ebp - 0x104]
0095b0c1 mulss xmm0, dword ptr [ebp - 0xc8]
0095b0c9 lahf 
0095b0ca movss dword ptr [ebp - 0xac], xmm2
0095b0d2 movss dword ptr [ebp - 0xbc], xmm0
0095b0da test ah, 0x44
0095b0dd jnp 0x95b17d
0095b0e3 call 0x6c3d90
0095b0e8 xorps xmm0, xmm0
0095b0eb cvtsi2sd xmm0, eax
0095b0ef shr eax, 0x1f
0095b0f2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b0fb cvtpd2ps xmm0, xmm0
0095b0ff mulss xmm0, dword ptr [0xb6a19c]
0095b107 subss xmm0, dword ptr [0xb6a480]
0095b10f mulss xmm0, xmm1
0095b113 mulss xmm0, dword ptr [0xb6a230]
0095b11b movss dword ptr [ebp - 0xfc], xmm0
0095b123 call 0x411fe0
0095b128 movss dword ptr [ebp - 0xdc], xmm0
0095b130 movss xmm0, dword ptr [ebp - 0xfc]
0095b138 call 0x412010
0095b13d movss xmm3, dword ptr [ebp - 0xdc]
0095b145 movaps xmm1, xmm0
0095b148 mulss xmm0, dword ptr [ebp - 0xac]
0095b150 movaps xmm2, xmm3
0095b153 mulss xmm3, dword ptr [ebp - 0xbc]
0095b15b mulss xmm2, dword ptr [ebp - 0xac]
0095b163 mulss xmm1, dword ptr [ebp - 0xbc]
0095b16b addss xmm3, xmm0
0095b16f subss xmm2, xmm1
0095b173 movss dword ptr [ebp - 0x178], xmm3
0095b17b jmp 0x95b185
0095b17d movss dword ptr [ebp - 0x178], xmm0
0095b185 movss xmm0, dword ptr [ebp - 0xd8]
0095b18d lea eax, [ebp - 0x17c]
0095b193 sub esp, 0xc
0095b196 movss dword ptr [ebp - 0x17c], xmm2
0095b19e mov ecx, esi
0095b1a0 movss dword ptr [esp + 8], xmm0
0095b1a6 movss xmm0, dword ptr [ebp - 0xb0]
0095b1ae movss dword ptr [esp + 4], xmm0
0095b1b4 push 6
0095b1b6 push eax
0095b1b7 lea eax, [ebp - 0xec]
0095b1bd push eax
0095b1be call 0x9453d0
0095b1c3 movss xmm1, dword ptr [ebp - 0xb4]
0095b1cb ucomiss xmm1, dword ptr [0xb6a18c]
0095b1d2 movss xmm0, dword ptr [ebp - 0xc8]
0095b1da xorps xmm0, xmmword ptr [0xb6c9b0]
0095b1e1 movss xmm2, dword ptr [ebp - 0x104]
0095b1e9 movss xmm3, dword ptr [ebp - 0x104]
0095b1f1 mulss xmm2, dword ptr [ebp - 0xb8]
0095b1f9 mulss xmm3, xmm0
0095b1fd lahf 
0095b1fe movss dword ptr [ebp - 0xac], xmm2
0095b206 movss dword ptr [ebp - 0xbc], xmm3
0095b20e test ah, 0x44
0095b211 jnp 0x95b2a7
0095b217 call 0x6c3d90
0095b21c xorps xmm0, xmm0
0095b21f cvtsi2sd xmm0, eax
0095b223 shr eax, 0x1f
0095b226 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b22f cvtpd2ps xmm0, xmm0
0095b233 mulss xmm0, dword ptr [0xb6a19c]
0095b23b subss xmm0, dword ptr [0xb6a480]
0095b243 mulss xmm0, xmm1
0095b247 mulss xmm0, dword ptr [0xb6a230]
0095b24f movss dword ptr [ebp - 0xfc], xmm0
0095b257 call 0x411fe0
0095b25c movss dword ptr [ebp - 0xdc], xmm0
0095b264 movss xmm0, dword ptr [ebp - 0xfc]
0095b26c call 0x412010
0095b271 movss xmm3, dword ptr [ebp - 0xdc]
0095b279 movaps xmm1, xmm0
0095b27c mulss xmm1, dword ptr [ebp - 0xbc]
0095b284 movaps xmm2, xmm3
0095b287 mulss xmm2, dword ptr [ebp - 0xac]
0095b28f mulss xmm3, dword ptr [ebp - 0xbc]
0095b297 mulss xmm0, dword ptr [ebp - 0xac]
0095b29f subss xmm2, xmm1
0095b2a3 addss xmm3, xmm0
0095b2a7 movss xmm0, dword ptr [ebp - 0xd8]
0095b2af lea eax, [ebp - 0x11c]
0095b2b5 sub esp, 0xc
0095b2b8 movss dword ptr [ebp - 0x118], xmm3
0095b2c0 mov ecx, esi
0095b2c2 movss dword ptr [ebp - 0x11c], xmm2
0095b2ca movss dword ptr [esp + 8], xmm0
0095b2d0 movss xmm0, dword ptr [ebp - 0xb0]
0095b2d8 movss dword ptr [esp + 4], xmm0
0095b2de push 6
0095b2e0 push eax
0095b2e1 lea eax, [ebp - 0xec]
0095b2e7 push eax
0095b2e8 call 0x9453d0
0095b2ed mov eax, dword ptr [ebp - 0xa4]
0095b2f3 movzx edi, ax
0095b2f6 test edi, edi
0095b2f8 je 0x95b5b3
0095b2fe movss xmm0, dword ptr [ebp - 0xb4]
0095b306 ucomiss xmm0, dword ptr [0xb6a18c]
0095b30d lahf 
0095b30e test ah, 0x44
0095b311 jnp 0x95b4c0
0095b317 call 0x6c3d90
0095b31c movd xmm0, eax
0095b320 cvtdq2pd xmm0, xmm0
0095b324 shr eax, 0x1f
0095b327 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b330 cvtpd2ps xmm0, xmm0
0095b334 mulss xmm0, dword ptr [0xb6a19c]
0095b33c mulss xmm0, dword ptr [0xb6ac40]
0095b344 mulss xmm0, dword ptr [0xb6a230]
0095b34c movss dword ptr [ebp - 0xfc], xmm0
0095b354 call 0x411fe0
0095b359 movss dword ptr [ebp - 0xdc], xmm0
0095b361 movss xmm0, dword ptr [ebp - 0xfc]
0095b369 call 0x412010
0095b36e movss xmm4, dword ptr [ebp - 0xdc]
0095b376 movaps xmm2, xmm0
0095b379 movss xmm0, dword ptr [ebp - 0xc8]
0095b381 movaps xmm3, xmm4
0095b384 movss xmm1, dword ptr [ebp - 0xb8]
0095b38c mulss xmm4, dword ptr [ebp - 0xb8]
0095b394 mulss xmm3, xmm0
0095b398 mulss xmm1, xmm2
0095b39c mulss xmm0, xmm2
0095b3a0 subss xmm3, xmm1
0095b3a4 addss xmm4, xmm0
0095b3a8 movss xmm0, dword ptr [ebp - 0x104]
0095b3b0 movaps xmm1, xmm0
0095b3b3 mulss xmm1, xmm3
0095b3b7 mulss xmm0, xmm4
0095b3bb movss dword ptr [ebp - 0xac], xmm1
0095b3c3 movss dword ptr [ebp - 0xbc], xmm0
0095b3cb movss dword ptr [ebp - 0xfc], xmm0
0095b3d3 call 0x6c3d90
0095b3d8 movd xmm0, eax
0095b3dc cvtdq2pd xmm0, xmm0
0095b3e0 shr eax, 0x1f
0095b3e3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b3ec cvtpd2ps xmm0, xmm0
0095b3f0 mulss xmm0, dword ptr [0xb6a19c]
0095b3f8 subss xmm0, dword ptr [0xb6a480]
0095b400 mulss xmm0, dword ptr [ebp - 0xb4]
0095b408 mulss xmm0, dword ptr [0xb6a230]
0095b410 movss dword ptr [ebp - 0xfc], xmm0
0095b418 call 0x411fe0
0095b41d movss dword ptr [ebp - 0xdc], xmm0
0095b425 movss xmm0, dword ptr [ebp - 0xfc]
0095b42d call 0x412010
0095b432 movaps xmm3, xmm0
0095b435 lea eax, [ebp - 0x154]
0095b43b movss xmm0, dword ptr [ebp - 0xdc]
0095b443 movaps xmm1, xmm3
0095b446 mulss xmm3, dword ptr [ebp - 0xac]
0095b44e movaps xmm2, xmm0
0095b451 sub esp, 0xc
0095b454 mov ecx, esi
0095b456 mulss xmm0, dword ptr [ebp - 0xbc]
0095b45e mulss xmm2, dword ptr [ebp - 0xac]
0095b466 mulss xmm1, dword ptr [ebp - 0xbc]
0095b46e addss xmm3, xmm0
0095b472 movss xmm0, dword ptr [ebp - 0xd8]
0095b47a movss dword ptr [esp + 8], xmm0
0095b480 movss xmm0, dword ptr [ebp - 0xb0]
0095b488 subss xmm2, xmm1
0095b48c movss dword ptr [esp + 4], xmm0
0095b492 push 6
0095b494 push eax
0095b495 lea eax, [ebp - 0xec]
0095b49b movss dword ptr [ebp - 0x150], xmm3
0095b4a3 push eax
0095b4a4 movss dword ptr [ebp - 0x154], xmm2
0095b4ac call 0x9453d0
0095b4b1 sub edi, 1
0095b4b4 jne 0x95b317
0095b4ba jmp 0x95b5b3
0095b4bf nop 
0095b4c0 call 0x6c3d90
0095b4c5 movd xmm0, eax
0095b4c9 cvtdq2pd xmm0, xmm0
0095b4cd shr eax, 0x1f
0095b4d0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b4d9 cvtpd2ps xmm0, xmm0
0095b4dd mulss xmm0, dword ptr [0xb6a19c]
0095b4e5 mulss xmm0, dword ptr [0xb6ac40]
0095b4ed mulss xmm0, dword ptr [0xb6a230]
0095b4f5 movss dword ptr [ebp - 0xfc], xmm0
0095b4fd call 0x411fe0
0095b502 movss dword ptr [ebp - 0xdc], xmm0
0095b50a movss xmm0, dword ptr [ebp - 0xfc]
0095b512 call 0x412010
0095b517 movss xmm4, dword ptr [ebp - 0xdc]
0095b51f lea eax, [ebp - 0x154]
0095b525 movss xmm1, dword ptr [ebp - 0xb8]
0095b52d movaps xmm2, xmm0
0095b530 movss xmm0, dword ptr [ebp - 0xc8]
0095b538 movaps xmm3, xmm4
0095b53b mulss xmm4, dword ptr [ebp - 0xb8]
0095b543 sub esp, 0xc
0095b546 mov ecx, esi
0095b548 mulss xmm3, xmm0
0095b54c mulss xmm0, xmm2
0095b550 mulss xmm1, xmm2
0095b554 addss xmm4, xmm0
0095b558 movss xmm0, dword ptr [ebp - 0x104]
0095b560 subss xmm3, xmm1
0095b564 movaps xmm1, xmm0
0095b567 mulss xmm0, xmm4
0095b56b mulss xmm1, xmm3
0095b56f movss dword ptr [ebp - 0x150], xmm0
0095b577 movss xmm0, dword ptr [ebp - 0xd8]
0095b57f movss dword ptr [esp + 8], xmm0
0095b585 movss xmm0, dword ptr [ebp - 0xb0]
0095b58d movss dword ptr [esp + 4], xmm0
0095b593 push 6
0095b595 push eax
0095b596 lea eax, [ebp - 0xec]
0095b59c movss dword ptr [ebp - 0x154], xmm1
0095b5a4 push eax
0095b5a5 call 0x9453d0
0095b5aa sub edi, 1
0095b5ad jne 0x95b4c0
0095b5b3 mov edi, dword ptr [ebp - 0xc0]
0095b5b9 test di, di
0095b5bc je 0x95b644
0095b5c2 call 0x6c3d90
0095b5c7 xorps xmm0, xmm0
0095b5ca movss xmm1, dword ptr [ebp - 0xb8]
0095b5d2 xorps xmm2, xmm2
0095b5d5 cvtsi2sd xmm0, eax
0095b5d9 shr eax, 0x1f
0095b5dc addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b5e5 movsx eax, di
0095b5e8 cvtpd2ps xmm3, xmm0
0095b5ec movss xmm0, dword ptr [ebp - 0xec]
0095b5f4 mulss xmm3, dword ptr [0xb6a19c]
0095b5fc cvtsi2ss xmm2, eax
0095b600 mulss xmm3, dword ptr [0xb6a350]
0095b608 mulss xmm1, xmm2
0095b60c addss xmm3, dword ptr [0xb6a3b0]
0095b614 mulss xmm1, xmm3
0095b618 subss xmm0, xmm1
0095b61c movss dword ptr [ebp - 0xec], xmm0
0095b624 movss xmm0, dword ptr [ebp - 0xc8]
0095b62c mulss xmm0, xmm2
0095b630 mulss xmm0, xmm3
0095b634 addss xmm0, dword ptr [ebp - 0xe8]
0095b63c movss dword ptr [ebp - 0xe8], xmm0
0095b644 mov eax, dword ptr [ebp - 0x10c]
0095b64a xor ecx, ecx
0095b64c movsx edi, ax
0095b64f mov dword ptr [ebp - 0xa4], ecx
0095b655 test edi, edi
0095b657 jle 0x95b8cc
0095b65d movss xmm0, dword ptr [ebp - 0xb4]
0095b665 ucomiss xmm0, dword ptr [0xb6a18c]
0095b66c movups xmm0, xmmword ptr [ebp - 0x24]
0095b670 movups xmm1, xmmword ptr [ebp - 0x34]
0095b674 lahf 
0095b675 test ah, 0x44
0095b678 jnp 0x95b7e9
0095b67e nop 
0095b680 mov edx, dword ptr [ebp - 0x14]
0095b683 sub esp, 0x24
0095b686 mov eax, esp
0095b688 push ecx
0095b689 movups xmmword ptr [eax], xmm1
0095b68c movups xmmword ptr [eax + 0x10], xmm0
0095b690 mov dword ptr [eax + 0x20], edx
0095b693 lea eax, [ebp - 0x1a4]
0095b699 movss xmm0, dword ptr [ebp - 0x104]
0095b6a1 movss dword ptr [esp], xmm0
0095b6a6 push dword ptr [ebp - 0x148]
0095b6ac push dword ptr [ebp - 0x14c]
0095b6b2 push dword ptr [esi + 0x2c]
0095b6b5 push ecx
0095b6b6 push eax
0095b6b7 call 0x943a80
0095b6bc call 0x6c3d90
0095b6c1 movd xmm0, eax
0095b6c5 cvtdq2pd xmm0, xmm0
0095b6c9 shr eax, 0x1f
0095b6cc addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095b6d5 cvtpd2ps xmm0, xmm0
0095b6d9 mulss xmm0, dword ptr [0xb6a19c]
0095b6e1 subss xmm0, dword ptr [0xb6a480]
0095b6e9 mulss xmm0, dword ptr [ebp - 0xb4]
0095b6f1 mulss xmm0, dword ptr [0xb6a230]
0095b6f9 movss dword ptr [ebp - 0xfc], xmm0
0095b701 call 0x411fe0
0095b706 movss dword ptr [ebp - 0xdc], xmm0
0095b70e movss xmm0, dword ptr [ebp - 0xfc]
0095b716 call 0x412010
0095b71b movss xmm2, dword ptr [ebp - 0x198]
0095b723 lea eax, [ebp - 0x15c]
0095b729 movss xmm5, dword ptr [ebp - 0x19c]
0095b731 movaps xmm1, xmm2
0095b734 mulss xmm2, dword ptr [ebp - 0xdc]
0095b73c movaps xmm3, xmm5
0095b73f sub esp, 0xc
0095b742 mov ecx, esi
0095b744 mulss xmm3, dword ptr [ebp - 0xdc]
0095b74c mulss xmm1, xmm0
0095b750 mulss xmm5, xmm0
0095b754 movss xmm0, dword ptr [ebp - 0xe8]
0095b75c subss xmm3, xmm1
0095b760 addss xmm0, dword ptr [ebp - 0x1a0]
0095b768 movss xmm1, dword ptr [ebp - 0xec]
0095b770 addss xmm5, xmm2
0095b774 addss xmm1, dword ptr [ebp - 0x1a4]
0095b77c movss dword ptr [ebp - 0x15c], xmm3
0095b784 movss dword ptr [ebp - 0x160], xmm0
0095b78c movss xmm0, dword ptr [ebp - 0xd8]
0095b794 movss dword ptr [esp + 8], xmm0
0095b79a movss xmm0, dword ptr [ebp - 0xb0]
0095b7a2 movss dword ptr [esp + 4], xmm0
0095b7a8 push 0
0095b7aa push eax
0095b7ab lea eax, [ebp - 0x164]
0095b7b1 movss dword ptr [ebp - 0x158], xmm5
0095b7b9 push eax
0095b7ba movss dword ptr [ebp - 0x164], xmm1
0095b7c2 call 0x9453d0
0095b7c7 mov ecx, dword ptr [ebp - 0xa4]
0095b7cd movups xmm0, xmmword ptr [ebp - 0x24]
0095b7d1 inc ecx
0095b7d2 mov dword ptr [ebp - 0xa4], ecx
0095b7d8 movups xmm1, xmmword ptr [ebp - 0x34]
0095b7dc cmp ecx, edi
0095b7de jl 0x95b680
0095b7e4 jmp 0x95b8cc
0095b7e9 xor edi, edi
0095b7eb nop dword ptr [eax + eax]
0095b7f0 mov ecx, dword ptr [ebp - 0x14]
0095b7f3 sub esp, 0x24
0095b7f6 mov eax, esp
0095b7f8 push ecx
0095b7f9 movups xmmword ptr [eax], xmm1
0095b7fc movups xmmword ptr [eax + 0x10], xmm0
0095b800 mov dword ptr [eax + 0x20], ecx
0095b803 lea eax, [ebp - 0x1a4]
0095b809 movss xmm0, dword ptr [ebp - 0x104]
0095b811 movss dword ptr [esp], xmm0
0095b816 push dword ptr [ebp - 0x148]
0095b81c push dword ptr [ebp - 0x14c]
0095b822 push dword ptr [esi + 0x2c]
0095b825 push edi
0095b826 push eax
0095b827 call 0x943a80
0095b82c movss xmm0, dword ptr [ebp - 0x19c]
0095b834 lea eax, [ebp - 0x15c]
0095b83a movss xmm1, dword ptr [ebp - 0xec]
0095b842 sub esp, 0xc
0095b845 addss xmm1, dword ptr [ebp - 0x1a4]
0095b84d movss dword ptr [ebp - 0x15c], xmm0
0095b855 mov ecx, esi
0095b857 movss xmm0, dword ptr [ebp - 0x198]
0095b85f movss dword ptr [ebp - 0x158], xmm0
0095b867 movss xmm0, dword ptr [ebp - 0xe8]
0095b86f addss xmm0, dword ptr [ebp - 0x1a0]
0095b877 movss dword ptr [ebp - 0x164], xmm1
0095b87f movss dword ptr [ebp - 0x160], xmm0
0095b887 movss xmm0, dword ptr [ebp - 0xd8]
0095b88f movss dword ptr [esp + 8], xmm0
0095b895 movss xmm0, dword ptr [ebp - 0xb0]
0095b89d movss dword ptr [esp + 4], xmm0
0095b8a3 push 0
0095b8a5 push eax
0095b8a6 lea eax, [ebp - 0x164]
0095b8ac push eax
0095b8ad call 0x9453d0
0095b8b2 mov ecx, dword ptr [ebp - 0x10c]
0095b8b8 inc edi
0095b8b9 movups xmm0, xmmword ptr [ebp - 0x24]
0095b8bd movsx eax, cx
0095b8c0 movups xmm1, xmmword ptr [ebp - 0x34]
0095b8c4 cmp edi, eax
0095b8c6 jl 0x95b7f0
0095b8cc mov edi, dword ptr [ebp - 0xcc]
0095b8d2 test edi, edi
0095b8d4 je 0x95c1e5
0095b8da mov ecx, edi
0095b8dc call 0x79cb80
0095b8e1 cmp eax, -1
0095b8e4 je 0x95c1e5
0095b8ea call 0x6c3d90
0095b8ef movss xmm1, dword ptr [ebp - 0xc8]
0095b8f7 mov esi, eax
0095b8f9 movss xmm0, dword ptr [ebp - 0xb8]
0095b901 mulss xmm0, xmm0
0095b905 mulss xmm1, xmm1
0095b909 addss xmm0, xmm1
0095b90d call 0x4228c0
0095b912 comiss xmm0, dword ptr [0xb6a18c]
0095b919 movss xmm2, dword ptr [ebp - 0xb8]
0095b921 jbe 0x95b941
0095b923 movss xmm1, dword ptr [0xb6a8cc]
0095b92b divss xmm1, xmm0
0095b92f movss xmm0, dword ptr [ebp - 0xc8]
0095b937 mulss xmm0, xmm1
0095b93b mulss xmm2, xmm1
0095b93f jmp 0x95b949
0095b941 movss xmm0, dword ptr [ebp - 0xc8]
0095b949 movss xmm1, dword ptr [ebp - 0xec]
0095b951 lea eax, [ebp - 0x1b8]
0095b957 mov ecx, dword ptr [0xbfd65c]
0095b95d addss xmm1, xmm0
0095b961 movss xmm0, dword ptr [ebp - 0xe8]
0095b969 push esi
0095b96a push 0
0095b96c push 0
0095b96e push 0xc02fec
0095b973 addss xmm0, xmm2
0095b977 movss dword ptr [ebp - 0x1b8], xmm1
0095b97f push eax
0095b980 push 0xf
0095b982 push 0x3e8
0095b987 movss dword ptr [ebp - 0x1b4], xmm0
0095b98f call 0x422e20
0095b994 mov esi, eax
0095b996 mov dword ptr [ebp - 0x28], 0
0095b99d push 0x29
0095b99f push 0xb5d1bc
0095b9a4 lea ecx, [ebp - 0x28]
0095b9a7 mov dword ptr [ebp - 0xfc], esi
0095b9ad mov dword ptr [esi + 0x3ac], 2
0095b9b7 mov dword ptr [esi + 0x3b0], 2
0095b9c1 mov dword ptr [ebp - 0x18], 0
0095b9c8 mov dword ptr [ebp - 0x14], 0xf
0095b9cf mov byte ptr [ebp - 0x28], 0
0095b9d3 call 0x407c80
0095b9d8 push 1
0095b9da lea eax, [ebp - 0x28]
0095b9dd mov dword ptr [ebp - 4], 0
0095b9e4 lea edi, [esi + 0x3c]
0095b9e7 push eax
0095b9e8 mov ecx, edi
0095b9ea call 0x407160
0095b9ef mov dword ptr [ebp - 4], 0xffffffff
0095b9f6 mov edx, dword ptr [ebp - 0x14]
0095b9f9 cmp edx, 0x10
0095b9fc jb 0x95ba2a
0095b9fe mov ecx, dword ptr [ebp - 0x28]
0095ba01 inc edx
0095ba02 mov eax, ecx
0095ba04 cmp edx, 0x1000
0095ba0a jb 0x95ba20
0095ba0c mov ecx, dword ptr [ecx - 4]
0095ba0f add edx, 0x23
0095ba12 sub eax, ecx
0095ba14 add eax, -4
0095ba17 cmp eax, 0x1f
0095ba1a ja 0x95c31d
0095ba20 push edx
0095ba21 push ecx
0095ba22 call 0x9eb08e
0095ba27 add esp, 8
0095ba2a mov dword ptr [esi + 0x2a4], 0
0095ba34 mov dword ptr [esi + 0x2a8], 0xc1a00000
0095ba3e call 0x6c3d90
0095ba43 and eax, 3
0095ba46 mov byte ptr [ebp - 0xf7], 0
0095ba4d add eax, 0x30
0095ba50 mov ecx, edi
0095ba52 mov byte ptr [ebp - 0xf8], al
0095ba58 lea eax, [ebp - 0xf8]
0095ba5e push 1
0095ba60 push eax
0095ba61 call 0x405740
0095ba66 test al, al
0095ba68 je 0x95ba7c
0095ba6a lea ecx, [edi + 0x30]
0095ba6d call 0x405330
0095ba72 mov esi, dword ptr [ebp - 0xfc]
0095ba78 mov byte ptr [edi + 0x44], 1
0095ba7c call 0x6c3d90
0095ba81 and eax, 1
0095ba84 push 0
0095ba86 lea eax, [eax*2 - 1]
0095ba8d push eax
0095ba8e push ecx
0095ba8f mov ecx, dword ptr [ebp - 0xcc]
0095ba95 lea eax, [ebp - 0x9c]
0095ba9b mov dword ptr [esp], 0x3f800000
0095baa2 push 1
0095baa4 push eax
0095baa5 call 0x7836a0
0095baaa movss xmm1, dword ptr [ebp - 0x50]
0095baaf movaps xmm0, xmm1
0095bab2 mulss xmm1, dword ptr [0xbc7a2c]
0095baba mulss xmm0, dword ptr [0xbc7a28]
0095bac2 movss dword ptr [esi + 0xdc], xmm1
0095baca movss dword ptr [esi + 0xd8], xmm0
0095bad2 movss xmm2, dword ptr [ebp - 0x78]
0095bad7 ucomiss xmm2, dword ptr [0xb6a18c]
0095bade movss xmm3, dword ptr [ebp - 0x94]
0095bae6 movss xmm4, dword ptr [ebp - 0x90]
0095baee movss xmm5, dword ptr [ebp - 0x8c]
0095baf6 movss xmm6, dword ptr [ebp - 0x88]
0095bafe lahf 
0095baff test ah, 0x44
0095bb02 jnp 0x95bb6f
0095bb04 movaps xmm0, xmm3
0095bb07 movaps xmm1, xmm4
0095bb0a mulss xmm0, dword ptr [0xb6a370]
0095bb12 mulss xmm1, dword ptr [0xb6a52c]
0095bb1a addss xmm1, xmm0
0095bb1e movaps xmm0, xmm5
0095bb21 mulss xmm0, dword ptr [0xb6a298]
0095bb29 addss xmm1, xmm0
0095bb2d movss xmm0, dword ptr [ebp - 0x84]
0095bb35 mulss xmm0, xmm1
0095bb39 subss xmm0, xmm3
0095bb3d mulss xmm0, xmm2
0095bb41 addss xmm3, xmm0
0095bb45 movss xmm0, dword ptr [ebp - 0x80]
0095bb4a mulss xmm0, xmm1
0095bb4e subss xmm0, xmm4
0095bb52 mulss xmm0, xmm2
0095bb56 addss xmm4, xmm0
0095bb5a movss xmm0, dword ptr [ebp - 0x7c]
0095bb5f mulss xmm0, xmm1
0095bb63 subss xmm0, xmm5
0095bb67 mulss xmm0, xmm2
0095bb6b addss xmm5, xmm0
0095bb6f movss xmm2, dword ptr [ebp - 0x74]
0095bb74 lea ecx, [esi + 0xe4]
0095bb7a movss xmm1, dword ptr [ebp - 0x70]
0095bb7f addss xmm2, xmm3
0095bb83 movss xmm0, dword ptr [ebp - 0x6c]
0095bb88 addss xmm1, xmm4
0095bb8c addss xmm0, xmm5
0095bb90 mov dword ptr [ebp - 0x1e4], 0
0095bb9a lea eax, [ebp - 0x204]
0095bba0 mov dword ptr [ebp - 0x1e0], 0
0095bbaa mov dword ptr [ebp - 0x1dc], 0
0095bbb4 xorps xmm3, xmm3
0095bbb7 movss dword ptr [ebp - 0x204], xmm2
0095bbbf movss dword ptr [ebp - 0x200], xmm1
0095bbc7 movss dword ptr [ebp - 0x1fc], xmm0
0095bbcf movss dword ptr [ebp - 0x1f8], xmm6
0095bbd7 cmp ecx, eax
0095bbd9 je 0x95bbff
0095bbdb movups xmm0, xmmword ptr [ebp - 0x204]
0095bbe2 mov eax, dword ptr [ebp - 0x1dc]
0095bbe8 movups xmmword ptr [ecx + 0x10], xmm3
0095bbec movups xmmword ptr [ecx], xmm0
0095bbef movq xmm0, qword ptr [ebp - 0x1e4]
0095bbf7 movq qword ptr [ecx + 0x20], xmm0
0095bbfc mov dword ptr [ecx + 0x28], eax
0095bbff movss xmm1, dword ptr [ebp - 0xc8]
0095bc07 movss xmm0, dword ptr [ebp - 0xb8]
0095bc0f call 0x447a80
0095bc14 cmp dword ptr [edi + 0x80], 0
0095bc1b movss dword ptr [ebp - 0xfc], xmm0
0095bc23 jg 0x95bc49
0095bc25 cmp dword ptr [edi + 0x14], 0x10
0095bc29 mov eax, edi
0095bc2b jb 0x95bc2f
0095bc2d mov eax, dword ptr [edi]
0095bc2f push 0
0095bc31 push eax
0095bc32 push 0xa0830c
0095bc37 push 3
0095bc39 call 0x95e330
0095bc3e movss xmm0, dword ptr [ebp - 0xfc]
0095bc46 add esp, 0x10
0095bc49 mov eax, dword ptr [edi + 0x7c]
0095bc4c lea ecx, [ebp - 0x1d8]
0095bc52 mulss xmm0, dword ptr [0xb6aa84]
0095bc5a push 2
0095bc5c movss dword ptr [eax + 0x3c], xmm0
0095bc61 call 0x95ed30
0095bc66 cmp dword ptr [edi + 0x80], 0
0095bc6d jg 0x95bc8b
0095bc6f cmp dword ptr [edi + 0x14], 0x10
0095bc73 mov eax, edi
0095bc75 jb 0x95bc79
0095bc77 mov eax, dword ptr [edi]
0095bc79 push 0
0095bc7b push eax
0095bc7c push 0xa0830c
0095bc81 push 3
0095bc83 call 0x95e330
0095bc88 add esp, 0x10
0095bc8b mov ecx, dword ptr [edi + 0x7c]
0095bc8e mov eax, dword ptr [ebp - 0x1d8]
0095bc94 mov dword ptr [ecx + 0x78], eax
0095bc97 mov eax, dword ptr [ebp - 0x1d4]
0095bc9d mov dword ptr [ecx + 0x7c], eax
0095bca0 mov eax, dword ptr [ebp - 0x1d0]
0095bca6 mov dword ptr [ecx + 0x80], eax
0095bcac mov eax, dword ptr [ebp - 0x1cc]
0095bcb2 mov dword ptr [ecx + 0x84], eax
0095bcb8 mov ecx, esi
0095bcba mov eax, dword ptr [esi]
0095bcbc call dword ptr [eax + 0xc]
0095bcbf call 0x6c3d90
0095bcc4 movd xmm0, eax
0095bcc8 cvtdq2pd xmm0, xmm0
0095bccc shr eax, 0x1f
0095bccf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095bcd8 cvtpd2ps xmm0, xmm0
0095bcdc mulss xmm0, dword ptr [0xb6a19c]
0095bce4 mulss xmm0, dword ptr [0xb6a350]
0095bcec addss xmm0, dword ptr [0xb6a2cc]
0095bcf4 xorps xmm0, xmmword ptr [0xb6c9b0]
0095bcfb movss dword ptr [ebp - 0xac], xmm0
0095bd03 call 0x6c3d90
0095bd08 mov esi, eax
0095bd0a call 0x6c3d90
0095bd0f movd xmm0, eax
0095bd13 cvtdq2pd xmm0, xmm0
0095bd17 shr eax, 0x1f
0095bd1a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095bd23 cvtpd2ps xmm0, xmm0
0095bd27 mulss xmm0, dword ptr [0xb6a19c]
0095bd2f mulss xmm0, dword ptr [0xb6a9c8]
0095bd37 subss xmm0, dword ptr [0xb6a974]
0095bd3f mulss xmm0, dword ptr [0xb6a230]
0095bd47 movss dword ptr [ebp - 0xfc], xmm0
0095bd4f call 0x411fe0
0095bd54 movss dword ptr [ebp - 0xdc], xmm0
0095bd5c movss xmm0, dword ptr [ebp - 0xfc]
0095bd64 call 0x412010
0095bd69 movss xmm3, dword ptr [ebp - 0xdc]
0095bd71 lea eax, [ebp - 0x144]
0095bd77 mov ecx, dword ptr [0xbfd65c]
0095bd7d movaps xmm1, xmm0
0095bd80 mulss xmm1, dword ptr [ebp - 0xb8]
0095bd88 movaps xmm2, xmm3
0095bd8b push esi
0095bd8c mulss xmm0, dword ptr [ebp - 0xc8]
0095bd94 push 0
0095bd96 mulss xmm2, dword ptr [ebp - 0xc8]
0095bd9e push 0
0095bda0 mulss xmm3, dword ptr [ebp - 0xb8]
0095bda8 push eax
0095bda9 subss xmm2, xmm1
0095bdad movss xmm1, dword ptr [ebp - 0xac]
0095bdb5 lea eax, [ebp - 0xec]
0095bdbb addss xmm3, xmm0
0095bdbf movaps xmm0, xmm1
0095bdc2 push eax
0095bdc3 push 0x1b
0095bdc5 mulss xmm0, xmm2
0095bdc9 push 0x3e8
0095bdce mulss xmm1, xmm3
0095bdd2 movss dword ptr [ebp - 0x144], xmm0
0095bdda movss dword ptr [ebp - 0x140], xmm1
0095bde2 call 0x422e20
0095bde7 push 0x23
0095bde9 mov dword ptr [ebp - 0x28], 0
0095bdf0 lea ecx, [ebp - 0x28]
0095bdf3 push 0xb5d1e8
0095bdf8 mov edi, eax
0095bdfa mov dword ptr [ebp - 0x18], 0
0095be01 mov dword ptr [ebp - 0x14], 0xf
0095be08 mov byte ptr [ebp - 0x28], 0
0095be0c call 0x407c80
0095be11 push 1
0095be13 lea eax, [ebp - 0x28]
0095be16 mov dword ptr [ebp - 4], 1
0095be1d push eax
0095be1e lea ecx, [edi + 0x3c]
0095be21 call 0x407160
0095be26 mov dword ptr [ebp - 4], 0xffffffff
0095be2d mov edx, dword ptr [ebp - 0x14]
0095be30 cmp edx, 0x10
0095be33 jb 0x95be61
0095be35 mov ecx, dword ptr [ebp - 0x28]
0095be38 inc edx
0095be39 mov eax, ecx
0095be3b cmp edx, 0x1000
0095be41 jb 0x95be57
0095be43 mov ecx, dword ptr [ecx - 4]
0095be46 add edx, 0x23
0095be49 sub eax, ecx
0095be4b add eax, -4
0095be4e cmp eax, 0x1f
0095be51 ja 0x95c31d
0095be57 push edx
0095be58 push ecx
0095be59 call 0x9eb08e
0095be5e add esp, 8
0095be61 push 1
0095be63 push 0xb44ed4
0095be68 lea ecx, [edi + 0x3c]
0095be6b call 0x405740
0095be70 test al, al
0095be72 je 0x95be83
0095be74 lea ecx, [edi + 0x6c]
0095be77 call 0x405330
0095be7c mov byte ptr [edi + 0x80], 1
0095be83 call 0x6c3d90
0095be88 movd xmm0, eax
0095be8c cvtdq2pd xmm0, xmm0
0095be90 shr eax, 0x1f
0095be93 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095be9c cvtpd2ps xmm0, xmm0
0095bea0 mulss xmm0, dword ptr [0xb6a19c]
0095bea8 mulss xmm0, dword ptr [0xb6a4c4]
0095beb0 addss xmm0, dword ptr [0xb6a560]
0095beb8 movss dword ptr [edi + 0x140], xmm0
0095bec0 call 0x6c3d90
0095bec5 mov ecx, edi
0095bec7 movd xmm0, eax
0095becb cvtdq2pd xmm0, xmm0
0095becf shr eax, 0x1f
0095bed2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095bedb mov eax, dword ptr [edi]
0095bedd cvtpd2ps xmm1, xmm0
0095bee1 movss xmm0, dword ptr [0xb6aeac]
0095bee9 mulss xmm1, dword ptr [0xb6a19c]
0095bef1 mulss xmm1, dword ptr [0xb6a9b0]
0095bef9 subss xmm0, xmm1
0095befd movss dword ptr [edi + 0x364], xmm0
0095bf05 call dword ptr [eax + 0xc]
0095bf08 mov edi, dword ptr [ebp - 0xcc]
0095bf0e mov ecx, edi
0095bf10 call 0x79cb80
0095bf15 add eax, -2
0095bf18 cmp eax, 3
0095bf1b ja 0x95c11c
0095bf21 jmp dword ptr [eax*4 + 0x95c758]
0095bf28 mov esi, dword ptr [0xbfd680]
0095bf2e lea ecx, [ebp - 0xa4]
0095bf34 mov dword ptr [ebp - 0xa4], 0x33b
0095bf3e call 0x8b1340
0095bf43 sub esp, 8
0095bf46 mov dword ptr [esp + 4], 0
0095bf4e mov dword ptr [esp], 0x3f800000
0095bf55 push 0
0095bf57 push 2
0095bf59 push ecx
0095bf5a mov dword ptr [esp], 0x3f800000
0095bf61 lea ecx, [esi + 0x29de0]
0095bf67 push dword ptr [ebp - 0xa4]
0095bf6d call 0x888de0
0095bf72 push 0x10
0095bf74 jmp 0x95c1d4
0095bf79 mov esi, dword ptr [0xbfd680]
0095bf7f lea ecx, [ebp - 0xa4]
0095bf85 mov dword ptr [ebp - 0xa4], 0x340
0095bf8f call 0x8b1340
0095bf94 sub esp, 8
0095bf97 mov dword ptr [esp + 4], 0
0095bf9f mov dword ptr [esp], 0x3f800000
0095bfa6 push 0
0095bfa8 push 2
0095bfaa push ecx
0095bfab mov dword ptr [esp], 0x3f800000
0095bfb2 lea ecx, [esi + 0x29de0]
0095bfb8 push dword ptr [ebp - 0xa4]
0095bfbe call 0x888de0
0095bfc3 push 0xa
0095bfc5 jmp 0x95c1d4
0095bfca mov esi, dword ptr [0xbfd680]
0095bfd0 lea ecx, [ebp - 0xa4]
0095bfd6 mov dword ptr [ebp - 0xa4], 0x33e
0095bfe0 call 0x8b1340
0095bfe5 sub esp, 8
0095bfe8 mov dword ptr [esp + 4], 0
0095bff0 mov dword ptr [esp], 0x3f800000
0095bff7 push 0
0095bff9 push 2
0095bffb push ecx
0095bffc mov dword ptr [esp], 0x3f800000
0095c003 lea ecx, [esi + 0x29de0]
0095c009 push dword ptr [ebp - 0xa4]
0095c00f call 0x888de0
0095c014 mov ecx, dword ptr [0xbfd65c]
0095c01a push 0xa
0095c01c call 0x6d5ad0
0095c021 movss xmm1, dword ptr [ebp - 0xc8]
0095c029 xorps xmm1, xmmword ptr [0xb6c9b0]
0095c030 mulss xmm1, dword ptr [0xb6a234]
0095c038 movss xmm2, dword ptr [ebp - 0xb8]
0095c040 xorps xmm2, xmmword ptr [0xb6c9b0]
0095c047 mulss xmm2, dword ptr [0xb6a234]
0095c04f movaps xmm0, xmm1
0095c052 mulss xmm0, xmm1
0095c056 movss dword ptr [ebp - 0xc8], xmm1
0095c05e movss dword ptr [ebp - 0xfc], xmm1
0095c066 movaps xmm1, xmm2
0095c069 mulss xmm1, xmm2
0095c06d movss dword ptr [ebp - 0xb8], xmm2
0095c075 movss dword ptr [ebp - 0xdc], xmm2
0095c07d addss xmm0, xmm1
0095c081 call 0x4228c0
0095c086 comiss xmm0, dword ptr [0xb6a18c]
0095c08d movss xmm1, dword ptr [ebp - 0xc8]
0095c095 jbe 0x95c0b4
0095c097 movss xmm3, dword ptr [0xb6a614]
0095c09f divss xmm3, xmm0
0095c0a3 movaps xmm2, xmm3
0095c0a6 mulss xmm3, dword ptr [ebp - 0xb8]
0095c0ae mulss xmm2, xmm1
0095c0b2 jmp 0x95c0c4
0095c0b4 movss xmm2, dword ptr [ebp - 0xfc]
0095c0bc movss xmm3, dword ptr [ebp - 0xdc]
0095c0c4 movss xmm0, dword ptr [edi + 0x2b8]
0095c0cc mulss xmm3, dword ptr [edi + 0x2bc]
0095c0d4 mulss xmm2, xmm0
0095c0d8 addss xmm2, xmm3
0095c0dc xorps xmm2, xmmword ptr [0xb6c9b0]
0095c0e3 maxss xmm2, dword ptr [0xb6a350]
0095c0eb mulss xmm1, xmm2
0095c0ef addss xmm1, xmm0
0095c0f3 movss xmm0, dword ptr [ebp - 0xb8]
0095c0fb mulss xmm0, xmm2
0095c0ff addss xmm0, dword ptr [edi + 0x2bc]
0095c107 movss dword ptr [edi + 0x2b8], xmm1
0095c10f movss dword ptr [edi + 0x2bc], xmm0
0095c117 jmp 0x95c1df
0095c11c movss xmm0, dword ptr [ebp - 0x50]
0095c121 lea ecx, [ebp - 0xa4]
0095c127 movss xmm1, dword ptr [0xb6a53c]
0095c12f comiss xmm1, xmm0
0095c132 mov esi, dword ptr [0xbfd680]
0095c138 jbe 0x95c17c
0095c13a mov dword ptr [ebp - 0xa4], 0x339
0095c144 call 0x8b1340
0095c149 sub esp, 8
0095c14c mov dword ptr [esp + 4], 0
0095c154 mov dword ptr [esp], 0x3f800000
0095c15b push 0
0095c15d push 2
0095c15f push ecx
0095c160 mov dword ptr [esp], 0x3f800000
0095c167 lea ecx, [esi + 0x29de0]
0095c16d push dword ptr [ebp - 0xa4]
0095c173 call 0x888de0
0095c178 push 3
0095c17a jmp 0x95c1d4
0095c17c comiss xmm0, dword ptr [0xb6a740]
0095c183 jbe 0x95c194
0095c185 mov dword ptr [ebp - 0xa4], 0x33a
0095c18f jmp 0x95bf8f
0095c194 mov dword ptr [ebp - 0xa4], 0x338
0095c19e call 0x8b1340
0095c1a3 sub esp, 8
0095c1a6 mov dword ptr [esp + 4], 0
0095c1ae mov dword ptr [esp], 0x3f800000
0095c1b5 push 0
0095c1b7 push 2
0095c1b9 push ecx
0095c1ba mov dword ptr [esp], 0x3f800000
0095c1c1 lea ecx, [esi + 0x29de0]
0095c1c7 push dword ptr [ebp - 0xa4]
0095c1cd call 0x888de0
0095c1d2 push 6
0095c1d4 mov ecx, dword ptr [0xbfd65c]
0095c1da call 0x6d5ad0
0095c1df mov esi, dword ptr [ebp - 0x108]
0095c1e5 movss xmm0, dword ptr [ebp - 0x12c]
0095c1ed movss xmm3, dword ptr [0xb6a614]
0095c1f5 movss xmm1, dword ptr [ebp - 0xd8]
0095c1fd addss xmm0, xmm3
0095c201 mov eax, dword ptr [ebp - 0x134]
0095c207 subss xmm1, xmm0
0095c20b movss dword ptr [ebp - 0xd8], xmm1
0095c213 test eax, eax
0095c215 jne 0x959e43
0095c21b mov ecx, dword ptr [ebp - 0xe4]
0095c221 mov edx, dword ptr [ebp - 0x120]
0095c227 mov eax, dword ptr [ebp - 0xc4]
0095c22d inc eax
0095c22e mov dword ptr [ebp - 0xc4], eax
0095c234 cmp eax, ecx
0095c236 jl 0x959bea
0095c23c cmp byte ptr [ebp - 0x124], 0
0095c243 je 0x95c448
0095c249 cmp byte ptr [ebp - 0x9d], 0
0095c250 je 0x95c323
0095c256 mov eax, dword ptr [esi]
0095c258 mov ecx, esi
0095c25a mov eax, dword ptr [eax + 0x18]
0095c25d call eax
0095c25f fadd dword ptr [0xb6a614]
0095c265 movss xmm0, dword ptr [esi + 0x14]
0095c26a xorps xmm3, xmm3
0095c26d movss xmm4, dword ptr [0xb6a614]
0095c275 movaps xmm2, xmm0
0095c278 fstp dword ptr [ebp - 0xc4]
0095c27e movss xmm1, dword ptr [ebp - 0xc4]
0095c286 addss xmm2, xmm4
0095c28a ucomiss xmm3, xmm1
0095c28d movss dword ptr [ebp - 0x134], xmm2
0095c295 lahf 
0095c296 test ah, 0x44
0095c299 jp 0x95c2ca
0095c29b push 0xb5d590
0095c2a0 push 3
0095c2a2 call 0x95e330
0095c2a7 movss xmm0, dword ptr [esi + 0x14]
0095c2ac add esp, 8
0095c2af movss xmm2, dword ptr [ebp - 0x134]
0095c2b7 xorps xmm3, xmm3
0095c2ba movss xmm1, dword ptr [ebp - 0xc4]
0095c2c2 movss xmm4, dword ptr [0xb6a614]
0095c2ca subss xmm1, xmm3
0095c2ce mov eax, dword ptr [esi + 4]
0095c2d1 subss xmm2, xmm3
0095c2d5 divss xmm2, xmm1
0095c2d9 movss xmm1, dword ptr [esi + 0x10]
0095c2de mulss xmm2, xmm2
0095c2e2 addss xmm1, xmm4
0095c2e6 maxss xmm1, xmm4
0095c2ea subss xmm1, xmm4
0095c2ee mulss xmm1, xmm2
0095c2f2 addss xmm1, xmm4
0095c2f6 test eax, eax
0095c2f8 je 0x95c302
0095c2fa movss xmm4, dword ptr [eax + 0x2f4]
0095c302 mulss xmm1, xmm4
0095c306 subss xmm0, xmm1
0095c30a maxss xmm0, xmm3
0095c30e movss dword ptr [esi + 0x14], xmm0
0095c313 movss dword ptr [esi + 0x44], xmm0
0095c318 jmp 0x95c703
0095c31d call dword ptr [0xa065ac]
0095c323 movss xmm0, dword ptr [esi + 0x14]
0095c328 mov eax, dword ptr [ebp - 0xcc]
0095c32e movss dword ptr [ebp - 0x134], xmm0
0095c336 test eax, eax
0095c338 je 0x95c34f
0095c33a mov edx, dword ptr [eax + 0x155c]
0095c340 lea ecx, [ebp - 0x20c]
0095c346 call 0x659400
0095c34b mov ecx, eax
0095c34d jmp 0x95c375
0095c34f movss xmm0, dword ptr [ebp - 0xd0]
0095c357 lea ecx, [ebp - 0x144]
0095c35d movss dword ptr [ebp - 0x144], xmm0
0095c365 movss xmm0, dword ptr [ebp - 0xd4]
0095c36d movss dword ptr [ebp - 0x140], xmm0
0095c375 mov eax, dword ptr [ecx]
0095c377 mov ecx, dword ptr [ecx + 4]
0095c37a mov dword ptr [ebp - 0x11c], eax
0095c380 mov eax, dword ptr [esi]
0095c382 mov dword ptr [ebp - 0x118], ecx
0095c388 mov ecx, esi
0095c38a mov eax, dword ptr [eax + 0x18]
0095c38d call eax
0095c38f movss xmm0, dword ptr [esi + 0x14]
0095c394 lea eax, [ebp - 0x11c]
0095c39a fstp dword ptr [ebp - 0xc4]
0095c3a0 movss xmm1, dword ptr [ebp - 0xc4]
0095c3a8 comiss xmm1, xmm0
0095c3ab push ecx
0095c3ac mov ecx, esi
0095c3ae jbe 0x95c41d
0095c3b0 divss xmm0, xmm1
0095c3b4 mulss xmm0, dword ptr [0xb6a9bc]
0095c3bc movss dword ptr [esp], xmm0
0095c3c1 push eax
0095c3c2 push 0
0095c3c4 push 0x255
0095c3c9 call 0x943ad0
0095c3ce mov eax, dword ptr [esi + 4]
0095c3d1 test eax, eax
0095c3d3 je 0x95c3f9
0095c3d5 movss xmm0, dword ptr [eax + 0x2f4]
0095c3dd addss xmm0, dword ptr [esi + 0x14]
0095c3e2 minss xmm0, dword ptr [ebp - 0xc4]
0095c3ea movss dword ptr [esi + 0x14], xmm0
0095c3ef movss dword ptr [esi + 0x44], xmm0
0095c3f4 jmp 0x95c703
0095c3f9 movss xmm0, dword ptr [0xb6a614]
0095c401 addss xmm0, dword ptr [esi + 0x14]
0095c406 minss xmm0, dword ptr [ebp - 0xc4]
0095c40e movss dword ptr [esi + 0x14], xmm0
0095c413 movss dword ptr [esi + 0x44], xmm0
0095c418 jmp 0x95c703
0095c41d mov dword ptr [esp], 0xbf800000
0095c424 push eax
0095c425 push 1
0095c427 push 0x255
0095c42c call 0x943ad0
0095c431 movss xmm0, dword ptr [ebp - 0x134]
0095c439 movss dword ptr [esi + 0x14], xmm0
0095c43e movss dword ptr [esi + 0x44], xmm0
0095c443 jmp 0x95c703
0095c448 test dl, dl
0095c44a je 0x95c703
0095c450 cmp byte ptr [ebp - 0x9d], 0
0095c457 je 0x95c691
0095c45d cmp byte ptr [ebp - 0xa5], 0
0095c464 movss xmm1, dword ptr [esi + 0x14]
0095c469 movss dword ptr [ebp - 0xc4], xmm1
0095c471 je 0x95c544
0095c477 mov eax, dword ptr [esi]
0095c479 mov ecx, esi
0095c47b mov eax, dword ptr [eax + 0x18]
0095c47e call eax
0095c480 movss xmm0, dword ptr [esi + 0x14]
0095c485 lea eax, [ebp - 0xf4]
0095c48b fstp dword ptr [ebp - 0xa4]
0095c491 movss xmm1, dword ptr [ebp - 0xa4]
0095c499 comiss xmm1, xmm0
0095c49c push ecx
0095c49d mov ecx, esi
0095c49f jbe 0x95c501
0095c4a1 divss xmm0, xmm1
0095c4a5 mulss xmm0, dword ptr [0xb6a9bc]
0095c4ad movss dword ptr [esp], xmm0
0095c4b2 push eax
0095c4b3 push 0
0095c4b5 push 0x45
0095c4b7 call 0x943ad0
0095c4bc mov eax, dword ptr [esi + 4]
0095c4bf test eax, eax
0095c4c1 je 0x95c4e2
0095c4c3 movss xmm1, dword ptr [eax + 0x2f4]
0095c4cb addss xmm1, dword ptr [esi + 0x14]
0095c4d0 minss xmm1, dword ptr [ebp - 0xa4]
0095c4d8 movss dword ptr [ebp - 0xc4], xmm1
0095c4e0 jmp 0x95c51a
0095c4e2 movss xmm1, dword ptr [0xb6a614]
0095c4ea addss xmm1, dword ptr [esi + 0x14]
0095c4ef minss xmm1, dword ptr [ebp - 0xa4]
0095c4f7 movss dword ptr [ebp - 0xc4], xmm1
0095c4ff jmp 0x95c51a
0095c501 mov dword ptr [esp], 0xbf800000
0095c508 push eax
0095c509 push 1
0095c50b push 0x45
0095c50d call 0x943ad0
0095c512 movss xmm1, dword ptr [ebp - 0xc4]
0095c51a push ecx
0095c51b push 1
0095c51d mov ecx, esi
0095c51f call 0x944fc0
0095c524 movss xmm5, dword ptr [ebp - 0xf0]
0095c52c movss xmm4, dword ptr [ebp - 0xf4]
0095c534 movss dword ptr [ebp - 0xd4], xmm5
0095c53c movss dword ptr [ebp - 0xd0], xmm4
0095c544 cmp byte ptr [ebp - 0x128], 0
0095c54b je 0x95c685
0095c551 mov eax, dword ptr [esi]
0095c553 mov ecx, esi
0095c555 mov eax, dword ptr [eax + 0x18]
0095c558 call eax
0095c55a movss xmm0, dword ptr [esi + 0x14]
0095c55f fstp dword ptr [ebp - 0xe4]
0095c565 movss xmm2, dword ptr [ebp - 0xe4]
0095c56d comiss xmm2, xmm0
0095c570 jbe 0x95c608
0095c576 mov eax, dword ptr [esi + 4]
0095c579 test eax, eax
0095c57b je 0x95c5db
0095c57d cmp dword ptr [eax + 0x28], 1
0095c581 lea eax, [ebp - 0xf4]
0095c587 push ecx
0095c588 mov ecx, esi
0095c58a jne 0x95c595
0095c58c mov dword ptr [esp], 0
0095c593 jmp 0x95c5a6
0095c595 divss xmm0, xmm2
0095c599 mulss xmm0, dword ptr [0xb6a9bc]
0095c5a1 movss dword ptr [esp], xmm0
0095c5a6 push eax
0095c5a7 push 0
0095c5a9 push 0x13c
0095c5ae call 0x943ad0
0095c5b3 movss xmm4, dword ptr [ebp - 0xf4]
0095c5bb movss xmm5, dword ptr [ebp - 0xf0]
0095c5c3 movss xmm2, dword ptr [ebp - 0xe4]
0095c5cb movss dword ptr [ebp - 0xd0], xmm4
0095c5d3 movss dword ptr [ebp - 0xd4], xmm5
0095c5db mov eax, dword ptr [esi + 4]
0095c5de test eax, eax
0095c5e0 je 0x95c5f5
0095c5e2 movss xmm1, dword ptr [eax + 0x2f4]
0095c5ea addss xmm1, dword ptr [esi + 0x14]
0095c5ef minss xmm1, xmm2
0095c5f3 jmp 0x95c655
0095c5f5 movss xmm1, dword ptr [0xb6a614]
0095c5fd addss xmm1, dword ptr [esi + 0x14]
0095c602 minss xmm1, xmm2
0095c606 jmp 0x95c655
0095c608 push ecx
0095c609 mov dword ptr [esp], 0xbf800000
0095c610 lea eax, [ebp - 0xf4]
0095c616 push eax
0095c617 push 1
0095c619 push 0x13c
0095c61e mov ecx, esi
0095c620 call 0x943ad0
0095c625 movss xmm0, dword ptr [ebp - 0xf0]
0095c62d movss xmm1, dword ptr [ebp - 0xc4]
0095c635 movss xmm2, dword ptr [ebp - 0xe4]
0095c63d movss dword ptr [ebp - 0xd4], xmm0
0095c645 movss xmm0, dword ptr [ebp - 0xf4]
0095c64d movss dword ptr [ebp - 0xd0], xmm0
0095c655 push ecx
0095c656 push 1
0095c658 mov ecx, esi
0095c65a call 0x944fc0
0095c65f addss xmm2, dword ptr [0xb6a614]
0095c667 movaps xmm0, xmm1
0095c66a addss xmm0, dword ptr [0xb6a614]
0095c672 mulss xmm0, dword ptr [0xb6a8f4]
0095c67a divss xmm0, xmm2
0095c67e cvttss2si eax, xmm0
0095c682 mov dword ptr [esi + 0x40], eax
0095c685 movss dword ptr [esi + 0x14], xmm1
0095c68a movss dword ptr [esi + 0x44], xmm1
0095c68f jmp 0x95c6aa
0095c691 mov eax, dword ptr [esi + 0x40]
0095c694 test eax, eax
0095c696 jle 0x95c69c
0095c698 dec eax
0095c699 mov dword ptr [esi + 0x40], eax
0095c69c mov ecx, esi
0095c69e mov dword ptr [esi + 0x14], 0
0095c6a5 call 0x9448e0
0095c6aa cmp byte ptr [ebp + 0xc], 0
0095c6ae je 0x95c703
0095c6b0 mov ecx, esi
0095c6b2 call 0x942c40
0095c6b7 test al, al
0095c6b9 je 0x95c6e3
0095c6bb movss xmm0, dword ptr [ebp - 0xd0]
0095c6c3 lea eax, [ebp - 0x144]
0095c6c9 movss dword ptr [ebp - 0x144], xmm0
0095c6d1 movss xmm0, dword ptr [ebp - 0xd4]
0095c6d9 movss dword ptr [ebp - 0x140], xmm0
0095c6e1 jmp 0x95c6f8
0095c6e3 lea eax, [ebp - 0xf4]
0095c6e9 mov ecx, esi
0095c6eb push eax
0095c6ec lea eax, [ebp - 0x14c]
0095c6f2 push eax
0095c6f3 call 0x942cc0
0095c6f8 mov ecx, dword ptr [eax]
0095c6fa mov dword ptr [esi + 0x1c], ecx
0095c6fd mov eax, dword ptr [eax + 4]
0095c700 mov dword ptr [esi + 0x20], eax
0095c703 mov ecx, dword ptr [ebp - 0xc]
0095c706 mov dword ptr fs:[0], ecx
0095c70d pop ecx
0095c70e pop edi
0095c70f pop esi
0095c710 mov ecx, dword ptr [ebp - 0x10]
0095c713 xor ecx, ebp
0095c715 call 0x9eacd7
0095c71a mov esp, ebp
0095c71c pop ebp
0095c71d ret 0xc
0095c720 push 0xc07190
0095c725 call 0x9eb26f
0095c72a add esp, 4
0095c72d cmp dword ptr [0xc07190], -1
0095c734 jne 0x95a6f4
0095c73a push 0xa05750
0095c73f call 0x9eb079
0095c744 push 0xc07190
0095c749 call 0x9eb225
0095c74e add esp, 8
0095c751 jmp 0x95a6f4
0095c756 nop 
0095c758 sub byte ptr [edi - 0x40d7ff6b], bh
0095c75e xchg ebp, eax
0095c75f add dl, cl
0095c761 mov edi, 0xbf790095
0095c766 xchg ebp, eax
0095c767 add ah, cl
0095c769 int3 
0095c76a int3 
