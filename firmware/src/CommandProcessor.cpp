#include <Arduino.h>
#include "CommandProcessor.h"

const char *words[] = {
    "ON",
    "OFF",
    "_nonsense",
};

void commandQueueProcessorTask(void *param)
{
    CommandProcessor *commandProcessor = (CommandProcessor *)param;
    while (true)
    {
        uint16_t commandIndex = 0;
        if (xQueueReceive(commandProcessor->m_command_queue_handle, &commandIndex, portMAX_DELAY) == pdTRUE)
        {
            commandProcessor->processCommand(commandIndex);
        }
    }
}

int calcDuty(int ms)
{
    // 50Hz = 20ms period
    return (65536 * ms) / 20000;
}

const int leftForward = 1600;
const int leftBackward = 1400;
const int leftStop = 1500;
const int rightBackward = 1600;
const int rightForward = 1445;
const int rightStop = 1500;

void CommandProcessor::processCommand(uint16_t commandIndex)
{
    //digitalWrite(GPIO_NUM_2, HIGH);
    switch (commandIndex)
    {
    case 0: // ON
        digitalWrite(GPIO_NUM_21, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        break;
    case 1: // OFF
        digitalWrite(GPIO_NUM_21, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        break;
    }
    //digitalWrite(GPIO_NUM_2, LOW);
}

CommandProcessor::CommandProcessor()
{
    pinMode(GPIO_NUM_2, OUTPUT);
    pinMode(GPIO_NUM_21, OUTPUT);

    // allow up to 5 commands to be in flight at once
    m_command_queue_handle = xQueueCreate(5, sizeof(uint16_t));
    if (!m_command_queue_handle)
    {
        Serial.println("Failed to create command queue");
    }
    // kick off the command processor task
    TaskHandle_t command_queue_task_handle;
    xTaskCreate(commandQueueProcessorTask, "Command Queue Processor", 1024, this, 1, &command_queue_task_handle);
}

void CommandProcessor::queueCommand(uint16_t commandIndex, float best_score)
{
    // unsigned long now = millis();
    if (commandIndex != 3 && commandIndex != -1)
    {
        Serial.printf("***** %ld Detected command %s(%f)\n", millis(), words[commandIndex], best_score);
        if (xQueueSendToBack(m_command_queue_handle, &commandIndex, 0) != pdTRUE)
        {
            Serial.println("No more space for command");
        }
    }
}
