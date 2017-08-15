/*
adapter9.h -- bridge dswifi with nitrosdk
adapter9.h is licenced under the MIT open source licence (same as dswifi):

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

typedef void (* VoidFn)(void);
typedef void (*FifoAddressHandlerFunc)(void * address, void * userdata);
typedef void (*FifoValue32HandlerFunc)(u32 value32, void * userdata);

bool fifoSendValue32(int channel, u32 value32);
bool fifoSendAddress(int channel, void *address);
bool fifoSetValue32Handler(int channel, FifoValue32HandlerFunc newhandler, void * userdata);
void irqEnable(u32 irq);
void irqSet(u32 irq, VoidFn handler);
void *memUncached(void *address);
int *__errno();
void swiWaitForVBlank();

//PXI

typedef void (*PXIFifoCallback) (int tag, u32 data, bool err);
int PXI_SendWordByFifo(int fifotag, u32 data, bool err);
void PXI_SetFifoRecvCallback(int fifotag, PXIFifoCallback callback);

//OS
typedef u32 OSIrqMask;
typedef void (*OSIrqFunction) (void);

OSIrqMask OS_EnableIrqMask(OSIrqMask intr);
void OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function);
void OS_Sleep(u32 msec);