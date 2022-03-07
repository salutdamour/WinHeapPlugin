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
	dprintf("   [>] PreviousBlockPrivateData: 0x%I64x\n", chunk.PreviousBlockPrivateData);
	dprintf("   [>] Size: 0x%x\n", chunk.Size << 4);
	dprintf("   [>] Flags: 0x%x\n", chunk.Flags);
	dprintf("   [>] PreviousSize: 0x%x\n", chunk.PreviousSize << 4);
}

// command !heaphelp
DECLARE_API(heaphelp)
{
	dprintf("[+] help for the windbgdll.dll\n");
	dprintf("   [>] !chunk <addr>  - show the chunk header info\n");
	dprintf("   [>] !heaphelp      - show the help message\n");
}