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
0069ce99 lea eax, [edi + 0x3c]
0069ce9c push 0xb40e34
0069cea1 mov ecx, eax
0069cea3 mov dword ptr [ebp - 0x2b4], eax
0069cea9 call 0x406290
0069ceae test eax, eax
0069ceb0 je 0x69cebc
0069ceb2 cmp byte ptr [eax + 0xc], 0
0069ceb6 jne 0x69cebc
0069ceb8 xor cl, cl
0069ceba jmp 0x69cebe
0069cebc mov cl, 1
0069cebe mov eax, dword ptr [edi + 0xbb4]
