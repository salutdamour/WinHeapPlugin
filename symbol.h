#pragma once

struct _HEAP_SEGMENT;
using HEAP_SEGMENT = _HEAP_SEGMENT;
using PHEAP_SEGMENT = _HEAP_SEGMENT*;

struct _HEAP;
using HEAP = _HEAP;
using PHEAP = _HEAP*;

struct _HEAP_ENTRY;
using HEAP_ENTRY = _HEAP_ENTRY;
using PHEAP_ENTRY = _HEAP_ENTRY*;

struct _HEAP_ENTRY
{
	ULONG64 PreviousBlockPrivateData;
	WORD Size;
	BYTE Flags;
	BYTE SmallTagIndex;
	WORD PreviousSize;
	BYTE SegmentOffset;
	BYTE UnusedBytes;
};

struct _HEAP_SEGMENT
{
	_HEAP_ENTRY Entry;
	ULONG32 SegmentSignature;
	ULONG32 SegmentFlags;
	_LIST_ENTRY SegmentListEntry;
	_HEAP * Heap;
	PULONG64 BaseAddress;
	ULONG32 NumberOfPages;
	_HEAP_ENTRY* FirstEntry;
	_HEAP_ENTRY* LastValidEntry;
	ULONG32 NumberOfUnCommittedPages;
	ULONG32 NumberOfUnCommittedRanges;
	WORD SegmentAllocatorBackTraceIndex;
	WORD Reserved;
	_LIST_ENTRY UCRSegmentList;
};

struct _HEAP
{
	_HEAP_SEGMENT Segment;
	ULONG32 Flags;
	ULONG32 ForceFlags;
	ULONG32 CompatibilityFlags;
	ULONG32 EncodeFlagMask;
	_HEAP_ENTRY Encoding;
	ULONG32 Interceptor;
	ULONG32 VirtualMemoryThreshold;
	ULONG32 Signature;
	ULONG64 SegmentReserve;
	ULONG64 SegmentCommit;
	ULONG64 DeCommitFreeBlockThreshold;
	ULONG64 DeCommitTotalFreeThreshold;
	ULONG64 TotalFreeSize;
	ULONG64 MaximumAllocationSize;
	WORD ProcessHeapsListIndex;
	WORD HeaderValidateLength;
	PULONG64 HeaderValidateCopy;
	WORD NextAvailableTagIndex;
	WORD MaximumTagIndex;
	PULONG64 TagEntries;
	_LIST_ENTRY UCRList;
	ULONG64 AlignRound;
	ULONG64 AlignMask;
	_LIST_ENTRY VirtualAllocdBlocks;
	_LIST_ENTRY SegmentList;
	WORD AllocatorBackTraceIndex;
	ULONG32 NonDedicatedListLength;
	PVOID BlocksIndex;
	PVOID UCRIndex;
	PULONG64 PseudoTagEntries;
	_LIST_ENTRY FreeLists;
	PULONG64 LockVariable;
	PULONG64 CommitRoutine;
	PULONG64 StackTraceInitVar;
	BYTE CommitLimitData[0x20];
	PVOID FrontEndHeap;
	WORD FrontHeapLockCount;
	BYTE FrontEndHeapType;
	BYTE RequestedFrontEndHeapType;
	PWCHAR FrontEndHeapUsageData;
	WORD FrontEndHeapMaximumIndex;
	BYTE FrontEndHeapStatusBitmap[129];
	BYTE Counters[0x78];
	BYTE TuningParameters[0x10];
};