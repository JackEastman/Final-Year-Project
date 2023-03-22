#ifndef _intent_processor_h_
#define _intent_processor_h_

#include <list>

class I2SOutput;
class Speaker;
class CommandProcessor
{
private:
    QueueHandle_t m_command_queue_handle;
    void processCommand(uint16_t commandIndex);
    Speaker *m_speaker;

public:
    CommandProcessor(Speaker *speaker);
    void queueCommand(uint16_t commandIndex, float score, uint8_t numOfCommand);
    friend void commandQueueProcessorTask(void *param);
};

#endif
