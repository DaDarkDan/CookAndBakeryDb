#include "homepage.h"
#include "recipemanager.h"
#include "iomanager.h"
#include "mainwindow.h"

#include "QStandardPaths"
#include "QFileDialog"
#include "QLineEdit"
#include "QSettings"
#include "QCoreApplication"

HomePage::HomePage(MainWindow* mw, QLineEdit *homeDirectoryLineEdit){
    this->mw = mw;
    this->homeDirectoryLineEdit = homeDirectoryLineEdit;
    homeDirectoryLineEdit->setText(mw->getRm()->getIoManager()->getDirectoryPath());
    homeDirectoryLineEdit->setDisabled(true);
}

void HomePage::on_homeSetDirectoryLabel_clicked(){
    QString path = QFileDialog::getExistingDirectory(mw, QObject::tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    mw->setRm(new RecipeManager(path));
    homeDirectoryLineEdit->setText(path);

    QSettings settings;
    settings.setValue("savePath", path);
}




