#ifndef STRUCTBUILDER_H
#define STRUCTBUILDER_H

#include <QObject>
#define MAX_CONSTRUCTOR_ARG_LENGTH 60

class StructBuilder : public QObject
{
    Q_OBJECT
public:
    explicit StructBuilder(QObject *parent = nullptr);

    bool build(const QString &templatePath, const QString &resultPath,
               const QString &structName, const QStringList &memberList);
private:
    bool m_hasOtherTypes;

    QString getStructTemplateString(const QString &templatePath);
    void fillName(QString &outTemplateString, const QString &structName);
    void fillIncludes(QString &outTemplateString);
    void fillConstructors(QString &outTemplateString, const QStringList &memberList);
    void fillMembers(QString &outTemplateString, const QStringList &memberList);
    bool saveResult(const QString &resultPath, const QString &templateString);
};

#endif // STRUCTBUILDER_H
