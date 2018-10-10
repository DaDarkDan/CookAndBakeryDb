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

class CreatePage
{
public:
    CreatePage(RecipeManager* rm) : rm(rm){}

    void setup(QComboBox* createCategoryComboBox, QComboBox* createAddIngredientWeightTypeComboBox,
               QWidget* createAddedIngredientsScrollViewContents, QWidget* createAddedKeywordsScrollViewContents,
               QFrame* searchRatingStarFrame);

    QString on_createSaveBtn_clicked(QTextEdit* createNameTxtEdit, QComboBox* createCategoryComboBox, vector<QWidget*> addedIngredientFrameList,
                                  vector<QWidget*> addedKeywordFrameList, QFrame* createRatingStarFrame, QTextEdit* createNotesTxtEdit,
                                  QLabel* createImgInputLabel, QCheckBox* createFavouriteCheckBox);
    QString on_createAddIngredientBtn_clicked(MainWindow* mainWindow, QTextEdit* createIngredientNameTxtEdit, QTextEdit* createIngredientAmountTxtEdit, QComboBox* createAddIngredientWeightTypeComboBox,
                                           QWidget* createAddedIngredientsScrollViewContents, vector<QWidget*> addedIngredientFrameList);
    QString on_createAddKeywordBtn_clicked(MainWindow* mainWindow, QTextEdit* createAddedKeywordsTxtEdit, QWidget* createAddedKeywordsScrollViewContents, vector<QWidget*> addedKeywordFrameList);

    void on_addedFrameDeleteButton_clicked(QPushButton* button, vector<QWidget*> addedIngredientFrameList, vector<QWidget*> addedKeywordFrameList);

    void on_uploadImgBtn_clicked();

private:
    RecipeManager* rm;

};

#endif // CREATEPAGE_H
