#include <stdbool.h>
#include <string.h>

#include <coreinit/time.h>
#include <vpad/input.h>
#include <whb/log_console.h>
#include <whb/log.h>
#include <whb/proc.h>

// Random variables for the game.
int input_count = 0;
int current_color = 0;
bool touch_held_down = false;

void count()
{
    input_count += 1;
    if (input_count == 1)
    {
        // The very first button is pressed, grammar matters.
        WHBLogPrintf("You mashed %d button!", input_count);
        WHBLogPrint("----------------------------------------");
    }
    else
    {
        // Anything that isn't the first button press.
        WHBLogPrintf("You mashed %d buttons!", input_count);
        WHBLogPrint("----------------------------------------");
    }
    if (input_count % 100 == 0)
    {
        // Small vibration every hundred presses.
        uint8_t pattern[15];
        memset(pattern, 0x99, 15);
        VPADControlMotor(VPAD_CHAN_0, pattern, 60);
        // Change the color from red, to blue, etc.
        if (current_color == 0)
        {
            WHBLogConsoleSetColor(0x99000000);
            current_color = 1;
        }
        else if (current_color == 1)
        {
            WHBLogConsoleSetColor(0x00990000);
            current_color = 2;
        }
        else if (current_color == 2)
        {
            WHBLogConsoleSetColor(0x00009900);
            current_color = 3;
        }
        else if (current_color == 3)
        {
            WHBLogConsoleSetColor(0x99000000);
            current_color = 1;
        }
    }
}

int main()
{
    // Initialize everything needed for the game.
    WHBProcInit();
    WHBLogConsoleInit();
    // Set some variables for the Wii U GamePad.
    VPADStatus input;
    VPADReadError error;
    // Print the console header.
    WHBLogConsoleSetColor(0x000000);
    WHBLogPrint("Button Break (v1.0.1)");
    WHBLogPrint("Created by Nightkingale");
    WHBLogPrint("----------------------------------------");
    WHBLogConsoleDraw();

    while (WHBProcIsRunning())
    {
        // Watch the Wii U GamePad for button presses.
        VPADRead(VPAD_CHAN_0, &input, 1, &error);

        if (input.tpNormal.touched != 0)
        {
            // Check if the screen is pressed on.
            if (touch_held_down == false)
            {
                // Change the color from red, to blue, etc.
                touch_held_down = true;
                if (current_color == 0)
                {
                    WHBLogConsoleSetColor(0x99000000);
                    current_color = 1;
                }
                else if (current_color == 1)
                {
                    WHBLogConsoleSetColor(0x00990000);
                    current_color = 2;
                }
                else if (current_color == 2)
                {
                    WHBLogConsoleSetColor(0x00009900);
                    current_color = 3;
                }
                else if (current_color == 3)
                {
                    WHBLogConsoleSetColor(0x00000000);
                    current_color = 0;
                }
            }
        }
        else
        {
            touch_held_down = false;
        }

        if (input.trigger & VPAD_BUTTON_A)
        {
            WHBLogPrint("You pressed the A button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_B)
        {
            WHBLogPrint("You pressed the B button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_X)
        {
            WHBLogPrint("You pressed the X button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_Y)
        {
            WHBLogPrint("You pressed the Y button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_PLUS)
        {
            WHBLogPrint("You pressed the Start button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_MINUS)
        {
            WHBLogPrint("You pressed the Select button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_L)
        {
            WHBLogPrint("You pressed the L button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_R)
        {
            WHBLogPrint("You pressed the R button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_ZL)
        {
            WHBLogPrint("You pressed the ZL button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_ZR)
        {
            WHBLogPrint("You pressed the ZR button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_STICK_L)
        {
            WHBLogPrint("You pressed the Left Control Stick!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_STICK_R)
        {
            WHBLogPrint("You pressed the Right Control Stick!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_UP)
        {
            WHBLogPrint("You pressed the Up D-Pad button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_DOWN)
        {
            WHBLogPrint("You pressed the Down D-Pad button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_LEFT)
        {
            WHBLogPrint("You pressed the Left D-Pad button!");
            count();
        }
        if (input.trigger & VPAD_BUTTON_RIGHT)
        {
            WHBLogPrint("You pressed the Right D-Pad button!");
            count();
        }

        if (input.trigger & VPAD_BUTTON_SYNC)
        {
            // Hidden vibration button.
            uint8_t pattern[15];
            memset(pattern, 0xFF, 15);
            VPADControlMotor(VPAD_CHAN_0, pattern, 120);
        }
        // Draw the text to each screen.
        WHBLogConsoleDraw();
    }
    // Clear everything when the game is exited.
    WHBLogConsoleFree();
    WHBProcShutdown();
    return 0;
}