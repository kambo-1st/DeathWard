008b0010 push ebp
008b0011 mov ebp, esp
008b0013 and esp, 0xfffffff8
008b0016 sub esp, 0x18
008b0019 push esi
008b001a push edi
008b001b mov edi, dword ptr [0xbfd680]
008b0021 mov ecx, dword ptr [edi + 0x4a264]
008b0027 mov eax, ecx
008b0029 and eax, 0x80000001
008b002e jns 0x8b0035
008b0030 dec eax
008b0031 or eax, 0xfffffffe
008b0034 inc eax
008b0035 cmp eax, 1
008b0038 jne 0x8b0068
008b003a cmp byte ptr [edi + 0x29e73], 0
008b0041 jne 0x8b0068
008b0043 cmp byte ptr [edi + 0x4a26c], 0
008b004a je 0x8b0059
008b004c cmp byte ptr [edi + 0x4a26d], 0
008b0053 je 0x8b05e1
008b0059 lea eax, [ecx + 1]
008b005c mov dword ptr [edi + 0x4a264], eax
008b0062 pop edi
008b0063 pop esi
008b0064 mov esp, ebp
008b0066 pop ebp
008b0067 ret 
