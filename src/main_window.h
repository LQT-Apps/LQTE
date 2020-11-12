#include "iohandler.h"
#include <QDialog>
#include <QTextEdit>
#include <QMessageBox>

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    QString origText;
    QDialog *di;
    QTextEdit *edit;
    void show();
    void errMsg(QString text);
public slots:
    void writeFile();
    void loadFile();
    void saveAs();
    void newFile();
    void indicateUnsaved();
};
