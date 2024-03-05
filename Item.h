class Item
{
private:
    int weight;
    int utility;
public:
    Item(int weight, int utility);
};

Item::Item(int weight, int utility)
{
    this->weight = weight;
    this->utility = utility;
}