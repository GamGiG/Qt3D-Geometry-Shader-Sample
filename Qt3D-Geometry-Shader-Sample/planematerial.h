#ifndef SPHEREMATERIAL_H
#define SPHEREMATERIAL_H

#include <QUrl>

#include <Qt3DRender/QParameter>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QTexture>

#include "planegeometryeffect.h"

class PlaneMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
public:
    static PlaneMaterial* Instance;

    PlaneMaterial(Qt3DCore::QNode* parent);
};

#endif // SPHEREMATERIAL_H
