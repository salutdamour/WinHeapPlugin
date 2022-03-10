#include "framework.h"

// command !chunk
DECLARE_API(chunk)
{
	if (!GetExpression(args))
	{
		dprintf("usage: !chunk <chunk header addr>\n");
		return;
	}

	ULONG64 chunk_head = GetExpression(args);
	ULONG64 heap_head = chunk_head & ~0xffff;
	
	HEAP_ENTRY chunk = { 0 };
	HEAP heap = { 0 };
	ULONG bytesRead = 0;

	if (!ReadMemory(heap_head, &heap, sizeof(HEAP), &bytesRead))
	{
		dprintf("[-] failed to read heap header\n");
		return;
	}

	if (!ReadMemory(chunk_head, &chunk, sizeof(HEAP_ENTRY), &bytesRead))
	{
		dprintf("[-] failed to read chunk header\n");
		return;
	}

	// get the xor cookie
	ULONG64 cookie = *(((PULONG64)&heap.Encoding) + 1);
	dprintf("[+] cookie: 0x%I64x\n", cookie);
	dprintf("[+] chunk:  0x%I64x\n", chunk_head);
	
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

// command !freelist
DECLARE_API(freelist)
{
	if (!GetExpression(args))
	{
		dprintf("usage: !freelist <heap header addr>\n");
		return;
	}

	ULONG64 list_header = GetExpression(args) + 0x150;
	dprintf("[+] list entry head: 0x%I64x\n", list_header);

	LIST_ENTRY64 first_list_entry = { 0 };
	ULONG bytesRead = 0;
	
	// first time get the flink and blink
	if (!ReadMemory(list_header, &first_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		dprintf("[-] failed to read list entry\n");
		return;
	}
	dprintf("   [>] Flink: 0x%I64x ", first_list_entry.Flink);

	LIST_ENTRY64 temp_list_entry = { 0 };
	ULONG64 flink = first_list_entry.Flink;
	int count = 2;
	BOOL flag = FALSE;

	while (ReadMemory(flink, &temp_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		if (temp_list_entry.Flink == first_list_entry.Flink)
		{
			break;
		}
		dprintf("-> 0x%I64x ", temp_list_entry.Flink);
		flink = temp_list_entry.Flink;

		// beautify output
		if (count % 6 == 0)
		{
			dprintf("\n           ");
			flag = TRUE;
		}
		else
		{
			flag = FALSE;
		}

		++count;
	}

	if (!flag)
	{
		dprintf("\n");
	}

	dprintf("\n   [>] Blink: 0x%I64x ", first_list_entry.Blink);

	temp_list_entry = { 0 };
	ULONG64 blink = first_list_entry.Blink;
	count = 2;

	while (ReadMemory(blink, &temp_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		if (temp_list_entry.Blink == first_list_entry.Blink)
		{
			break;
		}
		dprintf("-> 0x%I64x ", temp_list_entry.Blink);
		blink = temp_list_entry.Blink;

		if (count % 6 == 0)
		{
			dprintf("\n           ");
			flag = TRUE;
		}
		else
		{
			flag = FALSE;
		}
		++count;
	}

	if (!flag)
	{
		dprintf("\n");
	}

}

// command !heaphelp
DECLARE_API(heaphelp)
{
	dprintf("[+] help for the windbgdll.dll\n");
	dprintf("   [>] !chunk    <addr>  - show the chunk header info\n");
	dprintf("   [>] !freelist <addr>  - show the free list info\n");
	dprintf("   [>] !heaphelp         - show the help message\n");
}