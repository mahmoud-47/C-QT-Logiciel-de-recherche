#ifndef BASE_H
#define BASE_H
#include "TableHachage.h"
//push_back pop_back size myvector.erase(myvector.begin() + i);
/*
 * A chaque fois qu on ajoute, on appelle insert de TableHash et on append dans adds si insert ne renvoie pas false.
 * A chaue fois qu on supprime, on appelle del de TableHah et on appelle delInAdds
*/

class Base{

public:
    Base() = default;
    void charger(TableHachage &);
};

#endif // BASE_H
