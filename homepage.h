#ifndef HOMEPAGE_H
#define HOMEPAGE_H

class MainWindow;
class QLineEdit;

class HomePage
{
public:
    HomePage(MainWindow* mw, QLineEdit* homeDirectoryLineEdit);

    void on_homeSetDirectoryLabel_clicked();

private:
    MainWindow* mw;

    QLineEdit* homeDirectoryLineEdit;
};

#endif // HOMEPAGE_H
