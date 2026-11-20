00640070 push ebp
00640071 mov ebp, esp
00640073 and esp, 0xfffffff8
00640076 sub esp, 0x74
00640079 push ebx
0064007a mov ebx, ecx
0064007c push esi
0064007d push edi
0064007e mov dword ptr [esp + 0x1c], ebx
00640082 mov ecx, dword ptr [ebx + 0x2c]
00640085 cmp ecx, 0xe
00640088 jne 0x6400c3
0064008a cmp dword ptr [ebx + 0x360], 1
00640091 jne 0x6400b8
00640093 push 0
00640095 mov eax, 0x1e
0064009a mov dword ptr [ebx + 0x360], 2
006400a4 push 0xb4688c
006400a9 lea ecx, [ebx + 0x3c]
006400ac mov word ptr [ebx + 0x36a], ax
006400b3 call 0x4054f0
006400b8 xor al, al
006400ba pop edi
006400bb pop esi
006400bc pop ebx
006400bd mov esp, ebp
006400bf pop ebp
006400c0 ret 0x14
006400c3 mov edx, dword ptr [ebp + 0xc]
006400c6 mov eax, edx
006400c8 and eax, 4
006400cb or eax, 0
006400ce je 0x6400b8
006400d0 cmp ecx, 8
006400d3 jne 0x640586
006400d9 cmp dword ptr [ebx + 0x360], 3
006400e0 je 0x64087e
006400e6 push 0
006400e8 push 0xb408f8
006400ed lea ecx, [ebx + 0x3c]
006400f0 call 0x4054f0
006400f5 mov eax, dword ptr [0xbfd680]
006400fa lea edi, [ebx + 0x334]
00640100 mov dword ptr [ebx + 0x360], 3
0064010a mov ecx, edi
0064010c push 9
0064010e mov dword ptr [esp + 0x44], edi
00640112 mov esi, dword ptr [eax + 0x31c]
00640118 mov eax, 0x10624dd3
0064011d mul esi
0064011f shr edx, 6
00640122 imul eax, edx, 0x3e8
00640128 sub esi, eax
0064012a call 0x7a7d50
0064012f mov ecx, dword ptr [0xbfd680]
00640135 add eax, 7
00640138 cmp eax, esi
0064013a cmovle esi, eax
0064013d mov eax, esi
0064013f lea ecx, [ecx + 0x14]
00640142 neg eax
00640144 push eax
00640145 push 0x14
00640147 call 0x884e40
0064014c dec esi
0064014d mov dword ptr [esp + 0x2c], esi
00640151 test esi, esi
00640153 jle 0x64055f
00640159 lea eax, [ebx + 0x294]
0064015f mov dword ptr [esp + 0x28], eax
00640163 xor ebx, ebx
00640165 mov edx, dword ptr [edi]
00640167 test edx, edx
00640169 jne 0x640181
0064016b push 0xb4d6c4
00640170 push 3
00640172 call 0x95e330
00640177 mov edx, dword ptr [edi]
00640179 add esp, 8
0064017c test edx, edx
0064017e jne 0x640181
00640180 int3
00640181 mov ecx, dword ptr [edi + 4]
00640184 mov eax, edx
00640186 movq xmm0, qword ptr [0xa08b78]
0064018e shr eax, cl
00640190 mov ecx, dword ptr [edi + 8]
00640193 xor eax, edx
00640195 mov edx, eax
00640197 movq qword ptr [esp + 0x74], xmm0
0064019d shl edx, cl
0064019f mov ecx, dword ptr [edi + 0xc]
006401a2 xor edx, eax
006401a4 mov eax, edx
006401a6 shr eax, cl
006401a8 mov ecx, dword ptr [0xa08b80]
006401ae mov esi, eax
006401b0 xor esi, edx
006401b2 mov dword ptr [esp + 0x20], ecx
006401b6 mov dword ptr [edi], esi
006401b8 mov dword ptr [esp + 0x7c], ecx
006401bc cmp eax, edx
006401be jne 0x6401d0
006401c0 push 0xb4d6c4
006401c5 push 3
006401c7 call 0x95e330
006401cc add esp, 8
006401cf int3
006401d0 mov ecx, dword ptr [esp + 0x74]
006401d4 mov edx, esi
006401d6 shr edx, cl
006401d8 mov ecx, dword ptr [esp + 0x78]
006401dc xor edx, esi
006401de mov eax, edx
006401e0 shl eax, cl
006401e2 mov ecx, dword ptr [esp + 0x20]
006401e6 xor eax, edx
006401e8 mov edx, eax
006401ea shr edx, cl
006401ec xor edx, eax
006401ee movd xmm0, edx
006401f2 cvtdq2pd xmm0, xmm0
006401f6 shr edx, 0x1f
006401f9 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
00640202 cvtpd2ps xmm0, xmm0
00640206 mulss xmm0, dword ptr [0xb6a198]
0064020e mulss xmm0, dword ptr [0xb6a874]
00640216 addss xmm0, xmm0
0064021a movss dword ptr [esp + 0x20], xmm0
00640220 call 0x411fe0
00640225 mulss xmm0, dword ptr [0xb6a8f4]
0064022d movss dword ptr [esp + 0x14], xmm0
00640233 movss dword ptr [esp + 0x50], xmm0
00640239 movss xmm0, dword ptr [esp + 0x20]
0064023f call 0x412010
00640244 mulss xmm0, dword ptr [0xb6a8f4]
0064024c lea eax, [esp + 0x58]
00640250 mov esi, dword ptr [esp + 0x28]
00640254 movss xmm1, dword ptr [esp + 0x14]
0064025a mulss xmm1, dword ptr [0xb6a928]
00640262 mov ecx, dword ptr [0xbfd65c]
00640268 mulss xmm0, dword ptr [0xb6a350]
00640270 push 0
00640272 addss xmm1, dword ptr [esi]
00640276 mov ecx, dword ptr [ecx + 0x18190]
0064027c addss xmm0, dword ptr [0xb6a864]
00640284 push 0
00640286 push 0
00640288 push 0
0064028a push 1
0064028c movss dword ptr [esp + 0x48], xmm0
00640292 movss dword ptr [esp + 0x68], xmm0
00640298 mulss xmm0, dword ptr [0xb6a928]
006402a0 push eax
006402a1 push esi
006402a2 movss dword ptr [esp + 0x74], xmm1
006402a8 addss xmm0, dword ptr [esi + 4]
006402ad movss dword ptr [esp + 0x78], xmm0
006402b3 call 0x7af4b0
006402b8 test al, al
006402ba jne 0x6402c6
006402bc inc ebx
006402bd cmp ebx, 0xa
006402c0 jl 0x640165
006402c6 mov edx, dword ptr [edi]
006402c8 test edx, edx
006402ca jne 0x6402e2
006402cc push 0xb4d6c4
006402d1 push 3
006402d3 call 0x95e330
006402d8 mov edx, dword ptr [edi]
006402da add esp, 8
006402dd test edx, edx
006402df jne 0x6402e2
006402e1 int3
006402e2 mov ecx, dword ptr [edi + 4]
006402e5 mov eax, edx
006402e7 shr eax, cl
006402e9 mov ecx, dword ptr [edi + 8]
006402ec xor eax, edx
006402ee mov edx, eax
006402f0 mov ebx, dword ptr [0xbfd65c]
006402f6 shl edx, cl
006402f8 mov ecx, dword ptr [edi + 0xc]
006402fb xor edx, eax
006402fd mov eax, edx
006402ff mov dword ptr [esp + 0x38], ebx
00640303 shr eax, cl
00640305 xor eax, edx
00640307 mov dword ptr [esp + 0x1c], 1
0064030f mov dword ptr [edi], eax
00640311 mov dword ptr [esp + 0x18], eax
00640315 lea eax, [esp + 0x18]
00640319 push eax
0064031a lea eax, [esp + 0x20]
0064031e mov dword ptr [esp + 0x24], 0x14
00640326 push eax
00640327 push 0
00640329 lea eax, [esp + 0x5c]
0064032d mov dword ptr [esp + 0x1c], 5
00640335 push eax
00640336 push esi
00640337 lea eax, [esp + 0x34]
0064033b push eax
0064033c lea eax, [esp + 0x28]
00640340 push eax
00640341 call 0x800fb0
00640346 mov ecx, dword ptr [ebx + 0x1c3198]
0064034c push 0
0064034e push dword ptr [esp + 0x14]
00640352 call 0x6c4b30
00640357 mov ebx, eax
00640359 mov dword ptr [esp + 0x3c], ebx
0064035d test ebx, ebx
0064035f je 0x640554
00640365 call dword ptr [0xa064c0]
0064036b mov ecx, dword ptr [ebx + 0x320]
00640371 mov dword ptr [esp + 0x44], eax
00640375 lea eax, [ebx + 0x320]
0064037b mov dword ptr [ebx + 0x34], 0
00640382 mov dword ptr [ebx + 0x38], 0
00640389 test ecx, ecx
0064038b je 0x6403a7
0064038d mov dword ptr [esp + 0x30], eax
00640391 add ecx, 0x324
00640397 lea eax, [esp + 0x30]
0064039b push eax
0064039c call 0x4bc3c0
006403a1 lea eax, [ebx + 0x320]
006403a7 push dword ptr [esp + 0x18]
006403ab movss xmm0, dword ptr [esp + 0x18]
006403b1 mov ecx, ebx
006403b3 push dword ptr [esp + 0x20]
006403b7 mov dword ptr [eax], 0
006403bd mov eax, dword ptr [esi]
006403bf push dword ptr [esp + 0x28]
006403c3 mov dword ptr [ebx + 0x294], eax
006403c9 mov eax, dword ptr [esi + 4]
006403cc push dword ptr [esp + 0x1c]
006403d0 mov dword ptr [ebx + 0x298], eax
006403d6 mov eax, dword ptr [ebx]
006403d8 movss dword ptr [ebx + 0x2b8], xmm0
006403e0 movss xmm0, dword ptr [esp + 0x44]
006403e6 movss dword ptr [ebx + 0x2bc], xmm0
006403ee call dword ptr [eax + 4]
006403f1 mov esi, dword ptr [esp + 0x38]
006403f5 push ebx
006403f6 mov edx, dword ptr [esi + 0x18190]
006403fc mov ecx, dword ptr [edx + 0x1214]
00640402 lea eax, [ecx + 1]
00640405 mov dword ptr [edx + 0x1214], eax
0064040b mov dword ptr [ebx + 0x20], ecx
0064040e lea ecx, [edx + 0x1218]
00640414 call 0x413280
00640419 push ebx
0064041a call 0x6d94d0
0064041f test al, al
00640421 je 0x64042a
00640423 push ecx
00640424 push ebx
00640425 call 0x6d9590
0064042a cmp byte ptr [ebx + 0x16a], 0
00640431 je 0x640544
00640437 mov eax, dword ptr [esi + 0x283c20]
0064043d cmp eax, dword ptr [esi + 0x283c24]
00640443 je 0x640544
00640449 mov eax, dword ptr [ebx + 0x2c]
0064044c mov ecx, dword ptr [ebx + 0x28]
0064044f mov dword ptr [esp + 0x64], eax
00640453 lea eax, [esp + 0x60]
00640457 push eax
00640458 lea eax, [esp + 0x28]
0064045c mov dword ptr [esp + 0x64], ecx
00640460 push eax
00640461 lea ecx, [esi + 0x283c48]
00640467 call 0x937c80
0064046c mov eax, dword ptr [esp + 0x24]
00640470 cmp eax, dword ptr [esi + 0x283c48]
00640476 jne 0x6404ae
00640478 mov eax, dword ptr [ebx + 0x28]
0064047b lea ecx, [esi + 0x283c48]
00640481 mov dword ptr [esp + 0x68], eax
00640485 lea eax, [esp + 0x68]
00640489 push eax
0064048a lea eax, [esp + 0x4c]
0064048e mov dword ptr [esp + 0x70], 0xffffffff
00640496 push eax
00640497 call 0x937c80
0064049c mov eax, dword ptr [eax]
0064049e mov dword ptr [esp + 0x24], eax
006404a2 cmp eax, dword ptr [esi + 0x283c48]
006404a8 je 0x640544
006404ae mov esi, dword ptr [0xbfd65c]
006404b4 xor ebx, ebx
006404b6 mov eax, dword ptr [esi + 0x1ba54]
006404bc sub eax, dword ptr [esi + 0x1ba50]
006404c2 sar eax, 2
006404c5 test eax, eax
006404c7 je 0x640544
006404cd mov edi, dword ptr [esp + 0x3c]
006404d1 mov ecx, dword ptr [esi + 0x1ba54]
006404d7 mov eax, ecx
006404d9 sub eax, dword ptr [esi + 0x1ba50]
006404df test eax, 0xfffffffc
006404e4 jne 0x6404fb
006404e6 push 0xb3f4d0
006404eb push 3
006404ed call 0x95e330
006404f2 mov ecx, dword ptr [esi + 0x1ba54]
006404f8 add esp, 8
006404fb mov eax, dword ptr [esi + 0x1ba50]
00640501 sub ecx, eax
00640503 sar ecx, 2
00640506 cmp ebx, ecx
00640508 jae 0x64050d
0064050a lea eax, [eax + ebx*4]
0064050d lea ecx, [esp + 0x50]
00640511 push ecx
00640512 push dword ptr [esp + 0x2c]
00640516 mov ecx, dword ptr [eax]
00640518 push edi
00640519 push 6
0064051b add ecx, 0x1ec0
00640521 call 0x935fd0
00640526 mov esi, dword ptr [0xbfd65c]
0064052c inc ebx
0064052d mov eax, dword ptr [esi + 0x1ba54]
00640533 sub eax, dword ptr [esi + 0x1ba50]
00640539 sar eax, 2
0064053c cmp ebx, eax
0064053e jb 0x6404d1
00640540 mov edi, dword ptr [esp + 0x40]
00640544 call dword ptr [0xa064c0]
0064054a sub eax, dword ptr [esp + 0x44]
0064054e add dword ptr [0xbffe0c], eax
00640554 sub dword ptr [esp + 0x2c], 1
00640559 jne 0x640163
0064055f mov ecx, dword ptr [0xbfd65c]
00640565 mov eax, dword ptr [ecx + 0x1c316c]
0064056b or dword ptr [ecx + 0x1c3168], 0x40020000
00640575 mov dword ptr [ecx + 0x1c316c], eax
0064057b xor al, al
0064057d pop edi
0064057e pop esi
0064057f pop ebx
00640580 mov esp, ebp
00640582 pop ebp
00640583 ret 0x14
