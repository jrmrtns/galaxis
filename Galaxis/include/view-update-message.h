//
// Created by jmartens on 05.11.2023.
//

#ifndef GALAXIS_VIEW_UPDATE_MESSAGE_H
#define GALAXIS_VIEW_UPDATE_MESSAGE_H

enum ViewUpdateMessage {
    Coordinates,
    SearchResult,
    ShipCount,
    Active,
    Hint,
    Connected,
    GameOver,
    MenuItemChanged,
    Started,
    Searching,
    Round
};

#endif //GALAXIS_VIEW_UPDATE_MESSAGE_H
