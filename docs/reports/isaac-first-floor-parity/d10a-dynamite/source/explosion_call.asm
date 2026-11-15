0067cca9 mov eax, dword ptr [ebp - 0xac]
0067ccaf lea ecx, [eax + 0x1450]
0067ccb5 mov dword ptr [ebp - 0x6c], ecx
0067ccb8 jmp 0x67ccc0
0067ccba mov eax, dword ptr [ebp - 0xac]
0067ccc0 cmp byte ptr [edi + 0x398], 0
0067ccc7 jne 0x67ccfa
0067ccc9 test eax, eax
0067cccb je 0x67ccfa
0067cccd push 0
0067cccf push 0x89
0067ccd4 mov ecx, eax
0067ccd6 call 0x73af30
0067ccdb test al, al
0067ccdd je 0x67ccfa
0067ccdf mov ecx, dword ptr [ebp - 0x6c]
0067cce2 push 0x89
0067cce7 call 0x88b570
0067ccec test al, al
0067ccee jne 0x67ccfa
0067ccf0 cmp dword ptr [edi + 0x34], 1
0067ccf4 je 0x67db64
0067ccfa movups xmm1, xmmword ptr [esi]
0067ccfd mov eax, dword ptr [edi + 0x2c]
0067cd00 movups xmmword ptr [ebp - 0x88], xmm1
0067cd07 cmp eax, 0x11
0067cd0a je 0x67cd11
0067cd0c cmp eax, 0x14
0067cd0f jne 0x67cd48
0067cd11 mov eax, dword ptr [0xbc47d0]
0067cd16 or dword ptr [ebp - 0x88], eax
0067cd1c mov eax, dword ptr [0xbc47d4]
0067cd21 or dword ptr [ebp - 0x84], eax
0067cd27 mov eax, dword ptr [0xbc47d8]
0067cd2c or dword ptr [ebp - 0x80], eax
0067cd2f mov eax, dword ptr [0xbc47dc]
0067cd34 or dword ptr [ebp - 0x7c], eax
0067cd37 movups xmm1, xmmword ptr [ebp - 0x88]
0067cd3e mov dword ptr [edi + 0x3a8], 5
0067cd48 cmp byte ptr [edi + 0x398], 0
0067cd4f mov eax, 4
0067cd54 jne 0x67cd5b
0067cd56 mov eax, 0x40000004
0067cd5b movss xmm0, dword ptr [edi + 0x39c]
0067cd63 lea ecx, [edi + 0x294]
0067cd69 push 0
0067cd6b push 0
0067cd6d push eax
0067cd6e push 1
0067cd70 push ecx
0067cd71 movss dword ptr [esp], xmm0
0067cd76 lea eax, [edi + 0xe4]
0067cd7c movss xmm0, dword ptr [edi + 0x368]
0067cd84 push edi
0067cd85 push eax
0067cd86 sub esp, 0x10
0067cd89 mov eax, esp
0067cd8b push ecx
0067cd8c movups xmmword ptr [eax], xmm1
0067cd8f movss dword ptr [esp], xmm0
0067cd94 push ecx
0067cd95 mov ecx, dword ptr [0xbfd65c]
0067cd9b call 0x6d26e0
