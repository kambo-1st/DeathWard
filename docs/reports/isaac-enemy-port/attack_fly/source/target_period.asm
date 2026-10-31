004f6162 push 0
004f6164 push 3
004f6166 mov ecx, esi
004f6168 call 0x684790
004f616d test al, al
004f616f je 0x4f651a
004f6175 cmp edi, 0x12
004f6178 je 0x4f619d
004f617a cmp edi, 0x50
004f617d je 0x4f619d
004f617f cmp edi, 0xd6
004f6185 je 0x4f619d
004f6187 cmp edi, 0xf9
004f618d je 0x4f619d
004f618f mov eax, edi
004f6191 cmp edi, 0x333
004f6197 jne 0x4f6350
004f619d mov ecx, dword ptr [esi + 0x314]
004f61a3 mov eax, edi
004f61a5 test ecx, ecx
004f61a7 je 0x4f6347
004f61ad cmp dword ptr [esi + 0xe6c], -1
