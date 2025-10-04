#include "mydatastore.h"
#include "util.h"
#include <sstream>
#include <iomanip>
#include <cctype>

MyDataStore::MyDataStore()
{
  
}

MyDataStore::~MyDataStore() {
  //Delete all users
  std::map<std::string, User*>::iterator userit = users_.begin();
  while (userit != users_.end()) {
    delete userit->second;
    ++userit;
  }
  //Delete all products
  std::vector<Product*>::iterator prodit = products_.begin();
  while (prodit != products_.end()) {
    delete *prodit;
    ++prodit;
  }
}

std::string MyDataStore::toLower(const std::string& s) {
  std::string out;
  for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
    unsigned char ch = static_cast<unsigned char>(*it);
    out.push_back(static_cast<char>(std::tolower(ch)));
  }
  return out;
}

void MyDataStore::addProduct(Product* p) {
  //Add to products
  if (p == NULL) return;
  products_.push_back(p);

  //Put all keywords in index
  std::set<std::string> keys = p->keywords();
  std::set<std::string>::iterator keyit = keys.begin();
  while (keyit != keys.end()) {
    std::string key = toLower(*keyit);
    index_[key].insert(p);
    ++keyit;
  }
}

void MyDataStore::addUser(User* u) {
  //Add to users
  if (u == NULL) return;
  std::string uname = toLower(u->getName());
  users_[uname] = u;

  //Initialize empty cart for user
  if (carts_.find(uname) == carts_.end()) {
    std::vector<Product*> emptycart;
    carts_[uname] = emptycart;
  }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  lastHits_.clear();

  //Empty search
  if (terms.empty()) {
    return lastHits_;
  }

  //Get results for each term
  std::vector< std::set<Product*> > perTerm;

  for (std::size_t i = 0; i < terms.size(); ++i) {
    std::string key = toLower(terms[i]);
    std::map<std::string, std::set<Product*> >::const_iterator it = index_.find(key);
    if (it != index_.end()) {
      perTerm.push_back(it->second);
    }
    else {
      //No matches
      std::set<Product*> nomatches;
      perTerm.push_back(nomatches);
    }
  }

  //Combine perTerm results according to AND/OR search
  std::set<Product*> combined;
  if (type == 0) {
    //AND search
    if (!perTerm.empty()) {
      combined = perTerm[0];
      for (std::size_t i = 1; i < perTerm.size(); ++i) {
        std::set<Product*> a = combined;
        std::set<Product*> b = perTerm[i];
        combined = setIntersection(a, b);
      }
    }
  }
  else {
    //OR search
    for (std::size_t i = 0; i < perTerm.size(); ++i) {
      std::set<Product*> a = combined;
      std::set<Product*> b = perTerm[i];
      combined = setUnion(a, b);
    }
  }

  // move combined set into vector hits
  std::set<Product*>::const_iterator combinedit = combined.begin();
  while (combinedit != combined.end()) {
    lastHits_.push_back(*combinedit);
    ++combinedit;
  }

  return lastHits_;
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n";
  std::vector<Product*>::const_iterator prodit = products_.begin();
  while (prodit != products_.end()) {
    (*prodit)->dump(ofile);
    ++prodit;
  }
  ofile << "</products>\n";

  ofile << "<users>\n";
  std::map<std::string, User*>::const_iterator userit = users_.begin();
  while (userit != users_.end()) {
    userit->second->dump(ofile);
    ++userit;
  }
  ofile << "</users>\n";
}

void MyDataStore::addToCart(const std::string& username, int hit_result_index) {
  //Check if username is valid
  std::string uname = toLower(username);
  std::map<std::string, User*>::iterator userit = users_.find(uname);
  if (userit == users_.end()) {
    std::cout << "Invalid request\n";
    return;
  }

  //Check if index is valid (starts at 1)
  if (hit_result_index < 1 || static_cast<std::size_t>(hit_result_index) > lastHits_.size()) {
    std::cout << "Invalid request\n";
    return;
  }

  Product* p = lastHits_[static_cast<std::size_t>(hit_result_index) - 1];
  carts_[uname].push_back(p);
}

void MyDataStore::viewCart(const std::string& username) const {
  //Check if username is valid
  std::string uname = toLower(username);
  std::map<std::string, User*>::const_iterator userit = users_.find(uname);
  if (userit == users_.end()) {
    std::cout << "Invalid username\n";
    return;
  }

  std::map<std::string, std::vector<Product*> >::const_iterator cit = carts_.find(uname);
  if (cit == carts_.end()) {
    // empty cart known or not created yet -> print nothing
    return;
  }

  const std::vector<Product*>& cart = cit->second;
  for (std::size_t i = 0; i < cart.size(); ++i) {
    std::cout << "Item " << (i + 1) << ":\n";
    std::cout << cart[i]->displayString() << "\n" << "\n";
  }
}

void MyDataStore::buyCart(const std::string& username) {
  //Check if username is valid
  std::string uname = toLower(username);
  std::map<std::string, User*>::iterator userit = users_.find(uname);
  if (userit == users_.end()) {
    std::cout << "Invalid username\n";
    return;
  }

  User* u = userit->second;
  std::vector<Product*>& cart = carts_[uname];

  std::vector<Product*> remaining;

  for (std::size_t i = 0; i < cart.size(); ++i) {
    Product* p = cart[i];

    //Check stock and balance
    if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
      p->subtractQty(1);
      u->deductAmount(p->getPrice());
    }
    else { //Out of stock or user is BROKE
      remaining.push_back(p);
    }
  }
  cart.swap(remaining);
}
