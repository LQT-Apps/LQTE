#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QWidget>

class IOHandler : public QWidget
{
    Q_OBJECT
public:
    QString curFileName;

    std::vector<QString> loadFile(QString filename = "");
    QString saveFile(QString content);
    QString saveFileAs(QString content);
    QString newFile();
};

#endif
