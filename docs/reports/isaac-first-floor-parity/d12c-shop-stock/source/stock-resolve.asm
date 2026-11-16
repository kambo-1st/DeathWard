007d04a0 push ebp
007d04a1 mov ebp, esp
007d04a3 and esp, 0xfffffff8
007d04a6 sub esp, 0x24
007d04a9 mov eax, dword ptr [0xbaa3b4]
007d04ae xor eax, esp
007d04b0 mov dword ptr [esp + 0x20], eax
007d04b4 mov edx, dword ptr [0xbfd65c]
007d04ba push ebx
007d04bb mov ebx, dword ptr [ebp + 0x14]
007d04be push esi
007d04bf mov eax, dword ptr [edx + 0x243624]
007d04c5 mov esi, dword ptr [ebp + 0x10]
007d04c8 mov dword ptr [esp + 0x10], ecx
007d04cc mov ecx, dword ptr [ebp + 8]
007d04cf push edi
007d04d0 mov edi, dword ptr [ebp + 0xc]
007d04d3 cmp eax, 2
007d04d6 je 0x7d04e2
007d04d8 mov byte ptr [esp + 0x13], 0
007d04dd cmp eax, 3
007d04e0 jne 0x7d04e7
007d04e2 mov byte ptr [esp + 0x13], 1
007d04e7 mov eax, 8
007d04ec cmp ecx, eax
007d04ee push 1
007d04f0 cmovl eax, ecx
007d04f3 xor ecx, ecx
007d04f5 test eax, eax
007d04f7 push 0
007d04f9 cmovg ecx, eax
007d04fc mov dword ptr [esp + 0x20], ecx
007d0500 lea ecx, [edx + 0x1ba40]
007d0506 push 0xb8
007d050b call 0x91d550
007d0510 mov ecx, dword ptr [esp + 0x14]
007d0514 test eax, eax
007d0516 je 0x7d054e
007d0518 mov eax, dword ptr [ecx + 8]
007d051b cmp eax, 2
007d051e je 0x7d0525
007d0520 cmp eax, 0x16
007d0523 jne 0x7d054e
007d0525 mov eax, dword ptr [ecx + 4]
007d0528 mov edx, dword ptr [esp + 0x18]
007d052c lea edx, [eax + edx*2]
007d052f movzx eax, word ptr [edx + 0x94]
007d0536 cmp ax, 8
007d053a je 0x7d0542
007d053c cmp ax, 0x11
007d0540 jne 0x7d054e
007d0542 mov eax, 0x12
007d0547 mov word ptr [edx + 0x94], ax
007d054e mov eax, dword ptr [ecx + 4]
007d0551 mov edx, dword ptr [esp + 0x18]
007d0555 movsx eax, word ptr [eax + edx*2 + 0x94]
007d055d cmp eax, 0x14
007d0560 ja 0x7d08da
007d0566 jmp dword ptr [eax*4 + 0x7d08f0]
007d056d mov dword ptr [edi], 0xa
007d0573 mov dword ptr [esi], 1
007d0579 pop edi
007d057a pop esi
007d057b pop ebx
007d057c mov ecx, dword ptr [esp + 0x20]
007d0580 xor ecx, esp
007d0582 call 0x9eacd7
007d0587 mov esp, ebp
007d0589 pop ebp
007d058a ret 0x10
007d058d mov dword ptr [edi], 0x28
007d0593 mov dword ptr [esi], 1
007d0599 pop edi
007d059a pop esi
007d059b pop ebx
007d059c mov ecx, dword ptr [esp + 0x20]
007d05a0 xor ecx, esp
007d05a2 call 0x9eacd7
007d05a7 mov esp, ebp
007d05a9 pop ebp
007d05aa ret 0x10
007d05ad mov ecx, dword ptr [0xbfd65c]
007d05b3 push ebx
007d05b4 mov dword ptr [edi], 0x46
007d05ba lea ecx, [ecx + 0x1a5cc]
007d05c0 call 0x702590
007d05c5 jmp 0x7d08d8
007d05ca mov dword ptr [edi], 0x1e
007d05d0 mov dword ptr [esi], 1
007d05d6 pop edi
007d05d7 pop esi
007d05d8 pop ebx
007d05d9 mov ecx, dword ptr [esp + 0x20]
007d05dd xor ecx, esp
007d05df call 0x9eacd7
007d05e4 mov esp, ebp
007d05e6 pop ebp
007d05e7 ret 0x10
007d05ea mov dword ptr [edi], 0xa
007d05f0 mov dword ptr [esi], 3
007d05f6 pop edi
007d05f7 pop esi
007d05f8 pop ebx
007d05f9 mov ecx, dword ptr [esp + 0x20]
007d05fd xor ecx, esp
007d05ff call 0x9eacd7
007d0604 mov esp, ebp
007d0606 pop ebp
007d0607 ret 0x10
007d060a mov dword ptr [edi], 0x5a
007d0610 mov dword ptr [esi], 1
007d0616 pop edi
007d0617 pop esi
007d0618 pop ebx
007d0619 mov ecx, dword ptr [esp + 0x20]
007d061d xor ecx, esp
007d061f call 0x9eacd7
007d0624 mov esp, ebp
007d0626 pop ebp
007d0627 ret 0x10
007d062a push 1
007d062c push 0xa
007d062e push 0
007d0630 push 0x19
007d0632 push ebx
007d0633 mov dword ptr [edi], 0x12c
007d0639 call 0x701da0
007d063e push 0
007d0640 push 0
007d0642 push 1
007d0644 jmp 0x7d08b1
007d0649 mov dword ptr [edi], 0x45
007d064f mov dword ptr [esi], 1
007d0655 pop edi
007d0656 pop esi
007d0657 pop ebx
007d0658 mov ecx, dword ptr [esp + 0x20]
007d065c xor ecx, esp
007d065e call 0x9eacd7
007d0663 mov esp, ebp
007d0665 pop ebp
007d0666 ret 0x10
007d0669 push 0
007d066b push ebx
007d066c mov dword ptr [edi], 0x64
007d0672 call 0x7aab40
007d0677 jmp 0x7d08d8
007d067c cmp byte ptr [esp + 0x13], 0
007d0681 mov eax, 1
007d0686 mov ecx, 0x12
007d068b cmovne eax, ecx
007d068e push 0
007d0690 push 0
007d0692 push ebx
007d0693 push eax
007d0694 mov ecx, dword ptr [0xbfd65c]
007d069a mov dword ptr [edi], 0x64
007d06a0 lea ecx, [ecx + 0x1a5cc]
007d06a6 call 0x701230
007d06ab jmp 0x7d08d8
007d06b0 push 0
007d06b2 push 0
007d06b4 push ebx
007d06b5 push 0x1c
007d06b7 jmp 0x7d0694
007d06b9 mov dword ptr [edi], 0xa
007d06bf mov dword ptr [esi], 4
007d06c5 pop edi
007d06c6 pop esi
007d06c7 pop ebx
007d06c8 mov ecx, dword ptr [esp + 0x20]
007d06cc xor ecx, esp
007d06ce call 0x9eacd7
007d06d3 mov esp, ebp
007d06d5 pop ebp
007d06d6 ret 0x10
007d06d9 mov eax, dword ptr [0xbfd680]
007d06de cmp byte ptr [eax + 0x171], 0
007d06e5 jne 0x7d070c
007d06e7 cmp dword ptr [eax + 8], 2
007d06eb jne 0x7d0708
007d06ed mov eax, dword ptr [0xbfd65c]
007d06f2 test eax, eax
007d06f4 je 0x7d0708
007d06f6 cmp dword ptr [eax + 0x1c3204], 0
007d06fd ja 0x7d070c
007d06ff cmp byte ptr [eax + 0x1c31a1], 0
007d0706 jne 0x7d070c
007d0708 xor dl, dl
007d070a jmp 0x7d070e
007d070c mov dl, 1
007d070e test dl, dl
007d0710 mov eax, 1
007d0715 mov ecx, 0x33
007d071a mov ebx, 0x1e
007d071f cmove ecx, eax
007d0722 mov eax, 0x12c
007d0727 cmove eax, ebx
007d072a mov dword ptr [edi], eax
007d072c mov dword ptr [esi], ecx
007d072e pop edi
007d072f pop esi
007d0730 pop ebx
007d0731 mov ecx, dword ptr [esp + 0x20]
007d0735 xor ecx, esp
007d0737 call 0x9eacd7
007d073c mov esp, ebp
007d073e pop ebp
007d073f ret 0x10
007d0742 cmp byte ptr [esp + 0x13], 0
007d0747 mov eax, 2
007d074c mov edx, 0x11
007d0751 cmovne eax, edx
007d0754 jmp 0x7d068e
007d0759 movzx eax, byte ptr [esp + 0x13]
007d075e shl eax, 4
007d0761 jmp 0x7d068e
007d0766 mov ecx, dword ptr [0xbfd65c]
007d076c push 0
007d076e mov dword ptr [edi], 0x15e
007d0774 lea ecx, [ecx + 0x1a5cc]
007d077a call 0x701880
007d077f jmp 0x7d08d8
007d0784 movzx eax, byte ptr [esp + 0x13]
007d0789 shl eax, 4
007d078c add eax, 3
007d078f jmp 0x7d068e
007d0794 movzx eax, byte ptr [esp + 0x13]
007d0799 shl eax, 4
007d079c add eax, 4
007d079f jmp 0x7d068e
007d07a4 cmp byte ptr [esp + 0x13], 0
007d07a9 mov eax, 5
007d07ae mov edx, 0x16
007d07b3 cmovne eax, edx
007d07b6 jmp 0x7d068e
007d07bb movq xmm0, qword ptr [0xa08d04]
007d07c3 lea ecx, [esp + 0x1c]
007d07c7 mov eax, dword ptr [0xa08d0c]
007d07cc mov dword ptr [edi], 0xa
007d07d2 push 3
007d07d4 mov dword ptr [esi], 6
007d07da mov dword ptr [esp + 0x20], ebx
007d07de movq qword ptr [esp + 0x24], xmm0
007d07e4 mov dword ptr [esp + 0x2c], eax
007d07e8 call 0x7a7d50
007d07ed test eax, eax
007d07ef jne 0x7d07f7
007d07f1 mov dword ptr [esi], 4
007d07f7 push 4
007d07f9 lea ecx, [esp + 0x20]
007d07fd call 0x7a7d50
007d0802 test eax, eax
007d0804 jne 0x7d083b
007d0806 mov eax, dword ptr [0xbfd680]
007d080b cmp byte ptr [eax + 0x1e7], 0
007d0812 jne 0x7d0835
007d0814 cmp dword ptr [eax + 8], 2
007d0818 jne 0x7d083b
007d081a mov eax, dword ptr [0xbfd65c]
007d081f test eax, eax
007d0821 je 0x7d083b
007d0823 cmp dword ptr [eax + 0x1c3204], 0
007d082a ja 0x7d0835
007d082c cmp byte ptr [eax + 0x1c31a1], 0
007d0833 je 0x7d083b
007d0835 mov dword ptr [esi], 0xc
007d083b push 4
007d083d lea ecx, [esp + 0x20]
007d0841 call 0x7a7d50
007d0846 test eax, eax
007d0848 jne 0x7d08da
007d084e mov eax, dword ptr [0xbfd680]
007d0853 cmp byte ptr [eax + 0x1d3], 0
007d085a jne 0x7d087d
007d085c cmp dword ptr [eax + 8], 2
007d0860 jne 0x7d08da
007d0862 mov eax, dword ptr [0xbfd65c]
007d0867 test eax, eax
007d0869 je 0x7d08da
007d086b cmp dword ptr [eax + 0x1c3204], 0
007d0872 ja 0x7d087d
007d0874 cmp byte ptr [eax + 0x1c31a1], 0
007d087b je 0x7d08da
007d087d mov dword ptr [esi], 0xb
007d0883 pop edi
007d0884 pop esi
007d0885 pop ebx
007d0886 mov ecx, dword ptr [esp + 0x20]
007d088a xor ecx, esp
007d088c call 0x9eacd7
007d0891 mov esp, ebp
007d0893 pop ebp
007d0894 ret 0x10
007d0897 push 1
007d0899 push 0
007d089b push 1
007d089d push 0
007d089f push ebx
007d08a0 mov dword ptr [edi], 0x12c
007d08a6 call 0x701da0
007d08ab push 1
007d08ad push 1
007d08af push 0
007d08b1 movq xmm0, qword ptr [0xa08c44]
007d08b9 mov ecx, dword ptr [0xa08c4c]
007d08bf push eax
007d08c0 lea eax, [esp + 0x2c]
007d08c4 mov dword ptr [esp + 0x2c], ebx
007d08c8 push eax
007d08c9 movq qword ptr [esp + 0x34], xmm0
007d08cf mov dword ptr [esp + 0x3c], ecx
007d08d3 call 0x801c10
007d08d8 mov dword ptr [esi], eax
007d08da mov ecx, dword ptr [esp + 0x2c]
007d08de pop edi
007d08df pop esi
007d08e0 pop ebx
007d08e1 xor ecx, esp
007d08e3 call 0x9eacd7
007d08e8 mov esp, ebp
007d08ea pop ebp
007d08eb ret 0x10
