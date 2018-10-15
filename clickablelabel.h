#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include "QLabel"

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    ~ClickableLabel() override;

    QString getFullPath() const;
    void setFullPath(const QString &value);

signals:
    void clicked(QString fullPath);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    QString fullPath;
};

#endif // CLICKABLELABEL_H
