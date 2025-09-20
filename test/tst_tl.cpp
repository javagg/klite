#include <QCoreApplication>
#include <QtTest>

#include "tlClassRegistry.h"
#include "../main/other.h"
#include "layLayoutView.h"

// add necessary includes here

class tl_Tests : public QObject
{
    Q_OBJECT

public:
    tl_Tests();
    ~tl_Tests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

tl_Tests::tl_Tests() {}

tl_Tests::~tl_Tests() {}

void tl_Tests::initTestCase() {}

void tl_Tests::cleanupTestCase() {}

void tl_Tests::test_case1() {

    tl::RegisteredClass<db::StreamFormatDeclaration> format_decl (new GDS2FormatDeclaration (), 0, "GDS2");
    auto path = extractResourceToTemp(":/t10.gds", "demo.gds");

    tl::InputStream stream (path.toStdString());
    db::Reader reader (stream);

    db::Layout l;
    db::LoadLayoutOptions option;
    db::LayerMap new_lmap = reader.read (l, option);
    qInfo() << "new_lmap:" << new_lmap.to_string();


    lay::CellView cv;
    db::Manager manger;

    lay::LayoutHandle *handle = new lay::LayoutHandle (new db::Layout (false, &manger), path.toStdString());
    qInfo() << "LayoutHandle:" << handle;
    cv.set (handle);

}

QTEST_MAIN(tl_Tests)

#include "tst_tl.moc"
