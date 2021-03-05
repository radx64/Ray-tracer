#include "Object.hpp"

namespace rt {
namespace core {

void Object::setMaterial(std::unique_ptr<Material> material) { material_ = std::move(material); }

const core::Material &Object::getMaterial() { return *material_; }

void Object::setPosition(Point &p) { position_ = p; }

Point Object::getPosition() { return position_; }

} // namespace core
} // namespace rt