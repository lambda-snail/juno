#include "dir.h"

QString LambdaSnail::QtExtensions::LSDir::joinPath(QString const &path1, QString const &path2)
{
    return cleanPath(path1 + separator() + path2);
}
