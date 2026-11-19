0063b411 push 0
0063b413 push 0xb46840
0063b418 lea ecx, [edi + 0x3c]
0063b41b call 0x4054f0
0063b420 push 0xb46840
0063b425 lea ecx, [edi + 0x3c]
0063b428 call 0x4060f0
0063b42d test al, al
0063b42f je 0x63e3fe
0063b435 push 0x64
0063b437 mov ecx, ebx
0063b439 call 0x7a7d50
0063b43e test eax, eax
0063b440 jne 0x63b565
0063b446 mov ecx, dword ptr [0xbfd65c]
0063b44c push 0x22
0063b44e call 0x427900
0063b453 mov ecx, eax
0063b455 call 0x701d40
0063b45a test al, al
0063b45c je 0x63b565
0063b462 movss xmm0, dword ptr [0xc02fec]
0063b46a lea ebx, [edi + 0x294]
0063b470 movss dword ptr [ebp - 0x18], xmm0
0063b475 xor esi, esi
0063b477 movss xmm0, dword ptr [0xc02ff0]
0063b47f movss dword ptr [ebp - 0x14], xmm0
0063b484 nop dword ptr [eax]
0063b488 nop dword ptr [eax + eax]
0063b490 lea eax, [ebp - 0x84]
0063b496 mov dword ptr [ebp - 0x84], 0x40a00000
0063b4a0 push eax
0063b4a1 lea eax, [ebp - 0x7c]
0063b4a4 push eax
0063b4a5 lea ecx, [ebp - 0x30]
0063b4a8 call 0x7a7e20
0063b4ad mov edx, eax
0063b4af lea ecx, [ebp - 0x9c]
0063b4b5 call 0x6592f0
0063b4ba mov ecx, eax
0063b4bc call 0x962b50
0063b4c1 push eax
0063b4c2 lea ecx, [ebp - 0x18]
0063b4c5 call 0x962cd0
0063b4ca movss xmm0, dword ptr [ebp - 0x14]
0063b4cf lea eax, [ebp - 0x84]
0063b4d5 mulss xmm0, dword ptr [0xb6a350]
0063b4dd lea ecx, [ebp - 0x18]
0063b4e0 push 0
0063b4e2 push 0
0063b4e4 push 0
0063b4e6 addss xmm0, dword ptr [0xb6a864]
0063b4ee push 0
0063b4f0 push 1
0063b4f2 push eax
0063b4f3 lea eax, [ebp - 0xac]
0063b4f9 mov dword ptr [ebp - 0x84], 0x40e00000
0063b503 push eax
0063b504 movss dword ptr [ebp - 0x14], xmm0
0063b509 call 0x962b50
0063b50e push eax
0063b50f lea eax, [ebp - 0xb4]
0063b515 mov ecx, ebx
0063b517 push eax
0063b518 call 0x962a60
0063b51d mov ecx, dword ptr [0xbfd65c]
0063b523 push eax
0063b524 push ebx
0063b525 call 0x4023f0
0063b52a mov ecx, eax
0063b52c call 0x7af4b0
0063b531 test al, al
0063b533 jne 0x63b53f
0063b535 inc esi
0063b536 cmp esi, 0xa
0063b539 jl 0x63b490
0063b53f call 0x6c3d90
0063b544 mov ecx, dword ptr [0xbfd65c]
0063b54a push eax
0063b54b push 0x22
0063b54d push 0
0063b54f lea eax, [ebp - 0x18]
0063b552 push eax
0063b553 push ebx
0063b554 push 0x15e
0063b559 push 5
0063b55b call 0x422e20
0063b560 jmp 0x63b892
0063b565 push 0xf
0063b567 mov ecx, ebx
0063b569 call 0x7a7d50
0063b56e test eax, eax
0063b570 jne 0x63b65e
0063b576 mov esi, 0x87
0063b57b mov ecx, ebx
0063b57d push 2
0063b57f mov dword ptr [ebp - 0x80], esi
0063b582 call 0x7a7d50
0063b587 test eax, eax
0063b589 je 0x63b5a4
0063b58b mov ecx, dword ptr [0xbfd65c]
0063b591 push 0
0063b593 push esi
0063b594 call 0x427900
0063b599 mov ecx, eax
0063b59b call 0x700ad0
0063b5a0 test al, al
0063b5a2 jne 0x63b5c8
0063b5a4 mov ecx, dword ptr [0xbfd680]
0063b5aa push 0x93
0063b5af call 0x41c4a0
0063b5b4 mov ecx, eax
0063b5b6 call 0x884da0
0063b5bb test al, al
0063b5bd mov ecx, 0x77
0063b5c2 cmovne esi, ecx
0063b5c5 mov dword ptr [ebp - 0x80], esi
0063b5c8 mov ecx, dword ptr [0xbfd65c]
0063b5ce push 0
0063b5d0 push 0
0063b5d2 push esi
0063b5d3 call 0x427900
0063b5d8 mov ecx, eax
0063b5da call 0x701bd0
0063b5df mov eax, dword ptr [edi]
0063b5e1 mov ecx, edi
0063b5e3 call dword ptr [eax + 0x28]
0063b5e6 call 0x6c3d90
0063b5eb mov ecx, dword ptr [0xbfd65c]
0063b5f1 lea esi, [edi + 0x294]
0063b5f7 push eax
0063b5f8 push 0
0063b5fa push 0
0063b5fc push 0xc02fec
0063b601 push esi
0063b602 push 1
0063b604 push 0x3e8
0063b609 call 0x422e20
0063b60e push 0
0063b610 push 0xbeac80
0063b615 push 0xbeab18
0063b61a push 0
0063b61c mov ecx, ebx
0063b61e call 0x7a7e20
0063b623 mov ecx, dword ptr [0xbfd65c]
0063b629 push eax
0063b62a push dword ptr [ebp - 0x80]
0063b62d push 0
0063b62f push 0xc02fec
0063b634 push esi
0063b635 push 0x64
0063b637 push 5
0063b639 call 0x422e20
0063b63e push eax
0063b63f call 0x9ec34c
0063b644 add esp, 0x14
0063b647 mov esi, eax
0063b649 mov ecx, esi
0063b64b push 2
0063b64d call 0x6b8400
0063b652 mov edx, dword ptr [esi]
0063b654 mov ecx, esi
0063b656 call dword ptr [edx + 0xc]
0063b659 jmp 0x63b892
0063b65e mov esi, dword ptr [ebp - 0xa0]
0063b664 test esi, esi
0063b666 je 0x63b6f4
0063b66c mov ecx, esi
0063b66e call 0x78cdc0
0063b673 cmp eax, 3
0063b676 jne 0x63b6f4
0063b678 push 2
0063b67a mov ecx, ebx
0063b67c call 0x7a7d50
0063b681 push 0
0063b683 push 0x4b
0063b685 mov ecx, esi
0063b687 mov dword ptr [ebp - 0xa0], eax
0063b68d call 0x73af30
0063b692 test al, al
0063b694 je 0x63b6cf
0063b696 push 8
0063b698 mov ecx, ebx
0063b69a call 0x4076f0
0063b69f push eax
0063b6a0 lea ecx, [ebp - 0x40]
0063b6a3 call 0x7a7cd0
0063b6a8 mov byte ptr [ebp - 4], 2
0063b6ac mov ecx, dword ptr [ebp - 0x80]
0063b6af or ecx, 1
0063b6b2 mov dword ptr [ebp - 0x80], ecx
0063b6b5 mov dword ptr [ebp - 0x84], ecx
0063b6bb mov ecx, eax
0063b6bd push 4
0063b6bf call 0x7a7d50
0063b6c4 mov byte ptr [ebp - 0x8d], 1
0063b6cb test eax, eax
0063b6cd je 0x63b6d6
0063b6cf mov byte ptr [ebp - 0x8d], 0
0063b6d6 mov dword ptr [ebp - 4], 0
0063b6dd test byte ptr [ebp - 0x80], 1
0063b6e1 je 0x63b6eb
0063b6e3 lea ecx, [ebp - 0x40]
0063b6e6 call 0x407620
0063b6eb cmp byte ptr [ebp - 0x8d], 0
0063b6f2 jmp 0x63b761
0063b6f4 mov ecx, dword ptr [0xbfd65c]
0063b6fa call 0x6cba20
0063b6ff mov ecx, ebx
0063b701 test al, al
0063b703 je 0x63b72a
0063b705 push 2
0063b707 call 0x7a7d50
0063b70c mov dword ptr [ebp - 0xb0], eax
0063b712 lea edx, [ebp - 0xb0]
0063b718 mov dword ptr [ebp - 0xa8], 1
0063b722 lea ecx, [ebp - 0xa8]
0063b728 jmp 0x63b747
0063b72a push 3
0063b72c call 0x7a7d50
0063b731 mov dword ptr [ebp - 0x98], eax
0063b737 lea edx, [ebp - 0x98]
0063b73d mov dword ptr [ebp - 0x78], 1
0063b744 lea ecx, [ebp - 0x78]
0063b747 call 0x407dd0
0063b74c push 0
0063b74e push 0x4b
0063b750 mov ecx, esi
0063b752 mov eax, dword ptr [eax]
0063b754 mov dword ptr [ebp - 0xa0], eax
0063b75a call 0x73af30
0063b75f test al, al
0063b761 mov ecx, dword ptr [ebp - 0xa0]
0063b767 je 0x63b770
0063b769 inc ecx
0063b76a mov dword ptr [ebp - 0xa0], ecx
0063b770 test ecx, ecx
0063b772 je 0x63b892
0063b778 lea eax, [edi + 0x294]
0063b77e mov dword ptr [ebp - 0x78], eax
0063b781 mov edi, eax
0063b783 movss xmm0, dword ptr [0xc02fec]
0063b78b xor esi, esi
0063b78d movss dword ptr [ebp - 0x9c], xmm0
0063b795 movss xmm0, dword ptr [0xc02ff0]
0063b79d movss dword ptr [ebp - 0x98], xmm0
0063b7a5 lea eax, [ebp - 0x78]
0063b7a8 mov dword ptr [ebp - 0x78], 0x40a00000
0063b7af push eax
0063b7b0 lea eax, [ebp - 0x18]
0063b7b3 push eax
0063b7b4 lea ecx, [ebp - 0x30]
0063b7b7 call 0x7a7e20
0063b7bc mov edx, eax
0063b7be lea ecx, [ebp - 0xac]
0063b7c4 call 0x6592f0
0063b7c9 mov ecx, eax
0063b7cb call 0x962b50
0063b7d0 push eax
0063b7d1 lea ecx, [ebp - 0x9c]
0063b7d7 call 0x962cd0
0063b7dc movss xmm0, dword ptr [ebp - 0x98]
0063b7e4 lea eax, [ebp - 0x78]
0063b7e7 mulss xmm0, dword ptr [0xb6a350]
0063b7ef lea ecx, [ebp - 0x9c]
0063b7f5 push 0
0063b7f7 push 0
0063b7f9 push 0
0063b7fb addss xmm0, dword ptr [0xb6a864]
0063b803 push 0
0063b805 push 1
0063b807 push eax
0063b808 lea eax, [ebp - 0xb4]
0063b80e mov dword ptr [ebp - 0x78], 0x40e00000
0063b815 push eax
0063b816 movss dword ptr [ebp - 0x98], xmm0
0063b81e call 0x962b50
0063b823 push eax
0063b824 lea eax, [ebp - 0x88]
0063b82a mov ecx, edi
0063b82c push eax
0063b82d call 0x962a60
0063b832 mov ecx, dword ptr [0xbfd65c]
0063b838 push eax
0063b839 push edi
0063b83a call 0x4023f0
0063b83f mov ecx, eax
0063b841 call 0x7af4b0
0063b846 test al, al
0063b848 jne 0x63b854
0063b84a inc esi
0063b84b cmp esi, 0xa
0063b84e jl 0x63b7a5
0063b854 mov ecx, ebx
0063b856 call 0x7a7e20
0063b85b mov ecx, dword ptr [0xbfd65c]
0063b861 push eax
0063b862 push 0
0063b864 push 0
0063b866 lea eax, [ebp - 0x9c]
0063b86c push eax
0063b86d push edi
0063b86e push 0x14
0063b870 push 5
0063b872 call 0x422e20
0063b877 mov ecx, dword ptr [ebp - 0xa0]
0063b87d sub ecx, 1
0063b880 mov dword ptr [ebp - 0xa0], ecx
0063b886 jne 0x63b783
0063b88c mov edi, dword ptr [ebp - 0xb8]
