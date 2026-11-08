0078cc70 push ebp
0078cc71 mov ebp, esp
0078cc73 and esp, 0xfffffff8
0078cc76 push ecx
0078cc77 push ebx
0078cc78 push esi
0078cc79 push edi
0078cc7a mov edi, ecx
0078cc7c mov eax, dword ptr [edi + 0x2c]
0078cc7f test eax, eax
0078cc81 jne 0x78cccb
0078cc83 mov ebx, dword ptr [edi + 0x130c]
0078cc89 lea esi, [edi + 0x1450]
0078cc8f cmp ebx, 0x10
0078cc92 jne 0x78ccad
0078cc94 push 0x78
0078cc96 mov ecx, esi
0078cc98 call 0x88b600
0078cc9d test al, al
0078cc9f je 0x78ccad
0078cca1 lea eax, [ebx - 0xa]
0078cca4 pop edi
0078cca5 pop esi
0078cca6 pop ebx
0078cca7 mov esp, ebp
0078cca9 pop ebp
0078ccaa ret 4
0078ccad cmp ebx, 0x14
0078ccb0 jne 0x78ccd0
0078ccb2 push 0x79
0078ccb4 mov ecx, esi
0078ccb6 call 0x88b600
0078ccbb test al, al
0078ccbd je 0x78ccd0
0078ccbf lea eax, [ebx - 0x10]
0078ccc2 pop edi
0078ccc3 pop esi
0078ccc4 pop ebx
0078ccc5 mov esp, ebp
0078ccc7 pop ebp
0078ccc8 ret 4
0078cccb cmp eax, 1
0078ccce je 0x78cce7
0078ccd0 mov eax, dword ptr [edi + 0x130c]
0078ccd6 cmp eax, 0x10
0078ccd9 je 0x78cce7
0078ccdb cmp eax, 0x11
0078ccde je 0x78cce7
0078cce0 mov ebx, 0x18
0078cce5 jmp 0x78ccf2
0078cce7 mov eax, dword ptr [edi + 0x130c]
0078cced mov ebx, 0xc
0078ccf2 cmp eax, 1
0078ccf5 jne 0x78cd0c
0078ccf7 push 0
0078ccf9 push 0x26b
0078ccfe mov ecx, edi
0078cd00 call 0x73af30
0078cd05 test al, al
0078cd07 je 0x78cd0c
0078cd09 add ebx, 0xc
0078cd0c mov esi, dword ptr [edi + 0x130c]
0078cd12 cmp esi, 0xe
0078cd15 je 0x78cd28
0078cd17 cmp esi, 0x21
0078cd1a je 0x78cd28
0078cd1c cmp byte ptr [ebp + 8], 0
0078cd20 jne 0x78cdad
0078cd26 jmp 0x78cd9a
0078cd28 cmp byte ptr [ebp + 8], 0
0078cd2c jne 0x78cdad
0078cd2e mov ecx, edi
0078cd30 call 0x78fc70
0078cd35 xor ecx, ecx
0078cd37 cmp esi, 0x21
0078cd3a setne cl
0078cd3d cmp dword ptr [edi + 0x130c], 0xe
0078cd44 lea ecx, [ecx*2 + 4]
0078cd4b lea ebx, [ecx + eax*2]
0078cd4e jne 0x78cd65
0078cd50 push 0
0078cd52 push 0x26b
0078cd57 mov ecx, edi
0078cd59 call 0x73af30
0078cd5e test al, al
0078cd60 je 0x78cd65
0078cd62 add ebx, 2
0078cd65 push 0
0078cd67 push 0x1f5
0078cd6c mov ecx, edi
0078cd6e call 0x73af30
0078cd73 test al, al
0078cd75 je 0x78cd9a
0078cd77 mov esi, dword ptr [edi + 0x12b8]
0078cd7d mov eax, 0x51eb851f
0078cd82 imul esi
0078cd84 sar edx, 3
0078cd87 mov ecx, edx
0078cd89 shr ecx, 0x1f
0078cd8c add ecx, edx
0078cd8e cmp esi, 0x63
0078cd91 lea eax, [ecx + 1]
0078cd94 cmovne eax, ecx
0078cd97 lea ebx, [ebx + eax*2]
0078cd9a mov eax, dword ptr [edi + 0x1cc0]
0078cda0 mov ecx, ebx
0078cda2 add eax, eax
0078cda4 xor ebx, ebx
0078cda6 sub ecx, eax
0078cda8 test ecx, ecx
0078cdaa cmovg ebx, ecx
0078cdad pop edi
0078cdae pop esi
0078cdaf mov eax, ebx
0078cdb1 pop ebx
0078cdb2 mov esp, ebp
0078cdb4 pop ebp
0078cdb5 ret 4
0078cdb8 int3 
0078cdb9 int3 
0078cdba int3 
0078cdbb int3 
0078cdbc int3 
0078cdbd int3 
0078cdbe int3 
0078cdbf int3 
0078cdc0 mov eax, dword ptr [ecx + 0x130c]
0078cdc6 add eax, -4
0078cdc9 cmp eax, 0x24
0078cdcc ja 0x78cdf4
0078cdce movzx eax, byte ptr [eax + 0x78ce0c]
0078cdd5 jmp dword ptr [eax*4 + 0x78cdf8]
0078cddc mov eax, 1
0078cde1 ret 
0078cde2 mov eax, 2
0078cde7 ret 
0078cde8 mov eax, 3
0078cded ret 
0078cdee mov eax, 4
0078cdf3 ret 
0078cdf4 xor eax, eax
0078cdf6 ret 
0078cdf7 nop 
0078cdf8 fmul st(5), st(0)
0078cdfa js 0x78cdfc
0078cdfc loop 0x78cdcb
0078cdfe js 0x78ce00
0078ce00 call 0xee7946d2
0078ce05 int 0x78
0078ce07 add ah, dh
0078ce09 int 0x78
0078ce0b add byte ptr [eax], al
0078ce0d add al, 4
0078ce0f add al, 4
0078ce11 add al, 1
0078ce13 add al, 0
0078ce15 add al, 2
0078ce17 add al, 3
0078ce19 add byte ptr [esp + eax], al
0078ce1c add al, 4
0078ce1e add al, 4
0078ce20 add byte ptr [eax], al
0078ce22 add al, 4
0078ce24 add al, 4
0078ce26 add al, 1
0078ce28 add al, 2
0078ce2a add al, 0
0078ce2c add byte ptr [esp + eax], al
0078ce2f add al, 1
0078ce31 int3 
0078ce32 int3 
0078ce33 int3 
0078ce34 int3 
0078ce35 int3 
0078ce36 int3 
0078ce37 int3 
0078ce38 int3 
0078ce39 int3 
0078ce3a int3 
0078ce3b int3 
0078ce3c int3 
0078ce3d int3 
0078ce3e int3 
0078ce3f int3 
0078ce40 mov edx, ecx
0078ce42 call 0x78cdc0
0078ce47 cmp eax, 1
0078ce4a je 0x78ce61
0078ce4c cmp eax, 2
0078ce4f je 0x78ce61
0078ce51 mov ecx, dword ptr [edx + 0x1ca8]
0078ce57 mov eax, dword ptr [edx + 0x1290]
0078ce5d lea eax, [eax + ecx*2]
0078ce60 ret 
0078ce61 mov eax, dword ptr [edx + 0x1290]
0078ce67 ret 
0078ce68 int3 
0078ce69 int3 
0078ce6a int3 
0078ce6b int3 
0078ce6c int3 
0078ce6d int3 
0078ce6e int3 
0078ce6f int3 
0078ce70 push ebp
0078ce71 mov ebp, esp
0078ce73 push ecx
0078ce74 push ebx
0078ce75 push esi
0078ce76 mov esi, ecx
0078ce78 push edi
0078ce79 mov eax, dword ptr [esi + 0x1a0c]
0078ce7f add eax, -0x1b
0078ce82 cmp eax, 0x20
0078ce85 ja 0x78cfc1
0078ce8b movzx eax, byte ptr [eax + 0x78cfe8]
0078ce92 jmp dword ptr [eax*4 + 0x78cfc8]
0078ce99 push 2
0078ce9b call 0x725380
