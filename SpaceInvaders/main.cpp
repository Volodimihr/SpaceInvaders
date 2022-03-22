#include <game.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // создание Qt приложения

    Game win;
    win.setWindowTitle("Space Invaders");
    win.show(); // вывод виджета

    return a.exec();
}
