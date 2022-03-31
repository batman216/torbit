//! Template Factory

#ifndef _FACTORYTEMPLATE_HPP_
#define _FACTORYTEMPLATE_HPP_
#include <iostream>
#include <string>
#include <map>
#include <memory>

template <typename t_Product> 
class Factory {
public:
	virtual t_Product *produce() = 0;
protected:
	Factory() {}	
	virtual ~Factory() {}
};

template <typename t_Product> class Proxy; /// forward declaration
	
template <typename t_Product, typename t_ConcreteProduct> 
class ConcreteFactory : public Factory<t_Product> {
public:
	explicit ConcreteFactory(std::string p_name) {
		Proxy<t_Product>::Instance().registerProduct(this,p_name);
	}
	t_Product *produce() { return new t_ConcreteProduct; }

};

/**
 *   The class Proxy is like a flyweight factory
 */
template <typename t_Product>
class Proxy {
	Proxy() {}  /// private creator for singleton
	Proxy(const Proxy& other) {}  
public:
	/**
	 *  The clicent fetch/purchase concrete product by p_name
	 *  according to the regedit
	 */
	std::map<std::string, Factory<t_Product>*> regedit;
	
	static Proxy<t_Product>& Instance() {
		static Proxy<t_Product> instance;
		/// Meyers Singleton: create an instance only when this function is called.
		return instance;
	}
	void registerProduct(Factory<t_Product>* reg, std::string p_name) {
		regedit[p_name] = std::move(reg);
	}

	constexpr t_Product* get(std::string p_name) { /// flyweight singleton
		if (regedit.find(p_name) != regedit.end())
			return regedit[p_name]->produce();
			/// produce	
		else {
			std::cout << "no product named " << p_name 
					<< " is registered." << std::endl;	
			return nullptr;
		}
	}
};


#endif /* _FACTORYTEMPLATE_HPP_ */
