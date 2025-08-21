# STM32F429 DMA UART Receiver Project

## Overview

This project implements a DMA-based UART receiver with idle line detection on the STM32F429 microcontroller. It's designed to efficiently handle continuous data streams (such as GPS NMEA data) by using DMA transfers and idle line interrupts to minimize CPU overhead while ensuring reliable data reception.

## Features

- **DMA-based UART Reception**: Uses DMA2 Stream 2 for efficient data transfer
- **Idle Line Detection**: Automatically detects when transmission stops
- **Circular Buffer Management**: Handles continuous data streams with proper buffer management
- **Configurable Buffer Size**: 256-byte receive buffer with 4KB final buffer
- **Non-blocking Operation**: Minimal CPU involvement during data reception
- **Timer-based Processing**: Built-in timing mechanism for data processing

## Hardware Requirements

- STM32F429 Discovery Board or equivalent
- Serial communication device (GPS module, PC terminal, etc.)
- Connections:
  - USART1 TX: PA9
  - USART1 RX: PA10
  - Ground connection

## Software Requirements

- STM32CubeIDE or compatible development environment
- STM32F4xx HAL Library
- Custom DMAIdleReceiver library (included in project)

## Project Structure

```
├── main.c                    # Main application file
├── DMAIdleReceiver/          # Custom DMA UART library
├── Drivers/                  # STM32 HAL drivers
└── Inc/                      # Header files
```

## Configuration

### UART Settings
- **Baud Rate**: 115200
- **Word Length**: 8 bits
- **Stop Bits**: 1
- **Parity**: None
- **Flow Control**: None

### System Clock
- **HSE**: 8 MHz external crystal
- **System Clock**: 72 MHz (PLL configuration)
- **Voltage Scale**: Scale 3 for power optimization

### Buffer Configuration
```c
#define RXSIZE 256              // DMA receive buffer size
uint8_t RxData[RXSIZE];         // DMA receive buffer
uint8_t FinalBuf[4096];         // Final processing buffer
```

## Key Functions

### Main Reception Callback
```c
void HAL_DMAIdleRecieverEx_RxEventCallback(DMAIdleReciever_HandleTypeDef *hDMAIdleReciever, uint16_t Size)
```
This callback is triggered when:
- DMA buffer is full (256 bytes received)
- UART idle line is detected (end of transmission)

### Buffer Management
The system uses a two-buffer approach:
1. **RxData**: DMA circular buffer for incoming data
2. **FinalBuf**: Accumulation buffer for complete messages

## Usage

### Basic Initialization
```c
// Initialize peripherals
MX_GPIO_Init();
MX_DMA_Init();
MX_USART1_DMAIdleReciever_Init();

// Start reception
HAL_DMAIdleRecieverEx_ReceiveToIdle_DMA(&hDMAIdleReciever1, RxData, RXSIZE);
```

### Sending Data
```c
HAL_DMAIdleReciever_Transmit(&hDMAIdleReciever1, (uint8_t*)"Hello\r\n", 7, 1000);
```

## Implementation Details

### DMA Configuration
- **Controller**: DMA2
- **Stream**: Stream 2
- **Channel**: Channel 4 (USART1_RX)
- **Priority**: Normal
- **Mode**: Circular

### Interrupt Handling
- DMA2_Stream2_IRQn is configured with priority 0
- USART1 idle line detection enabled
- Callbacks handle both complete and partial transfers

### Buffer Logic
1. Data arrives via DMA into `RxData`
2. On idle or buffer full, data is copied to `FinalBuf`
3. Indexes track current positions in both buffers
4. Timer mechanism allows for message processing delays

## Troubleshooting

### Common Issues

1. **No Data Received**
   - Check UART pin connections (PA9/PA10 for USART1)
   - Verify baud rate matches sender
   - Ensure DMA and USART clocks are enabled

2. **Data Corruption**
   - Check system clock configuration
   - Verify DMA stream/channel assignment
   - Ensure buffer sizes are adequate

3. **Missing Characters**
   - Increase buffer sizes if needed
   - Check for proper idle line detection
   - Verify callback processing time

### Debug Tips
- Use the transmission function to verify UART functionality
- Monitor `count` variable to confirm callback execution
- Check `indx1`, `indx2`, and `rxcplt` for buffer state

## Example Applications

This code is ideal for:
- GPS/GNSS data logging
- Sensor data acquisition
- Serial protocol implementations
- IoT device communication

## Development Notes

- The project uses a custom DMAIdleReceiver library that extends standard HAL functionality
- Timer-based processing allows for efficient message handling
- Circular buffer design prevents data loss during continuous reception
- Code includes placeholder for message processing logic (commented out)

## Contributing

When modifying this code:
1. Maintain buffer size relationships
2. Preserve DMA configuration settings
3. Test with various data rates and message sizes
4. Document any changes to callback behavior

## License

This project is provided under the STMicroelectronics license terms. See LICENSE file for details.

---

**Note**: This implementation assumes the custom DMAIdleReceiver library is available. Ensure all required library files are included in your project build path.