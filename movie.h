#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <set>
#include "product.h"

class Movie : public Product {
 public:
    Movie(const std::string& name, const std::string& genre, const std::string& rating, double price, int qty);
    virtual ~Movie();

    //Returns the appropriate keywords that this movie should be associated with                              
    virtual std::set<std::string> keywords() const;

    //Returns a string to display the movie info for hits of the search                                       
    virtual std::string displayString() const;

    //Outputs the movie info in the database format                                                           
    virtual void dump(std::ostream& os) const;

    //Accessors                                                                                               
    std::string getGenre() const {return genre_;}
    std::string getRating() const {return rating_;}

 protected:
    std::string genre_;
    std::string rating_;
};

#endif
