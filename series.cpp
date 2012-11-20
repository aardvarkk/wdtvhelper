#include "series.h"

Series::Series()
{
    id = 0;
    airs_dayofweek = Qt::Monday;
    content_rating = ContentRating::TV_MA;
    language = QLocale::English;
    network_id = 0;
    rating = 0;
    rating_count = 0;
    runtime = 0;
    series_id = 0;
    status = Other;
    added_by = 0;
    last_updated = 0;
}
