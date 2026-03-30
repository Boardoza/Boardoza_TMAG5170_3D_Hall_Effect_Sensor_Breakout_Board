#include "TMAG5170.h"

/**
 * @brief Constructor for the TMAG5170 class.
 * 
 * Initializes the TMAG5170 object by setting the chip select pin and SPI settings.
 * 
 * @param csPin The chip select pin number for the TMAG5170 sensor.
 */
TMAG5170::TMAG5170(uint8_t csPin)
  : _cs(csPin)
  , _settings(10000000, MSBFIRST, SPI_MODE0)
{}

/**
 * @brief Initializes the TMAG5170 sensor.
 * 
 * This function configures the TMAG5170 sensor by setting up the SPI interface and
 * initializing the sensor in active measurement mode.
 */
void TMAG5170::begin() {
  pinMode(_cs, OUTPUT);
  csHigh();
  SPI.begin();               // VSPI: SCK=18, MISO=19, MOSI=23
}

/**
 * @brief Sets the chip select pin to LOW.
 */
void TMAG5170::csLow()  { digitalWrite(_cs, LOW);  }

/**
 * @brief Sets the chip select pin to HIGH.
 */
void TMAG5170::csHigh() { digitalWrite(_cs, HIGH); }

/**
 * @brief Configures a register in the TMAG5170 sensor.
 * 
 * This function sends a configuration command to the TMAG5170 sensor over SPI
 * and waits for the response. It handles the CRC calculation and ensures proper
 * communication with the sensor.
 * 
 * @param rw The read/write flag (READ_FLAG or WRITE_FLAG).
 * @param reg The register address to be configured.
 * @param data The data to be written to the register.
 */
void TMAG5170::regConfig(uint8_t rw, uint8_t reg, uint16_t data) {
  // rw flag + register
  uint8_t tx[4] = {
    uint8_t(rw | reg),        // byte0: RW|ADDR
    uint8_t(data >> 8),       // byte1: DATA[15:8]
    uint8_t(data & 0xFF),     // byte2: DATA[7:0]
    0x00                      // byte3: placeholder for CRC
  };

  // Collect the 28-bit part in a uint32:
  uint32_t frame28 = (uint32_t(tx[0]) << 20)
                   | (uint32_t(tx[1]) << 12)
                   | (uint32_t(tx[2]) << 4);

  // Calculate CRC4
  tx[3] = calculateCRC4(frame28);

  // send / receive
  uint8_t rx[4];
  SPI.beginTransaction(_settings);
    csLow();
      for (int i = 0; i < 4; ++i) rx[i] = SPI.transfer(tx[i]);
    csHigh();
  SPI.endTransaction();
}

/**
 * @brief Reads data from a register in the TMAG5170 sensor.
 * 
 * This function sends a read command to the TMAG5170 sensor over SPI and
 * returns the 16-bit data value read from the specified register.
 * 
 * @param reg The register address to read from.
 * @return The 16-bit data value read from the register.
 */
uint16_t TMAG5170::readRegData(uint8_t reg) {
  uint8_t tx[4] = { uint8_t(READ_FLAG | reg), 0x00, 0x00, 0x00 };
  uint8_t rx[4];

  SPI.beginTransaction(_settings);
  csLow();
  for(int i=0; i<4; i++) rx[i] = SPI.transfer(tx[i]);
  csHigh();
  SPI.endTransaction();

  return (uint16_t(rx[1]) << 8) | rx[2];
}

/**
 * @brief Initializes the TMAG5170 sensor for evaluation mode.
 * 
 * This function configures the TMAG5170 sensor in evaluation mode by setting
 * up the necessary registers and waiting for the sensor to initialize.
 */
void TMAG5170::initForEval() {
  regConfig(WRITE_FLAG, TEST_CONFIG, CRC_DIS_CRCdisabled);
  delay(5);
  // 1) Device configuration
  regConfig(WRITE_FLAG, DEVICE_CONFIG, DeviceStart);
  delay(5);
  // 2) Sensor configuration
  regConfig(WRITE_FLAG, SENSOR_CONFIG,
            ANGLE_EN_XY      |
            SLEEPTIME_1ms    |
            MAG_CH_EN_XYZZYX |
            Z_RANGE_25mT     |
            Y_RANGE_25mT     |
            X_RANGE_25mT);
  delay(5);
  // 3) System configuration
  regConfig(WRITE_FLAG, SYSTEM_CONFIG,
            DIAG_SEL_AllDataPath    |
            TRIGGER_MODE_SPI        |
            DATA_TYPE_32bit         |
            DIAG_EN_AFEdiagnosticsDisabled |
            Z_HLT_EN_ZaxisLimitCheckoff    |
            Y_HLT_EN_YaxisLimitCheckoff    |
            X_HLT_EN_XaxisLimitCheckoff);
    //regConfig(WRITE_FLAG, SYSTEM_CONFIG, 0x02C7);
  delay(5);
  // 4) Test configuration

  // 5) Mag gain configuration
  regConfig(WRITE_FLAG, MAG_GAIN_CONFIG, GAIN_SEL_noAxisSelected);
  delay(5);
  // 6) Finally, DeviceStart is set again to proceed with measurements
  regConfig(WRITE_FLAG, DEVICE_CONFIG, DeviceStart);
  delay(5);
}

