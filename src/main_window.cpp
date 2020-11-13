#include "main_window.h"

#include <QGridLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>
#include <iostream>

void MainWindow::show(int argc, char **argv)
{
    QGridLayout *layout = new QGridLayout(this);

    this->di = new QDialog();
    di->setWindowTitle("Lightweight Qt Text Editor");
    di->setGeometry(di->x(), di->y(), 500, 500);
    di->setLayout(layout);

    this->edit = new QTextEdit(di);
    connect(edit, &QTextEdit::textChanged, this, &MainWindow::indicateUnsaved);
    layout->addWidget(edit);

    QMenuBar *bar = new QMenuBar(this);
    layout->setMenuBar(bar);

    QMenu *fileMenu = bar->addMenu(tr("&File"));

    fileMenu->addAction(QIcon::fromTheme("document-new"), tr("&New..."), this, &MainWindow::newFile, QKeySequence(tr("Ctrl+N")))
            ->setStatusTip(tr("Create a new file."));

    fileMenu->addAction(QIcon::fromTheme("document-open"), tr("&Open..."), this, &MainWindow::loadFile, QKeySequence(tr("Ctrl+O")))
            ->setStatusTip(tr("Open an existing file."));

    fileMenu->addAction(QIcon::fromTheme("document-save"), tr("&Save..."), this, &MainWindow::writeFile, QKeySequence(tr("Ctrl+S")))
            ->setStatusTip(tr("Save current file."));
    fileMenu->addAction(QIcon::fromTheme("document-save-as"), tr("&Save As..."), this, &MainWindow::saveAs, QKeySequence(tr("Ctrl+Shift+S")))
            ->setStatusTip(tr("Save current file to a new location."));

    QMenu *aboutMenu = bar->addMenu(tr("&About"));

    QMessageBox *aboutBox = new QMessageBox(QMessageBox::NoIcon, tr("About LQTE"), tr("LQTE is a highly simplistic and lightweight text editor written in Qt, intended to be a tiny alternative to other text editors available, sacrificing features for the sake of lightness and simplicity.\nWritten by: swirl (aka sperg/binex)\nProject Repo: https://github.com/LQT-Apps/LQTE\nLQT Apps Project: https://github.com/LQT-Apps\nVersion: 1.1.0"), QMessageBox::Ok);
    aboutBox->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

    aboutMenu->addAction(tr("&About..."), aboutBox, &QMessageBox::show)->setStatusTip(tr("About LQTE"));
    aboutMenu->addAction(tr("&About Qt..."), qApp, &QApplication::aboutQt);

    if (argc > 1) {
        try {
            std::vector<QString> load = io->loadFile(argv[1]);
            edit->setText(load[0]);
            di->setWindowTitle(load[1]);
            this->origText = load[0];
        } catch (...) {
            errMsg("The specified file does not exist, not opening anything.");
        }
    }

    di->show();
}

void MainWindow::errMsg(std::string text) {
    QMessageBox *err = new QMessageBox(QMessageBox::Critical, tr("Message"), tr(text.c_str()), QMessageBox::Ok);
    err->show();
}

void MainWindow::writeFile() {
    QString write;
    try {
        write = io->saveFile(edit->toPlainText());
    } catch (...) {
        return errMsg("Could not open file for writing. Check permissions and try again.");
    }
    if (write == "") return errMsg("No location specified.");

    di->setWindowTitle(write);
    this->origText = edit->toPlainText();
    emit edit->textChanged();
}
void MainWindow::loadFile() {
    std::vector<QString> load;
    try {
        load = io->loadFile();
    } catch (...) {
        return errMsg("Could not open file for reading. Check permissions and try again.");
    }

    if (load[1] == "") return errMsg("No location specified.");

    edit->setText(load[0]);
    di->setWindowTitle(load[1]);
    this->origText = load[0];
}
void MainWindow::saveAs() {
    QString save;
    try {
        save = io->saveFileAs(edit->toPlainText());
    }  catch (...) {
        errMsg("Could not open file for writing. Check permissions and try again.");
    }
    if (save == "") errMsg("No location specified, not saving.");
    else di->setWindowTitle(save);

    this->origText = edit->toPlainText();
    emit edit->textChanged();
}
void MainWindow::newFile() {
    QString newF;
    try {
        newF = io->newFile();
    } catch (...) {
        errMsg("Could not open file in location for writing. Check permissions and try again.");
    }
    if (newF == "") return errMsg("No location specified, not creating.");
    edit->setText("");
    di->setWindowTitle(newF);
    this->origText = "";
}

void MainWindow::indicateUnsaved() {
    if (edit->toPlainText() == origText && di->windowTitle().endsWith(" *")) di->setWindowTitle(di->windowTitle().left(di->windowTitle().length() - 2));
    else if (edit->toPlainText() != origText && !di->windowTitle().endsWith(" *")) di->setWindowTitle(di->windowTitle() + " *");
}
