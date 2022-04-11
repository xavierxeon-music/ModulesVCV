#ifndef InterfaceH
#define InterfaceH

using Buffer = float[8];

using CreateFunction = void (*)();
using InitFunction = void (*)(const float&);
using ProcessFunction = void (*)(const Buffer&, Buffer&);
using TerminateFunction = void (*)();

#define CREATE_FUNCTION void create()
#define INIT_FUNCTION void init(const float& sampleRate)
#define PROCESS_FUNCTION void process(const Buffer& input, Buffer& output)
#define TERMINATE_FUNCTION void terminate()

#endif // InterfaceH