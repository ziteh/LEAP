/**
 ******************************************************************************
 * @file    convert.hpp
 * @author  Huang, Tzu-Fu
 *          National Formosa University
 *          Department of Electronic Engineering
 *          Intelligent Robot System Laboratory
 * @version V1.0.0
 * @date    31-August-2020
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