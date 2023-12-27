//
// Created by user on 22.09.2022.
//

#ifndef TEXT_LAYER_H
#define TEXT_LAYER_H

String roomStatusText = {2, "OK"};
String alarmText = {7, "WARNING"};
String outdoorTemperatureText = {4, "-40c"};
String waterPipeTemperatureText = {3, "65c"};
String gasPipeTemperatureText = {4, "200c"};
String boilerTemperatureText = {4, "65c"};
String gearCurrentText = {4, "200A"};
String gearTemperatureText = {3, "30c"};
TextObject roomStatusTextObject = {30, 100, &Font24, colorGreen, 1, &roomStatusText};
TextObject alarmTextObject = {30, 160, &Font24, colorRed, 1, &alarmText};
TextObject outdoorTemperatureTextObject = {30, 18, &Font24, colorBlue, 1, &outdoorTemperatureText};
TextObject waterPipeTemperatureTextObject = {210, 18, &Font24, colorOrange, 1, &waterPipeTemperatureText};
TextObject gasPipeTemperatureTextObject = {GasPipeStartX + 30, 18, &Font24, colorOrange, 1, &gasPipeTemperatureText};
TextObject boilerTemperatureTextObject = {BoilerStartX + 41, 150, &Font24, colorGreen, 1, &boilerTemperatureText};
TextObject gearCurrentTextObject = {30, 280, &Font24, colorSun, 1, &gearCurrentText};
TextObject gearTemperatureTextObject = {130, 280, &Font24, colorOrange, 1, &gearTemperatureText};
GraphicObject textOnScreen = {TEXT, 8, &roomStatusTextObject, &alarmTextObject, &outdoorTemperatureTextObject,
                              &waterPipeTemperatureTextObject, &gasPipeTemperatureTextObject,
                              &boilerTemperatureTextObject, &gearCurrentTextObject, &gearTemperatureTextObject};
GraphicLayer textLayer = {0, 0, 480, 320, 1, &textOnScreen};

#endif //TEXT_LAYER_H
