#include "latte/value.h"

namespace latte {

Value::Value(const Value& other) : concept_{other.CloneInto(memory_buffer_)} {}

Value& Value::operator=(const Value& other) {
  if (this != &other) {
    concept_.reset();
    concept_ = other.CloneInto(memory_buffer_);
  }

  return *this;
}

void Value::PrintJson() const { concept_->PrintJson(); }

Value::ConceptPtr Value::CloneInto(Value::MemoryBuffer& buffer) const { return concept_->CloneInto(buffer); }

}  // namespace latte
