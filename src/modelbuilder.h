#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <QObject>

class ModelBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ModelBuilder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MODELBUILDER_H