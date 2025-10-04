#include <sstream>
#include <iomanip>
#include "util.h"
#include "movie.h"

Movie::Movie(const std::string& name, const std::string& genre, const std::string& rating, double price, int qty) :
  Product("movie", name, price, qty),
  genre_(genre),
  rating_(rating)
{

}

Movie::~Movie() = default;

std::set<std::string> Movie::keywords() const {
  std::set<std::string> keys;

  //Name keywords
  std::set<std::string> nameWords = parseStringToWords(name_);
  keys.insert(nameWords.begin(), nameWords.end());

  //Genre
  keys.insert(genre_);

  return keys;
}

std::string Movie::displayString() const {
  std::ostringstream oss;
  oss << name_ << "\n";
  oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  oss << std::fixed << std::setprecision(2);
  oss << price_ << qty_ << " left.";
  return oss.str();
}

void Movie::dump(std::ostream& os) const {
  //Product dumps common fields: category, name, price, qty
  Product::dump(os);
  //Movie fields
  os << genre_ << "\n" << rating_ << std::endl;
}
