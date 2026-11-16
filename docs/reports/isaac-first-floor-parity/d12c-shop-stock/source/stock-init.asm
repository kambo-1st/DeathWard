007cf800 push ebp
007cf801 mov ebp, esp
007cf803 push -1
007cf805 push 0x9f9fa5
007cf80a mov eax, dword ptr fs:[0]
007cf810 push eax
007cf811 sub esp, 0x2c
007cf814 mov eax, dword ptr [0xbaa3b4]
007cf819 xor eax, ebp
007cf81b mov dword ptr [ebp - 0x10], eax
007cf81e push ebx
007cf81f push esi
007cf820 push edi
007cf821 push eax
007cf822 lea eax, [ebp - 0xc]
007cf825 mov dword ptr fs:[0], eax
007cf82b mov edi, ecx
007cf82d mov eax, dword ptr [edi + 4]
007cf830 movq xmm0, qword ptr [0xa08c44]
007cf838 mov ecx, dword ptr [0xa08c4c]
007cf83e movq qword ptr [ebp - 0x2c], xmm0
007cf843 xorps xmm0, xmm0
007cf846 mov ebx, dword ptr [eax + 0x60]
007cf849 movq qword ptr [eax + 0xa4], xmm0
007cf851 mov esi, dword ptr [edi + 8]
007cf854 mov dword ptr [ebp - 0x34], ebx
007cf857 mov dword ptr [ebp - 0x30], ebx
007cf85a mov dword ptr [ebp - 0x14], ecx
007cf85d mov dword ptr [ebp - 0x24], ecx
007cf860 cmp esi, 0xe
007cf863 je 0x7d02ee
007cf869 cmp esi, 0x16
007cf86c je 0x7d02ee
007cf872 mov ebx, dword ptr [edi + 4]
007cf875 mov eax, dword ptr [ebx + 0x44]
007cf878 shr eax, 0xb
007cf87b test al, 1
007cf87d jne 0x7d02eb
007cf883 cmp esi, 0xf
007cf886 jne 0x7cfb25
007cf88c mov dword ptr [ebp - 0x20], 0
007cf893 mov dword ptr [ebp - 0x1c], 0
007cf89a mov dword ptr [ebp - 0x18], 0
007cf8a1 lea eax, [ebp - 0x14]
007cf8a4 mov dword ptr [ebp - 4], 0
007cf8ab push eax
007cf8ac push 0
007cf8ae lea ecx, [ebp - 0x20]
007cf8b1 mov dword ptr [ebp - 0x14], 8
007cf8b8 call 0x426fb0
007cf8bd mov esi, dword ptr [ebp - 0x1c]
007cf8c0 mov eax, dword ptr [ebp - 0x18]
007cf8c3 mov dword ptr [ebp - 0x14], 4
007cf8ca cmp esi, eax
007cf8cc je 0x7cf8dc
007cf8ce mov dword ptr [esi], 4
007cf8d4 add esi, 4
007cf8d7 mov dword ptr [ebp - 0x1c], esi
007cf8da jmp 0x7cf8ef
007cf8dc lea eax, [ebp - 0x14]
007cf8df push eax
007cf8e0 push esi
007cf8e1 lea ecx, [ebp - 0x20]
007cf8e4 call 0x426fb0
007cf8e9 mov eax, dword ptr [ebp - 0x18]
007cf8ec mov esi, dword ptr [ebp - 0x1c]
007cf8ef mov dword ptr [ebp - 0x14], 4
007cf8f6 cmp esi, eax
007cf8f8 je 0x7cf908
007cf8fa mov dword ptr [esi], 4
007cf900 add esi, 4
007cf903 mov dword ptr [ebp - 0x1c], esi
007cf906 jmp 0x7cf91b
007cf908 lea eax, [ebp - 0x14]
007cf90b push eax
007cf90c push esi
007cf90d lea ecx, [ebp - 0x20]
007cf910 call 0x426fb0
007cf915 mov eax, dword ptr [ebp - 0x18]
007cf918 mov esi, dword ptr [ebp - 0x1c]
007cf91b mov dword ptr [ebp - 0x14], 3
007cf922 cmp esi, eax
007cf924 je 0x7cf934
007cf926 mov dword ptr [esi], 3
007cf92c add esi, 4
007cf92f mov dword ptr [ebp - 0x1c], esi
007cf932 jmp 0x7cf947
007cf934 lea eax, [ebp - 0x14]
007cf937 push eax
007cf938 push esi
007cf939 lea ecx, [ebp - 0x20]
007cf93c call 0x426fb0
007cf941 mov eax, dword ptr [ebp - 0x18]
007cf944 mov esi, dword ptr [ebp - 0x1c]
007cf947 mov dword ptr [ebp - 0x14], 3
007cf94e cmp esi, eax
007cf950 je 0x7cf960
007cf952 mov dword ptr [esi], 3
007cf958 add esi, 4
007cf95b mov dword ptr [ebp - 0x1c], esi
007cf95e jmp 0x7cf973
007cf960 lea eax, [ebp - 0x14]
007cf963 push eax
007cf964 push esi
007cf965 lea ecx, [ebp - 0x20]
007cf968 call 0x426fb0
007cf96d mov eax, dword ptr [ebp - 0x18]
007cf970 mov esi, dword ptr [ebp - 0x1c]
007cf973 mov dword ptr [ebp - 0x14], 0x13
007cf97a cmp esi, eax
007cf97c je 0x7cf98c
007cf97e mov dword ptr [esi], 0x13
007cf984 add esi, 4
007cf987 mov dword ptr [ebp - 0x1c], esi
007cf98a jmp 0x7cf99f
007cf98c lea eax, [ebp - 0x14]
007cf98f push eax
007cf990 push esi
007cf991 lea ecx, [ebp - 0x20]
007cf994 call 0x426fb0
007cf999 mov eax, dword ptr [ebp - 0x18]
007cf99c mov esi, dword ptr [ebp - 0x1c]
007cf99f mov dword ptr [ebp - 0x14], 0x13
007cf9a6 cmp esi, eax
007cf9a8 je 0x7cf9b8
007cf9aa mov dword ptr [esi], 0x13
007cf9b0 add esi, 4
007cf9b3 mov dword ptr [ebp - 0x1c], esi
007cf9b6 jmp 0x7cf9cb
007cf9b8 lea eax, [ebp - 0x14]
007cf9bb push eax
007cf9bc push esi
007cf9bd lea ecx, [ebp - 0x20]
007cf9c0 call 0x426fb0
007cf9c5 mov eax, dword ptr [ebp - 0x18]
007cf9c8 mov esi, dword ptr [ebp - 0x1c]
007cf9cb mov dword ptr [ebp - 0x14], 0x14
007cf9d2 cmp esi, eax
007cf9d4 je 0x7cf9e1
007cf9d6 mov dword ptr [esi], 0x14
007cf9dc add esi, 4
007cf9df jmp 0x7cf9f1
007cf9e1 lea eax, [ebp - 0x14]
007cf9e4 push eax
007cf9e5 push esi
007cf9e6 lea ecx, [ebp - 0x20]
007cf9e9 call 0x426fb0
007cf9ee mov esi, dword ptr [ebp - 0x1c]
007cf9f1 mov ebx, dword ptr [ebp - 0x20]
007cf9f4 lea ecx, [ebp - 0x30]
007cf9f7 push esi
007cf9f8 push ebx
007cf9f9 call 0x5b6400
007cf9fe sub esi, ebx
007cfa00 mov eax, 8
007cfa05 sar esi, 2
007cfa08 add esp, 8
007cfa0b xor edx, edx
007cfa0d cmp esi, eax
007cfa0f cmovl eax, esi
007cfa12 mov dword ptr [ebp - 0x14], eax
007cfa15 test eax, eax
007cfa17 jle 0x7cfa35
007cfa19 mov esi, 0x94
007cfa1e nop
007cfa20 mov ecx, dword ptr [edi + 4]
007cfa23 lea esi, [esi + 2]
007cfa26 mov ax, word ptr [ebx + edx*4]
007cfa2a inc edx
007cfa2b mov word ptr [esi + ecx - 2], ax
007cfa30 cmp edx, dword ptr [ebp - 0x14]
007cfa33 jl 0x7cfa20
007cfa35 mov eax, dword ptr [edi + 4]
007cfa38 mov edx, 8
007cfa3d mov esi, dword ptr [ebp - 0x30]
007cfa40 xor ecx, ecx
007cfa42 mov word ptr [eax + 0x96], dx
007cfa49 mov eax, dword ptr [edi + 4]
007cfa4c mov word ptr [eax + 0xac], cx
007cfa53 test esi, esi
007cfa55 jne 0x7cfa67
007cfa57 push 0xb4d6c4
007cfa5c push 3
007cfa5e call 0x95e330
007cfa63 add esp, 8
007cfa66 int3
007cfa67 mov ecx, dword ptr [ebp - 0x2c]
007cfa6a mov eax, esi
007cfa6c shr eax, cl
007cfa6e mov ecx, dword ptr [ebp - 0x28]
007cfa71 xor eax, esi
007cfa73 mov edx, eax
007cfa75 shl edx, cl
007cfa77 mov ecx, dword ptr [ebp - 0x24]
007cfa7a xor edx, eax
007cfa7c mov ebx, edx
007cfa7e mov eax, 0xaaaaaaab
007cfa83 shr ebx, cl
007cfa85 xor ebx, edx
007cfa87 mul ebx
007cfa89 mov ecx, ebx
007cfa8b shr edx, 1
007cfa8d lea eax, [edx + edx*2]
007cfa90 sub ecx, eax
007cfa92 je 0x7cfad8
007cfa94 test ebx, ebx
007cfa96 jne 0x7cfaa8
007cfa98 push 0xb4d6c4
007cfa9d push 3
007cfa9f call 0x95e330
007cfaa4 add esp, 8
007cfaa7 int3
007cfaa8 mov ecx, dword ptr [ebp - 0x2c]
007cfaab mov edx, ebx
007cfaad shr edx, cl
007cfaaf mov eax, 0xaaaaaaab
007cfab4 mov ecx, dword ptr [ebp - 0x28]
007cfab7 xor edx, ebx
007cfab9 mov esi, edx
007cfabb shl esi, cl
007cfabd mov ecx, dword ptr [ebp - 0x24]
007cfac0 xor esi, edx
007cfac2 mov ebx, esi
007cfac4 shr ebx, cl
007cfac6 xor ebx, esi
007cfac8 mul ebx
007cfaca mov ecx, ebx
007cfacc shr edx, 2
007cfacf lea eax, [edx + edx*2]
007cfad2 add eax, eax
007cfad4 sub ecx, eax
007cfad6 jmp 0x7cfadb
007cfad8 or ecx, 0xffffffff
007cfadb mov eax, dword ptr [edi + 4]
007cfade mov edx, dword ptr [ebp - 0x20]
007cfae1 mov word ptr [eax + 0xae], cx
007cfae8 test edx, edx
007cfaea je 0x7d02c9
007cfaf0 mov ecx, dword ptr [ebp - 0x18]
007cfaf3 mov eax, edx
007cfaf5 sub ecx, edx
007cfaf7 and ecx, 0xfffffffc
007cfafa cmp ecx, 0x1000
007cfb00 jb 0x7cfb16
007cfb02 mov edx, dword ptr [edx - 4]
007cfb05 add ecx, 0x23
007cfb08 sub eax, edx
007cfb0a add eax, -4
007cfb0d cmp eax, 0x1f
007cfb10 ja 0x7d01e6
007cfb16 push ecx
007cfb17 push edx
007cfb18 call 0x9eb08e
007cfb1d add esp, 8
007cfb20 jmp 0x7d02c9
007cfb25 cmp esi, 2
007cfb28 jne 0x7cfd5b
007cfb2e mov eax, dword ptr [ebx + 0x10]
007cfb31 mov eax, dword ptr [eax + 0x10]
007cfb34 sub eax, 0x64
007cfb37 cmp eax, 0x13
007cfb3a ja 0x7cfd5b
007cfb40 mov dword ptr [ebp - 0x20], 0
007cfb47 mov dword ptr [ebp - 0x1c], 0
007cfb4e mov dword ptr [ebp - 0x18], 0
007cfb55 lea eax, [ebp - 0x14]
007cfb58 mov dword ptr [ebp - 4], 1
007cfb5f push eax
007cfb60 push 0
007cfb62 lea ecx, [ebp - 0x20]
007cfb65 mov dword ptr [ebp - 0x14], 0xb
007cfb6c call 0x426fb0
007cfb71 mov esi, dword ptr [ebp - 0x1c]
007cfb74 mov ebx, dword ptr [ebp - 0x18]
007cfb77 mov dword ptr [ebp - 0x14], 3
007cfb7e cmp esi, ebx
007cfb80 je 0x7cfb90
007cfb82 mov dword ptr [esi], 3
007cfb88 add esi, 4
007cfb8b mov dword ptr [ebp - 0x1c], esi
007cfb8e jmp 0x7cfba3
007cfb90 lea eax, [ebp - 0x14]
007cfb93 push eax
007cfb94 push esi
007cfb95 lea ecx, [ebp - 0x20]
007cfb98 call 0x426fb0
007cfb9d mov ebx, dword ptr [ebp - 0x18]
007cfba0 mov esi, dword ptr [ebp - 0x1c]
007cfba3 mov dword ptr [ebp - 0x14], 1
007cfbaa cmp esi, ebx
007cfbac je 0x7cfbbc
007cfbae mov dword ptr [esi], 1
007cfbb4 add esi, 4
007cfbb7 mov dword ptr [ebp - 0x1c], esi
007cfbba jmp 0x7cfbcf
007cfbbc lea eax, [ebp - 0x14]
007cfbbf push eax
007cfbc0 push esi
007cfbc1 lea ecx, [ebp - 0x20]
007cfbc4 call 0x426fb0
007cfbc9 mov ebx, dword ptr [ebp - 0x18]
007cfbcc mov esi, dword ptr [ebp - 0x1c]
007cfbcf mov dword ptr [ebp - 0x14], 6
007cfbd6 cmp esi, ebx
007cfbd8 je 0x7cfbe8
007cfbda mov dword ptr [esi], 6
007cfbe0 add esi, 4
007cfbe3 mov dword ptr [ebp - 0x1c], esi
007cfbe6 jmp 0x7cfbfb
007cfbe8 lea eax, [ebp - 0x14]
007cfbeb push eax
007cfbec push esi
007cfbed lea ecx, [ebp - 0x20]
007cfbf0 call 0x426fb0
007cfbf5 mov ebx, dword ptr [ebp - 0x18]
007cfbf8 mov esi, dword ptr [ebp - 0x1c]
007cfbfb mov dword ptr [ebp - 0x14], 5
007cfc02 cmp esi, ebx
007cfc04 je 0x7cfc14
007cfc06 mov dword ptr [esi], 5
007cfc0c add esi, 4
007cfc0f mov dword ptr [ebp - 0x1c], esi
007cfc12 jmp 0x7cfc27
007cfc14 lea eax, [ebp - 0x14]
007cfc17 push eax
007cfc18 push esi
007cfc19 lea ecx, [ebp - 0x20]
007cfc1c call 0x426fb0
007cfc21 mov ebx, dword ptr [ebp - 0x18]
007cfc24 mov esi, dword ptr [ebp - 0x1c]
007cfc27 mov dword ptr [ebp - 0x14], 2
007cfc2e cmp esi, ebx
007cfc30 je 0x7cfc3d
007cfc32 mov dword ptr [esi], 2
007cfc38 add esi, 4
007cfc3b jmp 0x7cfc50
007cfc3d lea eax, [ebp - 0x14]
007cfc40 push eax
007cfc41 push esi
007cfc42 lea ecx, [ebp - 0x20]
007cfc45 call 0x426fb0
007cfc4a mov ebx, dword ptr [ebp - 0x18]
007cfc4d mov esi, dword ptr [ebp - 0x1c]
007cfc50 push esi
007cfc51 push dword ptr [ebp - 0x20]
007cfc54 lea ecx, [ebp - 0x30]
007cfc57 call 0x5b6400
007cfc5c mov ecx, dword ptr [edi + 4]
007cfc5f mov edx, dword ptr [ebp - 0x20]
007cfc62 push esi
007cfc63 mov esi, edx
007cfc65 push esi
007cfc66 movzx eax, word ptr [edx]
007cfc69 mov word ptr [ecx + 0x94], ax
007cfc70 mov ecx, dword ptr [edi + 4]
007cfc73 movzx eax, word ptr [edx + 4]
007cfc77 mov word ptr [ecx + 0x96], ax
007cfc7e mov ecx, 8
007cfc83 mov eax, dword ptr [edi + 4]
007cfc86 mov word ptr [eax + 0x98], cx
007cfc8d mov ecx, 9
007cfc92 mov eax, dword ptr [edi + 4]
007cfc95 mov word ptr [eax + 0x9a], cx
007cfc9c mov ecx, 0xa
007cfca1 mov eax, dword ptr [edi + 4]
007cfca4 mov word ptr [eax + 0x9c], cx
007cfcab mov dword ptr [edx], 8
007cfcb1 mov dword ptr [edx + 4], ecx
007cfcb4 lea ecx, [ebp - 0x30]
007cfcb7 call 0x5b6400
007cfcbc mov ecx, dword ptr [edi + 4]
007cfcbf add esp, 0x10
007cfcc2 movzx eax, word ptr [esi]
007cfcc5 mov word ptr [ecx + 0x9e], ax
007cfccc mov ecx, dword ptr [edi + 4]
007cfccf movzx eax, word ptr [esi + 4]
007cfcd3 push 3
007cfcd5 mov word ptr [ecx + 0xa0], ax
007cfcdc mov ecx, 0xa
007cfce1 mov eax, dword ptr [edi + 4]
007cfce4 mov word ptr [eax + 0xa2], cx
007cfceb xor ecx, ecx
007cfced mov eax, dword ptr [edi + 4]
007cfcf0 mov word ptr [eax + 0xac], cx
007cfcf7 lea ecx, [ebp - 0x30]
007cfcfa call 0x7a7d50
007cfcff test eax, eax
007cfd01 je 0x7cfd19
007cfd03 push 8
007cfd05 lea ecx, [ebp - 0x30]
007cfd08 call 0x7a7d50
007cfd0d mov ecx, dword ptr [edi + 4]
007cfd10 mov word ptr [ecx + 0xae], ax
007cfd17 jmp 0x7cfd26
007cfd19 mov eax, dword ptr [edi + 4]
007cfd1c or ecx, 0xffffffff
007cfd1f mov word ptr [eax + 0xae], cx
007cfd26 sub ebx, esi
007cfd28 mov eax, esi
007cfd2a and ebx, 0xfffffffc
007cfd2d cmp ebx, 0x1000
007cfd33 jb 0x7cfd49
007cfd35 mov esi, dword ptr [esi - 4]
007cfd38 add ebx, 0x23
007cfd3b sub eax, esi
007cfd3d add eax, -4
007cfd40 cmp eax, 0x1f
007cfd43 ja 0x7d01e6
007cfd49 push ebx
007cfd4a push esi
007cfd4b call 0x9eb08e
007cfd50 mov ebx, dword ptr [ebp - 0x30]
007cfd53 add esp, 8
007cfd56 jmp 0x7d02c9
007cfd5b mov ecx, dword ptr [0xbfd65c]
007cfd61 cmp dword ptr [ecx + 0x18194], -0xd
007cfd68 jne 0x7cffe3
007cfd6e mov dword ptr [ebp - 0x20], 0
007cfd75 mov dword ptr [ebp - 0x1c], 0
007cfd7c mov dword ptr [ebp - 0x18], 0
007cfd83 lea eax, [ebp - 0x14]
007cfd86 mov dword ptr [ebp - 4], 2
007cfd8d push eax
007cfd8e push 0
007cfd90 lea ecx, [ebp - 0x20]
007cfd93 mov dword ptr [ebp - 0x14], 8
007cfd9a call 0x426fb0
007cfd9f push 2
007cfda1 lea ecx, [ebp - 0x30]
007cfda4 call 0x7a7d50
007cfda9 mov esi, dword ptr [ebp - 0x1c]
007cfdac neg eax
007cfdae mov ebx, dword ptr [ebp - 0x18]
007cfdb1 sbb eax, eax
007cfdb3 add eax, 0xd
007cfdb6 mov dword ptr [ebp - 0x14], eax
007cfdb9 cmp esi, ebx
007cfdbb je 0x7cfdc7
007cfdbd mov dword ptr [esi], eax
007cfdbf add esi, 4
007cfdc2 mov dword ptr [ebp - 0x1c], esi
007cfdc5 jmp 0x7cfdda
007cfdc7 lea eax, [ebp - 0x14]
007cfdca push eax
007cfdcb push esi
007cfdcc lea ecx, [ebp - 0x20]
007cfdcf call 0x426fb0
007cfdd4 mov ebx, dword ptr [ebp - 0x18]
007cfdd7 mov esi, dword ptr [ebp - 0x1c]
007cfdda push 8
007cfddc lea ecx, [ebp - 0x30]
007cfddf call 0x7a7d50
007cfde4 neg eax
007cfde6 sbb eax, eax
007cfde8 and eax, 0xfffffffb
007cfdeb add eax, 0xe
007cfdee mov dword ptr [ebp - 0x14], eax
007cfdf1 cmp esi, ebx
007cfdf3 je 0x7cfdff
007cfdf5 mov dword ptr [esi], eax
007cfdf7 add esi, 4
007cfdfa mov dword ptr [ebp - 0x1c], esi
007cfdfd jmp 0x7cfe12
007cfdff lea eax, [ebp - 0x14]
007cfe02 push eax
007cfe03 push esi
007cfe04 lea ecx, [ebp - 0x20]
007cfe07 call 0x426fb0
007cfe0c mov ebx, dword ptr [ebp - 0x18]
007cfe0f mov esi, dword ptr [ebp - 0x1c]
007cfe12 mov dword ptr [ebp - 0x14], 0xb
007cfe19 cmp esi, ebx
007cfe1b je 0x7cfe2b
007cfe1d mov dword ptr [esi], 0xb
007cfe23 add esi, 4
007cfe26 mov dword ptr [ebp - 0x1c], esi
007cfe29 jmp 0x7cfe3e
007cfe2b lea eax, [ebp - 0x14]
007cfe2e push eax
007cfe2f push esi
007cfe30 lea ecx, [ebp - 0x20]
007cfe33 call 0x426fb0
007cfe38 mov ebx, dword ptr [ebp - 0x18]
007cfe3b mov esi, dword ptr [ebp - 0x1c]
007cfe3e mov dword ptr [ebp - 0x14], 0xb
007cfe45 cmp esi, ebx
007cfe47 je 0x7cfe57
007cfe49 mov dword ptr [esi], 0xb
007cfe4f add esi, 4
007cfe52 mov dword ptr [ebp - 0x1c], esi
007cfe55 jmp 0x7cfe6a
007cfe57 lea eax, [ebp - 0x14]
007cfe5a push eax
007cfe5b push esi
007cfe5c lea ecx, [ebp - 0x20]
007cfe5f call 0x426fb0
007cfe64 mov ebx, dword ptr [ebp - 0x18]
007cfe67 mov esi, dword ptr [ebp - 0x1c]
007cfe6a mov dword ptr [ebp - 0x14], 0xf
007cfe71 cmp esi, ebx
007cfe73 je 0x7cfe83
007cfe75 mov dword ptr [esi], 0xf
007cfe7b add esi, 4
007cfe7e mov dword ptr [ebp - 0x1c], esi
007cfe81 jmp 0x7cfe96
007cfe83 lea eax, [ebp - 0x14]
007cfe86 push eax
007cfe87 push esi
007cfe88 lea ecx, [ebp - 0x20]
007cfe8b call 0x426fb0
007cfe90 mov ebx, dword ptr [ebp - 0x18]
007cfe93 mov esi, dword ptr [ebp - 0x1c]
007cfe96 mov dword ptr [ebp - 0x14], 6
007cfe9d cmp esi, ebx
007cfe9f je 0x7cfeaf
007cfea1 mov dword ptr [esi], 6
007cfea7 add esi, 4
007cfeaa mov dword ptr [ebp - 0x1c], esi
007cfead jmp 0x7cfec2
007cfeaf lea eax, [ebp - 0x14]
007cfeb2 push eax
007cfeb3 push esi
007cfeb4 lea ecx, [ebp - 0x20]
007cfeb7 call 0x426fb0
007cfebc mov ebx, dword ptr [ebp - 0x18]
007cfebf mov esi, dword ptr [ebp - 0x1c]
007cfec2 mov dword ptr [ebp - 0x14], 0x10
007cfec9 cmp esi, ebx
007cfecb je 0x7cfed8
007cfecd mov dword ptr [esi], 0x10
007cfed3 add esi, 4
007cfed6 jmp 0x7cfee8
007cfed8 lea eax, [ebp - 0x14]
007cfedb push eax
007cfedc push esi
007cfedd lea ecx, [ebp - 0x20]
007cfee0 call 0x426fb0
007cfee5 mov esi, dword ptr [ebp - 0x1c]
007cfee8 mov ebx, dword ptr [ebp - 0x20]
007cfeeb lea ecx, [ebp - 0x30]
007cfeee push esi
007cfeef push ebx
007cfef0 call 0x5b6400
007cfef5 sub esi, ebx
007cfef7 mov eax, 8
007cfefc sar esi, 2
007cfeff add esp, 8
007cff02 xor edx, edx
007cff04 cmp esi, eax
007cff06 cmovl eax, esi
007cff09 mov dword ptr [ebp - 0x14], eax
007cff0c test eax, eax
007cff0e jle 0x7cff2a
007cff10 mov esi, 0x94
007cff15 mov ecx, dword ptr [edi + 4]
007cff18 lea esi, [esi + 2]
007cff1b mov ax, word ptr [ebx + edx*4]
007cff1f inc edx
007cff20 mov word ptr [esi + ecx - 2], ax
007cff25 cmp edx, dword ptr [ebp - 0x14]
007cff28 jl 0x7cff15
007cff2a mov eax, dword ptr [edi + 4]
007cff2d xor ecx, ecx
007cff2f mov esi, dword ptr [ebp - 0x30]
007cff32 mov word ptr [eax + 0xac], cx
007cff39 test esi, esi
007cff3b jne 0x7cff4d
007cff3d push 0xb4d6c4
007cff42 push 3
007cff44 call 0x95e330
007cff49 add esp, 8
007cff4c int3
007cff4d mov ecx, dword ptr [ebp - 0x2c]
007cff50 mov eax, esi
007cff52 shr eax, cl
007cff54 mov ecx, dword ptr [ebp - 0x28]
007cff57 xor eax, esi
007cff59 mov edx, eax
007cff5b shl edx, cl
007cff5d mov ecx, dword ptr [ebp - 0x24]
007cff60 xor edx, eax
007cff62 mov ebx, edx
007cff64 mov eax, 0xaaaaaaab
007cff69 shr ebx, cl
007cff6b xor ebx, edx
007cff6d mul ebx
007cff6f mov ecx, ebx
007cff71 mov dword ptr [ebp - 0x30], ebx
007cff74 shr edx, 1
007cff76 lea eax, [edx + edx*2]
007cff79 sub ecx, eax
007cff7b je 0x7cff96
007cff7d push 8
007cff7f lea ecx, [ebp - 0x30]
007cff82 call 0x7a7d50
007cff87 mov ecx, dword ptr [edi + 4]
007cff8a mov ebx, dword ptr [ebp - 0x30]
007cff8d mov word ptr [ecx + 0xae], ax
007cff94 jmp 0x7cffa3
007cff96 mov eax, dword ptr [edi + 4]
007cff99 or ecx, 0xffffffff
007cff9c mov word ptr [eax + 0xae], cx
007cffa3 mov edx, dword ptr [ebp - 0x20]
007cffa6 test edx, edx
007cffa8 je 0x7d02c9
007cffae mov ecx, dword ptr [ebp - 0x18]
007cffb1 mov eax, edx
007cffb3 sub ecx, edx
007cffb5 and ecx, 0xfffffffc
007cffb8 cmp ecx, 0x1000
007cffbe jb 0x7cffd4
007cffc0 mov edx, dword ptr [edx - 4]
007cffc3 add ecx, 0x23
007cffc6 sub eax, edx
007cffc8 add eax, -4
007cffcb cmp eax, 0x1f
007cffce ja 0x7d01e6
007cffd4 push ecx
007cffd5 push edx
007cffd6 call 0x9eb08e
007cffdb add esp, 8
007cffde jmp 0x7d02c9
007cffe3 call 0x6cba40
007cffe8 test al, al
007cffea jne 0x7d01ec
007cfff0 cmp esi, 2
007cfff3 jne 0x7d0009
007cfff5 mov eax, dword ptr [ebx + 0x10]
007cfff8 mov eax, dword ptr [eax + 0x10]
007cfffb cmp eax, 0x64
007cfffe jb 0x7d0009
007d0000 cmp eax, 0x78
007d0003 jb 0x7d01ec
007d0009 xor esi, esi
007d000b mov dword ptr [ebp - 0x20], 0
007d0012 xor eax, eax
007d0014 mov dword ptr [ebp - 0x1c], esi
007d0017 mov dword ptr [ebp - 0x18], eax
007d001a xor ebx, ebx
007d001c mov dword ptr [ebp - 4], 3
007d0023 mov dword ptr [ebp - 0x14], ebx
007d0026 cmp esi, eax
007d0028 je 0x7d0034
007d002a mov dword ptr [esi], ebx
007d002c add esi, 4
007d002f mov dword ptr [ebp - 0x1c], esi
007d0032 jmp 0x7d0047
007d0034 lea eax, [ebp - 0x14]
007d0037 push eax
007d0038 push esi
007d0039 lea ecx, [ebp - 0x20]
007d003c call 0x426fb0
007d0041 mov eax, dword ptr [ebp - 0x18]
007d0044 mov esi, dword ptr [ebp - 0x1c]
007d0047 inc ebx
007d0048 mov dword ptr [ebp - 0x14], ebx
007d004b cmp ebx, 8
007d004e jl 0x7d0026
007d0050 cmp dword ptr [edi + 0x6f5c], 4
007d0057 mov dword ptr [ebp - 0x14], eax
007d005a jl 0x7d0088
007d005c mov dword ptr [ebp - 0x34], 8
007d0063 cmp esi, eax
007d0065 je 0x7d0072
007d0067 mov dword ptr [esi], 8
007d006d add esi, 4
007d0070 jmp 0x7d0088
007d0072 lea eax, [ebp - 0x34]
007d0075 push eax
007d0076 push esi
007d0077 lea ecx, [ebp - 0x20]
007d007a call 0x426fb0
007d007f mov eax, dword ptr [ebp - 0x18]
007d0082 mov esi, dword ptr [ebp - 0x1c]
007d0085 mov dword ptr [ebp - 0x14], eax
007d0088 mov ebx, dword ptr [ebp - 0x20]
007d008b lea ecx, [ebp - 0x30]
007d008e push esi
007d008f push ebx
007d0090 call 0x5b6400
007d0095 sub esi, ebx
007d0097 mov eax, 8
007d009c sar esi, 2
007d009f add esp, 8
007d00a2 xor edx, edx
007d00a4 cmp esi, eax
007d00a6 cmovl eax, esi
007d00a9 mov dword ptr [ebp - 0x34], eax
007d00ac test eax, eax
007d00ae jle 0x7d00ca
007d00b0 mov esi, 0x94
007d00b5 mov ecx, dword ptr [edi + 4]
007d00b8 lea esi, [esi + 2]
007d00bb mov ax, word ptr [ebx + edx*4]
007d00bf inc edx
007d00c0 mov word ptr [esi + ecx - 2], ax
007d00c5 cmp edx, dword ptr [ebp - 0x34]
007d00c8 jl 0x7d00b5
007d00ca mov esi, dword ptr [ebp - 0x30]
007d00cd test esi, esi
007d00cf jne 0x7d00e1
007d00d1 push 0xb4d6c4
007d00d6 push 3
007d00d8 call 0x95e330
007d00dd add esp, 8
007d00e0 int3
007d00e1 mov ebx, dword ptr [ebp - 0x2c]
007d00e4 mov eax, esi
007d00e6 mov ecx, ebx
007d00e8 shr eax, cl
007d00ea mov ecx, dword ptr [ebp - 0x28]
007d00ed xor eax, esi
007d00ef mov edx, eax
007d00f1 shl edx, cl
007d00f3 mov ecx, dword ptr [ebp - 0x24]
007d00f6 xor edx, eax
007d00f8 mov eax, dword ptr [edi + 4]
007d00fb mov esi, edx
007d00fd shr esi, cl
007d00ff xor esi, edx
007d0101 mov edx, 8
007d0106 mov ecx, esi
007d0108 and ecx, 1
007d010b mov word ptr [eax + ecx*2 + 0x94], dx
007d0113 xor ecx, ecx
007d0115 mov eax, dword ptr [edi + 4]
007d0118 mov word ptr [eax + 0xac], cx
007d011f test esi, esi
007d0121 jne 0x7d0133
007d0123 push 0xb4d6c4
007d0128 push 3
007d012a call 0x95e330
007d012f add esp, 8
007d0132 int3
007d0133 mov ecx, ebx
007d0135 mov eax, esi
007d0137 shr eax, cl
007d0139 xor eax, esi
007d013b mov esi, dword ptr [ebp - 0x28]
007d013e mov edx, eax
007d0140 mov ecx, esi
007d0142 shl edx, cl
007d0144 mov ecx, dword ptr [ebp - 0x24]
007d0147 xor edx, eax
007d0149 mov ebx, edx
007d014b mov eax, 0xaaaaaaab
007d0150 shr ebx, cl
007d0152 xor ebx, edx
007d0154 mul ebx
007d0156 mov ecx, ebx
007d0158 shr edx, 1
007d015a lea eax, [edx + edx*2]
007d015d sub ecx, eax
007d015f je 0x7d01a4
007d0161 test ebx, ebx
007d0163 jne 0x7d0175
007d0165 push 0xb4d6c4
007d016a push 3
007d016c call 0x95e330
007d0171 add esp, 8
007d0174 int3
007d0175 mov ecx, dword ptr [ebp - 0x2c]
007d0178 mov eax, ebx
007d017a shr eax, cl
007d017c mov ecx, esi
007d017e xor eax, ebx
007d0180 mov edx, eax
007d0182 shl edx, cl
007d0184 mov ecx, dword ptr [ebp - 0x24]
007d0187 xor edx, eax
007d0189 mov ebx, edx
007d018b mov eax, 0xaaaaaaab
007d0190 shr ebx, cl
007d0192 xor ebx, edx
007d0194 mul ebx
007d0196 mov ecx, ebx
007d0198 shr edx, 2
007d019b lea eax, [edx + edx*2]
007d019e add eax, eax
007d01a0 sub ecx, eax
007d01a2 jmp 0x7d01a7
007d01a4 or ecx, 0xffffffff
007d01a7 mov eax, dword ptr [edi + 4]
007d01aa mov edx, dword ptr [ebp - 0x20]
007d01ad mov word ptr [eax + 0xae], cx
007d01b4 test edx, edx
007d01b6 je 0x7d02c9
007d01bc mov ecx, dword ptr [ebp - 0x14]
007d01bf mov eax, edx
007d01c1 sub ecx, edx
007d01c3 and ecx, 0xfffffffc
007d01c6 cmp ecx, 0x1000
007d01cc jb 0x7cffd4
007d01d2 mov edx, dword ptr [edx - 4]
007d01d5 add ecx, 0x23
007d01d8 sub eax, edx
007d01da add eax, -4
007d01dd cmp eax, 0x1f
007d01e0 jbe 0x7cffd4
007d01e6 call dword ptr [0xa065ac]
007d01ec mov eax, 3
007d01f1 xor ecx, ecx
007d01f3 mov word ptr [ebx + 0x94], ax
007d01fa mov eax, dword ptr [edi + 4]
007d01fd mov word ptr [eax + 0x96], cx
007d0204 mov ecx, 8
007d0209 mov eax, dword ptr [edi + 4]
007d020c mov word ptr [eax + 0x98], cx
007d0213 mov ecx, 9
007d0218 mov eax, dword ptr [edi + 4]
007d021b mov word ptr [eax + 0x9a], cx
007d0222 lea ecx, [ebp - 0x30]
007d0225 call 0x7a7e20
007d022a mov ecx, eax
007d022c call 0x7cf770
007d0231 mov ecx, dword ptr [edi + 4]
007d0234 mov word ptr [ecx + 0x9c], ax
007d023b lea ecx, [ebp - 0x30]
007d023e call 0x7a7e20
007d0243 mov ecx, eax
007d0245 call 0x7cf770
007d024a mov ecx, dword ptr [edi + 4]
007d024d mov word ptr [ecx + 0x9e], ax
007d0254 lea ecx, [ebp - 0x30]
007d0257 call 0x7a7e20
007d025c mov ecx, eax
007d025e call 0x7cf770
007d0263 mov ecx, dword ptr [edi + 4]
007d0266 mov word ptr [ecx + 0xa0], ax
007d026d lea ecx, [ebp - 0x30]
007d0270 call 0x7a7e20
007d0275 mov ecx, eax
007d0277 call 0x7cf770
007d027c mov ecx, dword ptr [edi + 4]
007d027f push 3
007d0281 mov word ptr [ecx + 0xa2], ax
007d0288 xor ecx, ecx
007d028a mov eax, dword ptr [edi + 4]
007d028d mov word ptr [eax + 0xac], cx
007d0294 lea ecx, [ebp - 0x30]
007d0297 call 0x7a7d50
007d029c test eax, eax
007d029e je 0x7d02b9
007d02a0 push 8
007d02a2 lea ecx, [ebp - 0x30]
007d02a5 call 0x7a7d50
007d02aa mov ecx, dword ptr [edi + 4]
007d02ad mov ebx, dword ptr [ebp - 0x30]
007d02b0 mov word ptr [ecx + 0xae], ax
007d02b7 jmp 0x7d02c9
007d02b9 mov ebx, dword ptr [ebp - 0x30]
007d02bc or ecx, 0xffffffff
007d02bf mov eax, dword ptr [edi + 4]
007d02c2 mov word ptr [eax + 0xae], cx
007d02c9 mov eax, dword ptr [edi + 4]
007d02cc mov dword ptr [eax + 0x60], ebx
007d02cf mov ecx, dword ptr [ebp - 0xc]
007d02d2 mov dword ptr fs:[0], ecx
007d02d9 pop ecx
007d02da pop edi
007d02db pop esi
007d02dc pop ebx
007d02dd mov ecx, dword ptr [ebp - 0x10]
007d02e0 xor ecx, ebp
007d02e2 call 0x9eacd7
007d02e7 mov esp, ebp
007d02e9 pop ebp
007d02ea ret
007d02eb mov ebx, dword ptr [ebp - 0x34]
007d02ee mov eax, dword ptr [edi + 4]
007d02f1 mov ecx, 8
007d02f6 mov word ptr [eax + 0x94], cx
007d02fd mov eax, dword ptr [edi + 4]
007d0300 mov word ptr [eax + 0x96], cx
007d0307 mov eax, dword ptr [edi + 4]
007d030a mov word ptr [eax + 0x98], cx
007d0311 mov eax, dword ptr [edi + 4]
007d0314 mov word ptr [eax + 0x9a], cx
007d031b mov eax, dword ptr [edi + 4]
007d031e mov word ptr [eax + 0x9c], cx
007d0325 mov eax, dword ptr [edi + 4]
007d0328 mov word ptr [eax + 0x9e], cx
007d032f mov eax, dword ptr [edi + 4]
007d0332 mov word ptr [eax + 0xa0], cx
007d0339 mov eax, dword ptr [edi + 4]
007d033c mov word ptr [eax + 0xa2], cx
007d0343 xor ecx, ecx
007d0345 mov eax, dword ptr [edi + 4]
007d0348 mov word ptr [eax + 0xac], cx
007d034f test ebx, ebx
007d0351 jne 0x7d0363
007d0353 push 0xb4d6c4
007d0358 push 3
007d035a call 0x95e330
007d035f add esp, 8
007d0362 int3
007d0363 mov ecx, dword ptr [ebp - 0x2c]
007d0366 mov edx, ebx
007d0368 mov esi, dword ptr [ebp - 0x14]
007d036b shr edx, cl
007d036d mov ecx, dword ptr [ebp - 0x28]
007d0370 xor edx, ebx
007d0372 mov eax, edx
007d0374 shl eax, cl
007d0376 mov ecx, esi
007d0378 xor eax, edx
007d037a mov ebx, eax
007d037c shr ebx, cl
007d037e xor ebx, eax
007d0380 mov eax, 0xaaaaaaab
007d0385 mul ebx
007d0387 mov ecx, ebx
007d0389 shr edx, 1
007d038b lea eax, [edx + edx*2]
007d038e sub ecx, eax
007d0390 je 0x7d02bc
007d0396 test ebx, ebx
007d0398 jne 0x7d03aa
007d039a push 0xb4d6c4
007d039f push 3
007d03a1 call 0x95e330
007d03a6 add esp, 8
007d03a9 int3
007d03aa mov ecx, dword ptr [ebp - 0x2c]
007d03ad mov eax, ebx
007d03af shr eax, cl
007d03b1 mov ecx, dword ptr [ebp - 0x28]
007d03b4 xor eax, ebx
007d03b6 mov edx, eax
007d03b8 shl edx, cl
007d03ba mov ecx, esi
007d03bc xor edx, eax
007d03be mov eax, 0xaaaaaaab
007d03c3 mov ebx, edx
007d03c5 shr ebx, cl
007d03c7 xor ebx, edx
007d03c9 mul ebx
007d03cb mov ecx, ebx
007d03cd shr edx, 2
007d03d0 lea eax, [edx + edx*2]
007d03d3 add eax, eax
007d03d5 sub ecx, eax
007d03d7 jmp 0x7d02bf
