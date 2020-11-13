#include "iohandler.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <vector>

std::vector<QString> IOHandler::loadFile(QString filename) {
    QString fileName;
    if (filename == "") fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    else fileName = filename;

    if (fileName == "") return {"", ""};

    QFile mFile(fileName);
    if (!mFile.open(QIODevice::ReadOnly))
        throw std::ios_base::failure("Error: couldn't open file for reading");
    QTextStream file(&mFile);
    QString content = file.readAll();
    curFileName = fileName;

    return {content, fileName};
}
QString IOHandler::saveFile(QString content) {
    QString fileName;
    if (curFileName == "")
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    else fileName = curFileName;

    QFile file(fileName);
    if (fileName == "") return fileName;

    if (!file.open(QIODevice::WriteOnly))
        throw std::ios_base::failure("Error: couldn't open for writing");
    this->curFileName = fileName;

    file.write(content.toStdString().c_str());
    return fileName;
}
QString IOHandler::saveFileAs(QString content) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    curFileName = fileName;

    return saveFile(content);
}
QString IOHandler::newFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("New File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (fileName == "") return fileName;
    if (!file.open(QIODevice::WriteOnly))
        throw std::ios_base::failure("Error: couldn't open for writing");

    curFileName = fileName;
    return fileName;
}
