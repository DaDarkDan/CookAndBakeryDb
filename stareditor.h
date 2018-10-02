#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>
#include "starrating.h"
#include "QSize"


class StarEditor : public QWidget
{
    Q_OBJECT

public:
    StarEditor(QWidget *parent = 0);

    virtual QSize sizeHint() const override;
    void setStarRating(const StarRating &starRating) {
        myStarRating = starRating;
    }
    StarRating starRating() { return myStarRating; }

signals:
    void editingFinished();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int starAtPosition(int x);

    StarRating myStarRating;
};

#endif // STAREDITOR_H
