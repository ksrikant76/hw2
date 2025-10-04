#include <sstream>
#include <iomanip>
#include "util.h"
#include "book.h"

Book::Book(const std::string& name, const std::string& isbn, const std::string& author, double price, int qty) :
  Product("book", name, price, qty),
  isbn_(isbn),
  author_(author)
{

}

Book::~Book() = default;

std::set<std::string> Book::keywords() const {
  std::set<std::string> keys;

  //Name keywords
  std::set<std::string> nameWords = parseStringToWords(name_);
  keys.insert(nameWords.begin(), nameWords.end());
  
  //Author keywords
  std::set<std::string> authorWords = parseStringToWords(author_);
  keys.insert(authorWords.begin(), authorWords.end());

  //ISBN
  keys.insert(isbn_);

  return keys;
}

std::string Book::displayString() const {
  std::ostringstream oss;
  oss << name_ << "\n";
  oss << "Author: " << author_ << "  ISBN: " << isbn_ << "\n";
  oss << std::fixed << std::setprecision(2);
  oss << "Price: " << price_ << "  Qty: " << qty_;
  return oss.str();
}

void Book::dump(std::ostream& os) const {
    //Product dumps common fields: category, name, price, qty
    Product::dump(os);
    //Book fields
    os << isbn_ << "\n" << author_ << std::endl;
}
