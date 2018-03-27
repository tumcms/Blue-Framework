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

#include "BlueFramework/Core/Diagnostics/log.h"
#include "Camera.h"

#include <map>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

CameraTransformation::CameraTransformation() : translation_(0, 0, 0), rotation_(0, 0, 0), offset_(0) {
}

buw::Vector3f CameraTransformation::viewDirectionToRotation(const buw::Vector3f & dir)
{
	float l = buw::Vector2f(dir.x(), dir.z()).norm();

	float yaw = 0;
	float pitch = (float)(M_PI / 2.0) * (dir.y() >= 0 ? 1 : -1);
	if (l > 0) {
		yaw = atan2(dir.z(), dir.x());
		pitch = atan(dir.y() / l);
	}

	return buw::Vector3f(yaw, pitch, 0);
}

CameraTransformation::CameraTransformation(const buw::Vector3f &translation, const buw::Vector3f &rotation, const float offset)
	: translation_(translation), rotation_(rotation), offset_(offset) {
}

const buw::Vector3f &CameraTransformation::translation() const {
	return translation_;
}
buw::Vector3f &CameraTransformation::translation() {
	return translation_;
}

const buw::Vector3f &CameraTransformation::rotation() const {
	return rotation_;
}
buw::Vector3f &CameraTransformation::rotation() {
	return rotation_;
}

const float &CameraTransformation::offset() const {
	return offset_;
}
float &CameraTransformation::offset() {
	return offset_;
}

const float &CameraTransformation::x() const {
	return translation_.x();
}
float &CameraTransformation::x() {
	return translation_.x();
}

const float &CameraTransformation::y() const {
	return translation_.y();
}
float &CameraTransformation::y() {
	return translation_.y();
}

const float &CameraTransformation::z() const {
	return translation_.z();
}
float &CameraTransformation::z() {
	return translation_.z();
}

const float &CameraTransformation::yaw() const {
	return rotation_.x();
}
float &CameraTransformation::yaw() {
	return rotation_.x();
}

const float &CameraTransformation::pitch() const {
	return rotation_.y();
}
float &CameraTransformation::pitch() {
	return rotation_.y();
}

const float &CameraTransformation::roll() const {
	return rotation_.z();
}
float &CameraTransformation::roll() {
	return rotation_.z();
}

CameraTransformation CameraTransformation::operator+(const CameraTransformation &rhs) const {
	return CameraTransformation(translation_ + rhs.translation_, rotation_ + rhs.rotation_, offset_ + rhs.offset_);
}

#define PI (float)M_PI

float mod(const float &a, const float &n) {
	return a - floor(a / n) * n;
}

float angleDiff(const float &a, const float &b) {
	float c = a - b;
	c = mod((c + PI), 2 * PI) - PI;
	return c;
}

CameraTransformation CameraTransformation::operator-(const CameraTransformation &rhs) const {
	buw::Vector3f rot;
	rot.x() = angleDiff(rotation_.x(), rhs.rotation_.x());
	rot.y() = angleDiff(rotation_.y(), rhs.rotation_.y());
	rot.z() = angleDiff(rotation_.z(), rhs.rotation_.z());

	return CameraTransformation(translation_ - rhs.translation_, rot, offset_ - rhs.offset_);
}
CameraTransformation CameraTransformation::operator*(const float rhs) const {
	return CameraTransformation(translation_ * rhs, rotation_ * rhs, offset_ * rhs);
}
CameraTransformation CameraTransformation::operator/(const float rhs) const {
	return CameraTransformation(translation_ / rhs, rotation_ / rhs, offset_ / rhs);
}

