#ifndef WALLSMATERIAL_H
#define WALLSMATERIAL_H

#include <QUrl>

#include <Qt3DRender/QParameter>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QTexture>

#include "wallsgeometryeffect.h"

class WallsMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
public:
    static WallsMaterial* Instance;
    static WallsGeometryEffect* Effect;

    WallsMaterial(Qt3DCore::QNode* parent);
};

#endif // WALLSMATERIAL_H
