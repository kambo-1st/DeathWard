0068694d mov eax, dword ptr [edi + 0x22c]
00686953 test eax, eax
00686955 jle 0x6869dc
0068695b dec eax
0068695c mov dword ptr [edi + 0x22c], eax
00686962 test eax, eax
00686964 jg 0x686982
00686966 and ecx, 0xffffefff
0068696c mov dword ptr [edi + 0x164], edx
00686972 mov dword ptr [edi + 0x160], ecx
00686978 mov dword ptr [edi + 0x27c], 0x40000000
