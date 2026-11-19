005a355b mov eax, dword ptr [ebp - 0x588]
005a3561 cmp dword ptr [eax + 0x2c], 0
005a3565 jne 0x5a1d01
005a356b mov ecx, dword ptr [0xbfd65c]
005a3571 mov dword ptr [eax + 0x1308], 0
005a357b mov dword ptr [ebp - 0x590], 0x42020
005a3585 call 0x41c480
005a358a cmp eax, 0x1e
005a358d jne 0x5a3599
005a358f mov dword ptr [ebp - 0x590], 0x42820
005a3599 mov edi, dword ptr [ebp - 0x588]
005a359f lea ecx, [ebp - 0x1648]
005a35a5 push 0x1e
005a35a7 mov esi, dword ptr [edi]
005a35a9 call 0x427290
005a35ae movss xmm0, dword ptr [0xb6a614]
005a35b6 push eax
005a35b7 mov eax, dword ptr [esi + 0x20]
005a35ba push 0
005a35bc push dword ptr [ebp - 0x590]
005a35c2 movss dword ptr [ebp - 0x590], xmm0
005a35ca push ecx
005a35cb mov ecx, edi
005a35cd mov dword ptr [esp], 0x3f800000
005a35d4 call eax
005a35d6 mov eax, dword ptr [ebp - 0x588]
005a35dc xor edi, edi
005a35de mov ecx, dword ptr [eax + 0x130c]
005a35e4 cmp ecx, 0xe
005a35e7 je 0x5a3681
005a35ed cmp ecx, 0x21
005a35f0 je 0x5a3681
005a35f6 mov ecx, dword ptr [0xbfd65c]
005a35fc lea esi, [eax + 0x334]
005a3602 call 0x6cba20
005a3607 mov ecx, esi
005a3609 test al, al
005a360b je 0x5a3632
005a360d push 2
005a360f call 0x7a7d50
005a3614 mov dword ptr [ebp - 0x760], eax
005a361a lea ecx, [ebp - 0x75c]
005a3620 mov dword ptr [ebp - 0x75c], 1
005a362a lea edx, [ebp - 0x760]
005a3630 jmp 0x5a3655
005a3632 push 3
005a3634 call 0x7a7d50
005a3639 mov dword ptr [ebp - 0x764], eax
005a363f lea ecx, [ebp - 0x8cc]
005a3645 mov dword ptr [ebp - 0x8cc], 1
005a364f lea edx, [ebp - 0x764]
005a3655 call 0x407dd0
005a365a mov esi, dword ptr [ebp - 0x588]
005a3660 mov ecx, esi
005a3662 push 0
005a3664 push 0x4b
005a3666 mov edi, dword ptr [eax]
005a3668 mov dword ptr [ebp - 0x5a4], edi
005a366e call 0x73af30
005a3673 test al, al
005a3675 je 0x5a36ff
005a367b inc edi
005a367c jmp 0x5a36f9
005a3681 push 0
005a3683 push 0x4b
005a3685 mov ecx, eax
005a3687 call 0x73af30
005a368c test al, al
005a368e je 0x5a36a4
005a3690 mov ecx, 2
005a3695 call 0x659230
005a369a test eax, eax
005a369c mov ecx, 1
005a36a1 cmove edi, ecx
005a36a4 mov esi, dword ptr [ebp - 0x588]
005a36aa mov ecx, esi
005a36ac push 0
005a36ae push 0xe3
005a36b3 call 0x73af30
005a36b8 test al, al
005a36ba je 0x5a36cc
005a36bc movss xmm0, dword ptr [0xb6a7b0]
005a36c4 movss dword ptr [ebp - 0x590], xmm0
005a36cc call 0x659200
005a36d1 mulss xmm0, dword ptr [ebp - 0x590]
005a36d9 xor eax, eax
005a36db test edi, edi
005a36dd jne 0x5a36e9
005a36df movss xmm1, dword ptr [0xb6a480]
005a36e7 jmp 0x5a36f1
005a36e9 movss xmm1, dword ptr [0xb6a38c]
005a36f1 comiss xmm1, xmm0
005a36f4 setae al
005a36f7 add edi, eax
005a36f9 mov dword ptr [ebp - 0x5a4], edi
005a36ff test edi, edi
005a3701 jle 0x5a1cf5
005a3707 mov edi, dword ptr [ebp - 0x59c]
005a370d nop dword ptr [eax]
005a3710 call 0x6c3d90
005a3715 push eax
005a3716 push 0
005a3718 push esi
005a3719 push 0xc02fec
005a371e push 0
005a3720 push 0
005a3722 push ecx
005a3723 mov ecx, dword ptr [0xbfd65c]
005a3729 lea eax, [ebp - 0x1178]
005a372f mov dword ptr [esp], 0x42200000
005a3736 push edi
005a3737 push eax
005a3738 call 0x4023f0
005a373d mov ecx, eax
005a373f call 0x7cf240
005a3744 mov ecx, dword ptr [0xbfd65c]
005a374a push eax
005a374b push 0x14
005a374d push 5
005a374f call 0x422e20
005a3754 sub dword ptr [ebp - 0x5a4], 1
005a375b jne 0x5a3710
005a375d jmp 0x5a1cf5
