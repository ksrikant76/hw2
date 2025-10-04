#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
 public:
    MyDataStore();
    virtual ~MyDataStore();

    //Interface commands
    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);
    
    //Cart commands
    void addToCart(const std::string& username, int hit_result_index);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);
    
    //Access last search hits
    const std::vector<Product*>& getLastHits() const {return lastHits_;}
    
 private:
    //Helper function
    static std::string toLower(const std::string& s);
    
    //Storage
    std::vector<Product*> products_;
    std::map<std::string, User*> users_; //lowercase username -> User*
    std::map<std::string, std::set<Product*> > index_; //lowercase keyword -> set of Product*
    std::map<std::string, std::vector<Product*> > carts_; //lowercase username -> FIFO cart
    
    std::vector<Product*> lastHits_;
};

#endif
