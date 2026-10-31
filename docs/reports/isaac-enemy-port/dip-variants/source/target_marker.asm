006af8d0 push ebp
006af8d1 mov ebp, esp
006af8d3 sub esp, 0x40
006af8d6 push ebx
006af8d7 mov ebx, dword ptr [ebp + 8]
006af8da movaps xmm0, xmm2
006af8dd push esi
006af8de push edi
006af8df mov edi, ecx
006af8e1 movss dword ptr [ebp - 8], xmm0
006af8e6 mov ecx, dword ptr [edi + 0xe78]
006af8ec lea esi, [edi + 0xe78]
006af8f2 test ecx, ecx
006af8f4 je 0x6af926
006af8f6 cmp dword ptr [ecx + 0x28], 0x3e8
006af8fd je 0x6afa52
006af903 mov eax, dword ptr [ecx]
006af905 call dword ptr [eax + 0x28]
006af908 mov ecx, dword ptr [esi]
006af90a test ecx, ecx
006af90c je 0x6af920
006af90e lea eax, [ebp + 8]
006af911 mov dword ptr [ebp + 8], esi
006af914 push eax
006af915 add ecx, 0x324
006af91b call 0x4bc3c0
006af920 mov dword ptr [esi], 0
006af926 test ebx, ebx
006af928 jne 0x6af966
006af92a lea eax, [ebp - 0x10]
006af92d xorps xmm2, xmm2
006af930 push eax
006af931 mov ecx, edi
006af933 call 0x6af380
006af938 mov ecx, eax
006af93a movss xmm0, dword ptr [ecx]
006af93e ucomiss xmm0, dword ptr [0xc02fec]
006af945 lahf 
006af946 test ah, 0x44
006af949 jp 0x6af9a2
006af94b movss xmm0, dword ptr [ecx + 4]
006af950 ucomiss xmm0, dword ptr [0xc02ff0]
006af957 lahf 
006af958 test ah, 0x44
006af95b jp 0x6af9a2
006af95d pop edi
006af95e pop esi
006af95f pop ebx
006af960 mov esp, ebp
006af962 pop ebp
006af963 ret 4
006af966 cmp ebx, 1
006af969 jne 0x6af9a2
006af96b lea eax, [ebp - 0x10]
006af96e xorps xmm2, xmm2
006af971 push eax
006af972 mov ecx, edi
006af974 call 0x6af0c0
006af979 mov ecx, eax
006af97b movss xmm0, dword ptr [ecx]
006af97f ucomiss xmm0, dword ptr [0xc02fec]
006af986 lahf 
006af987 test ah, 0x44
006af98a jp 0x6af9a2
006af98c movss xmm0, dword ptr [ecx + 4]
006af991 ucomiss xmm0, dword ptr [0xc02ff0]
006af998 lahf 
006af999 test ah, 0x44
006af99c jnp 0x6afa6e
006af9a2 call 0x6c3d90
006af9a7 mov ecx, dword ptr [0xbfd65c]
006af9ad push eax
006af9ae push 0
006af9b0 push edi
006af9b1 push 0xc02fec
006af9b6 lea eax, [edi + 0x294]
006af9bc push eax
006af9bd push 0x1e
006af9bf push 0x3e8
006af9c4 call 0x422e20
006af9c9 mov edi, eax
006af9cb mov ecx, edi
006af9cd mov edx, dword ptr [edi]
006af9cf mov dword ptr [edi + 0x3ac], 0
006af9d9 mov dword ptr [edi + 0x3b0], 0
006af9e3 call dword ptr [edx + 0xc]
006af9e6 movaps xmm1, xmmword ptr [0xb6bd80]
006af9ed lea ecx, [edi + 0xe4]
006af9f3 lea eax, [ebp - 0x3c]
006af9f6 mov dword ptr [ebp - 0x1c], 0
006af9fd mov dword ptr [ebp - 0x18], 0
006afa04 xorps xmm0, xmm0
006afa07 mov dword ptr [ebp - 0x14], 0
006afa0e cmp ecx, eax
006afa10 je 0x6afa29
006afa12 mov eax, dword ptr [ebp - 0x14]
006afa15 movups xmmword ptr [ecx + 0x10], xmm0
006afa19 movq xmm0, qword ptr [ebp - 0x1c]
006afa1e movq qword ptr [ecx + 0x20], xmm0
006afa23 movups xmmword ptr [ecx], xmm1
006afa26 mov dword ptr [ecx + 0x28], eax
006afa29 mov ecx, dword ptr [esi]
006afa2b test ecx, ecx
006afa2d je 0x6afa41
006afa2f lea eax, [ebp + 8]
006afa32 mov dword ptr [ebp + 8], esi
006afa35 push eax
006afa36 add ecx, 0x324
006afa3c call 0x4bc3c0
006afa41 push esi
006afa42 mov ecx, edi
006afa44 mov dword ptr [esi], edi
006afa46 call 0x4bae70
006afa4b mov ecx, dword ptr [esi]
006afa4d movss xmm0, dword ptr [ebp - 8]
006afa52 movss dword ptr [ecx + 0x3c4], xmm0
006afa5a mov eax, dword ptr [esi]
006afa5c mov dword ptr [eax + 0x374], 2
006afa66 mov eax, dword ptr [esi]
006afa68 mov dword ptr [eax + 0x378], ebx
006afa6e pop edi
006afa6f pop esi
006afa70 pop ebx
006afa71 mov esp, ebp
006afa73 pop ebp
006afa74 ret 4
