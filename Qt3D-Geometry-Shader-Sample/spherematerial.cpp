#include "spherematerial.h"

SphereMaterial::SphereMaterial(Qt3DCore::QNode *parent)
    : Qt3DRender::QMaterial(parent)
{
    SphereGeometryEffect* effect = new SphereGeometryEffect(this);
    this->setEffect(effect);
}
