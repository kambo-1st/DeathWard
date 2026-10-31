0089fbb0 push ebp
0089fbb1 mov ebp, esp
0089fbb3 and esp, 0xfffffff8
0089fbb6 sub esp, 0x30
0089fbb9 mov edx, dword ptr [0xbfd680]
0089fbbf push esi
0089fbc0 push edi
0089fbc1 mov dword ptr [esp + 0x1c], ecx
0089fbc5 mov eax, dword ptr [edx + 0x20a9ac]
0089fbcb cmp eax, dword ptr [edx + 0x20a9b0]
0089fbd1 je 0x89fe40
0089fbd7 mov ecx, dword ptr [0xbfd65c]
0089fbdd xor edi, edi
0089fbdf movss xmm0, dword ptr [0xb6aad4]
0089fbe7 movss xmm7, dword ptr [0xb6ac4c]
0089fbef mov eax, dword ptr [ecx + 0x18190]
0089fbf5 movss xmm4, dword ptr [eax + 0x14]
0089fbfa movss xmm6, dword ptr [eax + 0x18]
0089fbff subss xmm4, xmm0
0089fc03 movss xmm2, dword ptr [eax + 0x1c]
0089fc08 subss xmm6, xmm0
0089fc0c movss xmm3, dword ptr [eax + 0x20]
0089fc11 addss xmm2, xmm0
0089fc15 mov eax, dword ptr [ecx + 0x1ba54]
0089fc1b addss xmm3, xmm0
0089fc1f sub eax, dword ptr [ecx + 0x1ba50]
0089fc25 addss xmm4, xmm7
0089fc29 sar eax, 2
0089fc2c addss xmm6, dword ptr [0xb6abac]
0089fc34 subss xmm2, xmm7
0089fc38 subss xmm3, dword ptr [0xb6abac]
0089fc40 movss dword ptr [esp + 0x14], xmm4
0089fc46 movss dword ptr [esp + 0x18], xmm6
0089fc4c movss dword ptr [esp + 0xc], xmm2
0089fc52 movss dword ptr [esp + 0x10], xmm3
0089fc58 test eax, eax
0089fc5a je 0x89ff20
0089fc60 mov edx, dword ptr [ebp + 8]
0089fc63 add edx, 4
0089fc66 movss dword ptr [esp + 0x20], xmm2
0089fc6c movss dword ptr [esp + 0x24], xmm3
0089fc72 mov dword ptr [esp + 8], edx
0089fc76 nop word ptr [eax + eax]
0089fc80 lea esi, [ecx + 0x1ba50]
0089fc86 mov ecx, dword ptr [esi + 4]
0089fc89 mov eax, ecx
0089fc8b sub eax, dword ptr [esi]
0089fc8d test eax, 0xfffffffc
0089fc92 jne 0x89fcca
0089fc94 push 0xb3f4d0
0089fc99 push 3
0089fc9b call 0x95e330
0089fca0 mov ecx, dword ptr [esi + 4]
0089fca3 add esp, 8
0089fca6 movss xmm2, dword ptr [esp + 0xc]
0089fcac movss xmm3, dword ptr [esp + 0x10]
0089fcb2 movss xmm4, dword ptr [esp + 0x14]
0089fcb8 movss xmm6, dword ptr [esp + 0x18]
0089fcbe movss xmm7, dword ptr [0xb6ac4c]
0089fcc6 mov edx, dword ptr [esp + 8]
0089fcca mov eax, dword ptr [esi]
0089fccc sub ecx, eax
0089fcce sar ecx, 2
0089fcd1 cmp edi, ecx
0089fcd3 jae 0x89fcd8
0089fcd5 lea eax, [eax + edi*4]
0089fcd8 mov eax, dword ptr [eax]
0089fcda mov ecx, dword ptr [eax + 0x294]
0089fce0 mov eax, dword ptr [eax + 0x298]
0089fce6 mov dword ptr [esp + 0x34], eax
0089fcea mov eax, dword ptr [esp + 0x1c]
0089fcee mov dword ptr [esp + 0x30], ecx
0089fcf2 cmp byte ptr [eax + 0x8c], 0
0089fcf9 je 0x89fd30
0089fcfb cmp dword ptr [eax + 0x58], 0
0089fcff jle 0x89fd30
0089fd01 lea esi, [eax + 0x50]
0089fd04 mov eax, dword ptr [esi + 8]
0089fd07 dec eax
0089fd08 add eax, dword ptr [esi + 0xc]
0089fd0b cdq 
0089fd0c idiv dword ptr [esi + 4]
0089fd0f mov eax, dword ptr [esi]
0089fd11 movss xmm0, dword ptr [eax + edx*8]
0089fd16 lea eax, [eax + edx*8]
0089fd19 movss xmm1, dword ptr [eax + 4]
0089fd1e mov edx, dword ptr [esp + 8]
0089fd22 movss dword ptr [esp + 0x30], xmm0
0089fd28 movss dword ptr [esp + 0x34], xmm1
0089fd2e jmp 0x89fd3c
0089fd30 movss xmm1, dword ptr [esp + 0x34]
0089fd36 movss xmm0, dword ptr [esp + 0x30]
0089fd3c comiss xmm2, xmm0
0089fd3f lea eax, [esp + 0x30]
0089fd43 lea ecx, [esp + 0x20]
0089fd47 cmovbe eax, ecx
0089fd4a movss xmm0, dword ptr [eax]
0089fd4e comiss xmm0, xmm4
0089fd51 ja 0x89fd59
0089fd53 movss xmm5, xmm4
0089fd57 jmp 0x89fd5d
0089fd59 movss xmm5, xmm0
0089fd5d lea eax, [esp + 0x34]
0089fd61 lea ecx, [esp + 0x24]
0089fd65 comiss xmm3, xmm1
0089fd68 movss dword ptr [esp + 0x30], xmm5
0089fd6e cmovbe eax, ecx
0089fd71 movss xmm0, dword ptr [eax]
0089fd75 comiss xmm0, xmm6
0089fd78 ja 0x89fd80
0089fd7a movss xmm3, xmm6
0089fd7e jmp 0x89fd84
0089fd80 movss xmm3, xmm0
0089fd84 mov ecx, dword ptr [ebp + 8]
0089fd87 lea eax, [esp + 0x28]
0089fd8b movss xmm6, dword ptr [edx]
0089fd8f movaps xmm1, xmm5
0089fd92 addss xmm5, xmm7
0089fd96 movaps xmm4, xmm3
0089fd99 addss xmm3, dword ptr [0xb6abac]
0089fda1 subss xmm4, dword ptr [0xb6abac]
0089fda9 subss xmm1, xmm7
0089fdad comiss xmm5, dword ptr [ecx]
0089fdb0 movss dword ptr [esp + 0x28], xmm5
0089fdb6 movss dword ptr [esp + 0x2c], xmm3
0089fdbc cmova eax, ecx
0089fdbf movss xmm0, dword ptr [eax]
0089fdc3 comiss xmm0, xmm1
0089fdc6 ja 0x89fdce
0089fdc8 movss xmm1, xmm1
0089fdcc jmp 0x89fdd2
0089fdce movss xmm1, xmm0
0089fdd2 lea eax, [esp + 0x2c]
0089fdd6 comiss xmm3, xmm6
0089fdd9 cmova eax, edx
0089fddc movss xmm0, dword ptr [eax]
0089fde0 comiss xmm0, xmm4
0089fde3 ja 0x89fdeb
0089fde5 movss xmm0, xmm4
0089fde9 jmp 0x89fdef
0089fdeb movss xmm0, xmm0
0089fdef ucomiss xmm1, dword ptr [ecx]
0089fdf2 lahf 
0089fdf3 test ah, 0x44
0089fdf6 jp 0x89fe05
0089fdf8 ucomiss xmm0, xmm6
0089fdfb lahf 
0089fdfc test ah, 0x44
0089fdff jnp 0x89ff16
0089fe05 mov ecx, dword ptr [0xbfd65c]
0089fe0b inc edi
0089fe0c mov eax, dword ptr [ecx + 0x1ba54]
0089fe12 sub eax, dword ptr [ecx + 0x1ba50]
0089fe18 sar eax, 2
0089fe1b cmp edi, eax
0089fe1d jae 0x89ff20
0089fe23 movss xmm2, dword ptr [esp + 0xc]
0089fe29 movss xmm3, dword ptr [esp + 0x10]
0089fe2f movss xmm4, dword ptr [esp + 0x14]
0089fe35 movss xmm6, dword ptr [esp + 0x18]
0089fe3b jmp 0x89fc80
0089fe40 movss xmm7, dword ptr [0xbfec08]
0089fe48 movss xmm0, dword ptr [0xc02fec]
0089fe50 movaps xmm4, xmm7
0089fe53 subss xmm4, dword ptr [0xb6ac30]
0089fe5b subss xmm0, dword ptr [0xb6aa8c]
0089fe63 movss xmm3, dword ptr [0xb6a4dc]
0089fe6b movss xmm6, dword ptr [0xbfec68]
0089fe73 movaps xmm2, xmm6
0089fe76 movss xmm1, dword ptr [0xb6a6f4]
0089fe7e mulss xmm4, dword ptr [0xb6a480]
0089fe86 mov eax, dword ptr [ebp + 8]
0089fe89 subss xmm2, dword ptr [0xb6ab8c]
0089fe91 mulss xmm0, xmm3
0089fe95 movss xmm5, dword ptr [ecx + 0x6c]
0089fe9a xorps xmm5, xmmword ptr [0xb6c9b0]
0089fea1 mulss xmm2, dword ptr [0xb6a480]
0089fea9 addss xmm4, xmm0
0089fead movss xmm0, dword ptr [0xc02ff0]
0089feb5 subss xmm0, dword ptr [0xb6ab44]
0089febd mulss xmm5, xmm1
0089fec1 divss xmm4, xmm3
0089fec5 mulss xmm0, xmm3
0089fec9 subss xmm5, xmm4
0089fecd mulss xmm7, xmm1
0089fed1 addss xmm2, xmm0
0089fed5 movss xmm4, dword ptr [ecx + 0x70]
0089feda xorps xmm4, xmmword ptr [0xb6c9b0]
0089fee1 movss xmm0, dword ptr [eax]
0089fee5 comiss xmm0, xmm5
0089fee8 divss xmm2, xmm3
0089feec mulss xmm4, xmm1
0089fef0 mulss xmm6, xmm1
0089fef4 subss xmm4, xmm2
0089fef8 jbe 0x89ff20
0089fefa addss xmm7, xmm5
0089fefe comiss xmm7, xmm0
0089ff01 jbe 0x89ff20
0089ff03 movss xmm0, dword ptr [eax + 4]
0089ff08 comiss xmm0, xmm4
0089ff0b jbe 0x89ff20
0089ff0d addss xmm6, xmm4
0089ff11 comiss xmm6, xmm0
0089ff14 jbe 0x89ff20
0089ff16 mov al, 1
0089ff18 pop edi
0089ff19 pop esi
0089ff1a mov esp, ebp
0089ff1c pop ebp
0089ff1d ret 4
0089ff20 pop edi
0089ff21 xor al, al
0089ff23 pop esi
0089ff24 mov esp, ebp
0089ff26 pop ebp
0089ff27 ret 4
0089ff2a int3 
0089ff2b int3 
0089ff2c int3 
0089ff2d int3 
0089ff2e int3 
0089ff2f int3 
0089ff30 push ebp
0089ff31 mov ebp, esp
0089ff33 push esi
0089ff34 mov esi, ecx
0089ff36 cmp byte ptr [esi + 0x8c], 0
0089ff3d jne 0x89ff51
0089ff3f push dword ptr [ebp + 8]
0089ff42 lea ecx, [esi + 0x50]
0089ff45 call 0x8a0320
