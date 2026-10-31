; Installed-binary disassembly; field interpretations require the source review.
004a8340 push ebp
004a8341 mov ebp, esp
004a8343 movss xmm1, dword ptr [0xb6aa3c]
004a834b push esi
004a834c push edi
004a834d mov edi, ecx
004a834f movss xmm2, dword ptr [0xb6a480]
004a8357 mov eax, dword ptr [0xbfd65c]
004a835c movss xmm0, dword ptr [edi + 0x28c]
004a8364 subss xmm0, xmm1
004a8368 mov edx, dword ptr [eax + 0x18190]
004a836e divss xmm0, xmm1
004a8372 addss xmm0, xmm2
004a8376 cvttss2si esi, xmm0
004a837a test esi, esi
004a837c js 0x4a847d
004a8382 mov ecx, dword ptr [edx + 0xc]
004a8385 cmp esi, ecx
004a8387 jge 0x4a847d
004a838d movss xmm0, dword ptr [edi + 0x290]
004a8395 subss xmm0, dword ptr [0xb6ab20]
004a839d divss xmm0, xmm1
004a83a1 addss xmm0, xmm2
004a83a5 cvttss2si eax, xmm0
004a83a9 test eax, eax
004a83ab js 0x4a847d
004a83b1 cmp eax, dword ptr [edx + 0x10]
004a83b4 jge 0x4a847d
004a83ba imul ecx, eax
004a83bd add ecx, esi
004a83bf cmp ecx, 0x1bf
004a83c5 ja 0x4a847d
004a83cb mov al, byte ptr [ecx + edx + 0x7350]
004a83d2 cmp al, 0xff
004a83d4 je 0x4a847d
004a83da test al, 0x40
004a83dc je 0x4a83e2
004a83de xor eax, eax
004a83e0 jmp 0x4a83f4
004a83e2 test al, 0x10
004a83e4 je 0x4a83eb
004a83e6 or eax, 0xffffffff
004a83e9 jmp 0x4a83f4
004a83eb movzx eax, al
004a83ee shr eax, 5
004a83f1 and eax, 1
004a83f4 mov cl, byte ptr [ecx + edx + 0x7350]
004a83fb movzx ecx, cl
004a83fe and ecx, 0xf
004a8401 test eax, eax
004a8403 je 0x4a847d
004a8405 test ecx, ecx
004a8407 jne 0x4a8441
004a8409 test eax, eax
004a840b jns 0x4a8425
004a840d mov eax, dword ptr [ebp + 8]
004a8410 movss xmm0, dword ptr [0xb6ae44]
004a8418 pop edi
004a8419 pop esi
004a841a movss dword ptr [eax], xmm0
004a841e mov dword ptr [eax + 4], ecx
004a8421 pop ebp
004a8422 ret 4
004a8425 mov eax, dword ptr [ebp + 8]
004a8428 movss xmm0, dword ptr [0xb6a614]
004a8430 pop edi
004a8431 pop esi
004a8432 movss dword ptr [eax], xmm0
004a8436 mov dword ptr [eax + 4], 0
004a843d pop ebp
004a843e ret 4
004a8441 test eax, eax
004a8443 jns 0x4a8461
004a8445 mov eax, dword ptr [ebp + 8]
004a8448 movss xmm0, dword ptr [0xb6ae44]
004a8450 pop edi
004a8451 pop esi
004a8452 mov dword ptr [eax], 0
004a8458 movss dword ptr [eax + 4], xmm0
004a845d pop ebp
004a845e ret 4
004a8461 mov eax, dword ptr [ebp + 8]
004a8464 movss xmm0, dword ptr [0xb6a614]
004a846c pop edi
004a846d pop esi
004a846e mov dword ptr [eax], 0
004a8474 movss dword ptr [eax + 4], xmm0
004a8479 pop ebp
004a847a ret 4
004a847d mov eax, dword ptr [ebp + 8]
004a8480 mov ecx, dword ptr [0xc02fec]
004a8486 mov edx, dword ptr [0xc02ff0]
004a848c pop edi
004a848d mov dword ptr [eax], ecx
004a848f mov dword ptr [eax + 4], edx
004a8492 pop esi
004a8493 pop ebp
