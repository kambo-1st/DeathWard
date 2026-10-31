0069f849 mov edi, dword ptr [ebp - 0x2c0]
0069f84f mov esi, dword ptr [ebp - 0x27c]
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
0069f919 mov ecx, dword ptr [0xbfd65c]
0069f91f push 0xf
0069f921 call 0x641630
0069f926 test al, al
0069f928 je 0x69f9c2
0069f92e mov esi, dword ptr [edi]
0069f930 lea ecx, [ebp - 0x110]
0069f936 push 1
0069f938 push 0
0069f93a push 0xff
0069f93f push -1
0069f941 sub esp, 0x10
0069f944 xorps xmm3, xmm3
0069f947 xorps xmm2, xmm2
0069f94a xorps xmm1, xmm1
0069f94d mov dword ptr [esp + 0xc], 0
