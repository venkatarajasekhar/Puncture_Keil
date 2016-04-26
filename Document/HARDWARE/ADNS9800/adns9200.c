#include "adns9200.h" 
#include "stm32f10x.h"
#include "spi.h"
#include "stdio.h"

#define  Write_Read_Spi_Byte  SPI2_ReadWriteByte
extern u8  timer2flag;
s16_union motion_x,motion_y,count_x,count_y;
const unsigned short firmware_length = 3070;
u8  initComplete=0;
const u8 firmware_data[]  = {
  0x03, 0xa4, 0x6e, 0x16, 0x6d, 0x89, 0x3e, 0xfe, 0x5f, 0x1c, 0xb8, 0xf2, 0x47, 0x0c, 0x7b, 
  0x74, 0x6a, 0x56, 0x0f, 0x7d, 0x76, 0x71, 0x4b, 0x0c, 0x97, 0xb6, 0xcf, 0xfd, 0x78, 0x72, 
  0x66, 0x2f, 0xbd, 0xf8, 0x53, 0x24, 0xab, 0xd4, 0x2c, 0xb0, 0xe4, 0x32, 0xf1, 0x6a, 0x56, 
  0x2e, 0xbf, 0xfc, 0x7a, 0x57, 0x0d, 0x79, 0x70, 0x66, 0x46, 0x0e, 0x7f, 0x5d, 0x19, 0x91, 
  0xaa, 0xc2, 0x0d, 0x8e, 0x7f, 0x5d, 0x19, 0xb0, 0xe2, 0x46, 0xef, 0x5c, 0x3a, 0xd7, 0x2c, 
  0xbb, 0xf4, 0x6a, 0x37, 0xcd, 0x18, 0xb2, 0xc7, 0x0c, 0x9a, 0x97, 0x8f, 0x52, 0xfd, 0x0d, 
  0xb8, 0x41, 0x00, 0x9e, 0x8e, 0x9a, 0x1e, 0x6d, 0x0c, 0xe2, 0xaa, 0x13, 0x93, 0xb8, 0xc1, 
  0x2a, 0x29, 0xbb, 0x0b, 0xe3, 0x71, 0x08, 0x6d, 0xfd, 0xb6, 0xd9, 0xcf, 0x65, 0x21, 0x27, 
  0x45, 0x1b, 0xbe, 0xe2, 0x61, 0x86, 0x3c, 0xbf, 0x68, 0x9c, 0xd6, 0x75, 0x01, 0x5e, 0xe0, 
  0xc6, 0x92, 0x79, 0xf4, 0x6a, 0xa9, 0xbb, 0x2a, 0x79, 0xd0, 0xe1, 0x5c, 0x32, 0xb1, 0x5a, 
  0x1b, 0xba, 0xaf, 0x11, 0xea, 0x24, 0x6a, 0x83, 0x4f, 0x8d, 0xed, 0x19, 0x62, 0x70, 0x54, 
  0xfb, 0x0e, 0x1f, 0x83, 0xcc, 0xf0, 0xb7, 0xae, 0x05, 0xd3, 0x42, 0x5d, 0x48, 0xa0, 0x7a, 
  0x0b, 0x73, 0xb3, 0xc8, 0xa6, 0xb7, 0x1b, 0x08, 0x13, 0x9b, 0x89, 0x44, 0x42, 0xae, 0xd8, 
  0x6a, 0xba, 0x9b, 0x84, 0x25, 0x8b, 0xa4, 0x5e, 0x0b, 0x85, 0xb0, 0x8f, 0x8d, 0x80, 0x9c, 
  0xd1, 0x52, 0xc7, 0xcb, 0xff, 0x8d, 0x8b, 0xdd, 0x87, 0xf2, 0x63, 0xca, 0xe7, 0x4f, 0x4a, 
  0x57, 0x3c, 0xdf, 0xaf, 0xcb, 0x5c, 0xbb, 0x39, 0x0b, 0x01, 0x9c, 0x79, 0x22, 0x15, 0xb8, 
  0xa0, 0xd3, 0x72, 0x02, 0x35, 0x20, 0x40, 0xe0, 0x17, 0xde, 0x89, 0x88, 0xce, 0xe9, 0x2b, 
  0x75, 0xba, 0xa0, 0x96, 0x24, 0x1e, 0x71, 0xb5, 0x15, 0x00, 0x61, 0xe0, 0x5c, 0x93, 0x4e, 
  0xea, 0x53, 0xd0, 0xfc, 0xef, 0xae, 0x2b, 0xeb, 0x8f, 0xc7, 0x69, 0x68, 0xc7, 0xfc, 0x1a, 
  0x1f, 0x41, 0x0d, 0xd0, 0xc1, 0x03, 0xaf, 0xc9, 0xfd, 0xe4, 0x21, 0x43, 0xc4, 0xef, 0xc2, 
  0xdd, 0x7b, 0x73, 0xbc, 0xca, 0xf4, 0xa5, 0x2e, 0x83, 0x90, 0x1f, 0x78, 0x41, 0xc3, 0x13, 
  0x8e, 0x95, 0x0a, 0x57, 0xdf, 0x0a, 0x87, 0x40, 0x2b, 0xd9, 0xba, 0x56, 0x59, 0x9d, 0x2c, 
  0xb2, 0xb8, 0xb3, 0xfb, 0x77, 0x78, 0x3a, 0xef, 0xbf, 0x2d, 0xc8, 0xb9, 0x94, 0x62, 0x47, 
  0x92, 0x98, 0x42, 0x23, 0x07, 0xd9, 0x39, 0x46, 0x5e, 0x6f, 0xe0, 0x46, 0x14, 0x0e, 0x3d, 
  0x74, 0x40, 0x21, 0xb4, 0x67, 0x05, 0xa8, 0xe2, 0x12, 0x93, 0x41, 0xc2, 0x80, 0xb9, 0x56, 
  0x4b, 0xf9, 0x5a, 0x15, 0x9c, 0x37, 0xc4, 0x4b, 0x05, 0xad, 0x5a, 0xaf, 0xa1, 0x3e, 0xe4, 
  0x6e, 0xc5, 0x91, 0xb6, 0x75, 0x7d, 0x1b, 0xe4, 0xc5, 0x4d, 0x28, 0x6b, 0xe9, 0xad, 0x20, 
  0x8b, 0x64, 0x91, 0x57, 0x4f, 0xdf, 0x9a, 0x97, 0x7e, 0xbe, 0x8e, 0xd6, 0xd6, 0x3b, 0x17, 
  0xf9, 0x19, 0x28, 0xb2, 0x2e, 0x8f, 0x26, 0xb4, 0x9b, 0xe5, 0xde, 0x0f, 0x8d, 0x0a, 0x9a, 
  0x9d, 0x1b, 0xde, 0x6f, 0xcb, 0x84, 0xba, 0x26, 0xd0, 0x12, 0xef, 0x30, 0x38, 0x43, 0xac, 
  0xb7, 0xa7, 0xef, 0x09, 0x7c, 0x52, 0x27, 0xfc, 0x2e, 0xab, 0x50, 0xa0, 0x21, 0x40, 0xe7, 
  0xc1, 0x5f, 0x02, 0x41, 0x84, 0xa8, 0x54, 0xa8, 0x2e, 0x37, 0x6f, 0xd8, 0xb1, 0xa4, 0xd0, 
  0x75, 0xef, 0x31, 0xca, 0x54, 0x1e, 0x33, 0xad, 0x19, 0xa1, 0x94, 0xbc, 0x1b, 0x34, 0x6c, 
  0xfb, 0x5f, 0xcc, 0x45, 0x76, 0xc8, 0x96, 0xce, 0x1c, 0x3a, 0x0e, 0x77, 0xed, 0xd8, 0xd2, 
  0x96, 0xac, 0x77, 0x30, 0xe1, 0xef, 0xb0, 0x33, 0xf0, 0x6e, 0x3d, 0xce, 0x5e, 0x6d, 0xde, 
  0x8a, 0xdc, 0x9b, 0x91, 0x63, 0x2a, 0x95, 0x20, 0x0d, 0xfd, 0x78, 0xba, 0xcb, 0x15, 0x43, 
  0xc9, 0x20, 0x96, 0x83, 0x06, 0xd9, 0x11, 0xf3, 0xe2, 0x13, 0xcf, 0x9c, 0x91, 0x7f, 0x33, 
  0x46, 0xa7, 0xe2, 0xd3, 0x75, 0xff, 0x4f, 0x0c, 0x0c, 0xaf, 0xcd, 0xa6, 0x9c, 0xa6, 0x73, 
  0xe2, 0x6d, 0x17, 0x16, 0xb5, 0x99, 0x80, 0x35, 0xd9, 0x61, 0xf3, 0x48, 0x23, 0xff, 0xae, 
  0x53, 0x89, 0xfa, 0x55, 0x1c, 0x37, 0xa5, 0xe8, 0x62, 0x12, 0xb2, 0x22, 0x04, 0xed, 0x42, 
  0xb6, 0x65, 0xc4, 0x41, 0x42, 0x72, 0xca, 0x7e, 0x5e, 0x2f, 0x69, 0x46, 0xef, 0xbd, 0x7e, 
  0xdf, 0x35, 0x1e, 0x5b, 0x77, 0xaf, 0x8d, 0x39, 0xf8, 0xa7, 0xd8, 0x31, 0x00, 0xd3, 0x85, 
  0x66, 0xd5, 0xcd, 0x59, 0xd6, 0x5e, 0x9f, 0xb2, 0x3f, 0x09, 0xd1, 0xc4, 0x5b, 0x74, 0x62, 
  0xd3, 0x30, 0x35, 0xf3, 0xe3, 0x7d, 0x7f, 0xab, 0x38, 0xc2, 0x33, 0x42, 0xd0, 0x67, 0xd0, 
  0xf4, 0xcf, 0x97, 0xec, 0x35, 0x31, 0xfe, 0x94, 0x9c, 0xa1, 0x66, 0x91, 0xc8, 0x05, 0x45, 
  0x19, 0x85, 0x0f, 0x4a, 0xb0, 0x3a, 0x20, 0x44, 0xa4, 0x6b, 0x33, 0x0c, 0xa6, 0xb4, 0x4c, 
  0x46, 0x30, 0x15, 0x2d, 0xbb, 0x04, 0x3c, 0x9d, 0x48, 0xf6, 0x84, 0x9a, 0x62, 0x07, 0xe9, 
  0x6c, 0x8f, 0xde, 0x29, 0x28, 0x5a, 0x17, 0xec, 0x56, 0xf3, 0xc4, 0xe0, 0x86, 0x2f, 0xb5, 
  0x1c, 0x8f, 0xaa, 0xc6, 0xc0, 0xcf, 0x0d, 0xcf, 0x1d, 0x4f, 0xb2, 0xbf, 0x26, 0x5c, 0x7c, 
  0x8d, 0xd3, 0xe4, 0x56, 0xd1, 0xe8, 0x90, 0x94, 0x6a, 0xba, 0x27, 0xba, 0xf7, 0xba, 0x39, 
  0xc8, 0x08, 0x03, 0x25, 0x7f, 0x16, 0x8f, 0x61, 0xbf, 0xdf, 0x45, 0x88, 0x7d, 0x90, 0x80, 
  0x55, 0x58, 0x72, 0x4f, 0xf8, 0xd0, 0x94, 0xbb, 0x55, 0x2a, 0x47, 0x4f, 0xaa, 0x87, 0x2d, 
  0xd4, 0xe7, 0xaf, 0x08, 0x33, 0xc9, 0xec, 0x0b, 0x5b, 0xb8, 0x53, 0x27, 0x2e, 0xfb, 0xad, 
  0x69, 0xb6, 0x53, 0x64, 0x48, 0x13, 0x41, 0xf8, 0x02, 0x06, 0x6f, 0xb8, 0xcc, 0x64, 0xec, 
  0x65, 0x65, 0x7e, 0xdf, 0x3f, 0x1e, 0xe1, 0xee, 0xde, 0x3c, 0x1a, 0xe8, 0x0f, 0xf0, 0x2c, 
  0xea, 0x6e, 0x52, 0x77, 0x34, 0x41, 0xa1, 0xcc, 0x72, 0x8f, 0x6e, 0x9c, 0x3b, 0x8d, 0x39, 
  0xdf, 0xd4, 0x08, 0x24, 0xba, 0x36, 0xc7, 0x09, 0xf2, 0xf1, 0xa2, 0xd1, 0xe0, 0xa3, 0x6a, 
  0x5c, 0xc7, 0xb2, 0x0d, 0x1c, 0xfb, 0x5f, 0xc8, 0x86, 0xd8, 0x3e, 0x1c, 0xb7, 0x1f, 0x2d, 
  0xd8, 0xf2, 0xcd, 0x52, 0xeb, 0xde, 0x50, 0x14, 0xb7, 0xc7, 0xa2, 0x8b, 0x78, 0x70, 0x11, 
  0x87, 0x1a, 0xc5, 0xb8, 0xe5, 0x5e, 0xa5, 0xc9, 0x94, 0x22, 0x66, 0x7b, 0x8b, 0x74, 0xab, 
  0x85, 0x28, 0x95, 0x90, 0x6e, 0x07, 0xdd, 0x79, 0x57, 0xb3, 0x75, 0xc8, 0x18, 0x67, 0x39, 
  0x06, 0x21, 0x55, 0xba, 0xba, 0xda, 0xf9, 0x3b, 0xe9, 0x5d, 0xc9, 0x1f, 0x6f, 0x61, 0x3b, 
  0xc2, 0x7e, 0x3d, 0x07, 0xa6, 0x84, 0x91, 0xb7, 0x63, 0x7e, 0x5f, 0xfc, 0xd1, 0x7d, 0x08, 
  0xdd, 0x79, 0x07, 0xe1, 0x9e, 0x11, 0x25, 0xe8, 0x10, 0x05, 0x66, 0xfa, 0xca, 0xc3, 0x41, 
  0x01, 0x27, 0x54, 0xd2, 0x46, 0xae, 0xe3, 0xff, 0x43, 0xae, 0x8d, 0x0e, 0x31, 0x13, 0x1f, 
  0x95, 0x79, 0x82, 0x86, 0x7e, 0xfb, 0xd4, 0x17, 0x57, 0xb8, 0x25, 0xe7, 0x1d, 0x18, 0x8f, 
  0x06, 0x1a, 0xe5, 0xef, 0x55, 0x28, 0x72, 0x42, 0xae, 0xdf, 0x9e, 0xbb, 0x14, 0xab, 0xd8, 
  0x36, 0x4f, 0x46, 0x4b, 0x35, 0x92, 0x64, 0x6d, 0xbb, 0x60, 0xc2, 0x0b, 0x6f, 0x57, 0x5e, 
  0x3a, 0x8f, 0x3d, 0xcb, 0xe5, 0xda, 0x6c, 0x5c, 0x85, 0x8f, 0x9d, 0xa6, 0x7e, 0x1e, 0x49, 
  0x1a, 0xcc, 0xc9, 0xec, 0x04, 0xab, 0x35, 0xf2, 0x9b, 0xe7, 0xb3, 0x52, 0xb1, 0x1c, 0xc1, 
  0xfe, 0x5c, 0x0b, 0xf5, 0x72, 0x0b, 0xec, 0x8e, 0xcd, 0x67, 0x98, 0xbf, 0xa5, 0x28, 0xca, 
  0x48, 0x9b, 0x60, 0x1c, 0xee, 0x00, 0xde, 0x01, 0xbc, 0xa4, 0x02, 0xd2, 0x19, 0xb6, 0x05, 
  0xd6, 0x52, 0x78, 0xdb, 0x20, 0xbd, 0x3f, 0x95, 0x97, 0xb1, 0x59, 0x3d, 0x9d, 0x83, 0xc2, 
  0xfd, 0x23, 0xa5, 0xfd, 0xd8, 0x20, 0x92, 0x27, 0xee, 0x3c, 0xe9, 0x5a, 0x61, 0x11, 0xe1, 
  0x31, 0xb4, 0x4c, 0xb4, 0xa9, 0xe2, 0x6d, 0x2e, 0xae, 0x5f, 0x37, 0x8e, 0x07, 0xfd, 0xed, 
  0x85, 0x07, 0x79, 0x43, 0x7e, 0xfa, 0xd6, 0x03, 0xe8, 0x5b, 0x65, 0x2a, 0xe4, 0xf9, 0x36, 
  0x9e, 0xff, 0x53, 0x6d, 0x51, 0x50, 0x61, 0x72, 0x18, 0xcd, 0x3d, 0xe4, 0xb6, 0x27, 0x10, 
  0x4a, 0xdd, 0xfd, 0xa3, 0x36, 0x67, 0xac, 0xc7, 0x85, 0x1c, 0xd3, 0xe7, 0x17, 0x74, 0xe2, 
  0x8e, 0xee, 0xa6, 0xf4, 0xb6, 0x86, 0x24, 0xcf, 0x40, 0xdf, 0x35, 0x08, 0x0f, 0x55, 0xdd, 
  0x51, 0xe9, 0x7c, 0x39, 0x78, 0x5c, 0xdf, 0x20, 0x2a, 0xeb, 0xed, 0x35, 0x10, 0x26, 0x98, 
  0x77, 0x69, 0x4e, 0x51, 0x7a, 0xb2, 0x9f, 0x1d, 0xbc, 0x06, 0xcd, 0xcf, 0x4d, 0xb9, 0xfa, 
  0xb7, 0xaf, 0x6a, 0x07, 0x0c, 0x96, 0x42, 0x57, 0x6c, 0x3d, 0xa5, 0xfe, 0x91, 0xe3, 0x76, 
  0x9f, 0xdd, 0x3c, 0x83, 0x25, 0xab, 0x24, 0x89, 0x47, 0x7c, 0xba, 0xd7, 0x7d, 0x72, 0x90, 
  0x80, 0xb0, 0x03, 0xa4, 0xef, 0x04, 0x0a, 0x9e, 0x5a, 0x14, 0x1c, 0xab, 0x75, 0x47, 0x05, 
  0xcb, 0xa2, 0x97, 0x0d, 0x6a, 0xa5, 0x7c, 0xa4, 0x40, 0x90, 0xe2, 0x6c, 0xfa, 0xd4, 0xbd, 
  0x69, 0xd0, 0x06, 0x53, 0x67, 0xfa, 0xe7, 0xcc, 0x06, 0x42, 0x45, 0xbe, 0xbd, 0x6f, 0x3e, 
  0x48, 0x70, 0xf5, 0x2b, 0x83, 0xc7, 0xba, 0x54, 0x9c, 0xab, 0x54, 0x1f, 0x81, 0xe2, 0x11, 
  0x82, 0x51, 0x02, 0x51, 0x63, 0x13, 0x86, 0x38, 0xb1, 0x56, 0x0c, 0x4d, 0x68, 0xf3, 0x53, 
  0x1d, 0xfb, 0xe3, 0x15, 0xe8, 0x42, 0xf3, 0x27, 0x9b, 0xa5, 0x4a, 0x86, 0x90, 0xe1, 0x17, 
  0xdc, 0x99, 0xe2, 0x5c, 0x79, 0xc6, 0x5f, 0x7e, 0x33, 0xc0, 0x41, 0xb6, 0x9e, 0xfc, 0x10, 
  0x8a, 0xf4, 0xfd, 0xe9, 0xd2, 0x52, 0x53, 0x54, 0x89, 0x04, 0xbd, 0x69, 0xd2, 0x54, 0x32, 
  0x96, 0xec, 0x44, 0x08, 0xc3, 0x86, 0x10, 0xd1, 0x3e, 0x32, 0xb5, 0x4f, 0x52, 0x49, 0x58, 
  0x49, 0xf2, 0x8d, 0x83, 0x89, 0xf3, 0x24, 0x83, 0x65, 0x72, 0x53, 0xaf, 0x2d, 0x90, 0x61, 
  0x99, 0x92, 0x31, 0x75, 0x93, 0x46, 0xe5, 0xd3, 0x48, 0x11, 0x01, 0xc9, 0x10, 0x98, 0x66, 
  0x86, 0x79, 0x19, 0x73, 0x7d, 0xda, 0xa1, 0xb0, 0x41, 0x9e, 0xcd, 0xdc, 0xc2, 0x66, 0x86, 
  0xdd, 0xb8, 0xc9, 0xe3, 0xe7, 0x80, 0x96, 0xf5, 0x38, 0x72, 0xa5, 0xda, 0xe5, 0x38, 0x13, 
  0x57, 0x2b, 0xbd, 0x32, 0xc7, 0x44, 0xe0, 0xe3, 0x2d, 0xed, 0x54, 0x40, 0x74, 0x9d, 0x02, 
  0x55, 0x38, 0x45, 0x89, 0x6f, 0x14, 0x40, 0xf6, 0x7b, 0x41, 0x1e, 0x04, 0xdb, 0xa4, 0xd9, 
  0xf3, 0x90, 0xae, 0x10, 0xc9, 0xc3, 0x72, 0x5d, 0x0d, 0x01, 0x51, 0xf1, 0xd1, 0x96, 0x43, 
  0xc6, 0x1a, 0x98, 0x3d, 0xbd, 0xcd, 0xdf, 0x44, 0x82, 0xd0, 0x17, 0xa2, 0x9e, 0x6c, 0x0c, 
  0x2f, 0x46, 0xeb, 0xd8, 0x4a, 0xce, 0xfe, 0xbe, 0xcd, 0xf9, 0xd4, 0xe3, 0x36, 0xf3, 0xd8, 
  0x1c, 0x00, 0x24, 0xf2, 0xac, 0x03, 0x11, 0xb6, 0x18, 0x8f, 0x9c, 0xba, 0xf6, 0x4f, 0xfd, 
  0x78, 0x72, 0x83, 0xbf, 0x3e, 0x5c, 0x24, 0xf9, 0x4d, 0xea, 0x85, 0x74, 0x25, 0xe3, 0x46, 
  0x7b, 0x5e, 0xfe, 0xbd, 0xbf, 0x5e, 0x68, 0x51, 0xe5, 0x53, 0x85, 0x9a, 0x03, 0x4c, 0x09, 
  0xf0, 0x6b, 0xc2, 0x97, 0xfc, 0xcc, 0x96, 0x2c, 0xaf, 0xf7, 0x8c, 0x26, 0xd8, 0xc7, 0xfc, 
  0xda, 0x1f, 0x0e, 0x0f, 0x39, 0x1a, 0xb2, 0x0a, 0x98, 0x1a, 0x15, 0xdc, 0x3e, 0x4b, 0x9e, 
  0x9d, 0x40, 0x3e, 0x71, 0x5b, 0x66, 0xc3, 0x88, 0xf8, 0x57, 0x14, 0x06, 0xc7, 0x2c, 0xcd, 
  0x31, 0x8e, 0x1e, 0x88, 0x79, 0x9f, 0x33, 0x94, 0xea, 0x21, 0x08, 0x0d, 0x35, 0x7d, 0xa2, 
  0x57, 0x46, 0xe3, 0x0f, 0xb9, 0xa9, 0xbc, 0xd2, 0x06, 0xb8, 0xfa, 0xf9, 0xb0, 0xf3, 0xc3, 
  0x8a, 0x38, 0x82, 0x06, 0x7f, 0xd9, 0xce, 0x92, 0xa2, 0x9e, 0xfc, 0x2a, 0xc8, 0x51, 0xb7, 
  0x7d, 0xdb, 0x47, 0x37, 0xaf, 0x8b, 0xb8, 0x6d, 0x70, 0x21, 0x02, 0x63, 0x5e, 0xbd, 0x38, 
  0xf1, 0xe1, 0x9f, 0xe3, 0xe2, 0x79, 0x3b, 0x42, 0x05, 0xe2, 0xc6, 0x13, 0x7a, 0xe2, 0x91, 
  0x73, 0xe2, 0x79, 0x8b, 0x2f, 0x7f, 0x88, 0x02, 0x06, 0x4e, 0xb8, 0x66, 0xb8, 0xc0, 0xc4, 
  0x3b, 0x1c, 0x3e, 0x96, 0x0f, 0xbb, 0x7f, 0xe8, 0x85, 0x5b, 0xb2, 0xf6, 0xa7, 0x48, 0x5b, 
  0x95, 0x83, 0x57, 0xe0, 0xe8, 0x22, 0x67, 0x07, 0x3c, 0x27, 0x65, 0x66, 0xe8, 0x84, 0xab, 
  0xea, 0xf5, 0xb5, 0x00, 0xec, 0xa4, 0xa3, 0xe8, 0x25, 0x77, 0xd1, 0x81, 0x9c, 0x87, 0xd3, 
  0x1a, 0x31, 0x58, 0xa4, 0x0a, 0xa8, 0x71, 0x9c, 0x52, 0x88, 0x4d, 0x50, 0xff, 0xdb, 0x41, 
  0x81, 0x04, 0xc3, 0x84, 0xaa, 0x72, 0x79, 0x2f, 0x9b, 0x2d, 0x2f, 0x1c, 0xa5, 0x6b, 0x68, 
  0x9b, 0x3b, 0x6b, 0x1c, 0x67, 0xeb, 0x42, 0xe0, 0xe3, 0x2c, 0x7b, 0x52, 0x8e, 0xc1, 0x7e, 
  0xd8, 0xab, 0x02, 0x46, 0xd1, 0x83, 0x38, 0x1a, 0x18, 0xad, 0x90, 0x7f, 0xdb, 0x22, 0xc1, 
  0x80, 0xea, 0xf7, 0x67, 0x1d, 0xa7, 0xb2, 0x40, 0xdb, 0xc3, 0xc4, 0xd5, 0x8b, 0x49, 0xf8, 
  0xdc, 0x25, 0x80, 0x7e, 0xfa, 0x64, 0xac, 0x36, 0x4d, 0x74, 0x6f, 0x3e, 0x57, 0x23, 0xb4, 
  0x49, 0x7c, 0x6f, 0x3e, 0x7c, 0xa7, 0x34, 0xb7, 0x6b, 0x66, 0xf8, 0xd1, 0x69, 0x6d, 0x83, 
  0xc5, 0x8a, 0xe2, 0x42, 0x3f, 0x8b, 0x5e, 0x5a, 0xd5, 0xcd, 0x47, 0x64, 0xeb, 0x4e, 0xef, 
  0x62, 0x19, 0x37, 0xd3, 0x8e, 0x68, 0x51, 0x4a, 0x96, 0xbb, 0x5b, 0xa0, 0x34, 0xd8, 0xb4, 
  0xf4, 0xb0, 0x99, 0x53, 0xb1, 0x70, 0xc3, 0x1d, 0x6e, 0x2b, 0x03, 0x76, 0xc9, 0x00, 0x0b, 
  0x10, 0xca, 0xb7, 0xf3, 0xbe, 0x4b, 0xe2, 0xb4, 0x6c, 0x4a, 0x9f, 0x59, 0x39, 0x30, 0xc7, 
  0xc3, 0x88, 0x38, 0x63, 0xc4, 0xcf, 0xd1, 0xfd, 0xf0, 0x6d, 0xfe, 0x68, 0x92, 0x98, 0x11, 
  0x7d, 0x90, 0x0c, 0x64, 0x23, 0xe8, 0x25, 0x77, 0xd1, 0x81, 0x75, 0xa4, 0xf4, 0x35, 0x6f, 
  0xe4, 0x9c, 0x7a, 0x48, 0xd0, 0xde, 0x37, 0x42, 0xf8, 0x5b, 0xe9, 0x16, 0xba, 0x16, 0x4b, 
  0x7c, 0xdb, 0x2c, 0x0e, 0xa0, 0xbc, 0x5c, 0x82, 0x71, 0xa0, 0x9d, 0x3a, 0x0a, 0x7e, 0xd0, 
  0xdc, 0x93, 0x79, 0xf6, 0x78, 0xb5, 0x89, 0xd9, 0x70, 0x5d, 0xe0, 0x9d, 0xe7, 0xea, 0xee, 
  0x88, 0x52, 0x18, 0x11, 0x7d, 0xf1, 0xce, 0xc1, 0x69, 0x8d, 0x3f, 0xea, 0x51, 0xc1, 0x49, 
  0xb1, 0xc4, 0xa6, 0xf0, 0xdc, 0xbd, 0x61, 0xb7, 0x2c, 0x85, 0x4a, 0xcb, 0xdd, 0x96, 0x50, 
  0x8b, 0x68, 0xf7, 0x7e, 0xb9, 0x1c, 0x19, 0xfb, 0x5c, 0x79, 0xf8, 0x7d, 0xe9, 0xf3, 0x0e, 
  0xc7, 0x6e, 0x1c, 0x67, 0xb4, 0xb7, 0x4a, 0xc5, 0xbe, 0x3c, 0x8c, 0x94, 0x36, 0x02, 0x8f, 
  0x81, 0x57, 0xe7, 0x4b, 0xd6, 0x2b, 0x10, 0xbe, 0x3c, 0x97, 0xbb, 0x41, 0x88, 0x6f, 0x13, 
  0xe6, 0x27, 0x13, 0x4b, 0xd5, 0x44, 0xa9, 0xd9, 0x2d, 0xcd, 0x51, 0x91, 0x03, 0x14, 0xd5, 
  0x6b, 0x3d, 0xb5, 0x98, 0xf0, 0x09, 0xaa, 0x42, 0x8e, 0x82, 0xe8, 0xf1, 0x36, 0xec, 0xb5, 
  0x48, 0x5f, 0x9f, 0xca, 0x16, 0x5a, 0x3f, 0x4d, 0xbb, 0xa6, 0xd4, 0x08, 0x1a, 0xfb, 0xe5, 
  0xeb, 0x40, 0x04, 0xe8, 0x40, 0x84, 0xc4, 0x8e, 0x74, 0xae, 0x47, 0x4d, 0xfc, 0xb5, 0x91, 
  0xe2, 0x33, 0xf2, 0xf7, 0xae, 0xcd, 0x10, 0x47, 0xb1, 0x4b, 0xe2, 0xa2, 0x8d, 0x7c, 0x2c, 
  0x32, 0x6f, 0xdd, 0xc4, 0xc2, 0xf1, 0x09, 0x56, 0x2d, 0x1e, 0x9d, 0x7d, 0x67, 0x32, 0x61, 
  0x7f, 0x12, 0xe4, 0x3f, 0xfa, 0xe2, 0x7d, 0x7b, 0xd4, 0x67, 0x4e, 0x7f, 0x14, 0x6a, 0x6c, 
  0x8e, 0x74, 0x9b, 0xbc, 0x3d, 0xc4, 0x70, 0xc4, 0x37, 0xd5, 0x60, 0xe0, 0x87, 0xbd, 0xb8, 
  0x1a, 0x75, 0x9d, 0x7a, 0x80, 0xc1, 0xa9, 0x1f, 0xad, 0x7b, 0x27, 0xe5, 0x4c, 0xb0, 0x06, 
  0xd0, 0xfb, 0x1c, 0x5a, 0xeb, 0xbd, 0x2e, 0x96, 0x49, 0x13, 0x43, 0x06, 0x8b, 0xcb, 0x6a, 
  0xf0, 0x5d, 0x56, 0x6c, 0x4e, 0x18, 0x26, 0xd4, 0xc8, 0x53, 0x48, 0x70, 0xe2, 0x0f, 0x9c, 
  0xa1, 0x35, 0x01, 0x96, 0xc7, 0x0b, 0xc9, 0x4b, 0xd3, 0x19, 0xe8, 0x5a, 0x75, 0xad, 0xc8, 
  0x52, 0xce, 0x3c, 0x2e, 0xfd, 0x5f, 0x04, 0xcf, 0x9e, 0xd6, 0x33, 0xdb, 0x08, 0x34, 0xba, 
  0x34, 0x9b, 0xf4, 0x25, 0xaa, 0x7f, 0x52, 0x37, 0x4f, 0x8b, 0x94, 0x95, 0x94, 0x2d, 0x88, 
  0x10, 0xd1, 0x05, 0x07, 0xcf, 0xd4, 0x04, 0xdb, 0x95, 0xbe, 0x36, 0xd0, 0x1c, 0x1c, 0xa4, 
  0x85, 0x0a, 0x02, 0x80, 0xde, 0xb1, 0x1b, 0x56, 0xaf, 0x51, 0x22, 0xa7, 0xa4, 0x4a, 0x2c, 
  0x2f, 0x17, 0x7c, 0x13, 0x4c, 0x36, 0xad, 0x90, 0x8c, 0xea, 0xd4, 0x58, 0x3a, 0xca, 0xea, 
  0x1d, 0x5c, 0x6c, 0x93, 0xad, 0x59, 0xed, 0xb1, 0x17, 0xa4, 0x22, 0x95, 0x67, 0xbe, 0xbb, 
  0x25, 0xaf, 0x65, 0xc8, 0xe5, 0x90, 0xe1, 0x17, 0xdc, 0x7a, 0x47, 0xe9, 0x8f, 0xc3, 0xc3, 
  0x5a, 0xdc, 0x20, 0x20, 0x4a, 0x09, 0xfc, 0x39, 0x51, 0x29, 0x31, 0xfb, 0xa0, 0x0a, 0x61, 
  0x08, 0x9b, 0xb9, 0xb3, 0x6c, 0x95, 0xc5, 0x94, 0x00, 0x66, 0xf1, 0xb9, 0x79, 0x90, 0x7f, 
  0x95, 0x5f, 0x55, 0xe1, 0x13, 0x6b, 0x87, 0xa8, 0x62, 0x21, 0x98, 0xf2, 0x57, 0x19, 0x92, 
  0x10, 0xb3, 0x24, 0x81, 0x12, 0x21, 0xff, 0xd6, 0xf9, 0x73, 0x71, 0xc2, 0x62, 0x09, 0x31, 
  0xeb, 0xe0, 0x7a, 0x35, 0x60, 0x8d, 0xc9, 0xb1, 0xe5, 0xa7, 0x8b, 0xca, 0xbc, 0x2d, 0xfa, 
  0x63, 0xc7, 0x68, 0x1d, 0x19, 0xb5, 0x61, 0x78, 0xd0, 0x8b, 0xdb, 0xc0, 0x39, 0x22, 0x55, 
  0x6a, 0x28, 0xc2, 0x52, 0x1e, 0x6b, 0xf7, 0x1d, 0xb6, 0xfa, 0x4f, 0xcf, 0x27, 0x7c, 0xaf, 
  0x7f, 0x0c, 0x96, 0xba, 0xce, 0x2a, 0x54, 0x59, 0x5b, 0x20, 0xfb, 0x42, 0x87, 0x44, 0xd9, 
  0x2e, 0x10, 0x43, 0xab, 0x58, 0x92, 0xb6, 0x8d, 0x78, 0xf3, 0xa3, 0xde, 0x0e, 0x07, 0x75, 
  0x68, 0x52, 0x26, 0x3f, 0x3d, 0xec, 0xd0, 0x36, 0xdf, 0x1a, 0x16, 0x88, 0x5f, 0xbd, 0x1c, 
  0x4d, 0x9e, 0x27, 0x4c, 0x12, 0x07, 0x0d, 0x2b, 0xb1, 0xdc, 0x00, 0x45, 0x54, 0x3d, 0xfc, 
  0xcf, 0xfa, 0xc9, 0x06, 0x4b, 0x08, 0x64, 0xac, 0x8d, 0x17, 0x4d, 0xdf, 0x83, 0x24, 0xfb, 
  0xf6, 0x9e, 0x5f, 0xf9, 0x0f, 0x8d, 0x07, 0x18, 0xb1, 0xb2, 0x37, 0xd2, 0x66, 0x9c, 0x82, 
  0x09, 0x75, 0x52, 0x5b, 0x19, 0x74, 0x59, 0xa3, 0x64, 0x6d, 0x17, 0x93, 0x3a, 0x13, 0xd2, 
  0xda, 0x97, 0xa4, 0x2b, 0x55, 0x7a, 0x32, 0xf9, 0x2f, 0x9b, 0xaa, 0x87, 0x6d, 0xce, 0x1d, 
  0x07, 0x9a, 0x52, 0xfa, 0x40, 0xc5, 0x20, 0x43, 0xcc, 0xa8, 0xc3, 0x84, 0x2c, 0x44, 0x8b, 
  0x44, 0x88, 0x62, 0xe7, 0x68, 0x4c, 0x2a, 0x69, 0xa7, 0xcf, 0x6f, 0x4d, 0x06, 0xed, 0x8a, 
  0x8f, 0x9a, 0x62, 0xca, 0xed, 0xa5, 0x57, 0x18, 0x86, 0x9d, 0xe8, 0x7c, 0x14, 0xeb, 0x71, 
  0xeb, 0xc0, 0xf4, 0x3a, 0x98, 0x11, 0x01, 0xc0, 0xa3, 0x53, 0xaf, 0x20, 0x7e, 0xde, 0x22, 
  0x5c, 0x1f, 0x60, 0x8b, 0xb7, 0x5f, 0x74, 0x76, 0xd0, 0x87, 0xfa, 0x11, 0xd3, 0xa5, 0xba, 
  0x5c, 0x82, 0xe1, 0x52, 0x54, 0x6b, 0x69, 0xeb, 0x31, 0x43, 0x01, 0x1a, 0x55, 0x7f, 0xdc, 
  0x2f, 0xd8, 0x01, 0x26, 0x6f, 0x1c, 0x2d, 0x72, 0x7b, 0xc8, 0x93, 0x99, 0x2a, 0x08, 0xa8, 
  0x6f, 0xb4, 0x28, 0x40, 0x8a, 0x8a, 0x4e, 0xd5, 0x3b, 0x39, 0x45, 0xa8, 0xe4, 0xe7, 0x73, 
  0x8f, 0x00, 0x64, 0xd3, 0xc7, 0x87, 0xde, 0x43, 0x82, 0x2c, 0xe8, 0x57, 0x17, 0x29, 0xce, 
  0xb8, 0x47, 0xd6, 0x08, 0x79, 0xd7, 0xc4, 0xe9, 0x23, 0x43, 0x9d, 0xb8, 0xcb, 0x78, 0x08, 
  0x32, 0xf1, 0xec, 0x84, 0x80, 0x1e, 0xb9, 0x29, 0x12, 0x0c, 0x29, 0xcc, 0x9c, 0xd0, 0x10, 
  0xa7, 0xd6, 0x8a, 0xe9, 0xf6, 0xfa, 0x8d, 0x7e, 0x95, 0x2e, 0x57, 0xcf, 0x8e, 0x38, 0x6b, 
  0x35, 0xf0, 0xbc, 0xa6, 0x4e, 0x13, 0x7b, 0x41, 0x19, 0x15, 0x5d, 0x99, 0xbd, 0x22, 0x40, 
  0x6a, 0x07, 0x2d, 0xd5, 0xd6, 0xff, 0x1d, 0x7b, 0xa6, 0xc4, 0xaa, 0x77, 0x44, 0x78, 0x2f, 
  0x55, 0x9f, 0x7d, 0x53, 0xf0, 0x2b, 0x2b, 0xba, 0x36, 0xc2, 0xf8, 0x6d, 0xf0, 0x2b, 0xbb, 
  0x6b, 0x97, 0x05, 0xb4, 0x4a, 0xc2, 0x86, 0x62, 0xb8, 0x76, 0xe7, 0xbb, 0xdf, 0x9c, 0x5a, 
  0x70, 0x19, 0x95, 0x59, 0x15, 0xcf, 0xa6, 0xa9, 0x7a, 0x24, 0x4c, 0xc6, 0x65, 0xb9, 0xda, 
  0x17, 0x6f, 0x2b, 0x55, 0x07, 0x32, 0x72, 0xd1, 0xee, 0x9c, 0x3a, 0x51, 0x98, 0x36, 0x37, 
  0xf8, 0x61, 0xfc, 0x91, 0xbc, 0xcb, 0x34, 0xd8, 0x43, 0xa0, 0x7a, 0xea, 0xc4, 0x8a, 0x64, 
  0x4d, 0xe0, 0x03, 0x93, 0xfb, 0xb4, 0xd8, 0x11, 0x21, 0x11, 0x66, 0x97, 0xb9, 0xba, 0x81, 
  0x29, 0xc2, 0x8f, 0x8c, 0x14, 0x18, 0x22, 0x94, 0xc4, 0xb0, 0xf1, 0x10, 0xc4, 0x8b, 0x5d, 
  0x8d, 0x7f, 0x14, 0xaf, 0x46, 0x19, 0x36, 0xa4, 0x36, 0x22, 0x18, 0x18, 0xe3, 0xab, 0x2c, 
  0x91, 0x03, 0xf7, 0xc5, 0xf5, 0xf5, 0x59, 0xc2, 0xd2, 0xf7, 0xc7, 0x64, 0x54, 0x76, 0xfb, 
  0x71, 0x70, 0xe8, 0xb2, 0x44, 0xa1, 0x2d, 0x59, 0x17, 0x02, 0xd6, 0x6f, 0x7a, 0xeb, 0xe0, 
  0x53, 0x81, 0xf6, 0x5e, 0x7f, 0x37, 0xd4, 0x52, 0x13, 0x04, 0x44, 0xd5, 0xc8, 0xd3, 0xdd, 
  0x6f, 0xd5, 0xfb, 0x71, 0x20, 0xe3, 0x0d, 0x0c, 0x47, 0x25, 0xa1, 0x41, 0xd2, 0xc7, 0xe5, 
  0xc9, 0xd9, 0x27, 0xa5, 0x38, 0xe4, 0x30, 0xbb, 0x86, 0x07, 0x84, 0xef, 0x24, 0x9f, 0xf9, 
  0x52, 0x74, 0xd2, 0x50, 0x73, 0xc4, 0x27, 0x73, 0x3b, 0x8d, 0x9c, 0xa6, 0xf6, 0x4b, 0x25, 
  0x91, 0xc5, 0x9e, 0x1e, 0xb2, 0x78, 0x0c, 0x23, 0x80, 0xdd, 0xa3, 0x21, 0xf5, 0xa9, 0x9e, 
  0x00, 0x16, 0x19, 0xbc, 0xd9, 0x55, 0x09, 0x90, 0xa2, 0xc6, 0xef, 0x3d, 0xf8, 0x72, 0x66, 
  0x2f, 0xdc, 0x3a, 0xf6, 0x4f, 0xfd, 0x59, 0x30, 0xe2, 0x27, 0xcc, 0xfb, 0x55, 0x09, 0x71, 
  0x41, 0xe1, 0x21, 0xa1, 0xa1, 0xc0, 0xe3, 0x25, 0xa9, 0xd0, 0x22, 0xc6, 0xef, 0x5c, 0x1b, 
  0xb4, 0xea, 0x56, 0x2e, 0xbf, 0xfc, 0x5b, 0x34, 0xcb, 0x14, 0x8b, 0x94, 0xaa, 0xb7, 0xec, 
  0x5a, 0x36, 0xcf, 0x1c, 0xba, 0xf6, 0x4d, 0xdb, 0x35, 0xf3 };

