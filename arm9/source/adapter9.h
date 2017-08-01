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