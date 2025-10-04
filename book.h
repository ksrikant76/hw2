#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include "product.h"

class Book : public Product {
 public:
    Book(const std::string& name, const std::string& isbn, const std::string& author, double price, int qty);
    virtual ~Book();

    //Returns the appropriate keywords that this book should be associated with
    virtual std::set<std::string> keywords() const;

    //Returns a string to display the book info for hits of the search
    virtual std::string displayString() const;

    //Outputs the book info in the database format
    virtual void dump(std::ostream& os) const;

    //Accessors
    std::string getISBN() const {return isbn_;}
    std::string getAuthor() const {return author_;}

 protected:
    std::string isbn_;
    std::string author_;
};

#endif
