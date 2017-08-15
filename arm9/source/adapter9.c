/*
adapter9.c -- bridge dswifi with nitrosdk
adapter9.c is licenced under the MIT open source licence (same as dswifi):

Copyright (C) 2017 enler (enler2011@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

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
	*(VoidFn*)(0x27E0018 + 0x28) = handler;//is some case (for example, nitrosdk ver <= 4.0), use 0x27E0000 instead
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