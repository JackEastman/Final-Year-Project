#include "Speaker.h"
#include "I2SOutput.h"
#include "WAVFileReader.h"

Speaker::Speaker(I2SOutput *i2s_output)
{
    m_i2s_output = i2s_output;
    m_ok = new WAVFileReader("/ok.wav");

    m_ready_ping[0] = new WAVFileReader("/ready_ping.wav");
    m_ready_ping[1] = new WAVFileReader("/ready_ping1.wav");
    m_ready_ping[2] = new WAVFileReader("/ready_ping2.wav");
    m_ready_ping[3] = new WAVFileReader("/ready_ping3.wav");
    m_ready_ping[4] = new WAVFileReader("/ready_ping4.wav");
    m_ready_ping[5] = new WAVFileReader("/ready_ping5.wav");
    m_ready_ping[6] = new WAVFileReader("/ready_ping6.wav");
    m_ready_ping[7] = new WAVFileReader("/ready_ping7.wav");
    m_ready_ping[8] = new WAVFileReader("/ready_ping8.wav");
    /*
    m_ready_ping[9] = new WAVFileReader("/ready_ping9.wav");
    m_ready_ping[10] = new WAVFileReader("/ready_ping10.wav");
    m_ready_ping[11] = new WAVFileReader("/ready_ping11.wav");
    m_ready_ping[12] = new WAVFileReader("/ready_ping12.wav");
    m_ready_ping[13] = new WAVFileReader("/ready_ping13.wav");
    m_ready_ping[14] = new WAVFileReader("/ready_ping14.wav");
    m_ready_ping[15] = new WAVFileReader("/ready_ping15.wav");
    m_ready_ping[16] = new WAVFileReader("/ready_ping16.wav");
    m_ready_ping[17] = new WAVFileReader("/ready_ping17.wav");
    m_ready_ping[18] = new WAVFileReader("/ready_ping18.wav");
    m_ready_ping[19] = new WAVFileReader("/ready_ping19.wav");
    m_ready_ping[20] = new WAVFileReader("/ready_ping20.wav");
    */
}

Speaker::~Speaker()
{
    delete m_ok;
    delete m_ready_ping[0];
    delete m_ready_ping[1];
    delete m_ready_ping[2];
    delete m_ready_ping[3];
    delete m_ready_ping[4];
    delete m_ready_ping[5];
    delete m_ready_ping[6];
    delete m_ready_ping[7];
    delete m_ready_ping[8];
    /*
    delete m_ready_ping[9];
    delete m_ready_ping[10];
    delete m_ready_ping[11];
    delete m_ready_ping[12];
    delete m_ready_ping[13];
    delete m_ready_ping[14];
    delete m_ready_ping[15];
    delete m_ready_ping[16];
    delete m_ready_ping[17];
    delete m_ready_ping[18];
    delete m_ready_ping[19];
    delete m_ready_ping[20];
    */
}

void Speaker::playOK()
{
    //m_ok->reset();
    m_i2s_output->setSampleGenerator(m_ok);
}

void Speaker::playReady()
{
    //int readyping = random(21);
    static int readyping = 0;
    m_i2s_output->setSampleGenerator(m_ready_ping[readyping]);
    if(readyping < 8)
    {
        readyping++;
    }
    else
    {
        readyping = 0;
    }
}