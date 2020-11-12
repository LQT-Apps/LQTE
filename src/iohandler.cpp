#include "iohandler.h"
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <vector>

std::vector<QString> IOHandler::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    QFile mFile(fileName);
    mFile.open(QIODevice::ReadWrite);
    QTextStream file(&mFile);
    QString content = file.readAll();
    return {content, fileName};
}
QString IOHandler::saveFile(std::string content, std::string curFileName ) {
    QString fileName;
    if (curFileName == "")
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    else fileName = QString::fromStdString(curFileName);
    QFile file(fileName);
    if (fileName == "") return fileName;

    if (!file.open(QIODevice::WriteOnly))
        return "Error: couldn't open for writing";
    file.write(content.c_str());
    return fileName;
}
QString IOHandler::saveFileAs(std::string content) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));;
    return saveFile(content, fileName.toStdString());
}
QString IOHandler::newFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("New File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (fileName == "") return fileName;
    if (!file.open(QIODevice::WriteOnly))
        return "Error: couldn't open for writing";
    return fileName;
}
