#include "SchweineSystemJson.h"

#include <MusicTools.h>

// value

SchweineSystem::Json::Value::Value(json_t* value)
   : json(value)
{
}

SchweineSystem::Json::Value::Value(const bool& value)
   : json(json_boolean(value))
{
}

SchweineSystem::Json::Value::Value(const int64_t& value)
   : json(json_integer(value))
{
}

SchweineSystem::Json::Value::Value(const uint8_t& value)
   : json(json_integer(value))
{
}

SchweineSystem::Json::Value::Value(const uint16_t& value)
   : json(json_integer(value))
{
}

SchweineSystem::Json::Value::Value(const uint32_t& value)
   : json(json_integer(value))
{
}

SchweineSystem::Json::Value::Value(const double& value)
   : json(json_real(value))
{
}

SchweineSystem::Json::Value::Value(const std::string& value)
   : json(json_stringn(value.c_str(), value.size()))
{
}

SchweineSystem::Json::Object SchweineSystem::Json::Value::toObject() const
{
   return Object(json);
}

SchweineSystem::Json::Array SchweineSystem::Json::Value::toArray()
{
   return Array(json);
}

bool SchweineSystem::Json::Value::toBool() const
{
   if (!json)
      return false;

   return json_boolean_value(json);
}

int64_t SchweineSystem::Json::Value::toInt() const
{
   if (!json)
      return 0;

   return json_integer_value(json);
}

double SchweineSystem::Json::Value::toReal() const
{
   if (!json)
      return 0.0;

   return json_real_value(json);
}

std::string SchweineSystem::Json::Value::toString() const
{
   if (!json)
      return std::string();

   const char* test = json_string_value(json);
   return std::string(test);
}

json_t* SchweineSystem::Json::Value::toJson() const
{
   return json;
}

// array

SchweineSystem::Json::Array::Array(json_t* array)
   : Value(array)
{
   if (!json)
      json = json_array();
}

size_t SchweineSystem::Json::Array::size() const
{
   return json_array_size(json);
}

void SchweineSystem::Json::Array::append(const Value& value)
{
   json_array_append_new(json, value.toJson());
}

SchweineSystem::Json::Value SchweineSystem::Json::Array::get(const size_t& index) const
{
   return Value(json_array_get(json, index));
}

// object

SchweineSystem::Json::Object::Object(json_t* object)
   : Value(object)
{
   if (!json)
      json = json_object();
}

SchweineSystem::Json::Object::Object(const Bytes& data)
   : Value(nullptr)
{
   json_error_t error;
   json = json_loadb((const char*)data.data(), data.size(), 0, &error);
}

SchweineSystem::Json::Object::Object(const std::string& data)
   : Value(nullptr)
{
   json_error_t error;
   json = json_loadb(data.data(), data.size(), 0, &error);
}

void SchweineSystem::Json::Object::set(const std::string& key, const Value& value)
{
   json_object_set_new(json, key.c_str(), value.toJson());
}

SchweineSystem::Json::Value SchweineSystem::Json::Object::get(const std::string& key) const
{
   return Value(json_object_get(json, key.c_str()));
}

Bytes SchweineSystem::Json::Object::toBytes() const
{
   size_t size = json_dumpb(json, nullptr, 0, 0);
   if (size == 0)
      return Bytes();

   Bytes buffer(size);
   size = json_dumpb(json, (char*)buffer.data(), size, 0);

   return buffer;
}

std::string SchweineSystem::Json::Object::toString() const
{
   size_t size = json_dumpb(json, nullptr, 0, 0);
   if (size == 0)
      return std::string();

   Bytes buffer(size);
   json_dumpb(json, (char*)buffer.data(), size, 0);

   return std::string(buffer.begin(), buffer.end());
}
