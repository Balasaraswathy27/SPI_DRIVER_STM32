# STM32 Bare-Metal SPI Driver

A register-level SPI driver for the STM32C031C6 microcontroller developed entirely in Embedded C without using STM32 HAL or LL drivers.

The driver provides a configurable SPI interface for communicating with SPI slave devices. The implementation was validated using a chain of four MAX7219 LED matrix drivers.

---

# Features

- Register-level SPI implementation
- Master Mode
- Full Duplex communication
- Configurable Clock Prescaler
- 8 bit Datasize
- Configurable CPOL & CPHA
- MSB / LSB First
- Software Slave Management (SSM)
- Blocking Transmit
- Blocking Receive
- Full Duplex Transfer

---

# Supported MCU

- STM32C031C6

---


# Configuration

The SPI peripheral is configured using the `SPI_Config_t` structure.

```c
SPI_Handle_t SPIHandle;

SPIHandle.pSPIx = SPI1;

SPIHandle.SPIConfig.DeviceMode = SPI_DEVICE_MODE_MASTER;
SPIHandle.SPIConfig.BusConfig  = SPI_BUS_CONFIG_FD;
SPIHandle.SPIConfig.SclkSpeed  = SPI_SCLK_DIV8;
SPIHandle.SPIConfig.DataSize   = SPI_DATASIZE_8BIT;
SPIHandle.SPIConfig.CPOL       = SPI_CPOL_LOW;
SPIHandle.SPIConfig.CPHA       = SPI_CPHA_LOW;
SPIHandle.SPIConfig.BitOrder   = SPI_FIRSTBIT_MSB;
SPIHandle.SPIConfig.SSM        = SPI_SSM_ENABLE;
```

---

# Initialization

```c
RCC_SPIClockControl(SPI1, ENABLE);

SPI_Init(&SPIHandle);

SPI_SSIConfig(SPI1, ENABLE);

SPI_PeripheralControl(SPI1, ENABLE);
```

---

# SPI APIs

## Initialize SPI

```c
SPI_Init(&SPIHandle);
```

Initializes the SPI peripheral according to the configuration stored in `SPI_Config_t`.

---

## Enable/Disable SPI Peripheral

```c
SPI_PeripheralControl(SPI1, ENABLE);

SPI_PeripheralControl(SPI1, DISABLE);
```

---

## Configure Software Slave Management

```c
SPI_SSIConfig(SPI1, ENABLE);
```

Required when Software Slave Management (SSM) is enabled.

---

## Transmit

```c
SPI_Transmit(&SPIHandle,
             TxBuffer,
             Length);
```

Blocking transmit API.

---

## Receive

```c
SPI_Receive(&SPIHandle,
            RxBuffer,
            Length);
```

Blocking receive API.

---

## Full Duplex Transfer

```c
SPI_TransmitReceive(&SPIHandle,
                    TxBuffer,
                    RxBuffer,
                    Length);
```

Simultaneously transmits and receives data.

---

# Validation

The driver was validated by interfacing with a chain of four MAX7219 LED matrix drivers.

The following were verified:

- SPI clock generation
- Chip Select timing
- MOSI data transmission
- SPI frame length
- MSB-first transmission
- Register writes to MAX7219
- Character display across cascaded modules

The SPI communication was further verified using logic analyzer waveforms (VCD).

---

# Example Application

The SPI driver was used to initialize four cascaded MAX7219 devices and display custom characters on a 32×8 LED matrix.

Example:

```
B A L A
```

Each character is rendered from an 8×8 bitmap and transmitted over SPI using the custom driver.

---

# Future Improvements

- Interrupt-based SPI
- DMA support
- Non-blocking APIs
- Timeout support
- Generic SPI device layer

---

## License

This project is shared for learning and demonstration purposes.
