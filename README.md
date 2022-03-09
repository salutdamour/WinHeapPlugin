```shell
1: kd> dq 2a08f180850 2a08f180958
000002a0`8f180850  00000000`00000000 0800bbe9`d83e623f
000002a0`8f180860  61616161`61616161 61616161`61616161
......................................................
000002a0`8f180950  61616161`61616161 0800bbe8`d83e623f
1: kd> !chunk 2a08f180950
[+] cookie: 0xbbf8c93f622f
[+] chunk:  0x2a08f180950
   [>] PreviousBlockPrivateData: 0x6161616161616161 aaaaaaaa
   [>] Size: 0x100(256)
   [>] Flags: 0x1(busy)
   [>] PreviousSize: 0x100(256)
1: kd> !chunk 2a08f180a50
[+] cookie: 0xbbf8c93f622f
[+] chunk:  0x2a08f180a50
   [>] PreviousBlockPrivateData: 0x6161616161616161 aaaaaaaa
   [>] Size: 0x100(256)
   [>] Flags: 0x0(free)
   [>] PreviousSize: 0x100(256)
```

