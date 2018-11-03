#include "pathpixmap.h"

QString PathPixmap::getPath() const{
    return path;
}

QPixmap PathPixmap::getPixmap() const{
    return pixmap;
}

void PathPixmap::setPath(const QString &value)
{
    path = value;
}

