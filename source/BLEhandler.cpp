/* Handler for the Bluetooth Low Energy module
*/


#include "BLEhandler.h"
#include <bluefruit.h>
#include "StateMachine.h"
#include "packetParser.h"

// OTA DFU service
BLEDfu bledfu;

// Uart over BLE service
BLEUart bleuart;

// Packet buffer
extern uint8_t packetbuffer[];

// Directional mappings
#define FWD_BTN 5
#define BACK_BTN 6
#define LEFT_BTN 7
#define RIGHT_BTN 8


void BLEinit(void)
{
    Bluefruit.begin();
    Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
    Bluefruit.setName("L1zzy");
    
    // To be consistent OTA DFU should be added first if it exists
    bledfu.begin();
    
    // Configure and start the BLE Uart service
    bleuart.begin();

    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    
    // Include the BLE UART (AKA 'NUS') 128-bit UUID
    Bluefruit.Advertising.addService(bleuart);
    
    // Secondary Scan Response packet (optional)
    // Since there is no room for 'Name' in Advertising packet
    Bluefruit.ScanResponse.addName();
    
    /* Start Advertising
    * - Enable auto advertising if disconnected
    * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
    * - Timeout for fast mode is 30 seconds
    * - Start(timeout) with timeout = 0 will advertise forever (until connected)
    * 
    * For recommended advertising interval
    * https://developer.apple.com/library/content/qa/qa1931/_index.html   
    */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}
    


// BLE task
void BLEtask(void)
{
    // Wait for new data to arrive
    uint8_t len = readPacket(&bleuart, 500);
    if (len == 0) return;
    
    // If a button press is recieved
    // Butons from BLE override any previous commands
    if (packetbuffer[1] == 'B') {

        // Lock out the wander task so that it doesn't conflict with direct control
        SetLock(10);

        uint8_t btnnum = packetbuffer[2] - '0';
        boolean pressed = packetbuffer[3] - '0';

        // Set the state based directly based off the input
        // If pressed set the state to pressed
        if (pressed)
        {
            switch (btnnum)
            {
            case FWD_BTN:
                SetCurrentState(FORWARDS);
                break;

            case BACK_BTN:
                SetCurrentState(BACKWARDS);
                break;

            case LEFT_BTN:
                SetCurrentState(TURN_LEFT);
                break;

            case RIGHT_BTN:
                SetCurrentState(TURN_RIGHT);
                break;
            
            default:
                break;
            }
        }
        // If the button is released, return control to master
        else
        {
            SetCurrentState(SLEEP);
        }
    }
}
