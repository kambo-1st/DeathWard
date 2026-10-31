004efb00 push ebp
004efb01 mov ebp, esp
004efb03 and esp, 0xfffffff8
004efb06 sub esp, 0x2c
004efb09 push ebx
004efb0a push esi
004efb0b push edi
004efb0c call 0x6c3d90
004efb11 movd xmm0, eax
004efb15 cvtdq2pd xmm0, xmm0
004efb19 shr eax, 0x1f
004efb1c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004efb25 cvtpd2ps xmm0, xmm0
004efb29 mulss xmm0, dword ptr [0xb6a19c]
004efb31 mulss xmm0, dword ptr [0xb6a98c]
004efb39 movss dword ptr [esp + 0xc], xmm0
004efb3f call 0x6c3d90
004efb44 movd xmm0, eax
004efb48 cvtdq2pd xmm0, xmm0
004efb4c shr eax, 0x1f
004efb4f addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004efb58 cvtpd2ps xmm0, xmm0
004efb5c mulss xmm0, dword ptr [0xb6a19c]
004efb64 mulss xmm0, dword ptr [0xb6a874]
004efb6c addss xmm0, xmm0
004efb70 movss dword ptr [esp + 0x18], xmm0
004efb76 call 0x411fe0
004efb7b mulss xmm0, dword ptr [esp + 0xc]
004efb81 movss dword ptr [esp + 0x28], xmm0
004efb87 movss xmm0, dword ptr [esp + 0x18]
004efb8d call 0x412010
004efb92 mulss xmm0, dword ptr [esp + 0xc]
004efb98 movss dword ptr [esp + 0x2c], xmm0
004efb9e call 0x6c3d90
004efba3 mov ecx, dword ptr [ebp + 8]
004efba6 mov esi, dword ptr [0xbfd65c]
004efbac mov dword ptr [esp + 0x10], eax
004efbb0 lea eax, [esp + 0x10]
004efbb4 push eax
004efbb5 movss xmm1, dword ptr [ecx + 0x294]
004efbbd lea eax, [esp + 0x18]
004efbc1 push eax
004efbc2 push 0
004efbc4 lea eax, [esp + 0x34]
004efbc8 movss dword ptr [esp + 0x3c], xmm1
004efbce movss xmm1, dword ptr [ecx + 0x298]
004efbd6 push eax
004efbd7 lea eax, [esp + 0x40]
004efbdb movss dword ptr [esp + 0x44], xmm1
004efbe1 push eax
004efbe2 lea eax, [esp + 0x2c]
004efbe6 mov dword ptr [esp + 0x28], 3
004efbee push eax
004efbef lea eax, [esp + 0x24]
004efbf3 mov dword ptr [esp + 0x30], 2
004efbfb push eax
004efbfc mov dword ptr [esp + 0x28], 0x3e8
004efc04 call 0x800fb0
004efc09 mov ecx, dword ptr [esi + 0x1c3198]
004efc0f push 0
004efc11 push dword ptr [esp + 0x10]
004efc15 call 0x6c4b30
004efc1a mov ebx, eax
004efc1c test ebx, ebx
004efc1e je 0x4efe02
004efc24 call dword ptr [0xa064c0]
004efc2a mov ecx, dword ptr [ebx + 0x320]
004efc30 lea edi, [ebx + 0x320]
004efc36 mov dword ptr [esp + 0x24], eax
004efc3a mov dword ptr [ebx + 0x34], 0
004efc41 mov dword ptr [ebx + 0x38], 0
004efc48 test ecx, ecx
004efc4a je 0x4efc60
004efc4c lea eax, [esp + 0x20]
004efc50 mov dword ptr [esp + 0x20], edi
004efc54 push eax
004efc55 add ecx, 0x324
004efc5b call 0x4bc3c0
004efc60 push dword ptr [esp + 0x10]
004efc64 mov eax, dword ptr [ebx]
004efc66 mov ecx, ebx
004efc68 push dword ptr [esp + 0x18]
004efc6c mov dword ptr [edi], 0
004efc72 movss xmm0, dword ptr [esp + 0x38]
004efc78 push dword ptr [esp + 0x20]
004efc7c movss dword ptr [ebx + 0x294], xmm0
004efc84 movss xmm0, dword ptr [esp + 0x40]
004efc8a push dword ptr [esp + 0x18]
004efc8e movss dword ptr [ebx + 0x298], xmm0
004efc96 movss xmm0, dword ptr [esp + 0x38]
004efc9c movss dword ptr [ebx + 0x2b8], xmm0
004efca4 movss xmm0, dword ptr [esp + 0x3c]
004efcaa movss dword ptr [ebx + 0x2bc], xmm0
004efcb2 call dword ptr [eax + 4]
004efcb5 mov edx, dword ptr [esi + 0x18190]
004efcbb push ebx
004efcbc mov ecx, dword ptr [edx + 0x1214]
004efcc2 lea eax, [ecx + 1]
004efcc5 mov dword ptr [edx + 0x1214], eax
004efccb mov dword ptr [ebx + 0x20], ecx
004efcce lea ecx, [edx + 0x1218]
004efcd4 call 0x413280
004efcd9 push ebx
004efcda call 0x6d94d0
004efcdf test al, al
004efce1 je 0x4efcea
004efce3 push ecx
004efce4 push ebx
004efce5 call 0x6d9590
004efcea cmp byte ptr [ebx + 0x16a], 0
004efcf1 je 0x4efdf2
004efcf7 mov eax, dword ptr [esi + 0x283c20]
004efcfd cmp eax, dword ptr [esi + 0x283c24]
004efd03 je 0x4efdf2
004efd09 mov eax, dword ptr [ebx + 0x2c]
004efd0c lea ecx, [esi + 0x283c48]
004efd12 mov edi, dword ptr [ebx + 0x28]
004efd15 mov dword ptr [esp + 0x1c], eax
004efd19 lea eax, [esp + 0x18]
004efd1d push eax
004efd1e lea eax, [esp + 0x24]
004efd22 mov dword ptr [esp + 0x1c], edi
004efd26 push eax
004efd27 call 0x937c80
004efd2c mov eax, dword ptr [esi + 0x283c48]
004efd32 cmp dword ptr [esp + 0x20], eax
004efd36 jne 0x4efd67
004efd38 lea eax, [esp + 0x18]
004efd3c mov dword ptr [esp + 0x18], edi
004efd40 push eax
004efd41 lea eax, [esp + 0x24]
004efd45 mov dword ptr [esp + 0x20], 0xffffffff
004efd4d push eax
004efd4e lea ecx, [esi + 0x283c48]
004efd54 call 0x937c80
004efd59 mov ecx, dword ptr [esi + 0x283c48]
004efd5f cmp dword ptr [eax], ecx
004efd61 je 0x4efdf2
004efd67 mov esi, dword ptr [0xbfd65c]
004efd6d xor edi, edi
004efd6f mov eax, dword ptr [esi + 0x1ba54]
004efd75 sub eax, dword ptr [esi + 0x1ba50]
004efd7b sar eax, 2
004efd7e test eax, eax
004efd80 je 0x4efdf2
004efd82 mov ecx, dword ptr [esi + 0x1ba54]
004efd88 mov eax, ecx
004efd8a sub eax, dword ptr [esi + 0x1ba50]
004efd90 test eax, 0xfffffffc
004efd95 jne 0x4efdac
004efd97 push 0xb3f4d0
004efd9c push 3
004efd9e call 0x95e330
004efda3 mov ecx, dword ptr [esi + 0x1ba54]
004efda9 add esp, 8
004efdac mov eax, dword ptr [esi + 0x1ba50]
004efdb2 sub ecx, eax
004efdb4 sar ecx, 2
004efdb7 cmp edi, ecx
004efdb9 jae 0x4efdbe
004efdbb lea eax, [eax + edi*4]
004efdbe lea ecx, [esp + 0x28]
004efdc2 push ecx
004efdc3 lea ecx, [esp + 0x34]
004efdc7 push ecx
004efdc8 mov ecx, dword ptr [eax]
004efdca push ebx
004efdcb push 6
004efdcd add ecx, 0x1ec0
004efdd3 call 0x935fd0
004efdd8 mov esi, dword ptr [0xbfd65c]
004efdde inc edi
004efddf mov eax, dword ptr [esi + 0x1ba54]
004efde5 sub eax, dword ptr [esi + 0x1ba50]
004efdeb sar eax, 2
004efdee cmp edi, eax
004efdf0 jb 0x4efd82
004efdf2 call dword ptr [0xa064c0]
004efdf8 sub eax, dword ptr [esp + 0x24]
004efdfc add dword ptr [0xbffe0c], eax
004efe02 movss xmm0, dword ptr [esp + 0x28]
004efe08 movss xmm1, dword ptr [esp + 0x2c]
004efe0e addss xmm0, dword ptr [0xb6a18c]
004efe16 subss xmm1, dword ptr [0xb6a9f4]
004efe1e pop edi
004efe1f pop esi
004efe20 movss dword ptr [ebx + 0xd0], xmm0
004efe28 movss dword ptr [ebx + 0xd4], xmm1
004efe30 pop ebx
004efe31 mov esp, ebp
004efe33 pop ebp
004efe34 ret 
