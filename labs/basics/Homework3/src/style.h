#pragma once
#include <QString>

namespace styles {
    const QString MAIN_STYLE = R"(
        QMainWindow { background-color: #FFFFFF; }
        QLabel { font-size: 18px; color: #4B4B4B; }
        QPushButton { 
            background-color: #58CC02; border: none; border-bottom: 4px solid #46A302;
            color: white; padding: 12px; border-radius: 12px; font-weight: bold; font-size: 16px;
        }
        QPushButton#secondary { background-color: #1CB0F6; border-bottom: 4px solid #1899D6; }
        QPushButton:pressed { border-bottom: 0px; margin-top: 4px; }
        QLineEdit { border: 2px solid #E5E5E5; border-radius: 12px; padding: 10px; font-size: 16px; }
    )";

    const QString TOAST_CORRECT = "background-color: #D7FFB8; color: #58CC02; border: 2px solid #58CC02; border-radius: 15px; font-weight: bold; font-size: 20px;";
    const QString TOAST_WRONG = "background-color: #FFDFE0; color: #EA2B2B; border: 2px solid #EA2B2B; border-radius: 15px; font-weight: bold; font-size: 20px;";
}