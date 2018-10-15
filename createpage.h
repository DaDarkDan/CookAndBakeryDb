#include <vector>

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

class CreatePage
{
public:
    CreatePage(MainWindow* mw, QTextEdit* createNameTxtEdit, QComboBox* createCategoryComboBox,
               QComboBox* createAddIngredientWeightTypeComboBox, QWidget* createAddedIngredientsScrollViewContents,
               QWidget* createAddedKeywordsScrollViewContents, QFrame* createRatingStarFrame,
               QCheckBox* createFavouriteCheckBox, QCheckBox* createRatingCheckBox,
               vector<QWidget*> addedIngredientFrameList, vector<QWidget*> addedKeywordFrameList,
               QTextEdit* createNotesTxtEdit, QLabel* createImgInputLabel);

    void setup();

    QString on_createSaveBtn_clicked();
    QString on_createAddIngredientBtn_clicked(QTextEdit* createIngredientNameTxtEdit, QTextEdit* createIngredientAmountTxtEdit);
    QString on_createAddKeywordBtn_clicked(QTextEdit* createAddedKeywordsTxtEdit);

    void on_addedFrameDeleteButton_clicked(QPushButton* button);

    void on_uploadImgBtn_clicked();

    void on_createRatingCheckBox_stateChanged(int arg1);

    void on_createResetBtn_clicked();

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
    vector<QWidget*> addedIngredientFrameList, addedKeywordFrameList;
    QTextEdit* createNotesTxtEdit;
    QLabel* createImgInputLabel;
};

#endif // CREATEPAGE_H
