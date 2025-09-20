#include <QMainWindow>
#include "layLayoutViewBase.h"
#include "layLayoutView.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTemporaryFile>
#include <QTemporaryDir>
#include "tlClassRegistry.h"
#include "dbStream.h"
#include "dbReader.h"
#include "other.h"

int main(int argc, char *argv[])
{
    tl::RegisteredClass<db::StreamFormatDeclaration> format_decl (new GDS2FormatDeclaration (), 0, "GDS2");
    auto path = extractResourceToTemp(":/t10.gds", "demo.gds");

    tl::InputStream stream (path.toStdString());
    db::Reader reader (stream);

    db::Layout l;
    db::LoadLayoutOptions option;
    db::LayerMap new_lmap = reader.read (l, option);
    qInfo() << "new_lmap:" << new_lmap.to_string();

    QApplication a(argc, argv);
    QMainWindow w;
    w.resize(1200, 800);

    auto widget = new QWidget(&w);
    auto layout = new QVBoxLayout(widget);
    auto button = new QPushButton("Load");

    auto lw = new lay::LayoutViewWidget(nullptr, false, nullptr);
    lw->view()->load_layout(path.toStdString(), false);

    layout->addWidget(button);
    layout->addWidget(lw);
    w.setCentralWidget(widget);
    w.show();
    return a.exec();
}
