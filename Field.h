#ifndef FIELD_
#define FIELD_
#include <vector>
class Field
{
    public:
        Field()=delete;
        Field(const std::vector<std::vector<int>> & trg);
        Field(std::vector<std::vector<int>> && trg); 
        int Weight( int x1, int y1, int x2, int y2 ) const; //O(1)
        int PathCost() const; //O(N)

    private:
        std::vector<std::vector<int>> values;
        std::vector<std::vector<int>> costsArray;
};
#endif