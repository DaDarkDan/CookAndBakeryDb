#ifndef RECIPESEARCHRESULTFRAME_H
#define RECIPESEARCHRESULTFRAME_H

#include <QWidget>
#include "recipe.h"

class QHBoxLayout;
class QGridLayout;
class QLabel;
class QFrame;
class QPushButton;
class ParameterButton;
class MainWindow;
class ClickableLabel;

class RecipeSearchResultFrame : public QWidget
{
    Q_OBJECT

public:
    RecipeSearchResultFrame(MainWindow* mw, Recipe* recipe, QHBoxLayout* starLayout, int index, QWidget* parent = nullptr);

    QFrame *getFrame() const;

    ParameterButton *getDeleteButton() const;

    QLabel *getHeart() const;

signals:
    void on_mousePressed(Recipe* recipe);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Recipe* recipe;
    QFrame* frame;
    MainWindow* mw;

    QHBoxLayout* horLayout;
    QGridLayout* gridLayout;

    QLabel* createIndex(int index);
    ClickableLabel* createInspectLabel();
    QLabel* createTitle();
    QLabel* createFavouriteLabel();
    QLabel* createDate();
    QLabel* createCategoryIngredientAmountLabel();
    QFrame* createStarRating(QHBoxLayout* starLayout);
    QFrame* createImage();
    ParameterButton* createDeleteButton();

    ParameterButton* deleteButton;
    ClickableLabel* heart;
};

#endif // RECIPESEARCHRESULTFRAME_H
