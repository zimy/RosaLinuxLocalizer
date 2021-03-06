#include <QDebug>
#include <QGraphicsWebView>
#include <QWebFrame>
#include <QProcess>
#include <QFileDialog>

#include "bridge.h"

bool useStubs = false;

Bridge::Bridge(QWidget *parent) : Html5ApplicationViewer(parent) {
    QObject::connect(webView()->page()->mainFrame(),
                     SIGNAL(javaScriptWindowObjectCleared()), SLOT(addToJavaScript()));
}

void Bridge::addToJavaScript() {
    webView()->page()->mainFrame()->addToJavaScriptWindowObject("Bridge", this);
}

/* ======= Начало: работа с API библиотеки ======= */

QString scriptPath = "/home/zimy/Documents/HotProjects/RosaLinuxLocalizer/src/__init__.py";


QString Bridge::getTranslation(const QString &text) {
    qDebug() << "getTranslation: " << text;
    if (useStubs) { return text; }

    QString res = runPythonScript(scriptPath, "translate", text);
    return res;
}

QString Bridge::importPackages(const QString &jsonData) {
    qDebug() << "importPackages: " << jsonData;
    if (useStubs) { return "[{\"project_id\":91836,\"rpm\":\"terminology-0.9.0-1-rosa2014.1.x86_64.rpm\",\"package_name\":\"terminology\",\"git\":\"https://abf.io/import/terminology.git\",\"desktop_files\":[{\"path\":\"usr/share/applications/terminology.desktop\",\"strings\":[{\"variable_name\":\"Name\",\"value\":{\"en\":\"Terminology\",\"ru\":\"Терминология\"}},{\"variable_name\":\"Comment\",\"value\":{\"en\":\"Terminal emulator\",\"ru\":\"Эмулятор терминала\"}}]}],\"status\":\"4\"},{\"project_id\":378627,\"rpm\":\"pidgin-1.0-rosa2014.1.i586.rpm\",\"package_name\":\"pidgin\",\"git\":\"https://abf.io/import/pidgin.git\",\"desktop_files\":[{\"path\":\"usr/share/applications/pidgin.desktop\",\"strings\":[{\"variable_name\":\"Name\",\"value\":{\"en\":\"Pidgin\"}},{\"variable_name\":\"Comment\",\"value\":{\"en\":\"Another comment about this package.\"}}]},{\"path\":\"usr/share/desc/info.desktop\",\"strings\":[{\"variable_name\":\"Comment\",\"value\":{\"en\":\"Console application for educational purposes.\"}}]}],\"status\":\"2\"}]"; }

    QString res = runPythonScript(scriptPath, "import", jsonData);
    return res;
}

QString Bridge::getSettings() {
    qDebug() << "getSettings";
    if (useStubs) { return "{\"yandex_api_key\":\"webuy23dn289fydvbh8912e9vcydbu2e3rgvbudio2ecbudnvucbdowbu\",\"abf_projects_group\":\"import\",\"abf_login\":\"login\",\"abf_password\":\"password\",\"branches\":[{\"name\":\"import_cooker\",\"active\":false,\"first\":true},{\"name\":\"import_mandriva\",\"active\":false,\"first\":false},{\"name\":\"master\",\"active\":false,\"first\":false},{\"name\":\"red3\",\"active\":false,\"first\":false},{\"name\":\"rosa2012.1\",\"active\":false,\"first\":false},{\"name\":\"rosa2012lts\",\"active\":false,\"first\":false},{\"name\":\"rosa2014.1\",\"active\":true,\"first\":false}],\"variables\":[{\"name\":\"Name\",\"last\":false},{\"name\":\"Comment\",\"last\":true}]}"; }
    QString res = runPythonScript(scriptPath, "getSettings", "\"\"");
    return res;
}

QString Bridge::saveSettings(const QString &jsonData) {
    qDebug() << "saveSettings: " << jsonData;
    if (useStubs) { return jsonData; }

    QString res = runPythonScript(scriptPath, "saveSettings", jsonData);
    return res;
}

QString Bridge::saveTranslations(const QString &jsonData) {
    qDebug() << "saveTranslations: " << jsonData;
    if (useStubs) { return jsonData; }

    QString res = runPythonScript(scriptPath, "saveTranslations", jsonData);
    return res;
}

QString Bridge::runPythonScript(const QString &path, const QString &command, const QString &data) {
    QProcess p;
    QStringList params;

    params << path + " " << "{\"command\":\""+ command +"\", \"args\":"+ data +"}";
    qDebug() << "params: " << params;
    p.start("python3", params);
    p.waitForFinished(-1);

    QString p_stdout = p.readAll();
    return p_stdout;
}

/* ======= Конец: работа с API библиотеки ======= */

QStringList Bridge::openFiles(int mode) {
    qDebug() << "openFiles" << mode;
    QStringList res;
    switch (mode) {
        case 1: {//обычные .rpm-файлы
            QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Импорт файлов rpm..."),"",tr("RPM Files (*.mp3);;Any files (*.*)"));
            qDebug() << fileNames;
            res = fileNames;
            break;
        }
        case 2: {//директория
            //QFileDialog dialog;
            //dialog.setFileMode(QFileDialog::Directory);
            //dialog.setOption(QFileDialog::ShowDirsOnly);
            //QString dirName = dialog.getOpenFileName(this, tr("Выберите директорию..."),"",tr("(*.*)"));
            QString dirName = QFileDialog::getExistingDirectory(this, tr("Выберите директорию..."),
                                                     "",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
            qDebug() << dirName;
            res.append(dirName);
            break;
        }
        case 3: {//текстовый файл
            QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл..."),"",tr("Yaml file (*.yaml);;Text files (*.txt);;Any files (*.*)"));
            qDebug() << fileName;
            res.append(fileName);
            break;
        }
    }

    return res;
}

























