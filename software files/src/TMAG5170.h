#ifndef TMAG5170_H
#define TMAG5170_H

#include <Arduino.h>
#include <SPI.h>

// ————————————————————————
// SPI Flags
// ————————————————————————
#define READ_FLAG     0x80
#define WRITE_FLAG    0x00

// ————————————————————————
// TMAG5170 Register Addresses
// ————————————————————————
#define DEVICE_CONFIG    0x00
#define SENSOR_CONFIG    0x01
#define SYSTEM_CONFIG    0x02
#define TEST_CONFIG      0x0F
#define MAG_GAIN_CONFIG  0x11

#define X_CH_RESULT      0x09
#define Y_CH_RESULT      0x0A
#define Z_CH_RESULT      0x0B
#define TEMP_RESULT      0x0C
#define ANGLE_RESULT     0x13

// ————————————————————————
// DEVICE_CONFIG Bit Definitions
// ————————————————————————
#define CONV_AVG_16x   0x4000
#define MAG_TEMPCO_0pd 0x0000
#define OPERATING_MODE_ActiveMeasureMode  0x0020
#define T_CH_EN_TempChannelEnabled        0x0008
#define T_RATE_sameAsOtherSensors         0x0004
#define T_HLT_EN_tempLimitCheckOff        0x0002
#define TEMP_COMP_EN_TempCompensationDisabled 0x0001

// Writing this once puts the device into "operating mode"
#define DeviceStart  (CONV_AVG_16x | MAG_TEMPCO_0pd \
                     | OPERATING_MODE_ActiveMeasureMode \
                     | T_CH_EN_TempChannelEnabled \
                     | T_RATE_sameAsOtherSensors \
                     | T_HLT_EN_tempLimitCheckOff \
                     | TEMP_COMP_EN_TempCompensationDisabled)

// ————————————————————————
// SENSOR_CONFIG Bit Definitions
// ————————————————————————
#define ANGLE_EN_XY        0x4000
#define SLEEPTIME_1ms      0x0100
#define MAG_CH_EN_XYZZYX   0x01C0
#define X_RANGE_25mT       0x0001
#define Y_RANGE_25mT       0x0004
#define Z_RANGE_25mT       0x0010

// ————————————————————————
// SYSTEM_CONFIG Bit Definitions
// ————————————————————————
#define DIAG_SEL_AllDataPath            0x0000
#define TRIGGER_MODE_SPI                0x0000
#define DATA_TYPE_32bit                 0x0000
#define DIAG_EN_AFEdiagnosticsDisabled  0x0000
#define Z_HLT_EN_ZaxisLimitCheckoff     0x0004
#define Y_HLT_EN_YaxisLimitCheckoff     0x0002
#define X_HLT_EN_XaxisLimitCheckoff     0x0001

// ————————————————————————
// TEST_CONFIG & MAG_GAIN_CONFIG
// ————————————————————————
#define CRC_DIS_CRCdisabled     0x0004
#define GAIN_SEL_noAxisSelected 0x0000

// ————————————————————————
// Temperature Conversion Constants
// ————————————————————————
#define ECHAR_T_ADC_T0   17522.0f
#define ECHAR_T_SENS_T0  25.0f
#define ECHAR_T_ADC_RES  60.0f

class TMAG5170 {
public:
  TMAG5170(uint8_t csPin);

  /// Initializes GPIO, SPI
  void begin();

  /// Register array ported from TI eval code
  void initForEval();

  // Measurement APIs
  float getX();
  float getY();
  float getZ();
  float getTemperature();
  float getAngle();

  /// Reads 16-bit register
  uint16_t readRegData(uint8_t reg);
private:
  uint8_t      _cs;
  SPISettings  _settings;

  void csLow();
  void csHigh();

  /// Writes to 16-bit register and gets response
  void regConfig(uint8_t rw, uint8_t reg, uint16_t data);
  uint8_t calculateCRC4(uint32_t frame28);
};

#endif
