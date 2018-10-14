#ifndef STARRATING_H
#define STARRATING_H

#include "QPainter"

class StarRating
{
public:
    enum EditMode { Editable, ReadOnly };

    explicit StarRating(int starCount = 1, int maxStarCount = 10);

    void paint(QPainter *painter, const QRect &rect,
               const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;
    int starCount() const { return myStarCount; }
    int maxStarCount() const { return myMaxStarCount; }
    void setStarCount(int starCount) { myStarCount = starCount; }
    int getMyStarCount() const;
    void setMaxStarCount(int maxStarCount) { myMaxStarCount = maxStarCount; }

    void setPaintingScaleFactor(int value);

private:
    QPolygonF starPolygon;
    QPolygonF diamondPolygon;
    int myStarCount;
    int myMaxStarCount;

    int PaintingScaleFactor = 20;
};

Q_DECLARE_METATYPE(StarRating)

#endif // STARRATING_H
