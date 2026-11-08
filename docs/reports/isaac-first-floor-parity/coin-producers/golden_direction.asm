006c3450 push ebp
006c3451 mov ebp, esp
006c3453 and esp, 0xfffffff8
006c3456 sub esp, 0x24
006c3459 movss xmm0, dword ptr [0xc02fec]
006c3461 push ebx
006c3462 push esi
006c3463 mov esi, dword ptr [ebp + 0xc]
006c3466 xor ebx, ebx
006c3468 push edi
006c3469 mov edi, ecx
006c346b mov dword ptr [esp + 0x14], edx
006c346f mov dword ptr [esp + 0x10], ebx
006c3473 movss dword ptr [edi], xmm0
006c3477 movss xmm0, dword ptr [0xc02ff0]
006c347f movss dword ptr [edi + 4], xmm0
006c3484 test esi, esi
006c3486 je 0x6c3537
006c348c mov edx, dword ptr [esi]
006c348e test edx, edx
006c3490 jne 0x6c34a8
006c3492 push 0xb4d6c4
006c3497 push 3
006c3499 call 0x95e330
006c349e mov edx, dword ptr [esi]
006c34a0 add esp, 8
006c34a3 test edx, edx
006c34a5 jne 0x6c34a8
006c34a7 int3 
006c34a8 mov ecx, dword ptr [esi + 4]
006c34ab mov eax, edx
006c34ad movq xmm0, qword ptr [0xa08b78]
006c34b5 shr eax, cl
006c34b7 mov ecx, dword ptr [esi + 8]
006c34ba xor eax, edx
006c34bc mov edx, eax
006c34be movq qword ptr [esp + 0x24], xmm0
006c34c4 shl edx, cl
006c34c6 mov ecx, dword ptr [esi + 0xc]
006c34c9 xor edx, eax
006c34cb mov eax, edx
006c34cd shr eax, cl
006c34cf mov ecx, dword ptr [0xa08b80]
006c34d5 mov ebx, eax
006c34d7 xor ebx, edx
006c34d9 mov dword ptr [esp + 0xc], ecx
006c34dd mov dword ptr [esi], ebx
006c34df cmp eax, edx
006c34e1 jne 0x6c34f3
006c34e3 push 0xb4d6c4
006c34e8 push 3
006c34ea call 0x95e330
006c34ef add esp, 8
006c34f2 int3 
006c34f3 mov ecx, dword ptr [esp + 0x24]
006c34f7 mov edx, ebx
006c34f9 shr edx, cl
006c34fb mov ecx, dword ptr [esp + 0x28]
006c34ff xor edx, ebx
006c3501 mov eax, edx
006c3503 mov ebx, dword ptr [esp + 0x10]
006c3507 shl eax, cl
006c3509 mov ecx, dword ptr [esp + 0xc]
006c350d xor eax, edx
006c350f mov edx, eax
006c3511 shr edx, cl
006c3513 xor edx, eax
006c3515 movd xmm0, edx
006c3519 cvtdq2pd xmm0, xmm0
006c351d shr edx, 0x1f
006c3520 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
006c3529 cvtpd2ps xmm0, xmm0
006c352d mulss xmm0, dword ptr [0xb6a198]
006c3535 jmp 0x6c355c
006c3537 call 0x6c3d90
006c353c movd xmm0, eax
006c3540 cvtdq2pd xmm0, xmm0
006c3544 shr eax, 0x1f
006c3547 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006c3550 cvtpd2ps xmm0, xmm0
006c3554 mulss xmm0, dword ptr [0xb6a19c]
006c355c mulss xmm0, dword ptr [0xb6a874]
006c3564 addss xmm0, xmm0
006c3568 movss dword ptr [esp + 0xc], xmm0
006c356e call 0x411fe0
006c3573 mulss xmm0, dword ptr [0xb6a8f4]
006c357b movss dword ptr [esp + 0x10], xmm0
006c3581 movss xmm0, dword ptr [esp + 0xc]
006c3587 call 0x412010
006c358c cmp dword ptr [ebp + 8], 0
006c3590 mulss xmm0, dword ptr [0xb6a8f4]
006c3598 mov ecx, dword ptr [0xbfd65c]
006c359e movss xmm1, dword ptr [esp + 0x10]
006c35a4 movss dword ptr [edi], xmm1
006c35a8 movss dword ptr [edi + 4], xmm0
006c35ad jne 0x6c35d1
006c35af mov eax, dword ptr [ecx + 0x18190]
006c35b5 cmp dword ptr [eax + 8], 0xb
006c35b9 jne 0x6c35e6
006c35bb mulss xmm1, dword ptr [0xb6a434]
006c35c3 mulss xmm0, dword ptr [0xb6a434]
006c35cb movss dword ptr [edi], xmm1
006c35cf jmp 0x6c35e1
006c35d1 mulss xmm0, dword ptr [0xb6a350]
006c35d9 addss xmm0, dword ptr [0xb6a864]
006c35e1 movss dword ptr [edi + 4], xmm0
006c35e6 mov eax, dword ptr [esp + 0x14]
006c35ea lea edx, [esp + 0x18]
006c35ee mulss xmm1, dword ptr [0xb6a928]
006c35f6 mov ecx, dword ptr [ecx + 0x18190]
006c35fc mulss xmm0, dword ptr [0xb6a928]
006c3604 push 0
006c3606 addss xmm1, dword ptr [eax]
006c360a push 0
006c360c addss xmm0, dword ptr [eax + 4]
006c3611 push 0
006c3613 push 0
006c3615 push 1
006c3617 push edx
006c3618 push eax
006c3619 movss dword ptr [esp + 0x34], xmm1
006c361f movss dword ptr [esp + 0x38], xmm0
006c3625 call 0x7af4b0
006c362a test al, al
006c362c jne 0x6c363c
006c362e inc ebx
006c362f mov dword ptr [esp + 0x10], ebx
006c3633 cmp ebx, 0xa
006c3636 jl 0x6c3484
006c363c mov eax, edi
006c363e pop edi
006c363f pop esi
006c3640 pop ebx
006c3641 mov esp, ebp
006c3643 pop ebp
006c3644 ret 
