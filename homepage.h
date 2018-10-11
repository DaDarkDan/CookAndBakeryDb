#ifndef HOMEPAGE_H
#define HOMEPAGE_H

class MainWindow;

class HomePage
{
public:
    HomePage(MainWindow* mw) : mw(mw) {}

private:
    MainWindow* mw;
};

#endif // HOMEPAGE_H
