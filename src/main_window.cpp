#include "main_window.h"

#include <QGridLayout>
#include <QMenuBar>
#include <QDebug>
#include <iostream>

void MainWindow::show()
{
    this->di = new QDialog();
    di->setWindowTitle("Lightweight Qt Text Editor");

    this->edit = new QTextEdit(di);
    connect(edit, &QTextEdit::textChanged, this, &MainWindow::indicateUnsaved);

    QGridLayout *layout = new QGridLayout(this);
    QMenuBar *bar = new QMenuBar(this);
    QMenu *fileMenu = bar->addMenu(tr("&File"));

    QAction* newAct = new QAction(QIcon::fromTheme("document-new"), tr("&New..."), this);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    newAct->setStatusTip(tr("Create a new file."));
    newAct->setShortcut(QKeySequence(tr("Ctrl+N")));

    fileMenu->addAction(newAct);

    QAction* openAct = new QAction(QIcon::fromTheme("document-open"), tr("&Open..."), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::loadFile);

    openAct->setStatusTip(tr("Open an existing file."));
    openAct->setShortcut(QKeySequence(tr("Ctrl+O")));

    fileMenu->addAction(openAct);

    QAction* saveAct = new QAction(QIcon::fromTheme("document-save"), tr("&Save..."), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::writeFile);

    saveAct->setStatusTip(tr("Save current file."));
    saveAct->setShortcut(QKeySequence(tr("Ctrl+S")));

    fileMenu->addAction(saveAct);

    QAction* saveAsAct = new QAction(QIcon::fromTheme("document-save-as"), tr("&Save As..."));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    saveAsAct->setStatusTip(tr("Save current file to a new location."));
    saveAsAct->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));

    fileMenu->addAction(saveAsAct);

    layout->addWidget(edit);
    layout->setMenuBar(bar);
    di->setLayout(layout);

    di->setGeometry(di->x(), di->y(), 500, 500);

    di->show();
}

void MainWindow::errMsg(QString text) {
    QMessageBox err;
    err.setText(tr(text.toStdString().c_str()));
    err.setStandardButtons(QMessageBox::Ok);
    err.exec();
}

void MainWindow::writeFile() {
    IOHandler *io = new IOHandler();

    QString write = io->saveFile(edit->toPlainText().toStdString(), di->windowTitle().toStdString());
    if (write == tr("Error: couldn't open for writing")) errMsg("Could not open file for writing. Check permissions and try again.");
    else if (write == "") errMsg("No location specified.");
    else di->setWindowTitle(write);
    this->origText = edit->toPlainText();
    emit edit->textChanged();
}
void MainWindow::loadFile() {
    IOHandler *io = new IOHandler();
    QMessageBox buttonBox;
    buttonBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    buttonBox.setText(tr("Are you SURE you want to close the current file?"));
    buttonBox.setDefaultButton(QMessageBox::Cancel);

    if (edit->toPlainText().isEmpty() || buttonBox.exec() == QMessageBox::Ok) {
        std::vector<QString> load = io->loadFile();
        edit->setText(load[0]);
        di->setWindowTitle(load[1]);
        this->origText = load[0];
    }
}
void MainWindow::saveAs() {
    IOHandler *io = new IOHandler();
    QString save = io->saveFileAs(edit->toPlainText().toStdString());
    if (save == tr("Error: couldn't open for writing")) errMsg(tr("Could not open file for writing. Check permissions and try again."));
    else if (save == "") errMsg(tr("No location specified, not saving."));
    else di->setWindowTitle(save);
    this->origText = edit->toPlainText();
    emit edit->textChanged();
}
void MainWindow::newFile() {
    IOHandler *io = new IOHandler();
    QMessageBox buttonBox;
    buttonBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    buttonBox.setText(tr("Are you SURE you want to close the current file?"));
    buttonBox.setDefaultButton(QMessageBox::Cancel);

    if (edit->toPlainText().isEmpty() || buttonBox.exec() == QMessageBox::Ok) {
        QString newF = io->newFile();
        if (newF == tr("Error: couldn't open for writing")) errMsg(tr("Could not open file in location for writing. Check permissions and try again."));
        else if (newF == "") errMsg(tr("No location specified, not creating."));
        else edit->setText("");
        di->setWindowTitle(newF);
        this->origText = "";
    }
}

void MainWindow::indicateUnsaved() {
    if (edit->toPlainText() == origText) di->setWindowTitle(di->windowTitle().left(di->windowTitle().length() - 2));
    else if (!di->windowTitle().endsWith(" *")) di->setWindowTitle(di->windowTitle() + " *");
}
