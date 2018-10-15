#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent){}

ClickableLabel::~ClickableLabel(){}

void ClickableLabel::mousePressEvent(QMouseEvent* /*event*/) {
    emit clicked(fullPath);
}

QString ClickableLabel::getFullPath() const {
    return fullPath;
}

void ClickableLabel::setFullPath(const QString &value){
    fullPath = value;
}
