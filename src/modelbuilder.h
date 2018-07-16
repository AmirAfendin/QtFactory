#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <QObject>

class ModelBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ModelBuilder(QObject *parent = nullptr);

    bool build(const QString &templatePath, const QString &resultPath,
               const QString &structName, const QStringList &memberList);

private:
    QString getModelTemplateString(const QString &templatePath);
    void fillName(QString &outTemplateString, const QString &modelName);
};

#endif // MODELBUILDER_H
