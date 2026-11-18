0052b370 push ebp
0052b371 mov ebp, esp
0052b373 and esp, 0xfffffff8
0052b376 sub esp, 0x144
0052b37c mov eax, dword ptr [0xbaa3b4]
0052b381 xor eax, esp
0052b383 mov dword ptr [esp + 0x140], eax
0052b38a push ebx
0052b38b push esi
0052b38c push edi
0052b38d mov edi, ecx
0052b38f cmp dword ptr [edi + 0xac4], 1
0052b396 jne 0x52b5f6
0052b39c mov esi, dword ptr [edi + 0x28]
0052b39f xorps xmm2, xmm2
0052b3a2 mov edx, esi
0052b3a4 mov ecx, esi
0052b3a6 cmp esi, 0x114
0052b3ac jne 0x52b3eb
0052b3ae movss xmm0, dword ptr [edi + 0x14]
0052b3b3 mov edx, 0x114
0052b3b8 comiss xmm0, xmm2
0052b3bb jbe 0x52b3eb
0052b3bd mov eax, dword ptr [edi + 8]
0052b3c0 cmp eax, dword ptr [edi + 0xc]
0052b3c3 je 0x52b3eb
0052b3c5 test byte ptr [eax + 0x30], 1
0052b3c9 jne 0x52b3de
0052b3cb mov ecx, dword ptr [edi + 0x28]
0052b3ce cmp dword ptr [eax + 0x10], ecx
0052b3d1 je 0x52b3d8
0052b3d3 cmp dword ptr [eax + 0x18], ecx
0052b3d6 jne 0x52b3de
0052b3d8 mov dword ptr [eax], 0
0052b3de add eax, 0x38
0052b3e1 cmp eax, dword ptr [edi + 0xc]
0052b3e4 jne 0x52b3c5
0052b3e6 mov edx, dword ptr [edi + 0x28]
0052b3e9 mov ecx, edx
0052b3eb cmp edx, 0xf4
0052b3f1 jne 0x52d01f
0052b3f7 cmp dword ptr [edi + 0x2c], 3
0052b3fb mov edx, ecx
0052b3fd jne 0x52b466
0052b3ff movss xmm0, dword ptr [edi + 0x14]
0052b404 comiss xmm0, xmm2
0052b407 jbe 0x52b466
0052b409 mov eax, dword ptr [edi + 8]
0052b40c cmp eax, dword ptr [edi + 0xc]
0052b40f je 0x52b466
0052b411 mov ecx, dword ptr [eax + 0xc]
0052b414 mov edx, dword ptr [eax + 8]
0052b417 mov dword ptr [esp + 0x4c], ecx
0052b41b mov ecx, edx
0052b41d and ecx, 6
0052b420 or ecx, 0
0052b423 je 0x52b44f
0052b425 mov ecx, dword ptr [eax + 0x30]
0052b428 shr ecx, 1
0052b42a test cl, 1
0052b42d jne 0x52b44f
0052b42f cmp dword ptr [eax + 0x10], 1
0052b433 je 0x52b44f
0052b435 mov ecx, dword ptr [eax + 0x18]
0052b438 cmp ecx, 1
0052b43b je 0x52b44f
0052b43d cmp ecx, 3
0052b440 je 0x52b44f
0052b442 and edx, 0x1000
0052b448 or edx, 0
0052b44b jne 0x52b44f
0052b44d mov dword ptr [eax], edx
0052b44f add eax, 0x38
0052b452 cmp eax, dword ptr [edi + 0xc]
0052b455 jne 0x52b411
0052b457 mov edx, dword ptr [edi + 0x28]
0052b45a cmp edx, 0xf4
0052b460 jne 0x52d01f
0052b466 cmp dword ptr [edi + 0x2c], 2
0052b46a jne 0x52d01f
0052b470 cmp dword ptr [edi + 0x30], 1
0052b474 jne 0x52b4ac
0052b476 mov eax, dword ptr [edi + 0x314]
0052b47c mov ecx, edi
0052b47e test eax, eax
0052b480 je 0x52b491
0052b482 mov ecx, eax
0052b484 mov eax, dword ptr [ecx + 0x314]
0052b48a test eax, eax
0052b48c jne 0x52b482
0052b48e mov edx, dword ptr [edi + 0x28]
0052b491 cmp dword ptr [ecx + 0x28], edx
0052b494 jne 0x52b4a2
0052b496 cmp dword ptr [ecx + 0x2c], 2
0052b49a jne 0x52b4a2
0052b49c cmp dword ptr [ecx + 0x30], 0
0052b4a0 je 0x52b4ac
0052b4a2 mov eax, dword ptr [edi]
0052b4a4 mov ecx, edi
0052b4a6 call dword ptr [eax + 0x24]
0052b4a9 xorps xmm2, xmm2
0052b4ac cmp dword ptr [edi + 0x30], 0
0052b4b0 jne 0x52b5aa
0052b4b6 movss xmm1, dword ptr [0xb6adbc]
0052b4be mov eax, edi
0052b4c0 movss xmm0, dword ptr [eax + 0x2d8]
0052b4c8 minss xmm0, xmm1
0052b4cc movaps xmm1, xmm0
0052b4cf movss xmm0, dword ptr [eax + 0x14]
0052b4d4 mov eax, dword ptr [eax + 0x318]
0052b4da maxss xmm0, xmm2
0052b4de movaps xmm2, xmm0
0052b4e1 test eax, eax
0052b4e3 jne 0x52b4c0
0052b4e5 addss xmm0, xmm1
0052b4e9 movss dword ptr [esp + 0x14], xmm2
0052b4ef mov esi, edi
0052b4f1 movss dword ptr [esp + 0x3c], xmm0
0052b4f7 mov eax, dword ptr [esi]
0052b4f9 lea ecx, [esp + 0x74]
0052b4fd push 0x1e
0052b4ff push ecx
0052b500 push 0
0052b502 movss dword ptr [esi + 0x2d8], xmm0
0052b50a movss xmm1, dword ptr [0xc02fec]
0052b512 movss xmm0, dword ptr [0xc02ff0]
0052b51a push 0x2000
0052b51f push ecx
0052b520 mov ecx, esi
0052b522 mov dword ptr [esp + 0x88], 0
0052b52d mov dword ptr [esp + 0x8c], 0
0052b538 mov dword ptr [esp + 0x90], 0
0052b543 mov dword ptr [esp + 0x94], 0
0052b54e movss dword ptr [esp + 0x98], xmm1
0052b557 movss dword ptr [esp + 0x9c], xmm0
0052b560 movss dword ptr [esp + 0xa0], xmm1
0052b569 movss dword ptr [esp + 0xa4], xmm0
0052b572 mov dword ptr [esp + 0xa8], 0
0052b57d mov dword ptr [esp + 0xac], 0
0052b588 movss dword ptr [esp], xmm2
0052b58d call dword ptr [eax + 0x20]
0052b590 mov esi, dword ptr [esi + 0x318]
0052b596 movss xmm2, dword ptr [esp + 0x14]
0052b59c movss xmm0, dword ptr [esp + 0x3c]
0052b5a2 test esi, esi
0052b5a4 jne 0x52b4f7
0052b5aa cmp byte ptr [edi + 0x16b], 0
0052b5b1 je 0x52d01f
0052b5b7 mov eax, dword ptr [edi + 0x314]
0052b5bd test eax, eax
0052b5bf je 0x52b5d0
0052b5c1 mov edi, eax
0052b5c3 mov eax, dword ptr [edi + 0x314]
0052b5c9 test eax, eax
0052b5cb jne 0x52b5c1
0052b5cd nop dword ptr [eax]
0052b5d0 mov eax, dword ptr [edi]
0052b5d2 mov ecx, edi
0052b5d4 call dword ptr [eax + 0x24]
0052b5d7 mov edi, dword ptr [edi + 0x318]
0052b5dd test edi, edi
0052b5df jne 0x52b5d0
0052b5e1 pop edi
0052b5e2 pop esi
0052b5e3 pop ebx
0052b5e4 mov ecx, dword ptr [esp + 0x140]
0052b5eb xor ecx, esp
0052b5ed call 0x9eacd7
0052b5f2 mov esp, ebp
0052b5f4 pop ebp
0052b5f5 ret
0052b5f6 cmp byte ptr [edi + 0x16b], 0
0052b5fd je 0x52b634
0052b5ff movss xmm0, dword ptr [0xc02fec]
0052b607 movss dword ptr [edi + 0x2b8], xmm0
0052b60f movss xmm0, dword ptr [0xc02ff0]
0052b617 movss dword ptr [edi + 0x2bc], xmm0
0052b61f pop edi
0052b620 pop esi
0052b621 pop ebx
0052b622 mov ecx, dword ptr [esp + 0x140]
0052b629 xor ecx, esp
0052b62b call 0x9eacd7
0052b630 mov esp, ebp
0052b632 pop ebp
0052b633 ret
0052b634 movd xmm3, dword ptr [edi + 0xb14]
0052b63c xorps xmm2, xmm2
0052b63f movss xmm1, dword ptr [0xb6aae4]
0052b647 cvtdq2ps xmm3, xmm3
0052b64a push 1
0052b64c call 0x6afbd0
0052b651 mov eax, dword ptr [edi + 0xab4]
0052b657 test eax, eax
0052b659 jne 0x52bc42
0052b65f mov dword ptr [edi + 0xab4], 6
0052b669 lea esi, [edi + 0x294]
0052b66f mov eax, dword ptr [esi]
0052b671 mov ecx, edi
0052b673 mov dword ptr [edi + 0x28c], eax
0052b679 mov eax, dword ptr [esi + 4]
0052b67c push 1
0052b67e mov dword ptr [esp + 0x38], esi
0052b682 mov dword ptr [edi + 0x290], eax
0052b688 call 0x6971a0
0052b68d cmp dword ptr [edi + 0x28], 0xf4
0052b694 lea eax, [edi + 0x28]
0052b697 mov dword ptr [edi + 0xe68], 1
0052b6a1 mov dword ptr [esp + 0x58], eax
0052b6a5 jne 0x52d01f
0052b6ab cmp dword ptr [edi + 0x2c], 2
0052b6af lea eax, [edi + 0x2c]
0052b6b2 mov dword ptr [esp + 0x70], eax
0052b6b6 jne 0x52d01f
0052b6bc cmp dword ptr [edi + 0x30], 0
0052b6c0 jne 0x52d01f
0052b6c6 mov ebx, dword ptr [0xbfd65c]
0052b6cc add ebx, 0x18190
0052b6d2 push 0x384
0052b6d7 push esi
0052b6d8 mov ecx, dword ptr [ebx]
0052b6da call 0x4baf00
0052b6df movss xmm1, dword ptr [0xb6a19c]
0052b6e7 lea eax, [edi + 0x298]
0052b6ed mov dword ptr [esp + 0x6c], eax
0052b6f1 mov dword ptr [esp + 0x14], 5
0052b6f9 mov dword ptr [esp + 0x30], 0x3e8
0052b701 call 0x6c3d90
0052b706 movd xmm0, eax
0052b70a cvtdq2pd xmm0, xmm0
0052b70e shr eax, 0x1f
0052b711 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052b71a cvtpd2ps xmm0, xmm0
0052b71e mulss xmm0, xmm1
0052b722 mulss xmm0, dword ptr [0xb6aad4]
0052b72a addss xmm0, dword ptr [0xb6a9c8]
0052b732 movss dword ptr [esp + 0x20], xmm0
0052b738 call 0x6c3d90
0052b73d movd xmm0, eax
0052b741 cvtdq2pd xmm0, xmm0
0052b745 shr eax, 0x1f
0052b748 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052b751 cvtpd2ps xmm0, xmm0
0052b755 mulss xmm0, xmm1
0052b759 mulss xmm0, dword ptr [0xb6a874]
0052b761 addss xmm0, xmm0
0052b765 movss dword ptr [esp + 0x2c], xmm0
0052b76b call 0x411fe0
0052b770 mulss xmm0, dword ptr [esp + 0x20]
0052b776 addss xmm0, dword ptr [esi]
0052b77a movss dword ptr [esp + 0x64], xmm0
0052b780 movss xmm0, dword ptr [esp + 0x2c]
0052b786 call 0x412010
0052b78b mulss xmm0, dword ptr [esp + 0x20]
0052b791 sub esp, 0xc
0052b794 mov eax, dword ptr [esp + 0x78]
0052b798 movss xmm3, dword ptr [0xb6a974]
0052b7a0 mov ecx, dword ptr [ebx]
0052b7a2 mov dword ptr [esp + 8], 0x41200000
0052b7aa addss xmm0, dword ptr [eax]
0052b7ae mov dword ptr [esp + 4], 0x41200000
0052b7b6 lea eax, [esp + 0x70]
0052b7ba mov dword ptr [esp], 0x41200000
0052b7c1 push eax
0052b7c2 lea eax, [esp + 0x58]
0052b7c6 push eax
0052b7c7 movss dword ptr [esp + 0x7c], xmm0
0052b7cd call 0x7cec10
0052b7d2 push 0
0052b7d4 push 1
0052b7d6 push ecx
0052b7d7 mov ecx, dword ptr [ebx]
0052b7d9 lea eax, [esp + 0x54]
0052b7dd mov dword ptr [esp], 0
0052b7e4 push eax
0052b7e5 lea eax, [esp + 0x1c]
0052b7e9 push eax
0052b7ea call 0x7cf240
0052b7ef call 0x6c3d90
0052b7f4 movd xmm0, eax
0052b7f8 cvtdq2pd xmm0, xmm0
0052b7fc shr eax, 0x1f
0052b7ff addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052b808 cvtpd2ps xmm0, xmm0
0052b80c mulss xmm0, dword ptr [0xb6a19c]
0052b814 movss dword ptr [esp + 0x20], xmm0
0052b81a call 0x6c3d90
0052b81f movd xmm0, eax
0052b823 cvtdq2pd xmm0, xmm0
0052b827 shr eax, 0x1f
0052b82a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052b833 cvtpd2ps xmm0, xmm0
0052b837 mulss xmm0, dword ptr [0xb6a19c]
0052b83f mulss xmm0, dword ptr [0xb6a874]
0052b847 addss xmm0, xmm0
0052b84b movss dword ptr [esp + 0x2c], xmm0
0052b851 call 0x411fe0
0052b856 mulss xmm0, dword ptr [0xb6a9ac]
0052b85e mulss xmm0, dword ptr [esp + 0x20]
0052b864 addss xmm0, dword ptr [esp + 0xc]
0052b86a movss dword ptr [esp + 0xc], xmm0
0052b870 movss xmm0, dword ptr [esp + 0x2c]
0052b876 call 0x412010
0052b87b mulss xmm0, dword ptr [0xb6a9ac]
0052b883 mov esi, dword ptr [0xbfd65c]
0052b889 mulss xmm0, dword ptr [esp + 0x20]
0052b88f addss xmm0, dword ptr [esp + 0x10]
0052b895 movss dword ptr [esp + 0x10], xmm0
0052b89b call 0x6c3d90
0052b8a0 mov dword ptr [esp + 0x20], eax
0052b8a4 mov eax, dword ptr [esp + 0x70]
0052b8a8 mov dword ptr [esp + 0x50], 1
0052b8b0 mov eax, dword ptr [eax]
0052b8b2 mov dword ptr [esp + 0x2c], eax
0052b8b6 mov eax, dword ptr [esp + 0x58]
0052b8ba mov eax, dword ptr [eax]
0052b8bc mov dword ptr [esp + 0x24], eax
0052b8c0 lea eax, [esp + 0x20]
0052b8c4 push eax
0052b8c5 lea eax, [esp + 0x54]
0052b8c9 push eax
0052b8ca push 0
0052b8cc push 0xc02fec
0052b8d1 lea eax, [esp + 0x1c]
0052b8d5 push eax
0052b8d6 lea eax, [esp + 0x40]
0052b8da push eax
0052b8db lea eax, [esp + 0x3c]
0052b8df push eax
0052b8e0 call 0x800fb0
0052b8e5 mov ecx, dword ptr [esi + 0x1c3198]
0052b8eb push 0
0052b8ed push dword ptr [esp + 0x28]
0052b8f1 call 0x6c4b30
0052b8f6 mov ebx, eax
0052b8f8 test ebx, ebx
0052b8fa je 0x52bb0c
0052b900 call dword ptr [0xa064c0]
0052b906 mov ecx, dword ptr [ebx + 0x320]
0052b90c mov dword ptr [esp + 0x28], eax
0052b910 lea eax, [ebx + 0x320]
0052b916 mov dword ptr [ebx + 0x34], 0
0052b91d mov dword ptr [ebx + 0x38], 0
0052b924 test ecx, ecx
0052b926 je 0x52b942
0052b928 mov dword ptr [esp + 0x54], eax
0052b92c add ecx, 0x324
0052b932 lea eax, [esp + 0x54]
0052b936 push eax
0052b937 call 0x4bc3c0
0052b93c lea eax, [ebx + 0x320]
0052b942 push dword ptr [esp + 0x20]
0052b946 mov dword ptr [eax], 0
0052b94c mov ecx, ebx
0052b94e movss xmm0, dword ptr [esp + 0x10]
0052b954 push dword ptr [esp + 0x54]
0052b958 mov eax, dword ptr [ebx]
0052b95a push dword ptr [esp + 0x34]
0052b95e movss dword ptr [ebx + 0x294], xmm0
0052b966 movss xmm0, dword ptr [esp + 0x1c]
0052b96c push dword ptr [esp + 0x30]
0052b970 movss dword ptr [ebx + 0x298], xmm0
0052b978 movss xmm0, dword ptr [0xc02fec]
0052b980 movss dword ptr [ebx + 0x2b8], xmm0
0052b988 movss xmm0, dword ptr [0xc02ff0]
0052b990 movss dword ptr [ebx + 0x2bc], xmm0
0052b998 call dword ptr [eax + 4]
0052b99b mov edx, dword ptr [esi + 0x18190]
0052b9a1 push ebx
0052b9a2 mov ecx, dword ptr [edx + 0x1214]
0052b9a8 lea eax, [ecx + 1]
0052b9ab mov dword ptr [edx + 0x1214], eax
0052b9b1 mov dword ptr [ebx + 0x20], ecx
0052b9b4 lea ecx, [edx + 0x1218]
0052b9ba call 0x413280
0052b9bf push ebx
0052b9c0 call 0x6d94d0
0052b9c5 test al, al
0052b9c7 je 0x52b9d0
0052b9c9 push ecx
0052b9ca push ebx
0052b9cb call 0x6d9590
0052b9d0 cmp byte ptr [ebx + 0x16a], 0
0052b9d7 je 0x52bafc
0052b9dd mov eax, dword ptr [esi + 0x283c20]
0052b9e3 cmp eax, dword ptr [esi + 0x283c24]
0052b9e9 je 0x52bafc
0052b9ef mov eax, dword ptr [ebx + 0x2c]
0052b9f2 mov ecx, dword ptr [ebx + 0x28]
0052b9f5 mov dword ptr [esp + 0x44], eax
0052b9f9 lea eax, [esp + 0x40]
0052b9fd push eax
0052b9fe lea eax, [esp + 0x40]
0052ba02 mov dword ptr [esp + 0x44], ecx
0052ba06 push eax
0052ba07 lea ecx, [esi + 0x283c48]
0052ba0d call 0x937c80
0052ba12 mov eax, dword ptr [esi + 0x283c48]
0052ba18 cmp dword ptr [esp + 0x3c], eax
0052ba1c jne 0x52ba54
0052ba1e mov eax, dword ptr [ebx + 0x28]
0052ba21 lea ecx, [esi + 0x283c48]
0052ba27 mov dword ptr [esp + 0x18], eax
0052ba2b lea eax, [esp + 0x18]
0052ba2f push eax
0052ba30 lea eax, [esp + 0x60]
0052ba34 mov dword ptr [esp + 0x20], 0xffffffff
0052ba3c push eax
0052ba3d call 0x937c80
0052ba42 mov eax, dword ptr [eax]
0052ba44 mov dword ptr [esp + 0x3c], eax
0052ba48 cmp eax, dword ptr [esi + 0x283c48]
0052ba4e je 0x52bafc
0052ba54 mov esi, dword ptr [0xbfd65c]
0052ba5a xor edx, edx
0052ba5c mov dword ptr [esp + 0x24], edx
0052ba60 mov eax, dword ptr [esi + 0x1ba54]
0052ba66 sub eax, dword ptr [esi + 0x1ba50]
0052ba6c sar eax, 2
0052ba6f test eax, eax
0052ba71 je 0x52bafc
0052ba77 nop word ptr [eax + eax]
0052ba80 mov ecx, dword ptr [esi + 0x1ba54]
0052ba86 mov eax, ecx
0052ba88 sub eax, dword ptr [esi + 0x1ba50]
0052ba8e test eax, 0xfffffffc
0052ba93 jne 0x52baae
0052ba95 push 0xb3f4d0
0052ba9a push 3
0052ba9c call 0x95e330
0052baa1 mov ecx, dword ptr [esi + 0x1ba54]
0052baa7 add esp, 8
0052baaa mov edx, dword ptr [esp + 0x24]
0052baae mov eax, dword ptr [esi + 0x1ba50]
0052bab4 sub ecx, eax
0052bab6 sar ecx, 2
0052bab9 cmp edx, ecx
0052babb jae 0x52bac0
0052babd lea eax, [eax + edx*4]
0052bac0 push 0xc02fec
0052bac5 lea ecx, [esp + 0x10]
0052bac9 push ecx
0052baca mov ecx, dword ptr [eax]
0052bacc push ebx
0052bacd push 6
0052bacf add ecx, 0x1ec0
0052bad5 call 0x935fd0
0052bada mov esi, dword ptr [0xbfd65c]
0052bae0 mov edx, dword ptr [esp + 0x24]
0052bae4 inc edx
0052bae5 mov dword ptr [esp + 0x24], edx
0052bae9 mov eax, dword ptr [esi + 0x1ba54]
0052baef sub eax, dword ptr [esi + 0x1ba50]
0052baf5 sar eax, 2
0052baf8 cmp edx, eax
0052bafa jb 0x52ba80
0052bafc call dword ptr [0xa064c0]
0052bb02 sub eax, dword ptr [esp + 0x28]
0052bb06 add dword ptr [0xbffe0c], eax
0052bb0c mov ecx, dword ptr [ebx + 0x314]
0052bb12 lea esi, [ebx + 0x314]
0052bb18 test ecx, ecx
0052bb1a je 0x52bb30
0052bb1c lea eax, [esp + 0x28]
0052bb20 mov dword ptr [esp + 0x28], esi
0052bb24 push eax
0052bb25 add ecx, 0x324
0052bb2b call 0x4bc3c0
0052bb30 mov dword ptr [esi], edi
0052bb32 test edi, edi
0052bb34 je 0x52bb3e
0052bb36 push esi
0052bb37 mov ecx, edi
0052bb39 call 0x4bae70
0052bb3e mov ecx, dword ptr [edi + 0x318]
0052bb44 add edi, 0x318
0052bb4a test ecx, ecx
0052bb4c je 0x52bb62
0052bb4e lea eax, [esp + 0x28]
0052bb52 mov dword ptr [esp + 0x28], edi
0052bb56 push eax
0052bb57 add ecx, 0x324
0052bb5d call 0x4bc3c0
0052bb62 push edi
0052bb63 mov ecx, ebx
0052bb65 mov dword ptr [edi], ebx
0052bb67 call 0x4bae70
0052bb6c mov eax, dword ptr [ebx]
0052bb6e mov ecx, ebx
0052bb70 call dword ptr [eax + 0xc]
0052bb73 movss xmm2, dword ptr [0xb6aa3c]
0052bb7b movss xmm0, dword ptr [ebx + 0x294]
0052bb83 movss xmm1, dword ptr [ebx + 0x298]
0052bb8b subss xmm0, xmm2
0052bb8f subss xmm1, dword ptr [0xb6ab20]
0052bb97 mov esi, dword ptr [0xbfd65c]
0052bb9d add esi, 0x18190
0052bba3 mov dword ptr [esp + 0x28], esi
0052bba7 divss xmm0, xmm2
0052bbab mov esi, dword ptr [esi]
0052bbad divss xmm1, xmm2
0052bbb1 addss xmm0, dword ptr [0xb6a480]
0052bbb9 addss xmm1, dword ptr [0xb6a480]
0052bbc1 cvttss2si edx, xmm0
0052bbc5 cvttss2si ecx, xmm1
0052bbc9 test edx, edx
0052bbcb js 0x52bc10
0052bbcd mov eax, dword ptr [esi + 0xc]
0052bbd0 cmp edx, eax
0052bbd2 jge 0x52bc10
0052bbd4 test ecx, ecx
0052bbd6 js 0x52bc10
0052bbd8 cmp ecx, dword ptr [esi + 0x10]
0052bbdb jge 0x52bc10
0052bbdd imul eax, ecx
0052bbe0 lea edi, [eax + edx]
0052bbe3 cmp edi, 0x1bf
0052bbe9 ja 0x52bc10
0052bbeb mov ecx, dword ptr [esi + edi*4 + 0x76c]
0052bbf2 mov eax, ecx
0052bbf4 cdq
0052bbf5 idiv dword ptr [esp + 0x30]
0052bbf9 cmp edx, 0x384
0052bbff jge 0x52bc10
0052bc01 sub ecx, edx
0052bc03 add ecx, 0x384
0052bc09 mov dword ptr [esi + edi*4 + 0x76c], ecx
0052bc10 sub dword ptr [esp + 0x14], 1
0052bc15 mov edi, ebx
0052bc17 movss xmm1, dword ptr [0xb6a19c]
0052bc1f mov ebx, dword ptr [esp + 0x28]
0052bc23 mov esi, dword ptr [esp + 0x34]
0052bc27 jne 0x52b701
0052bc2d pop edi
0052bc2e pop esi
0052bc2f pop ebx
0052bc30 mov ecx, dword ptr [esp + 0x140]
0052bc37 xor ecx, esp
0052bc39 call 0x9eacd7
0052bc3e mov esp, ebp
0052bc40 pop ebp
0052bc41 ret
0052bc42 cmp eax, 6
0052bc45 jne 0x52bcd4
0052bc4b push 0
0052bc4d push 0xb42b00
0052bc52 lea ecx, [edi + 0x3c]
0052bc55 call 0x4054f0
0052bc5a cmp dword ptr [edi + 0x70], 0
0052bc5e je 0x52bc6d
0052bc60 cmp byte ptr [edi + 0x80], 0
0052bc67 jne 0x52cfb5
0052bc6d movss xmm0, dword ptr [edi + 0x14]
0052bc72 comiss xmm0, dword ptr [edi + 0x2d8]
0052bc79 jb 0x52bc94
0052bc7b mov dword ptr [edi + 0xab4], 8
0052bc85 mov dword ptr [edi + 0xb10], 0
0052bc8f jmp 0x52cfb5
0052bc94 mov dword ptr [edi + 0xab4], 4
0052bc9e movss xmm0, dword ptr [0xc02fec]
0052bca6 movss dword ptr [edi + 0x28c], xmm0
0052bcae movss xmm0, dword ptr [0xc02ff0]
0052bcb6 movss dword ptr [edi + 0x290], xmm0
0052bcbe mov dword ptr [edi + 0x180], 0
0052bcc8 mov byte ptr [edi + 0x169], 0
0052bccf jmp 0x52cfb5
0052bcd4 cmp eax, 4
0052bcd7 jne 0x52c0a9
0052bcdd cmp dword ptr [edi + 0x28], 0xf4
0052bce4 jne 0x52bcf6
0052bce6 cmp dword ptr [edi + 0x2c], 2
0052bcea jne 0x52bcf6
0052bcec cmp dword ptr [edi + 0x30], 1
0052bcf0 je 0x52cfb5
0052bcf6 cmp dword ptr [edi + 0xe6c], -1
0052bcfd je 0x52be55
0052bd03 cvttss2si ecx, dword ptr [edi + 0x2fc]
0052bd0b push 1
0052bd0d push 0
0052bd0f cvttss2si eax, dword ptr [edi + 0x2f8]
0052bd17 sub ecx, eax
0052bd19 add dword ptr [edi + 0xb14], ecx
0052bd1f push ecx
0052bd20 mov dword ptr [esp], 0x40400000
0052bd27 lea ecx, [edi + 0x364]
0052bd2d push 0xc02fec
0052bd32 call 0x7a3650
0052bd37 movss xmm1, dword ptr [0xb6accc]
0052bd3f mov ecx, edi
0052bd41 push 7
0052bd43 push 0
0052bd45 call 0x6a15a0
0052bd4a test al, al
0052bd4c jne 0x52bd5b
0052bd4e cmp dword ptr [edi + 0xb14], 0x5a
0052bd55 jl 0x52c03a
0052bd5b push dword ptr [edi + 0x298]
0052bd61 mov ebx, dword ptr [0xbfd65c]
0052bd67 lea esi, [edi + 0x294]
0052bd6d push dword ptr [esi]
0052bd6f mov ecx, dword ptr [ebx + 0x18190]
0052bd75 call 0x7aee40
0052bd7a test eax, eax
0052bd7c jne 0x52bd9f
0052bd7e movss xmm2, dword ptr [0xb6aad4]
0052bd86 sub esp, 8
0052bd89 mov ecx, edi
0052bd8b push esi
0052bd8c call 0x690880
0052bd91 test al, al
0052bd93 je 0x52be04
0052bd99 mov ebx, dword ptr [0xbfd65c]
0052bd9f push 0
0052bda1 push 1
0052bda3 push ecx
0052bda4 mov ecx, dword ptr [ebx + 0x18190]
0052bdaa lea eax, [esp + 0x18]
0052bdae mov dword ptr [esp], 0
0052bdb5 push esi
0052bdb6 push eax
0052bdb7 call 0x7cf240
0052bdbc movss xmm1, dword ptr [esp + 0xc]
0052bdc2 movss xmm0, dword ptr [esp + 0x10]
0052bdc8 subss xmm0, dword ptr [esi + 4]
0052bdcd subss xmm1, dword ptr [esi]
0052bdd1 mulss xmm0, xmm0
0052bdd5 mulss xmm1, xmm1
0052bdd9 addss xmm0, xmm1
0052bddd call 0x4228c0
0052bde2 movss xmm1, dword ptr [0xb6aa0c]
0052bdea comiss xmm1, xmm0
0052bded jbe 0x52be1a
0052bdef movss xmm0, dword ptr [esp + 0xc]
0052bdf5 movss dword ptr [esi], xmm0
0052bdf9 movss xmm0, dword ptr [esp + 0x10]
0052bdff movss dword ptr [esi + 4], xmm0
0052be04 mov eax, dword ptr [esi]
0052be06 mov dword ptr [edi + 0x28c], eax
0052be0c mov eax, dword ptr [esi + 4]
0052be0f mov dword ptr [edi + 0x290], eax
0052be15 jmp 0x52c03a
0052be1a cmp dword ptr [edi + 0xb14], 0x78
0052be21 jl 0x52c03a
0052be27 mov edx, dword ptr [edi]
0052be29 lea ecx, [esp + 0x74]
0052be2d push 0x1e
0052be2f mov dword ptr [edi + 0xb14], 0x5a
0052be39 call 0x427290
0052be3e push eax
0052be3f push 0
0052be41 push 0
0052be43 push ecx
0052be44 mov ecx, edi
0052be46 mov dword ptr [esp], 0x40600000
0052be4d call dword ptr [edx + 0x20]
0052be50 jmp 0x52c03a
0052be55 cmp dword ptr [edi + 0x360], 0
0052be5c jg 0x52c03a
0052be62 mov esi, dword ptr [0xbfd65c]
0052be68 mov eax, dword ptr [esi + 0x18190]
0052be6e movss xmm0, dword ptr [eax + 0x1c]
0052be73 movss dword ptr [esp + 0x34], xmm0
0052be79 movss xmm0, dword ptr [eax + 0x20]
0052be7e movss dword ptr [esp + 0x54], xmm0
0052be84 movss xmm0, dword ptr [eax + 0x14]
0052be89 movss dword ptr [esp + 0x30], xmm0
0052be8f movss xmm0, dword ptr [eax + 0x18]
0052be94 movss dword ptr [esp + 0x58], xmm0
0052be9a call 0x6c3d90
0052be9f movd xmm0, eax
0052bea3 cvtdq2pd xmm0, xmm0
0052bea7 shr eax, 0x1f
0052beaa addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052beb3 lea eax, [esp + 0x48]
0052beb7 push eax
0052beb8 cvtpd2ps xmm0, xmm0
0052bebc mulss xmm0, dword ptr [0xb6a19c]
0052bec4 mulss xmm0, dword ptr [0xb6abec]
0052becc addss xmm0, dword ptr [0xb6aa8c]
0052bed4 movss dword ptr [esp + 0x2c], xmm0
0052beda call 0x659290
0052bedf movss xmm3, dword ptr [esp + 0x38]
0052bee5 addss xmm3, dword ptr [esp + 0x34]
0052beeb movss xmm2, dword ptr [esp + 0x2c]
0052bef1 mov ecx, dword ptr [esi + 0x18190]
0052bef7 movaps xmm0, xmm2
0052befa mulss xmm0, dword ptr [eax]
0052befe mov dword ptr [esp], 0x41a00000
0052bf05 sub esp, 8
0052bf08 mulss xmm2, dword ptr [eax + 4]
0052bf0d lea eax, [esp + 0x18]
0052bf11 mulss xmm3, dword ptr [0xb6a480]
0052bf19 mov dword ptr [esp + 4], 0x41a00000
0052bf21 mov dword ptr [esp], 0x41a00000
0052bf28 push eax
0052bf29 addss xmm3, xmm0
0052bf2d movss xmm0, dword ptr [esp + 0x64]
0052bf33 addss xmm0, dword ptr [esp + 0x68]
0052bf39 lea eax, [esp + 0x28]
0052bf3d push eax
0052bf3e movss dword ptr [esp + 0x20], xmm3
0052bf44 mulss xmm0, dword ptr [0xb6a480]
0052bf4c movss xmm3, dword ptr [0xb6a9c8]
0052bf54 addss xmm0, xmm2
0052bf58 movss dword ptr [esp + 0x24], xmm0
0052bf5e call 0x7cec10
0052bf63 movss xmm0, dword ptr [esp + 0x18]
0052bf69 lea eax, [esp + 0xc]
0052bf6d push 0
0052bf6f push 1
0052bf71 push ecx
0052bf72 mov ecx, dword ptr [esi + 0x18190]
0052bf78 mov dword ptr [esp], 0
0052bf7f push eax
0052bf80 movss dword ptr [esp + 0x1c], xmm0
0052bf86 lea eax, [esp + 0x58]
0052bf8a movss xmm0, dword ptr [esp + 0x2c]
0052bf90 push eax
0052bf91 movss dword ptr [esp + 0x24], xmm0
0052bf97 call 0x7cf240
0052bf9c mov ecx, dword ptr [0xbfd65c]
0052bfa2 movss xmm0, dword ptr [eax]
0052bfa6 movss dword ptr [esp + 0x34], xmm0
0052bfac movss dword ptr [esp + 0xc], xmm0
0052bfb2 movss xmm0, dword ptr [eax + 4]
0052bfb7 lea eax, [esp + 0xc]
0052bfbb push eax
0052bfbc movss dword ptr [esp + 0x34], xmm0
0052bfc2 movss dword ptr [esp + 0x14], xmm0
0052bfc8 call 0x6d5e30
0052bfcd movss xmm2, dword ptr [esp + 0x34]
0052bfd3 movss xmm3, dword ptr [esp + 0x30]
0052bfd9 movaps xmm0, xmm2
0052bfdc movaps xmm1, xmm3
0052bfdf subss xmm1, dword ptr [eax + 0x298]
0052bfe7 subss xmm0, dword ptr [eax + 0x294]
0052bfef mulss xmm1, xmm1
0052bff3 mulss xmm0, xmm0
0052bff7 addss xmm1, xmm0
0052bffb call 0x6c3d90
0052c000 test al, 1
0052c002 jne 0x52c03a
0052c004 comiss xmm1, dword ptr [0xb6ad38]
0052c00b jbe 0x52c03a
0052c00d movss xmm0, dword ptr [0xb6ada0]
0052c015 comiss xmm0, xmm1
0052c018 jbe 0x52c03a
0052c01a movss dword ptr [edi + 0x28c], xmm2
0052c022 movss dword ptr [edi + 0x290], xmm3
0052c02a movss dword ptr [edi + 0x294], xmm2
0052c032 movss dword ptr [edi + 0x298], xmm3
0052c03a mov edx, dword ptr [edi + 0x360]
0052c040 test edx, edx
0052c042 jle 0x52c05e
0052c044 cvttss2si eax, dword ptr [edi + 0x2fc]
0052c04c cvttss2si ecx, dword ptr [edi + 0x2f8]
0052c054 sub ecx, eax
0052c056 add ecx, edx
0052c058 mov dword ptr [edi + 0x360], ecx
0052c05e push 0xc02fec
0052c063 lea ecx, [edi + 0x28c]
0052c069 call 0x962ca0
0052c06e test al, al
0052c070 je 0x52cfb5
0052c076 mov dword ptr [edi + 0xab4], 8
0052c080 mov ecx, edi
0052c082 mov dword ptr [edi + 0xb10], 0
0052c08c push 1
0052c08e mov byte ptr [edi + 0x169], 1
0052c095 call 0x6971a0
0052c09a mov dword ptr [edi + 0xb14], 0
0052c0a4 jmp 0x52cfb5
0052c0a9 cmp eax, 8
0052c0ac jne 0x52cfb5
0052c0b2 movss xmm2, dword ptr [0xb6ae44]
0052c0ba mov ecx, edi
0052c0bc push 0
0052c0be call 0x6af8d0
0052c0c3 push 0
0052c0c5 lea ebx, [edi + 0x3c]
0052c0c8 push 0xb42ae0
0052c0cd mov ecx, ebx
0052c0cf call 0x4054f0
0052c0d4 mov eax, dword ptr [edi + 0x2c]
0052c0d7 mov dword ptr [edi + 0x180], 4
0052c0e1 cmp eax, 1
0052c0e4 je 0x52c9cf
0052c0ea cmp eax, 3
0052c0ed je 0x52c9cf
0052c0f3 cmp dword ptr [edi + 0x28], 0xf4
0052c0fa jne 0x52c3fe
0052c100 cmp eax, 2
0052c103 jne 0x52c3fe
0052c109 cmp dword ptr [edi + 0x318], 0
0052c110 je 0x52c3fe
0052c116 push 0xb43388
0052c11b mov ecx, ebx
0052c11d call 0x4060f0
0052c122 test al, al
0052c124 je 0x52c3fe
0052c12a mov ecx, edi
0052c12c call 0x448120
0052c131 mov dword ptr [esp + 0x50], eax
0052c135 xor ebx, ebx
0052c137 movss xmm1, dword ptr [0xb6a19c]
0052c13f call 0x6c3d90
0052c144 movd xmm0, eax
0052c148 cvtdq2pd xmm0, xmm0
0052c14c shr eax, 0x1f
0052c14f addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052c158 cvtpd2ps xmm0, xmm0
0052c15c mulss xmm0, xmm1
0052c160 mulss xmm0, dword ptr [0xb6abec]
0052c168 addss xmm0, dword ptr [0xb6aa8c]
0052c170 movss dword ptr [esp + 0x14], xmm0
0052c176 call 0x6c3d90
0052c17b movd xmm0, eax
0052c17f cvtdq2pd xmm0, xmm0
0052c183 shr eax, 0x1f
0052c186 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052c18f cvtpd2ps xmm0, xmm0
0052c193 mulss xmm0, xmm1
0052c197 mulss xmm0, dword ptr [0xb6a874]
0052c19f addss xmm0, xmm0
0052c1a3 movss dword ptr [esp + 0x34], xmm0
0052c1a9 call 0x411fe0
0052c1ae mulss xmm0, dword ptr [esp + 0x14]
0052c1b4 addss xmm0, dword ptr [edi + 0x294]
0052c1bc movss dword ptr [esp + 0xc], xmm0
0052c1c2 movss xmm0, dword ptr [esp + 0x34]
0052c1c8 call 0x412010
0052c1cd mulss xmm0, dword ptr [esp + 0x14]
0052c1d3 lea eax, [esp + 0xc]
0052c1d7 mov esi, dword ptr [0xbfd65c]
0052c1dd sub esp, 0xc
0052c1e0 movss xmm3, dword ptr [0xb6a9c8]
0052c1e8 addss xmm0, dword ptr [edi + 0x298]
0052c1f0 mov ecx, dword ptr [esi + 0x18190]
0052c1f6 mov dword ptr [esp + 8], 0x41a00000
0052c1fe mov dword ptr [esp + 4], 0x41a00000
0052c206 mov dword ptr [esp], 0x41a00000
0052c20d push eax
0052c20e lea eax, [esp + 0x28]
0052c212 movss dword ptr [esp + 0x20], xmm0
0052c218 push eax
0052c219 call 0x7cec10
0052c21e movss xmm0, dword ptr [esp + 0x18]
0052c224 movss dword ptr [esp + 0xc], xmm0
0052c22a movss xmm0, dword ptr [esp + 0x1c]
0052c230 movss dword ptr [esp + 0x10], xmm0
0052c236 call 0x6c3d90
0052c23b movd xmm0, eax
0052c23f cvtdq2pd xmm0, xmm0
0052c243 shr eax, 0x1f
0052c246 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052c24f cvtpd2ps xmm0, xmm0
0052c253 mulss xmm0, dword ptr [0xb6a19c]
0052c25b movss dword ptr [esp + 0x3c], xmm0
0052c261 call 0x6c3d90
0052c266 push 0
0052c268 push 1
0052c26a push ecx
0052c26b movd xmm0, eax
0052c26f cvtdq2pd xmm0, xmm0
0052c273 shr eax, 0x1f
0052c276 mov ecx, dword ptr [esi + 0x18190]
0052c27c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052c285 mov dword ptr [esp], 0
0052c28c lea eax, [esp + 0x18]
0052c290 push eax
0052c291 lea eax, [esp + 0x58]
0052c295 push eax
0052c296 cvtpd2ps xmm0, xmm0
0052c29a mulss xmm0, dword ptr [0xb6a19c]
0052c2a2 mulss xmm0, dword ptr [0xb6a874]
0052c2aa addss xmm0, xmm0
0052c2ae movss dword ptr [esp + 0x28], xmm0
0052c2b4 call 0x7cf240
0052c2b9 movss xmm0, dword ptr [esp + 0x14]
0052c2bf mov esi, eax
0052c2c1 call 0x411fe0
0052c2c6 mulss xmm0, dword ptr [0xb6a9ac]
0052c2ce mulss xmm0, dword ptr [esp + 0x3c]
0052c2d4 addss xmm0, dword ptr [esi]
0052c2d8 movss dword ptr [esp + 0x2c], xmm0
0052c2de movss xmm0, dword ptr [esp + 0x14]
0052c2e4 call 0x412010
0052c2e9 mulss xmm0, dword ptr [0xb6a9ac]
0052c2f1 lea eax, [esp + 0xc]
0052c2f5 mov ecx, dword ptr [0xbfd65c]
0052c2fb movss xmm1, dword ptr [esp + 0x2c]
0052c301 push eax
0052c302 mulss xmm0, dword ptr [esp + 0x40]
0052c308 movss dword ptr [esp + 0x10], xmm1
0052c30e addss xmm0, dword ptr [esi + 4]
0052c313 movss dword ptr [esp + 0x38], xmm0
0052c319 movss dword ptr [esp + 0x14], xmm0
0052c31f call 0x6d5e30
0052c324 movss xmm2, dword ptr [esp + 0x2c]
0052c32a movss xmm1, dword ptr [esp + 0x34]
0052c330 movaps xmm0, xmm2
0052c333 movaps xmm3, xmm1
0052c336 subss xmm3, dword ptr [eax + 0x298]
0052c33e subss xmm0, dword ptr [eax + 0x294]
0052c346 mulss xmm3, xmm3
0052c34a mulss xmm0, xmm0
0052c34e addss xmm3, xmm0
0052c352 comiss xmm3, dword ptr [0xb6ad38]
0052c359 jbe 0x52c36d
0052c35b cmp ebx, 2
0052c35e jb 0x52c3ad
0052c360 movss xmm0, dword ptr [0xb6ada0]
0052c368 comiss xmm0, xmm3
0052c36b ja 0x52c3ad
0052c36d inc ebx
0052c36e cmp ebx, 0xa
0052c371 jl 0x52c137
0052c377 lea eax, [esp + 0x48]
0052c37b push eax
0052c37c call 0x659290
0052c381 add esp, 4
0052c384 movss xmm1, dword ptr [eax + 4]
0052c389 movss xmm2, dword ptr [eax]
0052c38d mulss xmm1, dword ptr [0xb6a9f4]
0052c395 mulss xmm2, dword ptr [0xb6a9f4]
0052c39d addss xmm1, dword ptr [edi + 0x298]
0052c3a5 addss xmm2, dword ptr [edi + 0x294]
0052c3ad mov ebx, dword ptr [esp + 0x50]
0052c3b1 movss dword ptr [ebx + 0x28c], xmm2
0052c3b9 push 1
0052c3bb lea edx, [ebx + 0x28c]
0052c3c1 lea ecx, [ebx + 0x294]
0052c3c7 mov esi, edx
0052c3c9 mov eax, ecx
0052c3cb movss dword ptr [esi + 4], xmm1
0052c3d0 movss dword ptr [ecx], xmm2
0052c3d4 mov ecx, ebx
0052c3d6 movss dword ptr [eax + 4], xmm1
0052c3db mov dword ptr [ebx + 0xab4], 8
0052c3e5 mov byte ptr [ebx + 0x169], 1
0052c3ec call 0x6971a0
0052c3f1 mov dword ptr [ebx + 0xb14], 0
0052c3fb lea ebx, [edi + 0x3c]
0052c3fe push 0xb400ac
0052c403 mov ecx, ebx
0052c405 call 0x4060f0
0052c40a test al, al
0052c40c je 0x52cec0
0052c412 mov ecx, edi
0052c414 call 0x695680
0052c419 mov esi, eax
0052c41b movss xmm0, dword ptr [esi + 0x2bc]
0052c423 mulss xmm0, dword ptr [0xb6a974]
0052c42b movss xmm1, dword ptr [esi + 0x2b8]
0052c433 mulss xmm1, dword ptr [0xb6a974]
0052c43b movaps xmm2, xmm0
0052c43e movss dword ptr [esp + 0x20], xmm0
0052c444 mulss xmm2, xmm0
0052c448 movss dword ptr [esp + 0x1c], xmm0
0052c44e movaps xmm0, xmm1
0052c451 mulss xmm0, xmm1
0052c455 movss dword ptr [esp + 0x24], xmm1
0052c45b movss dword ptr [esp + 0x18], xmm1
0052c461 addss xmm2, xmm0
0052c465 movss xmm0, dword ptr [0xb6a940]
0052c46d movss dword ptr [esp + 0x14], xmm0
0052c473 comiss xmm2, dword ptr [0xb6aafc]
0052c47a movss dword ptr [esp + 0x34], xmm2
0052c480 jbe 0x52c52b
0052c486 mov eax, dword ptr [esi + 0x294]
0052c48c mov ecx, dword ptr [esi + 0x298]
0052c492 mov dword ptr [esp + 0x40], eax
0052c496 lea eax, [esp + 0x18]
0052c49a push eax
0052c49b mov dword ptr [esp + 0x48], ecx
0052c49f lea eax, [esp + 0x44]
0052c4a3 mov ecx, dword ptr [0xbfd65c]
0052c4a9 push eax
0052c4aa lea eax, [esp + 0x50]
0052c4ae push eax
0052c4af mov ecx, dword ptr [ecx + 0x18190]
0052c4b5 call 0x7af200
0052c4ba movss xmm1, dword ptr [eax]
0052c4be movss xmm0, dword ptr [eax + 4]
0052c4c3 subss xmm0, dword ptr [esi + 0x298]
0052c4cb subss xmm1, dword ptr [esi + 0x294]
0052c4d3 mulss xmm0, xmm0
0052c4d7 mulss xmm1, xmm1
0052c4db addss xmm0, xmm1
0052c4df call 0x4228c0
0052c4e4 subss xmm0, dword ptr [0xb6a940]
0052c4ec movss dword ptr [esp + 0x30], xmm0
0052c4f2 movss xmm0, dword ptr [esp + 0x34]
0052c4f8 call 0x4228c0
0052c4fd movss xmm1, dword ptr [esp + 0x30]
0052c503 comiss xmm0, xmm1
0052c506 jbe 0x52c52b
0052c508 divss xmm1, xmm0
0052c50c movaps xmm0, xmm1
0052c50f mulss xmm0, dword ptr [esp + 0x24]
0052c515 movss dword ptr [esp + 0x24], xmm0
0052c51b movss xmm0, dword ptr [esp + 0x20]
0052c521 mulss xmm0, xmm1
0052c525 movss dword ptr [esp + 0x20], xmm0
0052c52b mov ecx, edi
0052c52d call 0x695680
0052c532 movss xmm0, dword ptr [esi + 0x294]
0052c53a sub esp, 0xc
0052c53d movss xmm1, dword ptr [esi + 0x298]
0052c545 addss xmm0, dword ptr [esp + 0x30]
0052c54b mov ecx, dword ptr [eax + 0x294]
0052c551 mov eax, dword ptr [eax + 0x298]
0052c557 addss xmm1, dword ptr [esp + 0x2c]
0052c55d movss xmm3, dword ptr [0xb6a9c8]
0052c565 mov dword ptr [esp + 8], 0x41a00000
0052c56d mov dword ptr [esp + 0x68], ecx
0052c571 mov ecx, dword ptr [0xbfd65c]
0052c577 mov dword ptr [esp + 0x6c], eax
0052c57b lea eax, [esp + 0x24]
0052c57f mov dword ptr [esp + 4], 0x41a00000
0052c587 mov dword ptr [esp], 0x41a00000
0052c58e mov ecx, dword ptr [ecx + 0x18190]
0052c594 push eax
0052c595 lea eax, [esp + 0x1c]
0052c599 movss dword ptr [esp + 0x28], xmm0
0052c59f push eax
0052c5a0 movss dword ptr [esp + 0x30], xmm1
0052c5a6 call 0x7cec10
0052c5ab mov ebx, dword ptr [edi + 0xe6c]
0052c5b1 cmp ebx, -1
0052c5b4 je 0x52c5e5
0052c5b6 lea eax, [esp + 0x48]
0052c5ba mov ecx, edi
0052c5bc push eax
0052c5bd call 0x6afac0
0052c5c2 movss xmm0, dword ptr [eax]
0052c5c6 movss xmm1, dword ptr [eax + 4]
0052c5cb movss dword ptr [esp + 0xc], xmm0
0052c5d1 movss dword ptr [esp + 0x10], xmm1
0052c5d7 movss dword ptr [esp + 0x5c], xmm0
0052c5dd movss dword ptr [esp + 0x60], xmm1
0052c5e3 jmp 0x52c5f1
0052c5e5 movss xmm1, dword ptr [esp + 0x10]
0052c5eb movss xmm0, dword ptr [esp + 0xc]
0052c5f1 subss xmm0, dword ptr [edi + 0x294]
0052c5f9 subss xmm1, dword ptr [edi + 0x298]
0052c601 lea esi, [edi + 0x294]
0052c607 mov ecx, edi
0052c609 push 0
0052c60b push 0x1000a00
0052c610 movss dword ptr [esp + 0x3c], xmm0
0052c616 movss dword ptr [esp + 0x40], xmm1
0052c61c call 0x4122f0
0052c621 test al, al
0052c623 jne 0x52cec0
0052c629 mov eax, dword ptr [edi + 0x28]
0052c62c cmp eax, 0xff
0052c631 jne 0x52c692
0052c633 lea ecx, [esp + 0xa0]
0052c63a call 0x430d70
0052c63f mov eax, dword ptr [esp + 0xfc]
0052c646 movss xmm0, dword ptr [esi]
0052c64a or dword ptr [esp + 0xf8], 0x800
0052c655 mov dword ptr [esp + 0xfc], eax
0052c65c lea eax, [esp + 0xa0]
0052c663 movss dword ptr [esp + 0x108], xmm0
0052c66c movss xmm0, dword ptr [esi + 4]
0052c671 push eax
0052c672 movss dword ptr [esp + 0x110], xmm0
0052c67b mov dword ptr [esp + 0x1c], 0x41200000
0052c683 mov dword ptr [esp + 0x20], 0x40a00000
0052c68b push 6
0052c68d jmp 0x52c99d
0052c692 cmp eax, 0x114
0052c697 jne 0x52c7a0
0052c69d lea ecx, [esp + 0xa0]
0052c6a4 call 0x430d70
0052c6a9 push eax
0052c6aa push ecx
0052c6ab mov dword ptr [esp], 0x41200000
0052c6b2 lea eax, [esp + 0x64]
0052c6b6 push eax
0052c6b7 push 1
0052c6b9 mov ecx, edi
0052c6bb call 0x6a3420
0052c6c0 mov edx, eax
0052c6c2 lea ecx, [esp + 0x74]
0052c6c6 movss xmm0, dword ptr [edx + 0x368]
0052c6ce subss xmm0, dword ptr [0xb6a3b0]
0052c6d6 movss xmm2, dword ptr [edx + 0x2b8]
0052c6de movss xmm3, dword ptr [edx + 0x2bc]
0052c6e6 mulss xmm2, dword ptr [0xb6a4a0]
0052c6ee mov eax, dword ptr [edx + 0x38c]
0052c6f4 mulss xmm3, dword ptr [0xb6a4a0]
0052c6fc or dword ptr [edx + 0x388], 2
0052c703 movss dword ptr [edx + 0x368], xmm0
0052c70b movss xmm0, dword ptr [edx + 0x364]
0052c713 mulss xmm0, dword ptr [0xb6a50c]
0052c71b mov dword ptr [edx + 0x38c], eax
0052c721 mov dword ptr [edx + 0x370], 0x3fcccccd
0052c72b subss xmm0, dword ptr [0xb6a994]
0052c733 movss dword ptr [edx + 0x364], xmm0
0052c73b movss xmm0, dword ptr [edx + 0x360]
0052c743 subss xmm0, dword ptr [0xb6a9c8]
0052c74b movss dword ptr [edx + 0x360], xmm0
0052c753 movss xmm0, dword ptr [0xb6a614]
0052c75b movss dword ptr [edx + 0x2b8], xmm2
0052c763 movaps xmm1, xmm0
0052c766 movss dword ptr [edx + 0x2bc], xmm3
0052c76e movaps xmm2, xmm0
0052c771 movaps xmm3, xmm0
0052c774 call 0x427080
0052c779 movaps xmm0, xmmword ptr [0xb6c330]
0052c780 push 1
0052c782 push 0
0052c784 push 0xff
0052c789 movups xmmword ptr [esp + 0x90], xmm0
0052c791 mov eax, dword ptr [edx]
0052c793 push -1
0052c795 push ecx
0052c796 mov ecx, edx
0052c798 call dword ptr [eax + 0x38]
0052c79b jmp 0x52c9aa
0052c7a0 cmp eax, 0x121
0052c7a5 jne 0x52c8a0
0052c7ab cmp ebx, -1
0052c7ae jne 0x52c7cf
0052c7b0 mov eax, dword ptr [0xbfd65c]
0052c7b5 push esi
0052c7b6 mov ecx, dword ptr [eax + 0x18190]
0052c7bc mov ecx, dword ptr [ecx + 0x11f8]
0052c7c2 call 0x89fbb0
0052c7c7 test al, al
0052c7c9 je 0x52cec0
0052c7cf mov ecx, dword ptr [0xbfd65c]
0052c7d5 lea eax, [esp + 0xc]
0052c7d9 push 0
0052c7db push 0
0052c7dd push 0
0052c7df mov ecx, dword ptr [ecx + 0x18190]
0052c7e5 push 0x3e7
0052c7ea push 3
0052c7ec push eax
0052c7ed push esi
0052c7ee call 0x7af4b0
0052c7f3 mov bl, al
0052c7f5 call 0x6c3d90
0052c7fa xor edx, edx
0052c7fc mov ecx, 0x64
0052c801 div ecx
0052c803 cmp edx, 0x4b
0052c806 jb 0x52c80c
0052c808 test bl, bl
0052c80a jne 0x52c853
0052c80c mov ecx, edi
0052c80e call 0x6ad7a0
0052c813 cmp eax, 7
0052c816 jge 0x52c853
0052c818 call 0x6c3d90
0052c81d mov ecx, dword ptr [0xbfd65c]
0052c823 push 0
0052c825 push eax
0052c826 push 0
0052c828 push edi
0052c829 push 0xc02fec
0052c82e push esi
0052c82f push 0
0052c831 push 0x100
0052c836 call 0x6d0ca0
0052c83b mov ecx, dword ptr [eax + 0x164]
0052c841 and dword ptr [eax + 0x160], 0xfffffffb
0052c848 mov dword ptr [eax + 0x164], ecx
0052c84e jmp 0x52c9aa
0052c853 cmp dword ptr [edi + 0x28], 0x121
0052c85a je 0x52c86a
0052c85c movss xmm2, dword ptr [0xb6a974]
0052c864 movss dword ptr [esp + 0x14], xmm2
0052c86a lea ecx, [esp + 0xa0]
0052c871 call 0x430d70
0052c876 movss xmm0, dword ptr [esp + 0x14]
0052c87c push eax
0052c87d push ecx
0052c87e movss dword ptr [esp], xmm0
0052c883 lea eax, [esp + 0x64]
0052c887 push eax
0052c888 push 1
0052c88a mov ecx, edi
0052c88c call 0x6a3420
0052c891 mov dword ptr [eax + 0x370], 0x3f800000
0052c89b jmp 0x52c9aa
0052c8a0 cmp eax, 0xf4
0052c8a5 jne 0x52c92b
0052c8ab cmp dword ptr [edi + 0x2c], 2
0052c8af jne 0x52c92b
0052c8b5 cmp dword ptr [edi + 0x30], 0
0052c8b9 jne 0x52c92b
0052c8bf lea ecx, [esp + 0xa0]
0052c8c6 call 0x430d70
0052c8cb lea eax, [esp + 0x48]
0052c8cf mov dword ptr [esp + 0xf8], 0
0052c8da push eax
0052c8db lea ecx, [esp + 0x38]
0052c8df mov dword ptr [esp + 0x100], 0x40
0052c8ea mov dword ptr [esp + 0xb8], 0x40000000
0052c8f5 call 0x962560
0052c8fa movss xmm1, dword ptr [eax + 4]
0052c8ff movss xmm0, dword ptr [eax]
0052c903 lea eax, [esp + 0xa0]
0052c90a mulss xmm1, dword ptr [0xb6a974]
0052c912 mulss xmm0, dword ptr [0xb6a974]
0052c91a movss dword ptr [esp + 0x1c], xmm1
0052c920 movss dword ptr [esp + 0x18], xmm0
0052c926 jmp 0x52c99a
0052c92b cmp ebx, -1
0052c92e jne 0x52c95b
0052c930 push 0
0052c932 push 0
0052c934 push 0
0052c936 push 0x3e7
0052c93b push 3
0052c93d lea eax, [esp + 0x20]
0052c941 push eax
0052c942 mov eax, dword ptr [0xbfd65c]
0052c947 push esi
0052c948 mov ecx, dword ptr [eax + 0x18190]
0052c94e call 0x7af4b0
0052c953 test al, al
0052c955 je 0x52cec0
0052c95b lea eax, [esp + 0x48]
0052c95f push eax
0052c960 lea ecx, [esp + 0x38]
0052c964 call 0x962560
0052c969 lea ecx, [esp + 0xa0]
0052c970 movss xmm1, dword ptr [eax + 4]
0052c975 movss xmm0, dword ptr [eax]
0052c979 mulss xmm0, dword ptr [0xb6a974]
0052c981 mulss xmm1, dword ptr [0xb6a974]
0052c989 movss dword ptr [esp + 0x18], xmm0
0052c98f movss dword ptr [esp + 0x1c], xmm1
0052c995 call 0x430d70
0052c99a push eax
0052c99b push 0
0052c99d lea eax, [esp + 0x20]
0052c9a1 mov ecx, edi
0052c9a3 push eax
0052c9a4 push esi
0052c9a5 call 0x6a1a20
0052c9aa push ecx
0052c9ab mov dword ptr [esp], 0x3f800000
0052c9b2 push 0
0052c9b4 push 2
0052c9b6 push ecx
0052c9b7 mov dword ptr [esp], 0x3f800000
0052c9be mov ecx, edi
0052c9c0 push 0x13e
0052c9c5 call 0x6ad720
0052c9ca jmp 0x52cec0
0052c9cf push 0xb4337c
0052c9d4 mov ecx, ebx
0052c9d6 call 0x4060f0
0052c9db test al, al
0052c9dd je 0x52ca13
0052c9df cmp dword ptr [edi + 0xe6c], -1
0052c9e6 jne 0x52ca13
0052c9e8 lea eax, [edi + 0x294]
0052c9ee push eax
0052c9ef mov eax, dword ptr [0xbfd65c]
0052c9f4 mov ecx, dword ptr [eax + 0x18190]
0052c9fa mov ecx, dword ptr [ecx + 0x11f8]
0052ca00 call 0x89fbb0
0052ca05 test al, al
0052ca07 jne 0x52ca13
0052ca09 mov dword ptr [edi + 0xab4], 6
0052ca13 push 0xb400ac
0052ca18 mov ecx, ebx
0052ca1a call 0x4060f0
0052ca1f test al, al
0052ca21 je 0x52ca5a
0052ca23 cmp dword ptr [edi + 0x2c], 3
0052ca27 mov ecx, 0xa
0052ca2c push ecx
0052ca2d mov eax, 1
0052ca32 cmovne eax, ecx
0052ca35 mov dword ptr [edi + 0xb10], eax
0052ca3b mov dword ptr [esp], 0x3f800000
0052ca42 push 0
0052ca44 push 2
0052ca46 push ecx
0052ca47 mov dword ptr [esp], 0x3f800000
0052ca4e mov ecx, edi
0052ca50 push 0x13e
0052ca55 call 0x6ad720
0052ca5a mov eax, dword ptr [edi + 0xb10]
0052ca60 test eax, eax
0052ca62 jle 0x52cea7
0052ca68 movss xmm0, dword ptr [0xb6aa0c]
0052ca70 dec eax
0052ca71 mov dword ptr [edi + 0xb10], eax
0052ca77 cmp dword ptr [edi + 0x2c], 3
0052ca7b movss dword ptr [esp + 0x14], xmm0
0052ca81 jne 0x52ca91
0052ca83 movss xmm0, dword ptr [0xb6aad4]
0052ca8b movss dword ptr [esp + 0x14], xmm0
0052ca91 mov ecx, edi
0052ca93 call 0x695680
0052ca98 mov esi, eax
0052ca9a call 0x6c3d90
0052ca9f movss xmm1, dword ptr [esi + 0x294]
0052caa7 lea ebx, [edi + 0x294]
0052caad subss xmm1, dword ptr [ebx]
0052cab1 movd xmm0, eax
0052cab5 cvtdq2pd xmm0, xmm0
0052cab9 shr eax, 0x1f
0052cabc mulss xmm1, xmm1
0052cac0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052cac9 cvtpd2ps xmm0, xmm0
0052cacd mulss xmm0, dword ptr [0xb6a19c]
0052cad5 movss dword ptr [esp + 0x30], xmm0
0052cadb movss xmm0, dword ptr [esi + 0x298]
0052cae3 subss xmm0, dword ptr [ebx + 4]
0052cae8 mulss xmm0, xmm0
0052caec addss xmm0, xmm1
0052caf0 call 0x4228c0
0052caf5 lea eax, [esp + 0x48]
0052caf9 movss dword ptr [esp + 0x34], xmm0
0052caff push eax
0052cb00 call 0x659290
0052cb05 movss xmm1, dword ptr [esi + 0x2b8]
0052cb0d movss xmm2, dword ptr [esi + 0x2bc]
0052cb15 mulss xmm1, dword ptr [0xb6a350]
0052cb1d mov ecx, dword ptr [0xbfd65c]
0052cb23 mulss xmm2, dword ptr [0xb6a350]
0052cb2b mov dword ptr [esp], 0x40800000
0052cb32 sub esp, 8
0052cb35 movss xmm0, dword ptr [eax]
0052cb39 mulss xmm1, dword ptr [esp + 0x40]
0052cb3f mov ecx, dword ptr [ecx + 0x18190]
0052cb45 mulss xmm2, dword ptr [esp + 0x40]
0052cb4b mov dword ptr [esp + 4], 0x40800000
0052cb53 addss xmm1, dword ptr [esi + 0x294]
0052cb5b movss xmm3, dword ptr [0xb6a8cc]
0052cb63 addss xmm2, dword ptr [esi + 0x298]
0052cb6b movss dword ptr [esp + 0x34], xmm0
0052cb71 movss xmm0, dword ptr [eax + 4]
0052cb76 lea eax, [esp + 0x24]
0052cb7a mov dword ptr [esp], 0x40800000
0052cb81 push eax
0052cb82 lea eax, [esp + 0x50]
0052cb86 movss dword ptr [esp + 0x64], xmm0
0052cb8c push eax
0052cb8d movss dword ptr [esp + 0x2c], xmm1
0052cb93 movss dword ptr [esp + 0x30], xmm2
0052cb99 call 0x7cec10
0052cb9e cmp dword ptr [edi + 0xe6c], -1
0052cba5 movss xmm1, dword ptr [esp + 0x30]
0052cbab movss xmm2, dword ptr [esp + 0x54]
0052cbb1 mulss xmm1, dword ptr [esp + 0x28]
0052cbb7 mulss xmm2, dword ptr [esp + 0x30]
0052cbbd mulss xmm1, dword ptr [esp + 0x14]
0052cbc3 mulss xmm2, dword ptr [esp + 0x14]
0052cbc9 addss xmm1, dword ptr [esp + 0x40]
0052cbcf addss xmm2, dword ptr [esp + 0x44]
0052cbd5 je 0x52cbec
0052cbd7 lea eax, [esp + 0x48]
0052cbdb mov ecx, edi
0052cbdd push eax
0052cbde call 0x6afac0
0052cbe3 movss xmm1, dword ptr [eax]
0052cbe7 movss xmm2, dword ptr [eax + 4]
0052cbec subss xmm1, dword ptr [ebx]
0052cbf0 subss xmm2, dword ptr [ebx + 4]
0052cbf5 lea ecx, [esp + 0xa0]
0052cbfc mulss xmm1, dword ptr [0xb6a244]
0052cc04 mulss xmm2, dword ptr [0xb6a244]
0052cc0c movss dword ptr [esp + 0x64], xmm1
0052cc12 movss dword ptr [esp + 0x68], xmm2
0052cc18 call 0x430d70
0052cc1d call 0x6c3d90
0052cc22 movss xmm1, dword ptr [0xb6a19c]
0052cc2a xorps xmm0, xmm0
0052cc2d cvtsi2sd xmm0, eax
0052cc31 shr eax, 0x1f
0052cc34 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052cc3d cvtpd2ps xmm0, xmm0
0052cc41 mulss xmm0, xmm1
0052cc45 mulss xmm0, dword ptr [0xb6a9ec]
0052cc4d movss dword ptr [esp + 0xa4], xmm0
0052cc56 call 0x6c3d90
0052cc5b xorps xmm0, xmm0
0052cc5e mov dword ptr [esp + 0xac], 0x3fc00000
0052cc69 cvtsi2sd xmm0, eax
0052cc6d shr eax, 0x1f
0052cc70 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052cc79 cvtpd2ps xmm0, xmm0
0052cc7d mulss xmm0, xmm1
0052cc81 mulss xmm0, dword ptr [0xb6a940]
0052cc89 subss xmm0, dword ptr [0xb6aa7c]
0052cc91 movss dword ptr [esp + 0xa8], xmm0
0052cc9a call 0x6c3d90
0052cc9f xorps xmm0, xmm0
0052cca2 cvtsi2sd xmm0, eax
0052cca6 shr eax, 0x1f
0052cca9 cmp dword ptr [edi + 0x2c], 3
0052ccad addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052ccb6 cvtpd2ps xmm0, xmm0
0052ccba mulss xmm0, xmm1
0052ccbe addss xmm0, dword ptr [0xb6a480]
0052ccc6 movss dword ptr [esp + 0xb4], xmm0
0052cccf jne 0x52cd6d
0052ccd5 movaps xmm0, xmmword ptr [0xb6c330]
0052ccdc mov dword ptr [esp + 0xf8], 2
0052cce7 mov dword ptr [esp + 0xfc], 0
0052ccf2 mov dword ptr [esp + 0xb4], 0x3fcccccd
0052ccfd movups xmmword ptr [esp + 0xdc], xmm0
0052cd05 mov dword ptr [esp + 0x18], 0
0052cd0d call 0x6c3d90
0052cd12 mov edx, ebx
0052cd14 mov dword ptr [esp + 0x40], 0
0052cd1c mov ecx, 2
0052cd21 mov dword ptr [esp + 0x44], 0xc1f00000
0052cd29 movd xmm0, eax
0052cd2d cvtdq2pd xmm0, xmm0
0052cd31 shr eax, 0x1f
0052cd34 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052cd3d lea eax, [esp + 0x18]
0052cd41 push eax
0052cd42 lea eax, [esp + 0xd0]
0052cd49 push eax
0052cd4a cvtpd2ps xmm0, xmm0
0052cd4e lea eax, [esp + 0x48]
0052cd52 push eax
0052cd53 mulss xmm0, xmm1
0052cd57 mulss xmm0, dword ptr [0xb6ae6c]
0052cd5f movss dword ptr [esp + 0x28], xmm0
0052cd65 call 0x6aead0
0052cd6a add esp, 0xc
0052cd6d lea eax, [esp + 0xa0]
0052cd74 mov ecx, edi
0052cd76 push eax
0052cd77 push 0
0052cd79 lea eax, [esp + 0x6c]
0052cd7d push eax
0052cd7e push ebx
0052cd7f call 0x6a1a20
0052cd84 mov eax, dword ptr [edi + 0xb10]
0052cd8a mov ecx, 6
0052cd8f cdq
0052cd90 idiv ecx
0052cd92 test edx, edx
0052cd94 jne 0x52cea7
0052cd9a cmp dword ptr [edi + 0x2c], 3
0052cd9e je 0x52cea7
0052cda4 mov dword ptr [esp + 0x18], edx
0052cda8 call 0x6c3d90
0052cdad lea ecx, [esp + 0x74]
0052cdb1 mov dword ptr [esp + 0x40], 0
0052cdb9 mov dword ptr [esp + 0x44], 0xc1f00000
0052cdc1 movd xmm0, eax
0052cdc5 cvtdq2pd xmm0, xmm0
0052cdc9 shr eax, 0x1f
0052cdcc addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052cdd5 lea eax, [esp + 0x18]
0052cdd9 push eax
0052cdda cvtpd2ps xmm0, xmm0
0052cdde mulss xmm0, dword ptr [0xb6a19c]
0052cde6 mulss xmm0, dword ptr [0xb6ae6c]
0052cdee movss dword ptr [esp + 0x20], xmm0
0052cdf4 call 0x402120
0052cdf9 push eax
0052cdfa lea eax, [esp + 0x48]
0052cdfe mov edx, ebx
0052ce00 push eax
0052ce01 mov ecx, 1
0052ce06 call 0x6aead0
0052ce0b add esp, 0xc
0052ce0e mov esi, eax
0052ce10 call 0x6c3d90
0052ce15 movd xmm0, eax
0052ce19 cvtdq2pd xmm0, xmm0
0052ce1d shr eax, 0x1f
0052ce20 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052ce29 cvtpd2ps xmm0, xmm0
0052ce2d mulss xmm0, dword ptr [0xb6a19c]
0052ce35 mulss xmm0, dword ptr [0xb6ac40]
0052ce3d movss dword ptr [esi + 0xe0], xmm0
0052ce45 call 0x6c3d90
0052ce4a movd xmm0, eax
0052ce4e cvtdq2pd xmm0, xmm0
0052ce52 shr eax, 0x1f
0052ce55 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052ce5e cvtpd2ps xmm1, xmm0
0052ce62 mulss xmm1, dword ptr [0xb6a19c]
0052ce6a mulss xmm1, dword ptr [0xb6a434]
0052ce72 addss xmm1, dword ptr [0xb6a560]
0052ce7a movaps xmm0, xmm1
0052ce7d mulss xmm1, dword ptr [0xbc7a2c]
0052ce85 mulss xmm0, dword ptr [0xbc7a28]
0052ce8d mov dword ptr [esi + 0x2ac], 0x64
0052ce97 movss dword ptr [esi + 0xdc], xmm1
0052ce9f movss dword ptr [esi + 0xd8], xmm0
0052cea7 cmp dword ptr [edi + 0x70], 0
0052ceab je 0x52ceb6
0052cead cmp byte ptr [edi + 0x80], 0
0052ceb4 jne 0x52cec0
0052ceb6 mov dword ptr [edi + 0xab4], 6
0052cec0 cmp dword ptr [edi + 0x28], 0x114
0052cec7 jne 0x52cf83
0052cecd movss xmm0, dword ptr [edi + 0x7c]
0052ced2 ucomiss xmm0, dword ptr [0xb6a18c]
0052ced9 lahf
0052ceda test ah, 0x44
0052cedd jp 0x52cf83
0052cee3 call 0x6c3d90
0052cee8 mov ecx, dword ptr [0xbfd65c]
0052ceee push 0
0052cef0 push eax
0052cef1 push 0
0052cef3 push edi
0052cef4 push 0xc02fec
0052cef9 lea eax, [edi + 0x294]
0052ceff push eax
0052cf00 push 0x3d
0052cf02 push 0x3e8
0052cf07 call 0x6d0ca0
0052cf0c mov esi, eax
0052cf0e mov ecx, dword ptr [esi + 0x314]
0052cf14 lea ebx, [esi + 0x314]
0052cf1a test ecx, ecx
0052cf1c je 0x52cf32
0052cf1e lea eax, [esp + 0x34]
0052cf22 mov dword ptr [esp + 0x34], ebx
0052cf26 push eax
0052cf27 add ecx, 0x324
0052cf2d call 0x4bc3c0
0052cf32 push ebx
0052cf33 mov ecx, edi
0052cf35 mov dword ptr [ebx], edi
0052cf37 call 0x4bae70
0052cf3c mov eax, dword ptr [edi + 0x2c8]
0052cf42 push ecx
0052cf43 mov dword ptr [esp], 0x3f800000
0052cf4a push 0
0052cf4c push 2
0052cf4e push ecx
0052cf4f mov dword ptr [esp], 0x3f800000
0052cf56 mov ecx, edi
0052cf58 push 0x34
0052cf5a mov dword ptr [esi + 0x3a4], eax
0052cf60 mov dword ptr [esi + 0x3a8], 0x42480000
0052cf6a mov dword ptr [esi + 0x3ac], 5
0052cf74 mov dword ptr [esi + 0x3b0], 5
0052cf7e call 0x6ad720
0052cf83 cmp dword ptr [edi + 0x70], 0
0052cf87 je 0x52cf92
0052cf89 cmp byte ptr [edi + 0x80], 0
0052cf90 jne 0x52cfb5
0052cf92 cmp dword ptr [edi + 0x28], 0xf4
0052cf99 mov dword ptr [edi + 0xab4], 6
0052cfa3 jne 0x52cfb5
0052cfa5 cmp dword ptr [edi + 0x2c], 2
0052cfa9 jne 0x52cfb5
0052cfab mov dword ptr [edi + 0x360], 0x2d
0052cfb5 movss xmm1, dword ptr [edi + 0x28c]
0052cfbd ucomiss xmm1, dword ptr [0xc02fec]
0052cfc4 lahf
0052cfc5 test ah, 0x44
0052cfc8 jp 0x52cfdf
0052cfca movss xmm0, dword ptr [edi + 0x290]
0052cfd2 ucomiss xmm0, dword ptr [0xc02ff0]
0052cfd9 lahf
0052cfda test ah, 0x44
0052cfdd jnp 0x52d007
0052cfdf movss xmm0, dword ptr [edi + 0x290]
0052cfe7 subss xmm1, dword ptr [edi + 0x294]
0052cfef subss xmm0, dword ptr [edi + 0x298]
0052cff7 movss dword ptr [edi + 0x2b8], xmm1
0052cfff movss dword ptr [edi + 0x2bc], xmm0
0052d007 movss xmm0, dword ptr [edi + 0x2c4]
0052d00f mulss xmm0, dword ptr [0xb6a560]
0052d017 movss dword ptr [edi + 0x2c4], xmm0
0052d01f mov ecx, dword ptr [esp + 0x14c]
0052d026 pop edi
0052d027 pop esi
0052d028 pop ebx
0052d029 xor ecx, esp
0052d02b call 0x9eacd7
0052d030 mov esp, ebp
0052d032 pop ebp
0052d033 ret
