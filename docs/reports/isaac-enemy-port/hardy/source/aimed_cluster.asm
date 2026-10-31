006a3420 push ebp
006a3421 mov ebp, esp
006a3423 and esp, 0xfffffff8
006a3426 sub esp, 0x2c
006a3429 movss xmm0, dword ptr [0xb6a614]
006a3431 xor eax, eax
006a3433 push ebx
006a3434 mov ebx, ecx
006a3436 movss dword ptr [esp + 0x10], xmm0
006a343c push esi
006a343d push edi
006a343e mov edx, dword ptr [ebx + 0x164]
006a3444 and edx, 0x400000
006a344a or eax, edx
006a344c je 0x6a345c
006a344e movss xmm0, dword ptr [0xb6a560]
006a3456 movss dword ptr [esp + 0x18], xmm0
006a345c cmp dword ptr [ebp + 8], 0
006a3460 jle 0x6a395a
006a3466 movss xmm0, dword ptr [ebp + 0x10]
006a346b mulss xmm0, dword ptr [0xb6a2cc]
006a3473 mov esi, dword ptr [ebp + 0x14]
006a3476 movss xmm2, dword ptr [0xb6a19c]
006a347e movss xmm3, dword ptr [0xb6a874]
006a3486 addss xmm0, dword ptr [0xb6a3c4]
006a348e movss dword ptr [esp + 0x24], xmm0
006a3494 nop dword ptr [eax]
006a3498 nop dword ptr [eax + eax]
006a34a0 mov ecx, dword ptr [ebp + 0xc]
006a34a3 movss xmm1, dword ptr [ecx]
006a34a7 ucomiss xmm1, dword ptr [0xc02fec]
006a34ae lahf 
006a34af test ah, 0x44
006a34b2 jp 0x6a3531
006a34b4 movss xmm0, dword ptr [ecx + 4]
006a34b9 ucomiss xmm0, dword ptr [0xc02ff0]
006a34c0 lahf 
006a34c1 test ah, 0x44
006a34c4 jp 0x6a3531
006a34c6 call 0x6c3d90
006a34cb xorps xmm0, xmm0
006a34ce cvtsi2sd xmm0, eax
006a34d2 shr eax, 0x1f
006a34d5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a34de cvtpd2ps xmm0, xmm0
006a34e2 mulss xmm0, xmm2
006a34e6 mulss xmm0, xmm3
006a34ea addss xmm0, xmm0
006a34ee movss dword ptr [esp + 0x14], xmm0
006a34f4 call 0x411fe0
006a34f9 mulss xmm0, dword ptr [0xb6a928]
006a3501 movss dword ptr [esp + 0x10], xmm0
006a3507 movss xmm0, dword ptr [esp + 0x14]
006a350d call 0x412010
006a3512 mulss xmm0, dword ptr [0xb6a928]
006a351a movss xmm1, dword ptr [esp + 0x10]
006a3520 movss dword ptr [esp + 0x28], xmm1
006a3526 movss dword ptr [esp + 0x2c], xmm0
006a352c jmp 0x6a3655
006a3531 movss xmm0, dword ptr [ecx + 4]
006a3536 subss xmm1, dword ptr [ebx + 0x294]
006a353e subss xmm0, dword ptr [ebx + 0x298]
006a3546 movss dword ptr [esp + 0xc], xmm1
006a354c movss dword ptr [esp + 0x10], xmm0
006a3552 call 0x6c3d90
006a3557 xorps xmm0, xmm0
006a355a cvtsi2sd xmm0, eax
006a355e shr eax, 0x1f
006a3561 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a356a cvtpd2ps xmm0, xmm0
006a356e mulss xmm0, xmm2
006a3572 movss dword ptr [esp + 0x14], xmm0
006a3578 call 0x6c3d90
006a357d xorps xmm0, xmm0
006a3580 cvtsi2sd xmm0, eax
006a3584 shr eax, 0x1f
006a3587 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a3590 cvtpd2ps xmm0, xmm0
006a3594 mulss xmm0, xmm2
006a3598 mulss xmm0, xmm3
006a359c addss xmm0, xmm0
006a35a0 movss dword ptr [esp + 0x1c], xmm0
006a35a6 call 0x411fe0
006a35ab mulss xmm0, dword ptr [esp + 0x14]
006a35b1 mulss xmm0, dword ptr [0xb6a8a0]
006a35b9 movss dword ptr [esp + 0x20], xmm0
006a35bf movss xmm0, dword ptr [esp + 0x1c]
006a35c5 call 0x412010
006a35ca mulss xmm0, dword ptr [esp + 0x14]
006a35d0 movss xmm1, dword ptr [esp + 0x10]
006a35d6 mulss xmm1, xmm1
006a35da mulss xmm0, dword ptr [0xb6a8a0]
006a35e2 movss dword ptr [esp + 0x1c], xmm0
006a35e8 movss xmm0, dword ptr [esp + 0xc]
006a35ee mulss xmm0, xmm0
006a35f2 addss xmm0, xmm1
006a35f6 call 0x4228c0
006a35fb comiss xmm0, dword ptr [0xb6a18c]
006a3602 jbe 0x6a3621
006a3604 movss xmm1, dword ptr [0xb6a614]
006a360c divss xmm1, xmm0
006a3610 movaps xmm0, xmm1
006a3613 mulss xmm1, dword ptr [esp + 0x10]
006a3619 mulss xmm0, dword ptr [esp + 0xc]
006a361f jmp 0x6a362d
006a3621 movss xmm0, dword ptr [esp + 0xc]
006a3627 movss xmm1, dword ptr [esp + 0x10]
006a362d mulss xmm0, dword ptr [0xb6a928]
006a3635 mulss xmm1, dword ptr [0xb6a928]
006a363d addss xmm0, dword ptr [esp + 0x20]
006a3643 addss xmm1, dword ptr [esp + 0x1c]
006a3649 movss dword ptr [esp + 0x28], xmm0
006a364f movss dword ptr [esp + 0x2c], xmm1
006a3655 call 0x6c3d90
006a365a movss xmm0, dword ptr [ebx + 0x294]
006a3662 addss xmm0, dword ptr [esi + 0x60]
006a3667 mov ecx, dword ptr [0xbfd65c]
006a366d push 0
006a366f push eax
006a3670 push 0
006a3672 push ebx
006a3673 lea eax, [esp + 0x38]
006a3677 movss dword ptr [esp + 0x40], xmm0
006a367d movss xmm0, dword ptr [ebx + 0x298]
006a3685 addss xmm0, dword ptr [esi + 0x64]
006a368a push eax
006a368b lea eax, [esp + 0x44]
006a368f push eax
006a3690 push dword ptr [esi + 0x94]
006a3696 movss dword ptr [esp + 0x50], xmm0
006a369c push 9
006a369e call 0x6d0ca0
006a36a3 push 0
006a36a5 push 0xbeabf4
006a36aa push 0xbeab18
006a36af push 0
006a36b1 push eax
006a36b2 call 0x9ec34c
006a36b7 movss xmm0, dword ptr [esp + 0x38]
006a36bd mov edi, eax
006a36bf add esp, 0x14
006a36c2 movss dword ptr [edi + 0x368], xmm0
006a36ca call 0x6c3d90
006a36cf movd xmm0, eax
006a36d3 cvtdq2pd xmm0, xmm0
006a36d7 shr eax, 0x1f
006a36da addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a36e3 cvtpd2ps xmm1, xmm0
006a36e7 movss xmm0, dword ptr [0xb6a8f4]
006a36ef mulss xmm1, dword ptr [0xb6a19c]
006a36f7 mulss xmm1, dword ptr [0xb6aa0c]
006a36ff mulss xmm1, dword ptr [0xb6a560]
006a3707 subss xmm0, xmm1
006a370b subss xmm0, dword ptr [ebp + 0x10]
006a3710 movss dword ptr [edi + 0x364], xmm0
006a3718 call 0x6c3d90
006a371d mov esi, eax
006a371f and esi, 1
006a3722 call 0x6c3d90
006a3727 movd xmm0, eax
006a372b cvtdq2pd xmm0, xmm0
006a372f shr eax, 0x1f
006a3732 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a373b cvtpd2ps xmm1, xmm0
006a373f movd xmm0, esi
006a3743 mulss xmm1, dword ptr [0xb6a19c]
006a374b shr esi, 0x1f
006a374e cvtdq2pd xmm0, xmm0
006a3752 mulss xmm1, dword ptr [0xb6a274]
006a375a addsd xmm0, qword ptr [esi*8 + 0xb6c940]
006a3763 mov esi, dword ptr [ebp + 0x14]
006a3766 cvtpd2ps xmm0, xmm0
006a376a mulss xmm0, dword ptr [0xb6a434]
006a3772 addss xmm0, dword ptr [0xb6a5a4]
006a377a addss xmm0, xmm1
006a377e xorps xmm1, xmm1
006a3781 mulss xmm0, dword ptr [esi + 0x14]
006a3786 mulss xmm0, dword ptr [esp + 0x18]
006a378c movss dword ptr [edi + 0x370], xmm0
006a3794 movss xmm0, dword ptr [esi + 0x9c]
006a379c comiss xmm1, xmm0
006a379f jbe 0x6a37a9
006a37a1 movss xmm0, dword ptr [0xb6a614]
006a37a9 mov eax, dword ptr [edi]
006a37ab push ecx
006a37ac mov ecx, edi
006a37ae movss dword ptr [esp], xmm0
006a37b3 call dword ptr [eax + 0x3c]
006a37b6 mov eax, dword ptr [esi + 0x58]
006a37b9 lea ecx, [esi + 0x2c]
006a37bc or dword ptr [edi + 0x388], eax
006a37c2 mov eax, dword ptr [esi + 0x5c]
006a37c5 or dword ptr [edi + 0x38c], eax
006a37cb movss xmm0, dword ptr [esi + 4]
006a37d0 addss xmm0, dword ptr [edi + 0x360]
006a37d8 mov eax, dword ptr [edi]
006a37da push 1
006a37dc push 0
006a37de push 0xff
006a37e3 movss dword ptr [edi + 0x360], xmm0
006a37eb movss xmm0, dword ptr [edi + 0x368]
006a37f3 addss xmm0, dword ptr [esi + 0xc]
006a37f8 push -1
006a37fa push ecx
006a37fb mov ecx, edi
006a37fd movss dword ptr [edi + 0x368], xmm0
006a3805 movss xmm0, dword ptr [esi + 8]
006a380a addss xmm0, dword ptr [edi + 0x364]
006a3812 movss dword ptr [edi + 0x364], xmm0
006a381a movss xmm1, dword ptr [esi + 0x10]
006a381f movaps xmm0, xmm1
006a3822 mulss xmm1, dword ptr [edi + 0x2bc]
006a382a mulss xmm0, dword ptr [edi + 0x2b8]
006a3832 movss dword ptr [edi + 0x2bc], xmm1
006a383a movss dword ptr [edi + 0x2b8], xmm0
006a3842 call dword ptr [eax + 0x38]
006a3845 mov ecx, dword ptr [edi + 0x314]
006a384b lea esi, [edi + 0x314]
006a3851 test ecx, ecx
006a3853 je 0x6a3869
006a3855 lea eax, [esp + 0x20]
006a3859 mov dword ptr [esp + 0x20], esi
006a385d push eax
006a385e add ecx, 0x324
006a3864 call 0x4bc3c0
006a3869 push esi
006a386a mov ecx, ebx
006a386c mov dword ptr [esi], ebx
006a386e call 0x4bae70
006a3873 mov edx, dword ptr [ebp + 0x14]
006a3876 mov eax, dword ptr [edx + 0x24]
006a3879 mov dword ptr [edi + 0x37c], eax
006a387f movss xmm0, dword ptr [edx + 0x68]
006a3884 movss xmm1, dword ptr [edx + 0x6c]
006a3889 movss dword ptr [edi + 0x28c], xmm0
006a3891 movss dword ptr [edi + 0x290], xmm1
006a3899 mov eax, dword ptr [edx + 0x80]
006a389f mov ecx, dword ptr [edx + 0x84]
006a38a5 mov dword ptr [edi + 0x398], eax
006a38ab mov dword ptr [edi + 0x39c], ecx
006a38b1 mov eax, dword ptr [edx + 0x88]
006a38b7 mov dword ptr [edi + 0x3a0], eax
006a38bd mov eax, dword ptr [edx + 0x8c]
006a38c3 mov dword ptr [edi + 0x3a4], eax
006a38c9 mov eax, dword ptr [edx + 0xa0]
006a38cf mov dword ptr [edi + 0x3b8], eax
006a38d5 cmp byte ptr [ebx + 0xbb3], 0
006a38dc je 0x6a38e6
006a38de mov edx, dword ptr [ebx + 0xbb4]
006a38e4 jmp 0x6a38e9
006a38e6 or edx, 0xffffffff
006a38e9 movss xmm1, dword ptr [ebx + 0xb88]
006a38f1 mov ecx, edi
006a38f3 push ebx
006a38f4 push dword ptr [ebx + 0x164]
006a38fa push dword ptr [ebx + 0x160]
006a3900 call 0x6a1750
006a3905 mov ecx, dword ptr [esi]
006a3907 add esp, 0xc
006a390a test ecx, ecx
006a390c je 0x6a3922
006a390e lea eax, [esp + 0x20]
006a3912 mov dword ptr [esp + 0x20], esi
006a3916 push eax
006a3917 add ecx, 0x324
006a391d call 0x4bc3c0
006a3922 push esi
006a3923 mov ecx, ebx
006a3925 mov dword ptr [esi], ebx
006a3927 call 0x4bae70
006a392c sub dword ptr [ebp + 8], 1
006a3930 mov eax, dword ptr [ebx + 0x28]
006a3933 movss xmm2, dword ptr [0xb6a19c]
006a393b movss xmm3, dword ptr [0xb6a874]
006a3943 mov esi, dword ptr [ebp + 0x14]
006a3946 mov dword ptr [edi + 0x34], eax
006a3949 jne 0x6a34a0
006a394f mov eax, edi
006a3951 pop edi
006a3952 pop esi
006a3953 pop ebx
006a3954 mov esp, ebp
006a3956 pop ebp
006a3957 ret 0x10
