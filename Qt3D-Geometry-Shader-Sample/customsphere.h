#ifndef CUSTOMSPHERE_H
#define CUSTOMSPHERE_H

#include <QVector3D>

#include <Qt3DCore/QEntity>

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>

class CustomSphere :  public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CustomSphere(QVector3D position, Qt3DCore::QNode* parent);

private:
    QVector3D position;

    void initGeometry(QVector3D position);
};

#endif // CUSTOMSPHERE_H
