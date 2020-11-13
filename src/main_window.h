#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "iohandler.h"
#include <QDialog>
#include <QTextEdit>

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    QString origText;
    QDialog *di;
    QTextEdit *edit;
    IOHandler *io = new IOHandler();

    void show(int argc, char **argv);
    void errMsg(std::string text);
public slots:
    void writeFile();
    void loadFile();
    void saveAs();
    void newFile();
    void indicateUnsaved();
};

#endif
