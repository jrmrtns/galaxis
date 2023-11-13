//
// Created by jmartens on 05.11.2023.
//

#ifndef GALAXIS_VIEW_UPDATE_MESSAGE_H
#define GALAXIS_VIEW_UPDATE_MESSAGE_H

#include "WString.h"
#include "subject.h"
#include <cstdio>

enum ViewUpdateMessage {
    Coordinates, SearchResult, ShipCount, ParticipantShipCount, Active, Hint, Connected, GameOver, MenuItemChanged, Started
};

#endif //GALAXIS_VIEW_UPDATE_MESSAGE_H
