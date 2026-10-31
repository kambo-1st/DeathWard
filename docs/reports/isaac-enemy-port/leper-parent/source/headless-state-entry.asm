004f8e40 push ebx
004f8e41 mov ebx, esp
004f8e43 sub esp, 8
004f8e46 and esp, 0xfffffff8
004f8e49 add esp, 4
004f8e4c push ebp
004f8e4d mov ebp, dword ptr [ebx + 4]
004f8e50 mov dword ptr [esp + 4], ebp
004f8e54 mov ebp, esp
004f8e56 push -1
004f8e58 push 0x9ef255
004f8e5d mov eax, dword ptr fs:[0]
004f8e63 push eax
004f8e64 push ebx
004f8e65 sub esp, 0x148
004f8e6b mov eax, dword ptr [0xbaa3b4]
004f8e70 xor eax, ebp
004f8e72 mov dword ptr [ebp - 0x14], eax
004f8e75 push esi
004f8e76 push edi
004f8e77 push eax
004f8e78 lea eax, [ebp - 0xc]
004f8e7b mov dword ptr fs:[0], eax
004f8e81 mov edi, ecx
004f8e83 cmp dword ptr [edi + 0xab4], 0
004f8e8a jne 0x4f8f3b
004f8e90 cmp dword ptr [edi + 0x28], 0xee
004f8e97 mov dword ptr [edi + 0xab4], 4
004f8ea1 jne 0x4f8ef8
004f8ea3 movaps xmm1, xmmword ptr [0xb6c290]
004f8eaa lea ecx, [edi + 0x1dc]
004f8eb0 lea eax, [ebp - 0x154]
004f8eb6 mov dword ptr [ebp - 0x134], 0xbe48c8ca
004f8ec0 mov dword ptr [ebp - 0x130], 0x3f028283
004f8eca xorps xmm0, xmm0
004f8ecd mov dword ptr [ebp - 0x12c], 0x3e48c8ca
004f8ed7 cmp ecx, eax
004f8ed9 je 0x4f8ef8
004f8edb mov eax, dword ptr [ebp - 0x12c]
004f8ee1 movups xmmword ptr [ecx + 0x10], xmm0
004f8ee5 movq xmm0, qword ptr [ebp - 0x134]
004f8eed movq qword ptr [ecx + 0x20], xmm0
004f8ef2 movups xmmword ptr [ecx], xmm1
004f8ef5 mov dword ptr [ecx + 0x28], eax
004f8ef8 call 0x6c3d90
004f8efd xor edx, edx
004f8eff mov ecx, 0x14
004f8f04 div ecx
004f8f06 add edx, ecx
004f8f08 cmp dword ptr [edi + 0x2c], 0
004f8f0c mov dword ptr [edi + 0xaf0], edx
004f8f12 jne 0x4f8f1a
004f8f14 cmp dword ptr [edi + 0x28], 0xb
004f8f18 je 0x4f8f27
004f8f1a cmp dword ptr [edi + 0x28], 0xee
004f8f21 jne 0x4f9a34
004f8f27 push 0
004f8f29 push 0xb41240
004f8f2e lea ecx, [edi + 0x3c]
004f8f31 call 0x405a00
004f8f36 jmp 0x4f9a34
004f8f3b cmp byte ptr [edi + 0x16b], 0
004f8f42 je 0x4f8f99
004f8f44 cmp dword ptr [edi + 0x28], 0xd2
004f8f4b jne 0x4f8f99
004f8f4d movss xmm0, dword ptr [edi + 0x2d8]
004f8f55 comiss xmm0, dword ptr [0xb6aef8]
004f8f5c jbe 0x4f9a34
004f8f62 call 0x6c3d90
004f8f67 test al, 1
004f8f69 jne 0x4f9a34
004f8f6f push -1
004f8f71 push 0
004f8f73 push 0
004f8f75 push 0xd3
004f8f7a mov ecx, edi
004f8f7c call 0x697c60
004f8f81 mov eax, dword ptr [edi + 0x2dc]
004f8f87 mov byte ptr [edi + 0x16b], 0
004f8f8e mov dword ptr [edi + 0x2d8], eax
004f8f94 jmp 0x4f9a34
004f8f99 cmp dword ptr [edi + 0x28], 0xee
004f8fa0 xorps xmm1, xmm1
004f8fa3 jne 0x4f9008
004f8fa5 movss xmm0, dword ptr [edi + 0x14]
004f8faa comiss xmm0, xmm1
004f8fad jbe 0x4f9008
004f8faf mov eax, dword ptr [edi + 8]
004f8fb2 cmp eax, dword ptr [edi + 0xc]
004f8fb5 je 0x4f9008
004f8fb7 nop word ptr [eax + eax]
004f8fc0 mov ecx, dword ptr [eax + 0xc]
004f8fc3 mov edx, dword ptr [eax + 8]
004f8fc6 mov dword ptr [ebp - 0x11c], ecx
004f8fcc mov ecx, edx
004f8fce and ecx, 4
004f8fd1 or ecx, 0
004f8fd4 je 0x4f9000
004f8fd6 mov ecx, dword ptr [eax + 0x30]
004f8fd9 shr ecx, 1
004f8fdb test cl, 1
004f8fde jne 0x4f9000
004f8fe0 cmp dword ptr [eax + 0x10], 1
004f8fe4 je 0x4f9000
004f8fe6 mov ecx, dword ptr [eax + 0x18]
004f8fe9 cmp ecx, 1
004f8fec je 0x4f9000
004f8fee cmp ecx, 3
004f8ff1 je 0x4f9000
004f8ff3 and edx, 0x1000
004f8ff9 or edx, 0
004f8ffc jne 0x4f9000
004f8ffe mov dword ptr [eax], edx
004f9000 add eax, 0x38
004f9003 cmp eax, dword ptr [edi + 0xc]
004f9006 jne 0x4f8fc0
