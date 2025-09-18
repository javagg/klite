#include <QMainWindow>
#include "dbManager.h"
#include "layLayoutViewBase.h"
#include "layLayoutView.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "dbInit.h"
#include "dbLayout.h"
#include <QFile>
#include <QTemporaryDir>


QString extractResourceToTemp(const QString &resourcePath, const QString &fileName)
{
    // 1. 从资源文件读取数据
    QFile resourceFile(resourcePath);
    if (!resourceFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open resource:" << resourcePath;
        return QString();
    }
    QByteArray data = resourceFile.readAll();
    resourceFile.close();

    // 2. 获取临时目录路径（推荐使用 QTemporaryDir 管理生命周期）
    static QTemporaryDir tempDir; // static 确保临时目录在程序运行期间不被删除
    if (!tempDir.isValid()) {
        qWarning() << "Failed to create temporary directory";
        return QString();
    }

    // 3. 构造目标文件路径
    QString tempFilePath = tempDir.path() + "/" + fileName;

    // 4. 写入临时文件
    QFile tempFile(tempFilePath);
    if (!tempFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to create temporary file:" << tempFilePath;
        return QString();
    }
    qint64 bytesWritten = tempFile.write(data);
    tempFile.close();

    if (bytesWritten != data.size()) {
        qWarning() << "Failed to write all data to temporary file";
        return QString();
    }

    qDebug() << "Resource extracted to:" << tempFilePath;
    return tempFilePath;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.resize(1200, 800);

    auto widget = new QWidget(&w);
    auto layout = new QVBoxLayout(widget);
    auto button = new QPushButton("Load");

    db::init();
    auto lw = new lay::LayoutViewWidget(nullptr, false, nullptr);
    auto path = extractResourceToTemp(":/t10.gds", "demo.gds");
    lw->view()->load_layout(path.toStdString(), false);
    layout->addWidget(button);
    layout->addWidget(lw);
    w.setCentralWidget(widget);
    w.show();
    return a.exec();
}
