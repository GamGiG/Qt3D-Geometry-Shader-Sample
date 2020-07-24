#ifndef CUSTOMPLANES_H
#define CUSTOMPLANES_H

#include <QRandomGenerator>
#include <QByteArray>

#include <QVector3D>

#include <Qt3DCore/QEntity>

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>

class CustomPlanes:  public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CustomPlanes(int count = 100, Qt3DCore::QNode* parent = nullptr);

private:
    void initGeometry();
    void initGeometry2();

    int count;
};

#endif // CUSTOMPLANES_H
