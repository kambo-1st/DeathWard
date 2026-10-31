; Bounded installed-binary disassembly; field names require separate verification.
00699730 push ebp
00699731 mov ebp, esp
00699733 and esp, 0xfffffff8
00699736 sub esp, 0xc0
0069973c mov eax, dword ptr [0xbaa3b4]
00699741 xor eax, esp
00699743 mov dword ptr [esp + 0xbc], eax
0069974a push esi
0069974b mov esi, ecx
0069974d push edi
0069974e cmp dword ptr [esi + 0xac4], 0
00699755 jne 0x699765
00699757 push esi
00699758 call 0x7fcec0
0069975d test al, al
0069975f jne 0x69a7e2
00699765 mov eax, dword ptr [esi + 0x28]
00699768 add eax, -0xa
0069976b cmp eax, 0x3bd
00699770 ja 0x69a7d3
00699776 movzx eax, byte ptr [eax + 0x69abc0]
0069977d jmp dword ptr [eax*4 + 0x69a7f8]
