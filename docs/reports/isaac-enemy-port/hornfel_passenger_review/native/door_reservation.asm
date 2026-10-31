; Installed-binary disassembly; field interpretations require the source review.
004a8710 push ebp
004a8711 mov ebp, esp
004a8713 push ecx
004a8714 push esi
004a8715 push edi
004a8716 mov edi, ecx
004a8718 cmp dword ptr [edi + 0x31c], 0
004a871f jne 0x4a878e
004a8721 mov eax, dword ptr [edi + 0x314]
004a8727 test eax, eax
004a8729 je 0x4a8734
004a872b cmp dword ptr [eax + 0x31c], 0
004a8732 jne 0x4a878e
004a8734 mov esi, dword ptr [ebp + 8]
004a8737 lea ecx, [edi + 0x31c]
004a873d mov dword ptr [ecx], esi
004a873f test esi, esi
004a8741 je 0x4a8751
004a8743 push ecx
004a8744 mov ecx, esi
004a8746 call 0x4bae70
004a874b mov eax, dword ptr [edi + 0x314]
004a8751 test eax, eax
004a8753 je 0x4a8785
004a8755 mov ecx, dword ptr [eax + 0x31c]
004a875b lea edi, [eax + 0x31c]
004a8761 test ecx, ecx
004a8763 je 0x4a8777
004a8765 lea eax, [ebp + 8]
004a8768 mov dword ptr [ebp + 8], edi
004a876b push eax
004a876c add ecx, 0x324
004a8772 call 0x4bc3c0
004a8777 mov dword ptr [edi], esi
004a8779 test esi, esi
004a877b je 0x4a8785
004a877d push edi
004a877e mov ecx, esi
004a8780 call 0x4bae70
004a8785 mov al, 1
004a8787 pop edi
004a8788 pop esi
004a8789 pop ecx
004a878a pop ebp
004a878b ret 4
004a878e pop edi
004a878f xor al, al
004a8791 pop esi
004a8792 pop ecx
004a8793 pop ebp
