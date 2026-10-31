; Installed-binary disassembly; field interpretations require the source review.
0068eff0 push ebp
0068eff1 mov ebp, esp
0068eff3 push ecx
0068eff4 push ebx
0068eff5 push esi
0068eff6 push edi
0068eff7 mov dword ptr [ebp - 4], ecx
0068effa call 0x6c3d90
0068efff mov esi, dword ptr [ebp + 8]
0068f002 mov ecx, dword ptr [0xbfd65c]
0068f008 push eax
0068f009 push 0
0068f00b push 0
0068f00d push 0xc02fec
0068f012 push esi
0068f013 push 0
0068f015 push 0x3c5
0068f01a call 0x422e20
0068f01f mov edi, dword ptr [ebp + 0xc]
0068f022 mov ebx, eax
0068f024 push edi
0068f025 push esi
0068f026 mov ecx, ebx
0068f028 mov dword ptr [ebx + 0xb08], 0x3f800000
0068f032 call 0x4bc1e0
0068f037 mov edx, dword ptr [ebx]
0068f039 mov ecx, ebx
0068f03b call dword ptr [edx + 0xc]
0068f03e movss xmm0, dword ptr [edi]
0068f042 movss xmm1, dword ptr [edi + 4]
0068f047 mov edi, dword ptr [ebp - 4]
0068f04a lea esi, [edi + 0x32c]
0068f050 movss dword ptr [ebx + 0x28c], xmm0
0068f058 movss dword ptr [ebx + 0x290], xmm1
0068f060 mov ecx, dword ptr [esi]
0068f062 cmp ecx, ebx
0068f064 je 0x68f086
0068f066 test ecx, ecx
0068f068 je 0x68f07c
0068f06a lea eax, [ebp + 8]
0068f06d mov dword ptr [ebp + 8], esi
0068f070 push eax
0068f071 add ecx, 0x324
0068f077 call 0x4bc3c0
0068f07c push esi
0068f07d mov ecx, ebx
0068f07f mov dword ptr [esi], ebx
0068f081 call 0x4bae70
0068f086 mov ecx, dword ptr [ebx + 0x318]
0068f08c lea esi, [ebx + 0x318]
0068f092 test ecx, ecx
0068f094 je 0x68f0a8
0068f096 lea eax, [ebp + 8]
0068f099 mov dword ptr [ebp + 8], esi
0068f09c push eax
0068f09d add ecx, 0x324
0068f0a3 call 0x4bc3c0
0068f0a8 mov dword ptr [esi], edi
0068f0aa test edi, edi
0068f0ac je 0x68f0b6
0068f0ae push esi
0068f0af mov ecx, edi
0068f0b1 call 0x4bae70
0068f0b6 pop edi
0068f0b7 pop esi
0068f0b8 mov eax, ebx
0068f0ba pop ebx
0068f0bb mov esp, ebp
0068f0bd pop ebp
0068f0be ret 8
