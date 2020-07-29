#ifndef SPHEREGEOMETRYEFFECT_H
#define SPHEREGEOMETRYEFFECT_H

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QAlphaTest>

#include <QStringLiteral>
#include <QUrl>

class PlaneGeometryEffect : public Qt3DRender::QEffect
{
    Q_OBJECT
public:
    PlaneGeometryEffect(Qt3DCore::QNode* parent);
};

#endif // SPHEREGEOMETRYEFFECT_H
