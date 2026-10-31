; Bounded installed-binary disassembly; field names require separate verification.
004f4e30 push ebp
004f4e31 mov ebp, esp
004f4e33 and esp, 0xfffffff8
004f4e36 sub esp, 0x1e0
004f4e3c mov eax, dword ptr [0xbaa3b4]
004f4e41 xor eax, esp
004f4e43 mov dword ptr [esp + 0x1dc], eax
004f4e4a push esi
004f4e4b mov esi, ecx
004f4e4d push edi
004f4e4e mov dword ptr [esp + 0x24], esi
004f4e52 cmp dword ptr [esi + 0x28], 0x3d
004f4e56 jne 0x4f4e9c
004f4e58 mov eax, dword ptr [esi + 0x2c]
004f4e5b cmp eax, 5
004f4e5e je 0x4f4e83
004f4e60 cmp eax, 6
004f4e63 je 0x4f4e83
004f4e65 cmp eax, 4
004f4e68 jne 0x4f4e9c
004f4e6a call 0x4ca880
004f4e6f pop edi
004f4e70 pop esi
004f4e71 mov ecx, dword ptr [esp + 0x1dc]
004f4e78 xor ecx, esp
004f4e7a call 0x9eacd7
004f4e7f mov esp, ebp
004f4e81 pop ebp
004f4e82 ret
004f4e83 call 0x5386a0
004f4e88 pop edi
004f4e89 pop esi
004f4e8a mov ecx, dword ptr [esp + 0x1dc]
004f4e91 xor ecx, esp
004f4e93 call 0x9eacd7
004f4e98 mov esp, ebp
004f4e9a pop ebp
004f4e9b ret
004f4e9c cmp dword ptr [esi + 0xab4], 0
004f4ea3 jne 0x4f4ff6
004f4ea9 mov dword ptr [esi + 0x17c], 3
004f4eb3 movss xmm0, dword ptr [0xc02fec]
004f4ebb movss dword ptr [esi + 0xb08], xmm0
004f4ec3 movss xmm0, dword ptr [0xc02ff0]
004f4ecb movss dword ptr [esi + 0xb0c], xmm0
004f4ed3 mov eax, dword ptr [esi + 0x28]
004f4ed6 mov dword ptr [esi + 0xab4], 3
004f4ee0 cmp eax, 0x3d
004f4ee3 jne 0x4f4f76
004f4ee9 mov eax, dword ptr [esi + 0x2c]
004f4eec cmp eax, 1
004f4eef jne 0x4f4f3b
004f4ef1 xorps xmm0, xmm0
004f4ef4 mov dword ptr [esp + 0x84], 0xbe48c8ca
004f4eff movups xmmword ptr [esp + 0x74], xmm0
004f4f04 lea eax, [esp + 0x64]
004f4f08 mov dword ptr [esp + 0x88], 0x3f028283
004f4f13 movaps xmm0, xmmword ptr [0xb6c290]
004f4f1a lea ecx, [esi + 0x1dc]
004f4f20 push eax
004f4f21 movups xmmword ptr [esp + 0x68], xmm0
004f4f26 mov dword ptr [esp + 0x90], 0x3e48c8ca
004f4f31 call 0x4021a0
004f4f36 jmp 0x4f4fec
004f4f3b cmp eax, 3
004f4f3e jne 0x4f4fec
004f4f44 movss xmm3, dword ptr [0xb6a274]
004f4f4c movss xmm1, dword ptr [0xb6a234]
004f4f54 movaps xmm2, xmm3
004f4f57 push ecx
004f4f58 lea ecx, [esp + 0x68]
004f4f5c mov dword ptr [esp], 0x3f800000
004f4f63 call 0x4325d0
004f4f68 push eax
004f4f69 lea ecx, [esi + 0x1dc]
004f4f6f call 0x4021a0
004f4f74 jmp 0x4f4fec
004f4f76 cmp eax, 0x333
004f4f7b jne 0x4f4fec
004f4f7d xorps xmm0, xmm0
004f4f80 mov dword ptr [esp + 0x84], 0x3df0f0f2
004f4f8b movups xmmword ptr [esp + 0x74], xmm0
004f4f90 lea eax, [esp + 0x64]
004f4f94 mov dword ptr [esp + 0x88], 0x3df0f0f2
004f4f9f movaps xmm0, xmmword ptr [0xb6bd30]
004f4fa6 lea ecx, [esi + 0x1dc]
004f4fac push eax
004f4fad movups xmmword ptr [esp + 0x68], xmm0
004f4fb2 mov dword ptr [esp + 0x90], 0x3df0f0f2
004f4fbd call 0x4021a0
004f4fc2 cmp dword ptr [esi + 0x2c], 1
004f4fc6 jne 0x4f4fec
004f4fc8 mov eax, dword ptr [esi + 0x164]
004f4fce or dword ptr [esi + 0x160], 0x11
004f4fd5 mov byte ptr [esi + 0x308], 1
004f4fdc mov dword ptr [esi + 0x17c], 0
004f4fe6 mov dword ptr [esi + 0x164], eax
004f4fec mov dword ptr [esi + 0xb10], 0
004f4ff6 mov ecx, dword ptr [0xbfd65c]
004f4ffc push 1
004f4ffe add ecx, 0x1ba40
004f5004 push ecx
004f5005 push 9
004f5007 call 0x91d340
004f500c test eax, eax
004f500e je 0x4f503a
004f5010 mov eax, dword ptr [esi + 0x160]
004f5016 and eax, 0x20000000
004f501b or eax, 0
004f501e jne 0x4f503a
004f5020 cmp dword ptr [esi + 0x28], 0x12
004f5024 mov byte ptr [esp + 0xb], 1
004f5029 jne 0x4f503f
004f502b push -1
004f502d push eax
004f502e push eax
004f502f push 0xd
004f5031 mov ecx, esi
004f5033 call 0x697c60
004f5038 jmp 0x4f503f
004f503a mov byte ptr [esp + 0xb], 0
004f503f push dword ptr [esi + 0x344]
004f5045 push ecx
004f5046 mov ecx, dword ptr [0xbfd65c]
004f504c add ecx, 0x1ba40
004f5052 call 0x91d7c0
004f5057 mov edi, eax
004f5059 test edi, edi
004f505b je 0x4f51a5
004f5061 cmp byte ptr [esi + 0x16b], 0
004f5068 jne 0x4f51a5
004f506e mov eax, dword ptr [esi + 0x28]
004f5071 cmp eax, 0x12
004f5074 je 0x4f518c
004f507a cmp eax, 0xd
004f507d je 0x4f518c
004f5083 cmp eax, 0xd6
004f5088 je 0x4f518c
004f508e cmp eax, 0xf9
004f5093 je 0x4f518c
004f5099 mov eax, dword ptr [esi]
004f509b mov ecx, esi
004f509d mov eax, dword ptr [eax + 0x48]
004f50a0 call eax
004f50a2 test al, al
004f50a4 jne 0x4f51a5
004f50aa push 0
004f50ac push 0x20000000
004f50b1 mov ecx, esi
004f50b3 call 0x4122f0
004f50b8 test al, al
004f50ba jne 0x4f51a5
004f50c0 mov eax, dword ptr [edi + 0x28]
004f50c3 movss xmm0, dword ptr [edi + 0x294]
004f50cb movss xmm1, dword ptr [edi + 0x298]
004f50d3 mov edx, dword ptr [edi + 0x160]
004f50d9 mov dword ptr [esp + 0x64], eax
004f50dd mov eax, dword ptr [edi + 0x2c]
004f50e0 mov dword ptr [esp + 0x68], eax
004f50e4 mov eax, dword ptr [edi + 0x34]
004f50e7 mov dword ptr [esp + 0x6c], eax
004f50eb mov eax, dword ptr [edi + 0x38]
004f50ee mov dword ptr [esp + 0x70], eax
004f50f2 mov eax, edx
004f50f4 movss dword ptr [esp + 0x74], xmm0
004f50fa and eax, 0x100
004f50ff or eax, 0
004f5102 movss xmm0, dword ptr [edi + 0x2b8]
004f510a movss dword ptr [esp + 0x78], xmm1
004f5110 movss xmm1, dword ptr [edi + 0x2bc]
004f5118 movss dword ptr [esp + 0x7c], xmm0
004f511e movss dword ptr [esp + 0x80], xmm1
004f5127 je 0x4f5130
004f5129 mov ecx, 1
004f512e jmp 0x4f5132
004f5130 xor ecx, ecx
004f5132 and edx, 0x20000000
004f5138 mov dword ptr [esp + 0x20], 2
004f5140 or edx, 0
004f5143 jne 0x4f514d
004f5145 mov dword ptr [esp + 0x20], 0
004f514d mov edx, dword ptr [edi + 0x164]
004f5153 xor eax, eax
004f5155 and edx, 0x400000
004f515b or eax, edx
004f515d je 0x4f5166
004f515f mov eax, 4
004f5164 jmp 0x4f5168
004f5166 xor eax, eax
004f5168 or ecx, dword ptr [esp + 0x20]
004f516c or ecx, eax
004f516e mov dword ptr [esp + 0x88], edi
004f5175 push -1
004f5177 lea eax, [esp + 0x68]
004f517b mov dword ptr [esp + 0x88], ecx
004f5182 push eax
004f5183 mov ecx, esi
004f5185 call 0x685510
004f518a jmp 0x4f51a5
004f518c mov eax, dword ptr [esi]
004f518e mov ecx, esi
004f5190 call dword ptr [eax + 0x28]
004f5193 push 0
004f5195 lea eax, [esi + 0x294]
004f519b mov ecx, edi
004f519d push eax
004f519e push 1
004f51a0 call 0x725cc0
004f51a5 cmp dword ptr [esi + 0x28], 0x3d
004f51a9 jne 0x4f51ca
004f51ab mov eax, dword ptr [esi + 0xe6c]
004f51b1 cmp eax, -1
004f51b4 je 0x4f51ca
004f51b6 push esi
004f51b7 push eax
004f51b8 push 9
004f51ba call 0x8b10b0
004f51bf test al, al
004f51c1 je 0x4f51ca
004f51c3 mov eax, dword ptr [esi]
004f51c5 mov ecx, esi
004f51c7 call dword ptr [eax + 0x24]
004f51ca cmp byte ptr [esi + 0x16b], 0
004f51d1 movss xmm1, dword ptr [0xb6a974]
004f51d9 movss xmm2, dword ptr [0xb6a940]
004f51e1 je 0x4f58ec
004f51e7 mov eax, dword ptr [esi + 0x28]
004f51ea cmp eax, 0x3d
004f51ed jne 0x4f571a
004f51f3 mov eax, dword ptr [esi + 0x2c]
004f51f6 test eax, eax
004f51f8 jne 0x4f522d
004f51fa call 0x6af030
004f51ff test eax, eax
004f5201 jle 0x4f5208
004f5203 movaps xmm0, xmm1
004f5206 jmp 0x4f520b
004f5208 movaps xmm0, xmm2
004f520b lea ecx, [esp + 0x90]
004f5212 movss dword ptr [esp + 0x18], xmm0
004f5218 mov dword ptr [esp + 0x1c], 0
004f5220 call 0x430d70
004f5225 push eax
004f5226 push 6
004f5228 jmp 0x4f5702
004f522d cmp eax, 1
004f5230 jne 0x4f533c
004f5236 mov ecx, esi
004f5238 call 0x695680
004f523d mov ecx, dword ptr [eax + 0x294]
004f5243 mov eax, dword ptr [eax + 0x298]
004f5249 mov dword ptr [esp + 0x18], ecx
004f524d lea ecx, [esp + 0x90]
004f5254 mov dword ptr [esp + 0x1c], eax
004f5258 call 0x430d70
004f525d push eax
004f525e push ecx
004f525f mov dword ptr [esp], 0x41200000
004f5266 lea eax, [esp + 0x20]
004f526a push eax
004f526b push 1
004f526d mov ecx, esi
004f526f call 0x6a3420
004f5274 mov edx, eax
004f5276 movss xmm0, dword ptr [edx + 0x368]
004f527e subss xmm0, dword ptr [0xb6a3b0]
004f5286 movss xmm1, dword ptr [edx + 0x2b8]
004f528e movss xmm2, dword ptr [edx + 0x2bc]
004f5296 mov ecx, dword ptr [edx + 0x38c]
004f529c mulss xmm1, dword ptr [0xb6a4a0]
004f52a4 or dword ptr [edx + 0x388], 2
004f52ab mulss xmm2, dword ptr [0xb6a4a0]
004f52b3 mov dword ptr [edx + 0x38c], ecx
004f52b9 lea ecx, [esp + 0x64]
004f52bd movss dword ptr [edx + 0x368], xmm0
004f52c5 movss xmm0, dword ptr [edx + 0x364]
004f52cd mulss xmm0, dword ptr [0xb6a50c]
004f52d5 mov dword ptr [edx + 0x370], 0x3fcccccd
004f52df movss dword ptr [edx + 0x2b8], xmm1
004f52e7 movss dword ptr [edx + 0x2bc], xmm2
004f52ef subss xmm0, dword ptr [0xb6a994]
004f52f7 movss dword ptr [edx + 0x364], xmm0
004f52ff movss xmm0, dword ptr [0xb6a614]
004f5307 movaps xmm3, xmm0
004f530a movaps xmm2, xmm0
004f530d movaps xmm1, xmm0
004f5310 call 0x427080
004f5315 movaps xmm0, xmmword ptr [0xb6c330]
004f531c push 1
004f531e push 0
004f5320 push 0xff
004f5325 movups xmmword ptr [esp + 0x80], xmm0
004f532d mov eax, dword ptr [edx]
004f532f push -1
004f5331 push ecx
004f5332 mov ecx, edx
004f5334 call dword ptr [eax + 0x38]
004f5337 jmp 0x4f58ec
004f533c cmp eax, 2
004f533f jne 0x4f538a
004f5341 call 0x6c3d90
004f5346 mov ecx, dword ptr [0xbfd65c]
004f534c push 0
004f534e push eax
004f534f push 0
004f5351 push esi
004f5352 push 0xc02fec
004f5357 lea eax, [esi + 0x294]
004f535d push eax
004f535e push 0x6e
004f5360 push 0x3e8
004f5365 call 0x6d0ca0
004f536a mov ecx, eax
004f536c mov edx, dword ptr [eax]
004f536e mov dword ptr [eax + 0x2a4], 0
004f5378 mov dword ptr [eax + 0x2a8], 0xc1700000
004f5382 call dword ptr [edx + 0xc]
004f5385 jmp 0x4f58ec
004f538a cmp eax, 3
004f538d jne 0x4f56a7
004f5393 lea ecx, [esp + 0x90]
004f539a call 0x430d70
004f539f push 0xbc5254
004f53a4 lea ecx, [esp + 0xc0]
004f53ab call 0x4021a0
004f53b0 call 0x6af030
004f53b5 test eax, eax
004f53b7 jg 0x4f53bc
004f53b9 movaps xmm1, xmm2
004f53bc lea eax, [esp + 0x90]
004f53c3 movss dword ptr [esp + 0x18], xmm1
004f53c9 push eax
004f53ca push 7
004f53cc lea eax, [esp + 0x20]
004f53d0 mov dword ptr [esp + 0x24], 0
004f53d8 lea edi, [esi + 0x294]
004f53de mov ecx, esi
004f53e0 push eax
004f53e1 push edi
004f53e2 mov dword ptr [esp + 0x3c], edi
004f53e6 call 0x6a1a20
004f53eb mov eax, dword ptr [0xbfd65c]
004f53f0 mov dword ptr [esp + 0x14], eax
004f53f4 call 0x6c3d90
004f53f9 mov dword ptr [esp + 0x40], eax
004f53fd lea eax, [esp + 0x40]
004f5401 push eax
004f5402 lea eax, [esp + 0x40]
004f5406 mov dword ptr [esp + 0x40], 0
004f540e push eax
004f540f push 0
004f5411 push 0xc02fec
004f5416 push edi
004f5417 lea eax, [esp + 0x3c]
004f541b mov dword ptr [esp + 0x3c], 0x1a
004f5423 push eax
004f5424 lea eax, [esp + 0x4c]
004f5428 mov dword ptr [esp + 0x4c], 0x3e8
004f5430 push eax
004f5431 call 0x800fb0
004f5436 mov ecx, dword ptr [esp + 0x14]
004f543a push 0
004f543c push dword ptr [esp + 0x38]
004f5440 mov ecx, dword ptr [ecx + 0x1c3198]
004f5446 call 0x6c4b30
004f544b mov edi, eax
004f544d mov dword ptr [esp + 0x20], edi
004f5451 test edi, edi
004f5453 je 0x4f5673
004f5459 call dword ptr [0xa064c0]
004f545f mov ecx, dword ptr [edi + 0x320]
004f5465 mov dword ptr [esp + 0xc], eax
004f5469 lea eax, [edi + 0x320]
004f546f mov dword ptr [edi + 0x34], 0
004f5476 mov dword ptr [edi + 0x38], 0
004f547d test ecx, ecx
004f547f je 0x4f549b
004f5481 mov dword ptr [esp + 0x44], eax
004f5485 add ecx, 0x324
004f548b lea eax, [esp + 0x44]
004f548f push eax
004f5490 call 0x4bc3c0
004f5495 lea eax, [edi + 0x320]
004f549b push dword ptr [esp + 0x40]
004f549f mov dword ptr [eax], 0
004f54a5 mov ecx, edi
004f54a7 mov eax, dword ptr [esi + 0x294]
004f54ad push dword ptr [esp + 0x40]
004f54b1 mov dword ptr [edi + 0x294], eax
004f54b7 mov eax, dword ptr [esi + 0x298]
004f54bd push dword ptr [esp + 0x30]
004f54c1 mov dword ptr [edi + 0x298], eax
004f54c7 movss xmm0, dword ptr [0xc02fec]
004f54cf mov eax, dword ptr [edi]
004f54d1 push dword ptr [esp + 0x40]
004f54d5 movss dword ptr [edi + 0x2b8], xmm0
004f54dd movss xmm0, dword ptr [0xc02ff0]
004f54e5 movss dword ptr [edi + 0x2bc], xmm0
004f54ed call dword ptr [eax + 4]
004f54f0 mov eax, dword ptr [esp + 0x14]
004f54f4 push edi
004f54f5 mov edx, dword ptr [eax + 0x18190]
004f54fb mov ecx, dword ptr [edx + 0x1214]
004f5501 lea eax, [ecx + 1]
004f5504 mov dword ptr [edx + 0x1214], eax
004f550a mov dword ptr [edi + 0x20], ecx
004f550d lea ecx, [edx + 0x1218]
004f5513 call 0x413280
004f5518 push edi
004f5519 call 0x6d94d0
004f551e test al, al
004f5520 je 0x4f5529
004f5522 push ecx
004f5523 push edi
004f5524 call 0x6d9590
004f5529 cmp byte ptr [edi + 0x16a], 0
004f5530 je 0x4f5663
004f5536 mov ecx, dword ptr [esp + 0x14]
004f553a mov eax, dword ptr [ecx + 0x283c20]
004f5540 cmp eax, dword ptr [ecx + 0x283c24]
004f5546 je 0x4f5663
004f554c mov eax, dword ptr [edi + 0x28]
004f554f mov dword ptr [esp + 0x18], eax
004f5553 mov eax, dword ptr [edi + 0x2c]
004f5556 mov dword ptr [esp + 0x1c], eax
004f555a lea eax, [ecx + 0x283c48]
004f5560 lea ecx, [esp + 0x18]
004f5564 mov dword ptr [esp + 0x44], eax
004f5568 push ecx
004f5569 lea ecx, [esp + 0x2c]
004f556d push ecx
004f556e mov ecx, eax
004f5570 call 0x937c80
004f5575 mov ecx, dword ptr [esp + 0x44]
004f5579 mov eax, dword ptr [ecx]
004f557b mov dword ptr [esp + 0x44], eax
004f557f cmp dword ptr [esp + 0x28], eax
004f5583 jne 0x4f55af
004f5585 mov eax, dword ptr [edi + 0x28]
004f5588 mov dword ptr [esp + 0x18], eax
004f558c lea eax, [esp + 0x18]
004f5590 push eax
004f5591 lea eax, [esp + 0x2c]
004f5595 mov dword ptr [esp + 0x20], 0xffffffff
004f559d push eax
004f559e call 0x937c80
004f55a3 mov ecx, dword ptr [esp + 0x44]
004f55a7 cmp dword ptr [eax], ecx
004f55a9 je 0x4f5663
004f55af mov edi, dword ptr [0xbfd65c]
004f55b5 xor edx, edx
004f55b7 mov dword ptr [esp + 0x34], edx
004f55bb mov eax, dword ptr [edi + 0x1ba54]
004f55c1 sub eax, dword ptr [edi + 0x1ba50]
004f55c7 sar eax, 2
004f55ca test eax, eax
004f55cc je 0x4f565f
004f55d2 mov esi, dword ptr [esp + 0x20]
004f55d6 nop word ptr [eax + eax]
004f55e0 mov ecx, dword ptr [edi + 0x1ba54]
004f55e6 mov eax, ecx
004f55e8 sub eax, dword ptr [edi + 0x1ba50]
004f55ee test eax, 0xfffffffc
004f55f3 jne 0x4f560e
004f55f5 push 0xb3f4d0
004f55fa push 3
004f55fc call 0x95e330
004f5601 mov ecx, dword ptr [edi + 0x1ba54]
004f5607 add esp, 8
004f560a mov edx, dword ptr [esp + 0x34]
004f560e mov eax, dword ptr [edi + 0x1ba50]
004f5614 sub ecx, eax
004f5616 sar ecx, 2
004f5619 cmp edx, ecx
004f561b jae 0x4f5620
004f561d lea eax, [eax + edx*4]
004f5620 mov ecx, dword ptr [eax]
004f5622 push 0xc02fec
004f5627 push dword ptr [esp + 0x30]
004f562b add ecx, 0x1ec0
004f5631 push esi
004f5632 push 6
004f5634 call 0x935fd0
004f5639 mov edi, dword ptr [0xbfd65c]
004f563f mov edx, dword ptr [esp + 0x34]
004f5643 inc edx
004f5644 mov dword ptr [esp + 0x34], edx
004f5648 mov eax, dword ptr [edi + 0x1ba54]
004f564e sub eax, dword ptr [edi + 0x1ba50]
004f5654 sar eax, 2
004f5657 cmp edx, eax
004f5659 jb 0x4f55e0
004f565b mov esi, dword ptr [esp + 0x24]
004f565f mov edi, dword ptr [esp + 0x20]
004f5663 call dword ptr [0xa064c0]
004f5669 sub eax, dword ptr [esp + 0xc]
004f566d add dword ptr [0xbffe0c], eax
004f5673 mov eax, dword ptr [edi]
004f5675 mov ecx, edi
004f5677 mov dword ptr [edi + 0xd8], 0x40800000
004f5681 mov dword ptr [edi + 0xdc], 0x40800000
004f568b mov dword ptr [edi + 0x3ac], 0x1c2
004f5695 mov dword ptr [edi + 0x3b0], 0x1c2
004f569f call dword ptr [eax + 0xc]
004f56a2 jmp 0x4f58ec
004f56a7 cmp eax, 7
004f56aa jne 0x4f58ec
004f56b0 lea ecx, [esp + 0x90]
004f56b7 call 0x430d70
004f56bc lea eax, [esp + 0x90]
004f56c3 mov dword ptr [esp + 0xa4], 0x3fe66666
004f56ce push eax
004f56cf mov dword ptr [esp + 0xec], 0
004f56da mov dword ptr [esp + 0xf0], 0x40
004f56e5 mov dword ptr [esp + 0xac], 0
004f56f0 mov dword ptr [esp + 0x1c], 0x41000000
004f56f8 mov dword ptr [esp + 0x20], 0x40c00000
004f5700 push 9
004f5702 lea eax, [esp + 0x20]
004f5706 mov ecx, esi
004f5708 push eax
004f5709 lea eax, [esi + 0x294]
004f570f push eax
004f5710 call 0x6a1a20
004f5715 jmp 0x4f58ec
004f571a cmp eax, 0x50
004f571d jne 0x4f58ec
004f5723 movss xmm0, dword ptr [esi + 0x2d8]
004f572b comiss xmm0, dword ptr [0xb6aee4]
004f5732 jbe 0x4f58ec
004f5738 cmp byte ptr [esp + 0xb], 0
004f573d jne 0x4f58ec
004f5743 mov ecx, esi
004f5745 call 0x695680
004f574a movss xmm1, dword ptr [eax + 0x298]
004f5752 subss xmm1, dword ptr [esi + 0x298]
004f575a movss xmm2, dword ptr [eax + 0x294]
004f5762 subss xmm2, dword ptr [esi + 0x294]
004f576a movaps xmm0, xmm1
004f576d movss dword ptr [esp + 0x14], xmm1
004f5773 mulss xmm0, xmm1
004f5777 movaps xmm1, xmm2
004f577a movss dword ptr [esp + 0x34], xmm2
004f5780 mulss xmm1, xmm2
004f5784 addss xmm0, xmm1
004f5788 call 0x4228c0
004f578d movaps xmm2, xmm0
004f5790 comiss xmm2, dword ptr [0xb6a18c]
004f5797 jbe 0x4f57be
004f5799 movss xmm0, dword ptr [esp + 0x14]
004f579f divss xmm0, xmm2
004f57a3 movss xmm1, dword ptr [esp + 0x34]
004f57a9 mulss xmm0, dword ptr [0xb6a974]
004f57b1 divss xmm1, xmm2
004f57b5 xorps xmm0, xmmword ptr [0xb6c9b0]
004f57bc jmp 0x4f57dc
004f57be lea eax, [esp + 0x18]
004f57c2 push eax
004f57c3 call 0x659290
004f57c8 add esp, 4
004f57cb movss xmm0, dword ptr [eax]
004f57cf mulss xmm0, dword ptr [0xb6a974]
004f57d7 movss xmm1, dword ptr [eax + 4]
004f57dc mulss xmm1, dword ptr [0xb6a974]
004f57e4 movss dword ptr [esp + 0xc], xmm0
004f57ea movss dword ptr [esp + 0x14], xmm0
004f57f0 movss dword ptr [esp + 0x10], xmm1
004f57f6 movss dword ptr [esp + 0x34], xmm1
004f57fc call 0x6c3d90
004f5801 addss xmm0, dword ptr [esi + 0x294]
004f5809 addss xmm1, dword ptr [esi + 0x298]
004f5811 mov ecx, dword ptr [0xbfd65c]
004f5817 push 0
004f5819 push eax
004f581a push 0
004f581c push esi
004f581d lea eax, [esp + 0x1c]
004f5821 movss dword ptr [esp + 0x28], xmm0
004f5827 push eax
004f5828 lea eax, [esp + 0x2c]
004f582c movss dword ptr [esp + 0x30], xmm1
004f5832 push eax
004f5833 push 0
004f5835 push 0x12
004f5837 call 0x6d0ca0
004f583c mov edi, eax
004f583e call 0x6c3d90
004f5843 movss xmm0, dword ptr [0xc02fec]
004f584b subss xmm0, dword ptr [esp + 0x14]
004f5851 mov ecx, dword ptr [0xbfd65c]
004f5857 push 0
004f5859 push eax
004f585a push 0
004f585c movss dword ptr [esp + 0x18], xmm0
004f5862 lea eax, [esp + 0x18]
004f5866 movss xmm0, dword ptr [0xc02ff0]
004f586e subss xmm0, dword ptr [esp + 0x40]
004f5874 push esi
004f5875 push eax
004f5876 lea eax, [esp + 0x40]
004f587a push eax
004f587b movss dword ptr [esp + 0x28], xmm0
004f5881 movss xmm0, dword ptr [esi + 0x294]
004f5889 subss xmm0, dword ptr [esp + 0x2c]
004f588f push 0
004f5891 push 0x12
004f5893 movss dword ptr [esp + 0x4c], xmm0
004f5899 movss xmm0, dword ptr [esi + 0x298]
004f58a1 subss xmm0, dword ptr [esp + 0x54]
004f58a7 movss dword ptr [esp + 0x50], xmm0
004f58ad call 0x6d0ca0
004f58b2 mov ecx, dword ptr [edi + 0x164]
004f58b8 mov esi, eax
004f58ba and dword ptr [edi + 0x160], 0xfffffffb
004f58c1 mov dword ptr [edi + 0x164], ecx
004f58c7 mov ecx, dword ptr [esi + 0x164]
004f58cd and dword ptr [esi + 0x160], 0xfffffffb
004f58d4 mov dword ptr [esi + 0x164], ecx
004f58da mov ecx, edi
004f58dc mov edx, dword ptr [edi]
004f58de call dword ptr [edx + 0xc]
004f58e1 mov eax, dword ptr [esi]
004f58e3 mov ecx, esi
004f58e5 call dword ptr [eax + 0xc]
004f58e8 mov esi, dword ptr [esp + 0x24]
004f58ec mov eax, dword ptr [esi + 0xb10]
004f58f2 test eax, eax
004f58f4 jle 0x4f592f
004f58f6 movss xmm1, dword ptr [esi + 0x2dc]
004f58fe movaps xmm0, xmm1
004f5901 divss xmm0, dword ptr [0xb6aa8c]
004f5909 addss xmm0, dword ptr [esi + 0x2d8]
004f5911 comiss xmm1, xmm0
004f5914 ja 0x4f591c
004f5916 movss xmm0, xmm1
004f591a jmp 0x4f5920
004f591c movss xmm0, xmm0
004f5920 dec eax
004f5921 mov dword ptr [esi + 0xb10], eax
004f5927 movss dword ptr [esi + 0x2d8], xmm0
004f592f cmp byte ptr [esi + 0x16b], 0
004f5936 je 0x4f59fd
004f593c cmp dword ptr [esi + 0x28], 0x333
004f5943 jne 0x4f59fd
004f5949 call 0x6c3d90
004f594e mov ecx, dword ptr [0xbfd65c]
004f5954 push 0
004f5956 push eax
004f5957 push 0
004f5959 push esi
004f595a lea eax, [esi + 0x2b8]
004f5960 push eax
004f5961 lea eax, [esi + 0x294]
004f5967 push eax
004f5968 push 0xe
004f596a push 4
004f596c call 0x6d0ca0
004f5971 mov edi, eax
004f5973 push 0
004f5975 push 0xb40360
004f597a lea ecx, [edi + 0x3c]
004f597d call 0x4054f0
004f5982 cmp dword ptr [edi + 0x70], 0
004f5986 je 0x4f5998
004f5988 movss xmm1, dword ptr [0xb6a940]
004f5990 lea ecx, [edi + 0x6c]
004f5993 call 0x403c00
004f5998 mov edx, dword ptr [edi + 0x314]
004f599e lea eax, [edi + 0x314]
004f59a4 mov ecx, dword ptr [esi + 0x314]
004f59aa mov dword ptr [esp + 0x2c], ecx
004f59ae test edx, edx
004f59b0 je 0x4f59d0
004f59b2 mov dword ptr [esp + 0xc], eax
004f59b6 lea ecx, [edx + 0x324]
004f59bc lea eax, [esp + 0xc]
004f59c0 push eax
004f59c1 call 0x4bc3c0
004f59c6 mov ecx, dword ptr [esp + 0x2c]
004f59ca lea eax, [edi + 0x314]
004f59d0 mov dword ptr [eax], ecx
004f59d2 test ecx, ecx
004f59d4 je 0x4f59dc
004f59d6 push eax
004f59d7 call 0x4bae70
004f59dc call 0x6c3d90
004f59e1 xor edx, edx
004f59e3 mov ecx, 0xf
004f59e8 div ecx
004f59ea mov eax, 0x3c
004f59ef sub eax, edx
004f59f1 mov dword ptr [edi + 0x360], eax
004f59f7 mov dword ptr [edi + 0x364], eax
004f59fd mov eax, dword ptr [esi + 0x28]
004f5a00 cmp eax, 0xd
004f5a03 je 0x4f5a8a
004f5a09 cmp eax, 0x50
004f5a0c je 0x4f5a8a
004f5a0e cmp eax, 0x3d
004f5a11 je 0x4f5a8a
004f5a13 cmp eax, 0x12
004f5a16 je 0x4f5a8a
004f5a18 cmp eax, 0xe
004f5a1b jne 0x4f5a5b
004f5a1d mov eax, dword ptr [esi + 0xab4]
004f5a23 cmp eax, 4
004f5a26 ja 0x4f5a39
004f5a28 push 0
004f5a2a push 0xb405b4
004f5a2f lea ecx, [esi + 0x3c]
004f5a32 call 0x4054f0
004f5a37 jmp 0x4f5ab2
004f5a39 cmp eax, 8
004f5a3c jne 0x4f5ab2
004f5a3e push 0xa081d4
004f5a43 lea ecx, [esi + 0x3c]
004f5a46 call 0x4056c0
004f5a4b test al, al
004f5a4d je 0x4f5ab2
004f5a4f mov dword ptr [esi + 0xab4], 4
004f5a59 jmp 0x4f5ab2
004f5a5b cmp eax, 0xd6
004f5a60 je 0x4f5a79
004f5a62 cmp eax, 0xf9
004f5a67 je 0x4f5a79
004f5a69 cmp eax, 0x333
004f5a6e jne 0x4f5ab2
004f5a70 cmp dword ptr [esi + 0xab4], 3
004f5a77 jne 0x4f5ab2
004f5a79 push 0
004f5a7b push 0xb3fd8c
004f5a80 lea ecx, [esi + 0x3c]
004f5a83 call 0x4054f0
004f5a88 jmp 0x4f5ab2
004f5a8a push 0
004f5a8c push 0xb405b4
004f5a91 lea ecx, [esi + 0x3c]
004f5a94 call 0x4054f0
004f5a99 cmp dword ptr [esi + 0x28], 0x3d
004f5a9d jne 0x4f5ab2
004f5a9f xorps xmm0, xmm0
004f5aa2 comiss xmm0, dword ptr [esi + 0x2b8]
004f5aa9 seta al
004f5aac mov byte ptr [esi + 0x13c], al
004f5ab2 cmp dword ptr [esi + 0x28], 0xd
004f5ab6 jne 0x4f5b1e
004f5ab8 call 0x6c3d90
004f5abd xor edx, edx
004f5abf mov ecx, 0x3e8
004f5ac4 div ecx
004f5ac6 test edx, edx
004f5ac8 jne 0x4f5b1e
004f5aca mov eax, dword ptr [0xbfd65c]
004f5acf mov edi, dword ptr [eax + 0x18190]
004f5ad5 lea eax, [esi + 0x294]
004f5adb push eax
004f5adc mov ecx, edi
004f5ade call 0x7ce950
004f5ae3 test eax, eax
004f5ae5 js 0x4f5b1e
004f5ae7 cmp eax, 0x1c0
004f5aec jge 0x4f5b1e
004f5aee mov ecx, dword ptr [edi + eax*4 + 0x24]
004f5af2 test ecx, ecx
004f5af4 je 0x4f5b1e
004f5af6 cmp dword ptr [ecx + 4], 0xe
004f5afa jne 0x4f5b1e
004f5afc mov eax, dword ptr [ecx]
004f5afe push 1
004f5b00 call dword ptr [eax + 0x10]
004f5b03 push -1
004f5b05 push 0
004f5b07 push 0
004f5b09 push 0xe
004f5b0b mov ecx, esi
004f5b0d call 0x697c60
004f5b12 mov eax, dword ptr [esi + 0x2dc]
004f5b18 mov dword ptr [esi + 0x2d8], eax
004f5b1e cmp dword ptr [esi + 0x28], 0xe
004f5b22 jne 0x4f5dc5
004f5b28 cmp byte ptr [esp + 0xb], 0
004f5b2d jne 0x4f5dc5
004f5b33 cmp dword ptr [esi + 0xaf0], 0
004f5b3a jg 0x4f5bd0
004f5b40 movss xmm1, dword ptr [0xb6aba8]
004f5b48 mov ecx, esi
004f5b4a push 7
004f5b4c push 0
004f5b4e call 0x6a15a0
004f5b53 test al, al
004f5b55 je 0x4f5bd0
004f5b57 cmp dword ptr [esi + 0x2c], 2
004f5b5b mov ecx, 0x3f
004f5b60 mov eax, 0x23
004f5b65 cmove eax, ecx
004f5b68 lea ecx, [esi + 0x3c]
004f5b6b push 0
004f5b6d push 0xb40510
004f5b72 mov dword ptr [esi + 0xaf0], eax
004f5b78 call 0x4054f0
004f5b7d push 1
004f5b7f mov ecx, esi
004f5b81 mov dword ptr [esi + 0xab4], 8
004f5b8b call 0x6afe20
004f5b90 lea ecx, [esi + 0xe70]
004f5b96 push 0xc02fec
004f5b9b call 0x962c70
004f5ba0 test al, al
004f5ba2 je 0x4f5bbd
004f5ba4 mov ecx, esi
004f5ba6 call 0x695680
004f5bab movss xmm0, dword ptr [eax + 0x294]
004f5bb3 subss xmm0, dword ptr [esi + 0x294]
004f5bbb jmp 0x4f5bc1
004f5bbd movss xmm0, dword ptr [ecx]
004f5bc1 xorps xmm1, xmm1
004f5bc4 comiss xmm1, xmm0
004f5bc7 seta al
004f5bca mov byte ptr [esi + 0x13c], al
004f5bd0 cmp dword ptr [esi + 0xab4], 8
004f5bd7 jne 0x4f5d59
004f5bdd push 0
004f5bdf mov ecx, esi
004f5be1 call 0x6afe20
004f5be6 push 0xb400ac
004f5beb lea ecx, [esi + 0x3c]
004f5bee call 0x4060f0
004f5bf3 test al, al
004f5bf5 je 0x4f5d59
004f5bfb lea ecx, [esi + 0xe70]
004f5c01 push 0xc02fec
004f5c06 lea edi, [esi + 0x294]
004f5c0c call 0x962c70
004f5c11 test al, al
004f5c13 je 0x4f5c43
004f5c15 mov ecx, esi
004f5c17 call 0x695680
004f5c1c movss xmm0, dword ptr [eax + 0x294]
004f5c24 movss xmm1, dword ptr [eax + 0x298]
004f5c2c subss xmm0, dword ptr [edi]
004f5c30 subss xmm1, dword ptr [edi + 4]
004f5c35 movss dword ptr [esp + 0xc], xmm0
004f5c3b movss dword ptr [esp + 0x10], xmm1
004f5c41 jmp 0x4f5c50
004f5c43 mov eax, dword ptr [ecx]
004f5c45 mov ecx, dword ptr [ecx + 4]
004f5c48 mov dword ptr [esp + 0xc], eax
004f5c4c mov dword ptr [esp + 0x10], ecx
004f5c50 lea ecx, [esp + 0xc]
004f5c54 mov eax, dword ptr [ecx]
004f5c56 mov ecx, dword ptr [ecx + 4]
004f5c59 mov dword ptr [esp + 0x38], ecx
004f5c5d mov ecx, dword ptr [esi + 0x2c]
004f5c60 mov dword ptr [esp + 0x34], eax
004f5c64 cmp ecx, 2
004f5c67 jne 0x4f5cdc
004f5c69 lea ecx, [esp + 0x138]
004f5c70 call 0x430d70
004f5c75 push ecx
004f5c76 lea ecx, [esp + 0x38]
004f5c7a mov dword ptr [esp + 0x150], 0x3fb33333
004f5c85 mov dword ptr [esp + 0x148], 0xbe19999a
004f5c90 mov dword ptr [esp + 0x144], 0x3f800000
004f5c9b mov dword ptr [esp + 0x164], 0x3f99999a
004f5ca6 mov dword ptr [esp + 0x194], 0
004f5cb1 mov dword ptr [esp + 0x198], 0x400000
004f5cbc mov byte ptr [esp + 0x1d4], 1
004f5cc4 mov dword ptr [esp], 0x40e00000
004f5ccb call 0x962860
004f5cd0 lea eax, [esp + 0x138]
004f5cd7 push eax
004f5cd8 push 4
004f5cda jmp 0x4f5d2c
004f5cdc call 0x6af030
004f5ce1 test eax, eax
004f5ce3 jle 0x4f5cfe
004f5ce5 cmp ecx, 1
004f5ce8 jne 0x4f5cf4
004f5cea movss xmm0, dword ptr [0xb6a940]
004f5cf2 jmp 0x4f5d06
004f5cf4 movss xmm0, dword ptr [0xb6a974]
004f5cfc jmp 0x4f5d06
004f5cfe movss xmm0, dword ptr [0xb6a928]
004f5d06 push ecx
004f5d07 lea ecx, [esp + 0x38]
004f5d0b movss dword ptr [esp], xmm0
004f5d10 call 0x962860
004f5d15 lea ecx, [esp + 0x138]
004f5d1c call 0x430d70
004f5d21 push eax
004f5d22 xor eax, eax
004f5d24 cmp dword ptr [esi + 0x2c], 1
004f5d28 sete al
004f5d2b push eax
004f5d2c lea eax, [esp + 0x3c]
004f5d30 mov ecx, esi
004f5d32 push eax
004f5d33 push edi
004f5d34 call 0x6a1a20
004f5d39 push ecx
004f5d3a mov dword ptr [esp], 0x3f800000
004f5d41 push 0
004f5d43 push 2
004f5d45 push ecx
004f5d46 mov dword ptr [esp], 0x3f800000
004f5d4d mov ecx, esi
004f5d4f push 0xb2
004f5d54 call 0x6ad720
004f5d59 mov edx, dword ptr [esi + 0xaf0]
004f5d5f test edx, edx
004f5d61 jle 0x4f5dc5
004f5d63 movss xmm0, dword ptr [esi + 0x2c4]
004f5d6b mulss xmm0, dword ptr [0xb6a560]
004f5d73 cvttss2si eax, dword ptr [esi + 0x2fc]
004f5d7b cvttss2si ecx, dword ptr [esi + 0x2f8]
004f5d83 movss dword ptr [esi + 0x2c4], xmm0
004f5d8b movss xmm0, dword ptr [esi + 0xb00]
004f5d93 sub ecx, eax
004f5d95 mulss xmm0, dword ptr [0xb6a50c]
004f5d9d add ecx, edx
004f5d9f mov dword ptr [esi + 0xaf0], ecx
004f5da5 movss dword ptr [esi + 0xb00], xmm0
004f5dad movss xmm0, dword ptr [esi + 0xb04]
004f5db5 mulss xmm0, dword ptr [0xb6a50c]
004f5dbd movss dword ptr [esi + 0xb04], xmm0
004f5dc5 mov eax, dword ptr [esi + 0x34]
004f5dc8 cmp eax, 0x66
004f5dcb jne 0x4f5ddf
004f5dcd cmp dword ptr [esi + 0x30], 0
004f5dd1 je 0x4f5e01
004f5dd3 mov ecx, esi
004f5dd5 call 0x4481f0
004f5dda jmp 0x4f651a
004f5ddf cmp eax, 0x369
004f5de4 jne 0x4f5e01
004f5de6 mov ecx, esi
004f5de8 call 0x54ee50
004f5ded pop edi
004f5dee pop esi
004f5def mov ecx, dword ptr [esp + 0x1dc]
004f5df6 xor ecx, esp
004f5df8 call 0x9eacd7
004f5dfd mov esp, ebp
004f5dff pop ebp
004f5e00 ret
004f5e01 mov edi, dword ptr [esi + 0x28]
004f5e04 cmp edi, 0x333
004f5e0a jne 0x4f6162
004f5e10 mov eax, dword ptr [esi + 0xab4]
004f5e16 cmp eax, 3
004f5e19 je 0x4f5fb4
004f5e1f cmp eax, 0x10
004f5e22 jne 0x4f651a
004f5e28 cmp dword ptr [esi + 0x360], -1
004f5e2f jne 0x4f5e7c
004f5e31 movss xmm0, dword ptr [esi + 0x2c4]
004f5e39 lea ecx, [esi + 0x3c]
004f5e3c mulss xmm0, dword ptr [0xb6a588]
004f5e44 push 0xa081d4
004f5e49 movss dword ptr [esi + 0x2c4], xmm0
004f5e51 call 0x4056c0
004f5e56 test al, al
004f5e58 je 0x4f6ebc
004f5e5e mov dword ptr [esi + 0xab4], 3
004f5e68 pop edi
004f5e69 pop esi
004f5e6a mov ecx, dword ptr [esp + 0x1dc]
004f5e71 xor ecx, esp
004f5e73 call 0x9eacd7
004f5e78 mov esp, ebp
004f5e7a pop ebp
004f5e7b ret
004f5e7c movss xmm0, dword ptr [0xb6aa60]
004f5e84 comiss xmm0, dword ptr [esi + 0x2d4]
004f5e8b jbe 0x4f5eaa
004f5e8d push ecx
004f5e8e lea ecx, [esi + 0x2b8]
004f5e94 mov dword ptr [esp], 0x41200000
004f5e9b call 0x962860
004f5ea0 mov dword ptr [esi + 0x2d4], 0x42480000
004f5eaa push 0
004f5eac push 0xb42eac
004f5eb1 lea ecx, [esi + 0x3c]
004f5eb4 call 0x4054f0
004f5eb9 inc dword ptr [esi + 0x360]
004f5ebf cmp dword ptr [esi + 0x360], 0x2d
004f5ec6 jg 0x4f5ef6
004f5ec8 movss xmm1, dword ptr [esi + 0x2bc]
004f5ed0 movss xmm0, dword ptr [esi + 0x2b8]
004f5ed8 mulss xmm0, xmm0
004f5edc mulss xmm1, xmm1
004f5ee0 addss xmm0, xmm1
004f5ee4 call 0x4228c0
004f5ee9 movss xmm1, dword ptr [0xb6a8f4]
004f5ef1 comiss xmm1, xmm0
004f5ef4 jbe 0x4f5f1e
004f5ef6 push 0
004f5ef8 push 0xb42eb8
004f5efd lea ecx, [esi + 0x3c]
004f5f00 call 0x4054f0
004f5f05 mov eax, dword ptr [esi + 0x288]
004f5f0b mov dword ptr [esi + 0x360], 0xffffffff
004f5f15 mov eax, dword ptr [eax + 0x44]
004f5f18 mov dword ptr [esi + 0x2d4], eax
004f5f1e cmp byte ptr [esi + 0x188], 0
004f5f25 je 0x4f6ebc
004f5f2b movss xmm5, dword ptr [esi + 0x190]
004f5f33 movss xmm3, dword ptr [esi + 0x18c]
004f5f3b movaps xmm0, xmm5
004f5f3e movss xmm2, dword ptr [esi + 0x194]
004f5f46 movaps xmm1, xmm3
004f5f49 movss xmm4, dword ptr [esi + 0x198]
004f5f51 mulss xmm1, xmm2
004f5f55 addss xmm2, xmm2
004f5f59 push ecx
004f5f5a mulss xmm0, xmm4
004f5f5e addss xmm4, xmm4
004f5f62 mov dword ptr [esp], 0x3f800000
004f5f69 push 0
004f5f6b push 2
004f5f6d addss xmm1, xmm0
004f5f71 push 0x28
004f5f73 mulss xmm2, xmm1
004f5f77 mulss xmm4, xmm1
004f5f7b subss xmm3, xmm2
004f5f7f movss xmm2, dword ptr [0xb6a614]
004f5f87 subss xmm5, xmm4
004f5f8b movss dword ptr [esi + 0x2b8], xmm3
004f5f93 movss dword ptr [esi + 0x2bc], xmm5
004f5f9b call 0x8b1480
004f5fa0 pop edi
004f5fa1 pop esi
004f5fa2 mov ecx, dword ptr [esp + 0x1dc]
004f5fa9 xor ecx, esp
004f5fab call 0x9eacd7
004f5fb0 mov esp, ebp
004f5fb2 pop ebp
004f5fb3 ret
004f5fb4 cmp dword ptr [esi + 0x2c], 1
004f5fb8 jne 0x4f6162
004f5fbe mov edi, dword ptr [esi + 0x314]
004f5fc4 mov byte ptr [esi + 0x308], 1
004f5fcb test edi, edi
004f5fcd je 0x4f6086
004f5fd3 movss xmm0, dword ptr [esi + 0x2f4]
004f5fdb mulss xmm0, dword ptr [0xb6a8f4]
004f5fe3 addss xmm0, dword ptr [esi + 0xb00]
004f5feb call 0x65a640
004f5ff0 movss dword ptr [esi + 0xb00], xmm0
004f5ff8 mulss xmm0, dword ptr [0xb6a230]
004f6000 movss dword ptr [esp + 0xc], xmm0
004f6006 call 0x411fe0
004f600b mulss xmm0, dword ptr [0xb6aa3c]
004f6013 addss xmm0, dword ptr [edi + 0x294]
004f601b movss dword ptr [esp + 0x2c], xmm0
004f6021 movss xmm0, dword ptr [esp + 0xc]
004f6027 call 0x412010
004f602c mulss xmm0, dword ptr [0xb6aa3c]
004f6034 movss xmm1, dword ptr [esp + 0x2c]
004f603a addss xmm0, dword ptr [edi + 0x298]
004f6042 movss dword ptr [esi + 0x28c], xmm1
004f604a movss dword ptr [esi + 0x290], xmm0
004f6052 subss xmm1, dword ptr [esi + 0x294]
004f605a subss xmm0, dword ptr [esi + 0x298]
004f6062 movss dword ptr [esi + 0x2b8], xmm1
004f606a movss dword ptr [esi + 0x2bc], xmm0
004f6072 pop edi
004f6073 pop esi
004f6074 mov ecx, dword ptr [esp + 0x1dc]
004f607b xor ecx, esp
004f607d call 0x9eacd7
004f6082 mov esp, ebp
004f6084 pop ebp
004f6085 ret
004f6086 mov eax, dword ptr [esi]
004f6088 mov ecx, esi
004f608a call dword ptr [eax + 0x24]
004f608d movss xmm0, dword ptr [esi + 0xb00]
004f6095 mulss xmm0, dword ptr [0xb6a230]
004f609d movss dword ptr [esp + 0xc], xmm0
004f60a3 call 0x411fe0
004f60a8 mulss xmm0, dword ptr [0xb6a9ac]
004f60b0 movss dword ptr [esp + 0x2c], xmm0
004f60b6 movss xmm0, dword ptr [esp + 0xc]
004f60bc call 0x412010
004f60c1 mulss xmm0, dword ptr [0xb6a9ac]
004f60c9 add esi, 0x2b8
004f60cf movss xmm1, dword ptr [esp + 0x2c]
004f60d5 movss dword ptr [esi], xmm1
004f60d9 movss dword ptr [esi + 4], xmm0
004f60de call 0x6c3d90
004f60e3 mov ecx, dword ptr [0xbfd65c]
004f60e9 push eax
004f60ea mov eax, dword ptr [esp + 0x28]
004f60ee push 0
004f60f0 push eax
004f60f1 push esi
004f60f2 add eax, 0x294
004f60f7 push eax
004f60f8 push 0xe
004f60fa push 4
004f60fc call 0x422e20
004f6101 mov edi, eax
004f6103 push 0
004f6105 push 0xb40360
004f610a lea ecx, [edi + 0x3c]
004f610d call 0x4054f0
004f6112 push 8
004f6114 lea ecx, [edi + 0x3c]
004f6117 call 0x405890
004f611c mov eax, dword ptr [esp + 0x24]
004f6120 mov ecx, edi
004f6122 push dword ptr [eax + 0x314]
004f6128 call 0x6818e0
004f612d call 0x6c3d90
004f6132 xor edx, edx
004f6134 mov ecx, 0xf
004f6139 div ecx
004f613b mov eax, 0x3c
004f6140 sub eax, edx
004f6142 mov dword ptr [edi + 0x360], eax
004f6148 mov dword ptr [edi + 0x364], eax
004f614e pop edi
004f614f pop esi
004f6150 mov ecx, dword ptr [esp + 0x1dc]
004f6157 xor ecx, esp
004f6159 call 0x9eacd7
004f615e mov esp, ebp
004f6160 pop ebp
004f6161 ret
004f6162 push 0
004f6164 push 3
004f6166 mov ecx, esi
004f6168 call 0x684790
004f616d test al, al
004f616f je 0x4f651a
004f6175 cmp edi, 0x12
004f6178 je 0x4f619d
004f617a cmp edi, 0x50
004f617d je 0x4f619d
004f617f cmp edi, 0xd6
004f6185 je 0x4f619d
004f6187 cmp edi, 0xf9
004f618d je 0x4f619d
004f618f mov eax, edi
004f6191 cmp edi, 0x333
004f6197 jne 0x4f6350
004f619d mov ecx, dword ptr [esi + 0x314]
004f61a3 mov eax, edi
004f61a5 test ecx, ecx
004f61a7 je 0x4f6347
004f61ad cmp dword ptr [esi + 0xe6c], -1
004f61b4 jne 0x4f6347
004f61ba movss xmm1, dword ptr [ecx + 0x298]
004f61c2 subss xmm1, dword ptr [esi + 0x298]
004f61ca movss xmm2, dword ptr [ecx + 0x294]
004f61d2 subss xmm2, dword ptr [esi + 0x294]
004f61da movaps xmm0, xmm1
004f61dd movss dword ptr [esp + 0x28], xmm1
004f61e3 mulss xmm0, xmm1
004f61e7 movaps xmm1, xmm2
004f61ea movss dword ptr [esp + 0x3c], xmm2
004f61f0 mulss xmm1, xmm2
004f61f4 addss xmm0, xmm1
004f61f8 call 0x4228c0
004f61fd movss xmm1, dword ptr [0xb6abf8]
004f6205 mov eax, edi
004f6207 comiss xmm1, xmm0
004f620a movss dword ptr [esp + 0xc], xmm0
004f6210 jbe 0x4f6347
004f6216 mov eax, dword ptr [0xbfd65c]
004f621b movd xmm0, dword ptr [eax + 0x1a30dc]
004f6223 cvtdq2ps xmm0, xmm0
004f6226 mulss xmm0, dword ptr [0xb6a234]
004f622e call 0x412010
004f6233 movss xmm2, dword ptr [0xb6a8f4]
004f623b lea eax, [esp + 0xc]
004f623f movss xmm3, dword ptr [esp + 0xc]
004f6245 lea ecx, [esp + 0x2c]
004f6249 mulss xmm0, xmm2
004f624d movaps xmm1, xmm3
004f6250 mov dword ptr [esp + 0x2c], 0xc0a00000
004f6258 addss xmm0, dword ptr [0xb6aaa0]
004f6260 subss xmm1, xmm0
004f6264 comiss xmm1, dword ptr [0xb6ae98]
004f626b movss dword ptr [esp + 0xc], xmm1
004f6271 cmovbe eax, ecx
004f6274 movss xmm0, dword ptr [eax]
004f6278 comiss xmm2, xmm0
004f627b ja 0x4f6283
004f627d movss xmm1, xmm2
004f6281 jmp 0x4f6287
004f6283 movss xmm1, xmm0
004f6287 lea eax, [esp + 0x2c]
004f628b mov ecx, esi
004f628d push 0
004f628f push eax
004f6290 movss xmm0, dword ptr [esp + 0x44]
004f6296 mulss xmm0, xmm1
004f629a movss dword ptr [esp + 0x14], xmm1
004f62a0 mulss xmm0, dword ptr [0xb6a480]
004f62a8 divss xmm0, xmm3
004f62ac movss dword ptr [esp + 0x34], xmm0
004f62b2 movss xmm0, dword ptr [esp + 0x30]
004f62b8 mulss xmm0, xmm1
004f62bc mulss xmm0, dword ptr [0xb6a480]
004f62c4 divss xmm0, xmm3
004f62c8 movss dword ptr [esp + 0x38], xmm0
004f62ce call 0x422b60
004f62d3 movss xmm1, dword ptr [esp + 0xc]
004f62d9 lea eax, [esp + 0xc]
004f62dd xorps xmm1, xmmword ptr [0xb6c9b0]
004f62e4 mov ecx, esi
004f62e6 andps xmm1, xmmword ptr [0xb6c980]
004f62ed movss xmm2, dword ptr [esp + 0x28]
004f62f3 mulss xmm2, dword ptr [0xb6a350]
004f62fb push 0
004f62fd addss xmm1, dword ptr [0xb6a7b0]
004f6305 movss xmm0, dword ptr [esi + 0x2c4]
004f630d push eax
004f630e divss xmm2, xmm1
004f6312 xorps xmm2, xmmword ptr [0xb6c9b0]
004f6319 divss xmm2, xmm0
004f631d movss dword ptr [esp + 0x14], xmm2
004f6323 movss xmm2, dword ptr [esp + 0x44]
004f6329 mulss xmm2, dword ptr [0xb6a350]
004f6331 divss xmm2, xmm1
004f6335 divss xmm2, xmm0
004f6339 movss dword ptr [esp + 0x18], xmm2
004f633f call 0x422b60
004f6344 mov eax, dword ptr [esi + 0x28]
004f6347 cmp eax, 0x12
004f634a je 0x4f64f5
004f6350 cmp eax, 0x3d
004f6353 je 0x4f64f5
004f6359 cmp eax, 0x50
004f635c je 0x4f64f5
004f6362 cmp eax, 0xd6
004f6367 je 0x4f64f5
004f636d cmp eax, 0xf9
004f6372 je 0x4f64f5
004f6378 cmp eax, 0x333
004f637d je 0x4f64f5
004f6383 cmp byte ptr [esp + 0xb], 0
004f6388 jne 0x4f64f5
004f638e call 0x6c3d90
004f6393 movd xmm0, eax
004f6397 cvtdq2pd xmm0, xmm0
004f639b shr eax, 0x1f
004f639e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f63a7 cvtpd2ps xmm1, xmm0
004f63ab mulss xmm1, dword ptr [0xb6a19c]
004f63b3 call 0x6c3d90
004f63b8 movd xmm0, eax
004f63bc cvtdq2pd xmm0, xmm0
004f63c0 shr eax, 0x1f
004f63c3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f63cc lea eax, [esp + 0x2c]
004f63d0 push eax
004f63d1 cvtpd2ps xmm0, xmm0
004f63d5 mulss xmm0, dword ptr [0xb6a19c]
004f63dd mulss xmm0, xmm1
004f63e1 mulss xmm0, dword ptr [0xb6abe4]
004f63e9 movss dword ptr [esp + 0x10], xmm0
004f63ef call 0x659290
004f63f4 movss xmm1, dword ptr [esp + 0x10]
004f63fa add esp, 4
004f63fd mov edi, dword ptr [0xbfd65c]
004f6403 movaps xmm0, xmm1
004f6406 mulss xmm0, dword ptr [eax]
004f640a mulss xmm1, dword ptr [eax + 4]
004f640f lea eax, [esp + 0xc]
004f6413 mov edi, dword ptr [edi + 0x18190]
004f6419 mov ecx, edi
004f641b addss xmm0, dword ptr [esi + 0x294]
004f6423 push eax
004f6424 addss xmm1, dword ptr [esi + 0x298]
004f642c movss dword ptr [esp + 0x10], xmm0
004f6432 movss dword ptr [esp + 0x14], xmm1
004f6438 call 0x7ce950
004f643d test eax, eax
004f643f js 0x4f6474
004f6441 cmp eax, 0x1c0
004f6446 jge 0x4f6474
004f6448 mov edx, dword ptr [edi + eax*4 + 0x24]
004f644c test edx, edx
004f644e je 0x4f6474
004f6450 cmp dword ptr [edx + 4], 0xe
004f6454 jne 0x4f6474
004f6456 push eax
004f6457 lea eax, [esp + 0x10]
004f645b mov ecx, edi
004f645d push eax
004f645e call 0x7cebc0
004f6463 mov ecx, dword ptr [eax]
004f6465 mov dword ptr [esi + 0x28c], ecx
004f646b mov eax, dword ptr [eax + 4]
004f646e mov dword ptr [esi + 0x290], eax
004f6474 call 0x6c3d90
004f6479 xor edx, edx
004f647b mov ecx, 0x64
004f6480 div ecx
004f6482 test edx, edx
004f6484 jne 0x4f651a
004f648a push edx
004f648b push edx
004f648c push -1
004f648e push -1
004f6490 push 0x21
004f6492 lea eax, [esp + 0x60]
004f6496 push eax
004f6497 mov eax, dword ptr [0xbfd65c]
004f649c mov ecx, dword ptr [eax + 0x18190]
004f64a2 add ecx, 0x1218
004f64a8 call 0x415ed0
004f64ad mov ecx, dword ptr [esp + 0x58]
004f64b1 mov edi, dword ptr [esp + 0x50]
004f64b5 test ecx, ecx
004f64b7 je 0x4f64e3
004f64b9 call 0x659230
004f64be lea eax, [edi + eax*4]
004f64c1 mov eax, dword ptr [eax]
004f64c3 movss xmm0, dword ptr [eax + 0x294]
004f64cb movss xmm1, dword ptr [eax + 0x298]
004f64d3 movss dword ptr [esi + 0x28c], xmm0
004f64db movss dword ptr [esi + 0x290], xmm1
004f64e3 cmp byte ptr [esp + 0x4c], 0
004f64e8 jne 0x4f651a
004f64ea push edi
004f64eb call 0x9eace5
004f64f0 add esp, 4
004f64f3 jmp 0x4f651a
004f64f5 push ecx
004f64f6 lea eax, [esp + 0x60]
004f64fa mov dword ptr [esp], 0
004f6501 push eax
004f6502 mov ecx, esi
004f6504 call 0x695a30
004f6509 mov ecx, dword ptr [eax]
004f650b mov dword ptr [esi + 0x28c], ecx
004f6511 mov eax, dword ptr [eax + 4]
004f6514 mov dword ptr [esi + 0x290], eax
004f651a mov eax, dword ptr [esi + 0x28]
004f651d cmp eax, 0xd
004f6520 je 0x4f6527
004f6522 cmp eax, 0xe
004f6525 jne 0x4f6553
004f6527 cmp dword ptr [esi + 0x34], 0x66
004f652b jne 0x4f6533
004f652d cmp dword ptr [esi + 0x30], 0
004f6531 jne 0x4f6553
004f6533 movss xmm0, dword ptr [0xc02fec]
004f653b movss dword ptr [esi + 0x28c], xmm0
004f6543 movss xmm0, dword ptr [0xc02ff0]
004f654b movss dword ptr [esi + 0x290], xmm0
004f6553 mov eax, dword ptr [esi + 0x160]
004f6559 and eax, 0x1000800
004f655e or eax, 0
004f6561 je 0x4f677e
004f6567 push 0
004f6569 push 0x720
004f656e mov ecx, esi
004f6570 call 0x4122f0
004f6575 test al, al
004f6577 jne 0x4f677e
004f657d cmp dword ptr [esi + 0xe6c], -1
004f6584 jne 0x4f677e
004f658a mov ecx, esi
004f658c call 0x695680
004f6591 movss xmm1, dword ptr [eax + 0x294]
004f6599 movss xmm0, dword ptr [eax + 0x298]
004f65a1 subss xmm0, dword ptr [esi + 0x298]
004f65a9 subss xmm1, dword ptr [esi + 0x294]
004f65b1 mulss xmm0, xmm0
004f65b5 mulss xmm1, xmm1
004f65b9 addss xmm0, xmm1
004f65bd call 0x4228c0
004f65c2 movss xmm1, dword ptr [0xb6ac60]
004f65ca comiss xmm1, xmm0
004f65cd jbe 0x4f677e
004f65d3 movss xmm2, dword ptr [0xb6aba8]
004f65db comiss xmm0, xmm2
004f65de movss xmm1, dword ptr [0xb6aafc]
004f65e6 movss dword ptr [esp + 0x3c], xmm1
004f65ec jbe 0x4f6607
004f65ee subss xmm0, xmm2
004f65f2 divss xmm0, xmm2
004f65f6 movaps xmm2, xmm1
004f65f9 mulss xmm0, xmm1
004f65fd subss xmm2, xmm0
004f6601 movss dword ptr [esp + 0x3c], xmm2
004f6607 cmp byte ptr [esi + 0x188], 0
004f660e movss xmm0, dword ptr [0xb6abc0]
004f6616 movss dword ptr [esp + 0x28], xmm0
004f661c je 0x4f662c
004f661e movss xmm0, dword ptr [0xb6ac40]
004f6626 movss dword ptr [esp + 0x28], xmm0
004f662c call 0x6c3d90
004f6631 mov ecx, esi
004f6633 movd xmm0, eax
004f6637 cvtdq2pd xmm0, xmm0
004f663b shr eax, 0x1f
004f663e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f6647 cvtpd2ps xmm0, xmm0
004f664b mulss xmm0, dword ptr [0xb6a19c]
004f6653 movss dword ptr [esp + 0xc], xmm0
004f6659 call 0x695680
004f665e movss xmm0, dword ptr [esi + 0x294]
004f6666 movss xmm1, dword ptr [esp + 0x28]
004f666c movss dword ptr [esp + 0x20], xmm0
004f6672 subss xmm0, dword ptr [eax + 0x294]
004f667a movss dword ptr [esp + 0x2c], xmm0
004f6680 movss xmm0, dword ptr [esi + 0x298]
004f6688 movss dword ptr [esp + 0x24], xmm0
004f668e subss xmm0, dword ptr [eax + 0x298]
004f6696 movss dword ptr [esp + 0x40], xmm0
004f669c movaps xmm0, xmm1
004f669f mulss xmm0, dword ptr [esp + 0xc]
004f66a5 mulss xmm1, dword ptr [0xb6a480]
004f66ad subss xmm0, xmm1
004f66b1 mulss xmm0, dword ptr [0xb6a230]
004f66b9 movss dword ptr [esp + 0xc], xmm0
004f66bf call 0x411fe0
004f66c4 movss dword ptr [esp + 0x44], xmm0
004f66ca movss xmm0, dword ptr [esp + 0xc]
004f66d0 call 0x412010
004f66d5 movss xmm5, dword ptr [esp + 0x2c]
004f66db lea eax, [esp + 0x4c]
004f66df movss xmm4, dword ptr [esp + 0x40]
004f66e5 movaps xmm2, xmm5
004f66e8 mulss xmm2, dword ptr [esp + 0x44]
004f66ee movaps xmm1, xmm4
004f66f1 push ecx
004f66f2 mulss xmm4, dword ptr [esp + 0x48]
004f66f8 lea ecx, [esp + 0x10]
004f66fc mulss xmm1, xmm0
004f6700 mulss xmm5, xmm0
004f6704 movss xmm0, dword ptr [esp + 0x40]
004f670a subss xmm2, xmm1
004f670e movss dword ptr [esp], xmm0
004f6713 addss xmm4, xmm5
004f6717 push eax
004f6718 movss dword ptr [esp + 0x14], xmm2
004f671e movss dword ptr [esp + 0x18], xmm4
004f6724 call 0x9628d0
004f6729 movss xmm0, dword ptr [esp + 0x24]
004f672f movss xmm1, dword ptr [esp + 0x20]
004f6735 addss xmm0, dword ptr [eax + 4]
004f673a addss xmm1, dword ptr [eax]
004f673e movss dword ptr [esi + 0x290], xmm0
004f6746 movss xmm0, dword ptr [esi + 0xb00]
004f674e mulss xmm0, dword ptr [0xb6a480]
004f6756 movss dword ptr [esi + 0x28c], xmm1
004f675e movss dword ptr [esi + 0xb00], xmm0
004f6766 movss xmm0, dword ptr [esi + 0xb04]
004f676e mulss xmm0, dword ptr [0xb6a480]
004f6776 movss dword ptr [esi + 0xb04], xmm0
004f677e cmp dword ptr [esi + 0x34], 0x66
004f6782 mov edi, 3
004f6787 jne 0x4f6793
004f6789 cmp dword ptr [esi + 0x30], 0
004f678d jne 0x4f6b62
004f6793 movss xmm0, dword ptr [esi + 0x28c]
004f679b ucomiss xmm0, dword ptr [0xc02fec]
004f67a2 lahf
004f67a3 test ah, 0x44
004f67a6 jp 0x4f67c1
004f67a8 movss xmm0, dword ptr [esi + 0x290]
004f67b0 ucomiss xmm0, dword ptr [0xc02ff0]
004f67b7 lahf
004f67b8 test ah, 0x44
004f67bb jnp 0x4f6a3f
004f67c1 movss xmm1, dword ptr [0xb6a7b0]
004f67c9 xorps xmm2, xmm2
004f67cc mov ecx, esi
004f67ce call 0x6847e0
004f67d3 test eax, eax
004f67d5 je 0x4f6a3f
004f67db movss xmm3, dword ptr [0xb6aa0c]
004f67e3 mov edi, dword ptr [esi + 0x28]
004f67e6 movss dword ptr [esp + 0x20], xmm3
004f67ec cmp edi, 0x12
004f67ef je 0x4f680e
004f67f1 cmp edi, 0x50
004f67f4 je 0x4f680e
004f67f6 cmp edi, 0xd6
004f67fc je 0x4f680e
004f67fe cmp edi, 0xf9
004f6804 je 0x4f680e
004f6806 cmp edi, 0x333
004f680c jne 0x4f681c
004f680e movss xmm3, dword ptr [0xb6a9ec]
004f6816 movss dword ptr [esp + 0x20], xmm3
004f681c cmp edi, 0x3d
004f681f je 0x4f6832
004f6821 movss xmm0, dword ptr [esi + 0xd8]
004f6829 comiss xmm0, dword ptr [0xb6a64c]
004f6830 jbe 0x4f6840
004f6832 movss xmm0, dword ptr [0xb6a9ac]
004f683a movss dword ptr [esp + 0x20], xmm0
004f6840 cmp dword ptr [esi + 0xe6c], -1
004f6847 movss xmm0, dword ptr [esi + 0x28c]
004f684f subss xmm0, dword ptr [esi + 0x294]
004f6857 movss xmm2, dword ptr [esi + 0x290]
004f685f subss xmm2, dword ptr [esi + 0x298]
004f6867 movaps xmm1, xmm0
004f686a movss dword ptr [esp + 0x14], xmm1
004f6870 je 0x4f689f
004f6872 lea eax, [esp + 0xc]
004f6876 xorps xmm2, xmm2
004f6879 push eax
004f687a mov ecx, esi
004f687c call 0x6af0c0
004f6881 mov edi, dword ptr [esi + 0x28]
004f6884 movss xmm1, dword ptr [eax]
004f6888 movss xmm2, dword ptr [eax + 4]
004f688d mulss xmm1, dword ptr [0xb6aafc]
004f6895 mulss xmm2, dword ptr [0xb6aafc]
004f689d jmp 0x4f6916
004f689f cmp edi, 0xd6
004f68a5 je 0x4f68af
004f68a7 cmp edi, 0x333
004f68ad jne 0x4f68c7
004f68af mov al, byte ptr [esp + 0xb]
004f68b3 test al, al
004f68b5 jne 0x4f68cb
004f68b7 movaps xmm1, xmm2
004f68ba xorps xmm1, xmmword ptr [0xb6c9b0]
004f68c1 addss xmm1, xmm0
004f68c5 jmp 0x4f68e5
004f68c7 mov al, byte ptr [esp + 0xb]
004f68cb cmp edi, 0xf9
004f68d1 jne 0x4f68ef
004f68d3 test al, al
004f68d5 jne 0x4f68ef
004f68d7 movaps xmm1, xmm2
004f68da addss xmm1, xmm0
004f68de xorps xmm0, xmmword ptr [0xb6c9b0]
004f68e5 addss xmm2, xmm0
004f68e9 movss dword ptr [esp + 0x14], xmm1
004f68ef cmp dword ptr [esi + 0x314], 0
004f68f6 mulss xmm2, dword ptr [0xb6a480]
004f68fe movss dword ptr [esp + 0x24], xmm2
004f6904 je 0x4f6922
004f6906 mulss xmm1, dword ptr [0xb6a350]
004f690e mulss xmm2, dword ptr [0xb6a350]
004f6916 movss dword ptr [esp + 0x24], xmm2
004f691c movss dword ptr [esp + 0x14], xmm1
004f6922 movaps xmm0, xmm1
004f6925 mulss xmm0, xmm1
004f6929 movaps xmm1, xmm2
004f692c mulss xmm1, xmm2
004f6930 addss xmm0, xmm1
004f6934 call 0x4228c0
004f6939 movss xmm2, dword ptr [esp + 0x14]
004f693f movaps xmm3, xmm0
004f6942 comiss xmm3, dword ptr [0xb6a18c]
004f6949 movss xmm1, dword ptr [esp + 0x24]
004f694f jbe 0x4f6959
004f6951 divss xmm2, xmm3
004f6955 divss xmm1, xmm3
004f6959 cmp byte ptr [esi + 0x16c], 0
004f6960 je 0x4f697a
004f6962 movss xmm0, dword ptr [esi + 0x2c4]
004f696a mulss xmm0, dword ptr [0xb6a5a4]
004f6972 movss dword ptr [esi + 0x2c4], xmm0
004f697a mov eax, edi
004f697c cmp edi, 0x12
004f697f je 0x4f69d6
004f6981 cmp edi, 0x3d
004f6984 je 0x4f69d6
004f6986 cmp edi, 0x50
004f6989 je 0x4f69d6
004f698b cmp edi, 0xd6
004f6991 je 0x4f69d6
004f6993 cmp edi, 0xf9
004f6999 je 0x4f69d6
004f699b cmp edi, 0x333
004f69a1 je 0x4f69d6
004f69a3 movss xmm0, dword ptr [esi + 0xb00]
004f69ab mulss xmm0, dword ptr [0xb6a50c]
004f69b3 movss dword ptr [esi + 0xb00], xmm0
004f69bb movss xmm0, dword ptr [esi + 0xb04]
004f69c3 mulss xmm0, dword ptr [0xb6a50c]
004f69cb movss dword ptr [esi + 0xb04], xmm0
004f69d3 mov eax, dword ptr [esi + 0x28]
004f69d6 movss xmm0, dword ptr [esp + 0x20]
004f69dc comiss xmm3, xmm0
004f69df jbe 0x4f6a3a
004f69e1 subss xmm3, xmm0
004f69e5 mulss xmm3, dword ptr [0xb6a2ac]
004f69ed minss xmm3, dword ptr [0xb6a670]
004f69f5 cmp eax, 0xd6
004f69fa je 0x4f6a0a
004f69fc cmp eax, 0xf9
004f6a01 je 0x4f6a0a
004f6a03 cmp eax, 0x333
004f6a08 jne 0x4f6a18
004f6a0a cmp byte ptr [esp + 0xb], 0
004f6a0f jne 0x4f6a18
004f6a11 movaps xmm0, xmm3
004f6a14 addss xmm3, xmm0
004f6a18 mulss xmm2, xmm3
004f6a1c lea eax, [esp + 0xc]
004f6a20 mov ecx, esi
004f6a22 mulss xmm1, xmm3
004f6a26 push 0
004f6a28 push eax
004f6a29 movss dword ptr [esp + 0x14], xmm2
004f6a2f movss dword ptr [esp + 0x18], xmm1
004f6a35 call 0x422b60
004f6a3a mov edi, 3
004f6a3f mov eax, dword ptr [esi + 0x28]
004f6a42 cmp eax, 0xd6
004f6a47 je 0x4f6a5b
004f6a49 cmp eax, 0xf9
004f6a4e je 0x4f6a5b
004f6a50 cmp eax, 0x333
004f6a55 jne 0x4f6b62
004f6a5b cmp byte ptr [esi + 0x188], 0
004f6a62 je 0x4f6ae2
004f6a64 call 0x6c3d90
004f6a69 xor edx, edx
004f6a6b div edi
004f6a6d test edx, edx
004f6a6f jne 0x4f6ae2
004f6a71 push edx
004f6a72 push 0x1000800
004f6a77 mov ecx, esi
004f6a79 call 0x4122f0
004f6a7e test al, al
004f6a80 jne 0x4f6ae2
004f6a82 call 0x6c3d90
004f6a87 push ecx
004f6a88 lea ecx, [esi + 0x194]
004f6a8e movd xmm0, eax
004f6a92 cvtdq2pd xmm0, xmm0
004f6a96 shr eax, 0x1f
004f6a99 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f6aa2 lea eax, [esp + 0x30]
004f6aa6 cvtpd2ps xmm1, xmm0
004f6aaa movss xmm0, dword ptr [0xb6ae6c]
004f6ab2 mulss xmm1, dword ptr [0xb6a19c]
004f6aba mulss xmm1, dword ptr [0xb6a6f0]
004f6ac2 subss xmm0, xmm1
004f6ac6 movss dword ptr [esp], xmm0
004f6acb push eax
004f6acc call 0x9628d0
004f6ad1 mov ecx, dword ptr [eax]
004f6ad3 mov dword ptr [esi + 0xb08], ecx
004f6ad9 mov eax, dword ptr [eax + 4]
004f6adc mov dword ptr [esi + 0xb0c], eax
004f6ae2 movss xmm1, dword ptr [esi + 0xb0c]
004f6aea lea eax, [esi + 0xb08]
004f6af0 movss xmm0, dword ptr [esi + 0xb08]
004f6af8 mulss xmm0, xmm0
004f6afc mulss xmm1, xmm1
004f6b00 addss xmm0, xmm1
004f6b04 comiss xmm0, dword ptr [0xb6a614]
004f6b0b jbe 0x4f6b49
004f6b0d push 0
004f6b0f push eax
004f6b10 mov ecx, esi
004f6b12 call 0x422b60
004f6b17 movss xmm0, dword ptr [esi + 0xb08]
004f6b1f mulss xmm0, dword ptr [0xb6a5a4]
004f6b27 movss dword ptr [esi + 0xb08], xmm0
004f6b2f movss xmm0, dword ptr [esi + 0xb0c]
004f6b37 mulss xmm0, dword ptr [0xb6a5a4]
004f6b3f movss dword ptr [esi + 0xb0c], xmm0
004f6b47 jmp 0x4f6b62
004f6b49 movss xmm0, dword ptr [0xc02fec]
004f6b51 movss dword ptr [eax], xmm0
004f6b55 movss xmm0, dword ptr [0xc02ff0]
004f6b5d movss dword ptr [eax + 4], xmm0
004f6b62 cmp dword ptr [esi + 0x17c], 0
004f6b69 jne 0x4f6bb9
004f6b6b movss xmm0, dword ptr [esi + 0x2c8]
004f6b73 lea edi, [esi + 0x294]
004f6b79 push ecx
004f6b7a mov ecx, dword ptr [0xbfd65c]
004f6b80 movss dword ptr [esp], xmm0
004f6b85 push edi
004f6b86 mov ecx, dword ptr [ecx + 0x18190]
004f6b8c call 0x7cf0a0
004f6b91 test al, al
004f6b93 je 0x4f6bb9
004f6b95 mov eax, dword ptr [0xbfd65c]
004f6b9a push dword ptr [edi + 4]
004f6b9d push dword ptr [edi]
004f6b9f mov ecx, dword ptr [eax + 0x18190]
004f6ba5 call 0x7aee40
004f6baa cmp eax, 4
004f6bad jge 0x4f6bb9
004f6baf mov dword ptr [esi + 0x17c], 3
004f6bb9 movss xmm0, dword ptr [esi + 0x28c]
004f6bc1 ucomiss xmm0, dword ptr [0xc02fec]
004f6bc8 lahf
004f6bc9 test ah, 0x44
004f6bcc jp 0x4f6d0e
004f6bd2 movss xmm0, dword ptr [esi + 0x290]
004f6bda ucomiss xmm0, dword ptr [0xc02ff0]
004f6be1 lahf
004f6be2 test ah, 0x44
004f6be5 jp 0x4f6d0e
004f6beb cmp dword ptr [esi + 0xe6c], -1
004f6bf2 je 0x4f6c6e
004f6bf4 movss xmm1, dword ptr [0xb6a7b0]
004f6bfc xorps xmm2, xmm2
004f6bff mov ecx, esi
004f6c01 call 0x6847e0
004f6c06 test eax, eax
004f6c08 je 0x4f6d0e
004f6c0e lea eax, [esp + 0xc]
004f6c12 xorps xmm2, xmm2
004f6c15 push eax
004f6c16 mov ecx, esi
004f6c18 call 0x6af0c0
004f6c1d movss xmm0, dword ptr [esp + 0xc]
004f6c23 mulss xmm0, dword ptr [0xb6a64c]
004f6c2b movss xmm1, dword ptr [esi + 0x2f4]
004f6c33 mulss xmm0, xmm1
004f6c37 addss xmm0, dword ptr [esi + 0x2b8]
004f6c3f movss dword ptr [esi + 0x2b8], xmm0
004f6c47 movss xmm0, dword ptr [esp + 0x10]
004f6c4d mulss xmm0, dword ptr [0xb6a64c]
004f6c55 mulss xmm0, xmm1
004f6c59 addss xmm0, dword ptr [esi + 0x2bc]
004f6c61 movss dword ptr [esi + 0x2bc], xmm0
004f6c69 jmp 0x4f6d0e
004f6c6e call 0x6c3d90
004f6c73 xor edx, edx
004f6c75 mov ecx, 5
004f6c7a div ecx
004f6c7c test edx, edx
004f6c7e jne 0x4f6d0e
004f6c84 mov ecx, esi
004f6c86 call 0x695680
004f6c8b lea ecx, [esp + 0xc]
004f6c8f movss xmm0, dword ptr [eax + 0x294]
004f6c97 movss xmm1, dword ptr [eax + 0x298]
004f6c9f lea eax, [esp + 0x44]
004f6ca3 subss xmm0, dword ptr [esi + 0x294]
004f6cab subss xmm1, dword ptr [esi + 0x298]
004f6cb3 push eax
004f6cb4 movss dword ptr [esp + 0x10], xmm0
004f6cba movss dword ptr [esp + 0x14], xmm1
004f6cc0 call 0x962560
004f6cc5 movss xmm1, dword ptr [esi + 0x2f4]
004f6ccd movss xmm2, dword ptr [eax + 4]
004f6cd2 movss xmm0, dword ptr [eax]
004f6cd6 mulss xmm0, dword ptr [0xb6a50c]
004f6cde mulss xmm2, dword ptr [0xb6a50c]
004f6ce6 mulss xmm0, xmm1
004f6cea mulss xmm2, xmm1
004f6cee addss xmm0, dword ptr [esi + 0x2b8]
004f6cf6 addss xmm2, dword ptr [esi + 0x2bc]
004f6cfe movss dword ptr [esi + 0x2b8], xmm0
004f6d06 movss dword ptr [esi + 0x2bc], xmm2
004f6d0e mov edi, dword ptr [0xbfd65c]
004f6d14 mov ecx, dword ptr [edi + 0x1a30dc]
004f6d1a mov eax, ecx
004f6d1c and eax, 0x80000003
004f6d21 jns 0x4f6d28
004f6d23 dec eax
004f6d24 or eax, 0xfffffffc
004f6d27 inc eax
004f6d28 cmp eax, 1
004f6d2b jne 0x4f6d89
004f6d2d lea eax, [esp + 0xc]
004f6d31 push eax
004f6d32 call 0x659290
004f6d37 add esp, 4
004f6d3a movss xmm2, dword ptr [eax + 4]
004f6d3f movss xmm0, dword ptr [eax]
004f6d43 mulss xmm0, dword ptr [0xb6a4c4]
004f6d4b mulss xmm2, dword ptr [0xb6a4c4]
004f6d53 addss xmm0, dword ptr [esi + 0xb00]
004f6d5b addss xmm2, dword ptr [esi + 0xb04]
004f6d63 mulss xmm0, dword ptr [0xb6a434]
004f6d6b mulss xmm2, dword ptr [0xb6a434]
004f6d73 movss dword ptr [esi + 0xb00], xmm0
004f6d7b movss dword ptr [esi + 0xb04], xmm2
004f6d83 mov ecx, dword ptr [edi + 0x1a30dc]
004f6d89 mov eax, ecx
004f6d8b mov ecx, 3
004f6d90 cdq
004f6d91 idiv ecx
004f6d93 cmp edx, 2
004f6d96 jne 0x4f6e78
004f6d9c cmp dword ptr [esi + 0x34], 0x43
004f6da0 je 0x4f6e2e
004f6da6 movss xmm2, dword ptr [esi + 0x298]
004f6dae movss xmm0, dword ptr [0xb6abd0]
004f6db6 comiss xmm0, xmm2
004f6db9 movss xmm1, dword ptr [0xb6a278]
004f6dc1 jbe 0x4f6dd1
004f6dc3 movss xmm0, dword ptr [esi + 0xb04]
004f6dcb addss xmm0, xmm1
004f6dcf jmp 0x4f6de6
004f6dd1 comiss xmm2, dword ptr [0xb6ac6c]
004f6dd8 jbe 0x4f6dee
004f6dda movss xmm0, dword ptr [esi + 0xb04]
004f6de2 subss xmm0, xmm1
004f6de6 movss dword ptr [esi + 0xb04], xmm0
004f6dee movss xmm2, dword ptr [esi + 0x294]
004f6df6 comiss xmm2, dword ptr [0xb6ac94]
004f6dfd jbe 0x4f6e0d
004f6dff movss xmm0, dword ptr [esi + 0xb00]
004f6e07 subss xmm0, xmm1
004f6e0b jmp 0x4f6e26
004f6e0d movss xmm0, dword ptr [0xb6aad4]
004f6e15 comiss xmm0, xmm2
004f6e18 jbe 0x4f6e2e
004f6e1a movss xmm0, dword ptr [esi + 0xb00]
004f6e22 addss xmm0, xmm1
004f6e26 movss dword ptr [esi + 0xb00], xmm0
004f6e2e movss xmm0, dword ptr [esi + 0xb00]
004f6e36 lea eax, [esp + 0x18]
004f6e3a addss xmm0, xmm0
004f6e3e mov ecx, esi
004f6e40 push 0
004f6e42 push eax
004f6e43 movss dword ptr [esp + 0x20], xmm0
004f6e49 movss xmm0, dword ptr [esi + 0xb04]
004f6e51 addss xmm0, xmm0
004f6e55 movss dword ptr [esp + 0x24], xmm0
004f6e5b call 0x422b60
004f6e60 movss xmm0, dword ptr [esi + 0x2c4]
004f6e68 mulss xmm0, dword ptr [0xb6a4c4]
004f6e70 movss dword ptr [esi + 0x2c4], xmm0
004f6e78 cmp dword ptr [esi + 0x28], 0xf9
004f6e7f jne 0x4f6ebc
004f6e81 cmp byte ptr [esi + 0x16b], 0
004f6e88 je 0x4f6ebc
004f6e8a lea ecx, [esp + 0x90]
004f6e91 mov dword ptr [esp + 0x18], 0x41000000
004f6e99 mov dword ptr [esp + 0x1c], 0x40c00000
004f6ea1 call 0x430d70
004f6ea6 push eax
004f6ea7 push 9
004f6ea9 lea eax, [esp + 0x20]
004f6ead mov ecx, esi
004f6eaf push eax
004f6eb0 lea eax, [esi + 0x294]
004f6eb6 push eax
004f6eb7 call 0x6a1a20
004f6ebc mov ecx, dword ptr [esp + 0x1e4]
004f6ec3 pop edi
004f6ec4 pop esi
004f6ec5 xor ecx, esp
004f6ec7 call 0x9eacd7
004f6ecc mov esp, ebp
004f6ece pop ebp
004f6ecf ret
