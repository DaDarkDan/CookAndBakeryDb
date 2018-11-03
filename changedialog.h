#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QDialog>

class Recipe;
class MainWindow;
class ClickableLabel;
class PathPixmap;

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDialog(MainWindow* mw, Recipe* recipe, QWidget *parent = nullptr);
    ~ChangeDialog();

private slots:
    void on_createChangeBtn_clicked();

    void on_createImageLeft_clicked();

    void on_createImgRight_clicked();

    void on_createRatingCheckBox_stateChanged(int arg1);

    void on_createAddIngredientBtn_clicked();

    void on_createAddKeywordBtn_clicked();

    void on_discardChangesButton_clicked();

    void on_createUploadImgBtn_clicked();

    void on_createDeleteImg_clicked();

private:
    Ui::ChangeDialog *ui;

    QList<QWidget*> disableList;
    Recipe* recipe;
    MainWindow* mw;
    int currentRecipePixmapIndex;
    QList<PathPixmap> currentPixmapList;
    ClickableLabel* createImgInputLabel;

    void setup();
    void saveChanges();

    QList<QWidget*> addedIngredientFrameList, addedKeywordFrameList;
};

#endif // CHANGEDIALOG_H
