#include "stareditor.h"
#include "QMouseEvent"

StarEditor::StarEditor(QWidget* parent) : QWidget(parent) {
    editable = true;
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void StarEditor::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QPalette* palette = new QPalette();
    QColor hColor(244,217,66);
    palette->setColor(QPalette::Highlight, hColor);
    palette->setColor(QPalette::Foreground, Qt::black);

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
    editable = !editable;
}

QSize StarEditor::sizeHint() const{
    return myStarRating.sizeHint();
}

void StarEditor::mouseReleaseEvent(QMouseEvent * /* event */) {
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
}

void StarEditor::setStarPosition(int pos){
    myStarRating.setStarCount(pos);
    update();
}

void StarEditor::setStarRatingPaintingScaleFactor(int value){
    myStarRating.setPaintingScaleFactor(value);
    update();
}
