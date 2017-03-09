/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2017  KDE neon <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "testy.h"
#include "imagewriter_debug.h"

#include <KAuth>
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    Testy testy(argc, argv);
    return 0;
}

Testy::Testy(int argc, char *argv[]) {
    QApplication app(argc, argv);
    m_button = new QPushButton("hello");
    m_button->show();
    connect(m_button, SIGNAL(clicked()), this, SLOT(run()));
    app.exec();    
}

void Testy::run() {
    qCDebug(IMAGEWRITER_LOG) << "run";
    KAuth::Action action(QLatin1String("org.kde.imagewriter.writefile"));
    action.setHelperId("org.kde.imagewriter");
    //KAuth::Action action(QLatin1String("org.kde.kcontrol.kcmplymouth.install"));
    //action.setHelperId("org.kde.kcontrol.kcmplymouth");
    //action.setArguments(helperargs);
    QVariantMap helperargs;
    helperargs[QStringLiteral("filename")] = "bar";
    action.setArguments(helperargs);
    
    KAuth::ExecuteJob *job = action.execute();
    bool execSuccess = job->exec();
    if (!execSuccess) {
        QMessageBox::information(m_button, "Error", QString("KAuth returned an error code: %1 string: %2").arg(job->error()).arg(job->errorString()));
    } else {
        qCDebug(IMAGEWRITER_LOG) << "all good";
        QVariantMap data = job->data();
        qCDebug(IMAGEWRITER_LOG) << "returned: " << data["contents"].value<QString>();
        qCDebug(IMAGEWRITER_LOG) << "returned: " << data.value("contents").value<QString>();
        QString contents = job->data()["contents"].toString();
        qCDebug(IMAGEWRITER_LOG) << "returned: " << contents;
    }
}