CameraTransformation &CameraTransformation::operator+=(const CameraTransformation &rhs) {
	translation_ += rhs.translation_;
	rotation_ += rhs.rotation_;
	offset_ += rhs.offset_;

	return *this;
}
CameraTransformation &CameraTransformation::operator-=(const CameraTransformation &rhs) {
	buw::Vector3f rot;
	rot.x() = angleDiff(rotation_.x(), rhs.rotation_.x());
	rot.y() = angleDiff(rotation_.y(), rhs.rotation_.y());
	rot.z() = angleDiff(rotation_.z(), rhs.rotation_.z());

	translation_ -= rhs.translation_;
	rotation_ = rot;
	offset_ -= rhs.offset_;

	return *this;
}
CameraTransformation &CameraTransformation::operator*=(const float rhs) {
	translation_ *= rhs;
	rotation_ *= rhs;
	offset_ *= rhs;

	return *this;
}
CameraTransformation &CameraTransformation::operator/=(const float rhs) {
	translation_ /= rhs;
	rotation_ /= rhs;
	offset_ /= rhs;

	return *this;
}

float CameraTransformation::length() const {
	buw::Vector<float, 7> trafo;
	trafo.segment<3>(0) = translation_;
	trafo.segment<3>(3) = rotation_;
	trafo[6] = offset_;

	return trafo.norm();
}
void CameraTransformation::normalize() {
	operator/=(length());
}


buw::Matrix44f CameraTransformation::rotationMatrix() const {
	return buw::createRotationMatrixY(yaw()) * buw::createRotationMatrixX(pitch()) * buw::createRotationMatrixZ(roll());
}
buw::Matrix44f CameraTransformation::transformationMatrix() const {
	return buw::createTranslationMatrix(translation()) * rotationMatrix() * buw::createTranslationMatrix(buw::Vector3f(0, 0, -offset()));
}
buw::Matrix44f CameraTransformation::viewMatrix() const {
	return transformationMatrix().inverse();
}

void CameraTransformation::setViewDirection(const buw::Vector3f & dir) {
	/*float l = buw::Vector2f(dir.x(), dir.z()).norm();

	float pitch = atan(dir.y() / l);
	float yaw = camera_->transformation().yaw();
	if (l > 0)
	yaw = atan2(dir.z(), dir.x()) + (float)(M_PI / 2.0);

	auto target = camera_->transformation();
	target.yaw() = yaw;
	target.pitch() = pitch;
	target.roll() = 0;*/
	rotation_ = viewDirectionToRotation(dir);
}

void CameraTransformation::fitToView(const buw::Vector3f& min, const buw::Vector3f& max, float fieldOfView) {
	buw::Vector3f center = (min + max) / 2.f;

	buw::Vector3f d1, d2;
	d1 = max - min;
	d2 = buw::Vector3f(max.x(), min.y(), min.z()) - buw::Vector3f(min.x(), max.y(), max.z());

	buw::Vector3f view = buw::Vector3f(1, 1, 1);
	buw::Vector3f rot = viewDirectionToRotation(view.normalized());

	float offset = std::max(0.01f, d1.norm() / 2.f / tan(fieldOfView / 2.f));

	translation_ = center;
	rotation_ = rot;
	offset_ = offset;
}

void CameraTransformation::lookAt(const buw::Vector3f & target, const buw::Vector3f & origin) {
	float yaw = 0;
	float pitch = 0;
	float roll = 0;

	buw::Vector3f v = target - origin;

	if (v.norm() > 0)
	{
		buw::Vector3f v1(v.x(), 0, v.z()), v2;
		if (v1.norm() > 0)
		{
			v1 = v1.normalized();
			v2 = v.normalized();

			yaw = buw::constantsf::pi_over_2() - atan2(v1.z(), v1.x());

			if (v.y() != 0)
				pitch = acos(std::max(-1.f, std::min(v1.dot(v2), 1.f)));
		}
		else
			pitch = buw::constantsf::pi_over_2();

		if (v.y() > 0)
			pitch *= -1;

	}

	translation_ = target;
	rotation_.x() = yaw;
	rotation_.y() = pitch;
	rotation_.z() = roll;
	offset_ = v.norm();
}


Camera::Camera() : frustum_(16, 9, 0.1f, 1000, eProjectionType::Perspective) {
}

const CameraTransformation &Camera::transformation() const {
	return transformation_;
}
CameraTransformation &Camera::transformation() {
	return transformation_;
}

const CameraTransformation &Camera::velocity() const {
	return velocity_;
}
CameraTransformation &Camera::velocity() {
	return velocity_;
}

