#pragma once

#include <QDir>

namespace LambdaSnail::QtExtensions
{
    /**
     * An extended QDir class.
     */
    class LSDir : public QDir
    {
    public:
        /**
         * Joins two paths in an OS-independent manner.
         */
        [[nodiscard]] static QString joinPath(QString const& path1, QString const& path2);
    };
}
