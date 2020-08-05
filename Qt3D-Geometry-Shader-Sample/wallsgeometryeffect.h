#ifndef WALLSGEOMETRYEFFECT_H
#define WALLSGEOMETRYEFFECT_H

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QAlphaTest>

#include <QStringLiteral>
#include <QUrl>

class WallsGeometryEffect: public Qt3DRender::QEffect
{
    Q_OBJECT
public:
    WallsGeometryEffect(Qt3DCore::QNode* parent);
};

#endif // WALLSGEOMETRYEFFECT_H
