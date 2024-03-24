#pragma once

#include "latte/print_json.h"

#include <array>
#include <memory>
#include <type_traits>
#include <cstddef>
#include <cstdlib>

namespace latte {

class Value {
 public:
  template <typename ValueType,
            typename = std::enable_if_t<!std::is_same_v<ValueType, Value> && std::is_copy_constructible_v<ValueType>>>
  Value(const ValueType& value)
      : memory_buffer_{}, concept_{::new(memory_buffer_.data()) ValueModel<ValueType>(value)} {
    static_assert(std::integral_constant<std::size_t, sizeof(ValueType)>::value <=
                      std::integral_constant<std::size_t, memory_buffer_size>::value,
                  "Expand memory_buffer_size if necessary");
  }

  template <std::size_t N>
  Value(const char (&value)[N])
      : memory_buffer_{}, concept_{::new(memory_buffer_.data()) ValueModel<std::string_view>(value)} {}

  Value(const Value& other);

  Value(Value&&) noexcept = delete;

  Value& operator=(const Value& other);

  Value& operator=(Value&&) noexcept = delete;

  ~Value() = default;

  void PrintJson() const;

 private:
  static constexpr std::size_t memory_buffer_size = 64;
  using MemoryBuffer = std::array<std::byte, memory_buffer_size>;

  struct PlacementDeleter {
    template <typename T>
    void operator()(const T* obj) const noexcept {
      obj->~T();
    }
  };

  class ValueConcept;
  using ConceptPtr = std::unique_ptr<ValueConcept, PlacementDeleter>;

  class ValueConcept {
   public:
    virtual ~ValueConcept() = default;
    virtual void PrintJson() const = 0;
    virtual ConceptPtr CloneInto(Value::MemoryBuffer& buffer) const = 0;
  };

  template <typename ValueType>
  class ValueModel : public ValueConcept {
   public:
    explicit ValueModel(const ValueType& value) : value_(value) {}

    void PrintJson() const override {
      using latte::PrintJson;
      PrintJson(value_);
    }

    ConceptPtr CloneInto(Value::MemoryBuffer& buffer) const override {
      return ConceptPtr{::new (buffer.data()) ValueModel(value_)};
    }

   private:
    ValueType value_;
  };

  ConceptPtr CloneInto(Value::MemoryBuffer& buffer) const;

  alignas(alignof(std::max_align_t)) MemoryBuffer memory_buffer_;
  ConceptPtr concept_;
};

}  // namespace latte
