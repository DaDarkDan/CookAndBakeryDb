#include "stareditor.h"
#include "QMouseEvent"

StarEditor::StarEditor(QWidget* parent, bool editable) : QWidget(parent), editable(editable){
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void StarEditor::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QPalette* palette = new QPalette();
    if (editable && this->isEnabled()){
        palette->setColor(QPalette::Highlight, QColor(255, 145, 35)); //orange
    } else if (!editable && this->isEnabled()){
        palette->setColor(QPalette::Highlight, QColor(244,217,66)); //yellow
    } else if (!editable && !this->isEnabled()){
        palette->setColor(QPalette::Highlight, QColor(196, 194, 178)); //grey
    } else if (editable && !this->isEnabled()){
        palette->setColor(QPalette::Highlight, QColor(244,217,66)); //yellow
    }
    myStarRating.paint(&painter, rect(), *palette, StarRating::Editable);
}

void StarEditor::mouseMoveEvent(QMouseEvent *event) {
    if (!editable){
        return;
    }
    int star = starAtPosition(event->x());

    if (star != myStarRating.starCount() && star != -1) {
        myStarRating.setStarCount(star);
        update();
    }
}

void StarEditor::mousePressEvent(QMouseEvent* /* event */){
}

QSize StarEditor::sizeHint() const{
    return myStarRating.sizeHint();
}

void StarEditor::mouseReleaseEvent(QMouseEvent * /* event */) {
    editable = !editable;
    this->update();
    emit editingFinished();
}

int StarEditor::starAtPosition(int x) {    
    int star = (x / (myStarRating.sizeHint().width() / myStarRating.maxStarCount())) + 1;
    if (star <= 0 || star > myStarRating.maxStarCount())
        return -1;

    return star;
}

void StarEditor::setEditable(bool value){
    editable = value;
    update();
}

void StarEditor::setStarPosition(int pos){
    myStarRating.setStarCount(pos);
    update();
}

void StarEditor::setStarRatingPaintingScaleFactor(int value){
    myStarRating.setPaintingScaleFactor(value);
    update();
}
