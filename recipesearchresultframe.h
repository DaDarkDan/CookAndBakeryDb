#ifndef RECIPESEARCHRESULTFRAME_H
#define RECIPESEARCHRESULTFRAME_H

#include <QWidget>
#include "recipe.h"

class QHBoxLayout;
class QGridLayout;
class QLabel;
class QFrame;

class RecipeSearchResultFrame : public QWidget
{
    Q_OBJECT

public:
    RecipeSearchResultFrame(Recipe recipe, QHBoxLayout* starLayout, int index, QWidget* parent = nullptr);

    QFrame *getFrame() const;

signals:
    void on_mousePressed(const QPixmap& pixmap, const QString& path);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Recipe recipe;
    QFrame* frame;

    QHBoxLayout* horLayout;
    QGridLayout* gridLayout;

    QLabel* createIndex(int index);
    QLabel* createTitle();
    QLabel* createDate();
    QLabel* createIngAmount();
    QFrame* createStarRating(QHBoxLayout* starLayout);
    QFrame* createImage();
};

#endif // RECIPESEARCHRESULTFRAME_H
