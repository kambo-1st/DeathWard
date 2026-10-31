; Repentance1.7.9b bounded native evidence; names are interpretive.
006ac370 push ebp
006ac371 mov ebp, esp
006ac373 and esp, 0xfffffff8
006ac376 sub esp, 0x3c
006ac379 movss xmm0, dword ptr [ebp + 8]
006ac37e push ebx
006ac37f mov ebx, dword ptr [ebp + 0x14]
006ac382 push esi
006ac383 push edi
006ac384 push dword ptr [ebp + 0x18]
006ac387 mov edi, ecx
006ac389 push ebx
006ac38a push dword ptr [ebp + 0x10]
006ac38d mov dword ptr [esp + 0x44], edi
006ac391 push dword ptr [ebp + 0xc]
006ac394 push ecx
006ac395 movss dword ptr [esp], xmm0
006ac39a call 0x684bb0