void delay_us_adns(u16 time)
{    
  u16 i=0;  
  while(time--)
  {
    i=6;  //尹工用的17 
    while(i--) ;    
  }
}
void delay_ms_adns(u16 time)
{    
  //u16 i=0;  
  /*
  while(time--)
  {
  i=72790;  //尹工用的18000
  while(i--) ;    
}
  */
  while(time--)
  {
    delay_us_adns(1000);
  }
}


void ADNS9200_Init(void)
{
  u8 lift_data;
  unsigned char spi_array[10];
  // Gpio_Int_Init(); 
  ADNS9200_SPI_Init();
  //performStartup(); 
  delay_ms_adns(100);
  //initComplete=9;
  ADNS9800_check_sequence();
  ADNS9800_power_up_sequence();
  ANDS9800_SROM_load_sequence();
  //	ADNS9800_load_resolution();
  
  lift_data = spi_hw_read_sensor(ADNS9800_LIFT_DETECTION_THR_ADDR); //default at 0x10
  
  spi_array[0] = spi_hw_read_sensor(ADNS9800_MOTION_ADDR);
  spi_array[1] = spi_hw_read_sensor(ADNS9800_LASER_CTRL0_ADDR);
  spi_array[2] = spi_hw_read_sensor(ADNS9800_LASER_CTRL1_ADDR);
  spi_array[3] = spi_hw_read_sensor(ADNS9800_LP_CFG0_ADDR);
  spi_array[4] = spi_hw_read_sensor(ADNS9800_LP_CFG1_ADDR);
  delay_us_adns(1);	
 // Time_Init();
  
  
  
}

