#include "modelbuilder.h"
#include <QFile>

ModelBuilder::ModelBuilder(QObject *parent) : QObject(parent)
{

}

bool ModelBuilder::build(const QString &templatePath, const QString &resultPath, const QString &structName, const QStringList &memberList)
{
    QString templateString = getModelTemplateString(templatePath);
}

QString ModelBuilder::getModelTemplateString(const QString &templatePath)
{
    QFile modelTemplate(templatePath);
    if (!modelTemplate.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical() << "Couldn't open:" << templatePath;
        return "";
    }

    QString structTemplateString = modelTemplate.readAll();
    modelTemplate.close();
    return structTemplateString;
}

void ModelBuilder::fillName(QString &outTemplateString, const QString &modelName)
{

}
