007458f3 mov ecx, dword ptr [ebp - 0x180]
007458f9 mov edx, dword ptr [edi + 0x132c]
007458ff lea esi, [edi + 0x132c]
00745905 test edx, edx
00745907 je 0x745915
00745909 mov eax, dword ptr [edi + 0x13a8]
0074590f mov dword ptr [edx + 0x10], eax
00745912 mov dword ptr [edx + 0x30], ecx
00745915 mov edx, dword ptr [edi + 0x1330]
0074591b test edx, edx
0074591d je 0x74592b
0074591f mov eax, dword ptr [edi + 0x13a8]
00745925 mov dword ptr [edx + 0x10], eax
00745928 mov dword ptr [edx + 0x30], ecx
0074592b mov edx, dword ptr [edi + 0x1334]
00745931 test edx, edx
00745933 je 0x745941
00745935 mov eax, dword ptr [edi + 0x13a8]
0074593b mov dword ptr [edx + 0x10], eax
0074593e mov dword ptr [edx + 0x30], ecx
00745941 mov edx, dword ptr [edi + 0x1338]
00745947 test edx, edx
00745949 je 0x745957
0074594b mov eax, dword ptr [edi + 0x13a8]
00745951 mov dword ptr [edx + 0x10], eax
00745954 mov dword ptr [edx + 0x30], ecx
00745957 mov edx, dword ptr [edi + 0x1328]
0074595d test edx, edx
0074595f je 0x7459aa
00745961 mov eax, dword ptr [edi + 0x13a8]
00745967 or ecx, 0x80000000
0074596d mov dword ptr [edx + 0x10], eax
