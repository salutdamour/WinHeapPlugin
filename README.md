# !chunk
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

# !freelist

```shell
1: kd> !heap 
        Heap Address      NT/Segment Heap

         1800ca50000              NT Heap
         1800c830000              NT Heap
         1800cca0000              NT Heap
         1800ca10000              NT Heap
1: kd> !freelist 1800ca10000
[+] list entry head: 0x1800ca10150
   [>] Flink: 0x1800ca11100 -> 0x1800ca166d0 -> 0x1800ca180e0 -> 0x1800ca10150 

   [>] Blink: 0x1800ca180e0 -> 0x1800ca166d0 -> 0x1800ca11100 -> 0x1800ca10150 
1: kd> !freelist 1800cca0000
[+] list entry head: 0x1800cca0150
   [>] Flink: 0x180113c9f50 -> 0x180113b5a00 -> 0x180113c9060 -> 0x180113c7e70 -> 0x1800ccaeb50 -> 0x180113c80d0 -> 0x180113b3e90 
           -> 0x180113c8280 -> 0x180113b73d0 -> 0x180113c91a0 -> 0x1800cca0150 

   [>] Blink: 0x180113c91a0 -> 0x180113b73d0 -> 0x180113c8280 -> 0x180113b3e90 -> 0x180113c80d0 -> 0x1800ccaeb50 -> 0x180113c7e70 
           -> 0x180113c9060 -> 0x180113b5a00 -> 0x180113c9f50 -> 0x1800cca0150 
```

