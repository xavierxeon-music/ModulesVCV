#include "SvinJson.h"

#include <MusicTools.h>

// value

Svin::Json::Value::Value(json_t* value)
   : json(value)
{
}

Svin::Json::Value::Value(const bool& value)
   : json(json_boolean(value))
{
}

Svin::Json::Value::Value(const int64_t& value)
   : json(json_integer(value))
{
}

Svin::Json::Value::Value(const uint8_t& value)
   : json(json_integer(value))
{
}

Svin::Json::Value::Value(const uint16_t& value)
   : json(json_integer(value))
{
}

Svin::Json::Value::Value(const uint32_t& value)
   : json(json_integer(value))
{
}

Svin::Json::Value::Value(const double& value)
   : json(json_real(value))
{
}

Svin::Json::Value::Value(const std::string& value)
   : json(json_stringn(value.c_str(), value.size()))
{
}

Svin::Json::Object Svin::Json::Value::toObject() const
{
   return Object(json);
}

Svin::Json::Array Svin::Json::Value::toArray()
{
   return Array(json);
}

bool Svin::Json::Value::toBool() const
{
   if (!json)
      return false;

   return json_boolean_value(json);
}

int64_t Svin::Json::Value::toInt() const
{
   if (!json)
      return 0;

   return json_integer_value(json);
}

double Svin::Json::Value::toReal() const
{
   if (!json)
      return 0.0;

   return json_real_value(json);
}

std::string Svin::Json::Value::toString() const
{
   if (!json)
      return std::string();

   const char* test = json_string_value(json);
   return std::string(test);
}

json_t* Svin::Json::Value::toJson() const
{
   return json;
}

// array

Svin::Json::Array::Array(json_t* array)
   : Value(array)
{
   if (!json)
      json = json_array();
}

size_t Svin::Json::Array::size() const
{
   return json_array_size(json);
}

void Svin::Json::Array::append(const Value& value)
{
   json_array_append_new(json, value.toJson());
}

Svin::Json::Value Svin::Json::Array::get(const size_t& index) const
{
   return Value(json_array_get(json, index));
}

// object

Svin::Json::Object::Object(json_t* object)
   : Value(object)
{
   if (!json)
      json = json_object();
}

Svin::Json::Object::Object(const Bytes& data)
   : Value(nullptr)
{
   json_error_t error;
   json = json_loadb((const char*)data.data(), data.size(), 0, &error);
}

Svin::Json::Object::Object(const std::string& data)
   : Value(nullptr)
{
   json_error_t error;
   json = json_loadb(data.data(), data.size(), 0, &error);
}

void Svin::Json::Object::set(const std::string& key, const Value& value)
{
   json_object_set_new(json, key.c_str(), value.toJson());
}

Svin::Json::Value Svin::Json::Object::get(const std::string& key) const
{
   return Value(json_object_get(json, key.c_str()));
}

bool Svin::Json::Object::hasKey(const std::string& key) const
{
   return (nullptr != json_object_get(json, key.c_str()));
}

Bytes Svin::Json::Object::toBytes() const
{
   size_t size = json_dumpb(json, nullptr, 0, 0);
   if (size == 0)
      return Bytes();

   Bytes buffer(size);
   size = json_dumpb(json, (char*)buffer.data(), size, 0);

   return buffer;
}

std::string Svin::Json::Object::toString() const
{
   size_t size = json_dumpb(json, nullptr, 0, 0);
   if (size == 0)
      return std::string();

   Bytes buffer(size);
   json_dumpb(json, (char*)buffer.data(), size, 0);

   return std::string(buffer.begin(), buffer.end());
}
