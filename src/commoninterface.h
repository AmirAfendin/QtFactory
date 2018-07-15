#ifndef COMMONINTERFACE_H
#define COMMONINTERFACE_H

#include <QObject>

#include "qqmlhelpers.h"
#include "membermodel.h"

#define TEMPLATE_FILE_STRUCT_H "./templates/struct_h.txt"
#define RESULT_FILE_STRUCT_H "./struct.h"
#define MAX_CONSTRUCTOR_ARG_LENGTH 60


class CommonInterface : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QString, structName)
public:
    explicit CommonInterface(QObject *parent = nullptr);
    MemberModel* memberModel() { return m_memberModel; }

public slots:
    void generateSources();

private:
    MemberModel *m_memberModel;
    bool m_hasOtherTypes;
    void generateStruct();
    QString getStructTemplateString();
    void fillName(QString &outTemplateString);
    void fillIncludes(QString &outTemplateString);
    void fillConstructors(QString &outTemplateString);
    void fillMembers(QString &outTemplateString);
};

#endif // COMMONINTERFACE_H
