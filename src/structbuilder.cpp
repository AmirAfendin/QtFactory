#include "structbuilder.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

StructBuilder::StructBuilder(QObject *parent) : QObject(parent)
{
    m_hasOtherTypes = false;
}

bool StructBuilder::build(const QString &templatePath, const QString &resultPath, const QString &structName,
                          const QStringList &memberList)
{
    QString templateString = getStructTemplateString(templatePath);
    if (templateString.isEmpty())
        return false;

    fillName(templateString, structName);
    fillMembers(templateString, memberList);
    fillIncludes(templateString);
    fillConstructors(templateString, memberList);

    return saveResult(resultPath, templateString);
}

QString StructBuilder::getStructTemplateString(const QString &templatePath)
{
    QFile structTemplate(templatePath);
    if (!structTemplate.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical() << "Couldn't open:" << templatePath;
        return "";
    }

    QString structTemplateString = structTemplate.readAll();
    structTemplate.close();
    return structTemplateString;
}

void StructBuilder::fillName(QString &outTemplateString, const QString &structName)
{
    outTemplateString.replace("[qtf_structName_allCapital]", QString(structName).toUpper());
    outTemplateString.replace("[qtf_structName]", structName);

}

void StructBuilder::fillIncludes(QString &outTemplateString)
{
    if (m_hasOtherTypes)
        outTemplateString.replace("[qtf_includes]", "#include <QObject>");
    else
        outTemplateString.replace("[qtf_includes]", "");
}

void StructBuilder::fillConstructors(QString &outTemplateString, const QStringList &memberList)
{

    int argumentLineCount = 1, assignmentLineCount = 1;
    QString argumentList, assignmentList, argument, assignment;
    QString indent("          ");

    for (int i = 0; i < memberList.count(); ++i) {
        assignment = argument = memberList.at(i);
        argument = argument.replace(argument.lastIndexOf(' ') + 1, 1, argument.at(argument.lastIndexOf(' ') + 1).toUpper());
        argument = argument.insert(argument.lastIndexOf(' ') + 1, "in");
        if (QString(argumentList + argument).trimmed().count() > MAX_CONSTRUCTOR_ARG_LENGTH * argumentLineCount) {
            argumentList += "\n" + indent + argument + ", ";
            ++argumentLineCount;
        } else {
            argumentList += argument + ", ";
        }

        assignment.remove(0, assignment.lastIndexOf(' ') + 1);
        assignment += '(' + argument.remove(0, argument.lastIndexOf(' ') + 1)  + ')';

        if (QString(assignmentList + assignment).trimmed().count() > MAX_CONSTRUCTOR_ARG_LENGTH * assignmentLineCount) {
            assignmentList += "\n" + indent + assignment + ", ";
            ++assignmentLineCount;
        } else {
            assignmentList += assignment + ", ";
        }
    }

    argumentList.chop(2); //remove last ", "
    assignmentList.chop(2);

    outTemplateString.replace("[qtf_constructorList]", argumentList);
    outTemplateString.replace("[qtf_constructorAssignmentList]", assignmentList);
}

void StructBuilder::fillMembers(QString &outTemplateString, const QStringList &memberList)
{
    m_hasOtherTypes = false;

    QString memberString, member;
    QString indent("    ");

    for (int i = 0; i < memberList.count(); ++i) {
        member = memberList.at(i);
        memberString += member + (member.contains(';') ? "" : ";");

        if (i != memberList.count() - 1)
            memberString += '\n' + indent;

        if (!m_hasOtherTypes) {
            if (member.at(0).isUpper())
                m_hasOtherTypes = true;
        }
    }

    outTemplateString.replace("[qtf_members]", memberString);
}

bool StructBuilder::saveResult(const QString &resultPath, const QString &templateString)
{
    QFile structResult(resultPath);
    if (!structResult.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        qCritical() << "Couldn't open:" << resultPath;
        return false;
    }

    QTextStream out(&structResult);
    out << templateString;

    structResult.close();
    return true;
}
