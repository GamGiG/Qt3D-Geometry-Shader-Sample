#include "planematerial.h"

PlaneMaterial* PlaneMaterial::Instance = nullptr;

PlaneMaterial::PlaneMaterial(Qt3DCore::QNode *parent)
    : Qt3DRender::QMaterial(parent)
{
    if (Instance == nullptr)
    {
        PlaneGeometryEffect* effect = new PlaneGeometryEffect(this);
        this->setEffect(effect);

        Qt3DRender::QTextureImage* textureImage = new Qt3DRender::QTextureImage();
        textureImage->setSource(QUrl("qrc:/Images/Images/texture_0.png"));

        Qt3DRender::QTexture2D* texture = new Qt3DRender::QTexture2D(this);
        texture->setGenerateMipMaps(true);

        texture->setFormat(Qt3DRender::QAbstractTexture::RGBAFormat);
        texture->addTextureImage(textureImage);

        Qt3DRender::QParameter* textureParameter = new Qt3DRender::QParameter(QStringLiteral("texture_diffuse1"), texture);

        this->addParameter(textureParameter);

        Instance=this;

        this->setShareable(true);
    }
}

