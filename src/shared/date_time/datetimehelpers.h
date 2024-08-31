#pragma once

#include <QDate>

namespace LambdaSnail::Juno::dateTime
{
    /**
     * Performs some validation and attempts to construct a QDate representing the given date. If the resulting QDate is not
     * valid, the function will attempt to adjust the day of the month. Thus calling this with e.g., (2020, 2, 30) will yield
     * a QDate representing (2020, 2, 29).
     *
     * If called with too small or too large parameters (e.g., negative years or d > 31) an assert will be triggered.
     * If all attempts to construct a valid QDate fail, a default constructed QDate will be returned.
     */
    inline QDate constructValidDate(int32_t y, int32_t m, int32_t d)
    {
        assert(m > 0, m <= 12);
        assert(d > 0, d <= 31);
        assert(y > 0);

        QDate const date(y, m, d);
        if(date.isValid())
        {
            return date;
        }

        QDate const month(y, m, 1);
        if(d > month.daysInMonth())
        {
            return { y, m, month.daysInMonth() };
        }

        return {};
    }
}
