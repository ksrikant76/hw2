#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>
#include <set>
#include "product.h"

class Clothing : public Product {
 public:
    Clothing(const std::string& name, const std::string& size, const std::string& brand, double price, int qty);
    virtual ~Clothing();

    //Returns the appropriate keywords that this clothing should be associated with                           
    virtual std::set<std::string> keywords() const;

    //Returns a string to display the clothing info for hits of the search                                    
    virtual std::string displayString() const;

    //Outputs the clothing info in the database format                                                        
    virtual void dump(std::ostream& os) const;

    //Accessors                                                                                               
    std::string getSize() const {return size_;}
    std::string getBrand() const {return brand_;}

 protected:
    std::string size_;
    std::string brand_;
};

#endif
