//
// Created by mikkel on 1/28/2026.
//

#ifndef UNA_DEVTOOLS_H
#define UNA_DEVTOOLS_H
#include "world/world.h"

void Activate_Devtool(World* w);
void Deactivate_Devtool();
bool Is_Devtool_Active();
void Devtool_Tick();

#endif //UNA_DEVTOOLS_H