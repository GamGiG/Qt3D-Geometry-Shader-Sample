#ifndef SPHEREGEOMETRYEFFECT_H
#define SPHEREGEOMETRYEFFECT_H

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QFilterKey>

#include <QStringLiteral>
#include <QUrl>

class SphereGeometryEffect : public Qt3DRender::QEffect
{
    Q_OBJECT
public:
    SphereGeometryEffect(Qt3DCore::QNode* parent);
};

#endif // SPHEREGEOMETRYEFFECT_H
