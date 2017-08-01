#include "nds/ndstypes.h"
#include "adapter7.h"

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

bool fifoSetValue32Handler(int channel, FifoValue32HandlerFunc newhandler, void * userdata) {
	if (FifoValue32Callback) return 0;
	FifoValue32Callback = newhandler;
	PXI_SetFifoRecvCallback(1, FifoValue32CallbackWrap);
	return 1;
}

bool fifoSetAddressHandler(int channel, FifoAddressHandlerFunc newhandler, void * userdata) {
	if (FifoAddressCallback) return 0;
	FifoAddressCallback = newhandler;
	PXI_SetFifoRecvCallback(2, FifoAddressCallbackWrap);
	return 1;
}

void irqSet(u32 irq, VoidFn handler) {
	OS_SetIrqFunction(irq, handler);
}

void irqDisable(u32 irq) {
	OS_DisableIrqMask(irq);
}

void irqEnable(u32 irq) {
	OS_EnableIrqMask(irq);
}

void readFirmware(u32 address, void * destination, u32 size) {
	FLASH_DirectRead(address, size, destination);
}
void swiDelay(u32 duration) {
	_Ven__SVC_WaitByLoop(duration);
}
