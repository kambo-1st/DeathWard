0078c350 push ebx
0078c351 mov ebx, esp
0078c353 sub esp, 8
0078c356 and esp, 0xfffffff8
0078c359 add esp, 4
0078c35c push ebp
0078c35d mov ebp, dword ptr [ebx + 4]
0078c360 mov dword ptr [esp + 4], ebp
0078c364 mov ebp, esp
0078c366 push -1
0078c368 push 0x9f9068
0078c36d mov eax, dword ptr fs:[0]
0078c373 push eax
0078c374 push ebx
0078c375 sub esp, 0x90
0078c37b mov eax, dword ptr [0xbaa3b4]
0078c380 xor eax, ebp
0078c382 mov dword ptr [ebp - 0x14], eax
0078c385 push esi
0078c386 push edi
0078c387 push eax
0078c388 lea eax, [ebp - 0xc]
0078c38b mov dword ptr fs:[0], eax
0078c391 mov edi, ecx
0078c393 mov dword ptr [ebp - 0x78], edi
0078c396 cmp dword ptr [ebx + 8], 0
0078c39a jle 0x78c7e5
0078c3a0 mov esi, dword ptr [0xbfd680]
0078c3a6 lea ecx, [ebp - 0x70]
0078c3a9 mov dword ptr [ebp - 0x70], 0x1ab
0078c3b0 call 0x8b1340
0078c3b5 sub esp, 8
0078c3b8 mov dword ptr [esp + 4], 0
0078c3c0 mov dword ptr [esp], 0x3f800000
0078c3c7 push 0
0078c3c9 push 2
0078c3cb push ecx
0078c3cc mov dword ptr [esp], 0x3f800000
0078c3d3 lea ecx, [esi + 0x29de0]
0078c3d9 push dword ptr [ebp - 0x70]
0078c3dc call 0x888de0
0078c3e1 call 0x6c3d90
0078c3e6 push eax
0078c3e7 push 0
0078c3e9 push 0
0078c3eb push 0xc02fec
0078c3f0 lea ecx, [edi + 0x294]
0078c3f6 push ecx
0078c3f7 mov ecx, dword ptr [0xbfd65c]
0078c3fd push 0xf
0078c3ff push 0x3e8
0078c404 call 0x422e20
0078c409 mov esi, eax
0078c40b mov dword ptr [ebp - 0x2c], 0
0078c412 push 0x30
0078c414 mov dword ptr [ebp - 0x74], esi
0078c417 mov dword ptr [ebp - 0x1c], 0
0078c41e mov dword ptr [ebp - 0x18], 0xf
0078c425 mov byte ptr [ebp - 0x2c], 0
0078c429 call 0x407de0
0078c42e movups xmm0, xmmword ptr [0xb4cf90]
0078c435 mov dword ptr [ebp - 0x1c], 0x20
0078c43c mov dword ptr [ebp - 0x18], 0x2f
0078c443 movups xmmword ptr [eax], xmm0
0078c446 movups xmm0, xmmword ptr [0xb4cfa0]
0078c44d movups xmmword ptr [eax + 0x10], xmm0
0078c451 mov byte ptr [eax + 0x20], 0
0078c455 mov dword ptr [ebp - 0x2c], eax
0078c458 add esi, 0x3c
0078c45b mov dword ptr [ebp - 4], 0
0078c462 push 1
0078c464 lea eax, [ebp - 0x2c]
0078c467 mov dword ptr [ebp - 0x70], esi
0078c46a push eax
0078c46b mov ecx, esi
0078c46d call 0x407160
0078c472 mov dword ptr [ebp - 4], 0xffffffff
0078c479 mov edx, dword ptr [ebp - 0x18]
0078c47c cmp edx, 0x10
0078c47f jb 0x78c4af
0078c481 mov ecx, dword ptr [ebp - 0x2c]
0078c484 inc edx
0078c485 mov eax, ecx
0078c487 cmp edx, 0x1000
0078c48d jb 0x78c4a5
0078c48f mov ecx, dword ptr [ecx - 4]
0078c492 add edx, 0x23
0078c495 sub eax, ecx
0078c497 add eax, -4
0078c49a cmp eax, 0x1f
0078c49d jbe 0x78c4a5
0078c49f call dword ptr [0xa065ac]
0078c4a5 push edx
0078c4a6 push ecx
0078c4a7 call 0x9eb08e
0078c4ac add esp, 8
0078c4af mov esi, dword ptr [esi + 0x34]
0078c4b2 test esi, esi
0078c4b4 je 0x78c4fd
0078c4b6 cmp dword ptr [esi + 0x14], 0x10
0078c4ba mov eax, esi
0078c4bc jb 0x78c4c0
0078c4be mov eax, dword ptr [esi]
0078c4c0 mov ecx, 0xb4cfdc
0078c4c5 mov dl, byte ptr [eax]
0078c4c7 cmp dl, byte ptr [ecx]
0078c4c9 jne 0x78c4e5
0078c4cb test dl, dl
0078c4cd je 0x78c4e1
0078c4cf mov dl, byte ptr [eax + 1]
0078c4d2 cmp dl, byte ptr [ecx + 1]
0078c4d5 jne 0x78c4e5
0078c4d7 add eax, 2
0078c4da add ecx, 2
0078c4dd test dl, dl
0078c4df jne 0x78c4c5
0078c4e1 xor eax, eax
0078c4e3 jmp 0x78c4ea
0078c4e5 sbb eax, eax
0078c4e7 or eax, 1
0078c4ea test eax, eax
0078c4ec jne 0x78c4fd
0078c4ee cmp byte ptr [esi + 0x34], al
0078c4f1 je 0x78c51e
0078c4f3 mov esi, dword ptr [ebp - 0x70]
0078c4f6 cmp byte ptr [esi + 0x44], al
0078c4f9 jne 0x78c51e
0078c4fb jmp 0x78c500
0078c4fd mov esi, dword ptr [ebp - 0x70]
0078c500 push 1
0078c502 push 0xb4cfdc
0078c507 mov ecx, esi
0078c509 call 0x405740
0078c50e test al, al
0078c510 je 0x78c51e
0078c512 lea ecx, [esi + 0x30]
0078c515 call 0x405330
0078c51a mov byte ptr [esi + 0x44], 1
0078c51e mov ecx, dword ptr [ebp - 0x74]
0078c521 mov eax, dword ptr [ecx]
0078c523 call dword ptr [eax + 0xc]
0078c526 call 0x6c3d90
0078c52b mov ecx, dword ptr [0xbfd65c]
0078c531 lea esi, [edi + 0x294]
0078c537 push eax
0078c538 push 0
0078c53a push 0
0078c53c push 0xc02fec
0078c541 push esi
0078c542 push 0x12
0078c544 push 0x3e8
0078c549 call 0x422e20
0078c54e mov ecx, eax
0078c550 mov edx, dword ptr [eax]
0078c552 mov dword ptr [eax + 0xf4], 0x41200000
0078c55c mov dword ptr [eax + 0xf8], 0x40f00000
0078c566 mov dword ptr [eax + 0xfc], 0
0078c570 mov dword ptr [eax + 0x100], 0x3f800000
0078c57a call dword ptr [edx + 0xc]
0078c57d nop dword ptr [eax]
0078c580 movaps xmm0, xmmword ptr [0xb6c610]
0078c587 movups xmmword ptr [ebp - 0x40], xmm0
0078c58b mov dword ptr [ebp - 0x20], 0
0078c592 xorps xmm0, xmm0
0078c595 mov dword ptr [ebp - 0x1c], 0
0078c59c movups xmmword ptr [ebp - 0x30], xmm0
0078c5a0 mov dword ptr [ebp - 0x18], 0
0078c5a7 call 0x6c3d90
0078c5ac push 0
0078c5ae push ecx
0078c5af movd xmm0, eax
0078c5b3 cvtdq2pd xmm0, xmm0
0078c5b7 shr eax, 0x1f
0078c5ba addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0078c5c3 lea eax, [ebp - 0x40]
0078c5c6 cvtpd2ps xmm1, xmm0
0078c5ca movss xmm0, dword ptr [edi + 0x2a8]
0078c5d2 mulss xmm1, dword ptr [0xb6a19c]
0078c5da movss dword ptr [esp], xmm0
0078c5df push eax
0078c5e0 mulss xmm1, dword ptr [0xb6a98c]
0078c5e8 push ecx
0078c5e9 mov ecx, dword ptr [0xbfd65c]
0078c5ef addss xmm1, dword ptr [0xb6a940]
0078c5f7 movss dword ptr [esp], xmm1
0078c5fc push 0xa
0078c5fe push 0x5f
0078c600 push esi
0078c601 call 0x6d57a0
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
0078c6dd sub dword ptr [ebx + 8], 1
0078c6e1 jne 0x78c580
0078c6e7 movss xmm3, dword ptr [0xb6aad4]
0078c6ef lea eax, [ebp - 0xa0]
0078c6f5 push 8
0078c6f7 push esi
0078c6f8 push eax
0078c6f9 mov eax, dword ptr [0xbfd65c]
0078c6fe mov ecx, dword ptr [eax + 0x18190]
0078c704 add ecx, 0x1218
0078c70a call 0x4157f0
0078c70f xor edi, edi
0078c711 mov dword ptr [ebp - 4], 1
0078c718 cmp dword ptr [ebp - 0x94], edi
0078c71e jbe 0x78c7ce
0078c724 mov eax, dword ptr [ebp - 0x9c]
0078c72a mov esi, dword ptr [eax + edi*4]
0078c72d mov eax, dword ptr [esi + 0x28]
0078c730 sub eax, 0xa
0078c733 cmp eax, 0x3dd
0078c738 ja 0x78c7c1
0078c73e mov ecx, esi
0078c740 mov dword ptr [esi + 0x230], 0
0078c74a call 0x681390
0078c74f push dword ptr [ebp - 0x78]
0078c752 lea ecx, [ebp - 0x3c]
0078c755 call 0x4229a0
0078c75a push 0xb4
0078c75f lea eax, [ebp - 0x3c]
0078c762 mov ecx, esi
0078c764 push eax
0078c765 call 0x685990
0078c76a mov eax, dword ptr [esi + 0x160]
0078c770 and eax, 0x400
0078c775 or eax, 0
0078c778 je 0x78c77e
0078c77a mov al, 1
0078c77c jmp 0x78c780
0078c77e xor al, al
0078c780 test al, al
0078c782 je 0x78c7c1
0078c784 mov eax, dword ptr [esi]
0078c786 lea ecx, [ebp - 0x6c]
0078c789 push 1
0078c78b push 1
0078c78d push 0xff
0078c792 xorps xmm0, xmm0
0078c795 mov dword ptr [ebp - 0x4c], 0x3f800000
0078c79c push 0xf
0078c79e movups xmmword ptr [ebp - 0x5c], xmm0
0078c7a2 push ecx
0078c7a3 movaps xmm0, xmmword ptr [0xb6c610]
0078c7aa mov ecx, esi
0078c7ac movups xmmword ptr [ebp - 0x6c], xmm0
0078c7b0 mov dword ptr [ebp - 0x48], 0x3f666666
0078c7b7 mov dword ptr [ebp - 0x44], 0
0078c7be call dword ptr [eax + 0x38]
0078c7c1 inc edi
0078c7c2 cmp edi, dword ptr [ebp - 0x94]
0078c7c8 jb 0x78c724
0078c7ce cmp byte ptr [ebp - 0xa0], 0
0078c7d5 jne 0x78c7e5
0078c7d7 push dword ptr [ebp - 0x9c]
0078c7dd call 0x9eace5
0078c7e2 add esp, 4
0078c7e5 mov ecx, dword ptr [ebp - 0xc]
0078c7e8 mov dword ptr fs:[0], ecx
0078c7ef pop ecx
0078c7f0 pop edi
0078c7f1 pop esi
0078c7f2 mov ecx, dword ptr [ebp - 0x14]
0078c7f5 xor ecx, ebp
0078c7f7 call 0x9eacd7
0078c7fc mov esp, ebp
0078c7fe pop ebp
0078c7ff mov esp, ebx
0078c801 pop ebx
0078c802 ret 4
0078c805 int3 
0078c806 int3 
0078c807 int3 
0078c808 int3 
0078c809 int3 
0078c80a int3 
0078c80b int3 
0078c80c int3 
0078c80d int3 
0078c80e int3 
0078c80f int3 
