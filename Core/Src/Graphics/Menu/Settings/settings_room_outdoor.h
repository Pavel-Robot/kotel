//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_ROOM_OUTDOOR_H
#define BOILER_GRAPHICS_SETTINGS_ROOM_OUTDOOR_H

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String roomOutdoorMenuElement1Name = {16, "THERMOSTAT NO/NC"};
String roomOutdoorMenuElement2Name = {7, "OUTDOOR"};
String roomOutdoorMenuElement3Name = {4, "EXIT"};

MenuElement roomOutdoorMenuElement1 = {true, NULL, NULL, NULL, &roomOutdoorMenuElement1Name};
MenuElement roomOutdoorMenuElement2 = {true, NULL, NULL, NULL, &roomOutdoorMenuElement2Name};
MenuElement roomOutdoorMenuElement3 = {true, NULL, NULL, ExitSubmenu, &roomOutdoorMenuElement3Name};

MenuList roomOutdoorMenuList = {&settingsMenuList, CLOSE, 0, 3, &roomOutdoorMenuElement1, &roomOutdoorMenuElement2,
                         &roomOutdoorMenuElement3};
#endif //BOILER_GRAPHICS_SETTINGS_ROOM_OUTDOOR_H
