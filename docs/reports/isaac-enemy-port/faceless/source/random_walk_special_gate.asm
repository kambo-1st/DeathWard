007a35d0 push ebp
007a35d1 mov ebp, esp
007a35d3 and esp, 0xfffffff8
007a35d6 push esi
007a35d7 mov esi, dword ptr [ecx]
007a35d9 push edi
007a35da test esi, esi
007a35dc je 0x7a3639
007a35de mov eax, dword ptr [esi + 0x160]
007a35e4 and eax, 0x100
007a35e9 or eax, 0
007a35ec jne 0x7a3631
007a35ee mov edi, dword ptr [esi + 0x28]
007a35f1 cmp edi, 0x322
007a35f7 je 0x7a3631
007a35f9 mov ecx, dword ptr [esi + 0x31c]
007a35ff test ecx, ecx
007a3601 je 0x7a3612
007a3603 push 0x100000
007a3608 push eax
007a3609 call 0x4122f0
007a360e test al, al
007a3610 jne 0x7a3631
007a3612 cmp edi, 0xa
007a3615 jl 0x7a3639
007a3617 cmp edi, 0x3e8
007a361d jge 0x7a3639
007a361f cmp dword ptr [esi + 0xe6c], -1
007a3626 jne 0x7a3631
007a3628 cmp dword ptr [esi + 0xe88], 0
007a362f je 0x7a3639
007a3631 mov al, 1
007a3633 pop edi
007a3634 pop esi
007a3635 mov esp, ebp
007a3637 pop ebp
007a3638 ret 
007a3639 pop edi
007a363a xor al, al
007a363c pop esi
007a363d mov esp, ebp
007a363f pop ebp
007a3640 ret 
