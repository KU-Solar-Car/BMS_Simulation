# CAN-Skeleton

This is the base project structure for any Arduino code that uses the CAN bus network.

## How to use this?

1. Clone the repo.
    1. If you have git in the terminal, run `git clone https://github.com/ku-solar-car/canskeleton.git`.
    2. Otherwise, click the download code button.
2. Edit the `canskeleton.ino` file.

## Can I rename the .ino file?

Only if you rename the folder to have the same name. So `canskeleton.ino` needs to be in the `canskeleton/` folder.

## What are these other files?

The other .cpp and .h files are from a library from the manufacturer. They don't need to be changed. Probably don't change them :)

## How do I send CAN messages?

CAN messages are sent using the `canTx` function. Most of the code is in a block like this:

```c
byte port = 0; // Or 1
long msgId = 0x700; // Choose an ID that is unique. Anything about 0x700 should be good
byte txData[] = {0x0, 0x1}; // Set the data you want to send
byte length = 2; // Set the length of byte array to send (1-8 bytes per frame)

if (canTx(port, msgId, false, txData, length) == CAN_OK) {
    // Do code that runs if message sent successfully
}
```

## How do I receive CAN messages?

```c
byte port = 0; // Or 1
long msgId; // This will hold the array of the CAN frame
bool extendedFormat; // This will tell if the message ID is long
byte rxData[8]; // Set the data you want to send, with the length
byte length = 8; // Set the length of byte array to send (1-8 bytes per frame)

if (canRx(port, &msgId, &extendedFormat, &rxData[0], &length) == CAN_OK) {
    if (msgId == 0x700) { // Substitute whatever ID you are looking for
        // Do stuff with that CAN frame
    }
}
```

