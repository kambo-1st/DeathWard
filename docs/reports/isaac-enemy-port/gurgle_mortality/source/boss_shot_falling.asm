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
