0063f660 push ebp
0063f661 mov ebp, esp
0063f663 sub esp, 0x94
0063f669 mov eax, dword ptr [0xbaa3b4]
0063f66e xor eax, ebp
0063f670 mov dword ptr [ebp - 4], eax
0063f673 push ebx
0063f674 push esi
0063f675 mov ebx, ecx
0063f677 mov dword ptr [ebp - 0x48], 0
0063f67e mov ecx, dword ptr [0xbfd65c]
0063f684 lea eax, [ebp - 0x48]
0063f687 push edi
0063f688 push eax
0063f689 push dword ptr [ebx + 0x344]
0063f68f lea ecx, [ecx + 0x1ba40]
0063f695 mov dword ptr [ebp - 0x4c], ebx
0063f698 push 0x16
0063f69a call 0x91d680
0063f69f mov eax, dword ptr [0xa08acc]
0063f6a4 movq xmm0, qword ptr [0xa08ac4]
0063f6ac mov ecx, dword ptr [ebx + 0x344]
0063f6b2 mov dword ptr [ebp - 0x5c], eax
0063f6b5 mov eax, dword ptr [ebx + 0x2c]
0063f6b8 mov dword ptr [ebp - 0x68], ecx
0063f6bb movq qword ptr [ebp - 0x64], xmm0
0063f6c0 cmp eax, 5
