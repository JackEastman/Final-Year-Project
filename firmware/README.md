# Final-year-project Firmware

This folder contains the firmware for the Final-year-project of Le Truong Vu 20181849.

I am using Platform.io to build the firmware.

To understand the code the best place to start is `src/main.cpp`. This creates our `CommandDetector` and `CommandProcessor` objects and also creates a task to service the command detector as audio samples come in.

From there you can look at `src/CommandDetector.cpp` and `src/CommandProcessor.cpp`.

The code should be well commented and hopefully easy to understand.