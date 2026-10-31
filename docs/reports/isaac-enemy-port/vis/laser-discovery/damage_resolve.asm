008ca010 add eax, dword ptr [eax]
008ca012 add cl, al
008ca014 clc 
008ca015 add eax, dword ptr [ebx + 0xff3ffc0]
008ca01b adc dword ptr [ebp - 0x80], ebx
008ca01e mov dword ptr [ebp - 0x88], ecx
008ca024 mov dword ptr [ebp - 0x90], eax
008ca02a je 0x8cb6f2
008ca030 mov eax, dword ptr [edi]
008ca032 mov dword ptr [ebp - 0x70], eax
008ca035 movss xmm0, dword ptr [eax + 0x2c8]
008ca03d addss xmm0, dword ptr [edx + 0x2c8]
008ca045 mov eax, dword ptr [edx + 0x3d0]
008ca04b movss dword ptr [ebp - 0xbc], xmm0
008ca053 nop dword ptr [eax]
008ca057 nop word ptr [eax + eax]
008ca060 movss xmm0, dword ptr [eax + ecx*8 + 8]
008ca066 movss dword ptr [ebp - 0x98], xmm0
008ca06e movss xmm0, dword ptr [eax + ecx*8 + 0xc]
008ca074 mov ecx, edx
008ca076 movss dword ptr [ebp - 0x78], xmm0
008ca07b call 0x4275d0
008ca080 mov edx, dword ptr [ebp - 0x7c]
008ca083 mov ecx, dword ptr [ebp - 0x88]
008ca089 test al, al
008ca08b jne 0x8ca15f
008ca091 mov eax, dword ptr [ebp - 0xb8]
008ca097 sub eax, edx
008ca099 sar eax, 3
008ca09c sub eax, 2
008ca09f cmp ecx, eax
008ca0a1 jne 0x8ca15f
008ca0a7 mov eax, dword ptr [ebp - 0x74]
008ca0aa cmp byte ptr [eax + 0x466], 0
008ca0b1 jne 0x8ca15f
008ca0b7 xorps xmm0, xmm0
008ca0ba comiss xmm0, dword ptr [eax + 0x420]
008ca0c1 jb 0x8ca15f
008ca0c7 movss xmm1, dword ptr [ebp - 0x78]
008ca0cc subss xmm1, dword ptr [edx + ecx*8 + 4]
008ca0d2 movss xmm2, dword ptr [ebp - 0x98]
008ca0da subss xmm2, dword ptr [edx + ecx*8]
008ca0df movaps xmm0, xmm1
008ca0e2 movss dword ptr [ebp - 0x84], xmm1
008ca0ea mulss xmm0, xmm1
008ca0ee movaps xmm1, xmm2
008ca0f1 movss dword ptr [ebp - 0x8c], xmm2
008ca0f9 mulss xmm1, xmm2
008ca0fd addss xmm0, xmm1
008ca101 call 0x4228c0
008ca106 comiss xmm0, dword ptr [0xb6a18c]
008ca10d jbe 0x8ca130
008ca10f movss xmm1, dword ptr [0xb6aa3c]
008ca117 divss xmm1, xmm0
008ca11b movaps xmm0, xmm1
008ca11e mulss xmm1, dword ptr [ebp - 0x84]
008ca126 mulss xmm0, dword ptr [ebp - 0x8c]
008ca12e jmp 0x8ca140
008ca130 movss xmm0, dword ptr [ebp - 0x8c]
008ca138 movss xmm1, dword ptr [ebp - 0x84]
008ca140 addss xmm1, dword ptr [ebp - 0x78]
008ca145 movss xmm5, dword ptr [ebp - 0x98]
008ca14d mov ecx, dword ptr [ebp - 0x88]
008ca153 addss xmm5, xmm0
008ca157 mov edx, dword ptr [ebp - 0x7c]
008ca15a movaps xmm6, xmm1
008ca15d jmp 0x8ca16c
008ca15f movss xmm6, dword ptr [ebp - 0x78]
008ca164 movss xmm5, dword ptr [ebp - 0x98]
008ca16c mov eax, dword ptr [ebp - 0x70]
008ca16f movaps xmm1, xmm5
008ca172 subss xmm1, dword ptr [edx + ecx*8]
008ca177 movaps xmm7, xmm6
008ca17a subss xmm7, dword ptr [edx + ecx*8 + 4]
008ca180 movss xmm3, dword ptr [eax + 0x294]
008ca188 subss xmm3, dword ptr [edx + ecx*8]
008ca18d movaps xmm0, xmm1
008ca190 movss dword ptr [ebp - 0x78], xmm1
008ca195 mulss xmm0, xmm1
008ca199 movss xmm1, dword ptr [eax + 0x298]
008ca1a1 movaps xmm4, xmm7
008ca1a4 subss xmm1, dword ptr [edx + ecx*8 + 4]
008ca1aa mulss xmm4, xmm7
008ca1ae movss dword ptr [ebp - 0x98], xmm7
008ca1b6 addss xmm4, xmm0
008ca1ba xorps xmm0, xmm0
008ca1bd ucomiss xmm4, xmm0
008ca1c0 lahf 
008ca1c1 test ah, 0x44
008ca1c4 jnp 0x8ca1ed
008ca1c6 movaps xmm0, xmm3
008ca1c9 movaps xmm2, xmm1
008ca1cc mulss xmm0, dword ptr [ebp - 0x78]
008ca1d1 mulss xmm2, xmm7
008ca1d5 addss xmm2, xmm0
008ca1d9 xorps xmm0, xmm0
008ca1dc divss xmm2, xmm4
008ca1e0 comiss xmm0, xmm2
008ca1e3 movss dword ptr [ebp - 0x84], xmm2
008ca1eb jbe 0x8ca20e
008ca1ed mulss xmm1, xmm1
008ca1f1 mulss xmm3, xmm3
008ca1f5 movss dword ptr [ebp - 0x84], xmm0
008ca1fd addss xmm1, xmm3
008ca201 movss dword ptr [ebp - 0x9c], xmm1
008ca209 jmp 0x8ca29a
008ca20e movss xmm3, dword ptr [0xb6a614]
008ca216 comiss xmm2, xmm3
008ca219 mov eax, dword ptr [ebp - 0x70]
008ca21c jbe 0x8ca254
008ca21e movss xmm0, dword ptr [eax + 0x294]
008ca226 movss xmm1, dword ptr [eax + 0x298]
008ca22e subss xmm0, xmm5
008ca232 subss xmm1, xmm6
008ca236 movss dword ptr [ebp - 0x84], xmm3
008ca23e mulss xmm0, xmm0
008ca242 mulss xmm1, xmm1
008ca246 addss xmm1, xmm0
008ca24a movss dword ptr [ebp - 0x9c], xmm1
008ca252 jmp 0x8ca29a
008ca254 movss xmm1, dword ptr [eax + 0x294]
008ca25c movaps xmm0, xmm2
008ca25f mulss xmm0, dword ptr [ebp - 0x78]
008ca264 addss xmm0, dword ptr [edx + ecx*8]
008ca269 subss xmm1, xmm0
008ca26d movaps xmm0, xmm2
008ca270 movss xmm2, dword ptr [eax + 0x298]
008ca278 mulss xmm0, xmm7
008ca27c mulss xmm1, xmm1
008ca280 addss xmm0, dword ptr [edx + ecx*8 + 4]
008ca286 subss xmm2, xmm0
008ca28a mulss xmm2, xmm2
008ca28e addss xmm2, xmm1
008ca292 movss dword ptr [ebp - 0x9c], xmm2
008ca29a movaps xmm0, xmm4
008ca29d call 0x4228c0
008ca2a2 mov ecx, dword ptr [ebp - 0x88]
008ca2a8 movaps xmm2, xmm0
008ca2ab mov edx, dword ptr [ebp - 0x74]
008ca2ae movss dword ptr [ebp - 0x8c], xmm2
008ca2b6 test ecx, ecx
008ca2b8 jne 0x8ca3c8
008ca2be mov ecx, edx
008ca2c0 call 0x8c5940
008ca2c5 test al, al
008ca2c7 je 0x8ca3af
008ca2cd movss xmm0, dword ptr [edx + 0x36c]
008ca2d5 mulss xmm0, dword ptr [0xb6a230]
008ca2dd movss dword ptr [ebp - 0xc4], xmm0
008ca2e5 call 0x411fe0
008ca2ea mov eax, dword ptr [ebp - 0x7c]
008ca2ed mulss xmm0, dword ptr [0xb6a9b0]
008ca2f5 movss xmm1, dword ptr [eax]
008ca2f9 mov eax, dword ptr [ebp - 0x70]
008ca2fc subss xmm1, xmm0
008ca300 movss xmm0, dword ptr [ebp - 0xc4]
008ca308 subss xmm1, dword ptr [eax + 0x294]
008ca310 movss dword ptr [ebp - 0xc8], xmm1
008ca318 call 0x412010
008ca31d mulss xmm0, dword ptr [0xb6a9b0]
008ca325 xorps xmm3, xmm3
008ca328 mov eax, dword ptr [ebp - 0x7c]
008ca32b mov ecx, dword ptr [ebp - 0x70]
008ca32e movss xmm1, dword ptr [ebp - 0x9c]
008ca336 mov edx, dword ptr [ebp - 0x74]
008ca339 movss xmm2, dword ptr [eax + 4]
008ca33e subss xmm2, xmm0
008ca342 movss xmm0, dword ptr [ebp - 0xc8]
008ca34a mulss xmm0, xmm0
008ca34e subss xmm2, dword ptr [ecx + 0x298]
008ca356 mov ecx, dword ptr [ebp - 0x88]
008ca35c mulss xmm2, xmm2
008ca360 addss xmm2, xmm0
008ca364 comiss xmm1, xmm2
008ca367 jbe 0x8ca374
008ca369 movaps xmm1, xmm2
008ca36c movss dword ptr [ebp - 0x84], xmm3
008ca374 movss xmm2, dword ptr [ebp - 0x8c]
008ca37c movss xmm0, dword ptr [ebp - 0xbc]
008ca384 mulss xmm0, xmm0
008ca388 comiss xmm0, xmm1
008ca38b ja 0x8ca3d8
008ca38d addss xmm2, dword ptr [ebp - 0x80]
008ca392 inc ecx
008ca393 mov dword ptr [ebp - 0x88], ecx
008ca399 movss dword ptr [ebp - 0x80], xmm2
008ca39e cmp ecx, dword ptr [ebp - 0x90]
008ca3a4 jb 0x8ca060
008ca3aa jmp 0x8cb6f2
008ca3af movss xmm1, dword ptr [ebp - 0x9c]
008ca3b7 xorps xmm3, xmm3
008ca3ba mov ecx, dword ptr [ebp - 0x88]
008ca3c0 mov eax, dword ptr [edx + 0x3d0]
008ca3c6 jmp 0x8ca37c
008ca3c8 movss xmm1, dword ptr [ebp - 0x9c]
008ca3d0 xorps xmm3, xmm3
008ca3d3 mov eax, dword ptr [ebp - 0x7c]
008ca3d6 jmp 0x8ca37c
008ca3d8 mov ecx, dword ptr [ebp - 0x70]
008ca3db mov eax, dword ptr [ecx + 0x28]
008ca3de cmp eax, 9
008ca3e1 jne 0x8ca403
008ca3e3 mov dword ptr [ecx + 0x388], 0
008ca3ed mov dword ptr [ecx + 0x38c], 0
008ca3f7 mov byte ptr [ecx + 0x16b], 1
008ca3fe jmp 0x8cb6f2
008ca403 cmp eax, 0x3e8
008ca408 jne 0x8ca416
008ca40a mov byte ptr [ecx + 0x16b], 1
008ca411 jmp 0x8cb6f2
008ca416 movss xmm0, dword ptr [ecx + 0x2c8]
008ca41e mulss xmm0, xmm0
008ca422 movss dword ptr [ebp - 0x90], xmm0
008ca42a movaps xmm0, xmm1
008ca42d call 0x4228c0
008ca432 mov eax, dword ptr [ebp - 0x74]
008ca435 movaps xmm1, xmm0
008ca438 movss xmm0, dword ptr [ebp - 0x90]
008ca440 subss xmm1, dword ptr [eax + 0x2c8]
008ca448 mulss xmm1, xmm1
008ca44c comiss xmm0, xmm1
008ca44f jbe 0x8ca462
008ca451 subss xmm0, xmm1
008ca455 call 0x4228c0
008ca45a mov eax, dword ptr [ebp - 0x74]
008ca45d movaps xmm5, xmm0
008ca460 jmp 0x8ca465
008ca462 xorps xmm5, xmm5
008ca465 movss xmm0, dword ptr [ebp - 0x8c]
008ca46d movss xmm3, dword ptr [ebp - 0x78]
008ca472 movaps xmm4, xmm0
008ca475 mulss xmm4, dword ptr [ebp - 0x84]
008ca47d mov ecx, dword ptr [ebp - 0x88]
008ca483 divss xmm3, xmm0
008ca487 mov edx, dword ptr [eax + 0x3d0]
008ca48d movaps xmm2, xmm4
008ca490 subss xmm4, xmm5
008ca494 addss xmm2, dword ptr [ebp - 0x80]
008ca499 movss dword ptr [ebp - 0x78], xmm3
008ca49e movaps xmm6, xmm2
008ca4a1 movss dword ptr [ebp - 0x8c], xmm2
008ca4a9 movss xmm2, dword ptr [ebp - 0x98]
008ca4b1 subss xmm6, xmm5
008ca4b5 divss xmm2, xmm0
008ca4b9 movss xmm0, dword ptr [eax + 0x494]
008ca4c1 movaps xmm5, xmm4
008ca4c4 comiss xmm0, xmm6
008ca4c7 mulss xmm5, xmm3
008ca4cb mulss xmm4, xmm2
008ca4cf addss xmm5, dword ptr [edx + ecx*8]
008ca4d4 movss dword ptr [ebp - 0x98], xmm2
008ca4dc addss xmm4, dword ptr [edx + ecx*8 + 4]
008ca4e2 movss dword ptr [ebp - 0x70], xmm5
008ca4e7 movss dword ptr [ebp - 0x7c], xmm4
008ca4ec jbe 0x8ca516
008ca4ee movss dword ptr [eax + 0x494], xmm6
008ca4f6 movss dword ptr [eax + 0x498], xmm5
008ca4fe movss dword ptr [eax + 0x49c], xmm4
008ca506 movss dword ptr [eax + 0x4a0], xmm3
008ca50e movss dword ptr [eax + 0x4a4], xmm2
008ca516 mov edx, dword ptr [ebp - 0x94]
008ca51c lea ecx, [ebp - 0x1e0]
008ca522 push 0xbc4bb0
008ca527 call 0x412050
008ca52c add esp, 4
008ca52f mov ecx, dword ptr [eax]
008ca531 or ecx, dword ptr [eax + 4]
008ca534 jne 0x8ca542
008ca536 mov ecx, dword ptr [eax + 8]
008ca539 or ecx, dword ptr [eax + 0xc]
008ca53c je 0x8ca658
008ca542 mov eax, dword ptr [ebp - 0x74]
008ca545 cmp byte ptr [eax + 0x3ac], 0
008ca54c jne 0x8ca572
008ca54e movss xmm1, dword ptr [0xb6a8cc]
008ca556 xorps xmm2, xmm2
008ca559 mov ecx, eax
008ca55b call 0x6847e0
008ca560 test eax, eax
008ca562 je 0x8ca658
008ca568 movss xmm4, dword ptr [ebp - 0x7c]
008ca56d movss xmm5, dword ptr [ebp - 0x70]
008ca572 mov ecx, dword ptr [0xbfd65c]
008ca578 lea eax, [ebp - 0x148]
008ca57e movss xmm3, dword ptr [0xb6a9ac]
008ca586 sub esp, 0xc
008ca589 movss dword ptr [ebp - 0x148], xmm5
008ca591 movss dword ptr [ebp - 0x144], xmm4
008ca599 mov ecx, dword ptr [ecx + 0x18190]
008ca59f mov dword ptr [esp + 8], 0x41700000
008ca5a7 mov dword ptr [esp + 4], 0x41700000
008ca5af mov dword ptr [esp], 0x41700000
008ca5b6 push eax
008ca5b7 lea eax, [ebp - 0x190]
008ca5bd push eax
008ca5be call 0x7cec10
008ca5c3 mov eax, dword ptr [ebp - 0x190]
008ca5c9 mov ecx, dword ptr [ebp - 0x18c]
008ca5cf mov dword ptr [ebp - 0x148], eax
008ca5d5 mov dword ptr [ebp - 0x144], ecx
008ca5db call 0x6c3d90
008ca5e0 mov edx, dword ptr [ebp - 0x74]
008ca5e3 mov ecx, dword ptr [0xbfd65c]
008ca5e9 push 0
008ca5eb push 0xbeaaec
008ca5f0 push 0xbeab18
008ca5f5 push 0
008ca5f7 push eax
008ca5f8 push 0
008ca5fa push dword ptr [edx + 0x320]
008ca600 lea eax, [ebp - 0x148]
008ca606 push 0xc02fec
008ca60b push eax
008ca60c push 0x35
008ca60e push 0x3e8
008ca613 call 0x422e20
008ca618 push eax
008ca619 call 0x9ec34c
008ca61e movss xmm1, dword ptr [0xbc7a28]
008ca626 mov ecx, eax
008ca628 movss xmm0, dword ptr [0xbc7a2c]
008ca630 add esp, 0x14
008ca633 mulss xmm1, dword ptr [0xb6a434]
008ca63b mulss xmm0, dword ptr [0xb6a434]
008ca643 mov eax, dword ptr [ecx]
008ca645 movss dword ptr [ecx + 0xd8], xmm1
008ca64d movss dword ptr [ecx + 0xdc], xmm0
008ca655 call dword ptr [eax + 0xc]
008ca658 mov edx, dword ptr [edi]
008ca65a mov ecx, dword ptr [edx + 0x28]
008ca65d lea eax, [ecx - 0xa]
008ca660 cmp eax, 0x3dd
008ca665 ja 0x8ca9bc
008ca66b cmp ecx, 0x21
008ca66e je 0x8ca9bc
008ca674 cmp ecx, 0x11
008ca677 je 0x8ca9bc
008ca67d cmp ecx, 0x124
008ca683 je 0x8ca9bc
008ca689 cmp ecx, 0x375
008ca68f jne 0x8ca697
008ca691 cmp dword ptr [edx + 0x2c], 0xa
008ca695 jmp 0x8ca6b5
008ca697 cmp ecx, 0x3c0
008ca69d je 0x8ca9bc
008ca6a3 cmp ecx, 0x3c5
008ca6a9 je 0x8ca9bc
008ca6af cmp ecx, 0xf5
008ca6b5 je 0x8ca9bc
008ca6bb cmp byte ptr [edx + 0x16b], 0
008ca6c2 jne 0x8ca9bc
008ca6c8 push 0xbc4830
008ca6cd push ecx
008ca6ce push 0xbc4b50
008ca6d3 mov edx, 0xbc4950
008ca6d8 lea ecx, [ebp - 0x1f0]
008ca6de call 0x427220
008ca6e3 add esp, 8
008ca6e6 lea ecx, [ebp - 0x200]
008ca6ec mov edx, eax
008ca6ee call 0x427220
008ca6f3 mov edx, dword ptr [ebp - 0x94]
008ca6f9 lea ecx, [ebp - 0x210]
008ca6ff add esp, 4
008ca702 push eax
008ca703 call 0x412050
008ca708 add esp, 4
008ca70b mov ecx, dword ptr [eax]
008ca70d or ecx, dword ptr [eax + 4]
008ca710 jne 0x8ca71e
008ca712 mov ecx, dword ptr [eax + 8]
008ca715 or ecx, dword ptr [eax + 0xc]
008ca718 je 0x8ca9bc
008ca71e mov eax, dword ptr [ebp - 0x74]
008ca721 cmp byte ptr [eax + 0x3ac], 0
008ca728 jne 0x8ca744
008ca72a movss xmm1, dword ptr [0xb6a8cc]
008ca732 xorps xmm2, xmm2
008ca735 mov ecx, eax
008ca737 call 0x6847e0
008ca73c test eax, eax
008ca73e je 0x8ca9bc
008ca744 mov eax, dword ptr [edi]
008ca746 movss xmm1, dword ptr [ebp - 0x7c]
008ca74b movss xmm2, dword ptr [ebp - 0x70]
008ca750 subss xmm1, dword ptr [eax + 0x298]
008ca758 subss xmm2, dword ptr [eax + 0x294]
008ca760 movaps xmm0, xmm1
008ca763 movss dword ptr [ebp - 0x7c], xmm1
008ca768 mulss xmm0, xmm1
008ca76c movaps xmm1, xmm2
008ca76f mulss xmm1, xmm2
008ca773 movss dword ptr [ebp - 0x70], xmm2
008ca778 addss xmm0, xmm1
008ca77c call 0x4228c0
008ca781 mov eax, dword ptr [edi]
008ca783 movss xmm1, dword ptr [eax + 0x2c8]
008ca78b comiss xmm0, xmm1
008ca78e jbe 0x8ca7b8
008ca790 comiss xmm0, dword ptr [0xb6a18c]
008ca797 jbe 0x8ca7b8
008ca799 divss xmm1, xmm0
008ca79d movaps xmm0, xmm1
008ca7a0 mulss xmm0, dword ptr [ebp - 0x70]
008ca7a5 movss dword ptr [ebp - 0x70], xmm0
008ca7aa movss xmm0, dword ptr [ebp - 0x7c]
008ca7af mulss xmm0, xmm1
008ca7b3 movss dword ptr [ebp - 0x7c], xmm0
008ca7b8 mov edx, dword ptr [ebp - 0x94]
008ca7be lea ecx, [ebp - 0x220]
008ca7c4 push 0xbc4b50
008ca7c9 call 0x412050
008ca7ce add esp, 4
008ca7d1 mov ecx, dword ptr [eax]
008ca7d3 or ecx, dword ptr [eax + 4]
008ca7d6 jne 0x8ca81a
008ca7d8 mov ecx, dword ptr [eax + 8]
008ca7db or ecx, dword ptr [eax + 0xc]
008ca7de jne 0x8ca81a
008ca7e0 mov edx, dword ptr [ebp - 0x94]
008ca7e6 lea ecx, [ebp - 0x230]
008ca7ec push 0xbc4830
008ca7f1 call 0x412050
008ca7f6 add esp, 4
008ca7f9 mov ecx, dword ptr [eax]
008ca7fb or ecx, dword ptr [eax + 4]
008ca7fe jne 0x8ca811
008ca800 mov ecx, dword ptr [eax + 8]
008ca803 or ecx, dword ptr [eax + 0xc]
008ca806 jne 0x8ca811
008ca808 mov dword ptr [ebp - 0x80], 0x13
008ca80f jmp 0x8ca821
008ca811 mov dword ptr [ebp - 0x80], 0x30
008ca818 jmp 0x8ca821
008ca81a mov dword ptr [ebp - 0x80], 0x1a
008ca821 lea eax, [ebp - 0x240]
008ca827 mov edx, 0xbc4a00
008ca82c push eax
008ca82d push ecx
008ca82e push 0xbc46b0
008ca833 push ecx
008ca834 push 0xbc46c0
008ca839 push ecx
008ca83a push 0xbc4890
008ca83f push ecx
008ca840 push 0xbc4a30
008ca845 push ecx
008ca846 push 0xbc4ce0
008ca84b push ecx
008ca84c push 0xbc49e0
008ca851 lea ecx, [ebp - 0x250]
008ca857 call 0x427220
008ca85c add esp, 8
008ca85f lea ecx, [ebp - 0x2b0]
008ca865 mov edx, eax
008ca867 call 0x427220
008ca86c add esp, 8
008ca86f lea ecx, [ebp - 0x260]
008ca875 mov edx, eax
008ca877 call 0x427220
008ca87c add esp, 8
008ca87f lea ecx, [ebp - 0x270]
008ca885 mov edx, eax
008ca887 call 0x427220
008ca88c add esp, 8
008ca88f lea ecx, [ebp - 0x280]
008ca895 mov edx, eax
008ca897 call 0x427220
008ca89c add esp, 8
008ca89f lea ecx, [ebp - 0x290]
008ca8a5 mov edx, eax
008ca8a7 call 0x427220
008ca8ac add esp, 8
008ca8af mov ecx, eax
008ca8b1 call 0x57f3a0
008ca8b6 mov edx, dword ptr [ebp - 0x94]
008ca8bc lea ecx, [ebp - 0x1c0]
008ca8c2 push eax
008ca8c3 call 0x412050
008ca8c8 add esp, 4
008ca8cb call 0x6c3d90
008ca8d0 mov ecx, dword ptr [edi]
008ca8d2 push eax
008ca8d3 mov eax, dword ptr [ebp - 0x74]
008ca8d6 push 0
008ca8d8 movss xmm0, dword ptr [ecx + 0x294]
008ca8e0 movss xmm1, dword ptr [ecx + 0x298]
008ca8e8 push dword ptr [eax + 0x320]
008ca8ee addss xmm0, dword ptr [ebp - 0x70]
008ca8f3 addss xmm1, dword ptr [ebp - 0x7c]
008ca8f8 mov ecx, dword ptr [0xbfd65c]
008ca8fe lea eax, [ebp - 0x188]
008ca904 push 0xc02fec
008ca909 push eax
008ca90a push dword ptr [ebp - 0x80]
008ca90d movss dword ptr [ebp - 0x188], xmm0
008ca915 push 2
008ca917 movss dword ptr [ebp - 0x184], xmm1
008ca91f call 0x422e20
008ca924 mov ecx, eax
008ca926 mov dword ptr [ebp - 0x70], eax
008ca929 mov edx, dword ptr [eax]
008ca92b call dword ptr [edx + 0xc]
008ca92e movups xmm0, xmmword ptr [ebp - 0x1c0]
008ca935 sub esp, 0x10
008ca938 mov ecx, esp
008ca93a movups xmmword ptr [ecx], xmm0
008ca93d mov ecx, dword ptr [ebp - 0x70]
008ca940 call 0x650280
008ca945 mov ecx, dword ptr [ebp - 0x70]
008ca948 mov edx, dword ptr [ebp - 0x74]
008ca94b push ecx
008ca94c mov eax, dword ptr [ecx]
008ca94e movss xmm0, dword ptr [edx + 0x2e0]
008ca956 movss dword ptr [esp], xmm0
008ca95b call dword ptr [eax + 0x3c]
008ca95e mov eax, dword ptr [ebp - 0x74]
008ca961 movss xmm0, dword ptr [eax + 0x430]
008ca969 maxss xmm0, dword ptr [0xb6a214]
008ca971 mov eax, dword ptr [ebp - 0x70]
008ca974 mov ecx, eax
008ca976 movss dword ptr [eax + 0x374], xmm0
008ca97e movss dword ptr [eax + 0x370], xmm0
008ca986 call 0x651770
008ca98b mov edx, dword ptr [ebp - 0x70]
008ca98e mov ecx, dword ptr [edi]
008ca990 inc dword ptr [0xbffe08]
008ca996 push 1
008ca998 mov eax, dword ptr [edx]
008ca99a mov dword ptr [ebp - 0x90], ecx
008ca9a0 push ecx
008ca9a1 mov ecx, edx
008ca9a3 call dword ptr [eax + 0x58]
008ca9a6 mov ecx, dword ptr [ebp - 0x90]
008ca9ac push 0
008ca9ae push dword ptr [ebp - 0x70]
008ca9b1 mov eax, dword ptr [ecx]
008ca9b3 call dword ptr [eax + 0x58]
008ca9b6 dec dword ptr [0xbffe08]
008ca9bc movss xmm0, dword ptr [ebp - 0xcc]
008ca9c4 mov ecx, dword ptr [ebp - 0x74]
008ca9c7 movss dword ptr [ebp - 0x90], xmm0
008ca9cf call 0x4275d0
008ca9d4 test al, al
008ca9d6 jne 0x8caaa3
008ca9dc mov edx, dword ptr [ebp - 0x94]
008ca9e2 lea ecx, [ebp - 0x2a0]
008ca9e8 push 0xbc4bc0
008ca9ed call 0x412050
008ca9f2 add esp, 4
008ca9f5 mov ecx, dword ptr [eax]
008ca9f7 or ecx, dword ptr [eax + 4]
008ca9fa jne 0x8caa1e
008ca9fc mov ecx, dword ptr [eax + 8]
008ca9ff or ecx, dword ptr [eax + 0xc]
008caa02 jne 0x8caa1e
008caa04 movss xmm1, dword ptr [ebp - 0xcc]
008caa0c movss xmm2, dword ptr [ebp - 0x8c]
008caa14 movss xmm0, dword ptr [0xb6a614]
008caa1c jmp 0x8caa55
008caa1e movss xmm2, dword ptr [ebp - 0x8c]
008caa26 movaps xmm1, xmm2
008caa29 movss xmm0, dword ptr [0xb6a614]
008caa31 minss xmm1, dword ptr [0xb6accc]
008caa39 mulss xmm1, dword ptr [0xb6a8f4]
008caa41 divss xmm1, dword ptr [0xb6accc]
008caa49 addss xmm1, xmm0
008caa4d mulss xmm1, dword ptr [ebp - 0xcc]
008caa55 mov edx, dword ptr [ebp - 0x94]
008caa5b lea ecx, [ebp - 0x2c0]
008caa61 push 0xbc4c60
008caa66 call 0x412050
008caa6b add esp, 4
008caa6e mov ecx, dword ptr [eax]
008caa70 or ecx, dword ptr [eax + 4]
008caa73 jne 0x8caa7d
008caa75 mov ecx, dword ptr [eax + 8]
008caa78 or ecx, dword ptr [eax + 0xc]
008caa7b je 0x8caa99
008caa7d minss xmm2, dword ptr [0xb6ac14]
008caa85 divss xmm2, dword ptr [0xb6ac14]
008caa8d subss xmm0, xmm2
008caa91 addss xmm0, xmm0
008caa95 mulss xmm1, xmm0
008caa99 maxss xmm1, dword ptr [0xb6a2cc]
008caaa1 jmp 0x8caaab
008caaa3 movss xmm1, dword ptr [ebp - 0x90]
008caaab push dword ptr [edi]
008caaad mov ecx, dword ptr [ebp - 0x74]
008caab0 movaps xmm2, xmm1
008caab3 call 0x8d6600
008caab8 mov ecx, dword ptr [ebp - 0x74]
008caabb call 0x4275d0
008caac0 mov ecx, dword ptr [ebp - 0x74]
008caac3 test al, al
008caac5 je 0x8caad1
008caac7 cmp dword ptr [ecx + 0x30], 2
008caacb jne 0x8cac88
008caad1 mov edx, dword ptr [edi]
008caad3 mov eax, dword ptr [edx + 0x160]
008caad9 and eax, 0x4000000
008caade or eax, 0
008caae1 je 0x8cab01
008caae3 cmp dword ptr [edx + 0x28], 4
008caae7 jne 0x8cac88
008caaed mov eax, dword ptr [ecx + 0x320]
008caaf3 test eax, eax
008caaf5 je 0x8cac88
008caafb cmp dword ptr [eax + 0x28], 1
008caaff jmp 0x8cab1f
008cab01 cmp dword ptr [edx + 0x28], 1
008cab05 jne 0x8cab25
008cab07 mov eax, dword ptr [ecx + 0x320]
008cab0d test eax, eax
008cab0f je 0x8cab25
008cab11 mov eax, dword ptr [eax + 0x160]
008cab17 and eax, 0x20000000
008cab1c or eax, 0
008cab1f jne 0x8cac88
008cab25 cmp dword ptr [ecx + 0x30], 2
008cab29 movss xmm2, dword ptr [ebp - 0x78]
008cab2e movss xmm1, dword ptr [ebp - 0x98]
008cab36 movss dword ptr [ebp - 0x70], xmm2
008cab3b movss dword ptr [ebp - 0x7c], xmm1
008cab40 jne 0x8caba9
008cab42 movss xmm1, dword ptr [ecx + 0x2bc]
008cab4a movss xmm2, dword ptr [ecx + 0x2b8]
008cab52 movaps xmm0, xmm1
008cab55 mulss xmm0, xmm1
008cab59 movss dword ptr [ebp - 0x7c], xmm1
008cab5e movaps xmm1, xmm2
008cab61 mulss xmm1, xmm2
008cab65 movss dword ptr [ebp - 0x70], xmm2
008cab6a addss xmm0, xmm1
008cab6e call 0x4228c0
008cab73 comiss xmm0, dword ptr [0xb6a18c]
008cab7a jbe 0x8caba4
008cab7c movss xmm1, dword ptr [0xb6a614]
008cab84 divss xmm1, xmm0
008cab88 movss xmm0, dword ptr [ebp - 0x70]
008cab8d mulss xmm0, xmm1
008cab91 movss dword ptr [ebp - 0x70], xmm0
008cab96 movss xmm0, dword ptr [ebp - 0x7c]
008cab9b mulss xmm0, xmm1
008cab9f movss dword ptr [ebp - 0x7c], xmm0
008caba4 mov ecx, dword ptr [ebp - 0x74]
008caba7 mov edx, dword ptr [edi]
008caba9 push ecx
008cabaa mov ecx, edx
008cabac call 0x689640
008cabb1 movss xmm1, dword ptr [ebp - 0x70]
008cabb6 xorps xmm3, xmm3
008cabb9 comiss xmm0, xmm3
008cabbc movss xmm2, dword ptr [ebp - 0x7c]
008cabc1 jbe 0x8cabcb
008cabc3 divss xmm1, xmm0
008cabc7 divss xmm2, xmm0
008cabcb mov eax, dword ptr [ebp - 0x74]
008cabce movss xmm0, dword ptr [eax + 0x2d4]
008cabd6 mov eax, dword ptr [edi]
008cabd8 mulss xmm0, dword ptr [0xb6a758]
008cabe0 mov eax, dword ptr [eax + 0x28]
008cabe3 mulss xmm1, xmm0
008cabe7 mulss xmm2, xmm0
008cabeb cmp eax, 1
008cabee je 0x8cabf5
008cabf0 cmp eax, 3
008cabf3 jne 0x8cac05
008cabf5 mulss xmm1, dword ptr [0xb6a350]
008cabfd mulss xmm2, dword ptr [0xb6a350]
008cac05 mov edx, dword ptr [ebp - 0x94]
008cac0b lea ecx, [ebp - 0x1d0]
008cac11 push 0xbc4ae0
008cac16 call 0x412050
008cac1b add esp, 4
008cac1e mov ecx, dword ptr [eax]
008cac20 or ecx, dword ptr [eax + 4]
008cac23 jne 0x8cac2d
008cac25 mov ecx, dword ptr [eax + 8]
008cac28 or ecx, dword ptr [eax + 0xc]
008cac2b je 0x8cac3b
008cac2d movaps xmm0, xmm1
008cac30 addss xmm1, xmm0
008cac34 movaps xmm0, xmm2
008cac37 addss xmm2, xmm0
008cac3b mov ecx, dword ptr [edi]
008cac3d movss xmm4, dword ptr [ecx + 0x2c4]
008cac45 ucomiss xmm4, xmm3
008cac48 lahf 
008cac49 test ah, 0x44
008cac4c jnp 0x8cac8b
008cac4e movss xmm0, dword ptr [ecx + 0x2f4]
008cac56 mulss xmm1, xmm0
008cac5a mulss xmm2, xmm0
008cac5e divss xmm1, xmm4
008cac62 divss xmm2, xmm4
008cac66 addss xmm1, dword ptr [ecx + 0x2b8]
008cac6e addss xmm2, dword ptr [ecx + 0x2bc]
008cac76 movss dword ptr [ecx + 0x2b8], xmm1
008cac7e movss dword ptr [ecx + 0x2bc], xmm2
008cac86 jmp 0x8cac8b
008cac88 xorps xmm3, xmm3
008cac8b mov edx, dword ptr [ebp - 0x74]
008cac8e mov ecx, edx
008cac90 call 0x8c5940
008cac95 test al, al
008cac97 je 0x8cb6f2
008cac9d mov eax, dword ptr [edx + 0x3d0]
008caca3 mov edx, dword ptr [ebp - 0x88]
008caca9 mov ecx, dword ptr [edi]
008cacab movss xmm1, dword ptr [ebp - 0x78]
008cacb0 xorps xmm1, xmmword ptr [0xb6c9b0]
008cacb7 movss xmm0, dword ptr [eax + edx*8 + 0xc]
008cacbd subss xmm0, dword ptr [eax + edx*8 + 4]
008cacc3 movss xmm5, dword ptr [eax + edx*8 + 8]
008cacc9 subss xmm5, dword ptr [eax + edx*8]
008cacce movss xmm3, dword ptr [ecx + 0x294]
008cacd6 movss xmm2, dword ptr [ecx + 0x298]
008cacde mulss xmm0, dword ptr [ebp - 0x84]
008cace6 mulss xmm5, dword ptr [ebp - 0x84]
008cacee addss xmm0, dword ptr [eax + edx*8 + 4]
008cacf4 movss dword ptr [ebp - 0x7c], xmm1
008cacf9 addss xmm5, dword ptr [eax + edx*8]
008cacfe mov edx, dword ptr [ebp - 0x74]
008cad01 subss xmm2, xmm0
008cad05 movss dword ptr [ebp - 0x9c], xmm0
008cad0d subss xmm3, xmm5
008cad11 movss dword ptr [ebp - 0x70], xmm5
008cad16 mulss xmm2, xmm1
008cad1a mulss xmm3, dword ptr [ebp - 0x98]
008cad22 movss xmm1, dword ptr [ecx + 0x2c8]
008cad2a addss xmm3, xmm2
008cad2e movss xmm2, dword ptr [edx + 0x2c8]
008cad36 movaps xmm0, xmm2
008cad39 xorps xmm0, xmmword ptr [0xb6c9b0]
008cad40 movaps xmm4, xmm3
008cad43 addss xmm3, xmm1
008cad47 subss xmm4, xmm1
008cad4b comiss xmm2, xmm3
008cad4e maxss xmm4, xmm0
008cad52 movss dword ptr [ebp - 0x8c], xmm4
008cad5a ja 0x8cad62
008cad5c movss xmm1, xmm2
008cad60 jmp 0x8cad66
008cad62 movss xmm1, xmm3
008cad66 movaps xmm0, xmm4
008cad69 movss dword ptr [ebp - 0x84], xmm1
008cad71 addss xmm0, dword ptr [0xb6a7b0]
008cad79 comiss xmm1, xmm0
008cad7c jbe 0x8cb728
008cad82 cmp dword ptr [edx + 0x70], 0
008cad86 jne 0x8cad9a
008cad88 push 0xa081ec
008cad8d push 3
008cad8f call 0x95e330
008cad94 mov edx, dword ptr [ebp - 0x74]
008cad97 add esp, 8
008cad9a mov eax, dword ptr [edx + 0x6c]
008cad9d cmp dword ptr [eax + 0x80], 0
008cada4 jg 0x8cadb8
008cada6 push 0xa0824c
008cadab push 3
008cadad call 0x95e330
008cadb2 mov edx, dword ptr [ebp - 0x74]
008cadb5 add esp, 8
008cadb8 mov ecx, dword ptr [edx + 0x70]
008cadbb mov eax, dword ptr [ecx + 0x38]
008cadbe test eax, eax
008cadc0 js 0x8cadfe
008cadc2 cmp eax, dword ptr [ecx + 0x1c]
008cadc5 jge 0x8cadfe
008cadc7 mov ecx, eax
008cadc9 mov eax, dword ptr [edx + 0x70]
008cadcc shl ecx, 4
008cadcf add ecx, dword ptr [eax + 0x18]
008cadd2 mov eax, dword ptr [edx + 0x74]
008cadd5 mov dword ptr [ebp - 0xbc], ecx
008caddb mov ecx, dword ptr [edx + 0x70]
008cadde mov edx, dword ptr [ecx + 0x38]
008cade1 mov ecx, dword ptr [ebp - 0xbc]
008cade7 mov eax, dword ptr [eax + edx*4]
008cadea mov edx, dword ptr [ebp - 0x74]
008caded test eax, eax
008cadef js 0x8cadfe
008cadf1 cmp eax, dword ptr [ecx + 8]
008cadf4 jge 0x8cadfe
008cadf6 imul eax, eax, 0x6c
008cadf9 add eax, dword ptr [ecx + 4]
008cadfc jmp 0x8cae00
008cadfe xor eax, eax
008cae00 cmp dword ptr [edx + 0xbc], 0
008cae07 mov dword ptr [ebp - 0x80], eax
008cae0a lea eax, [edx + 0x3c]
008cae0d mov dword ptr [ebp - 0x90], eax
008cae13 jg 0x8cae3a
008cae15 cmp dword ptr [eax + 0x14], 0x10
008cae19 mov ecx, eax
008cae1b jb 0x8cae1f
008cae1d mov ecx, dword ptr [eax]
008cae1f push 0
008cae21 push ecx
008cae22 push 0xa0830c
008cae27 push 3
008cae29 call 0x95e330
008cae2e mov edx, dword ptr [ebp - 0x74]
008cae31 add esp, 0x10
008cae34 mov eax, dword ptr [ebp - 0x90]
008cae3a mov ecx, dword ptr [eax + 0x7c]
008cae3d xorps xmm3, xmm3
008cae40 movups xmm0, xmmword ptr [edx + 0xf4]
008cae47 mov eax, dword ptr [edx + 0x10c]
008cae4d movups xmm7, xmmword ptr [edx + 0xe4]
008cae54 mov dword ptr [ebp - 0x108], eax
008cae5a movups xmmword ptr [ebp - 0x120], xmm0
008cae61 movq xmm0, qword ptr [edx + 0x104]
008cae69 movss xmm2, dword ptr [ecx + 0x58]
008cae6e movq qword ptr [ebp - 0x110], xmm0
008cae76 movups xmmword ptr [ebp - 0x130], xmm7
008cae7d movss xmm0, dword ptr [ebp - 0x12c]
008cae85 mulss xmm0, dword ptr [ecx + 0x4c]
008cae8a movss xmm4, dword ptr [ecx + 0x5c]
008cae8f movss xmm5, dword ptr [ecx + 0x60]
008cae94 movss dword ptr [ebp - 0x12c], xmm0
008cae9c movss xmm0, dword ptr [ebp - 0x128]
008caea4 mulss xmm0, dword ptr [ecx + 0x50]
008caea9 mulss xmm7, dword ptr [ecx + 0x48]
008caeae movss dword ptr [ebp - 0x128], xmm0
008caeb6 movss xmm0, dword ptr [ebp - 0x124]
008caebe mulss xmm0, dword ptr [ecx + 0x54]
008caec3 movss dword ptr [ebp - 0x130], xmm7
008caecb movss dword ptr [ebp - 0x124], xmm0
008caed3 movaps xmm0, xmm2
008caed6 addss xmm0, xmm4
008caeda addss xmm0, xmm5
008caede ucomiss xmm0, xmm3
008caee1 lahf 
008caee2 test ah, 0x44
008caee5 jnp 0x8caf8c
008caeeb movss xmm6, dword ptr [ebp - 0x120]
008caef3 movss xmm1, dword ptr [ecx + 0x64]
008caef8 movaps xmm0, xmm6
008caefb addss xmm0, dword ptr [ebp - 0x11c]
008caf03 addss xmm0, dword ptr [ebp - 0x118]
008caf0b ucomiss xmm0, xmm3
008caf0e lahf 
008caf0f test ah, 0x44
008caf12 jp 0x8caf36
008caf14 movss dword ptr [ebp - 0x120], xmm2
008caf1c movss dword ptr [ebp - 0x11c], xmm4
008caf24 movss dword ptr [ebp - 0x118], xmm5
008caf2c movss dword ptr [ebp - 0x114], xmm1
008caf34 jmp 0x8cafa4
008caf36 addss xmm4, dword ptr [ebp - 0x11c]
008caf3e addss xmm5, dword ptr [ebp - 0x118]
008caf46 addss xmm1, dword ptr [ebp - 0x114]
008caf4e movss xmm0, dword ptr [0xb6a480]
008caf56 addss xmm2, xmm6
008caf5a mulss xmm4, xmm0
008caf5e mulss xmm5, xmm0
008caf62 mulss xmm2, xmm0
008caf66 mulss xmm1, xmm0
008caf6a movss dword ptr [ebp - 0x120], xmm2
008caf72 movss dword ptr [ebp - 0x11c], xmm4
008caf7a movss dword ptr [ebp - 0x118], xmm5
008caf82 movss dword ptr [ebp - 0x114], xmm1
008caf8a jmp 0x8cafa4
008caf8c movss xmm5, dword ptr [ebp - 0x118]
008caf94 movss xmm4, dword ptr [ebp - 0x11c]
008caf9c movss xmm2, dword ptr [ebp - 0x120]
008cafa4 movss xmm0, dword ptr [ebp - 0x108]
008cafac addss xmm0, dword ptr [ecx + 0x70]
008cafb1 movss xmm6, dword ptr [ebp - 0x110]
008cafb9 addss xmm6, dword ptr [ecx + 0x68]
008cafbe movss xmm1, dword ptr [ebp - 0x10c]
008cafc6 addss xmm1, dword ptr [ecx + 0x6c]
008cafcb mov ecx, dword ptr [ebp - 0x80]
008cafce movss dword ptr [ebp - 0x108], xmm0
008cafd6 movups xmm0, xmmword ptr [ebp - 0x130]
008cafdd mov eax, dword ptr [ebp - 0x108]
008cafe3 mulss xmm7, dword ptr [ecx + 0x30]
008cafe8 mov dword ptr [ebp - 0xd8], eax
008cafee movups xmmword ptr [ebp - 0x100], xmm0
008caff5 movups xmm0, xmmword ptr [ebp - 0x120]
008caffc movaps xmmword ptr [ebp - 0x1b0], xmm6
008cb003 movups xmmword ptr [ebp - 0xf0], xmm0
008cb00a movaps xmm0, xmm6
008cb00d movss dword ptr [ebp - 0x100], xmm7
008cb015 unpcklps xmm0, xmm1
008cb018 movss xmm1, dword ptr [ecx + 0x40]
008cb01d movq qword ptr [ebp - 0xe0], xmm0
008cb025 movss xmm0, dword ptr [ebp - 0xfc]
008cb02d mulss xmm0, dword ptr [ecx + 0x34]
008cb032 movss xmm6, dword ptr [ecx + 0x44]
008cb037 movss xmm7, dword ptr [ecx + 0x48]
008cb03c movss dword ptr [ebp - 0xfc], xmm0
008cb044 movss xmm0, dword ptr [ebp - 0xf8]
008cb04c mulss xmm0, dword ptr [ecx + 0x38]
008cb051 movss dword ptr [ebp - 0xf8], xmm0
008cb059 movss xmm0, dword ptr [ebp - 0xf4]
008cb061 mulss xmm0, dword ptr [ecx + 0x3c]
008cb066 movss dword ptr [ebp - 0xf4], xmm0
008cb06e movaps xmm0, xmm1
008cb071 addss xmm0, xmm6
008cb075 addss xmm0, xmm7
008cb079 ucomiss xmm0, xmm3
008cb07c lahf 
008cb07d test ah, 0x44
008cb080 jnp 0x8cb10a
008cb086 movaps xmm0, xmm2
008cb089 addss xmm0, xmm4
008cb08d addss xmm0, xmm5
008cb091 ucomiss xmm0, xmm3
008cb094 lahf 
008cb095 test ah, 0x44
008cb098 jp 0x8cb0b1
008cb09a movss dword ptr [ebp - 0xf0], xmm1
008cb0a2 movss xmm1, dword ptr [ecx + 0x4c]
008cb0a7 movss dword ptr [ebp - 0xe4], xmm1
008cb0af jmp 0x8cb0fa
008cb0b1 movss xmm0, dword ptr [ebp - 0xe4]
008cb0b9 addss xmm1, xmm2
008cb0bd addss xmm0, dword ptr [ecx + 0x4c]
008cb0c2 movss xmm2, dword ptr [0xb6a480]
008cb0ca addss xmm6, dword ptr [ebp - 0xec]
008cb0d2 addss xmm7, dword ptr [ebp - 0xe8]
008cb0da mulss xmm1, xmm2
008cb0de mulss xmm0, xmm2
008cb0e2 movss dword ptr [ebp - 0xf0], xmm1
008cb0ea mulss xmm6, xmm2
008cb0ee mulss xmm7, xmm2
008cb0f2 movss dword ptr [ebp - 0xe4], xmm0
008cb0fa movss dword ptr [ebp - 0xe8], xmm7
008cb102 movss dword ptr [ebp - 0xec], xmm6
008cb10a movss xmm0, dword ptr [ebp - 0xd8]
008cb112 addss xmm0, dword ptr [ecx + 0x58]
008cb117 movaps xmm2, xmmword ptr [ebp - 0x1b0]
008cb11e addss xmm2, dword ptr [ecx + 0x50]
008cb123 movss xmm1, dword ptr [ebp - 0xdc]
008cb12b addss xmm1, dword ptr [ecx + 0x54]
008cb130 movss dword ptr [ebp - 0xd8], xmm0
008cb138 movups xmm0, xmmword ptr [ebp - 0x100]
008cb13f mov eax, dword ptr [ebp - 0xd8]
008cb145 mov dword ptr [ebp - 0x44], eax
008cb148 movups xmmword ptr [ebp - 0x6c], xmm0
008cb14c movups xmm0, xmmword ptr [ebp - 0xf0]
008cb153 unpcklps xmm2, xmm1
008cb156 movups xmmword ptr [ebp - 0x5c], xmm0
008cb15a movss xmm0, dword ptr [edx + 0x2a8]
008cb162 movq qword ptr [ebp - 0x4c], xmm2
008cb167 movss dword ptr [ebp - 0x88], xmm0
008cb16f call 0x6c3d90
008cb174 and eax, 3
008cb177 mov dword ptr [ebp - 0x90], eax
008cb17d jbe 0x8cb400
008cb183 movss xmm0, dword ptr [ebp - 0x78]
008cb188 mov edi, eax
008cb18a mulss xmm0, dword ptr [0xb6a864]
008cb192 movss xmm1, dword ptr [ebp - 0x84]
008cb19a movss xmm2, dword ptr [ebp - 0x8c]
008cb1a2 movss dword ptr [ebp - 0xc8], xmm0
008cb1aa subss xmm1, xmm2
008cb1ae movss xmm0, dword ptr [ebp - 0x98]
008cb1b6 mulss xmm0, dword ptr [0xb6a864]
008cb1be movss dword ptr [ebp - 0xa8], xmm1
008cb1c6 movss dword ptr [ebp - 0xb8], xmm0
008cb1ce nop 
008cb1d0 call 0x6c3d90
008cb1d5 movss xmm3, dword ptr [0xb6a19c]
008cb1dd movd xmm0, eax
008cb1e1 cvtdq2pd xmm0, xmm0
008cb1e5 shr eax, 0x1f
008cb1e8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb1f1 cvtpd2ps xmm0, xmm0
008cb1f5 mulss xmm0, xmm3
008cb1f9 mulss xmm0, dword ptr [0xb6a910]
008cb201 addss xmm0, dword ptr [0xb6a8cc]
008cb209 movss dword ptr [ebp - 0x80], xmm0
008cb20e call 0x6c3d90
008cb213 movd xmm0, eax
008cb217 cvtdq2pd xmm0, xmm0
008cb21b shr eax, 0x1f
008cb21e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb227 cvtpd2ps xmm0, xmm0
008cb22b mulss xmm0, xmm3
008cb22f movss dword ptr [ebp - 0xc4], xmm0
008cb237 call 0x6c3d90
008cb23c movd xmm0, eax
008cb240 cvtdq2pd xmm0, xmm0
008cb244 shr eax, 0x1f
008cb247 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb250 cvtpd2ps xmm0, xmm0
008cb254 mulss xmm0, xmm3
008cb258 mulss xmm0, xmm1
008cb25c addss xmm0, xmm2
008cb260 movss dword ptr [ebp - 0xbc], xmm0
008cb268 call 0x6c3d90
008cb26d mov dword ptr [ebp - 0xc0], eax
008cb273 call 0x6c3d90
008cb278 movd xmm0, eax
008cb27c cvtdq2pd xmm0, xmm0
008cb280 shr eax, 0x1f
008cb283 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb28c cvtpd2ps xmm0, xmm0
008cb290 mulss xmm0, xmm3
008cb294 mulss xmm0, dword ptr [0xb6a874]
008cb29c addss xmm0, xmm0
008cb2a0 movss dword ptr [ebp - 0x90], xmm0
008cb2a8 call 0x411fe0
008cb2ad movss xmm1, dword ptr [ebp - 0x78]
008cb2b2 mulss xmm1, dword ptr [ebp - 0x80]
008cb2b7 addss xmm0, xmm1
008cb2bb movss dword ptr [ebp - 0x180], xmm0
008cb2c3 movss xmm0, dword ptr [ebp - 0x90]
008cb2cb call 0x412010
008cb2d0 movss xmm1, dword ptr [ebp - 0x98]
008cb2d8 lea eax, [ebp - 0x180]
008cb2de mulss xmm1, dword ptr [ebp - 0x80]
008cb2e3 mov ecx, dword ptr [0xbfd65c]
008cb2e9 push dword ptr [ebp - 0xc0]
008cb2ef addss xmm0, xmm1
008cb2f3 movss xmm1, dword ptr [ebp - 0x98]
008cb2fb mulss xmm1, dword ptr [ebp - 0xbc]
008cb303 push 1
008cb305 push 0
008cb307 push eax
008cb308 addss xmm1, dword ptr [ebp - 0x70]
008cb30d movss dword ptr [ebp - 0x17c], xmm0
008cb315 lea eax, [ebp - 0x198]
008cb31b movss xmm0, dword ptr [ebp - 0xc8]
008cb323 mulss xmm0, dword ptr [ebp - 0xc4]
008cb32b push eax
008cb32c push 0x63
008cb32e push 0x3e8
008cb333 addss xmm1, xmm0
008cb337 movss xmm0, dword ptr [ebp - 0xb8]
008cb33f mulss xmm0, dword ptr [ebp - 0xc4]
008cb347 movss dword ptr [ebp - 0x198], xmm1
008cb34f movss xmm1, dword ptr [ebp - 0x7c]
008cb354 mulss xmm1, dword ptr [ebp - 0xbc]
008cb35c addss xmm1, dword ptr [ebp - 0x9c]
008cb364 addss xmm1, xmm0
008cb368 movss dword ptr [ebp - 0x194], xmm1
008cb370 call 0x422e20
008cb375 mov ecx, eax
008cb377 mov dword ptr [ebp - 0xc0], ecx
008cb37d movss xmm1, dword ptr [ecx + 0xd8]
008cb385 addss xmm1, xmm1
008cb389 movss xmm0, dword ptr [ecx + 0xdc]
008cb391 lea edx, [ebp - 0x6c]
008cb394 mov eax, dword ptr [ecx]
008cb396 addss xmm0, xmm0
008cb39a push 1
008cb39c push 0
008cb39e push 0xff
008cb3a3 push -1
008cb3a5 push edx
008cb3a6 movss dword ptr [ecx + 0xd8], xmm1
008cb3ae movss dword ptr [ecx + 0xdc], xmm0
008cb3b6 call dword ptr [eax + 0x38]
008cb3b9 mov ecx, dword ptr [ebp - 0xc0]
008cb3bf movss xmm0, dword ptr [ebp - 0x88]
008cb3c7 mov dword ptr [ecx + 0x2a4], 0
008cb3d1 movss dword ptr [ecx + 0x2a8], xmm0
008cb3d9 mov eax, dword ptr [ecx]
008cb3db call dword ptr [eax + 0xc]
008cb3de movss xmm1, dword ptr [ebp - 0xa8]
008cb3e6 movss xmm2, dword ptr [ebp - 0x8c]
008cb3ee sub edi, 1
008cb3f1 jne 0x8cb1d0
008cb3f7 mov edi, dword ptr [ebp - 0xa0]
008cb3fd xorps xmm3, xmm3
008cb400 mov eax, dword ptr [edi]
008cb402 mov ecx, dword ptr [eax + 0x164]
008cb408 xor eax, eax
008cb40a and ecx, 0x1000000
008cb410 or eax, ecx
008cb412 je 0x8cb418
008cb414 mov al, 1
008cb416 jmp 0x8cb41a
008cb418 xor al, al
008cb41a test al, al
008cb41c je 0x8cb6ef
008cb422 mov ecx, dword ptr [ebp - 0x74]
008cb425 xorps xmm4, xmm4
008cb428 movups xmmword ptr [ebp - 0x168], xmm4
008cb42f movss xmm0, dword ptr [ecx + 0xe4]
008cb437 movss xmm1, dword ptr [ecx + 0xf4]
008cb43f addss xmm0, xmm0
008cb443 movss xmm2, dword ptr [ecx + 0xf8]
008cb44b movss xmm5, dword ptr [ecx + 0xfc]
008cb453 movss dword ptr [ebp - 0x178], xmm0
008cb45b movss xmm0, dword ptr [ecx + 0xe8]
008cb463 movss dword ptr [ebp - 0x174], xmm0
008cb46b movss xmm0, dword ptr [ecx + 0xec]
008cb473 movss dword ptr [ebp - 0x170], xmm0
008cb47b movss xmm0, dword ptr [ecx + 0xf0]
008cb483 movss dword ptr [ebp - 0x16c], xmm0
008cb48b movaps xmm0, xmm1
008cb48e addss xmm0, xmm2
008cb492 addss xmm0, xmm5
008cb496 ucomiss xmm0, xmm3
008cb499 lahf 
008cb49a test ah, 0x44
008cb49d jnp 0x8cb4ce
008cb49f movss xmm0, dword ptr [ecx + 0x100]
008cb4a7 movss dword ptr [ebp - 0x168], xmm1
008cb4af movss dword ptr [ebp - 0x164], xmm2
008cb4b7 movss dword ptr [ebp - 0x160], xmm5
008cb4bf movss dword ptr [ebp - 0x15c], xmm0
008cb4c7 movups xmm4, xmmword ptr [ebp - 0x168]
008cb4ce movss xmm0, dword ptr [ecx + 0x10c]
008cb4d6 movss xmm2, dword ptr [ecx + 0x104]
008cb4de addss xmm0, xmm3
008cb4e2 movss xmm1, dword ptr [ecx + 0x108]
008cb4ea addss xmm2, xmm3
008cb4ee addss xmm1, xmm3
008cb4f2 movups xmmword ptr [ebp - 0x30], xmm4
008cb4f6 movss dword ptr [ebp - 0x150], xmm0
008cb4fe movups xmm0, xmmword ptr [ebp - 0x178]
008cb505 mov eax, dword ptr [ebp - 0x150]
008cb50b unpcklps xmm2, xmm1
008cb50e movups xmmword ptr [ebp - 0x40], xmm0
008cb512 mov dword ptr [ebp - 0x18], eax
008cb515 movq qword ptr [ebp - 0x20], xmm2
008cb51a call 0x6c3d90
008cb51f movss xmm3, dword ptr [0xb6a19c]
008cb527 movd xmm0, eax
008cb52b cvtdq2pd xmm0, xmm0
008cb52f shr eax, 0x1f
008cb532 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb53b cvtpd2ps xmm0, xmm0
008cb53f mulss xmm0, xmm3
008cb543 addss xmm0, xmm0
008cb547 addss xmm0, dword ptr [0xb6a7b0]
008cb54f movss dword ptr [ebp - 0x80], xmm0
008cb554 call 0x6c3d90
008cb559 movss xmm2, dword ptr [ebp - 0x84]
008cb561 subss xmm2, dword ptr [ebp - 0x8c]
008cb569 movd xmm0, eax
008cb56d cvtdq2pd xmm0, xmm0
008cb571 shr eax, 0x1f
008cb574 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb57d cvtpd2ps xmm0, xmm0
008cb581 mulss xmm0, xmm3
008cb585 mulss xmm0, xmm2
008cb589 addss xmm0, dword ptr [ebp - 0x8c]
008cb591 movss dword ptr [ebp - 0xc0], xmm0
008cb599 call 0x6c3d90
008cb59e mov dword ptr [ebp - 0x90], eax
008cb5a4 call 0x6c3d90
008cb5a9 movd xmm0, eax
008cb5ad cvtdq2pd xmm0, xmm0
008cb5b1 shr eax, 0x1f
008cb5b4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb5bd cvtpd2ps xmm0, xmm0
008cb5c1 mulss xmm0, xmm3
008cb5c5 mulss xmm0, dword ptr [0xb6a874]
008cb5cd addss xmm0, xmm0
008cb5d1 movss dword ptr [ebp - 0xa8], xmm0
008cb5d9 call 0x411fe0
008cb5de movss xmm1, dword ptr [ebp - 0x78]
008cb5e3 mulss xmm1, dword ptr [ebp - 0x80]
008cb5e8 addss xmm0, xmm1
008cb5ec movss dword ptr [ebp - 0x138], xmm0
008cb5f4 movss xmm0, dword ptr [ebp - 0xa8]
008cb5fc call 0x412010
008cb601 movss xmm2, dword ptr [ebp - 0x98]
008cb609 lea eax, [ebp - 0x138]
008cb60f push dword ptr [ebp - 0x90]
008cb615 mov ecx, dword ptr [0xbfd65c]
008cb61b movaps xmm1, xmm2
008cb61e mulss xmm1, dword ptr [ebp - 0x80]
008cb623 push 2
008cb625 mulss xmm2, dword ptr [ebp - 0xc0]
008cb62d push 0
008cb62f addss xmm0, xmm1
008cb633 movss xmm1, dword ptr [ebp - 0x7c]
008cb638 mulss xmm1, dword ptr [ebp - 0xc0]
008cb640 push eax
008cb641 addss xmm2, dword ptr [ebp - 0x70]
008cb646 lea eax, [ebp - 0x140]
008cb64c addss xmm1, dword ptr [ebp - 0x9c]
008cb654 push eax
008cb655 push 2
008cb657 push 0x3e8
008cb65c movss dword ptr [ebp - 0x134], xmm0
008cb664 movss dword ptr [ebp - 0x140], xmm2
008cb66c movss dword ptr [ebp - 0x13c], xmm1
008cb674 call 0x422e20
008cb679 mov dword ptr [ebp - 0x80], eax
008cb67c mov edx, dword ptr [eax]
008cb67e push 1
008cb680 push 0
008cb682 push 0xff
008cb687 push -1
008cb689 lea ecx, [ebp - 0x40]
008cb68c push ecx
008cb68d mov ecx, eax
008cb68f call dword ptr [edx + 0x38]
008cb692 mov eax, dword ptr [ebp - 0x80]
008cb695 movss xmm0, dword ptr [ebp - 0x88]
008cb69d mov dword ptr [eax + 0x2a4], 0
008cb6a7 movss dword ptr [eax + 0x2a8], xmm0
008cb6af call 0x6c3d90
008cb6b4 mov ecx, dword ptr [ebp - 0x80]
008cb6b7 movd xmm0, eax
008cb6bb cvtdq2pd xmm0, xmm0
008cb6bf shr eax, 0x1f
008cb6c2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008cb6cb mov eax, dword ptr [ecx]
008cb6cd cvtpd2ps xmm0, xmm0
008cb6d1 mulss xmm0, dword ptr [0xb6a19c]
008cb6d9 mulss xmm0, dword ptr [0xb6ac40]
008cb6e1 movss dword ptr [ecx + 0x3c4], xmm0
008cb6e9 call dword ptr [eax + 0xc]
008cb6ec xorps xmm3, xmm3
008cb6ef mov edx, dword ptr [ebp - 0x74]
008cb6f2 add edi, 4
008cb6f5 mov dword ptr [ebp - 0xa0], edi
008cb6fb cmp edi, esi
008cb6fd jne 0x8c9ff0
008cb703 mov ecx, dword ptr [ebp - 0xb4]
008cb709 test ecx, ecx
008cb70b je 0x8cbd4b
008cb711 mov eax, dword ptr [ebp - 0xac]
008cb717 sub eax, ecx
008cb719 sar eax, 2
008cb71c push eax
008cb71d push ecx
008cb71e call 0x407d90
008cb723 jmp 0x8cbd4b
008cb728 xorps xmm3, xmm3
008cb72b jmp 0x8cb6f2
008cb72d movss xmm0, dword ptr [edi + 0x36c]
008cb735 mulss xmm0, dword ptr [0xb6a230]
008cb73d movss dword ptr [ebp - 0xa8], xmm0
008cb745 call 0x411fe0