const CameraFrustum &Camera::frustum() const {
	return frustum_;
}
CameraFrustum &Camera::frustum() {
	return frustum_;
}

buw::Matrix44f Camera::viewProjectionMatrix() const {
	return frustum_.projectionMatrix() * transformation_.viewMatrix();
}

buw::Vector4f Camera::project(const buw::Vector4f &worldSpace) const {
	buw::Vector4f screenSpace = viewProjectionMatrix() * worldSpace;
	screenSpace /= screenSpace.w();
	return screenSpace;
}
buw::Vector4f Camera::deproject(const buw::Vector3f &screenSpace) const {
	buw::Vector4f worldSpace;

	float d1 = frustum().projectionMatrix()(2, 2);
	float d2 = frustum().projectionMatrix()(2, 3);

	float z = d2 / (screenSpace.z() - d1);

	worldSpace = buw::Vector4f(screenSpace.x() * z, screenSpace.y() * z, d1 * z + d2, z);

	worldSpace = viewProjectionMatrix().inverse() * worldSpace;
	return worldSpace;
}

void Camera::panCameraWorld(const buw::Vector2f &screenSpaceDelta) {
	panCameraWorld(screenSpaceDelta, transformation().translation());
}

void Camera::panCameraWorld(const buw::Vector2f &screenSpaceDelta, const buw::Vector3f &worldSpaceReference) {
	buw::Vector4f screenSpaceReference, worldSpaceDelta;

	buw::Matrix44f projectionMatrix = frustum().projectionMatrix();
	buw::Matrix44f viewMatrix = transformation().viewMatrix();

	screenSpaceReference = buw::Vector4f(worldSpaceReference.x(), worldSpaceReference.y(), worldSpaceReference.z(), 1);

	screenSpaceReference = viewMatrix * screenSpaceReference;

	screenSpaceReference = projectionMatrix * screenSpaceReference;

	float w = screenSpaceReference.w();
	screenSpaceReference /= w;

	worldSpaceDelta = buw::Vector4f(screenSpaceDelta.x(), screenSpaceDelta.y(), worldSpaceReference.z(), w);

	worldSpaceDelta *= w;

	worldSpaceDelta = projectionMatrix.inverse() * worldSpaceDelta;
	worldSpaceDelta.z() = 0;
	worldSpaceDelta.w() = 0;
	worldSpaceDelta = viewMatrix.inverse() * worldSpaceDelta;

	transformation().translation() += worldSpaceDelta.segment<3>(0);
}

void Camera::panCameraScreen(const buw::Vector2f &screenSpaceDelta, const buw::Vector3f &screenSpaceReference) {
	buw::Vector4f w1 = deproject(screenSpaceReference);
	buw::Vector4f w2 = deproject(screenSpaceReference + buw::Vector3f(screenSpaceDelta.x(), screenSpaceDelta.y(), 0));

	buw::Vector4f worldSpaceDelta = w2 - w1;

	transformation().translation() += worldSpaceDelta.segment<3>(0);
}

void Camera::moveCameraGlobal(const buw::Vector3f &worldSpaceDelta) {
	transformation().translation() += worldSpaceDelta;
}
void Camera::moveCameraLocal(const buw::Vector3f &localDelta) {
	transformation().translation() += transformation().rotationMatrix().block<3, 3>(0, 0) * localDelta;
}

void Camera::orbitCamera(float yaw) {
	transformation().yaw() += yaw;
}
void Camera::pitchCamera(float pitch) {
	transformation().pitch() += pitch;
}
void Camera::rollCamera(float roll) {
	transformation().roll() += roll;
}

void Camera::rotateCamera(const buw::Vector3f &rotation) {
	transformation().rotation() += rotation;
}

void Camera::pullCameraOut(float delta) {
	transformation().offset() *= delta;
}
void Camera::pullCameraIn(float delta) {
	transformation().offset() /= delta;
}

