#ifndef __ADNS9200_H
#define __ADNS9200_H	 
#include "sys.h"

#define ADNS9200_CS			PBout(12) //ADNS9200????D?o?
// Registers
#define REG_Product_ID                           0x00
#define REG_Revision_ID                          0x01
#define REG_Motion                               0x02
#define REG_Delta_X_L                            0x03
#define REG_Delta_X_H                            0x04
#define REG_Delta_Y_L                            0x05
#define REG_Delta_Y_H                            0x06
#define REG_SQUAL                                0x07
#define REG_Pixel_Sum                            0x08
#define REG_Maximum_Pixel                        0x09
#define REG_Minimum_Pixel                        0x0a
#define REG_Shutter_Lower                        0x0b
#define REG_Shutter_Upper                        0x0c
#define REG_Frame_Period_Lower                   0x0d
#define REG_Frame_Period_Upper                   0x0e
#define REG_Configuration_I                      0x0f
#define REG_Configuration_II                     0x10
#define REG_Frame_Capture                        0x12
#define REG_SROM_Enable                          0x13
#define REG_Run_Downshift                        0x14
#define REG_Rest1_Rate                           0x15
#define REG_Rest1_Downshift                      0x16
#define REG_Rest2_Rate                           0x17
#define REG_Rest2_Downshift                      0x18
#define REG_Rest3_Rate                           0x19
#define REG_Frame_Period_Max_Bound_Lower         0x1a
#define REG_Frame_Period_Max_Bound_Upper         0x1b
#define REG_Frame_Period_Min_Bound_Lower         0x1c
#define REG_Frame_Period_Min_Bound_Upper         0x1d
#define REG_Shutter_Max_Bound_Lower              0x1e
#define REG_Shutter_Max_Bound_Upper              0x1f
#define REG_LASER_CTRL0                          0x20
#define REG_Observation                          0x24
#define REG_Data_Out_Lower                       0x25
#define REG_Data_Out_Upper                       0x26
#define REG_SROM_ID                              0x2a
#define REG_Lift_Detection_Thr                   0x2e
#define REG_Configuration_V                      0x2f
#define REG_Configuration_IV                     0x39
#define REG_Power_Up_Reset                       0x3a
#define REG_Shutdown                             0x3b
#define REG_Inverse_Product_ID                   0x3f
#define REG_Motion_Burst                         0x50
#define REG_SROM_Load_Burst                      0x62
#define REG_Pixel_Burst                          0x64	


// Constant
//------------------------------------------------------------------------------------
#define DEFAULT_CFG0		0x4A
#define DEFAULT_CFG1		0xB5


//------------------------------------------------------------------------------------
// Register
//------------------------------------------------------------------------------------
// Motion Register Individual Bit Field Settings
#define ADNS9800_MOTION_MOT			0x80
#define ADNS9800_MOTION_FAULT		0x40
#define ADNS9800_MOTION_LPVALID		0x20
#define ADNS9800_MOTION_OVF			0x10
#define ADNS9800_MOTION_PIXFIRST	0x01

// Configuration I Register Settings
#define ADNS9800_RES100CPI			0x01		
#define ADNS9800_RES200CPI			0x02
#define ADNS9800_RES300CPI			0x03
#define ADNS9800_RES400CPI			0x04
#define ADNS9800_RES500CPI	  		0x05
#define ADNS9800_RES600CPI			0x06	
#define ADNS9800_RES700CPI			0x07
#define ADNS9800_RES800CPI			0x08
#define ADNS9800_RES900CPI			0x09
#define ADNS9800_RES1000CPI			0x0A
#define ADNS9800_RES1100CPI			0x0B
#define ADNS9800_RES1200CPI			0x0C
#define ADNS9800_RES1300CPI			0x0D
#define ADNS9800_RES1400CPI			0x0E
#define ADNS9800_RES1500CPI			0x0F
#define ADNS9800_RES1600CPI			0x10
#define ADNS9800_RES1700CPI			0x11
#define ADNS9800_RES1800CPI			0x12
#define ADNS9800_RES1900CPI			0x13
#define ADNS9800_RES2000CPI			0x14
#define ADNS9800_RES2100CPI			0x15
#define ADNS9800_RES2200CPI			0x16
#define ADNS9800_RES2300CPI			0x17
#define ADNS9800_RES2400CPI			0x18
#define ADNS9800_RES2500CPI			0x19	
#define ADNS9800_RES2600CPI			0x1A
#define ADNS9800_RES2700CPI			0x1B
#define ADNS9800_RES2800CPI			0x1C
#define ADNS9800_RES2900CPI			0x1D
#define ADNS9800_RES3000CPI			0x1E
#define ADNS9800_RES3100CPI			0x1F	
#define ADNS9800_RES3200CPI			0x20
#define ADNS9800_RES3300CPI			0x21
#define ADNS9800_RES3400CPI			0x22
#define ADNS9800_RES3500CPI			0x23
#define ADNS9800_RES3600CPI			0x24	
#define ADNS9800_RES3700CPI			0x25
#define ADNS9800_RES3800CPI			0x26
#define ADNS9800_RES3900CPI			0x27
#define ADNS9800_RES4000CPI			0x28
#define ADNS9800_RES4100CPI			0x29
#define ADNS9800_RES4200CPI			0x2A

// Configuration II Bits Register Individual Bit Field Settings
#define ADNS9800_FREST1				0x80
#define ADNS9800_FREST0				0x40
#define ADNS9800_REST_EN			0x20
#define ADNS9800_NAGC				0x10
#define ADNS9800_FIXED_FR			0x08
#define ADNS9800_RPT_MOD			0x04
#define ADNS9800_SYS_TEST			0x01

