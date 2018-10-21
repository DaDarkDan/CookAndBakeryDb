#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include "QLabel"

class Recipe;

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    ~ClickableLabel() override;

    QString getFullPath() const;
    void setFullPath(const QString &value);

    Recipe *getRecipe() const;
    void setRecipe(Recipe *value);

signals:
    void clicked(QString fullPath, Recipe* recipe = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    QString fullPath;
    Recipe* recipe;
};

#endif // CLICKABLELABEL_H
