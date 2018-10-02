#include "QStyledItemDelegate"

#ifndef STARDELEGATE_H
#define STARDELEGATE_H


class StarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    StarDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private slots:
    void commitAndCloseEditor();
};

#endif // STARDELEGATE_H
