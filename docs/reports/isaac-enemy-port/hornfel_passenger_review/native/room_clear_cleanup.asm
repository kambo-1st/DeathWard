; Installed-binary disassembly; field interpretations require the source review.
004a48b0 push ebp
004a48b1 mov ebp, esp
004a48b3 push -1
004a48b5 push 0x9ee585
004a48ba mov eax, dword ptr fs:[0]
004a48c0 push eax
004a48c1 sub esp, 0x64
004a48c4 mov eax, dword ptr [0xbaa3b4]
004a48c9 xor eax, ebp
004a48cb mov dword ptr [ebp - 0x10], eax
004a48ce push ebx
004a48cf push esi
004a48d0 push edi
004a48d1 push eax
004a48d2 lea eax, [ebp - 0xc]
004a48d5 mov dword ptr fs:[0], eax
004a48db mov eax, dword ptr [0xbfd65c]
004a48e0 xor ecx, ecx
004a48e2 xor ebx, ebx
004a48e4 mov dword ptr [ebp - 0x40], ecx
004a48e7 mov dword ptr [ebp - 0x64], ecx
004a48ea mov dword ptr [ebp - 0x60], ebx
004a48ed mov eax, dword ptr [eax + 0x18190]
004a48f3 mov dword ptr [ebp - 0x54], eax
004a48f6 mov dword ptr [ebp - 0x50], ecx
004a48f9 mov dword ptr [ebp - 0x5c], ecx
004a48fc xor edx, edx
004a48fe mov dword ptr [ebp - 4], ebx
004a4901 xor edi, edi
004a4903 mov dword ptr [ebp - 0x58], edx
004a4906 mov dword ptr [ebp - 0x70], edx
004a4909 mov dword ptr [ebp - 0x6c], edi
004a490c mov dword ptr [ebp - 0x4c], edx
004a490f mov dword ptr [ebp - 0x68], edx
004a4912 xor esi, esi
004a4914 mov byte ptr [ebp - 4], 1
004a4918 mov dword ptr [ebp - 0x44], esi
004a491b cmp dword ptr [eax + 0x1264], esi
004a4921 ja 0x4a4b33
004a4927 cmp esi, edi
004a4929 je 0x4a4984
004a492b nop dword ptr [eax + eax]
004a4930 call 0x6c3d90
004a4935 mov ecx, dword ptr [esi]
004a4937 push eax
004a4938 push 0
004a493a push 0
004a493c mov edx, dword ptr [ecx + 0x294]
004a4942 lea eax, [ebp - 0x48]
004a4945 mov ecx, dword ptr [ecx + 0x298]
004a494b push 0xc02fec
004a4950 push eax
004a4951 push 0xf
004a4953 mov dword ptr [ebp - 0x44], ecx
004a4956 mov ecx, dword ptr [0xbfd65c]
004a495c push 0x3e8
004a4961 mov dword ptr [ebp - 0x48], edx
004a4964 call 0x422e20
004a4969 mov ecx, dword ptr [esi]
004a496b mov eax, dword ptr [ecx]
004a496d call dword ptr [eax + 0x28]
004a4970 mov eax, dword ptr [esi]
004a4972 mov ecx, dword ptr [eax + 0x32c]
004a4978 mov eax, dword ptr [ecx]
004a497a call dword ptr [eax + 0x28]
004a497d add esi, 4
004a4980 cmp esi, edi
004a4982 jne 0x4a4930
004a4984 mov edi, dword ptr [ebp - 0x40]
004a4987 mov esi, edi
004a4989 cmp esi, ebx
004a498b je 0x4a4a1d
004a4991 movaps xmm0, xmmword ptr [0xb6c1b0]
004a4998 movups xmmword ptr [ebp - 0x3c], xmm0
004a499c mov dword ptr [ebp - 0x1c], 0
004a49a3 movaps xmm0, xmmword ptr [0xb6c610]
004a49aa movups xmmword ptr [ebp - 0x2c], xmm0
004a49ae mov dword ptr [ebp - 0x18], 0
004a49b5 mov dword ptr [ebp - 0x14], 0
004a49bc call 0x6c3d90
004a49c1 mov ecx, dword ptr [esi]
004a49c3 push eax
004a49c4 push 0
004a49c6 push 0
004a49c8 mov edx, dword ptr [ecx + 0x294]
004a49ce lea eax, [ebp - 0x48]
004a49d1 mov ecx, dword ptr [ecx + 0x298]
004a49d7 push 0xc02fec
004a49dc push eax
004a49dd push 0xf
004a49df mov dword ptr [ebp - 0x44], ecx
004a49e2 mov ecx, dword ptr [0xbfd65c]
004a49e8 push 0x3e8
004a49ed mov dword ptr [ebp - 0x48], edx
004a49f0 call 0x422e20
004a49f5 push 1
004a49f7 push 0
004a49f9 push 0xff
004a49fe mov edx, dword ptr [eax]
004a4a00 lea ecx, [ebp - 0x3c]
004a4a03 push -1
004a4a05 push ecx
004a4a06 mov ecx, eax
004a4a08 call dword ptr [edx + 0x38]
004a4a0b mov ecx, dword ptr [esi]
004a4a0d mov eax, dword ptr [ecx]
004a4a0f call dword ptr [eax + 0x28]
004a4a12 add esi, 4
004a4a15 cmp esi, ebx
004a4a17 jne 0x4a4991
004a4a1d mov eax, dword ptr [ebp - 0x54]
004a4a20 mov ecx, dword ptr [eax + 0x724]
004a4a26 test ecx, ecx
004a4a28 je 0x4a4a34
004a4a2a mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a34 mov ecx, dword ptr [eax + 0x728]
004a4a3a test ecx, ecx
004a4a3c je 0x4a4a48
004a4a3e mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a48 mov ecx, dword ptr [eax + 0x72c]
004a4a4e test ecx, ecx
004a4a50 je 0x4a4a5c
004a4a52 mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a5c mov ecx, dword ptr [eax + 0x730]
004a4a62 test ecx, ecx
004a4a64 je 0x4a4a70
004a4a66 mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a70 mov ecx, dword ptr [eax + 0x734]
004a4a76 test ecx, ecx
004a4a78 je 0x4a4a84
004a4a7a mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a84 mov ecx, dword ptr [eax + 0x738]
004a4a8a test ecx, ecx
004a4a8c je 0x4a4a98
004a4a8e mov dword ptr [ecx + 0xf4], 0x3f800000
004a4a98 mov ecx, dword ptr [eax + 0x73c]
004a4a9e test ecx, ecx
004a4aa0 je 0x4a4aac
004a4aa2 mov dword ptr [ecx + 0xf4], 0x3f800000
004a4aac mov eax, dword ptr [eax + 0x740]
004a4ab2 test eax, eax
004a4ab4 je 0x4a4ac0
004a4ab6 mov dword ptr [eax + 0xf4], 0x3f800000
004a4ac0 mov edx, dword ptr [ebp - 0x58]
004a4ac3 test edx, edx
004a4ac5 je 0x4a4af3
004a4ac7 mov ecx, dword ptr [ebp - 0x4c]
004a4aca mov eax, edx
004a4acc sub ecx, edx
004a4ace and ecx, 0xfffffffc
004a4ad1 cmp ecx, 0x1000
004a4ad7 jb 0x4a4ae9
004a4ad9 mov edx, dword ptr [edx - 4]
004a4adc add ecx, 0x23
004a4adf sub eax, edx
004a4ae1 add eax, -4
004a4ae4 cmp eax, 0x1f
004a4ae7 ja 0x4a4b25
004a4ae9 push ecx
004a4aea push edx
004a4aeb call 0x9eb08e
004a4af0 add esp, 8
004a4af3 test edi, edi
004a4af5 je 0x4a4bc9
004a4afb mov ecx, dword ptr [ebp - 0x50]
004a4afe mov eax, edi
004a4b00 sub ecx, edi
004a4b02 and ecx, 0xfffffffc
004a4b05 cmp ecx, 0x1000
004a4b0b jb 0x4a4bbf
004a4b11 mov edi, dword ptr [edi - 4]
004a4b14 add ecx, 0x23
004a4b17 sub eax, edi
004a4b19 add eax, -4
004a4b1c cmp eax, 0x1f
004a4b1f jbe 0x4a4bbf
004a4b25 call dword ptr [0xa065ac]
004a4b2b nop dword ptr [eax + eax]
004a4b30 mov ecx, dword ptr [ebp - 0x50]
004a4b33 mov eax, dword ptr [eax + 0x125c]
004a4b39 mov esi, dword ptr [eax + esi*4]
004a4b3c mov dword ptr [ebp - 0x40], esi
004a4b3f cmp dword ptr [esi + 0x28], 0x3c7
004a4b46 jne 0x4a4b6f
004a4b48 cmp ebx, ecx
004a4b4a je 0x4a4b56
004a4b4c mov dword ptr [ebx], esi
004a4b4e add ebx, 4
004a4b51 mov dword ptr [ebp - 0x60], ebx
004a4b54 jmp 0x4a4b6f
004a4b56 lea eax, [ebp - 0x40]
004a4b59 push eax
004a4b5a push ebx
004a4b5b lea ecx, [ebp - 0x64]
004a4b5e call 0x426fb0
004a4b63 mov eax, dword ptr [ebp - 0x5c]
004a4b66 mov ebx, dword ptr [ebp - 0x60]
004a4b69 mov edx, dword ptr [ebp - 0x4c]
004a4b6c mov dword ptr [ebp - 0x50], eax
004a4b6f cmp dword ptr [esi + 0x32c], 0
004a4b76 je 0x4a4b9c
004a4b78 cmp edi, edx
004a4b7a je 0x4a4b86
004a4b7c mov dword ptr [edi], esi
004a4b7e add edi, 4
004a4b81 mov dword ptr [ebp - 0x6c], edi
004a4b84 jmp 0x4a4b9c
004a4b86 lea eax, [ebp - 0x40]
004a4b89 push eax
004a4b8a push edi
004a4b8b lea ecx, [ebp - 0x70]
004a4b8e call 0x426fb0
004a4b93 mov edx, dword ptr [ebp - 0x68]
004a4b96 mov edi, dword ptr [ebp - 0x6c]
004a4b99 mov dword ptr [ebp - 0x4c], edx
004a4b9c mov esi, dword ptr [ebp - 0x44]
004a4b9f mov eax, dword ptr [ebp - 0x54]
004a4ba2 inc esi
004a4ba3 mov dword ptr [ebp - 0x44], esi
004a4ba6 cmp esi, dword ptr [eax + 0x1264]
004a4bac jb 0x4a4b30
004a4bae mov ecx, dword ptr [ebp - 0x64]
004a4bb1 mov esi, dword ptr [ebp - 0x70]
004a4bb4 mov dword ptr [ebp - 0x40], ecx
004a4bb7 mov dword ptr [ebp - 0x58], esi
004a4bba jmp 0x4a4927
004a4bbf push ecx
004a4bc0 push edi
004a4bc1 call 0x9eb08e
004a4bc6 add esp, 8
004a4bc9 mov ecx, dword ptr [ebp - 0xc]
004a4bcc mov dword ptr fs:[0], ecx
004a4bd3 pop ecx
004a4bd4 pop edi
004a4bd5 pop esi
004a4bd6 pop ebx
004a4bd7 mov ecx, dword ptr [ebp - 0x10]
004a4bda xor ecx, ebp
004a4bdc call 0x9eacd7
004a4be1 mov esp, ebp
004a4be3 pop ebp
004a4be4 ret
