0069cda8 mov eax, dword ptr [edi + 0xab4]
0069cdae cmp eax, 0x12
0069cdb1 je 0x69eb35
0069cdb7 cmp eax, 0x11
0069cdba je 0x69eb35
0069cdc0 mov ecx, edi
0069cdc2 call 0x69b0b0
0069cdc7 test al, al
0069cdc9 jne 0x69cdd4
0069cdcb cmp dword ptr [edi + 0xab4], 1
0069cdd2 jne 0x69cde1
0069cdd4 cmp byte ptr [edi + 0x16b], 0
0069cddb je 0x69eb35
0069cde1 push 0
0069cde3 push 0x100
0069cde8 mov ecx, edi
0069cdea call 0x4122f0
0069cdef test al, al
0069cdf1 jne 0x69ce57
0069cdf3 mov eax, dword ptr [edi + 0xad4]
0069cdf9 cmp eax, 0xb4
0069cdfe jle 0x69ce0c
0069ce00 mov dword ptr [edi + 0xad4], 0xffffffff
0069ce0a jmp 0x69ce1d
0069ce0c cmp eax, 0xffffff4c
0069ce11 jge 0x69ce1d
0069ce13 mov dword ptr [edi + 0xad4], 0
0069ce1d mov ecx, edi
0069ce1f call 0x695680
0069ce24 mov esi, eax
0069ce26 mov ecx, esi
0069ce28 call 0x412100
0069ce2d cmp eax, 3
0069ce30 jne 0x69ce46
0069ce32 mov ecx, esi
0069ce34 call 0x412110
0069ce39 cmp eax, 0x43
0069ce3c jne 0x69ce46
0069ce3e inc dword ptr [edi + 0xad4]
0069ce44 jmp 0x69ce57
0069ce46 mov eax, dword ptr [edi + 0xad4]
0069ce4c test eax, eax
0069ce4e je 0x69ce57
0069ce50 dec eax
0069ce51 mov dword ptr [edi + 0xad4], eax
0069ce57 cmp byte ptr [edi + 0x16b], 0
0069ce5e je 0x69ce88
0069ce60 cmp dword ptr [edi + 0xab4], 1
0069ce67 jne 0x69ce88
0069ce69 mov eax, dword ptr [edi + 0x2c0]
0069ce6f mov dword ptr [edi + 0x2c4], eax
0069ce75 mov eax, dword ptr [edi + 0xab8]
0069ce7b mov dword ptr [edi + 0xab4], eax
0069ce81 mov byte ptr [edi + 0x169], 1
0069ce88 cmp word ptr [edi + 0xbc4], 0
0069ce90 jne 0x69ce99
0069ce92 mov ecx, edi
0069ce94 call 0x699730
