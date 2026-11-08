007b82b0 push ebp
007b82b1 mov ebp, esp
007b82b3 sub esp, 0xc
007b82b6 push ebx
007b82b7 push esi
007b82b8 push edi
007b82b9 mov edi, dword ptr [ebp + 8]
007b82bc mov edx, dword ptr [edi]
007b82be test edx, edx
007b82c0 jne 0x7b82d8
007b82c2 push 0xb4d6c4
007b82c7 push 3
007b82c9 call 0x95e330
007b82ce mov edx, dword ptr [edi]
007b82d0 add esp, 8
007b82d3 test edx, edx
007b82d5 jne 0x7b82d8
007b82d7 int3 
007b82d8 mov ecx, dword ptr [edi + 4]
007b82db mov eax, edx
007b82dd shr eax, cl
007b82df xor esi, esi
007b82e1 mov ecx, dword ptr [edi + 8]
007b82e4 xor eax, edx
007b82e6 mov edx, eax
007b82e8 shl edx, cl
007b82ea mov ecx, dword ptr [edi + 0xc]
007b82ed xor edx, eax
007b82ef mov eax, edx
007b82f1 shr eax, cl
007b82f3 mov ecx, dword ptr [0xbfd65c]
007b82f9 xor eax, edx
007b82fb mov dword ptr [edi], eax
007b82fd add ecx, 0x1ba40
007b8303 push 1
007b8305 push ecx
007b8306 movd xmm0, eax
007b830a cvtdq2pd xmm0, xmm0
007b830e shr eax, 0x1f
007b8311 push 0x2e
007b8313 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007b831c cvtpd2ps xmm0, xmm0
007b8320 mulss xmm0, dword ptr [0xb6a198]
007b8328 movss dword ptr [ebp + 8], xmm0
007b832d call 0x91d340
007b8332 movss xmm2, dword ptr [0xb6a2cc]
007b833a test eax, eax
007b833c je 0x7b8354
007b833e movss xmm0, dword ptr [ebp + 8]
007b8343 mulss xmm0, dword ptr [0xb6a5a4]
007b834b addss xmm0, xmm2
007b834f movss dword ptr [ebp + 8], xmm0
007b8354 mov ebx, dword ptr [0xbfd65c]
007b835a xorps xmm1, xmm1
007b835d xorps xmm0, xmm0
007b8360 mov eax, dword ptr [ebx + 0x1ba50]
007b8366 mov ecx, dword ptr [ebx + 0x1ba54]
007b836c cmp eax, ecx
007b836e je 0x7b8386
007b8370 mov edx, dword ptr [eax]
007b8372 cmp dword ptr [edx + 0x2c], esi
007b8375 jne 0x7b837f
007b8377 addss xmm0, dword ptr [edx + 0x14b0]
007b837f add eax, 4
007b8382 cmp eax, ecx
007b8384 jne 0x7b8370
007b8386 comiss xmm0, xmm1
007b8389 lea eax, [ebp - 4]
007b838c mov dword ptr [ebp - 8], esi
007b838f lea ecx, [ebp - 8]
007b8392 movss dword ptr [ebp - 4], xmm0
007b8397 movss xmm0, dword ptr [0xb6a974]
007b839f cmovbe eax, ecx
007b83a2 movss xmm1, dword ptr [eax]
007b83a6 comiss xmm0, xmm1
007b83a9 ja 0x7b83b1
007b83ab movss xmm1, xmm0
007b83af jmp 0x7b83b5
007b83b1 movss xmm1, xmm1
007b83b5 mov edx, dword ptr [edi]
007b83b7 movss dword ptr [ebp - 4], xmm1
007b83bc test edx, edx
007b83be jne 0x7b83e9
007b83c0 push 0xb4d6c4
007b83c5 push 3
007b83c7 call 0x95e330
007b83cc mov edx, dword ptr [edi]
007b83ce add esp, 8
007b83d1 mov ebx, dword ptr [0xbfd65c]
007b83d7 movss xmm1, dword ptr [ebp - 4]
007b83dc movss xmm2, dword ptr [0xb6a2cc]
007b83e4 test edx, edx
007b83e6 jne 0x7b83e9
007b83e8 int3 
007b83e9 mov ecx, dword ptr [edi + 4]
007b83ec mov eax, edx
007b83ee shr eax, cl
007b83f0 mov ecx, dword ptr [edi + 8]
007b83f3 xor eax, edx
007b83f5 mov edx, eax
007b83f7 shl edx, cl
007b83f9 mov ecx, dword ptr [edi + 0xc]
007b83fc xor edx, eax
007b83fe mov eax, edx
007b8400 shr eax, cl
007b8402 lea ecx, [ebx + 0x1ba40]
007b8408 xor eax, edx
007b840a mov dword ptr [edi], eax
007b840c push 1
007b840e push 0
007b8410 movd xmm0, eax
007b8414 cvtdq2pd xmm0, xmm0
007b8418 shr eax, 0x1f
007b841b push 0x2a
007b841d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007b8426 cvtpd2ps xmm0, xmm0
007b842a mulss xmm0, dword ptr [0xb6a198]
007b8432 mulss xmm0, xmm1
007b8436 mulss xmm0, xmm2
007b843a addss xmm0, dword ptr [ebp + 8]
007b843f movss dword ptr [ebp + 8], xmm0
007b8444 call 0x91d550
007b8449 test eax, eax
007b844b je 0x7b84a6
007b844d mov ecx, dword ptr [0xbfd65c]
007b8453 push 1
007b8455 add ecx, 0x1ba40
007b845b push ecx
007b845c push 0x2e
007b845e call 0x91d340
007b8463 test eax, eax
007b8465 je 0x7b848c
007b8467 movss xmm0, dword ptr [ebp - 4]
007b846c comiss xmm0, dword ptr [0xb6a18c]
007b8473 jbe 0x7b848c
007b8475 movss xmm0, dword ptr [ebp + 8]
007b847a mulss xmm0, dword ptr [0xb6a604]
007b8482 addss xmm0, dword ptr [0xb6a234]
007b848a jmp 0x7b84a1
007b848c movss xmm0, dword ptr [ebp + 8]
007b8491 mulss xmm0, dword ptr [0xb6a5a4]
007b8499 addss xmm0, dword ptr [0xb6a2cc]
007b84a1 movss dword ptr [ebp + 8], xmm0
007b84a6 mov ecx, dword ptr [0xbfd65c]
007b84ac push 1
007b84ae add ecx, 0x1ba40
007b84b4 push ecx
007b84b5 push 0x29e
007b84ba call 0x91d340
007b84bf movss xmm3, dword ptr [0xb6a614]
007b84c7 xorps xmm4, xmm4
007b84ca movss xmm1, dword ptr [ebp + 8]
007b84cf test eax, eax
007b84d1 je 0x7b8523
007b84d3 movss xmm0, dword ptr [0xb6a278]
007b84db comiss xmm0, xmm1
007b84de jbe 0x7b8523
007b84e0 subss xmm1, xmm4
007b84e4 mov dword ptr [ebp + 8], esi
007b84e7 lea eax, [ebp + 8]
007b84ea lea ecx, [ebp - 8]
007b84ed divss xmm1, xmm0
007b84f1 comiss xmm4, xmm1
007b84f4 movss dword ptr [ebp - 8], xmm1
007b84f9 cmovbe eax, ecx
007b84fc movss xmm0, dword ptr [eax]
007b8500 comiss xmm0, xmm3
007b8503 ja 0x7b850b
007b8505 movss xmm0, xmm0
007b8509 jmp 0x7b850f
007b850b movss xmm0, xmm3
007b850f mulss xmm0, dword ptr [0xb6a54c]
007b8517 movaps xmm1, xmm3
007b851a subss xmm1, xmm0
007b851e movss dword ptr [ebp + 8], xmm1
007b8523 movss xmm2, dword ptr [0xb6a374]
007b852b comiss xmm2, xmm1
007b852e jb 0x7b857a
007b8530 cmp byte ptr [ebp + 0xc], 0
007b8534 je 0x7b857a
007b8536 subss xmm1, xmm4
007b853a mov dword ptr [ebp + 8], esi
007b853d lea eax, [ebp + 8]
007b8540 lea ecx, [ebp - 8]
007b8543 divss xmm1, xmm2
007b8547 comiss xmm4, xmm1
007b854a movss dword ptr [ebp - 8], xmm1
007b854f cmovbe eax, ecx
007b8552 movss xmm0, dword ptr [eax]
007b8556 comiss xmm0, xmm3
007b8559 ja 0x7b8561
007b855b movss xmm1, xmm0
007b855f jmp 0x7b8565
007b8561 movss xmm1, xmm3
007b8565 mulss xmm1, dword ptr [0xb6a548]
007b856d addss xmm1, dword ptr [0xb6a37c]
007b8575 movss dword ptr [ebp + 8], xmm1
007b857a comiss xmm1, xmm2
007b857d mov ebx, 0x32
007b8582 jbe 0x7b89f0
007b8588 movss xmm0, dword ptr [0xb6a3b0]
007b8590 comiss xmm0, xmm1
007b8593 jbe 0x7b8636
007b8599 mov edx, dword ptr [edi]
007b859b test edx, edx
007b859d jne 0x7b85b5
007b859f push 0xb4d6c4
007b85a4 push 3
007b85a6 call 0x95e330
007b85ab mov edx, dword ptr [edi]
007b85ad add esp, 8
007b85b0 test edx, edx
007b85b2 jne 0x7b85b5
007b85b4 int3 
007b85b5 mov ecx, dword ptr [edi + 4]
007b85b8 mov eax, edx
007b85ba shr eax, cl
007b85bc mov ecx, dword ptr [edi + 8]
007b85bf xor eax, edx
007b85c1 mov edx, eax
007b85c3 shl edx, cl
007b85c5 mov ecx, dword ptr [edi + 0xc]
007b85c8 xor edx, eax
007b85ca mov esi, edx
007b85cc shr esi, cl
007b85ce mov ecx, 3
007b85d3 xor esi, edx
007b85d5 xor edx, edx
007b85d7 mov eax, esi
007b85d9 mov dword ptr [edi], esi
007b85db div ecx
007b85dd test edx, edx
007b85df jne 0x7b85eb
007b85e1 mov esi, 0x12c
007b85e6 jmp 0x7b86e5
007b85eb test esi, esi
007b85ed jne 0x7b8605
007b85ef push 0xb4d6c4
007b85f4 push 3
007b85f6 call 0x95e330
007b85fb mov esi, dword ptr [edi]
007b85fd add esp, 8
007b8600 test esi, esi
007b8602 jne 0x7b8605
007b8604 int3 
007b8605 mov ecx, dword ptr [edi + 4]
007b8608 mov eax, esi
007b860a shr eax, cl
007b860c mov ecx, dword ptr [edi + 8]
007b860f xor eax, esi
007b8611 mov edx, eax
007b8613 mov esi, 0x46
007b8618 shl edx, cl
007b861a mov ecx, dword ptr [edi + 0xc]
007b861d xor edx, eax
007b861f mov eax, edx
007b8621 shr eax, cl
007b8623 xor eax, edx
007b8625 test al, 1
007b8627 mov dword ptr [edi], eax
007b8629 mov eax, 0x15e
007b862e cmove esi, eax
007b8631 jmp 0x7b86e5
007b8636 movss xmm0, dword ptr [0xb6a468]
007b863e comiss xmm0, xmm1
007b8641 ja 0x7b86e0
007b8647 movss xmm0, dword ptr [0xb6a480]
007b864f comiss xmm0, xmm1
007b8652 jbe 0x7b8674
007b8654 mov ecx, dword ptr [0xbfd65c]
007b865a push 1
007b865c push 0
007b865e push 0x54
007b8660 lea ecx, [ecx + 0x1ba40]
007b8666 call 0x91d550
007b866b test eax, eax
007b866d jne 0x7b86e0
007b866f movss xmm1, dword ptr [ebp + 8]
007b8674 movss xmm0, dword ptr [0xb6a4c4]
007b867c comiss xmm0, xmm1
007b867f jbe 0x7b86b5
007b8681 mov ecx, dword ptr [0xbfd65c]
007b8687 push 1
007b8689 push 0
007b868b push 0x16
007b868d lea ecx, [ecx + 0x1ba40]
007b8693 call 0x91d550
007b8698 test eax, eax
007b869a je 0x7b86a9
007b869c push 5
007b869e mov ecx, edi
007b86a0 call 0x7a7d50
007b86a5 test eax, eax
007b86a7 jne 0x7b86b0
007b86a9 mov esi, 0xa
007b86ae jmp 0x7b86e5
007b86b0 movss xmm1, dword ptr [ebp + 8]
007b86b5 movss xmm0, dword ptr [0xb6a560]
007b86bd comiss xmm0, xmm1
007b86c0 jbe 0x7b86c9
007b86c2 mov esi, 0x1e
007b86c7 jmp 0x7b86e5
007b86c9 movss xmm0, dword ptr [0xb6a5d8]
007b86d1 mov esi, ebx
007b86d3 comiss xmm0, xmm1
007b86d6 mov eax, 0x28
007b86db cmova esi, eax
007b86de jmp 0x7b86e5
007b86e0 mov esi, 0x14
007b86e5 mov edx, dword ptr [edi]
007b86e7 test edx, edx
007b86e9 jne 0x7b8701
007b86eb push 0xb4d6c4
007b86f0 push 3
007b86f2 call 0x95e330
007b86f7 mov edx, dword ptr [edi]
007b86f9 add esp, 8
007b86fc test edx, edx
007b86fe jne 0x7b8701
007b8700 int3 
007b8701 mov ecx, dword ptr [edi + 4]
007b8704 mov eax, edx
007b8706 shr eax, cl
007b8708 mov ecx, dword ptr [edi + 8]
007b870b xor eax, edx
007b870d mov edx, eax
007b870f shl edx, cl
007b8711 mov ecx, dword ptr [edi + 0xc]
007b8714 xor edx, eax
007b8716 mov eax, edx
007b8718 shr eax, cl
007b871a mov ecx, 0xf
007b871f xor eax, edx
007b8721 xor edx, edx
007b8723 mov dword ptr [edi], eax
007b8725 div ecx
007b8727 test edx, edx
007b8729 jne 0x7b874b
007b872b mov ecx, dword ptr [0xbfd65c]
007b8731 push 1
007b8733 push edx
007b8734 push 0x48
007b8736 lea ecx, [ecx + 0x1ba40]
007b873c call 0x91d550
007b8741 test eax, eax
007b8743 mov ecx, 0x5a
007b8748 cmovne esi, ecx
007b874b mov edx, dword ptr [edi]
007b874d test edx, edx
007b874f jne 0x7b8767
007b8751 push 0xb4d6c4
007b8756 push 3
007b8758 call 0x95e330
007b875d mov edx, dword ptr [edi]
007b875f add esp, 8
007b8762 test edx, edx
007b8764 jne 0x7b8767
007b8766 int3 
007b8767 mov ecx, dword ptr [edi + 4]
007b876a mov eax, edx
007b876c shr eax, cl
007b876e mov ecx, dword ptr [edi + 8]
007b8771 xor eax, edx
007b8773 mov edx, eax
007b8775 shl edx, cl
007b8777 mov ecx, dword ptr [edi + 0xc]
007b877a xor edx, eax
007b877c mov eax, edx
007b877e shr eax, cl
007b8780 xor eax, edx
007b8782 mov ecx, dword ptr [0xbfd65c]
007b8788 xor edx, edx
007b878a mov dword ptr [edi], eax
007b878c div ebx
007b878e push 1
007b8790 test edx, edx
007b8792 lea ecx, [ecx + 0x1ba40]
007b8798 push 0
007b879a mov eax, 0x45
007b879f push 0x2d
007b87a1 cmove esi, eax
007b87a4 call 0x91d550
007b87a9 test eax, eax
007b87ab je 0x7b87fd
007b87ad mov edx, dword ptr [edi]
007b87af test edx, edx
007b87b1 jne 0x7b87c9
007b87b3 push 0xb4d6c4
007b87b8 push 3
007b87ba call 0x95e330
007b87bf mov edx, dword ptr [edi]
007b87c1 add esp, 8
007b87c4 test edx, edx
007b87c6 jne 0x7b87c9
007b87c8 int3 
007b87c9 mov ecx, dword ptr [edi + 4]
007b87cc mov eax, edx
007b87ce shr eax, cl
007b87d0 mov ecx, dword ptr [edi + 8]
007b87d3 xor eax, edx
007b87d5 mov edx, eax
007b87d7 shl edx, cl
007b87d9 mov ecx, dword ptr [edi + 0xc]
007b87dc xor edx, eax
007b87de mov eax, edx
007b87e0 shr eax, cl
007b87e2 mov ecx, 0xa
007b87e7 xor eax, edx
007b87e9 xor edx, edx
007b87eb mov dword ptr [edi], eax
007b87ed div ecx
007b87ef test edx, edx
007b87f1 jne 0x7b87fd
007b87f3 mov esi, 0x12c
007b87f8 jmp 0x7b898c
007b87fd mov ecx, dword ptr [0xbfd65c]
007b8803 push 1
007b8805 push 0
007b8807 push 0x2c
007b8809 lea ecx, [ecx + 0x1ba40]
007b880f call 0x91d550
007b8814 test eax, eax
007b8816 je 0x7b8866
007b8818 mov edx, dword ptr [edi]
007b881a test edx, edx
007b881c jne 0x7b8834
007b881e push 0xb4d6c4
007b8823 push 3
007b8825 call 0x95e330
007b882a mov edx, dword ptr [edi]
007b882c add esp, 8
007b882f test edx, edx
007b8831 jne 0x7b8834
007b8833 int3 
007b8834 mov ecx, dword ptr [edi + 4]
007b8837 mov eax, edx
007b8839 shr eax, cl
007b883b mov ecx, dword ptr [edi + 8]
007b883e xor eax, edx
007b8840 mov edx, eax
007b8842 shl edx, cl
007b8844 mov ecx, dword ptr [edi + 0xc]
007b8847 xor edx, eax
007b8849 mov eax, edx
007b884b shr eax, cl
007b884d mov ecx, 0xa
007b8852 xor eax, edx
007b8854 xor edx, edx
007b8856 mov dword ptr [edi], eax
007b8858 div ecx
007b885a test edx, edx
007b885c jne 0x7b8866
007b885e lea esi, [ecx + 0x3c]
007b8861 jmp 0x7b898c
007b8866 mov ecx, dword ptr [0xbfd65c]
007b886c push 1
007b886e push 0
007b8870 push 0x29
007b8872 lea ecx, [ecx + 0x1ba40]
007b8878 call 0x91d550
007b887d test eax, eax
007b887f je 0x7b88cf
007b8881 mov edx, dword ptr [edi]
007b8883 test edx, edx
007b8885 jne 0x7b889d
007b8887 push 0xb4d6c4
007b888c push 3
007b888e call 0x95e330
007b8893 mov edx, dword ptr [edi]
007b8895 add esp, 8
007b8898 test edx, edx
007b889a jne 0x7b889d
007b889c int3 
007b889d mov ecx, dword ptr [edi + 4]
007b88a0 mov eax, edx
007b88a2 shr eax, cl
007b88a4 mov ecx, dword ptr [edi + 8]
007b88a7 xor eax, edx
007b88a9 mov edx, eax
007b88ab shl edx, cl
007b88ad mov ecx, dword ptr [edi + 0xc]
007b88b0 xor edx, eax
007b88b2 mov eax, edx
007b88b4 shr eax, cl
007b88b6 mov ecx, 0xa
007b88bb xor eax, edx
007b88bd xor edx, edx
007b88bf mov dword ptr [edi], eax
007b88c1 div ecx
007b88c3 test edx, edx
007b88c5 jne 0x7b88cf
007b88c7 lea esi, [ecx + 0x1e]
007b88ca jmp 0x7b898c
007b88cf mov ecx, dword ptr [0xbfd65c]
007b88d5 push 1
007b88d7 push 0
007b88d9 push 0x22
007b88db lea ecx, [ecx + 0x1ba40]
007b88e1 call 0x91d550
007b88e6 test eax, eax
007b88e8 je 0x7b895e
007b88ea mov edx, dword ptr [edi]
007b88ec test edx, edx
007b88ee jne 0x7b8906
007b88f0 push 0xb4d6c4
007b88f5 push 3
007b88f7 call 0x95e330
007b88fc mov edx, dword ptr [edi]
007b88fe add esp, 8
007b8901 test edx, edx
007b8903 jne 0x7b8906
007b8905 int3 
007b8906 mov ecx, dword ptr [edi + 4]
007b8909 mov eax, edx
007b890b shr eax, cl
007b890d mov ecx, dword ptr [edi + 8]
007b8910 xor eax, edx
007b8912 mov edx, eax
007b8914 shl edx, cl
007b8916 mov ecx, dword ptr [edi + 0xc]
007b8919 xor edx, eax
007b891b mov eax, edx
007b891d shr eax, cl
007b891f mov ecx, 0xa
007b8924 xor eax, edx
007b8926 xor edx, edx
007b8928 mov dword ptr [edi], eax
007b892a div ecx
007b892c test edx, edx
007b892e jne 0x7b895e
007b8930 mov ecx, dword ptr [0xbfd65c]
007b8936 push 1
007b8938 push edx
007b8939 push 0x16
007b893b lea ecx, [ecx + 0x1ba40]
007b8941 call 0x91d550
007b8946 test eax, eax
007b8948 je 0x7b8957
007b894a push 5
007b894c mov ecx, edi
007b894e call 0x7a7d50
007b8953 test eax, eax
007b8955 jne 0x7b895e
007b8957 mov esi, 0xa
007b895c jmp 0x7b898c
007b895e mov ecx, dword ptr [0xbfd65c]
007b8964 push 1
007b8966 push 0
007b8968 push 0x24
007b896a lea ecx, [ecx + 0x1ba40]
007b8970 call 0x91d550
007b8975 test eax, eax
007b8977 je 0x7b898c
007b8979 push 0xa
007b897b mov ecx, edi
007b897d call 0x7a7d50
007b8982 test eax, eax
007b8984 mov ecx, 0x1e
007b8989 cmove esi, ecx
007b898c mov ecx, dword ptr [0xbfd65c]
007b8992 push 1
007b8994 add ecx, 0x1ba40
007b899a push ecx
007b899b push 0x1df
007b89a0 call 0x91d340
007b89a5 test eax, eax
007b89a7 je 0x7b89f0
007b89a9 mov edx, dword ptr [edi]
007b89ab test edx, edx
007b89ad jne 0x7b89c5
007b89af push 0xb4d6c4
007b89b4 push 3
007b89b6 call 0x95e330
007b89bb mov edx, dword ptr [edi]
007b89bd add esp, 8
007b89c0 test edx, edx
007b89c2 jne 0x7b89c5
007b89c4 int3 
007b89c5 mov ecx, dword ptr [edi + 4]
007b89c8 mov eax, edx
007b89ca shr eax, cl
007b89cc mov ecx, dword ptr [edi + 8]
007b89cf xor eax, edx
007b89d1 mov edx, eax
007b89d3 shl edx, cl
007b89d5 mov ecx, dword ptr [edi + 0xc]
007b89d8 xor edx, eax
007b89da mov eax, edx
007b89dc shr eax, cl
007b89de xor eax, edx
007b89e0 xor edx, edx
007b89e2 mov dword ptr [edi], eax
007b89e4 div ebx
007b89e6 mov eax, 0x15e
007b89eb test edx, edx
007b89ed cmove esi, eax
007b89f0 mov ecx, dword ptr [0xbfd65c]
007b89f6 push 1
007b89f8 add ecx, 0x1ba40
007b89fe push ecx
007b89ff push 0x86
007b8a04 call 0x91d340
007b8a09 test eax, eax
007b8a0b je 0x7b8aff
007b8a11 mov edx, dword ptr [edi]
007b8a13 test edx, edx
007b8a15 jne 0x7b8a2d
007b8a17 push 0xb4d6c4
007b8a1c push 3
007b8a1e call 0x95e330
007b8a23 mov edx, dword ptr [edi]
007b8a25 add esp, 8
007b8a28 test edx, edx
007b8a2a jne 0x7b8a2d
007b8a2c int3 
007b8a2d mov ecx, dword ptr [edi + 4]
007b8a30 mov eax, edx
007b8a32 shr eax, cl
007b8a34 mov ecx, dword ptr [edi + 8]
007b8a37 xor eax, edx
007b8a39 mov edx, eax
007b8a3b shl edx, cl
007b8a3d mov ecx, dword ptr [edi + 0xc]
007b8a40 xor edx, eax
007b8a42 mov ebx, edx
007b8a44 shr ebx, cl
007b8a46 mov ecx, 3
007b8a4b xor ebx, edx
007b8a4d xor edx, edx
007b8a4f mov eax, ebx
007b8a51 mov dword ptr [edi], ebx
007b8a53 div ecx
007b8a55 test edx, edx
007b8a57 jne 0x7b8aa8
007b8a59 test ebx, ebx
007b8a5b jne 0x7b8a72
007b8a5d push 0xb4d6c4
007b8a62 push ecx
007b8a63 call 0x95e330
007b8a68 mov ebx, dword ptr [edi]
007b8a6a add esp, 8
007b8a6d test ebx, ebx
007b8a6f jne 0x7b8a72
007b8a71 int3 
007b8a72 mov ecx, dword ptr [edi + 4]
007b8a75 mov eax, ebx
007b8a77 shr eax, cl
007b8a79 mov ecx, dword ptr [edi + 8]
007b8a7c xor eax, ebx
007b8a7e mov esi, eax
007b8a80 shl esi, cl
007b8a82 mov ecx, dword ptr [edi + 0xc]
007b8a85 xor esi, eax
007b8a87 mov edx, esi
007b8a89 mov eax, 0x32
007b8a8e shr edx, cl
007b8a90 mov ecx, 0x3c
007b8a95 xor edx, esi
007b8a97 test dl, 1
007b8a9a mov dword ptr [edi], edx
007b8a9c cmovne eax, ecx
007b8a9f pop edi
007b8aa0 pop esi
007b8aa1 pop ebx
007b8aa2 mov esp, ebp
007b8aa4 pop ebp
007b8aa5 ret 8
007b8aa8 cmp byte ptr [ebp + 0xc], 0
007b8aac jne 0x7b8aff
007b8aae test ebx, ebx
007b8ab0 jne 0x7b8ac8
007b8ab2 push 0xb4d6c4
007b8ab7 push 3
007b8ab9 call 0x95e330
007b8abe mov ebx, dword ptr [edi]
007b8ac0 add esp, 8
007b8ac3 test ebx, ebx
007b8ac5 jne 0x7b8ac8
007b8ac7 int3 
007b8ac8 mov ecx, dword ptr [edi + 4]
007b8acb mov eax, ebx
007b8acd shr eax, cl
007b8acf mov ecx, dword ptr [edi + 8]
007b8ad2 xor eax, ebx
007b8ad4 mov edx, eax
007b8ad6 shl edx, cl
007b8ad8 mov ecx, dword ptr [edi + 0xc]
007b8adb xor edx, eax
007b8add mov eax, edx
007b8adf shr eax, cl
007b8ae1 mov ecx, 3
007b8ae6 xor eax, edx
007b8ae8 xor edx, edx
007b8aea mov dword ptr [edi], eax
007b8aec div ecx
007b8aee neg edx
007b8af0 sbb edx, edx
007b8af2 and edx, esi
007b8af4 mov eax, edx
007b8af6 pop edi
007b8af7 pop esi
007b8af8 pop ebx
007b8af9 mov esp, ebp
007b8afb pop ebp
007b8afc ret 8
007b8aff pop edi
007b8b00 mov eax, esi
007b8b02 pop esi
007b8b03 pop ebx
007b8b04 mov esp, ebp
007b8b06 pop ebp
007b8b07 ret 8
