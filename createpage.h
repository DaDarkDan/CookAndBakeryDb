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

class CreatePage
{
public:
    CreatePage(MainWindow* mw, QComboBox* createCategoryComboBox, QComboBox* createAddIngredientWeightTypeComboBox,
               QWidget* createAddedIngredientsScrollViewContents, QWidget* createAddedKeywordsScrollViewContents,
               QFrame* createRatingStarFrame, QCheckBox* createFavouriteCheckBox);

    void setup();

    QString on_createSaveBtn_clicked(QTextEdit* createNameTxtEdit, vector<QWidget*> addedIngredientFrameList,
                                  vector<QWidget*> addedKeywordFrameList, QTextEdit* createNotesTxtEdit,
                                  QLabel* createImgInputLabel, QCheckBox* createFavouriteCheckBox);
    QString on_createAddIngredientBtn_clicked(QTextEdit* createIngredientNameTxtEdit, QTextEdit* createIngredientAmountTxtEdit,
                                           vector<QWidget*> addedIngredientFrameList);
    QString on_createAddKeywordBtn_clicked(QTextEdit* createAddedKeywordsTxtEdit, vector<QWidget*> addedKeywordFrameList);

    void on_addedFrameDeleteButton_clicked(QPushButton* button, vector<QWidget*> addedIngredientFrameList, vector<QWidget*> addedKeywordFrameList);

    void on_uploadImgBtn_clicked();

private:
    MainWindow* mw;

    QComboBox* createCategoryComboBox;
    QComboBox* createAddIngredientWeightTypeComboBox;
    QWidget* createAddedIngredientsScrollViewContents;
    QWidget* createAddedKeywordsScrollViewContents;
    QFrame* createRatingStarFrame;
    QCheckBox* createFavouriteCheckBox;
};

#endif // CREATEPAGE_H
