//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Frontend.h"
#include <QApplication>
#include <QWindow>
#include <Windows.h>
int main(int argc, char *argv[]) {
  FreeConsole();
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //HiDPI pixmaps
  qputenv("QT_SCALE_FACTOR", "1");

  QApplication app(argc, argv);

  QPalette palette = qApp->palette();
  palette.setColor(QPalette::Window, QColor("#272b2e"));
  qApp->setPalette(palette);


  Login window;
  window.resize(800, 600);
  //window.setFixedSize(QSize(800, 600));

  window.setWindowTitle("PresetShare");
  window.show();
  //FreeConsole();
  return app.exec();
}
