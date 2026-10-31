00636a23 mov ecx, dword ptr [edi + 0x38c]
00636a29 xor eax, eax
00636a2b and ecx, 0x400
00636a31 or eax, ecx
00636a33 je 0x636be1
00636a39 movss xmm0, dword ptr [0xc02fec]
00636a41 lea ecx, [edi + 0x294]
00636a47 movss dword ptr [ebp - 0x390], xmm0
00636a4f xor eax, eax
00636a51 movss xmm0, dword ptr [0xc02ff0]
00636a59 movss dword ptr [ebp - 0x38c], xmm0
00636a61 movss xmm0, dword ptr [edi + 0x360]
00636a69 comiss xmm0, dword ptr [0xb6af28]
00636a70 mov dword ptr [ebp - 0x384], ecx
00636a76 setb al
00636a79 xor esi, esi
00636a7b lea eax, [eax*2 + 2]
00636a82 mov dword ptr [ebp - 0x3b8], eax
00636a88 lea eax, [edi + 0x170]
00636a8e mov ecx, eax
00636a90 mov dword ptr [ebp - 0x338], eax
00636a96 call 0x421d30
00636a9b test eax, eax
00636a9d je 0x636b35
00636aa3 mov edi, dword ptr [ebp - 0x338]
00636aa9 nop dword ptr [eax]
00636ab0 push esi
00636ab1 mov ecx, edi
00636ab3 call 0x421d20
00636ab8 mov ecx, dword ptr [ebp - 0x384]
00636abe push eax
00636abf lea eax, [ebp - 0x358]
00636ac5 push eax
00636ac6 call 0x962a60
00636acb push dword ptr [ebp - 0x354]
00636ad1 mov ecx, dword ptr [0xbfd65c]
00636ad7 push dword ptr [ebp - 0x358]
00636add call 0x4023f0
00636ae2 mov ecx, eax
00636ae4 call 0x7aee40
00636ae9 push dword ptr [ebp - 0x354]
00636aef mov ecx, dword ptr [0xbfd65c]
00636af5 push dword ptr [ebp - 0x358]
00636afb call 0x4023f0
00636b00 mov ecx, eax
00636b02 call 0x7aee40
00636b07 cmp eax, dword ptr [ebp - 0x3b8]
00636b0d jl 0x636b23
00636b0f push esi
00636b10 mov ecx, edi
00636b12 call 0x421d20
00636b17 push eax
00636b18 lea ecx, [ebp - 0x390]
00636b1e call 0x962a90
00636b23 mov ecx, edi
00636b25 inc esi
00636b26 call 0x421d30
00636b2b cmp esi, eax
00636b2d jb 0x636ab0
00636b2f mov edi, dword ptr [ebp - 0x320]
00636b35 push 0xc02fec
00636b3a lea ecx, [ebp - 0x390]
00636b40 call 0x962ca0
00636b45 test al, al
00636b47 je 0x636be1
00636b4d lea ecx, [ebp - 0x390]
00636b53 call 0x9624f0
00636b58 movss xmm1, dword ptr [ebp - 0x390]
00636b60 lea esi, [edi + 0x2b8]
00636b66 xorps xmm1, xmmword ptr [0xb6c9b0]
00636b6d movss xmm0, dword ptr [ebp - 0x38c]
00636b75 mulss xmm0, dword ptr [edi + 0x2bc]
00636b7d mulss xmm1, dword ptr [esi]
00636b81 subss xmm1, xmm0
00636b85 xorps xmm0, xmm0
00636b88 comiss xmm0, xmm1
00636b8b movss dword ptr [ebp - 0x384], xmm1
00636b93 jbe 0x636be1
00636b95 lea eax, [ebp - 0x338]
00636b9b mov dword ptr [ebp - 0x338], 0x40000000
00636ba5 push eax
00636ba6 lea eax, [ebp - 0x3fc]
00636bac push eax
00636bad lea eax, [ebp - 0x384]
00636bb3 push eax
00636bb4 lea eax, [ebp - 0x45c]
00636bba push eax
00636bbb lea ecx, [ebp - 0x390]
00636bc1 call 0x962b50
00636bc6 mov ecx, eax
00636bc8 call 0x962b50
00636bcd push eax
00636bce mov ecx, esi
00636bd0 call 0x962a90
00636bd5 push esi
00636bd6 lea ecx, [edi + 0x294]
00636bdc call 0x962a90
