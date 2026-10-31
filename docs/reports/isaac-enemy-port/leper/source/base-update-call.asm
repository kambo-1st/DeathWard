0069f855 mov ecx, edi
0069f857 call 0x6adb50
0069f85c mov ecx, edi
0069f85e call 0x6adfd0
0069f863 test byte ptr [edi + 0xe68], 1
0069f86a je 0x69f887
0069f86c mov ecx, edi
0069f86e mov dword ptr [edi + 0xac4], 1
0069f878 call 0x699730
0069f87d mov dword ptr [edi + 0xac4], 0
0069f887 cmp dword ptr [edi + 0x28], 0x3c5
0069f88e mov ecx, edi
0069f890 movss xmm0, dword ptr [edi + 0x2d8]
0069f898 movss dword ptr [ebp - 0x27c], xmm0
0069f8a0 jne 0x69f8a9
0069f8a2 call 0x4bafb0
0069f8a7 jmp 0x69f8ae
0069f8a9 call 0x6860a0
0069f8ae movss xmm0, dword ptr [ebp - 0x27c]
0069f8b6 lea edx, [ebp - 0x27c]
0069f8bc subss xmm0, dword ptr [edi + 0x2d8]
0069f8c4 lea ecx, [ebp - 0x2a4]
0069f8ca mov dword ptr [ebp - 0x2a4], 0
0069f8d4 movss dword ptr [ebp - 0x27c], xmm0
0069f8dc call 0x417c70
0069f8e1 test byte ptr [edi + 0xe68], 8
0069f8e8 movss xmm0, dword ptr [eax]
0069f8ec addss xmm0, dword ptr [edi + 0xbac]
0069f8f4 movss dword ptr [edi + 0xbac], xmm0
0069f8fc je 0x69f919
0069f8fe mov ecx, edi
0069f900 mov dword ptr [edi + 0xac4], 4
0069f90a call 0x699730
0069f90f mov dword ptr [edi + 0xac4], 0
