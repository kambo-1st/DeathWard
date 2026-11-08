0078c606 call 0x6c3d90
0078c60b xor edx, edx
0078c60d mov ecx, 6
0078c612 div ecx
0078c614 add edx, 3
0078c617 mov dword ptr [ebp - 0x70], edx
0078c61a test edx, edx
0078c61c jle 0x78c6dd
0078c622 call 0x6c3d90
0078c627 push 0
0078c629 push 0
0078c62b mov edx, esi
0078c62d lea ecx, [ebp - 0x80]
0078c630 movd xmm0, eax
0078c634 cvtdq2pd xmm0, xmm0
0078c638 shr eax, 0x1f
0078c63b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0078c644 cvtpd2ps xmm0, xmm0
0078c648 mulss xmm0, dword ptr [0xb6a19c]
0078c650 mulss xmm0, dword ptr [0xb6a4e0]
0078c658 addss xmm0, dword ptr [0xb6a3d4]
0078c660 movss dword ptr [ebp - 0x74], xmm0
0078c665 call 0x6c3450
0078c66a movss xmm2, dword ptr [ebp - 0x80]
0078c66f add esp, 8
0078c672 movss xmm1, dword ptr [ebp - 0x7c]
0078c677 mulss xmm2, dword ptr [ebp - 0x74]
0078c67c mulss xmm1, dword ptr [ebp - 0x74]
0078c681 movss dword ptr [ebp - 0x88], xmm2
0078c689 movss dword ptr [ebp - 0x84], xmm1
0078c691 call 0x6c3d90
0078c696 addss xmm2, dword ptr [esi]
0078c69a addss xmm1, dword ptr [edi + 0x298]
0078c6a2 mov ecx, dword ptr [0xbfd65c]
0078c6a8 push eax
0078c6a9 push 0
0078c6ab push edi
0078c6ac lea eax, [ebp - 0x88]
0078c6b2 movss dword ptr [ebp - 0x90], xmm2
0078c6ba push eax
0078c6bb lea eax, [ebp - 0x90]
0078c6c1 movss dword ptr [ebp - 0x8c], xmm1
0078c6c9 push eax
0078c6ca push 0x14
0078c6cc push 5
0078c6ce call 0x422e20
0078c6d3 sub dword ptr [ebp - 0x70], 1
0078c6d7 jne 0x78c622
