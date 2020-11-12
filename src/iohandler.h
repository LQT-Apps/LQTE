#include <QWidget>

class IOHandler : public QWidget
{
    Q_OBJECT
public:
    std::vector<QString> loadFile();
    QString saveFile(std::string content, std::string curFileName = "");
    QString saveFileAs(std::string content);
    QString newFile();
};
