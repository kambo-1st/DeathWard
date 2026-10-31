004e82e0 push ebx
004e82e1 mov ebx, esp
004e82e3 sub esp, 8
004e82e6 and esp, 0xfffffff8
004e82e9 add esp, 4
004e82ec push ebp
004e82ed mov ebp, dword ptr [ebx + 4]
004e82f0 mov dword ptr [esp + 4], ebp
004e82f4 mov ebp, esp
004e82f6 push -1
004e82f8 push 0x9ef065
004e82fd mov eax, dword ptr fs:[0]
004e8303 push eax
004e8304 push ebx
004e8305 sub esp, 0x128
004e830b mov eax, dword ptr [0xbaa3b4]
004e8310 xor eax, ebp
004e8312 mov dword ptr [ebp - 0x14], eax
004e8315 push esi
004e8316 push edi
004e8317 push eax
004e8318 lea eax, [ebp - 0xc]
004e831b mov dword ptr fs:[0], eax
004e8321 mov edi, ecx
004e8323 mov eax, dword ptr [0xbfd65c]
004e8328 movq xmm0, qword ptr [0xa08c44]
004e8330 movq qword ptr [ebp - 0x130], xmm0
004e8338 mov eax, dword ptr [eax + 0x18190]
004e833e mov dword ptr [ebp - 0x114], eax
004e8344 mov eax, dword ptr [edi + 0x344]
004e834a add eax, dword ptr [edi + 0x20]
004e834d mov dword ptr [ebp - 0x134], eax
004e8353 mov eax, dword ptr [0xa08c4c]
004e8358 mov dword ptr [ebp - 0x128], eax
004e835e mov eax, dword ptr [edi + 0xab4]
004e8364 cmp eax, 0x10
004e8367 ja 0x4e9349
004e836d movzx eax, byte ptr [eax + 0x4e9488]
004e8374 jmp dword ptr [eax*4 + 0x4e9474]
004e837b push 1
004e837d push 0xb404ec
004e8382 lea ecx, [edi + 0x3c]
004e8385 mov dword ptr [edi + 0xab4], 3
004e838f mov dword ptr [edi + 0xb10], 0
004e8399 mov dword ptr [edi + 0xb00], 0
004e83a3 mov dword ptr [edi + 0x360], 0
004e83ad call 0x405740
004e83b2 test al, al
004e83b4 je 0x4e83d6
004e83b6 mov eax, dword ptr [edi + 0x70]
004e83b9 test eax, eax
004e83bb je 0x4e83d6
004e83bd lea ecx, [edi + 0x6c]
004e83c0 xorps xmm1, xmm1
004e83c3 call 0x403c00
004e83c8 mov eax, dword ptr [edi + 0x70]
004e83cb test eax, eax
004e83cd je 0x4e83d6
004e83cf mov byte ptr [edi + 0x80], 0
004e83d6 push 1
004e83d8 push 0xb41e78
004e83dd lea ecx, [edi + 0x3c]
004e83e0 call 0x405bb0
004e83e5 test al, al
004e83e7 je 0x4e9349
004e83ed cmp dword ptr [edi + 0x90], 0
004e83f4 je 0x4e9349
004e83fa lea ecx, [edi + 0x8c]
004e8400 xorps xmm1, xmm1
004e8403 call 0x403c00
004e8408 jmp 0x4e9349
004e840d mov eax, dword ptr [0xb404ec]
004e8412 mov ecx, dword ptr [0xb404f0]
004e8418 mov dword ptr [ebp - 0x30], 0xf
004e841f mov dword ptr [ebp - 0x34], 8
004e8426 mov dword ptr [ebp - 0x44], eax
004e8429 mov dword ptr [ebp - 0x40], ecx
004e842c mov byte ptr [ebp - 0x3c], 0
004e8430 mov dword ptr [ebp - 4], 0
004e8437 mov eax, dword ptr [0xb40504]
004e843c mov ecx, dword ptr [0xb40508]
004e8442 mov dword ptr [ebp - 0x18], 0xf
004e8449 mov dword ptr [ebp - 0x1c], 8
004e8450 mov dword ptr [ebp - 0x2c], eax
004e8453 mov dword ptr [ebp - 0x28], ecx
004e8456 mov byte ptr [ebp - 0x24], 0
004e845a push ecx
004e845b mov byte ptr [ebp - 4], 1
004e845f lea eax, [ebp - 0x44]
004e8462 mov dword ptr [esp], 0x3dcccccd
004e8469 mov ecx, edi
004e846b push eax
004e846c lea eax, [ebp - 0x2c]
004e846f push eax
004e8470 call 0x6980a0
004e8475 mov byte ptr [ebp - 4], 0
004e8479 mov edx, dword ptr [ebp - 0x18]
004e847c cmp edx, 0x10
004e847f jb 0x4e84a9
004e8481 mov ecx, dword ptr [ebp - 0x2c]
004e8484 inc edx
004e8485 mov eax, ecx
004e8487 cmp edx, 0x1000
004e848d jb 0x4e849f
004e848f mov ecx, dword ptr [ecx - 4]
004e8492 add edx, 0x23
004e8495 sub eax, ecx
004e8497 add eax, -4
004e849a cmp eax, 0x1f
004e849d ja 0x4e84e8
004e849f push edx
004e84a0 push ecx
004e84a1 call 0x9eb08e
004e84a6 add esp, 8
004e84a9 mov dword ptr [ebp - 4], 0xffffffff
004e84b0 mov edx, dword ptr [ebp - 0x30]
004e84b3 mov dword ptr [ebp - 0x1c], 0
004e84ba mov dword ptr [ebp - 0x18], 0xf
004e84c1 mov byte ptr [ebp - 0x2c], 0
004e84c5 cmp edx, 0x10
004e84c8 jb 0x4e84f8
004e84ca mov ecx, dword ptr [ebp - 0x44]
004e84cd inc edx
004e84ce mov eax, ecx
004e84d0 cmp edx, 0x1000
004e84d6 jb 0x4e84ee
004e84d8 mov ecx, dword ptr [ecx - 4]
004e84db add edx, 0x23
004e84de sub eax, ecx
004e84e0 add eax, -4
004e84e3 cmp eax, 0x1f
004e84e6 jbe 0x4e84ee
004e84e8 call dword ptr [0xa065ac]
004e84ee push edx
004e84ef push ecx
004e84f0 call 0x9eb08e
004e84f5 add esp, 8
004e84f8 cmp dword ptr [edi + 0xab4], 8
004e84ff jne 0x4e886e
004e8505 push 0
004e8507 mov ecx, edi
004e8509 call 0x6afe20
004e850e push 0xb400ac
004e8513 lea ecx, [edi + 0x8c]
004e8519 call 0x405e90
004e851e test al, al
004e8520 je 0x4e8841
004e8526 cmp dword ptr [edi + 0x28], 0x340
004e852d lea esi, [edi + 0x294]
004e8533 jne 0x4e86fd
004e8539 mov ecx, edi
004e853b call 0x695680
004e8540 lea ecx, [ebp - 0x108]
004e8546 movss xmm0, dword ptr [eax + 0x294]
004e854e movss xmm1, dword ptr [eax + 0x298]
004e8556 lea eax, [ebp - 0x11c]
004e855c subss xmm0, dword ptr [esi]
004e8560 subss xmm1, dword ptr [esi + 4]
004e8565 push eax
004e8566 movss dword ptr [ebp - 0x108], xmm0
004e856e movss dword ptr [ebp - 0x104], xmm1
004e8576 call 0x962560
004e857b lea ecx, [edi + 0xe70]
004e8581 push 0xc02fec
004e8586 call 0x962ca0
004e858b test al, al
004e858d je 0x4e85a6
004e858f lea eax, [ebp - 0x124]
004e8595 push eax
004e8596 call 0x962560
004e859b movss xmm4, dword ptr [eax]
004e859f movss xmm5, dword ptr [eax + 4]
004e85a4 jmp 0x4e85b6
004e85a6 movss xmm5, dword ptr [ebp - 0x118]
004e85ae movss xmm4, dword ptr [ebp - 0x11c]
004e85b6 lea ecx, [ebp - 0x100]
004e85bc call 0x430d70
004e85c1 movss xmm3, dword ptr [0xb6a480]
004e85c9 lea ecx, [ebp - 0x58]
004e85cc mov eax, dword ptr [ebp - 0xa4]
004e85d2 xorps xmm2, xmm2
004e85d5 or dword ptr [ebp - 0xa8], 0x2800
004e85df movaps xmm1, xmm3
004e85e2 mov dword ptr [ebp - 0xa4], eax
004e85e8 call 0x427080
004e85ed push eax
004e85ee lea ecx, [ebp - 0xd4]
004e85f4 call 0x4021a0
004e85f9 movss xmm0, dword ptr [edi + 0x294]
004e8601 lea eax, [ebp - 0x100]
004e8607 mulss xmm4, dword ptr [0xb6a928]
004e860f lea esi, [edi + 0x294]
004e8615 mov ecx, edi
004e8617 mov byte ptr [ebp - 0x100], 0
004e861e mulss xmm5, dword ptr [0xb6a928]
004e8626 push eax
004e8627 push 0
004e8629 lea eax, [ebp - 0x110]
004e862f movss dword ptr [ebp - 0x98], xmm0
004e8637 movss xmm0, dword ptr [esi + 4]
004e863c push eax
004e863d push esi
004e863e movss dword ptr [ebp - 0x94], xmm0
004e8646 movss dword ptr [ebp - 0x110], xmm4
004e864e movss dword ptr [ebp - 0x10c], xmm5
004e8656 call 0x6a1a20
004e865b movss xmm0, dword ptr [ebp - 0x110]
004e8663 lea eax, [ebp - 0x100]
004e8669 xorps xmm0, xmmword ptr [0xb6c9b0]
004e8670 mov ecx, edi
004e8672 push eax
004e8673 movss dword ptr [ebp - 0x108], xmm0
004e867b lea eax, [ebp - 0x108]
004e8681 movss xmm0, dword ptr [ebp - 0x10c]
004e8689 xorps xmm0, xmmword ptr [0xb6c9b0]
004e8690 push 0
004e8692 push eax
004e8693 push esi
004e8694 movss dword ptr [ebp - 0x104], xmm0
004e869c call 0x6a1a20
004e86a1 call 0x6c3d90
004e86a6 mov ecx, dword ptr [0xbfd65c]
004e86ac push eax
004e86ad push 0
004e86af push 0
004e86b1 push 0xc02fec
004e86b6 push esi
004e86b7 push 0xb
004e86b9 push 0x3e8
004e86be call 0x422e20
004e86c3 push 1
004e86c5 push 0
004e86c7 push 0xff
004e86cc mov edx, dword ptr [eax]
004e86ce mov ecx, eax
004e86d0 push -1
004e86d2 push 0xbc51fc
004e86d7 mov dword ptr [eax + 0xd0], 0
004e86e1 mov dword ptr [eax + 0xd4], 0xc1600000
004e86eb mov dword ptr [eax + 0x2b0], 0x40800000
004e86f5 call dword ptr [edx + 0x38]
004e86f8 jmp 0x4e8801
004e86fd cmp dword ptr [edi + 0x2c], 1
004e8701 lea ecx, [ebp - 0x100]
004e8707 jne 0x4e8786
004e8709 call 0x430d70
004e870e lea eax, [ebp - 0x100]
004e8714 mov dword ptr [ebp - 0xe8], 0
004e871e push eax
004e871f push 9
004e8721 lea eax, [ebp - 0x110]
004e8727 mov dword ptr [ebp - 0xec], 0x3fa66666
004e8731 push eax
004e8732 push esi
004e8733 mov ecx, edi
004e8735 mov dword ptr [ebp - 0xf4], 0xbd75c28f
004e873f mov dword ptr [ebp - 0x110], 0x41000000
004e8749 mov dword ptr [ebp - 0x10c], 0x40c00000
004e8753 call 0x6a1a20
004e8758 call 0x6c3d90
004e875d mov ecx, dword ptr [0xbfd65c]
004e8763 push eax
004e8764 push 0
004e8766 push 0
004e8768 push 0xc02fec
004e876d push esi
004e876e push 0xb
004e8770 push 0x3e8
004e8775 call 0x422e20
004e877a mov dword ptr [eax + 0xd4], 0xc1800000
004e8784 jmp 0x4e87ed
004e8786 call 0x430d70
004e878b lea eax, [ebp - 0x100]
004e8791 mov dword ptr [ebp - 0xe8], 0
004e879b push eax
004e879c push 9
004e879e lea eax, [ebp - 0x110]
004e87a4 mov dword ptr [ebp - 0x110], 0x40e00000
004e87ae push eax
004e87af push esi
004e87b0 mov ecx, edi
004e87b2 mov dword ptr [ebp - 0x10c], 0x40c00000
004e87bc call 0x6a1a20
004e87c1 call 0x6c3d90
004e87c6 mov ecx, dword ptr [0xbfd65c]
004e87cc push eax
004e87cd push 0
004e87cf push 0
004e87d1 push 0xc02fec
004e87d6 push esi
004e87d7 push 0xb
004e87d9 push 0x3e8
004e87de call 0x422e20
004e87e3 mov dword ptr [eax + 0xd4], 0xc1600000
004e87ed mov dword ptr [eax + 0x2b0], 0x40800000
004e87f7 mov dword ptr [eax + 0xd0], 0
004e8801 push ecx
004e8802 mov dword ptr [esp], 0x3f800000
004e8809 push 0
004e880b push 2
004e880d push ecx
004e880e mov dword ptr [esp], 0x3f800000
004e8815 mov ecx, edi
004e8817 push 0xb2
004e881c call 0x6ad720
004e8821 movss xmm0, dword ptr [edi + 0xb00]
004e8829 subss xmm0, dword ptr [0xb6a928]
004e8831 maxss xmm0, dword ptr [0xb6a18c]
004e8839 movss dword ptr [edi + 0xb00], xmm0
004e8841 cmp dword ptr [edi + 0x90], 0
004e8848 lea ecx, [edi + 0x3c]
004e884b je 0x4e8856
004e884d cmp byte ptr [edi + 0xa0], 0
004e8854 jne 0x4e8888
004e8856 push 0
004e8858 push 0xb41e78
004e885d call 0x405cb0
004e8862 mov dword ptr [edi + 0xab4], 3
004e886c jmp 0x4e8888
004e886e cmp dword ptr [edi + 0x90], 0
004e8875 je 0x4e8888
004e8877 lea ecx, [edi + 0x3c]
004e887a call 0x4058f0
004e887f push eax
004e8880 lea ecx, [edi + 0x3c]
004e8883 call 0x405cf0
004e8888 cmp dword ptr [edi + 0x360], 0
004e888f jne 0x4e89ba
004e8895 cmp dword ptr [edi + 0xe6c], -1
004e889c jne 0x4e89b0
004e88a2 movss xmm0, dword ptr [edi + 0x2dc]
004e88aa comiss xmm0, dword ptr [edi + 0x2d8]
004e88b1 ja 0x4e89b0
004e88b7 mov eax, dword ptr [ebp - 0x114]
004e88bd mov dword ptr [ebp - 0x118], 0
004e88c7 cmp dword ptr [eax + 0x1264], 0
004e88ce jbe 0x4e89ba
004e88d4 mov ecx, dword ptr [eax + 0x125c]
004e88da mov dword ptr [ebp - 0x104], ecx
004e88e0 mov esi, dword ptr [ecx]
004e88e2 mov ecx, edi
004e88e4 push esi
004e88e5 call 0x695620
004e88ea test al, al
004e88ec je 0x4e8930
004e88ee movss xmm1, dword ptr [esi + 0x294]
004e88f6 movss xmm0, dword ptr [esi + 0x298]
004e88fe subss xmm0, dword ptr [edi + 0x298]
004e8906 subss xmm1, dword ptr [edi + 0x294]
004e890e mulss xmm0, xmm0
004e8912 mulss xmm1, xmm1
004e8916 addss xmm0, xmm1
004e891a call 0x4228c0
004e891f movss xmm1, dword ptr [0xb6aad4]
004e8927 comiss xmm1, xmm0
004e892a ja 0x4e89b0
004e8930 cmp dword ptr [esi + 0x28], 0x33b
004e8937 jne 0x4e8980
004e8939 cmp dword ptr [esi + 0x360], 0
004e8940 je 0x4e8980
004e8942 movss xmm1, dword ptr [esi + 0x294]
004e894a movss xmm0, dword ptr [esi + 0x298]
004e8952 subss xmm0, dword ptr [edi + 0x298]
004e895a subss xmm1, dword ptr [edi + 0x294]
004e8962 mulss xmm0, xmm0
004e8966 mulss xmm1, xmm1
004e896a addss xmm0, xmm1
004e896e call 0x4228c0
004e8973 movss xmm1, dword ptr [0xb6aad4]
004e897b comiss xmm1, xmm0
004e897e ja 0x4e89b0
004e8980 mov eax, dword ptr [ebp - 0x118]
004e8986 mov edx, dword ptr [ebp - 0x114]
004e898c inc eax
004e898d mov ecx, dword ptr [ebp - 0x104]
004e8993 add ecx, 4
004e8996 mov dword ptr [ebp - 0x118], eax
004e899c mov dword ptr [ebp - 0x104], ecx
004e89a2 cmp eax, dword ptr [edx + 0x1264]
004e89a8 jb 0x4e88e0
004e89ae jmp 0x4e89ba
004e89b0 mov dword ptr [edi + 0x360], 1
004e89ba call 0x6c3d90
004e89bf xor edx, edx
004e89c1 mov ecx, 6
004e89c6 div ecx
004e89c8 test edx, edx
004e89ca jne 0x4e8a0e
004e89cc call 0x6c3d90
004e89d1 push ecx
004e89d2 mov ecx, edi
004e89d4 movd xmm0, eax
004e89d8 cvtdq2pd xmm0, xmm0
004e89dc shr eax, 0x1f
004e89df addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e89e8 cvtpd2ps xmm0, xmm0
004e89ec mulss xmm0, dword ptr [0xb6a19c]
004e89f4 mulss xmm0, dword ptr [0xb6a480]
004e89fc addss xmm0, dword ptr [0xb6a350]
004e8a04 movss dword ptr [esp], xmm0
004e8a09 call 0x68d7b0
004e8a0e mov eax, dword ptr [edi + 0x160]
004e8a14 and eax, 0x1000800
004e8a19 or eax, 0
004e8a1c je 0x4e8a5c
004e8a1e cmp dword ptr [edi + 0xe6c], -1
004e8a25 jne 0x4e8a5c
004e8a27 mov ecx, edi
004e8a29 call 0x695680
004e8a2e push 0
004e8a30 mov ecx, dword ptr [eax + 0x294]
004e8a36 mov eax, dword ptr [eax + 0x298]
004e8a3c mov dword ptr [ebp - 0x10c], eax
004e8a42 lea eax, [ebp - 0x110]
004e8a48 mov dword ptr [ebp - 0x110], ecx
004e8a4e lea ecx, [edi + 0x364]
004e8a54 push eax
004e8a55 call 0x7a4830
004e8a5a jmp 0x4e8a72
004e8a5c cmp dword ptr [edi + 0x360], 0
004e8a63 jne 0x4e8a8f
004e8a65 push 0
004e8a67 lea ecx, [edi + 0x364]
004e8a6d call 0x7a6180
004e8a72 movss xmm0, dword ptr [edi + 0x2c4]
004e8a7a mulss xmm0, dword ptr [0xb6a560]
004e8a82 movss dword ptr [edi + 0x2c4], xmm0
004e8a8a jmp 0x4e8d5b
004e8a8f cmp dword ptr [edi + 0x28], 0x340
004e8a96 jne 0x4e8d28
004e8a9c cmp dword ptr [edi + 0xe6c], -1
004e8aa3 jne 0x4e8d28
004e8aa9 push ecx
004e8aaa lea eax, [ebp - 0x110]
004e8ab0 mov dword ptr [esp], 0
004e8ab7 push eax
004e8ab8 mov ecx, edi
004e8aba call 0x695a30
004e8abf mov ecx, edi
004e8ac1 call 0x695680
004e8ac6 push dword ptr [edi + 0x20]
004e8ac9 mov ecx, edi
004e8acb mov esi, eax
004e8acd push 0x1e
004e8acf call 0x684790
004e8ad4 test al, al
004e8ad6 je 0x4e8af8
004e8ad8 movss xmm0, dword ptr [esi + 0x2b8]
004e8ae0 movss xmm1, dword ptr [esi + 0x2bc]
004e8ae8 movss dword ptr [edi + 0xb08], xmm0
004e8af0 movss dword ptr [edi + 0xb0c], xmm1
004e8af8 push 0
004e8afa push 0
004e8afc push 0
004e8afe push 0
004e8b00 push 0
004e8b02 lea ecx, [ebp - 0x110]
004e8b08 push ecx
004e8b09 mov ecx, dword ptr [ebp - 0x114]
004e8b0f lea eax, [edi + 0x294]
004e8b15 push eax
004e8b16 call 0x7af4b0
004e8b1b test al, al
004e8b1d je 0x4e8d11
004e8b23 movss xmm1, dword ptr [ebp - 0x110]
004e8b2b movss xmm0, dword ptr [ebp - 0x10c]
004e8b33 subss xmm0, dword ptr [edi + 0x298]
004e8b3b subss xmm1, dword ptr [edi + 0x294]
004e8b43 mov eax, dword ptr [0xbfd65c]
004e8b48 mov dword ptr [ebp - 0x104], 0
004e8b52 mulss xmm0, xmm0
004e8b56 mov esi, dword ptr [eax + 0x1a30dc]
004e8b5c sub esi, dword ptr [edi + 0x280]
004e8b62 mulss xmm1, xmm1
004e8b66 addss xmm0, xmm1
004e8b6a call 0x4228c0
004e8b6f mulss xmm0, dword ptr [0xb6a480]
004e8b77 lea eax, [ebp - 0x104]
004e8b7d lea ecx, [ebp - 0x118]
004e8b83 xorps xmm1, xmm1
004e8b86 comiss xmm1, xmm0
004e8b89 movss dword ptr [ebp - 0x118], xmm0
004e8b91 movss xmm0, dword ptr [0xb6aa98]
004e8b99 cmovbe eax, ecx
004e8b9c movss xmm1, dword ptr [eax]
004e8ba0 comiss xmm1, xmm0
004e8ba3 ja 0x4e8bab
004e8ba5 movss xmm0, xmm1
004e8ba9 jmp 0x4e8baf
004e8bab movss xmm0, xmm0
004e8baf lea ecx, [ebp - 0x134]
004e8bb5 movss dword ptr [ebp - 0x114], xmm0
004e8bbd call 0x7a7db0
004e8bc2 movd xmm0, esi
004e8bc6 lea ecx, [ebp - 0x134]
004e8bcc cvtdq2ps xmm0, xmm0
004e8bcf movss dword ptr [ebp - 0x104], xmm0
004e8bd7 fmul dword ptr [ebp - 0x104]
004e8bdd fstp dword ptr [ebp - 0x118]
004e8be3 call 0x7a7db0
004e8be8 movss xmm1, dword ptr [ebp - 0x118]
004e8bf0 fstp dword ptr [ebp - 0x104]
004e8bf6 movss xmm0, dword ptr [ebp - 0x104]
004e8bfe addss xmm1, xmm1
004e8c02 mulss xmm0, dword ptr [0xb6ac40]
004e8c0a addss xmm0, xmm1
004e8c0e mulss xmm0, dword ptr [0xb6a230]
004e8c16 movss dword ptr [ebp - 0x104], xmm0
004e8c1e call 0x411fe0
004e8c23 movss dword ptr [ebp - 0x118], xmm0
004e8c2b movss xmm0, dword ptr [ebp - 0x104]
004e8c33 call 0x412010
004e8c38 movaps xmm3, xmm0
004e8c3b lea eax, [ebp - 0x124]
004e8c41 movss xmm0, dword ptr [ebp - 0x118]
004e8c49 lea ecx, [ebp - 0x108]
004e8c4f movaps xmm1, xmm3
004e8c52 movaps xmm2, xmm0
004e8c55 mulss xmm2, dword ptr [ebp - 0x114]
004e8c5d xorps xmm5, xmm5
004e8c60 push eax
004e8c61 mulss xmm3, dword ptr [ebp - 0x114]
004e8c69 mulss xmm0, xmm5
004e8c6d mulss xmm1, xmm5
004e8c71 addss xmm3, xmm0
004e8c75 movss xmm0, dword ptr [edi + 0x2c4]
004e8c7d mulss xmm0, dword ptr [0xb6a560]
004e8c85 subss xmm2, xmm1
004e8c89 addss xmm3, dword ptr [ebp - 0x10c]
004e8c91 movss dword ptr [edi + 0x2c4], xmm0
004e8c99 addss xmm2, dword ptr [ebp - 0x110]
004e8ca1 movss dword ptr [ebp - 0x10c], xmm3
004e8ca9 subss xmm3, dword ptr [edi + 0x298]
004e8cb1 movss dword ptr [ebp - 0x110], xmm2
004e8cb9 subss xmm2, dword ptr [edi + 0x294]
004e8cc1 movss dword ptr [ebp - 0x104], xmm3
004e8cc9 movss dword ptr [ebp - 0x108], xmm2
004e8cd1 call 0x962560
004e8cd6 push 0
004e8cd8 mov ecx, edi
004e8cda movss xmm0, dword ptr [eax]
004e8cde mulss xmm0, dword ptr [0xb6a560]
004e8ce6 movss dword ptr [ebp - 0x108], xmm0
004e8cee movss xmm0, dword ptr [eax + 4]
004e8cf3 lea eax, [ebp - 0x108]
004e8cf9 mulss xmm0, dword ptr [0xb6a560]
004e8d01 push eax
004e8d02 movss dword ptr [ebp - 0x104], xmm0
004e8d0a call 0x422b60
004e8d0f jmp 0x4e8d5b
004e8d11 push 1
004e8d13 push 0x384
004e8d18 push ecx
004e8d19 mov dword ptr [esp], 0x3f19999a
004e8d20 lea eax, [ebp - 0x110]
004e8d26 jmp 0x4e8d4f
004e8d28 push 1
004e8d2a push 0x384
004e8d2f sub esp, 8
004e8d32 lea eax, [ebp - 0x124]
004e8d38 mov ecx, edi
004e8d3a mov dword ptr [esp + 4], 0x3f19999a
004e8d42 mov dword ptr [esp], 0
004e8d49 push eax
004e8d4a call 0x695a30
004e8d4f push eax
004e8d50 lea ecx, [edi + 0x364]
004e8d56 call 0x7a3650
004e8d5b cmp dword ptr [edi + 0xab4], 8
004e8d62 je 0x4e8e4b
004e8d68 cmp dword ptr [edi + 0xe6c], -1
004e8d6f je 0x4e8d9a
004e8d71 movss xmm1, dword ptr [0xb6accc]
004e8d79 mov ecx, edi
004e8d7b push 7
004e8d7d push 0
004e8d7f call 0x6a15a0
004e8d84 test al, al
004e8d86 je 0x4e8e4b
004e8d8c push 1
004e8d8e mov ecx, edi
004e8d90 call 0x6afe20
004e8d95 jmp 0x4e8e32
004e8d9a cmp dword ptr [edi + 0x34], 0x38a
004e8da1 je 0x4e8e4b
004e8da7 movss xmm0, dword ptr [edi + 0xb00]
004e8daf call 0x4228c0
004e8db4 mov eax, dword ptr [edi + 0x28]
004e8db7 movaps xmm1, xmm0
004e8dba mulss xmm1, dword ptr [0xb6a2ac]
004e8dc2 addss xmm1, dword ptr [0xb6a210]
004e8dca cmp eax, 0x340
004e8dcf jne 0x4e8dd9
004e8dd1 mulss xmm1, dword ptr [0xb6a3d4]
004e8dd9 cmp dword ptr [edi + 0x32c], 0
004e8de0 je 0x4e8dea
004e8de2 mulss xmm1, dword ptr [0xb6a4dc]
004e8dea cmp eax, 0x33b
004e8def jne 0x4e8e08
004e8df1 cmp dword ptr [edi + 0x2c], 1
004e8df5 jne 0x4e8e08
004e8df7 cmp dword ptr [edi + 0x360], 0
004e8dfe jle 0x4e8e08
004e8e00 movss xmm1, dword ptr [0xb6a614]
004e8e08 call 0x6c3d90
004e8e0d movd xmm0, eax
004e8e11 cvtdq2pd xmm0, xmm0
004e8e15 shr eax, 0x1f
004e8e18 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e8e21 cvtpd2ps xmm0, xmm0
004e8e25 mulss xmm0, dword ptr [0xb6a19c]
004e8e2d comiss xmm1, xmm0
004e8e30 jb 0x4e8e4b
004e8e32 push 0
004e8e34 push 0xb40510
004e8e39 lea ecx, [edi + 0x3c]
004e8e3c call 0x405a00
004e8e41 mov dword ptr [edi + 0xab4], 8
004e8e4b cmp dword ptr [edi + 0x28], 0x33b
004e8e52 jne 0x4e9349
004e8e58 cmp dword ptr [edi + 0x2c], 1
004e8e5c jne 0x4e9349
004e8e62 mov eax, dword ptr [edi + 0x20]
004e8e65 xor edx, edx
004e8e67 mov ecx, 0x32
004e8e6c movss xmm1, dword ptr [0xb6aa60]
004e8e74 div ecx
004e8e76 mov ecx, edi
004e8e78 movd xmm0, edx
004e8e7c cvtdq2pd xmm0, xmm0
004e8e80 shr edx, 0x1f
004e8e83 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
004e8e8c cvtpd2ps xmm2, xmm0
004e8e90 call 0x6847e0
004e8e95 test eax, eax
004e8e97 je 0x4e9349
004e8e9d call 0x6c3d90
004e8ea2 test al, 1
004e8ea4 jne 0x4e9349
004e8eaa push ecx
004e8eab mov dword ptr [esp], 0x3f800000
004e8eb2 push 0
004e8eb4 push 2
004e8eb6 push ecx
004e8eb7 mov dword ptr [esp], 0x3f333333
004e8ebe mov ecx, edi
004e8ec0 push 3
004e8ec2 call 0x6ad720
004e8ec7 jmp 0x4e9349
004e8ecc cmp dword ptr [edi + 0x90], 0
004e8ed3 je 0x4e8ee4
004e8ed5 lea ecx, [edi + 0x8c]
004e8edb call 0x402350
004e8ee0 test al, al
004e8ee2 jne 0x4e8f4c
004e8ee4 mov eax, dword ptr [edi + 0x164]
004e8eea lea ecx, [edi + 0x3c]
004e8eed or dword ptr [edi + 0x160], 1
004e8ef4 push 0
004e8ef6 mov dword ptr [edi + 0x164], eax
004e8efc call 0x4062c0
004e8f01 mov byte ptr [eax + 0x74], 0
004e8f05 mov esi, dword ptr [edi + 0x30]
004e8f08 lea eax, [esi - 1]
004e8f0b cmp eax, 4
004e8f0e ja 0x4e8f13
004e8f10 dec esi
004e8f11 jmp 0x4e8f18
004e8f13 mov esi, 1
004e8f18 push 0
004e8f1a push dword ptr [esi*4 + 0xb42b90]
004e8f21 lea ecx, [edi + 0x3c]
004e8f24 call 0x405a00
004e8f29 cmp dword ptr [edi + 0x90], 0
004e8f30 je 0x4e8f3b
004e8f32 cmp byte ptr [edi + 0xa0], 0
004e8f39 jne 0x4e8f4c
004e8f3b push 0
004e8f3d push dword ptr [esi*4 + 0xb42b7c]
004e8f44 lea ecx, [edi + 0x3c]
004e8f47 call 0x405a00
004e8f4c mov edx, dword ptr [edi + 0x360]
004e8f52 test edx, edx
004e8f54 jle 0x4e9349
004e8f5a cvttss2si eax, dword ptr [edi + 0x2fc]
004e8f62 cvttss2si ecx, dword ptr [edi + 0x2f8]
004e8f6a sub ecx, eax
004e8f6c lea eax, [ecx + edx]
004e8f6f mov dword ptr [edi + 0x360], eax
004e8f75 test eax, eax
004e8f77 jg 0x4e9349
004e8f7d mov dword ptr [edi + 0xab4], 5
004e8f87 jmp 0x4e9349
004e8f8c push 0
004e8f8e lea esi, [edi + 0x3c]
004e8f91 push 0xb401c8
004e8f96 mov ecx, esi
004e8f98 call 0x405a00
004e8f9d push 0xb400ac
004e8fa2 lea ecx, [edi + 0x8c]
004e8fa8 call 0x405e90
004e8fad test al, al
004e8faf je 0x4e928f
004e8fb5 movss xmm2, dword ptr [0xb6a614]
004e8fbd push ecx
004e8fbe mov dword ptr [esp], 0x3f800000
004e8fc5 push 0
004e8fc7 push 2
004e8fc9 push 0x1e
004e8fcb call 0x8b1480
004e8fd0 call 0x6c3d90
004e8fd5 push eax
004e8fd6 push 1
004e8fd8 push 0
004e8fda push 0xc02fec
004e8fdf lea ecx, [edi + 0x294]
004e8fe5 push ecx
004e8fe6 mov ecx, dword ptr [0xbfd65c]
004e8fec push 0x93
004e8ff1 push 0x3e8
004e8ff6 call 0x422e20
004e8ffb mov esi, eax
004e8ffd mov ecx, esi
004e8fff mov edx, dword ptr [esi]
004e9001 call dword ptr [edx + 0xc]
004e9004 mov dword ptr [esi + 0xd0], 0
004e900e mov dword ptr [esi + 0xd4], 0xc1a00000
004e9018 mov edx, dword ptr [esi]
004e901a push ecx
004e901b mov ecx, esi
004e901d mov dword ptr [esp], 0
004e9024 call dword ptr [edx + 0x3c]
004e9027 call 0x6c3d90
004e902c mov ecx, dword ptr [0xbfd65c]
004e9032 lea esi, [edi + 0x294]
004e9038 push eax
004e9039 push 3
004e903b push 0
004e903d push 0xc02fec
004e9042 push esi
004e9043 push 2
004e9045 push 0x3e8
004e904a call 0x422e20
004e904f push 1
004e9051 push 0
004e9053 push 0xff
004e9058 mov edx, dword ptr [eax]
004e905a mov ecx, eax
004e905c push -1
004e905e push 0xbc5178
004e9063 call dword ptr [edx + 0x38]
004e9066 call 0x6c3d90
004e906b mov ecx, dword ptr [0xbfd65c]
004e9071 push eax
004e9072 push 0
004e9074 push 0
004e9076 push 0xc02fec
004e907b push esi
004e907c push 7
004e907e push 0x3e8
004e9083 call 0x422e20
004e9088 push 1
004e908a mov esi, eax
004e908c push 0
004e908e push 0xff
004e9093 push -1
004e9095 mov edx, dword ptr [esi]
004e9097 mov ecx, esi
004e9099 push 0xbc5178
004e909e call dword ptr [edx + 0x38]
004e90a1 mov eax, dword ptr [esi]
004e90a3 mov ecx, esi
004e90a5 call dword ptr [eax + 0xc]
004e90a8 call 0x6c3d90
004e90ad xor edx, edx
004e90af mov ecx, 5
004e90b4 div ecx
004e90b6 add edx, 3
004e90b9 mov dword ptr [ebp - 0x118], edx
004e90bf test edx, edx
004e90c1 jle 0x4e928c
004e90c7 call 0x6c3d90
004e90cc movd xmm0, eax
004e90d0 cvtdq2pd xmm0, xmm0
004e90d4 shr eax, 0x1f
004e90d7 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e90e0 cvtpd2ps xmm1, xmm0
004e90e4 mulss xmm1, dword ptr [0xb6a19c]
004e90ec mulss xmm1, dword ptr [0xb6a874]
004e90f4 addss xmm1, xmm1
004e90f8 movaps xmm0, xmm1
004e90fb movss dword ptr [ebp - 0x104], xmm1
004e9103 call 0x411fe0
004e9108 mulss xmm0, dword ptr [edi + 0x2c8]
004e9110 mulss xmm0, dword ptr [0xb6a480]
004e9118 addss xmm0, dword ptr [edi + 0x294]
004e9120 movss dword ptr [ebp - 0x124], xmm0
004e9128 movss xmm0, dword ptr [ebp - 0x104]
004e9130 call 0x412010
004e9135 mulss xmm0, dword ptr [edi + 0x2c8]
004e913d mulss xmm0, dword ptr [0xb6a480]
004e9145 addss xmm0, dword ptr [edi + 0x298]
004e914d movss dword ptr [ebp - 0x120], xmm0
004e9155 call 0x6c3d90
004e915a movd xmm0, eax
004e915e cvtdq2pd xmm0, xmm0
004e9162 shr eax, 0x1f
004e9165 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e916e cvtpd2ps xmm0, xmm0
004e9172 mulss xmm0, dword ptr [0xb6a19c]
004e917a mulss xmm0, dword ptr [0xb6a8cc]
004e9182 addss xmm0, dword ptr [0xb6a7b0]
004e918a movss dword ptr [ebp - 0x104], xmm0
004e9192 call 0x6c3d90
004e9197 movd xmm0, eax
004e919b cvtdq2pd xmm0, xmm0
004e919f shr eax, 0x1f
004e91a2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e91ab cvtpd2ps xmm0, xmm0
004e91af mulss xmm0, dword ptr [0xb6a19c]
004e91b7 mulss xmm0, dword ptr [0xb6a874]
004e91bf addss xmm0, xmm0
004e91c3 movss dword ptr [ebp - 0x114], xmm0
004e91cb call 0x411fe0
004e91d0 mulss xmm0, dword ptr [ebp - 0x104]
004e91d8 movss dword ptr [ebp - 0x110], xmm0
004e91e0 movss xmm0, dword ptr [ebp - 0x114]
004e91e8 call 0x412010
004e91ed mulss xmm0, dword ptr [ebp - 0x104]
004e91f5 movss dword ptr [ebp - 0x10c], xmm0
004e91fd call 0x6c3d90
004e9202 mov ecx, dword ptr [0xbfd65c]
004e9208 push eax
004e9209 push 0
004e920b push 0
004e920d lea eax, [ebp - 0x110]
004e9213 push eax
004e9214 lea eax, [ebp - 0x124]
004e921a push eax
004e921b push 5
004e921d push 0x3e8
004e9222 call 0x422e20
004e9227 push 1
004e9229 mov esi, eax
004e922b push 0
004e922d push 0xff
004e9232 push -1
004e9234 mov edx, dword ptr [esi]
004e9236 mov ecx, esi
004e9238 push 0xbc51fc
004e923d call dword ptr [edx + 0x38]
004e9240 lea ecx, [esi + 0x1dc]
004e9246 cmp ecx, 0xbc51fc
004e924c je 0x4e9278
004e924e movups xmm0, xmmword ptr [0xbc51fc]
004e9255 movups xmmword ptr [ecx], xmm0
004e9258 movups xmm0, xmmword ptr [0xbc520c]
004e925f movups xmmword ptr [ecx + 0x10], xmm0
004e9263 movq xmm0, qword ptr [0xbc521c]
004e926b movq qword ptr [ecx + 0x20], xmm0
004e9270 mov eax, dword ptr [0xbc5224]
004e9275 mov dword ptr [ecx + 0x28], eax
004e9278 mov eax, dword ptr [esi]
004e927a mov ecx, esi
004e927c call dword ptr [eax + 0xc]
004e927f sub dword ptr [ebp - 0x118], 1
004e9286 jne 0x4e90c7
004e928c lea esi, [edi + 0x3c]
004e928f cmp dword ptr [edi + 0x90], 0
004e9296 je 0x4e92a5
004e9298 cmp byte ptr [edi + 0xa0], 0
004e929f jne 0x4e9349
004e92a5 cmp dword ptr [esi + 0x80], 0
004e92ac jg 0x4e92ca
004e92ae cmp dword ptr [esi + 0x14], 0x10
004e92b2 mov eax, esi
004e92b4 jb 0x4e92b8
004e92b6 mov eax, dword ptr [esi]
004e92b8 push 0
004e92ba push eax
004e92bb push 0xa0830c
004e92c0 push 3
004e92c2 call 0x95e330
004e92c7 add esp, 0x10
004e92ca mov eax, dword ptr [esi + 0x7c]
004e92cd mov ecx, esi
004e92cf push 0
004e92d1 push 0xb404ec
004e92d6 mov byte ptr [eax + 0x74], 1
004e92da mov dword ptr [edi + 0xab4], 3
004e92e4 movss xmm0, dword ptr [0xc02fec]
004e92ec movss dword ptr [edi + 0x28c], xmm0
004e92f4 movss xmm0, dword ptr [0xc02ff0]
004e92fc movss dword ptr [edi + 0x290], xmm0
004e9304 call 0x405850
004e9309 push 1
004e930b push 0xb41e78
004e9310 mov ecx, esi
004e9312 call 0x405bb0
004e9317 test al, al
004e9319 je 0x4e932c
004e931b cmp dword ptr [esi + 0x54], 0
004e931f je 0x4e932c
004e9321 lea ecx, [esi + 0x50]
004e9324 xorps xmm1, xmm1
004e9327 call 0x403c00
004e932c mov eax, dword ptr [edi + 0x164]
004e9332 and dword ptr [edi + 0x160], 0xfffffffe
004e9339 mov dword ptr [edi + 0x164], eax
004e933f mov dword ptr [edi + 0x360], 1
004e9349 cmp byte ptr [edi + 0x16b], 0
004e9350 je 0x4e93b1
004e9352 movss xmm0, dword ptr [edi + 0x2d8]
004e935a comiss xmm0, dword ptr [0xb6aef8]
004e9361 jbe 0x4e93b1
004e9363 call 0x6c3d90
004e9368 test al, 1
004e936a jne 0x4e93b1
004e936c cmp dword ptr [edi + 0x28], 0x33b
004e9373 jne 0x4e937b
004e9375 cmp dword ptr [edi + 0x2c], 1
004e9379 je 0x4e93b1
004e937b call 0x6c3d90
004e9380 xor edx, edx
004e9382 mov ecx, 3
004e9387 div ecx
004e9389 xor eax, eax
004e938b mov ecx, edi
004e938d push -1
004e938f test edx, edx
004e9391 push 0
004e9393 sete al
004e9396 push eax
004e9397 push 0xb
004e9399 call 0x697c60
004e939e mov eax, dword ptr [edi + 0x2dc]
004e93a4 mov dword ptr [edi + 0x2d8], eax
004e93aa mov byte ptr [edi + 0x16b], 0
004e93b1 movss xmm0, dword ptr [edi + 0x14]
004e93b6 xorps xmm1, xmm1
004e93b9 comiss xmm0, xmm1
004e93bc jbe 0x4e93d0
004e93be addss xmm0, dword ptr [edi + 0xb00]
004e93c6 movss dword ptr [edi + 0xb00], xmm0
004e93ce jmp 0x4e93d8
004e93d0 movss xmm0, dword ptr [edi + 0xb00]
004e93d8 comiss xmm0, xmm1
004e93db jbe 0x4e93f1
004e93dd subss xmm0, dword ptr [0xb6a2dc]
004e93e5 maxss xmm0, xmm1
004e93e9 movss dword ptr [edi + 0xb00], xmm0
004e93f1 movss xmm2, dword ptr [edi + 0x28c]
004e93f9 ucomiss xmm2, dword ptr [0xc02fec]
004e9400 lahf 
004e9401 test ah, 0x44
004e9404 jp 0x4e941b
004e9406 movss xmm0, dword ptr [edi + 0x290]
004e940e ucomiss xmm0, dword ptr [0xc02ff0]
004e9415 lahf 
004e9416 test ah, 0x44
004e9419 jnp 0x4e9453
004e941b movss xmm1, dword ptr [edi + 0x290]
004e9423 subss xmm2, dword ptr [edi + 0x294]
004e942b subss xmm1, dword ptr [edi + 0x298]
004e9433 movss xmm0, dword ptr [edi + 0x2c4]
004e943b divss xmm2, xmm0
004e943f divss xmm1, xmm0
004e9443 movss dword ptr [edi + 0x2b8], xmm2
004e944b movss dword ptr [edi + 0x2bc], xmm1
004e9453 mov ecx, dword ptr [ebp - 0xc]
004e9456 mov dword ptr fs:[0], ecx
004e945d pop ecx
004e945e pop edi
004e945f pop esi
004e9460 mov ecx, dword ptr [ebp - 0x14]
004e9463 xor ecx, ebp
004e9465 call 0x9eacd7
004e946a mov esp, ebp
004e946c pop ebp
004e946d mov esp, ebx
004e946f pop ebx
004e9470 ret 