// Laser CTRL0 Bits Register Individual Bit Field Settings
#define ADNS9800_RANGE				0x80
#define ADNS9800_FORCE_DISABLED		0x01

// Laser CTRL1 Bits Register Individual Bit Field Settings
#define ADNS9800_RANGE_C			0x80

// Configuration IV Bits Register Individual Bit Field Settings
#define ADNS9800_SROM_SIZE_1_5K		0x00
#define ADNS9800_SROM_SIZE_3_0K		0x02

// Power Up Reset Register Settings
#define ADNS9800_POWER_UP_RESET		0x5A


// ADNS9800 Register Addresses
#define ADNS9800_PRODUCTID_ADDR							0x00
#define ADNS9800_REVISIONID_ADDR						0x01
#define ADNS9800_MOTION_ADDR							0x02
#define ADNS9800_DELTAX_L_ADDR							0x03
#define ADNS9800_DELTAX_H_ADDR							0x04
#define ADNS9800_DELTAY_L_ADDR							0x05
#define ADNS9800_DELTAY_H_ADDR							0x06
#define ADNS9800_SQUAL_ADDR								0x07
#define ADNS9800_PIXEL_SUM_ADDR							0x08
#define ADNS9800_MAXIMUM_PIXEL_ADDR						0x09
#define ADNS9800_MINIMUM_PIXEL_ADDR						0x0A
#define ADNS9800_SHUTTER_LOWER_ADDR						0x0B
#define ADNS9800_SHUTTER_UPPER_ADDR						0x0C
#define ADNS9800_FRAME_PERIOD_LOWER_ADDR				0x0D
#define ADNS9800_FRAME_PERIOD_UPPER_ADDR				0x0E
#define ADNS9800_CONFIGURATION_I_ADDR					0x0F
#define ADNS9800_CONFIGURATION_II_ADDR					0x10
#define ADNS9800_FRAME_CAPTURE_ADDR						0x12
#define ADNS9800_SROM_ENABLE_ADDR						0x13
#define ADNS9800_RUN_DOWNSHIFT_ADDR						0x14
#define ADNS9800_REST1_RATE_ADDR						0x15
#define ADNS9800_REST1_DOWNSHIFT_ADDR					0x16
#define ADNS9800_REST2_RATE_ADDR						0x17
#define ADNS9800_REST2_DOWNSHIFT_ADDR					0x18
#define ADNS9800_REST3_RATE_ADDR						0x19
#define ADNS9800_FRAME_PERIOD_MAX_BOUND_LOWER_ADDR		0x1A
#define ADNS9800_FRAME_PERIOD_MAX_BOUND_UPPER_ADDR		0x1B
#define ADNS9800_FRAME_PERIOD_MIN_BOUND_LOWER_ADDR		0x1C
#define ADNS9800_FRAME_PERIOD_MIN_BOUND_UPPER_ADDR		0x1D
#define ADNS9800_SHUTTER_MAX_BOUND_LOWER_ADDR 			0x1E
#define ADNS9800_SHUTTER_MAX_BOUND_UPPER_ADDR 			0x1F
#define ADNS9800_LASER_CTRL0_ADDR						0x20
#define ADNS9800_LASER_CTRL1_ADDR						0x21
#define ADNS9800_LP_CFG0_ADDR							0x22
#define ADNS9800_LP_CFG1_ADDR							0x23
#define ADNS9800_OBSERVATION_ADDR						0x24
#define ADNS9800_DATA_OUT_LOWER_ADDR					0x25
#define ADNS9800_DATA_OUT_UPPER_ADDR					0x26
#define ADNS9800_SROM_ID_ADDR							0x2A
#define ADNS9800_LIFT_DETECTION_THR_ADDR				0x2E
#define ADNS9800_CONFIGURATION_V_ADDR					0x2F
#define ADNS9800_CONFIGURATION_IV_ADDR					0x39
#define ADNS9800_POWER_UP_RESET_ADDR					0x3A
#define ADNS9800_SHUTDOWN_ADDR							0x3B
#define ADNS9800_INVERSE_PRODUCT_ID_ADDR				0x3F
#define ADNS9800_MOTION_BURST_ADDR						0x50
#define ADNS9800_SROM_LOAD_BURST_ADDR					0x62
#define ADNS9800_PIXEL_BURST_ADDR						0x64

typedef union
{
	s16 w;
	u8 b[2];    //低位在b[0]起  例如w=0x1234，则吧b[0]=0x34;b[1]=0x12
}s16_union;

void ADNS9200_Init(void);
void ADNS9200_SPI_Init(void);
void Gpio_Int_Init_adns9800(void);
u8 spi_hw_read_sensor(u8 reg_addr);
void spi_hw_write_sensor(u8 reg_addr, u8 data);
void adns_upload_firmware(void);
void performStartup(void);
int readXY(int *xy);
int readXY(int *xy);
void delay_us_adns(u16 time);
void delay_ms_adns(u16 time);
void EXTI0_IRQHandler(void);
void ADNS9800_check_sequence(void);
void ADNS9800_power_up_sequence(void);
void ANDS9800_SROM_load_sequence(void);
void ANDS9800_SROM_Download(void);
unsigned char ADNS9800_SROM_Check(void);
void ADNS9800_laser_power_enable_sequence(void);
void UpdateADNS9800(uint8_t* pDesArr);
void read_sensor_motion_burst(void);
void Read_ADNS9800(void);

void Update_ADNS9800_Value(uint8_t* pDesArr,uint8_t* pDesLength);
#endif
