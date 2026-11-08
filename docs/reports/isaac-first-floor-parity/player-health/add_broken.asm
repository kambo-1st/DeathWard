00794390 push ebp
00794391 mov ebp, esp
00794393 and esp, 0xfffffff8
00794396 push esi
00794397 mov esi, ecx
00794399 push edi
0079439a cmp dword ptr [esi + 0x130c], 0x28
007943a1 jne 0x7943b8
007943a3 mov eax, dword ptr [esi + 0x1d80]
007943a9 test eax, eax
007943ab je 0x7943b8
007943ad mov esi, eax
007943af cmp dword ptr [esi + 0x130c], 0x28
007943b6 je 0x7943a3
007943b8 mov edi, dword ptr [esi + 0x1cc0]
007943be mov ecx, esi
007943c0 add edi, dword ptr [ebp + 8]
007943c3 push 1
007943c5 call 0x78cc70
007943ca cdq 
007943cb xor ecx, ecx
007943cd sub eax, edx
007943cf sar eax, 1
007943d1 test edi, edi
007943d3 push 0
007943d5 cmovg ecx, edi
007943d8 cmp ecx, eax
007943da push 0
007943dc cmovl eax, ecx
007943df mov ecx, esi
007943e1 mov dword ptr [esi + 0x1cc0], eax
007943e7 call 0x724d50
007943ec push 0
007943ee push 0x2b6
007943f3 mov ecx, esi
007943f5 call 0x73af30
007943fa test al, al
007943fc je 0x79440c
007943fe or dword ptr [esi + 0x14b8], 1
00794405 mov ecx, esi
00794407 call 0x72ed20
0079440c pop edi
0079440d pop esi
0079440e mov esp, ebp
00794410 pop ebp
00794411 ret 4
00794414 int3 
00794415 int3 
00794416 int3 
00794417 int3 
00794418 int3 
00794419 int3 
0079441a int3 
0079441b int3 
0079441c int3 
0079441d int3 
0079441e int3 
0079441f int3 
