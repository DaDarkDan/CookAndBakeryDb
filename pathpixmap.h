#ifndef PATHPIXMAP_H
#define PATHPIXMAP_H

#include "QString"
#include "QPixmap"

class PathPixmap
{
public:
    PathPixmap(QString path, QPixmap pixmap) : path(path), pixmap(pixmap) {}

    QString getPath() const;
    QPixmap getPixmap() const;

    void setPath(const QString &value);

private:
    QString path;
    QPixmap pixmap;
};

#endif // PATHPIXMAP_H
