#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>
#include "starrating.h"
#include "QSize"


class StarEditor : public QWidget
{
    Q_OBJECT

public:
    StarEditor(QWidget* parent = nullptr);

    virtual QSize sizeHint() const override;
    void setStarRating(const StarRating &starRating) {
        myStarRating = starRating;
    }
    StarRating starRating() { return myStarRating; }

    void setEditable(bool value);
    void setStarPosition(int pos);
    void setStarRatingPaintingScaleFactor(int value);

signals:
    void editingFinished();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int starAtPosition(int x);

    bool editable;

    StarRating myStarRating;
};

#endif // STAREDITOR_H
