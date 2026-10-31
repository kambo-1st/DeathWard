004f92df lea ecx, [ebp - 0x118]
004f92e5 call 0x430d70
004f92ea cmp dword ptr [edi + 0x28], 0xee
004f92f1 mov dword ptr [ebp - 0x10c], 0x3e99999a
004f92fb mov dword ptr [ebp - 0x110], 0xc0a00000
004f9305 jne 0x4f934c
004f9307 cmp dword ptr [edi + 0xe6c], -1
004f930e je 0x4f9314
004f9310 xor edx, edx
004f9312 jmp 0x4f9322
004f9314 call 0x6c3d90
004f9319 xor edx, edx
004f931b mov ecx, 0x1e
004f9320 div ecx
004f9322 movaps xmm0, xmmword ptr [0xb6c330]
004f9329 lea eax, [edx + 0x3c]
004f932c or dword ptr [ebp - 0xc0], 2
004f9333 mov dword ptr [edi + 0xaf0], eax
004f9339 mov eax, dword ptr [ebp - 0xbc]
004f933f mov dword ptr [ebp - 0xbc], eax
004f9345 movups xmmword ptr [ebp - 0xdc], xmm0
004f934c call 0x690cc0
004f9351 sub eax, 6
004f9354 je 0x4f936c
004f9356 sub eax, 0x15
004f9359 je 0x4f936c
004f935b sub eax, 1
004f935e jne 0x4f9376
004f9360 mov dword ptr [ebp - 0x84], 3
004f936a jmp 0x4f9376
004f936c mov dword ptr [ebp - 0x84], 4
004f9376 movss xmm1, dword ptr [ebp - 0x124]
004f937e lea eax, [ebp - 0x118]
004f9384 mulss xmm1, dword ptr [0xb6a8f4]
004f938c mov ecx, edi
004f938e push eax
004f938f push 0
004f9391 lea eax, [ebp - 0x128]
004f9397 movss dword ptr [ebp - 0x128], xmm1
004f939f movss xmm1, dword ptr [ebp - 0x11c]
004f93a7 mulss xmm1, dword ptr [0xb6a8f4]
004f93af push eax
004f93b0 lea eax, [edi + 0x294]
004f93b6 push eax
004f93b7 movss dword ptr [ebp - 0x124], xmm1
004f93bf call 0x6a1a20
