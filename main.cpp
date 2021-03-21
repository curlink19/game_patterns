#include <cstdio>
#include <vector>
#include <utility>
#include <iostream>  

class Point {
public:
  int x;
  int y;
  int damage;

  Point():
    x(0),
    y(0),
    damage(0) {} 

  Point(int dx, int dy):
    x(dx),
    y(dy),
    damage(0) {} 
};

class Target {
private:
  Point aim;
  Point place;
  int time;

  Target():
    aim(Point()),
    place(Point()),
    time(0) {} 

  friend class Unit;
  friend class Archer;
  friend class FootSoldier;
};

class Unit {
protected:
  int health;
  int level;
  Point position;
  Target target;

  Unit():
    health(1),
    level(0),
    position(Point()),
    target(Target()) {} 

public:
  virtual void hit() = 0;
  virtual void move() = 0;
  virtual void shield() = 0;
  virtual void getDamage() = 0;
  virtual void print() = 0;

  friend class Cell;
};

class Archer: public Unit {
private:
  int bombCount;
public:
 
  Archer():
    Unit(),
    bombCount(0) {}
  
  void hit() override {}
  void move() override {} 
  void shield() override {}
  void getDamage() override {}

  void print() override { 
    int distx = position.x - target.aim.x;
    int disty = position.y - target.aim.y;
    if (std::abs(distx) > std::abs(disty)) {
      std::cout << (distx > 0 ? '^' : 'v');
    } else {
      std::cout << (disty > 0 ? '<' : '>');
    }
  }
};

class FootSoldier: public Unit {
private:
  int superTime;
public:

  FootSoldier():
    Unit(),
    superTime(0) {} 

  void hit() override {}
  void move() override {}
  void shield() override {}
  void getDamage() override {}

  void print() override {
    std::cout << level;
  }
};

class Cell {
public:
  Point point;
  Unit* unit;
  bool empty;

  Cell():
    point(Point()),
    unit(),
    empty(true) {} 

  void print() {
    if (!empty) { 
      unit->print();
    } else {
      std::cout << '.';
    }
  }

  void addUnit(Unit* var) {
    unit = var;
    unit->position = point;
    empty = false;
  }
};

class Border {
public:
  int height;
  int width;
  std::vector<std::vector<Cell>> field;

  Border(int n, int m):
    height(n),
    width(m),
    field(std::vector<std::vector<Cell>>(n, std::vector<Cell>(m, Cell()))) {
      for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
	  field[i][j].point = Point(i, j);
	}
      }
    } 

  void print() {
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        field[i][j].print();
      }
      std::cout << '\n';
    }
  }

  void addUnit(const Point& position, Unit* unit) {
    field[position.x][position.y].addUnit(unit);
  }
};

int main() {
  Border game(10, 10);
  return 0;
}
