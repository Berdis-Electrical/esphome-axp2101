#ifndef __AXP2101_H__
#define __AXP2101_H__

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

#define XPOWERS_CHIP_AXP2101
#include "XPowersLib.h"

namespace esphome {
namespace axp2101 {

enum AXP2101Model {
  AXP2101_TWATCHS3,
};

#define SLEEP_MSEC(us) (((uint64_t)us) * 1000L)
#define SLEEP_SEC(us)  (((uint64_t)us) * 1000000L)
#define SLEEP_MIN(us)  (((uint64_t)us) * 60L * 1000000L)
#define SLEEP_HR(us)   (((uint64_t)us) * 60L * 60L * 1000000L)

#define CURRENT_100MA  (0b0000)
#define CURRENT_190MA  (0b0001)
#define CURRENT_280MA  (0b0010)
#define CURRENT_360MA  (0b0011)
#define CURRENT_450MA  (0b0100)
#define CURRENT_550MA  (0b0101)
#define CURRENT_630MA  (0b0110)
#define CURRENT_700MA  (0b0111)


class AXP2101Component : public PollingComponent, public i2c::I2CDevice {
public:
  void set_batteryvoltage_sensor(sensor::Sensor *batteryvoltage_sensor) { batteryvoltage_sensor_ = batteryvoltage_sensor; }
  void set_batterylevel_sensor(sensor::Sensor *batterylevel_sensor) { batterylevel_sensor_ = batterylevel_sensor; }
  void set_batterycharging_bsensor(binary_sensor::BinarySensor *batterycharging_bsensor) { batterycharging_bsensor_ = batterycharging_bsensor; }
  void set_brightness(float brightness) { brightness_ = brightness; }
  void set_model(AXP2101Model model) { this->model_ = model; }

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

private:
    static std::string GetStartupReason();

protected:
    sensor::Sensor *batteryvoltage_sensor_;
    sensor::Sensor *batterylevel_sensor_;
    binary_sensor::BinarySensor *batterycharging_bsensor_;
    float brightness_{1.0f};
    float curr_brightness_{-1.0f};
    AXP2101Model model_;

    /** M5Stack Core2 Values
     * LDO2: ILI9342C PWR (Display)
     * LD03: Vibration Motor
     */

    void  UpdateBrightness();
    bool  GetBatState();
    uint8_t  GetBatData();

    void  EnableCoulombcounter(void);
    void  DisableCoulombcounter(void);
    void  StopCoulombcounter(void);
    void  ClearCoulombcounter(void);
    uint32_t GetCoulombchargeData(void);
    uint32_t GetCoulombdischargeData(void);
    float GetCoulombData(void);

    uint16_t GetVbatData(void) __attribute__((deprecated));
    uint16_t GetIchargeData(void) __attribute__((deprecated));
    uint16_t GetIdischargeData(void) __attribute__((deprecated));
    uint16_t GetTempData(void) __attribute__((deprecated));
    uint32_t GetPowerbatData(void) __attribute__((deprecated));
    uint16_t GetVinData(void) __attribute__((deprecated));
    uint16_t GetIinData(void) __attribute__((deprecated));
    uint16_t GetVusbinData(void) __attribute__((deprecated));
    uint16_t GetIusbinData(void) __attribute__((deprecated));
    uint16_t GetVapsData(void) __attribute__((deprecated));
    uint8_t GetBtnPress(void);

      // -- sleep
    void SetSleep(void);
    void DeepSleep(uint64_t time_in_us = 0);
    void LightSleep(uint64_t time_in_us = 0);

    // void SetChargeVoltage( uint8_t );
    void  SetChargeCurrent( uint8_t );
    float GetBatCurrent();
    float GetVinVoltage();
    float GetVinCurrent();
    float GetVBusVoltage();
    float GetVBusCurrent();
    float GetTempInAXP2101();
    float GetBatPower();
    float GetBatChargeCurrent();
    float GetAPSVoltage();
    float GetBatCoulombInput();
    float GetBatCoulombOut();
    uint8_t GetWarningLevel(void);
    void SetCoulombClear();
    void SetLDO2( bool State );
    void SetLDO3( bool State );
    void SetAdcState(bool State);

    void PowerOff();


    void Write1Byte( uint8_t Addr ,  uint8_t Data );
    uint8_t Read8bit( uint8_t Addr );
    uint16_t Read12Bit( uint8_t Addr);
    uint16_t Read13Bit( uint8_t Addr);
    uint16_t Read16bit( uint8_t Addr );
    uint32_t Read24bit( uint8_t Addr );
    uint32_t Read32bit( uint8_t Addr );
    void ReadBuff( uint8_t Addr , uint8_t Size , uint8_t *Buff );
};

}
}

#endif
