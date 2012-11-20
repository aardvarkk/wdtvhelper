#ifndef CONTENTRATING_H
#define CONTENTRATING_H

#include <QString>

class ContentRating
{
public:

    enum Rating {
        TV_Y,
        TV_Y7,
        TV_Y7_FV,
        TV_G,
        TV_PG,
        TV_14,
        TV_MA
    };

    static QString toString(ContentRating::Rating rating)
    {
        switch (rating)
        {
        case TV_Y: return "TV-Y";
        case TV_Y7: return "TV-Y7";
        case TV_Y7_FV: return "TV-Y7-FV";
        case TV_G: return "TV-G";
        case TV_PG: return "TV-PG";
        case TV_14: return "TV-14";
        case TV_MA: return "TV-MA";
        default: return "";
        }
    }
};

#endif // CONTENTRATING_H
