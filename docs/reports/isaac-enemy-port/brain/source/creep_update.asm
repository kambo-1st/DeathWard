005d17fc mov ecx, dword ptr [ebp - 0xeb8]
005d1802 cmp dword ptr [ecx + 0x3a0], 0
005d1809 jne 0x5d1cf5
005d180f mov edx, dword ptr [ebp - 0xeb8]
005d1815 mov eax, dword ptr [edx + 0x3a0]
005d181b add eax, 1
005d181e mov ecx, dword ptr [ebp - 0xeb8]
005d1824 mov dword ptr [ecx + 0x3a0], eax
005d182a mov ecx, dword ptr [ebp - 0xeb8]
005d1830 add ecx, 0x3c
005d1833 call 0x4120e0
005d1838 movss xmm0, dword ptr [eax]
005d183c movss dword ptr [ebp - 0xf98], xmm0
005d1844 mov edx, dword ptr [ebp - 0xeb8]
005d184a cmp dword ptr [edx + 0x320], 0
005d1851 je 0x5d1921
005d1857 mov eax, dword ptr [ebp - 0xeb8]
005d185d mov ecx, dword ptr [eax + 0x320]
005d1863 call 0x681340
005d1868 mov dword ptr [ebp - 0x1580], eax
005d186e cmp dword ptr [ebp - 0x1580], 0
005d1875 je 0x5d1921
005d187b mov ecx, dword ptr [ebp - 0x1580]
005d1881 call 0x412240
005d1886 movzx ecx, al
005d1889 test ecx, ecx
005d188b je 0x5d1921
005d1891 push 0
005d1893 push 0x6a
005d1895 mov ecx, dword ptr [ebp - 0x1580]
005d189b call 0x73b950
005d18a0 movzx edx, al
005d18a3 test edx, edx
005d18a5 je 0x5d1921
005d18a7 movss xmm0, dword ptr [ebp - 0xf98]
005d18af comiss xmm0, dword ptr [0xb6a7d8]
005d18b6 jb 0x5d18de
005d18b8 mov eax, dword ptr [ebp - 0xeb8]
005d18be movss xmm0, dword ptr [eax + 0x3c8]
005d18c6 mulss xmm0, dword ptr [0xb6a710]
005d18ce mov ecx, dword ptr [ebp - 0xeb8]
005d18d4 movss dword ptr [ecx + 0x3c8], xmm0
005d18dc jmp 0x5d1921
005d18de movss xmm0, dword ptr [0xb6a60c]
005d18e6 comiss xmm0, dword ptr [ebp - 0xf98]
005d18ed jbe 0x5d1909
005d18ef movss xmm0, dword ptr [ebp - 0xf98]
005d18f7 addss xmm0, dword ptr [0xb6a614]
005d18ff movss dword ptr [ebp - 0xf98], xmm0
005d1907 jmp 0x5d1921
005d1909 movss xmm0, dword ptr [ebp - 0xf98]
005d1911 mulss xmm0, dword ptr [0xb6a710]
005d1919 movss dword ptr [ebp - 0xf98], xmm0
005d1921 movss xmm0, dword ptr [0xb6a60c]
005d1929 comiss xmm0, dword ptr [ebp - 0xf98]
005d1930 jbe 0x5d1959
005d1932 mov ecx, 6
005d1937 call 0x659230
005d193c add eax, 1
005d193f push eax
005d1940 push 0xb45628
005d1945 push 0x20
005d1947 push 0xc049b0
005d194c call 0x418980
005d1951 add esp, 0x10
005d1954 jmp 0x5d1a18
005d1959 mov edx, dword ptr [ebp - 0xeb8]
005d195f cmp dword ptr [edx + 0x2c], 0x5c
005d1963 jne 0x5d198c
005d1965 mov ecx, 6
005d196a call 0x659230
005d196f add eax, 1
005d1972 push eax
005d1973 push 0xb45628
005d1978 push 0x20
005d197a push 0xc049b0
005d197f call 0x418980
005d1984 add esp, 0x10
005d1987 jmp 0x5d1a18
005d198c movss xmm0, dword ptr [0xb6a690]
005d1994 comiss xmm0, dword ptr [ebp - 0xf98]
005d199b jbe 0x5d19c1
005d199d mov ecx, 6
005d19a2 call 0x659230
005d19a7 add eax, 1
005d19aa push eax
005d19ab push 0xb4561c
005d19b0 push 0x20
005d19b2 push 0xc049b0
005d19b7 call 0x418980
005d19bc add esp, 0x10
005d19bf jmp 0x5d1a18
005d19c1 movss xmm0, dword ptr [0xb6a7d8]
005d19c9 comiss xmm0, dword ptr [ebp - 0xf98]
005d19d0 jbe 0x5d19f6
005d19d2 mov ecx, 6
005d19d7 call 0x659230
005d19dc add eax, 1
005d19df push eax
005d19e0 push 0xb4568c
005d19e5 push 0x20
005d19e7 push 0xc049b0
005d19ec call 0x418980
005d19f1 add esp, 0x10
005d19f4 jmp 0x5d1a18
005d19f6 mov ecx, 6
005d19fb call 0x659230
005d1a00 add eax, 1
005d1a03 push eax
005d1a04 push 0xb45678
005d1a09 push 0x20
005d1a0b push 0xc049b0
005d1a10 call 0x418980
005d1a15 add esp, 0x10
005d1a18 movss xmm0, dword ptr [0xb6a9c8]
005d1a20 mulss xmm0, dword ptr [ebp - 0xf98]
005d1a28 mov eax, dword ptr [ebp - 0xeb8]
005d1a2e mulss xmm0, dword ptr [eax + 0x3c8]
005d1a36 mov ecx, dword ptr [ebp - 0xeb8]
005d1a3c movss dword ptr [ecx + 0x2c8], xmm0
005d1a44 mov edx, dword ptr [ebp - 0xeb8]
005d1a4a add edx, 0x3c8
005d1a50 push edx
005d1a51 lea eax, [ebp - 0x327c]
005d1a57 push eax
005d1a58 mov ecx, 0xbc7a28
005d1a5d call 0x962b50
005d1a62 push eax
005d1a63 mov ecx, dword ptr [ebp - 0xeb8]
005d1a69 add ecx, 0x3c
005d1a6c call 0x41b8c0
005d1a71 push 0
005d1a73 push 0xc049b0
005d1a78 mov ecx, dword ptr [ebp - 0xeb8]
005d1a7e add ecx, 0x3c
005d1a81 call 0x4054f0
005d1a86 mov ecx, dword ptr [0xbfd65c]
005d1a8c call 0x402400
005d1a91 mov esi, eax
005d1a93 mov ecx, dword ptr [ebp - 0xeb8]
005d1a99 add ecx, 0x3c
005d1a9c call 0x419b40
005d1aa1 mov ecx, eax
005d1aa3 call 0x432ec0
005d1aa8 mov ecx, eax
005d1aaa mov eax, esi
005d1aac cdq 
005d1aad idiv ecx
005d1aaf mov dword ptr [ebp - 0x1d48], edx
005d1ab5 mov edx, dword ptr [ebp - 0x1d48]
005d1abb push edx
005d1abc mov ecx, dword ptr [ebp - 0xeb8]
005d1ac2 add ecx, 0x3c
005d1ac5 call 0x405890
005d1aca mov eax, dword ptr [ebp - 0xeb8]
005d1ad0 mov ecx, dword ptr [eax + 0x2c]
005d1ad3 mov dword ptr [ebp - 0x13d8], ecx
005d1ad9 mov edx, dword ptr [ebp - 0x13d8]
005d1adf sub edx, 0x2c
005d1ae2 mov dword ptr [ebp - 0x13d8], edx
005d1ae8 cmp dword ptr [ebp - 0x13d8], 0x32
005d1aef ja 0x5d1cd4
005d1af5 mov eax, dword ptr [ebp - 0x13d8]
005d1afb movzx ecx, byte ptr [eax + 0x5e9578]
005d1b02 jmp dword ptr [ecx*4 + 0x5e9568]
005d1b09 push 2
005d1b0b mov ecx, dword ptr [ebp - 0xeb8]
005d1b11 add ecx, 0x3c
005d1b14 call 0x405890
005d1b19 mov ecx, dword ptr [ebp - 0xeb8]
005d1b1f add ecx, 0x3c
005d1b22 call 0x4059d0
005d1b27 jmp 0x5d1cd4
005d1b2c push 0
005d1b2e mov ecx, dword ptr [ebp - 0xeb8]
005d1b34 add ecx, 0x3c
005d1b37 call 0x405890
005d1b3c mov ecx, dword ptr [ebp - 0xeb8]
005d1b42 add ecx, 0x3c
005d1b45 call 0x4059d0
005d1b4a mov edx, dword ptr [ebp - 0xeb8]
005d1b50 cmp dword ptr [edx + 0x2c], 0x36
005d1b54 jne 0x5d1c36
005d1b5a push 0xff
005d1b5f push 0xc9
005d1b64 push 0xa5
005d1b69 push 0x87
005d1b6e lea ecx, [ebp - 0x4580]
005d1b74 call 0x960af0
005d1b79 push eax
005d1b7a mov ecx, dword ptr [ebp - 0xeb8]
005d1b80 add ecx, 0x3c
005d1b83 call 0x4023b0
005d1b88 mov edx, eax
005d1b8a lea ecx, [ebp - 0x28fc]
005d1b90 call 0x4d1ee0
005d1b95 add esp, 4
005d1b98 push ecx
005d1b99 movss xmm0, dword ptr [ebp - 0x28f4]
005d1ba1 movss dword ptr [esp], xmm0
005d1ba6 push ecx
005d1ba7 movss xmm0, dword ptr [ebp - 0x28f8]
005d1baf movss dword ptr [esp], xmm0
005d1bb4 push ecx
005d1bb5 movss xmm0, dword ptr [ebp - 0x28fc]
005d1bbd movss dword ptr [esp], xmm0
005d1bc2 push ecx
005d1bc3 xorps xmm0, xmm0
005d1bc6 movss dword ptr [esp], xmm0
005d1bcb push ecx
005d1bcc xorps xmm0, xmm0
005d1bcf movss dword ptr [esp], xmm0
005d1bd4 push ecx
005d1bd5 xorps xmm0, xmm0
005d1bd8 movss dword ptr [esp], xmm0
005d1bdd push ecx
005d1bde xorps xmm0, xmm0
005d1be1 movss dword ptr [esp], xmm0
005d1be6 push ecx
005d1be7 movss xmm0, dword ptr [0xb6a614]
005d1bef movss dword ptr [esp], xmm0
005d1bf4 xorps xmm3, xmm3
005d1bf7 xorps xmm2, xmm2
005d1bfa xorps xmm1, xmm1
005d1bfd lea ecx, [ebp - 0xb98]
005d1c03 call 0x427150
005d1c08 push eax
005d1c09 mov ecx, dword ptr [ebp - 0xeb8]
005d1c0f add ecx, 0x3c
005d1c12 call 0x402370
005d1c17 mov eax, dword ptr [ebp - 0xeb8]
005d1c1d mov eax, dword ptr [eax + 0x3ac]
005d1c23 cdq 
005d1c24 sub eax, edx
005d1c26 sar eax, 1
005d1c28 mov ecx, dword ptr [ebp - 0xeb8]
005d1c2e mov dword ptr [ecx + 0x3ac], eax
005d1c34 jmp 0x5d1c7c
005d1c36 mov edx, dword ptr [ebp - 0xeb8]
005d1c3c cmp dword ptr [edx + 0x2c], 0x38
005d1c40 jne 0x5d1c7c
005d1c42 push 0x29
005d1c44 push 0x68
005d1c46 push 0xa6
005d1c4b push ecx
005d1c4c movss xmm0, dword ptr [0xb6a614]
005d1c54 movss dword ptr [esp], xmm0
005d1c59 xorps xmm3, xmm3
005d1c5c xorps xmm2, xmm2
005d1c5f xorps xmm1, xmm1
005d1c62 lea ecx, [ebp - 0xb6c]
005d1c68 call 0x4270d0
005d1c6d push eax
005d1c6e mov ecx, dword ptr [ebp - 0xeb8]
005d1c74 add ecx, 0x3c
005d1c77 call 0x402370
005d1c7c jmp 0x5d1cd4
005d1c7e push ecx
005d1c7f xorps xmm0, xmm0
005d1c82 movss dword ptr [esp], xmm0
005d1c87 push ecx
005d1c88 movss xmm0, dword ptr [0xb6a434]
005d1c90 movss dword ptr [esp], xmm0
005d1c95 push ecx
005d1c96 movss xmm0, dword ptr [0xb6a4c4]
005d1c9e movss dword ptr [esp], xmm0
005d1ca3 push ecx
005d1ca4 movss xmm0, dword ptr [0xb6a614]
005d1cac movss dword ptr [esp], xmm0
005d1cb1 xorps xmm3, xmm3
005d1cb4 xorps xmm2, xmm2
005d1cb7 xorps xmm1, xmm1
005d1cba lea ecx, [ebp - 0xb40]
005d1cc0 call 0x408270
005d1cc5 push eax
005d1cc6 mov ecx, dword ptr [ebp - 0xeb8]
005d1ccc add ecx, 0x3c
005d1ccf call 0x402370
005d1cd4 mov ecx, dword ptr [ebp - 0xeb8]
005d1cda add ecx, 0x3c
005d1cdd call 0x4023b0
005d1ce2 mov ecx, eax
005d1ce4 call 0x402220
005d1ce9 mov eax, dword ptr [ebp - 0xeb8]
005d1cef fstp dword ptr [eax + 0x3a4]
005d1cf5 mov ecx, dword ptr [0xbfd65c]
005d1cfb call 0x4023f0
005d1d00 mov dword ptr [ebp - 0x1584], eax
005d1d06 mov ecx, dword ptr [ebp - 0x1584]
005d1d0c call 0x4023e0
005d1d11 comiss xmm0, dword ptr [0xb6a2cc]
005d1d18 jbe 0x5d1d58
005d1d1a push 0
005d1d1c mov ecx, dword ptr [0xbfd65c]
005d1d22 call 0x420330
005d1d27 mov ecx, eax
005d1d29 call 0x706110
005d1d2e cmp eax, 0xc
005d1d31 je 0x5d1d4c
005d1d33 push 0
005d1d35 mov ecx, dword ptr [0xbfd65c]
005d1d3b call 0x420330
005d1d40 mov ecx, eax
005d1d42 call 0x706110
005d1d47 cmp eax, 0x21
005d1d4a jne 0x5d1d58
005d1d4c mov dword ptr [ebp - 0x160c], 1
005d1d56 jmp 0x5d1d62
005d1d58 mov dword ptr [ebp - 0x160c], 0
005d1d62 mov cl, byte ptr [ebp - 0x160c]
005d1d68 mov byte ptr [ebp - 0x1006], cl
005d1d6e mov ecx, dword ptr [ebp - 0x1584]
005d1d74 call 0x427700
005d1d79 mov byte ptr [ebp - 0x1005], al
005d1d7f mov edx, dword ptr [ebp - 0xeb8]
005d1d85 mov eax, dword ptr [edx + 0x2c]
005d1d88 push eax
005d1d89 call 0x5ed040
005d1d8e add esp, 4
005d1d91 mov byte ptr [ebp - 0x1004], al
005d1d97 push 0
005d1d99 push 0x20000000
005d1d9e mov ecx, dword ptr [ebp - 0xeb8]
005d1da4 call 0x4122f0
005d1da9 mov byte ptr [ebp - 0x1003], al
005d1daf movzx ecx, byte ptr [ebp - 0x1003]
005d1db6 test ecx, ecx
005d1db8 jne 0x5d1dfc
005d1dba movzx edx, byte ptr [ebp - 0x1004]
005d1dc1 test edx, edx
005d1dc3 jne 0x5d1dfc
005d1dc5 movzx eax, byte ptr [ebp - 0x1005]
005d1dcc test eax, eax
005d1dce je 0x5d1de6
005d1dd0 mov ecx, dword ptr [ebp - 0x1584]
005d1dd6 call 0x422d70
005d1ddb mov ecx, eax
005d1ddd call 0x447e70
005d1de2 test eax, eax
005d1de4 jle 0x5d1df1
005d1de6 movzx ecx, byte ptr [ebp - 0x1006]
005d1ded test ecx, ecx
005d1def je 0x5d1dfc
005d1df1 mov ecx, dword ptr [ebp - 0xeb8]
005d1df7 call 0x436b60
005d1dfc mov edx, dword ptr [ebp - 0xeb8]
005d1e02 movzx eax, byte ptr [edx + 0x16b]
005d1e09 test eax, eax
005d1e0b jne 0x5d31fd
005d1e11 push 0
005d1e13 push 0x10000
005d1e18 mov ecx, dword ptr [ebp - 0xeb8]
005d1e1e call 0x4122f0
005d1e23 movzx ecx, al
005d1e26 test ecx, ecx
005d1e28 jne 0x5d31fd
005d1e2e mov edx, dword ptr [ebp - 0xeb8]
005d1e34 cmp dword ptr [edx + 0x314], 0
005d1e3b jne 0x5d1e4b
005d1e3d mov eax, dword ptr [ebp - 0xeb8]
005d1e43 mov dword ptr [ebp - 0x1610], eax
005d1e49 jmp 0x5d1e5d
005d1e4b mov ecx, dword ptr [ebp - 0xeb8]
005d1e51 mov edx, dword ptr [ecx + 0x314]
005d1e57 mov dword ptr [ebp - 0x1610], edx
005d1e5d mov eax, dword ptr [ebp - 0x1610]
005d1e63 mov dword ptr [ebp - 0x1d58], eax
005d1e69 push 0
005d1e6b push 0x20000000
005d1e70 mov ecx, dword ptr [ebp - 0xeb8]
005d1e76 call 0x4122f0
005d1e7b mov byte ptr [ebp - 0xf3f], al
005d1e81 mov ecx, dword ptr [ebp - 0xeb8]
005d1e87 cmp dword ptr [ecx + 0x2c], 0x16
005d1e8b je 0x5d1ec7
005d1e8d mov edx, dword ptr [ebp - 0xeb8]
005d1e93 cmp dword ptr [edx + 0x2c], 0x17
005d1e97 je 0x5d1ec7
005d1e99 mov eax, dword ptr [ebp - 0xeb8]
005d1e9f cmp dword ptr [eax + 0x2c], 0x18
005d1ea3 je 0x5d1ec7
005d1ea5 mov ecx, dword ptr [ebp - 0xeb8]
005d1eab cmp dword ptr [ecx + 0x2c], 0xa9
005d1eb2 jne 0x5d2118
005d1eb8 movzx edx, byte ptr [ebp - 0xf3f]
005d1ebf test edx, edx
005d1ec1 jne 0x5d2118
005d1ec7 mov dword ptr [ebp - 0x13dc], 0
005d1ed1 jmp 0x5d1ee2
005d1ed3 mov eax, dword ptr [ebp - 0x13dc]
005d1ed9 add eax, 1
005d1edc mov dword ptr [ebp - 0x13dc], eax
005d1ee2 mov ecx, dword ptr [0xbfd65c]
005d1ee8 call 0x4127b0
005d1eed cmp dword ptr [ebp - 0x13dc], eax
005d1ef3 jae 0x5d2113
005d1ef9 mov ecx, dword ptr [ebp - 0x13dc]
005d1eff push ecx
005d1f00 mov ecx, dword ptr [0xbfd65c]
005d1f06 call 0x412750
005d1f0b mov dword ptr [ebp - 0xf58], eax
005d1f11 mov ecx, dword ptr [ebp - 0xf58]
005d1f17 call 0x412350
005d1f1c movzx edx, al
005d1f1f test edx, edx
005d1f21 jne 0x5d210e
005d1f27 mov ecx, dword ptr [ebp - 0xf58]
005d1f2d call 0x412230
005d1f32 test eax, eax
005d1f34 je 0x5d210e
005d1f3a mov ecx, dword ptr [ebp - 0xf58]
005d1f40 call 0x432f40
005d1f45 cmp eax, 5
005d1f48 jne 0x5d210e
005d1f4e push 0
005d1f50 push 0xe
005d1f52 mov ecx, dword ptr [ebp - 0xf58]
005d1f58 call 0x73b950
005d1f5d movzx eax, al
005d1f60 test eax, eax
005d1f62 jne 0x5d210e
005d1f68 push 0
005d1f6a push 0x23b
005d1f6f mov ecx, dword ptr [ebp - 0xf58]
005d1f75 call 0x73af30
005d1f7a movzx ecx, al
005d1f7d test ecx, ecx
005d1f7f jne 0x5d210e
005d1f85 mov edx, dword ptr [ebp - 0xeb8]
005d1f8b add edx, 0x294
005d1f91 push edx
005d1f92 lea eax, [ebp - 0x2b4c]
005d1f98 push eax
005d1f99 lea ecx, [ebp - 0x3284]
005d1f9f push ecx
005d1fa0 mov ecx, dword ptr [ebp - 0xf58]
005d1fa6 call 0x412130
005d1fab mov ecx, eax
005d1fad call 0x962ac0
005d1fb2 lea ecx, [ebp - 0x2b4c]
005d1fb8 call 0x962a00
005d1fbd fstp dword ptr [ebp - 0x1d4c]
005d1fc3 movss xmm0, dword ptr [ebp - 0x1d4c]
005d1fcb mov ecx, dword ptr [ebp - 0xeb8]
005d1fd1 movss dword ptr [ebp - 0x1d54], xmm0
005d1fd9 call 0x4121c0
005d1fde mov edx, dword ptr [ebp - 0xeb8]
005d1fe4 movss xmm0, dword ptr [edx + 0x2c8]
005d1fec mulss xmm0, dword ptr [eax]
005d1ff0 mov ecx, dword ptr [ebp - 0xf58]
005d1ff6 movss dword ptr [ebp - 0x1d50], xmm0
005d1ffe call 0x4121e0
005d2003 movss xmm1, dword ptr [ebp - 0x1d50]
005d200b addss xmm1, xmm0
005d200f movss xmm0, dword ptr [ebp - 0x1d54]
005d2017 comiss xmm1, xmm0
005d201a jbe 0x5d210e
005d2020 mov edx, dword ptr [ebp - 0xeb8]
005d2026 add edx, 0x294
005d202c lea ecx, [ebp - 0x328c]
005d2032 call 0x6594e0
005d2037 mov ecx, dword ptr [eax + 4]
005d203a push ecx
005d203b mov edx, dword ptr [eax]
005d203d push edx
005d203e lea eax, [ebp - 0x3294]
005d2044 push eax
005d2045 mov ecx, dword ptr [ebp - 0xf58]
005d204b call 0x412130
005d2050 mov edx, eax
005d2052 lea ecx, [ebp - 0x329c]
005d2058 call 0x6594e0
005d205d mov ecx, dword ptr [eax + 4]
005d2060 push ecx
005d2061 mov edx, dword ptr [eax]
005d2063 push edx
005d2064 push -1
005d2066 lea eax, [ebp - 0x2d5c]
005d206c push eax
005d206d mov ecx, dword ptr [ebp - 0xeb8]
005d2073 add ecx, 0x3c
005d2076 call 0x419b40
005d207b movss xmm2, dword ptr [0xb6a480]
005d2083 mov ecx, eax
005d2085 call 0x406460
005d208a movss xmm0, dword ptr [ebp - 0x2d50]
005d2092 comiss xmm0, dword ptr [0xb6a480]
005d2099 jbe 0x5d210e
005d209b mov ecx, dword ptr [ebp - 0x1d58]
005d20a1 push ecx
005d20a2 lea ecx, [ebp - 0x4990]
005d20a8 call 0x4229a0
005d20ad push 0x1e
005d20af lea edx, [ebp - 0x4990]
005d20b5 push edx
005d20b6 push 0
005d20b8 push 0x10
005d20ba push ecx
005d20bb movss xmm0, dword ptr [0xb6a614]
005d20c3 movss dword ptr [esp], xmm0
005d20c8 mov eax, dword ptr [ebp - 0xf58]
005d20ce mov edx, dword ptr [eax]
005d20d0 mov ecx, dword ptr [ebp - 0xf58]
005d20d6 mov eax, dword ptr [edx + 0x20]
005d20d9 call eax
005d20db mov ecx, dword ptr [ebp - 0xeb8]
005d20e1 cmp dword ptr [ecx + 0x2c], 0xa9
005d20e8 je 0x5d210e
005d20ea sub esp, 0x10
005d20ed mov ecx, esp
005d20ef mov dword ptr [ebp - 0x2af4], esp
005d20f5 lea edx, [ebp - 0x2d5c]
005d20fb push edx
005d20fc call 0x960b50
005d2101 push 0
005d2103 mov ecx, dword ptr [ebp - 0xf58]
005d2109 call 0x77da50
005d210e jmp 0x5d1ed3
005d2113 jmp 0x5d31fd
005d2118 mov eax, dword ptr [ebp - 0xeb8]
005d211e cmp dword ptr [eax + 0x2c], 0x19
005d2122 je 0x5d2140
005d2124 mov ecx, dword ptr [ebp - 0xeb8]
005d212a cmp dword ptr [ecx + 0x2c], 0x1a
005d212e je 0x5d2140
005d2130 mov edx, dword ptr [ebp - 0xeb8]
005d2136 cmp dword ptr [edx + 0x2c], 0x38
005d213a jne 0x5d2428
005d2140 mov eax, dword ptr [ebp - 0xeb8]
005d2146 cmp dword ptr [eax + 0x3ac], 0
005d214d jne 0x5d2174
005d214f mov ecx, dword ptr [ebp - 0xeb8]
005d2155 cmp dword ptr [ecx + 0x314], 0
005d215c jne 0x5d2174
005d215e mov ecx, 0x1e
005d2163 call 0x659230
005d2168 mov edx, dword ptr [ebp - 0xeb8]
005d216e mov dword ptr [edx + 0x3ac], eax
005d2174 mov dword ptr [ebp - 0x13e0], 0
005d217e jmp 0x5d218f
005d2180 mov eax, dword ptr [ebp - 0x13e0]
005d2186 add eax, 1
005d2189 mov dword ptr [ebp - 0x13e0], eax
005d218f mov ecx, dword ptr [0xbfd65c]
005d2195 call 0x4127b0
005d219a cmp dword ptr [ebp - 0x13e0], eax
005d21a0 jae 0x5d2423
005d21a6 mov ecx, dword ptr [ebp - 0x13e0]
005d21ac push ecx
005d21ad mov ecx, dword ptr [0xbfd65c]
005d21b3 call 0x412750
005d21b8 mov dword ptr [ebp - 0xf9c], eax
005d21be mov ecx, dword ptr [ebp - 0xf9c]
005d21c4 call 0x412350
005d21c9 movzx edx, al
005d21cc test edx, edx
005d21ce jne 0x5d241e
005d21d4 mov ecx, dword ptr [ebp - 0xf9c]
005d21da call 0x412230
005d21df test eax, eax
005d21e1 je 0x5d241e
005d21e7 mov ecx, dword ptr [ebp - 0xf9c]
005d21ed call 0x432f40
005d21f2 cmp eax, 5
005d21f5 jne 0x5d241e
005d21fb push 0
005d21fd push 0xe
005d21ff mov ecx, dword ptr [ebp - 0xf9c]
005d2205 call 0x73b950
005d220a movzx eax, al
005d220d test eax, eax
005d220f jne 0x5d241e
005d2215 push 0
005d2217 push 0x23b
005d221c mov ecx, dword ptr [ebp - 0xf9c]
005d2222 call 0x73af30
005d2227 movzx ecx, al
005d222a test ecx, ecx
005d222c jne 0x5d241e
005d2232 mov edx, dword ptr [ebp - 0xeb8]
005d2238 add edx, 0x294
005d223e push edx
005d223f lea eax, [ebp - 0x2b54]
005d2245 push eax
005d2246 lea ecx, [ebp - 0x32a4]
005d224c push ecx
005d224d mov ecx, dword ptr [ebp - 0xf9c]
005d2253 call 0x412130
005d2258 mov ecx, eax
005d225a call 0x962ac0
005d225f lea ecx, [ebp - 0x2b54]
005d2265 call 0x962a00
005d226a fstp dword ptr [ebp - 0x1d5c]
005d2270 movss xmm0, dword ptr [ebp - 0x1d5c]
005d2278 mov ecx, dword ptr [ebp - 0xeb8]
005d227e movss dword ptr [ebp - 0x1d64], xmm0
005d2286 call 0x4121c0
005d228b mov edx, dword ptr [ebp - 0xeb8]
005d2291 movss xmm0, dword ptr [edx + 0x2c8]
005d2299 mulss xmm0, dword ptr [eax]
005d229d mov ecx, dword ptr [ebp - 0xf9c]
005d22a3 movss dword ptr [ebp - 0x1d60], xmm0
005d22ab call 0x4121e0
005d22b0 movss xmm1, dword ptr [ebp - 0x1d60]
005d22b8 addss xmm1, xmm0
005d22bc movss xmm0, dword ptr [ebp - 0x1d64]
005d22c4 comiss xmm1, xmm0
005d22c7 jbe 0x5d241e
005d22cd mov edx, dword ptr [ebp - 0xeb8]
005d22d3 add edx, 0x294
005d22d9 lea ecx, [ebp - 0x32ac]
005d22df call 0x6594e0
005d22e4 mov ecx, dword ptr [eax + 4]
005d22e7 push ecx
005d22e8 mov edx, dword ptr [eax]
005d22ea push edx
005d22eb lea eax, [ebp - 0x32b4]
005d22f1 push eax
005d22f2 mov ecx, dword ptr [ebp - 0xf9c]
005d22f8 call 0x412130
005d22fd mov edx, eax
005d22ff lea ecx, [ebp - 0x32bc]
005d2305 call 0x6594e0
005d230a mov ecx, dword ptr [eax + 4]
005d230d push ecx
005d230e mov edx, dword ptr [eax]
005d2310 push edx
005d2311 push -1
005d2313 lea eax, [ebp - 0x2cec]
005d2319 push eax
005d231a mov ecx, dword ptr [ebp - 0xeb8]
005d2320 add ecx, 0x3c
005d2323 call 0x419b40
005d2328 movss xmm2, dword ptr [0xb6a480]
005d2330 mov ecx, eax
005d2332 call 0x406460
005d2337 movss xmm0, dword ptr [ebp - 0x2ce0]
005d233f comiss xmm0, dword ptr [0xb6a480]
005d2346 jbe 0x5d241e
005d234c mov ecx, dword ptr [ebp - 0xeb8]
005d2352 cmp dword ptr [ecx + 0x2c], 0x19
005d2356 jne 0x5d236a
005d2358 movss xmm0, dword ptr [0xb6a53c]
005d2360 movss dword ptr [ebp - 0x1614], xmm0
005d2368 jmp 0x5d237a
005d236a movss xmm0, dword ptr [0xb6a588]
005d2372 movss dword ptr [ebp - 0x1614], xmm0
005d237a movss xmm0, dword ptr [ebp - 0x1614]
005d2382 movss dword ptr [ebp - 0x1d68], xmm0
005d238a mov edx, dword ptr [ebp - 0xeb8]
005d2390 push edx
005d2391 lea ecx, [ebp - 0x4ddc]
005d2397 call 0x4229a0
005d239c sub esp, 0x2c
005d239f mov ecx, esp
005d23a1 mov dword ptr [ebp - 0x2af8], esp
005d23a7 push 0x28
005d23a9 push 0x28
005d23ab push 0x28
005d23ad push ecx
005d23ae movss xmm0, dword ptr [0xb6a614]
005d23b6 movss dword ptr [esp], xmm0
005d23bb movss xmm3, dword ptr [0xb6a690]
005d23c3 movss xmm2, dword ptr [0xb6a614]
005d23cb movss xmm1, dword ptr [0xb6a614]
005d23d3 call 0x4270d0
005d23d8 push ecx
005d23d9 movss xmm0, dword ptr [ebp - 0x1d68]
005d23e1 movss dword ptr [esp], xmm0
005d23e6 push -0xa
005d23e8 lea eax, [ebp - 0x4ddc]
005d23ee push eax
005d23ef mov ecx, dword ptr [ebp - 0xf9c]
005d23f5 call 0x685400
005d23fa sub esp, 0x10
005d23fd mov ecx, esp
005d23ff mov dword ptr [ebp - 0x2afc], esp
005d2405 lea edx, [ebp - 0x2cec]
005d240b push edx
005d240c call 0x960b50
005d2411 push 0
005d2413 mov ecx, dword ptr [ebp - 0xf9c]
005d2419 call 0x77da50
005d241e jmp 0x5d2180
005d2423 jmp 0x5d31fd
005d2428 mov eax, dword ptr [ebp - 0xeb8]
005d242e cmp dword ptr [eax + 0x2c], 0x5e
005d2432 jne 0x5d2680
005d2438 mov ecx, dword ptr [ebp - 0xeb8]
005d243e cmp dword ptr [ecx + 0x3ac], 0
005d2445 jne 0x5d246c
005d2447 mov edx, dword ptr [ebp - 0xeb8]
005d244d cmp dword ptr [edx + 0x314], 0
005d2454 jne 0x5d246c
005d2456 mov ecx, 0x1e
005d245b call 0x659230
005d2460 mov ecx, dword ptr [ebp - 0xeb8]
005d2466 mov dword ptr [ecx + 0x3ac], eax
005d246c mov dword ptr [ebp - 0x13e4], 0
005d2476 jmp 0x5d2487
005d2478 mov edx, dword ptr [ebp - 0x13e4]
005d247e add edx, 1
005d2481 mov dword ptr [ebp - 0x13e4], edx
005d2487 mov ecx, dword ptr [0xbfd65c]
005d248d call 0x4127b0
005d2492 cmp dword ptr [ebp - 0x13e4], eax
005d2498 jae 0x5d267b
005d249e mov eax, dword ptr [ebp - 0x13e4]
005d24a4 push eax
005d24a5 mov ecx, dword ptr [0xbfd65c]
005d24ab call 0x412750
005d24b0 mov dword ptr [ebp - 0xfa0], eax
005d24b6 mov ecx, dword ptr [ebp - 0xfa0]
005d24bc call 0x412350
005d24c1 movzx ecx, al
005d24c4 test ecx, ecx
005d24c6 jne 0x5d2676
005d24cc mov ecx, dword ptr [ebp - 0xfa0]
005d24d2 call 0x412230
005d24d7 test eax, eax
005d24d9 je 0x5d2676
005d24df mov ecx, dword ptr [ebp - 0xfa0]
005d24e5 call 0x432f40
005d24ea cmp eax, 5
005d24ed jne 0x5d2676
005d24f3 push 0
005d24f5 push 0xe
005d24f7 mov ecx, dword ptr [ebp - 0xfa0]
005d24fd call 0x73b950
005d2502 movzx edx, al
005d2505 test edx, edx
005d2507 jne 0x5d2676
005d250d push 0
005d250f push 0x23b
005d2514 mov ecx, dword ptr [ebp - 0xfa0]
005d251a call 0x73af30
005d251f movzx eax, al
005d2522 test eax, eax
005d2524 jne 0x5d2676
005d252a mov ecx, dword ptr [ebp - 0xeb8]
005d2530 add ecx, 0x294
005d2536 push ecx
005d2537 lea edx, [ebp - 0x2b5c]
005d253d push edx
005d253e lea eax, [ebp - 0x32c4]
005d2544 push eax
005d2545 mov ecx, dword ptr [ebp - 0xfa0]
005d254b call 0x412130
005d2550 mov ecx, eax
005d2552 call 0x962ac0
005d2557 lea ecx, [ebp - 0x2b5c]
005d255d call 0x962a00
005d2562 fstp dword ptr [ebp - 0x1d6c]
005d2568 movss xmm0, dword ptr [ebp - 0x1d6c]
005d2570 mov ecx, dword ptr [ebp - 0xeb8]
005d2576 movss dword ptr [ebp - 0x1d74], xmm0
005d257e call 0x4121c0
005d2583 mov ecx, dword ptr [ebp - 0xeb8]
005d2589 movss xmm0, dword ptr [ecx + 0x2c8]
005d2591 mulss xmm0, dword ptr [eax]
005d2595 mov ecx, dword ptr [ebp - 0xfa0]
005d259b movss dword ptr [ebp - 0x1d70], xmm0
005d25a3 call 0x4121e0
005d25a8 movss xmm1, dword ptr [ebp - 0x1d70]
005d25b0 addss xmm1, xmm0
005d25b4 movss xmm0, dword ptr [ebp - 0x1d74]
005d25bc comiss xmm1, xmm0
005d25bf jbe 0x5d2676
005d25c5 mov edx, dword ptr [ebp - 0xeb8]
005d25cb add edx, 0x294
005d25d1 lea ecx, [ebp - 0x32cc]
005d25d7 call 0x6594e0
005d25dc mov edx, dword ptr [eax + 4]
005d25df push edx
005d25e0 mov eax, dword ptr [eax]
005d25e2 push eax
005d25e3 lea ecx, [ebp - 0x32d4]
005d25e9 push ecx
005d25ea mov ecx, dword ptr [ebp - 0xfa0]
005d25f0 call 0x412130
005d25f5 mov edx, eax
005d25f7 lea ecx, [ebp - 0x32dc]
005d25fd call 0x6594e0
005d2602 mov edx, dword ptr [eax + 4]
005d2605 push edx
005d2606 mov eax, dword ptr [eax]
005d2608 push eax
005d2609 push -1
005d260b lea ecx, [ebp - 0x2cfc]
005d2611 push ecx
005d2612 mov ecx, dword ptr [ebp - 0xeb8]
005d2618 add ecx, 0x3c
005d261b call 0x419b40
005d2620 movss xmm2, dword ptr [0xb6a480]
005d2628 mov ecx, eax
005d262a call 0x406460
005d262f movss xmm0, dword ptr [ebp - 0x2cf0]
005d2637 comiss xmm0, dword ptr [0xb6a480]
005d263e jbe 0x5d2676
005d2640 push 0
005d2642 push 0x8000000
005d2647 mov ecx, dword ptr [ebp - 0xfa0]
005d264d call 0x4122a0
005d2652 sub esp, 0x10
005d2655 mov ecx, esp
005d2657 mov dword ptr [ebp - 0x2b00], esp
005d265d lea edx, [ebp - 0x2cfc]
005d2663 push edx
005d2664 call 0x960b50
005d2669 push 0
005d266b mov ecx, dword ptr [ebp - 0xfa0]
005d2671 call 0x77da50
005d2676 jmp 0x5d2478
005d267b jmp 0x5d31fd
005d2680 mov eax, dword ptr [ebp - 0xeb8]
005d2686 cmp dword ptr [eax + 0x2c], 0x2c
005d268a je 0x5d269c
005d268c mov ecx, dword ptr [ebp - 0xeb8]
005d2692 cmp dword ptr [ecx + 0x2c], 0x2d
005d2696 jne 0x5d28c0
005d269c push 8
005d269e mov ecx, dword ptr [ebp - 0xeb8]
005d26a4 add ecx, 0x3c
005d26a7 call 0x4120e0
005d26ac mov edx, dword ptr [ebp - 0xeb8]
005d26b2 movss xmm0, dword ptr [edx + 0x2c8]
005d26ba mulss xmm0, dword ptr [eax]
005d26be mov eax, dword ptr [ebp - 0xeb8]
005d26c4 add eax, 0x294
005d26c9 push eax
005d26ca lea ecx, [ebp - 0x290c]
005d26d0 push ecx
005d26d1 mov ecx, dword ptr [0xbfd65c]
005d26d7 movss dword ptr [ebp - 0x1d78], xmm0
005d26df call 0x4023f0
005d26e4 mov ecx, eax
005d26e6 call 0x422d70
005d26eb movss xmm0, dword ptr [ebp - 0x1d78]
005d26f3 movaps xmm3, xmm0
005d26f6 mov ecx, eax
005d26f8 call 0x4157f0
005d26fd mov dword ptr [ebp - 4], 0x1b
005d2704 mov dword ptr [ebp - 0x13e8], 0
005d270e jmp 0x5d271f
005d2710 mov edx, dword ptr [ebp - 0x13e8]
005d2716 add edx, 1
005d2719 mov dword ptr [ebp - 0x13e8], edx
005d271f lea ecx, [ebp - 0x290c]
005d2725 call 0x4083d0
005d272a cmp dword ptr [ebp - 0x13e8], eax
005d2730 jae 0x5d28a9
005d2736 mov eax, dword ptr [ebp - 0x13e8]
005d273c push eax
005d273d lea ecx, [ebp - 0x290c]
005d2743 call 0x4124b0
005d2748 mov ecx, dword ptr [eax]
005d274a mov dword ptr [ebp - 0x1120], ecx
005d2750 push 0
005d2752 mov ecx, dword ptr [ebp - 0x1120]
005d2758 call 0x684630
005d275d movzx edx, al
005d2760 test edx, edx
005d2762 je 0x5d28a4
005d2768 mov ecx, dword ptr [ebp - 0x1120]
005d276e call 0x684740
005d2773 movzx eax, al
005d2776 test eax, eax
005d2778 jne 0x5d28a4
005d277e mov ecx, dword ptr [ebp - 0xeb8]
005d2784 add ecx, 0x3c
005d2787 call 0x4120e0
005d278c mov ecx, dword ptr [ebp - 0xeb8]
005d2792 movss xmm0, dword ptr [ecx + 0x2c8]
005d279a mulss xmm0, dword ptr [eax]
005d279e mov ecx, dword ptr [ebp - 0x1120]
005d27a4 movss dword ptr [ebp - 0x1d7c], xmm0
005d27ac call 0x4121e0
005d27b1 movss xmm1, dword ptr [ebp - 0x1d7c]
005d27b9 addss xmm1, xmm0
005d27bd movss dword ptr [ebp - 0x1618], xmm1
005d27c5 mov edx, dword ptr [ebp - 0xeb8]
005d27cb add edx, 0x294
005d27d1 push edx
005d27d2 lea eax, [ebp - 0x23f8]
005d27d8 push eax
005d27d9 lea ecx, [ebp - 0x32e4]
005d27df push ecx
005d27e0 mov ecx, dword ptr [ebp - 0x1120]
005d27e6 call 0x412130
005d27eb mov ecx, eax
005d27ed call 0x962ac0
005d27f2 movss xmm0, dword ptr [ebp - 0x23f4]
005d27fa mulss xmm0, dword ptr [0xb6a740]
005d2802 movss dword ptr [ebp - 0x23f4], xmm0
005d280a lea ecx, [ebp - 0x23f8]
005d2810 call 0x962a30
005d2815 fstp dword ptr [ebp - 0x1d80]
005d281b movss xmm0, dword ptr [ebp - 0x1618]
005d2823 mulss xmm0, dword ptr [ebp - 0x1618]
005d282b comiss xmm0, dword ptr [ebp - 0x1d80]
005d2832 jbe 0x5d28a4
005d2834 mov edx, dword ptr [ebp - 0xeb8]
005d283a push edx
005d283b lea ecx, [ebp - 0x49b8]
005d2841 call 0x4229a0
005d2846 sub esp, 0x2c
005d2849 mov ecx, esp
005d284b mov dword ptr [ebp - 0x2b04], esp
005d2851 push 0x28
005d2853 push 0x28
005d2855 push 0x28
005d2857 push ecx
005d2858 movss xmm0, dword ptr [0xb6a614]
005d2860 movss dword ptr [esp], xmm0
005d2865 movss xmm3, dword ptr [0xb6a690]
005d286d movss xmm2, dword ptr [0xb6a614]
005d2875 movss xmm1, dword ptr [0xb6a614]
005d287d call 0x4270d0
005d2882 push ecx
005d2883 movss xmm0, dword ptr [0xb6a5a4]
005d288b movss dword ptr [esp], xmm0
005d2890 push -1
005d2892 lea eax, [ebp - 0x49b8]
005d2898 push eax
005d2899 mov ecx, dword ptr [ebp - 0x1120]
005d289f call 0x685400
005d28a4 jmp 0x5d2710
005d28a9 mov dword ptr [ebp - 4], 0xffffffff
005d28b0 lea ecx, [ebp - 0x290c]
005d28b6 call 0x412490
005d28bb jmp 0x5d31fd
005d28c0 mov ecx, dword ptr [ebp - 0xeb8]
005d28c6 cmp dword ptr [ecx + 0x2c], 0x2e
005d28ca je 0x5d28fa
005d28cc mov edx, dword ptr [ebp - 0xeb8]
005d28d2 cmp dword ptr [edx + 0x2c], 0x36
005d28d6 je 0x5d28fa
005d28d8 mov eax, dword ptr [ebp - 0xeb8]
005d28de cmp dword ptr [eax + 0x2c], 0xa9
005d28e5 jne 0x5d2ff7
005d28eb movzx ecx, byte ptr [ebp - 0xf3f]
005d28f2 test ecx, ecx
005d28f4 jne 0x5d2ff7
005d28fa mov ecx, dword ptr [0xbfd65c]
005d2900 call 0x402400
005d2905 cdq 
005d2906 mov ecx, 3
005d290b idiv ecx
005d290d test edx, edx
005d290f jne 0x5d2ff2
005d2915 push 8
005d2917 mov ecx, dword ptr [ebp - 0xeb8]
005d291d add ecx, 0x3c
005d2920 call 0x4120e0
005d2925 mov edx, dword ptr [ebp - 0xeb8]
005d292b movss xmm0, dword ptr [edx + 0x2c8]
005d2933 mulss xmm0, dword ptr [eax]
005d2937 mov eax, dword ptr [ebp - 0xeb8]
005d293d add eax, 0x294
005d2942 push eax
005d2943 lea ecx, [ebp - 0x292c]
005d2949 push ecx
005d294a mov ecx, dword ptr [0xbfd65c]
005d2950 movss dword ptr [ebp - 0x1d84], xmm0
005d2958 call 0x4023f0
005d295d mov ecx, eax
005d295f call 0x422d70
005d2964 movss xmm0, dword ptr [ebp - 0x1d84]
005d296c movaps xmm3, xmm0
005d296f mov ecx, eax
005d2971 call 0x4157f0
005d2976 mov dword ptr [ebp - 4], 0x1c
005d297d mov dword ptr [ebp - 0x13ec], 0
005d2987 jmp 0x5d2998
005d2989 mov edx, dword ptr [ebp - 0x13ec]
005d298f add edx, 1
005d2992 mov dword ptr [ebp - 0x13ec], edx
005d2998 lea ecx, [ebp - 0x292c]
005d299e call 0x4083d0
005d29a3 cmp dword ptr [ebp - 0x13ec], eax
005d29a9 jae 0x5d2c6b
005d29af mov eax, dword ptr [ebp - 0x13ec]
005d29b5 push eax
005d29b6 lea ecx, [ebp - 0x292c]
005d29bc call 0x4124b0
005d29c1 mov ecx, dword ptr [eax]
005d29c3 mov dword ptr [ebp - 0xf5c], ecx
005d29c9 push 0
005d29cb mov ecx, dword ptr [ebp - 0xf5c]
005d29d1 call 0x684630
005d29d6 movzx edx, al
005d29d9 test edx, edx
005d29db je 0x5d2c66
005d29e1 mov ecx, dword ptr [ebp - 0xf5c]
005d29e7 call 0x684740
005d29ec movzx eax, al
005d29ef test eax, eax
005d29f1 jne 0x5d2c66
005d29f7 mov ecx, dword ptr [ebp - 0xf5c]
005d29fd push ecx
005d29fe mov ecx, dword ptr [ebp - 0xeb8]
005d2a04 add ecx, 0x3cc
005d2a0a call 0x422d00
005d2a0f movzx edx, al
005d2a12 test edx, edx
005d2a14 jne 0x5d2c66
005d2a1a mov ecx, dword ptr [ebp - 0xeb8]
005d2a20 add ecx, 0x3c
005d2a23 call 0x4120e0
005d2a28 mov ecx, dword ptr [ebp - 0xeb8]
005d2a2e movss xmm0, dword ptr [ecx + 0x2c8]
005d2a36 mulss xmm0, dword ptr [eax]
005d2a3a mov ecx, dword ptr [ebp - 0xf5c]
005d2a40 movss dword ptr [ebp - 0x1d88], xmm0
005d2a48 call 0x4121e0
005d2a4d movss xmm1, dword ptr [ebp - 0x1d88]
005d2a55 addss xmm1, xmm0
005d2a59 movss dword ptr [ebp - 0x161c], xmm1
005d2a61 mov edx, dword ptr [ebp - 0xeb8]
005d2a67 add edx, 0x294
005d2a6d push edx
005d2a6e lea eax, [ebp - 0x2400]
005d2a74 push eax
005d2a75 lea ecx, [ebp - 0x32ec]
005d2a7b push ecx
005d2a7c mov ecx, dword ptr [ebp - 0xf5c]
005d2a82 call 0x412130
005d2a87 mov ecx, eax
005d2a89 call 0x962ac0
005d2a8e movss xmm0, dword ptr [ebp - 0x23fc]
005d2a96 mulss xmm0, dword ptr [0xb6a740]
005d2a9e movss dword ptr [ebp - 0x23fc], xmm0
005d2aa6 lea ecx, [ebp - 0x2400]
005d2aac call 0x962a30
005d2ab1 fstp dword ptr [ebp - 0x1d8c]
005d2ab7 movss xmm0, dword ptr [ebp - 0x161c]
005d2abf mulss xmm0, dword ptr [ebp - 0x161c]
005d2ac7 comiss xmm0, dword ptr [ebp - 0x1d8c]
005d2ace jbe 0x5d2c66
005d2ad4 mov edx, dword ptr [ebp - 0xf5c]
005d2ada mov eax, dword ptr [edx + 0x18]
005d2add and eax, 0x10
005d2ae0 mov ecx, dword ptr [edx + 0x1c]
005d2ae3 and ecx, 0
005d2ae6 mov dword ptr [ebp - 0x2408], eax
005d2aec mov dword ptr [ebp - 0x2404], ecx
005d2af2 mov edx, dword ptr [ebp - 0x2408]
005d2af8 or edx, dword ptr [ebp - 0x2404]
005d2afe je 0x5d2bb9
005d2b04 lea eax, [ebp - 0x111c]
005d2b0a push eax
005d2b0b mov ecx, dword ptr [ebp - 0xf5c]
005d2b11 add ecx, 8
005d2b14 call 0x447a00
005d2b19 jmp 0x5d2b26
005d2b1b lea ecx, [ebp - 0x111c]
005d2b21 call 0x48d8f0
005d2b26 lea ecx, [ebp - 0x2be0]
005d2b2c push ecx
005d2b2d mov ecx, dword ptr [ebp - 0xf5c]
005d2b33 add ecx, 8
005d2b36 call 0x4479f0
005d2b3b push eax
005d2b3c lea ecx, [ebp - 0x111c]
005d2b42 call 0x4479d0
005d2b47 movzx edx, al
005d2b4a test edx, edx
005d2b4c je 0x5d2bb7
005d2b4e lea ecx, [ebp - 0x111c]
005d2b54 call 0x4076f0
005d2b59 mov ecx, dword ptr [eax + 8]
005d2b5c and ecx, 0x10
005d2b5f mov edx, dword ptr [eax + 0xc]
005d2b62 and edx, 0
005d2b65 mov dword ptr [ebp - 0x2410], ecx
005d2b6b mov dword ptr [ebp - 0x240c], edx
005d2b71 mov eax, dword ptr [ebp - 0x2410]
005d2b77 or eax, dword ptr [ebp - 0x240c]
005d2b7d je 0x5d2bb2
005d2b7f mov esi, dword ptr [ebp - 0xeb8]
005d2b85 add esi, 0x2e0
005d2b8b lea ecx, [ebp - 0x111c]
005d2b91 call 0x4076f0
005d2b96 mov edx, esi
005d2b98 mov ecx, eax
005d2b9a call 0x417c70
005d2b9f mov esi, eax
005d2ba1 lea ecx, [ebp - 0x111c]
005d2ba7 call 0x4076f0
005d2bac mov ecx, dword ptr [esi]
005d2bae mov dword ptr [eax], ecx
005d2bb0 jmp 0x5d2bb7
005d2bb2 jmp 0x5d2b1b
005d2bb7 jmp 0x5d2bff
005d2bb9 mov edx, dword ptr [ebp - 0xeb8]
005d2bbf push edx
005d2bc0 lea ecx, [ebp - 0x49e0]
005d2bc6 call 0x4229a0
005d2bcb push 0x1e
005d2bcd lea eax, [ebp - 0x49e0]
005d2bd3 push eax
005d2bd4 push 0
005d2bd6 push 0x10
005d2bd8 mov ecx, dword ptr [ebp - 0xeb8]
005d2bde push ecx
005d2bdf movss xmm0, dword ptr [ecx + 0x2e0]
005d2be7 movss dword ptr [esp], xmm0
005d2bec mov edx, dword ptr [ebp - 0xf5c]
005d2bf2 mov eax, dword ptr [edx]
005d2bf4 mov ecx, dword ptr [ebp - 0xf5c]
005d2bfa mov edx, dword ptr [eax + 0x20]
005d2bfd call edx
005d2bff mov eax, dword ptr [ebp - 0xeb8]
005d2c05 cmp dword ptr [eax + 0x2c], 0x36
005d2c09 jne 0x5d2c66
005d2c0b mov ecx, dword ptr [ebp - 0xeb8]
005d2c11 push ecx
005d2c12 movss xmm0, dword ptr [ecx + 0x2e0]
005d2c1a movss dword ptr [esp], xmm0
005d2c1f mov edx, dword ptr [ebp - 0xeb8]
005d2c25 push edx
005d2c26 mov edx, dword ptr [ebp - 0xeb8]
005d2c2c add edx, 0x294
005d2c32 mov eax, dword ptr [ebp - 0xeb8]
005d2c38 add eax, 0x370
005d2c3d sub esp, 0x10
005d2c40 mov ecx, esp
005d2c42 mov esi, dword ptr [eax]
005d2c44 mov dword ptr [ecx], esi
005d2c46 mov esi, dword ptr [eax + 4]
005d2c49 mov dword ptr [ecx + 4], esi
005d2c4c mov esi, dword ptr [eax + 8]
005d2c4f mov dword ptr [ecx + 8], esi
005d2c52 mov eax, dword ptr [eax + 0xc]
005d2c55 mov dword ptr [ecx + 0xc], eax
005d2c58 mov ecx, dword ptr [ebp - 0xf5c]
005d2c5e call 0x654de0
005d2c63 add esp, 0x18
005d2c66 jmp 0x5d2989
005d2c6b mov ecx, dword ptr [ebp - 0xeb8]
005d2c71 cmp dword ptr [ecx + 0x2c], 0x36
005d2c75 jne 0x5d2fe0
005d2c7b push 0xbc4cb0
005d2c80 mov edx, dword ptr [ebp - 0xeb8]
005d2c86 add edx, 0x370
005d2c8c lea ecx, [ebp - 0x4590]
005d2c92 call 0x412050
005d2c97 add esp, 4
005d2c9a mov ecx, eax
005d2c9c call 0x412090
005d2ca1 movzx edx, al
005d2ca4 test edx, edx
005d2ca6 je 0x5d2fca
005d2cac mov eax, dword ptr [ebp - 0xeb8]
005d2cb2 cmp dword ptr [eax + 0x31c], 0
005d2cb9 jne 0x5d2f0c
005d2cbf mov dword ptr [ebp - 0x1624], 0
005d2cc9 movss xmm0, dword ptr [0xb6adb4]
005d2cd1 movss dword ptr [ebp - 0x1620], xmm0
005d2cd9 movss xmm0, dword ptr [0xb6a8f4]
005d2ce1 movss dword ptr [ebp - 0x1d90], xmm0
005d2ce9 push 8
005d2ceb mov ecx, dword ptr [ebp - 0xeb8]
005d2cf1 add ecx, 0x2b8
005d2cf7 push ecx
005d2cf8 lea edx, [ebp - 0x1d90]
005d2cfe lea ecx, [ebp - 0x32f4]
005d2d04 call 0x4120b0
005d2d09 add esp, 4
005d2d0c push eax
005d2d0d lea edx, [ebp - 0x32fc]
005d2d13 push edx
005d2d14 mov ecx, dword ptr [ebp - 0xeb8]
005d2d1a add ecx, 0x294
005d2d20 call 0x962a60
005d2d25 push eax
005d2d26 lea eax, [ebp - 0x291c]
005d2d2c push eax
005d2d2d mov ecx, dword ptr [0xbfd65c]
005d2d33 call 0x4023f0
005d2d38 mov ecx, eax
005d2d3a call 0x422d70
005d2d3f movss xmm3, dword ptr [0xb6ab30]
005d2d47 mov ecx, eax
005d2d49 call 0x4157f0
005d2d4e mov byte ptr [ebp - 4], 0x1d
005d2d52 mov dword ptr [ebp - 0x13f0], 0
005d2d5c jmp 0x5d2d6d
005d2d5e mov ecx, dword ptr [ebp - 0x13f0]
005d2d64 add ecx, 1
005d2d67 mov dword ptr [ebp - 0x13f0], ecx
005d2d6d lea ecx, [ebp - 0x291c]
005d2d73 call 0x4083d0
005d2d78 cmp dword ptr [ebp - 0x13f0], eax
005d2d7e jae 0x5d2eeb
005d2d84 mov edx, dword ptr [ebp - 0x13f0]
005d2d8a push edx
005d2d8b lea ecx, [ebp - 0x291c]
005d2d91 call 0x4124b0
005d2d96 mov eax, dword ptr [eax]
005d2d98 mov dword ptr [ebp - 0x10c8], eax
005d2d9e push 0
005d2da0 mov ecx, dword ptr [ebp - 0x10c8]
005d2da6 call 0x684630
005d2dab movzx ecx, al
005d2dae test ecx, ecx
005d2db0 je 0x5d2ee6
005d2db6 push 0
005d2db8 push 0x20000000
005d2dbd mov ecx, dword ptr [ebp - 0x10c8]
005d2dc3 call 0x4122f0
005d2dc8 movzx edx, al
005d2dcb test edx, edx
005d2dcd jne 0x5d2ee6
005d2dd3 mov ecx, dword ptr [ebp - 0x10c8]
005d2dd9 call 0x432f40
005d2dde cmp eax, 5
005d2de1 jne 0x5d2ee6
005d2de7 movss xmm0, dword ptr [0xb6a8f4]
005d2def movss dword ptr [ebp - 0x1d94], xmm0
005d2df7 lea eax, [ebp - 0x3304]
005d2dfd push eax
005d2dfe mov ecx, dword ptr [ebp - 0x10c8]
005d2e04 call 0x412130
005d2e09 push eax
005d2e0a mov ecx, dword ptr [ebp - 0xeb8]
005d2e10 add ecx, 0x2b8
005d2e16 push ecx
005d2e17 lea edx, [ebp - 0x1d94]
005d2e1d lea ecx, [ebp - 0x330c]
005d2e23 call 0x4120b0
005d2e28 add esp, 4
005d2e2b push eax
005d2e2c lea edx, [ebp - 0x3314]
005d2e32 push edx
005d2e33 mov ecx, dword ptr [ebp - 0xeb8]
005d2e39 add ecx, 0x294
005d2e3f call 0x962a60
005d2e44 mov ecx, eax
005d2e46 call 0x9626f0
005d2e4b fstp dword ptr [ebp - 0x1d98]
005d2e51 movss xmm0, dword ptr [ebp - 0x1d98]
005d2e59 movss dword ptr [ebp - 0x1d9c], xmm0
005d2e61 call 0x659200
005d2e66 mulss xmm0, dword ptr [0xb6ab30]
005d2e6e movss xmm1, dword ptr [ebp - 0x1d9c]
005d2e76 addss xmm1, xmm0
005d2e7a movss dword ptr [ebp - 0x13f4], xmm1
005d2e82 mov eax, dword ptr [ebp - 0x10c8]
005d2e88 push eax
005d2e89 mov ecx, dword ptr [ebp - 0xeb8]
005d2e8f add ecx, 0x3cc
005d2e95 call 0x422d00
005d2e9a movzx ecx, al
005d2e9d test ecx, ecx
005d2e9f je 0x5d2eb9
005d2ea1 movss xmm0, dword ptr [ebp - 0x13f4]
005d2ea9 addss xmm0, dword ptr [0xb6accc]
005d2eb1 movss dword ptr [ebp - 0x13f4], xmm0
005d2eb9 movss xmm0, dword ptr [ebp - 0x1620]
005d2ec1 comiss xmm0, dword ptr [ebp - 0x13f4]
005d2ec8 jbe 0x5d2ee6
005d2eca movss xmm0, dword ptr [ebp - 0x13f4]
005d2ed2 movss dword ptr [ebp - 0x1620], xmm0
005d2eda mov edx, dword ptr [ebp - 0x10c8]
005d2ee0 mov dword ptr [ebp - 0x1624], edx
005d2ee6 jmp 0x5d2d5e
005d2eeb mov eax, dword ptr [ebp - 0x1624]
005d2ef1 push eax
005d2ef2 mov ecx, dword ptr [ebp - 0xeb8]
005d2ef8 call 0x681960
005d2efd mov byte ptr [ebp - 4], 0x1c
005d2f01 lea ecx, [ebp - 0x291c]
005d2f07 call 0x412490
005d2f0c mov ecx, dword ptr [ebp - 0xeb8]
005d2f12 cmp dword ptr [ecx + 0x31c], 0
005d2f19 je 0x5d2fc8
005d2f1f mov edx, dword ptr [ebp - 0xeb8]
005d2f25 add edx, 0x294
005d2f2b push edx
005d2f2c lea eax, [ebp - 0x2418]
005d2f32 push eax
005d2f33 lea ecx, [ebp - 0x331c]
005d2f39 push ecx
005d2f3a mov edx, dword ptr [ebp - 0xeb8]
005d2f40 mov ecx, dword ptr [edx + 0x31c]
005d2f46 call 0x412130
005d2f4b mov ecx, eax
005d2f4d call 0x962ac0
005d2f52 lea ecx, [ebp - 0x2418]
005d2f58 call 0x962a00
005d2f5d fstp dword ptr [ebp - 0x1da0]
005d2f63 movss xmm0, dword ptr [ebp - 0x1da0]
005d2f6b comiss xmm0, dword ptr [0xb6a8cc]
005d2f72 jbe 0x5d2f8d
005d2f74 push ecx
005d2f75 movss xmm0, dword ptr [0xb6a8cc]
005d2f7d movss dword ptr [esp], xmm0
005d2f82 lea ecx, [ebp - 0x2418]
005d2f88 call 0x962860
005d2f8d movss xmm0, dword ptr [0xb6a974]
005d2f95 movss dword ptr [ebp - 0x1da4], xmm0
005d2f9d lea eax, [ebp - 0x1da4]
005d2fa3 push eax
005d2fa4 lea ecx, [ebp - 0x3324]
005d2faa push ecx
005d2fab lea ecx, [ebp - 0x2418]
005d2fb1 call 0x962c10
005d2fb6 push eax
005d2fb7 mov ecx, dword ptr [ebp - 0xeb8]
005d2fbd add ecx, 0x2b8
005d2fc3 call 0x962a90
005d2fc8 jmp 0x5d2fe0
005d2fca push 0xc02fec
005d2fcf mov ecx, dword ptr [ebp - 0xeb8]
005d2fd5 add ecx, 0x2b8
005d2fdb call 0x962cd0
005d2fe0 mov dword ptr [ebp - 4], 0xffffffff
005d2fe7 lea ecx, [ebp - 0x292c]
005d2fed call 0x412490
005d2ff2 jmp 0x5d31fd
005d2ff7 mov edx, dword ptr [ebp - 0xeb8]
005d2ffd cmp dword ptr [edx + 0x2c], 0x35
005d3001 jne 0x5d31fd
005d3007 push 8
005d3009 mov ecx, dword ptr [ebp - 0xeb8]
005d300f add ecx, 0x3c
005d3012 call 0x4120e0
005d3017 mov ecx, dword ptr [ebp - 0xeb8]
005d301d movss xmm0, dword ptr [ecx + 0x2c8]
005d3025 mulss xmm0, dword ptr [eax]
005d3029 mov edx, dword ptr [ebp - 0xeb8]
005d302f add edx, 0x294
005d3035 push edx
005d3036 lea eax, [ebp - 0x293c]
005d303c push eax
005d303d mov ecx, dword ptr [0xbfd65c]
005d3043 movss dword ptr [ebp - 0x1da8], xmm0
005d304b call 0x4023f0
005d3050 mov ecx, eax
005d3052 call 0x422d70
005d3057 movss xmm0, dword ptr [ebp - 0x1da8]
005d305f movaps xmm3, xmm0
005d3062 mov ecx, eax
005d3064 call 0x4157f0
005d3069 mov dword ptr [ebp - 4], 0x1e
005d3070 mov dword ptr [ebp - 0x13f8], 0
005d307a jmp 0x5d308b
005d307c mov ecx, dword ptr [ebp - 0x13f8]
005d3082 add ecx, 1
005d3085 mov dword ptr [ebp - 0x13f8], ecx
005d308b lea ecx, [ebp - 0x293c]
005d3091 call 0x4083d0
005d3096 cmp dword ptr [ebp - 0x13f8], eax
005d309c jae 0x5d31eb
005d30a2 mov edx, dword ptr [ebp - 0x13f8]
005d30a8 push edx
005d30a9 lea ecx, [ebp - 0x293c]
005d30af call 0x4124b0
005d30b4 mov eax, dword ptr [eax]
005d30b6 mov dword ptr [ebp - 0x10c4], eax
005d30bc push 0
005d30be mov ecx, dword ptr [ebp - 0x10c4]
005d30c4 call 0x684630
005d30c9 movzx ecx, al
005d30cc test ecx, ecx
005d30ce je 0x5d31e6
005d30d4 mov ecx, dword ptr [ebp - 0x10c4]
005d30da call 0x684740
005d30df movzx edx, al
005d30e2 test edx, edx
005d30e4 jne 0x5d31e6
005d30ea mov ecx, dword ptr [ebp - 0xeb8]
005d30f0 add ecx, 0x3c
005d30f3 call 0x4120e0
005d30f8 mov ecx, dword ptr [ebp - 0xeb8]
005d30fe movss xmm0, dword ptr [ecx + 0x2c8]
005d3106 mulss xmm0, dword ptr [eax]
005d310a mov ecx, dword ptr [ebp - 0x10c4]
005d3110 movss dword ptr [ebp - 0x1dac], xmm0
005d3118 call 0x4121e0
005d311d movss xmm1, dword ptr [ebp - 0x1dac]
005d3125 addss xmm1, xmm0
005d3129 movss dword ptr [ebp - 0x1628], xmm1
005d3131 mov edx, dword ptr [ebp - 0xeb8]
005d3137 add edx, 0x294
005d313d push edx
005d313e lea eax, [ebp - 0x2420]
005d3144 push eax
005d3145 lea ecx, [ebp - 0x332c]
005d314b push ecx
005d314c mov ecx, dword ptr [ebp - 0x10c4]
005d3152 call 0x412130
005d3157 mov ecx, eax
005d3159 call 0x962ac0
005d315e movss xmm0, dword ptr [ebp - 0x241c]
005d3166 mulss xmm0, dword ptr [0xb6a740]
005d316e movss dword ptr [ebp - 0x241c], xmm0
005d3176 lea ecx, [ebp - 0x2420]
005d317c call 0x962a30
005d3181 fstp dword ptr [ebp - 0x1db0]
005d3187 movss xmm0, dword ptr [ebp - 0x1628]
005d318f mulss xmm0, dword ptr [ebp - 0x1628]
005d3197 comiss xmm0, dword ptr [ebp - 0x1db0]
005d319e jbe 0x5d31e6
005d31a0 mov edx, dword ptr [ebp - 0xeb8]
005d31a6 push edx
005d31a7 lea ecx, [ebp - 0x4a08]
005d31ad call 0x4229a0
005d31b2 push 0x1e
005d31b4 lea eax, [ebp - 0x4a08]
005d31ba push eax
005d31bb push 0
005d31bd push 0
005d31bf mov ecx, dword ptr [ebp - 0xeb8]
005d31c5 push ecx
005d31c6 movss xmm0, dword ptr [ecx + 0x2e0]
005d31ce movss dword ptr [esp], xmm0
005d31d3 mov edx, dword ptr [ebp - 0x10c4]
005d31d9 mov eax, dword ptr [edx]
005d31db mov ecx, dword ptr [ebp - 0x10c4]
005d31e1 mov edx, dword ptr [eax + 0x20]
005d31e4 call edx
005d31e6 jmp 0x5d307c
005d31eb mov dword ptr [ebp - 4], 0xffffffff
005d31f2 lea ecx, [ebp - 0x293c]
005d31f8 call 0x412490
005d31fd mov eax, dword ptr [ebp - 0xeb8]
005d3203 movzx ecx, byte ptr [eax + 0x16b]
005d320a test ecx, ecx
005d320c je 0x5d32e7
005d3212 movss xmm0, dword ptr [0xb6a604]
005d321a movss dword ptr [ebp - 0x1db4], xmm0
005d3222 lea edx, [ebp - 0x1db4]
005d3228 push edx
005d3229 lea eax, [ebp - 0x3334]
005d322f push eax
005d3230 mov ecx, dword ptr [ebp - 0xeb8]
005d3236 add ecx, 0x3c
005d3239 call 0x4120e0
005d323e mov ecx, eax
005d3240 call 0x962b50
005d3245 push eax
005d3246 mov ecx, dword ptr [ebp - 0xeb8]
005d324c add ecx, 0x3c
005d324f call 0x41b8c0
005d3254 mov ecx, dword ptr [ebp - 0xeb8]
005d325a mov edx, 0x28
005d325f sub edx, dword ptr [ecx + 0x3a0]
005d3265 cvtsi2ss xmm2, edx
005d3269 divss xmm2, dword ptr [0xb6aa3c]
005d3271 movss xmm1, dword ptr [0xb6a614]
005d3279 xorps xmm0, xmm0
005d327c call 0x9623e0
005d3281 mov eax, dword ptr [ebp - 0xeb8]
005d3287 mulss xmm0, dword ptr [eax + 0x3a4]
005d328f push ecx
005d3290 movss dword ptr [esp], xmm0
005d3295 mov ecx, dword ptr [ebp - 0xeb8]
005d329b add ecx, 0x3c
005d329e call 0x4023b0
005d32a3 mov ecx, eax
005d32a5 call 0x402230
005d32aa mov ecx, dword ptr [ebp - 0xeb8]
005d32b0 mov edx, dword ptr [ecx + 0x3a0]
005d32b6 add edx, 1
005d32b9 mov eax, dword ptr [ebp - 0xeb8]
005d32bf mov dword ptr [eax + 0x3a0], edx
005d32c5 mov ecx, dword ptr [ebp - 0xeb8]
005d32cb cmp dword ptr [ecx + 0x3a0], 0x28
005d32d2 jle 0x5d32e7
005d32d4 mov edx, dword ptr [ebp - 0xeb8]
005d32da mov eax, dword ptr [edx]
005d32dc mov ecx, dword ptr [ebp - 0xeb8]
005d32e2 mov edx, dword ptr [eax + 0x28]
005d32e5 call edx
005d32e7 jmp 0x5e9122
