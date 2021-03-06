#ifndef LISTA_ATOMICA_H__
#define LISTA_ATOMICA_H__

#include <iostream>
#include <atomic>
#include <mutex>          // std::mutex

using namespace std;

template <typename T>
class Lista {
private:
	struct Nodo {
		Nodo(const T& val) : _val(val), _next(nullptr) {}
		T _val;
		Nodo *_next;
	};

	std::atomic<Nodo *> _head;
public:
	mutable std::mutex mtx;
	Lista() : _head(nullptr) {}
	~Lista() {
		Nodo *n, *t;
		n = _head.load();
		while (n) {
			t = n;
			n = n->_next;
			delete t;
		}
	}

	// Move initialization
  Lista(Lista&& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    _head = other._head().load(std::memory_order_relaxed);  
  }

  // Copy initialization
  Lista(const Lista& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    _head = other._head.load(std::memory_order_relaxed);
  }

  // Move assignment
  Lista& operator = (Lista&& other) {
    std::lock(mtx, other.mtx);
    std::lock_guard<std::mutex> self_lock(mtx, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.mtx, std::adopt_lock);
    _head = other._head().load(std::memory_order_relaxed);
    return *this;
  }

  // Copy assignment
  Lista& operator = (const Lista& other) {
    std::lock(mtx, other.mtx);
    std::lock_guard<std::mutex> self_lock(mtx, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.mtx, std::adopt_lock);
    _head = other._head.load(std::memory_order_relaxed);
    return *this;
  }

	void push_front(const T& val) {
		
		Nodo* nuevo = new Nodo(val);
		nuevo->_next = _head.exchange(nuevo);

	}

	T& front() const {
		return _head.load()->_val;
	}

	T& iesimo(int i) const {
		Nodo *n = _head.load();
		int j;
		for (int j = 0; j < i; j++)
			n = n->_next;
		return n->_val;
	}

	class Iterador {
	public:
		Iterador() : _lista(nullptr), _nodo_sig(nullptr) {}

		Iterador& operator = (const typename Lista::Iterador& otro) {
			_lista = otro._lista;
			_nodo_sig = otro._nodo_sig;
			return *this;
		}

		bool HaySiguiente() const {
			return _nodo_sig != nullptr;
		}

		T& Siguiente() {
			return _nodo_sig->_val;
		}

		void Avanzar() {
			_nodo_sig = _nodo_sig->_next;
		}

		bool operator == (const typename Lista::Iterador& otro) const {
			return _lista->_head.load() == otro._lista._head.load() && _nodo_sig == otro._nodo_sig;
		}

	private:
		Lista *_lista;

		typename Lista::Nodo *_nodo_sig;

		Iterador(Lista<T>* lista,typename Lista<T>::Nodo* sig) : _lista(lista), _nodo_sig(sig) {}
		friend typename Lista<T>::Iterador Lista<T>::CrearIt();
	};

	Iterador CrearIt() {
		return Iterador(this, _head);
	}
};

#endif /* LISTA_ATOMICA_H__ */
