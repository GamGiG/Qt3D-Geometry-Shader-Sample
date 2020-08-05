#include "wallsgeometryeffect.h"

WallsGeometryEffect::WallsGeometryEffect(Qt3DCore::QNode *parent)
    : Qt3DRender::QEffect(parent)
{
    Qt3DRender::QTechnique* technique = new Qt3DRender::QTechnique(this);
    technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    technique->graphicsApiFilter()->setMajorVersion(3);
    technique->graphicsApiFilter()->setMinorVersion(3);

    Qt3DRender::QFilterKey* filterKey = new Qt3DRender::QFilterKey(technique);
    filterKey->setName("renderingStyle");
    filterKey->setValue("forward");
    technique->addFilterKey(filterKey);

    Qt3DRender::QRenderPass* renderPass = new Qt3DRender::QRenderPass(technique);

    Qt3DRender::QShaderProgram* shaderProgram = new Qt3DRender::QShaderProgram(renderPass);
    shaderProgram->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Shaders/Shaders/generate_walls.vert"))));
    shaderProgram->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Shaders/Shaders/generate_walls.glsl"))));
    shaderProgram->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/Shaders/Shaders/generate_walls.frag"))));
    renderPass->setShaderProgram(shaderProgram);

    technique->addRenderPass(renderPass);
    this->addTechnique(technique);
}
