#pragma once
#include "ModelingFramework.h"
#include <queue>
#include <tuple>

#define MEMORY_SIZE (0x75)
#define MAX_FIFO_SIZE (4096)

class LSM6DSL : public ExternalPeripheral {
  public:
    LSM6DSL();
    void Main() override;
    void Stop() override;

  private:

    typedef enum {
        FIFO_MODE_BYPASS         = 0x00, // Bypass mode. Reset mode, fifo is disables
        FIFO_MODE_FIFO 		     = 0x01, //FIFO mode. Stops collecting data when FIFO is full.
        FIFO_MODE_STREAM 		 = 0x02, // Reserved
        FIFO_MODE_STF 	         = 0x03, // Continuous mode until trigger is deasserted, then FIFO mode.
        FIFO_MODE_BTS 		     = 0x04, // Bypass mode until trigger is deasserted, then Continuous mode
        FIFO_MODE_DYN_STREAM 	 = 0x05, // Reserved
        FIFO_MODE_DYN_STREAM_2   = 0x06, // Continuous mode. If the FIFO is full, the new sample overwrites the older one
        FIFO_MODE_BTF 		     = 0x07,  // Reserved
    } fifo_mode_t;

    typedef enum {
        DISABLE,
        ODR_12_5_HZ,
        ODR_26_HZ,
        ODR_52_HZ,
        ODR_104_HZ,
        ODR_208_HZ,
        ODR_416_HZ,
        ODR_833_HZ,
        ODR_1_66_KHZ,
        ODR_3_33_KHZ,
        ODR_6_66_KHZ,
    } fifo_oder_t;

    typedef enum {
        READ_ONLY,
        WRITE_ONLY,
        READ_WRITE,
        NONE_READ_WRITE
    } read_write_t;

    void WriteToFifoCntrl5(uint8_t value);
    void LoadDataIntoOutputRegs();
    void ClearFifo(std::queue<uint16_t> &fifo);
    bool IsIfIncSet();
    bool IsBduBitSet();
    void WriteDataToMaster(uint32_t start_reg);
    void ReadDataFromMaster(uint32_t start_reg_address);
    void MemReset();

    fifo_mode_t mode_;
    std::queue<uint16_t> fifo_; // data set is reserved for gyroscope data
    iSpiSlaveV1* spi_slave_ {};
    uint8_t memory_[MEMORY_SIZE] {};
    bool out_l_was_read;
    bool out_h_was_read;
    int sa0_pin_number_ {};
    int int1_pin_number_ {};
    int int2_pin_number_ {};
    bool should_stop_;
};

extern "C" ExternalPeripheral *PeripheralFactory() {
    return new LSM6DSL();
}
