0074ad55 push 0
0074ad57 push 0x37
0074ad59 mov ecx, edi
0074ad5b call 0x73af30
0074ad60 push 0
0074ad62 push 0x57
0074ad64 mov ecx, edi
0074ad66 mov byte ptr [esp + 0x1a], al
0074ad6a call 0x73af30
0074ad6f push 0
0074ad71 push 0xe5
0074ad76 mov ecx, edi
0074ad78 mov byte ptr [esp + 0x19], al
0074ad7c call 0x73af30
0074ad81 mov esi, dword ptr [ebp + 0xc]
0074ad84 mov byte ptr [esp + 0x13], al
0074ad88 cmp esi, 8
0074ad8b jne 0x74adb0
0074ad8d cmp byte ptr [esp + 0x12], 0
0074ad92 mov al, byte ptr [esp + 0x11]
0074ad96 jne 0x74ada6
0074ad98 test al, al
0074ad9a jne 0x74ada6
0074ad9c xor cl, cl
0074ad9e mov byte ptr [ebx + 0x1d], cl
0074ada1 jmp 0x74ae4a
0074ada6 mov cl, 1
0074ada8 mov byte ptr [ebx + 0x1d], cl
0074adab jmp 0x74ae4a
0074adb0 cmp byte ptr [esp + 0x12], 0
0074adb5 movss xmm2, dword ptr [0xb6a19c]
0074adbd je 0x74adfd
0074adbf call 0x6c3d90
0074adc4 movd xmm0, eax
0074adc8 cvtdq2pd xmm0, xmm0
0074adcc shr eax, 0x1f
0074adcf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0074add8 cvtpd2ps xmm1, xmm0
0074addc movss xmm0, dword ptr [edi + 0x14b0]
0074ade4 mulss xmm0, dword ptr [0xb6a2cc]
0074adec mulss xmm1, xmm2
0074adf0 addss xmm0, dword ptr [0xb6a480]
0074adf8 comiss xmm0, xmm1
0074adfb ja 0x74ae42
0074adfd cmp byte ptr [esp + 0x11], 0
0074ae02 je 0x74ae4d
0074ae04 call 0x6c3d90
0074ae09 movd xmm0, eax
0074ae0d cvtdq2pd xmm0, xmm0
0074ae11 shr eax, 0x1f
0074ae14 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0074ae1d cvtpd2ps xmm1, xmm0
0074ae21 movss xmm0, dword ptr [edi + 0x14b0]
0074ae29 mulss xmm0, dword ptr [0xb6a274]
0074ae31 mulss xmm1, xmm2
0074ae35 addss xmm0, dword ptr [0xb6a38c]
0074ae3d comiss xmm0, xmm1
0074ae40 jbe 0x74ae4d
0074ae42 mov al, byte ptr [esp + 0x11]
0074ae46 mov byte ptr [ebx + 0x1d], 1
0074ae4a mov byte ptr [ebx + 0x1e], al
