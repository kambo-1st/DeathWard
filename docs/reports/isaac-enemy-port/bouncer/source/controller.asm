004efe40 push ebx
004efe41 mov ebx, esp
004efe43 sub esp, 8
004efe46 and esp, 0xfffffff8
004efe49 add esp, 4
004efe4c push ebp
004efe4d mov ebp, dword ptr [ebx + 4]
004efe50 mov dword ptr [esp + 4], ebp
004efe54 mov ebp, esp
004efe56 push -1
004efe58 push 0x9ef145
004efe5d mov eax, dword ptr fs:[0]
004efe63 push eax
004efe64 push ebx
004efe65 sub esp, 0x1b0
004efe6b mov eax, dword ptr [0xbaa3b4]
004efe70 xor eax, ebp
004efe72 mov dword ptr [ebp - 0x14], eax
004efe75 push esi
004efe76 push edi
004efe77 push eax
004efe78 lea eax, [ebp - 0xc]
004efe7b mov dword ptr fs:[0], eax
004efe81 mov edi, ecx
004efe83 mov eax, dword ptr [edi + 0xab4]
004efe89 movss xmm0, dword ptr [0xb6a614]
004efe91 movss dword ptr [ebp - 0x19c], xmm0
004efe99 cmp eax, 0x10
004efe9c ja 0x4f0517
004efea2 movzx eax, byte ptr [eax + 0x4f087c]
004efea9 jmp dword ptr [eax*4 + 0x4f0868]
004efeb0 push 0
004efeb2 push 0xb41e88
004efeb7 lea ecx, [edi + 0x3c]
004efeba call 0x405a00
004efebf push 1
004efec1 push 0xb404ec
004efec6 lea ecx, [edi + 0x3c]
004efec9 call 0x405740
004efece test al, al
004efed0 je 0x4efef2
004efed2 mov eax, dword ptr [edi + 0x70]
004efed5 test eax, eax
004efed7 je 0x4efef2
004efed9 lea ecx, [edi + 0x6c]
004efedc xorps xmm1, xmm1
004efedf call 0x403c00
004efee4 mov eax, dword ptr [edi + 0x70]
004efee7 test eax, eax
004efee9 je 0x4efef2
004efeeb mov byte ptr [edi + 0x80], 0
004efef2 mov dword ptr [edi + 0xab4], 3
004efefc mov dword ptr [edi + 0x360], 0
004eff06 call 0x6c3d90
004eff0b movd xmm0, eax
004eff0f cvtdq2pd xmm0, xmm0
004eff13 shr eax, 0x1f
004eff16 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004eff1f cvtpd2ps xmm0, xmm0
004eff23 mulss xmm0, dword ptr [0xb6a19c]
004eff2b mulss xmm0, dword ptr [0xb6a8cc]
004eff33 addss xmm0, dword ptr [0xb6a910]
004eff3b movss dword ptr [edi + 0xb00], xmm0
004eff43 jmp 0x4f0517
004eff48 push 0
004eff4a push ecx
004eff4b lea eax, [ebp - 0x1a4]
004eff51 mov dword ptr [esp], 0
004eff58 push eax
004eff59 call 0x695a30
004eff5e push eax
004eff5f lea ecx, [edi + 0x364]
004eff65 call 0x7a4830
004eff6a cmp dword ptr [edi + 0xaa0], 0
004eff71 jle 0x4effb9
004eff73 mov eax, dword ptr [0xbfd65c]
004eff78 mov eax, dword ptr [eax + 0x1a30dc]
004eff7e sub eax, dword ptr [edi + 0x280]
004eff84 cmp eax, 0xa
004eff87 jle 0x4effb9
004eff89 call 0x6c3d90
004eff8e mov ecx, 0x64
004eff93 xor edx, edx
004eff95 div ecx
004eff97 push ecx
004eff98 mov dword ptr [esp], 0x3f800000
004eff9f push 0
004effa1 lea eax, [edx + 0x2d]
004effa4 push eax
004effa5 push ecx
004effa6 mov dword ptr [esp], 0x3f800000
004effad mov ecx, edi
004effaf push 0x8f
004effb4 call 0x6ad720
004effb9 mov eax, dword ptr [0xb404ec]
004effbe mov ecx, dword ptr [0xb404f0]
004effc4 mov dword ptr [ebp - 0x30], 0xf
004effcb mov dword ptr [ebp - 0x34], 8
004effd2 mov dword ptr [ebp - 0x44], eax
004effd5 mov dword ptr [ebp - 0x40], ecx
004effd8 mov byte ptr [ebp - 0x3c], 0
004effdc mov dword ptr [ebp - 4], 0
004effe3 mov eax, dword ptr [0xb40504]
004effe8 mov ecx, dword ptr [0xb40508]
004effee mov dword ptr [ebp - 0x18], 0xf
004efff5 mov dword ptr [ebp - 0x1c], 8
004efffc mov dword ptr [ebp - 0x2c], eax
004effff mov dword ptr [ebp - 0x28], ecx
004f0002 mov byte ptr [ebp - 0x24], 0
004f0006 push ecx
004f0007 mov byte ptr [ebp - 4], 1
004f000b lea eax, [ebp - 0x44]
004f000e mov dword ptr [esp], 0x3dcccccd
004f0015 mov ecx, edi
004f0017 push eax
004f0018 lea eax, [ebp - 0x2c]
004f001b push eax
004f001c call 0x6980a0
004f0021 mov byte ptr [ebp - 4], 0
004f0025 mov edx, dword ptr [ebp - 0x18]
004f0028 cmp edx, 0x10
004f002b jb 0x4f0055
004f002d mov ecx, dword ptr [ebp - 0x2c]
004f0030 inc edx
004f0031 mov eax, ecx
004f0033 cmp edx, 0x1000
004f0039 jb 0x4f004b
004f003b mov ecx, dword ptr [ecx - 4]
004f003e add edx, 0x23
004f0041 sub eax, ecx
004f0043 add eax, -4
004f0046 cmp eax, 0x1f
004f0049 ja 0x4f0094
004f004b push edx
004f004c push ecx
004f004d call 0x9eb08e
004f0052 add esp, 8
004f0055 mov dword ptr [ebp - 4], 0xffffffff
004f005c mov edx, dword ptr [ebp - 0x30]
004f005f mov dword ptr [ebp - 0x1c], 0
004f0066 mov dword ptr [ebp - 0x18], 0xf
004f006d mov byte ptr [ebp - 0x2c], 0
004f0071 cmp edx, 0x10
004f0074 jb 0x4f00a4
004f0076 mov ecx, dword ptr [ebp - 0x44]
004f0079 inc edx
004f007a mov eax, ecx
004f007c cmp edx, 0x1000
004f0082 jb 0x4f009a
004f0084 mov ecx, dword ptr [ecx - 4]
004f0087 add edx, 0x23
004f008a sub eax, ecx
004f008c add eax, -4
004f008f cmp eax, 0x1f
004f0092 jbe 0x4f009a
004f0094 call dword ptr [0xa065ac]
004f009a push edx
004f009b push ecx
004f009c call 0x9eb08e
004f00a1 add esp, 8
004f00a4 cmp dword ptr [edi + 0x70], 0
004f00a8 je 0x4f00f0
004f00aa cmp byte ptr [edi + 0x80], 0
004f00b1 je 0x4f00f0
004f00b3 movss xmm2, dword ptr [edi + 0x2b8]
004f00bb lea esi, [edi + 0x3c]
004f00be movss xmm1, dword ptr [edi + 0x2bc]
004f00c6 mov ecx, 0xb42b24
004f00cb andps xmm2, xmmword ptr [0xb6c980]
004f00d2 mov eax, 0xb42824
004f00d7 andps xmm1, xmmword ptr [0xb6c980]
004f00de comiss xmm2, xmm1
004f00e1 push 0
004f00e3 cmovbe eax, ecx
004f00e6 mov ecx, esi
004f00e8 push eax
004f00e9 call 0x405a00
004f00ee jmp 0x4f0116
004f00f0 push 1
004f00f2 lea esi, [edi + 0x3c]
004f00f5 push 0xb42b24
004f00fa mov ecx, esi
004f00fc call 0x405bb0
004f0101 test al, al
004f0103 je 0x4f0116
004f0105 cmp dword ptr [esi + 0x54], 0
004f0109 je 0x4f0116
004f010b lea ecx, [esi + 0x50]
004f010e xorps xmm1, xmm1
004f0111 call 0x403c00
004f0116 mov eax, dword ptr [0xbfd65c]
004f011b mov eax, dword ptr [eax + 0x1a30dc]
004f0121 sub eax, dword ptr [edi + 0x280]
004f0127 cmp eax, 0x1e
004f012a jle 0x4f016a
004f012c cmp dword ptr [edi + 0xaa0], 0
004f0133 jle 0x4f016a
004f0135 xorps xmm0, xmm0
004f0138 comiss xmm0, dword ptr [edi + 0xb00]
004f013f jb 0x4f016a
004f0141 call 0x6c3d90
004f0146 xor edx, edx
004f0148 mov ecx, 0x14
004f014d div ecx
004f014f test edx, edx
004f0151 jne 0x4f016a
004f0153 push edx
004f0154 push 0xb42b34
004f0159 mov ecx, esi
004f015b call 0x405a00
004f0160 mov dword ptr [edi + 0xab4], 8
004f016a movss xmm0, dword ptr [edi + 0xb00]
004f0172 xorps xmm1, xmm1
004f0175 comiss xmm0, xmm1
004f0178 jbe 0x4f01ac
004f017a subss xmm0, dword ptr [0xb6a25c]
004f0182 movss xmm2, dword ptr [edi + 0x14]
004f0187 comiss xmm2, xmm1
004f018a movss dword ptr [edi + 0xb00], xmm0
004f0192 jbe 0x4f01ac
004f0194 divss xmm2, dword ptr [0xb6a8a0]
004f019c subss xmm0, xmm2
004f01a0 maxss xmm0, xmm1
004f01a4 movss dword ptr [edi + 0xb00], xmm0
004f01ac movss xmm0, dword ptr [edi + 0x2c4]
004f01b4 mulss xmm0, dword ptr [0xb6a560]
004f01bc movss dword ptr [edi + 0x2c4], xmm0
004f01c4 jmp 0x4f0517
004f01c9 mov eax, dword ptr [0xb404ec]
004f01ce mov ecx, dword ptr [0xb404f0]
004f01d4 mov dword ptr [ebp - 0x30], 0xf
004f01db mov dword ptr [ebp - 0x34], 8
004f01e2 mov dword ptr [ebp - 0x44], eax
004f01e5 mov dword ptr [ebp - 0x40], ecx
004f01e8 mov byte ptr [ebp - 0x3c], 0
004f01ec mov dword ptr [ebp - 4], 2
004f01f3 mov eax, dword ptr [0xb40504]
004f01f8 mov ecx, dword ptr [0xb40508]
004f01fe mov dword ptr [ebp - 0x18], 0xf
004f0205 mov dword ptr [ebp - 0x1c], 8
004f020c mov dword ptr [ebp - 0x2c], eax
004f020f mov dword ptr [ebp - 0x28], ecx
004f0212 mov byte ptr [ebp - 0x24], 0
004f0216 push ecx
004f0217 mov byte ptr [ebp - 4], 3
004f021b lea eax, [ebp - 0x44]
004f021e mov dword ptr [esp], 0x3dcccccd
004f0225 mov ecx, edi
004f0227 push eax
004f0228 lea eax, [ebp - 0x2c]
004f022b push eax
004f022c call 0x6980a0
004f0231 mov byte ptr [ebp - 4], 2
004f0235 mov edx, dword ptr [ebp - 0x18]
004f0238 cmp edx, 0x10
004f023b jb 0x4f0265
004f023d mov ecx, dword ptr [ebp - 0x2c]
004f0240 inc edx
004f0241 mov eax, ecx
004f0243 cmp edx, 0x1000
004f0249 jb 0x4f025b
004f024b mov ecx, dword ptr [ecx - 4]
004f024e add edx, 0x23
004f0251 sub eax, ecx
004f0253 add eax, -4
004f0256 cmp eax, 0x1f
004f0259 ja 0x4f02a4
004f025b push edx
004f025c push ecx
004f025d call 0x9eb08e
004f0262 add esp, 8
004f0265 mov dword ptr [ebp - 4], 0xffffffff
004f026c mov edx, dword ptr [ebp - 0x30]
004f026f mov dword ptr [ebp - 0x1c], 0
004f0276 mov dword ptr [ebp - 0x18], 0xf
004f027d mov byte ptr [ebp - 0x2c], 0
004f0281 cmp edx, 0x10
004f0284 jb 0x4f02b4
004f0286 mov ecx, dword ptr [ebp - 0x44]
004f0289 inc edx
004f028a mov eax, ecx
004f028c cmp edx, 0x1000
004f0292 jb 0x4f02aa
004f0294 mov ecx, dword ptr [ecx - 4]
004f0297 add edx, 0x23
004f029a sub eax, ecx
004f029c add eax, -4
004f029f cmp eax, 0x1f
004f02a2 jbe 0x4f02aa
004f02a4 call dword ptr [0xa065ac]
004f02aa push edx
004f02ab push ecx
004f02ac call 0x9eb08e
004f02b1 add esp, 8
004f02b4 push 0xb42b08
004f02b9 lea ecx, [edi + 0x8c]
004f02bf call 0x405e90
004f02c4 test al, al
004f02c6 je 0x4f0438
004f02cc push ecx
004f02cd mov dword ptr [esp], 0x3f800000
004f02d4 push 0
004f02d6 push 0x1e
004f02d8 push ecx
004f02d9 mov dword ptr [esp], 0x3f800000
004f02e0 mov ecx, edi
004f02e2 push 0x1e4
004f02e7 call 0x6ad720
004f02ec movss xmm0, dword ptr [edi + 0x2c8]
004f02f4 mulss xmm0, dword ptr [0xb6a6f0]
004f02fc mov dword ptr [edi + 0xab4], 0x10
004f0306 movss dword ptr [edi + 0x2c8], xmm0
004f030e jmp 0x4f0438
004f0313 mov eax, dword ptr [0xb404ec]
004f0318 mov ecx, dword ptr [0xb404f0]
004f031e mov dword ptr [ebp - 0x30], 0xf
004f0325 mov dword ptr [ebp - 0x34], 8
004f032c mov dword ptr [ebp - 0x44], eax
004f032f mov dword ptr [ebp - 0x40], ecx
004f0332 mov byte ptr [ebp - 0x3c], 0
004f0336 mov dword ptr [ebp - 4], 4
004f033d mov eax, dword ptr [0xb40504]
004f0342 mov ecx, dword ptr [0xb40508]
004f0348 mov dword ptr [ebp - 0x18], 0xf
004f034f mov dword ptr [ebp - 0x1c], 8
004f0356 mov dword ptr [ebp - 0x2c], eax
004f0359 mov dword ptr [ebp - 0x28], ecx
004f035c mov byte ptr [ebp - 0x24], 0
004f0360 push ecx
004f0361 mov byte ptr [ebp - 4], 5
004f0365 lea eax, [ebp - 0x44]
004f0368 mov dword ptr [esp], 0x3dcccccd
004f036f mov ecx, edi
004f0371 push eax
004f0372 lea eax, [ebp - 0x2c]
004f0375 push eax
004f0376 call 0x6980a0
004f037b mov byte ptr [ebp - 4], 4
004f037f mov edx, dword ptr [ebp - 0x18]
004f0382 cmp edx, 0x10
004f0385 jb 0x4f03af
004f0387 mov ecx, dword ptr [ebp - 0x2c]
004f038a inc edx
004f038b mov eax, ecx
004f038d cmp edx, 0x1000
004f0393 jb 0x4f03a5
004f0395 mov ecx, dword ptr [ecx - 4]
004f0398 add edx, 0x23
004f039b sub eax, ecx
004f039d add eax, -4
004f03a0 cmp eax, 0x1f
004f03a3 ja 0x4f03ee
004f03a5 push edx
004f03a6 push ecx
004f03a7 call 0x9eb08e
004f03ac add esp, 8
004f03af mov dword ptr [ebp - 4], 0xffffffff
004f03b6 mov edx, dword ptr [ebp - 0x30]
004f03b9 mov dword ptr [ebp - 0x1c], 0
004f03c0 mov dword ptr [ebp - 0x18], 0xf
004f03c7 mov byte ptr [ebp - 0x2c], 0
004f03cb cmp edx, 0x10
004f03ce jb 0x4f03fe
004f03d0 mov ecx, dword ptr [ebp - 0x44]
004f03d3 inc edx
004f03d4 mov eax, ecx
004f03d6 cmp edx, 0x1000
004f03dc jb 0x4f03f4
004f03de mov ecx, dword ptr [ecx - 4]
004f03e1 add edx, 0x23
004f03e4 sub eax, ecx
004f03e6 add eax, -4
004f03e9 cmp eax, 0x1f
004f03ec jbe 0x4f03f4
004f03ee call dword ptr [0xa065ac]
004f03f4 push edx
004f03f5 push ecx
004f03f6 call 0x9eb08e
004f03fb add esp, 8
004f03fe cmp dword ptr [edi + 0x360], 0
004f0405 lea ecx, [edi + 0x3c]
004f0408 mov dword ptr [ebp - 0x34], 0
004f040f mov dword ptr [ebp - 0x30], 0xf
004f0416 mov byte ptr [ebp - 0x44], 0
004f041a jne 0x4f0455
004f041c cmp dword ptr [edi + 0x90], 0
004f0423 je 0x4f042e
004f0425 cmp byte ptr [edi + 0xa0], 0
004f042c jne 0x4f0438
004f042e mov dword ptr [edi + 0x360], 1
004f0438 movss xmm0, dword ptr [edi + 0x2c4]
004f0440 mulss xmm0, dword ptr [0xb6a4c4]
004f0448 movss dword ptr [edi + 0x2c4], xmm0
004f0450 jmp 0x4f0517
004f0455 cmp dword ptr [edi + 0x70], 0
004f0459 je 0x4f0472
004f045b cmp byte ptr [edi + 0x80], 0
004f0462 je 0x4f0472
004f0464 push 0
004f0466 push 0xb42b10
004f046b call 0x405a00
004f0470 jmp 0x4f047e
004f0472 push 0
004f0474 push 0xb42b10
004f0479 call 0x405cb0
004f047e mov eax, dword ptr [0xbfd65c]
004f0483 mov eax, dword ptr [eax + 0x1a30dc]
004f0489 sub eax, dword ptr [edi + 0x280]
004f048f test al, 1
004f0491 je 0x4f04a3
004f0493 movss xmm0, dword ptr [0xb6ae44]
004f049b movss dword ptr [ebp - 0x19c], xmm0
004f04a3 cmp dword ptr [edi + 0xbc], 1
004f04aa jg 0x4f04ca
004f04ac cmp dword ptr [edi + 0x50], 0x10
004f04b0 lea eax, [edi + 0x3c]
004f04b3 jb 0x4f04b8
004f04b5 mov eax, dword ptr [edi + 0x3c]
004f04b8 push 1
004f04ba push eax
004f04bb push 0xa0830c
004f04c0 push 3
004f04c2 call 0x95e330
004f04c7 add esp, 0x10
004f04ca mov eax, dword ptr [edi + 0xb8]
004f04d0 movss xmm0, dword ptr [ebp - 0x19c]
004f04d8 push ecx
004f04d9 mov dword ptr [esp], 0
004f04e0 mov ecx, edi
004f04e2 movss dword ptr [eax + 0xdc], xmm0
004f04ea lea eax, [ebp - 0x1a4]
004f04f0 push eax
004f04f1 call 0x695a30
004f04f6 push 1
004f04f8 push 0x384
004f04fd push ecx
004f04fe lea eax, [ebp - 0x1a4]
004f0504 mov dword ptr [esp], 0x3f666666
004f050b push eax
004f050c lea ecx, [edi + 0x364]
004f0512 call 0x7a3650
004f0517 cmp byte ptr [edi + 0x16b], 0
004f051e je 0x4f084a
004f0524 cmp dword ptr [edi + 0xab4], 0x10
004f052b jne 0x4f0813
004f0531 mov esi, dword ptr [0xbfd680]
004f0537 lea ecx, [ebp - 0x19c]
004f053d mov dword ptr [ebp - 0x19c], 0x8d
004f0547 call 0x8b1340
004f054c sub esp, 8
004f054f mov dword ptr [esp + 4], 0
004f0557 mov dword ptr [esp], 0x3fc00000
004f055e push 0
004f0560 push 2
004f0562 push ecx
004f0563 mov dword ptr [esp], 0x3f800000
004f056a lea ecx, [esi + 0x29de0]
004f0570 push dword ptr [ebp - 0x19c]
004f0576 call 0x888de0
004f057b mov ecx, dword ptr [0xbfd65c]
004f0581 push 6
004f0583 call 0x6d5ad0
004f0588 push 0
004f058a push 0
004f058c push edi
004f058d push ecx
004f058e mov ecx, dword ptr [0xbfd65c]
004f0594 lea esi, [edi + 0x294]
004f059a mov dword ptr [esp], 0x42f00000
004f05a1 push esi
004f05a2 call 0x6d6570
004f05a7 push 0
004f05a9 push 4
004f05ab mov edx, 3
004f05b0 mov ecx, 0x4efb00
004f05b5 call 0x5ed350
004f05ba mov ecx, dword ptr [esi]
004f05bc add esp, 8
004f05bf mov dword ptr [eax + 0x294], ecx
004f05c5 mov ecx, dword ptr [esi + 4]
004f05c8 mov dword ptr [eax + 0x298], ecx
004f05ce mov ecx, dword ptr [0xbfd65c]
004f05d4 push 8
004f05d6 call 0x6d5ad0
004f05db lea ecx, [ebp - 0xf0]
004f05e1 call 0x430d70
004f05e6 push eax
004f05e7 push ecx
004f05e8 mov dword ptr [esp], 0
004f05ef mov ecx, edi
004f05f1 push 0xc02fec
004f05f6 push 0xc
004f05f8 call 0x6a3420
004f05fd mov dword ptr [ebp - 0x19c], 0x16
004f0607 call 0x6c3d90
004f060c movd xmm0, eax
004f0610 cvtdq2pd xmm0, xmm0
004f0614 shr eax, 0x1f
004f0617 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f0620 cvtpd2ps xmm0, xmm0
004f0624 mulss xmm0, dword ptr [0xb6a19c]
004f062c mulss xmm0, dword ptr [0xb6a874]
004f0634 addss xmm0, xmm0
004f0638 movss dword ptr [ebp - 0x1a8], xmm0
004f0640 call 0x411fe0
004f0645 movss dword ptr [ebp - 0x1ac], xmm0
004f064d movss xmm0, dword ptr [ebp - 0x1a8]
004f0655 call 0x412010
004f065a movaps xmm3, xmm0
004f065d call 0x6c3d90
004f0662 movss xmm2, dword ptr [ebp - 0x1ac]
004f066a movaps xmm0, xmm2
004f066d mulss xmm2, dword ptr [0xb6a8f4]
004f0675 mulss xmm0, dword ptr [0xb6a9ac]
004f067d movd xmm1, eax
004f0681 cvtdq2pd xmm1, xmm1
004f0685 shr eax, 0x1f
004f0688 addss xmm2, dword ptr [esi]
004f068c addsd xmm1, qword ptr [eax*8 + 0xb6c940]
004f0695 movss dword ptr [ebp - 0x1a4], xmm2
004f069d cvtpd2ps xmm1, xmm1
004f06a1 mulss xmm1, dword ptr [0xb6a19c]
004f06a9 mulss xmm0, xmm1
004f06ad movss dword ptr [ebp - 0x1b4], xmm0
004f06b5 movaps xmm0, xmm3
004f06b8 mulss xmm3, dword ptr [0xb6a8f4]
004f06c0 mulss xmm0, dword ptr [0xb6a9ac]
004f06c8 addss xmm3, dword ptr [edi + 0x298]
004f06d0 mulss xmm0, xmm1
004f06d4 movss dword ptr [ebp - 0x1a0], xmm3
004f06dc movss dword ptr [ebp - 0x1b0], xmm0
004f06e4 call 0x6c3d90
004f06e9 mov ecx, dword ptr [0xbfd65c]
004f06ef push eax
004f06f0 push 0
004f06f2 push edi
004f06f3 lea eax, [ebp - 0x1b4]
004f06f9 push eax
004f06fa lea eax, [ebp - 0x1a4]
004f0700 push eax
004f0701 push 0
004f0703 push 9
004f0705 call 0x422e20
004f070a mov esi, eax
004f070c call 0x6c3d90
004f0711 movss xmm2, dword ptr [0xb6a19c]
004f0719 mov dword ptr [esi + 0x364], 0
004f0723 movd xmm0, eax
004f0727 cvtdq2pd xmm0, xmm0
004f072b shr eax, 0x1f
004f072e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f0737 cvtpd2ps xmm1, xmm0
004f073b movss xmm0, dword ptr [0xb6aee8]
004f0743 mulss xmm1, xmm2
004f0747 mulss xmm1, dword ptr [0xb6a940]
004f074f subss xmm0, xmm1
004f0753 movss dword ptr [esi + 0x360], xmm0
004f075b call 0x6c3d90
004f0760 movd xmm0, eax
004f0764 cvtdq2pd xmm0, xmm0
004f0768 shr eax, 0x1f
004f076b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f0774 cvtpd2ps xmm1, xmm0
004f0778 movss xmm0, dword ptr [0xb6addc]
004f0780 mulss xmm1, xmm2
004f0784 mulss xmm1, dword ptr [0xb6a24c]
004f078c subss xmm0, xmm1
004f0790 movss dword ptr [esi + 0x368], xmm0
004f0798 call 0x6c3d90
004f079d movd xmm0, eax
004f07a1 cvtdq2pd xmm0, xmm0
004f07a5 shr eax, 0x1f
004f07a8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f07b1 cvtpd2ps xmm0, xmm0
004f07b5 mulss xmm0, xmm2
004f07b9 mulss xmm0, dword ptr [0xb6a66c]
004f07c1 mov ecx, edi
004f07c3 push esi
004f07c4 mov dword ptr [esi + 0x37c], 0x3f666666
004f07ce mov dword ptr [esi + 0x388], 0
004f07d8 addss xmm0, dword ptr [0xb6a4c4]
004f07e0 mov dword ptr [esi + 0x38c], 0x20
004f07ea movss dword ptr [esi + 0x370], xmm0
004f07f2 call 0x6a19c0
004f07f7 mov eax, dword ptr [esi]
004f07f9 mov ecx, esi
004f07fb call dword ptr [eax + 0xc]
004f07fe sub dword ptr [ebp - 0x19c], 1
004f0805 lea esi, [edi + 0x294]
004f080b jne 0x4f0607
004f0811 jmp 0x4f084a
004f0813 lea ecx, [ebp - 0x198]
004f0819 mov dword ptr [ebp - 0x1bc], 0x41200000
004f0823 mov dword ptr [ebp - 0x1b8], 0
004f082d call 0x430d70
004f0832 push eax
004f0833 push 7
004f0835 lea eax, [ebp - 0x1bc]
004f083b mov ecx, edi
004f083d push eax
004f083e lea eax, [edi + 0x294]
004f0844 push eax
004f0845 call 0x6a1a20
004f084a mov ecx, dword ptr [ebp - 0xc]
004f084d mov dword ptr fs:[0], ecx
004f0854 pop ecx
004f0855 pop edi
004f0856 pop esi
004f0857 mov ecx, dword ptr [ebp - 0x14]
004f085a xor ecx, ebp
004f085c call 0x9eacd7
004f0861 mov esp, ebp
004f0863 pop ebp
004f0864 mov esp, ebx
004f0866 pop ebx
004f0867 ret 
