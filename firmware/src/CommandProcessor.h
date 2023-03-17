#ifndef _command_processor_h_
#define _command_processor_h_

#include <list>
class Speaker;

class CommandProcessor
{
private:
    QueueHandle_t m_command_queue_handle;
    Speaker m_speaker;
    void processCommand(uint16_t commandIndex);

public:
    CommandProcessor(Speaker *speaker);
    void queueCommand(uint16_t commandIndex, float score, uint8_t numOfCommand);
    friend void commandQueueProcessorTask(void *param);
};

#endif
