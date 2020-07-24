#ifndef SPHEREMATERIAL_H
#define SPHEREMATERIAL_H

#include <Qt3DRender/QMaterial>

#include "spheregeometryeffect.h"

class SphereMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
public:
    SphereMaterial(Qt3DCore::QNode* parent);
};

#endif // SPHEREMATERIAL_H
