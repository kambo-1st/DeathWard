007a3d8b xor ecx, ecx
007a3d8d movd xmm1, edx
007a3d91 movd xmm0, eax
007a3d95 cvtdq2ps xmm1, xmm1
007a3d98 cvtdq2ps xmm0, xmm0
007a3d9b mulss xmm1, xmm2
007a3d9f mulss xmm0, xmm2
007a3da3 addss xmm1, xmm2
007a3da7 addss xmm0, xmm3
007a3dab movss dword ptr [ebp - 0x34], xmm1
007a3db0 movss dword ptr [ebp - 0x30], xmm0
007a3db5 cmp byte ptr [ebp - 0x23], cl
007a3db8 jne 0x7a3dbf
007a3dba cmp byte ptr [ebp - 0x21], cl
007a3dbd je 0x7a3dc4
007a3dbf mov ecx, 0x384
007a3dc4 mov eax, dword ptr [ebx]
007a3dc6 cmp dword ptr [eax + 0x17c], 3
007a3dcd jne 0x7a3dd8
007a3dcf mov byte ptr [ebx + 0x72c], 1
007a3dd6 jmp 0x7a3dfc
007a3dd8 movzx eax, byte ptr [ebx + 0x738]
007a3ddf push 0
007a3de1 push 0
007a3de3 push eax
007a3de4 push ecx
007a3de5 push 0
007a3de7 lea eax, [ebp - 0x34]
007a3dea mov ecx, esi
007a3dec push eax
007a3ded lea eax, [ebp - 0x6c]
007a3df0 push eax
007a3df1 call 0x7af4b0
007a3df6 mov byte ptr [ebx + 0x72c], al
