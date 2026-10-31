; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a5a10 push ebp
004a5a11 mov ebp, esp
004a5a13 push -1
004a5a15 push 0x9ed6ad
004a5a1a mov eax, dword ptr fs:[0]
004a5a20 push eax
004a5a21 sub esp, 0x1c
004a5a24 push ebx
004a5a25 push esi
004a5a26 push edi
004a5a27 mov eax, dword ptr [0xbaa3b4] ; [0xbaa3b4] f32=-0.00294341473
004a5a2c xor eax, ebp
004a5a2e push eax
004a5a2f lea eax, [ebp - 0xc]
004a5a32 mov dword ptr fs:[0], eax
004a5a38 mov esi, ecx
004a5a3a cmp dword ptr [esi + 0xab4], 0xa
004a5a41 mov edi, dword ptr [esi + 0x32c]
004a5a47 jne 0x4a5b36
004a5a4d mov ebx, dword ptr [esi + 0xb3c]
004a5a53 test ebx, ebx
004a5a55 je 0x4a5b36
004a5a5b cmp byte ptr [esi + 0xaf6], 0
004a5a62 jg 0x4a5ae1
004a5a64 movss xmm0, dword ptr [0xb6a910] ; [0xb6a910] f32=6
004a5a6c mov eax, 1
004a5a71 mov dword ptr [esi + 0xab4], 7
004a5a7b mov byte ptr [esi + 0x169], 0
004a5a82 mov dword ptr [esi + 0x180], 0
004a5a8c mov word ptr [esi + 0x360], ax
004a5a93 mov eax, dword ptr [esi + 0x294]
004a5a99 mov dword ptr [esi + 0x28c], eax
004a5a9f mov eax, dword ptr [esi + 0x298]
004a5aa5 mov dword ptr [esi + 0x290], eax
004a5aab mov dword ptr [esi + 0x150], 0
004a5ab5 minss xmm0, dword ptr [edi + 0xb08]
004a5abd mov dword ptr [edi + 0x150], 0
004a5ac7 movss dword ptr [edi + 0xb08], xmm0
004a5acf mov ecx, dword ptr [ebp - 0xc]
004a5ad2 mov dword ptr fs:[0], ecx
004a5ad9 pop ecx
004a5ada pop edi
004a5adb pop esi
004a5adc pop ebx
004a5add mov esp, ebp
004a5adf pop ebp
004a5ae0 ret 
004a5ae1 lea eax, [ebp - 0x14]
004a5ae4 mov ecx, ebx
004a5ae6 push eax
004a5ae7 call 0x4a8340
004a5aec lea eax, [ebp - 0x14]
004a5aef mov ecx, edi
004a5af1 push eax
004a5af2 lea eax, [ebx + 0x28c]
004a5af8 push eax
004a5af9 call 0x4bc1e0
004a5afe movss xmm0, dword ptr [edi + 0x294]
004a5b06 movss xmm1, dword ptr [edi + 0x298]
004a5b0e dec byte ptr [esi + 0xaf6]
004a5b14 movss dword ptr [esi + 0x294], xmm0
004a5b1c movss dword ptr [esi + 0x298], xmm1
004a5b24 mov ecx, dword ptr [ebp - 0xc]
004a5b27 mov dword ptr fs:[0], ecx
004a5b2e pop ecx
004a5b2f pop edi
004a5b30 pop esi
004a5b31 pop ebx
004a5b32 mov esp, ebp
004a5b34 pop ebp
004a5b35 ret 
004a5b36 push 0
004a5b38 push 0
004a5b3a mov dword ptr [esi + 0xab4], 6
004a5b44 mov eax, 0x2d
004a5b49 mov word ptr [esi + 0x360], ax
004a5b50 mov byte ptr [esi + 0x169], 0
004a5b57 mov dword ptr [esi + 0x180], 0
004a5b61 mov eax, dword ptr [esi + 0x294]
004a5b67 mov dword ptr [esi + 0x28c], eax
004a5b6d mov eax, dword ptr [esi + 0x298]
004a5b73 push -1
004a5b75 mov dword ptr [esi + 0x290], eax
004a5b7b lea eax, [ebp - 0x24]
004a5b7e push -1
004a5b80 push 0x333
004a5b85 push eax
004a5b86 mov eax, dword ptr [0xbfd65c]
004a5b8b mov dword ptr [esi + 0x150], 0
004a5b95 mov dword ptr [edi + 0x150], 0
004a5b9f mov ecx, dword ptr [eax + 0x18190]
004a5ba5 add ecx, 0x1218
004a5bab call 0x415ed0
004a5bb0 mov edx, dword ptr [ebp - 0x18]
004a5bb3 xor edi, edi
004a5bb5 test edx, edx
004a5bb7 je 0x4a5c18
004a5bb9 nop dword ptr [eax]
004a5bc0 mov eax, dword ptr [ebp - 0x20]
004a5bc3 mov ebx, dword ptr [eax + edi*4]
004a5bc6 mov ecx, dword ptr [ebx + 0x314]
004a5bcc lea eax, [ebx + 0x314]
004a5bd2 cmp ecx, esi
004a5bd4 jne 0x4a5c13
004a5bd6 test ecx, ecx
004a5bd8 je 0x4a5bf5
004a5bda mov dword ptr [ebp - 0x10], eax
004a5bdd add ecx, 0x324
004a5be3 lea eax, [ebp - 0x10]
004a5be6 push eax
004a5be7 call 0x4bc3c0
004a5bec mov edx, dword ptr [ebp - 0x18]
004a5bef lea eax, [ebx + 0x314]
004a5bf5 movss xmm0, dword ptr [0xb6a8a0] ; [0xb6a8a0] f32=3.5
004a5bfd minss xmm0, dword ptr [ebx + 0x2d8]
004a5c05 mov dword ptr [eax], 0
004a5c0b movss dword ptr [ebx + 0x2d8], xmm0
004a5c13 inc edi
004a5c14 cmp edi, edx
004a5c16 jb 0x4a5bc0
004a5c18 cmp byte ptr [ebp - 0x24], 0
004a5c1c jne 0x4a5c29
004a5c1e push dword ptr [ebp - 0x20]
004a5c21 call 0x9eace5
004a5c26 add esp, 4
004a5c29 mov ecx, dword ptr [ebp - 0xc]
004a5c2c mov dword ptr fs:[0], ecx
004a5c33 pop ecx
004a5c34 pop edi
004a5c35 pop esi
004a5c36 pop ebx
004a5c37 mov esp, ebp
004a5c39 pop ebp
004a5c3a ret 
004a5c3b int3 
004a5c3c int3 
004a5c3d int3 
004a5c3e int3 
004a5c3f int3 
