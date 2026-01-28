//
// Created by mikkel on 1/28/2026.
//

#ifndef UNA_POSITION_H
#define UNA_POSITION_H

typedef struct Location {
    Location(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Location* Add(int x, int y) {
        return new Location(this->x + x, this->y + y);
    }

    int x;
    int y;
} Location;

#endif //UNA_POSITION_H