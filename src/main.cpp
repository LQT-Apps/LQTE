#include "main_window.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication *app = new QApplication(argc, argv);

    MainWindow *main = new MainWindow();
    main->show();

    return app->exec();
}
