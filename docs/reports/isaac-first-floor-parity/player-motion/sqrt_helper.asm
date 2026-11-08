004228c0 push ebp
004228c1 mov ebp, esp
004228c3 and esp, 0xfffffff8
004228c6 cvtss2sd xmm0, xmm0
004228ca xorps xmm1, xmm1
004228cd ucomisd xmm1, xmm0
004228d1 ja 0x4228df
004228d3 sqrtsd xmm0, xmm0
004228d7 cvtsd2ss xmm0, xmm0
004228db mov esp, ebp
004228dd pop ebp
004228de ret 
