typedef u32 OSIrqMask;

typedef void (* VoidFn)(void);
typedef void (*FifoAddressHandlerFunc)(void * address, void * userdata);
typedef void (*FifoValue32HandlerFunc)(u32 value32, void * userdata);

typedef void (*PXIFifoCallback) (int tag, u32 data, bool err);
typedef void (*OSIrqFunction) (void);

bool fifoSendValue32(int channel, u32 value32);
bool fifoSetValue32Handler(int channel, FifoValue32HandlerFunc newhandler, void * userdata);
bool fifoSetAddressHandler(int channel, FifoAddressHandlerFunc newhandler, void * userdata);
void irqDisable(u32 irq);
void irqEnable(u32 irq);
void irqSet(u32 irq, VoidFn handler);
void readFirmware(u32 address, void * destination, u32 size);
void swiDelay(u32 duration);

//link with nitro sdk
int     PXI_SendWordByFifo(int fifotag, u32 data, bool err);
void    PXI_SetFifoRecvCallback(int fifotag, PXIFifoCallback callback);
OSIrqMask OS_DisableIrqMask(OSIrqMask intr);
OSIrqMask OS_EnableIrqMask(OSIrqMask intr);
void    OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function);
void FLASH_DirectRead(u32 address, u32 size, void * destination);
void _Ven__SVC_WaitByLoop(u32 duration);