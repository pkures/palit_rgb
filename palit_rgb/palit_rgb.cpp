#include <Windows.h>
#include "..\nvapi\nvapi.h"

#include <iostream>
#include "palit_rgb.h"


void sendcmd(NV_U8 reg, NV_U8 data, NV_PHYSICAL_GPU_HANDLE  hGPU);

int main(int argc, char* argv[])
{
  NV_STATUS ret = NvAPI_Initialize();

  if (ret != 0)
  {
    return -1;
  }

/* Enumerate physical GPU handles
 Note: i was testing GPU enumeration to identify the Palit GPU in systems with multiple GPUs, but have no time to finish it now

  NV_PHYSICAL_GPU_HANDLE hGPU_a[64] = { 0 }; // handle to GPUs
  NV_S32 gpuCount = 0;

  ret = NvAPI_EnumPhysicalGPUs(hGPU_a, &gpuCount);
  if (ret != 0)
  {
    printf("NvAPI_EnumPhysicalGPUs() failed with status %d\n", ret);
    printf("\n");
    printf("I2C Read/Write brightness test FAILED");
    return 1;
  }
  printf("Total number of GPU's = %u\n", gpuCount);

  NV_SHORT_STRING cardName;

  for (int i = 0; i < gpuCount; i++)
  {
    NvAPI_GPU_GetFullName(hGPU_a[i], cardName);
    
    NV_U32 deviceId;
    NV_U32 subsysId;
    NV_U32 extDeviceId;
    NvAPI_GPU_GetPCIIdentifiers(hGPU_a[i], &deviceId, &subsysId, 0, &extDeviceId);

    printf("%s %08x %08x\n", cardName, extDeviceId, subsysId);
  }

  if (gpuCount > 1)
  {
  }
*/

  if (argc > 1)
  {
    unsigned int color = 0;

    sscanf_s(argv[1], "%08x",&color);

    sendcmd(0xE0, 0x00, hGPU_a[0]); // solid color ?
    sendcmd(0x60, 0x01, hGPU_a[0]); // 0/1 OFF/ON ... cycling colors ? cycling speed ?

   
    sendcmd(0x6C, (color >> 16) & 0xff, hGPU_a[0]); // R
    sendcmd(0x6D, (color >> 8) & 0xff, hGPU_a[0]);  // G
    sendcmd(0x6E, color & 0xff, hGPU_a[0]);         // B
    
    sendcmd(0x6F, 0x64, hGPU_a[0]);                // intensity
  }
  else
  {
    sendcmd(0xE0, 0x80, hGPU_a[0]); // 0x80 == sync ?
  }

  return 0;
}
void sendcmd(NV_U8 reg, NV_U8 data, NV_PHYSICAL_GPU_HANDLE  hGPU)
{

  NV_I2C_INFO_V3 i2c;

  i2c.is_ddc_port = 0;
  i2c.i2c_dev_address = 0x49 << 1;

  i2c.reg_addr_size = 0x01;
  i2c.i2c_reg_address = &reg;

  i2c.size = 1;
  i2c.data = &data;

  i2c.port_id = 1;
  i2c.is_port_id_set = 1;



  i2c.i2c_speed = 0xffff;
  i2c.i2c_speed_khz = NV_I2C_SPEED::NVAPI_I2C_SPEED_DEFAULT;

  //CalculateI2cChecksum(i2c);
  
  unsigned int unknown = 0;

  NV_STATUS ret = NvAPI_I2CWriteEx(hGPU, &i2c, &unknown);
}




/* set RGB
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x00
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x60 Size: 0x01 Data: 0x01
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6C Size: 0x01 Data: 0xFF R
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6D Size: 0x01 Data: 0x00 G
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6E Size: 0x01 Data: 0x00 B
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6F Size: 0x01 Data: 0x64


NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x00
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x60 Size: 0x01 Data: 0x01
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6C Size: 0x01 Data: 0xFF
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6D Size: 0x01 Data: 0x26
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6E Size: 0x01 Data: 0x00
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6F Size: 0x01 Data: 0x64
*/

/*
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80
*/


  /*
  * cycle colors 0x03 is medium speed 0x00 is fastest
  * 
  * 0x01 0x00 0x03 0x1F
  *      0x01 - flip direction                                                   speed
  NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x04 Data: 0x01 0x00 0x03 0x1F
  */

  /*
  * strobe
  NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0x45 0xC8 0x00 0x64 0x05

  yellow slower strobe

  NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0xC8 0xBB 0x08 0x64 0x05

  white                                                                                       R    G    B
  NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0xFF 0xFF 0xFF 0x64 0x05
  */