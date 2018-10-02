#include "stareditor.h"
#include "QMouseEvent"

StarEditor::StarEditor(QWidget *parent) : QWidget(parent) {
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
    int star = starAtPosition(event->x());

    if (star != myStarRating.starCount() && star != -1) {
        myStarRating.setStarCount(star);
        update();
    }
}

QSize StarEditor::sizeHint() const{
    return myStarRating.sizeHint();
}

void StarEditor::mouseReleaseEvent(QMouseEvent * /* event */) {
    emit editingFinished();
}

int StarEditor::starAtPosition(int x) {
    int star = (x / (myStarRating.sizeHint().width()
                     / myStarRating.maxStarCount())) + 1;
    if (star <= 0 || star > myStarRating.maxStarCount())
        return -1;

    return star;
}
