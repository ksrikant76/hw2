#include <sstream>
#include <iomanip>
#include "util.h"
#include "clothing.h"

Clothing::Clothing(const std::string& name, const std::string& size, const std::string& brand, double price, int qty) :
  Product("clothing", name, price, qty),
  size_(size),
  brand_(brand)
{

}

Clothing::~Clothing() = default;

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keys;

  //Name keywords
  std::set<std::string> nameWords = parseStringToWords(name_);
  keys.insert(nameWords.begin(), nameWords.end());

  //Brand keywords
  std::set<std::string> brandWords = parseStringToWords(brand_);
  keys.insert(brandWords.begin(), brandWords.end());

  return keys;
}

std::string Clothing::displayString() const {
  std::ostringstream oss;
  oss << name_ << "\n";
  oss << "Brand: " << brand_ << " Size: " << size_ << "\n";
  oss << std::fixed << std::setprecision(2);
  oss << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Clothing::dump(std::ostream& os) const {
  //Product dumps common fields: category, name, price, qty
  Product::dump(os);
  //Clothing fields
  os << size_ << "\n" << brand_ << std::endl;
}
