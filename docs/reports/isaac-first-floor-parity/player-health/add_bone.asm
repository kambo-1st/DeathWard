0078c870 push ebp
0078c871 mov ebp, esp
0078c873 and esp, 0xfffffff8
0078c876 push ecx
0078c877 push ebx
0078c878 push esi
0078c879 push edi
0078c87a mov esi, ecx
0078c87c nop dword ptr [eax]
0078c880 mov edx, dword ptr [esi + 0x130c]
0078c886 cmp edx, 0x28
0078c889 jne 0x78c899
0078c88b mov eax, dword ptr [esi + 0x1d80]
0078c891 test eax, eax
0078c893 je 0x78c899
0078c895 mov esi, eax
0078c897 jmp 0x78c880
0078c899 mov ecx, esi
0078c89b call 0x78cdc0
0078c8a0 cmp eax, 2
0078c8a3 je 0x78c9f5
0078c8a9 call 0x78cdc0
0078c8ae cmp eax, 3
0078c8b1 je 0x78c9d6
0078c8b7 cmp edx, 0x11
0078c8ba jne 0x78c8cf
0078c8bc mov esi, dword ptr [esi + 0x1cb8]
0078c8c2 test esi, esi
0078c8c4 jne 0x78c880
0078c8c6 pop edi
0078c8c7 pop esi
0078c8c8 pop ebx
0078c8c9 mov esp, ebp
0078c8cb pop ebp
0078c8cc ret 4
0078c8cf mov edi, dword ptr [ebp + 8]
0078c8d2 mov ecx, esi
0078c8d4 test edi, edi
0078c8d6 jns 0x78c932
0078c8d8 call 0x78cdc0
0078c8dd cmp eax, 4
0078c8e0 jne 0x78c8ee
0078c8e2 mov eax, edi
0078c8e4 neg eax
0078c8e6 add eax, eax
0078c8e8 push eax
0078c8e9 call 0x724d00
0078c8ee mov ecx, dword ptr [esi + 0x1ca8]
0078c8f4 xor eax, eax
0078c8f6 add ecx, edi
0078c8f8 test ecx, ecx
0078c8fa cmovg eax, ecx
0078c8fd mov ecx, esi
0078c8ff mov dword ptr [esi + 0x1ca8], eax
0078c905 call 0x78ce40
0078c90a mov ecx, dword ptr [esi + 0x1294]
0078c910 cmp eax, ecx
0078c912 cmovl ecx, eax
0078c915 mov dword ptr [esi + 0x1294], ecx
0078c91b mov ecx, esi
0078c91d call 0x78cb90
0078c922 mov ecx, esi
0078c924 call 0x78bf20
0078c929 pop edi
0078c92a pop esi
0078c92b pop ebx
0078c92c mov esp, ebp
0078c92e pop ebp
0078c92f ret 4
0078c932 mov ebx, dword ptr [esi + 0x129c]
0078c938 push 0
0078c93a call 0x78cc70
0078c93f mov ecx, dword ptr [esi + 0x1ca8]
0078c945 add ecx, edi
0078c947 lea ecx, [ebx + ecx*2]
0078c94a sub ecx, eax
0078c94c mov eax, dword ptr [esi + 0x1290]
0078c952 add eax, ecx
0078c954 cmp eax, ebx
0078c956 cmovl ebx, eax
0078c959 test ebx, ebx
0078c95b jle 0x78c967
0078c95d neg ebx
0078c95f mov ecx, esi
0078c961 push ebx
0078c962 call 0x725130
0078c967 push 0
0078c969 mov ecx, esi
0078c96b call 0x78cc70
0078c970 mov ecx, dword ptr [esi + 0x1ca8]
0078c976 mov ebx, dword ptr [esi + 0x129c]
0078c97c cdq 
0078c97d sub eax, edx
0078c97f sar eax, 1
0078c981 lea edx, [ebx + ecx*2]
0078c984 mov ecx, dword ptr [esi + 0x1290]
0078c98a inc ecx
0078c98b add ecx, edx
0078c98d sar ecx, 1
0078c98f sub eax, ecx
0078c991 cmp eax, edi
0078c993 cmovl edi, eax
0078c996 test edi, edi
0078c998 jle 0x78c9f5
0078c99a mov eax, dword ptr [esi + 0x1ca8]
0078c9a0 inc ebx
0078c9a1 mov ecx, dword ptr [esi + 0x1cac]
0078c9a7 sar ebx, 1
0078c9a9 add ebx, eax
0078c9ab add eax, edi
0078c9ad mov dword ptr [esi + 0x1ca8], eax
0078c9b3 xor edx, edx
0078c9b5 lea eax, [edx + ebx]
0078c9b8 inc edx
0078c9b9 bts ecx, eax
0078c9bc cmp edx, edi
0078c9be jl 0x78c9b5
0078c9c0 mov dword ptr [esi + 0x1cac], ecx
0078c9c6 mov ecx, esi
0078c9c8 call 0x78bf20
0078c9cd pop edi
0078c9ce pop esi
0078c9cf pop ebx
0078c9d0 mov esp, ebp
0078c9d2 pop ebp
0078c9d3 ret 4
0078c9d6 mov ecx, dword ptr [ebp + 8]
0078c9d9 test ecx, ecx
0078c9db jle 0x78c9f5
0078c9dd push 0
0078c9df lea eax, [esi + 0x294]
0078c9e5 push eax
0078c9e6 lea eax, [ecx*4]
0078c9ed mov ecx, esi
0078c9ef push eax
0078c9f0 call 0x725cc0
0078c9f5 pop edi
0078c9f6 pop esi
0078c9f7 pop ebx
0078c9f8 mov esp, ebp
0078c9fa pop ebp
0078c9fb ret 4
0078c9fe int3 
0078c9ff int3 
