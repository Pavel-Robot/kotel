/*
 * settings_user.h
 *
 *  Created on: 23 авг. 2022 г.
 *      Author: computer
 */

//Файл для задания настроек пользователя

#ifndef SRC_APP_SETTINGS_USER_H_
#define SRC_APP_SETTINGS_USER_H_

#include "settings_default.h"

//#define USER 555
//МОЖЕТ ТУТ СТРУКТУРОЙ ВСЕ НАПИСАТЬ?

Settings mainSettings = {defaultScrewSettings,defaultFanSettings,
                         defaultCentralHeatingSettings,defaultHotWaterSettings,
                         defaultGraphScheduleSettings};

#endif /* SRC_APP_SETTINGS_USER_H_ */