/*  using the board of zhanqian
void ADNS9200_SPI_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //??AFIO??
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //??JTAG??  	

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	//PA15 NSS引脚  JP4 5脚
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化指定IO
GPIO_SetBits(GPIOA,GPIO_Pin_15);//上拉

SPI1_Init();   //初始化SPI2
ADNS9200_CS=1;  //MPU9250片选取消
}
*/

void ADNS9200_SPI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  //NCS inital
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
  GPIO_SetBits(GPIOB,GPIO_Pin_12);				
  
  
  SPI2_Init();   
  
  SPI_Cmd(SPI2,DISABLE);  
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
  SPI_InitStructure.SPI_CRCPolynomial = 7;	
  SPI_Init(SPI2, &SPI_InitStructure); 
  
  SPI_Cmd(SPI2,ENABLE);
  ADNS9200_CS=1;  
  
}


void Gpio_Int_Init_adns9800(void)
{
  
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  
  /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  /* Configure PA.00 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  /* Connect EXTI0 Line to PA.00 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

u8 spi_hw_read_sensor(u8 reg_addr)
{
  u8 data;
  ADNS9200_CS=0;
  delay_us_adns(6);
  Write_Read_Spi_Byte(reg_addr & 0x7f);
  delay_us_adns(100);
  data = Write_Read_Spi_Byte(0xff);
  delay_us_adns(120);
  ADNS9200_CS=1;
  //delay_us_adns(19);
  return data;
}

void spi_hw_write_sensor(u8 reg_addr, u8 data)
{	
  
  ADNS9200_CS=0;
  delay_us_adns(6);
  //send adress of the register, with MSBit = 1 to indicate it's a write
  Write_Read_Spi_Byte(reg_addr | 0x80 );
  //sent data
  delay_us_adns(50);
  Write_Read_Spi_Byte(data);
  
  delay_us_adns(30); // tSCLK-NCS for write operation
  ADNS9200_CS=1;
  delay_us_adns(100); // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound 
}




//------------------------------------------------------------------------------------
// Sub Functions 
//------------------------------------------------------------------------------------
void ADNS9800_check_sequence(void)
{
  //--------------------------------------
  // Local VARIABLES
  //--------------------------------------
  unsigned char spi_array[10];	
  //--------------------------------------
  // Local Sequence
  //--------------------------------------
  spi_array[0] = spi_hw_read_sensor(ADNS9800_PRODUCTID_ADDR);			
  spi_array[1] = spi_hw_read_sensor(ADNS9800_REVISIONID_ADDR);
  spi_array[2] = spi_hw_read_sensor(ADNS9800_INVERSE_PRODUCT_ID_ADDR);
  
}

void ADNS9800_power_up_sequence(void)
{
  //--------------------------------------
  // Local VARIABLES
  //--------------------------------------
  unsigned char spi_array[10];
  //--------------------------------------
  // Local Sequence
  //--------------------------------------
  spi_hw_write_sensor(ADNS9800_POWER_UP_RESET_ADDR, ADNS9800_POWER_UP_RESET);
  delay_ms_adns(50);
  spi_array[0] = spi_hw_read_sensor(ADNS9800_MOTION_ADDR);
  spi_array[1] = spi_hw_read_sensor(ADNS9800_DELTAX_L_ADDR);
  spi_array[2] = spi_hw_read_sensor(ADNS9800_DELTAX_H_ADDR);
  spi_array[3] = spi_hw_read_sensor(ADNS9800_DELTAY_L_ADDR);
  spi_array[4] = spi_hw_read_sensor(ADNS9800_DELTAY_H_ADDR);
  
}

void ANDS9800_SROM_load_sequence(void)
{
  //--------------------------------------
  // Local VARIABLES
  //--------------------------------------
  unsigned char temp;	
  //unsigned char spi_temp;
  //--------------------------------------
  // Local Sequence
  //--------------------------------------
  
  
  ANDS9800_SROM_Download();
  delay_ms_adns(1);		
  temp = spi_hw_read_sensor(0x2A);
  ADNS9800_SROM_Check();
  ADNS9800_laser_power_enable_sequence();
  
}


void ANDS9800_SROM_Download(void)
{
  unsigned int temp_int;
  
  spi_hw_write_sensor(ADNS9800_CONFIGURATION_IV_ADDR, ADNS9800_SROM_SIZE_3_0K); 	// Select 3k SROM size
  
  delay_ms_adns(1);	
  spi_hw_write_sensor(ADNS9800_SROM_ENABLE_ADDR, 0x1D);
  
  delay_ms_adns(10);																// Wait 1 frame period
  
  spi_hw_write_sensor(ADNS9800_SROM_ENABLE_ADDR, 0x18);
  delay_us_adns(120);
  
  //NCS = 0;	
  ADNS9200_CS=0;
  delay_us_adns(10);
  Write_Read_Spi_Byte(ADNS9800_SROM_LOAD_BURST_ADDR | 0x80);
  
  
  delay_ms_adns(10);
  
  for(temp_int = 0; temp_int < 3070; temp_int++)
  {	
    
    Write_Read_Spi_Byte(firmware_data[temp_int]);
    delay_us_adns(100);
  }
  
  
  //delay_us_adns(200);
  //NCS = 1;
  ADNS9200_CS=1;
}


unsigned char ADNS9800_SROM_Check(void)
{
  unsigned char spi_array[10];
  
  spi_array[0] = spi_hw_read_sensor(ADNS9800_SROM_ID_ADDR);					// Check SROM version
  delay_us_adns(10);
  spi_array[1] = spi_hw_read_sensor(ADNS9800_MOTION_ADDR);					// Check Fault
  delay_us_adns(10);
  if((spi_array[1] & ADNS9800_MOTION_FAULT) == ADNS9800_MOTION_FAULT)
  {
    
    return 0;
  }
  
  
  spi_hw_write_sensor(ADNS9800_SROM_ENABLE_ADDR, 0x15);						// Check CRC Test
  
  
  delay_ms_adns(50);															// Wait 1 frame period
  
  spi_array[2] = spi_hw_read_sensor(ADNS9800_DATA_OUT_LOWER_ADDR);			
  
  delay_us_adns(10);
  
  spi_array[3] = spi_hw_read_sensor(ADNS9800_DATA_OUT_UPPER_ADDR);			
  delay_us_adns(10);
  
  if((spi_array[2] != 0xEF) || (spi_array[3] != 0xBE))
  {
    
    return 0;
  }
  
  spi_hw_write_sensor(ADNS9800_OBSERVATION_ADDR, 0x00);						// Clear Observation Register
  
  delay_us_adns(1);
  
  spi_array[4] = spi_hw_read_sensor(ADNS9800_OBSERVATION_ADDR);				// Check if SROM is running
  
  
  if((spi_array[4] & 0x40) == 0)
  {
    return 0;
  }
  
  return 1;
}


void ADNS9800_laser_power_enable_sequence(void)
{
  //--------------------------------------
  // Local VARIABLES
  //--------------------------------------
  unsigned char temp;	
  
  //--------------------------------------
  // Local Sequence
  //--------------------------------------
  
  temp = spi_hw_read_sensor(ADNS9800_LASER_CTRL0_ADDR);
  spi_hw_write_sensor(ADNS9800_LASER_CTRL0_ADDR, (temp & 0xFE));				// Enable Laser Power
  
}

void Read_ADNS9800(void)
{
  read_sensor_motion_burst();	// read motion burst register
  count_x.w += motion_x.w;	// motion accumulate
  count_y.w += motion_y.w;		
  //  printf("X:%d  Y:%d\n", motion_x.w, motion_y.w);	
}

void UpdateADNS9800(uint8_t* pDesArr)
{	
  //	read_sensor_motion_burst();	// read motion burst register
  //	count_x.w += motion_x.w;	// motion accumulate
  //	count_y.w += motion_y.w;		
  // printf("X:%d  Y:%d\n",count_x.w,count_y.w);	
  pDesArr[20]=count_x.b[1];
  pDesArr[21]=count_x.b[0];
  pDesArr[22]=count_y.b[1];
  pDesArr[23]=count_y.b[0];
  //delay_ms_adns(20);   //2ms polling
}


void Update_ADNS9800_Value(uint8_t* pDesArr,uint8_t* pDesLength)
{	
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = count_x.b[1];  
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4]  = count_x.b[0];
  
    *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = count_y.b[1];
  *pDesLength = *pDesLength+1;
  pDesArr[*pDesLength+4] = count_y.b[0];
  //change the vaild data length
  pDesArr[4]=*pDesLength;
}

void read_sensor_motion_burst(void)
{		
  
  u8 temp;
  ADNS9200_CS=0;
  delay_us_adns(6);
  
  Write_Read_Spi_Byte(ADNS9800_MOTION_BURST_ADDR);	//send address to sensor before start spi_read
  delay_us_adns(100);
  
  ///// start motion burst (hardware SPI)/////
  temp 			= Write_Read_Spi_Byte(0xff); //bit 0
  temp			= Write_Read_Spi_Byte(0xff); //bit 1
  motion_x.b[0] = Write_Read_Spi_Byte(0xff); //bit 2
  motion_x.b[1] = Write_Read_Spi_Byte(0xff); //bit 3
  motion_y.b[0] = Write_Read_Spi_Byte(0xff); //bit 4
  motion_y.b[1] = Write_Read_Spi_Byte(0xff); //bit 5
  ///// end motion burst /////
  
  //NCS = 1;
  ADNS9200_CS = 1;  // manual NCS high				
}

/*
void Time_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
  NVIC_InitTypeDef NVIC_InitStructure; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  
  TIM_TimeBaseStructure.TIM_Period = 1799;
  TIM_TimeBaseStructure.TIM_Prescaler = 399;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
   
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  TIM_Cmd(TIM2, ENABLE); 
}
*/

