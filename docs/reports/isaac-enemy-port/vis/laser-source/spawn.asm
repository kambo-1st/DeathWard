008c7550 push ebp
008c7551 mov ebp, esp
008c7553 and esp, 0xfffffff8
008c7556 push ecx
008c7557 push ebx
008c7558 push esi
008c7559 push edi
008c755a call 0x6c3d90
008c755f movzx ecx, byte ptr [ebp + 0x20]
008c7563 mov ebx, dword ptr [ebp + 0x1c]
008c7566 push ecx
008c7567 mov ecx, dword ptr [0xbfd65c]
008c756d push eax
008c756e push 0
008c7570 push ebx
008c7571 push 0xc02fec
008c7576 push dword ptr [ebp + 0xc]
008c7579 push dword ptr [ebp + 8]
008c757c push 7
008c757e call 0x6d0ca0
008c7583 mov esi, eax
008c7585 test esi, esi
008c7587 jne 0x8c7590
008c7589 pop edi
008c758a pop esi
008c758b pop ebx
008c758c mov esp, ebp
008c758e pop ebp
008c758f ret 
008c7590 mov ecx, dword ptr [ebp + 0x18]
008c7593 movss xmm0, dword ptr [ebp + 0x10]
008c7598 mov eax, dword ptr [ebp + 0x14]
008c759b movss dword ptr [esi + 0x36c], xmm0
008c75a3 movss dword ptr [esi + 0x368], xmm0
008c75ab mov dword ptr [esi + 0x3a8], eax
008c75b1 mov eax, dword ptr [ecx]
008c75b3 mov dword ptr [esi + 0x2a4], eax
008c75b9 mov eax, dword ptr [ecx + 4]
008c75bc mov dword ptr [esi + 0x2a8], eax
008c75c2 test ebx, ebx
008c75c4 je 0x8c7656
008c75ca mov ecx, dword ptr [esi + 0x320]
008c75d0 lea edi, [esi + 0x320]
008c75d6 test ecx, ecx
008c75d8 je 0x8c75ee
008c75da lea eax, [esp + 0xc]
008c75de mov dword ptr [esp + 0xc], edi
008c75e2 push eax
008c75e3 add ecx, 0x324
008c75e9 call 0x4bc3c0
008c75ee push edi
008c75ef mov ecx, ebx
008c75f1 mov dword ptr [edi], ebx
008c75f3 call 0x4bae70
008c75f8 mov ecx, dword ptr [esi + 0x314]
008c75fe lea edi, [esi + 0x314]
008c7604 test ecx, ecx
008c7606 je 0x8c761c
008c7608 lea eax, [esp + 0xc]
008c760c mov dword ptr [esp + 0xc], edi
008c7610 push eax
008c7611 add ecx, 0x324
008c7617 call 0x4bc3c0
008c761c push edi
008c761d mov ecx, ebx
008c761f mov dword ptr [edi], ebx
008c7621 call 0x4bae70
008c7626 movss xmm1, dword ptr [esi + 0x294]
008c762e movss xmm0, dword ptr [esi + 0x298]
008c7636 subss xmm1, dword ptr [ebx + 0x294]
008c763e subss xmm0, dword ptr [ebx + 0x298]
008c7646 movss dword ptr [esi + 0x360], xmm1
008c764e movss dword ptr [esi + 0x364], xmm0
008c7656 pop edi
008c7657 mov eax, esi
008c7659 pop esi
008c765a pop ebx
008c765b mov esp, ebp
008c765d pop ebp
008c765e ret 
