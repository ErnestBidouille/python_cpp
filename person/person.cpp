#include <pybind11/pybind11.h>
#include <string>

struct Person
{
  std::string name;
  std::int8_t age;
  Person(const std::string name, const std::int8_t age) : age(age), name(name) {}
  void setName(const std::string &name_) { name = name_; }
  const std::string &getName() const { return name; }
  void setAge(const std::int8_t &age_) { age = age_; }
  const std::int8_t &getAge() const { return age; }
};

namespace py = pybind11;

PYBIND11_MODULE(person, m)
{
  py::class_<Person>(m, "Person")
      .def(py::init<const std::string &, const std::int8_t &>())
      .def("set_name", &Person::setName)
      .def("get_name", &Person::getName)
      .def("set_age", &Person::setAge)
      .def("get_age", &Person::getAge)
      .def("__repr__", [](const Person &p) {
        return "<person.Person named '" + p.name + "' and aged " + std::to_string(p.age) + " >";
      });
}
