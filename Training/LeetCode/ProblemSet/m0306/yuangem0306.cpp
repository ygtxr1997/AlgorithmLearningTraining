class AnimalShelf {
public:
    queue<int> Dog;
    queue<int> Cat;
    AnimalShelf() {

    }
    
    void enqueue(vector<int> animal) {
        int ind = animal[0], type = animal[1];
        if (type == 0) Cat.push(ind);
        else Dog.push(ind);
    }
    
    vector<int> dequeueAny() {
        if (Cat.empty() && Dog.empty()) return vector<int>(2, -1);
        if (Cat.empty()) return dequeueDog();
        if (Dog.empty()) return dequeueCat();
        int iDog = Dog.front(), iCat = Cat.front();
        if (iDog < iCat) {
            Dog.pop();
            return vector<int>({iDog, 1});
        } else {
            Cat.pop();
            return vector<int>({iCat, 0});
        }
    }
    
    vector<int> dequeueDog() {
        if (Dog.empty()) return vector<int>(2, -1);
        int iDog = Dog.front();
        Dog.pop();
        return vector<int>({iDog, 1});
    }
    
    vector<int> dequeueCat() {
        if (Cat.empty()) return vector<int>(2, -1);
        int iCat = Cat.front();
        Cat.pop();
        return vector<int>({iCat, 0});
    }
};

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */