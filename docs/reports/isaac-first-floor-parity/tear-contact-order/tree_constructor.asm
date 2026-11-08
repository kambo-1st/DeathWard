00416880 push ebp
00416881 mov ebp, esp
00416883 push -1
00416885 push 0x9ecf80
0041688a mov eax, dword ptr fs:[0]
00416890 push eax
00416891 push ecx
00416892 push ebx
00416893 push esi
00416894 push edi
00416895 mov eax, dword ptr [0xbaa3b4]
0041689a xor eax, ebp
0041689c push eax
0041689d lea eax, [ebp - 0xc]
004168a0 mov dword ptr fs:[0], eax
004168a6 mov esi, ecx
004168a8 mov dword ptr [ebp - 0x10], esi
004168ab movss xmm1, dword ptr [ebp + 0xc]
004168b0 mov eax, dword ptr [ebp + 8]
004168b3 mov dword ptr [esi], eax
004168b5 movss dword ptr [esi + 4], xmm3
004168ba movss dword ptr [esi + 8], xmm1
004168bf movss dword ptr [esi + 0x14], xmm2
004168c4 mov dword ptr [esi + 0x18], 0
004168cb mov dword ptr [esi + 0x1c], 0
004168d2 mov dword ptr [esi + 0x20], 0
004168d9 divss xmm1, xmm2
004168dd mov dword ptr [ebp - 4], 0
004168e4 divss xmm3, xmm2
004168e8 addss xmm1, dword ptr [0xb6a480]
004168f0 addss xmm3, dword ptr [0xb6a480]
004168f8 cvttss2si ecx, xmm1
004168fc cvttss2si eax, xmm3
00416900 mov dword ptr [esi + 0x10], ecx
00416903 imul ecx, eax
00416906 mov dword ptr [esi + 0xc], eax
00416909 mov eax, 0x63e7063f
0041690e imul dword ptr [esi + 0x1c]
00416911 sar edx, 6
00416914 mov ebx, edx
00416916 shr ebx, 0x1f
00416919 add ebx, edx
0041691b cmp ecx, ebx
0041691d jae 0x416927
0041691f imul eax, ecx, 0xa4
00416925 jmp 0x416959
00416927 jbe 0x41695c
00416929 mov eax, 0x63e7063f
0041692e imul dword ptr [esi + 0x20]
00416931 sar edx, 6
00416934 mov eax, edx
00416936 shr eax, 0x1f
00416939 add eax, edx
0041693b cmp ecx, eax
0041693d jbe 0x41694b
0041693f push ecx
00416940 push ecx
00416941 lea ecx, [esi + 0x18]
00416944 call 0x418520
00416949 jmp 0x41695c
0041694b push dword ptr [ebp + 8]
0041694e sub ecx, ebx
00416950 push ecx
00416951 push dword ptr [esi + 0x1c]
00416954 call 0x418410
00416959 mov dword ptr [esi + 0x1c], eax
0041695c mov eax, esi
0041695e mov ecx, dword ptr [ebp - 0xc]
00416961 mov dword ptr fs:[0], ecx
00416968 pop ecx
00416969 pop edi
0041696a pop esi
0041696b pop ebx
0041696c mov esp, ebp
0041696e pop ebp
0041696f ret 8
00416972 int3 
00416973 int3 
00416974 int3 
00416975 int3 
00416976 int3 
00416977 int3 
00416978 int3 
00416979 int3 
0041697a int3 
0041697b int3 
