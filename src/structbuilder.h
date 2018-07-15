#ifndef STRUCTBUILDER_H
#define STRUCTBUILDER_H

#include <QObject>

class StructBuilder : public QObject
{
    Q_OBJECT
public:
    explicit StructBuilder(QObject *parent = nullptr);

    bool build(QString templatePath, QString resultPath);
private:
    bool m_hasOtherTypes;

    QString getStructTemplateString(QString templatePath);
    void fillName(QString &outTemplateString);
    void fillIncludes(QString &outTemplateString);
    void fillConstructors(QString &outTemplateString);
    void fillMembers(QString &outTemplateString);
    bool saveResult(QString resultPath, QString templateString);
};

#endif // STRUCTBUILDER_H
