00685510 push ebp
00685511 mov ebp, esp
00685513 and esp, 0xfffffff8
00685516 sub esp, 0x3c
00685519 mov eax, dword ptr [0xbaa3b4]
0068551e xor eax, esp
00685520 mov dword ptr [esp + 0x38], eax
00685524 push ebx
00685525 push esi
00685526 push edi
00685527 mov edi, ecx
00685529 mov ecx, dword ptr [ebp + 8]
0068552c mov eax, dword ptr [edi + 0x160]
00685532 and eax, 0x20000000
00685537 or eax, 0
0068553a jne 0x6857ae
00685540 push ecx
00685541 push dword ptr [ebp + 0xc]
00685544 mov ecx, edi
00685546 call 0x685020
0068554b mov ecx, edi
0068554d mov ebx, eax
0068554f mov esi, edi
00685551 call 0x681710
00685556 test al, al
00685558 je 0x685570
0068555a mov ecx, dword ptr [edi + 0x314]
00685560 test ecx, ecx
00685562 je 0x685570
00685564 mov esi, ecx
00685566 mov ecx, dword ptr [esi + 0x314]
0068556c test ecx, ecx
0068556e jne 0x685564
00685570 mov edx, dword ptr [esi + 0x160]
00685576 mov eax, edx
00685578 mov ecx, dword ptr [esi + 0x164]
0068557e and eax, 0x20000100
00685583 or eax, 0
00685586 mov byte ptr [esp + 0x13], 1
0068558b jne 0x685592
0068558d mov byte ptr [esp + 0x13], 0
00685592 test ebx, ebx
00685594 jle 0x68563f
0068559a mov eax, edx
0068559c and eax, 1
0068559f or eax, 0
006855a2 jne 0x685768
006855a8 cmp dword ptr [esi + 0x230], eax
006855ae jg 0x685768
006855b4 mov ecx, dword ptr [esi + 0x21c]
006855ba xorps xmm0, xmm0
006855bd cmp ecx, ebx
006855bf mov dword ptr [esp + 0x38], 0x3e20a0a1
006855c7 push 1
006855c9 cmovl ecx, ebx
006855cc mov dword ptr [esp + 0x40], 0x3e20a0a1
006855d4 mov dword ptr [esi + 0x21c], ecx
006855da or edx, 0x100
006855e0 mov eax, dword ptr [esi + 0x164]
006855e6 push 0
006855e8 push 0xff
006855ed push ecx
006855ee mov dword ptr [esi + 0x164], eax
006855f4 lea ecx, [esp + 0x28]
006855f8 mov eax, dword ptr [esi]
006855fa movups xmmword ptr [esp + 0x38], xmm0
006855ff push ecx
00685600 movaps xmm0, xmmword ptr [0xb6c470]
00685607 mov ecx, esi
00685609 mov dword ptr [esi + 0x160], edx
0068560f movups xmmword ptr [esp + 0x2c], xmm0
00685614 mov dword ptr [esp + 0x54], 0x3e20a0a1
0068561c call dword ptr [eax + 0x38]
0068561f mov eax, dword ptr [esi]
00685621 mov ecx, esi
00685623 mov eax, dword ptr [eax + 0x48]
00685626 call eax
00685628 test al, al
0068562a je 0x685768
00685630 mov dword ptr [esi + 0x230], 0xf0
0068563a jmp 0x685768
0068563f jns 0x685768
00685645 or edx, 0x20000100
0068564b mov dword ptr [esi + 0x164], ecx
00685651 mov dword ptr [esi + 0x21c], 0
0068565b mov ecx, edi
0068565d mov dword ptr [esi + 0x160], edx
00685663 mov eax, dword ptr [edi]
00685665 mov eax, dword ptr [eax + 0x48]
00685668 call eax
0068566a test al, al
0068566c jne 0x6856a4
0068566e push 0
00685670 mov ecx, edi
00685672 call 0x68cf40
00685677 test al, al
00685679 je 0x6856a4
0068567b cmp dword ptr [edi + 0x28], 0x17
0068567f jne 0x68568d
00685681 cmp dword ptr [edi + 0x2c], 0
00685685 jne 0x68568d
00685687 cmp dword ptr [edi + 0x30], 1
0068568b je 0x6856a4
0068568d mov eax, dword ptr [0xbfd65c]
00685692 push edi
00685693 mov ecx, dword ptr [eax + 0x18190]
00685699 add ecx, 0x1218
0068569f call 0x416340
006856a4 mov ecx, dword ptr [0xbfd65c]
006856aa call 0x6d7180
006856af test al, al
006856b1 jne 0x685754
006856b7 mov eax, dword ptr [0xbfd680]
006856bc cmp byte ptr [eax + 0x1cf], 0
006856c3 jne 0x685754
006856c9 cmp dword ptr [eax + 8], 2
006856cd mov eax, dword ptr [0xbfd65c]
006856d2 jne 0x6856ea
006856d4 test eax, eax
006856d6 je 0x6856ea
006856d8 cmp dword ptr [eax + 0x1c3204], 0
006856df ja 0x685754
006856e1 cmp byte ptr [eax + 0x1c31a1], 0
006856e8 jne 0x685754
006856ea mov edx, dword ptr [eax + 0x18190]
006856f0 xor edi, edi
006856f2 mov ebx, dword ptr [edx + 0x1264]
006856f8 test ebx, ebx
006856fa je 0x685754
006856fc mov edx, dword ptr [edx + 0x125c]
00685702 mov ecx, dword ptr [edx]
00685704 mov eax, dword ptr [ecx + 0x28]
00685707 sub eax, 0xa
0068570a cmp eax, 0x3dd
0068570f ja 0x685734
00685711 mov eax, dword ptr [ecx + 0x160]
00685717 and eax, 0x20000000
0068571c or eax, 0
0068571f je 0x685734
00685721 call 0x681710
00685726 test al, al
00685728 je 0x685733
0068572a cmp dword ptr [ecx + 0x314], 0
00685731 jne 0x685734
00685733 inc edi
00685734 add edx, 4
00685737 sub ebx, 1
0068573a jne 0x685702
0068573c cmp edi, 3
0068573f jb 0x685754
00685741 mov ecx, dword ptr [0xbfd680]
00685747 push 0x183
0068574c add ecx, 0x14
0068574f call 0x884c80
00685754 mov eax, dword ptr [esi + 0x28]
00685757 sub eax, 0xa
0068575a cmp eax, 0x3dd
0068575f ja 0x685768
00685761 mov eax, dword ptr [esi]
00685763 mov ecx, esi
00685765 call dword ptr [eax + 0x5c]
00685768 mov ecx, esi
0068576a call 0x681390
0068576f cmp dword ptr [esi + 0x21c], 0
00685776 je 0x6857ae
00685778 cmp byte ptr [esp + 0x13], 0
0068577d jne 0x6857ae
0068577f mov eax, dword ptr [esi + 0x28]
00685782 sub eax, 0xa
00685785 cmp eax, 0x3dd
0068578a ja 0x6857ae
0068578c push 0
0068578e push 0xbeab70
00685793 push 0xbeab18
00685798 push 0
0068579a push esi
0068579b call 0x9ec34c
006857a0 add esp, 0x14
006857a3 test eax, eax
006857a5 je 0x6857ae
006857a7 mov ecx, eax
006857a9 call 0x680df0
006857ae mov ecx, dword ptr [esp + 0x44]
006857b2 pop edi
006857b3 pop esi
006857b4 pop ebx
006857b5 xor ecx, esp
006857b7 call 0x9eacd7
006857bc mov esp, ebp
006857be pop ebp
006857bf ret 8
