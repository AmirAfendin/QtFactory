#ifndef COMMONINTERFACE_H
#define COMMONINTERFACE_H

#include <QObject>

#include "qqmlhelpers.h"
#include "membermodel.h"
#include "structbuilder.h"
#include "modelbuilder.h"

#define TEMPLATE_FILE_STRUCT_H "./templates/struct_h.txt"
#define TEMPLATE_FILE_MODEL_H "./templates/model_h.txt"
#define TEMPLATE_FILE_MODEL_CPP "./templates/model_cpp.txt"
#define RESULT_FILE_STRUCT_H "./struct.h"
#define RESULT_FILE_MODEL_H "./model.h"
#define RESULT_FILE_MODEL_CPP "./model.cpp"


class CommonInterface : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QString, structName)
public:
    explicit CommonInterface(QObject *parent = nullptr);
    MemberModel* memberModel() { return m_memberModel; }

public slots:
    void buildSources();

private:
    MemberModel *m_memberModel;
    StructBuilder m_structBuilder;
    ModelBuilder m_modelBuilder;
};

#endif // COMMONINTERFACE_H