/**
 * @brief Reads the X-axis magnetic field value from the TMAG5170 sensor.
 * 
 * This function reads the raw X-axis magnetic field value from the sensor
 * and converts it to milliTesla (mT) using a linear conversion factor.
 * 
 * @return The X-axis magnetic field value in mT.
 */
float TMAG5170::getX() {
  int16_t raw = int16_t(readRegData(X_CH_RESULT));
  return raw * 50.0f  / 32768.0f;
}

/**
 * @brief Reads the Y-axis magnetic field value from the TMAG5170 sensor.
 * 
 * This function reads the raw Y-axis magnetic field value from the sensor
 * and converts it to milliTesla (mT) using a linear conversion factor.
 * 
 * @return The Y-axis magnetic field value in mT.
 */
float TMAG5170::getY() {
  int16_t raw = int16_t(readRegData(Y_CH_RESULT));
  return raw * 25.0f  / 32768.0f;
}

/**
 * @brief Reads the Z-axis magnetic field value from the TMAG5170 sensor.
 * 
 * This function reads the raw Z-axis magnetic field value from the sensor
 * and converts it to milliTesla (mT) using a linear conversion factor.
 * 
 * @return The Z-axis magnetic field value in mT.
 */
float TMAG5170::getZ() {
  int16_t raw = int16_t(readRegData(Z_CH_RESULT));
  return raw * 25.0f  / 32768.0f;
}

/**
 * @brief Reads the temperature value from the TMAG5170 sensor.
 * 
 * This function reads the raw temperature value from the sensor and converts
 * it to degrees Celsius using a linear conversion factor.
 * 
 * @return The temperature value in degrees Celsius.
 */
float TMAG5170::getTemperature() {
  uint16_t t = readRegData(TEMP_RESULT);
  return ECHAR_T_SENS_T0 + ( (float(t) - ECHAR_T_ADC_T0) / ECHAR_T_ADC_RES );
}

/**
 * @brief Reads the angle value from the TMAG5170 sensor.
 * 
 * This function reads the raw angle value from the sensor and converts it to
 * degrees using a linear conversion factor.
 * 
 * @return The angle value in degrees.
 */
float TMAG5170::getAngle() {
  uint16_t a = readRegData(ANGLE_RESULT);
  // upper 12 bits are degrees, lower 4 bits are fraction
  return float(a >> 4); //+ float(a & 0x0F) / 16.0f;
}

/**
 * @brief Calculates the CRC4 value for a given 28-bit frame.
 * 
 * This function calculates the CRC4 value for a given 28-bit frame using a
 * CRC4 algorithm. The CRC4 algorithm is used to ensure data integrity in
 * communication with the TMAG5170 sensor.
 * 
 * @param frame28 The 28-bit frame for which to calculate the CRC4 value.
 * @return The calculated CRC4 value.
 */
uint8_t TMAG5170::calculateCRC4(uint32_t frame28) {
  // frame28: [27:0], here MSB bit27 is the highest.
// Shift left 4 to move to 32-bit, lower 4 bits are zero:
  uint32_t padded = frame28 << 4;
  uint8_t  crc    = 0xF;   // initial value = 4'hf

  // i = 31 … 0
  for (int i = 31; i >= 0; --i) {
    bool inv = ( ((padded >> i) & 0x1) ^ ((crc >> 3) & 0x1) );

    uint8_t b2 = (crc >> 2) & 1;
    uint8_t b1 = (crc >> 1) & 1;
    uint8_t b0 =  crc       & 1;

    // new CRC bits
    uint8_t new3 = b2;
    uint8_t new2 = b1;
    uint8_t new1 = b0 ^ inv;
    uint8_t new0 = inv;

    crc = (new3 << 3)
        | (new2 << 2)
        | (new1 << 1)
        |  new0;
  }
  return crc & 0x0F;
}