void Camera::setOffset(float offset) {
	buw::Vector3f oldPos = (transformation().transformationMatrix() * buw::Vector4f(0, 0, 0, 1)).block<3, 1>(0, 0);
	buw::Vector3f newCenter = deproject(buw::Vector3f(0, 0, offset)).block<3, 1>(0, 0);

	transformation().translation() = newCenter;
	transformation().offset() = (oldPos - newCenter).norm();
}

void Camera::setViewDirection(const buw::Vector3f & dir)
{
	transformation().setViewDirection(dir);
}

void Camera::fitToView(const buw::Vector3f & min, const buw::Vector3f & max)
{
	transformation().fitToView(min, max, frustum().fieldOfView());
}

void Camera::lookAt(const buw::Vector3f &target, const buw::Vector3f& origin)
{
	transformation().lookAt(target, origin);
}

void Camera::tick(const float delta) {
	transformation_ += velocity_ * delta;
}

CameraFrustum::CameraFrustum(float left,
	float right,
	float bottom,
	float top,
	float near,
	float far,
	eProjectionType projectionType,
	float fieldOfView /*= (float)M_PI / 4.f*/,
	float scaling /*= 0*/)
	: leftPlane_(left)
	, rightPlane_(right)
	, bottomPlane_(bottom)
	, topPlane_(top)
	, nearPlane_(near)
	, farPlane_(far)
	, projectionType_(projectionType)
	, fieldOfView_(fieldOfView)
	, scaling_(scaling) {
}

CameraFrustum::CameraFrustum(float width, float height, float near, float far, eProjectionType projectionType, float fieldOfView /*= (float)M_PI / 4.f*/, float scaling /*= 0*/)
	: leftPlane_(-width / 2.f)
	, rightPlane_(width / 2.f)
	, bottomPlane_(-height / 2.f)
	, topPlane_(height / 2.f)
	, nearPlane_(near)
	, farPlane_(far)
	, projectionType_(projectionType)
	, fieldOfView_(fieldOfView)
	, scaling_(scaling) {
}

float CameraFrustum::width() const {
	return rightPlane_ - leftPlane_;
}
float CameraFrustum::height() const {
	return topPlane_ - bottomPlane_;
}
float CameraFrustum::depth() const {
	return farPlane_ - nearPlane_;
}

void CameraFrustum::width(float w) {
	leftPlane_ = -w / 2.f;
	rightPlane_ = w / 2.f;
}
void CameraFrustum::height(float h) {
	bottomPlane_ = -h / 2.f;
	topPlane_ = h / 2.f;
}
void CameraFrustum::depth(float d) {
	nearPlane_ = 0.001f;
	farPlane_ = d - nearPlane_;
}

float CameraFrustum::fieldOfView() const {
	return fieldOfView_;
}
void CameraFrustum::fieldOfView(float f) {
	fieldOfView_ = f;
};

buw::Matrix44f CameraFrustum::projectionMatrix() const {
	switch (projectionType_) {
	case eProjectionType::Perspective: return buw::createPerspectiveProjectionMatrixRH(fieldOfView_, width() / height(), nearPlane_, farPlane_); break;
	case eProjectionType::Orthographic:
	default: return buw::createOrthographicProjectionMatrixRH(width() / scaling_, height() / scaling_, -farPlane_, farPlane_);
	}
}

CameraController::CameraController() :
	state_(eState::Orbiting),
	bInterpolating_(false),
	moveDirection_(0, 0, 0),
	velocity_(5) {
	camera_ = buw::makeReferenceCounted<Camera>();
}
CameraController::CameraController(buw::ReferenceCounted<Camera> camera) :
	camera_(camera),
	state_(eState::Orbiting),
	bInterpolating_(false),
	moveDirection_(0, 0, 0),
	velocity_(5) {
}

void CameraController::setState(eState state) {
	if (state_ == eState::Orbiting && state == eState::Free)
		camera_->setOffset(0);
	else if (state_ == eState::Free && state == eState::Orbiting)
		camera_->setOffset(0.1f);

	moveDirection_ *= 0;
	state_ = state;
}

CameraController::eState CameraController::getState()
{
	return state_;
}

