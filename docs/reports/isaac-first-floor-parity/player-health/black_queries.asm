00725540 push ebp
00725541 mov ebp, esp
00725543 mov edx, dword ptr [ebp + 8]
00725546 push esi
00725547 mov esi, ecx
00725549 cmp edx, dword ptr [esi + 0x129c]
0072554f jg 0x725572
00725551 test edx, edx
00725553 js 0x725572
00725555 mov eax, dword ptr [esi + 0x12a0]
0072555b shr edx, 1
0072555d btr eax, edx
00725560 mov dword ptr [esi + 0x12a0], eax
00725566 call 0x78c810
0072556b mov ecx, esi
0072556d call 0x78cb90
00725572 pop esi
00725573 pop ebp
00725574 ret 4
00725577 int3 
00725578 int3 
00725579 int3 
0072557a int3 
0072557b int3 
0072557c int3 
0072557d int3 
0072557e int3 
0072557f int3 
00725580 push ebp
00725581 mov ebp, esp
00725583 mov eax, dword ptr [ebp + 8]
00725586 push esi
00725587 mov esi, ecx
00725589 cmp eax, dword ptr [esi + 0x129c]
0072558f jg 0x7255b8
00725591 cmp eax, 1
00725594 jl 0x7255b8
00725596 test al, 1
00725598 je 0x7255b8
0072559a dec eax
0072559b cdq 
0072559c sub eax, edx
0072559e mov edx, 1
007255a3 sar eax, 1
007255a5 mov ecx, eax
007255a7 shl edx, cl
007255a9 test dword ptr [esi + 0x12a0], edx
007255af je 0x7255b8
007255b1 mov al, 1
007255b3 pop esi
007255b4 pop ebp
007255b5 ret 4
007255b8 xor al, al
007255ba pop esi
007255bb pop ebp
007255bc ret 4
007255bf int3 
007255c0 mov eax, dword ptr [ecx + 0x129c]
007255c6 inc eax
007255c7 cdq 
007255c8 sub eax, edx
007255ca mov edx, eax
007255cc push esi
007255cd sar edx, 1
007255cf xor esi, esi
007255d1 test edx, edx
007255d3 jle 0x7255f3
007255d5 push edi
007255d6 mov edi, dword ptr [ecx + 0x12a0]
007255dc mov ecx, 1
007255e1 test ecx, edi
007255e3 lea eax, [esi + 1]
007255e6 cmove eax, esi
007255e9 rol ecx, 1
007255eb mov esi, eax
007255ed sub edx, 1
007255f0 jne 0x7255e1
007255f2 pop edi
007255f3 mov eax, esi
007255f5 pop esi
007255f6 ret 
007255f7 int3 
007255f8 int3 
007255f9 int3 
007255fa int3 
007255fb int3 
007255fc int3 
007255fd int3 
007255fe int3 
007255ff int3 
