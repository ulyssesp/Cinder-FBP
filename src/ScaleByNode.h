#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "TextureNode.h"

class ScaleByNode : public TextureNode {
private:
	ci::gl::GlslProgRef mShader;
	ci::vec2 mScale, mPivot;

public:
	ScaleByNode(std::string name);

protected:
	void update(int frame) override;
};
