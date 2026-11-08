0078c810 push ebx
0078c811 push esi
0078c812 mov esi, ecx
0078c814 push edi
0078c815 cmp byte ptr [esi + 0x16b], 0
0078c81c jne 0x78c869
0078c81e mov edi, dword ptr [esi + 0x186c]
0078c824 test edi, edi
0078c826 jle 0x78c869
0078c828 mov ecx, dword ptr [esi + 0x1290]
0078c82e mov eax, dword ptr [esi + 0x1294]
0078c834 cmp ecx, eax
0078c836 cmovl eax, ecx
0078c839 inc eax
0078c83a cdq 
0078c83b sub eax, edx
0078c83d mov ebx, eax
0078c83f mov eax, dword ptr [esi + 0x129c]
0078c845 inc eax
0078c846 sar ebx, 1
0078c848 cdq 
0078c849 sub eax, edx
0078c84b sar eax, 1
0078c84d add ebx, eax
0078c84f add ebx, dword ptr [esi + 0x1ca8]
0078c855 cmp edi, ebx
0078c857 jle 0x78c869
0078c859 sub edi, ebx
0078c85b mov ecx, esi
0078c85d push edi
0078c85e call 0x78c350
0078c863 mov dword ptr [esi + 0x186c], ebx
0078c869 pop edi
0078c86a pop esi
0078c86b pop ebx
0078c86c ret 
0078c86d int3 
0078c86e int3 
0078c86f int3 
