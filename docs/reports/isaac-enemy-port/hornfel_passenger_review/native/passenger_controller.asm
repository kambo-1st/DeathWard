; Installed-binary disassembly; field interpretations require the source review.
004a9240 push ebp
004a9241 mov ebp, esp
004a9243 and esp, 0xfffffff8
004a9246 sub esp, 0x6c
004a9249 mov eax, dword ptr [0xbaa3b4]
004a924e xor eax, esp
004a9250 mov dword ptr [esp + 0x68], eax
004a9254 mov eax, dword ptr [0xbfd65c]
004a9259 push ebx
004a925a mov ebx, ecx
004a925c push esi
004a925d mov esi, dword ptr [eax + 0x18190]
004a9263 push edi
004a9264 cmp dword ptr [ebx + 0x3a0], 0
004a926b mov dword ptr [esp + 0x28], ebx
004a926f jne 0x4a92b2
004a9271 call 0x4a3fb0
004a9276 call 0x6c3d90
004a927b xor edx, edx
004a927d mov dword ptr [ebx + 0x3a0], 1
004a9287 mov ecx, 0xd2
004a928c div ecx
004a928e add edx, 0x96
004a9294 mov dword ptr [ebx + 0x3ac], edx
004a929a mov dword ptr [ebx + 0x3b0], edx
004a92a0 pop edi
004a92a1 pop esi
004a92a2 pop ebx
004a92a3 mov ecx, dword ptr [esp + 0x68]
004a92a7 xor ecx, esp
004a92a9 call 0x9eacd7
004a92ae mov esp, ebp
004a92b0 pop ebp
004a92b1 ret
004a92b2 mov eax, dword ptr [esi + 4]
004a92b5 test byte ptr [eax + 0x44], 1
004a92b9 je 0x4a92c7
004a92bb call 0x4a48b0
004a92c0 mov eax, dword ptr [ebx]
004a92c2 mov ecx, ebx
004a92c4 call dword ptr [eax + 0x28]
004a92c7 mov ecx, dword ptr [esi + 0x12cc]
004a92cd xor eax, eax
004a92cf add ecx, dword ptr [esi + 0x12c8]
004a92d5 test ecx, ecx
004a92d7 cmovg eax, ecx
004a92da test eax, eax
004a92dc jle 0x4a9666
004a92e2 cmp byte ptr [ebx + 0x16b], 0
004a92e9 je 0x4a9666
004a92ef call 0x4a8150
004a92f4 mov dword ptr [esp + 0x30], eax
004a92f8 test eax, eax
004a92fa je 0x4a961d
004a9300 lea ecx, [esp + 0x34]
004a9304 push ecx
004a9305 mov ecx, eax
004a9307 call 0x4a8340
004a930c movss xmm0, dword ptr [esp + 0x34]
004a9312 ucomiss xmm0, dword ptr [0xc02fec]
004a9319 lahf
004a931a test ah, 0x44
004a931d jp 0x4a9336
004a931f movss xmm0, dword ptr [esp + 0x38]
004a9325 ucomiss xmm0, dword ptr [0xc02ff0]
004a932c lahf
004a932d test ah, 0x44
004a9330 jnp 0x4a961d
004a9336 movaps xmm0, xmmword ptr [0xb6b0f0]
004a933d movups xmmword ptr [esp + 0x3c], xmm0
004a9342 mov dword ptr [esp + 0x6c], 0x124
004a934a movaps xmm0, xmmword ptr [0xb6b0d0]
004a9351 movups xmmword ptr [esp + 0x4c], xmm0
004a9356 mov dword ptr [esp + 0x70], 0
004a935e movaps xmm0, xmmword ptr [0xb6b090]
004a9365 movups xmmword ptr [esp + 0x5c], xmm0
004a936a call 0x6c3d90
004a936f xor edx, edx
004a9371 lea esi, [esp + 0x3c]
004a9375 mov ecx, 7
004a937a div ecx
004a937c mov eax, dword ptr [0xbfd65c]
004a9381 mov dword ptr [esp + 0x10], eax
004a9385 lea esi, [esi + edx*8]
004a9388 call 0x6c3d90
004a938d mov dword ptr [esp + 0x20], eax
004a9391 mov eax, dword ptr [esi + 4]
004a9394 mov dword ptr [esp + 0x14], eax
004a9398 mov eax, dword ptr [esi]
004a939a mov dword ptr [esp + 0x1c], eax
004a939e lea eax, [esp + 0x20]
004a93a2 push eax
004a93a3 lea eax, [esp + 0x28]
004a93a7 mov dword ptr [esp + 0x28], 0
004a93af push eax
004a93b0 push 0
004a93b2 push 0xc02fec
004a93b7 push 0xc02fec
004a93bc lea eax, [esp + 0x28]
004a93c0 push eax
004a93c1 lea eax, [esp + 0x34]
004a93c5 push eax
004a93c6 call 0x800fb0
004a93cb mov esi, dword ptr [esp + 0x10]
004a93cf push 0
004a93d1 push dword ptr [esp + 0x20]
004a93d5 mov ecx, dword ptr [esi + 0x1c3198]
004a93db call 0x6c4b30
004a93e0 mov edi, eax
004a93e2 test edi, edi
004a93e4 je 0x4a95e4
004a93ea call dword ptr [0xa064c0]
004a93f0 mov ecx, dword ptr [edi + 0x320]
004a93f6 mov dword ptr [esp + 0x2c], eax
004a93fa lea eax, [edi + 0x320]
004a9400 mov dword ptr [edi + 0x34], 0
004a9407 mov dword ptr [edi + 0x38], 0
004a940e test ecx, ecx
004a9410 je 0x4a942c
004a9412 mov dword ptr [esp + 0x10], eax
004a9416 add ecx, 0x324
004a941c lea eax, [esp + 0x10]
004a9420 push eax
004a9421 call 0x4bc3c0
004a9426 lea eax, [edi + 0x320]
004a942c push dword ptr [esp + 0x20]
004a9430 mov dword ptr [eax], 0
004a9436 mov ecx, edi
004a9438 movss xmm0, dword ptr [0xc02fec]
004a9440 push dword ptr [esp + 0x28]
004a9444 mov eax, dword ptr [edi]
004a9446 push dword ptr [esp + 0x1c]
004a944a movss dword ptr [edi + 0x294], xmm0
004a9452 movss xmm0, dword ptr [0xc02ff0]
004a945a push dword ptr [esp + 0x28]
004a945e movss dword ptr [edi + 0x298], xmm0
004a9466 movss xmm0, dword ptr [0xc02fec]
004a946e movss dword ptr [edi + 0x2b8], xmm0
004a9476 movss xmm0, dword ptr [0xc02ff0]
004a947e movss dword ptr [edi + 0x2bc], xmm0
004a9486 call dword ptr [eax + 4]
004a9489 mov edx, dword ptr [esi + 0x18190]
004a948f push edi
004a9490 mov ecx, dword ptr [edx + 0x1214]
004a9496 lea eax, [ecx + 1]
004a9499 mov dword ptr [edx + 0x1214], eax
004a949f mov dword ptr [edi + 0x20], ecx
004a94a2 lea ecx, [edx + 0x1218]
004a94a8 call 0x413280
004a94ad push edi
004a94ae call 0x6d94d0
004a94b3 test al, al
004a94b5 je 0x4a94be
004a94b7 push ecx
004a94b8 push edi
004a94b9 call 0x6d9590
004a94be cmp byte ptr [edi + 0x16a], 0
004a94c5 je 0x4a95d4
004a94cb mov eax, dword ptr [esi + 0x283c20]
004a94d1 cmp eax, dword ptr [esi + 0x283c24]
004a94d7 je 0x4a95d4
004a94dd mov eax, dword ptr [edi + 0x28]
004a94e0 lea ecx, [esi + 0x283c48]
004a94e6 mov dword ptr [esp + 0x14], eax
004a94ea mov eax, dword ptr [edi + 0x2c]
004a94ed mov dword ptr [esp + 0x18], eax
004a94f1 lea eax, [esp + 0x14]
004a94f5 push eax
004a94f6 lea eax, [esp + 0x14]
004a94fa push eax
004a94fb call 0x937c80
004a9500 mov eax, dword ptr [esi + 0x283c48]
004a9506 cmp dword ptr [esp + 0x10], eax
004a950a jne 0x4a953e
004a950c mov eax, dword ptr [edi + 0x28]
004a950f lea ecx, [esi + 0x283c48]
004a9515 mov dword ptr [esp + 0x14], eax
004a9519 lea eax, [esp + 0x14]
004a951d push eax
004a951e lea eax, [esp + 0x14]
004a9522 mov dword ptr [esp + 0x1c], 0xffffffff
004a952a push eax
004a952b call 0x937c80
004a9530 mov ecx, dword ptr [esi + 0x283c48]
004a9536 cmp dword ptr [eax], ecx
004a9538 je 0x4a95d4
004a953e mov esi, dword ptr [0xbfd65c]
004a9544 xor ebx, ebx
004a9546 mov eax, dword ptr [esi + 0x1ba54]
004a954c sub eax, dword ptr [esi + 0x1ba50]
004a9552 sar eax, 2
004a9555 test eax, eax
004a9557 je 0x4a95d0
004a9559 nop dword ptr [eax]
004a9560 mov ecx, dword ptr [esi + 0x1ba54]
004a9566 mov eax, ecx
004a9568 sub eax, dword ptr [esi + 0x1ba50]
004a956e test eax, 0xfffffffc
004a9573 jne 0x4a958a
004a9575 push 0xb3f4d0
004a957a push 3
004a957c call 0x95e330
004a9581 mov ecx, dword ptr [esi + 0x1ba54]
004a9587 add esp, 8
004a958a mov eax, dword ptr [esi + 0x1ba50]
004a9590 sub ecx, eax
004a9592 sar ecx, 2
004a9595 cmp ebx, ecx
004a9597 jae 0x4a959c
004a9599 lea eax, [eax + ebx*4]
004a959c mov ecx, dword ptr [eax]
004a959e push 0xc02fec
004a95a3 push 0xc02fec
004a95a8 push edi
004a95a9 push 6
004a95ab add ecx, 0x1ec0
004a95b1 call 0x935fd0
004a95b6 mov esi, dword ptr [0xbfd65c]
004a95bc inc ebx
004a95bd mov eax, dword ptr [esi + 0x1ba54]
004a95c3 sub eax, dword ptr [esi + 0x1ba50]
004a95c9 sar eax, 2
004a95cc cmp ebx, eax
004a95ce jb 0x4a9560
004a95d0 mov ebx, dword ptr [esp + 0x28]
004a95d4 call dword ptr [0xa064c0]
004a95da sub eax, dword ptr [esp + 0x2c]
004a95de add dword ptr [0xbffe0c], eax
004a95e4 mov eax, dword ptr [edi + 0x164]
004a95ea mov ecx, edi
004a95ec mov esi, dword ptr [esp + 0x30]
004a95f0 and dword ptr [edi + 0x160], 0xfffffffb
004a95f7 mov dword ptr [edi + 0x164], eax
004a95fd lea eax, [esp + 0x34]
004a9601 push eax
004a9602 lea eax, [esi + 0x28c]
004a9608 mov dword ptr [edi + 0x34], 0x38a
004a960f push eax
004a9610 call 0x68eff0
004a9615 push edi
004a9616 mov ecx, esi
004a9618 call 0x4a8710
004a961d call 0x6c3d90
004a9622 xor edx, edx
004a9624 mov ecx, 0xd2
004a9629 div ecx
004a962b mov eax, dword ptr [0xbfd65c]
004a9630 mov eax, dword ptr [eax + 0x18190]
004a9636 lea esi, [edx + 0x96]
004a963c mov ecx, dword ptr [eax + 0x10]
004a963f imul ecx, dword ptr [eax + 0xc]
004a9643 mov eax, esi
004a9645 cdq
004a9646 sub eax, edx
004a9648 mov byte ptr [ebx + 0x16b], 0
004a964f sar eax, 1
004a9651 cmp ecx, 0x87
004a9657 cmovle eax, esi
004a965a mov dword ptr [ebx + 0x3ac], eax
004a9660 mov dword ptr [ebx + 0x3b0], eax
004a9666 mov ecx, dword ptr [esp + 0x74]
004a966a pop edi
004a966b pop esi
004a966c pop ebx
004a966d xor ecx, esp
004a966f call 0x9eacd7
004a9674 mov esp, ebp
004a9676 pop ebp
004a9677 ret
