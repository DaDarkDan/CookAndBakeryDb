#include <vector>
#include "QList"
#include "pathpixmap.h"

using std::vector;

#ifndef CREATEPAGE_H
#define CREATEPAGE_H



class QTextEdit;
class QComboBox;
class QWidget;
class QFrame;
class QLabel;
class QCheckBox;
class RecipeManager;
class QString;
class QPushButton;
class MainWindow;
class QCheckBox;
class StarEditor;
class QLineEdit;

class CreatePage
{
public:
    CreatePage(MainWindow* mw, QTextEdit* createNameTxtEdit, QComboBox* createCategoryComboBox,
               QComboBox* createAddIngredientWeightTypeComboBox, QWidget* createAddedIngredientsScrollViewContents,
               QWidget* createAddedKeywordsScrollViewContents, QFrame* createRatingStarFrame,
               QCheckBox* createFavouriteCheckBox, QCheckBox* createRatingCheckBox,
               QList<QWidget*> addedIngredientFrameList, QList<QWidget*> addedKeywordFrameList,
               QTextEdit* createNotesTxtEdit, QLabel* createImgInputLabel,
               QLineEdit* createIngredientNameLineEdit, QTextEdit* createIngredientAmountTxtEdit,
               QLineEdit* createAddedKeywordsLineEdit, QLabel* createIngredientIconLabel,
               QLabel* createKeywordIconLabel, QLabel* createImgTitleLabel);

    void setup();

    QString on_createSaveBtn_clicked();
    QString on_createAddIngredientBtn_clicked();
    QString on_createAddKeywordBtn_clicked();

    void on_addedFrameDeleteButton_clicked(QPushButton* button);

    void on_uploadImgBtn_clicked();

    void on_createRatingCheckBox_stateChanged(int arg1);

    void on_createResetBtn_clicked();

    void on_createNameTxtEdit_textChanged();

    void on_createDeleteImg_clicked();

    void on_createImageLeft_clicked();

    void on_createImgRight_clicked();

    QTextEdit *getCreateNameTxtEdit() const;

private:
    MainWindow* mw;

    StarEditor* starEditor = nullptr;

    QTextEdit* createNameTxtEdit;
    QComboBox* createCategoryComboBox;
    QComboBox* createAddIngredientWeightTypeComboBox;
    QWidget* createAddedIngredientsScrollViewContents;
    QWidget* createAddedKeywordsScrollViewContents;
    QFrame* createRatingStarFrame;
    QCheckBox* createFavouriteCheckBox;
    QCheckBox* createRatingCheckBox;
    QList<QWidget*> addedIngredientFrameList, addedKeywordFrameList;
    QTextEdit* createNotesTxtEdit;
    QLabel* createImgInputLabel;
    QLineEdit* createIngredientNameLineEdit;
    QTextEdit* createIngredientAmountTxtEdit;
    QLineEdit* createAddedKeywordsLineEdit;
    QLabel* createIngredientIconLabel, *createKeywordIconLabel, *createImgTitleLabel;

    QList<QPixmap> currentPixmapList;
    int currentPixmapIndex;
};

#endif // CREATEPAGE_H
