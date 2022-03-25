# WinHeapPlugin

## usage

```shell
.load /path/to/WindbgDll.dll
```

you can use the command  `.chain`  to check if it is loaded.

## !freelist

```shell
3: kd> !heap
        Heap Address      NT/Segment Heap

         1ff3fae0000              NT Heap
         1ff3fa60000              NT Heap
         1ff3fcf0000              NT Heap
         1ff40240000              NT Heap
3: kd> !freelist 1ff3fae0000
[+] freelist head: 0x1ff3fae0150
   [>] Flink: 0x1ff3fb1d1e0 -> 0x1ff3fb05f50 -> 0x1ff3fafd970 -> 0x1ff3fb1a690 -> 0x1ff3fae1500 -> 0x1ff3fb286d0 
           -> 0x1ff3fb1ca20 -> 0x1ff3faf3de0 -> 0x1ff3fb01ff0 -> 0x1ff3fb34a60 -> 0x1ff3fb222e0 -> 0x1ff3fae8210 
           -> 0x1ff3faf4110 -> 0x1ff3fb1cea0 -> 0x1ff3fb0e120 -> 0x1ff3fae6f40 -> 0x1ff3fae6df0 -> 0x1ff3fae71a0 
           -> 0x1ff3fb31610 -> 0x1ff3fb1bd00 -> 0x1ff3fb193e0 -> 0x1ff3fae7ac0 -> 0x1ff3fae8b50 -> 0x1ff3fae8920 
           -> 0x1ff3fb283f0 -> 0x1ff3fb05b20 -> 0x1ff3fb322f0 -> 0x1ff3fb06170 -> 0x1ff3fb19f10 -> 0x1ff3fb057d0 
           -> 0x1ff3fb1e8a0 -> 0x1ff3fb32700 -> 0x1ff3fae7260 -> 0x1ff3fae40e0 -> 0x1ff3fae84a0 -> 0x1ff3fb36e90 
           -> 0x1ff3fb33d50 -> 0x1ff3fb16270 -> 0x1ff3fb25b90 -> 0x1ff3fb24840 -> 0x1ff3faf6a10 -> 0x1ff3fb0f080 
           -> 0x1ff3faffce0 -> 0x1ff3fb2f8b0 -> 0x1ff3fb17eb0 -> 0x1ff3fb06490 -> 0x1ff3fb26710 -> 0x1ff3fb11ab0 
           -> 0x1ff3fb393a0 

   [>] Blink: 0x1ff3fb393a0 -> 0x1ff3fb11ab0 -> 0x1ff3fb26710 -> 0x1ff3fb06490 -> 0x1ff3fb17eb0 -> 0x1ff3fb2f8b0 
           -> 0x1ff3faffce0 -> 0x1ff3fb0f080 -> 0x1ff3faf6a10 -> 0x1ff3fb24840 -> 0x1ff3fb25b90 -> 0x1ff3fb16270 
           -> 0x1ff3fb33d50 -> 0x1ff3fb36e90 -> 0x1ff3fae84a0 -> 0x1ff3fae40e0 -> 0x1ff3fae7260 -> 0x1ff3fb32700 
           -> 0x1ff3fb1e8a0 -> 0x1ff3fb057d0 -> 0x1ff3fb19f10 -> 0x1ff3fb06170 -> 0x1ff3fb322f0 -> 0x1ff3fb05b20 
           -> 0x1ff3fb283f0 -> 0x1ff3fae8920 -> 0x1ff3fae8b50 -> 0x1ff3fae7ac0 -> 0x1ff3fb193e0 -> 0x1ff3fb1bd00 
           -> 0x1ff3fb31610 -> 0x1ff3fae71a0 -> 0x1ff3fae6df0 -> 0x1ff3fae6f40 -> 0x1ff3fb0e120 -> 0x1ff3fb1cea0 
           -> 0x1ff3faf4110 -> 0x1ff3fae8210 -> 0x1ff3fb222e0 -> 0x1ff3fb34a60 -> 0x1ff3fb01ff0 -> 0x1ff3faf3de0 
           -> 0x1ff3fb1ca20 -> 0x1ff3fb286d0 -> 0x1ff3fae1500 -> 0x1ff3fb1a690 -> 0x1ff3fafd970 -> 0x1ff3fb05f50 
           -> 0x1ff3fb1d1e0 
```

## !hchunk

```shell
3: kd> !hchunk 0x1ff3fb1d1e0
[!] To get the right result, you have to use !freelist first
[+] cookie:  0x7a4962b56ebe
[+] chunk:  0x1ff3fb1d1e0
   [>] PreviousBlockPrivateData: 0x0 00 00 00 00 00 00 00 00  ........
   [>] Size: 0x20(32)
   [>] Flags: 0x0(free)
   [>] PreviousSize: 0xb0(176)
3: kd> !hchunk 0x1ff3fb05f50
[!] To get the right result, you have to use !freelist first
[+] cookie:  0x7a4962b56ebe
[+] chunk:  0x1ff3fb05f50
   [>] PreviousBlockPrivateData: 0x0 00 00 00 00 00 00 00 00  ........
   [>] Size: 0x20(32)
   [>] Flags: 0x0(free)
   [>] PreviousSize: 0xb0(176)
```

