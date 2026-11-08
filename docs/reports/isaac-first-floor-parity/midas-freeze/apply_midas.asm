00685990 push ebp
00685991 mov ebp, esp
00685993 and esp, 0xfffffff8
00685996 sub esp, 0x30
00685999 mov eax, dword ptr [0xbaa3b4]
0068599e xor eax, esp
006859a0 mov dword ptr [esp + 0x2c], eax
006859a4 push esi
006859a5 push edi
006859a6 mov edi, dword ptr [ebp + 8]
006859a9 mov esi, ecx
006859ab push edi
006859ac call 0x684b00
006859b1 test al, al
006859b3 jne 0x685ac2
006859b9 push edi
006859ba push dword ptr [ebp + 0xc]
006859bd mov ecx, esi
006859bf call 0x685020
006859c4 mov ecx, esi
006859c6 mov edi, eax
006859c8 call 0x681710
006859cd test al, al
006859cf je 0x6859ec
006859d1 mov ecx, dword ptr [esi + 0x314]
006859d7 test ecx, ecx
006859d9 je 0x6859ec
006859db nop dword ptr [eax + eax]
006859e0 mov esi, ecx
006859e2 mov ecx, dword ptr [esi + 0x314]
006859e8 test ecx, ecx
006859ea jne 0x6859e0
006859ec test edi, edi
006859ee jle 0x685abb
006859f4 cmp dword ptr [esi + 0x224], 0
006859fb jne 0x685abb
00685a01 cmp dword ptr [esi + 0x230], 0
00685a08 jg 0x685abb
00685a0e cmp dword ptr [esi + 0x28], 0xf5
00685a15 jne 0x685a31
00685a17 mov dword ptr [esi + 0x2c], 1
00685a1e pop edi
00685a1f pop esi
00685a20 mov ecx, dword ptr [esp + 0x2c]
00685a24 xor ecx, esp
00685a26 call 0x9eacd7
00685a2b mov esp, ebp
00685a2d pop ebp
00685a2e ret 8
00685a31 push 0
00685a33 push 1
00685a35 mov ecx, esi
00685a37 call 0x4122f0
00685a3c test al, al
00685a3e jne 0x685abb
00685a40 mov eax, dword ptr [esi + 0x164]
00685a46 lea ecx, [esp + 8]
00685a4a or dword ptr [esi + 0x160], 0x420
00685a54 xorps xmm0, xmm0
00685a57 push 1
00685a59 push 0
00685a5b push 0xff
00685a60 mov dword ptr [esi + 0x164], eax
00685a66 mov eax, dword ptr [esi]
00685a68 push edi
00685a69 movups xmmword ptr [esp + 0x28], xmm0
00685a6e push ecx
00685a6f movaps xmm0, xmmword ptr [0xb6c150]
00685a76 mov ecx, esi
00685a78 mov dword ptr [esi + 0x224], edi
00685a7e mov dword ptr [esi + 0x210], edi
00685a84 movups xmmword ptr [esp + 0x1c], xmm0
00685a89 mov dword ptr [esp + 0x3c], 0x3e20a0a1
00685a91 mov dword ptr [esp + 0x40], 0x3e20a0a1
00685a99 mov dword ptr [esp + 0x44], 0x3e20a0a1
00685aa1 call dword ptr [eax + 0x38]
00685aa4 mov eax, dword ptr [esi]
00685aa6 mov ecx, esi
00685aa8 mov eax, dword ptr [eax + 0x48]
00685aab call eax
00685aad test al, al
00685aaf je 0x685abb
00685ab1 mov dword ptr [esi + 0x230], 0xf0
00685abb mov ecx, esi
00685abd call 0x681390
00685ac2 mov ecx, dword ptr [esp + 0x34]
00685ac6 pop edi
00685ac7 pop esi
00685ac8 xor ecx, esp
00685aca call 0x9eacd7
00685acf mov esp, ebp
00685ad1 pop ebp
