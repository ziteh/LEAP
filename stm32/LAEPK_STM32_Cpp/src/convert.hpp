/**
 ******************************************************************************
 * @file    convert.hpp
 * @author  ZiTe (honmonoh@gmail.com)
 * @version V1.0
 * @date    14-November-2020
 * @brief   Header for convert.cpp module
 ******************************************************************************
 * @attention
 *
 * None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef __CONVERT_HPP
#define __CONVERT_HPP

#include <string>
#include <sstream>

extern "C"
{
#include <stdio.h>
}

namespace Convert
{
  char *ToString(int intValue);
}

#endif /* __CONVERT_HPP */

/*********************************END OF FILE**********************************/