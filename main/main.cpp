#include <QMainWindow>
#include "layLayoutView.h"
#include "dbManager.h"
#include "layLayoutCanvas.h"
#include "layLayoutViewBase.h"

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "dbInit.h"
#include "tlColor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.resize(400, 200);


    auto widget = new QWidget(&w);
    auto layout = new QVBoxLayout(widget);
    auto button = new QPushButton("Load");

    db::init();
    auto p = new QFrame();
    auto manager = new db::Manager();
    auto base = new lay::LayoutViewBase(manager, false, nullptr);
    base->load_layout("/Users/alex/t10.gds", false);
    auto canvas = new lay::LayoutCanvas(base);
    canvas->set_colors(tl::Color("black"), tl::Color("black"), tl::Color("red"));
    canvas->init_ui(p);

    layout->addWidget(button);

    layout->addWidget(p);
    w.setCentralWidget(widget);
    w.show();
    return a.exec();
}
