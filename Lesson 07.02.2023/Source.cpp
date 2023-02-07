#include <iostream>
#include <windows.h>
#include <memory>


class A {
public:
	//A(A& a) = delete;данная конструкция написана внутри unique_ptr
	A() {
		std::cout << "Constructor" << std::endl;
	}
	~A() {
		std::cout << "Destructor" << std::endl;
	}

};
class Point {
public:
	Point(int x, int y) : _x(x), _y(y) {
		std::cout << "Point constructor" << std::endl;
	}
	int getX() const {
		return _x;
	}
	~Point() {
		std::cout << "Point destructor" << std::endl;
	}
private:
	int _x;
	int _y;

};
template<class T>
class SmartPtr {
T* _ptr;
public:
	SmartPtr(T* t) : _ptr(t) {}

	T* operator->() {
		return _ptr; //_ptr->operator->
	}
	T* get() {
		return _ptr;
	}
	~SmartPtr() {
		delete _ptr;
	}
	

};

//unique_ptr  как любой пользовательский тип можно передавать
//в параметры функции по ссылке
void basicFunc(std::unique_ptr<Point>& p) {//передали ссылку на птр и вернули указатель на х
	std::cout << p->getX() << std::endl;
}

class Parent{};
class Child : public Parent{};

std::shared_ptr<Parent> SomeMethod() { // b превратили в сслыку на а
	Child b;
	std::shared_ptr<Parent> a = std::make_shared<Parent>(b);
	return a;

}
class Ivehicle {
public:
	virtual int getSpeed() const = 0;
	virtual const std::string& getType() const = 0;
	virtual ~Ivehicle(){}
};
class Car : public Ivehicle {
public:
	Car(int speed) : _speed(speed) {}
		int getSpeed() const override {
			return _speed;
		}
		const std::string& getType() const override {
			return _type;
		}
private:
	int _speed;
	std::string _type = "Car";
};

class Van: public Car {
public:
	Van(int speed) : Car(speed) {}
	
	const std::string& getType() const override {
		return _type;
	}
private:
	std::string _type = "Van";
};
void funcCar(std::shared_ptr<Car> carPtr) {
	std::cout << "Inside funcCar" << std::endl;
	std::cout << carPtr->getSpeed() << std::endl;
	std::cout << carPtr->getType() << std::endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::shared_ptr<Van> v = std::make_shared<Van>(50);
	std::cout << v->getSpeed() << std::endl;
	std::cout << v->getType() << std::endl;
	std::cout << "+++++++++++++++++++" << std::endl;

	//std::dynamic_pointer_cast<type>(object to cast);
	std::shared_ptr<Car> c = std::dynamic_pointer_cast<Car>(v);
	//Car *c = dynamic_pointer_cast<Car*>(v);
	std::cout << c->getSpeed() << std::endl;
	std::cout << c->getType() << std::endl;
	std::cout << "+++++++++++++++++++" << std::endl;
	funcCar(c);

	/*std::auto_ptr<A> p(new A());
	std::auto_ptr<A> p2 = p;*/
	//auto_ptr - устарел и его не используют
	//shared_ptr-имеет контрольный блок, в котором
	// помимо прочего лежит счетчик указателей
	// unique_ptr-гарантирует, что только один указатель
	// будет владеть одним объектом
	//A* a = new A();

	//std::unique_ptr<A> uptr(new A());
	//std::unique_ptr<A> uptr2= uptr; так сделать нельзя

	//std::unique_ptr<Point> pPoint(new Point(5, 4));
	//std::cout << pPoint->getX() << std::endl;
	//pPoint.get()->getX();
	//pPoint.reset();//сбрасывает указатель


	
	//SmartPtr<Point>  sm(new Point(5, 4));
	//std::cout << sm->getX() << std::endl;
	////стрелочный оператор, если возвращает указатель, то в этом случае
	////на указатель снова вызывается стрелочный оператор рекурсивно
	////до тех пор пока не вернется объект

	//std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4);
	//std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);

	//std::shared_ptr<Point> sp2 = sp1;

	////basicFunc
}