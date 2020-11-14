/**
 ******************************************************************************
 * @file    convert.cpp
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
 * @brief   Program body of convert
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

#include "convert.hpp"

namespace Convert
{
  char *ToString(int intValue)
  {
    static char string[3];
    sprintf(string, "%d", intValue);
    return string;
  }
} // namespace Convert

/*********************************END OF FILE**********************************/
