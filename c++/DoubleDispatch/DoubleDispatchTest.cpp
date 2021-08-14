

class SpaceShip {};
class GiantSpaceShip : public SpaceShip {};
 
class Asteroid {
public:
  virtual void CollideWith(SpaceShip&) {
    cout << "Asteroid hit a SpaceShip" << endl;
  }
  virtual void CollideWith(GiantSpaceShip&) {
    cout << "Asteroid hit a GiantSpaceShip" << endl;
  }
};
 
class ExplodingAsteroid : public Asteroid {
public:
  virtual void CollideWith(SpaceShip&) {
    cout << "ExplodingAsteroid hit a SpaceShip" << endl;
  }
  virtual void CollideWith(GiantSpaceShip&) {
    cout << "ExplodingAsteroid hit a GiantSpaceShip" << endl;
  }
};



