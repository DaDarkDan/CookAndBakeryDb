#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QString fullPath, QWidget *parent) : QLabel(parent), fullPath(fullPath){

}

ClickableLabel::~ClickableLabel(){}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked(fullPath);
}
