#include "SchweineSystemJson.h"

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

SchweineSystem::Json::Value::Value(const double& value)
   : json(json_real(value))
{
}

SchweineSystem::Json::Value::Value(const std::string& value)
   : json(nullptr)
{
}

SchweineSystem::Json::Object SchweineSystem::Json::Value::toObject() const
{
}

SchweineSystem::Json::Array SchweineSystem::Json::Value::toArray()
{
}

bool SchweineSystem::Json::Value::toBool() const
{
}

int64_t SchweineSystem::Json::Value::toInt() const
{
}

double SchweineSystem::Json::Value::toReal() const
{
}

std::string SchweineSystem::Json::Value::toString() const
{
}

json_t* SchweineSystem::Json::Value::toJson() const
{
   return json;
}

// array

SchweineSystem::Json::Array::Array(json_t* array)
   : Value(array)
{
}

size_t SchweineSystem::Json::Array::size()
{
}

void SchweineSystem::Json::Array::append(const Value& value)
{
}

SchweineSystem::Json::Value SchweineSystem::Json::Array::get(const size_t& index)
{
}

std::vector<SchweineSystem::Json::Value> SchweineSystem::Json::Array::asList() const
{
}

// object

SchweineSystem::Json::Object::Object(json_t* object)
   : Value(object)
{
}

void SchweineSystem::Json::Object::set(const std::string& key, const Value& value)
{
}

SchweineSystem::Json::Value SchweineSystem::Json::Object::get(const std::string& key)
{
}

std::map<std::string, SchweineSystem::Json::Value> SchweineSystem::Json::Object::asMap() const
{
}
