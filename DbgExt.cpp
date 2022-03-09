#include "framework.h"

// command !chunk
DECLARE_API(chunk)
{
	if (!GetExpression(args))
	{
		dprintf("usage: !chunk <chunk_header addr>\n");
		return;
	}

	ULONG64 chunk_addr = GetExpression(args);
	ULONG64 heap_head = chunk_addr & ~0xffff;
	
	HEAP_ENTRY chunk = { 0 };
	HEAP heap = { 0 };

	ULONG bytesRead = 0;
	if (!ReadMemory(heap_head, &heap, sizeof(HEAP), &bytesRead))
	{
		dprintf("[-] failed to read heap header\n");
		return;
	}

	if (!ReadMemory(chunk_addr, &chunk, sizeof(HEAP_ENTRY), &bytesRead))
	{
		dprintf("[-] failed to read chunk header\n");
		return;
	}

	// get the xor cookie
	ULONG64 cookie = *(((PULONG64)&heap.Encoding) + 1);
	dprintf("[+] cookie: 0x%I64x\n", cookie);
	dprintf("[+] chunk:  0x%I64x\n", chunk_addr);
	
	// decode the chunk header
	*(((PULONG64)&chunk) + 1) ^= cookie;
	dprintf("   [>] PreviousBlockPrivateData: 0x%I64x ", chunk.PreviousBlockPrivateData);
	CHAR Data[9] = { 0 };
	memcpy(Data, &chunk.PreviousBlockPrivateData, 8);
	for (ULONG32 i = 0; i < 8; ++i)
	{
		if (Data[i] >= 20 && Data[i] <= 0x7e)
		{
			dprintf("%c", Data[i]);
		}
		else
		{
			dprintf(".");
		}
	}

	dprintf("\n   [>] Size: 0x%x(%u)\n", chunk.Size << 4, chunk.Size << 4);

	if (chunk.Flags & 0x1)
	{
		dprintf("   [>] Flags: 0x%x(busy)\n", chunk.Flags);
	}
	else
	{
		dprintf("   [>] Flags: 0x%x(free)\n", chunk.Flags);
	}
	
	dprintf("   [>] PreviousSize: 0x%x(%u)\n", chunk.PreviousSize << 4, chunk.PreviousSize << 4);
}

// command !heaphelp
DECLARE_API(heaphelp)
{
	dprintf("[+] help for the windbgdll.dll\n");
	dprintf("   [>] !chunk <addr>  - show the chunk header info\n");
	dprintf("   [>] !heaphelp      - show the help message\n");
}