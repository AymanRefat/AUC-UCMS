#include "utils.h"
#include "qdir.h"
#include <QCoreApplication>

QStringList parseCsvLine(const QString &line) {
    QStringList fields;
    QString field;
    bool inQuotes = false;

    for (const QChar &c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;  // Toggle quote status
        } else if (c == ',' && !inQuotes) {
            // Field separator outside quotes
            fields.append(field.trimmed());
            field.clear();
        } else {
            field.append(c);  // Add character to field
        }
    }
    fields.append(field.trimmed());  // Add the last field
    return fields;
}


QString getCurrentDir() {
    QDir current_dir = QDir(QCoreApplication::applicationDirPath());

    current_dir.cdUp();
    current_dir.cdUp();
    current_dir.cdUp();
#ifdef Q_OS_APPLE
    current_dir.cdUp();
    current_dir.cdUp();
#endif
    return current_dir.absolutePath();
}
