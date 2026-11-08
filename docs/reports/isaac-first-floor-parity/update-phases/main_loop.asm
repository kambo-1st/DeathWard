0088bd40 call 0x970040
0088bd45 movsd qword ptr [ebp - 0x43c], xmm0
0088bd4d subsd xmm0, qword ptr [ebp - 0x434]
0088bd55 movsd qword ptr [ebp - 0x444], xmm0
0088bd5d movsd xmm1, qword ptr [0xb6a778]
0088bd65 divsd xmm1, xmm0
0088bd69 addsd xmm1, qword ptr [0xb6a748]
0088bd71 movsd qword ptr [ebp - 0x434], xmm1
0088bd79 fld qword ptr [ebp - 0x434]
0088bd7f sub esp, 8
0088bd82 fstp qword ptr [esp]
0088bd85 call 0x9ec3b2
0088bd8a add esp, 8
0088bd8d call 0x9ec2c0
0088bd92 mov ecx, dword ptr [0xbfd680]
0088bd98 mov dword ptr [ecx + 0x1ea6bc], eax
0088bd9e movsd xmm0, qword ptr [ebp - 0x43c]
0088bda6 movsd qword ptr [ebp - 0x434], xmm0
0088bdae movsd xmm0, qword ptr [0xb6a658]
0088bdb6 divsd xmm0, qword ptr [ebp - 0x444]
0088bdbe comisd xmm0, xmmword ptr [0xb6a780]
0088bdc6 jbe 0x88bde6
0088bdc8 inc esi
0088bdc9 mov dword ptr [ebp - 0x428], esi
0088bdcf cmp esi, 0x1e
0088bdd2 jbe 0x88bdee
0088bdd4 mov bl, 1
0088bdd6 mov byte ptr [ebp - 0x41d], bl
0088bddc xor edi, edi
0088bdde mov dword ptr [ebp - 0x424], edi
0088bde4 jmp 0x88bdee
0088bde6 xor esi, esi
0088bde8 mov dword ptr [ebp - 0x428], esi
0088bdee xor cl, cl
0088bdf0 call 0x998d60
0088bdf5 call 0x8b0010
0088bdfa call 0x8b0600
0088bdff cmp dword ptr [0xbfd65c], 0
0088be06 je 0x88be0d
0088be08 call 0x8022d0
0088be0d mov eax, dword ptr [0xbc7b08]
0088be12 cmp byte ptr [0xbfd66b], 0
0088be19 jne 0x88beb1
0088be1f push 0
0088be21 push 0x10001
0088be26 call 0x99b7a0
0088be2b add esp, 8
0088be2e test bl, bl
0088be30 jne 0x88be3e
0088be32 cmp byte ptr [0xbc7b0d], bl
0088be38 jne 0x88bd40
0088be3e call 0x970040
0088be43 subsd xmm0, qword ptr [ebp - 0x43c]
0088be4b movsd xmm1, qword ptr [0xb6a658]
0088be53 subsd xmm1, xmm0
0088be57 mulsd xmm1, qword ptr [0xb6ae90]
0088be5f cvttsd2si eax, xmm1
0088be63 not eax
0088be65 mov dword ptr [ebp - 0x42c], eax
0088be6b mov dword ptr [ebp - 0x440], 0
0088be75 xor ecx, ecx
0088be77 test eax, eax
0088be79 cmovg ecx, eax
0088be7c mov dword ptr [ebp - 0x42c], ecx
0088be82 test ecx, ecx
0088be84 je 0x88bece
0088be86 xor edi, edi
0088be88 mov dword ptr [ebp - 0x424], edi
0088be8e mov ecx, dword ptr [0xbfd680]
0088be94 lea ecx, [ecx + 0x20a00]
0088be9a call 0x8b7890
0088be9f test al, al
0088bea1 jne 0x88bef0
0088bea3 push dword ptr [ebp - 0x42c]
0088bea9 call dword ptr [0xa06138]
0088beaf jmp 0x88bef0
0088beb1 cmp byte ptr [eax + 8], 1
0088beb5 jne 0x88be2e
0088bebb call 0x90c280
0088bec0 call 0x998e90
0088bec5 call dword ptr [0xa066a4]
0088becb wait 
0088becc jmp 0x88bf1c
0088bece inc edi
0088becf mov dword ptr [ebp - 0x424], edi
0088bed5 cmp edi, 0x1e
0088bed8 jbe 0x88bef0
0088beda xor bl, bl
0088bedc mov byte ptr [ebp - 0x41d], bl
0088bee2 xor esi, esi
0088bee4 mov dword ptr [ebp - 0x428], esi
0088beea nop word ptr [eax + eax]
0088bef0 call 0x970040
0088bef5 subsd xmm0, qword ptr [ebp - 0x43c]
0088befd movsd xmm1, qword ptr [0xb6a658]
0088bf05 comisd xmm1, xmm0
0088bf09 ja 0x88bef0
0088bf0b jmp 0x88bd40
