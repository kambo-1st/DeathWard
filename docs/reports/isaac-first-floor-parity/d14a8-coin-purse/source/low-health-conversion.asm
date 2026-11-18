00702888 push esi
00702889 mov ecx, edi
0070288b call 0x7876f0
00702890 test al, al
00702892 jne 0x7028b5
00702894 cmp esi, 1
00702897 jne 0x7028aa
00702899 test bl, bl
0070289b mov esi, 5
007028a0 mov eax, 8
007028a5 cmovne esi, eax
007028a8 jmp 0x7028b5
007028aa cmp esi, 6
007028ad jne 0x7028b5
007028af movzx esi, bl
007028b2 add esi, 7
