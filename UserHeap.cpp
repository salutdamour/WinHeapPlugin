#include "framework.h"

namespace global
{
	ULONG64 cookie_addr = 0;
}

// command !freelist
DECLARE_API(freelist)
{
	if (!GetExpression(args))
	{
		dprintf("usage: !freelist <heap_addr>\n");
		return;
	}

	CONST ULONG64 list_offset = 0x150, cookie_offset = 0x88;
	ULONG64 list_header = GetExpression(args) + list_offset;
	global::cookie_addr = GetExpression(args) + cookie_offset;
	
	dprintf("[+] freelist head: 0x%I64x\n", list_header);

	LIST_ENTRY64 first_list_entry = { 0 };
	ULONG bytesRead = 0;
	
	// first time get the flink and blink
	if (!ReadMemory(list_header, &first_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		dprintf("[-] failed to read list entry\n");
		return;
	}
	dprintf("   [>] Flink: 0x%I64x ", first_list_entry.Flink - 0x10);

	LIST_ENTRY64 temp_list_entry = { 0 };
	ULONG64 flink = first_list_entry.Flink;
	int count = 2;
	BOOL flag = FALSE;

	// get all flinks
	while (ReadMemory(flink, &temp_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		if (temp_list_entry.Flink == first_list_entry.Flink || temp_list_entry.Flink == list_header)
		{
			break;
		}
		dprintf("-> 0x%I64x ", temp_list_entry.Flink - 0x10);
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
	
	dprintf("\n   [>] Blink: 0x%I64x ", first_list_entry.Blink - 0x10);

	temp_list_entry = { 0 };
	ULONG64 blink = first_list_entry.Blink;
	count = 2; 
	flag = FALSE;

	// get all blinks
	while (ReadMemory(blink, &temp_list_entry, sizeof(LIST_ENTRY64), &bytesRead))
	{
		if (temp_list_entry.Blink == first_list_entry.Blink || temp_list_entry.Blink == list_header)
		{
			break;
		}
		dprintf("-> 0x%I64x ", temp_list_entry.Blink - 0x10);
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

	dprintf("\n");

}

// command !hchunk
DECLARE_API(hchunk)
{
	if (!GetExpression(args))
	{
		dprintf("usage: !chunk <chunk header addr>\n");
		return;
	}

	dprintf("[!] To get the right result, you have to use !freelist <heap_addr> first\n");

	ULONG64 chunk_head = GetExpression(args);
	ULONG64 cookie = 0;
	HEAP_ENTRY chunk = { 0 };
	ULONG bytesRead = 0;

	if (!ReadMemory(global::cookie_addr, &cookie, 8, &bytesRead))
	{
		dprintf("[-] failed to read chunk cookie\n");
		return;
	}

	if (!ReadMemory(chunk_head, &chunk, sizeof(HEAP_ENTRY), &bytesRead))
	{
		dprintf("[-] failed to read chunk header\n");
		return;
	}

	// get the xor cookie
	dprintf("[+] cookie:  0x%I64x\n", cookie);
	dprintf("[+] chunk:  0x%I64x\n", chunk_head);

	// decode the chunk header
	*(((PULONG64)&chunk) + 1) ^= cookie;

	dprintf("   [>] PreviousBlockPrivateData: 0x%I64x ", chunk.PreviousBlockPrivateData);
	BYTE Data[8] = { 0 };
	memcpy(Data, &chunk.PreviousBlockPrivateData, 8);

	for (auto item : Data)
	{
		if (item < 0x10)
		{
			dprintf("0%x ", item);
		}
		else
		{
			dprintf("%x ", item);
		}

	}
	dprintf(" ");

	for (auto item : Data)
	{
		if (item >= 0x20 && item <= 0x7e)
		{
			dprintf("%c", item);
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

DECLARE_API(listhint)
{

}


// command !heaphelp
DECLARE_API(heaphelp)
{
	dprintf("[+] help for the windbgdll.dll\n");
	dprintf("   [>] !heaphelp                - show the help message\n");
	dprintf("   [>] !hchunk   <chunk_addr>   - show the heapchunk info\n");
	dprintf("   [>] !freelist <heap_addr>    - show the freelist info\n");
	dprintf("   [>] !listhint <heap_addr>    - show the listhint info\n");
}