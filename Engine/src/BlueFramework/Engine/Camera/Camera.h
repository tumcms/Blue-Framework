/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef BlueFramework_Engine_Camera_314cb89d_4dfa_43ee_9443_912135e20ac5_h
#define BlueFramework_Engine_Camera_314cb89d_4dfa_43ee_9443_912135e20ac5_h

#include "BlueFramework/Core/Math/Matrix.h"
#include "BlueFramework/Core/Math/Vector.h"
#include "BlueFramework/Core/Math/constants.h"
#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Engine/namespace.h"

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

struct CameraTransformation {
	static buw::Vector3f viewDirectionToRotation(const buw::Vector3f &dir);

	CameraTransformation();
	CameraTransformation(const buw::Vector3f &translation, const buw::Vector3f &rotation, const float offset);

	const buw::Vector3f &translation() const;
	buw::Vector3f &translation();

	const buw::Vector3f &rotation() const;
	buw::Vector3f &rotation();

	const float &offset() const;
	float &offset();

	const float &x() const;
	float &x();

	const float &y() const;
	float &y();

	const float &z() const;
	float &z();

	const float &yaw() const;
	float &yaw();

	const float &pitch() const;
	float &pitch();

	const float &roll() const;
	float &roll();

	CameraTransformation operator+(const CameraTransformation &rhs) const;
	CameraTransformation operator-(const CameraTransformation &rhs) const;
	CameraTransformation operator*(const float rhs) const;
	CameraTransformation operator/(const float rhs) const;

	CameraTransformation &operator+=(const CameraTransformation &rhs);
	CameraTransformation &operator-=(const CameraTransformation &rhs);
	CameraTransformation &operator*=(const float rhs);
	CameraTransformation &operator/=(const float rhs);

	float length() const;
	void normalize();

	buw::Matrix44f rotationMatrix() const;
	buw::Matrix44f transformationMatrix() const;
	buw::Matrix44f viewMatrix() const;

	void setViewDirection(const buw::Vector3f &dir);
	void fitToView(const buw::Vector3f &min, const buw::Vector3f &max, float fieldOfView);
	void lookAt(const buw::Vector3f &target, const buw::Vector3f& origin);

private:
	buw::Vector3f translation_;
	buw::Vector3f rotation_;
	float offset_;
};

enum class eProjectionType { Perspective, Orthographic };

struct CameraFrustum {
public:
	CameraFrustum(float left,
	              float right,
	              float bottom,
	              float top,
	              float near,
	              float far,
	              eProjectionType projectionType,
	              float fieldOfView = buw::constantsf::pi_over_4(),
	              float scaling = 1);
	CameraFrustum(float width, 
				  float height, 
				  float near, 
				  float far, 
				  eProjectionType projectionType, 
				  float fieldOfView = buw::constantsf::pi_over_4(), 
				  float scaling = 1);

	float width() const;
	float height() const;
	float depth() const;

	void width(float w);
	void height(float h);
	void depth(float d);

	float fieldOfView() const;
	void fieldOfView(float f);

	buw::Matrix44f projectionMatrix() const;

private:
	float leftPlane_, rightPlane_;
	float bottomPlane_, topPlane_;
	float nearPlane_, farPlane_;

	eProjectionType projectionType_;
	float fieldOfView_;
	float scaling_;
};

class Camera {
public:
	Camera();

	void tick(const float delta);

	const CameraTransformation &transformation() const;
	CameraTransformation &transformation();

	const CameraTransformation &velocity() const;
	CameraTransformation &velocity();

	const CameraFrustum &frustum() const;
	CameraFrustum &frustum();

	buw::Matrix44f viewProjectionMatrix() const;

	buw::Vector4f project(const buw::Vector4f &worldSpace) const;
	buw::Vector4f deproject(const buw::Vector3f &screenSpace) const;

	void panCameraWorld(const buw::Vector2f &screenSpaceDelta);
	void panCameraWorld(const buw::Vector2f &screenSpaceDelta, const buw::Vector3f &worldSpaceReference);
	void panCameraScreen(const buw::Vector2f &screenSpaceDelta, const buw::Vector3f &screenSpaceReference);

	void moveCameraGlobal(const buw::Vector3f &worldSpaceDelta);
	void moveCameraLocal(const buw::Vector3f &localDelta);

	void orbitCamera(float yaw);
	void pitchCamera(float pitch);
	void rollCamera(float roll);
	void rotateCamera(const buw::Vector3f &rotation);

	void pullCameraOut(float delta);
	void pullCameraIn(float delta);

	void setOffset(float offset);

	void setViewDirection(const buw::Vector3f &dir);
	void fitToView(const buw::Vector3f &min, const buw::Vector3f &max);
	void lookAt(const buw::Vector3f &target, const buw::Vector3f& origin);

private:
	CameraTransformation transformation_, velocity_;
	CameraFrustum frustum_;
};

class CameraController {
public:
	enum class eState { Orbiting, Free };

	enum class eKey { MoveForward, MoveBackward, MoveRight, MoveLeft, MoveUp, MoveDown, ViewForward, ViewBackward, ViewRight, ViewLeft, ViewUp, ViewDown };

public:
	CameraController();
	CameraController(buw::ReferenceCounted<Camera> camera);

	void setState(eState state);
	eState getState();

	void tick(const float delta);

	void setViewDirection(const buw::Vector3f &dir);
	void fitToView(const buw::Vector3f &min, const buw::Vector3f &max);
	void lookAt(const buw::Vector3f &target, const buw::Vector3f& origin);

	void handleKeyDown(eKey key);
	void handleKeyUp(eKey key);

	void handleWheel(float delta);

	buw::ReferenceCounted<Camera> getCamera();
	bool isInterpolating();
	float getVelocity();

private:
	void startInterpolation(float duration, const CameraTransformation &target);

private:
	buw::ReferenceCounted<Camera> camera_;

	eState state_;

	bool bInterpolating_;
	float duration_;
	CameraTransformation target_;

	buw::Vector3f moveDirection_;
	float velocity_;
};

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(eProjectionType)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(CameraFrustum)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(Camera)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(CameraController)

#endif // end define BlueFramework_Engine_Camera_314cb89d_4dfa_43ee_9443_912135e20ac5_h
