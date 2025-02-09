#include "mainwindow.h"

#include <QtCore/QTimer>
#include <QtGui/QBitmap>
#include <QtGui/QPixmap>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSplashScreen>

#include "yacasrequest.h"

#include "preferences.h"

void addSplashScreen(MainWindow* widget);

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    try {
        app.setApplicationName("yacas-gui");
        app.setApplicationDisplayName("Yacas GUI");
        app.setOrganizationName("yacas.org");
        app.setOrganizationDomain("yacas.org");

#ifndef _WIN32
        app.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

        qRegisterMetaType<YacasRequest::State>("YacasRequest::State");

        Preferences prefs(app);

        MainWindow* widget = new MainWindow(prefs);

#ifndef __APPLE__
        addSplashScreen(widget);
#endif

        widget->show();

        return app.exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Yacas GUI Error", e.what());
        return 1;
    } catch (...) {
        QMessageBox::critical(nullptr, "Yacas GUI Error", "Unknown error");
        return 1;
    }

    return 0;
}

void addSplashScreen(MainWindow* widget)
{
    QPixmap si(":/resources/img/splash.png");
    QSplashScreen ss(widget, si, Qt::WindowStaysOnTopHint);
    ss.setMask(si.mask());
    ss.showFullScreen();
    QTimer::singleShot(3000, &ss, SLOT(close()));
}
