#include <Arduino.h>
#include "CommandProcessor.h"
#include "Speaker.h"

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

CommandProcessor::CommandProcessor(Speaker *speaker)
{
    m_speaker = speaker;
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
    printf("EASTMAN: in %s line %d jump here\n", __FUNCTION__, __LINE__);
    xTaskCreate(commandQueueProcessorTask, "Command Queue Processor", 1024, this, 1, &command_queue_task_handle);
    printf("EASTMAN: in %s line %d jump here\n", __FUNCTION__, __LINE__);
    //uint32_t free_ram = esp_get_free_heap_size();
    //Serial.printf("Free ram after playing notification %d\n", free_ram);
}

void CommandProcessor::processCommand(uint16_t commandIndex)
{
    //digitalWrite(GPIO_NUM_2, HIGH);
    switch (commandIndex)
    {
    case 0: // ON
        digitalWrite(GPIO_NUM_21, LOW);
        //vTaskDelay(500 / portTICK_PERIOD_MS);
        m_speaker->playOK();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //delete m_speaker;
        break;
    case 1: // OFF
        digitalWrite(GPIO_NUM_21, HIGH);
        //vTaskDelay(500 / portTICK_PERIOD_MS);
        m_speaker->playReady();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //delete m_speaker;
        break;
    }
    //digitalWrite(GPIO_NUM_2, LOW);
}

void CommandProcessor::queueCommand(uint16_t commandIndex, float best_score, uint8_t numCommand)
{
    // unsigned long now = millis();
    if (commandIndex != numCommand && commandIndex != -1)
    {
        Serial.printf("***** %ld Detected command %s\n", millis(), words[commandIndex]);
        if (xQueueSendToBack(m_command_queue_handle, &commandIndex, 0) != pdTRUE)
        {
            Serial.println("No more space for command");
        }
    }
}
