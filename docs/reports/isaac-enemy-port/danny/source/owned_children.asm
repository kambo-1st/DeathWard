006a6f60 push ebp
006a6f61 mov ebp, esp
006a6f63 push ecx
006a6f64 mov ecx, dword ptr [0xbfd65c]
006a6f6a xor edx, edx
006a6f6c push ebx
006a6f6d push esi
006a6f6e push edi
006a6f6f mov esi, dword ptr [ecx + 0x18190]
006a6f75 xor edi, edi
006a6f77 mov dword ptr [esi + 0x1294], 0
006a6f81 mov eax, dword ptr [ecx + 0x18190]
006a6f87 mov dword ptr [ebp - 4], eax
006a6f8a cmp dword ptr [eax + 0x1264], edx
006a6f90 jbe 0x6a702b
006a6f96 nop word ptr [eax + eax]
006a6fa0 mov eax, dword ptr [eax + 0x125c]
006a6fa6 mov ecx, dword ptr [eax + edi*4]
006a6fa9 mov eax, dword ptr [ecx + 0x28]
006a6fac sub eax, 0xa
006a6faf cmp eax, 0x3dd
006a6fb4 ja 0x6a7013
006a6fb6 push 0
006a6fb8 push 0xbeab70
006a6fbd push 0xbeab18
006a6fc2 push 0
006a6fc4 push ecx
006a6fc5 call 0x9ec34c
006a6fca mov ebx, eax
006a6fcc add esp, 0x14
006a6fcf test ebx, ebx
006a6fd1 je 0x6a7013
006a6fd3 mov eax, dword ptr [ebp + 0xc]
006a6fd6 cmp dword ptr [ebx + 0xbcc], eax
006a6fdc jne 0x6a7013
006a6fde mov edx, dword ptr [esi + 0x1294]
006a6fe4 lea ecx, [edx + 1]
006a6fe7 cmp ecx, dword ptr [esi + 0x1290]
006a6fed jbe 0x6a7004
006a6fef push 0xb3f428
006a6ff4 push 3
006a6ff6 call 0x95e330
006a6ffb mov edx, dword ptr [esi + 0x1294]
006a7001 add esp, 8
006a7004 mov eax, dword ptr [esi + 0x128c]
006a700a mov dword ptr [eax + edx*4], ebx
006a700d inc dword ptr [esi + 0x1294]
006a7013 mov eax, dword ptr [ebp - 4]
006a7016 inc edi
006a7017 cmp edi, dword ptr [eax + 0x1264]
006a701d jb 0x6a6fa0
006a701f mov edx, dword ptr [esi + 0x1294]
006a7025 mov ecx, dword ptr [0xbfd65c]
006a702b mov eax, dword ptr [ecx + 0x18190]
006a7031 mov edi, dword ptr [ebp + 8]
006a7034 add eax, 0x1298
006a7039 push edx
006a703a push eax
006a703b mov ecx, edi
006a703d call 0x412420
006a7042 mov ecx, dword ptr [esi + 0x1294]
006a7048 cmp dword ptr [edi + 8], ecx
006a704b jae 0x6a7062
006a704d push 0xb3f4b0
006a7052 push 3
006a7054 call 0x95e330
006a7059 mov ecx, dword ptr [esi + 0x1294]
006a705f add esp, 8
006a7062 shl ecx, 2
006a7065 push ecx
006a7066 push dword ptr [esi + 0x128c]
006a706c push dword ptr [edi + 4]
006a706f call 0x9ec14c
006a7074 mov ecx, dword ptr [esi + 0x1294]
006a707a add esp, 0xc
006a707d mov dword ptr [edi + 0xc], ecx
006a7080 mov eax, edi
006a7082 pop edi
006a7083 pop esi
006a7084 pop ebx
006a7085 mov esp, ebp
006a7087 pop ebp
006a7088 ret 8
