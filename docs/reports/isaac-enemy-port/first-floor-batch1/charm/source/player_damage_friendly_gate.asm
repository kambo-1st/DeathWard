0073cb0d mov ecx, edi
0073cb0f call 0x79c9b0
0073cb14 test al, al
0073cb16 jne 0x741614
0073cb1c cmp dword ptr [esi], 0x3e8
0073cb22 jne 0x73cb34
0073cb24 cmp dword ptr [esi + 4], 0x13
0073cb28 jne 0x73cb34
0073cb2a cmp dword ptr [esi + 8], 1
0073cb2e je 0x741614
0073cb34 test byte ptr [esi + 0x20], 2
0073cb38 jne 0x741614
0073cb3e mov ecx, dword ptr [ebp + 0x10]
0073cb41 xor eax, eax
0073cb43 and ecx, 4
0073cb46 or eax, ecx
0073cb48 jne 0x741614