void CameraController::tick(const float delta) {
	if (bInterpolating_) {
		auto diff = target_ - camera_->transformation();
		if (diff.length() < camera_->velocity().length() * delta) {
			camera_->transformation() = target_;
			camera_->velocity() *= 0;
			bInterpolating_ = false;
        }
        else {
            startInterpolation(std::max(duration_ - delta, delta), target_);
        }
	}
	else {
		buw::Vector3f vel(0, 0, 0);
		if (velocity_ > 0 && moveDirection_.norm() > 0)
			vel = moveDirection_.normalized() * velocity_;
		vel = camera_->transformation().rotationMatrix().block<3, 3>(0, 0) * vel;
		camera_->velocity().translation() = vel;
	}
}

void CameraController::setViewDirection(const buw::Vector3f &dir) {
	auto target = camera_->transformation();
	target.setViewDirection(dir);

	startInterpolation(0.5f, target);
}

void CameraController::fitToView(const buw::Vector3f &min, const buw::Vector3f &max) {
	CameraTransformation target = camera_->transformation();
	target.fitToView(min, max, camera_->frustum().fieldOfView());

	state_ = eState::Orbiting;
	startInterpolation(1, target);
}

void CameraController::lookAt(const buw::Vector3f& target, const buw::Vector3f& origin) {
	CameraTransformation targetTransformation = camera_->transformation();
	targetTransformation.lookAt(target, origin);

	state_ = eState::Orbiting;
	startInterpolation(1, targetTransformation);
}

void CameraController::startInterpolation(float duration, const CameraTransformation &target) {
    duration_ = duration;
	target_ = target;
	auto diff = target_ - camera_->transformation();

	camera_->velocity() = diff / duration;
	bInterpolating_ = true;
}


const std::map<CameraController::eKey, buw::Vector3f> key2MoveDirection = {
	{ CameraController::eKey::MoveForward,	buw::Vector3f(0, 0, 1) },
	{ CameraController::eKey::MoveBackward,	buw::Vector3f(0, 0, -1) },
	{ CameraController::eKey::MoveRight,	buw::Vector3f(1, 0, 0) },
	{ CameraController::eKey::MoveLeft,		buw::Vector3f(-1, 0, 0) },
	{ CameraController::eKey::MoveUp,		buw::Vector3f(0, 1, 0) },
	{ CameraController::eKey::MoveDown,		buw::Vector3f(0, -1, 0) },
};

const std::map<CameraController::eKey, buw::Vector3f> key2ViewDirection = {
	{ CameraController::eKey::ViewForward,	buw::Vector3f(0, 0, 1) },
	{ CameraController::eKey::ViewBackward,	buw::Vector3f(0, 0, -1) },
	{ CameraController::eKey::ViewRight,	buw::Vector3f(1, 0, 0) },
	{ CameraController::eKey::ViewLeft,		buw::Vector3f(-1, 0, 0) },
	{ CameraController::eKey::ViewUp,		buw::Vector3f(0, 1, 0) },
	{ CameraController::eKey::ViewDown,		buw::Vector3f(0, -1, 0) },
};

void CameraController::handleKeyDown(eKey key) {
	if (state_ == eState::Free && key2MoveDirection.find(key) != key2MoveDirection.end()) {
		moveDirection_ += key2MoveDirection.at(key);
	}
	else if (state_ == eState::Orbiting && key2ViewDirection.find(key) != key2ViewDirection.end()) {
		setViewDirection(key2ViewDirection.at(key));
	}
}

void CameraController::handleKeyUp(eKey key) {
	if (state_ == eState::Free && key2MoveDirection.find(key) != key2MoveDirection.end()) {
		moveDirection_ -= key2MoveDirection.at(key);
	}
}

void CameraController::handleWheel(float factor) {
	if (state_ == eState::Free)
		velocity_ *= factor;
	else if (state_ == eState::Orbiting)
		camera_->pullCameraOut(factor);
}

buw::ReferenceCounted<Camera> CameraController::getCamera()
{
    return camera_;
}

const bool CameraController::isCameraMoving() const
{
	return camera_->velocity().length() > 0.0f;
}

BLUEFRAMEWORK_ENGINE_NAMESPACE_END