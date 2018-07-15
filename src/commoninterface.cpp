#include "commoninterface.h"
#include <QFile>
#include <QDebug>

CommonInterface::CommonInterface(QObject *parent) : QObject(parent)
{
    m_memberModel = new MemberModel(this);
    m_structName = "";
    m_hasOtherTypes = false;
    m_structName = "Interval";
}

void CommonInterface::generateSources()
{
    generateStruct();
}

void CommonInterface::generateStruct()
{
    QString templateString = getStructTemplateString();
    if (templateString.isEmpty())
        return;

    fillName(templateString);
    fillMembers(templateString);
    fillIncludes(templateString);
    fillConstructors(templateString);


    QFile structResult(RESULT_FILE_STRUCT_H);
    if (!structResult.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        qCritical() << "Couldn't open:" << RESULT_FILE_STRUCT_H;
        return;
    }

    QTextStream out(&structResult);
    out << templateString;

    structResult.close();
}

QString CommonInterface::getStructTemplateString()
{
    QFile structTemplate(TEMPLATE_FILE_STRUCT_H);
    if (!structTemplate.open(QIODevice::ReadOnly | QIODevice::Text)){
        qCritical() << "Couldn't open:" << TEMPLATE_FILE_STRUCT_H;
        return "";
    }

    QString structTemplateString = structTemplate.readAll();
    structTemplate.close();
    return structTemplateString;
}

void CommonInterface::fillName(QString &outTemplateString)
{
    outTemplateString.replace("[qtf_structName_allCapital]", QString(m_structName).toUpper());
    outTemplateString.replace("[qtf_structName]", m_structName);

}

void CommonInterface::fillIncludes(QString &outTemplateString)
{
    if (m_hasOtherTypes)
        outTemplateString.replace("[qtf_includes]", "#include <QObject>");
    else
        outTemplateString.replace("[qtf_includes]", "");
}

void CommonInterface::fillConstructors(QString &outTemplateString)
{
    QStringList memberList = m_memberModel->getMemberList();

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

void CommonInterface::fillMembers(QString &outTemplateString)
{
    m_hasOtherTypes = false;

    QStringList memberList = m_memberModel->getMemberList();

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
