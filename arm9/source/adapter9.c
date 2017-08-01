#include "nds/ndstypes.h"
#include "adapter9.h"

FifoValue32HandlerFunc FifoValue32Callback = 0;
FifoAddressHandlerFunc FifoAddressCallback = 0;

void FifoValue32CallbackWrap(int tag, u32 data, bool err) {
	if (FifoValue32Callback)
		FifoValue32Callback(data, 0);
}
	
void FifoAddressCallbackWrap(int tag, u32 data, bool err) {
	if (FifoAddressCallback)
		FifoAddressCallback((void*)data, 0);
}

bool fifoSendValue32(int channel, u32 value32) {
	return PXI_SendWordByFifo(1, value32, 0) >= 0;
}

bool fifoSendAddress(int channel, void *address) {
	return PXI_SendWordByFifo(2, (u32)address, 0) >= 0;
}

bool fifoSetValue32Handler(int channel, FifoValue32HandlerFunc newhandler, void * userdata) {
	if (FifoValue32Callback) return 0;
	FifoValue32Callback = newhandler;
	PXI_SetFifoRecvCallback(1, FifoValue32CallbackWrap);
	return 1;
}

void irqEnable(u32 irq) {
	OS_EnableIrqMask(irq);
}

void irqSet(u32 irq, VoidFn handler) {
	OS_SetIrqFunction(irq, handler);
	*(VoidFn*)(0x27E0018 + 0x28) = handler;
}

static inline u32 uncacheAddr(u32 address)
{
	return (address & 0x3FFFFF) + 0x2400000;
}

void *memUncached(void *address) {
	return (void*)uncacheAddr((u32)address);
}

int * __errno() {
	static int errno = 0;
	return &errno;
}

void swiWaitForVBlank() {
	OS_Sleep(1);
}