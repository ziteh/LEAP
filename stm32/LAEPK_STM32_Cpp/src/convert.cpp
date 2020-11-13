/**
 ******************************************************************************
 * @file    convert.cpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
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
